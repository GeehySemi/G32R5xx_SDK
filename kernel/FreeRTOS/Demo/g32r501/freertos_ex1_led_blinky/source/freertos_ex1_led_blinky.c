//#############################################################################
//
// FILE:    freertos_ex1_led_blinky.c
//
// TITLE:   FreeRTOS led blinky example
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//#############################################################################
// $Copyright:
// Copyright (C) 2024 Geehy Semiconductor - http://www.geehy.com/
// Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.com/
//
// SPDX-License-Identifier: MIT
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
///
// $
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define STACK_SIZE  256U
#define RED         0xDEADBEAF
#define GREEN       0xBAADF00D

static StaticTask_t redTask_Buffer;
static StackType_t  redTask_Stack[STACK_SIZE];

static StaticTask_t greenTask_Buffer;
static StackType_t  greenTask_Stack[STACK_SIZE];

static StaticTask_t idleTask_Buffer;
static StackType_t  idleTask_Stack[STACK_SIZE];

static SemaphoreHandle_t xSemaphore = NULL;
static StaticSemaphore_t xSemaphoreBuffer;

void SysTick_Handler(void);
void PendSV_Handler(void);
void SVC_Handler(void);

//-------------------------------------------------------------------------------------------------

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
    while(1);
}

//-------------------------------------------------------------------------------------------------
static void LedGreen_Toggle(void)
{
    static uint32_t counter = 0;

    counter++;
    GPIO_writePin(34, counter & 0x1);
}

//-------------------------------------------------------------------------------------------------
static void LedRed_Toggle(void)
{
    static uint32_t counter = 0;

    counter++;
    GPIO_writePin(23, counter & 0x1);
}

//-------------------------------------------------------------------------------------------------
static void Led_Toggle(uint32_t led)
{
    if(RED == led)
    {
        LedRed_Toggle();
    }
    else
    if(GREEN == led)
    {
        LedGreen_Toggle();
    } 
}

//
// configTMR - This function initializes the selected timer to the
// period specified by the "freq" and "period" variables. The "freq" is
// CPU frequency in Hz and the period in uSeconds. The timer is held in
// the stopped state after configuration.
//
void
configTMR(uint32_t TMR, uint32_t period)
{
    uint32_t temp, freq = DEVICE_SYSCLK_FREQ;

    //
    // Initialize timer period:
    //
    temp = ((freq / 1000000) * period);
    TMR_setPeriod(TMR, temp);

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    TMR_setPreScaler(TMR, 0);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    //
    TMR_stopTimer(TMR);
    TMR_reloadTimerCounter(TMR);
    TMR_setEmulationMode(TMR,
                              TMR_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    TMR_enableInterrupt(TMR);

}

//-------------------------------------------------------------------------------------------------
interrupt void Tmr1_ISR( void )
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xSemaphoreGiveFromISR( xSemaphore, &xHigherPriorityTaskWoken );

    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

//-------------------------------------------------------------------------------------------------
static void Tmr1_Init( void )
{
    Interrupt_register(INT_TIMER1, &Tmr1_ISR);

    TMR_setPeriod(TMR1_BASE, 0xFFFFFFFF);
    TMR_setPreScaler(TMR1_BASE, 0);
    TMR_stopTimer(TMR1_BASE);
    TMR_reloadTimerCounter(TMR1_BASE);

    configTMR(TMR1_BASE, 100000);

    TMR_enableInterrupt(TMR1_BASE);

    Interrupt_enable(INT_TIMER1);
    TMR_startTimer(TMR1_BASE);
}

//-------------------------------------------------------------------------------------------------
void RedLED_Task(void * pvParameters)
{
    for(;;)
    {
        if(xSemaphoreTake( xSemaphore, portMAX_DELAY ) == pdTRUE)
        {
            Led_Toggle((uint32_t)pvParameters);
        }
    }
}

//-------------------------------------------------------------------------------------------------
void GreenLED_Task(void * pvParameters)
{
    for(;;)
    {
        Led_Toggle((uint32_t)pvParameters);
        vTaskDelay(250 / portTICK_PERIOD_MS);
    }
}

//-------------------------------------------------------------------------------------------------

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
    *ppxIdleTaskTCBBuffer = &idleTask_Buffer;
    *ppxIdleTaskStackBuffer = idleTask_Stack;
    *pulIdleTaskStackSize = STACK_SIZE;
}

//-------------------------------------------------------------------------------------------------


//
// Main
//
void example_main(void)
{
    //
    // Initializes system control, device clock, and peripherals
    //
    Device_init();
    GPIO_setDrivingCapability(34,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(34, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(34, GPIO_DIR_MODE_OUT);
    GPIO_setDrivingCapability(23,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(23, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(23, GPIO_DIR_MODE_OUT);

    GPIO_writePin(34, 1);
    GPIO_writePin(23, 1);

    //
    // Initializes NVIC and clears NVIC registers. Disables CPU interrupts.
    // and clear all CPU interrupt flags.
    //
    Interrupt_initModule();

    //
    // Initializes the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    Interrupt_register(INT_SVCALL, &SVC_Handler);
    Interrupt_register(INT_PENDSV, &PendSV_Handler);
    Interrupt_register(INT_SYSTICK, &SysTick_Handler);

    xSemaphore = xSemaphoreCreateBinaryStatic( &xSemaphoreBuffer );

    Tmr1_Init();

    // Create the task without using any dynamic memory allocation.
    xTaskCreateStatic(RedLED_Task,          // Function that implements the task.
                      "Red LED task",       // Text name for the task.
                      STACK_SIZE,           // Number of indexes in the xStack array.
                      ( void * ) RED,       // Parameter passed into the task.
                      tskIDLE_PRIORITY + 2, // Priority at which the task is created.
                      redTask_Stack,         // Array to use as the task's stack.
                      &redTask_Buffer );     // Variable to hold the task's data structure.

    xTaskCreateStatic(GreenLED_Task,         // Function that implements the task.
                      "Green LED task",      // Text name for the task.
                      STACK_SIZE,           // Number of indexes in the xStack array.
                      ( void * ) GREEN,      // Parameter passed into the task.
                      tskIDLE_PRIORITY + 1, // Priority at which the task is created.
                      greenTask_Stack,        // Array to use as the task's stack.
                      &greenTask_Buffer );    // Variable to hold the task's data structure.

    vTaskStartScheduler();
}


//
// End of File
//

