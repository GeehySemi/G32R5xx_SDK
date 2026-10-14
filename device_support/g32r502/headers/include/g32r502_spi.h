//###########################################################################
//
// FILE:    g32r502_spi.h
//
// TITLE:   Definitions for the SPI registers.
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

#ifndef G32R502_SPI_H
#define G32R502_SPI_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// SPI Individual Register Bit Definitions:

struct SPICFG_BITS {                    // bits description
    Uint16 CLENSEL    : 4;            // [3..0] Character Length select
    Uint16 LBEN       : 1;            // [4..4] Loopback Mode Enable
    Uint16 HSEN       : 1;            // [5..5] High Speed Mode Enable
    Uint16 POLCFG     : 1;            // [6..6] Clock Polarity Configure
    Uint16 SPIRDY     : 1;            // [7..7] SPI ready
    Uint16 rsvd       : 8;
};

union SPICFG_REG {
    Uint16  all;
    struct  SPICFG_BITS  bit;
};

struct SPICTRL_BITS {                    // bits description
    Uint16 IEN        : 1;            // [0..0] SPI Interrupt Enable
    Uint16 TXEN       : 1;            // [1..1] Transmit Enable
    Uint16 MSCFG      : 1;            // [2..2] Master Slave mode configure
    Uint16 PHASEL     : 1;            // [3..3] Clock Phase Select
    Uint16 OVRIEN     : 1;            // [4..4] Overrun Interrupt Enable
    Uint16 rsvd       : 11;
};

union SPICTRL_REG {
    Uint16  all;
    struct  SPICTRL_BITS  bit;
};

struct SPISTS_BITS {                    // bits description
    Uint16 rsvd1        :5;
    Uint16 TXBFFLG      :1;             // [5..5] Transmit Buffer Full Flag
    Uint16 IFLG         :1;             // [6..6] Interrupt Flag
    Uint16 RXOVRFLG     :1;             // [7..7] Receiver Overrun Flag
    Uint16 rsvd2        :8;
};

union SPISTS_REG {
    Uint16  all;
    struct  SPISTS_BITS  bit;
};

struct SPIBR_BITS {                    // bits description
    Uint16 BRSEL          :7;          // [6..0] Baud Rate selcet
    Uint16 rsvd           :9;
};

union SPIBR_REG {
    Uint16  all;
    struct  SPIBR_BITS  bit;
};

struct SPITXFIFO_BITS {               // bits description
    Uint16 TXFFILSEL  : 5;            // [4..0] Transmit FIFO interrupt level Selcet
    Uint16 TXFFIEN    : 1;            // [5..5] Transmit FIFO Interrupt Enable
    Uint16 TXFFICLR   : 1;            // [6..6] Transmit FIFO Interrupt Flag Clear
    Uint16 TXFFIFLG   : 1;            // [7..7] Transmit FIFO interrupt flag
    Uint16 TXFFSTS    : 5;            // [12..8] transmit FIFO status
    Uint16 TXFFEN     : 1;            // [13..13] transmit FIFO enable
    Uint16 SPIFFEEN   : 1;            // [14..14] SPI FIFO Enhancements enable
    Uint16 SPIEN      : 1;            // [15..15] SPI Enable
};

union SPITXFIFO_REG {
    Uint16  all;
    struct  SPITXFIFO_BITS  bit;
};

struct SPIRXFIFO_BITS {               // bits description
    Uint16 RXFFILSEL  : 5;            // [4..0] Receive FIFO interrupt level Selcet
    Uint16 RXFFIEN    : 1;            // [5..5] Receive FIFO Interrupt Enable
    Uint16 RXFFICLR   : 1;            // [6..6] Receive FIFO Interrupt Flag Clear
    Uint16 RXFFIFLG   : 1;            // [7..7] Receive FIFO interrupt flag
    Uint16 RXFFSTS    : 5;            // [12..8] Receive FIFO status
    Uint16 RXFFEN     : 1;            // [13..13] Receive FIFO enable
    Uint16 RXFFOVRCLR : 1;            // [14..14] Receive FIFO Overflow Flag Clear
    Uint16 RXFFOVRFLG : 1;            // [15..15] Receive FIFO Overflow Flag
};

union SPIRXFIFO_REG {
    Uint16  all;
    struct  SPIRXFIFO_BITS  bit;
};

struct SPIFFCTRL_BITS {                   // bits description
    Uint16 FFTXDLYSEL:8;                  // 7:0 FIFO Transmit Delay Bits
    Uint16 rsvd      :8;
};

union SPIFFCTRL_REG {
    Uint16  all;
    struct  SPIFFCTRL_BITS  bit;
};

struct SPIPRICTRL_BITS {                    // bits description
    Uint16 SPIMSEL    : 1;            // [0..0] SPI Mode Selcet
    Uint16 STEINV     : 1;            // [1..1] STEn Inversion
    Uint16 rsvd1      : 2;
    Uint16 EMUFREEEN  : 1;            // [4..4] Emulation Free Run Enable
    Uint16 EMUSOFT    : 1;            // [5..5] Emulation Soft Run
    Uint16 rsvd2      : 10;
};

union SPIPRICTRL_REG {
    Uint16  all;
    struct  SPIPRICTRL_BITS  bit;
};

struct SPI_REGS {
    union   SPICFG_REG                       SPICFG;                       // SPI Configuration Control Register
    union   SPICTRL_REG                      SPICTRL;                       // SPI Operation Control Register
    union   SPISTS_REG                       SPISTS;                       // SPI Status Register
    Uint16                                   rsvd1;                        // Reserved
    union   SPIBR_REG                        SPIBR;                       // SPI Baud Rate Register
    Uint16                                   rsvd2;                        // Reserved
    Uint16                                   SPIRXEMU;                     // SPI Emulation Buffer Register
    Uint16                                   SPIRXBUF;                     // SPI Serial Input Buffer Register
    Uint16                                   SPITXBUF;                     // SPI Serial Output Buffer Register
    Uint16                                   SPIDAT;                       // SPI Serial Data Register
    union   SPITXFIFO_REG                    SPITXFIFO;                      // SPI FIFO Transmit Register
    union   SPIRXFIFO_REG                    SPIRXFIFO;                      // SPI FIFO Receive Register
    union   SPIFFCTRL_REG                    SPIFFCTRL;                      // SPI FIFO Control Register
    Uint16                                   rsvd3[2];                     // Reserved
    union   SPIPRICTRL_REG                   SPIPRICTRL;                       // SPI Priority Control Register
};

//---------------------------------------------------------------------------
// SPI External References & Function Declarations:
//
extern volatile struct SPI_REGS SpiaRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
