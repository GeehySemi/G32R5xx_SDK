//###########################################################################
//
// FILE:    g32r502_as.h
//
// TITLE:   Definitions for the ANALOGSUBSYS registers.
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

#ifndef G32R502_AS_H
#define G32R502_AS_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// ANALOGSUBSYS Individual Register Bit Definitions:

struct CONFIGLOCK_BITS {                // bits description
    Uint16 rsvd1        : 3;
    Uint16 AGPIOCTRL    : 1;            // [3..3] Locks all AGPIOCTRL Register
    Uint16 rsvd2        : 12;
};

union CONFIGLOCK_REG {
    Uint16  all;
    struct  CONFIGLOCK_BITS  bit;
};

struct TSNSCTL_BITS {                   // bits description
    Uint16 ENABLE       : 1;            // [0..0] Temperature Sensor Enable
    Uint16 rsvd1        : 15;
};

union TSNSCTL_REG {
    Uint16  all;
    struct  TSNSCTL_BITS  bit;
};

struct ANAREFCTL_BITS {                 // bits description
    Uint16 ANAREFASEL    : 2;           // [1..0] Analog reference A mode select
    Uint16 ANAREFCSEL    : 1;           // [2..2] Analog reference C mode select
    Uint16 rsvd1         : 5;           // [7..3] Reserved
    Uint16 ANAREFA2P5SEL : 2;           // [9..8] Analog reference A 2.5V select
    Uint16 ANAREFC2P5SEL : 1;           // [10..10] Analog reference C 2.5V select
    Uint16 rsvd2         : 5;           // [15..11] Reserved
};

union ANAREFCTL_REG {
    Uint16  all;
    struct  ANAREFCTL_BITS  bit;
};

struct VMONCTL_BITS {                   // bits description
    Uint16 rsvd1      : 8;
    Uint16 BORLDIS    : 1;              // [8..8] BORL disable on VDDIO
    Uint16 rsvd2      : 7;
};

union VMONCTL_REG {
    Uint16  all;
    struct  VMONCTL_BITS  bit;
};

struct CMPHPMXSEL_BITS {                 // bits description
    Uint32 CMP1HPMXSEL : 3;              // [2..0] Select source on the COMP1_HP input
    Uint32 CMP2HPMXSEL : 3;              // [5..3] Select source on the COMP2_HP input
    Uint32 CMP3HPMXSEL : 3;              // [8..6] Select source on the COMP3_HP input
    Uint32 CMP4HPMXSEL : 3;              // [11..9] Select source on the COMP4_HP input
    Uint32 rsvd1       : 20;
};

union CMPHPMXSEL_REG {
    Uint32  all;
    struct  CMPHPMXSEL_BITS  bit;
};

struct CMPLPMXSEL_BITS {                 // bits description
    Uint32 CMP1LPMXSEL : 3;              // [2..0] Select source on the COMP1_LP input
    Uint32 CMP2LPMXSEL : 3;              // [5..3] Select source on the COMP2_LP input
    Uint32 CMP3LPMXSEL : 3;              // [8..6] Select source on the COMP3_LP input
    Uint32 CMP4LPMXSEL : 3;              // [11..9] Select source on the COMP4_LP input
    Uint32 rsvd1       : 20;
};

union CMPLPMXSEL_REG {
    Uint32  all;
    struct  CMPLPMXSEL_BITS  bit;
};

struct CMPHNMXSEL_BITS {                // bits description
    Uint16 CMP1HNMXSEL : 1;              // [0..0] Select source on the COMP1_HN input
    Uint16 CMP2HNMXSEL : 1;              // [1..1] Select source on the COMP2_HN input
    Uint16 CMP3HNMXSEL : 1;              // [2..2] Select source on the COMP3_HN input
    Uint16 CMP4HNMXSEL : 1;              // [3..3] Select source on the COMP4_HN input
    Uint16 rsvd1       : 12;
};

union CMPHNMXSEL_REG {
    Uint16  all;
    struct  CMPHNMXSEL_BITS  bit;
};

struct CMPLNMXSEL_BITS {                // bits description
    Uint16 CMP1LNMXSEL : 1;              // [0..0] Select source on the COMP1_LN input
    Uint16 CMP2LNMXSEL : 1;              // [1..1] Select source on the COMP2_LN input
    Uint16 CMP3LNMXSEL : 1;              // [2..2] Select source on the COMP3_LN input
    Uint16 CMP4LNMXSEL : 1;              // [3..3] Select source on the COMP4_LN input
    Uint16 rsvd1       : 12;
};

union CMPLNMXSEL_REG {
    Uint16  all;
    struct  CMPLNMXSEL_BITS  bit;
};

struct ADCDACLOOPBACK_BITS {             // bits description
    Uint32 ENLB2ADCA : 1;                //[0..0] Loopback COMPDACA output to ADCA
    Uint32 rsvd1     : 1;
    Uint32 ENLB2ADCC : 1;                //[2..2] Loopback COMPDACA output to ADCC
    Uint32 rsvd2     : 13;
    Uint32 KEY       : 16;               // 31:16 Key
};

union ADCDACLOOPBACK_REG {
    Uint32 all;
    struct ADCDACLOOPBACK_BITS  bit;
};

struct LOCK_BITS {                     // bits description
    Uint32 TSNSCTL    : 1;             // [0..0] AS_TSNSCTL Register Lock
    Uint32 ANAREFCTL  : 1;             // [1..1] ANAREFCTL Register Lock
    Uint32 VMONCTL    : 1;             // [2..2] AS_VMONCTL Register Lock
    Uint32 rsvd1      : 2;
    Uint32 CMPHPMXSEL : 1;             // [5..5] AS_CMPHPMXSEL Register Lock
    Uint32 CMPLPMXSEL : 1;             // [6..6] AS_CMPLPMXSEL Register Lock
    Uint32 CMPHNMXSEL : 1;             // [7..7] AS_CMPHNMXSEL Register Lock
    Uint32 CMPLNMXSEL : 1;             // [8..8] AS_CMPLNMXSEL Register Lock
    Uint32 rsvd2      : 7;
    Uint32 rsvd3      :16;
};

union LOCK_REG {
    Uint32  all;
    struct  LOCK_BITS  bit;
};

struct AGPIOCTRLA_BITS {
    Uint32 rsvd0     : 12;              // [0..11] Reserved
    Uint32 GPIO12    : 1;               // [12] Enable AGPIO function for GPIO12
    Uint32 GPIO13    : 1;               // [13] Enable AGPIO function for GPIO13
    Uint32 rsvd1     : 6;               // [14..19] Reserved
    Uint32 GPIO20    : 1;               // [20] Enable AGPIO function for GPIO20
    Uint32 GPIO21    : 1;               // [21] Enable AGPIO function for GPIO21
    Uint32 rsvd2     : 6;               // [22..27] Reserved
    Uint32 GPIO28    : 1;               // [28] Enable AGPIO function for GPIO28
    Uint32 rsvd3     : 3;               // [29..31] Reserved
};

union AGPIOCTRLA_REG {
    Uint32                all;
    struct AGPIOCTRLA_BITS bit;
};

struct AGPIOCTRLH_BITS {
    Uint32 GPIO224 : 1;                 // [0] Enable AGPIO function for GPIO224
    Uint32 rsvd0   : 1;                 // [1] Reserved
    Uint32 GPIO226 : 1;                 // [2] Enable AGPIO function for GPIO226
    Uint32 GPIO227 : 1;                 // [3] Enable AGPIO function for GPIO227
    Uint32 GPIO228 : 1;                 // [4] Enable AGPIO function for GPIO228
    Uint32 rsvd1   : 1;                 // [5] Reserved
    Uint32 GPIO230 : 1;                 // [6] Enable AGPIO function for GPIO230
    Uint32 rsvd2   : 11;                // [7..17] Reserved
    Uint32 GPIO242 : 1;                 // [18] Enable AGPIO function for GPIO242
    Uint32 rsvd3   : 13;                // [19..31] Reserved
};

union AGPIOCTRLH_REG {
    Uint32                all;
    struct AGPIOCTRLH_BITS bit;
};

struct AS_REGS {
    Uint16                                   rsvd1[94];                // Reserved
    union   CONFIGLOCK_REG                   CONFIGLOCK;               // Lock Register for all the config registers.
    Uint16                                   rsvd2;                    // Reserved
    union   TSNSCTL_REG                      TSNSCTL;                  // Temperature Sensor Control Register
    Uint16                                   rsvd3[7];                 // Reserved
    union   ANAREFCTL_REG                    ANAREFCTL;                // Analog Reference Control Register
    Uint16                                   rsvd4[7];                 // Reserved
    union   VMONCTL_REG                      VMONCTL;                  // Voltage Monitor Control Register
    Uint16                                   rsvd5[17];                // Reserved
    union   CMPHPMXSEL_REG                   CMPHPMXSEL;               // Bits to select one of the many sources on CopmHP inputs. Refer to Pimux diagram for details.
    union   CMPLPMXSEL_REG                   CMPLPMXSEL;               // Bits to select one of the many sources on CopmLP inputs. Refer to Pimux diagram for details.
    union   CMPHNMXSEL_REG                   CMPHNMXSEL;               // Bits to select one of the many sources on CopmHN inputs. Refer to Pimux diagram for details.
    union   CMPLNMXSEL_REG                   CMPLNMXSEL;               // Bits to select one of the many sources on CopmLN inputs. Refer to Pimux diagram for details.
    union   ADCDACLOOPBACK_REG               ADCDACLOOPBACK;           // Enabble loopback from DAC to ADCs
    Uint16                                   rsvd6[4];                 // Reserved
    union   LOCK_REG                         LOCK;                     // Lock Register
    Uint16                                   rsvd7[122];               // Reserved
    union   AGPIOCTRLA_REG                   AGPIOCTRLA;               // Analog GPIO Control Register A
    Uint16                                   rsvd8[12];                // Reserved
    union   AGPIOCTRLH_REG                   AGPIOCTRLH;               // Analog GPIO Control Register H
};

//---------------------------------------------------------------------------
// ANALOGSUBSYS External References & Function Declarations:
//
extern volatile struct AS_REGS ASRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
