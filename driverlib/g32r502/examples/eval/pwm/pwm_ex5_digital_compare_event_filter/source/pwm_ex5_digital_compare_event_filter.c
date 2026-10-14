//#############################################################################
//
// FILE:    pwm_ex5_digital_compare_event_filter.c
//
// TITLE:   PWM Using Digital Compare Submodule with
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//         Event Filter (Blanking Window).
//
//! \addtogroup driver_example_list
//! <h1>PWM Digital Compare Event Filter Blanking Window</h1>
//!
//! This example configures PWM1 as follows
//!  - PWM1 with DCAEVT1 forcing the PWM output LOW
//!  - GPIO25 is used as the input to the INPUT XBAR INPUT1
//!  - INPUT1 (from INPUT XBAR) is used as the source for DCAEVT1
//!  - GPIO25's PULL-UP resistor is enabled, in order to test the trip, PULL
//!    this pin to GND
//!
//!  - PWM1 with DCBEVT1 forcing the PWM output LOW
//!  - GPIO25 is used as the input to the INPUT XBAR INPUT1
//!  - INPUT1 (from INPUT XBAR) is used as the source for DCAEVT1
//!  - GPIO25's PULL-UP resistor is enabled, in order to test the trip, PULL
//!    this pin to GND
//!  - DCBEVT1 uses the filtered version of DCBEVT1
//!  - The DCFILT signal uses the blanking window to ignore the DCBEVT1
//!    for the duration of DC Blanking window
//!
//! \b External \b Connections \n
//! - GPIO0 PWM1A
//! - GPIO1 PWM1B
//! - GPIO25 TRIPIN1, pull this pin low to trip the PWM
//!
//! \b Watch \b Variables \n
//! - None.
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
// Globals
//
uint32_t  pwm1TZIntCount;

//
// Function Prototypes
//
void INT_PWM1_TRIP_ZONE_IRQHandler(void);

//
// Main
//
void example_main(void)
{
    //
    // Initialize global variables
    //
    pwm1TZIntCount = 0U;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
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
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_PWM1_TRIP_ZONE, &INT_PWM1_TRIP_ZONE_IRQHandler);

    //
    // Disable sync(Freeze clock to PWM as well). GTBCLKSYNC is applicable
    // only for multiple core devices. Uncomment the below statement if
    // applicable.
    //
    // SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_GTBCLKSYNC);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    Interrupt_setPriority(INT_PWM1_TRIP_ZONE,0,0);

    //
    // Configure PWM1, and TZ GPIOs
    //
    Board_init();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_PWM1_TRIP_ZONE);

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
void INT_PWM1_TRIP_ZONE_IRQHandler(void)
{
    pwm1TZIntCount++;

    //
    // To re-enable the Interrupts
    //
    PWM_clearTripZoneFlag(PWM1_BASE,
                           PWM_TZ_FLAG_DCAEVT1 | PWM_TZ_FLAG_DCBEVT1 | PWM_TZ_INTERRUPT);
}

