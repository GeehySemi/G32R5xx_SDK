//#############################################################################
//
// FILE:    cap_ex3_apwm_phase_shift.c
//
// TITLE:   CAP APWM Phase-shift Example.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1>CAP APWM Phase-shift Example</h1>
//!
//! This program sets up the CAP1 and CAP2 modules in APWM mode to generate
//! the two phase-shifted PWM outputs of same duty and frequency value
//! The frequency, duty and phase values can be programmed of choice by updating
//! the defined macros. By default 10 Khz frequency, 50% duty and 30% phase
//! shift values are used. CAP2 output leads the CAP1 output by 30%
//! GPIO5 and GPIO6 are used as CAP1/2 outputs and can be probed using
//! analyzer/CRO to observe the waveforms.
//!
//
//! \b External \b Connections \n
//!  - Optional: probe the CAP APWM output pin documented in the example.
//!
//! \b Watch \b Variables \n
//!  - None.
//!
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
#define PWM_FREQUENCY        10000U // 10 Khz
#define PWM_DUTY             0.5f   // 50% duty 
#define PWM_PHASE_SHIFT      0.3f   // 30% Phase shift 
#define PWM_PRD_VAL          (DEVICE_AHBCLK_FREQ / PWM_FREQUENCY)
#define PWM_CMP_VAL          (uint32_t)(PWM_DUTY * PWM_PRD_VAL)
#define PWM_PHASE_VAL        (uint32_t)(PWM_PHASE_SHIFT * PWM_PRD_VAL)

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
    // Board initialization
    // Select CAP1OUT on MUX 0. Make GPIO5 as CAP1OUT for PWM output
    // Select CAP2OUT on MUX 2. Make GPIO6 as CAP2OUT for PWM output
    // Configure CAP1 in APWM mode with defined period and duty values
    // Polarity as low and configure SYNCOUT at CTR=PRD
    //
    Board_init();

    while(1)
    {
        
    }
}

//
// End of File
//

