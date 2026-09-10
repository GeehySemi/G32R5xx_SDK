//#############################################################################
//
// FILE:    uart_ex4_echoback.c
//
// TITLE:   UART echoback example.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1>UART Echoback</h1>
//!
//! This test receives and echo-backs data through the UART-A port. A terminal 
//! such as 'putty' can be used to view the data from the UART and to send 
//! information to the UART. Characters received by the UART port are sent back 
//! to the host.
//!
//! \b Running \b the \b Application \n
//!  Open a COM port with the following settings using a terminal:
//!  -  Find correct COM port
//!  -  Bits per second = 9600
//!  -  Data Bits = 8
//!  -  Parity = None
//!  -  Stop Bits = 1
//!  -  Hardware Control = None
//!
//! The program will print out a greeting and then ask you to enter a character 
//! which it will echo back to the terminal.
//!
//! \b Watch \b Variables \n
//!  - \b loopCounter - The number of characters sent
//!
//! \b External \b Connections \n
//!  Connect the UART-A port to a PC via a transceiver and cable.
//!  - GPIO28 is UART_A-RXD (Connect to Pin3, PC-TX, of serial DB9 cable)
//!  - GPIO29 is UART_A-TXD (Connect to Pin2, PC-RX, of serial DB9 cable)
//!
//#############################################################################
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
// 1. Modified some function and macro definition and variable names.
// 2. Updated interrupt handling to use NVIC functions.
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
// Define AUTOBAUD to use the autobaud lock feature
//#define AUTOBAUD

//
// Globals
//
uint16_t loopCounter = 0;

//
// Main
//
void example_main(void)
{
    uint16_t receivedChar;
    unsigned char *msg;
    uint16_t rxStatus = 0U;

    //
    // Configure PLL, disable WD, enable peripheral clocks.
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // GPIO28 is the UART Rx pin.
    //
    GPIO_setMasterCore(DEVICE_GPIO_PIN_UARTRXDA, GPIO_CORE_CPU0);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_UARTRXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_UARTRXDA, GPIO_DIR_MODE_IN);
    GPIO_setDrivingCapability(DEVICE_GPIO_PIN_UARTRXDA,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_UARTRXDA, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_UARTRXDA, GPIO_QUAL_ASYNC);

    //
    // GPIO29 is the UART Tx pin.
    //
    GPIO_setMasterCore(DEVICE_GPIO_PIN_UARTTXDA, GPIO_CORE_CPU0);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_UARTTXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_UARTTXDA, GPIO_DIR_MODE_OUT);
    GPIO_setDrivingCapability(DEVICE_GPIO_PIN_UARTTXDA,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_UARTTXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_UARTTXDA, GPIO_QUAL_ASYNC);

    //
    // Initialize interrupt controller and vector table.
    //
    Interrupt_initModule();
    Interrupt_initVectorTable();

    //
    // Initialize UARTA and its FIFO.
    //
    UART_performSoftwareReset(UARTA_BASE);

    //
    // Configure UARTA for echoback.
    //
    UART_setConfig(UARTA_BASE, DEVICE_LSPCLK_FREQ, 9600, (UART_CONFIG_WLEN_8 |
                                                        UART_CONFIG_STOP_ONE |
                                                        UART_CONFIG_PAR_NONE));
    UART_resetChannels(UARTA_BASE);
    UART_resetRxFIFO(UARTA_BASE);
    UART_resetTxFIFO(UARTA_BASE);
    UART_clearInterruptStatus(UARTA_BASE, UART_INT_TXFF | UART_INT_RXFF);
    UART_enableFIFO(UARTA_BASE);
    UART_enableModule(UARTA_BASE);
    UART_performSoftwareReset(UARTA_BASE);

#ifdef AUTOBAUD
    //
    // Perform an autobaud lock.
    // UART expects an 'a' or 'A' to lock the baud rate.
    //
    UART_lockAutobaud(UARTA_BASE);
#endif

    //
    // Send starting message.
    //
    msg = (uint8_t*)"\r\n\n\nHello World!\0";
    UART_writeCharArray(UARTA_BASE, msg, 17);
    msg = (uint8_t*)"\r\nYou will enter a character, and the MCU will echo it back!\n\0";
    UART_writeCharArray(UARTA_BASE, msg, 62);

    for (;;)
    {
        msg = (uint8_t*)"\r\nEnter a character: \0";
        UART_writeCharArray(UARTA_BASE, msg, 22);

        //
        // Read a character from the FIFO.
        //
        receivedChar = UART_readCharBlockingFIFO(UARTA_BASE);

        rxStatus = UART_getRxStatus(UARTA_BASE);
        if ((rxStatus & UART_RXSTATUS_ERROR) != 0)
        {
            //
            //If Execution stops here there is some error
            //Analyze UART_getRxStatus() API return value
            //
            ESTOP0;
        }

        //
        // Echo back the character.
        //
        msg = (uint8_t*)"  You sent: \0";
        UART_writeCharArray(UARTA_BASE, msg, 13);
        UART_writeCharBlockingFIFO(UARTA_BASE, receivedChar);

        //
        // Increment the loop count variable.
        //
        loopCounter++;
    }
}

//
// End of File
//

