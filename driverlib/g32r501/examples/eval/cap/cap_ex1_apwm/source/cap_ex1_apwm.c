//#############################################################################
//
// FILE:    cap_ex1_apwm.c
//
// TITLE:   CAP APWM Example.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1>CAP APWM Example</h1>
//!
//! This program sets up the CAP module in APWM mode. The PWM waveform will
//! come out on GPIO5. The frequency of PWM is configured to vary between 5Hz
//! and 10Hz using the shadow registers to load the next period/compare values.
//!
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
// 1. Modify some comments, function names, and function contents.
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
#define DECREASE_FREQUENCY  0
#define INCREASE_FREQUENCY  1

//
// Globals
//
uint16_t direction;
volatile uint32_t cap1Count;

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
    // Board initialization
    // Select CAP1OUT on MUX 0. Make GPIO5 CAP1OUT for PWM output
    // Configure CAP in APWM mode
    //
    Board_init();

    for(;;)
    {
        //
        // Set the duty cycle to 50%
        //
        CAP_setAPWMShadowCompare(myCAP0_BASE,
                      (CAP_getEventTimeStamp(myCAP0_BASE, CAP_EVENT_1) >> 1U));

        cap1Count = CAP_getEventTimeStamp(myCAP0_BASE, CAP_EVENT_1);

        //
        // Vary frequency
        //
        if(cap1Count >= 20000000U)
        {
           direction = INCREASE_FREQUENCY;
        }
        else if (cap1Count <= 10000000U)
        {
           direction = DECREASE_FREQUENCY;
        }

        if(direction == INCREASE_FREQUENCY)
        {
           CAP_setAPWMShadowPeriod(myCAP0_BASE, (cap1Count - 500000U));
        }
        else
        {
           CAP_setAPWMShadowPeriod(myCAP0_BASE, (cap1Count + 500000U));
        }
    }
}

