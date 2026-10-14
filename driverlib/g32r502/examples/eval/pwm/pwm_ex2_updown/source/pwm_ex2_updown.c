//#############################################################################
//
// FILE:    pwm_ex2_updown.c
//
// TITLE:   PWM Action Qualifier Module - Using up/down count.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1> PWM Up Down Count Action Qualifier</h1>
//!
//! This example configures PWM1, PWM2, PWM3 to produce a waveform with
//! independent modulation on PWMxA and PWMxB.
//!
//! The compare values CMPA and CMPB are modified within the PWM's ISR.
//!
//! The TB counter is in up/down count mode for this example.
//!
//! View the PWM1A/B(GPIO0 & GPIO1), PWM2A/B(GPIO2 &GPIO3)
//! and PWM3A/B(GPIO4 & GPIO5) waveforms on oscilloscope.
//! \b External \b Connections \n
//!  - Optional: probe EPWM outputs on the EVAL header.
//!
//! \b Watch \b Variables \n
//!  - None.
//!
//
//#############################################################################
//
//
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
// 1. Modified some function and macro definition and variable names.
// 2. Updated interrupt handling to use NVIC functions.
//
//###########################################################################

#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Defines
//
#define PWM1_TIMER_TBPRD  2000U
#define PWM1_MAX_CMPA     1950U
#define PWM1_MIN_CMPA       50U
#define PWM1_MAX_CMPB     1950U
#define PWM1_MIN_CMPB       50U

#define PWM2_TIMER_TBPRD  2000U
#define PWM2_MAX_CMPA     1950U
#define PWM2_MIN_CMPA       50U
#define PWM2_MAX_CMPB     1950U
#define PWM2_MIN_CMPB       50U

#define PWM3_TIMER_TBPRD  2000U
#define PWM3_MAX_CMPA      950U
#define PWM3_MIN_CMPA       50U
#define PWM3_MAX_CMPB     1950U
#define PWM3_MIN_CMPB     1050U

#define PWM_CMP_UP           1U
#define PWM_CMP_DOWN         0U

//
// Globals
//
typedef struct
{
    uint32_t pwmModule;
    uint16_t pwmCompADirection;
    uint16_t pwmCompBDirection;
    uint16_t pwmTimerIntCount;
    uint16_t pwmMaxCompA;
    uint16_t pwmMinCompA;
    uint16_t pwmMaxCompB;
    uint16_t pwmMinCompB;
} pwmInformation;

//
// Globals to hold the PWM information used in this example
//
pwmInformation pwm1Info;
pwmInformation pwm2Info;
pwmInformation pwm3Info;

//
// Function Prototypes
//
void initPWM1(void);
void initPWM2(void);
void initPWM3(void);
void INT_PWM1_IRQHandler(void);
void INT_PWM2_IRQHandler(void);
void INT_PWM3_IRQHandler(void);
void updateCompare(pwmInformation *pwmInfo);

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
    // Disable pin locks and enable internal pull ups.
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
    // Assign the interrupt service routines to PWM interrupts
    //
    Interrupt_register(INT_PWM1, &INT_PWM1_IRQHandler);
    Interrupt_register(INT_PWM2, &INT_PWM2_IRQHandler);
    Interrupt_register(INT_PWM3, &INT_PWM3_IRQHandler);

    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    Interrupt_setPriority(INT_PWM1,0,0);
    Interrupt_setPriority(INT_PWM2,1,0);
    Interrupt_setPriority(INT_PWM3,2,0);

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure GPIO0/1 , GPIO2/3 and GPIO4/5 as PWM1A/1B, PWM2A/2B and
    // PWM3A/3B pins respectively
    // Configure PWM Modules
    //
    Board_init();

    initPWM1();
    initPWM2();
    initPWM3();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable PWM interrupts
    //
    Interrupt_enable(INT_PWM1);
    Interrupt_enable(INT_PWM2);
    Interrupt_enable(INT_PWM3);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        NOP;
    }
}

//
// pwm1ISR - PWM 1 ISR
//
void INT_PWM1_IRQHandler(void)
{
    //
    // Update the CMPA and CMPB values
    //
    updateCompare(&pwm1Info);

    //
    // Clear INT flag for this timer
    //
    PWM_clearEventTriggerInterruptFlag(myPWM1_BASE);
}

//
// pwm2ISR - PWM 2 ISR
//
void INT_PWM2_IRQHandler(void)
{
    //
    // Update the CMPA and CMPB values
    //
    updateCompare(&pwm2Info);

    //
    // Clear INT flag for this timer
    //
    PWM_clearEventTriggerInterruptFlag(myPWM2_BASE);
}

//
// pwm3ISR - PWM 3 ISR
//
void INT_PWM3_IRQHandler(void)
{
    //
    // Update the CMPA and CMPB values
    //
    updateCompare(&pwm3Info);

    //
    // Clear INT flag for this timer
    //
    PWM_clearEventTriggerInterruptFlag(myPWM3_BASE);
}

//
// initPWM1 - Configure PWM1
//
void initPWM1()
{
    //
    // Information this example uses to keep track of the direction the
    // CMPA/CMPB values are moving, the min and max allowed values and
    // a pointer to the correct PWM registers
    //
    pwm1Info.pwmCompADirection = PWM_CMP_UP;
    pwm1Info.pwmCompBDirection = PWM_CMP_DOWN;
    pwm1Info.pwmTimerIntCount = 0U;
    pwm1Info.pwmModule = myPWM1_BASE;
    pwm1Info.pwmMaxCompA = PWM1_MAX_CMPA;
    pwm1Info.pwmMinCompA = PWM1_MIN_CMPA;
    pwm1Info.pwmMaxCompB = PWM1_MAX_CMPB;
    pwm1Info.pwmMinCompB = PWM1_MIN_CMPB;
}

//
// initPWM2 - Configure PWM2
//
void initPWM2()
{
    //
    // Information this example uses to keep track of the direction the
    // CMPA/CMPB values are moving, the min and max allowed values and
    // a pointer to the correct PWM registers
    //
    pwm2Info.pwmCompADirection = PWM_CMP_UP;
    pwm2Info.pwmCompBDirection = PWM_CMP_UP;
    pwm2Info.pwmTimerIntCount = 0U;
    pwm2Info.pwmModule = myPWM2_BASE;
    pwm2Info.pwmMaxCompA = PWM2_MAX_CMPA;
    pwm2Info.pwmMinCompA = PWM2_MIN_CMPA;
    pwm2Info.pwmMaxCompB = PWM2_MAX_CMPB;
    pwm2Info.pwmMinCompB = PWM2_MIN_CMPB;
}

//
// initPWM3 - Configure PWM3
//
void initPWM3(void)
{
    //
    // Information this example uses to keep track of the direction the
    // CMPA/CMPB values are moving, the min and max allowed values and
    // a pointer to the correct PWM registers
    //
    pwm3Info.pwmCompADirection = PWM_CMP_UP;
    pwm3Info.pwmCompBDirection = PWM_CMP_DOWN;
    pwm3Info.pwmTimerIntCount = 0U;
    pwm3Info.pwmModule = myPWM3_BASE;
    pwm3Info.pwmMaxCompA = PWM3_MAX_CMPA;
    pwm3Info.pwmMinCompA = PWM3_MIN_CMPA;
    pwm3Info.pwmMaxCompB = PWM3_MAX_CMPB;
    pwm3Info.pwmMinCompB = PWM3_MIN_CMPB;
}

//
// updateCompare - Function to update the frequency
//
void updateCompare(pwmInformation *pwmInfo)
{
    uint16_t compAValue;
    uint16_t compBValue;

    compAValue = PWM_getCounterCompareValue(pwmInfo->pwmModule,
                                             PWM_COUNTER_COMPARE_A);

    compBValue = PWM_getCounterCompareValue(pwmInfo->pwmModule,
                                             PWM_COUNTER_COMPARE_B);

    //
    //  Change the CMPA/CMPB values every 10th interrupt.
    //
    if (pwmInfo->pwmTimerIntCount == 10U)
    {
        pwmInfo->pwmTimerIntCount = 0U;

        //
        // If we were increasing CMPA, check to see if we reached the max
        // value. If not, increase CMPA else, change directions and decrease
        // CMPA
        //
        if (pwmInfo->pwmCompADirection == PWM_CMP_UP)
        {
            if (compAValue < (pwmInfo->pwmMaxCompA))
            {
                PWM_setCounterCompareValue(pwmInfo->pwmModule,
                                            PWM_COUNTER_COMPARE_A,
                                            ++compAValue);
            }
            else
            {
                pwmInfo->pwmCompADirection = PWM_CMP_DOWN;
                PWM_setCounterCompareValue(pwmInfo->pwmModule,
                                            PWM_COUNTER_COMPARE_A,
                                            --compAValue);
            }
        }
        //
        // If we were decreasing CMPA, check to see if we reached the min
        // value. If not, decrease CMPA else, change directions and increase
        // CMPA
        //
        else
        {
            if ( compAValue == (pwmInfo->pwmMinCompA))
            {
                pwmInfo->pwmCompADirection = PWM_CMP_UP;
                PWM_setCounterCompareValue(pwmInfo->pwmModule,
                                            PWM_COUNTER_COMPARE_A,
                                            ++compAValue);
            }
            else
            {
                PWM_setCounterCompareValue(pwmInfo->pwmModule,
                                            PWM_COUNTER_COMPARE_A,
                                            --compAValue);
            }
        }

        //
        // If we were increasing CMPB, check to see if we reached the max
        // value. If not, increase CMPB else, change directions and decrease
        // CMPB
        //
        if (pwmInfo->pwmCompBDirection == PWM_CMP_UP)
        {
            if (compBValue < (pwmInfo->pwmMaxCompB))
            {
                PWM_setCounterCompareValue(pwmInfo->pwmModule,
                                            PWM_COUNTER_COMPARE_B,
                                            ++compBValue);
            }
            else
            {
                pwmInfo->pwmCompBDirection = PWM_CMP_DOWN;
                PWM_setCounterCompareValue(pwmInfo->pwmModule,
                                            PWM_COUNTER_COMPARE_B,
                                            --compBValue);
            }
        }
        //
        // If we were decreasing CMPB, check to see if we reached the min
        // value. If not, decrease CMPB else, change directions and increase
        // CMPB
        //
        else
        {
            if (compBValue == (pwmInfo->pwmMinCompB))
            {
                pwmInfo->pwmCompBDirection = PWM_CMP_UP;
                PWM_setCounterCompareValue(pwmInfo->pwmModule,
                                            PWM_COUNTER_COMPARE_B,
                                            ++compBValue);
            }
            else
            {
                PWM_setCounterCompareValue(pwmInfo->pwmModule,
                                            PWM_COUNTER_COMPARE_B,
                                            --compBValue);
            }
        }
    }
    else
    {
        pwmInfo->pwmTimerIntCount++;
    }
}
