//#############################################################################
//
// FILE:    board.h
//
// TITLE:   Board header file
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2024 Geehy Semiconductor - http://www.geehy.com/
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
// - 2024-07-08: 
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

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************

//
// QEP1 -> myQEP0 Pinmux
//
//
// QEP1_A - GPIO Settings
//
#define GPIO_PIN_QEP1_A 6
#define myQEP0_QEPA_GPIO 6
#define myQEP0_QEPA_PIN_CONFIG GPIO_6_QEP1_A
//
// QEP1_B - GPIO Settings
//
#define GPIO_PIN_QEP1_B 11
#define myQEP0_QEPB_GPIO 11
#define myQEP0_QEPB_PIN_CONFIG GPIO_11_QEP1_B
//
// QEP1_STROBE - GPIO Settings
//
#define GPIO_PIN_QEP1_STROBE 12
#define myQEP0_QEPSTROBE_GPIO 12
#define myQEP0_QEPSTROBE_PIN_CONFIG GPIO_12_QEP1_STROBE
//
// QEP1_INDEX - GPIO Settings
//
#define GPIO_PIN_QEP1_INDEX 13
#define myQEP0_QEPINDEX_GPIO 13
#define myQEP0_QEPINDEX_PIN_CONFIG GPIO_13_QEP1_INDEX

//*****************************************************************************
//
// QEP Configurations
//
//*****************************************************************************
#define myQEP0_BASE QEP1_BASE
void myQEP0_init();

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_myQEP0
#define INT_myQEP0 INT_QEP1
#define INT_myQEP0_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP5
extern void INT_myQEP0_ISR(void);

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void    Board_init();
void    QEP_init();
void    INTERRUPT_init();
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
