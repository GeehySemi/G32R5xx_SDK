//#############################################################################
//
// FILE:    pwm_ex1_trip_zone.c
//
// TITLE:   PWM Using Trip-Zone Submodule.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1>PWM Trip Zone</h1>
//!
//! This example configures PWM1 and PWM2 as follows
//!  - PWM1 has TZ1 as one shot trip source
//!  - PWM2 has TZ1 as cycle by cycle trip source
//!
//! Initially tie TZ1 high. During the test, monitor PWM1 or PWM2
//! outputs on a scope. Pull TZ1 low to see the effect.
//!
//!  \b External \b Connections \n
//!  - PWM1A is on GPIO0
//!  - PWM2A is on GPIO2
//!  - TZ1 is on GPIO12
//!
//! This example also makes use of the Input X-BAR. GPIO12 (the external
//! trigger) is routed to the input X-BAR, from which it is routed to TZ1.
//!
//! The TZ-Event is defined such that PWM1A will undergo a One-Shot Trip
//! and PWM2A will undergo a Cycle-By-Cycle Trip.
//!
//              _____________             __________________
//              |           |             |                |
//  GPIO12 -----| I/P X-BAR |-----TZ1-----| PWM TZ Module |-----TZ-Event
//              |___________|             |________________|
//
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

//
// Globals
//
uint32_t  pwm1TZIntCount;
uint32_t  pwm2TZIntCount;

//
// Function Prototypes
//
void INT_PWM1_TZ_IRQHandler(void);
void INT_PWM2_TZ_IRQHandler(void);

void example_main(void)
{
    //
    // Initialize global variables
    //
    pwm1TZIntCount = 0U;
    pwm2TZIntCount = 0U;

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
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_7_6_SUB_5_0);

    Interrupt_setPriority(INT_PWM1_TZ,1,0);
    Interrupt_setPriority(INT_PWM2_TZ,2,0);
    Interrupt_setPriority(INT_PWM3_TZ,3,0);

    //
    // Configure PWM1, PWM2, and TZ GPIOs/Modules
    //
    Board_init();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for (;;)
    {
        NOP;
    }
}

//
// pwm1TZISR - PWM1 TZ ISR
//
void INT_PWM1_TZ_IRQHandler(void)
{
    pwm1TZIntCount++;

    //
    // To re-enable the OST Interrupt, uncomment the below code:
    //
     PWM_clearTripZoneFlag(PWM1_BASE,
                            (PWM_TZ_INTERRUPT | PWM_TZ_FLAG_OST));
}

//
// pwm2TZISR - PWM2 TZ ISR
//
void INT_PWM2_TZ_IRQHandler(void)
{
    pwm2TZIntCount++;

    //
    // Toggle GPIO to notify when TZ is entered
    //
    GPIO_togglePin(myGPIO11);

    //
    // Clear the flags - we will continue to take this interrupt until the TZ
    // pin goes high.
    //
    PWM_clearTripZoneFlag(myPWM2_BASE, (PWM_TZ_INTERRUPT | PWM_TZ_FLAG_CBC));
}

