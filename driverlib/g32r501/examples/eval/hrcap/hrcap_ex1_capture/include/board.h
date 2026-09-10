//###########################################################################
//
// FILE:    board.h
//
// TITLE:   Board header file.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
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
#ifndef BOARD_H
#define BOARD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************
//
// GPIO2 - GPIO Settings
//
#define myGPIO0_GPIO_PIN_CONFIG GPIO_2_GPIO2

//
// OTHER -> myOTHER0 Pinmux
//
//
// XCLKOUT - GPIO Settings
//
#define GPIO_PIN_XCLKOUT 16
#define myOTHER0_XCLKOUT_GPIO 16
#define myOTHER0_XCLKOUT_PIN_CONFIG GPIO_16_XCLKOUT

//*****************************************************************************
//
// CAP Configurations
//
//*****************************************************************************
#define myCAP0_BASE CAP7_BASE
#define myCAP0_HR_BASE HRCAP7_BASE
#define myCAP0_SIGNAL_MUNIT_BASE CAP7SIGNALMONITORING_BASE
void myCAP0_init();

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define myGPIO0 2
void myGPIO0_init();

//*****************************************************************************
//
// INPUTXBAR Configurations
//
//*****************************************************************************
#define myINPUTXBARINPUT0_SOURCE 2
#define myINPUTXBARINPUT0_INPUT XBAR_INPUT7
void myINPUTXBARINPUT0_init();

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_myCAP0
#define INT_myCAP0 INT_CAP7
#define INT_myCAP0_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP4
extern void INT_myCAP0_ISR(void);

// Interrupt Settings for INT_myCAP0_HR
#define INT_myCAP0_HR INT_CAP7_2
#define INT_myCAP0_HR_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP4
extern void INT_myCAP0_HR_ISR(void);

//*****************************************************************************
//
// OTHER Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void    Board_init();
void    CAP_init();
void    GPIO_init();
void    INPUTXBAR_init();
void    INTERRUPT_init();
void    OTHER_init();
void    SYNC_init();
void    PinMux_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
