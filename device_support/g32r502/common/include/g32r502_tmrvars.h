//###########################################################################
//
// FILE:    g32r502_tmrvars.h
//
// TITLE:   g32r502 Device TMRS Register Definitions.
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
// 1. Updated header file title for G32R502 timer variable definitions.
// 2. Changed file name to g32r502_tmrvars.h to reflect the new architecture.
// 3. Renamed structure and register references to match G32R502 timer specifications.
//
//###########################################################################

#ifndef G32R502_TMRVARS_H
#define G32R502_TMRVARS_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Cputimers External References & Function Declarations
//

//
// CPU Timer Support Variables:
//
struct TMR_VARS {
   volatile struct  TMR_REGS  *RegsAddr;
   Uint32    InterruptCount;
   float   CPUFreqInMHz;
   float   PeriodInUSec;
};

//
// Function prototypes and external definitions:
//
void InitTimers(void);
void ConfigTimer(struct TMR_VARS *Timer, float Freq, float Period);

extern struct TMR_VARS Timer0;
extern struct TMR_VARS Timer1;
extern struct TMR_VARS Timer2;

//
// Useful Timer Operations
//

//
// Start Timer:
//
#define StartTimer0()   Timer0Regs.TCR.bit.TSS = 0

//
// Stop Timer:
//
#define StopTimer0()   Timer0Regs.TCR.bit.TSS = 1

//
// Reload Timer With period Value:
//
#define ReloadTimer0() Timer0Regs.TCR.bit.TRB = 1

//
// Read 32-Bit Timer Value:
//
#define ReadTimer0Counter() Timer0Regs.TIM.all

//
// Read 32-Bit Period Value:
//
#define ReadTimer0Period() Timer0Regs.PRD.all

//
// Start Timer:
//
#define StartTimer1()   Timer1Regs.TCR.bit.TSS = 0
#define StartTimer2()   Timer2Regs.TCR.bit.TSS = 0

//
// Stop Timer:
//
#define StopTimer1()   Timer1Regs.TCR.bit.TSS = 1
#define StopTimer2()   Timer2Regs.TCR.bit.TSS = 1

//
// Reload Timer With period Value:
//
#define ReloadTimer1() Timer1Regs.TCR.bit.TRB = 1
#define ReloadTimer2() Timer2Regs.TCR.bit.TRB = 1

//
// Read 32-Bit Timer Value:
//
#define ReadTimer1Counter() Timer1Regs.TIM.all
#define ReadTimer2Counter() Timer2Regs.TIM.all

//
// Read 32-Bit Period Value:
//
#define ReadTimer1Period() Timer1Regs.PRD.all
#define ReadTimer2Period() Timer2Regs.PRD.all

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif  // end of G32R502_TMRVARS_H definition

//
// End of file.
//
