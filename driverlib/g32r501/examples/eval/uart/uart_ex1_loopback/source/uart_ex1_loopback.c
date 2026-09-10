//###########################################################################
//
// FILE:    uart_ex1_loopback.c
//
// TITLE:   UART FIFO Digital Loop Back.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1>UART FIFO Digital Loop Back</h1>
//!
//! This program uses the internal loop back test mode of the peripheral. 
//!  Other than boot mode pin configuration, no other hardware configuration is 
//!  required. This test uses the loopback test mode of the UART module to send 
//!  characters starting with 0x00 through 0xFF. The test will send a character 
//!  and then check the receive buffer for a correct match.
//!
//! \b Watch \b Variables \n
//!  - \b loopCount - Number of characters sent
//!  - \b errorCount - Number of errors detected
//!  - \b sendChar - Character sent
//!  - \b receivedChar - Character received
//!
//
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
#include "board.h"

//
// Globals
//
uint16_t loopCount;
uint16_t errorCount;

//
// Function Prototypes
//
void error();

//
// Main
//
void example_main(void)
{
    uint16_t sendChar;
    uint16_t receivedChar;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Setup GPIO by disabling pin locks and enabling pullups
    //
    Device_initGPIO();

    //
    // Initialize NVIC and clear NVIC registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    // Initialize the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Board Initialization
    //
    Board_init();

    //
    // Enables CPU interrupts
    //
    Interrupt_enableMaster();

    //
    // Initialize counts
    //
    loopCount = 0;
    errorCount = 0;

    //
    // Send a character starting with 0
    //
    sendChar = 0;

    //
    // Send Characters forever starting with 0x00 and going through 0xFF.
    // After sending each, check the receive buffer for the correct value.
    //
    for (;;)
    {
        UART_writeCharNonBlocking(myUART0_BASE, sendChar);

        //
        // Wait for RRDY/RXFFST = 1 for 1 data available in FIFO
        //
        while (UART_getRxFIFOStatus(myUART0_BASE) == UART_FIFO_RX0)
        {
        }

        //
        // Check received character
        //
        receivedChar = UART_readCharBlockingFIFO(myUART0_BASE);

        //
        // Received character not correct
        //
        if (receivedChar != sendChar)
        {
            errorCount++;
            ESTOP0;
        }

        //
        // Move to the next character and repeat the test
        //
        sendChar++;

        //
        // Limit the character to 8-bits
        //
        sendChar &= 0x00FF;
        loopCount++;

    }
}

//
// End of file
//
