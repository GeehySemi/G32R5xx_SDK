//###########################################################################
//
// FILE:    tasks_led.c
//
// TITLE:   LED tasks (CPU1)
//
// VERSION: 1.0.0
//
// DATE:    2026-08-24
//
//###########################################################################
#include "tasks_app.h"
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

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
