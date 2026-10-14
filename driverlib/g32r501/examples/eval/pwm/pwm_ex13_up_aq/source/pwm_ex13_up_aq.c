//###########################################################################
//
// FILE:    pwm_ex13_up_aq.c
//
// TITLE:   Action Qualifier Module - Using up count.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1> PWM Action Qualifier (pwm_up_aq)</h1>
//!
//! This example configures PWM1, PWM2, PWM3 to produce an
//! waveform with independent modulation on PWMxA and
//! PWMxB.
//!
//! The compare values CMPA and CMPB are modified within the PWM's ISR.
//!
//! The TB counter is in up count mode for this example.
//!
//! View the PWM1A/B(GPIO0 & GPIO1), PWM2A/B(GPIO2 & GPIO3)
//! and PWM3A/B(GPIO4 & GPIO5) waveforms via an oscilloscope.
//!
//
//###########################################################################
//
//
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
// - 2024-07-08: 
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
#define PWM1_TIMER_TBPRD  2000  // Period register
#define PWM1_MAX_CMPA     1950
#define PWM1_MIN_CMPA       50
#define PWM1_MAX_CMPB     1950
#define PWM1_MIN_CMPB       50

#define PWM2_TIMER_TBPRD  2000  // Period register
#define PWM2_MAX_CMPA     1950
#define PWM2_MIN_CMPA       50
#define PWM2_MAX_CMPB     1950
#define PWM2_MIN_CMPB       50

#define PWM3_TIMER_TBPRD  2000  // Period register
#define PWM3_MAX_CMPA      950
#define PWM3_MIN_CMPA       50
#define PWM3_MAX_CMPB     1950
#define PWM3_MIN_CMPB     1050

#define PWM_CMP_UP           1
#define PWM_CMP_DOWN         0

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
} pwmInfo;

pwmInfo pwm1Info;
pwmInfo pwm2Info;
pwmInfo pwm3Info;

volatile uint16_t compAVal, compBVal;

//
//  Function Prototypes
//
void initPWM1(void);
void initPWM2(void);
void initPWM3(void);
void INT_PWM1_IRQHandler(void);
void INT_PWM2_IRQHandler(void);
void INT_PWM3_IRQHandler(void);
void updateCompare(pwmInfo*);

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
    // Disable pin locks and enable internal pull-ups.
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
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    Interrupt_register(INT_PWM1, &INT_PWM1_IRQHandler);
    Interrupt_register(INT_PWM2, &INT_PWM2_IRQHandler);
    Interrupt_register(INT_PWM3, &INT_PWM3_IRQHandler);

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure GPIO pins and PWM Modules
    //
    Board_init();

    initPWM1();
    initPWM2();
    initPWM3();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    Interrupt_setPriority(INT_PWM1,1,0);
    Interrupt_setPriority(INT_PWM2,2,0);
    Interrupt_setPriority(INT_PWM3,3,0);

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_PWM1);
    Interrupt_enable(INT_PWM2);
    Interrupt_enable(INT_PWM3);

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        __asm ("  NOP");
    }
}

//
// pwm1ISR - PWM1 ISR to update compare values
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
// pwm2ISR - PWM2 ISR to update compare values
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
// pwm3ISR - PWM3 ISR to update compare values
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
// initPWM1 Information
//
void initPWM1()
{
   //
   // Information this example uses to keep track
   // of the direction the CMPA/CMPB values are
   // moving, the min and max allowed values and
   // a pointer to the correct PWM registers
   //

    // Start by increasing CMPA & CMPB
    pwm1Info.pwmCompADirection = PWM_CMP_UP;
    pwm1Info.pwmCompBDirection = PWM_CMP_UP;

    // Clear interrupt counter
    pwm1Info.pwmTimerIntCount = 0;

    // Set base as PWM1
    pwm1Info.pwmModule = myPWM1_BASE;

    // Setup min/max CMPA/CMP values
    pwm1Info.pwmMaxCompA = PWM1_MAX_CMPA;
    pwm1Info.pwmMinCompA = PWM1_MIN_CMPA;
    pwm1Info.pwmMaxCompB = PWM1_MAX_CMPB;
    pwm1Info.pwmMinCompB = PWM1_MIN_CMPB;
}

//
// initPWM2 Information
//
void initPWM2()
{
    //
    // Information this example uses to keep track
    // of the direction the CMPA/CMPB values are
    // moving, the min and max allowed values and
    // a pointer to the correct PWM registers
    //

    // Start by increasing CMPA & decreasing CMPB
    pwm2Info.pwmCompADirection = PWM_CMP_UP;
    pwm2Info.pwmCompBDirection = PWM_CMP_DOWN;

    // Clear interrupt counter
    pwm2Info.pwmTimerIntCount = 0;

    // Set base as PWM2
    pwm2Info.pwmModule = myPWM2_BASE;

    // Setup min/max CMPA/CMP values
    pwm2Info.pwmMaxCompA = PWM2_MAX_CMPA;
    pwm2Info.pwmMinCompA = PWM2_MIN_CMPA;
    pwm2Info.pwmMaxCompB = PWM2_MAX_CMPB;
    pwm2Info.pwmMinCompB = PWM2_MIN_CMPB;
}

//
// initPWM3 Information
//
void initPWM3(void)
{
   //
   // Information this example uses to keep track
   // of the direction the CMPA/CMPB values are
   // moving, the min and max allowed values and
   // a pointer to the correct PWM registers
   //

    // Start by increasing CMPA & decreasing CMPB
    pwm3Info.pwmCompADirection = PWM_CMP_UP;
    pwm3Info.pwmCompBDirection = PWM_CMP_DOWN;

    // Start the count at 0
    pwm3Info.pwmTimerIntCount = 0;

    // Set base as PWM3
    pwm3Info.pwmModule = myPWM3_BASE;

    // Setup min/max CMPA/CMP values
    pwm3Info.pwmMaxCompA = PWM3_MAX_CMPA;
    pwm3Info.pwmMinCompA = PWM3_MIN_CMPA;
    pwm3Info.pwmMaxCompB = PWM3_MAX_CMPB;
    pwm3Info.pwmMinCompB = PWM3_MIN_CMPB;
}

//
// updateCompare - Update the compare values for the specified PWM
//
void updateCompare(pwmInfo *pwm_info)
{
   //
   // Every 10'th interrupt, change the CMPA/CMPB values
   //
   if (pwm_info->pwmTimerIntCount == 10)
   {
       pwm_info->pwmTimerIntCount = 0;
       compAVal = PWM_getCounterCompareValue(pwm_info->pwmModule,
                                              PWM_COUNTER_COMPARE_A);
       compBVal = PWM_getCounterCompareValue(pwm_info->pwmModule,
                                              PWM_COUNTER_COMPARE_B);

       //
       // If we were increasing CMPA, check to see if
       // we reached the max value.  If not, increase CMPA
       // else, change directions and decrease CMPA
       //
       if (pwm_info->pwmCompADirection == PWM_CMP_UP)
       {
           if(compAVal < pwm_info->pwmMaxCompA)
           {
               PWM_setCounterCompareValue(pwm_info->pwmModule,
                                           PWM_COUNTER_COMPARE_A, ++compAVal);
           }
           else
           {
               pwm_info->pwmCompADirection = PWM_CMP_DOWN;
               PWM_setCounterCompareValue(pwm_info->pwmModule,
                                           PWM_COUNTER_COMPARE_A, --compAVal);
           }
       }

       //
       // If we were decreasing CMPA, check to see if
       // we reached the min value.  If not, decrease CMPA
       // else, change directions and increase CMPA
       //
       else
       {
           if (compAVal == pwm_info->pwmMinCompA)
           {
               pwm_info->pwmCompADirection = PWM_CMP_UP;
               PWM_setCounterCompareValue(pwm_info->pwmModule,
                                           PWM_COUNTER_COMPARE_A, ++compAVal);

           }
           else
           {
               PWM_setCounterCompareValue(pwm_info->pwmModule,
                                           PWM_COUNTER_COMPARE_A, --compAVal);
           }
       }

       //
       // If we were increasing CMPB, check to see if
       // we reached the max value.  If not, increase CMPB
       // else, change directions and decrease CMPB
       //
       if (pwm_info->pwmCompBDirection == PWM_CMP_UP)
       {
           if (compBVal < pwm_info->pwmMaxCompB)
           {
               PWM_setCounterCompareValue(pwm_info->pwmModule,
                                           PWM_COUNTER_COMPARE_B, ++compBVal);
           }
           else
           {
               pwm_info->pwmCompBDirection = PWM_CMP_DOWN;
               PWM_setCounterCompareValue(pwm_info->pwmModule,
                                           PWM_COUNTER_COMPARE_B, --compBVal);

           }
       }

       //
       // If we were decreasing CMPB, check to see if
       // we reached the min value.  If not, decrease CMPB
       // else, change directions and increase CMPB
       //
       else
       {
           if (compBVal == pwm_info->pwmMinCompB)
           {
               pwm_info->pwmCompBDirection = PWM_CMP_UP;
               PWM_setCounterCompareValue(pwm_info->pwmModule,
                                           PWM_COUNTER_COMPARE_B, ++compBVal);
           }
           else
           {
               PWM_setCounterCompareValue(pwm_info->pwmModule,
                                           PWM_COUNTER_COMPARE_B, --compBVal);
           }
       }
   }

   //
   // Increment interrupt count if < 10
   //
   else
   {
      pwm_info->pwmTimerIntCount++;
   }
   return;
}
//
// End of file
//
