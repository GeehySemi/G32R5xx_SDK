//#############################################################################
//
// FILE:    board.c
//
// TITLE:   Board source file
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//###########################################################################
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
// 2. Added DMA_init function definitions.
//
//###########################################################################

#include "board.h"

void Board_init()
{
    WRPRT_DISABLE;

    PinMux_init();
    DMA_init();
    INTERRUPT_init();

    WRPRT_ENABLE;
}

void PinMux_init()
{

}

void DMA_init()
{
    DMA_initController();
     
    //myDMA0 initialization
    DMA_setEmulationMode(DMA_EMULATION_STOP);
    DMA_configAddresses(myDMA0_BASE, destAddr, srcAddr);
    DMA_configBurst(myDMA0_BASE, 8U, 1, 1);
    DMA_configTransfer(myDMA0_BASE, 16U, 1, 1);
    DMA_configWrap(myDMA0_BASE, 65535U, 0, 65535U, 0);
    DMA_configMode(myDMA0_BASE, DMA_TRIGGER_SOFTWARE, DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_DISABLE | DMA_CFG_SIZE_16BIT);
    DMA_setInterruptMode(myDMA0_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(myDMA0_BASE);
    DMA_disableOverrunInterrupt(myDMA0_BASE);
    DMA_enableTrigger(myDMA0_BASE);
    DMA_stopChannel(myDMA0_BASE);
}
void INTERRUPT_init()
{
    // Interrupt Setings for INT_myDMA0
    Interrupt_register(INT_myDMA0, &INT_DMA_CH6_IRQHandler);
    Interrupt_disable(INT_myDMA0);
}

