//#############################################################################
//
// FILE:    boot_ex2_customBootConfig.c
//
// TITLE:   Customized Boot Configuration Example
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1> Customized Boot Configuration Example </h1>
//!
//! The example implements a custom boot configuration. Use the MDK
//! Configuration Wizard on boot_ex2_customBootConfig.h to choose the
//! boot flow (standalone vs emulation), BMSP count (0 / 1 / 3), GPIO
//! assignments, and BOOTDEF slot map. Alternatively, select the MDK or
//! IAR build configuration ZERO_BMSPS, ONE_BMSP, or THREE_BMSPS.
//!
//!
//! Select the build configuration and run the
//! program. To test a specific boot mode: pause the program, apply
//! appropriate voltages to BMSPs as necessary, then perform a reset.
//! If more than one specific boot mode is to be tested, reset the debugger
//! and run the program before following the steps above; this ensures that
//! the device is not executing 'non-debuggable' code from the previous boot mode
//! and the emulation-equivalent Boot ROM registers contain the appropriate
//! values. Do not power-cycle the device in order to perform a reset; values in the
//! emulation-equivalent Boot ROM registers may change if the device is power-cycled.
//!
//!
//! By default, the example will configure the boot mode
//! select pins and boot mode options for the emulation boot process to
//! be executed.
//!
//! The following settings are in boot_ex2_customBootConfig.h (Configuration
//! Wizard when using MDK):
//!
//! - STANDALONE_BOOT - Standalone vs emulation boot on reset
//! - BOOT_EX2_BMSP_GROUP - 0, 1, or 3 boot mode select pins
//! - BOOTPIN_CONFIG_BMSP0/1/2 - GPIO numbers for each BMSP
//! - BOOTDEF_LOW_0..3 / BOOTDEF_HIGH_4..7 - boot mode per truth-table slot
//!
//!   ZERO_BMSPS:   Boot Mode Number BMSP2 BMSP1 BMSP0  Boot Mode
//!                      0            N/A   N/A   N/A   Flash Boot
//!
//!   ONE_BMSP:          0            N/A   N/A   0     Flash Boot
//!                      1            N/A   N/A   1     UART Boot
//!
//!   THREE_BMSPS        0            0      0    0     Flash Boot
//!                      1            0      0    1     UART Boot
//!                      2            0      1    0     Flash Boot Alt.1
//!                      3            0      1    1     UART Boot Alt.1
//!                      4            1      0    0     CAN Boot
//!                      5            1      0    1     SPI Boot
//!                      6            1      1    0     CAN FD Boot
//!                      7            1      1    1     I2C Boot
//!
//!
//!  Watch the addresses below in the memory browser when running the
//!  emulation boot configuration:
//! - 0x40012C00 for EMU_BOOTPIN_CONFIG
//! - 0x40012C04 for EMU_BOOTDEF_LOW
//! - 0x40012C08 for EMU_BOOTDEF_HIGH
//!
//!  Watch the address below in the memory browser when STANDALONE_BOOT
//!  constant is set to a non-zero value:
//! - 0x40012C00 for EMU_BOOTPIN_CONFIG
//!
//! \b External \b Connections \n
//!  - Connect 3V or GND to BMSP2 as appropriate
//!  - Connect 3V or GND to BMSP1 as appropriate
//!  - Connect 3V or GND to BMSP0 as appropriate
//!
//! \b Watch \b Variables \n
//!  - None
//!
//
//###########################################################################
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
// 1. Modify some comments, macros, function names, and function contents.
// 2. Update THREE_BMSPS boot table and EMU register watch addresses for G32R502.
//
//###########################################################################


//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "boot_ex2_customBootConfig.h"

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
    // Globally disable interrupts and clear all NVIC enable/pending bits
    //
    Interrupt_initModule();
    //
    // Initialize RAM vector table and set VTOR; unregistered IRQs use
    // Interrupt_defaultHandler until Interrupt_register() is called
    //
    Interrupt_initVectorTable();

    #if STANDALONE_BOOT

        //
        // Enable writing to the WRPRT_DISABLE protected registers
        //
        WRPRT_DISABLE;

        //
        // Write a value of 0xA5 to the emulation equivalent
        // of Z1_OTP_BOOTPIN_CONFIG in order to emulate
        // the standalone boot flow
        //
        HWREG(EMU_BOOTPIN_CONFIG) = (EMU_STANDALONE_KEYVAL  << 24);

        //
        // Disable writing to the WRPRT_DISABLE protected registers
        //
        WRPRT_ENABLE;

    #else

        //
        // Configure emulation boot table per BOOT_EX2_BMSP_GROUP (MDK
        // Configuration Wizard or Target name ZERO_BMSPS / ONE_BMSP /
        // THREE_BMSPS).
        //
        #if (BOOT_EX2_BMSP_GROUP == 0)

            configBMSPS0();

        #elif (BOOT_EX2_BMSP_GROUP == 1)

            configBMSPS1();

        #else

            configBMSPS3();

        #endif

    #endif

    //
    // Loop Forever
    //
    for(;;)
    {
        //
        // Do nothing. NOP == No Operation
        //
        NOP;
    }
}

//
// Functions
//

//
// configBMSPS0 - Configures a custom boot EMU configuration when zero boot mode
//                select pins are being used
//
//                Boot Mode Number                          Boot Mode
//                      0                                   Flash Boot
//
void configBMSPS0(void)
{
    //
    // Enable writing to the WRPRT_DISABLE protected registers
    //
    WRPRT_DISABLE;

    //
    // Write a value of 0x5A to the Key field of
    // EMU_BOOTPIN_CONFIG in order to execute
    // a custom boot process. Write the values of
    // BMSPs to be used.
    //
    HWREG(EMU_BOOTPIN_CONFIG) = (BOOTPIN_CONFIG_KEY  << 24) +
                                (BOOTPIN_CONFIG_BMSPDISABLE << 16) +
                                (BOOTPIN_CONFIG_BMSPDISABLE << 8) +
                                (BOOTPIN_CONFIG_BMSPDISABLE);

    //
    // Write boot mode option 0 to the EMU_BOOTDEF_LOW register
    //
    HWREG(EMU_BOOTDEF_LOW) = BOOTDEF_LOW_0;

    //
    // Disable writing to the WRPRT_DISABLE protected registers
    //
    WRPRT_ENABLE;
}

//
// configBMSPS1 - Configures a custom EMU boot configuration when 1 boot mode
//                select pin is being used.
//
//                Boot Mode Number     BMSP0          Boot Mode
//                      0                0            Flash Boot
//                      1                1            UART Boot
//
void configBMSPS1(void)
{
    //
    // Enable writing to the WRPRT_DISABLE protected registers
    //
    WRPRT_DISABLE;

    //
    // Write a value of 0x5A to the Key field of
    // EMU_BOOTPIN_CONFIG in order to execute
    // a custom boot process. Write the values of
    // BMSPs to be used.
    //
    HWREG(EMU_BOOTPIN_CONFIG) = (BOOTPIN_CONFIG_KEY  << 24) +
                                (BOOTPIN_CONFIG_BMSPDISABLE << 16) +
                                (BOOTPIN_CONFIG_BMSPDISABLE << 8) +
                                (BOOTPIN_CONFIG_BMSP0);

    //
    // Write boot mode options 1 and 0 to the EMU_BOOTDEF_LOW register
    //
    HWREG(EMU_BOOTDEF_LOW) = (BOOTDEF_LOW_1 << 8) + BOOTDEF_LOW_0;

    //
    // Disable writing to the WRPRT_DISABLE protected registers
    //
    WRPRT_ENABLE;
}

//
// configBMSPS3 - Configures a custom EMU boot configuration when 3 boot
//                mode select pins are used.
//
//                Boot Mode Number  BMSP2  BMSP1  BMSP0    Boot Mode
//                     0              0      0      0      Flash Boot
//                     1              0      0      1      UART Boot
//                     2              0      1      0      Flash Boot Alt.1
//                     3              0      1      1      UART Boot Alt.1
//                     4              1      0      0      CAN Boot
//                     5              1      0      1      SPI Boot
//                     6              1      1      0      CAN FD Boot
//                     7              1      1      1      I2C Boot
//
void configBMSPS3(void)
{
    //
    // Enable writing to the WRPRT_DISABLE protected registers
    //
    WRPRT_DISABLE;

    //
    // Write a value of 0x5A to the Key field of
    // EMU_BOOTPIN_CONFIG in order to execute
    // a custom boot process. Write the values of
    // BMSPs to be used.
    //
    HWREG(EMU_BOOTPIN_CONFIG) = (BOOTPIN_CONFIG_KEY  << 24) +
                                (BOOTPIN_CONFIG_BMSP2 << 16) +
                                (BOOTPIN_CONFIG_BMSP1 << 8) +
                                (BOOTPIN_CONFIG_BMSP0);

    //
    // Write boot mode options 3, 2, 1, and 0 to the EMU_BOOTDEF_LOW register
    //
    HWREG(EMU_BOOTDEF_LOW) = (BOOTDEF_LOW_3 << 24) + (BOOTDEF_LOW_2 << 16) +
                             (BOOTDEF_LOW_1 << 8) + BOOTDEF_LOW_0;

    //
    // Write boot mode options 7, 6, 5, and 4 to the EMU_BOOTDEF_HIGH register
    //
    HWREG(EMU_BOOTDEF_HIGH) = (BOOTDEF_HIGH_7 << 24) + (BOOTDEF_HIGH_6 << 16)
                              + (BOOTDEF_HIGH_5 << 8) + BOOTDEF_HIGH_4;

    //
    // Disable writing to the WRPRT_DISABLE protected registers
    //
    WRPRT_ENABLE;
}

//
// End of File
//
