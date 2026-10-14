//#############################################################################
//
// FILE:    hrpwm_ex5_slider_qformat.c
//
// TITLE:   HRPWM Slider (Q format).
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1>HRPWM Slider (Q format)</h1>
//!
//! This example modifies the MEP control registers to show edge displacement
//! due to HRPWM. Control blocks of the respective PWM module channel A and B
//! will have fine edge movement due to HRPWM logic.
//!
//! \b External \b Connections \n
//! Monitor PWM1 A/B pins on an oscilloscope.
//!
//
//! \b Watch \b Variables 
//!  - dutyFine - HRPWM duty sweep value (Q format, auto wrap in main loop)
//!  - status - status variable used by the example
//!
//!
//#############################################################################
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
// 1. Modified peripheral register names by Geehy Semiconductor.
//
//#############################################################################

#include "board.h"

//
// Defines
//

//
// Globals
//
#define PWM_TIMER_TBPRD 100

uint16_t dutyFine = 1;
uint16_t previousDutyFine = 1;
uint16_t status;

//
// Function Prototypes
//
void error(void);

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
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Initialize the PWM GPIOs and CHANGE XBAR inputs from using GPIO0
    //
    Board_init();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    for (;;)
    {
        if (dutyFine != previousDutyFine)
        {
            HRPWM_setCounterCompareValue(myPWM1_BASE, HRPWM_COUNTER_COMPARE_A,
                                         (PWM_TIMER_TBPRD/2 << 8) | dutyFine);
            HRPWM_setCounterCompareValue(myPWM1_BASE, HRPWM_COUNTER_COMPARE_B,
                                         (PWM_TIMER_TBPRD/2 << 8) | dutyFine);

            previousDutyFine = dutyFine;
        }
        
        DEVICE_DELAY_US(1000000);
        dutyFine++;
        if (dutyFine > 10)
        {
            dutyFine = 1;
        }
     }
}

//
// error - Halt debugger when called
//
void error (void)
{
    ESTOP0;         // Stop here and handle error
}

