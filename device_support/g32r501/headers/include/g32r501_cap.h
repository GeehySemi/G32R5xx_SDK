//###########################################################################
//
// FILE:    g32r501_cap.h
//
// TITLE:   Definitions for the CAP registers.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
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
// 1. Update register naming and access rules.
//
//###########################################################################

#ifndef G32R501_CAP_H
#define G32R501_CAP_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// CAP Individual Register Bit Definitions:

struct CCTL0_BITS {                     // bits description
    Uint32 INPUTSEL : 7;               // 6:0 INPUT source select
    Uint32 rsvd1    : 9;               // 15:7 Reserved
    Uint32 rsvd2    : 16;              // 31:16 Reserved
};

union CCTL0_REG {
    Uint32  all;
    struct  CCTL0_BITS  bit;
};

struct CCTL1_BITS {                   // bits description
    Uint16 CAP1POL   : 1;            // [0..0] Capture Event 1 Polarity select
    Uint16 CTRRST1   : 1;            // [1..1] Capture Event 1 Counter Reset
    Uint16 CAP2POL   : 1;            // [2..2] Capture Event 2 Polarity select
    Uint16 CTRRST2   : 1;            // [3..3] Capture Event 2 Counter Reset
    Uint16 CAP3POL   : 1;            // [4..4] Capture Event 3 Polarity select
    Uint16 CTRRST3   : 1;            // [5..5] Capture Event 3 Counter Reset
    Uint16 CAP4POL   : 1;            // [6..6] Capture Event 4 Polarity select
    Uint16 CTRRST4   : 1;            // [7..7] Capture Event 4 Counter Reset
    Uint16 CAPLDEN   : 1;            // [8..8] Enable load CAP_CAP1/2/3/4 register on capture event
    Uint16 PRESCALE  : 5;            // [13..9] Event Filter prescale select
    Uint16 FREE_SOFT : 2;            // [15..14] TSCTR counter run mode Select
};

union CCTL1_REG {
    Uint16  all;
    struct  CCTL1_BITS  bit;
};

struct CCTL2_BITS {                    // bits description
    Uint16 CONT_ONESHT : 1;           // [0..0] Operate mode Select
    Uint16 STOP_WRAP   : 2;           // [2..1] Select how to run after capture events in capture / one-shot mode
    Uint16 REARM       : 1;           // [3..3] Re-Arming Control
    Uint16 TSCTRSTOP   : 1;           // [4..4] TSCTR run mode
    Uint16 SYNCI_EN    : 1;           // [5..5] sync-in mode enable
    Uint16 SYNCO_SEL   : 2;           // [7..6] sync-out signal Select
    Uint16 SWSYNC      : 1;           // [8..8] Software-forced TSCTR Synchronizer
    Uint16 CAP_APWM    : 1;           // [9..9] CAP/APWM operating mode select
    Uint16 APWMPOL     : 1;           // [10..10] APWM output polarity select
    Uint16 CTRFILTRESET: 1;           // [11..11] Reset
    Uint16 DMAEVTSEL   : 2;           // [13..12] DMA interrupt source select
    Uint16 MODCNTRSTS  : 2;           // [15..14] reads modulo counter status
};

union CCTL2_REG {
    Uint16  all;
    struct  CCTL2_BITS  bit;
};

struct CEINT_BITS {                   // bits description
    Uint16 rsvd1:1;
    Uint16 CEVT1      : 1;            // [1..1] Capture Event 1 Interrupt Enable
    Uint16 CEVT2      : 1;            // [2..2] Capture Event 2 Interrupt Enable
    Uint16 CEVT3      : 1;            // [3..3] Capture Event 3 Interrupt Enable
    Uint16 CEVT4      : 1;            // [4..4] Capture Event 4 Interrupt Enable
    Uint16 CTROVF     : 1;            // [5..5] Counter Overflow Interrupt Enable
    Uint16 CTR_EQ_PRD : 1;            // [6..6] Counter Equal Period Interrupt Enable
    Uint16 CTR_EQ_CMP : 1;            // [7..7] Counter Equal Compare Interrupt Enable
    Uint16 rsvd2      : 1;
    Uint16 rsvd3      : 7;
};

union CEINT_REG {
    Uint16  all;
    struct  CEINT_BITS  bit;
};

struct CFLG_BITS {                    // bits description
    Uint16 INT        : 1;            // [0..0] Global Interrupt Flag
    Uint16 CEVT1      : 1;            // [1..1] Capture Event 1 Interrupt Flag
    Uint16 CEVT2      : 1;            // [2..2] Capture Event 2 Interrupt Flag
    Uint16 CEVT3      : 1;            // [3..3] Capture Event 3 Interrupt Flag
    Uint16 CEVT4      : 1;            // [4..4] Capture Event 4 Interrupt Flag
    Uint16 CTROVF     : 1;            // [5..5] Counter Overflow Interrupt Flag
    Uint16 CTR_PRD    : 1;            // [6..6] Counter Equal Period Interrupt Flag
    Uint16 CTR_CMP    : 1;            // [7..7] Counter Equal Compare Interrupt Flag
    Uint16 rsvd1      : 1;
    Uint16 rsvd2      : 7;
};

union CFLG_REG {
    Uint16  all;
    struct  CFLG_BITS  bit;
};

struct CCLR_BITS {                    // bits description
    Uint16 INT        : 1;            // [0..0] Global Interrupt Flag Clear
    Uint16 CEVT1      : 1;            // [1..1] Capture Event 1 Interrupt Flag Clear
    Uint16 CEVT2      : 1;            // [2..2] Capture Event 2 Interrupt Flag Clear
    Uint16 CEVT3      : 1;            // [3..3] Capture Event 3 Interrupt Flag Clear
    Uint16 CEVT4      : 1;            // [4..4] Capture Event 4 Interrupt Flag Clear
    Uint16 CTROVF     : 1;            // [5..5] Counter Overflow Interrupt Flag Clear
    Uint16 CTR_PRD    : 1;            // [6..6] Counter Equal Period Interrupt Flag Clear
    Uint16 CTR_CMP    : 1;            // [7..7] Counter Equal Compare Interrupt Flag Clear
    Uint16 rsvd1      : 1;
    Uint16 rsvd2      : 7;
};

union CCLR_REG {
    Uint16  all;
    struct  CCLR_BITS  bit;
};

struct CFRC_BITS {                    // bits description
    Uint16 rsvd1      : 1;
    Uint16 CEVT1      : 1;            // [1..1] Force Capture Event 1 Interrupt
    Uint16 CEVT2      : 1;            // [2..2] Force Capture Event 2 Interrupt
    Uint16 CEVT3      : 1;            // [3..3] Force Capture Event 3 Interrupt
    Uint16 CEVT4      : 1;            // [4..4] Force Capture Event 4 Interrupt
    Uint16 CTROVF     : 1;            // [5..5] Force Counter Overflow Interrupt
    Uint16 CTR_PRD    : 1;            // [6..6] Force Capture Event 2
    Uint16 CTR_CMP    : 1;            // [7..7] Force Counter Equal Compare Interrupt
    Uint16 rsvd2      : 1;
    Uint16 rsvd3      : 7;
};

union CFRC_REG {
    Uint16  all;
    struct  CFRC_BITS  bit;
};

struct CAP_REGS {
    Uint32                                   TSCTR;                        // 0x00 Time-Stamp Counter
    Uint32                                   CTRPHS;                       // 0x04 Counter Phase Offset Value Register
    Uint32                                   CAP1;                         // 0x08 Capture 1 Register
    Uint32                                   CAP2;                         // 0x0C Capture 2 Register
    Uint32                                   CAP3;                         // 0x10 Capture 3 Register
    Uint32                                   CAP4;                         // 0x14 Capture 4 Register
    Uint16                                   rsvd1[6];                     // 0x18 Reserved
    union   CCTL0_REG                        CCTL0;                        // 0x24 Capture Control Register 0
    union   CCTL1_REG                        CCTL1;                        // 0x28 Capture Control Register 1
    union   CCTL2_REG                        CCTL2;                        // 0x2A Capture Control Register 2
    union   CEINT_REG                        CEINT;                        // 0x2C Capture Interrupt Enable Register
    union   CFLG_REG                         CFLG;                         // 0x2E Capture Interrupt Flag Register
    union   CCLR_REG                         CCLR;                         // 0x30 Capture Interrupt Clear Register
    union   CFRC_REG                         CFRC;                         // 0x32 Capture Interrupt Force Register
};

struct HRCTL_BITS {                   // bits description
    Uint32 HRE        : 1;            // [0..0] High Resolution Enable
    Uint32 HRCLKE     : 1;            // [1..1] High Resolution Clock Enable
    Uint32 PRDSEL     : 1;            // [2..2] Calibration Period Match Select
    Uint32 CALIBSTART : 1;            // [3..3] Calibration start
    Uint32 CALIBSTS   : 1;            // [4..4] Calibration Flag
    Uint32 CALIBCONT  : 1;            // [5..5] Continuous mode Enable
    Uint32 rsvd1      : 10;
    Uint32 rsvd2      : 16;
};

union HRCTL_REG {
    Uint32  all;
    struct  HRCTL_BITS  bit;
};

struct HRINTEN_BITS {                 // bits description
    Uint32 rsvd1        : 1;
    Uint32 CALIBDONE    : 1;          // [1..1] Calibration done Interrupt Enable
    Uint32 CALPRDCHKSTS : 1;          // [2..2] Calibration Period Check Interrupt Enable
    Uint32 rsvd2        : 13;
    Uint32 rsvd3        : 16;
};

union HRINTEN_REG {
    Uint32  all;
    struct  HRINTEN_BITS  bit;
};

struct HRFLG_BITS {                   // bits description
    Uint32 CALIBINT     : 1;          // [0..0] Global calibration Interrupt Status Flag
    Uint32 CALIBDONE    : 1;          // [1..1] Calibration Done Interrupt Flag Bit
    Uint32 CALPRDCHKSTS : 1;          // [2..2] Calibration Period Check Interrupt Flag Bit
    Uint32 rsvd1        : 13;
    Uint32 rsvd2        : 16;
};

union HRFLG_REG {
    Uint32  all;
    struct  HRFLG_BITS  bit;
};

struct HRCLR_BITS {                   // bits description
    Uint32 CALIBINT     : 1;          // [0..0] Clear Global calibration Interrupt Flag
    Uint32 CALIBDONE    : 1;          // [1..1] Clear Calibration Done Interrupt Flag Bit
    Uint32 CALPRDCHKSTS : 1;          // [2..2] Clear Calibration period check status Flag Bit
    Uint32 rsvd1        : 13;
    Uint32 rsvd2        : 16;
};

union HRCLR_REG {
    Uint32  all;
    struct  HRCLR_BITS  bit;
};

struct HRFRC_BITS {                   // bits description
    Uint32 rsvd1        : 1;
    Uint32 CALIBDONE    : 1;          // [1..1] Force Calibration Done Interrupt Flag Bit
    Uint32 CALPRDCHKSTS : 1;          // [2..2] Force Calibration period check status Flag Bit
    Uint32 rsvd2        : 13;
    Uint32 rsvd3        : 16;
};

union HRFRC_REG {
    Uint32  all;
    struct  HRFRC_BITS  bit;
};

struct HRCAP_REGS {
    union   HRCTL_REG                        HRCTL;                        // 0x00 High-Res Control Register
    Uint16                                   rsvd1[2];                     // 0x04 Reserved
    union   HRINTEN_REG                      HRINTEN;                      // 0x08 High-Res Calibration Interrupt Enable Register
    union   HRFLG_REG                        HRFLG;                        // 0x0C High-Res Calibration Interrupt Flag Register
    union   HRCLR_REG                        HRCLR;                        // 0x10 High-Res Calibration Interrupt Clear Register
    union   HRFRC_REG                        HRFRC;                        // 0x14 High-Res Calibration Interrupt Force Register
    Uint32                                   HRCALPRD;                     // 0x18 High-Res Calibration Period Register
    Uint32                                   HRSYSCLKCTR;                  // 0x1C High-Res Calibration SYSCLK Counter Register
    Uint32                                   HRSYSCLKCAP;                  // 0x20 High-Res Calibration SYSCLK Capture Register
    Uint32                                   HRCLKCTR;                     // 0x24 High-Res Calibration HRCLK Counter Register
    Uint32                                   HRCLKCAP;                     // 0x28 High-Res Calibration HRCLK Capture Register
};

//---------------------------------------------------------------------------
// CAP External References & Function Declarations:
//
extern volatile struct CAP_REGS Cap1Regs;
extern volatile struct CAP_REGS Cap2Regs;
extern volatile struct CAP_REGS Cap3Regs;
extern volatile struct CAP_REGS Cap4Regs;
extern volatile struct CAP_REGS Cap5Regs;
extern volatile struct CAP_REGS Cap6Regs;
extern volatile struct CAP_REGS Cap7Regs;
extern volatile struct HRCAP_REGS HRCap6Regs;
extern volatile struct HRCAP_REGS HRCap7Regs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
