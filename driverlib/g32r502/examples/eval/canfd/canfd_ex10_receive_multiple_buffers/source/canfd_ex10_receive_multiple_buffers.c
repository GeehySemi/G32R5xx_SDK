//#############################################################################
//
// FILE:   canfd_ex10_receive_multiple_buffers.c
//
// TITLE:  CANFD receive multiple messages using Rx Buffer
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//
//! \addtogroup driver_example_c28x_list
//! <h1> CANFD receive using Rx Buffer </h1>
//!
//! This example demonstrates how to receive CANFD messages in multiple buffers,
//! including the configuration and handling of the messages. Communication is done
//! between atleast two CAN nodes. The transmitting node could be another MCU or a
//! CAN bus analysis tool capable of transmitting CAN FD frames. The transmit
//! and receive pins of the CANFD module should be connected to a CAN
//! transceiver. Nominal bit rate 1 Mbps and data bit rate 2 Mbps (CANFD bit
//! clock: 20 MHz XTAL).
//!
//! Standard frames with message IDs 0x123, 0x124, 0x125, 0x126 are received.
//! (For Extended frames, same procedure to be followed for configuration
//!   by adding Extended Message ID Filter Element(s))
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
//!  - rxMsg
//!
//
//#############################################################################
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
// 1. Align CANFD example with G32R502 eval board pinout and driverlib APIs.
//
//#############################################################################

//
// Include Files
//
#include "driverlib.h"
#include "device.h"
#include "inc/stw_types.h"
#include "inc/stw_dataTypes.h"
#include <string.h>

//
// Defines.
//
#define NUM_OF_MSG                      (4U)
#define CANFD_STD_ID_FILTER_NUM          (4U)
#define CANFD_EXT_ID_FILTER_NUM          (0U)
#define CANFD_FIFO_0_NUM                 (0U)
#define CANFD_FIFO_0_ELEM_SIZE           (CANFD_ELEM_SIZE_64BYTES)
#define CANFD_FIFO_1_NUM                 (0U)
#define CANFD_FIFO_1_ELEM_SIZE           (CANFD_ELEM_SIZE_64BYTES)
#define CANFD_RX_BUFF_NUM                (10U)
#define CANFD_RX_BUFF_ELEM_SIZE          (CANFD_ELEM_SIZE_64BYTES)
#define CANFD_TX_BUFF_SIZE               (0U)
#define CANFD_TX_FQ_SIZE                 (0U)
#define CANFD_TX_BUFF_ELEM_SIZE          (CANFD_ELEM_SIZE_64BYTES)
#define CANFD_TX_EVENT_SIZE              (0U)

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
int32_t     error = 0;
CANFD_RxBufElement rxMsg[NUM_OF_MSG];
int32_t loopCnt = 0U;


//
// Function Prototype.
//
static void CANFDConfig(void);
static void CANFDIntrConfig(void);
void INT_CANFDA_INT1_IRQHandler(void);

//
// Main
//
void example_main()
{
    int i = 0;
    uint32_t dataBytes = 64;

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
    // Configure the divisor for the CANFD bit-clock
    //
        //
    // ISR Configuration.
    //
    CANFDIntrConfig();

    //
    // Configure GPIO pins for CANFDTX/CANFDRX operation
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANFDRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANFDTXA);

    for(loopCnt = 0; loopCnt < NUM_OF_MSG; loopCnt++)
    {
      //
      // Initialize message to receive
      //
      rxMsg[loopCnt].id = 0U;
      rxMsg[loopCnt].rtr = 0U;
      rxMsg[loopCnt].xtd = 0U;
      rxMsg[loopCnt].esi = 0U;
      rxMsg[loopCnt].rxts = 0U;   // Rx Timestamp
      rxMsg[loopCnt].dlc = 0U;
      rxMsg[loopCnt].brs = 0U;
      rxMsg[loopCnt].fdf = 0U;
      rxMsg[loopCnt].fidx = 0U;   // Filter Index
                                  // (of matching Rx acceptance filter element)
      rxMsg[loopCnt].anmf = 0U;   // Accepted Non-matching Frame

      for(i = 0; i < dataBytes; i++)  // Initialize receive buffer to 0
      {
          rxMsg[loopCnt].data[i]  = 0;
      }
    }

    //
    // Configure the CANFD Module.
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

    for(;;)
    {
        //
        //  Adding delay of 1 second
        //
        DEVICE_DELAY_US(1000000);

        //
        //  Message handling code goes here
        //

    }

    //
    // Stop Application.
    //
    ESTOP0;
}

//
// CANFDConfig - CANFD Config.
//
static void CANFDConfig(void)
{
    CANFD_InitParams initParams;
    CANFD_MsgRAMConfigParams    msgRAMConfigParams;
    CANFD_StdMsgIDFilterElement stdFiltelem;
    CANFD_BitTimingParams       bitTimes;

    //
    //  Initializing all structs to zero to prevent stray values
    //
    memset(&initParams, 0, sizeof(initParams));
    memset(&msgRAMConfigParams, 0, sizeof(msgRAMConfigParams));
    memset(&stdFiltelem, 0, sizeof(stdFiltelem));
    memset(&bitTimes, 0, sizeof(bitTimes));

    //
    // CANFD bit clock = XTAL (20 MHz).
    //
    CANFD_selectClockSource(CANFDA_DRIVER_BASE, CANFD_CLOCK_SOURCE_XTAL);

    //
    // Configure CANFD initialization parameters
    //
    initParams.fdMode            = 0x1U; // FD operation enabled.
    initParams.brsEnable         = 0x1U; // Bit rate switching enabled
    initParams.wakeIntEnable     = 0x1U;
    initParams.tdcEnable         = 0x1U;
    initParams.tdcConfig.tdcf    = 0x2U;
    initParams.tdcConfig.tdco    = 0x4U;

    //
    // Initialize Message RAM Sections Configuration Parameters
    //
    msgRAMConfigParams.flssa                = CANFD_STD_ID_FILT_START_ADDR;
    // Standard ID Filter List Start Address.
    msgRAMConfigParams.lss                  = CANFD_STD_ID_FILTER_NUM;
    // List Size: Standard ID.
    msgRAMConfigParams.rxBufStartAddr       = CANFD_RX_BUFF_START_ADDR;
    // Rx Buffer Start Address.
    msgRAMConfigParams.rxBufElemSize        = CANFD_RX_BUFF_ELEM_SIZE;
    // Rx Buffer Element Size.

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
    while (CANFD_OPERATION_MODE_SW_INIT != CANFD_getOpMode(CANFDA_DRIVER_BASE))
    {}

    //
    // Initialize CANFD module.
    //
    CANFD_init(CANFDA_DRIVER_BASE, &initParams);

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
    stdFiltelem.sfec               = 0x7U; // Store into Rx Buffer
                                           // configuration of SFT[1:0] ignored

    //
    // Configuring SFID2[10:9] = 0 to store message in RX Buffer
    // SFID2[5:0] defines which RX Buffer element received message
    // will be stored into (among upto 64 buffer elements)
    // Frames matching different filter elements cannot be
    // configured to be stored in the same buffer element
    // i.e. SFID2[5:0] HAS to be distinct for every filter element
    //


    //
    // Configure Standard ID filter element 0
    //
    stdFiltelem.sfid2              = 0x0U; // Standard Filter ID 2.
    stdFiltelem.sfid1              = 0x123U; // Standard Filter ID 1.

    CANFD_addStdMsgIDFilter(CANFDA_DRIVER_BASE, 0U, &stdFiltelem);

    //
    // Configure Standard ID filter element 1
    //
    stdFiltelem.sfid2              = 0x1U; // Standard Filter ID 2.
    stdFiltelem.sfid1              = 0x124U; // Standard Filter ID 1.

    CANFD_addStdMsgIDFilter(CANFDA_DRIVER_BASE, 1U, &stdFiltelem);

    //
    // Configure Standard ID filter element 2
    //
    stdFiltelem.sfid2              = 0x2U; // Standard Filter ID 2.
    stdFiltelem.sfid1              = 0x125U; // Standard Filter ID 1.

    CANFD_addStdMsgIDFilter(CANFDA_DRIVER_BASE, 2U, &stdFiltelem);

    //
    // Configure Standard ID filter element 3
    //
    stdFiltelem.sfid2              = 0x3U; // Standard Filter ID 2.
    stdFiltelem.sfid1              = 0x126U; // Standard Filter ID 1.

    CANFD_addStdMsgIDFilter(CANFDA_DRIVER_BASE, 3U, &stdFiltelem);

    //
    // Take CANFD out of the SW initialization mode
    //
    CANFD_setOpMode(CANFDA_DRIVER_BASE, CANFD_OPERATION_MODE_NORMAL);

    while (CANFD_OPERATION_MODE_NORMAL != CANFD_getOpMode(CANFDA_DRIVER_BASE))
    {

    }

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
    CANFD_RxNewDataStatus newData;

    intrStatus = CANFD_getIntrStatus(CANFDA_DRIVER_BASE);

    //
    // Clear the interrupt Status.
    //
    CANFD_clearIntrStatus(CANFDA_DRIVER_BASE, intrStatus);

    //
    //  Clearing the interrupt lineNum
    //
    //
    //  Check to see if the interrupt is caused by a message being
    //  received in dedicated RX Buffers
    //
    if((CANFD_IR_DRX_MASK & intrStatus) == CANFD_IR_DRX_MASK)
    {
        //
        // Read the NewData registers
        //
        CANFD_getNewDataStatus(CANFDA_DRIVER_BASE, &newData);

        //  If message is received in buffer element 0
        if((newData.statusLow & (1UL << 0U)) != 0)
        {
            CANFD_readMsgRam(CANFDA_DRIVER_BASE, CANFD_MEM_TYPE_BUF, 0U,
                          0, &rxMsg[0]);
        }
        //  If message is received in buffer element 1
        if((newData.statusLow & (1UL << 1U)) != 0)
        {
            CANFD_readMsgRam(CANFDA_DRIVER_BASE, CANFD_MEM_TYPE_BUF, 1U,
                          0, &rxMsg[1]);
        }
        if((newData.statusLow & (1UL << 2U)) != 0)
        {
            CANFD_readMsgRam(CANFDA_DRIVER_BASE, CANFD_MEM_TYPE_BUF, 2U,
                          0, &rxMsg[2]);
        }
        if((newData.statusLow & (1UL << 3U)) != 0)
        {
            CANFD_readMsgRam(CANFDA_DRIVER_BASE, CANFD_MEM_TYPE_BUF, 3U,
                          0, &rxMsg[3]);
        }

        //
        //  Clearing the NewData registers
        //
        CANFD_clearNewDataStatus(CANFDA_DRIVER_BASE, &newData);
    }
    else
    {
        error++;

        //
        //  Interrupt handling for other interrupt sources goes here
        //

    }

    //
    // Acknowledge this interrupt located in group 9
    //
}
