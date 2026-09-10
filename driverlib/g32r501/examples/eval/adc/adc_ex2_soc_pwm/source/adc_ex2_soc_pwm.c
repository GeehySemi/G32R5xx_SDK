//#############################################################################
//
// FILE:    adc_ex2_soc_pwm.c
//
// TITLE:   ADC PWM Triggering
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1>ADC PWM Triggering</h1>
//!
//! This example sets up PWM1 to periodically trigger a conversion on ADCA.
//!
//! \b External \b Connections \n
//!  - A0 should be connected to a signal to convert
//!
//! \b Watch \b Variables \n
//! - \b myADC0Results - A sequence of analog-to-digital conversion samples from
//!   pin A0. The time between samples is determined based on the period
//!   of the PWM timer.
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
// 1. Modify some comments, macros, function names, and function contents.
//
//###########################################################################


//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Defines
//
#define RESULTS_BUFFER_SIZE     256

//
// Globals
//
static volatile uint16_t myADC0Results[RESULTS_BUFFER_SIZE];   // Buffer for results
static volatile uint16_t index;                                // Index into result buffer
static volatile uint16_t bufferFull;                           // Flag to indicate buffer is full

//
// Function Prototypes
//
void initPWM(void);

void INT_ADCA1_IRQHandler(void);
//
// Main
//
void example_main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Initialize NVIC and clears NVIC registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Board Initialization
    // - Set up the ADC and initialize the SOC
    // - Enable ADC interrupt
    //
    Board_init();

    // Set up the PWM
    initPWM();

    //
    // Initialize results buffer
    //
    for(index = 0; index < RESULTS_BUFFER_SIZE; index++)
    {
        myADC0Results[index] = 0;
    }

    index = 0;
    bufferFull = 0;

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop indefinitely
    //
    while(1)
    {
        //
        // Start PWM1, enabling SOCA and putting the counter in up-count mode
        //
        PWM_enableADCTrigger(PWM1_BASE, PWM_SOC_A);
        PWM_setTimeBaseCounterMode(PWM1_BASE, PWM_COUNTER_MODE_UP);

        //
        // Wait while PWM1 causes ADC conversions which then cause interrupts.
        // When the results buffer is filled, the bufferFull flag will be set.
        //
        while(bufferFull == 0)
        {
        }
        bufferFull = 0;     // Clear the buffer full flag

        //
        // Stop PWM1, disabling SOCA and freezing the counter
        //
        PWM_disableADCTrigger(PWM1_BASE, PWM_SOC_A);
        PWM_setTimeBaseCounterMode(PWM1_BASE, PWM_COUNTER_MODE_STOP_FREEZE);

        //
        // Software breakpoint. At this point, conversion results are stored in
        // myADC0Results.
        //
        // Hit run again to get updated conversions.
        //
        ESTOP0;
    }
}

//
// Function to configure PWM1 to generate the SOC.
//
void initPWM(void)
{
    //
    // Disable SOCA
    //
    PWM_disableADCTrigger(PWM1_BASE, PWM_SOC_A);

    //
    // Configure the SOC to occur on the first up-count event
    //
    PWM_setADCTriggerSource(PWM1_BASE, PWM_SOC_A, PWM_SOC_TBCTR_U_CMPA);
    PWM_setADCTriggerEventPrescale(PWM1_BASE, PWM_SOC_A, 1);

    //
    // Set the compare A value to 1000 and the period to 1999
    // Assuming PWM clock is 100MHz, this would give 50kHz sampling
    // 50MHz PWM clock would give 25kHz sampling, etc.
    // The sample rate can also be modulated by changing the PWM period
    // directly (ensure that the compare A value is less than the period).
    //
    PWM_setCounterCompareValue(PWM1_BASE, PWM_COUNTER_COMPARE_A, 1000);
    PWM_setTimeBasePeriod(PWM1_BASE, 1999);

    //
    // Set the local PWM module clock divider to /1
    //
    PWM_setClockPrescaler(PWM1_BASE,
                           PWM_CLOCK_DIVIDER_1,
                           PWM_HSCLOCK_DIVIDER_1);

    //
    // Freeze the counter
    //
    PWM_setTimeBaseCounterMode(PWM1_BASE, PWM_COUNTER_MODE_STOP_FREEZE);
}

//
// adcA1ISR - ADC A Interrupt 1 ISR
//
void INT_ADCA1_IRQHandler(void)
{
    //
    // Add the latest result to the buffer
    //
    myADC0Results[index++] = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);

    //
    // Set the bufferFull flag if the buffer is full
    //
    if(RESULTS_BUFFER_SIZE <= index)
    {
        index = 0;
        bufferFull = 1;
    }

    //
    // Clear the interrupt flag
    //
    ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);

    //
    // Check if overflow has occurred
    //
    if(true == ADC_getInterruptOverflowStatus(myADC0_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(myADC0_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);
    }
}
