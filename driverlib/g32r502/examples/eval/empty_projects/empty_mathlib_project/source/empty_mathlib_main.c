//#############################################################################
//
// FILE:    empty_mathlib_main.c
//
// TITLE:   Empty Project
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
// Empty Project Example
//
// This example is an empty project setup for Driverlib development.
//
// JTAG / Debug Note: This example uses GPIO35 (EVAL LD1), muxed with JTAG TDI on
// G32R502 EVAL. Using it as GPIO or LED may prevent subsequent program download
// or debug over JTAG until power cycle or debugger reconnect restores default
// JTAG pinmux. SWD debugging is recommended for this example.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
//
// You may not use this file except in compliance with the
// GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
//
// The program is only for reference, which is distributed in the hope
// that it will be useful and instructional for customers to develop
// their software. Unless required by applicable law or agreed to in
// writing, the program is distributed on an "AS IS" BASIS, WITHOUT
// ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
// See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
// and limitations under the License.
// $
//###########################################################################

//
// Included Files
//
#include "g32r502_examples.h"
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Main
//
void example_main(void)
{
    //
    // Initializes system control, device clock, and peripherals
    //
    Device_init();

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
    // Board Initialization
    //
    Board_init();

    GPIO_writePin(myGPIOOutput_LED2,1);
    GPIO_writePin(myGPIOOutput_LED1,1);
    
    //
    // Enables CPU interrupts
    //
    Interrupt_enableMaster();

    //
    // Loop.
    //
    for(;;)
    {
        GPIO_togglePin(myGPIOOutput_LED1);
        DEVICE_DELAY_US(1000000);
    }
}


//
// End of File
//

