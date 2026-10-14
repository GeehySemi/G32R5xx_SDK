//#############################################################################
//
// FILE:    interrupt_ex2_with_i2c_uart_spi_loopback.c
//
// TITLE:   Multiple interrupt handling of I2C, UART & SPI Digital Loopback
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1>Multiple interrupt handling of I2C, UART & SPI Digital Loopback</h1>
//!
//! This program is used to demonstrate how to handle multiple interrupts
//! when using multiple communication peripherals like I2C, UART & SPI
//! Digital Loopback all in a single example. The data transfers would
//! be done with FIFO Interrupts.
//!
//! It uses the internal loopback test mode of these modules. Both
//! the TX and RX FIFOs and their interrupts are used.
//! Other than boot mode pin configuration, no other hardware configuration
//! is required.
//!
//! A stream of data is sent and then compared to the received stream.
//! The sent data looks like this for I2C and UART: \n
//!  0000 0001 \n
//!  0001 0002 \n
//!  0002 0003 \n
//!  .... \n
//!  00FE 00FF \n
//!  00FF 0000 \n
//!  etc.. \n
//!
//! The sent data looks like this for SPI: \n
//!  0000 0001 \n
//!  0001 0002 \n
//!  0002 0003 \n
//!  .... \n
//!  FFFE FFFF \n
//!  FFFF 0000 \n
//!  etc.. \n
//!
//! This pattern is repeated forever.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - \b sDatai2cA   - Data to send through I2C
//!  - \b rDatai2cA   - Received I2C data
//!  - \b rDataPoint  - Used to keep track of the last position in the receive
//!    I2C stream for error checking
//!
//!  - \b sDataspiA   - Data to send through SPI
//!  - \b rDataspiA   - Received SPI data
//!  - \b rDataPointspiA - Used to keep track of the last position in the receive
//!    SPI stream for error checking
//!
//!  - \b sDatauartA  - UART Data being sent
//!  - \b rDatauartA  - UART Data received
//!  - \b rDataPointA - Keep track of where we are in the UART data stream.
//!    This is used to check the incoming data
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
// - 2026-08-18:
// 1. Mask SPI 16-bit wrap in RX FIFO compare and pointer increment.
//
//###########################################################################

//
// Included Files
//
#include "g32r501_examples.h"
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define SLAVE_ADDRESS   0x3C

//
// Globals
//

//
// I2C data Globals
//
uint16_t sDatai2cA[2];                  // Send I2CA data buffer
uint16_t rDatai2cA[2];                  // Receive I2CA data buffer
uint16_t rDataPoint = 0;                // To keep track of where we are in the
                                        // data stream to check received I2C data
//
// UART data Globals
//
uint8_t sDatauartA[2];              // Send UART-A data buffer
uint8_t rDatauartA[2];              // Receive UART-A data buffer
uint16_t rDataPointA = 0;           // Used for checking the received UART data

//
// SPI data Globals
//
uint16_t sDataspiA[2];                  // Send SPI data buffer
uint16_t rDataspiA[2];                  // Receive SPI data buffer
uint16_t rDataPointspiA = 0;            // To keep track of where we are in the
                                        // data stream to check received SPI data
//
// Function Prototypes
//
void initI2CFIFO(void);
__interrupt void INT_I2CA_FIFO_IRQHandler(void);
__interrupt void INT_UARTA_TX_IRQHandler(void);
__interrupt void INT_UARTA_RX_IRQHandler(void);
void initUARTAFIFO(void);
void initSPIFIFO(void);
__interrupt void INT_SPIA_TX_IRQHandler(void);
__interrupt void INT_SPIA_RX_IRQHandler(void);
//
// Main
//
void example_main(void)
{
    uint16_t i;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize NVIC and clears NVIC registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_I2CA_FIFO, &INT_I2CA_FIFO_IRQHandler);
    Interrupt_register(INT_UARTA_RX, &INT_UARTA_RX_IRQHandler);
    Interrupt_register(INT_UARTA_TX, &INT_UARTA_TX_IRQHandler);
    Interrupt_register(INT_SPIA_TX, &INT_SPIA_TX_IRQHandler);
    Interrupt_register(INT_SPIA_RX, &INT_SPIA_RX_IRQHandler);

    //
    // Set I2C use, initializing it for FIFO mode
    //
    initI2CFIFO();

    //
    // Set UART use, initializing it for FIFO mode
    //
    initUARTAFIFO();

    //
    // Set up SPI, initializing it for FIFO mode
    //
    initSPIFIFO();

    //
    // Initialize the I2C data buffers
    //
    for(i = 0; i < 2; i++)
    {
        sDatai2cA[i] = i;
        rDatai2cA[i]= 0;
    }

    //
    // Init the UART send data.  After each transmission this data
    // will be updated for the next transmission
    //
    for(i = 0; i < 2; i++)
    {
        sDatauartA[i] = i;
    }

    //
    // Initialize the SPI data buffers
    //
    for(i = 0; i < 2; i++)
    {
        sDataspiA[i] = i;
        rDataspiA[i]= 0;
    }

    //
    // Set the priority group to indicate the PREEMPT and SUB priortiy bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);
    //
    // Set the global and group priority to allow CPU interrupts
    // with higher priority
    //
    Interrupt_setPriority(INT_I2CA_FIFO,1,0);
    Interrupt_setPriority(INT_UARTA_RX,1,0);
    Interrupt_setPriority(INT_UARTA_TX,1,0);
    Interrupt_setPriority(INT_SPIA_TX,1,0);
    Interrupt_setPriority(INT_SPIA_RX,1,0);
    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_I2CA_FIFO);
    Interrupt_enable(INT_UARTA_RX);
    Interrupt_enable(INT_UARTA_TX);
    Interrupt_enable(INT_SPIA_TX);
    Interrupt_enable(INT_SPIA_RX);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop forever. Suspend or place breakpoints to observe the buffers.
    //
    while(1)
    {
     // A FIFO interrupt will be generated for each Tx and Rx based
     // on the Interrupt levels configured for each of the modules.
    }
}

//
// Function to configure I2C A in FIFO mode.
//
void initI2CFIFO()
{
    //
    // Must put I2C into reset before configuring it
    //
    I2C_disableModule(I2CA_BASE);

    //
    // I2C configuration. Use a 400kHz I2CCLK with a 50% duty cycle.
    //
    I2C_initMaster(I2CA_BASE, DEVICE_APBCLK_FREQ, 400000, I2C_DUTYCYCLE_50);
    I2C_setConfig(I2CA_BASE, I2C_MASTER_SEND_MODE);
    I2C_setDataCount(I2CA_BASE, 2);
    I2C_setBitCount(I2CA_BASE, I2C_BITCOUNT_8);

    //
    // Configure for internal loopback mode
    //
    I2C_setSlaveAddress(I2CA_BASE, SLAVE_ADDRESS);
    I2C_setOwnSlaveAddress(I2CA_BASE, SLAVE_ADDRESS);
    I2C_enableLoopback(I2CA_BASE);
    I2C_setEmulationMode(I2CA_BASE, I2C_EMULATION_STOP_SCL_LOW);

    //
    // FIFO and interrupt configuration
    //
    I2C_enableFIFO(I2CA_BASE);
    I2C_clearInterruptStatus(I2CA_BASE, I2C_INT_RXFF | I2C_INT_TXFF);

    //
    // Transmit FIFO interrupt levels are set to generate an interrupt
    // when the 16 byte TX fifo contains 2 or lesser bytes of data.
    // Receive FIFO interrupt levels are set to generate an interrupt
    // when the 16 byte RX fifo contains 2 or greater bytes of data.
    //
    I2C_setFIFOInterruptLevel(I2CA_BASE, I2C_FIFO_TX2, I2C_FIFO_RX2);
    I2C_enableInterrupt(I2CA_BASE, I2C_INT_RXFF | I2C_INT_TXFF);

    //
    // Configuration complete. Enable the module.
    //
    I2C_enableModule(I2CA_BASE);
}

//
// I2C A Transmit & Receive FIFO ISR.
// The ISR will handle pushing/pulling data to/from the TX and
// RX FIFOs resp.
//
NO_OPTIMIZE
 __interrupt void INT_I2CA_FIFO_IRQHandler(void)
{
    uint16_t i;

    //
    // If receive FIFO interrupt flag is set, read data
    //
    if((I2C_getInterruptStatus(I2CA_BASE) & I2C_INT_RXFF) != 0)
    {
        for(i = 0; i < 2; i++)
        {
            rDatai2cA[i] = I2C_getData(I2CA_BASE);
        }

        //
        // Check received data
        //
        for(i = 0; i < 2; i++)
        {
            if(rDatai2cA[i] != ((rDataPoint + i) & 0xFF))
            {
                //
                // Something went wrong. rDatai2cA doesn't contain expected data.
                //
                ESTOP0;
            }
        }

        rDataPoint = (rDataPoint + 1) & 0xFF;

        //
        // Clear interrupt flag
        //
        I2C_clearInterruptStatus(I2CA_BASE, I2C_INT_RXFF);
    }
    //
    // If transmit FIFO interrupt flag is set, put data in the buffer
    //
    else if((I2C_getInterruptStatus(I2CA_BASE) & I2C_INT_TXFF) != 0)
    {
        for(i = 0; i < 2; i++)
        {
            I2C_putData(I2CA_BASE, sDatai2cA[i]);
        }

        //
        // Send the start condition
        //
        I2C_sendStartCondition(I2CA_BASE);

        //
        // Increment data for next cycle
        //
        for(i = 0; i < 2; i++)
        {
           sDatai2cA[i] = (sDatai2cA[i] + 1) & 0xFF;
        }

        //
        // Clear interrupt flag
        //
        I2C_clearInterruptStatus(I2CA_BASE, I2C_INT_TXFF);
    }
}

 //
 // uartaTXFIFOISR - UARTA Transmit FIFO ISR
 //
 __interrupt void INT_UARTA_TX_IRQHandler(void)
 {
     uint16_t i;

     UART_writeCharArray(UARTA_BASE, sDatauartA, 2);

     //
     // Increment send data for next cycle
     //
     for(i = 0; i < 2; i++)
     {
         sDatauartA[i] = (sDatauartA[i] + 1) & 0x00FF;
     }

     UART_clearInterruptStatus(UARTA_BASE, UART_INT_TXFF);
 }

 //
 // uartaRXFIFOISR - UARTA Receive FIFO ISR
 //
NO_OPTIMIZE
 __interrupt void INT_UARTA_RX_IRQHandler(void)
 {
     uint16_t i;

     UART_readCharArray(UARTA_BASE, rDatauartA, 2);

     //
     // Check received data
     //
     for(i = 0; i < 2; i++)
     {
         if(rDatauartA[i] != ((rDataPointA + i) & 0x00FF))
         {
             //
             // Something went wrong. rDatauartA doesn't contain expected data.
             //
             ESTOP0;
         }
     }

     rDataPointA = (rDataPointA + 1) & 0x00FF;

     UART_clearOverflowStatus(UARTA_BASE);

     UART_clearInterruptStatus(UARTA_BASE, UART_INT_RXFF);
 }

 //
 // initUARTAFIFO - Configure UARTA FIFO
 //
 void initUARTAFIFO()
 {
     //
     // 8 char bits, 1 stop bit, no parity. Baud rate is 9600.
     //
     UART_setConfig(UARTA_BASE, DEVICE_LSPCLK_FREQ, 9600, (UART_CONFIG_WLEN_8 |
                                                         UART_CONFIG_STOP_ONE |
                                                         UART_CONFIG_PAR_NONE));
     UART_enableModule(UARTA_BASE);
     UART_enableLoopback(UARTA_BASE);
     UART_resetChannels(UARTA_BASE);
     UART_enableFIFO(UARTA_BASE);

     //
     // RX and TX FIFO Interrupts Enabled
     //
     UART_enableInterrupt(UARTA_BASE, (UART_INT_RXFF | UART_INT_TXFF));
     UART_disableInterrupt(UARTA_BASE, UART_INT_RXERR);

     //
     // The transmit FIFO generates an interrupt when FIFO status
     // bits are less than or equal to 2 out of 16 words
     // The receive FIFO generates an interrupt when FIFO status
     // bits are greater than equal to 2 out of 16 words
     //
     UART_setFIFOInterruptLevel(UARTA_BASE, UART_FIFO_TX2, UART_FIFO_RX2);
     UART_performSoftwareReset(UARTA_BASE);

     UART_resetTxFIFO(UARTA_BASE);
     UART_resetRxFIFO(UARTA_BASE);
 }

 //
 // Function to configure SPI A in FIFO mode.
 //
 void initSPIFIFO()
 {
     //
     // Must put SPI into reset before configuring it
     //
     SPI_disableModule(SPIA_BASE);

     //
     // SPI configuration. Use a 500kHz SPICLK and 16-bit word size.
     //
     SPI_setConfig(SPIA_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA0,
                   SPI_MODE_MASTER, 500000, 16);
     SPI_enableLoopback(SPIA_BASE);
     SPI_setEmulationMode(SPIA_BASE, SPI_EMULATION_STOP_AFTER_TRANSMIT);

     //
     // FIFO and interrupt configuration
     //
     SPI_enableFIFO(SPIA_BASE);
     SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_RXFF | SPI_INT_TXFF);
     SPI_setFIFOInterruptLevel(SPIA_BASE, SPI_FIFO_TX2, SPI_FIFO_RX2);
     SPI_enableInterrupt(SPIA_BASE, SPI_INT_RXFF | SPI_INT_TXFF);

     //
     // Configuration complete. Enable the module.
     //
     SPI_enableModule(SPIA_BASE);
 }

 //
 // SPI A Transmit FIFO ISR
 //
 __interrupt void INT_SPIA_TX_IRQHandler(void)
 {
     uint16_t i;

     //
     // Send data
     //
     for(i = 0; i < 2; i++)
     {
        SPI_writeDataNonBlocking(SPIA_BASE, sDataspiA[i]);
     }

     //
     // Increment data for next cycle
     //
     for(i = 0; i < 2; i++)
     {
        sDataspiA[i] = sDataspiA[i] + 1;
     }

     //
     // Clear interrupt flag and issue ACK
     //
     SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_TXFF);
 }

 //
 // SPI A Receive FIFO ISR
 //

NO_OPTIMIZE
  __interrupt void INT_SPIA_RX_IRQHandler(void)
 {
     uint16_t i;

     //
     // Read data
     //
     for(i = 0; i < 2; i++)
     {
         rDataspiA[i] = SPI_readDataNonBlocking(SPIA_BASE);
     }

     //
     // Check received data
     //
     for(i = 0; i < 2; i++)
     {
         if(rDataspiA[i] != ((rDataPointspiA + i) & 0xFFFF))
         {
             // Something went wrong. rDataspiA doesn't contain expected data.
             ESTOP0;
         }
     }

     rDataPointspiA = (rDataPointspiA + 1) & 0xFFFF;

     //
     // Clear interrupt flag and issue ACK
     //
     SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_RXFF);
 }

//
// End of File
//

