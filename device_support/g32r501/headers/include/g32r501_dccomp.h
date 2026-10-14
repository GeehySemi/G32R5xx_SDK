//###########################################################################
//
// FILE:    g32r501_DCCOMP.h
//
// TITLE:   Definitions for the DCCOMP registers.
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

#ifndef G32R501_DCCOMP_H
#define G32R501_DCCOMP_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// DCCOMP Individual Register Bit Definitions:

struct DCCOMPCTRL_BITS {                // bits description
    Uint32 DCCOMPEN:4;                   // 3:0 DCCOMP Enable
    Uint32 ERREN:4;                      // 7:4 Error Enable
    Uint32 SIGEN:4;                      // 11:8 Single Shot Mode Enable
    Uint32 DONEEN:4;                     // 15:12 DONE Enable
    Uint32 rsvd1:16;                     // 31:16 Reserved
};

union DCCOMPCTRL_REG {
    Uint32  all;
    struct  DCCOMPCTRL_BITS  bit;
};

struct DCCOMPREV_BITS {                 // bits description
    Uint32 MINOR:6;                      // 5:0 Major Revision Number
    Uint32 rsvd1:2;                      // 7:6 Reserved
    Uint32 MAJOR:3;                      // 10:8 Major Revision Number
    Uint32 rsvd2:5;                      // 15:11 Reserved
    Uint32 rsvd3:12;                     // 27:16 Reserved
    Uint32 rsvd4:2;                      // 29:28 Reserved
    Uint32 rsvd5:2;                      // 31:30 Reserved
};

union DCCOMPREV_REG {
    Uint32  all;
    struct  DCCOMPREV_BITS  bit;
};

struct DCCOMPCNTSEED0_BITS {            // bits description
    Uint32 CNTSEED0:20;                  // 19:0 Counter 0 Seed Value
    Uint32 rsvd1:12;                     // 31:20 Reserved
};

union DCCOMPCNTSEED0_REG {
    Uint32  all;
    struct  DCCOMPCNTSEED0_BITS  bit;
};

struct DCCOMPVALSEED0_BITS {            // bits description
    Uint32 VALSEED0:16;                  // 15:0 Valid Duration Counter 0 Seed Value
    Uint32 rsvd1:16;                     // 31:16 Reserved
};

union DCCOMPVALSEED0_REG {
    Uint32  all;
    struct  DCCOMPVALSEED0_BITS  bit;
};

struct DCCOMPCNTSEED1_BITS {            // bits description
    Uint32 CNTSEED1:20;                  // 19:0 Counter 1 Seed Value
    Uint32 rsvd1:12;                     // 31:20 Reserved
};

union DCCOMPCNTSEED1_REG {
    Uint32  all;
    struct  DCCOMPCNTSEED1_BITS  bit;
};

struct DCCOMPFLG_BITS {                 // bits description
    Uint32 ERRFLG:1;                     // 0 Error Flag
    Uint32 SIGDONEFLG:1;                 // 1 Single-Shot Done Flag
    Uint32 rsvd1:14;                     // 15:2 Reserved
    Uint32 rsvd2:16;                     // 31:16 Reserved
};

union DCCOMPFLG_REG {
    Uint32  all;
    struct  DCCOMPFLG_BITS  bit;
};

struct DCCOMPCLKSRCCNT0_BITS {           // bits description
    Uint32 CLKSRCCNT0:20;                 // 19:0 Clock Source 0 counter attached Value
    Uint32 rsvd1:12;                      // 31:20 Reserved
};

union DCCOMPCLKSRCCNT0_REG {
    Uint32  all;
    struct  DCCOMPCLKSRCCNT0_BITS  bit;
};

struct DCCOMPCLKSRCVAL0_BITS {          // bits description
    Uint32 CLKSRCVAL0:16;                // 15:0 Clock Source 0 valid counter attached Value
    Uint32 rsvd1:16;                     // 31:16 Reserved
};

union DCCOMPCLKSRCVAL0_REG {
    Uint32  all;
    struct  DCCOMPCLKSRCVAL0_BITS  bit;
};

struct DCCOMPCLKSRCCNT1_BITS {          // bits description
    Uint32 CLKSRCCNT1:20;                // 19:0 Clock Source 1 counter attached Value
    Uint32 rsvd1:12;                     // 31:20 Reserved
};

union DCCOMPCLKSRCCNT1_REG {
    Uint32  all;
    struct  DCCOMPCLKSRCCNT1_BITS  bit;
};

struct DCCOMPCLKSRCSEL1_BITS {          // bits description
    Uint32 CLKSRCSEL1:4;                 // 3:0 Counter 1 Clock Source Select
    Uint32 rsvd1:8;                      // 11:4 Reserved
    Uint32 CLKSRCWEN:4;                  // 15:12 Counter 1 Clock Source Write Enable
    Uint32 rsvd2:16;                     // 31:16 Reserved
};

union DCCOMPCLKSRCSEL1_REG {
    Uint32  all;
    struct  DCCOMPCLKSRCSEL1_BITS  bit;
};

struct DCCOMPCLKSRCSEL0_BITS {          // bits description
    Uint32 CLKSRCSEL0:4;                 // 3:0 Counter 0 Clock Source Select
    Uint32 rsvd1:12;                     // 15:4 Reserved
    Uint32 rsvd2:16;                     // 31:16 Reserved
};

union DCCOMPCLKSRCSEL0_REG {
    Uint32  all;
    struct  DCCOMPCLKSRCSEL0_BITS  bit;
};

struct DCCOMP_REGS {
    union   DCCOMPCTRL_REG                      DCCOMPCTRL;                     // Global Control Register
    Uint32                                      rsvd1;
    union   DCCOMPREV_REG                       DCCOMPREV;                      // DCCOMP Revision Register
    Uint32                                      rsvd2;
    union   DCCOMPCNTSEED0_REG                  DCCOMPCNTSEED0;                 // Counter 0 Seed Value
    Uint32                                      rsvd3;
    union   DCCOMPVALSEED0_REG                  DCCOMPVALSEED0;                 // Valid 0 Seed Value
    Uint32                                      rsvd4;
    union   DCCOMPCNTSEED1_REG                  DCCOMPCNTSEED1;                 // Counter 1 Seed Value
    Uint32                                      rsvd5;
    union   DCCOMPFLG_REG                       DCCOMPFLG;                      // DCCOMP Status
    Uint32                                      rsvd6;
    union   DCCOMPCLKSRCCNT0_REG                DCCOMPCLKSRCCNT0;               // Counter 0 Value
    Uint32                                      rsvd7;
    union   DCCOMPCLKSRCVAL0_REG                DCCOMPCLKSRCVAL0;               // Valid Value 0
    Uint32                                      rsvd8;
    union   DCCOMPCLKSRCCNT1_REG                DCCOMPCLKSRCCNT1;               // Counter 1 Value
    Uint32                                      rsvd9;
    union   DCCOMPCLKSRCSEL1_REG                DCCOMPCLKSRCSEL1;               // Clock Source 1
    Uint32                                      rsvd10;
    union   DCCOMPCLKSRCSEL0_REG                DCCOMPCLKSRCSEL0;               // Clock Source 0
};

//---------------------------------------------------------------------------
// DCCOMP External References & Function Declarations:
//
extern volatile struct DCCOMP_REGS Dccomp0Regs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
