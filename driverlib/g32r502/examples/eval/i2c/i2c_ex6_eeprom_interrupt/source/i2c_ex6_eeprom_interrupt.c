//#############################################################################
//
// FILE:    i2c_ex6_eeprom_interrupt.c
//
// TITLE:   I2C EEPROM Write / Read using interrupt
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1>I2C EEPROM</h1>
//!
//! This program shows EEPROM write/read using I2C interrupts.
//! Tuned for **AT24C02** (256 x 8, 1-byte word address, page size 8).
//!
//! //Example 1: EEPROM Byte Write
//! //Example 2: EEPROM Byte Read
//! //Example 3: EEPROM word (16-bit) write
//! //Example 4: EEPROM word (16-bit) read
//! //Example 5: EEPROM Page write (8 bytes)
//! //Example 6: EEPROM page read
//!
//! \b External \b Connections \n
//!  - AT24C02 at I2C address 0x50
//!  - GPIO2 (I2CB SDA) to EEPROM SDA (+ pull-up)
//!  - GPIO3 (I2CB SCL) to EEPROM SCL (+ pull-up)
//!  - Common GND; VCC typically 3.3 V
//!
//! \b Watch \b Variables \n
//!  - \b TX_MsgBuffer / \b RX_MsgBuffer
//!  - \b testResult — 1=pass, 2=fail
//!  - \b passCount / \b failCount
//!
//!
//#############################################################################
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
// 1. Modified some function and macro definition and variable names.
//
//###########################################################################

#include "g32r502_examples.h"
#include "driverlib.h"
#include "device.h"

#include "i2cLib_FIFO_master_interrupt.h"

//
// Defines
//
#define EEPROM_SLAVE_ADDRESS        0x50
#define EEPROM_PAGE_SIZE            8U     // AT24C02 page size

//
// Globals
//
struct I2CHandle EEPROM;
struct I2CHandle TempSensor;

struct I2CHandle *currentResponderPtr;                   // Used in interrupt

volatile uint16_t passCount = 0;
volatile uint16_t failCount = 0;
volatile uint16_t testResult = 0;   // 0=running, 1=pass, 2=fail

uint16_t AvailableI2C_slaves[20];

uint16_t TX_MsgBuffer[MAX_BUFFER_SIZE];
uint16_t RX_MsgBuffer[MAX_BUFFER_SIZE];
uint32_t ControlAddr;
uint16_t status=0;



//
// Function Prototypes
//

void INT_I2CB_FIFO_IRQHandler(void);
void INT_I2CB_IRQHandler(void);


void fail(void);
void pass(void);
void initI2CFIFO(void);
void verifyEEPROMRead(void);

void I2C_GPIO_init(void);
void I2Cinit(void);

//
// Main
//
void example_main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Initialize I2C pins
    //
    I2C_GPIO_init();

    //
    // Globally disable interrupts and clear all NVIC enable/pending bits
    //
    Interrupt_initModule();

    //
    // Initialize RAM vector table and set VTOR; unregistered IRQs use
    // Interrupt_defaultHandler until Interrupt_register() is called
    //
    Interrupt_initVectorTable();

    I2Cinit();
    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_I2CB_FIFO, &INT_I2CB_FIFO_IRQHandler);

    Interrupt_enable(INT_I2CB_FIFO);

    Interrupt_register(INT_I2CB, &INT_I2CB_IRQHandler);

    Interrupt_enable(INT_I2CB);

    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    Interrupt_setPriority(INT_I2CB_FIFO,1,0);
    Interrupt_setPriority(INT_I2CB,0,0);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //I2Cs connected to I2CA will be found in AvailableI2C_slaves buffer
    //after you run I2CBusScan function.
    uint16_t *pAvailableI2C_slaves = AvailableI2C_slaves;
    status = I2CBusScan(I2CB_BASE, pAvailableI2C_slaves);

    uint16_t i;

    currentResponderPtr = &EEPROM;

    EEPROM.currentHandlePtr     = &EEPROM;
    EEPROM.SlaveAddr            = EEPROM_SLAVE_ADDRESS;
    EEPROM.WriteCycleTime_in_us = 10000;    // AT24C02 tWR
    EEPROM.base                 = I2CB_BASE;
    EEPROM.pControlAddr         = &ControlAddr;
    EEPROM.NumOfAddrBytes       = 1;        // AT24C02: 1-byte word address

    //Example 1: EEPROM Byte Write
    //Write 11 to EEPROM address 0x0
    ControlAddr = 0x0;     //EEPROM address to write
    EEPROM.NumOfDataBytes       = 1;
    TX_MsgBuffer[0]             = 11;
    EEPROM.pTX_MsgBuffer        = TX_MsgBuffer;

    status = I2C_MasterTransmitter(&EEPROM);

    //Wait for EEPROM write cycle time
    //This delay is not mandatory. User can run their application code instead.
    //It is however important to wait for EEPROM write cycle time before you initiate
    //another read / write transaction
    DEVICE_DELAY_US(EEPROM.WriteCycleTime_in_us);

    //Example 2: EEPROM Byte Read
    //Make sure 11 is written to EEPROM address 0x0
    ControlAddr = 0;
    EEPROM.pControlAddr   = &ControlAddr;
    EEPROM.pRX_MsgBuffer  = RX_MsgBuffer;
    EEPROM.NumOfDataBytes = 1;

    status = I2C_MasterReceiver(&EEPROM);

    while(I2C_getStatus(EEPROM.base) & I2C_STS_BUS_BUSY);

    verifyEEPROMRead();

    //Example 3: EEPROM word (16-bit) write
    //EEPROM address 0x1 = 22 &  0x2 = 33
    ControlAddr = 1;   //EEPROM address to write
    EEPROM.NumOfDataBytes  = 2;
    TX_MsgBuffer[0]        = 0x11;
    TX_MsgBuffer[1]        = 0x22;
    EEPROM.pTX_MsgBuffer   = TX_MsgBuffer;
    status = I2C_MasterTransmitter(&EEPROM);

    //Wait for EEPROM write cycle time
    //This delay is not mandatory. User can run their application code instead.
    //It is however important to wait for EEPROM write cycle time before you initiate
    //another read / write transaction
    DEVICE_DELAY_US(EEPROM.WriteCycleTime_in_us);

    //Example 4: EEPROM word (16-bit) read
     //Make sure EEPROM address 1 has 0x11 and 2 has 0x22
     ControlAddr = 1;
     EEPROM.pControlAddr   = &ControlAddr;
     EEPROM.pRX_MsgBuffer  = RX_MsgBuffer;
     EEPROM.NumOfDataBytes = 2;

     status = I2C_MasterReceiver(&EEPROM);

     verifyEEPROMRead();


    //Example 5: EEPROM Page write (AT24C02: 8 bytes, page-aligned)
    for (i = 0; i < EEPROM_PAGE_SIZE; i++)
    {
        TX_MsgBuffer[i] = i + 64;
    }

    ControlAddr = 64;
    EEPROM.NumOfDataBytes  = EEPROM_PAGE_SIZE;
    EEPROM.pTX_MsgBuffer   = TX_MsgBuffer;
    status = I2C_MasterTransmitter(&EEPROM);

    DEVICE_DELAY_US(EEPROM.WriteCycleTime_in_us);

    //Example 6: EEPROM page read
    ControlAddr = 64;
    EEPROM.pControlAddr   = &ControlAddr;
    EEPROM.pRX_MsgBuffer  = RX_MsgBuffer;
    EEPROM.NumOfDataBytes = EEPROM_PAGE_SIZE;

    status = I2C_MasterReceiver(&EEPROM);

    verifyEEPROMRead();

    if (status)
    {
        fail();
    }
    else
    {
        pass();
    }

}

//
// pass - Function to be called if data written matches data read
//
void pass(void)
{
    testResult = 1U;
    ESTOP0;
    for(;;);
}

//
// fail - Function to be called if data written does NOT match data read
//
void fail(void)
{
    testResult = 2U;
    failCount++;
    ESTOP0;
    for(;;);
}

//
// verifyEEPROMRead - verify EEPROM Read.
//
void verifyEEPROMRead(void)
{
    uint16_t i;
    while (I2C_getStatus(EEPROM.base) & I2C_STS_BUS_BUSY);

    for (i = 0; i < EEPROM.NumOfDataBytes; i++)
    {
        if (RX_MsgBuffer[i] != TX_MsgBuffer[i])
        {
            ESTOP0;
            fail();
        }
        passCount++;
    }
}

//
// INT_I2CB_IRQHandler - NVIC interrupt handler for I2CB.
//
void INT_I2CB_IRQHandler(void)
{
    uint16_t MasterSlave = HWREGH(currentResponderPtr->base + I2C_O_CTRL);

    handleI2C_ErrorCondition(currentResponderPtr);

    if (MasterSlave & I2C_CTRL_MSCFG)
    {
        I2C_enableInterrupt(currentResponderPtr->base, I2C_INT_RXFF);
        I2C_clearInterruptStatus(currentResponderPtr->base,(I2C_INT_RXFF));
    }
}

//
// INT_I2CB_FIFO_IRQHandler - NVIC interrupt handler for I2CB_FIFO.
//
void INT_I2CB_FIFO_IRQHandler(void)
{
    Write_Read_TX_RX_FIFO(currentResponderPtr);
}


//
// I2C_GPIO_init - I2C_GPIO Configurations
//
void I2C_GPIO_init(void)
{
    // I2CB pins (SDAB / SCLB) — EVAL default GPIO2 / GPIO3
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SDAB, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SDAB, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SDAB, GPIO_QUAL_ASYNC);

    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCLB, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCLB, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCLB, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_SDAB);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCLB);
}

//
// I2Cinit - I2 Cinit.
//
void I2Cinit(void)
{
    // myI2CB initialization
    I2C_disableModule(I2CB_BASE);
    I2C_initMaster(I2CB_BASE, DEVICE_APBCLK_FREQ, 100000, I2C_DUTYCYCLE_50);
    I2C_setConfig(I2CB_BASE, I2C_MASTER_SEND_MODE);
    I2C_setSlaveAddress(I2CB_BASE, 80);
    I2C_setOwnSlaveAddress(I2CB_BASE, 96); //I2CA address
    I2C_disableLoopback(I2CB_BASE);
    I2C_setBitCount(I2CB_BASE, I2C_BITCOUNT_8);
    I2C_setDataCount(I2CB_BASE, 2);
    I2C_setAddressMode(I2CB_BASE, I2C_ADDR_MODE_7BITS);
    I2C_enableFIFO(I2CB_BASE);
    I2C_clearInterruptStatus(I2CB_BASE, I2C_INT_ARB_LOST | I2C_INT_NO_ACK);
    I2C_setFIFOInterruptLevel(I2CB_BASE, I2C_FIFO_TXEMPTY, I2C_FIFO_RX2);
    I2C_enableInterrupt(I2CB_BASE, I2C_INT_ADDR_SLAVE | I2C_INT_ARB_LOST | I2C_INT_NO_ACK | I2C_INT_STOP_CONDITION);
    I2C_setEmulationMode(I2CB_BASE, I2C_EMULATION_FREE_RUN);
    I2C_enableModule(I2CB_BASE);
}
//
// End of File
//

