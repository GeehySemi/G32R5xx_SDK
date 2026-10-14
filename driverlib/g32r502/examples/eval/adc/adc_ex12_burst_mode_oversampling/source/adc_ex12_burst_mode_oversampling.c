//#############################################################################
//
// FILE:    adc_ex12_burst_mode_oversampling.c
//
// TITLE:   ADC burst mode oversampling example
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1>ADC Burst Mode Oversampling</h1>
//!
//! This example is an ADC oversampling example implemented with software. The
//! ADC SOCs are configured in burst mode, triggered by the PWM SOC A event
//! trigger. All sixteen SOCs convert pin A1; the ISR accumulates results
//! according to Oversampling_Amount.
//!
//! \b External \b Connections \n
//!  - A1
//!
//! \b Watch \b Variables \n
//! - \b lv_results - Array of digital values measured on pin A1 (oversampling
//!                 is configured by Oversampling_Amount)
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
// Macros and Enumerations
//
#define DO_TOGGLE 0
#define RESULTS_SIZE 8192U

typedef enum
{
    Baseline = 0,           //!< No oversampling
    X2_Oversampling = 1,    //!< 2X oversampling
    X4_Oversampling = 2,    //!< 4X oversampling
    X8_Oversampling = 3,    //!< 8X oversampling
    X16_Oversampling = 4,   //!< 16X oversampling
} Oversampling_Amount;

//
// Global Variables
//
uint16_t acc;
uint16_t numBins = RESULTS_SIZE;
volatile uint16_t nloops = 0;
static uint16_t resultsBuffer[RESULTS_SIZE];
volatile uint16_t *lv_results;
Oversampling_Amount ovrsmplAmt = Baseline;

//
// Functions
//
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
    // Set up ADCs:
    // Signal Mode           : single-ended
    // Conversion Resolution : 12-bit;
    //
    // Burst mode configuration:
    // 1 burst of 16 conversions (SOC0 - SOC15) with equal priority
    //
    // Burst mode trigger is PWM1 SOCA. All SOCs convert channel A1.
    //
    Board_init();

    //
    // Results buffer (TI gold uses a fixed RAM address; use local array here)
    //
    lv_results = resultsBuffer;

    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_myADC0_1, &INT_ADCA1_IRQHandler);
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);
    Interrupt_setPriority(INT_myADC0_1, 2, 0);
    Interrupt_enable(INT_myADC0_1);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(1)
    {
    }
}

//
// INT_ADCA1_IRQHandler - ADC A Interrupt Burst Mode ISR
// Interrupt performs oversampling calculation based on oversampling factor
//
void INT_ADCA1_IRQHandler(void)
{
    //
    // Clear the interrupt flag
    //
    ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);

#if(DO_TOGGLE == 1)
    GPIO_togglePin(myGPIO0);
#endif

    //
    // Accumulate SOC results (store only 1 value per burst)
    //
    if(ovrsmplAmt == Baseline)
    {
        lv_results[nloops++] = ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER0);
    }
    else if(ovrsmplAmt == X2_Oversampling)
    {
        lv_results[nloops++] =
            (ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER0) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER1));
    }
    else if(ovrsmplAmt == X4_Oversampling)
    {
        lv_results[nloops++] =
            (ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER0) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER1) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER2) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER3));
    }
    else if(ovrsmplAmt == X8_Oversampling)
    {
        lv_results[nloops++] =
            (ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER0) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER1) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER2) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER3) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER4) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER5) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER6) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER7));
    }
    else if(ovrsmplAmt == X16_Oversampling)
    {
        acc =
            (ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER0) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER1) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER2) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER3) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER4) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER5) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER6) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER7) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER8) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER9) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER10) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER11) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER12) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER13) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER14) +
             ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER15));
        lv_results[nloops] = acc;
        nloops++;
    }

    //
    // Check if overflow has occurred
    //
    if(true == ADC_getInterruptOverflowStatus(myADC0_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(myADC0_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);
    }

    //
    // Check if all results are stored
    //
    if(nloops >= numBins)
    {
        ADC_disableInterrupt(myADC0_BASE, ADC_INT_NUMBER1);
        ESTOP0;
    }
}

//
// End of file
//
