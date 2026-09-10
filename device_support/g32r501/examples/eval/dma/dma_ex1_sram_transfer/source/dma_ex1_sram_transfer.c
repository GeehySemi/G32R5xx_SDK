//###########################################################################
//
// FILE:    dma_ex1_sram_transfer.c
//
// TITLE:   DMA SRAM Transfer
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup bitfield_example_list
//! <h1>DMA SRAM Transfer (dma_sram_transfer)</h1>
//!
//! This example uses one DMA channel to transfer data from a buffer in
//! SRAM1 to a buffer in SRAM1. The example sets the DMA channel
//! PERINTFRC bit repeatedly until the transfer of 16 bursts (where each
//! burst is 8 16-bit words) has been completed. When the whole transfer is
//! complete, it will trigger the DMA interrupt.
//!
//! \b Watch \b Variables \n
//!  - \b sdata - Data to send
//!  - \b rdata - Received data
//!
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
// 1. Updated file name to dma_ex1_sram_transfer.c and title to DMA SRAM Transfer.
// 2. Updated interrupt handling to use NVIC functions.
//
//###########################################################################

//
// Included Files
//
#include "g32r501_project.h"

//
// Defines
//
#define BURST       7       // write 7 to the register for a burst size of 8
#define TRANSFER    15      // [(MEM_BUFFER_SIZE/(BURST + 1)) - 1]

//
// Globals
//
SECTION_SRAM1_SHARE_DATA uint16_t sdata[128];
SECTION_SRAM1_SHARE_DATA uint16_t rdata[128]; 

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
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // Set the GPIO to it's default state.
    //
//  InitGpio();  // Skipped for this example

    //
    // Step 3. Initialize NVIC vector table:
    // Disable and clear all CPU interrupts
    //
    DINT;

    //
    // Initialize the NVIC control registers to their default state.
    // The default state is all NVIC interrupts disabled and flags
    // are cleared.
    //
    Interrupt_initModule();

    //
    // Initialize the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Initialize the NVIC vector table with pointers to the default Interrupt
    // Service Routines (ISR)
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_7_6_SUB_5_0);

    Interrupt_setPriority(INT_DMA_CH6,2,0);

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    Interrupt_register(INT_DMA_CH6, INT_DMA_CH6_IRQHandler);
    Interrupt_enable(INT_DMA_CH6);

    //
    // Step 4. Initialize the Device Peripherals:
    //
    dma_init();  // set up the dma

    //
    // Step 5. User specific code, enable interrupts:
    // Initialize the data buffers
    //
    for(i = 0; i < 128; i++)
    {
        sdata[i] = i;
        rdata[i] = 0;
    }

    //
    // Enable interrupts required for this example
    //
    EINT;                                // Enable Global Interrupts

    StartDMACH6();      // Start DMA channel

    done = 0;           // Test is not done yet

    while(!done)        // wait until the DMA transfer is complete
    {
        WRPRT_DISABLE;
        DmaRegs.CH6.CONTROL.bit.PERINTFRC = 1;
        WRPRT_ENABLE;

        DELAY_US(1000);
    }

    //
    // When the DMA transfer is complete the program will stop here
    //
    ESTOP0;

    while (1);
}

//
// error - Error Function which will halt the debugger
//
void error(void)
{
    ESTOP0;  //Test failed!! Stop!
    for (;;);
}

//
// dma_init - DMA setup for both TX and RX channels.
//
void dma_init()
{
    //
    // Refer to dma.c for the descriptions of the following functions.
    //

    //
    //Initialize DMA
    //
    DMAInitialize();

    DMASource = (volatile Uint16 *)sdata;
    DMADest = (volatile Uint16 *)rdata;

    //
    // configure DMA CH6
    //
    DMACH6AddrConfig(DMADest,DMASource);
    DMACH6BurstConfig(BURST,1,1);
    DMACH6TransferConfig(TRANSFER,1,1);
    DMACH6ModeConfig(0,PERINT_ENABLE,SIGDIS_DISABLE,CONT_DISABLE,
                     SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,
                     CHINT_END,CHINT_ENABLE);
}

//
// local_D_INTCH6_ISR - DMA Channel6 ISR
//
void INT_DMA_CH6_IRQHandler(void)
{
    Uint16 i;

    WRPRT_DISABLE;  // NEED TO EXECUTE WRPRT_DISABLE INSIDE ISR !!!
    DmaRegs.CH6.CONTROL.bit.HALT = 1;
    WRPRT_ENABLE;

    for( i = 0; i < 128; i++ )
    {
        //
        // check for data integrity
        //
        if (rdata[i] != i)
        {
            error();
        }
    }

    done = 1; // Test done.
    return;
}

//
// End of file
//
