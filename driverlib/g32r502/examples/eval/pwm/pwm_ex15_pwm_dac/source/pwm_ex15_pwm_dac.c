//###########################################################################
//
// FILE:    pwm_ex15_pwm_dac.c
//
// TITLE:   PWM-DAC Path Check
//
// VERSION: 1.0.0
//
// DATE:    2026-08-07
//
//! \addtogroup driver_example_list
//! <h1>PWM-DAC Path Check</h1>
//!
//! This example drives the on-board PWM-DAC path with fixed settings:
//! - PWM4A on GPIO22 (duty for about 0.8 V DC after buffer)
//! - PWM1B on GPIO31 (duty for about 1.6 V DC after buffer)
//!
//! PWM frequency is 50 kHz (TBCLK = DEVICE_AHBCLK_FREQ).
//! After a 3.3 V buffer, DC is approximately V = 3.3 * D.
//! Duty and frequency are applied once at startup.
//!
//! \b External \b Connections \n
//! - Logic analyzer / scope: probe PWM4A on GPIO22 and PWM1B on GPIO31
//!   (MCU pins) for the 50 kHz PWM waveform.
//! - Multimeter DC: probe buffered nets GPIO22_PWM_DAC / GPIO31_PWM_DAC
//!   (after the on-board buffer) for averaged DC voltage.
//!
//! \b Watch \b Variables \n
//! - \b dutyPct_ch22 - GPIO22 / PWM4A duty percent (24, ~0.8 V)
//! - \b dutyPct_ch31 - GPIO31 / PWM1B duty percent (48, ~1.6 V)
//! - \b freqHz - PWM frequency in Hz (50000)
//!
//! \b Pass \b / \b Fail \b Indication \n
//! - PASS: J1-20 ~0.8 V DC, J3-20 ~1.6 V DC (default duty).
//! - FAIL: voltages far from target, or no PWM on MCU GPIO22 / GPIO31.
//!
//###########################################################################
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
volatile uint32_t freqHz = PWM_DAC_FREQ_HZ;
volatile uint16_t dutyPct_ch22 = PWM_DAC_DUTY_PCT_CH22;
volatile uint16_t dutyPct_ch31 = PWM_DAC_DUTY_PCT_CH31;

static void configurePwmChannel(uint32_t base, bool configA, uint16_t cmpVal);

//
// Main
//
void example_main(void)
{
    //
    // Initializes system control, device clock, and peripherals
    //
    Device_init();

    //
    // Initializes GPIO unlock and analog mode defaults
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
    // Disable TBCLKSYNC before PWM configuration
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Board Initialization (PinMux + PWM)
    //
    Board_init();

    //
    // Enable TBCLKSYNC so PWM time bases start
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enables CPU interrupts and real-time debug
    //
    EINT;
    ERTM;

    //
    // Idle loop; PWM runs from hardware
    //
    for(;;)
    {
        __asm("  NOP");
    }
}

//
// configurePwmChannel - Configure one PWM channel for PWM-DAC output.
// configA = true: CMPA / AQ output A; false: CMPB / AQ output B.
// Call only while SYSCTL_PERIPH_CLK_TBCLKSYNC is disabled.
//
static void configurePwmChannel(uint32_t base, bool configA, uint16_t cmpVal)
{
    //
    // Time-base: free-run, TBCLK undivided, direct period load, up-count
    //
    PWM_setEmulationMode(base, PWM_EMULATION_FREE_RUN);
    PWM_setClockPrescaler(base, PWM_CLOCK_DIVIDER_1, PWM_HSCLOCK_DIVIDER_1);
    PWM_setPeriodLoadMode(base, PWM_PERIOD_DIRECT_LOAD);
    PWM_setTimeBasePeriod(base, PWM_DAC_TBPRD);
    PWM_setTimeBaseCounter(base, 0U);
    PWM_disablePhaseShiftLoad(base);
    PWM_setPhaseShift(base, 0U);

    //
    // Compare shadow load on zero
    //
    PWM_setCounterCompareShadowLoadMode(base, PWM_COUNTER_COMPARE_A,
                                        PWM_COMP_LOAD_ON_CNTR_ZERO);
    PWM_setCounterCompareShadowLoadMode(base, PWM_COUNTER_COMPARE_B,
                                        PWM_COMP_LOAD_ON_CNTR_ZERO);

    if(configA)
    {
        //
        // PWM4A: high on zero, low on CMPA (up-count)
        //
        PWM_setCounterCompareValue(base, PWM_COUNTER_COMPARE_A, cmpVal);
        PWM_setActionQualifierAction(base, PWM_AQ_OUTPUT_A,
                                     PWM_AQ_OUTPUT_HIGH,
                                     PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
        PWM_setActionQualifierAction(base, PWM_AQ_OUTPUT_A,
                                     PWM_AQ_OUTPUT_NO_CHANGE,
                                     PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
        PWM_setActionQualifierAction(base, PWM_AQ_OUTPUT_A,
                                     PWM_AQ_OUTPUT_LOW,
                                     PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
        PWM_setActionQualifierAction(base, PWM_AQ_OUTPUT_A,
                                     PWM_AQ_OUTPUT_NO_CHANGE,
                                     PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
        PWM_setActionQualifierAction(base, PWM_AQ_OUTPUT_A,
                                     PWM_AQ_OUTPUT_NO_CHANGE,
                                     PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
        PWM_setActionQualifierAction(base, PWM_AQ_OUTPUT_A,
                                     PWM_AQ_OUTPUT_NO_CHANGE,
                                     PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    }
    else
    {
        //
        // PWM1B: high on zero, low on CMPB (up-count)
        //
        PWM_setCounterCompareValue(base, PWM_COUNTER_COMPARE_B, cmpVal);
        PWM_setActionQualifierAction(base, PWM_AQ_OUTPUT_B,
                                     PWM_AQ_OUTPUT_HIGH,
                                     PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
        PWM_setActionQualifierAction(base, PWM_AQ_OUTPUT_B,
                                     PWM_AQ_OUTPUT_NO_CHANGE,
                                     PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
        PWM_setActionQualifierAction(base, PWM_AQ_OUTPUT_B,
                                     PWM_AQ_OUTPUT_NO_CHANGE,
                                     PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
        PWM_setActionQualifierAction(base, PWM_AQ_OUTPUT_B,
                                     PWM_AQ_OUTPUT_NO_CHANGE,
                                     PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
        PWM_setActionQualifierAction(base, PWM_AQ_OUTPUT_B,
                                     PWM_AQ_OUTPUT_LOW,
                                     PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
        PWM_setActionQualifierAction(base, PWM_AQ_OUTPUT_B,
                                     PWM_AQ_OUTPUT_NO_CHANGE,
                                     PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    }

    //
    // Dead-band not used
    //
    PWM_setRisingEdgeDelayCountShadowLoadMode(base, PWM_RED_LOAD_ON_CNTR_ZERO);
    PWM_disableRisingEdgeDelayCountShadowLoadMode(base);
    PWM_setFallingEdgeDelayCountShadowLoadMode(base, PWM_FED_LOAD_ON_CNTR_ZERO);
    PWM_disableFallingEdgeDelayCountShadowLoadMode(base);

    PWM_setTimeBaseCounterMode(base, PWM_COUNTER_MODE_UP);
}

//
// PWM_init - Configure PWM4A and PWM1B for the PWM-DAC path.
// Call only while SYSCTL_PERIPH_CLK_TBCLKSYNC is disabled.
//
void PWM_init(void)
{
    //
    // GPIO22 <- PWM4A, CMPA ~24%
    //
    configurePwmChannel(myPWM4_BASE, true, PWM_DAC_CMPA_CH22);

    //
    // GPIO31 <- PWM1B, CMPB ~48%
    //
    configurePwmChannel(myPWM1_BASE, false, PWM_DAC_CMPB_CH31);
}

//
// End of File
//
