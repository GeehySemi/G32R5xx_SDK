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
// PWM1 -> myPWM1 Pinmux
//
#define GPIO_PIN_PWM1_A 0
#define myPWM1_PWMA_GPIO 0
#define myPWM1_PWMA_PIN_CONFIG GPIO_0_PWM1_A
#define GPIO_PIN_PWM1_B 1
#define myPWM1_PWMB_GPIO 1
#define myPWM1_PWMB_PIN_CONFIG GPIO_1_PWM1_B

//
// PWM2 -> myPWM2 Pinmux
//
#define GPIO_PIN_PWM2_A 2
#define myPWM2_PWMA_GPIO 2
#define myPWM2_PWMA_PIN_CONFIG GPIO_2_PWM2_A
#define GPIO_PIN_PWM2_B 3
#define myPWM2_PWMB_GPIO 3
#define myPWM2_PWMB_PIN_CONFIG GPIO_3_PWM2_B

//*****************************************************************************
//
// PWM Configurations
//
//*****************************************************************************
#define myPWM1_BASE PWM1_BASE
#define myPWM1_TBPRD 99
#define myPWM2_BASE PWM2_BASE
#define myPWM2_TBPRD 100

//*****************************************************************************
//
// INPUTXBAR Configurations
//
//*****************************************************************************
// Unused GPIO40 XBAR mapping removed; INPUTXBAR_init() is empty.

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void    Board_init();
void    PWM_init();
void    INPUTXBAR_init();
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
