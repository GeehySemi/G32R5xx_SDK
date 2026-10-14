//#############################################################################
//
// FILE:    qep_ex4_freq_cal_interrupt.c
//
// TITLE:   Frequency Measurement Using QEP via unit timeout interrupt
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1>Frequency Measurement Using QEP via unit timeout interrupt</h1>
//!
//! This example will calculate the frequency of an input signal using the
//! QEP module.  PWM1A is configured to generate this input signal with a
//! frequency of 5 kHz. QEP unit timeout is set which will generate
//! an interrupt every \b UNIT_PERIOD microseconds and frequency calculation
//! occurs continuously
//!
//! The configuration for this example is as follows
//! - PWM frequency is specified as 5000Hz
//! - UNIT_PERIOD is specified as 10000 us
//! - Min frequency is (1/(2*10ms)) i.e 50Hz
//! - Highest frequency can be (2^32)/ ((2*10ms))
//! - Resolution of frequency measurement is 50hz
//!
//! \b freq : Frequency Measurement is obtained by counting the
//! external input pulses for UNIT_PERIOD (unit timer set to 10 ms).
//!
//! \b External \b Connections\n
//! - Connect GPIO6/QEP1A to GPIO10/PWMA
//!
//! \b Watch \b Variables \n
//! - \b freq - Frequency measurement using position counter/unit
//!   time out
//! - \b pass - If measured frequency matches with PWM frequency
//!             then pass = 1 else 0
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
// 3. Use DEVICE_AHBCLK_FREQ for PWM PRD.
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
#define TB_CLK    DEVICE_AHBCLK_FREQ         // PWM TBCLK on AHB
#define PWM_CLK   5000U                      // PWM frequency as 5 kHz
#define PRD_VAL   (TB_CLK / (PWM_CLK * 2))  // Calculate value period value
                                            // for up-down count mode
#define UNIT_PERIOD  10000U // Specify the unit timeout period in
                            // microseconds
                            
//
// Function Prototypes
//
void initPWM(void);

//
// Globals
//
uint32_t oldcount = 0;  // stores the previous position counter value
int32_t freq = 0;      // measured frequency using QEP
uint32_t count = 0;     // just to make sure measured frequency gets saturated
uint32_t pass = 0, fail = 0; // test pass or fail indicator

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
    // Board Initialization
    // - Setup QEP1, configuring the unit timer and quadrature capture units
    // - Initialize GPIOs for QEP1A
    // - Interrupts that are used in this example are re-mapped to ISR functions
    //   found within this file.
    // - Enable interrupts required for this example
    //
    Board_init();
    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    // Set the priority group to indicate the PREEMPT and SUB priortiy bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);
    //
    // Set the global and group priority to allow CPU interrupts
    // with higher priority
    //
    Interrupt_setPriority(INT_myQEP0, 0, 0);
    Interrupt_register(INT_myQEP0, &INT_myQEP0_ISR);
    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_myQEP0);


    //
    // Initialize GPIOs for PWM1A
    //
    //
    // On EVAL Board, Initialize GPIO10 to PWM1A, GPIO10 on QEP1A

    GPIO_setPinConfig(DEVICE_GPIO_CFG_PWMxA);
    GPIO_setDrivingCapability(DEVICE_GPIO_PIN_PWMxA,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_PWMxA, GPIO_PIN_TYPE_STD);

    //
    // Setup PWM1 to generate a 5 kHz signal to be an input to the QEP
    //
    initPWM();

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
    PWM_setPhaseShift(DEVICE_PERIPHERAL_BASE_PWM, 0);
    PWM_setTimeBaseCounter(DEVICE_PERIPHERAL_BASE_PWM, 0);

    //
    // Disable the shadow load; the load will be immediate instead
    //
    PWM_disableCounterCompareShadowLoadMode(DEVICE_PERIPHERAL_BASE_PWM,
                                             PWM_COUNTER_COMPARE_A);
    PWM_disableCounterCompareShadowLoadMode(DEVICE_PERIPHERAL_BASE_PWM,
                                             PWM_COUNTER_COMPARE_B);

    //
    // Set the compare A value to half the period value, compare B to 0
    //
    PWM_setCounterCompareValue(DEVICE_PERIPHERAL_BASE_PWM, PWM_COUNTER_COMPARE_A, PRD_VAL/2);
    PWM_setCounterCompareValue(DEVICE_PERIPHERAL_BASE_PWM, PWM_COUNTER_COMPARE_B, 0);

    //
    // Set action qualifier behavior on compare A events
    // - PWM1A --> 1 when CTR = CMPA and increasing
    // - PWM1A --> 0 when CTR = CMPA and decreasing
    //
    PWM_setActionQualifierAction(DEVICE_PERIPHERAL_BASE_PWM, PWM_AQ_OUTPUT_A,
                                  PWM_AQ_OUTPUT_HIGH,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    PWM_setActionQualifierAction(DEVICE_PERIPHERAL_BASE_PWM, PWM_AQ_OUTPUT_A,
                                  PWM_AQ_OUTPUT_LOW,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

    //
    // Configure PWM1B to be complementary to PWM1A
    //
    PWM_setDeadBandDelayPolarity(DEVICE_PERIPHERAL_BASE_PWM, PWM_DB_FED,
                                  PWM_DB_POLARITY_ACTIVE_LOW);
    PWM_setDeadBandDelayMode(DEVICE_PERIPHERAL_BASE_PWM, PWM_DB_FED, true);
    PWM_setDeadBandDelayMode(DEVICE_PERIPHERAL_BASE_PWM, PWM_DB_RED, true);

    //
    // Set the time base clock prescaler to /1
    //
    PWM_setClockPrescaler(DEVICE_PERIPHERAL_BASE_PWM, PWM_CLOCK_DIVIDER_1,
                           PWM_HSCLOCK_DIVIDER_1);

    //
    // Set the period value; don't shadow the register
    //
    PWM_setPeriodLoadMode(DEVICE_PERIPHERAL_BASE_PWM, PWM_PERIOD_DIRECT_LOAD);
    PWM_setTimeBasePeriod(DEVICE_PERIPHERAL_BASE_PWM, PRD_VAL);

    //
    // Put the time base counter into up-down count mode
    //
    PWM_setTimeBaseCounterMode(DEVICE_PERIPHERAL_BASE_PWM, PWM_COUNTER_MODE_UP_DOWN);

    //
    // Sync the PWM time base clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

//
// qep11 ISR- interrupts once per PWM period
//
void
INT_myQEP0_ISR(void)
{

    uint32_t temp =0, newcount = 0 ;
    
    count++;  // increment count value so to wait for frequency saturation

    newcount = QEP_getPositionLatch(myQEP0_BASE); // new position counter value
    temp = newcount;

    //
    // Calculates the number of position counts in unit time
    //
    if (newcount >= oldcount)
        newcount = newcount - oldcount;
    else
        newcount = (0xFFFFFFFF - oldcount) + newcount;

    //
    // Stores the current position count value to oldcount variable
    //
    oldcount = temp;

    //
    // Frequency calculation equation i.e
    // freq = ((position counts) * 1000000 )/ (2 * Unit_time (in microseconds))
    //
    freq = (newcount * (uint32_t)1000000U)/(2 * (uint32_t)UNIT_PERIOD);

    //
    // Compares the measured frequency with input frequency
    //
    if (count >= 2){
        if (((freq - (int32_t)PWM_CLK) < 50) && ((freq - (int32_t)PWM_CLK) > -50)){
            pass = 1; fail = 0;
        }
        else {
            fail = 1; pass = 0;
        }
    }

    //
    // Clears the interrupt flag
    //
    QEP_clearInterruptStatus(myQEP0_BASE,QEP_INT_UNIT_TIME_OUT|QEP_INT_GLOBAL);
}

//
// End of File
//

