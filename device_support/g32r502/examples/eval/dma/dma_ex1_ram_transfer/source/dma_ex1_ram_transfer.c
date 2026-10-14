//###########################################################################
//
// FILE:    dma_ex1_ram_transfer.c
//
// TITLE:   DMA SRAM Transfer
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup bitfield_example_list
//! <h1>DMA SRAM Transfer (dma_ex1_ram_transfer)</h1>
//!
//! This example uses DMA channel 6 to copy 128 halfwords from \b sdata[] to
//! \b rdata[] in DTCM. Software sets CH6 PERINTFRC until 16 bursts (8
//! halfwords each) finish; the channel interrupt runs when the transfer ends.
//! Program DMA SRC/DST with the CPU pointer plus \b DMA_DTCM_ADDR_OFFSET.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - \b sdata
//!  - \b rdata
//!  - \b done
//!
//
//###########################################################################
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
// 1. Updated file name to dma_ex1_ram_transfer.c and title to DMA SRAM Transfer.
// 2. Updated interrupt handling to use NVIC functions.
// 3. Added DMA ITCM/DTCM address offsets for SRC/DST programming.
//
//###########################################################################

//
// Included Files
//
#include "g32r502_project.h"

//
// Defines
//
#define BURST       7       // 8 halfwords per burst
#define TRANSFER    15      // 16 bursts (128 halfwords total)

//
// Globals
//
SECTION_DTCM_DATA uint16_t sdata[128];
SECTION_DTCM_DATA uint16_t rdata[128]; 

volatile Uint16 *DMADest;
volatile Uint16 *DMASource;
volatile Uint16 done;

//
// Function Prototypes
//
void INT_DMA_CH6_IRQHandler(void);
void dma_init(void);
void error();

//
// Main
//
void example_main(void)
{
    Uint16 i;

    //
    // Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    //
    InitSysCtrl();

    //
    // Disable CPU interrupts
    //
    DINT;

    //
    // Globally disable interrupts and clear all NVIC enable/pending bits
    //
    Interrupt_initModule();

    //
    // Initialize RAM vector table and set VTOR; unregistered IRQs use
    // Interrupt_defaultHandler until Interrupt_register() is called
    //
    Interrupt_initVectorTable();

    //
    // Register and enable DMA channel 6 interrupt
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);
    Interrupt_setPriority(INT_DMA_CH6, 2, 0);
    Interrupt_register(INT_DMA_CH6, INT_DMA_CH6_IRQHandler);
    Interrupt_enable(INT_DMA_CH6);

    //
    // Configure DMA
    //
    dma_init();

    //
    // Initialize source and destination buffers
    //
    for(i = 0; i < 128; i++)
    {
        sdata[i] = i;
        rdata[i] = 0;
    }

    //
    // Enable global interrupts
    //
    EINT;

    //
    // Start DMA channel 6
    //
    StartDMACH6();

    done = 0;

    //
    // Force peripheral interrupts until the transfer completes
    //
    while(!done)
    {
        WRPRT_DISABLE;
        DmaRegs.CH6.CONTROL.bit.PERINTFRC = 1;
        WRPRT_ENABLE;

        DELAY_US(1000);
    }

    ESTOP0;

    while (1);
}

//
// error - Error Function which will halt the debugger
//
void error(void)
{
    ESTOP0;
    for (;;);
}

//
// dma_init - Configure DMA channel 6 for the RAM transfer.
//
void dma_init()
{
    //
    // Initialize DMA module
    //
    DMAInitialize();

    //
    // Convert CPU DTCM pointers to the DMA address view
    //
    DMASource = (volatile Uint16 *)DMA_ADDR_DTCM(sdata);
    DMADest = (volatile Uint16 *)DMA_ADDR_DTCM(rdata);

    //
    // Configure DMA channel 6
    //
    DMACH6AddrConfig(DMADest, DMASource);
    DMACH6BurstConfig(BURST, 1, 1);
    DMACH6TransferConfig(TRANSFER, 1, 1);
    DMACH6ModeConfig(0, PERINT_ENABLE, SIGDIS_DISABLE, CONT_DISABLE,
                     SYNC_DISABLE, SYNC_SRC, OVRFLOW_DISABLE, SIXTEEN_BIT,
                     CHINT_END, CHINT_ENABLE);
}

//
// INT_DMA_CH6_IRQHandler - DMA channel 6 interrupt handler
//
void INT_DMA_CH6_IRQHandler(void)
{
    Uint16 i;

    //
    // Halt channel 6; write-protect must be disabled to access DMA registers
    //
    WRPRT_DISABLE;
    DmaRegs.CH6.CONTROL.bit.HALT = 1;
    WRPRT_ENABLE;

    for(i = 0; i < 128; i++)
    {
        if (rdata[i] != i)
        {
            error();
        }
    }

    done = 1;
}

//
// End of File
//
