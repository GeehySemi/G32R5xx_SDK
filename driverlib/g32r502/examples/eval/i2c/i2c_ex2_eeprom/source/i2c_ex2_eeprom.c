//#############################################################################
//
// FILE:    i2c_ex2_eeprom.c
//
// TITLE:   I2C EEPROM
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1>I2C EEPROM</h1>
//!
//! This program writes bytes to an external EEPROM and reads them back. The
//! data written and the EEPROM word address are in i2cMsgOut; data read back
//! is in i2cMsgIn. Tuned for **AT24C02** (256 x 8, **1-byte** word address,
//! 7-bit slave 0x50, page size 8).
//!
//! \b External \b Connections on EVAL Board\n
//!  - AT24C02 (or compatible) at I2C address 0x50
//!  - GPIO2 (I2CB SDA) to EEPROM SDA (+ pull-up)
//!  - GPIO3 (I2CB SCL) to EEPROM SCL (+ pull-up)
//!  - Common GND; VCC per EEPROM datasheet (typically 3.3 V)
//!
//! \b Watch \b Variables \n
//!  - \b i2cMsgOut / \b i2cMsgIn
//!  - \b passCount / \b failCount — PASS when passCount==NUM_BYTES and failCount==0
//!  - \b testResult — 1=pass, 2=fail (after compare)
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
// 1. Modified some function names and macro definition names.
// 2. Add interrupt priority settings.
//
//###########################################################################

#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define SLAVE_ADDRESS               0x50
#define EEPROM_HIGH_ADDR            0x00    // unused for AT24C02 (1-byte addr)
#define EEPROM_LOW_ADDR             0x30    // AT24C02 word address (0..255)
#define EEPROM_ADDR_BYTES           1U      // AT24C02: 1 word-address byte
#define NUM_BYTES                   8       // <= AT24C02 page size (8)
#define MAX_BUFFER_SIZE             14      // FIFO headroom

//
// I2C message states for I2CMsg struct
//
#define MSG_STATUS_INACTIVE         0x0000 // Message not in use, do not send
#define MSG_STATUS_SEND_WITHSTOP    0x0010 // Send message with stop bit
#define MSG_STATUS_WRITE_BUSY       0x0011 // Message sent, wait for stop
#define MSG_STATUS_SEND_NOSTOP      0x0020 // Send message without stop bit
#define MSG_STATUS_SEND_NOSTOP_BUSY 0x0021 // Message sent, wait for ARDY
#define MSG_STATUS_RESTART          0x0022 // Ready to become master-receiver
#define MSG_STATUS_READ_BUSY        0x0023 // Wait for stop before reading data

//
// Error messages for read and write functions
//
#define ERROR_BUS_BUSY              0x1000
#define ERROR_STOP_NOT_READY        0x5555
#define SUCCESS                     0x0000

//
// Typedefs
//
struct I2CMsg {
    uint16_t msgStatus;                  // Word stating what state msg is in.
                                         // See MSG_STATUS_* defines above.
    uint16_t slaveAddr;                  // Slave address tied to the message.
    uint16_t numBytes;                   // Number of valid bytes in message.
    uint16_t memoryHighAddr;             // EEPROM address of data associated
                                         // with message (high byte).
    uint16_t memoryLowAddr;              // EEPROM address of data associated
                                         // with message (low byte).
    uint16_t msgBuffer[MAX_BUFFER_SIZE]; // Array holding message data.
};

//
// Globals
//
struct I2CMsg i2cMsgOut = {MSG_STATUS_SEND_WITHSTOP,
                           SLAVE_ADDRESS,
                           NUM_BYTES,
                           EEPROM_HIGH_ADDR,
                           EEPROM_LOW_ADDR,
                           {0x01,                // Message bytes
                           0x23,
                           0x45,
                           0x67,
                           0x89,
                           0xAB,
                           0xCD,
                           0xEF}};
struct I2CMsg i2cMsgIn  = {MSG_STATUS_SEND_NOSTOP,
                           SLAVE_ADDRESS,
                           NUM_BYTES,
                           EEPROM_HIGH_ADDR,
                           EEPROM_LOW_ADDR};

struct I2CMsg *currentMsgPtr;                   // Used in interrupt

volatile uint16_t passCount = 0;
volatile uint16_t failCount = 0;
volatile uint16_t testResult = 0;   // 0=running, 1=pass, 2=fail

//
// Function Prototypes
//
void initI2C(void);
uint16_t readData(struct I2CMsg *msg);
uint16_t writeData(struct I2CMsg *msg);

void fail(void);
void pass(void);

void INT_I2CB_IRQHandler(void);

//
// Main
//
void example_main(void)
{
    uint16_t error;
    uint16_t i;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // I2CB on EVAL default: SDA=GPIO2, SCL=GPIO3 (AT24C02)
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SDAB);
    GPIO_setDrivingCapability(DEVICE_GPIO_PIN_SDAB,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SDAB, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SDAB, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCLB);
    GPIO_setDrivingCapability(DEVICE_GPIO_PIN_SCLB,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCLB, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCLB, GPIO_QUAL_ASYNC);

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
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_I2CB, &INT_I2CB_IRQHandler);

    //
    // Set I2C use, initializing it for FIFO mode
    //
    initI2C();

    //
    // Clear incoming message buffer
    //
    for (i = 0; i < MAX_BUFFER_SIZE; i++)
    {
        i2cMsgIn.msgBuffer[i] = 0x0000;
    }

    //
    // Set message pointer used in interrupt to point to outgoing message
    //
    currentMsgPtr = &i2cMsgOut;

    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    Interrupt_setPriority(INT_I2CB,0,0);

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_I2CB);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop indefinitely
    //
    while(1)
    {
        //
        // **** Write data to EEPROM section ****
        //
        // Check the outgoing message to see if it should be sent. In this
        // example it is initialized to send with a stop bit.
        //
        if (i2cMsgOut.msgStatus == MSG_STATUS_SEND_WITHSTOP)
        {
            //
            // Send the data to the EEPROM
            //
            error = writeData(&i2cMsgOut);

            //
            // If communication is correctly initiated, set msg status to busy
            // and update currentMsgPtr for the interrupt service routine.
            // Otherwise, do nothing and try again next loop. Once message is
            // initiated, the I2C interrupts will handle the rest. See the
            // function i2cAISR().
            //
            if (error == SUCCESS)
            {
                currentMsgPtr = &i2cMsgOut;
                i2cMsgOut.msgStatus = MSG_STATUS_WRITE_BUSY;
            }
        }

        //
        // **** Read data from EEPROM section ****
        //
        // Check outgoing message status. Bypass read section if status is
        // not inactive.
        //
        if (i2cMsgOut.msgStatus == MSG_STATUS_INACTIVE)
        {
            //
            // AT24C02 write-cycle settle (~5 ms typ); once after first write
            //
            static uint16_t eepromWriteSettled = 0U;
            if (eepromWriteSettled == 0U)
            {
                DEVICE_DELAY_US(10000U);
                eepromWriteSettled = 1U;
            }

            //
            // Check incoming message status
            //
            if (i2cMsgIn.msgStatus == MSG_STATUS_SEND_NOSTOP)
            {
                //
                // Update current message pointer and message status
                //
                currentMsgPtr = &i2cMsgIn;
                //
                // Send EEPROM address setup
                //
                while (readData(&i2cMsgIn) != SUCCESS)
                {
                    //
                    // Maybe setup an attempt counter to break an infinite
                    // while loop. The EEPROM will send back a NACK while it is
                    // performing a write operation. Even though the write
                    // is complete at this point, the EEPROM could still be
                    // busy programming the data. Therefore, multiple
                    // attempts are necessary.
                    //
                }
            }

            //
            // Once message has progressed past setting up the internal address
            // of the EEPROM, send a restart to read the data bytes from the
            // EEPROM. Complete the communique with a stop bit. msgStatus is
            // updated in the interrupt service routine.
            //
            else if (i2cMsgIn.msgStatus == MSG_STATUS_RESTART)
            {
                //
                // Update current message pointer and message status
                //
                currentMsgPtr = &i2cMsgIn;
                //
                // Read data portion
                //
                while (readData(&i2cMsgIn) != SUCCESS)
                {
                    //
                    // Maybe setup an attempt counter to break an infinite
                    // while loop.
                    //
                }
            }
        }
    }
}

//
// Function to configure I2C A in FIFO mode.
//
void initI2C()
{
    //
    // Must put I2C into reset before configuring it
    //
    I2C_disableModule(I2CB_BASE);

    //
    // I2C configuration. Use a 400kHz I2CCLK with a 33% duty cycle.
    //
    I2C_initMaster(I2CB_BASE, DEVICE_APBCLK_FREQ, 400000, I2C_DUTYCYCLE_50);
    I2C_setBitCount(I2CB_BASE, I2C_BITCOUNT_8);
    I2C_setSlaveAddress(I2CB_BASE, SLAVE_ADDRESS);
    I2C_setEmulationMode(I2CB_BASE, I2C_EMULATION_FREE_RUN);

    //
    // Enable stop condition and register-access-ready interrupts
    //
    I2C_enableInterrupt(I2CB_BASE, I2C_INT_STOP_CONDITION |
                                   I2C_INT_REG_ACCESS_RDY);

    //
    // FIFO configuration
    //
    I2C_enableFIFO(I2CB_BASE);
    I2C_clearInterruptStatus(I2CB_BASE, I2C_INT_RXFF | I2C_INT_TXFF);

    //
    // Configuration complete. Enable the module.
    //
    I2C_enableModule(I2CB_BASE);
}

//
// Function to send the data that is to be written to the EEPROM
//
uint16_t writeData(struct I2CMsg *msg)
{
    uint16_t i;

    //
    // Wait until the STP bit is cleared from any previous master
    // communication. Clearing of this bit by the module is delayed until after
    // the SCD bit is set. If this bit is not checked prior to initiating a new
    // message, the I2C could get confused.
    //
    if (I2C_getStopConditionStatus(I2CB_BASE))
    {
        return(ERROR_STOP_NOT_READY);
    }

    //
    // Setup slave address
    //
    I2C_setSlaveAddress(I2CB_BASE, SLAVE_ADDRESS);

    //
    // Check if bus busy
    //
    if (I2C_isBusBusy(I2CB_BASE))
    {
        return(ERROR_BUS_BUSY);
    }

    //
    // Setup number of bytes to send: word address + payload
    //
    I2C_setDataCount(I2CB_BASE, (msg->numBytes + EEPROM_ADDR_BYTES));

    //
    // AT24C02: one word-address byte (memoryLowAddr)
    //
    I2C_putData(I2CB_BASE, msg->memoryLowAddr);

    for (i = 0; i < msg->numBytes; i++)
    {
        I2C_putData(I2CB_BASE, msg->msgBuffer[i]);
    }

    //
    // Send start as master transmitter
    //
    I2C_setConfig(I2CB_BASE, I2C_MASTER_SEND_MODE);
    I2C_sendStartCondition(I2CB_BASE);
    I2C_sendStopCondition(I2CB_BASE);

    return(SUCCESS);
}

//
// Function to prepare for the data that is to be read from the EEPROM
//
uint16_t readData(struct I2CMsg *msg)
{
    //
    // Wait until the STP bit is cleared from any previous master
    // communication. Clearing of this bit by the module is delayed until after
    // the SCD bit is set. If this bit is not checked prior to initiating a new
    // message, the I2C could get confused.
    //
    if (I2C_getStopConditionStatus(I2CB_BASE))
    {
        return(ERROR_STOP_NOT_READY);
    }

    //
    // Setup slave address
    //
    I2C_setSlaveAddress(I2CB_BASE, SLAVE_ADDRESS);

    //
    // If we are in the the address setup phase, send the address without a
    // stop condition.
    //
    if (msg->msgStatus == MSG_STATUS_SEND_NOSTOP)
    {
        //
        // Check if bus busy
        //
        if (I2C_isBusBusy(I2CB_BASE))
        {
            return(ERROR_BUS_BUSY);
        }

        //
        // Send word address to setup EEPROM internal pointer (AT24C02: 1 byte)
        //
        I2C_setDataCount(I2CB_BASE, EEPROM_ADDR_BYTES);
        I2C_putData(I2CB_BASE, msg->memoryLowAddr);
        I2C_setConfig(I2CB_BASE, I2C_MASTER_SEND_MODE);
        I2C_sendStartCondition(I2CB_BASE);
        msg->msgStatus = MSG_STATUS_SEND_NOSTOP_BUSY;
    }
    else if (msg->msgStatus == MSG_STATUS_RESTART)
    {
        //
        // Address setup phase has completed. Now setup how many bytes expected
        // and send restart as master-receiver.
        //
        I2C_setDataCount(I2CB_BASE, (msg->numBytes));
        I2C_setConfig(I2CB_BASE, I2C_MASTER_RECEIVE_MODE);
        I2C_sendStartCondition(I2CB_BASE);
        I2C_sendStopCondition(I2CB_BASE);
        i2cMsgIn.msgStatus = MSG_STATUS_READ_BUSY;
    }

    return(SUCCESS);
}

//
// I2C A ISR (non-FIFO)
//
void INT_I2CB_IRQHandler(void)
{
    I2C_InterruptSource intSource;
    uint16_t i;

    //
    // Read interrupt source
    //
    intSource = I2C_getInterruptSource(I2CB_BASE);

    //
    // Interrupt source = stop condition detected
    //
    if (intSource == I2C_INTSRC_STOP_CONDITION)
    {
        //
        // If completed message was writing data, reset msg to inactive state
        //
        if (currentMsgPtr->msgStatus == MSG_STATUS_WRITE_BUSY)
        {
            currentMsgPtr->msgStatus = MSG_STATUS_INACTIVE;
        }
        else
        {
            //
            // If a message receives a NACK during the address setup portion of
            // the EEPROM read, the code further below included in the register
            // access ready interrupt source code will generate a stop
            // condition. After the stop condition is received (here), set the
            // message status to try again. User may want to limit the number
            // of retries before generating an error.
            //
            if (currentMsgPtr->msgStatus == MSG_STATUS_SEND_NOSTOP_BUSY)
            {
                currentMsgPtr->msgStatus = MSG_STATUS_SEND_NOSTOP;
            }
            //
            // If completed message was reading EEPROM data, reset message to
            // inactive state and read data from FIFO.
            //
            else if (currentMsgPtr->msgStatus == MSG_STATUS_READ_BUSY)
            {
                currentMsgPtr->msgStatus = MSG_STATUS_INACTIVE;
                for (i = 0; i < NUM_BYTES; i++)
                {
                    currentMsgPtr->msgBuffer[i] = I2C_getData(I2CB_BASE);
                }

                //
                // Check received data
                //
                for (i = 0; i < NUM_BYTES; i++)
                {
                    if (i2cMsgIn.msgBuffer[i] == i2cMsgOut.msgBuffer[i])
                    {
                        passCount++;
                    }
                    else
                    {
                        failCount++;
                    }
                }

                if (passCount == NUM_BYTES)
                {
                    pass();
                }
                else
                {
                    fail();
                }
            }
        }
    }
    //
    // Interrupt source = Register Access Ready
    //
    // This interrupt is used to determine when the EEPROM address setup
    // portion of the read data communication is complete. Since no stop bit
    // is commanded, this flag tells us when the message has been sent
    // instead of the SCD flag.
    //
    else if (intSource == I2C_INTSRC_REG_ACCESS_RDY)
    {
        //
        // If a NACK is received, clear the NACK bit and command a stop.
        // Otherwise, move on to the read data portion of the communication.
        //
        if ((I2C_getStatus(I2CB_BASE) & I2C_STS_NO_ACK) != 0)
        {
            I2C_sendStopCondition(I2CB_BASE);
            I2C_clearStatus(I2CB_BASE, I2C_STS_NO_ACK);
        }
        else if (currentMsgPtr->msgStatus == MSG_STATUS_SEND_NOSTOP_BUSY)
        {
            currentMsgPtr->msgStatus = MSG_STATUS_RESTART;
        }
    }
    else
    {
        //
        // Generate some error from invalid interrupt source
        //
        ESTOP0;
    }
}

//
// Function to be called if data written matches data read
//
void pass(void)
{
    testResult = 1U;
    ESTOP0;
    for(;;);
}

//
// Function to be called if data written does NOT match data read
//
void fail(void)
{
    testResult = 2U;
    ESTOP0;
    for(;;);
}
