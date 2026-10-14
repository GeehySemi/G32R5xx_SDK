//#############################################################################
//
// FILE:   canfd_ex12_receive_priority.c
//
// TITLE:   CANFD Receive High Priority Message Example
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//
//! \addtogroup driver_example_c28x_list
//! <h1> CANFD Receive High Priority Message </h1>
//!
//! This example demonstrates the CANFD receive function for High Priority Messages.
//! Messages with Message IDs from the range 0x1 to 0xB are received in Rx FIFO 1,
//! while messages with Message IDs 0x3 and 0x9 are marked as High Priority by the
//! receiving CAN node (frames in itself conform to CAN Protocol, Priority is only
//! marked from the perspective of the receiving CAN Node), following which a separate
//! interrupt is generated and the messages can be read.

//! Communication is done between two CAN nodes. The transmitting node could be another
//! MCU or a CAN bus analysis tool capable of transmitting CAN FD frames. The transmit
//! and receive pins of the CANFD module should be connected to a CAN
//! transceiver. Nominal bit rate 1 Mbps and data bit rate 2 Mbps (CANFD bit
//! clock: 20 MHz XTAL).
//!
//! Only Standard frames within the message ID range 0x1 to 0xB are received.
//!
//! If another node is used as the transmitter, canfd_ex9_transmit.c can be
//! run on it for the transmit function.
//!
//! \b Hardware \b Required \n
//!  - G32R502 evaluation board with CAN FD transceiver
//!
//! \b External \b Connections \n
//!   Both nodes should communicate through CAN FD capable transceivers.
//!
//!  - CANFD is on DEVICE_GPIO_PIN_CANRXA (CANFDRXA)
//!  - and DEVICE_GPIO_PIN_CANTXA (CANFDTXA)
//!
//! \b Watch \b Variables \n
//!  - rxMsg, rxMsg1
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
// 1. Align CANFD example with G32R502 eval board pinout and driverlib APIs.
// - 2026-08-21:
// 1. Relative to TI mcan_ex12_receive_priority: correct std filter SFEC from
//    PRI_FIFO0/FIFO0 to PRI_FIFO1/FIFO1 so filters match the FIFO1 msgRAM and
//    ISR path already used by the TI-derived example comments.
// 2. Fix Doxygen title / ID-range wording (remove Loopback leftover; unify
//    accepted range to 0x1..0xB).
//
//#############################################################################

//
// Include Files
//
#include "driverlib.h"
#include <string.h>
#include "device.h"
#include "inc/stw_dataTypes.h"
#include "inc/stw_types.h"

//
// Defines
//
#define CANFD_STD_ID_FILTER_NUM          (3U)
#define CANFD_EXT_ID_FILTER_NUM          (0U)
#define CANFD_FIFO_0_NUM                 (5U)
#define CANFD_FIFO_0_ELEM_SIZE           (CANFD_ELEM_SIZE_64BYTES)
#define CANFD_FIFO_1_NUM                 (10U)
#define CANFD_FIFO_1_ELEM_SIZE           (CANFD_ELEM_SIZE_64BYTES)
#define CANFD_RX_BUFF_NUM                (10U)
#define CANFD_RX_BUFF_ELEM_SIZE          (CANFD_ELEM_SIZE_64BYTES)
#define CANFD_TX_BUFF_SIZE               (10U)
#define CANFD_TX_BUFF_ELEM_SIZE          (CANFD_ELEM_SIZE_64BYTES)
#define CANFD_TX_EVENT_SIZE              (10U)

//
//  Defining Starting Addresses for Message RAM Sections,
//  (Calculated from Macros based on User defined configuration above)
//
#define CANFD_STD_ID_FILT_START_ADDR     (0x0U)
#define CANFD_EXT_ID_FILT_START_ADDR     (CANFD_STD_ID_FILT_START_ADDR + ((CANFD_STD_ID_FILTER_NUM * CANFD_MSGRAM_STD_ID_FILTER_SIZE_WORDS * 4U)))
#define CANFD_FIFO_0_START_ADDR          (CANFD_EXT_ID_FILT_START_ADDR + ((CANFD_EXT_ID_FILTER_NUM * CANFD_MSGRAM_EXT_ID_FILTER_SIZE_WORDS * 4U)))
#define CANFD_FIFO_1_START_ADDR          (CANFD_FIFO_0_START_ADDR + (CANFD_getMsgObjSize(CANFD_FIFO_0_ELEM_SIZE) * 4U * CANFD_FIFO_0_NUM))
#define CANFD_RX_BUFF_START_ADDR         (CANFD_FIFO_1_START_ADDR + (CANFD_getMsgObjSize(CANFD_FIFO_1_ELEM_SIZE) * 4U * CANFD_FIFO_1_NUM))
#define CANFD_TX_BUFF_START_ADDR         (CANFD_RX_BUFF_START_ADDR + (CANFD_getMsgObjSize(CANFD_RX_BUFF_ELEM_SIZE) * 4U * CANFD_RX_BUFF_NUM))
#define CANFD_TX_EVENT_START_ADDR        (CANFD_TX_BUFF_START_ADDR + (CANFD_getMsgObjSize(CANFD_TX_BUFF_ELEM_SIZE) * 4U * CANFD_TX_BUFF_SIZE))

//
// Global Variables.
//
volatile uint32_t isrIntr0Flag = 1U;
volatile uint32_t isrIntr1Flag = 1U;
volatile uint16_t monEn = 0x0;
volatile unsigned long msgCount = 0;
volatile unsigned long error = 0;
CANFD_RxBufElement rxMsg, rxMsg1;
CANFD_RxFIFOStatus RxFS;

//
// Function Prototype.
//
static void CANFDConfig(void);
static void CANFDIntrConfig(void);
void INT_CANFDA_INT1_IRQHandler(void);

//
// Main
//
void example_main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and unlock the GPIO configuration registers
    //
    Device_initGPIO();

    //
    // Globally disable interrupts and clear all NVIC enable/pending bits
    //
    Interrupt_initModule();
    //
    // Initialize RAM vector table and set VTOR; unregistered IRQs use
    // Interrupt_defaultHandler until Interrupt_register() is called
    //
    Interrupt_initVectorTable();

    EINT;
    ERTM;

    //
    // Configuring the GPIOs for CANFD.
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANFDRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANFDTXA);

    //
    // Configure the divisor for the CANFD bit-clock
    //
        //
    // CrossBar and ISR Configuration.
    //
    CANFDIntrConfig();

    //
    // Configure CANFD.
    //
    CANFDConfig();

    //
    // Enable Interrupts.
    //
    CANFD_enableIntr(CANFDA_DRIVER_BASE, CANFD_INTR_MASK_ALL, 1U);

    //
    // Select Interrupt Line.
    //
    CANFD_selectIntrLine(CANFDA_DRIVER_BASE, CANFD_INTR_MASK_ALL, CANFD_INTR_LINE_NUM_1);

    //
    // Enable Interrupt Line.
    //
    CANFD_enableIntrLine(CANFDA_DRIVER_BASE, CANFD_INTR_LINE_NUM_1, 1U);

    while(1)
    {
        //
        //  Adding delay of 1 second
        //
        DEVICE_DELAY_US(1000000);

        //
        //  Message Handling Code goes here
        //

    }

    //
    // Stop Application.
    //
    ESTOP0;
}

//
// This function will configure CANFD module.
//
static void CANFDConfig(void)
{
    CANFD_RevisionId revId;
    CANFD_InitParams initParams;
    CANFD_ConfigParams configParams;
    CANFD_MsgRAMConfigParams    msgRAMConfigParams;
    CANFD_StdMsgIDFilterElement stdFiltelem;
    CANFD_BitTimingParams       bitTimes;

    //
    //  Initializing all structs to zero to prevent stray values
    //
    memset(&initParams, 0, sizeof(initParams));
    memset(&configParams, 0, sizeof(configParams));
    memset(&msgRAMConfigParams, 0, sizeof(msgRAMConfigParams));
    memset(&stdFiltelem, 0, sizeof(stdFiltelem));
    memset(&bitTimes, 0, sizeof(bitTimes));

    //
    // CANFD bit clock = XTAL (20 MHz).
    //
    CANFD_selectClockSource(CANFDA_DRIVER_BASE, CANFD_CLOCK_SOURCE_XTAL);

    //
    // Initialize CANFD Init parameters.
    //
    initParams.fdMode            = 0x1U; // FD operation enabled.
    initParams.brsEnable         = 0x1U; // Bit rate switching for
                                         // transmissions enabled.
    initParams.txpEnable         = 0x0U; // Transmit pause disabled.
    initParams.efbi              = 0x0U; // Edge filtering disabled.
    initParams.pxhddisable       = 0x0U; // Protocol exception handling enabled
    initParams.darEnable         = 0x0U; // Enable Automatic retransmission of
                                       // messages not transmitted successfully
    initParams.wakeIntEnable     = 0x1U;
    initParams.tdcEnable         = 0x1U; // Transmitter Delay Compensation is
                                         // enabled.
    initParams.wdcPreload        = 0xFFU; // Start value of the Message RAM
                                          // Watchdog Counter preload.

    //
    // Transmitter Delay Compensation parameters.
    //
    initParams.tdcConfig.tdcf    = 0x2U;
    initParams.tdcConfig.tdco    = 0x4U;

    //
    // Initialize CANFD Config parameters.
    //
    configParams.monEnable         = monEn; // Bus Monitoring Mode is disabled
    configParams.asmEnable         = 0x0U;  // Normal CAN operation.
    configParams.tsPrescalar       = 0xFU;  // Prescaler Value.
    configParams.tsSelect          = 0x0U;  // Timestamp counter value.
    configParams.timeoutSelect     = CANFD_TIMEOUT_SELECT_CONT;
    // Time-out counter source select.
    configParams.timeoutPreload    = 0xFFFFU; // Start value of the Timeout
                                              // Counter.
    configParams.timeoutCntEnable  = 0x0U; // Time-out Counter is disabled.
    configParams.filterConfig.rrfs = 0x1U; // Reject all remote frames with
                                           // 29-bit extended IDs.
    configParams.filterConfig.rrfe = 0x1U; // Reject all remote frames with
                                           // 11-bit standard IDs.
    configParams.filterConfig.anfe = 0x1U; // Accept in Rx FIFO 1.
    configParams.filterConfig.anfs = 0x1U; // Accept in Rx FIFO 1.

    //
    // Initialize Message RAM Sections Configuration Parameters.
    //
    msgRAMConfigParams.flssa                = CANFD_STD_ID_FILT_START_ADDR;
    // Standard ID Filter List Start Address.
    msgRAMConfigParams.lss                  = CANFD_STD_ID_FILTER_NUM;
    // Standard ID Filter List Size
    msgRAMConfigParams.rxFIFO1startAddr     = CANFD_FIFO_1_START_ADDR;
    // Rx FIFO1 Start Address.
    msgRAMConfigParams.rxFIFO1size          = CANFD_FIFO_1_NUM;
    // Number of Rx FIFO elements.
    msgRAMConfigParams.rxFIFO1waterMark     = 8U; // Level for Rx FIFO 1
                                                  // watermark interrupt.
    msgRAMConfigParams.rxFIFO1OpMode        = 0U; // FIFO blocking mode.
    msgRAMConfigParams.rxFIFO1ElemSize      = CANFD_FIFO_1_ELEM_SIZE;
    // Rx FIFO1 Element Size.

    //
    // Initialize bit timings (20MHz XTAL: 1M nom / 2M data).
    // CANFD: TQ = NTSEG1 + NTSEG2 + 3; f_bit = f_canfd / ((BRP+1) * TQ)
    // Nom: 20MHz / (2 * 10) = 1M; Data: 20MHz / (2 * 5) = 2M
    //
    bitTimes.nomRatePrescalar   = 0x1U; // Nominal Baud Rate Pre-scaler
    bitTimes.nomTimeSeg1        = 0x6U; // Nominal Time segment before SP
    bitTimes.nomTimeSeg2        = 0x1U; // Nominal Time segment after SP
    bitTimes.nomSynchJumpWidth  = 0x1U; // Nominal SJW
    bitTimes.dataRatePrescalar  = 0x1U; // Data Baud Rate Pre-scaler
    bitTimes.dataTimeSeg1       = 0x2U; // Data Time segment before SP
    bitTimes.dataTimeSeg2       = 0x0U; // Data Time segment after SP
    bitTimes.dataSynchJumpWidth = 0x0U; // Data SJW

    //
    // Get CANFDSS Revision ID.
    //
    CANFD_getRevisionId(CANFDA_DRIVER_BASE, &revId);

    //
    // Initialize Message RAM (ERM hardware init; ECC remains disabled).
    //
    if(CANFD_requestAndWaitMemInit(CANFDA_DRIVER_BASE, 0x000FFFFFU) != STW_SOK)
    {
        ESTOP0;
    }

    //
    // Put CANFD in SW initialization mode.
    //
    CANFD_setOpMode(CANFDA_DRIVER_BASE, CANFD_OPERATION_MODE_SW_INIT);

    //
    // Wait till CANFD is not initialized.
    //
    while (CANFD_OPERATION_MODE_SW_INIT != CANFD_getOpMode(CANFDA_DRIVER_BASE));

    //
    // Initialize CANFD module.
    //
    CANFD_init(CANFDA_DRIVER_BASE, &initParams);

    //
    // Configure CANFD module.
    //
    CANFD_config(CANFDA_DRIVER_BASE, &configParams);

    //
    // Configure Bit timings.
    //
    CANFD_setBitTime(CANFDA_DRIVER_BASE, &bitTimes);

    //
    // Configure Message RAM Sections
    //
    CANFD_msgRAMConfig(CANFDA_DRIVER_BASE, &msgRAMConfigParams);

    //
    // Initialize Rx Buffer Configuration parameters.
    //
    stdFiltelem.sfid2              = 0x3U; // Standard Filter ID 2.
    stdFiltelem.sfid1              = 0x9U; // Standard Filter ID 1.
    stdFiltelem.sfec               = CANFD_STDFILTEC_PRI_FIFO1; // Priority + Rx FIFO 1
    stdFiltelem.sft                = 0x1U; // Dual ID filter for SFID1 and SFID2

    //
    // Configure Standard ID filter element
    //
    CANFD_addStdMsgIDFilter(CANFDA_DRIVER_BASE, 0U, &stdFiltelem);

    //
    // Initialize Rx Buffer Configuration parameters.
    //
    stdFiltelem.sfid2              = 0x1U; // Standard Filter ID 2.
    stdFiltelem.sfid1              = 0xBU; // Standard Filter ID 1.
    stdFiltelem.sfec               = CANFD_STDFILTEC_FIFO1; // Store in Rx FIFO 1
    stdFiltelem.sft                = 0x0U; // Range filter from SFID1 to SFID2

    //
    // Configure Standard ID filter element
    //
    CANFD_addStdMsgIDFilter(CANFDA_DRIVER_BASE, 1U, &stdFiltelem);

    //
    // Take CANFD out of the SW initialization mode
    //
    CANFD_setOpMode(CANFDA_DRIVER_BASE, CANFD_OPERATION_MODE_NORMAL);

    while (CANFD_OPERATION_MODE_NORMAL != CANFD_getOpMode(CANFDA_DRIVER_BASE));
}

//
// This function will configure X-BAR for CANFD interrupts.
//
static void CANFDIntrConfig(void)
{
    Interrupt_register(INT_CANFDA_INT1, &INT_CANFDA_INT1_IRQHandler);
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);
    Interrupt_setPriority(INT_CANFDA_INT1, 2, 0);
    Interrupt_enable(INT_CANFDA_INT1);
}

//
// This is Interrupt Service Routine for CANFD interrupt 1.
//
void INT_CANFDA_INT1_IRQHandler(void)
{
    uint32_t intrStatus;

    intrStatus = CANFD_getIntrStatus(CANFDA_DRIVER_BASE);

    if((intrStatus & CANFD_INTR_SRC_HIGH_PRIO_MSG) == CANFD_INTR_SRC_HIGH_PRIO_MSG)
    {
        CANFD_readHighPriorityMsgRam(CANFDA_DRIVER_BASE, &rxMsg);

        //
        //  High Priority Message Handling Goes Here
        //

    }
    if((intrStatus & CANFD_INTR_SRC_RX_FIFO1_WATERMARK) == CANFD_INTR_SRC_RX_FIFO1_WATERMARK)
    {
        CANFD_RxFIFOStatus RxFS;

        RxFS.num = CANFD_RX_FIFO_NUM_1;

        CANFD_getRxFIFOStatus(CANFDA_DRIVER_BASE, &RxFS);

        while(RxFS.fillLvl)
        {
            CANFD_readMsgRam(CANFDA_DRIVER_BASE, CANFD_MEM_TYPE_FIFO, 0U,
                                CANFD_RX_FIFO_NUM_1, &rxMsg1);

            CANFD_writeRxFIFOAck(CANFDA_DRIVER_BASE, CANFD_RX_FIFO_NUM_1,
                                RxFS.getIdx);
        }
    }

    //
    // Clear the interrupt Status.
    //
    CANFD_clearIntrStatus(CANFDA_DRIVER_BASE, intrStatus);

    //
    //  Clearing the interrupt lineNum
    //
    //
    // Acknowledge this interrupt located in group 9
    //
}
