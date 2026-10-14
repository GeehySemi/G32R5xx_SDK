//###########################################################################
//
// FILE:    g32r502_canfd.h
//
// TITLE:   Definitions for the CANFD registers.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//###########################################################################
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
//
// You may not use this file except in compliance with the
// GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
//
// The program is only for reference, which is distributed in the hope
// that it will be useful and instructional for customers to develop
// their software. Unless required by applicable law or agreed to in
// writing, the program is distributed on an "AS IS" BASIS, WITHOUT
// ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
// See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
// and limitations under the License.
// $
//###########################################################################

#ifndef G32R502_CANFD_H
#define G32R502_CANFD_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// CANFD Individual Register Bit Definitions:

struct CREL_BITS {                   // bits description
    Uint32 DAY       : 8;            // [7..0] Time Stamp Day
    Uint32 MON       : 8;            // [15..8] Time Stamp Month
    Uint32 YEAR      : 4;            // [19..16] Year
    Uint32 SUBSTEP   : 4;            // [23..20] Sub-step of Core Release
    Uint32 STEP      : 4;            // [27..24] Step of Core Release
    Uint32 REL       : 4;            // [31..28] Core Release
};

union CREL_REG {
    Uint32        all;
    struct CREL_BITS bit;
};

struct ENDN_BITS {                   // bits description
    Uint32 ETV       : 32;           // [31..0] Endianness Test Value
};

union ENDN_REG {
    Uint32       all;
    struct ENDN_BITS bit;
};

struct DBTP_BITS {                   // bits description
    Uint32 DSJW      : 4;            // [3..0] Data (Re)Synchronization Jump Width
    Uint32 DTSEG2    : 4;            // [7..4] Data time segment after sample point
    Uint32 DTSEG1    : 5;            // [12..8] Data time segment before sample point
    Uint32 rsvd1     : 3;            // [15..13] Reserved
    Uint32 DBRP      : 5;            // [20..16] Data Bit Rate Prescaler
    Uint32 rsvd2     : 2;            // [22..21] Reserved
    Uint32 TDC       : 1;            // [23..23] Transmitter Delay Compensation
    Uint32 rsvd3     : 8;            // [31..24] Reserved
};

union DBTP_REG {
    Uint32        all;
    struct DBTP_BITS bit;
};

struct TEST_BITS {                   // bits description
    Uint32 rsvd1     : 4;            // [3..0] Reserved
    Uint32 LBCK      : 1;            // [4..4] Loop Back Mode
    Uint32 TX        : 2;            // [6..5] Control of Transmit Pin
    Uint32 RX        : 1;            // [7..7] Receive Pin
    Uint32 TXBNP     : 5;            // [12..8] Tx Buffer Number Prepared
    Uint32 PVAL      : 1;            // [13..13] Prepared Valid
    Uint32 rsvd2     : 2;            // [15..14] Reserved
    Uint32 TXBNS     : 5;            // [20..16] Tx Buffer Number Started
    Uint32 SVAL      : 1;            // [21..21] Started Valid
    Uint32 rsvd3     : 10;           // [31..22] Reserved
};

union TEST_REG {
    Uint32        all;
    struct TEST_BITS bit;
};

struct RWD_BITS {                    // bits description
    Uint32 WDC       : 8;            // [7..0] Watchdog Configuration
    Uint32 WDV       : 8;            // [15..8] Watchdog Value
    Uint32 rsvd      : 16;           // [31..16] Reserved
};

union RWD_REG {
    Uint32       all;
    struct RWD_BITS bit;
};

struct CCCR_BITS {                   // bits description
    Uint32 INIT      : 1;            // [0..0] Initialization
    Uint32 CCE       : 1;            // [1..1] Configuration Change Enable
    Uint32 ASM       : 1;            // [2..2] Restricted Operation Mode
    Uint32 CSA       : 1;            // [3..3] Clock Stop Acknowledge
    Uint32 CSR       : 1;            // [4..4] Clock Stop Request
    Uint32 MON       : 1;            // [5..5] Bus Monitoring Mode
    Uint32 DAR       : 1;            // [6..6] Disable Automatic Retransmission
    Uint32 TEST      : 1;            // [7..7] Test Mode Enable
    Uint32 FDOE      : 1;            // [8..8] FD Operation Enable
    Uint32 BRSE      : 1;            // [9..9] Bit Rate Switch Enable
    Uint32 rsvd1     : 1;            // [10..10] Reserved
    Uint32 WMM       : 1;            // [11..11] Wide Message Marker
    Uint32 PXHD      : 1;            // [12..12] Protocol Exception Handling Disable
    Uint32 EFBI      : 1;            // [13..13] Edge Filtering during Bus Integration
    Uint32 TXP       : 1;            // [14..14] Transmit Pause
    Uint32 NISO      : 1;            // [15..15] Non ISO Operation
    Uint32 rsvd2     : 16;           // [31..16] Reserved
};

union CCCR_REG {
    Uint32        all;
    struct CCCR_BITS bit;
};

struct NBTP_BITS {                   // bits description
    Uint32 NTSEG2    : 7;            // [6..0] Nominal Time segment after sample point
    Uint32 rsvd1     : 1;            // [7..7] Reserved
    Uint32 NTSEG1    : 8;            // [15..8] Nominal Time segment before sample point
    Uint32 NBRP      : 9;            // [24..16] Nominal Bit Rate Prescaler
    Uint32 NSJW      : 7;            // [31..25] Nominal (Re)Synchronization Jump Width
};

union NBTP_REG {
    Uint32        all;
    struct NBTP_BITS bit;
};

struct TSCC_BITS {                   // bits description
    Uint32 rsvd1  :16;               // [15..0] Reserved
    Uint32 TCP :4;                   // [19..16] Timestamp Counter Prescaler
    Uint32 rsvd2 :12;                // [31..20] Reserved
};

union TSCC_REG {
    Uint32     all;
    struct TSCC_BITS   bit;
};

struct TSCV_BITS {                      // bits description
    Uint32 TSC :16;                     // [15..0] Timestamp Counter
    Uint32 rsvd1 :16;                   // [31..16] Reserved
};

union TSCV_REG {
    Uint32     all;
    struct TSCV_BITS   bit;
};

struct TOCC_BITS {              // bits description
    Uint32 ETOC :1;             // [0..0] Enable Timeout Counter
    Uint32 TOS  :2;             // [2..1] Timeout Select
    Uint32 rsvd1 :13;          // [15..3] Reserved
    Uint32 TOP  :16;           // [31..16] Timeout Period
};

union TOCC_REG {
    Uint32     all;
    struct TOCC_BITS   bit;
};

struct TOCV_BITS {                  // bits description
    Uint32 TOC :16;                 // [15..0] Timeout Counter
    Uint32 rsvd1 :16;               // [31..16] Reserved
};

union TOCV_REG {
    Uint32     all;
    struct TOCV_BITS  bit;
};

struct ECR_BITS {                   // bits description
    Uint32 TEC :8;                  // [7..0] Transmit Error Counter
    Uint32 REC :7;                  // [14..8] Receive Error Counter
    Uint32 RP  :1;                  // [15..15] Receive Error Passive
    Uint32 CEL :8;                  // [23..16] CAN Error Logging
    Uint32 rsvd1 :8;                // [31..24] Reserved
};

union ECR_REG {
    Uint32    all;
    struct ECR_BITS   bit;
};

struct PSR_BITS {              // bits description
    Uint32 LEC  :3;            // [2..0] Last Error Code
    Uint32 ACT  :2;            // [4..3] Activity
    Uint32 EP   :1;            // [5..5] Error Passive
    Uint32 EW   :1;            // [6..6] Warning Status
    Uint32 BO   :1;            // [7..7] Bus_Off Status
    Uint32 DLEC :3;            // [10..8] Data Phase Last Error Code
    Uint32 RESI :1;            // [11..11] ESI flag of last received CAN FD Message
    Uint32 RBRS :1;            // [12..12] BRS flag of last received CAN FD Message
    Uint32 RFDF :1;            // [13..13] Received a CAN FD Message
    Uint32 PXE  :1;            // [14..14] Protocol Exception Event
    Uint32 rsvd1 :1;           // [15..15] Reserved
    Uint32 TDCV :7;            // [22..16] Transmitter Delay Compensation Value
    Uint32 rsvd2 :9;           // [31..23] Reserved
};

union PSR_REG {
    Uint32    all;
    struct PSR_BITS   bit;
};

struct TDCR_BITS {              // bits description
    Uint32 TDCF :7;             // [6..0] TDC Filter Window
    Uint32 rsvd1 :1;            // [7..7] Reserved
    Uint32 TDCO :7;             // [14..8] TDC SSP Offset
    Uint32 rsvd2 :17;           // [31..15] Reserved
};

union TDCR_REG {
    Uint32     all;
    struct TDCR_BITS   bit;
};

struct IR_BITS {               // bits description
    Uint32 RF0N :1;            // [0..0] Rx FIFO 0 New Message
    Uint32 RF0W :1;            // [1..1] Rx FIFO 0 Watermark Reached
    Uint32 RF0F :1;            // [2..2] Rx FIFO 0 Full
    Uint32 RF0L :1;            // [3..3] Rx FIFO 0 Message Lost
    Uint32 RF1N :1;            // [4..4] Rx FIFO 1 New Message
    Uint32 RF1W :1;            // [5..5] Rx FIFO 1 Watermark Reached
    Uint32 RF1F :1;            // [6..6] Rx FIFO 1 Full
    Uint32 RF1L :1;            // [7..7] Rx FIFO 1 Message Lost
    Uint32 HPM  :1;            // [8..8] High Priority Message
    Uint32 TC   :1;            // [9..9] Transmission Completed
    Uint32 TCF  :1;            // [10..10] Transmission Cancellation Finished
    Uint32 TFE  :1;            // [11..11] Tx FIFO Empty
    Uint32 TEFN :1;            // [12..12] Tx Event FIFO New Entry
    Uint32 TEFW :1;            // [13..13] Tx Event FIFO Watermark Reached
    Uint32 TEFF :1;            // [14..14] Tx Event FIFO Full
    Uint32 TEFL :1;            // [15..15] Tx Event FIFO Element Lost
    Uint32 TSW  :1;            // [16..16] Timestamp Wraparound
    Uint32 MRAF :1;            // [17..17] Message RAM Access Failure
    Uint32 TOO  :1;            // [18..18] Timeout Occurred
    Uint32 DRX  :1;            // [19..19] Message stored to Dedicated Rx Buffer
    Uint32 rsvd1 :2;           // [21..20] Reserved
    Uint32 ELO  :1;            // [22..22] Error Logging Overflow
    Uint32 EP   :1;            // [23..23] Error Passive
    Uint32 EW   :1;            // [24..24] Warning Status
    Uint32 BO   :1;            // [25..25] Bus_Off Status
    Uint32 WDI  :1;            // [26..26] Watchdog Interrupt
    Uint32 PEA  :1;            // [27..27] Protocol Error in Arbitration Phase
    Uint32 PED  :1;            // [28..28] Protocol Error in Data Phase
    Uint32 ARA  :1;            // [29..29] Access to Reserved Address
    Uint32 rsvd2 :2;           // [31..30] Reserved
};

union IR_REG {
    Uint32   all;
    struct IR_BITS   bit;
};

struct IE_BITS {               // bits description
    Uint32 RF0NE :1;           // [0..0] Rx FIFO 0 New Message IE
    Uint32 RF0WE :1;           // [1..1] Rx FIFO 0 Watermark IE
    Uint32 RF0FE :1;           // [2..2] Rx FIFO 0 Full IE
    Uint32 RF0LE :1;           // [3..3] Rx FIFO 0 Message Lost IE
    Uint32 RF1NE :1;           // [4..4] Rx FIFO 1 New Message IE
    Uint32 RF1WE :1;           // [5..5] Rx FIFO 1 Watermark IE
    Uint32 RF1FE :1;           // [6..6] Rx FIFO 1 Full IE
    Uint32 RF1LE :1;           // [7..7] Rx FIFO 1 Message Lost IE
    Uint32 HPME  :1;           // [8..8] High Priority Message IE
    Uint32 TCE   :1;           // [9..9] Transmission Completed IE
    Uint32 TCFE  :1;           // [10..10] Transmission Cancellation Finished IE
    Uint32 TFEE  :1;           // [11..11] Tx FIFO Empty IE
    Uint32 TEFNE :1;           // [12..12] Tx Event FIFO New Entry IE
    Uint32 TEFWE :1;           // [13..13] Tx Event FIFO Watermark IE
    Uint32 TEFFE :1;           // [14..14] Tx Event FIFO Full IE
    Uint32 TEFLE :1;           // [15..15] Tx Event FIFO Event Lost IE
    Uint32 TSWE  :1;           // [16..16] Timestamp Wraparound IE
    Uint32 MRAFE :1;           // [17..17] Message RAM Access Failure IE
    Uint32 TOOE  :1;           // [18..18] Timeout Occurred IE
    Uint32 DRXE  :1;           // [19..19] Dedicated Rx Buffer IE
    Uint32 rsvd1 :2;           // [21..20] Reserved
    Uint32 ELOE  :1;           // [22..22] Error Logging Overflow IE
    Uint32 EPE   :1;           // [23..23] Error Passive IE
    Uint32 EWE   :1;           // [24..24] Warning Status IE
    Uint32 BOE   :1;           // [25..25] Bus_Off Status IE
    Uint32 WDIE  :1;           // [26..26] Watchdog IE
    Uint32 PEAE  :1;           // [27..27] Protocol Error in Arbitration Phase IE
    Uint32 PEDE  :1;           // [28..28] Protocol Error in Data Phase IE
    Uint32 ARAE  :1;           // [29..29] Access to Reserved Address IE
    Uint32 rsvd2 :2;           // [31..30] Reserved
};

union IE_REG {
    Uint32   all;
    struct IE_BITS   bit;
};

struct ILS_BITS {              // bits description
    Uint32 RF0NL :1;           // [0..0] Rx FIFO 0 New Message Interrupt Line
    Uint32 RF0WL :1;           // [1..1] Rx FIFO 0 Watermark Interrupt Line
    Uint32 RF0FL :1;           // [2..2] Rx FIFO 0 Full Interrupt Line
    Uint32 RF0LL :1;           // [3..3] Rx FIFO 0 Message Lost Interrupt Line
    Uint32 RF1NL :1;           // [4..4] Rx FIFO 1 New Message Interrupt Line
    Uint32 RF1WL :1;           // [5..5] Rx FIFO 1 Watermark Interrupt Line
    Uint32 RF1FL :1;           // [6..6] Rx FIFO 1 Full Interrupt Line
    Uint32 RF1LL :1;           // [7..7] Rx FIFO 1 Message Lost Interrupt Line
    Uint32 HPML  :1;           // [8..8] High Priority Message Interrupt Line
    Uint32 TCL   :1;           // [9..9] Transmission Completed Interrupt Line
    Uint32 TCFL  :1;           // [10..10] Transmission Cancellation Finished Interrupt Line
    Uint32 TFEL  :1;           // [11..11] Tx FIFO Empty Interrupt Line
    Uint32 TEFNL :1;           // [12..12] Tx Event FIFO New Entry Interrupt Line
    Uint32 TEFWL :1;           // [13..13] Tx Event FIFO Watermark Interrupt Line
    Uint32 TEFFL :1;           // [14..14] Tx Event FIFO Full Interrupt Line
    Uint32 TEFLL :1;           // [15..15] Tx Event FIFO Event Lost Interrupt Line
    Uint32 TSWL  :1;           // [16..16] Timestamp Wraparound Interrupt Line
    Uint32 MRAFL :1;           // [17..17] Message RAM Access Failure Interrupt Line
    Uint32 TOOL  :1;           // [18..18] Timeout Occurred Interrupt Line
    Uint32 DRXL  :1;           // [19..19] Dedicated Rx Buffer Interrupt Line
    Uint32 rsvd1 :2;           // [21..20] Reserved
    Uint32 ELOL  :1;           // [22..22] Error Logging Overflow Interrupt Line
    Uint32 EPL   :1;           // [23..23] Error Passive Interrupt Line
    Uint32 EWL   :1;           // [24..24] Warning Status Interrupt Line
    Uint32 BOL   :1;           // [25..25] Bus_Off Status Interrupt Line
    Uint32 WDIL  :1;           // [26..26] Watchdog Interrupt Line
    Uint32 PEAL  :1;           // [27..27] Protocol Error in Arbitration Phase Line
    Uint32 PEDL  :1;           // [28..28] Protocol Error in Data Phase Line
    Uint32 ARAL  :1;           // [29..29] Access to Reserved Address Line
    Uint32 rsvd2 :2;           // [31..30] Reserved
};

union ILS_REG {
    Uint32   all;
    struct ILS_BITS  bit;
};

struct ILE_BITS {                      // bits description
    Uint32 EINT0 : 1;                 // [0..0] Enable Interrupt Line 0
    Uint32 EINT1 : 1;                 // [1..1] Enable Interrupt Line 1
    Uint32 rsvd1 : 30;                // [31..2] Reserved
};

union ILE_REG {
    Uint32       all;
    struct ILE_BITS bit;
};

struct GFC_BITS {                      // bits description
    Uint32 RRFE : 1;                  // [0..0] Reject Remote Frames Extended
    Uint32 RRFS : 1;                  // [1..1] Reject Remote Frames Standard
    Uint32 ANFE : 2;                  // [3..2] Accept Non-matching Frames Extended
    Uint32 ANFS : 2;                  // [5..4] Accept Non-matching Frames Standard
    Uint32 rsvd1 : 26;                // [31..6] Reserved
};

union GFC_REG {
    Uint32       all;
    struct GFC_BITS bit;
};

struct SIDFC_BITS {                    // bits description
    Uint32 rsvd1 : 2;                 // [1..0] Reserved
    Uint32 FLSSA : 14;                // [15..2] Filter List Standard Start Address
    Uint32 LSS   : 8;                 // [23..16] List Size Standard
    Uint32 rsvd2 : 8;                 // [31..24] Reserved
};

union SIDFC_REG {
    Uint32          all;
    struct SIDFC_BITS bit;
};

struct XIDFC_BITS {                    // bits description
    Uint32 rsvd1 : 2;                 // [1..0] Reserved
    Uint32 FLESA : 14;                // [15..2] Filter List Extended Start Address
    Uint32 LSE   : 7;                 // [22..16] List Size Extended
    Uint32 rsvd2 : 9;                 // [31..23] Reserved
};

union XIDFC_REG {
    Uint32          all;
    struct XIDFC_BITS bit;
};

struct XIDAM_BITS {                    // bits description
    Uint32 EIDM  : 29;                // [28..0] Extended ID Mask
    Uint32 rsvd1 : 3;                 // [31..29] Reserved
};

union XIDAM_REG {
    Uint32          all;
    struct XIDAM_BITS bit;
};

struct HPMS_BITS {                    // bits description
    Uint32 BIDX  : 6;                 // [5..0] Buffer Index
    Uint32 MSI   : 2;                 // [7..6] Message Storage Indicator
    Uint32 FIDX  : 7;                 // [14..8] Filter Index
    Uint32 FLST  : 1;                 // [15..15] Filter List
    Uint32 rsvd1 : 16;                // [31..16] Reserved
};

union HPMS_REG {
    Uint32         all;
    struct HPMS_BITS bit;
};

struct NDAT1_BITS {                   // bits description
    Uint32 ND0:1;                        // 0 New Data RX Buffer 0
    Uint32 ND1:1;                        // 1 New Data RX Buffer 1
    Uint32 ND2:1;                        // 2 New Data RX Buffer 2
    Uint32 ND3:1;                        // 3 New Data RX Buffer 3
    Uint32 ND4:1;                        // 4 New Data RX Buffer 4
    Uint32 ND5:1;                        // 5 New Data RX Buffer 5
    Uint32 ND6:1;                        // 6 New Data RX Buffer 6
    Uint32 ND7:1;                        // 7 New Data RX Buffer 7
    Uint32 ND8:1;                        // 8 New Data RX Buffer 8
    Uint32 ND9:1;                        // 9 New Data RX Buffer 9
    Uint32 ND10:1;                       // 10 New Data RX Buffer 10
    Uint32 ND11:1;                       // 11 New Data RX Buffer 11
    Uint32 ND12:1;                       // 12 New Data RX Buffer 12
    Uint32 ND13:1;                       // 13 New Data RX Buffer 13
    Uint32 ND14:1;                       // 14 New Data RX Buffer 14
    Uint32 ND15:1;                       // 15 New Data RX Buffer 15
    Uint32 ND16:1;                       // 16 New Data RX Buffer 16
    Uint32 ND17:1;                       // 17 New Data RX Buffer 17
    Uint32 ND18:1;                       // 18 New Data RX Buffer 18
    Uint32 ND19:1;                       // 19 New Data RX Buffer 19
    Uint32 ND20:1;                       // 20 New Data RX Buffer 20
    Uint32 ND21:1;                       // 21 New Data RX Buffer 21
    Uint32 ND22:1;                       // 22 New Data RX Buffer 22
    Uint32 ND23:1;                       // 23 New Data RX Buffer 23
    Uint32 ND24:1;                       // 24 New Data RX Buffer 24
    Uint32 ND25:1;                       // 25 New Data RX Buffer 25
    Uint32 ND26:1;                       // 26 New Data RX Buffer 26
    Uint32 ND27:1;                       // 27 New Data RX Buffer 27
    Uint32 ND28:1;                       // 28 New Data RX Buffer 28
    Uint32 ND29:1;                       // 29 New Data RX Buffer 29
    Uint32 ND30:1;                       // 30 New Data RX Buffer 30
    Uint32 ND31:1;                       // 31 New Data RX Buffer 31
};

union NDAT1_REG {
    Uint32          all;
    struct NDAT1_BITS bit;
};

struct NDAT2_BITS {                   // bits description
    Uint32 ND32:1;                       // 0 New Data RX Buffer 32
    Uint32 ND33:1;                       // 1 New Data RX Buffer 33
    Uint32 ND34:1;                       // 2 New Data RX Buffer 34
    Uint32 ND35:1;                       // 3 New Data RX Buffer 35
    Uint32 ND36:1;                       // 4 New Data RX Buffer 36
    Uint32 ND37:1;                       // 5 New Data RX Buffer 37
    Uint32 ND38:1;                       // 6 New Data RX Buffer 38
    Uint32 ND39:1;                       // 7 New Data RX Buffer 39
    Uint32 ND40:1;                       // 8 New Data RX Buffer 40
    Uint32 ND41:1;                       // 9 New Data RX Buffer 41
    Uint32 ND42:1;                       // 10 New Data RX Buffer 42
    Uint32 ND43:1;                       // 11 New Data RX Buffer 43
    Uint32 ND44:1;                       // 12 New Data RX Buffer 44
    Uint32 ND45:1;                       // 13 New Data RX Buffer 45
    Uint32 ND46:1;                       // 14 New Data RX Buffer 46
    Uint32 ND47:1;                       // 15 New Data RX Buffer 47
    Uint32 ND48:1;                       // 16 New Data RX Buffer 48
    Uint32 ND49:1;                       // 17 New Data RX Buffer 49
    Uint32 ND50:1;                       // 18 New Data RX Buffer 50
    Uint32 ND51:1;                       // 19 New Data RX Buffer 51
    Uint32 ND52:1;                       // 20 New Data RX Buffer 52
    Uint32 ND53:1;                       // 21 New Data RX Buffer 53
    Uint32 ND54:1;                       // 22 New Data RX Buffer 54
    Uint32 ND55:1;                       // 23 New Data RX Buffer 55
    Uint32 ND56:1;                       // 24 New Data RX Buffer 56
    Uint32 ND57:1;                       // 25 New Data RX Buffer 57
    Uint32 ND58:1;                       // 26 New Data RX Buffer 58
    Uint32 ND59:1;                       // 27 New Data RX Buffer 59
    Uint32 ND60:1;                       // 28 New Data RX Buffer 60
    Uint32 ND61:1;                       // 29 New Data RX Buffer 61
    Uint32 ND62:1;                       // 30 New Data RX Buffer 62
    Uint32 ND63:1;                       // 31 New Data RX Buffer 63
};

union NDAT2_REG {
    Uint32          all;
    struct NDAT2_BITS bit;
};

struct RXF0C_BITS {                   // bits description
    Uint32 rsvd1 : 2;                 // [1..0] Reserved
    Uint32 F0SA  : 14;                // [15..2] Rx FIFO 0 Start Address
    Uint32 F0S   : 7;                 // [22..16] Rx FIFO 0 Size
    Uint32 rsvd2 : 1;                 // [23..23] Reserved
    Uint32 F0WM  : 7;                 // [30..24] Rx FIFO 0 Watermark
    Uint32 F0OM  : 1;                 // [31..31] FIFO 0 Operation Mode
};

union RXF0C_REG {
    Uint32          all;
    struct RXF0C_BITS bit;
};

struct RXF0S_BITS {                   // bits description
    Uint32 F0FL  : 7;                 // [6..0] Rx FIFO 0 Fill Level
    Uint32 rsvd1 : 1;                 // [7..7] Reserved
    Uint32 F0GI  : 6;                 // [13..8] Rx FIFO 0 Get Index
    Uint32 rsvd2 : 2;                 // [15..14] Reserved
    Uint32 F0PI  : 6;                 // [21..16] Rx FIFO 0 Put Index
    Uint32 rsvd3 : 2;                 // [23..22] Reserved
    Uint32 F0F   : 1;                 // [24..24] Rx FIFO 0 Full
    Uint32 RF0L  : 1;                 // [25..25] Rx FIFO 0 Message Lost
    Uint32 rsvd4 : 6;                 // [31..26] Reserved
};

union RXF0S_REG {
    Uint32          all;
    struct RXF0S_BITS bit;
};

struct RXF0A_BITS {                   // bits description
    Uint32 F0AI  : 6;                 // [5..0] Rx FIFO 0 Acknowledge Index
    Uint32 rsvd1 : 26;                // [31..6] Reserved
};

union RXF0A_REG {
    Uint32          all;
    struct RXF0A_BITS bit;
};

struct RXBC_BITS {                    // bits description
    Uint32 rsvd1 : 2;                 // [1..0] Reserved
    Uint32 RBSA  : 14;                // [15..2] Rx Buffer Start Address
    Uint32 rsvd2 : 16;                // [31..16] Reserved
};

union RXBC_REG {
    Uint32         all;
    struct RXBC_BITS bit;
};

struct RXF1C_BITS {                   // bits description
    Uint32 rsvd1 : 2;                 // [1..0] Reserved
    Uint32 F1SA  : 14;                // [15..2] Rx FIFO 1 Start Address
    Uint32 F1S   : 7;                 // [22..16] Rx FIFO 1 Size
    Uint32 rsvd2 : 1;                 // [23..23] Reserved
    Uint32 F1WM  : 7;                 // [30..24] Rx FIFO 1 Watermark
    Uint32 F1OM  : 1;                 // [31..31] FIFO 1 Operation Mode
};

union RXF1C_REG {
    Uint32          all;
    struct RXF1C_BITS bit;
};

struct RXF1S_BITS {                   // bits description
    Uint32 F1FL  : 7;                 // [6..0] Rx FIFO 1 Fill Level
    Uint32 rsvd1 : 1;                 // [7..7] Reserved
    Uint32 F1GI  : 6;                 // [13..8] Rx FIFO 1 Get Index
    Uint32 rsvd2 : 2;                 // [15..14] Reserved
    Uint32 F1PI  : 6;                 // [21..16] Rx FIFO 1 Put Index
    Uint32 rsvd3 : 2;                 // [23..22] Reserved
    Uint32 F1F   : 1;                 // [24..24] Rx FIFO 1 Full
    Uint32 RF1L  : 1;                 // [25..25] Rx FIFO 1 Message Lost
    Uint32 rsvd4 : 4;                 // [29..26] Reserved
    Uint32 DMS   : 2;                 // [31..30] Debug Message Status
};

union RXF1S_REG {
    Uint32          all;
    struct RXF1S_BITS bit;
};

struct RXF1A_BITS {                   // bits description
    Uint32 F1AI  : 6;                 // [5..0] Rx FIFO 1 Acknowledge Index
    Uint32 rsvd1 : 26;                // [31..6] Reserved
};

union RXF1A_REG {
    Uint32          all;
    struct RXF1A_BITS bit;
};

struct RXESC_BITS {                   // bits description
    Uint32 F0DS  : 3;                 // [2..0] Rx FIFO 0 Data Field Size
    Uint32 rsvd1 : 1;                 // [3..3] Reserved
    Uint32 F1DS  : 3;                 // [6..4] Rx FIFO 1 Data Field Size
    Uint32 rsvd2 : 1;                 // [7..7] Reserved
    Uint32 RBDS  : 3;                 // [10..8] Rx Buffer Data Field Size
    Uint32 rsvd3 : 21;                // [31..11] Reserved
};

union RXESC_REG {
    Uint32          all;
    struct RXESC_BITS bit;
};

struct TXBC_BITS {                    // bits description
    Uint32 rsvd1 : 2;                 // [1..0] Reserved
    Uint32 TBSA  : 14;                // [15..2] Tx Buffers Start Address
    Uint32 NDTB  : 6;                 // [21..16] Number of Dedicated Tx Buffers
    Uint32 rsvd2 : 2;                 // [23..22] Reserved
    Uint32 TFQS  : 6;                 // [29..24] Tx FIFO/Queue Size
    Uint32 TFQM  : 1;                 // [30..30] Tx FIFO/Queue Mode
    Uint32 rsvd3 : 1;                 // [31..31] Reserved
};

union TXBC_REG {
    Uint32        all;
    struct TXBC_BITS bit;
};

struct TXFQS_BITS {                     // bits description
    Uint32 TFFL  : 6;                   // [5..0] Tx FIFO Free Level
    Uint32 rsvd1 : 2;                   // [7..6] Reserved
    Uint32 TFGI  : 5;                   // [12..8] Tx FIFO Get Index
    Uint32 rsvd2 : 3;                   // [15..13] Reserved
    Uint32 TFQPI : 5;                   // [20..16] Tx FIFO/Queue Put Index
    Uint32 TFQF  : 1;                   // [21..21] Tx FIFO/Queue Full
    Uint32 rsvd3 : 10;                  // [31..22] Reserved
};

union TXFQS_REG {
    Uint32         all;
    struct TXFQS_BITS bit;
};

struct TXESC_BITS {                     // bits description
    Uint32 TBDS  : 3;                   // [2..0] Tx Buffer Data Field Size
    Uint32 rsvd1 : 29;                  // [31..3] Reserved
};

union TXESC_REG {
    Uint32         all;
    struct TXESC_BITS bit;
};

struct TXBRP_BITS {                     // bits description
    Uint32 TRP0:1;                      // [0..0]   Transmission Request Pending 0
    Uint32 TRP1:1;                      // [1..1]   Transmission Request Pending 1
    Uint32 TRP2:1;                      // [2..2]   Transmission Request Pending 2
    Uint32 TRP3:1;                      // [3..3]   Transmission Request Pending 3
    Uint32 TRP4:1;                      // [4..4]   Transmission Request Pending 4
    Uint32 TRP5:1;                      // [5..5]   Transmission Request Pending 5
    Uint32 TRP6:1;                      // [6..6]   Transmission Request Pending 6
    Uint32 TRP7:1;                      // [7..7]   Transmission Request Pending 7
    Uint32 TRP8:1;                      // [8..8]   Transmission Request Pending 8
    Uint32 TRP9:1;                      // [9..9]   Transmission Request Pending 9
    Uint32 TRP10:1;                     // [10..10] Transmission Request Pending 10
    Uint32 TRP11:1;                     // [11..11] Transmission Request Pending 11
    Uint32 TRP12:1;                     // [12..12] Transmission Request Pending 12
    Uint32 TRP13:1;                     // [13..13] Transmission Request Pending 13
    Uint32 TRP14:1;                     // [14..14] Transmission Request Pending 14
    Uint32 TRP15:1;                     // [15..15] Transmission Request Pending 15
    Uint32 TRP16:1;                     // [16..16] Transmission Request Pending 16
    Uint32 TRP17:1;                     // [17..17] Transmission Request Pending 17
    Uint32 TRP18:1;                     // [18..18] Transmission Request Pending 18
    Uint32 TRP19:1;                     // [19..19] Transmission Request Pending 19
    Uint32 TRP20:1;                     // [20..20] Transmission Request Pending 20
    Uint32 TRP21:1;                     // [21..21] Transmission Request Pending 21
    Uint32 TRP22:1;                     // [22..22] Transmission Request Pending 22
    Uint32 TRP23:1;                     // [23..23] Transmission Request Pending 23
    Uint32 TRP24:1;                     // [24..24] Transmission Request Pending 24
    Uint32 TRP25:1;                     // [25..25] Transmission Request Pending 25
    Uint32 TRP26:1;                     // [26..26] Transmission Request Pending 26
    Uint32 TRP27:1;                     // [27..27] Transmission Request Pending 27
    Uint32 TRP28:1;                     // [28..28] Transmission Request Pending 28
    Uint32 TRP29:1;                     // [29..29] Transmission Request Pending 29
    Uint32 TRP30:1;                     // [30..30] Transmission Request Pending 30
    Uint32 TRP31:1;                     // [31..31] Transmission Request Pending 31
};

union TXBRP_REG {
    Uint32         all;
    struct TXBRP_BITS bit;
};

struct TXBAR_BITS {                     // bits description
    Uint32 AR0:1;                       // [0..0]   Add Request 0
    Uint32 AR1:1;                       // [1..1]   Add Request 1
    Uint32 AR2:1;                       // [2..2]   Add Request 2
    Uint32 AR3:1;                       // [3..3]   Add Request 3
    Uint32 AR4:1;                       // [4..4]   Add Request 4
    Uint32 AR5:1;                       // [5..5]   Add Request 5
    Uint32 AR6:1;                       // [6..6]   Add Request 6
    Uint32 AR7:1;                       // [7..7]   Add Request 7
    Uint32 AR8:1;                       // [8..8]   Add Request 8
    Uint32 AR9:1;                       // [9..9]   Add Request 9
    Uint32 AR10:1;                      // [10..10] Add Request 10
    Uint32 AR11:1;                      // [11..11] Add Request 11
    Uint32 AR12:1;                      // [12..12] Add Request 12
    Uint32 AR13:1;                      // [13..13] Add Request 13
    Uint32 AR14:1;                      // [14..14] Add Request 14
    Uint32 AR15:1;                      // [15..15] Add Request 15
    Uint32 AR16:1;                      // [16..16] Add Request 16
    Uint32 AR17:1;                      // [17..17] Add Request 17
    Uint32 AR18:1;                      // [18..18] Add Request 18
    Uint32 AR19:1;                      // [19..19] Add Request 19
    Uint32 AR20:1;                      // [20..20] Add Request 20
    Uint32 AR21:1;                      // [21..21] Add Request 21
    Uint32 AR22:1;                      // [22..22] Add Request 22
    Uint32 AR23:1;                      // [23..23] Add Request 23
    Uint32 AR24:1;                      // [24..24] Add Request 24
    Uint32 AR25:1;                      // [25..25] Add Request 25
    Uint32 AR26:1;                      // [26..26] Add Request 26
    Uint32 AR27:1;                      // [27..27] Add Request 27
    Uint32 AR28:1;                      // [28..28] Add Request 28
    Uint32 AR29:1;                      // [29..29] Add Request 29
    Uint32 AR30:1;                      // [30..30] Add Request 30
    Uint32 AR31:1;                      // [31..31] Add Request 31
};

union TXBAR_REG {
    Uint32         all;
    struct TXBAR_BITS bit;
};

struct TXBCR_BITS {                     // bits description
    Uint32 CR0:1;                       // [0..0]   Cancellation Request 0
    Uint32 CR1:1;                       // [1..1]   Cancellation Request 1
    Uint32 CR2:1;                       // [2..2]   Cancellation Request 2
    Uint32 CR3:1;                       // [3..3]   Cancellation Request 3
    Uint32 CR4:1;                       // [4..4]   Cancellation Request 4
    Uint32 CR5:1;                       // [5..5]   Cancellation Request 5
    Uint32 CR6:1;                       // [6..6]   Cancellation Request 6
    Uint32 CR7:1;                       // [7..7]   Cancellation Request 7
    Uint32 CR8:1;                       // [8..8]   Cancellation Request 8
    Uint32 CR9:1;                       // [9..9]   Cancellation Request 9
    Uint32 CR10:1;                      // [10..10] Cancellation Request 10
    Uint32 CR11:1;                      // [11..11] Cancellation Request 11
    Uint32 CR12:1;                      // [12..12] Cancellation Request 12
    Uint32 CR13:1;                      // [13..13] Cancellation Request 13
    Uint32 CR14:1;                      // [14..14] Cancellation Request 14
    Uint32 CR15:1;                      // [15..15] Cancellation Request 15
    Uint32 CR16:1;                      // [16..16] Cancellation Request 16
    Uint32 CR17:1;                      // [17..17] Cancellation Request 17
    Uint32 CR18:1;                      // [18..18] Cancellation Request 18
    Uint32 CR19:1;                      // [19..19] Cancellation Request 19
    Uint32 CR20:1;                      // [20..20] Cancellation Request 20
    Uint32 CR21:1;                      // [21..21] Cancellation Request 21
    Uint32 CR22:1;                      // [22..22] Cancellation Request 22
    Uint32 CR23:1;                      // [23..23] Cancellation Request 23
    Uint32 CR24:1;                      // [24..24] Cancellation Request 24
    Uint32 CR25:1;                      // [25..25] Cancellation Request 25
    Uint32 CR26:1;                      // [26..26] Cancellation Request 26
    Uint32 CR27:1;                      // [27..27] Cancellation Request 27
    Uint32 CR28:1;                      // [28..28] Cancellation Request 28
    Uint32 CR29:1;                      // [29..29] Cancellation Request 29
    Uint32 CR30:1;                      // [30..30] Cancellation Request 30
    Uint32 CR31:1;                      // [31..31] Cancellation Request 31
};

union TXBCR_REG {
    Uint32         all;
    struct TXBCR_BITS bit;
};

struct TXBTO_BITS {                     // bits description
    Uint32 TO0:1;                       // [0..0]   Transmission Occurred 0
    Uint32 TO1:1;                       // [1..1]   Transmission Occurred 1
    Uint32 TO2:1;                       // [2..2]   Transmission Occurred 2
    Uint32 TO3:1;                       // [3..3]   Transmission Occurred 3
    Uint32 TO4:1;                       // [4..4]   Transmission Occurred 4
    Uint32 TO5:1;                       // [5..5]   Transmission Occurred 5
    Uint32 TO6:1;                       // [6..6]   Transmission Occurred 6
    Uint32 TO7:1;                       // [7..7]   Transmission Occurred 7
    Uint32 TO8:1;                       // [8..8]   Transmission Occurred 8
    Uint32 TO9:1;                       // [9..9]   Transmission Occurred 9
    Uint32 TO10:1;                      // [10..10] Transmission Occurred 10
    Uint32 TO11:1;                      // [11..11] Transmission Occurred 11
    Uint32 TO12:1;                      // [12..12] Transmission Occurred 12
    Uint32 TO13:1;                      // [13..13] Transmission Occurred 13
    Uint32 TO14:1;                      // [14..14] Transmission Occurred 14
    Uint32 TO15:1;                      // [15..15] Transmission Occurred 15
    Uint32 TO16:1;                      // [16..16] Transmission Occurred 16
    Uint32 TO17:1;                      // [17..17] Transmission Occurred 17
    Uint32 TO18:1;                      // [18..18] Transmission Occurred 18
    Uint32 TO19:1;                      // [19..19] Transmission Occurred 19
    Uint32 TO20:1;                      // [20..20] Transmission Occurred 20
    Uint32 TO21:1;                      // [21..21] Transmission Occurred 21
    Uint32 TO22:1;                      // [22..22] Transmission Occurred 22
    Uint32 TO23:1;                      // [23..23] Transmission Occurred 23
    Uint32 TO24:1;                      // [24..24] Transmission Occurred 24
    Uint32 TO25:1;                      // [25..25] Transmission Occurred 25
    Uint32 TO26:1;                      // [26..26] Transmission Occurred 26
    Uint32 TO27:1;                      // [27..27] Transmission Occurred 27
    Uint32 TO28:1;                      // [28..28] Transmission Occurred 28
    Uint32 TO29:1;                      // [29..29] Transmission Occurred 29
    Uint32 TO30:1;                      // [30..30] Transmission Occurred 30
    Uint32 TO31:1;                      // [31..31] Transmission Occurred 31
};

union TXBTO_REG {
    Uint32         all;
    struct TXBTO_BITS bit;
};

struct TXBCF_BITS {                     // bits description
    Uint32 CF0:1;                       // [0..0]   Cancellation Finished 0
    Uint32 CF1:1;                       // [1..1]   Cancellation Finished 1
    Uint32 CF2:1;                       // [2..2]   Cancellation Finished 2
    Uint32 CF3:1;                       // [3..3]   Cancellation Finished 3
    Uint32 CF4:1;                       // [4..4]   Cancellation Finished 4
    Uint32 CF5:1;                       // [5..5]   Cancellation Finished 5
    Uint32 CF6:1;                       // [6..6]   Cancellation Finished 6
    Uint32 CF7:1;                       // [7..7]   Cancellation Finished 7
    Uint32 CF8:1;                       // [8..8]   Cancellation Finished 8
    Uint32 CF9:1;                       // [9..9]   Cancellation Finished 9
    Uint32 CF10:1;                      // [10..10] Cancellation Finished 10
    Uint32 CF11:1;                      // [11..11] Cancellation Finished 11
    Uint32 CF12:1;                      // [12..12] Cancellation Finished 12
    Uint32 CF13:1;                      // [13..13] Cancellation Finished 13
    Uint32 CF14:1;                      // [14..14] Cancellation Finished 14
    Uint32 CF15:1;                      // [15..15] Cancellation Finished 15
    Uint32 CF16:1;                      // [16..16] Cancellation Finished 16
    Uint32 CF17:1;                      // [17..17] Cancellation Finished 17
    Uint32 CF18:1;                      // [18..18] Cancellation Finished 18
    Uint32 CF19:1;                      // [19..19] Cancellation Finished 19
    Uint32 CF20:1;                      // [20..20] Cancellation Finished 20
    Uint32 CF21:1;                      // [21..21] Cancellation Finished 21
    Uint32 CF22:1;                      // [22..22] Cancellation Finished 22
    Uint32 CF23:1;                      // [23..23] Cancellation Finished 23
    Uint32 CF24:1;                      // [24..24] Cancellation Finished 24
    Uint32 CF25:1;                      // [25..25] Cancellation Finished 25
    Uint32 CF26:1;                      // [26..26] Cancellation Finished 26
    Uint32 CF27:1;                      // [27..27] Cancellation Finished 27
    Uint32 CF28:1;                      // [28..28] Cancellation Finished 28
    Uint32 CF29:1;                      // [29..29] Cancellation Finished 29
    Uint32 CF30:1;                      // [30..30] Cancellation Finished 30
    Uint32 CF31:1;                      // [31..31] Cancellation Finished 31
};

union TXBCF_REG {
    Uint32         all;
    struct TXBCF_BITS bit;
};

struct TXBTIE_BITS {                    // bits description
    Uint32 TIE0:1;                      // [0..0]   Transmission Interrupt Enable 0
    Uint32 TIE1:1;                      // [1..1]   Transmission Interrupt Enable 1
    Uint32 TIE2:1;                      // [2..2]   Transmission Interrupt Enable 2
    Uint32 TIE3:1;                      // [3..3]   Transmission Interrupt Enable 3
    Uint32 TIE4:1;                      // [4..4]   Transmission Interrupt Enable 4
    Uint32 TIE5:1;                      // [5..5]   Transmission Interrupt Enable 5
    Uint32 TIE6:1;                      // [6..6]   Transmission Interrupt Enable 6
    Uint32 TIE7:1;                      // [7..7]   Transmission Interrupt Enable 7
    Uint32 TIE8:1;                      // [8..8]   Transmission Interrupt Enable 8
    Uint32 TIE9:1;                      // [9..9]   Transmission Interrupt Enable 9
    Uint32 TIE10:1;                     // [10..10] Transmission Interrupt Enable 10
    Uint32 TIE11:1;                     // [11..11] Transmission Interrupt Enable 11
    Uint32 TIE12:1;                     // [12..12] Transmission Interrupt Enable 12
    Uint32 TIE13:1;                     // [13..13] Transmission Interrupt Enable 13
    Uint32 TIE14:1;                     // [14..14] Transmission Interrupt Enable 14
    Uint32 TIE15:1;                     // [15..15] Transmission Interrupt Enable 15
    Uint32 TIE16:1;                     // [16..16] Transmission Interrupt Enable 16
    Uint32 TIE17:1;                     // [17..17] Transmission Interrupt Enable 17
    Uint32 TIE18:1;                     // [18..18] Transmission Interrupt Enable 18
    Uint32 TIE19:1;                     // [19..19] Transmission Interrupt Enable 19
    Uint32 TIE20:1;                     // [20..20] Transmission Interrupt Enable 20
    Uint32 TIE21:1;                     // [21..21] Transmission Interrupt Enable 21
    Uint32 TIE22:1;                     // [22..22] Transmission Interrupt Enable 22
    Uint32 TIE23:1;                     // [23..23] Transmission Interrupt Enable 23
    Uint32 TIE24:1;                     // [24..24] Transmission Interrupt Enable 24
    Uint32 TIE25:1;                     // [25..25] Transmission Interrupt Enable 25
    Uint32 TIE26:1;                     // [26..26] Transmission Interrupt Enable 26
    Uint32 TIE27:1;                     // [27..27] Transmission Interrupt Enable 27
    Uint32 TIE28:1;                     // [28..28] Transmission Interrupt Enable 28
    Uint32 TIE29:1;                     // [29..29] Transmission Interrupt Enable 29
    Uint32 TIE30:1;                     // [30..30] Transmission Interrupt Enable 30
    Uint32 TIE31:1;                     // [31..31] Transmission Interrupt Enable 31
};

union TXBTIE_REG {
    Uint32          all;
    struct TXBTIE_BITS bit;
};

struct TXBCIE_BITS {                    // bits description
    Uint32 CFIE0:1;                     // [0..0]   Cancellation Finished Interrupt Enable 0
    Uint32 CFIE1:1;                     // [1..1]   Cancellation Finished Interrupt Enable 1
    Uint32 CFIE2:1;                     // [2..2]   Cancellation Finished Interrupt Enable 2
    Uint32 CFIE3:1;                     // [3..3]   Cancellation Finished Interrupt Enable 3
    Uint32 CFIE4:1;                     // [4..4]   Cancellation Finished Interrupt Enable 4
    Uint32 CFIE5:1;                     // [5..5]   Cancellation Finished Interrupt Enable 5
    Uint32 CFIE6:1;                     // [6..6]   Cancellation Finished Interrupt Enable 6
    Uint32 CFIE7:1;                     // [7..7]   Cancellation Finished Interrupt Enable 7
    Uint32 CFIE8:1;                     // [8..8]   Cancellation Finished Interrupt Enable 8
    Uint32 CFIE9:1;                     // [9..9]   Cancellation Finished Interrupt Enable 9
    Uint32 CFIE10:1;                    // [10..10] Cancellation Finished Interrupt Enable 10
    Uint32 CFIE11:1;                    // [11..11] Cancellation Finished Interrupt Enable 11
    Uint32 CFIE12:1;                    // [12..12] Cancellation Finished Interrupt Enable 12
    Uint32 CFIE13:1;                    // [13..13] Cancellation Finished Interrupt Enable 13
    Uint32 CFIE14:1;                    // [14..14] Cancellation Finished Interrupt Enable 14
    Uint32 CFIE15:1;                    // [15..15] Cancellation Finished Interrupt Enable 15
    Uint32 CFIE16:1;                    // [16..16] Cancellation Finished Interrupt Enable 16
    Uint32 CFIE17:1;                    // [17..17] Cancellation Finished Interrupt Enable 17
    Uint32 CFIE18:1;                    // [18..18] Cancellation Finished Interrupt Enable 18
    Uint32 CFIE19:1;                    // [19..19] Cancellation Finished Interrupt Enable 19
    Uint32 CFIE20:1;                    // [20..20] Cancellation Finished Interrupt Enable 20
    Uint32 CFIE21:1;                    // [21..21] Cancellation Finished Interrupt Enable 21
    Uint32 CFIE22:1;                    // [22..22] Cancellation Finished Interrupt Enable 22
    Uint32 CFIE23:1;                    // [23..23] Cancellation Finished Interrupt Enable 23
    Uint32 CFIE24:1;                    // [24..24] Cancellation Finished Interrupt Enable 24
    Uint32 CFIE25:1;                    // [25..25] Cancellation Finished Interrupt Enable 25
    Uint32 CFIE26:1;                    // [26..26] Cancellation Finished Interrupt Enable 26
    Uint32 CFIE27:1;                    // [27..27] Cancellation Finished Interrupt Enable 27
    Uint32 CFIE28:1;                    // [28..28] Cancellation Finished Interrupt Enable 28
    Uint32 CFIE29:1;                    // [29..29] Cancellation Finished Interrupt Enable 29
    Uint32 CFIE30:1;                    // [30..30] Cancellation Finished Interrupt Enable 30
    Uint32 CFIE31:1;                    // [31..31] Cancellation Finished Interrupt Enable 31
};

union TXBCIE_REG {
    Uint32          all;
    struct TXBCIE_BITS bit;
};

struct TXEFC_BITS {                     // bits description
    Uint32 rsvd1 : 2;                   // [1..0] Reserved
    Uint32 EFSA  : 14;                  // [15..2] Event FIFO Start Address
    Uint32 EFS   : 6;                   // [21..16] Event FIFO Size
    Uint32 rsvd2 : 2;                   // [23..22] Reserved
    Uint32 EFWM  : 6;                   // [29..24] Event FIFO Watermark
    Uint32 rsvd3 : 2;                   // [31..30] Reserved
};

union TXEFC_REG {
    Uint32         all;
    struct TXEFC_BITS bit;
};

struct TXEFS_BITS {                     // bits description
    Uint32 EFFL  : 6;                   // [5..0] Event FIFO Fill Level
    Uint32 rsvd1 : 2;                   // [7..6] Reserved
    Uint32 EFGI  : 5;                   // [12..8] Event FIFO Get Index
    Uint32 rsvd2 : 3;                   // [15..13] Reserved
    Uint32 EFPI  : 5;                   // [20..16] Event FIFO Put Index
    Uint32 rsvd3 : 3;                   // [23..21] Reserved
    Uint32 EFF   : 1;                   // [24..24] Event FIFO Full
    Uint32 TEFL  : 1;                   // [25..25] Tx Event FIFO Element Lost
    Uint32 rsvd4 : 6;                   // [31..26] Reserved
};

union TXEFS_REG {
    Uint32         all;
    struct TXEFS_BITS bit;
};

struct TXEFA_BITS {                     // bits description
    Uint32 EFAI  : 5;                   // [4..0] Event FIFO Acknowledge Index
    Uint32 rsvd1 : 27;                  // [31..5] Reserved
};

union TXEFA_REG {
    Uint32         all;
    struct TXEFA_BITS bit;
};

struct ERM_CTRL_BITS {                  // bits description
    Uint32 ECC_EN:1;                    // 0 ECC check enable
    Uint32 BEC_INT_EN:1;                // 1 Single-bit error corrected interrupt enable
    Uint32 BEU_INT_EN:1;                // 2 Multi-bit error uncorrectable interrupt enable
    Uint32 WAKE_INT_EN:1;               // 3 CANFD wake-up interrupt enable
    Uint32 rsvd1:28;                    // 31:4 Reserved
};

union ERM_CTRL_REG {
    Uint32          all;
    struct ERM_CTRL_BITS bit;
};

struct ERM_STS_BITS {                   // bits description
    Uint32 BEC_FLAG:1;                  // 0 Single-bit error detected and corrected
    Uint32 BEU_FLAG:1;                  // 1 Multiple-bit error detected and uncorrectable
    Uint32 rsvd1:30;                    // 31:2 Reserved
};

union ERM_STS_REG {
    Uint32          all;
    struct ERM_STS_BITS bit;
};

struct ERM_ECC_ADDR_LOG_BITS {          // bits description
    Uint32 ERR_ADDR:10;                 // 9:0 Error address
    Uint32 rsvd1:22;                    // 31:10 Reserved
};

union ERM_ECC_ADDR_LOG_REG {
    Uint32          all;
    struct ERM_ECC_ADDR_LOG_BITS bit;
};

struct ERM_ECC_DATA_LOG_BITS {          // bits description
    Uint32 ERR_DATA:32;                 // 31:0 Error data
};

union ERM_ECC_DATA_LOG_REG {
    Uint32          all;
    struct ERM_ECC_DATA_LOG_BITS bit;
};

struct ERM_RAM_INIT_BITS {              // bits description
    Uint32 RAM_INIT_EN:1;               // 0 RAM initialization request
    Uint32 RAM_INIT_DONE:1;             // 1 RAM initialization done flag
    Uint32 rsvd1:30;                    // 31:2 Reserved
};

union ERM_RAM_INIT_REG {
    Uint32          all;
    struct ERM_RAM_INIT_BITS bit;
};

struct ERM_EXTC_CTRL_BITS {             // bits description
    Uint32 ETCP:10;                     // 9:0 External Timestamp Prescaler Value
    Uint32 rsvd1:21;                    // 30:10 Reserved
    Uint32 ETCE:1;                      // 31 External Timestamp Counter Enable
};

union ERM_EXTC_CTRL_REG {
    Uint32          all;
    struct ERM_EXTC_CTRL_BITS bit;
};

struct ERM_EXTC_VAL_BITS {              // bits description
    Uint32 ETSC:16;                     // 15:0 External Timestamp Counter
    Uint32 rsvd1:16;                    // 31:16 Reserved
};

union ERM_EXTC_VAL_REG {
    Uint32          all;
    struct ERM_EXTC_VAL_BITS bit;
};

struct CANFD_REGS
{
    union CREL_REG              CREL;           // Core Release Register
    union ENDN_REG              ENDN;           // Endian Register
    Uint32                      rsvd1;          // Reserved
    union DBTP_REG              DBTP;           // Data Bit Timing & Prescaler Register
    union TEST_REG              TEST;           // Test Register
    union RWD_REG               RWD;            // RAM Watchdog
    union CCCR_REG              CCCR;           // CC Control Register
    union NBTP_REG              NBTP;           // Nominal Bit Timing & Prescaler Register
    union TSCC_REG              TSCC;           // Timestamp Counter Configuration
    union TSCV_REG              TSCV;           // Timestamp Counter Value
    union TOCC_REG              TOCC;           // Timeout Counter Configuration
    union TOCV_REG              TOCV;           // Timeout Counter Value
    Uint32                      rsvd2[4];       // Reserved
    union ECR_REG               ECR;            // Error Counter Register
    union PSR_REG               PSR;            // Protocol Status Register
    union TDCR_REG              TDCR;           // Transmitter Delay Compensation Register
    Uint32                      rsvd3;           // Reserved
    union IR_REG                IR;             // Interrupt Register
    union IE_REG                IE;             // Interrupt Enable
    union ILS_REG               ILS;            // Interrupt Line Select
    union ILE_REG               ILE;            // Interrupt Line Enable
    Uint32                      rsvd4[8];       // Reserved
    union GFC_REG               GFC;            // Global Filter Configuration
    union SIDFC_REG             SIDFC;          // Standard ID Filter Configuration
    union XIDFC_REG             XIDFC;          // Extended ID Filter Configuration
    Uint32                      rsvd5;           // Reserved
    union XIDAM_REG             XIDAM;          // Extended ID AND Mask
    union HPMS_REG              HPMS;           // High Priority Message Status
    union NDAT1_REG             NDAT1;          // New Data 1
    union NDAT2_REG             NDAT2;          // New Data 2
    union RXF0C_REG             RXF0C;          // Rx FIFO 0 Configuration
    union RXF0S_REG             RXF0S;          // Rx FIFO 0 Status
    union RXF0A_REG             RXF0A;          // Rx FIFO 0 Acknowledge
    union RXBC_REG              RXBC;           // Rx Buffer Configuration
    union RXF1C_REG             RXF1C;          // Rx FIFO 1 Configuration
    union RXF1S_REG             RXF1S;          // Rx FIFO 1 Status
    union RXF1A_REG             RXF1A;          // Rx FIFO 1 Acknowledge
    union RXESC_REG             RXESC;          // Rx Buffer / FIFO Element Size Configuration
    union TXBC_REG              TXBC;           // Tx Buffer Configuration
    union TXFQS_REG             TXFQS;          // Tx FIFO/Queue Status
    union TXESC_REG             TXESC;          // Tx Buffer Element Size Configuration
    union TXBRP_REG             TXBRP;          // Tx Buffer Request Pending
    union TXBAR_REG             TXBAR;          // Tx Buffer Add Request
    union TXBCR_REG             TXBCR;          // Tx Buffer Cancellation Request
    union TXBTO_REG             TXBTO;          // Tx Buffer Transmission Occurred
    union TXBCF_REG             TXBCF;          // Tx Buffer Cancellation Finished
    union TXBTIE_REG            TXBTIE;         // Tx Buffer Transmission Interrupt Enable
    union TXBCIE_REG            TXBCIE;         // Tx Buffer Cancellation Finished Interrupt Enable
    Uint32                      rsvd6[2];       // Reserved
    union TXEFC_REG             TXEFC;          // Tx Event FIFO Configuration
    union TXEFS_REG             TXEFS;          // Tx Event FIFO Status
    union TXEFA_REG             TXEFA;          // Tx Event FIFO Acknowledge
    Uint32                      rsvd7;          // Reserved (align ERM block to 0x100)
    union ERM_CTRL_REG          ERM_CTRL;       // ERM Control Register
    union ERM_STS_REG           ERM_STS;        // ERM Status Register
    union ERM_ECC_ADDR_LOG_REG  ERM_ECC_ADDR_LOG; // ERM ECC Address Log
    union ERM_ECC_DATA_LOG_REG  ERM_ECC_DATA_LOG; // ERM ECC Data Log
    union ERM_RAM_INIT_REG      ERM_RAM_INIT;   // ERM RAM Initialization Control
    union ERM_EXTC_CTRL_REG     ERM_EXTC_CTRL;  // ERM External Timestamp Counter Control
    union ERM_EXTC_VAL_REG      ERM_EXTC_VAL;   // ERM External Timestamp Counter Value
};

//---------------------------------------------------------------------------
// CANFD External References & Function Declarations:
//
extern volatile struct CANFD_REGS CanfdaRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
