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
//! \addtogroup driver_example_list
//! <h1> CPU Timers </h1>
//!
//! This example configures CPU Timer0, 1, and 2 and increments
//! a counter each time the timer asserts an interrupt.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - cpuTimer0IntCount
//! - cpuTimer1IntCount
//! - cpuTimer2IntCount
//!
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
// 1. Modified some function and macro definition and variable names.
// 2. Updated interrupt handling to use NVIC functions.
//
//###########################################################################

#include "driverlib.h"
#include "device.h"

//
// Globals
//
uint16_t cpuTimer0IntCount;
uint16_t cpuTimer1IntCount;
uint16_t cpuTimer2IntCount;

//
// Function Prototypes
//
void INT_TMR0_IRQHandler(void);
void INT_TMR1_IRQHandler(void);
void INT_TMR2_IRQHandler(void);
void initCPUTimers(void);
void configCPUTimer(uint32_t, float, float);

//
// Main
//
void example_main(void)
{
    //
    // Initializes device clock and peripherals
    //
    Device_init();

    //
    // Initializes NVIC and clears NVIC registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initializes the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // ISRs for each CPU Timer interrupt
    //
    Interrupt_register(INT_TMR0, &INT_TMR0_IRQHandler);
    Interrupt_register(INT_TMR1, &INT_TMR1_IRQHandler);
    Interrupt_register(INT_TMR2, &INT_TMR2_IRQHandler);

    //
    // Initializes the Device Peripheral. For this example, only initialize the
    // Cpu Timers.
    //
    initCPUTimers();

    //
    // Configure CPU-Timer 0, 1, and 2 to interrupt every 1, 2, 4 seconds:
    // 1, 2, 4 Period respectively (in uSeconds)
    //
    configCPUTimer(TMR0_BASE, DEVICE_SYSCLK_FREQ, 1000000);
    configCPUTimer(TMR1_BASE, DEVICE_SYSCLK_FREQ, 2000000);
    configCPUTimer(TMR2_BASE, DEVICE_SYSCLK_FREQ, 4000000);

    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    Interrupt_setPriority(INT_TMR0,0,0);
    Interrupt_setPriority(INT_TMR1,1,0);
    Interrupt_setPriority(INT_TMR2,2,0);

    //
    // To ensure precise timing, use write-only instructions to write to the
    // entire register. Therefore, if any of the configuration bits are changed
    // in configCPUTimer and initCPUTimers, the below settings must also
    // be updated.
    //
    TMR_enableInterrupt(TMR0_BASE);
    TMR_enableInterrupt(TMR1_BASE);
    TMR_enableInterrupt(TMR2_BASE);

    //
    // Enables CPU int1, int13, and int14 which are connected to CPU-Timer 0,
    // CPU-Timer 1, and CPU-Timer 2 respectively.
    // Enable TINT0 in the NVIC: Group 1 interrupt 7
    //
    Interrupt_enable(INT_TMR0);
    Interrupt_enable(INT_TMR1);
    Interrupt_enable(INT_TMR2);

    //
    // Starts CPU-Timer 0, CPU-Timer 1, and CPU-Timer 2.
    //
    TMR_startTimer(TMR0_BASE);
    TMR_startTimer(TMR1_BASE);
    TMR_startTimer(TMR2_BASE);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // IDLE loop. Just sit and loop forever (optional)
    //
    while(1)
    {
    }
}

//
// initCPUTimers - This function initializes all three CPU timers
// to a known state.
//
void initCPUTimers(void)
{
    //
    // Initialize timer period to maximum
    //
    TMR_setPeriod(TMR0_BASE, 0xFFFFFFFF);
    TMR_setPeriod(TMR1_BASE, 0xFFFFFFFF);
    TMR_setPeriod(TMR2_BASE, 0xFFFFFFFF);

    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    TMR_setPreScaler(TMR0_BASE, 0);
    TMR_setPreScaler(TMR1_BASE, 0);
    TMR_setPreScaler(TMR2_BASE, 0);

    //
    // Make sure timer is stopped
    //
    TMR_stopTimer(TMR0_BASE);
    TMR_stopTimer(TMR1_BASE);
    TMR_stopTimer(TMR2_BASE);

    //
    // Reload all counter register with period value
    //
    TMR_reloadTimerCounter(TMR0_BASE);
    TMR_reloadTimerCounter(TMR1_BASE);
    TMR_reloadTimerCounter(TMR2_BASE);

    //
    // Reset interrupt counter
    //
    cpuTimer0IntCount = 0;
    cpuTimer1IntCount = 0;
    cpuTimer2IntCount = 0;
}

//
// configCPUTimer - This function initializes the selected timer to the
// period specified by the "freq" and "period" parameters. The "freq" is
// entered as Hz and the period in uSeconds. The timer is held in the stopped
// state after configuration.
//
void configCPUTimer(uint32_t cpuTimer, float freq, float period)
{
    uint32_t temp;

    //
    // Initialize timer period:
    //
    temp = (uint32_t)((freq / 1000000) * period);
    TMR_setPeriod(cpuTimer, temp);

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    TMR_setPreScaler(cpuTimer, 0);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run enabled, and interrupt enabled.
    //
    TMR_stopTimer(cpuTimer);
    TMR_reloadTimerCounter(cpuTimer);
    TMR_setEmulationMode(cpuTimer, TMR_EMULATIONMODE_RUNFREE);
    TMR_enableInterrupt(cpuTimer);

    //
    // Resets interrupt counters for the three cpuTimers
    //
    if (cpuTimer == TMR0_BASE)
    {
        cpuTimer0IntCount = 0;
    }
    else if(cpuTimer == TMR1_BASE)
    {
        cpuTimer1IntCount = 0;
    }
    else if(cpuTimer == TMR2_BASE)
    {
        cpuTimer2IntCount = 0;
    }
}

//
// cpuTimer0ISR - Counter for CpuTimer0
//
void INT_TMR0_IRQHandler(void)
{
    cpuTimer0IntCount++;
}

//
// cpuTimer1ISR - Counter for CpuTimer1
//
void INT_TMR1_IRQHandler(void)
{
    //
    // The CPU acknowledges the interrupt.
    //
    cpuTimer1IntCount++;
}

//
// cpuTimer2ISR - Counter for CpuTimer2
//
void INT_TMR2_IRQHandler(void)
{
    //
    // The CPU acknowledges the interrupt.
    //
    cpuTimer2IntCount++;
}

//
// End of File
//
