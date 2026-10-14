//###########################################################################
//
// FILE:    main.c
//
// TITLE:   g32r501_eval CPU1 FreeRTOS + Zidian worker entry
//
// VERSION: 1.0.0
//
// DATE:    2026-08-24
//
//###########################################################################
#include "device.h"
#include "board.h"
#include "tasks_app.h"

#include "FreeRTOS.h"
#include "task.h"

//
// main - CPU1 application entry: create LED/worker tasks and start scheduler
//
int main(void)
{
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    Board_init();
    Interrupt_enableMaster();

    xTaskCreate(vLed2Task, "Led2", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(vIpcWorkerTask, "Worker", configMINIMAL_STACK_SIZE * 3U, NULL, 3, NULL);

    vTaskStartScheduler();

    for(;;)
    {
    }
}

//
// vApplicationStackOverflowHook - FreeRTOS stack overflow hook; disables interrupts and halts
//
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask;
    (void)pcTaskName;
    taskDISABLE_INTERRUPTS();
    for(;;)
    {
    }
}
