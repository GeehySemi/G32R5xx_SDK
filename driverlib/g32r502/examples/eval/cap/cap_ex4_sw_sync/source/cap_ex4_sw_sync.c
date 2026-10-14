//#############################################################################
//
// FILE:    cap_ex4_sw_sync.c
//
// TITLE:   Software Sync.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1>CAP Software Sync Example</h1>
//!
//! This example configures PWM3A for:
//! - Up count mode
//! - Period starts at 500 and goes up to 8000
//! - Toggle output on PRD
//!
//! CAP1, CAP2 and CAP3 are configured to capture the time between rising
//! and falling edge of the PWM3A output.
//!
//! \b External \b Connections \n
//! - CAP1, CAP2, CAP3 are on GPIO16
//! - PWM3A is on GPIO4
//! - Connect GPIO4 to GPIO16.
//!
//! \b Watch \b Variables \n
//! - \b capPassCount - Successful captures.
//! - \b cap3IntCount - Interrupt counts.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
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
// - 2026-06-30:
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
bool firstInterrupt;
uint32_t cap3IntCount;
uint32_t capPassCount;
uint32_t pwm3TimerDirection;
volatile uint16_t pwm3PeriodCount;
volatile uint16_t cap1Cap1Count;
volatile uint16_t cap1Cap2Count;
volatile uint16_t cap1Cap3Count;
volatile uint16_t cap1Cap4Count;
volatile uint16_t cap2Cap1Count;
volatile uint16_t cap2Cap2Count;
volatile uint16_t cap2Cap3Count;
volatile uint16_t cap2Cap4Count;
volatile uint16_t cap3Cap1Count;
volatile uint16_t cap3Cap2Count;
volatile uint16_t cap3Cap3Count;
volatile uint16_t cap3Cap4Count;

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
    // switch clock
    //
    Clockswitch();
    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Globally disable interrupts and clear all NVIC enable/pending bits
    //
    Interrupt_initModule();

    //
    // Initialize RAM vector table and set VTOR; unregistered IRQs use
    // Interrupt_defaultHandler until Interrupt_register() is called
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
    //
    Board_init();
    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    // Set the priority group to indicate the PREEMPT and SUB priortiy bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);
    //
    // Set the global and group priority to allow CPU interrupts
    // with higher priority
    //
    Interrupt_setPriority(INT_myCAP3, 0, 0);
    Interrupt_register(INT_myCAP3, &INT_myCAP3_ISR);
    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_myCAP3);


    //
    // Configure PWM
    //
    initPWM();
    
    //
    // Initialize counters: and values
    //
    firstInterrupt = true;
    cap3IntCount = 0U;
    capPassCount = 0U;
    pwm3PeriodCount = 0U;
    cap1Cap1Count = 0U;
    cap1Cap2Count = 0U;
    cap1Cap3Count = 0U;
    cap1Cap4Count = 0U;
    cap2Cap1Count = 0U;
    cap2Cap2Count = 0U;
    cap2Cap3Count = 0U;
    cap2Cap4Count = 0U;
    cap3Cap1Count = 0U;
    cap3Cap2Count = 0U;
    cap3Cap3Count = 0U;
    cap3Cap4Count = 0U;

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
// myCAP3 ISR
//
void INT_myCAP3_ISR(void)
{
    //
    // Get the capture counts. Each capture should match for all the CAPs. 
    //
    cap1Cap1Count = CAP_getEventTimeStamp(myCAP1_BASE, CAP_EVENT_1);
    cap1Cap2Count = CAP_getEventTimeStamp(myCAP1_BASE, CAP_EVENT_2);
    cap1Cap3Count = CAP_getEventTimeStamp(myCAP1_BASE, CAP_EVENT_3);
    cap1Cap4Count = CAP_getEventTimeStamp(myCAP1_BASE, CAP_EVENT_4);
    cap2Cap1Count = CAP_getEventTimeStamp(myCAP2_BASE, CAP_EVENT_1);
    cap2Cap2Count = CAP_getEventTimeStamp(myCAP2_BASE, CAP_EVENT_2);
    cap2Cap3Count = CAP_getEventTimeStamp(myCAP2_BASE, CAP_EVENT_3);
    cap2Cap4Count = CAP_getEventTimeStamp(myCAP2_BASE, CAP_EVENT_4);
    cap3Cap1Count = CAP_getEventTimeStamp(myCAP3_BASE, CAP_EVENT_1);
    cap3Cap2Count = CAP_getEventTimeStamp(myCAP3_BASE, CAP_EVENT_2);
    cap3Cap3Count = CAP_getEventTimeStamp(myCAP3_BASE, CAP_EVENT_3);
    cap3Cap4Count = CAP_getEventTimeStamp(myCAP3_BASE, CAP_EVENT_4);

    //
    // Compare the period value with the captured count
    //
    pwm3PeriodCount = PWM_getTimeBasePeriod(PWM3_BASE);
    
    //
    // Validate synchronization. 
    //
    if(firstInterrupt){
        firstInterrupt = false;
    }
    else{
        if (!((cap1Cap1Count == cap2Cap1Count)&&(cap2Cap1Count == cap3Cap1Count)))
        {
            error();
        }
    }
    if (!((cap1Cap2Count == cap2Cap2Count)&&(cap2Cap2Count == cap3Cap2Count)))
    {
        error();
    }
    if (!((cap1Cap3Count == cap2Cap3Count)&&(cap2Cap3Count == cap3Cap3Count)))
    {
        error();
    }
    if (!((cap1Cap4Count == cap2Cap4Count)&&(cap2Cap4Count == cap3Cap4Count)))
    {
        error();
    }

    cap3IntCount++;

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
    capPassCount++;

    //
    // Clear interrupt flags for more interrupts.
    //
    CAP_clearInterrupt(myCAP3_BASE,CAP_ISR_SOURCE_CAPTURE_EVENT_4);
    CAP_clearGlobalInterrupt(myCAP3_BASE);

    //
    // Start CAP
    //
    CAP_reArm(myCAP1_BASE);
    CAP_reArm(myCAP2_BASE);
    CAP_reArm(myCAP3_BASE);
}

//
// error - Error function
//
void error()
{
    ESTOP0;
}
