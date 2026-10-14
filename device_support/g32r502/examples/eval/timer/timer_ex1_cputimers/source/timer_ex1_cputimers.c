//#############################################################################
//
// FILE:    timer_ex1_cputimers.c
//
// TITLE:   CPU Timers Example
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup bitfield_example_list
//! <h1>CPU Timers (timer_ex1_cputimers)</h1>
//!
//! Configures CPU Timer0, 1, and 2 at 200 MHz SYSCLK with the same 1 s period.
//! Timer2 has the highest NVIC preempt priority, then Timer1, then Timer0.
//! Each ISR increments \b Timerx.InterruptCount.
//!
//! \b Pass \b criteria \n
//!  - All three \b InterruptCount values increment about once per second. \n
//!  - When interrupts coincide, higher-priority Timer2 ISR runs before Timer1/0.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - \b Timer0.InterruptCount \n
//!  - \b Timer1.InterruptCount \n
//!  - \b Timer2.InterruptCount
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
// 1. Updated file name to timer_ex1_tmrs.c and title to CPU Timers Example.
// 2. Updated interrupt handling to use NVIC functions.
// 3. Renamed ISR functions to match NVIC naming conventions.
// 4. Same 1 s period at 200 MHz SYSCLK; NVIC priority Timer2 > Timer1 > Timer0.
//
//###########################################################################

//
// Included Files
//
#include "g32r502_device.h"
#include "g32r502_examples.h"

//
// CPU timer frequency for ConfigTimer() (MHz, matches CPU_RATE / SYSCLK)
//
#define CPU_TIMER_FREQ_MHZ      (CPU_RATE / 1000000.0f)

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
    // Register timer ISRs
    //
    Interrupt_register(INT_TMR0, INT_TMR0_IRQHandler);
    Interrupt_register(INT_TMR1, INT_TMR1_IRQHandler);
    Interrupt_register(INT_TMR2, INT_TMR2_IRQHandler);

    //
    // Initialize the device peripheral. For this example, only initialize the
    // CPU timers.
    //
    InitTimers();

    //
    // Configure CPU-Timer 0, 1, and 2 to interrupt every second:
    // 200 MHz CPU freq, 1 second period (in uSeconds)
    //
    ConfigTimer(&Timer0, CPU_TIMER_FREQ_MHZ, 1000000);
    ConfigTimer(&Timer1, CPU_TIMER_FREQ_MHZ, 1000000);
    ConfigTimer(&Timer2, CPU_TIMER_FREQ_MHZ, 1000000);

    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);
    Interrupt_setPriority(INT_TMR0, 2, 0);
    Interrupt_setPriority(INT_TMR1, 1, 0);
    Interrupt_setPriority(INT_TMR2, 0, 0);

    //
    // To ensure precise timing, use write-only instructions to write to the
    // entire register. Therefore, if any of the configuration bits are changed
    // in ConfigTimer and InitTimers, the below settings must also be updated.
    //
    Timer0Regs.TCR.all = 0x4000;
    Timer1Regs.TCR.all = 0x4000;
    Timer2Regs.TCR.all = 0x4000;

    //
    // Enable CPU int1 which is connected to CPU-Timer 0, CPU int13
    // which is connected to CPU-Timer 1, and CPU int14, which is connected
    // to CPU-Timer 2
    //
    Interrupt_enable(INT_TMR0);
    Interrupt_enable(INT_TMR1);
    Interrupt_enable(INT_TMR2);

    //
    // Enable global interrupts and higher priority real-time debug events
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
// INT_TMR0_IRQHandler - CPU Timer0 ISR with interrupt counter
//
void INT_TMR0_IRQHandler(void)
{
    Timer0.InterruptCount++;
}

//
// INT_TMR1_IRQHandler - CPU Timer1 ISR with interrupt counter
//
void INT_TMR1_IRQHandler(void)
{
    Timer1.InterruptCount++;
}

//
// INT_TMR2_IRQHandler - CPU Timer2 ISR with interrupt counter
//
void INT_TMR2_IRQHandler(void)
{
    Timer2.InterruptCount++;
}

//
// End of file
//
