//#############################################################################
//
// FILE:    qep_ex2_pos_speed.c
//
// TITLE:   Position and Speed Measurement Using QEP
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1> Position and Speed Measurement Using QEP</h1>
//!
//! This example provides position and speed measurement using the
//! capture unit and speed measurement using unit time out of the QEP module.
//! PWM1 and a GPIO are configured to generate simulated QEP signals. The
//! PWM module will interrupt once every period and call the position/speed
//! calculation function. This example uses the Fix32math library to simplify
//! high-precision calculations.
//!
//! In addition to the main example file, the following files must be included
//! in this project:
//! - \b qep_ex2_calculation.c - contains position/speed calculation function
//! - \b qep_ex2_calculation.h - includes initialization values for
//!                               position/speed structure
//!
//! The configuration for this example is as follows
//! - Maximum speed is configured to 6000rpm (baseRPM)
//! - Minimum speed is assumed at 10rpm for capture pre-scalar selection
//! - Pole pair is configured to 2 (polePairs)
//! - Encoder resolution is configured to 4000 counts/revolution (mechScaler)
//! - Which means: 4000 / 4 = 1000 line/revolution quadrature encoder
//!   (simulated by PWM1)
//! - PWM1 (simulating QEP encoder signals) is configured for a 5kHz frequency
//!   or 300 rpm (= 4 * 5000 cnts/sec * 60 sec/min) / 4000 cnts/rev)
//!
//! \b SPEEDRPM_FR: High Speed Measurement is obtained by counting the QEP
//! input pulses for 10ms (unit timer set to 100Hz).
//!
//! \b SPEEDRPM_FR = (Position Delta / 10ms) * 60 rpm
//!
//! \b SPEEDRPM_PR: Low Speed Measurement is obtained by measuring time period
//! of QEP edges. Time measurement is averaged over 64 edges for better results
//! and the capture unit performs the time measurement using pre-scaled APBCLK.
//!
//! Note that the pre-scaler for capture unit clock is selected such that the
//! capture timer does not overflow at the required minimum frequency. This
//! example runs indefinitely until the user stops it.
//!
//! For more information about the position/speed calculation see the comments
//! at the beginning of qep_ex2_calculation.c.
//!
//! \b External \b Connections \n
//!
//! - Connect GPIO6/QEP1A to GPIO0/PWM1A 
//!   (simulates QEP Phase A signal)
//! - Connect GPIO7/QEP1B to GPIO1/PWM1B 
//!   (simulates QEP Phase B signal)
//! - Connect GPIO9/QEP1I to GPIO4 
//!   (simulates QEP Index Signal)
//!
//! \b Watch \b Variables \n
//!  - \b posSpeed.speedRPMFR - Speed meas. in rpm using QEP position counter
//!  - \b posSpeed.speedRPMPR - Speed meas. in rpm using capture unit
//!  - \b posSpeed.thetaMech  - Motor mechanical angle (Q15)
//!  - \b posSpeed.thetaElec  - Motor electrical angle (Q15)
//!
//
//#############################################################################
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
// 2. Updated interrupt handling to use NVIC functions.
//
//###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "Fix32mathLib.h"
#include "qep_ex2_calculation.h"
#include "board.h"


//
// Defines
//
#define TB_CLK    DEVICE_APBCLK_FREQ        // Time base clock is APBCLK
#define PWM_CLK   5000                      // We want to output at 5 kHz
                                            // (300 rpm)
#define PRD_VAL   (TB_CLK / (PWM_CLK * 2))  // Calculate value period value
                                            // for up-down count mode

// .9999 / 4000 converted to IQ26 fixed point format
#define MECH_SCALER     16776
// 2 pole pairs in this example
#define POLE_PAIRS      2
// Angular offset between encoder and Phase A
#define CAL_ANGLE       0
// See Equation 5 in qep_ex2_calculation.c
#define SPEED_SCALER    ((((uint64_t)32 * DEVICE_APBCLK_FREQ / 64) * 60) / (24000000))
// Base/max rpm is 6000rpm
#define BASE_RPM        6000


//
// Function Prototypes
//
void initPWM(void);
void pwmISR(void);

//
// Globals
//
PosSpeed_Object posSpeed =
{
    0, 0, 0, 0,               // Initialize outputs to zero
    MECH_SCALER,               // mechScaler
    POLE_PAIRS,                // polePairs
    CAL_ANGLE,                 // calAngle
    (uint32_t)SPEED_SCALER,    // speedScaler
    0,                         // Initialize output to zero
    BASE_RPM,                  // baseRPM
    0, 0, 0, 0                // Initialize outputs to zero
};

uint16_t interruptCount = 0;
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
    // Set the priority group to indicate the PREEMPT and SUB priority bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_7_6_SUB_5_0);

    //
    // Set the global and group interrupt priority to allow CPU interrupts
    // with higher priority
    Interrupt_setPriority(INT_PWM6, 0, 0);

    //
    // Board Initialization
    // Setup QEP1, configuring the unit timer and quadrature capture units
    // Initialize GPIOs for use as QEP1A, QEP1B, and QEP1I
    //
    Board_init();

    //
    // On EVAL Board, use GPIO10 on PWM6A, GPIO11 on PWM6B, and 
    // GPIO8 as an output.
    // They will be used to simulate incoming QEP Phase A, Phase B, and Index
    // signals respectively.
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_PWMxA);
    GPIO_setDrivingCapability(DEVICE_GPIO_PIN_PWMxA,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_PWMxA, GPIO_PIN_TYPE_STD);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_PWMxB);
    GPIO_setDrivingCapability(DEVICE_GPIO_PIN_PWMxB,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_PWMxB, GPIO_PIN_TYPE_STD);
    
    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(DEVICE_PERIPHERAL_INT_PWM, &pwmISR);

    //
    // Setup PWM1 to generate a 5 kHz signal to be an input to the QEP
    //
    initPWM();

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(DEVICE_PERIPHERAL_INT_PWM);

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
// Function to configure PWM1 to generate a 5 kHz signal.
//
void initPWM(void)
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
    PWM_setCounterCompareValue(DEVICE_PERIPHERAL_BASE_PWM, 
                                PWM_COUNTER_COMPARE_A, PRD_VAL/2);
    PWM_setCounterCompareValue(DEVICE_PERIPHERAL_BASE_PWM, 
                                PWM_COUNTER_COMPARE_B, 0);

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
    // Set action qualifier behavior on compare B events
    // - PWM1B --> 1 when CTR = PRD and increasing
    // - PWM1B --> 0 when CTR = 0 and decreasing
    //
    PWM_setActionQualifierAction(DEVICE_PERIPHERAL_BASE_PWM, PWM_AQ_OUTPUT_B,
                                  PWM_AQ_OUTPUT_HIGH,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    PWM_setActionQualifierAction(DEVICE_PERIPHERAL_BASE_PWM, PWM_AQ_OUTPUT_B,
                                  PWM_AQ_OUTPUT_LOW,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

    //
    // Enable interrupt when the counter is equal to PRD
    //
    PWM_setInterruptSource(DEVICE_PERIPHERAL_BASE_PWM, PWM_INT_TBCTR_PERIOD);
    PWM_enableInterrupt(DEVICE_PERIPHERAL_BASE_PWM);

    //
    // Interrupt on first event
    //
    PWM_setInterruptEventCount(DEVICE_PERIPHERAL_BASE_PWM, 1);

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
    PWM_setTimeBaseCounterMode(DEVICE_PERIPHERAL_BASE_PWM,  
                                PWM_COUNTER_MODE_UP_DOWN);


    //
    // Sync the PWM time base clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

//
// PWM1 ISR--interrupts once every 4 QCLK counts (one period)
//
void pwmISR(void)
{
    uint16_t i;

    //
    // Position speed and measurement
    //
    PosSpeed_calculate(&posSpeed);


    //
    // Control loop for position control and speed control
    //
    interruptCount++;
    if(interruptCount == 1000)
    {
        //
        // Pulse index signal (1 pulse/rev)
        //
        GPIO_writePin(DEVICE_GPIO_PIN_IOINDEX, 1);
        for(i = 0; i < 700; i++)
        {
            ;
        }
        GPIO_writePin(DEVICE_GPIO_PIN_IOINDEX, 0);
    }

    //
    // Clear interrupt flag and issue ACK
    //
    PWM_clearEventTriggerInterruptFlag(DEVICE_PERIPHERAL_BASE_PWM);
}
