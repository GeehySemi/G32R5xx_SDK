//#############################################################################
//
// FILE:    buffdac_ex1_enable.c
//
// TITLE:   Buffered DAC Enable Output Example
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1> Buffered DAC Enable </h1>
//!
//! This example enables buffered DACA and drives a constant code on
//! DACA_OUT (G32R502 EVAL Expand A0 / AIO231). The DAC reference is
//! VDAC; an external reference must be present on A5/C2 / AIO244.
//!
//! With dacVal = 2048 (mid-scale) and VDAC = 3.3 V, expect about 1.65 V
//! on DACA_OUT.
//!
//! \b External \b Connections \n
//!  - Apply 3.3 V to VDAC (Expand A5 or C2, AIO244) if the
//!    board does not already tie VDAC to VDDA.
//!  - Measure DACA_OUT on Expand A0 (AIO231) with a DMM or scope.
//!
//! \b Watch \b Variables \n
//!  - \b dacVal - DAC shadow code (default 2048, mid-scale)
//!
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
// 1. Modify some comments, function names.
// - 2026-08-   :
// 1. Align default dacVal with mid-scale Doxygen (2048).
//
//###########################################################################


//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Globals
//
uint16_t dacVal = 2048;

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
    // Configure DAC - Setup the reference voltage and output value for the DAC
    //
    Board_init();

    //
    // Continuously set the DAC output value
    //
    while(1)
    {
        DAC_setShadowValue(myDAC0_BASE, dacVal);
        DEVICE_DELAY_US(2);
    }
}

//
// End of File
//
