//#############################################################################
//
// FILE:    adc_ex10_multiple_soc_pwm.c
//
// TITLE:   ADC PWM Triggering Multiple SOC
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1>ADC PWM Triggering Multiple SOC</h1>
//!
//! This example sets up PWM1 to periodically trigger a set of conversions on
//! ADCA and ADCC. This example demonstrates multiple ADCs working together
//! to process of a batch of conversions using the available parallelism
//! across multiple ADCs.
//!
//! ADCA Interrupt ISRs are used to read results of both ADCA and ADCC.
//!
//! \b External \b Connections \n
//!  - A0, A1, A3 and C2, C3, C4 pins should be connected to signals to be
//!    converted.
//!
//! \b Watch \b Variables \n
//! - \b adcAResult0 - Digital representation of the voltage on pin A0
//! - \b adcAResult1 - Digital representation of the voltage on pin A1
//! - \b adcAResult2 - Digital representation of the voltage on pin A3
//! - \b adcCResult0 - Digital representation of the voltage on pin C2
//! - \b adcCResult1 - Digital representation of the voltage on pin C3
//! - \b adcCResult2 - Digital representation of the voltage on pin C4
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
// Globals
//
uint16_t adcAResult0;
uint16_t adcAResult1;
uint16_t adcAResult2;
uint16_t adcCResult0;
uint16_t adcCResult1;
uint16_t adcCResult2;

//
// Function Prototypes
//
void initPWM();
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
    // Globally disable interrupts and clear all NVIC enable/pending bits
    //
    Interrupt_initModule();

    //
    // Initialize RAM vector table and set VTOR; unregistered IRQs use
    // Interrupt_defaultHandler until Interrupt_register() is called
    //
    Interrupt_initVectorTable();

    //
    // Set up the ADCA and ADCC and initialize the ADC SOC.
    // ADC Resolution - 12-bit, signal mode - single ended
    // ADCA SOC0, SOC1, SOC2 are configured to convert A0,
    // A1 and A3 channels with PWM1SOCA as SOC trigger.
    // ADCC SOC0, SOC1, SOC2 are configured to convert C2,
    // C3, C4 channels with PWM1SOCA as trigger
    //
    Board_init();
    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_myADC0_1, &INT_ADCA1_IRQHandler);
    //
    // Set the priority group to indicate the PREEMPT and SUB priortiy bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);
    //
    // Set the global and group priority to allow CPU interrupts
    // with higher priority
    //
    Interrupt_setPriority(INT_myADC0_1, 2, 0);
    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_myADC0_1);


    //
    // Configure PWM1 ADC SOCA trigger
    //
    initPWM();

    //
    // Enable ADC interrupt
    //
    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_ADCA1);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Start PWM1, enabling SOCA and putting the counter in up-count mode
    //
    PWM_enableADCTrigger(PWM1_BASE, PWM_SOC_A);
    PWM_setTimeBaseCounterMode(PWM1_BASE, PWM_COUNTER_MODE_UP);

    //
    // Take conversions indefinitely in loop
    //
    do
    {
        //
        // Wait while PWM causes ADC conversions.
        // ADCA1 ISR processes each new set of conversions.
        //
    }
    while(1);
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
    // At default eval clocks (TBCLK = DEVICE_AHBCLK_FREQ = 200 MHz, prescaler /1),
    // this gives 100 kHz SOC sampling. Rate scales with SYSCLK or PWM prescalers.
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
// ADC A Interrupt 1 ISR
//
void INT_ADCA1_IRQHandler(void)
{
    //
    // Store results
    //
    adcAResult0 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
    adcAResult1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1);
    adcAResult2 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER2);
    adcCResult0 = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER0);
    adcCResult1 = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER1);
    adcCResult2 = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER2);

    //
    // Clear the interrupt flag
    //
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

    //
    // Check if overflow has occurred
    //
    if(true == ADC_getInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
    }
}

//
// End of file
//
