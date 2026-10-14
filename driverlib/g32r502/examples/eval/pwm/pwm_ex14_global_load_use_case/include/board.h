//#############################################################################
//
// FILE:    board.h
//
// TITLE:   Board header file
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
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
// 1. Modified function names and macro definition names.
//
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

//
// PWM1 -> myPWM1 Pinmux
//
//
// PWM1_A - GPIO Settings
//
#define GPIO_PIN_PWM1_A 0
#define myPWM1_PWMA_GPIO 0
#define myPWM1_PWMA_PIN_CONFIG GPIO_0_PWM1_A
//
// PWM1_B - GPIO Settings
//
#define GPIO_PIN_PWM1_B 1
#define myPWM1_PWMB_GPIO 1
#define myPWM1_PWMB_PIN_CONFIG GPIO_1_PWM1_B

//
// PWM2 -> myPWM2 Pinmux
//
//
// PWM2_A - GPIO Settings
//
#define GPIO_PIN_PWM2_A 2
#define myPWM2_PWMA_GPIO 2
#define myPWM2_PWMA_PIN_CONFIG GPIO_2_PWM2_A
//
// PWM2_B - GPIO Settings
//
#define GPIO_PIN_PWM2_B 3
#define myPWM2_PWMB_GPIO 3
#define myPWM2_PWMB_PIN_CONFIG GPIO_3_PWM2_B

//
// PWM3 -> myPWM3 Pinmux
//
//
// PWM3_A - GPIO Settings
//
#define GPIO_PIN_PWM3_A 4
#define myPWM3_PWMA_GPIO 4
#define myPWM3_PWMA_PIN_CONFIG GPIO_4_PWM3_A
//
// PWM3_B - GPIO Settings
//
#define GPIO_PIN_PWM3_B 5
#define myPWM3_PWMB_GPIO 5
#define myPWM3_PWMB_PIN_CONFIG GPIO_5_PWM3_B
//
// GPIO6 - GPIO Settings
//
#define myGPIO6_GPIO_PIN_CONFIG GPIO_6_GPIO6

//*****************************************************************************
//
// COMP Configurations
//
//*****************************************************************************
#define myCOMP1_BASE COMP1_BASE
#define myCOMP1_HIGH_COMP_BASE COMP1_BASE
#define myCOMP1_LOW_COMP_BASE COMP1_BASE

#define myPWM1_BASE PWM1_BASE
#define myPWM2_BASE PWM2_BASE
#define myPWM3_BASE PWM3_BASE

#define myINPUTXBARINPUT0_SOURCE 6
#define myINPUTXBARINPUT0_INPUT XBAR_INPUT1

#define myPWMXBAR4 XBAR_TRIP4
#define myPWMXBAR4_ENABLED_MUXES (XBAR_MUX00)

#define myGPIO6 6

// Interrupt Settings for INT_myPWM1_TRIP_ZONE
#define INT_myPWM1_TRIP_ZONE INT_PWM1_TRIP_ZONE
extern void INT_PWM1_IRQHandler(void);

// Interrupt Settings for INT_myPWM2_TRIP_ZONE
#define INT_myPWM2_TRIP_ZONE INT_PWM2_TRIP_ZONE
extern void INT_PWM2_IRQHandler(void);

// Interrupt Settings for INT_myPWM2_TRIP_ZONE
#define INT_myPWM3_TRIP_ZONE INT_PWM3_TRIP_ZONE
extern void INT_PWM3_IRQHandler(void);

void    COMP_init();
void    Board_init();
void    PWM_init();
void    SYNC_init();
void    PinMux_init();
void    GPIO_init();
void    PWMXBAR_init();
void    INPUTXBAR_init();
//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
