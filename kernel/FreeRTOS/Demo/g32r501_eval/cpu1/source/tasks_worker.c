//###########################################################################
//
// FILE:    tasks_worker.c
//
// TITLE:   CPU1 worker: shared-RAM request + Zidian + IPC doorbell response
//
// VERSION: 1.1.0
//
// DATE:    2026-08-24
//
//###########################################################################
#include "tasks_app.h"
#include "board.h"
#include "driverlib.h"
#include "ipc_shm_msg.h"
#include "zidian_math.h"

#include "FreeRTOS.h"
#include "task.h"

//
// g_ipcReq - Shared SRAM1 request bank (same physical layout as CPU0)
//
SECTION_SRAM1_SHARE_DATA volatile IpcReqBank g_ipcReq;
//
// g_ipcRsp - Shared SRAM2 response bank (same physical layout as CPU0)
//
SECTION_SRAM2_SHARE_DATA volatile IpcRspBank g_ipcRsp;

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
// vIpcWorkerTask - Handles shared-RAM sinf requests via Zidian and replies by IPC doorbell
//
void vIpcWorkerTask(void *pvParameters)
{
    uint32_t door = 0U;
    uint32_t seq;
    uint32_t op;
    float arg0;
    float result = 0.0f;
    uint32_t err = 0U;

    (void)pvParameters;

    g_ipcReq.status = IPC_BUF_IDLE;
    g_ipcRsp.status = IPC_BUF_IDLE;

    for(;;)
    {
        if(Ipc_pollRx(IPC_RX_0, &door, pdMS_TO_TICKS(1000)) != true)
        {
            if(g_ipcReq.status != IPC_BUF_READY)
            {
                continue;
            }
        }

        if(g_ipcReq.status != IPC_BUF_READY)
        {
            continue;
        }

        __DMB();
        seq = g_ipcReq.seq;
        op = g_ipcReq.op;
        arg0 = g_ipcReq.arg0;
        g_ipcReq.status = IPC_BUF_BUSY;
        __DMB();

        err = 0U;
        result = 0.0f;

        if(op == (uint32_t)IPC_OP_SINF)
        {
            result = sinf(arg0);
        }
        else
        {
            err = 1U;
        }

        g_ipcRsp.seq = seq;
        g_ipcRsp.op = op;
        g_ipcRsp.err = err;
        g_ipcRsp.arg0 = arg0;
        g_ipcRsp.result = result;
        __DMB();
        g_ipcRsp.status = IPC_BUF_READY;
        __DMB();

        Ipc_waitTxEmpty(IPC_TX_0);
        IPC_transmit32Bits(IPC_TX_0, IPC_DOOR_RSP_MAGIC | (seq & IPC_DOOR_SEQ_MASK));
    }
}
