//#############################################################################
//
// FILE:    interrupt_ex3_sw_prioritization.c
//
// TITLE:   CPU Timer Interrupt Software Prioritization
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1> CPU Timer Interrupt Software Prioritization </h1>
//!
//! This examples demonstrates the software prioritization of interrupts
//! through CPU Timer Interrupts. Software prioritization of interrupts is
//! achieved by enabling interrupt nesting.
//!
//! In this device, hardware priorities for CPU Timer 0, 1 and 2 are set
//! as timer 0 being highest priority and timer 2 being lowest priority.
//! This example configures CPU Timer0, 1, and 2 priority in software with
//! timer 2 priority being highest and timer 0 being lowest in software and
//! prints a trace for the order of execution.
//!
//! For most applications, the hardware prioritizing of the interrupts is
//! sufficient. For applications that need custom prioritizing, this example
//! illustrates how this can be done through software.User specific priorities
//! can be configured in sw_prioritized_isr_level.h header file.
//!
//! To enable interrupt nesting, following sequence needs to followed in ISRs.
//! <b>Step 1:</b> Set the global priority:
//! Modify the IER register to allow CPU interrupts with a higher user
//! priority to be serviced.
//! Note: at this time IER has already been saved on the stack.
//! <b>Step 2:</b> Set the group priority: (optional)
//! Modify the group interrupts with a higher user set priority to be serviced. 
//! <b>Step 3:</b> Enable interrupts:
//! <b>Step 4:</b> Run the main part of the ISR
//! <b>Step 5:</b> Disable interrupts.
//! <b>Step 6:</b> Return from ISR
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - traceISR - the order in which ISRs are executed.
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
#define TRACE_SIZE  101U

//
// Globals
//
uint16_t cpuTimer0IntCount;
uint16_t cpuTimer1IntCount;
uint16_t cpuTimer2IntCount;

//
// This array will be used as a trace to check the
// order that the interrupts were serviced
//
uint16_t  traceISR[TRACE_SIZE];

//
// Index to update an element in the trace buffer
//
uint16_t  traceISRIndex = 0;

//
// Function Prototypes
//
__interrupt void INT_TIMER0_IRQHandler(void);
__interrupt void INT_TIMER1_IRQHandler(void);
__interrupt void INT_TIMER2_IRQHandler(void);

void initTMRs(void);
void configTMR(uint32_t, float, float);

//
// Main
//
void example_main(void)
{
    uint32_t i;

    //
    // Initializes device clock and peripherals
    //
    Device_init();

    //
    // Configures the GPIO pin as a push-pull output
    //
    Device_initGPIO();

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
    Interrupt_register(INT_TIMER0, &INT_TIMER0_IRQHandler);
    Interrupt_register(INT_TIMER1, &INT_TIMER1_IRQHandler);
    Interrupt_register(INT_TIMER2, &INT_TIMER2_IRQHandler);

    //
    // Reset the ISR trace
    //
    for(i = 0; i < TRACE_SIZE; i++)
    {
       traceISR[i] = 0;
    }

    //
    // Initializes the Device Peripheral. For this example, only initialize the
    // Cpu Timers.
    //
    initTMRs();

    //
    // Configure CPU-Timer 0, 1, and 2 to interrupt every second:
    // 1 second Period (in uSeconds)
    //
    configTMR(TMR0_BASE, DEVICE_OSCSRC_FREQ, 1000000);
    configTMR(TMR1_BASE, DEVICE_OSCSRC_FREQ, 1000000);
    configTMR(TMR2_BASE, DEVICE_OSCSRC_FREQ, 1000000);

    //
    // Set the priority group to indicate the PREEMPT and SUB priortiy bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_7_6_SUB_5_0);

    //
    // Set the global and group priority to allow CPU interrupts
    // with higher priority
    //
    Interrupt_setPriority(INT_TIMER0, 2, 0);
    Interrupt_setPriority(INT_TIMER1, 1, 0);
    Interrupt_setPriority(INT_TIMER2, 0, 0);

    //
    // Enables CPU int38, int13, and int14 which are connected to CPU-Timer 0,
    // CPU-Timer 1, and CPU-Timer 2 respectively.
    //
    Interrupt_enable(INT_TIMER0);
    Interrupt_enable(INT_TIMER1);
    Interrupt_enable(INT_TIMER2);

    //
    // To ensure precise timing, use write-only instructions to write to the
    // entire register. Therefore, if any of the configuration bits are changed
    // in configTMR and initTMRs, the below settings must also
    // be updated.
    //
    TMR_enableInterrupt(TMR0_BASE);
    TMR_enableInterrupt(TMR1_BASE);
    TMR_enableInterrupt(TMR2_BASE);

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
// initTMRs - This function initializes all three CPU timers
// to a known state.
//
void
initTMRs(void)
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
// configTMR - This function initializes the selected timer to the
// period specified by the "freq" and "period" parameters. The "freq" is
// entered as Hz and the period in uSeconds. The timer is held in the stopped
// state after configuration.
//
void
configTMR(uint32_t cpuTimer, float freq, float period)
{
    uint32_t temp;

    //
    // Initialize timer period:
    //
    temp = (uint32_t)(freq / 1000000 * period);
    TMR_setPeriod(cpuTimer, temp);

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    TMR_setPreScaler(cpuTimer, 0);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    //
    TMR_stopTimer(cpuTimer);
    TMR_reloadTimerCounter(cpuTimer);
    TMR_setEmulationMode(cpuTimer,
                              TMR_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
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
__interrupt void INT_TIMER0_IRQHandler(void)
{
    //
    //  Add ISR to Trace
    //
    traceISR[traceISRIndex % TRACE_SIZE] = 0x1017;
    traceISRIndex++;

    TMR_clearOverflowFlag(TMR0_BASE);
    //
    // Insert ISR code here
    //
    cpuTimer0IntCount++;

    //
    // Disable interrupts and restore registers saved:
    //

    //
    //  Add ISR to Trace
    //
    traceISR[traceISRIndex % TRACE_SIZE] = 0x0017;
    traceISRIndex++;
}

//
// cpuTimer1ISR - Counter for CpuTimer1
//
__interrupt void INT_TIMER1_IRQHandler(void)
{
    //
    //  Add ISR to Trace
    //
    traceISR[traceISRIndex % TRACE_SIZE] = 0x10D0;
    traceISRIndex++;
    TMR_clearOverflowFlag(TMR1_BASE);

    //
    // Insert ISR code here
    //
    cpuTimer1IntCount++;

    //
    //  Add ISR to Trace
    //
    traceISR[traceISRIndex % TRACE_SIZE] = 0x00D0;
    traceISRIndex++;
}


//
// cpuTimer2ISR - Counter for CpuTimer2
//
__interrupt void INT_TIMER2_IRQHandler(void)
{
    //
    //  Add ISR to Trace
    //
    traceISR[traceISRIndex % TRACE_SIZE] = 0x10E0;
    traceISRIndex++;
    TMR_clearOverflowFlag(TMR2_BASE);

    //
    // Insert ISR code here
    //
    cpuTimer2IntCount++;

    //
    //  Add ISR to Trace
    //
    traceISR[traceISRIndex % TRACE_SIZE] = 0x00E0;
    traceISRIndex++;
}

//
// End of File
//
