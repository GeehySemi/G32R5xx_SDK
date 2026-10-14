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
// 1. Partial comments, macro definitions, function names
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

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************
//
// GPIO16 - GPIO Settings
//

//*****************************************************************************
//
// CAP Configurations
//
//*****************************************************************************
#define myCAP1_BASE CAP1_BASE
#define myCAP1_SIGNAL_MUNIT_BASE CAP1SIGNALMONITORING_BASE
void myCAP1_init();
#define myCAP2_BASE CAP2_BASE
#define myCAP2_SIGNAL_MUNIT_BASE CAP2SIGNALMONITORING_BASE
void myCAP2_init();
#define myCAP3_BASE CAP3_BASE
#define myCAP3_SIGNAL_MUNIT_BASE CAP3SIGNALMONITORING_BASE
void myCAP3_init();

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************

//*****************************************************************************
//
//
//*****************************************************************************

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_myCAP3
#define INT_myCAP3 INT_CAP3
extern void INT_myCAP3_ISR(void);

// Redefine sysclk at 100 MHz
#define CAP_SETCLOCK_CFG         (SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(5) | \
                                     SYSCTL_FMULT_0 | SYSCTL_ODIV(1) | SYSCTL_SYSDIV(1) | \
                                     SYSCTL_PLL_ENABLE)

//
// 100MHz SYSCLK frequency based on the above CAP_SETCLOCK_CFG.
//
#define CAP_SYSCLK_FREQ         (DEVICE_OSCSRC_FREQ * (5 + 0)) / (1 * 1)

//
// 100MHz APBCLK frequency based on the above CAP_SYSCLK_FREQ and 
// APB peripheral clock divider of 1.
//
#define CAP_APBCLK_FREQ          (CAP_SYSCLK_FREQ / 1)


//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
// INPUTXBAR Configurations
#define myINPUTXBARINPUT0_SOURCE 16
#define myINPUTXBARINPUT0_INPUT XBAR_INPUT7
void myINPUTXBARINPUT0_init();

#define myGPIO0_GPIO_PIN_CONFIG GPIO_16_GPIO16
#define myGPIO0 16
void myGPIO0_init();

void    Board_init();
void    CAP_init();
void    GPIO_init();
void    INPUTXBAR_init();
void    SYNC_init();
void    PinMux_init();
void    Clockswitch();
//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
