//###########################################################################
//
// FILE:    g32r501_pwm.h
//
// TITLE:   Definitions for the PWM registers.
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
#ifndef G32R501_PWM_H
#define G32R501_PWM_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// PWM Individual Register Bit Definitions:

struct TBCTL_BITS {                     // bits description
    Uint16 CTRMODE:2;                   // 1:0 Counter Mode
    Uint16 PHSEN:1;                     // 2 Phase Load Enable
    Uint16 PRDLD:1;                     // 3 Active Period Load
    Uint16 SYNCOSEL:2;                  // 5:4 Sync Output Select
    Uint16 SWFSYNC:1;                   // 6 Software Force Sync Pulse
    Uint16 HSPCLKDIV:3;                 // 9:7 High Speed TBCLK Pre-scaler
    Uint16 CLKDIV:3;                    // 12:10 Time Base Clock Pre-scaler
    Uint16 PHSDIR:1;                    // 13 Phase Direction Bit
    Uint16 FREE_SOFT:2;                 // 15:14 Emulation Mode Bits
};

union TBCTL_REG {
    Uint16  all;
    struct  TBCTL_BITS  bit;
};

struct TBCTL2_BITS {                    // bits description
    Uint16 rsvd1:5;                     // 4:0 Reserved
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 OSHTSYNCMODE:1;              // 6 One shot sync mode
    Uint16 OSHTSYNC:1;                  // 7 One shot sync
    Uint16 rsvd3:4;                     // 11:8 Reserved
    Uint16 SYNCOSELX:2;                 // 13:12 Syncout selection
    Uint16 PRDLDSYNC:2;                 // 15:14 PRD Shadow to Active Load on SYNC Event
};

union TBCTL2_REG {
    Uint16  all;
    struct  TBCTL2_BITS  bit;
};

struct TBSTS_BITS {                     // bits description
    Uint16 CTRDIR:1;                    // 0 Counter Direction Status
    Uint16 SYNCI:1;                     // 1 External Input Sync Status
    Uint16 CTRMAX:1;                    // 2 Counter Max Latched Status
    Uint16 rsvd1:13;                    // 15:3 Reserved
};

union TBSTS_REG {
    Uint16  all;
    struct  TBSTS_BITS  bit;
};

struct CMPCTL_BITS {                    // bits description
    Uint16 LOADAMODE:2;                 // 1:0 Active Compare A Load
    Uint16 LOADBMODE:2;                 // 3:2 Active Compare B Load
    Uint16 SHDWAMODE:1;                 // 4 Compare A Register Block Operating Mode
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 SHDWBMODE:1;                 // 6 Compare B Register Block Operating Mode
    Uint16 rsvd2:1;                     // 7 Reserved
    Uint16 SHDWAFULL:1;                 // 8 Compare A Shadow Register Full Status
    Uint16 SHDWBFULL:1;                 // 9 Compare B Shadow Register Full Status
    Uint16 LOADASYNC:2;                 // 11:10 Active Compare A Load on SYNC
    Uint16 LOADBSYNC:2;                 // 13:12 Active Compare B Load on SYNC
    Uint16 rsvd3:2;                     // 15:14 Reserved
};

union CMPCTL_REG {
    Uint16  all;
    struct  CMPCTL_BITS  bit;
};

struct CMPCTL2_BITS {                   // bits description
    Uint16 LOADCMODE:2;                 // 1:0 Active Compare C Load
    Uint16 LOADDMODE:2;                 // 3:2 Active Compare D load
    Uint16 SHDWCMODE:1;                 // 4 Compare C Block Operating Mode
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 SHDWDMODE:1;                 // 6 Compare D Block Operating Mode
    Uint16 rsvd2:3;                     // 9:7 Reserved
    Uint16 LOADCSYNC:2;                 // 11:10 Active Compare C Load on SYNC
    Uint16 LOADDSYNC:2;                 // 13:12 Active Compare D Load on SYNC
    Uint16 rsvd3:2;                     // 15:14 Reserved
};

union CMPCTL2_REG {
    Uint16  all;
    struct  CMPCTL2_BITS  bit;
};

struct DBCTL_BITS {                     // bits description
    Uint16 OUT_MODE:2;                  // 1:0 Dead Band Output Mode Control
    Uint16 POLSEL:2;                    // 3:2 Polarity Select Control
    Uint16 IN_MODE:2;                   // 5:4 Dead Band Input Select Mode Control
    Uint16 LOADREDMODE:2;               // 7:6 Active DBRED Load Mode
    Uint16 LOADFEDMODE:2;               // 9:8 Active DBFED Load Mode
    Uint16 SHDWDBREDMODE:1;             // 10 DBRED Block Operating Mode
    Uint16 SHDWDBFEDMODE:1;             // 11 DBFED Block Operating Mode
    Uint16 OUTSWAP:2;                   // 13:12 Dead Band Output Swap Control
    Uint16 DEDB_MODE:1;                 // 14 Dead Band Dual-Edge B Mode Control
    Uint16 HALFCYCLE:1;                 // 15 Half Cycle Clocking Enable
};

union DBCTL_REG {
    Uint16  all;
    struct  DBCTL_BITS  bit;
};

struct DBCTL2_BITS {                    // bits description
    Uint16 LOADDBCTLMODE:2;             // 1:0 DBCTL Load from Shadow Mode Select
    Uint16 SHDWDBCTLMODE:1;             // 2 DBCTL Load mode Select
    Uint16 rsvd1:13;                    // 15:3 Reserved
};

union DBCTL2_REG {
    Uint16  all;
    struct  DBCTL2_BITS  bit;
};

struct AQCTL_BITS {                     // bits description
    Uint16 LDAQAMODE:2;                 // 1:0 Action Qualifier A Load Select
    Uint16 LDAQBMODE:2;                 // 3:2 Action Qualifier B Load Select
    Uint16 SHDWAQAMODE:1;               // 4 Action Qualifer A Operating Mode
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 SHDWAQBMODE:1;               // 6 Action Qualifier B Operating Mode
    Uint16 rsvd2:1;                     // 7 Reserved
    Uint16 LDAQASYNC:2;                 // 9:8 AQCTLA Register Load on SYNC
    Uint16 LDAQBSYNC:2;                 // 11:10 AQCTLB Register Load on SYNC
    Uint16 rsvd3:4;                     // 15:12 Reserved
};

union AQCTL_REG {
    Uint16  all;
    struct  AQCTL_BITS  bit;
};

struct AQTSRCSEL_BITS {                 // bits description
    Uint16 T1SEL:4;                     // 3:0 T1 Event Source Select Bits
    Uint16 T2SEL:4;                     // 7:4 T2 Event Source Select Bits
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union AQTSRCSEL_REG {
    Uint16  all;
    struct  AQTSRCSEL_BITS  bit;
};

struct PCCTL_BITS {                     // bits description
    Uint16 CHPEN:1;                     // 0 PWM chopping enable
    Uint16 OSHTWTH:4;                   // 4:1 One-shot pulse width
    Uint16 CHPFREQ:3;                   // 7:5 Chopping clock frequency
    Uint16 CHPDUTY:3;                   // 10:8 Chopping clock Duty cycle
    Uint16 rsvd1:5;                     // 15:11 Reserved
};

union PCCTL_REG {
    Uint16  all;
    struct  PCCTL_BITS  bit;
};

struct VCAPCTL_BITS {                   // bits description
    Uint16 VCAPE:1;                     // 0 Valley  Capture mode
    Uint16 VCAPSTART:1;                 // 1 Valley  Capture Start
    Uint16 TRIGSEL:3;                   // 4:2 Capture Trigger Select
    Uint16 rsvd1:2;                     // 6:5 Reserved
    Uint16 VDELAYDIV:3;                 // 9:7 Valley Delay Mode Divide Enable
    Uint16 EDGEFILTDLYSEL:1;            // 10 Valley Switching Mode Delay Select
    Uint16 rsvd2:5;                     // 15:11 Reserved
};

union VCAPCTL_REG {
    Uint16  all;
    struct  VCAPCTL_BITS  bit;
};

struct VCNTCFG_BITS {                   // bits description
    Uint16 STARTEDGE:4;                 // 3:0 Counter Start Edge Selection
    Uint16 rsvd1:3;                     // 6:4 Reserved
    Uint16 STARTEDGESTS:1;              // 7 Start Edge Status Bit
    Uint16 STOPEDGE:4;                  // 11:8 Counter Start Edge Selection
    Uint16 rsvd2:3;                     // 14:12 Reserved
    Uint16 STOPEDGESTS:1;               // 15 Stop Edge Status Bit
};

union VCNTCFG_REG {
    Uint16  all;
    struct  VCNTCFG_BITS  bit;
};

struct HRCNFG_BITS {                    // bits description
    Uint16 EDGMODE:2;                   // 1:0 PWMxA Edge Mode Select Bits
    Uint16 CTLMODE:1;                   // 2 PWMxA Control Mode Select Bits
    Uint16 HRLOAD:2;                    // 4:3 PWMxA Shadow Mode Select Bits
    Uint16 SELOUTB:1;                   // 5 PWMB Output Selection Bit
    Uint16 AUTOCONV:1;                  // 6 Autoconversion Bit
    Uint16 SWAPAB:1;                    // 7 Swap PWMA and PWMB Outputs Bit
    Uint16 EDGMODEB:2;                  // 9:8 PWMxB Edge Mode Select Bits
    Uint16 CTLMODEB:1;                  // 10 PWMxB Control Mode Select Bits
    Uint16 HRLOADB:2;                   // 12:11 PWMxB Shadow Mode Select Bits
    Uint16 rsvd1:1;                     // 13 Reserved
    Uint16 rsvd2:2;                     // 15:14 Reserved
};

union HRCNFG_REG {
    Uint16  all;
    struct  HRCNFG_BITS  bit;
};

struct HRPWR_BITS {                     // bits description
    Uint16 rsvd1:2;                     // 1:0 Reserved
    Uint16 rsvd2:1;                     // 2 Reserved
    Uint16 rsvd3:1;                     // 3 Reserved
    Uint16 rsvd4:1;                     // 4 Reserved
    Uint16 rsvd5:1;                     // 5 Reserved
    Uint16 rsvd6:4;                     // 9:6 Reserved
    Uint16 rsvd7:5;                     // 14:10 Reserved
    Uint16 CALPWRON:1;                  // 15 Calibration Power On
};

union HRPWR_REG {
    Uint16  all;
    struct  HRPWR_BITS  bit;
};

struct HRMSTEP_BITS {                   // bits description
    Uint16 HRMSTEP:8;                   // 7:0 High Resolution Micro Step Value
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union HRMSTEP_REG {
    Uint16  all;
    struct  HRMSTEP_BITS  bit;
};

struct HRCNFG2_BITS {                   // bits description
    Uint16 EDGMODEDB:2;                 // 1:0 Dead-Band Edge-Mode Select Bits
    Uint16 CTLMODEDBRED:2;              // 3:2 DBRED Control Mode Select Bits
    Uint16 CTLMODEDBFED:2;              // 5:4 DBFED Control Mode Select Bits
    Uint16 rsvd1:8;                     // 13:6 Reserved
    Uint16 rsvd2:1;                     // 14 Reserved
    Uint16 rsvd3:1;                     // 15 Reserved
};

union HRCNFG2_REG {
    Uint16  all;
    struct  HRCNFG2_BITS  bit;
};

struct HRPCTL_BITS {                    // bits description
    Uint16 HRPE:1;                      // 0 High Resolution Period Enable
    Uint16 PWMSYNCSEL:1;                // 1 PWMSYNCPER Source Select
    Uint16 TBPHSHRLOADE:1;              // 2 TBPHSHR Load Enable
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 PWMSYNCSELX:3;               // 6:4 PWMSYNCPER Extended Source Select Bit:
    Uint16 rsvd2:9;                     // 15:7 Reserved
};

union HRPCTL_REG {
    Uint16  all;
    struct  HRPCTL_BITS  bit;
};

struct TRREM_BITS {                     // bits description
    Uint16 TRREM:11;                    // 10:0 HRPWM Remainder Bits
    Uint16 rsvd1:5;                     // 15:11 Reserved
};

union TRREM_REG {
    Uint16  all;
    struct  TRREM_BITS  bit;
};

struct GLDCTL_BITS {                    // bits description
    Uint16 GLD:1;                       // 0 Global Shadow to Active load event control
    Uint16 GLDMODE:4;                   // 4:1 Shadow to Active Global Load Pulse Selection
    Uint16 OSHTMODE:1;                  // 5 One Shot Load mode control bit
    Uint16 rsvd1:1;                     // 6 Reserved
    Uint16 GLDPRD:3;                    // 9:7 Global Load Strobe Period Select Register
    Uint16 GLDCNT:3;                    // 12:10 Global Load Strobe Counter Register
    Uint16 rsvd2:3;                     // 15:13 Reserved
};

union GLDCTL_REG {
    Uint16  all;
    struct  GLDCTL_BITS  bit;
};

struct GLDCFG_BITS {                    // bits description
    Uint16 TBPRD_TBPRDHR:1;             // 0 Global load event configuration for TBPRD:TBPRDHR
    Uint16 CMPA_CMPAHR:1;               // 1 Global load event configuration for CMPA:CMPAHR
    Uint16 CMPB_CMPBHR:1;               // 2 Global load event configuration for CMPB:CMPBHR
    Uint16 CMPC:1;                      // 3 Global load event configuration for CMPC
    Uint16 CMPD:1;                      // 4 Global load event configuration for CMPD
    Uint16 DBRED_DBREDHR:1;             // 5 Global load event configuration for DBRED:DBREDHR
    Uint16 DBFED_DBFEDHR:1;             // 6 Global load event configuration for DBFED:DBFEDHR
    Uint16 DBCTL:1;                     // 7 Global load event configuration for DBCTL
    Uint16 AQCTLA_AQCTLA2:1;            // 8 Global load event configuration for AQCTLA/A2
    Uint16 AQCTLB_AQCTLB2:1;            // 9 Global load event configuration for AQCTLB/B2
    Uint16 AQCSFRC:1;                   // 10 Global load event configuration for AQCSFRC
    Uint16 rsvd1:5;                     // 15:11 Reserved
};

union GLDCFG_REG {
    Uint16  all;
    struct  GLDCFG_BITS  bit;
};

struct PWMXLINK_BITS {                 // bits description
    Uint32 TBPRDLINK:4;                 // 3:0 TBPRD:TBPRDHR  Link
    Uint32 CMPALINK:4;                  // 7:4 CMPA:CMPAHR Link
    Uint32 CMPBLINK:4;                  // 11:8 CMPB:CMPBHR Link
    Uint32 CMPCLINK:4;                  // 15:12 CMPC Link
    Uint32 CMPDLINK:4;                  // 19:16 CMPD Link
    Uint32 rsvd1:8;                     // 27:20 Reserved
    Uint32 GLDCTL2LINK:4;               // 31:28 GLDCTL2 Link
};

union PWMXLINK_REG {
    Uint32  all;
    struct  PWMXLINK_BITS  bit;
};

struct AQCTLA_BITS {                    // bits description
    Uint16 ZRO:2;                       // 1:0 Action Counter = Zero
    Uint16 PRD:2;                       // 3:2 Action Counter = Period
    Uint16 CAU:2;                       // 5:4 Action Counter = Compare A Up
    Uint16 CAD:2;                       // 7:6 Action Counter = Compare A Down
    Uint16 CBU:2;                       // 9:8 Action Counter = Compare B Up
    Uint16 CBD:2;                       // 11:10 Action Counter = Compare B Down
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union AQCTLA_REG {
    Uint16  all;
    struct  AQCTLA_BITS  bit;
};

struct AQCTLA2_BITS {                   // bits description
    Uint16 T1U:2;                       // 1:0 Action when event occurs on T1 in UP-Count
    Uint16 T1D:2;                       // 3:2 Action when event occurs on T1 in DOWN-Count
    Uint16 T2U:2;                       // 5:4 Action when event occurs on T2 in UP-Count
    Uint16 T2D:2;                       // 7:6 Action when event occurs on T2 in DOWN-Count
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union AQCTLA2_REG {
    Uint16  all;
    struct  AQCTLA2_BITS  bit;
};

struct AQCTLB_BITS {                    // bits description
    Uint16 ZRO:2;                       // 1:0 Action Counter = Zero
    Uint16 PRD:2;                       // 3:2 Action Counter = Period
    Uint16 CAU:2;                       // 5:4 Action Counter = Compare A Up
    Uint16 CAD:2;                       // 7:6 Action Counter = Compare A Down
    Uint16 CBU:2;                       // 9:8 Action Counter = Compare B Up
    Uint16 CBD:2;                       // 11:10 Action Counter = Compare B Down
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union AQCTLB_REG {
    Uint16  all;
    struct  AQCTLB_BITS  bit;
};

struct AQCTLB2_BITS {                   // bits description
    Uint16 T1U:2;                       // 1:0 Action when event occurs on T1 in UP-Count
    Uint16 T1D:2;                       // 3:2 Action when event occurs on T1 in DOWN-Count
    Uint16 T2U:2;                       // 5:4 Action when event occurs on T2 in UP-Count
    Uint16 T2D:2;                       // 7:6 Action when event occurs on T2 in DOWN-Count
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union AQCTLB2_REG {
    Uint16  all;
    struct  AQCTLB2_BITS  bit;
};

struct AQSFRC_BITS {                    // bits description
    Uint16 ACTSFA:2;                    // 1:0 Action when One-time SW Force A Invoked
    Uint16 OTSFA:1;                     // 2 One-time SW Force A Output
    Uint16 ACTSFB:2;                    // 4:3 Action when One-time SW Force B Invoked
    Uint16 OTSFB:1;                     // 5 One-time SW Force A Output
    Uint16 RLDCSF:2;                    // 7:6 Reload from Shadow Options
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union AQSFRC_REG {
    Uint16  all;
    struct  AQSFRC_BITS  bit;
};

struct AQCSFRC_BITS {                   // bits description
    Uint16 CSFA:2;                      // 1:0 Continuous Software Force on output A
    Uint16 CSFB:2;                      // 3:2 Continuous Software Force on output B
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union AQCSFRC_REG {
    Uint16  all;
    struct  AQCSFRC_BITS  bit;
};

struct DBREDHR_BITS {                   // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:7;                     // 7:1 Reserved
    Uint16 rsvd3:1;                     // 8 Reserved
    Uint16 DBREDHR:7;                   // 15:9 DBREDHR High Resolution Bits
};

union DBREDHR_REG {
    Uint16  all;
    struct  DBREDHR_BITS  bit;
};

struct DBRED_BITS {                     // bits description
    Uint16 DBRED:14;                    // 13:0 Rising edge delay value
    Uint16 rsvd1:2;                     // 15:14 Reserved
};

union DBRED_REG {
    Uint16  all;
    struct  DBRED_BITS  bit;
};

struct DBFEDHR_BITS {                   // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:7;                     // 7:1 Reserved
    Uint16 rsvd3:1;                     // 8 Reserved
    Uint16 DBFEDHR:7;                   // 15:9 DBFEDHR High Resolution Bits
};

union DBFEDHR_REG {
    Uint16  all;
    struct  DBFEDHR_BITS  bit;
};

struct DBFED_BITS {                     // bits description
    Uint16 DBFED:14;                    // 13:0 Falling edge delay value
    Uint16 rsvd1:2;                     // 15:14 Reserved
};

union DBFED_REG {
    Uint16  all;
    struct  DBFED_BITS  bit;
};

struct TBPHS_BITS {                     // bits description
    Uint32 TBPHSHR:16;                  // 15:0 Extension Register for HRPWM Phase (8-bits)
    Uint32 TBPHS:16;                    // 31:16 Phase Offset Register
};

union TBPHS_REG {
    Uint32  all;
    struct  TBPHS_BITS  bit;
};

struct CMPA_BITS {                      // bits description
    Uint32 CMPAHR:16;                   // 15:0 Compare A HRPWM Extension Register
    Uint32 CMPA:16;                     // 31:16 Compare A Register
};

union CMPA_REG {
    Uint32  all;
    struct  CMPA_BITS  bit;
};

struct CMPB_BITS {                      // bits description
    Uint32 CMPBHR:16;                   // 15:0 Compare B High Resolution Bits
    Uint32 CMPB:16;                     // 31:16 Compare B Register
};

union CMPB_REG {
    Uint32  all;
    struct  CMPB_BITS  bit;
};

struct GLDCTL2_BITS {                   // bits description
    Uint16 OSHTLD:1;                    // 0 Enable reload event in one shot mode
    Uint16 GFRCLD:1;                    // 1 Force reload event in one shot mode
    Uint16 rsvd1:14;                    // 15:2 Reserved
};

union GLDCTL2_REG {
    Uint16  all;
    struct  GLDCTL2_BITS  bit;
};

struct TZSEL_BITS {                     // bits description
    Uint16 CBC1:1;                      // 0 TZ1 CBC select
    Uint16 CBC2:1;                      // 1 TZ2 CBC select
    Uint16 CBC3:1;                      // 2 TZ3 CBC select
    Uint16 CBC4:1;                      // 3 TZ4 CBC select
    Uint16 CBC5:1;                      // 4 TZ5 CBC select
    Uint16 CBC6:1;                      // 5 TZ6 CBC select
    Uint16 DCAEVT2:1;                   // 6 DCAEVT2 CBC select
    Uint16 DCBEVT2:1;                   // 7 DCBEVT2 CBC select
    Uint16 OSHT1:1;                     // 8 One-shot TZ1 select
    Uint16 OSHT2:1;                     // 9 One-shot TZ2 select
    Uint16 OSHT3:1;                     // 10 One-shot TZ3 select
    Uint16 OSHT4:1;                     // 11 One-shot TZ4 select
    Uint16 OSHT5:1;                     // 12 One-shot TZ5 select
    Uint16 OSHT6:1;                     // 13 One-shot TZ6 select
    Uint16 DCAEVT1:1;                   // 14 One-shot DCAEVT1 select
    Uint16 DCBEVT1:1;                   // 15 One-shot DCBEVT1 select
};

union TZSEL_REG {
    Uint16  all;
    struct  TZSEL_BITS  bit;
};

struct TZDCSEL_BITS {                   // bits description
    Uint16 DCAEVT1:3;                   // 2:0 Digital Compare Output A Event 1
    Uint16 DCAEVT2:3;                   // 5:3 Digital Compare Output A Event 2
    Uint16 DCBEVT1:3;                   // 8:6 Digital Compare Output B Event 1
    Uint16 DCBEVT2:3;                   // 11:9 Digital Compare Output B Event 2
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union TZDCSEL_REG {
    Uint16  all;
    struct  TZDCSEL_BITS  bit;
};

struct TZCTL_BITS {                     // bits description
    Uint16 TZA:2;                       // 1:0 TZ1 to TZ6 Trip Action On PWMxA
    Uint16 TZB:2;                       // 3:2 TZ1 to TZ6 Trip Action On PWMxB
    Uint16 DCAEVT1:2;                   // 5:4 PWMxA action on DCAEVT1
    Uint16 DCAEVT2:2;                   // 7:6 PWMxA action on DCAEVT2
    Uint16 DCBEVT1:2;                   // 9:8 PWMxB action on DCBEVT1
    Uint16 DCBEVT2:2;                   // 11:10 PWMxB action on DCBEVT2
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union TZCTL_REG {
    Uint16  all;
    struct  TZCTL_BITS  bit;
};

struct TZCTL2_BITS {                    // bits description
    Uint16 TZAU:3;                      // 2:0 Trip Action On PWMxA while Count direction is UP
    Uint16 TZAD:3;                      // 5:3 Trip Action On PWMxA while Count direction is DOWN
    Uint16 TZBU:3;                      // 8:6 Trip Action On PWMxB while Count direction is UP
    Uint16 TZBD:3;                      // 11:9 Trip Action On PWMxB while Count direction is DOWN
    Uint16 rsvd1:3;                     // 14:12 Reserved
    Uint16 ETZE:1;                      // 15 TZCTL2 Enable
};

union TZCTL2_REG {
    Uint16  all;
    struct  TZCTL2_BITS  bit;
};

struct TZCTLDCA_BITS {                  // bits description
    Uint16 DCAEVT1U:3;                  // 2:0 DCAEVT1 Action On PWMxA while Count direction is UP
    Uint16 DCAEVT1D:3;                  // 5:3 DCAEVT1 Action On PWMxA while Count direction is DOWN
    Uint16 DCAEVT2U:3;                  // 8:6 DCAEVT2 Action On PWMxA while Count direction is UP
    Uint16 DCAEVT2D:3;                  // 11:9 DCAEVT2 Action On PWMxA while Count direction is DOWN
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union TZCTLDCA_REG {
    Uint16  all;
    struct  TZCTLDCA_BITS  bit;
};

struct TZCTLDCB_BITS {                  // bits description
    Uint16 DCBEVT1U:3;                  // 2:0 DCBEVT1 Action On PWMxA while Count direction is UP
    Uint16 DCBEVT1D:3;                  // 5:3 DCBEVT1 Action On PWMxA while Count direction is DOWN
    Uint16 DCBEVT2U:3;                  // 8:6 DCBEVT2 Action On PWMxA while Count direction is UP
    Uint16 DCBEVT2D:3;                  // 11:9 DCBEVT2 Action On PWMxA while Count direction is DOWN
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union TZCTLDCB_REG {
    Uint16  all;
    struct  TZCTLDCB_BITS  bit;
};

struct TZEINT_BITS {                    // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 CBC:1;                       // 1 Trip Zones Cycle By Cycle Int Enable
    Uint16 OST:1;                       // 2 Trip Zones One Shot Int Enable
    Uint16 DCAEVT1:1;                   // 3 Digital Compare A Event 1 Int Enable
    Uint16 DCAEVT2:1;                   // 4 Digital Compare A Event 2 Int Enable
    Uint16 DCBEVT1:1;                   // 5 Digital Compare B Event 1 Int Enable
    Uint16 DCBEVT2:1;                   // 6 Digital Compare B Event 2 Int Enable
    Uint16 rsvd2:9;                     // 15:7 Reserved
};

union TZEINT_REG {
    Uint16  all;
    struct  TZEINT_BITS  bit;
};

struct TZFLG_BITS {                     // bits description
    Uint16 INT:1;                       // 0 Global Int Status Flag
    Uint16 CBC:1;                       // 1 Trip Zones Cycle By Cycle Flag
    Uint16 OST:1;                       // 2 Trip Zones One Shot Flag
    Uint16 DCAEVT1:1;                   // 3 Digital Compare A Event 1 Flag
    Uint16 DCAEVT2:1;                   // 4 Digital Compare A Event 2 Flag
    Uint16 DCBEVT1:1;                   // 5 Digital Compare B Event 1 Flag
    Uint16 DCBEVT2:1;                   // 6 Digital Compare B Event 2 Flag
    Uint16 rsvd1:9;                     // 15:7 Reserved
};

union TZFLG_REG {
    Uint16  all;
    struct  TZFLG_BITS  bit;
};

struct TZCBCFLG_BITS {                  // bits description
    Uint16 CBC1:1;                      // 0 Latched Status Flag for CBC1 Trip Latch
    Uint16 CBC2:1;                      // 1 Latched Status Flag for CBC2 Trip Latch
    Uint16 CBC3:1;                      // 2 Latched Status Flag for CBC3 Trip Latch
    Uint16 CBC4:1;                      // 3 Latched Status Flag for CBC4 Trip Latch
    Uint16 CBC5:1;                      // 4 Latched Status Flag for CBC5 Trip Latch
    Uint16 CBC6:1;                      // 5 Latched Status Flag for CBC6 Trip Latch
    Uint16 DCAEVT2:1;                   // 6 Latched Status Flag for Digital Compare Output A Event 2
    Uint16 DCBEVT2:1;                   // 7 Latched Status Flag for Digital Compare Output B Event 2
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union TZCBCFLG_REG {
    Uint16  all;
    struct  TZCBCFLG_BITS  bit;
};

struct TZOSTFLG_BITS {                  // bits description
    Uint16 OST1:1;                      // 0 Latched Status Flag for OST1 Trip Latch
    Uint16 OST2:1;                      // 1 Latched Status Flag for OST2 Trip Latch
    Uint16 OST3:1;                      // 2 Latched Status Flag for OST3 Trip Latch
    Uint16 OST4:1;                      // 3 Latched Status Flag for OST4 Trip Latch
    Uint16 OST5:1;                      // 4 Latched Status Flag for OST5 Trip Latch
    Uint16 OST6:1;                      // 5 Latched Status Flag for OST6 Trip Latch
    Uint16 DCAEVT1:1;                   // 6 Latched Status Flag for Digital Compare Output A Event 1
    Uint16 DCBEVT1:1;                   // 7 Latched Status Flag for Digital Compare Output B Event 1
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union TZOSTFLG_REG {
    Uint16  all;
    struct  TZOSTFLG_BITS  bit;
};

struct TZCLR_BITS {                     // bits description
    Uint16 INT:1;                       // 0 Global Interrupt Clear Flag
    Uint16 CBC:1;                       // 1 Cycle-By-Cycle Flag Clear
    Uint16 OST:1;                       // 2 One-Shot Flag Clear
    Uint16 DCAEVT1:1;                   // 3 DCAVET1 Flag Clear
    Uint16 DCAEVT2:1;                   // 4 DCAEVT2 Flag Clear
    Uint16 DCBEVT1:1;                   // 5 DCBEVT1 Flag Clear
    Uint16 DCBEVT2:1;                   // 6 DCBEVT2 Flag Clear
    Uint16 rsvd1:7;                     // 13:7 Reserved
    Uint16 CBCPULSE:2;                  // 15:14 Clear Pulse for CBC Trip Latch
};

union TZCLR_REG {
    Uint16  all;
    struct  TZCLR_BITS  bit;
};

struct TZCBCCLR_BITS {                  // bits description
    Uint16 CBC1:1;                      // 0 Clear Flag for Cycle-By-Cycle (CBC1) Trip Latch
    Uint16 CBC2:1;                      // 1 Clear Flag for Cycle-By-Cycle (CBC2) Trip Latch
    Uint16 CBC3:1;                      // 2 Clear Flag for Cycle-By-Cycle (CBC3) Trip Latch
    Uint16 CBC4:1;                      // 3 Clear Flag for Cycle-By-Cycle (CBC4) Trip Latch
    Uint16 CBC5:1;                      // 4 Clear Flag for Cycle-By-Cycle (CBC5) Trip Latch
    Uint16 CBC6:1;                      // 5 Clear Flag for Cycle-By-Cycle (CBC6) Trip Latch
    Uint16 DCAEVT2:1;                   // 6 Clear Flag forDCAEVT2 selected for CBC
    Uint16 DCBEVT2:1;                   // 7 Clear Flag for DCBEVT2 selected for CBC
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union TZCBCCLR_REG {
    Uint16  all;
    struct  TZCBCCLR_BITS  bit;
};

struct TZOSTCLR_BITS {                  // bits description
    Uint16 OST1:1;                      // 0 Clear Flag for Oneshot (OST1) Trip Latch
    Uint16 OST2:1;                      // 1 Clear Flag for Oneshot (OST2) Trip Latch
    Uint16 OST3:1;                      // 2 Clear Flag for Oneshot (OST3) Trip Latch
    Uint16 OST4:1;                      // 3 Clear Flag for Oneshot (OST4) Trip Latch
    Uint16 OST5:1;                      // 4 Clear Flag for Oneshot (OST5) Trip Latch
    Uint16 OST6:1;                      // 5 Clear Flag for Oneshot (OST6) Trip Latch
    Uint16 DCAEVT1:1;                   // 6 Clear Flag for DCAEVT1 selected for OST
    Uint16 DCBEVT1:1;                   // 7 Clear Flag for DCBEVT1 selected for OST
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union TZOSTCLR_REG {
    Uint16  all;
    struct  TZOSTCLR_BITS  bit;
};

struct TZFRC_BITS {                     // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 CBC:1;                       // 1 Force Trip Zones Cycle By Cycle Event
    Uint16 OST:1;                       // 2 Force Trip Zones One Shot Event
    Uint16 DCAEVT1:1;                   // 3 Force Digital Compare A Event 1
    Uint16 DCAEVT2:1;                   // 4 Force Digital Compare A Event 2
    Uint16 DCBEVT1:1;                   // 5 Force Digital Compare B Event 1
    Uint16 DCBEVT2:1;                   // 6 Force Digital Compare B Event 2
    Uint16 rsvd2:9;                     // 15:7 Reserved
};

union TZFRC_REG {
    Uint16  all;
    struct  TZFRC_BITS  bit;
};

struct ETSEL_BITS {                     // bits description
    Uint16 INTSEL:3;                    // 2:0 PWMxINTn Select
    Uint16 INTEN:1;                     // 3 PWMxINTn Enable
    Uint16 SOCASELCMP:1;                // 4 PWMxSOCA Compare Select
    Uint16 SOCBSELCMP:1;                // 5 PWMxSOCB Compare Select
    Uint16 INTSELCMP:1;                 // 6 PWMxINT Compare Select
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 SOCASEL:3;                   // 10:8 Start of Conversion A Select
    Uint16 SOCAEN:1;                    // 11 Start of Conversion A Enable
    Uint16 SOCBSEL:3;                   // 14:12 Start of Conversion B Select
    Uint16 SOCBEN:1;                    // 15 Start of Conversion B Enable
};

union ETSEL_REG {
    Uint16  all;
    struct  ETSEL_BITS  bit;
};

struct ETPS_BITS {                      // bits description
    Uint16 INTPRD:2;                    // 1:0 PWMxINTn Period Select
    Uint16 INTCNT:2;                    // 3:2 PWMxINTn Counter Register
    Uint16 INTPSSEL:1;                  // 4 PWMxINTn Pre-Scale Selection Bits
    Uint16 SOCPSSEL:1;                  // 5 PWMxSOC A/B  Pre-Scale Selection Bits
    Uint16 rsvd1:2;                     // 7:6 Reserved
    Uint16 SOCAPRD:2;                   // 9:8 PWMxSOCA Period Select
    Uint16 SOCACNT:2;                   // 11:10 PWMxSOCA Counter Register
    Uint16 SOCBPRD:2;                   // 13:12 PWMxSOCB Period Select
    Uint16 SOCBCNT:2;                   // 15:14 PWMxSOCB Counter
};

union ETPS_REG {
    Uint16  all;
    struct  ETPS_BITS  bit;
};

struct ETFLG_BITS {                     // bits description
    Uint16 INT:1;                       // 0 PWMxINTn Flag
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 SOCA:1;                      // 2 PWMxSOCA Flag
    Uint16 SOCB:1;                      // 3 PWMxSOCB Flag
    Uint16 rsvd2:12;                    // 15:4 Reserved
};

union ETFLG_REG {
    Uint16  all;
    struct  ETFLG_BITS  bit;
};

struct ETCLR_BITS {                     // bits description
    Uint16 INT:1;                       // 0 PWMxINTn Clear
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 SOCA:1;                      // 2 PWMxSOCA Clear
    Uint16 SOCB:1;                      // 3 PWMxSOCB Clear
    Uint16 rsvd2:12;                    // 15:4 Reserved
};

union ETCLR_REG {
    Uint16  all;
    struct  ETCLR_BITS  bit;
};

struct ETFRC_BITS {                     // bits description
    Uint16 INT:1;                       // 0 PWMxINTn Force
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 SOCA:1;                      // 2 PWMxSOCA Force
    Uint16 SOCB:1;                      // 3 PWMxSOCB Force
    Uint16 rsvd2:12;                    // 15:4 Reserved
};

union ETFRC_REG {
    Uint16  all;
    struct  ETFRC_BITS  bit;
};

struct ETINTPS_BITS {                   // bits description
    Uint16 INTPRD2:4;                   // 3:0 PWMxINTn Period Select
    Uint16 INTCNT2:4;                   // 7:4 PWMxINTn Counter Register
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union ETINTPS_REG {
    Uint16  all;
    struct  ETINTPS_BITS  bit;
};

struct ETSOCPS_BITS {                   // bits description
    Uint16 SOCAPRD2:4;                  // 3:0 PWMxSOCA Period Select
    Uint16 SOCACNT2:4;                  // 7:4 PWMxSOCA Counter Register
    Uint16 SOCBPRD2:4;                  // 11:8 PWMxSOCB Period Select
    Uint16 SOCBCNT2:4;                  // 15:12 PWMxSOCB Counter Register
};

union ETSOCPS_REG {
    Uint16  all;
    struct  ETSOCPS_BITS  bit;
};

struct ETCNTINITCTL_BITS {              // bits description
    Uint16 rsvd1:10;                    // 9:0 Reserved
    Uint16 INTINITFRC:1;                // 10 PWMxINT Counter Initialization Force
    Uint16 SOCAINITFRC:1;               // 11 PWMxSOCA Counter Initialization Force
    Uint16 SOCBINITFRC:1;               // 12 PWMxSOCB Counter Initialization Force
    Uint16 INTINITEN:1;                 // 13 PWMxINT Counter Initialization Enable
    Uint16 SOCAINITEN:1;                // 14 PWMxSOCA Counter Initialization Enable
    Uint16 SOCBINITEN:1;                // 15 PWMxSOCB Counter Initialization Enable
};

union ETCNTINITCTL_REG {
    Uint16  all;
    struct  ETCNTINITCTL_BITS  bit;
};

struct ETCNTINIT_BITS {                 // bits description
    Uint16 INTINIT:4;                   // 3:0 PWMxINT Counter Initialization Bits
    Uint16 SOCAINIT:4;                  // 7:4 PWMxSOCA Counter Initialization Bits
    Uint16 SOCBINIT:4;                  // 11:8 PWMxSOCB Counter Initialization Bits
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ETCNTINIT_REG {
    Uint16  all;
    struct  ETCNTINIT_BITS  bit;
};

struct DCTRIPSEL_BITS {                 // bits description
    Uint16 DCAHCOMPSEL:4;               // 3:0 Digital Compare A High COMP Input Select
    Uint16 DCALCOMPSEL:4;               // 7:4 Digital Compare A Low COMP Input Select
    Uint16 DCBHCOMPSEL:4;               // 11:8 Digital Compare B High COMP Input Select
    Uint16 DCBLCOMPSEL:4;               // 15:12 Digital Compare B Low COMP Input Select
};

union DCTRIPSEL_REG {
    Uint16  all;
    struct  DCTRIPSEL_BITS  bit;
};

struct DCACTL_BITS {                    // bits description
    Uint16 EVT1SRCSEL:1;                // 0 DCAEVT1 Source Signal
    Uint16 EVT1FRCSYNCSEL:1;            // 1 DCAEVT1 Force Sync Signal
    Uint16 EVT1SOCE:1;                  // 2 DCAEVT1 SOC Enable
    Uint16 EVT1SYNCE:1;                 // 3 DCAEVT1 SYNC Enable
    Uint16 rsvd1:4;                     // 7:4 Reserved
    Uint16 EVT2SRCSEL:1;                // 8 DCAEVT2 Source Signal
    Uint16 EVT2FRCSYNCSEL:1;            // 9 DCAEVT2 Force Sync Signal
    Uint16 rsvd2:6;                     // 15:10 Reserved
};

union DCACTL_REG {
    Uint16  all;
    struct  DCACTL_BITS  bit;
};

struct DCBCTL_BITS {                    // bits description
    Uint16 EVT1SRCSEL:1;                // 0 DCBEVT1 Source Signal
    Uint16 EVT1FRCSYNCSEL:1;            // 1 DCBEVT1 Force Sync Signal
    Uint16 EVT1SOCE:1;                  // 2 DCBEVT1 SOC Enable
    Uint16 EVT1SYNCE:1;                 // 3 DCBEVT1 SYNC Enable
    Uint16 rsvd1:4;                     // 7:4 Reserved
    Uint16 EVT2SRCSEL:1;                // 8 DCBEVT2 Source Signal
    Uint16 EVT2FRCSYNCSEL:1;            // 9 DCBEVT2 Force Sync Signal
    Uint16 rsvd2:6;                     // 15:10 Reserved
};

union DCBCTL_REG {
    Uint16  all;
    struct  DCBCTL_BITS  bit;
};

struct DCFCTL_BITS {                    // bits description
    Uint16 SRCSEL:2;                    // 1:0 Filter Block Signal Source Select
    Uint16 BLANKE:1;                    // 2 Blanking Enable/Disable
    Uint16 BLANKINV:1;                  // 3 Blanking Window Inversion
    Uint16 PULSESEL:2;                  // 5:4 Pulse Select for Blanking & Capture Alignment
    Uint16 EDGEFILTSEL:1;               // 6 Edge Filter Select
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 EDGEMODE:2;                  // 9:8 Edge Mode
    Uint16 EDGECOUNT:3;                 // 12:10 Edge Count
    Uint16 EDGESTATUS:3;                // 15:13 Edge Status
};

union DCFCTL_REG {
    Uint16  all;
    struct  DCFCTL_BITS  bit;
};

struct DCCAPCTL_BITS {                  // bits description
    Uint16 CAPE:1;                      // 0 Counter Capture Enable
    Uint16 SHDWMODE:1;                  // 1 Counter Capture Mode
    Uint16 rsvd1:11;                    // 12:2 Reserved
    Uint16 CAPSTS:1;                    // 13 Latched Status Flag for Capture Event
    Uint16 CAPCLR:1;                    // 14 DC Capture Latched Status Clear Flag
    Uint16 CAPMODE:1;                   // 15 Counter Capture Mode
};

union DCCAPCTL_REG {
    Uint16  all;
    struct  DCCAPCTL_BITS  bit;
};

struct DCAHTRIPSEL_BITS {               // bits description
    Uint16 TRIPINPUT1:1;                // 0 Trip Input 1 Select to DCAH Mux
    Uint16 TRIPINPUT2:1;                // 1 Trip Input 2 Select to DCAH Mux
    Uint16 TRIPINPUT3:1;                // 2 Trip Input 3 Select to DCAH Mux
    Uint16 TRIPINPUT4:1;                // 3 Trip Input 4 Select to DCAH Mux
    Uint16 TRIPINPUT5:1;                // 4 Trip Input 5 Select to DCAH Mux
    Uint16 TRIPINPUT6:1;                // 5 Trip Input 6 Select to DCAH Mux
    Uint16 TRIPINPUT7:1;                // 6 Trip Input 7 Select to DCAH Mux
    Uint16 TRIPINPUT8:1;                // 7 Trip Input 8 Select to DCAH Mux
    Uint16 TRIPINPUT9:1;                // 8 Trip Input 9 Select to DCAH Mux
    Uint16 TRIPINPUT10:1;               // 9 Trip Input 10 Select to DCAH Mux
    Uint16 TRIPINPUT11:1;               // 10 Trip Input 11 Select to DCAH Mux
    Uint16 TRIPINPUT12:1;               // 11 Trip Input 12 Select to DCAH Mux
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 TRIPINPUT14:1;               // 13 Trip Input 14 Select to DCAH Mux
    Uint16 TRIPINPUT15:1;               // 14 Trip Input 15 Select to DCAH Mux
    Uint16 rsvd2:1;                     // 15 Reserved
};

union DCAHTRIPSEL_REG {
    Uint16  all;
    struct  DCAHTRIPSEL_BITS  bit;
};

struct DCALTRIPSEL_BITS {               // bits description
    Uint16 TRIPINPUT1:1;                // 0 Trip Input 1 Select to DCAL Mux
    Uint16 TRIPINPUT2:1;                // 1 Trip Input 2 Select to DCAL Mux
    Uint16 TRIPINPUT3:1;                // 2 Trip Input 3 Select to DCAL Mux
    Uint16 TRIPINPUT4:1;                // 3 Trip Input 4 Select to DCAL Mux
    Uint16 TRIPINPUT5:1;                // 4 Trip Input 5 Select to DCAL Mux
    Uint16 TRIPINPUT6:1;                // 5 Trip Input 6 Select to DCAL Mux
    Uint16 TRIPINPUT7:1;                // 6 Trip Input 7 Select to DCAL Mux
    Uint16 TRIPINPUT8:1;                // 7 Trip Input 8 Select to DCAL Mux
    Uint16 TRIPINPUT9:1;                // 8 Trip Input 9 Select to DCAL Mux
    Uint16 TRIPINPUT10:1;               // 9 Trip Input 10 Select to DCAL Mux
    Uint16 TRIPINPUT11:1;               // 10 Trip Input 11 Select to DCAL Mux
    Uint16 TRIPINPUT12:1;               // 11 Trip Input 12 Select to DCAL Mux
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 TRIPINPUT14:1;               // 13 Trip Input 14 Select to DCAL Mux
    Uint16 TRIPINPUT15:1;               // 14 Trip Input 15 Select to DCAL Mux
    Uint16 rsvd2:1;                     // 15 Reserved
};

union DCALTRIPSEL_REG {
    Uint16  all;
    struct  DCALTRIPSEL_BITS  bit;
};

struct DCBHTRIPSEL_BITS {               // bits description
    Uint16 TRIPINPUT1:1;                // 0 Trip Input 1 Select to DCBH Mux
    Uint16 TRIPINPUT2:1;                // 1 Trip Input 2 Select to DCBH Mux
    Uint16 TRIPINPUT3:1;                // 2 Trip Input 3 Select to DCBH Mux
    Uint16 TRIPINPUT4:1;                // 3 Trip Input 4 Select to DCBH Mux
    Uint16 TRIPINPUT5:1;                // 4 Trip Input 5 Select to DCBH Mux
    Uint16 TRIPINPUT6:1;                // 5 Trip Input 6 Select to DCBH Mux
    Uint16 TRIPINPUT7:1;                // 6 Trip Input 7 Select to DCBH Mux
    Uint16 TRIPINPUT8:1;                // 7 Trip Input 8 Select to DCBH Mux
    Uint16 TRIPINPUT9:1;                // 8 Trip Input 9 Select to DCBH Mux
    Uint16 TRIPINPUT10:1;               // 9 Trip Input 10 Select to DCBH Mux
    Uint16 TRIPINPUT11:1;               // 10 Trip Input 11 Select to DCBH Mux
    Uint16 TRIPINPUT12:1;               // 11 Trip Input 12 Select to DCBH Mux
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 TRIPINPUT14:1;               // 13 Trip Input 14 Select to DCBH Mux
    Uint16 TRIPINPUT15:1;               // 14 Trip Input 15 Select to DCBH Mux
    Uint16 rsvd2:1;                     // 15 Reserved
};

union DCBHTRIPSEL_REG {
    Uint16  all;
    struct  DCBHTRIPSEL_BITS  bit;
};

struct DCBLTRIPSEL_BITS {               // bits description
    Uint16 TRIPINPUT1:1;                // 0 Trip Input 1 Select to DCBL Mux
    Uint16 TRIPINPUT2:1;                // 1 Trip Input 2 Select to DCBL Mux
    Uint16 TRIPINPUT3:1;                // 2 Trip Input 3 Select to DCBL Mux
    Uint16 TRIPINPUT4:1;                // 3 Trip Input 4 Select to DCBL Mux
    Uint16 TRIPINPUT5:1;                // 4 Trip Input 5 Select to DCBL Mux
    Uint16 TRIPINPUT6:1;                // 5 Trip Input 6 Select to DCBL Mux
    Uint16 TRIPINPUT7:1;                // 6 Trip Input 7 Select to DCBL Mux
    Uint16 TRIPINPUT8:1;                // 7 Trip Input 8 Select to DCBL Mux
    Uint16 TRIPINPUT9:1;                // 8 Trip Input 9 Select to DCBL Mux
    Uint16 TRIPINPUT10:1;               // 9 Trip Input 10 Select to DCBL Mux
    Uint16 TRIPINPUT11:1;               // 10 Trip Input 11 Select to DCBL Mux
    Uint16 TRIPINPUT12:1;               // 11 Trip Input 12 Select to DCBL Mux
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 TRIPINPUT14:1;               // 13 Trip Input 14 Select to DCBL Mux
    Uint16 TRIPINPUT15:1;               // 14 Trip Input 15 Select to DCBL Mux
    Uint16 rsvd2:1;                     // 15 Reserved
};

union DCBLTRIPSEL_REG {
    Uint16  all;
    struct  DCBLTRIPSEL_BITS  bit;
};

struct PWMLOCK_BITS {                  // bits description
    Uint32 HRLOCK:1;                    // 0 HRPWM Register Set Lock
    Uint32 GLLOCK:1;                    // 1 Global Load Register Set Lock
    Uint32 TZCFGLOCK:1;                 // 2 TripZone Register Set Lock
    Uint32 TZCLRLOCK:1;                 // 3 TripZone Clear Register Set Lock
    Uint32 DCLOCK:1;                    // 4 Digital Compare Register Set Lock
    Uint32 rsvd1:11;                    // 15:5 Reserved
    Uint32 KEY:16;                      // 31:16 Key to write to this register
};

union PWMLOCK_REG {
    Uint32  all;
    struct  PWMLOCK_BITS  bit;
};

struct PWM_REGS {
    union   TBCTL_REG                        TBCTL;                        // 0x00 Time Base Control Register
    union   TBCTL2_REG                       TBCTL2;                       // 0x02 Time Base Control Register 2
    Uint16                                   rsvd1[2];                     // 0x04 Reserved
    Uint16                                   TBCTR;                        // 0x08 Time Base Counter Register
    union   TBSTS_REG                        TBSTS;                        // 0x0A Time Base Status Register
    Uint16                                   rsvd2[2];                     // 0x0C Reserved
    union   CMPCTL_REG                       CMPCTL;                       // 0x10 Counter Compare Control Register
    union   CMPCTL2_REG                      CMPCTL2;                      // 0x12 Counter Compare Control Register 2
    Uint16                                   rsvd3[2];                     // 0x14 Reserved
    union   DBCTL_REG                        DBCTL;                        // 0x18 Dead-Band Generator Control Register
    union   DBCTL2_REG                       DBCTL2;                       // 0x1A Dead-Band Generator Control Register 2
    Uint16                                   rsvd4[2];                     // 0x1C Reserved
    union   AQCTL_REG                        AQCTL;                        // 0x20 Action Qualifier Control Register
    union   AQTSRCSEL_REG                    AQTSRCSEL;                    // 0x22 Action Qualifier Trigger Event Source Select Register
    Uint16                                   rsvd5[2];                     // 0x24 Reserved
    union   PCCTL_REG                        PCCTL;                        // 0x28 PWM Chopper Control Register
    Uint16                                   rsvd6[3];                     // 0x2A Reserved
    union   VCAPCTL_REG                      VCAPCTL;                      // 0x30 Valley Capture Control Register
    union   VCNTCFG_REG                      VCNTCFG;                      // 0x32 Valley Counter Config Register
    Uint16                                   rsvd7[6];                     // 0x34 Reserved
    union   HRCNFG_REG                       HRCNFG;                       // 0x40 HRPWM Configuration Register
    union   HRPWR_REG                        HRPWR;                        // 0x42 HRPWM Power Register
    Uint16                                   rsvd8[4];                     // 0x44 Reserved
    union   HRMSTEP_REG                      HRMSTEP;                      // 0x4C HRPWM MEP Step Register
    union   HRCNFG2_REG                      HRCNFG2;                      // 0x4E HRPWM Configuration 2 Register
    Uint16                                   rsvd9[5];                     // 0x50 Reserved
    union   HRPCTL_REG                       HRPCTL;                       // 0x5A High Resolution Period Control Register
    union   TRREM_REG                        TRREM;                        // 0x5CHRPWM High Resolution Remainder Register
    Uint16                                   rsvd10[5];                    // 0x5E Reserved
    union   GLDCTL_REG                       GLDCTL;                       // 0x68 Global PWM Load Control Register
    union   GLDCFG_REG                       GLDCFG;                       // 0x6A Global PWM Load Config Register
    Uint16                                   rsvd11[2];                    // 0x6C Reserved
    union   PWMXLINK_REG                    PWMXLINK;                    // 0x70 PWMx Link Register
    Uint16                                   rsvd12[6];                    // 0x74 Reserved
    union   AQCTLA_REG                       AQCTLA;                       // 0x80 Action Qualifier Control Register For Output A
    union   AQCTLA2_REG                      AQCTLA2;                      // 0x82 Additional Action Qualifier Control Register For Output A
    union   AQCTLB_REG                       AQCTLB;                       // 0x84 Action Qualifier Control Register For Output B
    union   AQCTLB2_REG                      AQCTLB2;                      // 0x86 Additional Action Qualifier Control Register For Output B
    Uint16                                   rsvd13[3];                    // 0x88 Reserved
    union   AQSFRC_REG                       AQSFRC;                       // 0x8E Action Qualifier Software Force Register
    Uint16                                   rsvd14;                       // 0x90 Reserved
    union   AQCSFRC_REG                      AQCSFRC;                      // 0x92 Action Qualifier Continuous S/W Force Register
    Uint16                                   rsvd15[6];                    // 0x94 Reserved
    union   DBREDHR_REG                      DBREDHR;                      // 0xA0 Dead-Band Generator Rising Edge Delay High Resolution Mirror Register
    union   DBRED_REG                        DBRED;                        // 0xA2 Dead-Band Generator Rising Edge Delay High Resolution Mirror Register
    union   DBFEDHR_REG                      DBFEDHR;                      // 0xA4 Dead-Band Generator Falling Edge Delay High Resolution Register
    union   DBFED_REG                        DBFED;                        // 0xA6 Dead-Band Generator Falling Edge Delay Count Register
    Uint16                                   rsvd16[12];                   // 0xA8 Reserved
    union   TBPHS_REG                        TBPHS;                        // 0xC0 Time Base Phase High
    Uint16                                   TBPRDHR;                      // 0xC4 Time Base Period High Resolution Register
    Uint16                                   TBPRD;                        // 0xC6 Time Base Period Register
    Uint16                                   rsvd17[6];                    // 0xC8 Reserved
    union   CMPA_REG                         CMPA;                         // 0xD4 Counter Compare A Register
    union   CMPB_REG                         CMPB;                         // 0xD8Compare B Register
    Uint16                                   rsvd18;                       // 0xDC Reserved
    Uint16                                   CMPC;                         // 0xDE Counter Compare C Register
    Uint16                                   rsvd19;                       // 0xE0 Reserved
    Uint16                                   CMPD;                         // 0xE2 Counter Compare D Register
    Uint16                                   rsvd20[2];                    // 0xE4 Reserved
    union   GLDCTL2_REG                      GLDCTL2;                      // 0xE8 Global PWM Load Control Register 2
    Uint16                                   rsvd21[2];                    // 0xEA Reserved
    Uint16                                   SWVDELVAL;                    // 0xEE Software Valley Mode Delay Register
    Uint16                                   rsvd22[8];                    // 0xF0 Reserved
    union   TZSEL_REG                        TZSEL;                        // 0x100 Trip Zone Select Register
    Uint16                                   rsvd23;                       // 0x102 Reserved
    union   TZDCSEL_REG                      TZDCSEL;                      // 0x104Trip Zone Digital Comparator Select Register
    Uint16                                   rsvd24;                       // 0x106 Reserved
    union   TZCTL_REG                        TZCTL;                        // 0x108 Trip Zone Control Register
    union   TZCTL2_REG                       TZCTL2;                       // 0x10A Additional Trip Zone Control Register
    union   TZCTLDCA_REG                     TZCTLDCA;                     // 0x10C Trip Zone Control Register Digital Compare A
    union   TZCTLDCB_REG                     TZCTLDCB;                     // 0x10E Trip Zone Control Register Digital Compare B
    Uint16                                   rsvd25[5];                    // 0x110 Reserved
    union   TZEINT_REG                       TZEINT;                       // 0x11A Trip Zone Enable Interrupt Register
    Uint16                                   rsvd26[5];                    // 0x11C Reserved
    union   TZFLG_REG                        TZFLG;                        // 0x126 Trip Zone Flag Register
    union   TZCBCFLG_REG                     TZCBCFLG;                     // 0x128 Trip Zone CBC Flag Register
    union   TZOSTFLG_REG                     TZOSTFLG;                     // 0x12A Trip Zone OST Flag Register
    Uint16                                   rsvd27;                       // 0x12C Reserved
    union   TZCLR_REG                        TZCLR;                        // 0x12E Trip Zone Clear Register
    union   TZCBCCLR_REG                     TZCBCCLR;                     // 0x130 Trip Zone CBC Clear Register
    union   TZOSTCLR_REG                     TZOSTCLR;                     // 0x132 Trip Zone OST Clear Register
    Uint16                                   rsvd28;                       // 0x134 Reserved
    union   TZFRC_REG                        TZFRC;                        // 0x136 Trip Zone Force Register
    Uint16                                   rsvd29[8];                    // 0x138 Reserved
    union   ETSEL_REG                        ETSEL;                        // 0x148 Event Trigger Selection Register
    Uint16                                   rsvd30;                       // 0x14A Reserved
    union   ETPS_REG                         ETPS;                         // 0x14C Event Trigger Pre-Scale Register
    Uint16                                   rsvd31;                       // 0x14E Reserved
    union   ETFLG_REG                        ETFLG;                        // 0x150 Event Trigger Flag Register
    Uint16                                   rsvd32;                       // 0x152 Reserved
    union   ETCLR_REG                        ETCLR;                        // 0x154 Event Trigger Clear Register
    Uint16                                   rsvd33;                       // 0x156 Reserved
    union   ETFRC_REG                        ETFRC;                        // 0x158 Event Trigger Force Register
    Uint16                                   rsvd34;                       // 0x15A Reserved
    union   ETINTPS_REG                      ETINTPS;                      // 0x15C Event-Trigger Interrupt Pre-Scale Register
    Uint16                                   rsvd35;                       // 0x15E Reserved
    union   ETSOCPS_REG                      ETSOCPS;                      // 0x160 Event-Trigger SOC Pre-Scale Register
    Uint16                                   rsvd36;                       // 0x162 Reserved
    union   ETCNTINITCTL_REG                 ETCNTINITCTL;                 // 0x164 Event-Trigger Counter Initialization Control Register
    Uint16                                   rsvd37;                       // 0x166 Reserved
    union   ETCNTINIT_REG                    ETCNTINIT;                    // 0x168 Event-Trigger Counter Initialization Register
    Uint16                                   rsvd38[11];                   // 0x16A Reserved
    union   DCTRIPSEL_REG                    DCTRIPSEL;                    // 0x180 Digital Compare Trip Select Register
    Uint16                                   rsvd39[2];                    // 0x182 Reserved
    union   DCACTL_REG                       DCACTL;                       // 0x186 Digital Compare A Control Register
    union   DCBCTL_REG                       DCBCTL;                       // 0x188 Digital Compare B Control Register
    Uint16                                   rsvd40[2];                    // 0x18A Reserved
    union   DCFCTL_REG                       DCFCTL;                       // 0x18E Digital Compare Filter Control Register
    union   DCCAPCTL_REG                     DCCAPCTL;                     // 0x190 Digital Compare Capture Control Register
    Uint16                                   DCFOFFSET;                    // 0x192 Digital Compare Filter Offset Register
    Uint16                                   DCFOFFSETCNT;                 // 0x194 Digital Compare Filter Offset Counter Register
    Uint16                                   DCFWINDOW;                    // 0x196 Digital Compare Filter Window Register
    Uint16                                   DCFWINDOWCNT;                 // 0x198 Digital Compare Filter Window Counter Register
    Uint16                                   rsvd41[2];                    // 0x19A Reserved
    Uint16                                   DCCAP;                        // 0x19E Digital Compare Counter Capture Register
    Uint16                                   rsvd42[2];                    // 0x1A0 Reserved
    union   DCAHTRIPSEL_REG                  DCAHTRIPSEL;                  // 0x1A4 Digital Compare AH Trip Select
    union   DCALTRIPSEL_REG                  DCALTRIPSEL;                  // 0x1A6 Digital Compare AL Trip Select
    union   DCBHTRIPSEL_REG                  DCBHTRIPSEL;                  // 0x1A8 Digital Compare BH Trip Select
    union   DCBLTRIPSEL_REG                  DCBLTRIPSEL;                  // 0x1AA Digital Compare BL Trip Select
    Uint16                                   rsvd43[36];                   // 0x1AC Reserved
    union   PWMLOCK_REG                     PWMLOCK;                       // 0x1F4 PWM Lock Register
    Uint16                                   rsvd44;                       // 0x1F8 Reserved
    Uint16                                   HWVDELVAL;                    // 0x1FA Hardware Valley Mode Delay Register
    Uint16                                   VCNTVAL;                      // 0x1FC Hardware Valley Counter Register
};

//---------------------------------------------------------------------------
// PWM External References & Function Declarations:
//
extern volatile struct PWM_REGS Pwm1Regs;
extern volatile struct PWM_REGS Pwm2Regs;
extern volatile struct PWM_REGS Pwm3Regs;
extern volatile struct PWM_REGS Pwm4Regs;
extern volatile struct PWM_REGS Pwm5Regs;
extern volatile struct PWM_REGS Pwm6Regs;
extern volatile struct PWM_REGS Pwm7Regs;
extern volatile struct PWM_REGS Pwm8Regs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
