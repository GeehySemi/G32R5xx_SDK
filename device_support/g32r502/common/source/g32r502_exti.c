//###########################################################################
//
// FILE:    g32r502_exti.c
//
// TITLE:   g32r502 Device NVIC Control Register Initialization Functions.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
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
// - 2026-06-30: 
// 1. Updated header file title for G32R502 NVIC control register functions.
// 2. Changed file name to g32r502_exti.c to reflect the new architecture.
// 3. Adjusted function names and register accesses to match G32R502 
//    specifications.
//
//###########################################################################

//
// Included Files
//
#include "g32r502_device.h"      // g32r502 Headerfile Include File
#include "g32r502_examples.h"    // g32r502 Examples Include File

//
// InitExtiCtrl - This function initializes the EXTI control registers
// to a known state.
//
void
InitExtiCtrl(void)
{
    //
    // Disable Interrupts at the CPU level:
    //
    DINT;

    //
    // Disable the EXTI
    //
    ExtiRegs.EXTI_RTEN.all = 0;

    //
    // Clear all EXTI registers:
    //
    ExtiRegs.EXTI_FTEN.all = 0;
    ExtiRegs.EXTI_SWINTE.all = 0;
    ExtiRegs.EXTI_GPIOSEL.all = 0;
    ExtiRegs.EXTI_IMASK.all = 0;
    ExtiRegs.EXTI_EMASK.all = 0;
    ExtiRegs.EXTI_IPEND.all = 0;
}

//
// EnableInterrupts - This function enables the NVIC module and CPU __interrupts
//
void
EnableInterrupts()
{
    //
    // Enable Interrupts at the CPU level
    //
    EINT;
}

//
// End of file.
//
