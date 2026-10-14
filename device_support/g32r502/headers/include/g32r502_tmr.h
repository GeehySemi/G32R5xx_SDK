//###########################################################################
//
// FILE:    g32r502_tmr.h
//
// TITLE:   Definitions for the TIMER registers.
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
// 1. Update register naming and access rules.
//
//###########################################################################

#ifndef G32R502_TMR_H
#define G32R502_TMR_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// TIMER Individual Register Bit Definitions:

struct TIM_BITS {                       // bits description
    Uint32 LSW:16;                      // 15:0 Timer Counter Registers
    Uint32 MSW:16;                      // 31:16 Timer Counter Registers High
};

union TIM_REG {
    Uint32  all;
    struct  TIM_BITS  bit;
};

struct PRD_BITS {                       // bits description
    Uint32 LSW:16;                      // 15:0 Timer Period Registers
    Uint32 MSW:16;                      // 31:16 Timer Period Registers High
};

union PRD_REG {
    Uint32  all;
    struct  PRD_BITS  bit;
};

struct TCR_BITS {                       // bits description
    Uint16 rsvd1:4;                     // 3:0 Reserved
    Uint16 TSS:1;                       // 4 Timer stop status bit.
    Uint16 TRB:1;                       // 5 Timer reload
    Uint16 rsvd2:4;                     // 9:6 Reserved
    Uint16 SOFT:1;                      // 10 Emulation modes
    Uint16 FREE:1;                      // 11 Emulation modes
    Uint16 rsvd3:2;                     // 13:12 Reserved
    Uint16 TIE:1;                       // 14 Timer Interrupt Enable.
    Uint16 TIF:1;                       // 15 Timer Interrupt Flag.
};

union TCR_REG {
    Uint16  all;
    struct  TCR_BITS  bit;
};

struct TPR_BITS {                       // bits description
    Uint16 TDDR:8;                      // 7:0 Timer Divide-Down.
    Uint16 PSC:8;                       // 15:8 Timer Prescale Counter.
};

union TPR_REG {
    Uint16  all;
    struct  TPR_BITS  bit;
};

struct TPRH_BITS {                      // bits description
    Uint16 TDDRH:8;                     // 7:0 Timer Divide-Down.
    Uint16 PSCH:8;                      // 15:8 Timer Prescale Counter.
};

union TPRH_REG {
    Uint16  all;
    struct  TPRH_BITS  bit;
};

struct TMR_REGS {
    union   TIM_REG                          TIM;                          // Timer, Counter Register
    union   PRD_REG                          PRD;                          // Timer, Period Register
    union   TCR_REG                          TCR;                          // Timer, Control Register
    Uint16                                   rsvd1;                        // Reserved
    union   TPR_REG                          TPR;                          // Timer, Prescale Register
    union   TPRH_REG                         TPRH;                         // Timer, Prescale Register High
};

//---------------------------------------------------------------------------
// TIMER External References & Function Declarations:
//
extern volatile struct TMR_REGS Timer0Regs;
extern volatile struct TMR_REGS Timer1Regs;
extern volatile struct TMR_REGS Timer2Regs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
