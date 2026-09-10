//#############################################################################
//
// FILE:    dac_ex1_enable.c
//
// TITLE:   DAC Enable Output Example
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup bitfield_example_list
//! <h1>Buffered DAC Enable</h1>
//!
//! This example generates a voltage on the buffered DAC output,
//! DACOUTA/ADCINA0 and uses the default DAC reference setting of
//! VDAC.
//!
//! \b External \b Connections \n
//!  - When the DAC reference is set to VDAC, an external reference voltage
//!    must be applied to the VDAC pin. This can be accomplished by connecting a
//!    jumper wire from 3.3V to ADCINB3.
//!
//! \b Watch \b Variables \n
//!  - None.
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
// 1. Updated interrupt handling to use NVIC functions.
//
//###########################################################################

//
// Included Files
//
#include "g32r501_project.h"

//
// Globals
//
volatile struct DAC_REGS* DAC_PTR[3] = {0x0,&DacaRegs,&DacbRegs};
uint16_t dacval = 2048;

//
// Defines
//
#define REFERENCE_VDAC      0
#define REFERENCE_VREF      1
#define DACA         1
#define DACB         2

#define REFERENCE            REFERENCE_VDAC
#define DAC_NUM                DACA

//
// Function Prototypes
//
void configureDAC(uint16_t dac_num);

//
// Main
//
void example_main(void)
{
    //
    // Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    //
    InitSysCtrl();

    //
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the NVIC control registers to their default state.
    // The default state is all NVIC interrupts disabled and flags are cleared.
    //
    Interrupt_initModule();

    //
    //Initialize the NVIC vector table with pointers to the shell Interrupt
    //Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Configure DAC
    //
    configureDAC(DAC_NUM);

    while(1)
    {
        DAC_PTR[DAC_NUM]->DACVALS.all = dacval;
        DELAY_US(2);
    }
}

//
// configureDAC - Configure specified DAC output
//
void configureDAC(uint16_t dac_num)
{
    WRPRT_DISABLE;
    DAC_PTR[dac_num]->DACCTL.bit.DACREFSEL = REFERENCE;
    DAC_PTR[dac_num]->DACOUTEN.bit.DACOUTEN = 1;
    DAC_PTR[dac_num]->DACVALS.all = 0;
    DELAY_US(10); // Delay for buffered DAC to power up
    WRPRT_ENABLE;
}

//
// End of File
//
