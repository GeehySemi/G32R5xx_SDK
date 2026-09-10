//#############################################################################
//
// FILE:    lpm_ex2_idlewake_watchdog.c
//
// TITLE:   Idle entry and Exit example.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1>Low Power Modes: Device Idle Mode and Wakeup using Watchdog</h1>
//!
//!  This example puts the device into IDLE mode and then wakes up the device
//!  from IDLE using watchdog timer.
//!
//!  The device wakes up from the IDLE mode when the watchdog timer overflows,
//!  triggering an interrupt.
//!  A pre scalar is set for the watchdog timer to change the counter overflow
//!  time.
//!
//!  GPIO1 is pulled high before entering the IDLE mode and is pulled low when
//!  in the wakeup ISR.
//!
//! \b External \b Connections \n
//!  - On device wakeup, the GPIO1 will be low and LED1 will start blinking
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
void wakeupISR(void);

//
// To avoid flash accesses, the function enterLPM and the ISR wakeupISR should
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
    // Disable global interrupts.
    //
    DINT;

    //
    // Initialize interrupt controller and vector table.
    //
    Interrupt_initModule();
    Interrupt_initVectorTable();

    //
    // Set the priority group to indicate the PREEMPT and SUB priority bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_7_6_SUB_5_0);

    //
    // Set the global and group interrupt priority to allow CPU interrupts
    // with higher priority
    Interrupt_setPriority(INT_WAKE, 0, 0);

    //
    // Re-map watchdog wake interrupt signal to call the ISR function in this
    // example
    //
    Interrupt_register(INT_WAKE, &wakeupISR);

    //
    // Set the watchdog to generate an interrupt signal instead of a
    // reset signal
    //
    SysCtl_setWatchdogMode(SYSCTL_WDT_MODE_INTERRUPT);
    SysCtl_setWatchdogPrescaler(SYSCTL_WDT_PRESCALE_64);

    //
    // Enable the wake interrupt in the NVIC: Group 1 interrupt 8.
    //
    Interrupt_enable(INT_WAKE);

    //
    // Enable global interrupts.
    //
    EINT;

    //
    // Reset the watchdog counter
    //
    SysCtl_serviceWatchdog();

    //
    // Enable the watchdog
    //
    SysCtl_enableWatchdog();

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
        // 100ms delay
        //
        DEVICE_DELAY_US(100000);

        //
        // Service watchdog
        //
        SysCtl_serviceWatchdog();
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
// Wakeup ISR - The interrupt service routine called when the watchdog
//              triggers the wake interrupt signal
//
RAMFUNC void wakeupISR(void)
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
