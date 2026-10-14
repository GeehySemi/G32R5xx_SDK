//###########################################################################
//
// FILE:    main.c
//
// TITLE:   g32r501_eval CPU0 FreeRTOS + shared-RAM IPC entry
//
// VERSION: 1.1.0
//
// DATE:    2026-08-24
//
//###########################################################################
#include "device.h"
#include "board.h"
#include "tasks_app.h"
#include "driverlib.h"
#include "ipc_shm_msg.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include <stdio.h>

extern QueueHandle_t g_ipcResultQueue;

#define IPC_RESULT_QUEUE_LEN   (8U)

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
  extern uint32_t Image$$ER_ROM_CPU1$$Base;
  extern uint32_t Image$$ER_ROM_CPU1$$Length;
#elif defined(__ICCARM__)
  extern unsigned char cpu1_image_start[];
#elif defined (__clang__) && !defined (__ARMCC_VERSION)
  extern const char __cpu1_image_start__;
  extern const char __cpu1_image_end__;
#endif

//
// G32R501_incbin - Embeds cpu1_image.bin into CPU0 flash for CPU1 boot (MDK)
//
#if defined(__ARMCC_VERSION)
__attribute__((__used__, section("cpu1_code")))
void G32R501_incbin(void)
{
    __asm(".incbin \"../../source/cpu1_image.bin\"");
}
//
// G32R501_incbin - Embeds cpu1_image.bin into CPU0 flash for CPU1 boot (Eclipse/GCC)
//
#elif defined (__clang__) && !defined(__ARMCC_VERSION)
__attribute__((__used__, section("cpu1_code")))
void G32R501_incbin(void)
{
    __asm(".incbin \"../cpu1_image.bin\"");
}
#endif

//
// APP_bootCPU1 - Sets CPU1 boot address and releases CPU1 from reset
//
static void APP_bootCPU1(uint32_t cpu1Address)
{
    SysCtl_setCPU1BootAddress(cpu1Address);
    SysCtl_enableBootCPU1();
}

//
// main - CPU0 application entry: boot CPU1, create IPC/UART tasks, start scheduler
//
int main(void)
{
    uint32_t cpu1_imageSize = 0U;
    uint32_t cpu1_imageStartAddr = 0U;
    char line[96];

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
    cpu1_imageSize = (uint32_t)&Image$$ER_ROM_CPU1$$Length;
    cpu1_imageStartAddr = (uint32_t)&Image$$ER_ROM_CPU1$$Base;
#elif defined(__ICCARM__)
    #pragma section = "__cpu1_image"
    cpu1_imageSize = (uint32_t)__section_end("__cpu1_image") - (uint32_t)&cpu1_image_start;
    cpu1_imageStartAddr = (uint32_t)&cpu1_image_start;
#elif defined (__clang__) && !defined (__ARMCC_VERSION)
    cpu1_imageSize = (uint32_t)&__cpu1_image_end__ - (uint32_t)&__cpu1_image_start__;
    cpu1_imageStartAddr = (uint32_t)&__cpu1_image_start__;
#endif

    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    Board_init();
    Interrupt_enableMaster();

    Board_uartWriteString("\r\nFreeRTOS g32r501_eval CPU0 Ready\r\n");
    snprintf(line, sizeof(line),
             "CPU1 boot addr=0x%08lx size=0x%lx\r\n",
             (unsigned long)cpu1_imageStartAddr,
             (unsigned long)cpu1_imageSize);
    Board_uartWriteString(line);

    APP_bootCPU1(cpu1_imageStartAddr);
    DEVICE_DELAY_US(100000);

    g_ipcResultQueue = xQueueCreate(IPC_RESULT_QUEUE_LEN, sizeof(IpcResultMsg));

    xTaskCreate(vLed1Task, "Led1", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(vIpcCmdTask, "IpcCmd", configMINIMAL_STACK_SIZE * 2U, NULL, 3, NULL);
    xTaskCreate(vIpcRspTask, "IpcRsp", configMINIMAL_STACK_SIZE * 2U, NULL, 3, NULL);
    xTaskCreate(vUartLogTask, "Uart", configMINIMAL_STACK_SIZE * 3U, NULL, 1, NULL);

    vTaskStartScheduler();

    for(;;)
    {
    }
}

//
// vApplicationStackOverflowHook - FreeRTOS stack overflow hook; reports the task name and halts
//
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask;
    Board_uartWriteString("StackOverflow: ");
    Board_uartWriteString(pcTaskName);
    Board_uartWriteString("\r\n");
    taskDISABLE_INTERRUPTS();
    for(;;)
    {
    }
}
