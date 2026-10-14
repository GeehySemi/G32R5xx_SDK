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
// SPIA -> mySPI0 Pinmux
//
//
// SPIA_PICO - GPIO Settings
//
#define GPIO_PIN_SPIA_PICO 8
#define mySPI0_SPIPICO_GPIO 8
#define mySPI0_SPIPICO_PIN_CONFIG GPIO_8_SPIA_SIMO
//
// SPIA_POCI - GPIO Settings
//
#define GPIO_PIN_SPIA_POCI 10
#define mySPI0_SPIPOCI_GPIO 10
#define mySPI0_SPIPOCI_PIN_CONFIG GPIO_10_SPIA_SOMI
//
// SPIA_CLK - GPIO Settings
//
#define GPIO_PIN_SPIA_CLK 9
#define mySPI0_SPICLK_GPIO 9
#define mySPI0_SPICLK_PIN_CONFIG GPIO_9_SPIA_CLK
//
// SPIA_PTE - GPIO Settings
//
#define GPIO_PIN_SPIA_PTE 11
#define mySPI0_SPIPTE_GPIO 11
#define mySPI0_SPIPTE_PIN_CONFIG GPIO_11_SPIA_STE

extern const void *destAddr;
#define mySPI0_RX_DMA_BASE DMA_CH6_BASE
#define mySPI0_RX_DMA_BURSTSIZE 8U
#define mySPI0_RX_DMA_TRANSFERSIZE 16U
extern const void *srcAddr;
#define mySPI0_TX_DMA_BASE DMA_CH5_BASE
#define mySPI0_TX_DMA_BURSTSIZE 8U
#define mySPI0_TX_DMA_TRANSFERSIZE 16U


// Interrupt Settings for INT_mySPI0_RX_DMA
#define INT_mySPI0_RX_DMA INT_DMA_CH6
extern void INT_DMA_CH6_IRQHandler(void);

// Interrupt Settings for INT_mySPI0_TX_DMA
#define INT_mySPI0_TX_DMA INT_DMA_CH5
extern void INT_DMA_CH5_IRQHandler(void);


#define mySPI0_BASE SPIA_BASE
#define mySPI0_BITRATE 500000
#define mySPI0_RX_DMA_TRIGGER DMA_TRIGGER_SPIARX
#define mySPI0_RX_DMA_ADDRESS ((uint16_t *)(SPIA_BASE + SPI_O_RXB))
#define mySPI0_TX_DMA_TRIGGER DMA_TRIGGER_SPIATX
#define mySPI0_TX_DMA_ADDRESS ((uint16_t *)(SPIA_BASE + SPI_O_TXB))

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void    Board_init();
void    DMA_init();
void    SPI_init();
void    PinMux_init();
void    SYSCTL_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
