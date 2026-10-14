//#############################################################################
//
// FILE:    can_ex8_mask.c
//
// TITLE:   CAN Acceptance Mask Example
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1> CAN example that illustrates the usage of Mask registers </h1>
//!
//! This example initializes CAN module A for Reception. When a frame with a
//! matching filter criterion is received, the data will be copied in mailbox 1
//! and LED will be toggled a few times and the code gets ready for the next
//! frame. If a message of any other MSGID is received, an ACK will be provided
//! Completion of reception is determined by polling CAN_NDAT_21 register.
//! No interrupts are used.
//!
//! \b Hardware \b Required \n
//!  - An external CAN node that transmits to CAN-A on the G32R5xx MCU
//!
//! \b JTAG \b / \b Debug \b Note \n
//!  This example uses GPIO35 (EVAL LD1), which is muxed with JTAG TDI on
//!  G32R502 EVAL. Using it as GPIO or LED may prevent subsequent program
//!  download or debug over JTAG until power cycle or debugger reconnect
//!  restores the default JTAG pinmux. SWD debugging is recommended for
//!  this example.
//!
//! \b Watch \b Variables \n
//!  - rxMsgCount - A counter for the number of messages received
//!  - rxMsgData - An array with the data that was received
//!
//
//! \b External \b Connections \n
//!  - CAN loopback or second node on CANH/CANL (see board CAN transceiver).
//!
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
// 1. Modify some comments, macros, global variables, function names,
//    and function contents.
//
//###########################################################################


//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define MSG_DATA_LENGTH    0    // "Don't care" for a Receive mailbox
#define RX_MSG_OBJ_ID      1    // Use mailbox 1

//
// Globals
//
uint8_t rxMsgData[8];           // Buffer for received data
uint16_t Toggle_ctr;            // GPIO toggle counter
volatile uint32_t rxMsgCount = 0;

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
    // Globally disable interrupts and clear all NVIC enable/pending bits
    //
    Interrupt_initModule();

    //
    // Initialize RAM vector table and set VTOR; unregistered IRQs use
    // Interrupt_defaultHandler until Interrupt_register() is called
    //
    Interrupt_initVectorTable();

    //
    // Initialize GPIO
    //
    Device_initGPIO();

    //
    // Configure GPIO pins for CANTX/CANRX
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANTXA);

    //
    // Configure LD1 (GPIO35); GPIO_setPinConfig required to leave JTAG TDI mux.
    // EVAL LED is active-low: write 1 for off before waiting for RX.
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED1);
    GPIO_setDrivingCapability(DEVICE_GPIO_PIN_LED1, GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_LED1, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 1U);

    //
    // Initialize the receive buffer to a known value
    //
    rxMsgData[0] = 0x5A;
    rxMsgData[1] = 0x5A;
    rxMsgData[2] = 0x5A;
    rxMsgData[3] = 0x5A;
    rxMsgData[4] = 0x5A;
    rxMsgData[5] = 0x5A;
    rxMsgData[6] = 0x5A;
    rxMsgData[7] = 0x5A;

    //
    // Initialize the CAN controller
    //
    CAN_initModule(CANA_BASE);

    //
    // CANA bit clock = APBCLK.
    //
    CAN_selectClockSource(CANA_BASE, CAN_CLOCK_SOURCE_APB);

    //
    // Set up the CAN bus bit rate to 500kbps for each module
    // Refer to the Driver Library User Guide for information on how to set
    // tighter timing control. Additionally, consult the device data sheet
    // for more information about the CAN module clocking.
    //
    CAN_setBitRate(CANA_BASE, DEVICE_APBCLK_FREQ, 500000, 25);

    //
    // Initialize the receive message object used for receiving CAN messages.
    // Possible flags: CAN_MSG_OBJ_NO_FLAGS, CAN_MSG_OBJ_USE_EXT_FILTER,
    //                 CAN_MSG_OBJ_USE_DIR_FILTER
    // Message Object Parameters:
    //      CAN Module: A
    //      Message Object ID Number: 1
    //      Message Identifier: 0x1F9FFFFA
    //      Message Frame: Extended
    //      Message Type: Receive
    //      Message ID Mask: 0x1F000000
    //      Message Object Flags: UMask, MXtd, MDir
    //      Message Object flag CAN_MSG_OBJ_USE_ID_FILTER enables usage 
    //       of msgIDMask parameter for Message Identifier based filtering
    //      Message Object flag CAN_MSG_OBJ_USE_EXT_FILTER enables usage 
    //       of frameType parameter for Message Frame based filtering
    //      Message Data Length: "Don't care" for a Receive mailbox
    CAN_setupMessageObject(CANA_BASE, RX_MSG_OBJ_ID, 0x1F9FFFFA,
                           CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_RX, 0x1F000000,
                           (CAN_MSG_OBJ_USE_ID_FILTER | CAN_MSG_OBJ_NO_FLAGS |
                           CAN_MSG_OBJ_USE_EXT_FILTER), MSG_DATA_LENGTH);

    //
    // Start CAN module A operations
    //
    CAN_startModule(CANA_BASE);

    //
    // Start reception - Just wait for data from another node
    //
    while(1)
    {
        //
        // Poll bit0 in CAN_NDAT_21 register to check completion of Reception
        //
        if((HWREG_BP(CANA_BASE + CAN_O_NDATA))  == 0x00000001)
        {
            //
            // Get the received message
            //
            __asm("  NOP");
            CAN_readMessage(CANA_BASE, RX_MSG_OBJ_ID, rxMsgData);

            rxMsgCount++;
            for(Toggle_ctr=0; Toggle_ctr<10; Toggle_ctr++)
            {
                GPIO_togglePin(DEVICE_GPIO_PIN_LED1);
                DEVICE_DELAY_US(100000);
            }
        }
    }
}

//
// End of File
//
