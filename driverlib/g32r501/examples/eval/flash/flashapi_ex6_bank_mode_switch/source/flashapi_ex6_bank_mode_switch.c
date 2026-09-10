//#############################################################################
//
// FILE:    flashapi_ex6_bank_mode_switch.c
//
// TITLE:   Flash Programming Switch Bank Mode Example
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1> Flash Programming Switch Bank Mode </h1>
//!
//! This example demonstrates how to use Flash API to switch flash bank modes.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2024 Geehy Semiconductor - http://www.geehy.com/
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
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "Fapi.h"

//
// define flash bank mode
//
#define FLASH_BANK_MODE Fapi_SingleBank
//#define FLASH_BANK_MODE Fapi_DualBank

int Flash_BankModeSwitch(Fapi_FlashBankModeType baknMode);

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
    // Initializes NVIC and clears NVIC registers. Disables CPU interrupts.
    // and clear all CPU interrupt flags.
    //
    Interrupt_initModule();

    //
    // Initializes the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Board Initialization
    //
    Board_init();

    //
    // Enables CPU interrupts
    //
    Interrupt_enableMaster();

    //
    // Set Flash bank mode
    //
    Flash_BankModeSwitch(FLASH_BANK_MODE);

    //
    // Loop.
    //
    for(;;)
    {
        GPIO_togglePin(myGPIOOutput_LED2);
        DEVICE_DELAY_US(1000000);
    }
}

int Flash_BankModeSwitch(Fapi_FlashBankModeType baknMode)
{
    Fapi_StatusType retCheck;

    //
    // Zone1 CSM unlock
    //
    *(uint32_t *)0x50024020 = 0xFFFFFFFF;
    *(uint32_t *)0x50024024 = 0xFFFFFFDC;
    *(uint32_t *)0x50024028 = 0xFFFFFFFF;
    *(uint32_t *)0x5002402C = 0xFFFFFFFF;
   
    //
    // Zone2 CSM unlock
    //
    *(uint32_t *)0x500240A0 = 0xFFFFFFFF;
    *(uint32_t *)0x500240A4 = 0xFFFEDFFF;
    *(uint32_t *)0x500240A8 = 0xFFFFFFFF;
    *(uint32_t *)0x500240AC = 0xFFFFFFFF;

    //
    // Initialize the Flash API by providing the Flash register base address
    // and operating frequency.
    // This function is required to initialize the Flash API based on System frequency
    // before any other Flash API operation can be performed.
    // This function must also be called whenever System frequency or RWAIT is changed.
    //
    retCheck = Fapi_initializeAPI(FAPI_BASE_ADDRESS, 200);
    if(retCheck != Fapi_Status_Success)
    {
        return 0;
    }

    //
    // Initialize the Flash banks and FMC for erase and program operations.
    //
    retCheck = Fapi_setActiveFlashBank(Fapi_FlashBank0);
    if(retCheck != Fapi_Status_Success)
    {
        return 0;
    }

    //
    // Switch the Flash bank mode.
    //
    retCheck = Fapi_writeFlashBankMode(baknMode);
    while(Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}
    if(retCheck != Fapi_Status_Success)
    {
        return 0;
    }

    return 1;
}

//
// End of File
//

