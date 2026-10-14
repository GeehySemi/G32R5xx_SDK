//#############################################################################
//
// FILE:    interrupt_ex5_hw_prioritization.c
//
// TITLE:   CPU Timer Interrupt Hardware Prioritization
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1> CPU Timer Interrupt Hardware Prioritization </h1>
//!
//! This example demonstrates the hardware prioritization of interrupts
//! through CPU Timer Interrupts.
//!
//! This example configures CPU Timer0, 1, and 2 priority with timer 2 priority
//! being highest and timer 0 being lowest and prints a trace for the order of
//! execution.
//!
//! For most applications, the default prioritizing of the interrupts is
//! sufficient. For applications that need custom prioritizing, this example
//! illustrates how this can be done.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - traceISR - The order in which ISRs are executed.
//!
//
//#############################################################################
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
//
// You may not use this file except in compliance with the
// GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
//
// The program is only for reference, which is distributed in the hope
// that it will be useful and instructional for customers to develop
// their software. Unless required by applicable law or agreed to in
// writing, the program is distributed on an "AS IS" BASIS, WITHOUT
// ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
// See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
// and limitations under the License.
// $
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define TRACE_SIZE  51U

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
void cpuTimer0ISR(void);
void cpuTimer1ISR(void);
void cpuTimer2ISR(void);
void initCPUTimers(void);
void configCPUTimer(uint32_t, float, float);

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
    // Initializes NVIC and clears NVIC registers. Disables CPU interrupts.
    //
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
    // ISRs for each CPU Timer interrupt
    //
    Interrupt_register(INT_TMR0, &cpuTimer0ISR);
    Interrupt_register(INT_TMR1, &cpuTimer1ISR);
    Interrupt_register(INT_TMR2, &cpuTimer2ISR);

    //
    // Reset the ISR trace
    //
    for(i = 0; i < TRACE_SIZE; i++)
    {
       traceISR[i] = 0;
    }

    //
    // Set the priority group to indicate the PREEMPT and SUB priortiy bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    //
    // Configures the PREEMPT and SUB priority
    //
    Interrupt_setPriority(INT_TMR0, 2, 0);
    Interrupt_setPriority(INT_TMR1, 1, 0);
    Interrupt_setPriority(INT_TMR2, 0, 0);

    //
    // Enables CPU int38, int13, and int14 which are connected to CPU-Timer 0,
    // CPU-Timer 1, and CPU-Timer 2 respectively.
    //
    Interrupt_enable(INT_TMR0);
    Interrupt_enable(INT_TMR1);
    Interrupt_enable(INT_TMR2);

    //
    // Force CPU-Timer 0 to trigger interrupt
    //
    Interrupt_setPending(INT_TMR0);

    //
    // Enable Global Interrupt and realtime interrupt
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
// cpuTimer0ISR - Counter for CpuTimer0
//
void
cpuTimer0ISR(void)
{
    //
    // Insert ISR code here
    //
    ESTOP0;
    cpuTimer0IntCount++;

    //
    // Add ISR to Trace
    //
    traceISR[traceISRIndex % TRACE_SIZE] = 0x1017;
    traceISRIndex++;

    //
    // Force CPU-Timer 1 to trigger interrupt
    //
    Interrupt_setPending(INT_TMR1);
    DEVICE_DELAY_US(100000);

    //
    // Add ISR to Trace
    //
    traceISR[traceISRIndex % TRACE_SIZE] = 0x0017;
    traceISRIndex++;
}

//
// cpuTimer1ISR - Counter for CpuTimer1
//
void
cpuTimer1ISR(void)
{
    //
    // Insert ISR code here
    //
    ESTOP0;
    cpuTimer1IntCount++;

    //
    //  Add ISR to Trace
    //
    traceISR[traceISRIndex % TRACE_SIZE] = 0x10D0;
    traceISRIndex++;

    //
    // Force CPU-Timer 2 to trigger interrupt
    //
    Interrupt_setPending(INT_TMR2);
    DEVICE_DELAY_US(100000);

    //
    // Add ISR to Trace
    //
    traceISR[traceISRIndex % TRACE_SIZE] = 0x00D0;
    traceISRIndex++;
}

//
// cpuTimer2ISR - Counter for CpuTimer2
//
void
cpuTimer2ISR(void)
{
    //
    // Insert ISR code here
    //
    ESTOP0;
    cpuTimer2IntCount++;

    //
    // Add ISR to Trace
    //
    traceISR[traceISRIndex % TRACE_SIZE] = 0x10E0;
    traceISRIndex++;

    //
    // Force CPUTimer 0 to trigger interrupt
    //
    Interrupt_setPending(INT_TMR0);
    DEVICE_DELAY_US(100000);

    traceISR[traceISRIndex % TRACE_SIZE] = 0x00E0;
    traceISRIndex++;
}

//
// End of File
//
