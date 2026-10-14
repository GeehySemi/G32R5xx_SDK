//#############################################################################
//
// FILE:    timer_ex1_tmrs.c
//
// TITLE:   CPU Timers Example
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup bitfield_example_list
//! <h1> CPU Timers </h1>
//!
//! This example configures CPU Timer0, 1, and 2 and increments
//! a counter each time the timer asserts an interrupt.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - Timer0.InterruptCount
//! - Timer1.InterruptCount
//! - Timer2.InterruptCount
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
// 1. Updated file name to timer_ex1_tmrs.c and title to CPU Timers Example.
// 2. Updated interrupt handling to use NVIC functions.
// 3. Renamed ISR functions to match NVIC naming conventions.
//
//###########################################################################

//
// Included Files
//
#include "g32r501_device.h"
#include "g32r501_examples.h"

//
// Function Prototypes
//
void INT_TMR0_IRQHandler(void);
void INT_TMR1_IRQHandler(void);
void INT_TMR2_IRQHandler(void);

//
// Main
//
void example_main(void)
{
    //
    // Initialize device clock and peripherals
    //
    InitSysCtrl();

    //
    // Initialize GPIO
    //
    InitGpio();
    GPIO_SetupPinMux(31U, GPIO_MUX_CPU0, 0);
    GPIO_SetupPinOptions(31U, GPIO_OUTPUT, GPIO_PUSHPULL);

    //
    // Disable CPU interrupts
    //
    DINT;

    //
    //Initialize the NVIC control registers to their default state.
    //The default state is all NVIC interrupts disabled and flags
    //are cleared.
    //
    Interrupt_initModule();

    //
    //Initialize the NVIC vector table with pointers to the shell Interrupt
    //Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Initialize the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR)
    //

    Interrupt_register(INT_TMR0, INT_TMR0_IRQHandler);
    Interrupt_register(INT_TMR1, INT_TMR1_IRQHandler);
    Interrupt_register(INT_TMR2, INT_TMR2_IRQHandler);

    Interrupt_enable(INT_TMR0);
    Interrupt_enable(INT_TMR1);
    Interrupt_enable(INT_TMR2);

    //
    // Initialize the Device Peripheral. For this example, only initialize the
    // Cpu Timers.
    //
    InitTimers();

    //
    // Configure CPU-Timer 0, 1, and 2 to interrupt every second:
    // 100MHz CPU Freq, 1 second Period (in uSeconds)
    //
    ConfigTimer(&Timer0, 100, 1000000);
    ConfigTimer(&Timer1, 100, 1000000);
    ConfigTimer(&Timer2, 100, 1000000);

    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    Interrupt_setPriority(INT_TMR0,2,0);
    Interrupt_setPriority(INT_TMR1,1,0);
    Interrupt_setPriority(INT_TMR2,0,0);

    //
    // To ensure precise timing, use write-only instructions to write to the
    // entire register. Therefore, if any of the configuration bits are changed
    // in ConfigCpuTimer and InitCpuTimers, the below settings must also be
    // be updated.
    //
    Timer0Regs.TCR.all = 0x4000;
    Timer1Regs.TCR.all = 0x4000;
    Timer2Regs.TCR.all = 0x4000;

    //
    // Enable CPU int1 which is connected to CPU-Timer 0, CPU int13
    // which is connected to CPU-Timer 1, and CPU int 14, which is connected
    // to CPU-Timer 2
    //

    Interrupt_enable(INT_TMR0);
    Interrupt_enable(INT_TMR1);
    Interrupt_enable(INT_TMR2);


    //
    // Enable global Interrupts and higher priority real-time debug events
    //
    EINT;
    ERTM;

    //
    // IDLE loop. Just sit and loop forever (optional).
    //
    while(1)
    {

    }
}

//
// cpuTimer0ISR - CPU Timer0 ISR with interrupt counter
//
void INT_TMR0_IRQHandler(void)
{
    Timer0.InterruptCount++;
}

//
// cpuTimer1ISR - CPU Timer1 ISR with interrupt counter
//
void INT_TMR1_IRQHandler(void)
{
    //
    // The CPU acknowledges the interrupt
    //
    Timer1.InterruptCount++;
}

//
// cpuTimer2ISR CPU Timer2 ISR with interrupt counter
//
void INT_TMR2_IRQHandler(void)
{
    //
    // The CPU acknowledges the interrupt
    //
    Timer2.InterruptCount++;
}

//
// End of file
//
