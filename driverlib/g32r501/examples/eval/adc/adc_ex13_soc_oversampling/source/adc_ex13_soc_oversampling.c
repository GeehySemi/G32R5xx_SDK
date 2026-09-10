//#############################################################################
//
// FILE:    adc_ex13_soc_oversampling.c
//
// TITLE:   ADC Oversampling Using Multiple SOCs
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1>ADC SOC Oversampling </h1>
//!
//! This example sets up PWM1 to periodically trigger a set of conversions on
//! ADCA including multiple SOCs that all convert A2 to achieve oversampling on
//! A2.
//!
//! ADCA Interrupt ISRs are used to read results of ADCA.
//!
//! \b External \b Connections \n
//!  - A0, A1, A2 should be connected to signals to be converted.
//!
//! \b Watch \b Variables \n
//! - \b adcAResult0 - Digital representation of the voltage on pin A0
//! - \b adcAResult1 - Digital representation of the voltage on pin A1
//! - \b adcAResult2 - Digital representation of the voltage on pin A2
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
// Globals
//
uint16_t adcAResult0;
uint16_t adcAResult1;
uint16_t adcAResult2;

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
    // Initialize NVIC and clears NVIC registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Set up ADCs:
    // Signal Mode           : single-ended
    // Conversion Resolution : 12-bit;
    //
    // Configure SOC0-1 in round robin mode to sample A0 and A1 channel
    // respectively and SOC2-SOC5 oversamples channel A2 on PWM1SOCA
    // trigger.
    //
    // Register and enable the interrupts:
    // SOC0 and SOC1 results are read after each PWM trigger for
    // channel 0 and 1 outputs while SOC2-SOC5 results will be
    // averaged together for oversampled channel A2 result
    //
    Board_init();

    //
    // Initialize PWM
    //
    initPWM();

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
    // Store results for A0 and A1
    //
    adcAResult0 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
    adcAResult1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1);

    //
    // Average the 4 oversampled A2 results together
    //
    adcAResult2 =
        (ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER2) +
        ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER3) +
        ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER4) +
        ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER5)) >> 2;

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
