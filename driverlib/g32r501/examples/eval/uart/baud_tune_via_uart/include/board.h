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

//
// UARTA_RX - GPIO Settings
//
#define GPIO_PIN_UARTA_RX 3
#define myUART0_UARTRX_GPIO 3
#define myUART0_UARTRX_PIN_CONFIG GPIO_3_UARTA_RX
//
// UARTA_TX - GPIO Settings
//
#define GPIO_PIN_UARTA_TX 2
#define myUART0_UARTTX_GPIO 2
#define myUART0_UARTTX_PIN_CONFIG GPIO_2_UARTA_TX

#define myUART0_BASE UARTA_BASE
#define myUART0_BAUDRATE 9600
#define myUART0_CONFIG_WLEN UART_CONFIG_WLEN_8
#define myUART0_CONFIG_STOP UART_CONFIG_STOP_ONE
#define myUART0_CONFIG_PAR UART_CONFIG_PAR_NONE
#define myUART0_FIFO_TX_LVL UART_FIFO_TX0
#define myUART0_FIFO_RX_LVL UART_FIFO_RX0

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void    Board_init();
void    UART_init();
void    SYSCTL_init();
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
