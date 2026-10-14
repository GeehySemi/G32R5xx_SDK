//#############################################################################
//
// FILE:    i2c_ex1_slave.c
//
// TITLE:   I2C Example Slave.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup bitfield_example_list
//! <h1>I2C-B master/slave communication (bit-field, no FIFO)</h1>
//!
//! I2C-B slave (interrupt-driven). Pair with \b i2c_ex1_master on a second board.
//!
//! \b Hardware \n
//!  - Two G32R502 EVAL boards; download and run this slave before the master. \n
//!  - Own address 0x6A; compares RX vs TX on STOP. \n
//!  - SCL rate follows master (\b i2c_ex1_master): 100 kHz.
//!
//! \b External \b Connections (I2C-B) \n
//!  ----------------------------------------------------------------
//!    Signal   |  Master board         |  Slave board
//!  ----------------------------------------------------------------
//!     SDA     |  GPIO34 (mux 14)      |  GPIO34 (mux 14)
//!     SCL     |  GPIO3  (mux 11)      |  GPIO3  (mux 11)
//!     GND     |  GND                  |  GND
//!  ----------------------------------------------------------------
//!
//! \b Pass \b criteria \n
//!  - \b FailCount == 0; \b PassCount increases after each successful transfer.
//!
//! \b Watch \b Variables \n
//!  - \b PassCount, \b FailCount, \b I2C_TXdata, \b I2C_RXdata
//!
//
//###########################################################################
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
// 1. Updated interrupt handling to use NVIC functions.
// 2. I2C-B on GPIO34/GPIO3 for G32R502 EVAL; explicit GPxAMSEL digital mode.
// 3. Document bus SCL 100 kHz (set by paired master example).
// 4. I2C GPIO open-drain + pull-up (required for ACK on SDA).
//
//###########################################################################

//
// Included Files
//
#include "g32r502_project.h"

//
// Defines
//
#define I2C_SLAVE_ADDR 0x6AU
#define MAX_BUFFER_SIZE 0x10
#define I2C_NUMBYTES    0x2U

//
// I2C GPIO pins
//
#define GPIO_PIN_SDAB        34U   // I2C-B SDA (GPIO34, mux 14)
#define GPIO_PIN_SCLB        3U    // I2C-B SCL (GPIO3, mux 11)
#define GPIO_MUX_I2CB_SDA    14U
#define GPIO_MUX_I2CB_SCL    11U

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

    WRPRT_DISABLE;
    CpuSysRegs.PCLKCR9.bit.I2C_B = 1;
    WRPRT_ENABLE;

    //
    // I2C-B: GPIO34 (SDA) and GPIO3 (SCL), G32R502 EVAL pinout
    //
    WRPRT_DISABLE;
    GpioCtrlRegs.GPBAMSEL.bit.GPIO34 = 0;
    GpioCtrlRegs.GPAAMSEL.bit.GPIO3 = 0;
    WRPRT_ENABLE;

    GPIO_SetupPinMux(GPIO_PIN_SDAB, GPIO_MUX_I2CB_SDA);
    GPIO_SetupPinOptions(GPIO_PIN_SDAB, GPIO_OUTPUT, GPIO_PULLUP);
    GPIO_SetupPinMux(GPIO_PIN_SCLB, GPIO_MUX_I2CB_SCL);
    GPIO_SetupPinOptions(GPIO_PIN_SCLB, GPIO_OUTPUT, GPIO_PULLUP);

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
    // Set the priority group to indicate the PREEMPT and SUB priority bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    //
    // Set the global and group interrupt priority to allow CPU interrupts
    // with higher priority
    Interrupt_setPriority(INT_I2CB, 0, 0);

    //
    // Register the interrupt ISR
    //
    WRPRT_DISABLE;
    Interrupt_register(INT_I2CB, &I2CISR);
    WRPRT_ENABLE;


    //
    // Enable Interrupts
    //
    Interrupt_enable(INT_I2CB);

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
// Configure I2C-B as slave receiver.
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
    I2cbRegs.I2CCTRL.all &= ~(0x20U);

    //
    // Configure I2C as slave in Receive mode
    //
    I2cbRegs.I2CCTRL.bit.MSCFG = 0x0U;
    I2cbRegs.I2CCTRL.bit.RXTXCFG = 0x0U;

    //
    // Set the bit count to 8 bits per data byte, 7-bit addressing
    //
    I2cbRegs.I2CCTRL.bit.DBSEL = 0x0U;
    I2cbRegs.I2CCTRL.bit.ADDRLEN = 0U;
    I2cbRegs.I2CCTRL.bit.NACKCFG = 0U;

    //
    // Set emulation mode to FREEEN
    //
    I2cbRegs.I2CCTRL.bit.FREEEN = 0x1;

    //
    // Configure I2C own address
    //
    I2cbRegs.I2COADDR.all = I2CSlave_OwnAddress;      // Own address

    //
    //Clear all status
    //
    I2cbRegs.I2CSTS.all = 0xFFFF;

    //
    // Enable I2C Interrupts- AAS, STOP, TXDIREN and RXDIFLG
    //
    I2cbRegs.I2CIREN.all = 0x78;

    //
    // Take I2C out of reset
    //
    I2cbRegs.I2CCTRL.all |= 0x0020;

    WRPRT_ENABLE;
}


//
// I2CISR - Handle I2C slave interrupt
//
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
     IntSource = I2cbRegs.I2CISRC.all;

     //
     // Interrupt source
     //
     if(IntSource == 0x7U)   // AAS interrupt
     {
         if(I2cbRegs.I2CSTS.bit.SFLG)
         {
             // Configure slave as transmitter
             I2cbRegs.I2CCTRL.bit.RXTXCFG = 0x1U;

         }
         else
         {
             //Configure slave as receiver
             I2cbRegs.I2CCTRL.bit.RXTXCFG = 0x0U;

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
         while(I2cbRegs.I2CSTS.bit.RXDIFLG!=0)
         {
             I2C_RXdata[count] = I2cbRegs.I2CRXD.all;
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
         I2cbRegs.I2CCTRL.bit.RXTXCFG = 1;

         //
         // Disable the interrupt till all the bytes are sent
         //
         I2cbRegs.I2CIREN.bit.TXDIREN = 0;
         //
         //transmit the bytes
         //
         for(index=0; index < I2C_NUMBYTES; index++)
         {
             I2cbRegs.I2CTXD.all= I2C_TXdata[index];
             //
             //wait till byte is sent
             //
             while(I2cbRegs.I2CSTS.bit.BTXCFLG != 0x1);
             //
             //clear the byte sent
             //
             I2cbRegs.I2CSTS.bit.BTXCFLG = 0x1;
         }

         //
         // Enable the interrupt after all the bytes are sent
         //
         I2cbRegs.I2CIREN.bit.TXDIREN = 1;
     }
 }

//
// End of file
//
