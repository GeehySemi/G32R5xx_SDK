//#############################################################################
//
// FILE:    pwm_ex3_synchronization.c
//
// TITLE:   PWM Using The Synch Chain and Phase Shift.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1>PWM Synchronization</h1>
//!
//! This example configures PWM1, PWM2, PWM3 and PWM4 as follows
//!  - PWM1 without phase shift as sync source
//!  - PWM2 with phase shift of 300 TBCLKs
//!  - PWM3 with phase shift of 600 TBCLKs
//!  - PWM4 with phase shift of 900 TBCLKs
//!
//! \b External \b Connections \n
//! - GPIO0 PWM1A
//! - GPIO1 PWM1B
//! - GPIO2 PWM2A
//! - GPIO3 PWM2B
//! - GPIO4 PWM3A
//! - GPIO5 PWM3B
//! - GPIO6 PWM4A
//! - GPIO7 PWM4B
//!
//! \b Watch \b Variables \n
//! - None.
//#############################################################################
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


void INT_PWM1_IRQHandler(void);
void INT_PWM2_IRQHandler(void);
void INT_PWM3_IRQHandler(void);
void INT_PWM4_IRQHandler(void);

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
    // Initialize NVIC and clears NVIC registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Assign the interrupt service routines to PWM interrupts
    //
    Interrupt_register(INT_PWM1, &INT_PWM1_IRQHandler);
    Interrupt_register(INT_PWM2, &INT_PWM2_IRQHandler);
    Interrupt_register(INT_PWM3, &INT_PWM3_IRQHandler);
    Interrupt_register(INT_PWM4, &INT_PWM4_IRQHandler);

    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_7_6_SUB_5_0);

    Interrupt_setPriority(INT_PWM1,0,0);
    Interrupt_setPriority(INT_PWM2,1,0);
    Interrupt_setPriority(INT_PWM3,2,0);
    Interrupt_setPriority(INT_PWM4,3,0);


    // Disable sync(Freeze clock to PWM as well). GTBCLKSYNC is applicable
    // only for multiple core devices. Uncomment the below statement if
    // applicable.
    //
    // SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_GTBCLKSYNC);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //

    // Configure GPIO0/1 , GPIO2/3 and GPIO4/5 and GPIO6/7 as
    // PWM1A/1B, PWM2A/2B, PWM3A/3B, PWM4A/4B pins respectively
    // Configure PWM Modules
    // 
    Board_init();

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
    Interrupt_enable(INT_PWM4);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for (;;)
    {

    }
}

//
// pwm1ISR - PWM 1 ISR
//
void INT_PWM1_IRQHandler(void)
{
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
    // Clear INT flag for this timer
    //
    PWM_clearEventTriggerInterruptFlag(myPWM3_BASE);
}

//
// pwm4ISR - PWM 4 ISR
//
void INT_PWM4_IRQHandler(void)
{
    //
    // Clear INT flag for this timer
    //
    PWM_clearEventTriggerInterruptFlag(myPWM4_BASE);
}


