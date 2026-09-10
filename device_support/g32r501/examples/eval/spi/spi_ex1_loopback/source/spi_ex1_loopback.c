//###########################################################################
//
// FILE:    spi_ex1_loopback.c
//
// TITLE:   SPI Digital Loop Back Example.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup bitfield_example_list
//! <h1>SPI Digital Loop Back </h1>
//!
//!  This program uses the internal loop back test mode of the peripheral.
//!  Other than boot mode pin configuration, no other hardware configuration
//!  is required. Interrupts are not used.
//!
//!  A stream of data is sent and then compared to the received stream.
//!  The sent data looks like this: \n
//!  0000 0001 0002 0003 0004 0005 0006 0007 .... FFFE FFFF \n
//!  This pattern is repeated forever.
//!
//!  \b Watch \b Variables \n
//!  - \b sdata - sent data
//!  - \b rdata - received data
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
// 1. Updated SPI register names for new device.
// 2. Updated interrupt handling to use NVIC functions.
//
//###########################################################################

//
// Included Files
//
#include "g32r501_project.h"

//
// Function Prototypes
//
void transmitData(uint16_t a);
void initSPIFIFO(void);
void error(void);
void InitSpia(void);
void InitSpiaGpios(void);

void example_main(void)
{
    uint16_t sdata;  // sent data
    uint16_t rdata;  // received data

    //
    // Initialize device clock and peripherals
    //
    InitSysCtrl();

    //
    // Initialize GPIO
    //
    InitGpio();
    InitSpiaGpios();

    //
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the NVIC control registers to their default state.
    // The default state is all NVIC interrupts disabled and flags
    // are cleared.
    //
    Interrupt_initModule();

    //
    // Initialize the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Set up SPI, initializing it for FIFO mode
    //
    initSPIFIFO();

    //
    // Loop forever. Suspend or place breakpoints to observe the buffers.
    //
    sdata = 0x0000;
    for (;;)
    {
        //
        // Transmit data
        //
        transmitData(sdata);

        //
        // Wait until data is received
        //
        while(SpiaRegs.SPIRXFIFO.bit.RXFFSTS != 1)
        {

        }

        //
        // Check against sent data
        //
        rdata = SpiaRegs.SPIRXBUF;
        if (rdata != sdata)
        {
            error();
        }
        sdata++;
    }
}

//
// error - Error function that halts the debugger
//
void error(void)
{
    ESTOP0;         // Test failed!! Stop!
    for(;;);
}

//
// transmitData - Transmit value via SPI
//
void transmitData(uint16_t a)
{
    SpiaRegs.SPITXBUF = a;
}

//
// initSPIFIFO - Initialize SPIA FIFO
//
void initSPIFIFO(void)
{
    //
    // Initialize SPI FIFO registers
    //
    SpiaRegs.SPITXFIFO.all = 0xE040;
    SpiaRegs.SPIRXFIFO.all = 0x2044;
    SpiaRegs.SPIFFCTRL.all = 0x0;

    //
    // Initialize core SPI registers
    //
    InitSpia();
}

//
// InitSPI - This function initializes the SPI to a known state
//
void InitSpia(void)
{
    //
    // Initialize SPI-A
    //

    //
    // Set reset low before configuration changes
    // Clock polarity (0 == rising, 1 == falling)
    // 16-bit character
    // Enable loop-back
    //
    SpiaRegs.SPICFG.bit.SPIRDY = 0;
    SpiaRegs.SPICFG.bit.POLCFG = 0;
    SpiaRegs.SPICFG.bit.CLENSEL = (16 - 1);
    SpiaRegs.SPICFG.bit.LBEN = 1;

    //
    // Enable master (0 == slave, 1 == master)
    // Enable transmission (Talk)
    // Clock phase (0 == normal, 1 == delayed)
    // SPI interrupts are disabled
    //
    SpiaRegs.SPICTRL.bit.MSCFG = 1;
    SpiaRegs.SPICTRL.bit.TXEN = 1;
    SpiaRegs.SPICTRL.bit.PHASEL = 0;
    SpiaRegs.SPICTRL.bit.IEN = 0;

    //
    // Set the baud rate using a 1.25 MHz SPICLK
    // BRR = (LSPCLK / SPICLK) - 1
    //
    // SYSCLK = 200M
    // APBCLK = SYSCLK / 2 = 100M
    // LSPCLK = APBCLK / 4 = 25M
    //
    SpiaRegs.SPIBR.bit.BRSEL = ((25000000 / 1250000) - 1);

    // Set FREE bit
    // Halting on a breakpoint will not halt the SPI
    //
    SpiaRegs.SPIPRICTRL.bit.EMUFREEEN = 1;

    //
    // Release the SPI from reset
    //
    SpiaRegs.SPICFG.bit.SPIRDY = 1;
}


void InitSpiaGpios(void)
{
    WRPRT_DISABLE;

    //
    // Enable internal pull-up for the selected pins
    //
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;  // Enable pull-up on GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;  // Enable pull-up on GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPBPUD.bit.GPIO56 = 0;  // Enable pull-up on GPIO56 (SPICLKA)
    GpioCtrlRegs.GPBPUD.bit.GPIO57 = 0;  // Enable pull-up on GPIO57 (SPISTEA)

    //
    // Set qualification for selected pins to asynch only
    //
    // This will select asynch (no qualification) for the selected pins.
    //
    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = 3; // Asynch input GPIO56 (SPICLKA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO57 = 3; // Asynch input GPIO57 (SPISTEA)

    //
    // Configure SPI-A pins
    //
    // This specifies which of the possible GPIO pins will be SPI functional
    // pins.
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1; // Configure GPIO16 as SPISIMOA
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1; // Configure GPIO17 as SPISOMIA
    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 1; // Configure GPIO56 as SPICLKA
    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 1; // Configure GPIO57 as SPISTEA

    WRPRT_ENABLE;
}

//
// End of file
//
