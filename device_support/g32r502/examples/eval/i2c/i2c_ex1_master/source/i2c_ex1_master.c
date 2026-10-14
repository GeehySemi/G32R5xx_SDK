//#############################################################################
//
// FILE:    i2c_ex1_master.c
//
// TITLE:   I2C Example Master.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup bitfield_example_list
//! <h1>I2C-B master/slave communication (bit-field, no FIFO)</h1>
//!
//! I2C-B master (polling). Pair with \b i2c_ex1_slave on a second board.
//!
//! \b Hardware \n
//!  - Two G32R502 EVAL boards; run slave first, then master. \n
//!  - Slave address 0x6A; 2-byte transfers per example. \n
//!  - I2C-B SCL: 100 kHz (standard mode, master sets bus clock).
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
//!  - Four \b ESTOP0 hits (examples 1--4); \b I2C_RXdata[0..1] == 0x11, 0x22
//!    after read examples; slave \b PassCount increases, \b FailCount == 0.
//!
//! \b Watch \b Variables \n
//!  - \b I2C_TXdata, \b I2C_RXdata
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
// 3. Restored WRPRT_ENABLE at end of I2CMaster_Init().
// 4. I2C GPIO open-drain + pull-up (required for ACK on SDA).
// 5. I2C-B SCL 100 kHz (APBCLK 100 MHz, PSC=9, CLKL/CLKH=45).
//
//###########################################################################

//
// Included Files
//
#include "g32r502_project.h"

//
// Defines
//
#define I2C_SLAVE_ADDRESS 0x6AU
#define I2C_OWN_ADDRESS 0x30U
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


//
// Function Prototypes
//
void I2CMaster_Init(uint16_t I2CSlave_OwnAddress, uint16_t I2CSlave_Address);
void I2CWrite(uint16_t slaveAddr, uint16_t byteCount, bool sendStopCondition);
uint16_t I2CRead(uint16_t slaveAddr, uint16_t byteCount, bool sendStopCondition);


//
// Main
//
void example_main(void)
{
    //
    // Locals
    //
    uint16_t index = 0U;
    uint16_t count = 0U;

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
    // Set the buffer to some default non-zero value
    //
    for (index=0; index<MAX_BUFFER_SIZE;index++)
    {
        I2C_RXdata[index] = 0xBAADU;
        I2C_TXdata[index] = 0x11 * (index+1);
    }

    //
    // Initialize I2C Module as Master Transmitter
    //
    I2CMaster_Init(I2C_OWN_ADDRESS,I2C_SLAVE_ADDRESS);

    //
    // Example 1 : Master as a Transmitter , writes two bytes
    //
    I2CWrite(I2C_SLAVE_ADDRESS, I2C_NUMBYTES, true);

    //
    // Wait for I2C bus to clear
    //
    while(I2cbRegs.I2CCTRL.bit.STOGEN !=0x0);
    while(I2cbRegs.I2CSTS.bit.BBSYFLG !=0x0);

    ESTOP0;  // Example 1: master write complete

    //
    // Example 2 : Master as a Receiver , receives two bytes
    //
    count = I2CRead(I2C_SLAVE_ADDRESS,I2C_NUMBYTES,true);

    //
    // Wait for I2C bus to clear
    //
    while(I2cbRegs.I2CCTRL.bit.STOGEN !=0x0);
    while(I2cbRegs.I2CSTS.bit.BBSYFLG !=0x0);

    ESTOP0;  // Example 2: master read complete; check I2C_RXdata[0..1]

    //
    //clear the Rx buffer
    //
    for (index=0; index<count;index++)
    {
        I2C_RXdata[index] = 0xBAADU;
    }

    //
    // Example 3 : Master Transmitter followed by Master Receiver
    //
    I2CWrite(I2C_SLAVE_ADDRESS, I2C_NUMBYTES, false); //Write byte
    count = I2CRead(I2C_SLAVE_ADDRESS,I2C_NUMBYTES,true);

    //
    // Wait for I2C bus to clear
    //
    while(I2cbRegs.I2CCTRL.bit.STOGEN !=0x0);
    while(I2cbRegs.I2CSTS.bit.BBSYFLG !=0x0);

    ESTOP0;  // Example 3: write + repeated-start read complete

    //
    //clear the Rx buffer
    //
    for (index=0; index<count;index++)
    {
        I2C_RXdata[index] = 0xBAADU;
    }

    //
    // Example 4: master read then write (repeated start)
    //
    count = I2CRead(I2C_SLAVE_ADDRESS, I2C_NUMBYTES, false);
    I2CWrite(I2C_SLAVE_ADDRESS, I2C_NUMBYTES, true);

    //
    // Wait for I2C bus to clear
    //
    while(I2cbRegs.I2CCTRL.bit.STOGEN !=0x0);
    while(I2cbRegs.I2CSTS.bit.BBSYFLG !=0x0);

    ESTOP0;  // Example 4: read + repeated-start write complete

    //
    //clear the Rx buffer
    //
    for (index=0; index<count;index++)
    {
        I2C_RXdata[index] = 0xBAADU;
    }

    //
    // Loop forever.
    //
    while(1)
    {

    }

}

//
// Configure I2C-B as master transmitter.
//
void I2CMaster_Init(uint16_t I2C_OwnAddress, uint16_t I2CSlave_Address)
{
    WRPRT_DISABLE;
    //
    // Must put I2C into reset before configuring it
    //
    I2cbRegs.I2CCTRL.all &= ~(0x20U);

    //
    // I2C-B SCL = 100 kHz @ APBCLK 100 MHz, 50% duty (I2C_initMaster equivalent).
    // f_mod = APBCLK / (PSC + 1) = 100 MHz / 10 = 10 MHz
    // f_SCL = f_mod / (I2CCLKL + I2CCLKH + 2*dValue), dValue=5 when PSC>=2
    //       = 10 MHz / (45 + 45 + 10) = 100 kHz
    //
    //I2C_initMaster(I2CB_BASE, DEVICE_APBCLK_FREQ, 100000, I2C_DUTYCYCLE_50);
    I2cbRegs.I2CPSC.all = 9U;         // PSC=9 -> f_mod = 10 MHz
    I2cbRegs.I2CCLKL = 45U;           // NOTE: must be non zero
    I2cbRegs.I2CCLKH = 45U;           // NOTE: must be non zero


    //
    // Configure Master as a Transmitter
    //
    I2cbRegs.I2CCTRL.bit.MSCFG = 0x1;
    I2cbRegs.I2CCTRL.bit.RXTXCFG = 0x1;

    //
    // Set data count
    //
    I2cbRegs.I2CCNT = I2C_NUMBYTES;

    //
    // Set the bit count to 8 bits per data byte, 7-bit addressing
    //
    I2cbRegs.I2CCTRL.bit.DBSEL = 0x0U;

    //
    // Configure slave and own address
    //
    I2cbRegs.I2COADDR.all = I2C_OwnAddress;         // Own address
    I2cbRegs.I2CSADDR.all = I2CSlave_Address;       // Slave address

    //
    // Set emulation mode to FREEEN
    //
    I2cbRegs.I2CCTRL.bit.FREEEN = 0x1;

    //
    //Clear all status
    //
    I2cbRegs.I2CSTS.all = 0xFFFF;

    //
    // Enable I2C Interrupts- RRDY
    //
    I2cbRegs.I2CIREN.all = 0x08;

    //
    // Take I2C out of reset
    //
    I2cbRegs.I2CCTRL.all |= 0x0020;

    WRPRT_ENABLE;
}

//
// Function to send data over I2C.
//
void I2CWrite(uint16_t slaveAddr, uint16_t byteCount, bool sendStopCondition)
{

    //
    // Locals
    //
    uint16_t index = 0;

    //
    // Configure slave address
    //
    I2cbRegs.I2CSADDR.all = slaveAddr;      // Slave address

    //
    // Configure I2C as Master Transmitter
    //
    I2cbRegs.I2CCTRL.bit.MSCFG = 0x1;
    I2cbRegs.I2CCTRL.bit.RXTXCFG = 0x1;

    //
    //Set Data Count
    //
    I2cbRegs.I2CCNT = byteCount;

    //
    // send Start condition
    //
    I2cbRegs.I2CCTRL.bit.STAGEN = 0x1;

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
    // Send STOP condition if specified
    //
    if(sendStopCondition)
    {
        I2cbRegs.I2CCTRL.bit.STOGEN = 0x1;
        while(I2cbRegs.I2CCTRL.bit.STOGEN != 0x0);

        I2cbRegs.I2CSTS.bit.BTXCFLG = 0x1;
    }
}

//
// Function to read data over I2C. Returns the number of bytes read
//
uint16_t I2CRead(uint16_t slaveAddr, uint16_t byteCount, bool sendStopCondition)
{
    //
    // Configure slave address
    //
    I2cbRegs.I2CSADDR.all = slaveAddr;

    //
    // Configure I2C in Master Receiver mode
    //
    I2cbRegs.I2CCTRL.bit.MSCFG = 0x1;
    I2cbRegs.I2CCTRL.bit.RXTXCFG = 0x0;

    //
    //Set Data Count
    //
    //I2cbRegs.I2CCNT = byteCount;

    //
    // send Start condition
    //
    I2cbRegs.I2CCTRL.bit.STAGEN = 0x1;

    uint16_t count = 0;

    //
    // Read the received data into RX buffer
    //
    while(count < I2C_NUMBYTES)
    {
        if(I2cbRegs.I2CSTS.bit.RXDIFLG ==0x1)
        {
            I2C_RXdata[count] = I2cbRegs.I2CRXD.all;
            count++;
        }
    }

    //
    // Send STOP condition
    //
    if(sendStopCondition)
    {
        I2cbRegs.I2CCTRL.bit.STOGEN = 0x1;
        while(I2cbRegs.I2CCTRL.bit.STOGEN != 0x0);

        I2cbRegs.I2CSTS.bit.BTXCFLG = 0x1;

    }
    return count;
}

//
//
// End of File
//
