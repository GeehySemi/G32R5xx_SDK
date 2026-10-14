//###########################################################################
//
// FILE:    tasks_ipc.c
//
// TITLE:   CPU0 IPC command / response tasks (shared RAM + mailbox doorbell)
//
// VERSION: 1.1.0
//
// DATE:    2026-08-24
//
//###########################################################################
#include "tasks_app.h"
#include "board.h"
#include "driverlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include <math.h>
#include <stdio.h>

//
// g_ipcReq - Shared SRAM1 request bank (linker section visible to CPU1)
//
SECTION_SRAM1_SHARE_DATA volatile IpcReqBank g_ipcReq;
//
// g_ipcRsp - Shared SRAM2 response bank (linker section visible to CPU1)
//
SECTION_SRAM2_SHARE_DATA volatile IpcRspBank g_ipcRsp;

//
// g_ipcResultQueue - FreeRTOS queue from vIpcRspTask to vUartLogTask
//
QueueHandle_t g_ipcResultQueue = NULL;

//
// Ipc_waitTxEmpty - Blocks until the IPC transmit mailbox is empty
//
static void Ipc_waitTxEmpty(IPC_TxNumber tx)
{
    while(IPC_isTxBufferEmpty(tx) != true)
    {
        vTaskDelay(1);
    }
}

//
// Ipc_pollRx - Polls IPC receive mailbox until data arrives or timeout
//
static bool Ipc_pollRx(IPC_RxNumber rx, uint32_t *outWord, TickType_t waitTicks)
{
    TickType_t start = xTaskGetTickCount();

    while(IPC_isRxBufferFull(rx) != true)
    {
        if((xTaskGetTickCount() - start) >= waitTicks)
        {
            return false;
        }
        vTaskDelay(1);
    }

    *outWord = IPC_receive32Bits(rx);
    return true;
}

//
// vIpcCmdTask - Posts sinf phase requests to shared RAM and rings IPC doorbell
//
void vIpcCmdTask(void *pvParameters)
{
    uint32_t seq = 1U;
    float phase = 0.0f;

    (void)pvParameters;

    g_ipcReq.status = IPC_BUF_IDLE;
    g_ipcRsp.status = IPC_BUF_IDLE;

    vTaskDelay(pdMS_TO_TICKS(200));

    for(;;)
    {
        while(g_ipcReq.status == IPC_BUF_READY)
        {
            vTaskDelay(1);
        }

        g_ipcReq.seq = seq;
        g_ipcReq.op = (uint32_t)IPC_OP_SINF;
        g_ipcReq.arg0 = phase;
        g_ipcReq.reserved = 0U;
        __DMB();
        g_ipcReq.status = IPC_BUF_READY;
        __DMB();

        Ipc_waitTxEmpty(IPC_TX_0);
        IPC_transmit32Bits(IPC_TX_0, IPC_DOOR_REQ_MAGIC | (seq & IPC_DOOR_SEQ_MASK));

        phase += IPC_DEMO_PHASE_STEP;
        if(phase >= IPC_DEMO_TWO_PI)
        {
            phase -= IPC_DEMO_TWO_PI;
        }

        seq++;
        vTaskDelay(pdMS_TO_TICKS(IPC_DEMO_IPC_PERIOD_MS));
    }
}

//
// vIpcRspTask - Collects CPU1 responses, computes ref/abs_err, enqueues for UART
//
void vIpcRspTask(void *pvParameters)
{
    uint32_t door = 0U;
    IpcResultMsg msg;

    (void)pvParameters;

    for(;;)
    {
        if(Ipc_pollRx(IPC_RX_0, &door, pdMS_TO_TICKS(1000)) != true)
        {
            if(g_ipcRsp.status != IPC_BUF_READY)
            {
                continue;
            }
        }

        if(g_ipcRsp.status != IPC_BUF_READY)
        {
            continue;
        }

        __DMB();
        msg.seq = g_ipcRsp.seq;
        msg.phase = g_ipcRsp.arg0;
        msg.result = g_ipcRsp.result;
        msg.ref = sinf(msg.phase);
        msg.absErr = fabsf(msg.result - msg.ref);
        msg.err = g_ipcRsp.err;
        __DMB();
        g_ipcRsp.status = IPC_BUF_IDLE;
        g_ipcReq.status = IPC_BUF_IDLE;

        if(g_ipcResultQueue != NULL)
        {
            (void)xQueueSend(g_ipcResultQueue, &msg, 0);
        }
    }
}

//
// vUartLogTask - FreeRTOS task that prints IPC results (phase/ref/abs_err) over UART
//
void vUartLogTask(void *pvParameters)
{
    IpcResultMsg msg;
    char line[192];

    (void)pvParameters;

    for(;;)
    {
        if(xQueueReceive(g_ipcResultQueue, &msg, pdMS_TO_TICKS(2000)) == pdTRUE)
        {
            snprintf(line, sizeof(line),
                     "IPC seq=%lu phase=%.6frad result=%.6f ref=%.6f abs_err=%.2e err=%lu\r\n",
                     (unsigned long)msg.seq,
                     (double)msg.phase,
                     (double)msg.result,
                     (double)msg.ref,
                     (double)msg.absErr,
                     (unsigned long)msg.err);
            Board_uartWriteString(line);
        }
        else
        {
            Board_uartWriteString("IPC wait timeout\r\n");
        }
    }
}
