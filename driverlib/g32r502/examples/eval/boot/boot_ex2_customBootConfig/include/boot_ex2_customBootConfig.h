
//###########################################################################
//
// FILE:    boot_ex2_customBootConfig.h
//
// TITLE:   Defines and Function Prototypes for Custom Boot Configuration
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
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
// 1. Partial comments, macro definitions
// 2. Align G32R502 peripheral boot GPIO comments; add CAN FD boot modes.
// 3. Add MDK Configuration Wizard annotations for boot flow and BOOTDEF slots.
//
//###########################################################################

#ifndef _BOOT_EX2_CUSTOMBOOTCONFIG_H_
#define _BOOT_EX2_CUSTOMBOOTCONFIG_H_

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Boot Emulation Flow
// <q> Emulate standalone boot flow
// <i> Requires programmed DCS OTP. Writes key 0xA5 to EMU_BOOTPIN_CONFIG.
#define STANDALONE_BOOT        0

// <o> Boot mode select pin count
//   <0=> 0 BMSPs Flash boot only
//   <1=> 1 BMSP Flash or UART
//   <2=> 3 BMSPs 8-entry boot table
#define BOOT_EX2_BMSP_GROUP    0
// </h>

// <h> BMSP GPIO Assignment
// <i> Set 255 to disable a BMSP. Invalid GPIOs 20-23 36 38 60-223.
// <o> BMSP0 GPIO <0-255>
#define BOOTPIN_CONFIG_BMSP0        0
// <o> BMSP1 GPIO <0-255>
#define BOOTPIN_CONFIG_BMSP1        1
// <o> BMSP2 GPIO <0-255>
#define BOOTPIN_CONFIG_BMSP2        2
// </h>

// <h> BOOTDEF Slot Assignment
// <i> Boot mode value for each BMSP truth-table slot. See mode defines below.
// <o> BOOTDEF0 slot 0
//   <0x03=> Flash Boot
//   <0x01=> UART Boot
//   <0x23=> Flash Boot Alt1
//   <0x21=> UART Boot Alt1
//   <0x02=> CAN Boot
//   <0x06=> SPI Boot
//   <0x08=> CAN FD Boot
//   <0x07=> I2C Boot
#define BOOTDEF_LOW_0        0x03
// <o> BOOTDEF1 slot 1
//   <0x03=> Flash Boot
//   <0x01=> UART Boot
//   <0x23=> Flash Boot Alt1
//   <0x21=> UART Boot Alt1
//   <0x02=> CAN Boot
//   <0x06=> SPI Boot
//   <0x08=> CAN FD Boot
//   <0x07=> I2C Boot
#define BOOTDEF_LOW_1        0x01
// <o> BOOTDEF2 slot 2
//   <0x03=> Flash Boot
//   <0x01=> UART Boot
//   <0x23=> Flash Boot Alt1
//   <0x21=> UART Boot Alt1
//   <0x02=> CAN Boot
//   <0x06=> SPI Boot
//   <0x08=> CAN FD Boot
//   <0x07=> I2C Boot
#define BOOTDEF_LOW_2        0x23
// <o> BOOTDEF3 slot 3
//   <0x03=> Flash Boot
//   <0x01=> UART Boot
//   <0x23=> Flash Boot Alt1
//   <0x21=> UART Boot Alt1
//   <0x02=> CAN Boot
//   <0x06=> SPI Boot
//   <0x08=> CAN FD Boot
//   <0x07=> I2C Boot
#define BOOTDEF_LOW_3        0x21
// <o> BOOTDEF4 slot 4
//   <0x03=> Flash Boot
//   <0x01=> UART Boot
//   <0x23=> Flash Boot Alt1
//   <0x21=> UART Boot Alt1
//   <0x02=> CAN Boot
//   <0x06=> SPI Boot
//   <0x08=> CAN FD Boot
//   <0x07=> I2C Boot
#define BOOTDEF_HIGH_4        0x02
// <o> BOOTDEF5 slot 5
//   <0x03=> Flash Boot
//   <0x01=> UART Boot
//   <0x23=> Flash Boot Alt1
//   <0x21=> UART Boot Alt1
//   <0x02=> CAN Boot
//   <0x06=> SPI Boot
//   <0x08=> CAN FD Boot
//   <0x07=> I2C Boot
#define BOOTDEF_HIGH_5        0x06
// <o> BOOTDEF6 slot 6
//   <0x03=> Flash Boot
//   <0x01=> UART Boot
//   <0x23=> Flash Boot Alt1
//   <0x21=> UART Boot Alt1
//   <0x02=> CAN Boot
//   <0x06=> SPI Boot
//   <0x08=> CAN FD Boot
//   <0x07=> I2C Boot
#define BOOTDEF_HIGH_6        0x08
// <o> BOOTDEF7 slot 7
//   <0x03=> Flash Boot
//   <0x01=> UART Boot
//   <0x23=> Flash Boot Alt1
//   <0x21=> UART Boot Alt1
//   <0x02=> CAN Boot
//   <0x06=> SPI Boot
//   <0x08=> CAN FD Boot
//   <0x07=> I2C Boot
#define BOOTDEF_HIGH_7        0x07
// </h>

//
// MDK Target / IAR configuration names override the wizard default above.
//
#if defined(ZERO_BMSPS)
    #undef BOOT_EX2_BMSP_GROUP
    #define BOOT_EX2_BMSP_GROUP    0
#elif defined(ONE_BMSP)
    #undef BOOT_EX2_BMSP_GROUP
    #define BOOT_EX2_BMSP_GROUP    1
#elif defined(THREE_BMSPS)
    #undef BOOT_EX2_BMSP_GROUP
    #define BOOT_EX2_BMSP_GROUP    2
#endif

//
// Register and boot-mode reference (not edited by Configuration Wizard)
//
// When the standalone boot flow is emulated, the 3 OTP registers below are programmed.
// The table below specifies the content in each register.
//
//                              Bits       Name                                 Description
// Z1_OTP_BOOTPIN_CONFIG:       31-24      Key                                  Write 0x5A to use custom boot config.
//                                                                              Write any other value in order to
//                                                                              use factory default.
//
//                              23-16      Boot Mode Select Pin 2 (BMSP2)       Set to GPIO to be used during boot
//                              15-8       Boot Mode Select Pin 1 (BMSP1)       Refer to BMSP2
//                              7-0        Boot Mode Select Pin 0 (BMSP0)       Refer to BMSP2
//
// Z1_OTP_BOOTDEF_LOW:          31-24      BOOTDEF3                             BOOTDEF option 3
//                              23-16      BOOTDEF2                             BOOTDEF option 2
//                              15-8       BOOTDEF1                             BOOTDEF option 1
//                              7-0        BOOTDEF0                             BOOTDEF option 0
//
// Z1_OTP_BOOTDEF_HIGH:         31-24      BOOTDEF7                             BOOTDEF option 7
//                              23-16      BOOTDEF6                             BOOTDEF option 6
//                              15-8       BOOTDEF5                             BOOTDEF option 5
//                              7-0        BOOTDEF4                             BOOTDEF option 4
//
// Z1_OTP_BOOTPIN_CONFIG is read by boot ROM from address 0x0810A010, but address 0x0810A018 needs to be written to
// Z1_OTP_BOOTDEF_LOW is read by boot ROM from address 0x0810A018, but address 0x0810A038 needs to be written to
// Z1_OTP_BOOTDEF_HIGH is read by boot ROM from address 0x0810A008, but address 0x0810A03C needs to be written to
//

//
// EMU_BOOTPIN_CONFIG is the emulation equivalent of Z1_OTP_BOOTPIN_CONFIG.
//                              Bits       Name                                 Description
// EMU_BOOTPIN_CONFIG:          31-24      Key                                  Write 0x5A to use emulation custom
//                                                                              boot config. Write 0xA5 to emulate
//                                                                              standalone boot mode. Write any other
//                                                                              value for Wait Boot.
//
//                              23-16      Boot Mode Select Pin 2 (BMSP2)       Set to GPIO to be used during boot
//                              15-8       Boot Mode Select Pin 1 (BMSP1)       Refer to BMSP2
//                              7-0        Boot Mode Select Pin 0 (BMSP0)       Refer to BMSP2
//
// The address of EMU_BOOTPIN_CONFIG is 0x40012C00
//
#define EMU_BOOTPIN_CONFIG     (uint32_t)0x40012C00

//
// EMU_BOOTDEF_LOW is the emulation equivalent of Z1_OTP_BOOTDEF_LOW.
//
// EMU_BOOTDEF_LOW:          31-24      BOOTDEF3                             BOOTDEF option 3
//                           23-16      BOOTDEF2                             BOOTDEF option 2
//                           15-8       BOOTDEF1                             BOOTDEF option 1
//                           7-0        BOOTDEF0                             BOOTDEF option 0
//
// The address of EMU_BOOTDEF_LOW is 0x40012C04
//
#define EMU_BOOTDEF_LOW        (uint32_t)0x40012C04

//
// EMU_BOOTDEF_HIGH is the emulation equivalent of Z1_OTP_BOOTDEF_HIGH.
//
// EMU_BOOTDEF_HIGH:         31-24      BOOTDEF7                             BOOTDEF option 7
//                           23-16      BOOTDEF6                             BOOTDEF option 6
//                           15-8       BOOTDEF5                             BOOTDEF option 5
//                           7-0        BOOTDEF4                             BOOTDEF option 4
//
// The address of EMU_BOOTDEF_HIGH is 0x40012C08
//
#define EMU_BOOTDEF_HIGH         (uint32_t)0x40012C08

//
// BOOTPIN_CONFIG_KEY is the value for the
// bootpin config key that allows for a custom
// boot process to be executed.
//
#define BOOTPIN_CONFIG_KEY        (uint32_t)0x5A

//
// EMU_STANDALONE_KEYVAL is the value for the
// emulation bootpin config key that allows
// the standalone boot process to be executed
// while debugger is connected.
//
#define EMU_STANDALONE_KEYVAL     (uint32_t)0xA5

//
// Boot Mode Definitions
//

//
// Parallel Boot
//
#define PARALLEL_BOOT          (uint32_t)0x00

//
// UART Boot (Mode 0x01)
// Tx: GPIO29; Rx: GPIO28
// Alternatives: 0x21 GPIO1/GPIO0, 0x41 GPIO8/GPIO9, 0x61 GPIO7/GPIO3,
//               0x81 GPIO16/GPIO3
//
#define UART_BOOT               (uint32_t)0x01

//
// UART Boot Alternative 1 (Mode 0x21)
// Tx: GPIO1; Rx: GPIO0
//
#define UART_BOOT_ALT1          (uint32_t)0x21

//
// CAN Boot (Mode 0x02)
// Tx: GPIO7; Rx: GPIO5
// Alternatives: 0x22 GPIO32/GPIO33, 0x42 GPIO2/GPIO3, 0x62 GPIO13/GPIO12
//
#define CAN_BOOT               (uint32_t)0x02

//
// Flash Boot
// Bank 0, Sector 0(Busmatrix IF)
//
#define FLASH_BOOT             (uint32_t)0x03

//
// Flash Boot Alternative
// Bank 0, Sector 0(ITCM IF)
//
#define FLASH_BOOT_ALT1        (uint32_t)0x23

//
// Wait Boot
// WDog enabled
//
#define WAIT_BOOT              (uint32_t)0x04

//
// RAM Boot
//
#define RAM_BOOT               (uint32_t)0x05

//
// SPI Master Boot (Mode 0x06)
// MOSI: GPIO7; MISO: GPIO1; SCK: GPIO3; CS: GPIO5
// Alternatives: 0x26 GPIO16/GPIO1/GPIO3/GPIO0, 0x46 GPIO8/GPIO10/GPIO9/GPIO11,
//               0x66 GPIO16/GPIO13/GPIO12/GPIO29
//
#define SPI_MASTER_BOOT        (uint32_t)0x06

//
// I2C Master Boot (Mode 0x07)
// SDA: GPIO0; SCL: GPIO1
// Alternatives: 0x27 GPIO32/GPIO33, 0x47 GPIO5/GPIO4
//
#define I2C_MASTER_BOOT        (uint32_t)0x07

//
// CAN FD Boot (Mode 0x08)
// Tx: GPIO1; Rx: GPIO0
//
#define CANFD_BOOT             (uint32_t)0x08

//
// CAN FD Boot Alternative 1 (Mode 0x28)
// Tx: GPIO4; Rx: GPIO5
//
#define CANFD_BOOT_ALT1        (uint32_t)0x28

//
// CAN FD Boot Alternative 2 (Mode 0x48)
// Tx: GPIO13; Rx: GPIO12
//
#define CANFD_BOOT_ALT2        (uint32_t)0x48

//
// BOOTPIN_CONFIG_BMSPDISABLE is the value that
// causes a BMSP to be disabled.
//
#define BOOTPIN_CONFIG_BMSPDISABLE        (uint32_t)0xFF

//
// Function Prototypes
//
void configBMSPS0(void);
void configBMSPS1(void);
void configBMSPS3(void);

#endif // _BOOT_EX2_CUSTOMBOOTCONFIG_H_

// 
// End of File 
//
