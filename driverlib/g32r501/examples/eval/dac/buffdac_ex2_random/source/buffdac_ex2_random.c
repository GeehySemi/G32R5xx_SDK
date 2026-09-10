//#############################################################################
//
// FILE:    buffdac_ex2_random.c
//
// TITLE:   Buffered DAC Random Output Example
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1> Buffered DAC Random </h1>
//!
//! This example generates random voltages on the buffered DAC output,
//! DACOUTA/ADCINA0 and uses the default DAC reference setting of
//! VDAC.
//!
//! \b External \b Connections \n
//!  - When the DAC reference is set to VDAC, an external reference voltage
//!    must be applied to the VDAC pin. This can accomplished by connecting a
//!    jumper wire from 3.3V to ADCINB3.
//!
//! \b Watch \b Variables \n
//!  - None.
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
#include "g32r501_examples.h"
#include <time.h>
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
    // Initialize NVIC and clears NVIC registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Initialize a random time seed
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
