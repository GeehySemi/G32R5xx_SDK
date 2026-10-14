//###########################################################################
//
// FILE:    main.c
//
// TITLE:   Main
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//###########################################################################
//
//
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
//
// You may not use this file except in compliance with the
// GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
//
// The program is only for reference, which is distributed in the hope
// that it will be useful and instructional for customers to develop
// their software. Unless required by applicable law or agreed to in
// writing, the program is distributed on an "AS IS" BASIS, WITHOUT
// ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
// See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
// and limitations under the License.
// $
//###########################################################################
//
#include "device.h"
#include "board.h"
#include "tasks_app.h"

#include "FreeRTOS.h"
#include "task.h"

#include <stdio.h>

//
// main - Application entry point
//
int main(void)
{
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    Board_init();

    Board_uartWriteString("FreeRTOS Eval Ready\r\n");

    xTaskCreate(vLed1Task, "Led1", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(vLed2Task, "Led2", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(vUartLogTask, "Uart", configMINIMAL_STACK_SIZE * 2U, NULL, 1, NULL);

    vTaskStartScheduler();

    for(;;)
    {
    }
}

//
// vApplicationStackOverflowHook - FreeRTOS stack overflow hook; reports the task name and halts
//
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
    (void)xTask;
    Board_uartWriteString("StackOverflow: ");
    Board_uartWriteString( pcTaskName );
    Board_uartWriteString("\r\n");
    taskDISABLE_INTERRUPTS();
    for(;;)
    {
    }
}
