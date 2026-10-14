//###########################################################################
//
// FILE:    g32r502_can.h
//
// TITLE:   Definitions for the CAN registers.
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

#ifndef G32R502_CAN_H
#define G32R502_CAN_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// CAN Individual Register Bit Definitions:

struct CAN_CTRL_BITS {                   // bits description
    bp_32 INIT       : 1;            // [0..0] Initialization Mode
    bp_32 IEN0       : 1;            // [1..1] Interrupt line 0 Enable
    bp_32 SCHIEN     : 1;            // [2..2] Status Change Interrupt Enable
    bp_32 ERRIEN     : 1;            // [3..3] Error Interrupt Enable
    bp_32 rsvd1      : 1;
    bp_32 DISARETX   : 1;            // [5..5] Disable Automatic ReTransmit
    bp_32 CFGWACCEN  : 1;            // [6..6] Configure write access Enable
    bp_32 TESTEN     : 1;            // [7..7] Test Mode Enable
    bp_32 IDBGSEN    : 1;            // [8..8] Interrupt Debug Support Enable
    bp_32 ABOEN      : 1;            // [9..9] Auto-Bus-On Enable
    bp_32 PEN        : 4;            // [13..10] Parity Enable
    bp_32 rsvd2      : 1;
    bp_32 SWRSTEN    : 1;            // [15..15] Software Reset Enable
    bp_32 DBGFLG     : 1;            // [16..16] Debug Mode Flag
    bp_32 IEN1       : 1;            // [17..17] Interrupt line 1 Enable
    bp_32 IFDEN1     : 1;            // [18..18] IF1 DMA request line Enable
    bp_32 IFDEN2     : 1;            // [19..19] IF2 DMA request line Enable
    bp_32 IFDEN3     : 1;            // [20..20] IF3 DMA request line Enable
    bp_32 rsvd3      : 11;
};

union CAN_CTRL_REG {
    bp_32  all;
    struct  CAN_CTRL_BITS  bit;
};

struct CAN_EFLG_BITS {                    // bits description
    bp_32 LEC        : 3;            // [2..0] Last Error Code
    bp_32 TXCFLG     : 1;            // [3..3] Transmit completion flag
    bp_32 RXCFLG     : 1;            // [4..4] Reception completion flag
    bp_32 EPFLG      : 1;            // [5..5] Error Passive Flag
    bp_32 EWFLG      : 1;            // [6..6] Error Warning Flag
    bp_32 BUSOFLG    : 1;            // [7..7] Bus-off Flag
    bp_32 PEFLG      : 1;            // [8..8] Parity Error Flag
    bp_32 rsvd1      : 23;
};

union CAN_EFLG_REG {
    bp_32  all;
    struct  CAN_EFLG_BITS  bit;
};

struct CAN_ECNT_BITS {                  // bits description
    bp_32 TXECNT     : 8;            // [7..0] Transmit Error Counter
    bp_32 RXECNT     : 7;            // [14..8] Receive Error Counter
    bp_32 RXEP       : 1;            // [15..15] Receive Error Passive
    bp_32 rsvd1      : 16;
};

union CAN_ECNT_REG {
    bp_32  all;
    struct  CAN_ECNT_BITS  bit;
};

struct CAN_BTIM_BITS {                   // bits description
    bp_32 BRPSC      : 6;            // [5..0] Baud Rate Prescaler
    bp_32 SJWP       : 2;            // [7..6] Synchronization Jump Width Valid programmed values
    bp_32 TSSPVP1    : 4;            // [11..8] Time segment 1 before the sample point Valid programmed values
    bp_32 TSSPVP2    : 3;            // [14..12] Time segment 2 before the sample point Valid programmed values
    bp_32 rsvd1      : 1;
    bp_32 BRPSCEXT   : 4;            // [19..16] Baud Rate Prescaler Extension
    bp_32 rsvd2      : 12;
};

union CAN_BTIM_REG {
    bp_32  all;
    struct  CAN_BTIM_BITS  bit;
};

struct CAN_INT_BITS {                   // bits description
    bp_32 INT0       : 16;           // [15..0] Interrupt 0
    bp_32 INT1       : 8;            // [23..16] Interrupt 1
    bp_32 rsvd1      : 8;
};

union CAN_INT_REG {
    bp_32  all;
    struct  CAN_INT_BITS  bit;
};

struct CAN_TEST_BITS {                  // bits description
    bp_32 rsvd1      : 3;
    bp_32 MUTEEN     : 1;            // [3..3] Mute Mode Enable
    bp_32 LBEN       : 1;            // [4..4] Loop Back Mode Enable
    bp_32 TXCTRL     : 2;            // [6..5] TX pin Control
    bp_32 RXMON      : 1;            // [7..7] RX pin Monitors
    bp_32 EXTLBEN    : 1;            // [8..8] External Loop Back Mode Enable
    bp_32 RDAEN      : 1;            // [9..9] RAM Direct Access Enable
    bp_32 rsvd2      : 22;
};

union CAN_TEST_REG {
    bp_32  all;
    struct  CAN_TEST_BITS  bit;
};

struct CAN_PE_BITS {                  // bits description
    bp_32 MAILNUM    : 8;            // [7..0] parity error Mailbox number
    bp_32 WORDNUM    : 3;            // [10..8] parity error Word number
    bp_32 rsvd1      : 21;
};

union CAN_PE_REG {
    bp_32  all;
    struct  CAN_PE_BITS  bit;
};

struct CAN_RAMINIT_BITS {              // bits description
    bp_32 KEY0       : 1;            // [0..0] Key 0
    bp_32 KEY1       : 1;            // [1..1] Key 1
    bp_32 KEY2       : 1;            // [2..2] Key 2
    bp_32 KEY3       : 1;            // [3..3] Key 3
    bp_32 RAMINIT    : 1;            // [4..4] Initiate CAN Mailbox RAM initialization
    bp_32 RAMINITCFLG : 1;           // [5..5] CAN Mailbox RAM initialization completion flag
    bp_32 rsvd1       : 26;
};

union CAN_RAMINIT_REG {
    bp_32  all;
    struct  CAN_RAMINIT_BITS  bit;
};

struct CAN_GLBINTEN_BITS {            // bits description
    bp_32 GLBINT0EN  : 1;            // [0..0] CANINT0 Global Interrupt Enable
    bp_32 GLBINT1EN  : 1;            // [1..1] CANINT1 Global Interrupt Enable
    bp_32 rsvd1      : 30;
};

union CAN_GLBINTEN_REG {
    bp_32  all;
    struct  CAN_GLBINTEN_BITS  bit;
};

struct CAN_GLBINTFLG_BITS {           // bits description
    bp_32 GLBINT0FLG : 1;            // [0..0] CANINT0 Global Interrupt Flag
    bp_32 GLBINT1FLG : 1;            // [1..1] CANINT1 Global Interrupt Flag
    bp_32 rsvd1      : 30;
};

union CAN_GLBINTFLG_REG {
    bp_32  all;
    struct  CAN_GLBINTFLG_BITS  bit;
};

struct CAN_GLBINTCLR_BITS {           // bits description
    bp_32 GLBINT0CLR : 1;            // [0..0] CANINT0 Global Interrupt Flag Clear
    bp_32 GLBINT1CLR : 1;            // [1..1] CANINT1 Global Interrupt Flag Clear
    bp_32 rsvd1      : 30;
};

union CAN_GLBINTCLR_REG {
    bp_32  all;
    struct  CAN_GLBINTCLR_BITS  bit;
};

struct CAN_TXREQFLG_BITS {                // bits description
    bp_32 TXREQ1FLG  : 2;            // [1..0] Transmit Request Register 1 flag
    bp_32 TXREQ2FLG  : 2;            // [3..2] Transmit Request Register 2 flag
    bp_32 rsvd1      : 28;
};

union CAN_TXREQFLG_REG {
    bp_32  all;
    struct  CAN_TXREQFLG_BITS  bit;
};

struct CAN_NDATAFLG_BITS {                // bits description
    bp_32 NDATA1FLG  : 2;            // [1..0] New Data Register 1 flag
    bp_32 NDATA2FLG  : 2;            // [3..2] New Data Register 2 flag
    bp_32 rsvd1      : 28;
};

union CAN_NDATAFLG_REG {
    bp_32  all;
    struct  CAN_NDATAFLG_BITS  bit;
};

struct CAN_IPENDFLG_BITS {                // bits description
    bp_32 IPEND1FLG  : 2;            // [1..0] Interrupt Pending Register 1 flag
    bp_32 IPEND2FLG  : 2;            // [3..2] Interrupt Pending Register 2 flag
    bp_32 rsvd1      : 28;
};

union CAN_IPENDFLG_REG {
    bp_32  all;
    struct  CAN_IPENDFLG_BITS  bit;
};

struct CAN_MVALFLG_BITS {                // bits description
    bp_32 MVAL1FLG   : 2;            // [1..0] Message Valid Register 1 flag
    bp_32 MVAL2FLG   : 2;            // [3..2] Message Valid Register 2 flag
    bp_32 rsvd1      : 28;
};

union CAN_MVALFLG_REG {
    bp_32  all;
    struct  CAN_MVALFLG_BITS  bit;
};

struct CAN_IF1COM_BITS {                // bits description
    bp_32 VALMNUM    : 8;            // [7..0] Valid Mailbox Number
    bp_32 rsvd1      : 6;
    bp_32 REQDMAIF1  : 1;            // [14..14] Request DMA after IF1 update
    bp_32 BUSYFLG    : 1;            // [15..15] Busy Flag
    bp_32 DATABYTEB  : 1;            // [16..16] Access Data Bytes 4-7
    bp_32 DATABYTEA  : 1;            // [17..17] Access Data Bytes 0-3
    bp_32 TXREQCFG   : 1;            // [18..18] Transmit Request/ New Data Configure
    bp_32 IPENDCLR   : 1;            // [19..19] Interrupt Pending Clear
    bp_32 ACCCTRL    : 1;            // [20..20] Access control
    bp_32 ACCARB     : 1;            // [21..21] Access Arbitration
    bp_32 ACCMASK    : 1;            // [22..22] Access Mask
    bp_32 RWCFG      : 1;            // [23..23] Read/Write function Configure
    bp_32 rsvd2      : 8;
};

union CAN_IF1COM_REG {
    bp_32  all;
    struct  CAN_IF1COM_BITS  bit;
};

struct CAN_IF1MASK_BITS {                // bits description
    bp_32 IDMASK     : 29;           // [28..0] Identifier Mask
    bp_32 rsvd1      : 1;
    bp_32 DIRMASK    : 1;            // [30..30] Message Direction Mask
    bp_32 EXTMASK    : 1;            // [31..31] Extended Identifier Mask
};

union CAN_IF1MASK_REG {
    bp_32  all;
    struct  CAN_IF1MASK_BITS  bit;
};

struct CAN_IF1ARB_BITS {                // bits description
    bp_32 MIDCFG     : 29;           // [28..0] Message Identifier Configure
    bp_32 MDIRCFG    : 1;            // [29..29] Message Direction Configure
    bp_32 EXTIDCFG   : 1;            // [30..30] Extended Identifier Configure
    bp_32 MAILEN     : 1;            // [31..31] mailbox enable
};

union CAN_IF1ARB_REG {
    bp_32  all;
    struct  CAN_IF1ARB_BITS  bit;
};

struct CAN_IF1MCTRL_BITS {               // bits description
    bp_32 DLCCFG     : 4;            // [3..0] Data Length Code Configure
    bp_32 rsvd1      : 3;
    bp_32 EOBEN      : 1;            // [7..7] End of Block Enable
    bp_32 TXREQEN    : 1;            // [8..8] Transmit Request Enable
    bp_32 REMEN      : 1;            // [9..9] Remote Enable
    bp_32 RXIEN      : 1;            // [10..10] Receive Interrupt Enable
    bp_32 TXIEN      : 1;            // [11..11] Transmit Interrupt Enable
    bp_32 MASKEN     : 1;            // [12..12] Mask Enable
    bp_32 IPEND      : 1;            // [13..13] Interrupt Pending
    bp_32 MLOST      : 1;            // [14..14] Message Lost
    bp_32 NDATA      : 1;            // [15..15] New Data
    bp_32 rsvd2      : 16;
};

union CAN_IF1MCTRL_REG {
    bp_32  all;
    struct  CAN_IF1MCTRL_BITS  bit;
};

struct CAN_IF1DATAA_BITS {               // bits description
    bp_32 DATD0      : 8;            // [7..0] Data Byte 0
    bp_32 DATD1      : 8;            // [15..8] Data Byte 1
    bp_32 DATD2      : 8;            // [23..16] Data Byte 2
    bp_32 DATD3      : 8;            // [31..24] Data Byte 3
};

union CAN_IF1DATAA_REG {
    bp_32  all;
    struct  CAN_IF1DATAA_BITS  bit;
};

struct CAN_IF1DATAB_BITS {               // bits description
    bp_32 DATD4      : 8;            // [7..0] Data Byte 4
    bp_32 DATD5      : 8;            // [15..8] Data Byte 5
    bp_32 DATD6      : 8;            // [23..16] Data Byte 6
    bp_32 DATD7      : 8;            // [31..24] Data Byte 7
};

union CAN_IF1DATAB_REG {
    bp_32  all;
    struct  CAN_IF1DATAB_BITS  bit;
};

struct CAN_IF2COM_BITS {                // bits description
    bp_32 VALMNUM    : 8;            // [7..0] Valid Mailbox Number
    bp_32 rsvd1      : 6;
    bp_32 REQDMAIF2  : 1;            // [14..14] Request DMA after IF2 update
    bp_32 BUSYFLG    : 1;            // [15..15] Busy Flag
    bp_32 DATABYTEB  : 1;            // [16..16] Access Data Bytes 4-7
    bp_32 DATABYTEA  : 1;            // [17..17] Access Data Bytes 0-3
    bp_32 TXREQCFG   : 1;            // [18..18] Transmit Request/ New Data Configure
    bp_32 IPENDCLR   : 1;            // [19..19] Interrupt Pending Clear
    bp_32 ACCCTRL    : 1;            // [20..20] Access control
    bp_32 ACCARB     : 1;            // [21..21] Access Arbitration
    bp_32 ACCMASK    : 1;            // [22..22] Access Mask
    bp_32 RWCFG      : 1;            // [23..23] Read/Write function Configure
    bp_32 rsvd2      : 8;
};

union CAN_IF2COM_REG {
    bp_32  all;
    struct  CAN_IF2COM_BITS  bit;
};

struct CAN_IF2MASK_BITS {                // bits description
    bp_32 IDMASK     : 29;           // [28..0] Identifier Mask
    bp_32 rsvd1      : 1;
    bp_32 DIRMASK    : 1;            // [30..30] Message Direction Mask
    bp_32 EXTMASK    : 1;            // [31..31] Extended Identifier Mask
};

union CAN_IF2MASK_REG {
    bp_32  all;
    struct  CAN_IF2MASK_BITS  bit;
};

struct CAN_IF2ARB_BITS {                // bits description
    bp_32 MIDCFG     : 29;           // [28..0] Message Identifier Configure
    bp_32 MDIRCFG    : 1;            // [29..29] Message Direction Configure
    bp_32 EXTIDCFG   : 1;            // [30..30] Extended Identifier Configure
    bp_32 MAILEN     : 1;            // [31..31] mailbox enable
};

union CAN_IF2ARB_REG {
    bp_32  all;
    struct  CAN_IF2ARB_BITS  bit;
};

struct CAN_IF2MCTRL_BITS {               // bits description
    bp_32 DLCCFG     : 4;            // [3..0] Data Length Code Configure
    bp_32 rsvd1      : 3;
    bp_32 EOBEN      : 1;            // [7..7] End of Block Enable
    bp_32 TXREQEN    : 1;            // [8..8] Transmit Request Enable
    bp_32 REMEN      : 1;            // [9..9] Remote Enable
    bp_32 RXIEN      : 1;            // [10..10] Receive Interrupt Enable
    bp_32 TXIEN      : 1;            // [11..11] Transmit Interrupt Enable
    bp_32 MASKEN     : 1;            // [12..12] Mask Enable
    bp_32 IPEND      : 1;            // [13..13] Interrupt Pending
    bp_32 MLOST      : 1;            // [14..14] Message Lost
    bp_32 NDATA      : 1;            // [15..15] New Data
    bp_32 rsvd2      : 16;
};

union CAN_IF2MCTRL_REG {
    bp_32  all;
    struct  CAN_IF2MCTRL_BITS  bit;
};

struct CAN_IF2DATAA_BITS {               // bits description
    bp_32 DATD0      : 8;            // [7..0] Data Byte 0
    bp_32 DATD1      : 8;            // [15..8] Data Byte 1
    bp_32 DATD2      : 8;            // [23..16] Data Byte 2
    bp_32 DATD3      : 8;            // [31..24] Data Byte 3
};

union CAN_IF2DATAA_REG {
    bp_32  all;
    struct  CAN_IF2DATAA_BITS  bit;
};

struct CAN_IF2DATAB_BITS {               // bits description
    bp_32 DATD4      : 8;            // [7..0] Data Byte 4
    bp_32 DATD5      : 8;            // [15..8] Data Byte 5
    bp_32 DATD6      : 8;            // [23..16] Data Byte 6
    bp_32 DATD7      : 8;            // [31..24] Data Byte 7
};

union CAN_IF2DATAB_REG {
    bp_32  all;
    struct  CAN_IF2DATAB_BITS  bit;
};

struct CAN_IF3OBS_BITS {                // bits description
    bp_32 MASKRD     : 1;            // [0..0] Mask data read
    bp_32 ARBRD      : 1;            // [1..1] Arbitration data read
    bp_32 CTRLRD     : 1;            // [2..2] Control bits read
    bp_32 DATAARD    : 1;            // [3..3] Data A read
    bp_32 DATABRD    : 1;            // [4..4] Data B read
    bp_32 rsvd1      : 3;
    bp_32 MASKRDACC  : 1;            // [8..8] Mask data read access status
    bp_32 ARBRDACC   : 1;            // [9..9] Arbitration data read access status
    bp_32 CTRLRDACC  : 1;            // [10..10] Control bits read access status
    bp_32 DATAARDACC : 1;            // [11..11] Data A read access status
    bp_32 DATABRDACC : 1;            // [12..12] Data B read access status
    bp_32 rsvd2      : 2;
    bp_32 UDDATA     : 1;            // [15..15] Update Data
    bp_32 rsvd3      : 16;
};

union CAN_IF3OBS_REG {
    bp_32  all;
    struct  CAN_IF3OBS_BITS  bit;
};

struct CAN_IF3MASK_BITS {                // bits description
    bp_32 IDMASK     : 29;           // [28..0] Identifier Mask
    bp_32 rsvd1      : 1;
    bp_32 DIRMASK    : 1;            // [30..30] Message Direction Mask
    bp_32 EXTMASK    : 1;            // [31..31] Extended Identifier Mask
};

union CAN_IF3MASK_REG {
    bp_32  all;
    struct  CAN_IF3MASK_BITS  bit;
};

struct CAN_IF3ARB_BITS {                // bits description
    bp_32 MIDCFG     : 29;           // [28..0] Message Identifier Configure
    bp_32 MDIRCFG    : 1;            // [29..29] Message Direction Configure
    bp_32 EXTIDCFG   : 1;            // [30..30] Extended Identifier Configure
    bp_32 MAILEN     : 1;            // [31..31] mailbox enable
};

union CAN_IF3ARB_REG {
    bp_32  all;
    struct  CAN_IF3ARB_BITS  bit;
};

struct CAN_IF3MCTRL_BITS {               // bits description
    bp_32 DLCCFG     : 4;            // [3..0] Data Length Code Configure
    bp_32 rsvd1      : 3;
    bp_32 EOBEN      : 1;            // [7..7] End of Block Enable
    bp_32 TXREQEN    : 1;            // [8..8] Transmit Request Enable
    bp_32 REMEN      : 1;            // [9..9] Remote Enable
    bp_32 RXIEN      : 1;            // [10..10] Receive Interrupt Enable
    bp_32 TXIEN      : 1;            // [11..11] Transmit Interrupt Enable
    bp_32 MASKEN     : 1;            // [12..12] Mask Enable
    bp_32 IPEND      : 1;            // [13..13] Interrupt Pending
    bp_32 MLOST      : 1;            // [14..14] Message Lost
    bp_32 NDATA      : 1;            // [15..15] New Data
    bp_32 rsvd2      : 16;
};

union CAN_IF3MCTRL_REG {
    bp_32  all;
    struct  CAN_IF3MCTRL_BITS  bit;
};

struct CAN_IF3DATAA_BITS {               // bits description
    bp_32 DATD0      : 8;            // [7..0] Data Byte 0
    bp_32 DATD1      : 8;            // [15..8] Data Byte 1
    bp_32 DATD2      : 8;            // [23..16] Data Byte 2
    bp_32 DATD3      : 8;            // [31..24] Data Byte 3
};

union CAN_IF3DATAA_REG {
    bp_32  all;
    struct  CAN_IF3DATAA_BITS  bit;
};

struct CAN_IF3DATAB_BITS {               // bits description
    bp_32 DATD4      : 8;            // [7..0] Data Byte 4
    bp_32 DATD5      : 8;            // [15..8] Data Byte 5
    bp_32 DATD6      : 8;            // [23..16] Data Byte 6
    bp_32 DATD7      : 8;            // [31..24] Data Byte 7
};

union CAN_IF3DATAB_REG {
    bp_32  all;
    struct  CAN_IF3DATAB_BITS  bit;
};

struct CAN_REGS {
    union   CAN_CTRL_REG                     CAN_CTRL;             // Control Register
    union   CAN_EFLG_REG                     CAN_EFLG;             // Error and Flag Register
    union   CAN_ECNT_REG                     CAN_ECNT;             // Error Counter Register
    union   CAN_BTIM_REG                     CAN_BTIM;             // Bit time Register
    union   CAN_INT_REG                      CAN_INT;              // Interrupt Register
    union   CAN_TEST_REG                     CAN_TEST;             // Test Register
    uint32_t                                 rsvd1[1];             // Reserved
    union   CAN_PE_REG                       CAN_PE;               // parity error Register
    uint32_t                                 rsvd2[8];             // Reserved
    union   CAN_RAMINIT_REG                  CAN_RAMINIT;          // RAM initialize Register
    uint32_t                                 rsvd3[3];             // Reserved
    union   CAN_GLBINTEN_REG                 CAN_GLBINTEN;         // Global Interrupt Enable Register
    union   CAN_GLBINTFLG_REG                CAN_GLBINTFLG;        // Global Interrupt Flag Register
    union   CAN_GLBINTCLR_REG                CAN_GLBINTCLR;        // Global Interrupt Clear Register
    uint32_t                                 rsvd4[9];             // Reserved
    bp_32                                    CAN_ABOTMR;           // Auto-Bus-On Timer Register
    union   CAN_TXREQFLG_REG                 CAN_TXREQFLG;         // Transmit Request Flag Register
    bp_32                                    CAN_TXRQ_21;          // Transmit Request Register
    uint32_t                                 rsvd5[3];             // Reserved
    union   CAN_NDATAFLG_REG                 CAN_NDATAFLG;         // New Data Flag Register
    bp_32                                    CAN_NDAT_21;          // New Data Register
    uint32_t                                 rsvd6[3];             // Reserved
    union   CAN_IPENDFLG_REG                 CAN_IPENDFLG;         // Interrupt Pending Flag Register
    bp_32                                    CAN_IPEN_21;          // Interrupt Pending Register
    uint32_t                                 rsvd7[3];             // Reserved
    union   CAN_MVALFLG_REG                  CAN_MVALFLG;          // Message Valid Flag Register
    bp_32                                    CAN_MVAL_21;          // Message Valid Register
    uint32_t                                 rsvd8[4];             // Reserved
    bp_32                                    CAN_IP_MUX21;         // Interrupt mailbox Register
    uint32_t                                 rsvd9[9];             // Reserved
    union   CAN_IF1COM_REG                   CAN_IF1COM;           // IF1 Command Register
    union   CAN_IF1MASK_REG                  CAN_IF1MASK;          // IF1 Mask Register
    union   CAN_IF1ARB_REG                   CAN_IF1ARB;           // IF1 Arbitration Register
    union   CAN_IF1MCTRL_REG                 CAN_IF1MCTRL;         // IF1 Message Control Register
    union   CAN_IF1DATAA_REG                 CAN_IF1DATAA;         // IF1 data A Register
    union   CAN_IF1DATAB_REG                 CAN_IF1DATAB;         // IF1 data B Register
    uint32_t                                 rsvd10[2];            // Reserved
    union   CAN_IF2COM_REG                   CAN_IF2COM;           // IF2 Command Register
    union   CAN_IF2MASK_REG                  CAN_IF2MASK;          // IF2 Mask Register
    union   CAN_IF2ARB_REG                   CAN_IF2ARB;           // IF2 Arbitration Register
    union   CAN_IF2MCTRL_REG                 CAN_IF2MCTRL;         // IF2 Message Control Register
    union   CAN_IF2DATAA_REG                 CAN_IF2DATAA;         // IF2 data A Register
    union   CAN_IF2DATAB_REG                 CAN_IF2DATAB;         // IF2 data B Register
    uint32_t                                 rsvd11[4];            // Reserved
    union   CAN_IF3OBS_REG                   CAN_IF3OBS;           // IF3 Observation register
    union   CAN_IF3MASK_REG                  CAN_IF3MASK;          // IF3 Mask Register
    union   CAN_IF3ARB_REG                   CAN_IF3ARB;           // IF3 Arbitration Register
    union   CAN_IF3MCTRL_REG                 CAN_IF3MCTRL;         // IF3 Message Control Register
    union   CAN_IF3DATAA_REG                 CAN_IF3DATAA;         // IF3 data A Register
    union   CAN_IF3DATAB_REG                 CAN_IF3DATAB;         // IF3 data B Register
    uint32_t                                 rsvd12[4];            // Reserved
    bp_32                                    CAN_IF3UPD;           // IF3 Update enable Register
};

//---------------------------------------------------------------------------
// CAN External References & Function Declarations:
//
extern volatile struct CAN_REGS CanaRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
