//###########################################################################
//
// FILE:    board.h
//
// TITLE:   Board header file.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
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
// GPIO28 - GPIO Settings
//
#define myGPIOInputInterrupt0_GPIO_PIN_CONFIG GPIO_28_GPIO28
//
// GPIO13 - GPIO Settings
//
#define myGPIOOutput0_GPIO_PIN_CONFIG DEVICE_GPIO_CFG_LED1

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define myGPIOInputInterrupt0 28
void myGPIOInputInterrupt0_init();
#define myGPIOOutput0 DEVICE_GPIO_PIN_LED1
void myGPIOOutput0_init();

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void    Board_init();
void    GPIO_init();
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
