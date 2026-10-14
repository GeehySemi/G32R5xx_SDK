//#############################################################################
//
// FILE:    i2c_ex1_slave.c
//
// TITLE:   I2C Example Slave.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup bitfield_example_list
//! <h1>I2C master slave communication using bit-field and without FIFO </h1>
//!
//! This program shows how to use I2CA in slave configuration.
//! This example uses I2C interrupts and doesn't use FIFO. 
//!  
//! \b Requires two Control Cards - one configured as Master and other as Slave \n
//! \b Master will run the binary generated from "i2c_ex1_master.uvprojx" \n
//! \b Slave will run the binary generated from "i2c_ex1_slave.uvprojx" \n
//! \b External \b Connections on Control Cards should be made as shown below \n
//!  --------------------------------------------------------------
//!    Signal   |  I2CA on Board1       |  I2CA on Board 2
//!  -----------------------------------------------------------------
//!     SCL     | GPIO_PIN_SCLA         |  GPIO_PIN_SCLA
//!     SDA     | GPIO_PIN_SDAA         |  GPIO_PIN_SDAA
//!     GND     |   GND                 |   GND
//!  ---------------------------------------------------------------
//!
//! \b Watch \b Variables in memory window\n
//!  - \b I2CA_TXdata
//!  - \b I2CA_RXdata
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
// 1. Updated interrupt handling to use NVIC functions.
//
//###########################################################################

//
// Included Files
//
#include "g32r501_project.h"

//
// Defines
//
#define I2C_SLAVE_ADDR 0x6AU
#define MAX_BUFFER_SIZE 0x10
#define I2C_NUMBYTES    0x2U

//
// I2C GPIO pins
//
#define GPIO_PIN_SDAA        26U  // GPIO number for I2C SDAA
#define GPIO_PIN_SCLA        27U  // GPIO number for I2C SCLA
//

//
// Globals
//
uint16_t I2C_TXdata[MAX_BUFFER_SIZE];
uint16_t I2C_RXdata[MAX_BUFFER_SIZE];
uint16_t PassCount=0x0, FailCount =0x0;

//
// Function Prototypes
//
void I2CSlave_Init(uint16_t I2CSlave_OwnAddress);
void I2CISR(void);

//
// Main
//
void example_main(void)
{
    //
    // Locals
    //
    uint16_t index = 0U;

    //
    // Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    //
    InitSysCtrl();

    //
    // Initialize GPIO
    //
    InitGpio();

    //
    //Configure I2C pins
    //

    GPIO_SetupPinMux(GPIO_PIN_SDAA, GPIO_MUX_CPU0, 11);
    GPIO_SetupPinOptions(GPIO_PIN_SDAA, GPIO_OUTPUT, GPIO_PULLUP);
    GPIO_SetupPinMux(GPIO_PIN_SCLA, GPIO_MUX_CPU0, 11);
    GPIO_SetupPinOptions(GPIO_PIN_SCLA, GPIO_OUTPUT, GPIO_PULLUP);


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
    // Set the priority group to indicate the PREEMPT and SUB priority bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    //
    // Set the global and group interrupt priority to allow CPU interrupts
    // with higher priority
    Interrupt_setPriority(INT_I2CA, 0, 0);

    //
    // Register the interrupt ISR
    //
    WRPRT_DISABLE;
    Interrupt_register(INT_I2CA, &I2CISR);
    WRPRT_ENABLE;


    //
    // Enable Interrupts
    //
    Interrupt_enable(INT_I2CA);

    EINT;                                   // Enable Global Interrupts

    EnableInterrupts();

    //
    // Set the buffer to some default non-zero value
    //
    for (index=0; index<MAX_BUFFER_SIZE;index++)
    {
        I2C_RXdata[index] = 0xBAADU;
        I2C_TXdata[index] = 0x11 * (index+1);
    }


    // Initialize I2C Module
    I2CSlave_Init(I2C_SLAVE_ADDR);

    // Application loop
    while(1)
    {
           //respond to master commands
    }

}

//
// Function to configure I2CA as Slave Receiver.
//
void I2CSlave_Init(uint16_t I2CSlave_OwnAddress)
{

    //
    // I2C configured as slave receiver mode
    //

    WRPRT_DISABLE;
    //
    // Reset the I2C Module
    //
    I2caRegs.I2CCTRL.all &= ~(0x20U);

    //
    // Configure I2C as slave in Receive mode
    //
    I2caRegs.I2CCTRL.bit.MSCFG = 0x0U;
    I2caRegs.I2CCTRL.bit.RXTXCFG = 0x0U;

    //
    // Set the bit count to 8 bits per data byte
    //
    I2caRegs.I2CCTRL.bit.DBSEL = 0x0U;

    //
    // Set emulation mode to FREEEN
    //
    I2caRegs.I2CCTRL.bit.FREEEN = 0x1;

    //
    // Configure I2C own address
    //
    I2caRegs.I2COADDR.all = I2CSlave_OwnAddress;      // Own address

    //
    //Clear all status
    //
    I2caRegs.I2CSTS.all = 0xFFFF;

    //
    // Enable I2C Interrupts- AAS, STOP, TXDIREN and RXDIFLG
    //
    I2caRegs.I2CIREN.all = 0x78;

    //
    // Take I2C out of reset
    //
    I2caRegs.I2CCTRL.all |= 0x0020;

    WRPRT_ENABLE;
}


void I2CISR(void)
{
    //
    // Handle I2C interrupt
    //
     uint16_t IntSource, index=0U;
     static bool bDataReceived = false;
     static volatile uint16_t count = 0U;

     //
     // Read Interrupt source
     //
     IntSource = I2caRegs.I2CISRC.all;

     //
     // Interrupt source
     //
     if(IntSource == 0x7U)   // AAS interrupt
     {
         if(I2caRegs.I2CSTS.bit.SFLG)
         {
             // Configure slave as transmitter
             I2caRegs.I2CCTRL.bit.RXTXCFG = 0x1U;

         }
         else
         {
             //Configure slave as receiver
             I2caRegs.I2CCTRL.bit.RXTXCFG = 0x0U;

        }
     }
     else if(IntSource == 0x6U) // STOP interrupt
     {
         //
         // Check if data has been received, then do a compare
         //
         if(bDataReceived)
         {
             bDataReceived = false;
             for(index=0; index < count; index++)
             {
                   if(I2C_RXdata[index] == I2C_TXdata[index])
                   {
                       PassCount++;
                   }
                   else
                   {
                       FailCount++;
                   }
             }
             //
             // Reinitialize the RX buffer to non-zero
             //
             if(FailCount ==0)
             {
                 for (index=0; index<count;index++)
                 {
                     I2C_RXdata[index] = 0xBAADU;
                 }
             }
             count =0U;
         }
     }
     else if (IntSource == 0x4U)  // RXDIFLG interrupt
     {
         //
         // Read the received data into RX buffer
         //
         while(I2caRegs.I2CSTS.bit.RXDIFLG!=0)
         {
             I2C_RXdata[count] = I2caRegs.I2CRXD.all;
             count++;
             //
             // set the data received flag to true to do a compare
             //
             bDataReceived = true;
         }

     }
     else if (IntSource == 0x5U) // TXDIREN interrupt
     {

         //
         //configure slave as transmitter
         //
         I2caRegs.I2CCTRL.bit.RXTXCFG = 1;

         //
         // Disable the interrupt till all the bytes are sent
         //
         I2caRegs.I2CIREN.bit.TXDIREN = 0;
         //
         //transmit the bytes
         //
         for(index=0; index < I2C_NUMBYTES; index++)
         {
             I2caRegs.I2CTXD.all= I2C_TXdata[index];
             //
             //wait till byte is sent
             //
             while(I2caRegs.I2CSTS.bit.BTXCFLG != 0x1);
             //
             //clear the byte sent
             //
             I2caRegs.I2CSTS.bit.BTXCFLG = 0x1;
         }

         //
         // Enable the interrupt after all the bytes are sent
         //
         I2caRegs.I2CIREN.bit.TXDIREN = 1;
     }
 }

//
// End of file
//
