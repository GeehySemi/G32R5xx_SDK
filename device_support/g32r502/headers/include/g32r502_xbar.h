//###########################################################################
//
// FILE:    g32r502_xbar.h
//
// TITLE:   Definitions for the XBAR registers.
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

#ifndef G32R502_XBAR_H
#define G32R502_XBAR_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// XBAR Individual Register Bit Definitions:

struct XBARFLG1_BITS
{
    Uint32 COMP1_CTRIPL     : 1;  // 0  COMP1_PWML input flag
    Uint32 COMP1_CTRIPH     : 1;  // 1  COMP1_PWMH input flag
    Uint32 COMP2_CTRIPL     : 1;  // 2  COMP2_PWML input flag
    Uint32 COMP2_CTRIPH     : 1;  // 3  COMP2_PWMH input flag
    Uint32 COMP3_CTRIPL     : 1;  // 4  COMP3_PWML input flag
    Uint32 COMP3_CTRIPH     : 1;  // 5  COMP3_PWMH input flag
    Uint32 COMP4_CTRIPL     : 1;  // 6  COMP4_PWML input flag
    Uint32 COMP4_CTRIPH     : 1;  // 7  COMP4_PWMH input flag
    Uint32 rsvd1            : 8;  // 8-15 Reserved
    Uint32 COMP1_CTRIPOUTL  : 1;  // 16 COMP1_OUTL input flag
    Uint32 COMP1_CTRIPOUTH  : 1;  // 17 COMP1_OUTH input flag
    Uint32 COMP2_CTRIPOUTL  : 1;  // 18 COMP2_OUTL input flag
    Uint32 COMP2_CTRIPOUTH  : 1;  // 19 COMP2_OUTH input flag
    Uint32 COMP3_CTRIPOUTL  : 1;  // 20 COMP3_OUTL input flag
    Uint32 COMP3_CTRIPOUTH  : 1;  // 21 COMP3_OUTH input flag
    Uint32 COMP4_CTRIPOUTL  : 1;  // 22 COMP4_OUTL input flag
    Uint32 COMP4_CTRIPOUTH  : 1;  // 23 COMP4_OUTH input flag
    Uint32 rsvd2            : 8;  // 24-31 Reserved
};

union XBARFLG1_REG
{
    Uint32               all;
    struct XBARFLG1_BITS bit;
};

struct XBARFLG2_BITS
{
    Uint32 INPUT1      : 1;  // 0  INPUT1 input flag
    Uint32 INPUT2      : 1;  // 1  INPUT2 input flag
    Uint32 INPUT3      : 1;  // 2  INPUT3 input flag
    Uint32 INPUT4      : 1;  // 3  INPUT4 input flag
    Uint32 INPUT5      : 1;  // 4  INPUT5 input flag
    Uint32 INPUT6      : 1;  // 5  INPUT6 input flag
    Uint32 ADCSOCA     : 1;  // 6  ADCSOCA input flag
    Uint32 ADCSOCB     : 1;  // 7  ADCSOCB input flag
    Uint32 INPUT7      : 1;  // 8  INPUT7 input flag
    Uint32 INPUT8      : 1;  // 9  INPUT8 input flag
    Uint32 INPUT9      : 1;  // 10 INPUT9 input flag
    Uint32 INPUT10     : 1;  // 11 INPUT10 input flag
    Uint32 INPUT11     : 1;  // 12 INPUT11 input flag
    Uint32 INPUT12     : 1;  // 13 INPUT12 input flag
    Uint32 INPUT13     : 1;  // 14 INPUT13 input flag
    Uint32 INPUT14     : 1;  // 15 INPUT14 input flag
    Uint32 CAP1_OUT    : 1;  // 16 CAP1_OUT input flag
    Uint32 CAP2_OUT    : 1;  // 17 CAP2_OUT input flag
    Uint32 CAP3_OUT    : 1;  // 18 CAP3_OUT input flag
    Uint32 rsvd1       : 1;  // 19 Reserved
    Uint32 rsvd2       : 1;  // 20 Reserved
    Uint32 rsvd3       : 1;  // 21 Reserved
    Uint32 EXTSYNCOUT  : 1;  // 22 EXTSYNCOUT input flag
    Uint32 ADCAEVT1    : 1;  // 23 ADCAEVT1 input flag
    Uint32 ADCAEVT2    : 1;  // 24 ADCAEVT2 input flag
    Uint32 ADCAEVT3    : 1;  // 25 ADCAEVT3 input flag
    Uint32 ADCAEVT4    : 1;  // 26 ADCAEVT4 input flag
    Uint32 rsvd4       : 4;  // 27-30 Reserved
    Uint32 ADCCEVT1    : 1;  // 31 ADCCEVT1 input flag
};

union XBARFLG2_REG
{
    Uint32               all;
    struct XBARFLG2_BITS bit;
};

struct XBARFLG3_BITS
{
    Uint32 ADCCEVT2 : 1;  // 0  ADCCEVT2 input flag
    Uint32 ADCCEVT3 : 1;  // 1  ADCCEVT3 input flag
    Uint32 ADCCEVT4 : 1;  // 2  ADCCEVT4 input flag
    Uint32 rsvd1    : 29; // 3-31 Reserved
};

union XBARFLG3_REG
{
    Uint32               all;
    struct XBARFLG3_BITS bit;
};

struct XBARFLG4_BITS
{
    Uint32 rsvd0        : 16;  // 0-15   Reserved
    Uint32 FLB1_OUT4    : 1;  // 16    FLB1_OUT4 input flag
    Uint32 FLB1_OUT5    : 1;  // 17    FLB1_OUT5 input flag
    Uint32 FLB2_OUT4    : 1;  // 18    FLB2_OUT4 input flag
    Uint32 FLB2_OUT5    : 1;  // 19    FLB2_OUT5 input flag
    Uint32 FLB3_OUT4    : 1;  // 20    FLB3_OUT4 input flag
    Uint32 FLB3_OUT5    : 1;  // 21    FLB3_OUT5 input flag
    Uint32 FLB4_OUT4    : 1;  // 22    FLB4_OUT4 input flag
    Uint32 FLB4_OUT5    : 1;  // 23    FLB4_OUT5 input flag
    Uint32 rsvd1        : 8;  // 24-31 Reserved
};

union XBARFLG4_REG
{
    Uint32               all;
    struct XBARFLG4_BITS bit;
};

struct XBARCLR1_BITS
{
    Uint32 COMP1_CTRIPL     : 1;  // 0  Write 1 to clear COMP1_CTRIPL flag
    Uint32 COMP1_CTRIPH     : 1;  // 1  Write 1 to clear COMP1_CTRIPH flag
    Uint32 COMP2_CTRIPL     : 1;  // 2  Write 1 to clear COMP2_CTRIPL flag
    Uint32 COMP2_CTRIPH     : 1;  // 3  Write 1 to clear COMP2_CTRIPH flag
    Uint32 COMP3_CTRIPL     : 1;  // 4  Write 1 to clear COMP3_CTRIPL flag
    Uint32 COMP3_CTRIPH     : 1;  // 5  Write 1 to clear COMP3_CTRIPH flag
    Uint32 COMP4_CTRIPL     : 1;  // 6  Write 1 to clear COMP4_CTRIPL flag
    Uint32 COMP4_CTRIPH     : 1;  // 7  Write 1 to clear COMP4_CTRIPH flag
    Uint32 rsvd1            : 8;  // 8-15 Reserved
    Uint32 COMP1_CTRIPOUTL  : 1;  // 16 Write 1 to clear COMP1_CTRIPOUTL flag
    Uint32 COMP1_CTRIPOUTH  : 1;  // 17 Write 1 to clear COMP1_CTRIPOUTH flag
    Uint32 COMP2_CTRIPOUTL  : 1;  // 18 Write 1 to clear COMP2_CTRIPOUTL flag
    Uint32 COMP2_CTRIPOUTH  : 1;  // 19 Write 1 to clear COMP2_CTRIPOUTH flag
    Uint32 COMP3_CTRIPOUTL  : 1;  // 20 Write 1 to clear COMP3_CTRIPOUTL flag
    Uint32 COMP3_CTRIPOUTH  : 1;  // 21 Write 1 to clear COMP3_CTRIPOUTH flag
    Uint32 COMP4_CTRIPOUTL  : 1;  // 22 Write 1 to clear COMP4_CTRIPOUTL flag
    Uint32 COMP4_CTRIPOUTH  : 1;  // 23 Write 1 to clear COMP4_CTRIPOUTH flag
    Uint32 rsvd2            : 8;  // 24-31 Reserved
};

union XBARCLR1_REG
{
    Uint32                all;
    struct XBARCLR1_BITS  bit;
};

struct XBARCLR2_BITS
{
    Uint32 INPUT1      : 1;  // 0  Write 1 to clear INPUT1 flag
    Uint32 INPUT2      : 1;  // 1  Write 1 to clear INPUT2 flag
    Uint32 INPUT3      : 1;  // 2  Write 1 to clear INPUT3 flag
    Uint32 INPUT4      : 1;  // 3  Write 1 to clear INPUT4 flag
    Uint32 INPUT5      : 1;  // 4  Write 1 to clear INPUT5 flag
    Uint32 INPUT6      : 1;  // 5  Write 1 to clear INPUT6 flag
    Uint32 ADCSOCA     : 1;  // 6  Write 1 to clear ADCSOCA flag
    Uint32 ADCSOCB     : 1;  // 7  Write 1 to clear ADCSOCB flag
    Uint32 INPUT7      : 1;  // 8  Write 1 to clear INPUT7 flag
    Uint32 INPUT8      : 1;  // 9  Write 1 to clear INPUT8 flag
    Uint32 INPUT9      : 1;  // 10 Write 1 to clear INPUT9 flag
    Uint32 INPUT10     : 1;  // 11 Write 1 to clear INPUT10 flag
    Uint32 INPUT11     : 1;  // 12 Write 1 to clear INPUT11 flag
    Uint32 INPUT12     : 1;  // 13 Write 1 to clear INPUT12 flag
    Uint32 INPUT13     : 1;  // 14 Write 1 to clear INPUT13 flag
    Uint32 INPUT14     : 1;  // 15 Write 1 to clear INPUT14 flag
    Uint32 CAP1_OUT    : 1;  // 16 Write 1 to clear CAP1_OUT flag
    Uint32 CAP2_OUT    : 1;  // 17 Write 1 to clear CAP2_OUT flag
    Uint32 CAP3_OUT    : 1;  // 18 Write 1 to clear CAP3_OUT flag
    Uint32 rsvd1       : 1;  // 19 Reserved
    Uint32 rsvd2       : 1;  // 20 Reserved
    Uint32 rsvd3       : 1;  // 21 Reserved
    Uint32 EXTSYNCOUT  : 1;  // 22 Write 1 to clear EXTSYNCOUT flag
    Uint32 ADCAEVT1    : 1;  // 23 Write 1 to clear ADCAEVT1 flag
    Uint32 ADCAEVT2    : 1;  // 24 Write 1 to clear ADCAEVT2 flag
    Uint32 ADCAEVT3    : 1;  // 25 Write 1 to clear ADCAEVT3 flag
    Uint32 ADCAEVT4    : 1;  // 26 Write 1 to clear ADCAEVT4 flag
    Uint32 rsvd4       : 4;  // 27-30 Reserved
    Uint32 ADCCEVT1    : 1;  // 31 Write 1 to clear ADCCEVT1 flag
};

union XBARCLR2_REG
{
    Uint32                all;
    struct XBARCLR2_BITS  bit;
};

struct XBARCLR3_BITS
{
    Uint32 ADCCEVT2 : 1;  // 0  Write 1 to clear ADCCEVT2 flag
    Uint32 ADCCEVT3 : 1;  // 1  Write 1 to clear ADCCEVT3 flag
    Uint32 ADCCEVT4 : 1;  // 2  Write 1 to clear ADCCEVT4 flag
    Uint32 rsvd1    : 29; // 3-31 Reserved
};

union XBARCLR3_REG
{
    Uint32                all;
    struct XBARCLR3_BITS  bit;
};

struct XBARCLR4_BITS
{
    Uint32 rsvd0      : 16; // 0-15  Reserved
    Uint32 FLB1_OUT4  : 1;  // 16    Write 1 to clear FLB1_OUT4 flag
    Uint32 FLB1_OUT5  : 1;  // 17    Write 1 to clear FLB1_OUT5 flag
    Uint32 FLB2_OUT4  : 1;  // 18    Write 1 to clear FLB2_OUT4 flag
    Uint32 FLB2_OUT5  : 1;  // 19    Write 1 to clear FLB2_OUT5 flag
    Uint32 FLB3_OUT4  : 1;  // 20    Write 1 to clear FLB3_OUT4 flag
    Uint32 FLB3_OUT5  : 1;  // 21    Write 1 to clear FLB3_OUT5 flag
    Uint32 FLB4_OUT4  : 1;  // 22    Write 1 to clear FLB4_OUT4 flag
    Uint32 FLB4_OUT5  : 1;  // 23    Write 1 to clear FLB4_OUT5 flag
    Uint32 rsvd1      : 8;  // 24-31 Reserved
};

union XBARCLR4_REG
{
    Uint32                all;
    struct XBARCLR4_BITS  bit;
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
