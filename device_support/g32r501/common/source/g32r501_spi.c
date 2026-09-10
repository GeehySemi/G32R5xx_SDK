//###########################################################################
//
// FILE:    g32r501_Spi.c
//
// TITLE:   g32r501 SPI Initialization & Support Functions.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
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
// 1. Updated header file title for G32R501 SPI initialization functions.
// 2. Changed file name to g32r501_spi.c to reflect the architecture.
// 3. Adjusted baud rate calculation to match G32R501 specifications.
// 4. Updated SPI register configurations for G32R501 device.
//
//###########################################################################

//
// Included Files
//
#include "g32r501_device.h"      // Headerfile Include File
#include "g32r501_examples.h"    // Examples Include File

//
// Calculate BRR: 7-bit baud rate register value
// SPI CLK freq = 625 kHz
// LSPCLK freq  = CPU freq / 4  (by default)
// BRR          = (LSPCLK freq / SPI CLK freq) - 1
//
// SYSCLK = 200M
// APBCLK = SYSCLK / 2 = 100M
// LSPCLK = APBCLK / 4 = 25M
//
#define SPI_BRR        ((25000000 / 625000) - 1)


//
// InitSPI - This function initializes the SPI to a known state
//
void InitSpi(void)
{
    //
    // Initialize SPI-A
    //
    // Set reset low before configuration changes
    // Clock polarity (0 == rising, 1 == falling)
    // 16-bit character
    // Enable loop-back
    //
    SpiaRegs.SPICFG.bit.SPIRDY = 0;
    SpiaRegs.SPICFG.bit.POLCFG = 0;
    SpiaRegs.SPICFG.bit.CLENSEL = (16-1);
    SpiaRegs.SPICFG.bit.LBEN = 1;

    //
    // Enable master (0 == slave, 1 == master)
    // Enable transmission (TXEN)
    // Clock phase (0 == normal, 1 == delayed)
    // SPI interrupts are disabled
    //
    SpiaRegs.SPICTRL.bit.MSCFG = 1;
    SpiaRegs.SPICTRL.bit.TXEN = 1;
    SpiaRegs.SPICTRL.bit.PHASEL = 0;
    SpiaRegs.SPICTRL.bit.IEN = 0;

    //
    // Set the baud rate
    //
    SpiaRegs.SPIBR.bit.BRSEL = SPI_BRR;

    //
    // Set EMUFREEEN bit
    // Halting on a breakpoint will not halt the SPI
    //
    SpiaRegs.SPIPRICTRL.bit.EMUFREEEN = 1;

    //
    // Release the SPI from reset
    //
    SpiaRegs.SPICFG.bit.SPIRDY = 1;
}

//
// InitSpiGpio - This function initializes GPIO pins to function as SPI pins.
//               Each GPIO pin can be configured as a GPIO pin or up to 3
//               different peripheral functional pins. By default all pins come
//               up as GPIO inputs after reset.
//
//               Caution:
//               For each SPI peripheral
//               Only one GPIO pin should be enabled for SPISOMO operation.
//               Only one GPIO pin should be enabled for SPISOMI operation.
//               Only one GPIO pin should be enabled for SPICLK  operation.
//               Only one GPIO pin should be enabled for SPISTE  operation.
//               Comment out other unwanted lines.
//
void InitSpiGpio()
{
    InitSpiaGpio();
}

//
// InitSpiaGpio - Initialize SPIA GPIOs
//
void InitSpiaGpio()
{
    WRPRT_DISABLE;

    //
    // Enable internal pull-up for the selected pins
    //
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0; // Enable pull-up on GPIO16 (SPISIMOA)
    // GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;  // Enable pull-up on GPIO5 (SPISIMOA)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0; // Enable pull-up on GPIO17 (SPISOMIA)
    // GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;  // Enable pull-up on GPIO3 (SPISOMIA)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0; // Enable pull-up on GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0; // Enable pull-up on GPIO19 (SPISTEA)

    //
    // Set qualification for selected pins to asynch only
    //
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input GPIO16 (SPISIMOA)
    // GpioCtrlRegs.GPAQSEL1.bit.GPIO5 = 3;  // Asynch input GPIO5 (SPISIMOA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input GPIO17 (SPISOMIA)
    // GpioCtrlRegs.GPAQSEL1.bit.GPIO3 = 3;  // Asynch input GPIO3 (SPISOMIA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynch input GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19 (SPISTEA)

    //
    //Configure SPI-A pins using GPIO regs
    //
    // This specifies which of the possible GPIO pins will be SPI functional
    // pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1; // Configure GPIO16 as SPISIMOA
    // GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 2;  // Configure GPIO5 as SPISIMOA
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1; // Configure GPIO17 as SPISOMIA
    // GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 2;  // Configure GPIO3 as SPISOMIA
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1; // Configure GPIO18 as SPICLKA
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1; // Configure GPIO19 as SPISTEA

    WRPRT_ENABLE;
}

//
// End of file
//
