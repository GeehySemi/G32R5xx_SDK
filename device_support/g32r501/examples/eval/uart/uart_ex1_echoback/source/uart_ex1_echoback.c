//#############################################################################
//
// FILE:    uart_ex1_echoback.c
//
// TITLE:   UART Echoback Example.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup bitfield_example_list
//! <h1>UART Echoback</h1>
//!
//!  This test receives and echo-backs data through the UART-A port.
//!
//!  A terminal such as 'putty' can be used to view the data from
//!  the UART and to send information to the UART. Characters received
//!  by the UART port are sent back to the host.
//!
//!  \b Running \b the \b Application
//!  Open a COM port with the following settings using a terminal:
//!  -  Find correct COM port
//!  -  Bits per second = 9600
//!  -  Data Bits = 8
//!  -  Parity = None
//!  -  Stop Bits = 1
//!  -  Hardware Control = None
//!
//!  The program will print out a greeting and then ask you to
//!  enter a character which it will echo back to the terminal.
//!
//!  \b Watch \b Variables \n
//!  - loopCounter - the number of characters sent
//!
//! \b External \b Connections \n
//!  Connect the UART-A port to a PC via a transceiver and cable.
//!  - GPIO28 is UART_A-RXD (Connect to Pin3, PC-TX, of serial DB9 cable)
//!  - GPIO29 is UART_A-TXD (Connect to Pin2, PC-RX, of serial DB9 cable)
//!
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
// 1. Replaced SCIA references with UARTA for the new device.
// 2. Updated GPIO setup and UART initialization functions.
// 3. Updated interrupt handling to use NVIC functions.
//
//###########################################################################

//
// Included Files
//
#include "g32r501_device.h"
#include "g32r501_examples.h"

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
// Function Prototypes
//
void initUARTAEchoback(void);
void transmitUARTAChar(uint16_t a);
void transmitUARTAMessage(unsigned char * msg);
void initUARTAFIFO(void);

//
// Main
//
void example_main(void)
{
    uint16_t ReceivedChar;
    unsigned char *msg;

    //
    // Initialize device clock and peripherals
    //
    InitSysCtrl();

    //
    // Initialize GPIO
    //
    InitGpio();

    //
    // For this example, only init the pins for the UART-A port.
    // GPIO_SetupPinMux() - Sets the GPxMUX1/2 and GPyMUX1/2 register bits
    // GPIO_SetupPinOptions() - Sets the direction and configuration of GPIOs
    //
    GPIO_SetupPinMux(28, GPIO_MUX_CPU0, 1);
    GPIO_SetupPinOptions(28, GPIO_INPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(29, GPIO_MUX_CPU0, 1);
    GPIO_SetupPinOptions(29, GPIO_OUTPUT, GPIO_ASYNC);

    //
    // Disable CPU interrupts
    //
    DINT;

    //
    //Initialize the NVIC control registers to their default state.
    //The default state is all NVIC interrupts disabled and flags
    //are cleared.
    //
    Interrupt_initModule();

    //
    //Initialize the NVIC vector table with pointers to the shell Interrupt
    //Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Initialize the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR)
    //
    //InitPieVectTable();

    loopCounter = 0;

    initUARTAFIFO();                         // Initialize the UART FIFO
    initUARTAEchoback();                     // Initialize UART for echoback

    msg = (unsigned char*)"\r\n\n\nHello World!\0";
    transmitUARTAMessage(msg);

    msg = (unsigned char*)"\r\nYou will enter a character, and the DSP will echo it back! \n\0";
    transmitUARTAMessage(msg);

    for(;;)
    {
        msg = (unsigned char*)"\r\nEnter a character: \0";
        transmitUARTAMessage(msg);

        //
        // Wait for character
        //
        while(UartaRegs.UARTFFRX.bit.RXFFST == 0)
        {

        } // wait for empty state

        //
        // Get character
        //
        ReceivedChar = UartaRegs.UARTRXBUF.all;

        //
        // Echo character back
        //
        msg = (unsigned char*)"  You sent: \0";
        transmitUARTAMessage(msg);
        transmitUARTAChar(ReceivedChar);

        loopCounter++;
    }
}

//
//  initUARTAEchoback - Initialize UART-A for echoback
//
void initUARTAEchoback(void)
{
    //
    // Note: Clocks were turned on to the UARTA peripheral
    // in the InitSysCtrl() function
    //
    UartaRegs.UARTCCR.all = 0x0007;         // 1 stop bit,  No loopback
                                            // No parity, 8 char bits,
                                            // async mode, idle-line protocol
    UartaRegs.UARTCTL1.all = 0x0003;        // enable TX, RX, internal UARTCLK,
                                            // Disable RX ERR, SLEEP, TXWAKE
    UartaRegs.UARTCTL2.all = 0x0003;
    UartaRegs.UARTCTL2.bit.TXINTENA = 1;
    UartaRegs.UARTCTL2.bit.RXBKINTENA = 1;

    //
    // UARTA at 9600 baud
    // @LSPCLK = 25 MHz (200 MHz SYSCLK) HBAUD = 0x01  and LBAUD = 0x45.
    // UART Asynchronous Baud = LSPCLK / ((BRR + 1) *8)
    // BRR = (UARTHBAUD << 8) + (UARTLBAUD)
    //
    UartaRegs.UARTHBAUD.all = 0x0001;
    UartaRegs.UARTLBAUD.all = 0x0045;

    UartaRegs.UARTCTL1.all = 0x0023;          // Relinquish UART from Reset
}

//
// transmitUARTAChar - Transmit a character from the UART
//
void transmitUARTAChar(uint16_t a)
{
    while (UartaRegs.UARTFFTX.bit.TXFFST != 0)
    {

    }
    UartaRegs.UARTTXBUF.all = a;
}

//
// transmitUARTAMessage - Transmit message via UARTA
//
void transmitUARTAMessage(unsigned char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        transmitUARTAChar(msg[i]);
        i++;
    }
}

//
// initUARTAFIFO - Initialize the UART FIFO
//
void initUARTAFIFO(void)
{
    UartaRegs.UARTFFTX.all = 0xE040;
    UartaRegs.UARTFFRX.all = 0x2044;
    UartaRegs.UARTFFCT.all = 0x0;
}

//
// End of file
//
