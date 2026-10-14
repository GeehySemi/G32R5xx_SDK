//###########################################################################
//
// FILE:    tasks_led.c
//
// TITLE:   Tasks led
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

//
// vLed1Task - FreeRTOS task that toggles LED1 periodically
//
void vLed1Task(void *pvParameters)
{
    (void)pvParameters;

    for(;;)
    {
        Board_toggleLed1();
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

//
// vLed2Task - FreeRTOS task that toggles LED2 periodically
//
void vLed2Task(void *pvParameters)
{
    (void)pvParameters;

    vTaskDelay(pdMS_TO_TICKS(250));

    for(;;)
    {
        Board_toggleLed2();
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
