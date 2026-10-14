//###########################################################################
//
// FILE:    tasks_uart.c
//
// TITLE:   Tasks uart
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
#include "tasks_app.h"
#include "board.h"

#include "FreeRTOS.h"
#include "task.h"

#include <stdio.h>

//
// vUartLogTask - FreeRTOS task that logs tick, LED state, and stack usage over UART
//
void vUartLogTask(void *pvParameters)
{
    char line[160];
    TaskHandle_t led1Handle = NULL;
    TaskHandle_t led2Handle = NULL;
    TaskHandle_t selfHandle = xTaskGetCurrentTaskHandle();

    (void)pvParameters;

    for(;;)
    {
        led1Handle = xTaskGetHandle("Led1");
        led2Handle = xTaskGetHandle("Led2");

        snprintf(line, sizeof(line),
                 "Tick=%lu LED1=%u LED2=%u StackLed1=%lu StackLed2=%lu StackUart=%lu\r\n",
                 (unsigned long)xTaskGetTickCount(),
                 (unsigned int)Board_getLed1State(),
                 (unsigned int)Board_getLed2State(),
                 (unsigned long)((led1Handle != NULL) ? uxTaskGetStackHighWaterMark(led1Handle) : 0U),
                 (unsigned long)((led2Handle != NULL) ? uxTaskGetStackHighWaterMark(led2Handle) : 0U),
                 (unsigned long)uxTaskGetStackHighWaterMark(selfHandle));

        Board_uartWriteString(line);
        vTaskDelay(pdMS_TO_TICKS(400));
    }
}
