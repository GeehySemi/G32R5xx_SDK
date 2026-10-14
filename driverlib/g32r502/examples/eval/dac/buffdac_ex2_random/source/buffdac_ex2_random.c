//#############################################################################
//
// FILE:    buffdac_ex2_random.c
//
// TITLE:   Buffered DAC Random Output Example
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1> Buffered DAC Random </h1>
//!
//! This example generates pseudo-random codes on buffered DACA output
//! DACA_OUT (G32R502 EVAL Expand A0 / AIO231). The DAC reference is
//! VDAC.
//!
//! \b External \b Connections \n
//!  - Apply 3.3 V to VDAC (Expand A5 or C2, AIO244) if the
//!    board does not already tie VDAC to VDDA.
//!  - Measure DACA_OUT on Expand A0 (AIO231) with a scope
//!    (preferred) or DMM.
//!
//! \b Watch \b Variables \n
//!  - \b lowLimit - lower bound of random code (default 410)
//!  - \b highLimit - exclusive upper bound (default 3686)
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
// 1. Modify some comments, function names, and function contents.
// - 2026-08-29:
// 1. Replace ADCINB3 External Connections with A5/C2 / AIO244.
// 2. Document Watch variables; remove unused includes.
//
//###########################################################################


//
// Included Files
//
#include <stdlib.h>
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Globals
//
uint16_t lowLimit = 410;
uint16_t highLimit = 3686;

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
    // Seed the PRNG
    //
    srand(1);

    //
    // Configure the DAC module
    // Configure DAC - Setup the reference voltage and output value for the DAC
    //
    Board_init();

    //
    // Continuously set the DAC output value based on random value
    //
    while(1)
    {
        DAC_setShadowValue(myDAC0_BASE, ((rand() % (highLimit - lowLimit)) +
                                       lowLimit));
        DEVICE_DELAY_US(1);
    }
}

//
// End of File
//
