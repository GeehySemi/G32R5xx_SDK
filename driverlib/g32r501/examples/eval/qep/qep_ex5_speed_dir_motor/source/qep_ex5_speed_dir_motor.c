//#############################################################################
//
// FILE:    qep_ex5_speed_dir_motor.c
//
// TITLE:   Motor encoder speed and direction measurement using QEP
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//         via unit timeout interrupt
//
//! \addtogroup driver_example_list
//! <h1>Motor speed and direction measurement using QEP
//! via unit timeout interrupt</h1>
//!
//! This example can be used to sense the speed and direction of motor
//! using QEP in quadrature encoder mode. PWM1A is configured to simulate
//! motor encoder signals with frequency of 5 kHz on both A and B pins with 90
//! degree phase shift (so as to run this example without motor).
//! QEP unit timeout is set which will generate an interrupt every
//!  \b UNIT_PERIOD microseconds and speed calculation occurs continuously
//!  based on the direction of motor
//!
//! The configuration for this example is as follows
//! - PWM frequency is specified as 5000Hz
//! - UNIT_PERIOD is specified as 10000 us
//! - Simulated quadrature signal frequency is 20000Hz (4 * 5000)
//! - Encoder holes assumed as 1000
//! - Thus Simulated motor speed is 300rpm (5000 * (60 / 1000))
//!
//! \b freq : Simulated quadrature signal frequency measured by counting
//! the external input pulses for UNIT_PERIOD (unit timer set to 10 ms).
//! \b speed : Measure motor speed in rpm
//! \b dir : Indicates clockwise (1) or anticlockwise (-1)
//!
//! \b External \b Connections (if motor encoder signals are simulated
//! by PWM) \n
//!
//! - Connect GPIO6/QEP1A to GPIO10/PWMA 
//!   (simulates QEP Phase A signal)
//! - Connect GPIO7/QEP1B to GPIO11/PWMB 
//!   (simulates QEP Phase B signal)
//!
//! \b Watch \b Variables \n
//! - \b freq : Simulated motor frequency measurement is obtained by counting
//! the external input pulses for UNIT_PERIOD (unit timer set to 10 ms).
//! - \b speed : Measure motor speed in rpm
//! - \b dir : Indicates clockwise (1) or anticlockwise (-1)
//! - \b pass - If measured qudrature frequency matches with i.e. input
//!             quadrature frequency (4 * PWM frequency) then pass = 1
//!             else fail = 1 (** only when "MOTOR" is commented out)
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
// - 2026-08-18:
// 1. Use DEVICE_APBCLK_FREQ for PWM PRD.
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
#define TB_CLK    DEVICE_APBCLK_FREQ         // PWM TBCLK is APBCLK
#define PWM_CLK   5000U                      // We want to output at 5 kHz
#define PRD_VAL   (TB_CLK / (PWM_CLK * 2))  // Calculate value period value
                                           // for up-down count mode
#define UNIT_PERIOD  10000U // Specify the period in microseconds
//Uncomment if motor is available for interfacing
//#define MOTOR

//
// Function Prototypes
//
void initPWM(void);

//
// Globals
//
uint32_t oldcount = 0;  // stores the previous position counter value
int32_t freq = 0;   // measured quadrature signal frequency of motor using QEP
float32_t speed = 0.0f;       // measured speed of motor in rpm
int32_t dir = 0;       // direction of rotation of motor
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
    // - Setup QEP1, configuring the unit timer and quadrature capture units
    // - Interrupts that are used in this example are re-mapped to ISR functions
    //   found within this file.
    // - Enable interrupts required for this example
    //
    Board_init();

    //
    // Initialize GPIOs for use as PWM1A,PWM1B and QEP1A,
    // QEPB
    //
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

#ifndef MOTOR
    //
    // Setup PWM1 to generate a 5 kHz signal to be an input to the QEP
    //
    initPWM();

#endif
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
// qep1 ISR- interrupts once per PWM period
//
void
INT_myQEP0_ISR(void)
{
    uint32_t temp = 0, newcount = 0 ;
    
    count++; // increment count value so to wait for frequency saturation

    newcount = QEP_getPositionLatch(myQEP0_BASE); // new position counter value
    temp = newcount;

   //
   // Gets direction of rotation of motor
   //
   dir = QEP_getDirection(myQEP0_BASE);

   //
   // Calculates the number of position in unit time based on
   // motor's direction of rotation
   //
   if (dir > 0 ){
       if (newcount >= oldcount)
            newcount = newcount - oldcount;
        else
            newcount = (0xFFFFFFFF - oldcount) + newcount;
        }
   else {
        if (newcount <= oldcount)
            newcount = oldcount - newcount;
        else
            newcount = (0xFFFFFFFF - newcount) + oldcount;
        }

   //
   // Stores the current position count value to oldcount variable
   //
   oldcount = temp;

   //
   // Simulated Frequency and speed calculation
   //
   freq = (newcount * (uint32_t)1000000U)/((uint32_t)UNIT_PERIOD);
   speed = (freq * 60)/4000.0f;

   //
   // Compares the measured quadrature simulated frequency with input quadrature
   // frequency and if difference is within the measurement resolution
   // (1/10ms = 100Hz) then pass = 1 else fail = 1
   //
#ifndef MOTOR
   if (count >= 2){
        if (((freq - (int32_t)PWM_CLK * 4) < 100) && ((freq - (int32_t)PWM_CLK * 4) > -100)){
            pass = 1; fail = 0;
        }
        else {
            fail = 1; pass = 0;
        }
    }
#endif

   //
   // Clear interrupt flag and issue ACK
   //
   QEP_clearInterruptStatus(myQEP0_BASE,QEP_INT_UNIT_TIME_OUT|QEP_INT_GLOBAL);
 }

//
// End of File
//

