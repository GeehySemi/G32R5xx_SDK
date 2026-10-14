//###########################################################################
//
// FILE:    g32r502_pmbus.h
//
// TITLE:   Definitions for the PMBUS registers.
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

#ifndef G32R502_PMBUS_H
#define G32R502_PMBUS_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// PMBUS Individual Register Bit Definitions:

struct PMBUS_MCTRL_BITS {               // bits description
    Uint32 RWCFG:1;                     // 0 RWCFG - message read and write Configure
    Uint32 SADDR:7;                     // 7:1 SADDR - current message slave address
    Uint32 BYTENUM:8;                   // 15:8 BYTENUM - number of bytes of data transferred in the current message
    Uint32 COMCEN:1;                    // 16 COMCEN - use of command code on Master initiated messages Enable
    Uint32 BYTECFG:1;                   // 17 BYTECFG - Use bytes for Command Code Configure
    Uint32 PECBYTEEN:1;                 // 18 PECBYTEEN - PEC byte Enables
    Uint32 GCOMEN:1;                    // 19 GCOMEN - Transmit of Group Command message Enable
    Uint32 TXPROMEN:1;                  // 20 TXPROMEN - Transmit Process Call message Enable
    Uint32 rsvd1:11;                    // 31:21 Reserved
};

union PMBUS_MCTRL_REG {
    Uint32  all;
    struct  PMBUS_MCTRL_BITS  bit;
};

struct PMBUS_ACK_BITS {                 // bits description
    Uint32 ACK:1;                       // 0 ACK - Acknowledge received data
    Uint32 rsvd1:31;                    // 31:1 Reserved
};

union PMBUS_ACK_REG {
    Uint32  all;
    struct  PMBUS_ACK_BITS  bit;
};

struct PMBUS_STS_BITS {                 // bits description
    Uint32 RXBYTE:3;                    // 2:0 RXBYTE - Receive byte Select
    Uint32 READDATA:1;                  // 3 READDATA - Read data prior to bus activity
    Uint32 ADITDATA:1;                  // 4 ADITDATA - Request additional data
    Uint32 ENDFLG:1;                    // 5 ENDFLG - Current message End Flag
    Uint32 RXDFLG:1;                    // 6 RXDFLG - Receive data Flag
    Uint32 PECVALID:1;                  // 7 PECVALID - Received PEC is valid
    Uint32 CLKLTOFLG:1;                 // 8 CLKLTOFLG - Clock low timeout Flag
    Uint32 CLKHFLG:1;                   // 9 CLKHFLG - Clock High Flag
    Uint32 RDYRSADDR:1;                 // 10 RDYRSADDR - Ready read slave address
    Uint32 RXRESFLG:1;                  // 11 RXRESFLG - Received Repeated Star Flag
    Uint32 BUSYFLG:1;                   // 12 BUSYFLG - Busy Flag
    Uint32 AVAFLG:1;                    // 13 AVAFLG - Available Flag
    Uint32 LOSTCTRL:1;                  // 14 LOSTCTRL - Master lost control of PMBus
    Uint32 MASTERFLG:1;                 // 15 MASTERFLG - Master Mode Flag
    Uint32 ALERTTRAN:1;                 // 16 ALERTTRAN - Alert pin transitioned
    Uint32 CTRLTRAN:1;                  // 17 CTRLTRAN - Control pin transitioned
    Uint32 ALERTOLL:1;                  // 18 ALERTOLL - Alert pin at logic level high
    Uint32 CTRLOLL:1;                   // 19 CTRLOLL - Control pin at logic level high
    Uint32 SDAOLL:1;                    // 20 SDAOLL - Data pin at logic level high
    Uint32 SCLOLL:1;                    // 21 SCLOLL - Clock pin at logic level high
    Uint32 rsvd1:10;                    // 31:22 Reserved
};

union PMBUS_STS_REG {
    Uint32  all;
    struct  PMBUS_STS_BITS  bit;
};

struct PMBUS_IMASK_BITS {               // bits description
    Uint32 DISBUSIDLE:1;                // 0 DISBUSIDLE - Disables Bus Idle generation interrupt
    Uint32 DISCLKLTO:1;                 // 1 DISCLKLTO - Disables Clock Low Timeout generation interrupt
    Uint32 DISDRDY:1;                   // 2 DISDRDY - Disables Data Ready generation interrupt
    Uint32 DISDREQ:1;                   // 3 DISDREQ - Disables Data Request generation interrupt
    Uint32 DISSADDRRDY:1;               // 4 DISSADDRRDY - Disables Slave Address Ready generation interrupt
    Uint32 DISEND:1;                    // 5 DISEND - Disables Message End generation interrupt
    Uint32 DISALERT:1;                  // 6 DISALERT - Disables Alert generation interrupt
    Uint32 DISCTRL:1;                   // 7 DISCTRL - Disables Control generation interrupt
    Uint32 DISLOSTARB:1;                // 8 DISLOSTARB - Disables Lost Arbitration generation interrupt
    Uint32 DISCLKH:1;                   // 9 DISCLKH - Disables Clock High generation interrupt
    Uint32 rsvd1:22;                    // 31:10 Reserved
};

union PMBUS_IMASK_REG {
    Uint32  all;
    struct  PMBUS_IMASK_BITS  bit;
};

struct PMBUS_SCTRL_BITS {                // bits description
    Uint32 SDEVADDR:7;                   // 6:0 SDEVADDR - Slave current device address Set
    Uint32 SADDRACKEN:1;                 // 7 SADDRACKEN - Manual Slave Address Acknowledgement Enable
    Uint32 SMASKEN:7;                    // 14:8 SMASKEN - Slave mask enable
    Uint32 PECPROEN:1;                   // 15 PECPROEN - PEC processing enable
    Uint32 VALBYTESEL:3;                 // 18:16 VALBYTESEL - Valid bytes Select
    Uint32 TXPEC:1;                      // 19 TXPEC - Transmit a PEC byte at the end of the message
    Uint32 COMC:1;                       // 20 COMC - Data Request flag generated after receive of command code
    Uint32 AUTOACK:2;                    // 22:21 AUTOACK - Slave mode automatic acknowledge data bytes Configure
    Uint32 rsvd1:9;                      // 31:23 Reserved
};

union PMBUS_SCTRL_REG {
    Uint32  all;
    struct  PMBUS_SCTRL_BITS  bit;
};

struct PMBUS_HSADDR_BITS {               // bits description
    Uint32 ADDRRW:1;                     // 0 ADDRRW - Address stored R/W bit
    Uint32 DEVADDR:7;                    // 7:1 DEVADDR - Stored device address
    Uint32 rsvd1:24;                     // 31:8 Reserved
};

union PMBUS_HSADDR_REG {
    Uint32  all;
    struct  PMBUS_HSADDR_BITS  bit;
};

struct PMBUS_CTRL_BITS {                // bits description
    Uint32 STSMRSTEN:1;                 // 0 STSMRSTEN - State machines reset enable
    Uint32 ALERTLOW:1;                  // 1 ALERTLOW - PMBus Alert driven low by slave
    Uint32 CLKLTOCFG:1;                 // 2 CLKLTOCFG - Clock low timeout generated interrupt configure
    Uint32 FASTEN:1;                    // 3 FASTEN - Fast Mode enable
    Uint32 rsvd1:1;                     // 4 Reserved
    Uint32 CTRLINTCFG:1;                // 5 CTRLINTCFG - Control generated interrupt configure
    Uint32 ALERTCFG:1;                  // 6 ALERTCFG - Alert pin configure
    Uint32 ALERTDRVCFG:1;               // 7 ALERTDRVCFG - GPIO Mode Alert pin driven configure
    Uint32 ALERTDIRCFG:1;               // 8 ALERTDIRCFG - Alert pin direction configure
    Uint32 CTRLCFG:1;                   // 9 CTRLCFG - Control pin configure
    Uint32 CTRLDRVCFG:1;                // 10 CTRLDRVCFG - GPIO Mode Control pin driven configure
    Uint32 CTRLDIRCFG:1;                // 11 CTRLDIRCFG - Control pin direction configure
    Uint32 SDACFG:1;                    // 12 SDACFG - Data pin configure
    Uint32 SDADRVCFG:1;                 // 13 SDADRVCFG - GPIO Mode Data pin driven configure
    Uint32 SDADIRCFG:1;                 // 14 SDADIRCFG - Data pin direction configure
    Uint32 SCLCFG:1;                    // 15 SCLCFG - Clock pin configure
    Uint32 SCLDRVCFG:1;                 // 16 SCLDRVCFG - GPIO Mode Clock pin driven configure
    Uint32 SCLDIRCFG:1;                 // 17 SCLDIRCFG - Clock pin direction configure
    Uint32 THRUENA:1;                   // 18 THRUENA - Current source for PMBus address detection thru ADC enable
    Uint32 THRUENB:1;                   // 19 THRUENB - Current source for PMBus address detection thru ADC enable
    Uint32 DISCLKLTO:1;                 // 20 DISCLKLTO - Clock Low Timeout Disabled
    Uint32 SLAVEEN:1;                   // 21 SLAVEEN - PMBus Slave Enables
    Uint32 MASTEREN:1;                  // 22 MASTEREN - PMBus Master Enables
    Uint32 CLKDIV:5;                    // 27:23 CLKDIV - SYSCLK clock divider
    Uint32 rsvd2:3;                     // 30:28 Reserved
    Uint32 MODECFG:1;                   // 31 MODECFG - Mode Configure
};

union PMBUS_CTRL_REG {
    Uint32  all;
    struct  PMBUS_CTRL_BITS  bit;
};

struct PMBUS_TIMCTRL_BITS {             // bits description
    Uint32 PARCFG:1;                    // 0 PARCFG - FSM parameters Configure
    Uint32 rsvd1:31;                    // 31:1 Reserved
};

union PMBUS_TIMCTRL_REG {
    Uint32  all;
    struct  PMBUS_TIMCTRL_BITS  bit;
};

struct PMBUS_CLKTIM_BITS {              // bits description
    Uint32 CLKHIGHP:8;                  // 7:0 CLKHIGHP - number of FSM input clock in the PMBUS master clock high pulse Set
    Uint32 rsvd1:8;                     // 15:8 Reserved
    Uint32 CLKTIM:8;                    // 23:16 CLKTIM - number of FSM input clock in the PMBUS master clock period
    Uint32 rsvd2:8;                     // 31:24 Reserved
};

union PMBUS_CLKTIM_REG {
    Uint32  all;
    struct  PMBUS_CLKTIM_BITS  bit;
};

struct PMBUS_STATIM_BITS {              // bits description
    Uint32 STATIM:8;                    // 7:0 STATIM - time between the last rising edge of the PMBus master clock and the next starting edge
    Uint32 rsvd1:24;                    // 31:8 Reserved
};

union PMBUS_STATIM_REG {
    Uint32  all;
    struct  PMBUS_STATIM_BITS  bit;
};

struct PMBUS_BUSIDTIM_BITS {            // bits description
    Uint32 BUSIDTIM:10;                 // 9:0 BUSIDTIM - Bus Idle Time Set
    Uint32 rsvd1:22;                    // 31:10 Reserved
};

union PMBUS_BUSIDTIM_REG {
    Uint32  all;
    struct  PMBUS_BUSIDTIM_BITS  bit;
};

struct PMBUS_CLKLTOTIM_BITS {          // bits description
    Uint32 CLKLTOTIM:20;               // 19:0 CLKLTOTIM - Clock Low Timeout Time
    Uint32 rsvd1:12;                    // 31:20 Reserved
};

union PMBUS_CLKLTOTIM_REG {
    Uint32  all;
    struct  PMBUS_CLKLTOTIM_BITS  bit;
};

struct PMBUS_CLKHTOTIM_BITS {          // bits description
    Uint32 CLKHTOTIM:10;               // 9:0 CLKHTOTIM - Clock High Timeout Time
    Uint32 rsvd1:22;                    // 31:10 Reserved
};

union PMBUS_CLKHTOTIM_REG {
    Uint32  all;
    struct  PMBUS_CLKHTOTIM_BITS  bit;
};

struct PMBUS_REGS {
    union   PMBUS_MCTRL_REG                 PMBUS_MCTRL;                  // PMBUS Master Mode Control Register
    Uint32                                  PMBUS_TXB;                    // PMBUS Transmit Buffer
    Uint32                                  PMBUS_RXB;                    // PMBUS Receive Buffer
    union   PMBUS_ACK_REG                   PMBUS_ACK;                    // PMBUS Acknowledge Register
    union   PMBUS_STS_REG                   PMBUS_STS;                    // PMBUS Status Register
    union   PMBUS_IMASK_REG                 PMBUS_IMASK;                  // PMBUS Interrupt Mask Register
    union   PMBUS_SCTRL_REG                 PMBUS_SCTRL;                  // PMBUS Slave Mode Configuration Register
    union   PMBUS_HSADDR_REG                PMBUS_HSADDR;                 // PMBUS Hold Slave Address Register
    union   PMBUS_CTRL_REG                  PMBUS_CTRL;                   // PMBUS Control Register
    union   PMBUS_TIMCTRL_REG               PMBUS_TIMCTRL;                // PMBUS Timing Control Register
    union   PMBUS_CLKTIM_REG                PMBUS_CLKTIM;                 // PMBUS Clock Timing Register
    union   PMBUS_STATIM_REG                PMBUS_STATIM;                 // PMBUS Start Setup Time Register
    union   PMBUS_BUSIDTIM_REG              PMBUS_BUSIDTIM;               // PMBUS Bus Idle Time Register
    union   PMBUS_CLKLTOTIM_REG            PMBUS_CLKLTOTIM;             // PMBUS Clock Low Timeout Value Register
    union   PMBUS_CLKHTOTIM_REG            PMBUS_CLKHTOTIM;             // PMBUS Clock High Timeout Value Register
};

//---------------------------------------------------------------------------
// PMBUS External References & Function Declarations:
//
extern volatile struct PMBUS_REGS PmbusaRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
