//###########################################################################
//
// FILE:    g32r501_xbar.h
//
// TITLE:   Definitions for the XBAR registers.
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

#ifndef G32R501_XBAR_H
#define G32R501_XBAR_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// XBAR Individual Register Bit Definitions:

struct XBARFLG1_BITS {                  // bits description
    Uint32 COMP1_CTRIPL:1;             // 0 Input Flag for COMP1.CTRIPL Signal
    Uint32 COMP1_CTRIPH:1;             // 1 Input Flag for COMP1.CTRIPH Signal
    Uint32 COMP2_CTRIPL:1;             // 2 Input Flag for COMP2.CTRIPL Signal
    Uint32 COMP2_CTRIPH:1;             // 3 Input Flag for COMP2.CTRIPH Signal
    Uint32 COMP3_CTRIPL:1;             // 4 Input Flag for COMP3.CTRIPL Signal
    Uint32 COMP3_CTRIPH:1;             // 5 Input Flag for COMP3.CTRIPH Signal
    Uint32 COMP4_CTRIPL:1;             // 6 Input Flag for COMP4.CTRIPL Signal
    Uint32 COMP4_CTRIPH:1;             // 7 Input Flag for COMP4.CTRIPH Signal
    Uint32 COMP5_CTRIPL:1;             // 8 Input Flag for COMP5.CTRIPL Signal
    Uint32 COMP5_CTRIPH:1;             // 9 Input Flag for COMP5.CTRIPH Signal
    Uint32 COMP6_CTRIPL:1;             // 10 Input Flag for COMP6.CTRIPL Signal
    Uint32 COMP6_CTRIPH:1;             // 11 Input Flag for COMP6.CTRIPH Signal
    Uint32 COMP7_CTRIPL:1;             // 12 Input Flag for COMP7.CTRIPL Signal
    Uint32 COMP7_CTRIPH:1;             // 13 Input Flag for COMP7.CTRIPH Signal
    Uint32 COMP8_CTRIPL:1;             // 14 Input Flag for COMP8.CTRIPL Signal
    Uint32 COMP8_CTRIPH:1;             // 15 Input Flag for COMP8.CTRIPH Signal
    Uint32 COMP1_CTRIPOUTL:1;          // 16 Input Flag for COMP1.CTRIPOUTL Signal
    Uint32 COMP1_CTRIPOUTH:1;          // 17 Input Flag for COMP1.CTRIPOUTH Signal
    Uint32 COMP2_CTRIPOUTL:1;          // 18 Input Flag for COMP2.CTRIPOUTL Signal
    Uint32 COMP2_CTRIPOUTH:1;          // 19 Input Flag for COMP2.CTRIPOUTH Signal
    Uint32 COMP3_CTRIPOUTL:1;          // 20 Input Flag for COMP3.CTRIPOUTL Signal
    Uint32 COMP3_CTRIPOUTH:1;          // 21 Input Flag for COMP3.CTRIPOUTH Signal
    Uint32 COMP4_CTRIPOUTL:1;          // 22 Input Flag for COMP4.CTRIPOUTL Signal
    Uint32 COMP4_CTRIPOUTH:1;          // 23 Input Flag for COMP4.CTRIPOUTH Signal
    Uint32 COMP5_CTRIPOUTL:1;          // 24 Input Flag for COMP5.CTRIPOUTL Signal
    Uint32 COMP5_CTRIPOUTH:1;          // 25 Input Flag for COMP5.CTRIPOUTH Signal
    Uint32 COMP6_CTRIPOUTL:1;          // 26 Input Flag for COMP6.CTRIPOUTL Signal
    Uint32 COMP6_CTRIPOUTH:1;          // 27 Input Flag for COMP6.CTRIPOUTH Signal
    Uint32 COMP7_CTRIPOUTL:1;          // 28 Input Flag for COMP7.CTRIPOUTL Signal
    Uint32 COMP7_CTRIPOUTH:1;          // 29 Input Flag for COMP7.CTRIPOUTH Signal
    Uint32 COMP8_CTRIPOUTL:1;          // 30 Input Flag for COMP8.CTRIPOUTL Signal
    Uint32 COMP8_CTRIPOUTH:1;          // 31 Input Flag for COMP8.CTRIPOUTH Signal
};

union XBARFLG1_REG {
    Uint32  all;
    struct  XBARFLG1_BITS  bit;
};

struct XBARFLG2_BITS {                  // bits description
    Uint32 INPUT1:1;                    // 0 Input Flag for INPUT1 Signal
    Uint32 INPUT2:1;                    // 1 Input Flag for INPUT2 Signal
    Uint32 INPUT3:1;                    // 2 Input Flag for INPUT3 Signal
    Uint32 INPUT4:1;                    // 3 Input Flag for INPUT4 Signal
    Uint32 INPUT5:1;                    // 4 Input Flag for INPUT5 Signal
    Uint32 INPUT6:1;                    // 5 Input Flag for INPUT6 Signal
    Uint32 ADCSOCA:1;                   // 6 Input Flag for ADCSOCA Signal
    Uint32 ADCSOCB:1;                   // 7 Input Flag for ADCSOCB Signal
    Uint32 INPUT7:1;                    // 8 Input Flag for INPUT7 Signal
    Uint32 INPUT8:1;                    // 9 Input Flag for INPUT8 Signal
    Uint32 INPUT9:1;                    // 10 Input Flag for INPUT9 Signal
    Uint32 INPUT10:1;                   // 11 Input Flag for INPUT10\ Signal
    Uint32 INPUT11:1;                   // 12 Input Flag for INPUT11 Signal
    Uint32 INPUT12:1;                   // 13 Input Flag for INPUT12 Signal
    Uint32 INPUT13:1;                   // 14 Input Flag for INPUT13 Signal
    Uint32 INPUT14:1;                   // 15 Input Flag for INPUT14 Signal
    Uint32 CAP1_OUT:1;                 // 16 Input Flag for CAP1.OUT Signal
    Uint32 CAP2_OUT:1;                 // 17 Input Flag for CAP2.OUT Signal
    Uint32 CAP3_OUT:1;                 // 18 Input Flag for CAP3.OUT Signal
    Uint32 CAP4_OUT:1;                 // 19 Input Flag for CAP4.OUT Signal
    Uint32 CAP5_OUT:1;                 // 20 Input Flag for CAP5.OUT Signal
    Uint32 CAP6_OUT:1;                 // 21 Input Flag for CAP6.OUT Signal
    Uint32 EXTSYNCOUT:1;                // 22 Input Flag for EXTSYNCOUT Signal
    Uint32 ADCAEVT1:1;                  // 23 Input Flag for ADCAEVT1 Signal
    Uint32 ADCAEVT2:1;                  // 24 Input Flag for ADCAEVT2 Signal
    Uint32 ADCAEVT3:1;                  // 25 Input Flag for ADCAEVT3 Signal
    Uint32 ADCAEVT4:1;                  // 26 Input Flag for ADCAEVT4 Signal
    Uint32 ADCBEVT1:1;                  // 27 Input Flag for ADCBEVT1 Signal
    Uint32 ADCBEVT2:1;                  // 28 Input Flag for ADCBEVT2 Signal
    Uint32 ADCBEVT3:1;                  // 29 Input Flag for ADCBEVT3 Signal
    Uint32 ADCBEVT4:1;                  // 30 Input Flag for ADCBEVT4 Signal
    Uint32 ADCCEVT1:1;                  // 31 Input Flag for ADCCEVT1 Signal
};

union XBARFLG2_REG {
    Uint32  all;
    struct  XBARFLG2_BITS  bit;
};

struct XBARFLG3_BITS {                  // bits description
    Uint32 ADCCEVT2:1;                  // 0 Input Flag for ADCCEVT2 Signal
    Uint32 ADCCEVT3:1;                  // 1 Input Flag for ADCCEVT3 Signal
    Uint32 ADCCEVT4:1;                  // 2 Input Flag for ADCCEVT4 Signal
    Uint32 rsvd1:1;                     // 3 Reserved
    Uint32 rsvd2:1;                     // 4 Reserved
    Uint32 rsvd3:1;                     // 5 Reserved
    Uint32 rsvd4:1;                     // 6 Reserved
    Uint32 SD1FLT1_COMPL:1;             // 7 Input Flag for SD1FLT1.COMPL Signal
    Uint32 SD1FLT1_COMPH:1;             // 8 Input Flag for SD1FLT1.COMPH Signal
    Uint32 SD1FLT2_COMPL:1;             // 9 Input Flag for SD1FLT2.COMPL Signal
    Uint32 SD1FLT2_COMPH:1;             // 10 Input Flag for SD1FLT2.COMPH Signal
    Uint32 SD1FLT3_COMPL:1;             // 11 Input Flag for SD1FLT3.COMPL Signal
    Uint32 SD1FLT3_COMPH:1;             // 12 Input Flag for SD1FLT3.COMPH Signal
    Uint32 SD1FLT4_COMPL:1;             // 13 Input Flag for SD1FLT4.COMPL Signal
    Uint32 SD1FLT4_COMPH:1;             // 14 Input Flag for SD1FLT4.COMPH Signal
    Uint32 SD2FLT1_COMPL:1;             // 15 Input Flag for SD2FLT1.COMPL Signal
    Uint32 SD2FLT1_COMPH:1;             // 16 Input Flag for SD2FLT1.COMPH Signal
    Uint32 SD2FLT2_COMPL:1;             // 17 Input Flag for SD2FLT2.COMPL Signal
    Uint32 SD2FLT2_COMPH:1;             // 18 Input Flag for SD2FLT2.COMPH Signal
    Uint32 SD2FLT3_COMPL:1;             // 19 Input Flag for SD2FLT3.COMPL Signal
    Uint32 SD2FLT3_COMPH:1;             // 20 Input Flag for SD2FLT3.COMPH Signal
    Uint32 SD2FLT4_COMPL:1;             // 21 Input Flag for SD2FLT4.COMPL Signal
    Uint32 SD2FLT4_COMPH:1;             // 22 Input Flag for SD2FLT4.COMPH Signal
    Uint32 CAP7_OUT:1;                 // 23 Input Flag for CAP7.OUT Signal
    Uint32 SD1FLT1_COMPZ:1;             // 24 Input Flag for SD1FLT1.COMPZ Signal
    Uint32 SD1FLT1_DRINT:1;             // 25 Input Flag for SD1FLT1.DRINT Signal
    Uint32 SD1FLT2_COMPZ:1;             // 26 Input Flag for SD1FLT2.COMPZ Signal
    Uint32 SD1FLT2_DRINT:1;             // 27 Input Flag for SD1FLT2.DRINT Signal
    Uint32 SD1FLT3_COMPZ:1;             // 28 Input Flag for SD1FLT3.COMPZ Signal
    Uint32 SD1FLT3_DRINT:1;             // 29 Input Flag for SD1FLT3.DRINT Signal
    Uint32 SD1FLT4_COMPZ:1;             // 30 Input Flag for SD1FLT4.COMPZ Signal
    Uint32 SD1FLT4_DRINT:1;             // 31 Input Flag for SD1FLT4.DRINT Signal
};

union XBARFLG3_REG {
    Uint32  all;
    struct  XBARFLG3_BITS  bit;
};

struct XBARFLG4_BITS {                  // bits description
    Uint32 SD2FLT1_COMPZ:1;             // 0 Input Flag for SD2FLT1.COMPZ Signal
    Uint32 SD2FLT1_DRINT:1;             // 1 Input Flag for SD2FLT1.DRINT Signal
    Uint32 SD2FLT2_COMPZ:1;             // 2 Input Flag for SD2FLT2.COMPZ Signal
    Uint32 SD2FLT2_DRINT:1;             // 3 Input Flag for SD2FLT2.DRINT Signal
    Uint32 SD2FLT3_COMPZ:1;             // 4 Input Flag for SD2FLT3.COMPZ Signal
    Uint32 SD2FLT3_DRINT:1;             // 5 Input Flag for SD2FLT3.DRINT Signal
    Uint32 SD2FLT4_COMPZ:1;             // 6 Input Flag for SD2FLT4.COMPZ Signal
    Uint32 SD2FLT4_DRINT:1;             // 7 Input Flag for SD2FLT4.DRINT Signal
    Uint32 EMAC_PPS0:1;                 // 8 Input Flag for EMAC_PPS0 Signal
    Uint32 MCANA_FEVT0:1;               // 9 Input Flag for MCANA_FEVT0 Signal
    Uint32 MCANA_FEVT1:1;               // 10 Input Flag for MCANA_FEVT1 Signal
    Uint32 MCANA_FEVT2:1;               // 11 Input Flag for MCANA_FEVT2 Signal
    Uint32 FLB7_4_1:1;                  // 12 Input Flag for FLB7_4.1 Signal
    Uint32 FLB7_5_1:1;                  // 13 Input Flag for FLB7_5.1 Signal
    Uint32 FLB8_4_1:1;                  // 14 Input Flag for FLB8_4.1 Signal
    Uint32 FLB8_5_1:1;                  // 15 Input Flag for FLB8_5.1 Signal
    Uint32 FLB1_OUT4:1;                 // 16 Input Flag for FLB1_OUT4 Signal
    Uint32 FLB1_OUT5:1;                 // 17 Input Flag for FLB1_OUT5 Signal
    Uint32 FLB2_OUT4:1;                 // 18 Input Flag for FLB2_OUT4 Signal
    Uint32 FLB2_OUT5:1;                 // 19 Input Flag for FLB2_OUT5 Signal
    Uint32 FLB3_OUT4:1;                 // 20 Input Flag for FLB3_OUT4 Signal
    Uint32 FLB3_OUT5:1;                 // 21 Input Flag for FLB3_OUT5 Signal
    Uint32 FLB4_OUT4:1;                 // 22 Input Flag for FLB4_OUT4 Signal
    Uint32 FLB4_OUT5:1;                 // 23 Input Flag for FLB4_OUT5 Signal
    Uint32 rsvd1:1;                     // 24 Reserved
    Uint32 rsvd2:1;                     // 25 Reserved
    Uint32 rsvd3:1;                     // 26 Reserved
    Uint32 rsvd4:1;                     // 27 Reserved
    Uint32 rsvd5:1;                     // 28 Reserved
    Uint32 rsvd6:1;                     // 29 Reserved
    Uint32 rsvd7:1;                     // 30 Reserved
    Uint32 CLAHALT:1;                   // 31 Input Latch for CLAHALT Signal
};

union XBARFLG4_REG {
    Uint32  all;
    struct  XBARFLG4_BITS  bit;
};

struct XBARCLR1_BITS {                  // bits description
    Uint32 COMP1_CTRIPL:1;             // 0 Input Flag Clear for COMP1.CTRIPL Signal
    Uint32 COMP1_CTRIPH:1;             // 1 Input Flag Clear for COMP1.CTRIPH Signal
    Uint32 COMP2_CTRIPL:1;             // 2 Input Flag Clear for COMP2.CTRIPL Signal
    Uint32 COMP2_CTRIPH:1;             // 3 Input Flag Clear for COMP2.CTRIPH Signal
    Uint32 COMP3_CTRIPL:1;             // 4 Input Flag Clear for COMP3.CTRIPL Signal
    Uint32 COMP3_CTRIPH:1;             // 5 Input Flag Clear for COMP3.CTRIPH Signal
    Uint32 COMP4_CTRIPL:1;             // 6 Input Flag Clear for COMP4.CTRIPL Signal
    Uint32 COMP4_CTRIPH:1;             // 7 Input Flag Clear for COMP4.CTRIPH Signal
    Uint32 COMP5_CTRIPL:1;             // 8 Input Flag Clear for COMP5.CTRIPL Signal
    Uint32 COMP5_CTRIPH:1;             // 9 Input Flag Clear for COMP5.CTRIPH Signal
    Uint32 COMP6_CTRIPL:1;             // 10 Input Flag Clear for COMP6.CTRIPL Signal
    Uint32 COMP6_CTRIPH:1;             // 11 Input Flag Clear for COMP6.CTRIPH Signal
    Uint32 COMP7_CTRIPL:1;             // 12 Input Flag Clear for COMP7.CTRIPL Signal
    Uint32 COMP7_CTRIPH:1;             // 13 Input Flag Clear for COMP7.CTRIPH Signal
    Uint32 COMP8_CTRIPL:1;             // 14 Input Flag Clear for COMP8.CTRIPL Signal
    Uint32 COMP8_CTRIPH:1;             // 15 Input Flag Clear for COMP8.CTRIPH Signal
    Uint32 COMP1_CTRIPOUTL:1;          // 16 Input Flag Clear for COMP1.CTRIPOUTL Signal
    Uint32 COMP1_CTRIPOUTH:1;          // 17 Input Flag Clear for COMP1.CTRIPOUTH Signal
    Uint32 COMP2_CTRIPOUTL:1;          // 18 Input Flag Clear for COMP2.CTRIPOUTL Signal
    Uint32 COMP2_CTRIPOUTH:1;          // 19 Input Flag Clear for COMP2.CTRIPOUTH Signal
    Uint32 COMP3_CTRIPOUTL:1;          // 20 Input Flag Clear for COMP3.CTRIPOUTL Signal
    Uint32 COMP3_CTRIPOUTH:1;          // 21 Input Flag Clear for COMP3.CTRIPOUTH Signal
    Uint32 COMP4_CTRIPOUTL:1;          // 22 Input Flag Clear for COMP4.CTRIPOUTL Signal
    Uint32 COMP4_CTRIPOUTH:1;          // 23 Input Flag Clear for COMP4.CTRIPOUTH Signal
    Uint32 COMP5_CTRIPOUTL:1;          // 24 Input Flag Clear for COMP5.CTRIPOUTL Signal
    Uint32 COMP5_CTRIPOUTH:1;          // 25 Input Flag Clear for COMP5.CTRIPOUTH Signal
    Uint32 COMP6_CTRIPOUTL:1;          // 26 Input Flag Clear for COMP6.CTRIPOUTL Signal
    Uint32 COMP6_CTRIPOUTH:1;          // 27 Input Flag Clear for COMP6.CTRIPOUTH Signal
    Uint32 COMP7_CTRIPOUTL:1;          // 28 Input Flag Clear for COMP7.CTRIPOUTL Signal
    Uint32 COMP7_CTRIPOUTH:1;          // 29 Input Flag Clear for COMP7.CTRIPOUTH Signal
    Uint32 COMP8_CTRIPOUTL:1;          // 30 Input Flag Clear for COMP8.CTRIPOUTL Signal
    Uint32 COMP8_CTRIPOUTH:1;          // 31 Input Flag Clear for COMP8.CTRIPOUTH Signal
};

union XBARCLR1_REG {
    Uint32  all;
    struct  XBARCLR1_BITS  bit;
};

struct XBARCLR2_BITS {                  // bits description
    Uint32 INPUT1:1;                    // 0 Input Flag Clear for INPUT1 Signal
    Uint32 INPUT2:1;                    // 1 Input Flag Clear for INPUT2 Signal
    Uint32 INPUT3:1;                    // 2 Input Flag Clear for INPUT3 Signal
    Uint32 INPUT4:1;                    // 3 Input Flag Clear for INPUT4 Signal
    Uint32 INPUT5:1;                    // 4 Input Flag Clear for INPUT5 Signal
    Uint32 INPUT6:1;                    // 5 Input Flag Clear for INPUT6 Signal
    Uint32 ADCSOCA:1;                   // 6 Input Flag Clear for ADCSOCA Signal
    Uint32 ADCSOCB:1;                   // 7 Input Flag Clear for ADCSOCB Signal
    Uint32 INPUT7:1;                    // 8 Input Flag Clear for INPUT7 Signal
    Uint32 INPUT8:1;                    // 9 Input Flag Clear for INPUT8 Signal
    Uint32 INPUT9:1;                    // 10 Input Flag Clear for INPUT9 Signal
    Uint32 INPUT10:1;                   // 11 Input Flag Clear for INPUT10 Signal
    Uint32 INPUT11:1;                   // 12 Input Flag Clear for INPUT11 Signal
    Uint32 INPUT12:1;                   // 13 Input Flag Clear for INPUT12 Signal
    Uint32 INPUT13:1;                   // 14 Input Flag Clear for INPUT13 Signal
    Uint32 INPUT14:1;                   // 15 Input Flag Clear for INPUT14 Signal
    Uint32 CAP1_OUT:1;                 // 16 Input Flag Clear for CAP1.OUT Signal
    Uint32 CAP2_OUT:1;                 // 17 Input Flag Clear for CAP2.OUT Signal
    Uint32 CAP3_OUT:1;                 // 18 Input Flag Clear for CAP3.OUT Signal
    Uint32 CAP4_OUT:1;                 // 19 Input Flag Clear for CAP4.OUT Signal
    Uint32 CAP5_OUT:1;                 // 20 Input Flag Clear for CAP5.OUT Signal
    Uint32 CAP6_OUT:1;                 // 21 Input Flag Clear for CAP6.OUT Signal
    Uint32 EXTSYNCOUT:1;                // 22 Input Flag Clear for EXTSYNCOUT Signal
    Uint32 ADCAEVT1:1;                  // 23 Input Flag Clear for ADCAEVT1 Signal
    Uint32 ADCAEVT2:1;                  // 24 Input Flag Clear for ADCAEVT2 Signal
    Uint32 ADCAEVT3:1;                  // 25 Input Flag Clear for ADCAEVT3 Signal
    Uint32 ADCAEVT4:1;                  // 26 Input Flag Clear for ADCAEVT4 Signal
    Uint32 ADCBEVT1:1;                  // 27 Input Flag Clear for ADCBEVT1 Signal
    Uint32 ADCBEVT2:1;                  // 28 Input Flag Clear for ADCBEVT2 Signal
    Uint32 ADCBEVT3:1;                  // 29 Input Flag Clear for ADCBEVT3 Signal
    Uint32 ADCBEVT4:1;                  // 30 Input Flag Clear for ADCBEVT4 Signal
    Uint32 ADCCEVT1:1;                  // 31 Input Flag Clear for ADCCEVT1 Signal
};

union XBARCLR2_REG {
    Uint32  all;
    struct  XBARCLR2_BITS  bit;
};

struct XBARCLR3_BITS {                  // bits description
    Uint32 ADCCEVT2:1;                  // 0 Input Flag Clear for ADCCEVT2 Signal
    Uint32 ADCCEVT3:1;                  // 1 Input Flag Clear for ADCCEVT3 Signal
    Uint32 ADCCEVT4:1;                  // 2 Input Flag Clear for ADCCEVT4 Signal
    Uint32 rsvd1:1;                     // 3 Reserved
    Uint32 rsvd2:1;                     // 4 Reserved
    Uint32 rsvd3:1;                     // 5 Reserved
    Uint32 rsvd4:1;                     // 6 Reserved
    Uint32 SD1FLT1_COMPL:1;             // 7 Input Flag Clear for SD1FLT1.COMPL Signal
    Uint32 SD1FLT1_COMPH:1;             // 8 Input Flag Clear for SD1FLT1.COMPH Signal
    Uint32 SD1FLT2_COMPL:1;             // 9 Input Flag Clear for SD1FLT2.COMPL Signal
    Uint32 SD1FLT2_COMPH:1;             // 10 Input Flag Clear for SD1FLT2.COMPH Signal
    Uint32 SD1FLT3_COMPL:1;             // 11 Input Flag Clear for SD1FLT3.COMPL Signal
    Uint32 SD1FLT3_COMPH:1;             // 12 Input Flag Clear for SD1FLT3.COMPH Signal
    Uint32 SD1FLT4_COMPL:1;             // 13 Input Flag Clear for SD1FLT4.COMPL Signal
    Uint32 SD1FLT4_COMPH:1;             // 14 Input Flag Clear for SD1FLT4.COMPH Signal
    Uint32 SD2FLT1_COMPL:1;             // 15 Input Flag Clear for SD2FLT1.COMPL Signal
    Uint32 SD2FLT1_COMPH:1;             // 16 Input Flag Clear for SD2FLT1.COMPH Signal
    Uint32 SD2FLT2_COMPL:1;             // 17 Input Flag Clear for SD2FLT2.COMPL Signal
    Uint32 SD2FLT2_COMPH:1;             // 18 Input Flag Clear for SD2FLT2.COMPH Signal
    Uint32 SD2FLT3_COMPL:1;             // 19 Input Flag Clear for SD2FLT3.COMPL Signal
    Uint32 SD2FLT3_COMPH:1;             // 20 Input Flag Clear for SD2FLT3.COMPH Signal
    Uint32 SD2FLT4_COMPL:1;             // 21 Input Flag Clear for SD2FLT4.COMPL Signal
    Uint32 SD2FLT4_COMPH:1;             // 22 Input Flag Clear for SD2FLT4.COMPH Signal
    Uint32 CAP7_OUT:1;                 // 23 Input Flag clear for CAP7.OUT Signal
    Uint32 SD1FLT1_COMPZ:1;             // 24 Input Flag clear for SD1FLT1.COMPZ Signal
    Uint32 SD1FLT1_DRINT:1;             // 25 Input Flag clear for SD1FLT1.DRINT Signal
    Uint32 SD1FLT2_COMPZ:1;             // 26 Input Flag clear for SD1FLT2.COMPZ Signal
    Uint32 SD1FLT2_DRINT:1;             // 27 Input Flag clear for SD1FLT2.DRINT Signal
    Uint32 SD1FLT3_COMPZ:1;             // 28 Input Flag clear for SD1FLT3.COMPZ Signal
    Uint32 SD1FLT3_DRINT:1;             // 29 Input Flag clear for SD1FLT3.DRINT Signal
    Uint32 SD1FLT4_COMPZ:1;             // 30 Input Flag clear for SD1FLT4.COMPZ Signal
    Uint32 SD1FLT4_DRINT:1;             // 31 Input Flag clear for SD1FLT4.DRINT Signal
};

union XBARCLR3_REG {
    Uint32  all;
    struct  XBARCLR3_BITS  bit;
};

struct XBARCLR4_BITS {                  // bits description
    Uint32 SD2FLT1_COMPZ:1;             // 0 Input Flag clear for SD2FLT1.COMPZ Signal
    Uint32 SD2FLT1_DRINT:1;             // 1 Input Flag clear for SD2FLT1.DRINT Signal
    Uint32 SD2FLT2_COMPZ:1;             // 2 Input Flag clear for SD2FLT2.COMPZ Signal
    Uint32 SD2FLT2_DRINT:1;             // 3 Input Flag clear for SD2FLT2.DRINT Signal
    Uint32 SD2FLT3_COMPZ:1;             // 4 Input Flag clear for SD2FLT3.COMPZ Signal
    Uint32 SD2FLT3_DRINT:1;             // 5 Input Flag clear for SD2FLT3.DRINT Signal
    Uint32 SD2FLT4_COMPZ:1;             // 6 Input Flag clear for SD2FLT4.COMPZ Signal
    Uint32 SD2FLT4_DRINT:1;             // 7 Input Flag clear for SD2FLT4.DRINT Signal
    Uint32 rsvd1:1;                     // 8 Reserved
    Uint32 rsvd2:1;                     // 9 Reserved
    Uint32 rsvd3:1;                     // 10 Reserved
    Uint32 rsvd4:1;                     // 11 Reserved
    Uint32 FLB7_4_1:1;                  // 12 Input Flag clear for FLB7_4_1 Signal
    Uint32 FLB7_5_1:1;                  // 13 Input Flag clear for FLB7_5_1 Signal
    Uint32 FLB8_4_1:1;                  // 14 Input Flag clear for FLB8_4_1 Signal
    Uint32 FLB8_5_1:1;                  // 15 Input Flag clear for FLB8_5_1 Signal
    Uint32 FLB1_OUT4:1;                 // 16 Input Flag clear for FLB1_OUT4 Signal
    Uint32 FLB1_OUT5:1;                 // 17 Input Flag clear for FLB1_OUT5 Signal
    Uint32 FLB2_OUT4:1;                 // 18 Input Flag clear for FLB2_OUT4 Signal
    Uint32 FLB2_OUT5:1;                 // 19 Input Flag clear for FLB2_OUT5 Signal
    Uint32 FLB3_OUT4:1;                 // 20 Input Flag clear for FLB3_OUT4 Signal
    Uint32 FLB3_OUT5:1;                 // 21 Input Flag clear for FLB3_OUT5 Signal
    Uint32 FLB4_OUT4:1;                 // 22 Input Flag clear for FLB4_OUT4 Signal
    Uint32 FLB4_OUT5:1;                 // 23 Input Flag clear for FLB4_OUT5 Signal
    Uint32 rsvd5:1;                     // 24 Reserved
    Uint32 rsvd6:1;                     // 25 Reserved
    Uint32 rsvd7:1;                     // 26 Reserved
    Uint32 rsvd8:1;                     // 27 Reserved
    Uint32 rsvd9:1;                     // 28 Reserved
    Uint32 rsvd10:1;                    // 29 Reserved
    Uint32 rsvd11:1;                    // 30 Reserved
    Uint32 CLAHALT:1;                   // 31 Input Flag clear for CLAHALT Signal
};

union XBARCLR4_REG {
    Uint32  all;
    struct  XBARCLR4_BITS  bit;
};

struct XBAR_REGS {
    union   XBARFLG1_REG                     XBARFLG1;                     // X-Bar Input Flag Register 1
    union   XBARFLG2_REG                     XBARFLG2;                     // X-Bar Input Flag Register 2
    union   XBARFLG3_REG                     XBARFLG3;                     // X-Bar Input Flag Register 3
    union   XBARFLG4_REG                     XBARFLG4;                     // X-Bar Input Flag Register 4
    union   XBARCLR1_REG                     XBARCLR1;                     // X-Bar Input Flag Clear Register 1
    union   XBARCLR2_REG                     XBARCLR2;                     // X-Bar Input Flag Clear Register 2
    union   XBARCLR3_REG                     XBARCLR3;                     // X-Bar Input Flag Clear Register 3
    union   XBARCLR4_REG                     XBARCLR4;                     // X-Bar Input Flag Clear Register 4
};

//---------------------------------------------------------------------------
// XBAR External References & Function Declarations:
//
extern volatile struct XBAR_REGS XbarRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
