//###########################################################################
//
// FILE:    dma_ex1_gsram_transfer.c
//
// TITLE:   DMA GSRAM Transfer
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1>DMA GSRAM Transfer (dma_ex1_gsram_transfer)</h1>
//!
//!  This example uses one DMA channel to transfer data from a buffer in
//!  RAMGS0 to a buffer in RAMGS1. The example sets the DMA channel
//!  PERINTFRC bit repeatedly until the transfer of 16 bursts (where each
//!  burst is 8 16-bit words) has been completed. When the whole transfer is
//!  complete, it will trigger the DMA interrupt.
//!
//!  \b Watch \b Variables \n
//!  - \b sData - Data to send
//!  - \b rData - Received data
//!
//
//###########################################################################
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
// - 2024-09-13: 
// 1. Modified peripheral register names by Geehy Semiconductor.
// 2. Modified Geehy interrupt usage.
//
//###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Globals
//
__attribute__((section("sram1.share_data"))) uint16_t sData[128];   // Send data buffer
__attribute__((section("sram1.share_data"))) uint16_t rData[128];   // Receive data buffer

volatile uint16_t done;

const void *destAddr = (const void *)rData;
const void *srcAddr = (const void *)sData;

//
// Function Prototypes
//
void error();
void INT_DMA_CH6_IRQHandler(void);

//
// Main
//
void example_main(void)
{
    uint16_t i;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize NVIC and clear NVIC registers. Disables CPU interrupts
    //
    Interrupt_initModule();

    //
    // Initialize the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR)
    //
    Interrupt_initVectorTable();

    Board_init();

    //
    // User specific code, enable interrupts:
    // Initialize the data buffers
    //
    for(i = 0; i < 128; i++)
    {
        sData[i] = i;
        rData[i] = 0;
    }

    //
    // Set the priority group to indicate the PREEMPT and SUB priortiy bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_7_6_SUB_5_0);

    //
    // Set the global and group priority to allow CPU interrupts
    // with higher priority
    //
    Interrupt_setPriority(INT_myDMA0, 1, 0);

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_myDMA0);
    EINT;                                // Enable Global Interrupts
    // Start DMA channel
    DMA_startChannel(myDMA0_BASE);

    done = 0;           // Test is not done yet

    while (!done)        // wait until the DMA transfer is complete
    {
       DMA_forceTrigger(myDMA0_BASE);

        for (i = 0; i < 255; i++)
        {
            __asm(" NOP");
        }
    }

    //
    // When the DMA transfer is complete the program will stop here
    //
    ESTOP0;

    for (;;)
    {
    }
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
// local_D_INTCH6_ISR - DMA Channel6 ISR
//
void INT_DMA_CH6_IRQHandler(void)
{
    uint16_t i;

    DMA_stopChannel(myDMA0_BASE);

    for( i = 0; i < 128; i++ )
    {
        //
        // check for data integrity
        //
        if (rData[i] != i)
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
