//###########################################################################
//
// FILE:    g32r501_flash.h
//
// TITLE:   Definitions for the FLASH registers.
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

#ifndef G32R501_FLASH_H
#define G32R501_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// FLASH Individual Register Bit Definitions:

struct FRDCNTL_BITS {                   // bits description
    Uint32 rsvd1: 8;                    // 7:0 Reserved
    Uint32 RWAIT: 8;                    // 15:8 Read waitstate
    Uint32 rsvd2: 16;                   // 31:16 Reserved
};

union FRDCNTL_REG {
    Uint32  all;
    struct  FRDCNTL_BITS  bit;
};

struct FBAC_BITS {                      // bits description
    Uint32 rsvd1: 8;                    // 7:0 Reserved
    Uint32 BAGP: 8;                     // 15:8 Bank Counter reload value Set
    Uint32 rsvd2: 16;                   // 31:16 Reserved
};

union FBAC_REG {
    Uint32  all;
    struct  FBAC_BITS  bit;
};

struct FBFALLBACK_BITS {                // bits description
    Uint32 BNKPWR0: 2;                  // 1:0 Bank 0 Fall Back power mode select
    Uint32 BNKPWR1: 2;                  // 3:2 Bank 1 Fall Back power mode select
    Uint32 rsvd1: 28;                   // 31:4 Reserved
};

union FBFALLBACK_REG {
    Uint32  all;
    struct  FBFALLBACK_BITS  bit;
};

struct FBPRDY_BITS {                    // bits description
    Uint32 BANK0RDY: 1;                 // 0 Bank 0 Ready Flag
    Uint32 BANK1RDY: 1;                 // 1 Bank 1 Ready Flag
    Uint32 rsvd1: 13;                   // 14:2 Reserved
    Uint32 PUMPRDY: 1;                  // 15 Pump Ready Flag
    Uint32 rsvd2: 16;                   // 31:16 Reserved
};

union FBPRDY_REG {
    Uint32  all;
    struct  FBPRDY_BITS  bit;
};

struct PACTRL1_BITS {                   // bits description
    Uint32 rsvd1: 32;                   // 31:0 Reserved
};

union PACTRL1_REG {
    Uint32  all;
    struct  PACTRL1_BITS  bit;
};

struct PACTRL2_BITS {                   // bits description
    Uint32 rsvd1: 32;                   // 31:0 Reserved
};

union PACTRL2_REG {
    Uint32  all;
    struct  PACTRL2_BITS  bit;
};

struct FMSTAT_BITS {                    // bits description
    Uint32 rsvd1: 1;                    // 0 Reserved
    Uint32 PSUSP: 1;                    // 1 Flash receives and processed a program pend Flag
    Uint32 ESUSP: 1;                    // 2 Flash receives and processed a erase pend Flag
    Uint32 rsvd2: 1;                    // 3 Reserved
    Uint32 CSTAT: 1;                    // 4 Command Fail Flag
    Uint32 INVDAT: 1;                   // 5 Invalid Data Flag
    Uint32 PGM: 1;                      // 6 Executive program Flag
    Uint32 ERS: 1;                      // 7 Executive Erase Flag
    Uint32 BUSY: 1;                     // 8 Busy Flag
    Uint32 rsvd3: 1;                    // 9 Reserved
    Uint32 EV: 1;                       // 10 Erase Verify Flag
    Uint32 rsvd4: 1;                    // 11 Reserved
    Uint32 PGV: 1;                      // 12 Programming Verify Flag
    Uint32 REG_NOT_WRITABLE: 1;         // 13 Disable Write Register
    Uint32 rsvd5: 18;                   // 31:14 Reserved
};

union FMSTAT_REG {
    Uint32  all;
    struct  FMSTAT_BITS  bit;
};

struct FRD_INTF_CTRL_BITS {             // bits description
    Uint32 FACC0_prften : 1;            // 0 CPU0 ART accelerator Prefetch enable
    Uint32 FACC0_icen : 1;              // 1 ART accelerator Instructions cache enable
    Uint32 FACC0_dcen : 1;              // 2 CPU0 ART accelerator Data cache enable
    Uint32 FACC0_icrst: 1;              // 3 CPU0 ART accelerator Instructions cache clear
    Uint32 FACC0_dcrst: 1;              // 4 CPU0 ART accelerator Data cache clear
    Uint32 FACC1_prften: 1;             // 5 CPU1 ART accelerator Prefetch enable
    Uint32 FACC1_icen : 1;              // 6 CPU1 ART accelerator Instructions cache enable
    Uint32 FACC1_dcen : 1;              // 7 CPU1 ART accelerator Data cache enable
    Uint32 FACC1_icrst: 1;              // 8 CPU1 ART accelerator Instructions cache clear
    Uint32 FACC1_dcrst: 1;              // 9 CPU1 ART accelerator Data cache clear
    Uint32 Bus_prften : 1;              // 10 busmatrix interface Prefetch enable
    Uint32 Bus_buf_clr : 1;             // 11 busmatrix interface buffer Clear
    Uint32 rsvd1: 20;                   // 31:12 Reserved
};

union FRD_INTF_CTRL_REG {
    Uint32  all;
    struct  FRD_INTF_CTRL_BITS  bit;
};

struct FLASH_CTRL_REGS {
    union   FRDCNTL_REG                 FRDCNTL;                // Flash Read Control Register
    Uint16                               rsvd1[28];             // Reserved
    union   FBAC_REG                    FBAC;                   // Flash Bank Access Control Register
    union   FBFALLBACK_REG              FBFALLBACK;             // Flash Bank Fallback Power Register
    union   FBPRDY_REG                  FBPRDY;                 // Flash Bank Pump Ready Register
    Uint16                               rsvd2[6];              // Reserved
    union   FMSTAT_REG                  FMSTAT;                 // Flash Module Status Register
    Uint16                               rsvd3[340];            // Reserved
    union   FRD_INTF_CTRL_REG           FRD_INTF_CTRL;          // Flash Read Interface Control Register
};

struct ECC_ENABLE_BITS {                // bits description
    Uint32 DECODE_ENABLE: 4;            // 3:0 ECC decode enable
    Uint32 ENCODE_ENABLE: 4;            // 7:4 ECC encode enable
    Uint32 rsvd1: 24;                   // 31:8 Reserved
};

union ECC_ENABLE_REG {
    Uint32  all;
    struct  ECC_ENABLE_BITS  bit;
};

struct ERR_STATUS_BITS {                // bits description
    Uint32 FLASH0_FAIL_0_L: 1;          // 0 FLASH Bank0 Lower 64bits Single Bit Error Corrected Value 0
    Uint32 FLASH0_FAIL_1_L: 1;          // 1 FLASH Bank0 Lower 64bits Single Bit Error Corrected Value 1
    Uint32 FLASH0_UNC_ERR_L: 1;         // 2 FLASH Bank0 Lower 64 bits Uncorrectable error occurred
    Uint32 rsvd1: 4;                    // 7:3 Reserved
    Uint32 FLASH0_FAIL_0_H: 1;          // 8 FLASH Bank0 High 64bits Single Bit Error Corrected Value 0
    Uint32 FLASH0_FAIL_1_H: 1;          // 9 FLASH Bank0 High 64bits Single Bit Error Corrected Value 1
    Uint32 FLASH0_UNC_ERR_H: 1;         // 10 FLASH Bank0 High 64 bits Uncorrectable error occurred
    Uint32 rsvd2: 4;                    // 15:11 Reserved
    Uint32 FLASH1_FAIL_0_L: 1;          // 16 FLASH Bank1 Lower 64bits Single Bit Error Corrected Value 0
    Uint32 FLASH1_FAIL_1_L: 1;          // 17 FLASH Bank1 Lower 64bits Single Bit Error Corrected Value 1
    Uint32 FLASH1_UNC_ERR_L: 1;         // 18 FLASH Bank1 Lower 64 bits Uncorrectable error occurred
    Uint32 rsvd3: 4;                    // 23:19 Reserved
    Uint32 FLASH1_FAIL_0_H: 1;          // 24 FLASH Bank1 High 64bits Single Bit Error Corrected Value 0
    Uint32 FLASH1_FAIL_1_H: 1;          // 25 FLASH Bank1 High 64bits Single Bit Error Corrected Value 1
    Uint32 FLASH1_UNC_ERR_H: 1;         // 26 FLASH Bank1 High 64 bits Uncorrectable error occurred
    Uint32 rsvd4: 4;                    // 31:27 Reserved
};

union ERR_STATUS_REG {
    Uint32  all;
    struct  ERR_STATUS_BITS  bit;
};

struct ERR_POS_BITS {                   // bits description
    Uint32 Flash0_ERR_POS_L: 6;         // 5:0 FLASH0 Error position Low
    Uint32 rsvd1: 1;                    // 6 Reserved
    Uint32 FLASH0_ERR_TYPE_L: 1;        // 7 FLASH0 Error type Low
    Uint32 Flash0_ERR_POS_H: 6;         // 13:8 FLASH0 Error position High
    Uint32 rsvd2: 1;                    // 14 Reserved
    Uint32 FLASH0_ERR_TYPE_H: 1;        // 15 FLASH0 Error type High
    Uint32 Flash1_ERR_POS_L: 6;         // 21:16 FLASH1 Error position Low
    Uint32 rsvd3: 1;                    // 22 Reserved
    Uint32 FLASH1_ERR_TYPE_L: 1;        // 23 FLASH1 Error type Low
    Uint32 Flash1_ERR_POS_H: 6;         // 29:24 FLASH1 Error position High
    Uint32 rsvd4: 1;                    // 30 Reserved
    Uint32 FLASH1_ERR_TYPE_H: 1;        // 31 FLASH1 Error type High
};

union ERR_POS_REG {
    Uint32  all;
    struct  ERR_POS_BITS  bit;
};

struct ERR_STATUS_CLR_BITS {            // bits description
    Uint32 FLASH0_FAIL_0_L_CLR: 1;      // 0 FLASH0 Fail on 0 Single Error Low Flag clear
    Uint32 FLASH0_FAIL_1_L_CLR: 1;      // 1 FLASH0 Fail on 1 Single Error Low Flag clear
    Uint32 FLASH0_UNC_ERR_L_CLR: 1;     // 2 FLASH0 Uncorrectable Error Low Flag clear
    Uint32 rsvd1: 5;                    // 7:3 Reserved
    Uint32 FLASH0_FAIL_0_H_CLR: 1;      // 8 FLASH0 Fail on 0 Single Error High Flag clear
    Uint32 FLASH0_FAIL_1_H_CLR: 1;      // 9 FLASH0 Fail on 1 Single Error High Flag clear
    Uint32 FLASH0_UNC_ERR_H_CLR: 1;     // 10 FLASH0 Uncorrectable Error High Flag clear
    Uint32 rsvd2: 5;                    // 15:11 Reserved
    Uint32 FLASH1_FAIL_0_L_CLR: 1;      // 16 FLASH1 Fail on 0 Single Error Low Flag clear
    Uint32 FLASH1_FAIL_1_L_CLR: 1;      // 17 FLASH1 Fail on 1 Single Error Low Flag clear
    Uint32 FLASH1_UNC_ERR_L_CLR: 1;     // 18 FLASH1 Uncorrectable Error Low Flag clear
    Uint32 rsvd3: 5;                    // 23:19 Reserved
    Uint32 FLASH1_FAIL_0_H_CLR: 1;      // 24 FLASH1 Fail on 0 Single Error High Flag clear
    Uint32 FLASH1_FAIL_1_H_CLR: 1;      // 25 FLASH1 Fail on 1 Single Error High Flag clear
    Uint32 FLASH1_UNC_ERR_H_CLR: 1;     // 26 FLASH1 Uncorrectable Error High Flag clear
    Uint32 rsvd4: 5;                    // 31:27 Reserved
};

union ERR_STATUS_CLR_REG {
    Uint32  all;
    struct  ERR_STATUS_CLR_BITS  bit;
};

struct ERR_CNT_BITS {                   // bits description
    Uint32 ERR_CNT: 16;                 // 15:0 Single bit error count
    Uint32 rsvd1: 16;                   // 31:16 Reserved
};

union ERR_CNT_REG {
    Uint32  all;
    struct  ERR_CNT_BITS  bit;
};

struct ERR_THRESHOLD_BITS {             // bits description
    Uint32 ERR_THRESHOLD: 16;           // 15:0 Single bit error threshold
    Uint32 rsvd1: 16;                   // 31:16 Reserved
};

union ERR_THRESHOLD_REG {
    Uint32  all;
    struct  ERR_THRESHOLD_BITS  bit;
};

struct ERR_INTFLG_BITS {                // bits description
    Uint32 SINGLE_ERR_INTFLG: 1;        // 0 Single bit error interrupt flag
    Uint32 UNC_ERR_INTFLG: 1;           // 1 Uncorrectable error interrupt flag
    Uint32 rsvd1: 14;                   // 15:2 Reserved
    Uint32 rsvd2: 16;                   // 31:16 Reserved
};

union ERR_INTFLG_REG {
    Uint32  all;
    struct  ERR_INTFLG_BITS  bit;
};

struct ERR_INTCLR_BITS {                // bits description
    Uint32 SINGLE_ERR_INTCLR: 1;        // 0 Single bit error interrupt flag clear
    Uint32 UNC_ERR_INTCLR : 1;          // 1 Uncorrectable error interrupt flag clear
    Uint32 rsvd1: 14;                   // 15:2 Reserved
    Uint32 rsvd2: 16;                   // 31:16 Reserved
};

union ERR_INTCLR_REG {
    Uint32  all;
    struct  ERR_INTCLR_BITS  bit;
};

struct FADDR_TEST_BITS {                // bits description
    Uint32 rsvd1: 3;                    // 2:0 Reserved
    Uint32 ADDRL: 13;                   // 15:3 Selected data Address low
    Uint32 ADDRH: 6;                    // 21:16 Selected data Address high
    Uint32 rsvd2: 10;                   // 31:22 Reserved
};

union FADDR_TEST_REG {
    Uint32  all;
    struct  FADDR_TEST_BITS  bit;
};

struct FECC_TEST_BITS {                 // bits description
    Uint32 ECC: 8;                      // 7:0 Selected data ECC
    Uint32 rsvd1: 8;                    // 15:8 Reserved
    Uint32 rsvd2: 16;                   // 31:16 Reserved
};

union FECC_TEST_REG {
    Uint32  all;
    struct  FECC_TEST_BITS  bit;
};

struct FECC_CTRL_BITS {                 // bits description
    Uint32 ECC_TEST_EN: 1;              // 0 ECC test mode enable
    Uint32 ECC_SELECT: 2;               // 2:1 ECC block select
    Uint32 DO_ECC_CALC: 1;              // 3 Enable ECC Calculation
    Uint32 rsvd1: 28;                   // 31:4 Reserved
};

union FECC_CTRL_REG {
    Uint32  all;
    struct  FECC_CTRL_BITS  bit;
};

struct FECC_STATUS_BITS {               // bits description
    Uint32 SINGLE_ERR: 1;               // 0 Test mode ECC single bit error Flag
    Uint32 UNC_ERR: 1;                  // 1 Test mode Uncorrectable Error Flag
    Uint32 DATA_ERR_POS: 6;             // 7:2 Test mode single bit error position
    Uint32 ERR_TYPE: 1;                 // 8 Test mode single bit error type
    Uint32 rsvd1: 7;                    // 15:9 Reserved
    Uint32 rsvd2: 16;                   // 31:16 Reserved
};

union FECC_STATUS_REG {
    Uint32  all;
    struct  FECC_STATUS_BITS  bit;
};

struct FLASH_ECC_REGS {
    union   ECC_ENABLE_REG                  ECC_ENABLE;                 // ECC Enable
    Uint32                                   SINGLE_ERR_ADDR_LOW_0;     // FLASH Bank0 single error address low
    Uint32                                   SINGLE_ERR_ADDR_HIGH_0;    // FLASH Bank0 single error address high
    Uint32                                   UNC_ERR_ADDR_LOW_0;        // FLASH Bank0 uncorrectable error address low
    Uint32                                   UNC_ERR_ADDR_HIGH_0;       // FLASH Bank0 uncorrectable error address high
    union   ERR_STATUS_REG                  ERR_STATUS;                 // Error Status
    union   ERR_POS_REG                     ERR_POS;                    // Error Position
    union   ERR_STATUS_CLR_REG              ERR_STATUS_CLR;             // Error Status Clear
    union   ERR_CNT_REG                     ERR_CNT;                    // Error counter
    union   ERR_THRESHOLD_REG               ERR_THRESHOLD;              // Error threshold
    union   ERR_INTFLG_REG                  ERR_INTFLG;                 // Error interrupt flag
    union   ERR_INTCLR_REG                  ERR_INTCLR;                 // Error interrupt clear
    Uint32                                   FDATAH_TEST;               // Data high test
    Uint32                                   FDATAL_TEST;               // Data low test
    union   FADDR_TEST_REG                  FADDR_TEST;                 // ECC test address
    union   FECC_TEST_REG                   FECC_TEST;                  // ECC test ECC
    union   FECC_CTRL_REG                   FECC_CTRL;                  // ECC Control
    Uint32                                   FOUTH_TEST;                // Test Data Out High
    Uint32                                   FOUTL_TEST;                // Test Data Out Low
    union   FECC_STATUS_REG                 FECC_STATUS;                // ECC Status
    Uint32                                   SINGLE_ERR_ADDR_LOW_1;     // FLASH Bank1 single error address low
    Uint32                                   SINGLE_ERR_ADDR_HIGH_1;    // FLASH Bank1 single error address high
    Uint32                                   UNC_ERR_ADDR_LOW_1;        // FLASH Bank1 uncorrectable error address low
    Uint32                                   UNC_ERR_ADDR_HIGH_1;       // FLASH Bank1 uncorrectable error address high
};

//---------------------------------------------------------------------------
// FLASH External References & Function Declarations:
//
extern volatile struct FLASH_CTRL_REGS Flash0CtrlRegs;
extern volatile struct FLASH_ECC_REGS Flash0EccRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
