//#############################################################################
//
// FILE:    qep_ex1_freq_cal.c
//
// TITLE:   Frequency Measurement Using QEP
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1>Frequency Measurement Using QEP</h1>
//!
//! This example will calculate the frequency of an input signal using the QEP
//! module.  PWM1A is configured to generate this input signal with a
//! frequency of 5 kHz. It will interrupt once every period and call the
//! frequency calculation function. This example uses the Fix32math library to
//! simplify high-precision calculations.
//!
//! In addition to the main example file, the following files must be included
//! in this project:
//! - \b qep_ex1_calculation.c - contains frequency calculation function
//! - \b qep_ex1_calculation.h - includes initialization values for frequency
//!                               structure
//!
//! The configuration for this example is as follows
//! - Maximum frequency is configured to 10KHz (baseFreq)
//! - Minimum frequency is assumed at 50Hz for capture pre-scalar selection
//!
//! \b SPEED_FR: High Frequency Measurement is obtained by counting the
//! external input pulses for 10ms (unit timer set to 100Hz).
//! \f[ SPEED\_FR = \frac{Count\ Delta}{10ms} \f]
//!
//! \b SPEED_PR: Low Frequency Measurement is obtained by measuring time
//! period of input edges. Time measurement is averaged over 64 edges for
//! better results and the capture unit performs the time measurement using
//! pre-scaled AHBCLK.
//!
//! Note that the pre-scaler for capture unit clock is selected such that the
//! capture timer does not overflow at the required minimum frequency. This
//! example runs indefinitely until the user stops it.
//!
//! For more information about the frequency calculation see the comments at
//! the beginning of qep_ex1_calculation.c.
//!
//! \b External \b Connections for G32R502 EVAL\n
//! - Connect GPIO20/QEP1A to GPIO0/PWM1A
//!
//! \b Watch \b Variables \n
//! - \b freq.freqHzFR - Frequency measurement using position counter/unit
//!   time out
//! - \b freq.freqHzPR - Frequency measurement using capture unit
//! - \b pass - Set to 1 when measured frequency is within 50 Hz of PWM_CLK
//! - \b fail - Set to 1 when measured frequency is outside tolerance
//!
//
//#############################################################################
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
// 1. Modified some function and macro definition and variable names.
// 2. Updated interrupt handling to use NVIC functions.
// 3. External Connections: GPIO20/QEP1A to GPIO0/PWM1A for G32R502 EVAL.
// 4. Restore pass/fail/count auto-check in PWM ISR.
// 5. Use DEVICE_AHBCLK_FREQ for PWM PRD and QEP frequency scalers.
//
//###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "Fix32mathLib.h"
#include "qep_ex1_calculation.h"
#include "board.h"


//
// Defines
//
#define TB_CLK    DEVICE_AHBCLK_FREQ        // PWM TBCLK on AHB
#define PWM_CLK   5000                      // We want to output at 5 kHz
#define PRD_VAL   (TB_CLK / (PWM_CLK * 2))  // Period for up-down count mode

// Base/max frequency is 10 kHz
#define BASE_FREQ       10000
// See Equation 5 in qep_ex1_calculation.c
#define FREQ_SCALER_PR  (((DEVICE_AHBCLK_FREQ / 128) * 8) / (2 * BASE_FREQ))
// See Equation 2 in qep_ex1_calculation.c
// Unit timer period = DEVICE_AHBCLK_FREQ / 100 in board.c (10 ms, 100 Hz timeout)
#define FREQ_SCALER_FR  ((BASE_FREQ * 2) / 100)

//
// Function Prototypes
//
void initPWM(void);
void pwmISR(void);

//
// Globals
//
FreqCal_Object freq =
{
    (uint32_t) FREQ_SCALER_PR,  // freqScalerPR
    (uint32_t) FREQ_SCALER_FR,  // freqScalerFR
    (uint32_t) BASE_FREQ,       // baseFreq
    0, 0, 0, 0, 0    // Initialize outputs to zero
};
uint32_t count = 0;   // Counter to check measurement gets saturated
uint32_t pass = 0, fail = 0; // Pass or fail indicator

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
    // Set the priority group to indicate the PREEMPT and SUB priority bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    //
    // Set the global and group interrupt priority to allow CPU interrupts
    // with higher priority
    Interrupt_setPriority(INT_PWM1, 0, 0);

    //
    // Board Initialization
    // Setup QEP1, configuring the unit timer and quadrature capture units
    //
    Board_init();

    //
    // Initialize GPIOs for use as PWM1A and QEP1A
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_PWM1A);
    GPIO_setDrivingCapability(DEVICE_GPIO_PIN_PWM1A,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_PWM1A, GPIO_PIN_TYPE_STD);

    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_PWM1, &pwmISR);

    //
    // Setup PWM1 to generate a 5 kHz signal to be an input to the QEP
    //
    initPWM();

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_PWM1);

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
        ;
    }
}


//
// initPWM - Function to configure PWM1 to generate a 5 kHz signal.
//
void
initPWM(void)
{
    //
    // Disable the PWM time base clock before configuring the module
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Set phase shift to 0 and clear the time base counter
    //
    PWM_setPhaseShift(PWM1_BASE, 0);
    PWM_setTimeBaseCounter(PWM1_BASE, 0);

    //
    // Disable the shadow load; the load will be immediate instead
    //
    PWM_disableCounterCompareShadowLoadMode(PWM1_BASE,
                                             PWM_COUNTER_COMPARE_A);
    PWM_disableCounterCompareShadowLoadMode(PWM1_BASE,
                                             PWM_COUNTER_COMPARE_B);

    //
    // Set the compare A value to half the period value, compare B to 0
    //
    PWM_setCounterCompareValue(PWM1_BASE, PWM_COUNTER_COMPARE_A, PRD_VAL/2);
    PWM_setCounterCompareValue(PWM1_BASE, PWM_COUNTER_COMPARE_B, 0);
    //
    // Set action qualifier behavior on compare A events
    // - PWM1A --> 1 when CTR = CMPA and increasing
    // - PWM1A --> 0 when CTR = CMPA and decreasing
    //
    PWM_setActionQualifierAction(PWM1_BASE, PWM_AQ_OUTPUT_A,
                                  PWM_AQ_OUTPUT_HIGH,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    PWM_setActionQualifierAction(PWM1_BASE, PWM_AQ_OUTPUT_A,
                                  PWM_AQ_OUTPUT_LOW,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

    //
    // Configure PWM1B to be complementary to PWM1A
    //
    PWM_setDeadBandDelayPolarity(PWM1_BASE, PWM_DB_FED,
                                  PWM_DB_POLARITY_ACTIVE_LOW);
    PWM_setDeadBandDelayMode(PWM1_BASE, PWM_DB_FED, true);
    PWM_setDeadBandDelayMode(PWM1_BASE, PWM_DB_RED, true);

    //
    // Enable interrupt when the counter is equal to 0
    //
    PWM_setInterruptSource(PWM1_BASE, PWM_INT_TBCTR_ZERO);
    PWM_enableInterrupt(PWM1_BASE);

    //
    // Interrupt on first event
    //
    PWM_setInterruptEventCount(PWM1_BASE, 1);

    //
    // Set the time base clock prescaler to /1
    //
    PWM_setClockPrescaler(PWM1_BASE, PWM_CLOCK_DIVIDER_1,
                           PWM_HSCLOCK_DIVIDER_1);

    //
    // Set the period value; don't shadow the register
    //
    PWM_setPeriodLoadMode(PWM1_BASE, PWM_PERIOD_DIRECT_LOAD);
    PWM_setTimeBasePeriod(PWM1_BASE, PRD_VAL);

    //
    // Put the time base counter into up-down count mode
    //
    PWM_setTimeBaseCounterMode(PWM1_BASE, PWM_COUNTER_MODE_UP_DOWN);

    //
    // Sync the PWM time base clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

//
// PWM1 ISR- interrupts once per PWM period
//
void
pwmISR(void)
{
    //
    // Checks for events and calculates frequency.
    //
    FreqCal_calculate(&freq, &count);

    //
    // Comparing the QEP measured frequency with the PWM frequency.
    // After count becomes 3, QEP measurement gets saturated and
    // pass = 1 if measured frequency is 50 Hz more or less than input.
    //
    if(count >= 3U)
    {
        if(((freq.freqHzFR - PWM_CLK) < 50) && ((freq.freqHzFR - PWM_CLK) > -50))
        {
            pass = 1U;
            fail = 0U;
        }
        else
        {
            fail = 1U;
            pass = 0U;
        }
    }

    //
    // Clear interrupt flag and issue ACK
    //
    PWM_clearEventTriggerInterruptFlag(PWM1_BASE);
}

//
// End of File
//

