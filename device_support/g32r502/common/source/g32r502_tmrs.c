//###########################################################################
//
// FILE:    g32r502_tmrs.c
//
// TITLE:   g32r502 CPU 32-bit Timers Initialization & Support Functions.
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
// 1. Updated header file title for G32R502 timer initialization functions.
// 2. Changed file name to g32r502_tmrs.c to reflect the new architecture.
// 3. Adjusted structure and register names to align with G32R502 specifications.
//
//###########################################################################

//
// Included Files
//
#include "g32r502_device.h"      // Headerfile Include File
#include "g32r502_examples.h"    // Examples Include File

//
// Globals
//
struct TMR_VARS Timer0;
struct TMR_VARS Timer1;
struct TMR_VARS Timer2;

//
// InitTimers - This function initializes all three timers
// to a known state.
//
void
InitTimers(void)
{
    //
    // Timer 0
    // Initialize address pointers to respective timer registers
    //
    Timer0.RegsAddr = &Timer0Regs;

    //
    // Initialize timer period to maximum
    //
    Timer0Regs.PRD.all  = 0xFFFFFFFF;

    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    Timer0Regs.TPR.all  = 0;
    Timer0Regs.TPRH.all = 0;

    //
    // Make sure timer is stopped
    //
    Timer0Regs.TCR.bit.TSS = 1;

    //
    // Reload all counter register with period value
    //
    Timer0Regs.TCR.bit.TRB = 1;

    //
    // Reset interrupt counters
    //
    Timer0.InterruptCount = 0;

    //
    // Timer 1 and 2
    // Initialize address pointers to respective timer registers
    //
    Timer1.RegsAddr = &Timer1Regs;
    Timer2.RegsAddr = &Timer2Regs;

    //
    // Initialize timer period to maximum
    //
    Timer1Regs.PRD.all  = 0xFFFFFFFF;
    Timer2Regs.PRD.all  = 0xFFFFFFFF;

    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    Timer1Regs.TPR.all  = 0;
    Timer1Regs.TPRH.all = 0;
    Timer2Regs.TPR.all  = 0;
    Timer2Regs.TPRH.all = 0;

    //
    // Make sure timers are stopped
    //
    Timer1Regs.TCR.bit.TSS = 1;
    Timer2Regs.TCR.bit.TSS = 1;

    //
    // Reload all counter register with period value
    //
    Timer1Regs.TCR.bit.TRB = 1;
    Timer2Regs.TCR.bit.TRB = 1;

    //
    // Reset interrupt counters
    //
    Timer1.InterruptCount = 0;
    Timer2.InterruptCount = 0;
}

//
// ConfigTimer - This function initializes the selected timer to the period
// specified by the "Freq" and "Period" parameters. The "Freq" is entered
// as "MHz" and the "Period" in "uSeconds". The timer is held in the stopped
// state after configuration.
//
void
ConfigTimer(struct TMR_VARS *Timer, float Freq, float Period)
{
    Uint32 temp;

    //
    // Initialize timer period
    //
    Timer->CPUFreqInMHz = Freq;
    Timer->PeriodInUSec = Period;
    temp = (long) (Freq * Period);
    Timer->RegsAddr->PRD.all = temp;

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    Timer->RegsAddr->TPR.all  = 0;
    Timer->RegsAddr->TPRH.all  = 0;

    //
    // Initialize timer control register
    //

    //
    // 1 = Stop timer, 0 = Start/Restart Timer
    //
    Timer->RegsAddr->TCR.bit.TSS = 1;

    //
    // 1 = reload timer
    //
    Timer->RegsAddr->TCR.bit.TRB = 1;
    Timer->RegsAddr->TCR.bit.SOFT = 0;

    //
    // Timer Free Run Disabled
    //
    Timer->RegsAddr->TCR.bit.FREE = 0;

    //
    // 0 = Disable 1 = Enable Timer Interrupt
    //
    Timer->RegsAddr->TCR.bit.TIE = 1;

    //
    // Reset interrupt counter
    //
    Timer->InterruptCount = 0;
}

//
// End of File
//
