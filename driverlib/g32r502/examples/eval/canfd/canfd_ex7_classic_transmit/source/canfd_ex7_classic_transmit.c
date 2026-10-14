//#############################################################################
//
// FILE:   canfd_ex7_classic_transmit.c
//
// TITLE:  CANFD Classic frames transmission using Tx Buffer
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//
//! \addtogroup driver_example_c28x_list
//! <h1> CANFD Classic frames transmission using Tx Buffer </h1>
//!
//! This simple example shows external communication between the CANFD module
//! and another CAN node. It shows how to transmit classic CAN frames.
//! The GPIOs of CANFD should be connected to a CAN Transceiver.
//! Nominal bit rate 1 Mbps (CANFD bit clock: 20 MHz XTAL, classic CAN).
//! Extended Identifier 0x15A5A5A5 is transmitted with
//! 8 data bytes.
//!
//! \b Hardware \b Required \n
//!  - G32R502 evaluation board with CAN FD transceiver
//!
//! \b External \b Connections \n
//!  Both nodes should communicate through CAN transceivers.
//!
//!  - CANFD is on DEVICE_GPIO_PIN_CANRXA (CANFDRXA)
//!  - and DEVICE_GPIO_PIN_CANTXA (CANFDTXA)
//!
//! \b Watch \b Variables \n
//!  - txMsg
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
#define NUM_OF_MSG                      (1U)
#define CANFD_STD_ID_FILTER_NUM          (0U)
#define CANFD_EXT_ID_FILTER_NUM          (0U)
#define CANFD_FIFO_0_NUM                 (0U)
#define CANFD_FIFO_0_ELEM_SIZE           (CANFD_ELEM_SIZE_64BYTES)
#define CANFD_FIFO_1_NUM                 (0U)
#define CANFD_FIFO_1_ELEM_SIZE           (CANFD_ELEM_SIZE_64BYTES)
#define CANFD_RX_BUFF_NUM                (0U)
#define CANFD_RX_BUFF_ELEM_SIZE          (CANFD_ELEM_SIZE_64BYTES)
#define CANFD_TX_BUFF_SIZE               (NUM_OF_MSG)
#define CANFD_TX_FQ_SIZE                 (0U)
#define CANFD_TX_BUFF_ELEM_SIZE          (CANFD_ELEM_SIZE_8BYTES)
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
CANFD_TxBufElement txMsg[NUM_OF_MSG];
int32_t loopCnt = 0U;

//
// Function Prototype.
//
static void CANFDConfig(void);

//
// Main
//
void example_main()
{
    int i = 0;
    uint32_t dataBytes = 8;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure GPIO pins for CANTX/CANRX
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
    // Configuring the GPIOs for CANFD.
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANFDRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANFDTXA);

    //
    // Initialize message to transmit.
    //
    txMsg[loopCnt].id       = ((uint32_t)(0x15A5A5A5)) ;
    txMsg[loopCnt].rtr      = 0U;
    txMsg[loopCnt].xtd      = 1U;
    txMsg[loopCnt].esi      = 0U;
    txMsg[loopCnt].dlc      = 8U;
    txMsg[loopCnt].brs      = 0U;
    txMsg[loopCnt].fdf      = 0U;
    txMsg[loopCnt].efc      = 1U;
    txMsg[loopCnt].mm       = 0xAAU;
    txMsg[loopCnt].data[i]  = 0x1;
    for(i = 1; i < dataBytes; i++)
    {
        txMsg[loopCnt].data[i]  = txMsg[loopCnt].data[i-1] + 1;
    }
    i = 0;

    //
    // Configure the CANFD Module.
    //
    CANFDConfig();

    //
    // Write message to Message RAM.
    //
    CANFD_writeMsgRam(CANFDA_DRIVER_BASE, CANFD_MEM_TYPE_BUF, loopCnt,
                     &txMsg[loopCnt]);

    while(1)
    {
        //
        // Add request for all transmission.
        //
        CANFD_txBufAddReq(CANFDA_DRIVER_BASE, 0U);

        //
        // Wait till all the messages are transmitted.
        //
        while(CANFD_getTxBufReqPend(CANFDA_DRIVER_BASE))
        {
        }
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
    CANFD_BitTimingParams       bitTimes;

    //
    //  Initializing all structs to zero to prevent stray values
    //
    memset(&initParams, 0, sizeof(initParams));
    memset(&msgRAMConfigParams, 0, sizeof(msgRAMConfigParams));
    memset(&bitTimes, 0, sizeof(bitTimes));

    //
    // CANFD bit clock = XTAL (20 MHz).
    //
    CANFD_selectClockSource(CANFDA_DRIVER_BASE, CANFD_CLOCK_SOURCE_XTAL);

    //
    // Initialize CANFD Init parameters.
    //
    initParams.fdMode            = 0x0U; // FD operation disabled.
    initParams.brsEnable         = 0x0U; // Bit rate switching for
                                         // transmissions disabled.

    //
    // Initialize Message RAM Sections Configuration Parameters
    //
    msgRAMConfigParams.txStartAddr          = CANFD_TX_BUFF_START_ADDR;
    // Tx Buffers Start Address.
    msgRAMConfigParams.txBufNum             = CANFD_TX_BUFF_SIZE;
    // Number of Dedicated Transmit Buffers.
    msgRAMConfigParams.txBufMode            = 0U;
    msgRAMConfigParams.txBufElemSize        = CANFD_TX_BUFF_ELEM_SIZE;
    // Tx Buffer Element Size.

    //
    // Initialize bit timings (20MHz XTAL: 1M nominal, classic CAN).
    // CANFD: TQ = NTSEG1 + NTSEG2 + 3; f_bit = f_canfd / ((BRP+1) * TQ)
    //
    bitTimes.nomRatePrescalar   = 0x1U; // Nominal Baud Rate Pre-scaler
    bitTimes.nomTimeSeg1        = 0x6U; // Nominal Time segment before SP
    bitTimes.nomTimeSeg2        = 0x1U; // Nominal Time segment after SP
    bitTimes.nomSynchJumpWidth  = 0x1U; // Nominal SJW

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
    // Take CANFD out of the SW initialization mode
    //
    CANFD_setOpMode(CANFDA_DRIVER_BASE, CANFD_OPERATION_MODE_NORMAL);

    while (CANFD_OPERATION_MODE_NORMAL != CANFD_getOpMode(CANFDA_DRIVER_BASE))
    {

    }
}
