//###########################################################################
//
// FILE:    tasks_led.c
//
// TITLE:   LED tasks
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
