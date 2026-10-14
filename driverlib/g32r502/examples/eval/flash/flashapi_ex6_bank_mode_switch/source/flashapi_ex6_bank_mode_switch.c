//#############################################################################
//
// FILE:    flashapi_ex6_bank_mode_switch.c
//
// TITLE:   Flash Programming Switch Bank Mode Example
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1> Flash Programming Switch Bank Mode </h1>
//!
//! This example uses Flash API to program the Flash bank mode option byte.
//!
//! After programming, perform a power cycle or hardware reset before the new
//! mode is applied. On reset, the bank mode is loaded from the option byte
//! into CR.nDBANK.
//!
//! Changing the bank mode invalidates existing data in Flash main memory.
//! Erase and reprogram Flash after a mode change.
//!
//! Bank mode selection (Fapi_FlashBankModeType):
//! - \b Fapi_SingleBank (0): Single-bank mode, 256-bit read width
//! - \b Fapi_DualBank (1): Dual-bank mode, 128-bit read width
//!
//! \b JTAG \b / \b Debug \b Note \n
//!  This example uses GPIO35 (EVAL LD1), which is muxed with JTAG TDI on
//!  G32R502 EVAL. Using it as GPIO or LED may prevent subsequent program
//!  download or debug over JTAG until power cycle or debugger reconnect
//!  restores the default JTAG pinmux. SWD debugging is recommended for
//!  this example.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - None.
//!
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
        GPIO_togglePin(myGPIOOutput_LED1);
        DEVICE_DELAY_US(1000000);
    }
}

//
// Flash_BankModeSwitch - Flash Bank Mode Switch.
//
int Flash_BankModeSwitch(Fapi_FlashBankModeType baknMode)
{
    Fapi_StatusType retCheck;

    //
    // Zone1 CSM unlock
    //
    *(uint32_t *)0x40010820 = 0xFFFFFFFF;
    *(uint32_t *)0x40010824 = 0xFFFFFFDC;
    *(uint32_t *)0x40010828 = 0xFFFFFFFF;
    *(uint32_t *)0x4001082C = 0xFFFFFFFF;
   
    //
    // Zone2 CSM unlock
    //
    *(uint32_t *)0x400108A0 = 0xFFFFFFFF;
    *(uint32_t *)0x400108A4 = 0xFFFEDFFF;
    *(uint32_t *)0x400108A8 = 0xFFFFFFFF;
    *(uint32_t *)0x400108AC = 0xFFFFFFFF;

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

