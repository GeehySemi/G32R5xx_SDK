//#############################################################################
//
// FILE:    cap_ex2_capture_pwm.c
//
// TITLE:   Capture PWM3.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1>CAP Capture PWM Example</h1>
//!
//! This example configures PWM3A for:
//! - Up count mode
//! - Period starts at 500 and goes up to 8000
//! - Toggle output on PRD
//!
//! CAP1 is configured to capture the time between rising
//! and falling edge of the PWM3A output.
//!
//! \b External \b Connections \n
//! - CAP1 is on GPIO16
//! - PWM3A is on GPIO4
//! - Connect GPIO4 to GPIO16.
//!
//! \b Watch \b Variables \n
//! - \b cap1PassCount - Successful captures.
//! - \b cap1IntCount - Interrupt counts.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2024 Geehy Semiconductor - http://www.geehy.com/
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//
// Modifications:
// - 2024-09-13:
// 1. Modify some comments, macros, function names, and function contents.
//
//###########################################################################


//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Defines
//
#define PWM3_TIMER_MIN     500U
#define PWM3_TIMER_MAX     8000U
#define PWM_TIMER_UP      1U
#define PWM_TIMER_DOWN    0U

//
// Globals
//
uint32_t cap1IntCount;
uint32_t cap1PassCount;
uint32_t pwm3TimerDirection;
volatile uint16_t cap2Count;
volatile uint16_t cap3Count;
volatile uint16_t cap4Count;
volatile uint16_t pwm3PeriodCount;

//
// Function Prototypes
//
void error(void);
void initCAP(void);
void initPWM(void);

//
// Main
//
void example_main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Initialize NVIC and clears NVIC registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Configure GPIO4/5 as PWM3A/3B
    //
    GPIO_setDrivingCapability(4,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(4,GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_4_PWM3_A);
    GPIO_setDrivingCapability(5,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(5,GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_5_PWM3_B);

    //
    // Board initialization
    // Configure GPIO 16 as CAP input
    // Enable interrupts required for this example
    //
    Board_init();
    
    //
    // Configure PWM
    //
    initPWM();

    //
    // Initialize counters:
    //
    cap2Count = 0U;
    cap3Count = 0U;
    cap4Count = 0U;
    cap1IntCount = 0U;
    cap1PassCount = 0U;
    pwm3PeriodCount = 0U;

    //
    // Enable Global Interrupt (INTM) and Real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop forever. Suspend or place breakpoints to observe the buffers.
    //
    for(;;)
    {
       NOP;
    }
}

//
// initPWM - Configure PWM
//
void initPWM()
{
    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure PWM
    //       Counter runs in up-count mode.
    //       Action qualifier will toggle output on period match
    //
    PWM_setTimeBaseCounterMode(PWM3_BASE, PWM_COUNTER_MODE_UP);
    PWM_setTimeBasePeriod(PWM3_BASE, PWM3_TIMER_MIN);
    PWM_setPhaseShift(PWM3_BASE, 0U);
    PWM_setActionQualifierAction(PWM3_BASE,
                                  PWM_AQ_OUTPUT_A,
                                  PWM_AQ_OUTPUT_TOGGLE,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    PWM_setClockPrescaler(PWM3_BASE,
                           PWM_CLOCK_DIVIDER_1,
                           PWM_HSCLOCK_DIVIDER_2);

    pwm3TimerDirection = PWM_TIMER_UP;

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

//
// myCAP0 ISR
//
void INT_myCAP0_ISR(void)
{
    //
    // Get the capture counts. Each capture should be 2x the PWM count
    // because of the PWM clock divider.
    //
    cap2Count = CAP_getEventTimeStamp(myCAP0_BASE, CAP_EVENT_2);
    cap3Count = CAP_getEventTimeStamp(myCAP0_BASE, CAP_EVENT_3);
    cap4Count = CAP_getEventTimeStamp(myCAP0_BASE, CAP_EVENT_4);

    //
    // Compare the period value with the captured count
    //
    pwm3PeriodCount = PWM_getTimeBasePeriod(PWM3_BASE);

    if(cap2Count > ((pwm3PeriodCount *2) + 2U) ||
       cap2Count < ((pwm3PeriodCount *2) - 2U))
    {
        error();
    }

    if(cap3Count > ((pwm3PeriodCount *2) + 2U) ||
       cap3Count < ((pwm3PeriodCount *2) - 2U))
    {
        error();
    }

    if(cap4Count > ((pwm3PeriodCount *2) + 2U) ||
       cap4Count < ((pwm3PeriodCount *2) - 2U))
    {
        error();
    }

    cap1IntCount++;

    //
    // Keep track of the PWM direction and adjust period accordingly to
    // generate a variable frequency PWM.
    //
    if(pwm3TimerDirection == PWM_TIMER_UP)
    {
        if(pwm3PeriodCount < PWM3_TIMER_MAX)
        {
           PWM_setTimeBasePeriod(PWM3_BASE, ++pwm3PeriodCount);
        }
        else
        {
           pwm3TimerDirection = PWM_TIMER_DOWN;
           PWM_setTimeBasePeriod(PWM3_BASE, ++pwm3PeriodCount);
        }
    }
    else
    {
        if(pwm3PeriodCount > PWM3_TIMER_MIN)
        {
            PWM_setTimeBasePeriod(PWM3_BASE, --pwm3PeriodCount);
        }
        else
        {
           pwm3TimerDirection = PWM_TIMER_UP;
           PWM_setTimeBasePeriod(PWM3_BASE, ++pwm3PeriodCount);
        }
    }

    //
    // Count correct captures
    //
    cap1PassCount++;

    //
    // Clear interrupt flags for more interrupts.
    //
    CAP_clearInterrupt(myCAP0_BASE,CAP_ISR_SOURCE_CAPTURE_EVENT_4);
    CAP_clearGlobalInterrupt(myCAP0_BASE);

    //
    // Start CAP
    //
    CAP_reArm(myCAP0_BASE);
}

//
// error - Error function
//
void error()
{
    ESTOP0;
}
