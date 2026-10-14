//###########################################################################
//
// FILE:    pwm_ex14_global_load_use_case.c
//
// TITLE:   PWM Developers Guide
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1> PWM Global Load (pwm_up_aq)</h1>
//!
//! The use case described in the application report is the following:
//!
//! Output frequency of 500 kHz for PWM1/2/3
//! Phase shift of 120 degrees for PWM2 with respect to PWM1
//! Phase shift of 240 degrees for PWM3 with respect to PWM1
//! Duty cycle of 45% for PWM1/2/3
//! Active high complementary signal pairs with 200 nsec of rising/falling edge delay for PWM1/2/3
//! Cycle-by-Cycle trip zone protection through comparator signal on PWM2
//! One-Shot trip protection through GPIO on PWM3
//! Interrupt generation everytime the time base counter equals zero on PWM1
//! Global loading to support asynchronous updates of action qualifier settings
//! Link CMPA/CMPB of PWM1 to PWM2 and PWM3
//!
//! \b External \b Connections \n
//!  - Optional: probe EPWM outputs on the EVAL header.
//!
//! \b Watch \b Variables \n
//!  - None.
//!
//
//###########################################################################
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
// - 2026-08-18:
// 1. Updated Global Load demo CMP values for TBPRD=200 (500 kHz at 200 MHz AHB).
//
//###########################################################################

#include "driverlib.h"
//
// Included Files
//
#include "device.h"
#include "board.h"

//
//  Function Prototypes
//

void INT_PWM1_IRQHandler(void);
void INT_PWM2_IRQHandler(void);
void INT_PWM3_IRQHandler(void);

uint16_t perform_one_shot_load = 0;

//
// Main
//
void example_main(void)
{
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
    //
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
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Set the priority group to indicate the PREEMPT and SUB priortiy bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    //
    // Set the global and group priority to allow CPU interrupts
    // with higher priority
    //
    Interrupt_setPriority(INT_PWM1_TRIP_ZONE,1,0);
    Interrupt_setPriority(INT_PWM2_TRIP_ZONE,2,0);
    Interrupt_setPriority(INT_PWM3_TRIP_ZONE,3,0);

    //
    // Configure ePWM1, ePWM2, and TZ GPIOs
    //
    Board_init();
    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_myPWM1_TRIP_ZONE, &INT_PWM1_IRQHandler);
    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_myPWM1_TRIP_ZONE);
    Interrupt_register(INT_myPWM2_TRIP_ZONE, &INT_PWM2_IRQHandler);
    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_myPWM2_TRIP_ZONE);
    Interrupt_register(INT_myPWM3_TRIP_ZONE, &INT_PWM3_IRQHandler);
    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_myPWM3_TRIP_ZONE);


    /*
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);

    PWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    PWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    PWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    PWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);

    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);


    // PWM1, PWM2, PWM3 are linked so this will update both
    PWM_setGlobalLoadOneShotLatch(myPWM1_BASE);
    */

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        if(perform_one_shot_load==1)
        {
            //
            // PWM1, PWM2, PWM3 are linked so only PWM1 needs to be updated
            //
            PWM_setCounterCompareValue(myPWM1_BASE, PWM_COUNTER_COMPARE_A, 160);
            PWM_setCounterCompareValue(myPWM1_BASE, PWM_COUNTER_COMPARE_B, 160);

            //
            // Change the Action Qualifier Settings for PWM1, PWM2, and PWM3
            //
            PWM_setActionQualifierAction(myPWM1_BASE,PWM_AQ_OUTPUT_A,PWM_AQ_OUTPUT_LOW,
                                        PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
            PWM_setActionQualifierAction(myPWM1_BASE,PWM_AQ_OUTPUT_A,PWM_AQ_OUTPUT_HIGH,
                                        PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
            PWM_setActionQualifierAction(myPWM2_BASE,PWM_AQ_OUTPUT_A,PWM_AQ_OUTPUT_LOW,
                                        PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
            PWM_setActionQualifierAction(myPWM2_BASE,PWM_AQ_OUTPUT_A,PWM_AQ_OUTPUT_HIGH,
                                        PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
            PWM_setActionQualifierAction(myPWM3_BASE,PWM_AQ_OUTPUT_A,PWM_AQ_OUTPUT_LOW,
                                        PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
            PWM_setActionQualifierAction(myPWM3_BASE,PWM_AQ_OUTPUT_A,PWM_AQ_OUTPUT_HIGH,
                                        PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

            // PWM1, PWM2, PWM3 are linked
            PWM_setGlobalLoadOneShotLatch(myPWM1_BASE);

            // Clear the setting
            perform_one_shot_load = 0;
        }
    }
}

//
// pwm1ISR - PWM1 ISR to update compare values
//
void INT_PWM1_IRQHandler(void)
{

}

//
// pwm2ISR - PWM2 ISR to update compare values
//
void INT_PWM2_IRQHandler(void)
{
    //
    // Clear INT flag for this timer
    //
    PWM_clearEventTriggerInterruptFlag(myPWM2_BASE);

    //
    // Clear the flags
    //
    PWM_clearTripZoneFlag(myPWM2_BASE, (PWM_TZ_INTERRUPT | PWM_TZ_FLAG_CBC));
}

//
// pwm3ISR - PWM3 ISR to update compare values
//
void INT_PWM3_IRQHandler(void)
{
    //
    // Re-enable the OST Interrupt
    //
    PWM_clearTripZoneFlag(myPWM3_BASE, (PWM_TZ_INTERRUPT | PWM_TZ_FLAG_OST));
}

//
// End of file
//
