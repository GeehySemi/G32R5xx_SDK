//###########################################################################
//
// FILE:    g32r502_i2c.h
//
// TITLE:   Definitions for the I2C registers.
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

#ifndef G32R502_I2C_H
#define G32R502_I2C_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// I2C Individual Register Bit Definitions:

struct I2COADDR_BITS {                    // bits description
    Uint16 OADDR:10;                    // 9:0 I2C Own address
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union I2COADDR_REG {
    Uint16  all;
    struct  I2COADDR_BITS  bit;
};

struct I2CIREN_BITS {                    // bits description
    Uint16 ARBLIREN   : 1;               // [0..0] Arbitration lost interrupt request enable
    Uint16 NACKIREN   : 1;               // [1..1] No acknowledgment interrupt request enable
    Uint16 RAIREN     : 1;               // [2..2] Register access ready interrupt request enable
    Uint16 RXDIREN    : 1;               // [3..3] Receive data ready interrupt request enable
    Uint16 TXDIREN    : 1;               // [4..4] Transmit data ready interrupt request enable
    Uint16 STODIREN   : 1;               // [5..5] Stop condition detected interrupt request enable
    Uint16 SAIREN     : 1;               // [6..6] slave Addressed interrupt request enable
    Uint16 rsvd1:9;                      // 15:7 Reserved
};

union I2CIREN_REG {
    Uint16  all;
    struct  I2CIREN_BITS  bit;
};

struct I2CSTS_BITS {                    // bits description
    Uint16 ARBLIFLG   : 1;            // [0..0] Arbitration lost interrupt flag
    Uint16 NACKIFLG   : 1;            // [1..1] No acknowledgment interrupt flag
    Uint16 RAIFLG     : 1;            // [2..2] Register access ready interrupt flag
    Uint16 RXDIFLG    : 1;            // [3..3] Receive data ready interrupt flag
    Uint16 TXDIFLG    : 1;            // [4..4] Transmit data ready interrupt flag
    Uint16 STODIFLG   : 1;            // [5..5] Stop condition detected interrupt flag
    Uint16 BTXCFLG    : 1;            // [6..6] Byte Transmit Complete flag
    Uint16 rsvd1      : 1;
    Uint16 ZEROAFLG   : 1;            // [8..8] all zeros address flag
    Uint16 SAFLG      : 1;            // [9..9] slave Addressed Flag
    Uint16 TXSNEFLG   : 1;            // [10..10] Transmit shift register not empty Flag
    Uint16 RXSFFLG    : 1;            // [11..11] Receive shift register full Flag
    Uint16 BBSYFLG    : 1;            // [12..12] Bus busy Flag
    Uint16 TXNACKFLG  : 1;            // [13..13] Transmit No acknowledgment flag
    Uint16 SFLG       : 1;            // [14..14] Slave Flag
    Uint16 rsvd2      : 1;
};

union I2CSTS_REG {
    Uint16  all;
    struct  I2CSTS_BITS  bit;
};

struct I2CRXD_BITS {                    // bits description
    Uint16 RXD:8;                       // 7:0 Receive data
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union I2CRXD_REG {
    Uint16  all;
    struct  I2CRXD_BITS  bit;
};

struct I2CSADDR_BITS {                    // bits description
    Uint16 SADDR:10;                      // 9:0 slave address Set
    Uint16 rsvd1:6;                       // 15:10 Reserved
};

union I2CSADDR_REG {
    Uint16  all;
    struct  I2CSADDR_BITS  bit;
};

struct I2CTXD_BITS {                    // bits description
    Uint16 TXD:8;                       // 7:0 Transmit data
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union I2CTXD_REG {
    Uint16  all;
    struct  I2CTXD_BITS  bit;
};

struct I2CCTRL_BITS {                    // bits description
    Uint16 DBSEL      : 3;            // [2..0] data byte select
    Uint16 FDFEN      : 1;            // [3..3] Free data format mode enable
    Uint16 STABEN     : 1;            // [4..4] Start byte mode enable
    Uint16 I2CEN      : 1;            // [5..5] I2C enable
    Uint16 DLBEN      : 1;            // [6..6] Digital loopback mode enable
    Uint16 REEN       : 1;            // [7..7] Repeat mode enable
    Uint16 ADDRLEN    : 1;            // [8..8] Address Length Configure
    Uint16 RXTXCFG    : 1;            // [9..9] Receive Transmit mode Configure
    Uint16 MSCFG      : 1;            // [10..10] Master Slave mode configure
    Uint16 STOGEN     : 1;            // [11..11] stop condition Generating
    Uint16 rsvd1      : 1;            // [12..12] Reserved
    Uint16 STAGEN     : 1;            // [13..13] start condition Generating
    Uint16 FREEEN     : 1;            // [14..14] I2C Free Run Enable
    Uint16 NACKCFG    : 1;            // [15..15] NACK mode Configure
};

union I2CCTRL_REG {
    Uint16  all;
    struct  I2CCTRL_BITS  bit;
};

struct I2CISRC_BITS {                   // bits description
    Uint16 IFLG:3;                      // 2:0 Interrupt Flag
    Uint16 rsvd1:5;                     // 7:3 Reserved
    Uint16 INTEST:4;                    // 11:8 internal testing
    Uint16 rsvd2:4;                     // 15:12 Reserved
};

union I2CISRC_REG {
    Uint16  all;
    struct  I2CISRC_BITS  bit;
};

struct I2CEXT_BITS {                    // bits description
    Uint16 BWCCFG     : 1;            // [0..0] Backwards compatibility mode Configure
    Uint16 FWCCFG     : 1;            // [1..1] Forward Compatibility mode Configure
    Uint16 rsvd1:14;                  // 15:2 Reserved
};

union I2CEXT_REG {
    Uint16  all;
    struct  I2CEXT_BITS  bit;
};

struct I2CPSC_BITS {                    // bits description
    Uint16 PSC        : 8;              // [7..0] prescaler value
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union I2CPSC_REG {
    Uint16  all;
    struct  I2CPSC_BITS  bit;
};

struct I2CTXFIFO_BITS {                   // bits description
    Uint16 TXFFILEVEL : 5;            // [4..0] Transmit FIFO interrupt level Set
    Uint16 TXFFIEN    : 1;            // [5..5] Transmit FIFO Interrupt Enable
    Uint16 TXFFICLR   : 1;            // [6..6] Transmit FIFO Interrupt Flag Clear
    Uint16 TXFFIFLG   : 1;            // [7..7] Transmit FIFO interrupt flag
    Uint16 TXFFSTS    : 5;            // [12..8] transmit FIFO status
    Uint16 TXFFEN     : 1;            // [13..13] transmit FIFO enable
    Uint16 I2CFFEN    : 1;            // [14..14] I2C FIFO enable
    Uint16 rsvd       :1;
};

union I2CTXFIFO_REG {
    Uint16  all;
    struct  I2CTXFIFO_BITS  bit;
};

struct I2CRXFIFO_BITS {                   // bits description
    Uint16 RXFFILEVEL : 5;            // [4..0] Receive FIFO interrupt level Set
    Uint16 RXFFIEN    : 1;            // [5..5] Receive FIFO Interrupt Enable
    Uint16 RXFFICLR   : 1;            // [6..6] Receive FIFO Interrupt Flag Clear
    Uint16 RXFFIFLG   : 1;            // [7..7] Receive FIFO interrupt flag
    Uint16 RXFFSTS    : 5;            // [12..8] Receive FIFO status
    Uint16 RXFFEN     : 1;            // [13..13] Receive FIFO enable
    Uint16 rsvd       :2;
};

union I2CRXFIFO_REG {
    Uint16  all;
    struct  I2CRXFIFO_BITS  bit;
};

struct I2C_REGS {
    union   I2COADDR_REG                      I2COADDR;                     // I2C Own address
    union   I2CIREN_REG                       I2CIREN;                      // I2C Interrupt Enable
    union   I2CSTS_REG                        I2CSTS;                       // I2C Status
    Uint16                                    I2CCLKL;                      // I2C Clock low-time divider
    Uint16                                    I2CCLKH;                      // I2C Clock high-time divider
    Uint16                                    I2CCNT;                       // I2C Data count
    union   I2CRXD_REG                        I2CRXD;                       // I2C Data receive
    union   I2CSADDR_REG                      I2CSADDR;                     // I2C Slave address
    union   I2CTXD_REG                        I2CTXD;                       // I2C Data Transmit
    union   I2CCTRL_REG                       I2CCTRL;                      // I2C Mode
    union   I2CISRC_REG                       I2CISRC;                      // I2C Interrupt Source
    union   I2CEXT_REG                        I2CEXT;                       // I2C Extended Mode
    union   I2CPSC_REG                        I2CPSC;                       // I2C Prescaler
    Uint16                                    rsvd1[19];                    // Reserved
    union   I2CTXFIFO_REG                     I2CTXFIFO;                    // I2C FIFO Transmit
    union   I2CRXFIFO_REG                     I2CRXFIFO;                    // I2C FIFO Receive
};

//---------------------------------------------------------------------------
// I2C External References & Function Declarations:
//
extern volatile struct I2C_REGS I2caRegs;
extern volatile struct I2C_REGS I2cbRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
