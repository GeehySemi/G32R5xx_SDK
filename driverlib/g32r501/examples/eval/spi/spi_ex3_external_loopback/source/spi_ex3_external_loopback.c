//#############################################################################
//
// FILE:    spi_ex3_external_loopback.c
//
// TITLE:   SPI Digital Loopback without using FIFOs and Interrupts
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1>SPI Digital External Loopback without FIFO Interrupts</h1>
//!
//! This program uses the external loopback between two SPI modules. Both
//! the SPI FIFOs and interrupts are not used in this example. SPIA is
//! configured as a slave and SPI B is configured as master. This example
//! demonstrates full duplex communication where both master and slave transmits
//! and receives data simultaneously.
//!
//!
//! \b External \b Connections \n
//! -GPIO7  and GPIO16 - SPISIMO
//! -GPIO25 and GPIO17 - SPISOMI
//! -GPIO26 and GPIO3  - SPICLK
//! -GPIO27 and GPIO11 - SPISTE
//!
//! \b Watch \b Variables \n
//!  - \b TxData_SPIA - Data send from SPIA (slave)
//!  - \b TxData_SPIB - Data send from SPIB (master)
//!  - \b RxData_SPIA - Data received by SPIA (slave)
//!  - \b RxData_SPIB - Data received by SPIB (master)
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
// 1. Modified some function and macro definition and variable names.
// 2. Updated interrupt handling to use NVIC functions.
//
//###########################################################################

#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Main
//
void example_main(void)
{
    uint16_t i;

    uint16_t TxData_SPIA[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    uint16_t RxData_SPIA[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    uint16_t TxData_SPIB[] = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};
    uint16_t RxData_SPIB[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Initialize NVIC and clear NVIC registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Board initialization
    //
    Board_init();

    //
    // Loop forever. Suspend or place breakpoints to observe the buffers.
    //
    for (i = 0; i < 16; i++)
    {
        
        //
        // Set the TX buffer of slave SPI.
        //
        SPI_writeDataNonBlocking(SPIA_BASE, TxData_SPIA[i]);

        //
        // Set the the master TX buffer. This triggers the data transmission
        //
        SPI_writeDataNonBlocking(SPIB_BASE, TxData_SPIB[i]);

        //
        // Read the received data
        //
        RxData_SPIA[i] = SPI_readDataBlockingNonFIFO(SPIA_BASE);
        RxData_SPIB[i] = SPI_readDataBlockingNonFIFO(SPIB_BASE);

        //
        // Check the received data
        //
        if (RxData_SPIA[i] != TxData_SPIB[i])
        {
            ESTOP0;
        }
        if (RxData_SPIB[i] != TxData_SPIA[i])
        {
            ESTOP0;
        }
    }

    //
    // Loop forever
    //
    while(1);
}
