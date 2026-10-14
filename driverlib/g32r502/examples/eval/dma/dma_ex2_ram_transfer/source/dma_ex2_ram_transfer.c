//###########################################################################
//
// FILE:    dma_ex2_gsram_transfer.c
//
// TITLE:   DMA GSRAM Transfer
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1>DMA GSRAM Transfer (dma_ex2_gsram_transfer)</h1>
//!
//!  This example uses DMA channel 6 to copy 128 halfwords from \b sData[] to
//!  \b rData[] in DTCM. Software triggers the channel until 16 bursts (8
//!  halfwords each) complete and the channel interrupt fires. Program DMA
//!  SRC/DST with the CPU pointer plus \b DMA_DTCM_ADDR_OFFSET.
//!
//!  \b External \b Connections \n
//!  - None.
//!
//!  \b Watch \b Variables \n
//!  - \b sData
//!  - \b rData
//!  - \b done
//!
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
// 1. Modified peripheral register names by Geehy Semiconductor.
// 2. Modified Geehy interrupt usage.
// 3. Added DMA ITCM/DTCM address offsets for SRC/DST programming.
//
//###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define BURST       8       // 8 halfwords per burst
#define TRANSFER    16      // 16 bursts (128 halfwords total)

//
// Globals
//
SECTION_DTCM_DATA uint16_t sData[128];   // Send data buffer
SECTION_DTCM_DATA uint16_t rData[128];   // Receive data buffer
volatile uint16_t done;

//
// Function Prototypes
//
void INT_myDMA6_ISR(void);
void initDMA(void);
void error();

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
    // Globally disable interrupts and clear all NVIC enable/pending bits
    //
    Interrupt_initModule();

    //
    // Initialize RAM vector table and set VTOR; unregistered IRQs use
    // Interrupt_defaultHandler until Interrupt_register() is called
    //
    Interrupt_initVectorTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    Interrupt_register(INT_DMA_CH6, &INT_myDMA6_ISR);

    //
    // Initialize the Device Peripherals:
    //
    initDMA();  // set up the dma

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
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    //
    // Set the global and group priority to allow CPU interrupts
    // with higher priority
    //
    Interrupt_setPriority(INT_DMA_CH6, 1, 0);

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_DMA_CH6);
    EINT;                                // Enable Global Interrupts
    // Start DMA channel
    DMA_startChannel(DMA_CH6_BASE);

    done = 0;           // Test is not done yet

    while(!done)        // wait until the DMA transfer is complete
    {
        DMA_forceTrigger(DMA_CH6_BASE);

        for (int i = 0; i < 255; i++)
        {
            __asm("NOP");
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
// dma_init - DMA setup for both TX and RX channels.
//
void initDMA()
{
    //
    // Refer to dma.c for the descriptions of the following functions.
    //

    //
    // Initialize DMA
    //
    DMA_initController();

    DMA_ConfigParams  transfParams;

    //
    // Configure DMA CH6
    //
    transfParams.transferTrigger  = DMA_TRIGGER_SOFTWARE;
    transfParams.interruptMode    = DMA_INT_AT_END;
    transfParams.enableInterrupt  = 1;
    transfParams.configSize       = DMA_CFG_SIZE_16BIT;
    transfParams.transferMode     = DMA_CFG_ONESHOT_DISABLE;
    transfParams.reinitMode       = DMA_CFG_CONTINUOUS_DISABLE;
    transfParams.burstSize        = BURST;
    transfParams.transferSize     = TRANSFER;
    transfParams.srcWrapSize      = 0xFFFF;
    transfParams.destWrapSize     = 0xFFFF;
    transfParams.destAddr         = DMA_ADDR_DTCM(rData);
    transfParams.srcAddr          = DMA_ADDR_DTCM(sData);
    transfParams.srcBurstStep     = 1;
    transfParams.destBurstStep    = 1;
    transfParams.srcTransferStep  = 1;
    transfParams.destTransferStep = 1;
    transfParams.srcWrapStep      = 0;
    transfParams.destWrapStep     = 0;

    DMA_configChannel(DMA_CH6_BASE, &transfParams);
}

//
// local_D_INTCH6_ISR - DMA Channel6 ISR
//
void INT_myDMA6_ISR(void)
{
    uint16_t i;

    DMA_stopChannel(DMA_CH6_BASE);

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

