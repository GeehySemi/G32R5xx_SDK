//#############################################################################
//
// FILE:    canfd_ex1_loopback.c
//
// TITLE:   CANFD Loopback with Interrupts Example
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1> CANFD External Loopback with Interrupt </h1>
//!
//! This example transmits one CAN FD frame (standard ID 0x4, BRS enabled)
//! in External Loopback mode. The frame is visible on the CANFD TX pin and
//! is received internally by the CANFD controller. After the interrupt
//! handler runs, the application reads the received frame and compares the
//! payload to the transmitted data. Nominal bit rate 1 Mbps and data bit rate
//! 2 Mbps (CANFD bit clock: 20 MHz XTAL).
//!
//! \b External \b Connections \n
//!  - None. CANFDA uses GPIO4 (TX) and GPIO5 (RX) on G32R502 EVAL; no external
//!    transceiver or second node is required for external loopback.
//!
//! \b Watch \b Variables \n
//!  - msgCount - Set to 1 after one successful receive and payload match
//!  - error - Incremented in the ISR if the interrupt status is unexpected
//!  - isrIntr1Flag - Cleared in the ISR when the looped-back frame is received
//!
//! \b Pass \b criteria \n
//!  - Run completes without ESTOP0; msgCount == 1 and error == 0
//!  - Program idles in the final while(1) loop
//!
//
//###########################################################################
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
// 1. Modify some comments, macros, function names, and function contents.
// 2. Select XTAL (20MHz) as CANFD bit clock; 1M nominal / 2M data bit timing.
//
//###########################################################################


//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "inc/stw_dataTypes.h"
#include "inc/stw_types.h"
#include <string.h>

//
// Defines
//
#define CANFD_STD_ID_FILTER_NUM          (1U)
#define CANFD_EXT_ID_FILTER_NUM          (0U)
#define CANFD_FIFO_0_NUM                 (5U)
#define CANFD_FIFO_0_ELEM_SIZE           (CANFD_ELEM_SIZE_64BYTES)
#define CANFD_FIFO_1_NUM                 (10U)
#define CANFD_FIFO_1_ELEM_SIZE           (CANFD_ELEM_SIZE_64BYTES)
#define CANFD_RX_BUFF_NUM                (10U)
#define CANFD_RX_BUFF_ELEM_SIZE          (CANFD_ELEM_SIZE_64BYTES)
#define CANFD_TX_BUFF_SIZE               (10U)
#define CANFD_TX_FQ_SIZE                 (0U)
#define CANFD_TX_BUFF_ELEM_SIZE          (CANFD_ELEM_SIZE_64BYTES)
#define CANFD_TX_EVENT_SIZE              (10U)
#define CANFD_EXT_ID_AND_MASK            (0x1FFFFFFFU)

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
#define CANFD_TX_EVENT_START_ADDR        (CANFD_TX_BUFF_START_ADDR + (CANFD_getMsgObjSize(CANFD_TX_BUFF_ELEM_SIZE) * 4U * (CANFD_TX_BUFF_SIZE + CANFD_TX_FQ_SIZE)))

//
// Global Variables.
//
volatile uint32_t isrIntr1Flag = 1U;
volatile uint16_t monEn = 0x0;
volatile unsigned long msgCount = 0;
volatile unsigned long error = 0;

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
    CANFD_TxBufElement    txMsg;
    CANFD_RxBufElement    rxMsg;
    CANFD_RxNewDataStatus newData;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure GPIO pins for CANTX/CANRX
    //
    Device_initGPIO();
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANFDRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANFDTXA);

    //
    // Globally disable interrupts and clear all NVIC enable/pending bits
    //
    Interrupt_initModule();

    //
    // Initialize RAM vector table and set VTOR; unregistered IRQs use
    // Interrupt_defaultHandler until Interrupt_register() is called
    //
    Interrupt_initVectorTable();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // CANFD interrupt configuration.
    //
    CANFDIntrConfig();

    //
    // Initialize message to transmit.
    //
    txMsg.id       = ((uint32_t)(0x4)) << 18U; // Identifier Value.
    txMsg.rtr      = 0U; // Transmit data frame.
    txMsg.xtd      = 0U; // 11-bit standard identifier.
    txMsg.esi      = 0U; // ESI bit in CAN FD format depends only on error
                         // passive flag.
    txMsg.dlc      = 4U; // CAN + CAN FD: transmit frame has 0-8 data bytes.
    txMsg.brs      = 1U; // CAN FD frames transmitted with bit rate
                         // switching.
    txMsg.fdf      = 1U; // Frame transmitted in CAN FD format.
    txMsg.efc      = 1U; // Store Tx events.
    txMsg.mm       = 0xAAU; // Message Marker.

    //
    // Data bytes.
    //
    txMsg.data[0]  = 0x12;
    txMsg.data[1]  = 0x34;
    txMsg.data[2]  = 0x56;
    txMsg.data[3]  = 0x78;

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

    //
    // Write Tx Message to the Message RAM.
    //
    CANFD_writeMsgRam(CANFDA_DRIVER_BASE, CANFD_MEM_TYPE_BUF, 1U, &txMsg);

    //
    // Enable Transmission interrupt.
    //
    CANFD_txBufTransIntrEnable(CANFDA_DRIVER_BASE, 1U,1U);

    //
    // Add request for transmission.
    //
    CANFD_txBufAddReq(CANFDA_DRIVER_BASE, 1U);

    //
    // Wait for the isrIntr1Flag to be reset.
    //
    while(isrIntr1Flag)
    {
    }

    //
    // Read Message RAM.
    //
    CANFD_readMsgRam(CANFDA_DRIVER_BASE, CANFD_MEM_TYPE_BUF, 0U,
                     CANFD_RX_FIFO_NUM_1, &rxMsg);

    //
    // Get the New Data Status.
    //
    CANFD_getNewDataStatus(CANFDA_DRIVER_BASE, &newData);

    //
    // Check New Data flag for Rx buffer 0.
    //
    if((newData.statusLow & (1UL << 0U)) == 0U)
    {
        ESTOP0;
    }

    //
    // Check that received data matches sent data.
    // Device will halt here during debug if data doesn't match.
    //
    if((txMsg.data[0] != rxMsg.data[0]) ||
       (txMsg.data[1] != rxMsg.data[1]) ||
       (txMsg.data[2] != rxMsg.data[2]) ||
       (txMsg.data[3] != rxMsg.data[3]))
    {
        //
        // Device will halt here if transmitted and received data are
        // not same.
        //
        ESTOP0;
    }
    else
    {
        //
        // Increment message count if message is received.
        //
        msgCount++;
    }

    while(1)
    {
        
    }
}

//
// This function will configure CANFD module.
//
static void CANFDConfig(void)
{
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
    // List Size: Standard ID.
    msgRAMConfigParams.flesa                = CANFD_EXT_ID_FILT_START_ADDR;
    // Extended ID Filter List Start Address.
    msgRAMConfigParams.lse                  = CANFD_EXT_ID_FILTER_NUM;
    // List Size: Extended ID.
    msgRAMConfigParams.txStartAddr          = CANFD_TX_BUFF_START_ADDR;
    // Tx Buffers Start Address.
    msgRAMConfigParams.txBufNum             = CANFD_TX_BUFF_SIZE;
    // Number of Dedicated Transmit Buffers.
    msgRAMConfigParams.txFIFOSize           = CANFD_TX_FQ_SIZE; 
    // Number of Tx FIFO or Tx Queue Elements
    msgRAMConfigParams.txBufMode            = 0U; //Tx FIFO operation
    msgRAMConfigParams.txBufElemSize        = CANFD_TX_BUFF_ELEM_SIZE;
    // Tx Buffer Element Size.
    msgRAMConfigParams.txEventFIFOStartAddr = CANFD_TX_EVENT_START_ADDR;
    // Tx Event FIFO Start Address.
    msgRAMConfigParams.txEventFIFOSize      = CANFD_TX_BUFF_SIZE;
    // Event FIFO Size.
    msgRAMConfigParams.txEventFIFOWaterMark = 3U;
    // Level for Tx Event FIFO watermark interrupt.
    msgRAMConfigParams.rxFIFO0startAddr     = CANFD_FIFO_0_START_ADDR;
    // Rx FIFO0 Start Address.
    msgRAMConfigParams.rxFIFO0size          = CANFD_FIFO_0_NUM;
    // Number of Rx FIFO elements.
    msgRAMConfigParams.rxFIFO0waterMark     = 3U; // Rx FIFO0 Watermark.
    msgRAMConfigParams.rxFIFO0OpMode        = 0U; // FIFO blocking mode.
    msgRAMConfigParams.rxFIFO1startAddr     = CANFD_FIFO_1_START_ADDR;
    // Rx FIFO1 Start Address.
    msgRAMConfigParams.rxFIFO1size          = CANFD_FIFO_1_NUM;
    // Number of Rx FIFO elements.
    msgRAMConfigParams.rxFIFO1waterMark     = 3U; // Level for Rx FIFO 1
                                                  // watermark interrupt.
    msgRAMConfigParams.rxFIFO1OpMode        = 0U; // FIFO blocking mode.
    msgRAMConfigParams.rxBufStartAddr       = CANFD_RX_BUFF_START_ADDR;
    // Rx Buffer Start Address.
    msgRAMConfigParams.rxBufElemSize        = CANFD_RX_BUFF_ELEM_SIZE;
    // Rx Buffer Element Size.
    msgRAMConfigParams.rxFIFO0ElemSize      = CANFD_FIFO_0_ELEM_SIZE;
    // Rx FIFO0 Element Size.
    msgRAMConfigParams.rxFIFO1ElemSize      = CANFD_FIFO_1_ELEM_SIZE;
    // Rx FIFO1 Element Size.

    //
    // Initialize Rx Buffer Configuration parameters.
    //
    stdFiltelem.sfid2              = 0x0U; // Standard Filter ID 2.
    stdFiltelem.sfid1              = 0x4U; // Standard Filter ID 1.
    stdFiltelem.sfec               = 0x7U; // Store into Rx Buffer
    stdFiltelem.sft                = 0x0U; // Range filter from SFID1 to SFID2

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
    // Configure Standard ID filter element
    //
    CANFD_addStdMsgIDFilter(CANFDA_DRIVER_BASE, 0U, &stdFiltelem);

    //
    // Enable external loopback mode
    //
    CANFD_lpbkModeEnable(CANFDA_DRIVER_BASE, CANFD_LPBK_MODE_EXTERNAL, TRUE);

    //
    // Take CANFD out of the SW initialization mode
    //
    CANFD_setOpMode(CANFDA_DRIVER_BASE, CANFD_OPERATION_MODE_NORMAL);

    while (CANFD_OPERATION_MODE_NORMAL != CANFD_getOpMode(CANFDA_DRIVER_BASE));
}


//
// Register and enable the CANFD interrupt in NVIC.
//
static void CANFDIntrConfig(void)
{

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    // This registers the interrupt handler in NVIC vector table.
    //
    Interrupt_register(INT_CANFDA_INT1, &INT_CANFDA_INT1_IRQHandler);

    //
    // Set the priority group to indicate the PREEMPT and SUB priortiy bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    //
    // Set the global and group priority to allow CPU interrupts
    // with higher priority
    //
    Interrupt_setPriority(INT_CANFDA_INT1, 2, 0);

    //
    // Enable the CANFD interrupt in NVIC.
    //
    Interrupt_enable(INT_CANFDA_INT1);

}

//
// This is Interrupt Service Routine for CANFD interrupt 1.
//
void INT_CANFDA_INT1_IRQHandler(void)
{
    uint32_t intrStatus;

    intrStatus = CANFD_getIntrStatus(CANFDA_DRIVER_BASE);

    if((intrStatus & CANFD_INTR_SRC_DEDICATED_RX_BUFF_MSG) ==
        CANFD_INTR_SRC_DEDICATED_RX_BUFF_MSG)
    {
        //
        // Update the flag value.
        //
        isrIntr1Flag = 0U;
    }

    //
    // Clear the interrupt status.
    //
    CANFD_clearIntrStatus(CANFDA_DRIVER_BASE, intrStatus);
}

//
// End of File
//
