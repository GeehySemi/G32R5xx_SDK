//###########################################################################
//
// FILE:    g32r502_lin.h
//
// TITLE:   Definitions for the LIN registers.
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

#ifndef G32R502_LIN_H
#define G32R502_LIN_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// LIN Individual Register Bit Definitions:

struct LINGCTRL0_BITS {                   // bits description
    bp_32 RST:1;                      // 0 LIN Module reset bit
    bp_32 rsvd1:15;                     // 15:1 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union LINGCTRL0_REG {
    bp_32  all;
    struct  LINGCTRL0_BITS  bit;
};

struct LINGCTRL1_BITS {                // bits description
    bp_32 COMCFG:1;                    // 0 UART/LIN communication mode Configure
    bp_32 TIM:1;                       // 1 UART timing mode
    bp_32 PARITYEN:1;                  // 2 UART/LIN Parity Enable
    bp_32 PARITY:1;                    // 3 UART Odd/Even Parity Select
    bp_32 STOPCFG:1;                   // 4 UART STOP Bit Configure
    bp_32 CLK_MSCFG:1;                 // 5 UART internal clock enable/LIN Master Slave configure
    bp_32 LINEN:1;                     // 6 LIN mode Enable
    bp_32 RDY:1;                       // 7 UART/LIN Ready
    bp_32 SLEEPEN:1;                   // 8 UART Sleep mode enable
    bp_32 ABEN:1;                      // 9 LIN Automatic baudrate adjustment enable
    bp_32 MBUFEN:1;                    // 10 UART/LIN multi-buffer mode enable
    bp_32 CHASUMCFG:1;                 // 11 LIN Checksum Configure
    bp_32 HGENCTRL:1;                  // 12 LIN HGEN control
    bp_32 STOEXTCOM:1;                 // 13 Stop LIN extended frame communication
    bp_32 rsvd1:2;                     // 15:14 Reserved
    bp_32 LBEN:1;                      // 16 UART/LIN Loopback Mode Enable
    bp_32 CONTSUS:1;                   // 17 UART/LIN Continue work on suspend
    bp_32 rsvd2:6;                     // 23:18 Reserved
    bp_32 RXEN:1;                      // 24 UART/LIN Receive enable
    bp_32 TXEN:1;                      // 25 UART/LIN Transmit enable
    bp_32 rsvd3:6;                     // 31:26 Reserved
};

union LINGCTRL1_REG {
    bp_32  all;
    struct  LINGCTRL1_BITS  bit;
};

struct LINGCTRL2_BITS {                 // bits description
    bp_32 LPREQ:1;                      // 0 low-power mode Request
    bp_32 rsvd1:7;                      // 7:1 Reserved
    bp_32 WUPGEN:1;                     // 8 Generate wakeup signal
    bp_32 rsvd2:7;                      // 15:9 Reserved
    bp_32 TXCHAEN:1;                    // 16 Transmit Checksum Byte Enable
    bp_32 COMPCHASUM:1;                 // 17 Compare Checksum
    bp_32 rsvd3:14;                     // 31:18 Reserved
};

union LINGCTRL2_REG {
    bp_32  all;
    struct  LINGCTRL2_BITS  bit;
};

struct LINIEN_BITS {                    // bits description
    bp_32 BRKDETIEN:1;                  // 0 break detect interrupt Enable
    bp_32 WUPIEN:1;                     // 1 wake up interrupt Enable
    bp_32 rsvd1:2;                      // 3:2 Reserved
    bp_32 TOIEN:1;                      // 4 timeout interrupt Enable
    bp_32 rsvd2:1;                      // 5 Reserved
    bp_32 TOWUPSIEN:1;                  // 6 Timeout After Wakeup Signal interrupt Enable
    bp_32 TO3WUPSIEN:1;                 // 7 Timeout After 3 Wakeup Signal interrupt Enable
    bp_32 TXIEN:1;                      // 8 Transmitter interrupt Enable
    bp_32 RXIEN:1;                      // 9 Receiver interrupt Enable
    bp_32 rsvd3:3;                      // 12:10 Reserved
    bp_32 IDIEN:1;                      // 13 Identification interrupt Enable
    bp_32 rsvd4:2;                      // 15:14 Reserved
    bp_32 TXDREQEN:1;                   // 16 transmit DMA request enable
    bp_32 RXDREQEN:1;                   // 17 Receive DMA request enable
    bp_32 ADRXDREQEN:1;                 // 18 Address &amp; Data frames Receive DMA request enable
    bp_32 rsvd5:5;                      // 23:19 Reserved
    bp_32 PIEN:1;                       // 24 parity interrupt Enable
    bp_32 OREIEN:1;                     // 25 overrun error interrupt Enable
    bp_32 FEIEN:1;                      // 26 framing error interrupt Enable
    bp_32 NREIEN:1;                     // 27 no response error interrupt Enable
    bp_32 ISFEIEN:1;                    // 28 inconsistent sync field error interrupt Enable
    bp_32 CSEIEN:1;                     // 29 checksum-error Interrupt Enable
    bp_32 PBEIEN:1;                     // 30 physical bus error interrupt Enable
    bp_32 BEIEN:1;                      // 31 bit error interrupt Enable
};

union LINIEN_REG {
    bp_32  all;
    struct  LINIEN_BITS  bit;
};

struct LINICLR_BITS {                  // bits description
    bp_32 BRKDETICLR:1;                // 0 break detect interrupt Clear
    bp_32 WUPICLR:1;                   // 1 wake up interrupt Clear
    bp_32 rsvd1:2;                     // 3:2 Reserved
    bp_32 TOICLR:1;                    // 4 timeout interrupt Clear
    bp_32 rsvd2:1;                     // 5 Reserved
    bp_32 TOWUPSICLR:1;                // 6 Timeout After Wakeup Signal interrupt Clear
    bp_32 TO3WUPSICLR:1;               // 7 Timeout After 3 Wakeup Signal interrupt Clear
    bp_32 TXICLR:1;                    // 8 Transmitter interrupt Clear
    bp_32 RXICLR:1;                    // 9 Receiver interrupt Clear
    bp_32 rsvd3:3;                     // 12:10 Reserved
    bp_32 IDICLR:1;                    // 13 Identification interrupt Clear
    bp_32 rsvd4:2;                     // 15:14 Reserved
    bp_32 TXDREQCLR:1;                 // 16 transmit DMA request Clear
    bp_32 RXDREQCLR:1;                 // 17 Receive DMA request Clear
    bp_32 rsvd5:1;                     // 18 Reserved
    bp_32 rsvd6:5;                     // 23:19 Reserved
    bp_32 PICLR:1;                     // 24 parity interrupt Clear
    bp_32 OREICLR:1;                   // 25 overrun error interrupt Clear
    bp_32 FEICLR:1;                    // 26 framing error interrupt Clear
    bp_32 NREICLR:1;                   // 27 no response error interrupt Clear
    bp_32 ISFEICLR:1;                  // 28 inconsistent sync field error interrupt Clear
    bp_32 CSEICLR:1;                   // 29 checksum-error Interrupt Clear
    bp_32 PBEICLR:1;                   // 30 physical bus error interrupt Clear
    bp_32 BEICLR:1;                    // 31 bit error interrupt Clear
};

union LINICLR_REG {
    bp_32  all;
    struct  LINICLR_BITS  bit;
};

struct LINILEN_BITS {                   // bits description
    bp_32 BRKDETILEN:1;                 // 0 break detect interrupt level 1 Enable
    bp_32 WUPILEN:1;                    // 1 wake up interrupt level 1 Enable
    bp_32 rsvd1:2;                      // 3:2 Reserved
    bp_32 TOILEN:1;                     // 4 timeout interrupt level 1 Enable
    bp_32 rsvd2:1;                      // 5 Reserved
    bp_32 TOWUPSILEN:1;                 // 6 Timeout After Wakeup Signal interrupt level 1 Enable
    bp_32 TO3WUPSILEN:1;                // 7 Timeout After 3 Wakeup Signal interrupt level 1 Enable
    bp_32 TXILEN:1;                     // 8 Transmitter interrupt level 1 Enable
    bp_32 RXILEN:1;                     // 9 Receiver interrupt level 1 Enable
    bp_32 rsvd3:3;                      // 12:10 Reserved
    bp_32 IDILEN:1;                     // 13 Identification interrupt level 1 Enable
    bp_32 rsvd4:2;                      // 15:14 Reserved
    bp_32 rsvd5:2;                      // 17:16 Reserved
    bp_32 rsvd6:1;                      // 18 Reserved
    bp_32 rsvd7:5;                      // 23:19 Reserved
    bp_32 PILEN:1;                      // 24 parity interrupt level 1 Enable
    bp_32 OREILEN:1;                    // 25 overrun error interrupt level 1 Enable
    bp_32 FEILEN:1;                     // 26 framing error interrupt level 1 Enable
    bp_32 NREILEN:1;                    // 27 no response error interrupt level 1 Enable
    bp_32 ISFEILEN:1;                   // 28 inconsistent sync field error interrupt level 1 Enable
    bp_32 CSEILEN:1;                    // 29 checksum-error Interrupt level 1 Enable
    bp_32 PBEILEN:1;                    // 30 physical bus error interrupt level 1 Enable
    bp_32 BEILEN:1;                     // 31 bit error interrupt level 1 Enable
};

union LINILEN_REG {
    bp_32  all;
    struct  LINILEN_BITS  bit;
};

struct LINILCLR_BITS {                  // bits description
    bp_32 BRKDETILCLR:1;                // 0 break detect interrupt level 1 Clear
    bp_32 WUPILCLR:1;                   // 1 wake up interrupt level 1 Clear
    bp_32 rsvd1:2;                      // 3:2 Reserved
    bp_32 TOILCLR:1;                    // 4  timeout interrupt level 1 Clear
    bp_32 rsvd2:1;                      // 5 Reserved
    bp_32 TOWUPSILCLR:1;                // 6 Timeout After Wakeup Signal interrupt level 1 Clear
    bp_32 TO3WUPSILCLR:1;               // 7 Timeout After 3 Wakeup Signal interrupt level 1 Clear
    bp_32 TXILCLR:1;                    // 8 Transmitter interrupt level 1 Clear
    bp_32 RXILCLR:1;                    // 9 Receiver interrupt level 1 Clear
    bp_32 rsvd3:3;                      // 12:10 Reserved
    bp_32 IDILCLR:1;                    // 13 Identification interrupt level 1 Clear
    bp_32 rsvd4:2;                      // 15:14 Reserved
    bp_32 rsvd5:2;                      // 17:16 Reserved
    bp_32 rsvd6:1;                      // 18 Reserved
    bp_32 rsvd7:5;                      // 23:19 Reserved
    bp_32 PILCLR:1;                     // 24 parity interrupt level 1 Clear
    bp_32 OREILCLR:1;                   // 25 overrun error interrupt level 1 Clear
    bp_32 FEILCLR:1;                    // 26 framing error interrupt level 1 Clear
    bp_32 NREILCLR:1;                   // 27 no response error interrupt level 1 Clear
    bp_32 ISFEILCLR:1;                  // 28 inconsistent sync field error interrupt level 1 Clear
    bp_32 CSEILCLR:1;                   // 29 checksum-error Interrupt level 1 Clear
    bp_32 PBEILCLR:1;                   // 30 physical bus error interrupt level 1 Clear
    bp_32 BEILCLR:1;                    // 31 bit error interrupt level 1 Clear
};

union LINILCLR_REG {
    bp_32  all;
    struct  LINILCLR_BITS  bit;
};

struct LINFLG_BITS {                         // bits description
    bp_32 BRKDETFLG:1;                       // 0 Break detect flag
    bp_32 WUPFLG:1;                          // 1 Wake up flag
    bp_32 RXIDLEFLG:1;                       // 2 receiver idle flag
    bp_32 BUSYFLG:1;                         // 3 Bus BUSY flag
    bp_32 LINIDLEFLG:1;                      // 4 LIN bus idle flag
    bp_32 rsvd1:1;                           // 5 Reserved
    bp_32 TOWUPSFLG:1;                       // 6 Timeout After Wakeup Signal flag
    bp_32 TO3WUPSFLG:1;                      // 7 Timeout After 3 Wakeup Signal flag
    bp_32 TXBRDYFLG:1;                       // 8 Transmitter buffer ready flag
    bp_32 RXRDYFLG:1;                        // 9 Receiver ready flag
    bp_32 TXWUPSEL:1;                        // 10 Transmitter wakeup mode select
    bp_32 TXEFLG:1;                          // 11 Transmitter Empty flag
    bp_32 RXWUPSEL:1;                        // 12 Receiver wakeup mode select
    bp_32 TXIDFLG:1;                         // 13 Transmit Identifier Flag
    bp_32 RXIDFLG:1;                         // 14 Receive Identifier Flag
    bp_32 rsvd2:1;                           // 15 Reserved
    bp_32 rsvd3:8;                           // 23:16 Reserved
    bp_32 PEFLG:1;                           // 24 Parity error flag
    bp_32 OREFLG:1;                          // 25 Overrun error flag
    bp_32 FEFLG:1;                           // 26 Framing Error Flag
    bp_32 NREFLG:1;                          // 27 No Response Error Flag
    bp_32 ISFEFLG:1;                         // 28 Inconsistent Sync Field Error Flag
    bp_32 CSEFLG:1;                          // 29 Checksum Error Flag
    bp_32 PBEFLG:1;                          // 30 Physical Bus Error Flag
    bp_32 BEFLG:1;                           // 31 Bit Error Flag
};

union LINFLG_REG {
    bp_32  all;
    struct  LINFLG_BITS  bit;
};

struct LINIVO0_BITS {                   // bits description
    bp_32 IVO0:5;                       // 4:0 INT0 Interrupt vector offset
    bp_32 rsvd1:11;                     // 15:5 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union LINIVO0_REG {
    bp_32  all;
    struct  LINIVO0_BITS  bit;
};

struct LINIVO1_BITS {                   // bits description
    bp_32 IVO1:5;                       // 4:0 INT1 Interrupt vector offset
    bp_32 rsvd1:11;                     // 15:5 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union LINIVO1_REG {
    bp_32  all;
    struct  LINIVO1_BITS  bit;
};

struct LINLCFG_BITS {                   // bits description
    bp_32 CLCFG:3;                      // 2:0 Character length Configure
    bp_32 rsvd1:13;                     // 15:3 Reserved
    bp_32 FLCFG:3;                      // 18:16 Frame length Configure
    bp_32 rsvd2:13;                     // 31:19 Reserved
};

union LINLCFG_REG {
    bp_32  all;
    struct  LINLCFG_BITS  bit;
};

struct LINBR_BITS {                           // bits description
    bp_32 PSCSELL:16;                         // 15:0 24-Bit Prescaler Select (Low Bits)
    bp_32 PSCSELH:8;                          // 23:16 24-Bit Prescaler Select (High Bits)
    bp_32 FDIVSEL:4;                          // 27:24 4 bit Fractional Divider Selcet
    bp_32 SFDIVSEL:3;                         // 30:28 Superfractional Divider Selcet
    bp_32 rsvd1:1;                            // 31 Reserved
};

union LINBR_REG {
    bp_32  all;
    struct  LINBR_BITS  bit;
};

struct LINRXED_BITS {                     // bits description
    bp_32 RXED:8;                         // 7:0 Receiver Emulation Data
    bp_32 rsvd1:8;                        // 15:8 Reserved
    bp_32 rsvd2:16;                       // 31:16 Reserved
};

union LINRXED_REG {
    bp_32  all;
    struct  LINRXED_BITS  bit;
};

struct LINRXD_BITS {                     // bits description
    bp_32 RXD:8;                         // 7:0 Received Data.
    bp_32 rsvd1:8;                       // 15:8 Reserved
    bp_32 rsvd2:16;                      // 31:16 Reserved
};

union LINRXD_REG {
    bp_32  all;
    struct  LINRXD_BITS  bit;
};

struct LINTXD_BITS {                      // bits description
    bp_32 TXD:8;                         // 7:0 Transmit data
    bp_32 rsvd1:8;                       // 15:8 Reserved
    bp_32 rsvd2:16;                      // 31:16 Reserved
};

union LINTXD_REG {
    bp_32  all;
    struct  LINTXD_BITS  bit;
};

struct LINPCTRL0_BITS {                 // bits description
    bp_32 rsvd1:1;                      // 0 Reserved
    bp_32 RXPEN:1;                      // 1 Receive pin Enable
    bp_32 TXPEN:1;                      // 2 Transmit  pin Enable
    bp_32 rsvd2:13;                     // 15:3 Reserved
    bp_32 rsvd3:16;                     // 31:16 Reserved
};

union LINPCTRL0_REG {
    bp_32  all;
    struct  LINPCTRL0_BITS  bit;
};

struct LINPCTRL2_BITS {                   // bits description
    bp_32 rsvd1:1;                        // 0 Reserved
    bp_32 RXPVAL:1;                       // 1 Receive pin current value
    bp_32 TXPVAL:1;                       // 2 Transmit  pin current value
    bp_32 rsvd2:13;                       // 15:3 Reserved
    bp_32 rsvd3:16;                       // 31:16 Reserved
};

union LINPCTRL2_REG {
    bp_32  all;
    struct  LINPCTRL2_BITS  bit;
};

struct LINCOMP_BITS {                     // bits description
    bp_32 SBEXTSEL:3;                     // 2:0 Sync Break extend Selcet
    bp_32 rsvd1:5;                        // 7:3 Reserved
    bp_32 SDCOMPSEL:2;                    // 9:8 Sync Delimiter compare Selcet
    bp_32 rsvd2:6;                        // 15:10 Reserved
    bp_32 rsvd3:16;                       // 31:16 Reserved
};

union LINCOMP_REG {
    bp_32  all;
    struct  LINCOMP_BITS  bit;
};

struct LINRXB0_BITS {                    // bits description
    bp_32 RXB3:8;                        // 7:0 Receive Buffer 3
    bp_32 RXB2:8;                        // 15:8 Receive Buffer 2
    bp_32 RXB1:8;                        // 23:16 Receive Buffer 1
    bp_32 RXB0:8;                        // 31:24 Receive Buffer 0
};

union LINRXB0_REG {
    bp_32  all;
    struct  LINRXB0_BITS  bit;
};

struct LINRXB1_BITS {                    // bits description
    bp_32 RXB7:8;                        // 7:0 Receive Buffer 7
    bp_32 RXB6:8;                        // 15:8 Receive Buffer 6
    bp_32 RXB5:8;                        // 23:16 Receive Buffer 5
    bp_32 RXB4:8;                        // 31:24 Receive Buffer 4
};

union LINRXB1_REG {
    bp_32  all;
    struct  LINRXB1_BITS  bit;
};

struct LINIDMASK_BITS {                 // bits description
    bp_32 TXIDMASK:8;                   // 7:0 Transmit ID mask
    bp_32 rsvd1:8;                      // 15:8 Reserved
    bp_32 RXIDMASK:8;                   // 23:16 Receive ID mask
    bp_32 rsvd2:8;                      // 31:24 Reserved
};

union LINIDMASK_REG {
    bp_32  all;
    struct  LINIDMASK_BITS  bit;
};

struct LINID_BITS {                     // bits description
    bp_32 IDBYTE:8;                     // 7:0 ID byte Set
    bp_32 IDSTBYTE:8;                   // 15:8 ID Slave Task byte
    bp_32 RXID:8;                       // 23:16 Received ID
    bp_32 rsvd1:8;                      // 31:24 Reserved
};

union LINID_REG {
    bp_32  all;
    struct  LINID_BITS  bit;
};

struct LINTXB0_BITS {                    // bits description
    bp_32 TXB3:8;                        // 7:0 TRANSMIT Buffer 3
    bp_32 TXB2:8;                        // 15:8 TRANSMIT Buffer 2
    bp_32 TXB1:8;                        // 23:16 TRANSMIT Buffer 1
    bp_32 TXB0:8;                        // 31:24 TRANSMIT Buffer 0
};

union LINTXB0_REG {
    bp_32  all;
    struct  LINTXB0_BITS  bit;
};

struct LINTXB1_BITS {                    // bits description
    bp_32 TXB7:8;                        // 7:0 TRANSMIT Buffer 7
    bp_32 TXB6:8;                        // 15:8 TRANSMIT Buffer 6
    bp_32 TXB5:8;                        // 23:16 TRANSMIT Buffer 5
    bp_32 TXB4:8;                        // 31:24 TRANSMIT Buffer 4
};

union LINTXB1_REG {
    bp_32  all;
    struct  LINTXB1_BITS  bit;
};

struct LINMBRPSC_BITS {                 // bits description
    bp_32 MBRPSC:13;                    // 12:0 Maximum Baud Rate Prescaler
    bp_32 rsvd1:3;                      // 15:13 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union LINMBRPSC_REG {
    bp_32  all;
    struct  LINMBRPSC_BITS  bit;
};

struct LINEET_BITS {                    // bits description
    bp_32 ALBCFG:1;                     // 0 Analog loopback Configure
    bp_32 LBCFG:1;                      // 1 loopback Mode Configure
    bp_32 rsvd1:6;                      // 7:2 Reserved
    bp_32 IODFTEN:4;                    // 11:8 IO DFT Enable
    bp_32 rsvd2:4;                      // 15:12 Reserved
    bp_32 TXDLYCFG:3;                   // 18:16 Transmit Delay Configure
    bp_32 PSMASK:2;                     // 20:19 Pin sample mask
    bp_32 rsvd3:3;                      // 23:21 Reserved
    bp_32 BEEN:1;                       // 24 BRKDT error Enable
    bp_32 PEEN:1;                       // 25 Parity error Enable
    bp_32 FEEN:1;                       // 26 Frame error Enable
    bp_32 rsvd4:1;                      // 27 Reserved
    bp_32 ISFEEN:1;                     // 28 Inconsistent Sync Field Error Enable
    bp_32 CSEEN:1;                      // 29 Checksum Error Enable
    bp_32 PBEEN:1;                      // 30 Physical Bus Error Enable
    bp_32 BERRENA:1;                    // 31 Bit Error Enable 
};

union LINEET_REG {
    bp_32  all;
    struct  LINEET_BITS  bit;
};

struct LINGIEN_BITS {               // bits description
    bp_32 GIEN0:1;                 // 0 Global Interrupt Enable for LIN INT0
    bp_32 GIEN1:1;                 // 1 Global Interrupt Enable for LIN INT1
    bp_32 rsvd1:14;                // 15:2 Reserved
    bp_32 rsvd2:16;                // 31:16 Reserved
};

union LINGIEN_REG {
    bp_32  all;
    struct  LINGIEN_BITS  bit;
};

struct LINGIFLG_BITS {           // bits description
    bp_32 GIFLG0:1;              // 0 Global Interrupt Flag for LIN INT0
    bp_32 GIFLG1:1;              // 1 Global Interrupt Flag for LIN INT1
    bp_32 rsvd1:14;              // 15:2 Reserved
    bp_32 rsvd2:16;              // 31:16 Reserved
};

union LINGIFLG_REG {
    bp_32  all;
    struct  LINGIFLG_BITS  bit;
};

struct LINGICLR_BITS {           // bits description
    bp_32 GICLR0:1;              // 0 Global Interrupt flag clear for LIN INT0
    bp_32 GICLR1:1;              // 1 Global Interrupt flag  clear for LIN INT1
    bp_32 rsvd1:14;              // 15:2 Reserved
    bp_32 rsvd2:16;              // 31:16 Reserved
};

union LINGICLR_REG {
    bp_32  all;
    struct  LINGICLR_BITS  bit;
};

struct LIN_REGS {
    union   LINGCTRL0_REG                      LINGCTRL0;                      // Global Control Register 0
    union   LINGCTRL1_REG                      LINGCTRL1;                      // Global Control Register 1
    union   LINGCTRL2_REG                      LINGCTRL2;                      // Global Control Register 2
    union   LINIEN_REG                         LINIEN;                         // Interrupt Enable Register
    union   LINICLR_REG                        LINICLR;                        // Interrupt Disable Register
    union   LINILEN_REG                        LINILEN;                        // Set Interrupt Level Register
    union   LINILCLR_REG                       LINILCLR;                       // Clear Interrupt Level Register
    union   LINFLG_REG                         LINFLG;                         // Flag Register
    union   LINIVO0_REG                        LINIVO0;                        // Interrupt Vector Offset Register 0
    union   LINIVO1_REG                        LINIVO1;                        // Interrupt Vector Offset Register 1
    union   LINLCFG_REG                        LINLCFG;                        // Length Control Register
    union   LINBR_REG                          LINBR;                          // Baud Rate Selection Register
    union   LINRXED_REG                        LINRXED;                        // Emulation buffer Register
    union   LINRXD_REG                         LINRXD;                         // Receiver data buffer Register
    union   LINTXD_REG                         LINTXD;                         // Transmit data buffer Register
    union   LINPCTRL0_REG                      LINPCTRL0;                      // Pin control Register 0
    uint32_t                                   rsvd1;                          // Reserved
    union   LINPCTRL2_REG                      LINPCTRL2;                      // Pin control Register 2
    uint32_t                                   rsvd2[6];                       // Reserved
    union   LINCOMP_REG                        LINCOMP;                        // Compare register
    union   LINRXB0_REG                        LINRXB0;                        // Receive data register 0
    union   LINRXB1_REG                        LINRXB1;                        // Receive data register 1
    union   LINIDMASK_REG                      LINIDMASK;                      // Acceptance mask register
    union   LINID_REG                          LINID;                          // LIN ID Register
    union   LINTXB0_REG                        LINTXB0;                        // Transmit Data Register 0
    union   LINTXB1_REG                        LINTXB1;                        // Transmit Data Register 1
    union   LINMBRPSC_REG                      LINMBRPSC;                      // Maximum Baud Rate Selection Register
    uint32_t                                   rsvd3[4];                       // Reserved
    union   LINEET_REG                         LINEET;                         // IODFT for LIN
    uint32_t                                   rsvd4[19];                      // Reserved
    union   LINGIEN_REG                        LINGIEN;                        // LIN Global Interrupt Enable Register
    union   LINGIFLG_REG                       LINGIFLG;                       // LIN Global Interrupt Flag Register
    union   LINGICLR_REG                       LINGICLR;                       // LIN Global Interrupt Clear Register
};

//---------------------------------------------------------------------------
// LIN External References & Function Declarations:
//
extern volatile struct LIN_REGS LinaRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
