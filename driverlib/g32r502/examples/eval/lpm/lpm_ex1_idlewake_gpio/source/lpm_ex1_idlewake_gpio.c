//#############################################################################
//
// FILE:    lpm_ex1_idlewake_gpio.c
//
// TITLE:   Idle entry and Exit example.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1>Low Power Modes: Device Idle Mode and Wakeup using GPIO</h1>
//!
//!  This example puts the device into IDLE mode and then wakes up the device
//!  from IDLE using XINT1 which triggers on a falling edge of GPIO0.
//!
//!  The GPIO0 pin must be pulled from high to low by an external agent for
//!  wakeup. GPIO0 is configured as an XINT1 pin to trigger an XINT1 interrupt
//!  upon detection of a falling edge.
//!
//!  Initially, pull GPIO0 high externally. To wake device from IDLE mode by
//!  triggering an XINT1 interrupt, pull GPIO0 low (falling edge). The wakeup
//!  process begins as soon as GPIO0 is held low for the time indicated in the
//!  device datasheet.
//!
//!  GPIO1 is pulled high before entering the IDLE mode and is pulled low when
//!  in the external interrupt ISR.
//!
//! \b JTAG \b / \b Debug \b Note \n
//!  This example uses GPIO35 (EVAL LD1), which is muxed with JTAG TDI on
//!  G32R502 EVAL. Using it as GPIO or LED may prevent subsequent program
//!  download or debug over JTAG until power cycle or debugger reconnect
//!  restores the default JTAG pinmux. SWD debugging is recommended for
//!  this example.
//!
//! \b External \b Connections \n
//!  - GPIO0 needs to be pulled low to wake up the device.
//!  - On device wakeup, the GPIO1 will be low and LED1 will start blinking
//!
//! \b Watch \b Variables \n
//!  - None.
//!
//
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
// 2. Updated interrupt handling to use NVIC functions.
//
//###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Function Prototypes
//
void enterLPM();
void xint1ISR(void);

//
// To avoid flash accesses, the function enterLPM and the ISR xint1ISR should
// be run from RAM.
// Note that the function SysCtl_enterIdleMode is defined inline. But this
// example is built with opt_level=off which does not inline functions. To avoid
// flash accesses, include SysCtl_enterIdleMode in itcm.ramfunc section (This is
// not required if optimization level 0 or higher is used)
//

#define RAMFUNC __attribute__((section("itcm.ramfunc")))

//
// Main
//
void example_main(void)
{
    //
    // Configure PLL, disable WD, enable peripheral clocks.
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // GPIO0 is the external wake-up source
    //
    GPIO_setPinConfig(GPIO_0_GPIO0);
    GPIO_setDirectionMode(0, GPIO_DIR_MODE_IN);
    GPIO_setDrivingCapability(0,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(0, GPIO_QUAL_ASYNC);

    //
    // GPIO1 is an output
    //
    GPIO_setPinConfig(GPIO_1_GPIO1);
    GPIO_setDirectionMode(1, GPIO_DIR_MODE_OUT);
    GPIO_setDrivingCapability(1,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(1, GPIO_PIN_TYPE_STD);

    //
    // LED pin configuration
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED1);
    GPIO_setDrivingCapability(DEVICE_GPIO_PIN_LED1,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);

    //
    // Configure GPIO0 as external wake source. The input XBAR is configured
    // to map the GPIO0 to the XINT1 using XBAR input 4
    //
    XBAR_setInputPin(XBAR_INPUT4, 0);
    GPIO_setInterruptType(GPIO_INT_XINT1, GPIO_INT_TYPE_FALLING_EDGE);
    GPIO_enableInterrupt(GPIO_INT_XINT1);

    //
    // Disable global interrupts.
    //
    DINT;

    //
    // Initialize interrupt controller and vector table.
    //
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
    Interrupt_setPriority(INT_XINT1, 0, 0);

    //
    // Map the ISR to the XINT1 interrupt.
    //
    Interrupt_register(INT_XINT1, xint1ISR);

    //
    // Enable the wake interrupt in the NVIC: Group 1 interrupt 4.
    //
    Interrupt_enable(INT_XINT1);

    //
    // Enable global interrupts.
    //
    EINT;

    //
    // Set GPIO1 high.
    //
    GPIO_writePin(1, 1);

    //
    // Power down the flash and enter LPM
    //
    enterLPM();

    while(1)
    {
        //
        // Toggle LED1
        //
        GPIO_togglePin(DEVICE_GPIO_PIN_LED1);

        //
        // 500ms delay
        //
        DEVICE_DELAY_US(500000);
    }
}

//
// enterLPM() - This will power down the flash and enter LPM.
//
RAMFUNC void enterLPM()
{
    //
    // Power down the flash bank and pump. Ensure there are no subsequent
    // flash accesses.
    //
    Flash_powerDown(FLASH0CTRL_BASE);

    //
    // Enter idle mode.
    //
    SysCtl_enterIdleMode();
}

//
// xint1ISR - External interrupt when GPIO0 is pulled from high to low.
//
RAMFUNC void xint1ISR(void)
{
    //
    // Wake the flash from low power mode.
    //
    Flash_wakeFromLPM(FLASH0CTRL_BASE);

    //
    // Set GPIO1 low.
    //
    GPIO_writePin(1, 0);
}

//
// End of File
//

