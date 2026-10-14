//#############################################################################
//
// FILE:    dac_ex1_enable.c
//
// TITLE:   DAC Enable Output Example
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup bitfield_example_list
//! <h1>Buffered DAC Enable</h1>
//!
//! This example generates a voltage on the buffered DAC output, DACOUTA
//! (AIO231 / G32R502 EVAL A0), with the DAC reference set to VDAC.
//!
//! \b External \b Connections \n
//!  - On G32R502, the VDAC pin is AIO244 (also ADC-A5 / ADC-C2 on the eval
//!    board). Apply an external reference (for example 3.3V) to AIO244. A
//!    100pF capacitor to VSSA on this pin is fixed on-chip and cannot be
//!    disabled; avoid drawing significant current from the reference.
//!  - Measure the buffered DAC output on AIO231 (eval A0). With VDAC at
//!    3.3V and dacval = 2048 (50% of 4095), expect about 1.65V.
//!
//! \b Watch \b Variables \n
//!  - None.
//!
//
//###########################################################################
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
// - 2026-06-15:
// 1. Updated external connection notes for G32R502 VDAC (AIO244) and DACA
//    output (AIO231 / eval A0).
// - 2026-06-30:
// 1. Updated interrupt handling to use NVIC functions.
//
//###########################################################################

//
// Included Files
//
#include "g32r502_project.h"

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
    // Globally disable interrupts and clear all NVIC enable/pending bits
    //
    Interrupt_initModule();

    //
    // Initialize RAM vector table and set VTOR; unregistered IRQs use
    // Interrupt_defaultHandler until Interrupt_register() is called
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
