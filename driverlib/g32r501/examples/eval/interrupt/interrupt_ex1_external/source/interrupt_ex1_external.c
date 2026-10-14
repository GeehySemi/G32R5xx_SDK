//###########################################################################
//
// FILE:    interrupt_ex1_external.c
//
// TITLE:   External Interrupt test program.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1>External Interrupts (ExternalInterrupt)</h1>
//!
//! This program sets up GPIO0 as XINT1 (EXTI_LINE_4) and GPIO1 as XINT2
//! (EXTI_LINE_5).  Two other GPIO signals are used to trigger the interrupt
//! (GPIO10 triggers XINT1 and GPIO11 triggers XINT2).  The user is
//! required to externally connect these signals for the program to work
//! properly.
//!
//! XINT1 input is synced to SYSCLKOUT.
//!
//! XINT2 has a long qualification - 6 samples at 510*SYSCLKOUT each.
//!
//! GPIO16 will go high outside of the interrupts and low within the
//! interrupts. This signal can be monitored on a scope.
//!
//! Each interrupt is fired in sequence - XINT1 first and then XINT2
//!
//! \b External \b Connections \n
//! - Connect GPIO10 to GPIO0(GPIO0 will be assigned to XINT1).
//! - Connect GPIO11 to GPIO1(GPIO1 will be assigned to XINT2).
//!
//! Monitor GPIO16 with an oscilloscope. GPIO16 will be high outside of the
//! ISRs and low within each ISR.
//!
//! \b Watch \b Variables \n
//!  - xint1Count - The number of times through XINT1 interrupt
//!  - xint2Count - The number of times through XINT2 interrupt
//!  - loopCount  - The number of times through the idle loop
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
// 1. Modified some function and macro definition and variable names.
//
//###########################################################################

//
// Included Files
//
#include "device.h"
#include "driverlib.h"

//
// Defines
//

// Qualification period at 6 samples in microseconds
#define DELAY   (6.0 * 510.0 * 1000000.0 * (1.0 / DEVICE_SYSCLK_FREQ))

//
// Globals
//
volatile uint32_t xint1Count;
volatile uint32_t xint2Count;
volatile uint32_t loopCount;

//
// Function Prototypes
//
void xint1ISR(void);
void xint2ISR(void);

//
// Main
//
void example_main(void)
{
    uint32_t tempX1Count;
    uint32_t tempX2Count;

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

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    Interrupt_register(INT_XINT1, &xint1ISR);
    Interrupt_register(INT_XINT2, &xint2ISR);

    //
    // User specific code, enable interrupts:
    //
    // Clear the counters
    //
    xint1Count = 0; // Count XINT1 interrupts
    xint2Count = 0; // Count XINT2 interrupts
    loopCount = 0;  // Count times through idle loop

    //
    // Set the priority group to indicate the PREEMPT and SUB priortiy bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);
    //
    // Set the global and group priority to allow CPU interrupts
    // with higher priority
    //
    Interrupt_setPriority(INT_XINT1,1,0);
    Interrupt_setPriority(INT_XINT2,1,0);
    //
    // Enable XINT1 and XINT2 in the NVIC.
    // Enable INT1 which is connected to WAKEINT:
    //
    Interrupt_enable(INT_XINT1);
    Interrupt_enable(INT_XINT2);

    //
    // Enable Global Interrupt and real time interrupt
    //
    EINT;
    ERTM;

    //
    // GPIO10 & GPIO11 are outputs, start GPIO10 high and GPIO11 low
    //

    //
    // Load the output latch
    //
    GPIO_writePin(10, 1);
    GPIO_setDirectionMode(10, GPIO_DIR_MODE_OUT);           // output

    //
    // Load the output latch
    //
    GPIO_writePin(11, 0);
    GPIO_setDirectionMode(11, GPIO_DIR_MODE_OUT);           // output

    //
    // GPIO0 and GPIO1 are configured as inputs
    //
    GPIO_setDirectionMode(0, GPIO_DIR_MODE_IN);             // input

    //
    // XINT1 Synch to SYSCLKOUT only
    //
    GPIO_setQualificationMode(0, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(1, GPIO_DIR_MODE_IN);             // input

    //
    // XINT2 Qual using 6 samples
    //
    GPIO_setQualificationMode(1, GPIO_QUAL_6SAMPLE);

    //
    // Set qualification period for GPIO0 to GPIO7
    // Each sampling window is 510*SYSCLKOUT
    //
    GPIO_setQualificationPeriod(3, 510);

    //
    // GPIO0 is mapped to XINT1, GPIO1 is mapped to XINT2
    //
    GPIO_setInterruptPin(0, GPIO_INT_XINT1);
    GPIO_setInterruptPin(1, GPIO_INT_XINT2);

    //
    // Configure falling edge trigger for XINT1
    //
    GPIO_setInterruptType(GPIO_INT_XINT1, GPIO_INT_TYPE_FALLING_EDGE);

    //
    // Configure rising edge trigger for XINT2
    //
    GPIO_setInterruptType(GPIO_INT_XINT2, GPIO_INT_TYPE_RISING_EDGE);

    //
    // Enable XINT1 and XINT2
    //
    GPIO_enableInterrupt(GPIO_INT_XINT1);         // Enable XINT1
    GPIO_enableInterrupt(GPIO_INT_XINT2);         // Enable XINT2

    //
    // GPIO16 will go low inside each interrupt.  Monitor this on a scope
    //
    GPIO_setDirectionMode(16, GPIO_DIR_MODE_OUT);  // output


    //
    // IDLE loop:
    //
    for(;;)
    {
        tempX1Count = xint1Count;
        tempX2Count = xint2Count;

        //
        // Set GPIO16
        //
        GPIO_writePin(16, 1);

        //
        // Lower GPIO10, trigger XINT1
        //
        GPIO_clearPortPins(GPIO_PORT_A, GPIO_GPADIR_GPIO10);
        while(xint1Count == tempX1Count) {}

        //
        // Set GPIO16
        //
        GPIO_writePin(16, 1);

        //
        // Wait for Qual period
        //
        DEVICE_DELAY_US((uint32_t)DELAY);

        //
        // Raise GPIO11, trigger XINT2
        //
        GPIO_writePin(11, 1);
        while(xint2Count == tempX2Count) {}

        //
        // Check that the counts were incremented properly and get ready
        // to start over.
        //
        if((xint1Count == tempX1Count + 1) && (xint2Count == tempX2Count + 1))
        {
            loopCount++;

            //
            // Raise GPIO10
            //
            GPIO_writePin(10, 1);

            //
            // Lower GPIO11
            //
            GPIO_writePin(11, 0);
        }
        else
        {
            ESTOP0;
        }
    }
}

//
// xint1ISR - External Interrupt 1 ISR
//
void xint1ISR(void)
{
    //
    // Get External Interrupt 1 status
    //
    if(EXTI_getInterruptStatus(EXTI_CORE_CPU0, EXTI_LINE_4))
    {
        GPIO_writePin(16, 0); // GPIO16 is lowered
        xint1Count++;

        //
        // Clear external interrupt 1 status
        //
        EXTI_clearInterruptStatus(EXTI_CORE_CPU0, EXTI_LINE_4);
    }
}

//
// xint2ISR - External Interrupt 2 ISR
//
void xint2ISR(void)
{
    //
    // Get External Interrupt 2 status
    //
    if(EXTI_getInterruptStatus(EXTI_CORE_CPU0, EXTI_LINE_5))
    {
        GPIO_writePin(16, 0); // GPIO16 is lowered
        xint2Count++;

        //
        // Clear External Interrupt 2 status
        //
        EXTI_clearInterruptStatus(EXTI_CORE_CPU0, EXTI_LINE_5);
    }
}

//
// End of file
//
