//#############################################################################
//
// FILE:    adc_ex1_soc_pwm.c
//
// TITLE:   ADC PWM Triggering
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup bitfield_example_list
//! <h1>ADC PWM Triggering</h1>
//!
//! This example sets up PWM1 to periodically trigger a conversion on ADCA.
//!
//! \b External \b Connections \n
//!  - A1 should be connected to a signal to convert
//!
//! \b Watch \b Variables \n
//! - \b adcAResults - A sequence of analog-to-digital conversion samples from
//!   pin A1. The time between samples is determined based on the period
//!   of the PWM timer.
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
// 1. Updated file name to adc_ex1_soc_pwm.c and title to ADC PWM Triggering.
// 2. Replaced ePWM references with PWM.
// 3. Updated interrupt handling to use NVIC functions.
//
//###########################################################################

//
// Included Files
//
#include "g32r501_project.h"

//
// Defines
//
#define RESULTS_BUFFER_SIZE     256

//
// Globals
//
uint16_t adcAResults[RESULTS_BUFFER_SIZE];   // Buffer for results
uint16_t Index;                              // Index into result buffer
volatile uint16_t bufferFull;                // Flag to indicate buffer is full

//
// Function Prototypes
//
void initADC(void);
void initPWM(void);
void initADCSOC(void);
void adcA1ISR(void);

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
    // Set the priority group to indicate the PREEMPT and SUB priority bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_7_6_SUB_5_0);

    //
    // Set the global and group interrupt priority to allow CPU interrupts
    // with higher priority
    Interrupt_setPriority(INT_ADCA1, 0, 0);

    //
    // Map ISR functions
    //
    WRPRT_DISABLE;
    Interrupt_register(INT_ADCA1, &adcA1ISR);
    WRPRT_ENABLE;

    //
    // Configure the ADC and power it up
    //
    initADC();

    //
    // Configure the PWM
    //
    initPWM();

    //
    // Setup the ADC for PWM triggered conversions on channel 1
    //
    initADCSOC();

    //
    // Enable NVIC interrupt
    //
    Interrupt_enable(INT_ADCA1);

    EINT;           // Enable Global interrupt INTM
    ERTM;           // Enable Global realtime interrupt DBGM

    //
    // Initialize results buffer
    //
    for(Index = 0; Index < RESULTS_BUFFER_SIZE; Index++)
    {
        adcAResults[Index] = 0;
    }

    Index = 0;
    bufferFull = 0;

    //
    // Sync PWM
    //
    WRPRT_DISABLE;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;

    //
    // Take conversions indefinitely in loop
    //
    while(1)
    {
        //
        // Start PWM
        //
        Pwm1Regs.ETSEL.bit.SOCAEN = 1;    // Enable SOCA
        Pwm1Regs.TBCTL.bit.CTRMODE = 0;   // Unfreeze, and enter up count mode

        //
        // Wait while PWM causes ADC conversions, which then cause interrupts,
        // which fill the results buffer, eventually setting the bufferFull
        // flag
        //
        while(!bufferFull)
        {
        }
        bufferFull = 0; //clear the buffer full flag

        //
        // Stop PWM
        //
        Pwm1Regs.ETSEL.bit.SOCAEN = 0;    // Disable SOCA
        Pwm1Regs.TBCTL.bit.CTRMODE = 3;   // Freeze counter

        //
        // Software breakpoint. At this point, conversion results are stored in
        // adcAResults.
        //
        // Hit run again to get updated conversions.
        //
        ESTOP0;
    }
}

//
// initADC - Function to configure and power up ADCA.
//
void initADC(void)
{
    //
    // Setup VREF as internal
    //
    SetVREF(ADC_ADCA, ADC_INTERNAL, ADC_VREF3P3);

    WRPRT_DISABLE;

    //
    // Set ADCCLK divider to /4
    //
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6;

    //
    // Set pulse positions to late
    //
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    //
    // Power up the ADC and then delay for 1 ms
    //
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    WRPRT_ENABLE;

    DELAY_US(1000);
}

//
// initPWM - Function to configure PWM1 to generate the SOC.
//
void initPWM(void)
{
    WRPRT_DISABLE;

    Pwm1Regs.ETSEL.bit.SOCAEN = 0;     // Disable SOC on A group
    Pwm1Regs.ETSEL.bit.SOCASEL = 4;    // Select SOC on up-count
    Pwm1Regs.ETPS.bit.SOCAPRD = 1;     // Generate pulse on 1st event

    Pwm1Regs.CMPA.bit.CMPA = 0x0800;   // Set compare A value to 2048 counts
    Pwm1Regs.TBPRD = 0x1000;           // Set period to 4096 counts

    Pwm1Regs.TBCTL.bit.CTRMODE = 3;    // Freeze counter

    WRPRT_ENABLE;
}

//
// initADCSOC - Function to configure ADCA's SOC0 to be triggered by PWM1.
//
void initADCSOC(void)
{
    //
    // Select the channels to convert and the end of conversion flag
    //
    WRPRT_DISABLE;

    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 1;     // SOC0 will convert pin A1
                                           // 0:A0  1:A1  2:A2  3:A3
                                           // 4:A4   5:A5   6:A6   7:A7
                                           // 8:A8   9:A9   A:A10  B:A11
                                           // C:A12  D:A13  E:A14  F:A15
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 5;   // Trigger on PWM1 SOCA

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0; // End of SOC0 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;   // Enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // Make sure INT1 flag is cleared

    WRPRT_ENABLE;
}

//
// adcA1ISR - ADC A Interrupt 1 ISR
//
void adcA1ISR(void)
{
    //
    // Add the latest result to the buffer
    // ADCRESULT0 is the result register of SOC0
    adcAResults[Index++] = AdcaResultRegs.ADCRESULT0;

    //
    // Set the bufferFull flag if the buffer is full
    //
    if(RESULTS_BUFFER_SIZE <= Index)
    {
        Index = 0;
        bufferFull = 1;
    }

    //
    // Clear the interrupt flag
    //
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    //
    // Check if overflow has occurred
    //
    if(1 == AdcaRegs.ADCINTOVF.bit.ADCINT1)
    {
        AdcaRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
        AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }
}

//
// End of File
//
