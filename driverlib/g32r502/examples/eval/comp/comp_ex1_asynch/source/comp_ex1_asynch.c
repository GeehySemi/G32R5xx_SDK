//#############################################################################
//
// FILE:    comp_ex1_asynch.c
//
// TITLE:   COMP Asynchronous Trip
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1> COMP Asynchronous Trip </h1>
//!
//! This example enables the COMP1 COMPH comparator and feeds the asynchronous
//! CTRIPOUTH signal to the GPIO14/OUTPUTXBAR3 pin and CTRIPH to GPIO13/PWM7B.
//!
//! COMP is configured to generate trip signals to trip the PWM signals.
//! CMP1_HP0 (ADCC C9 / GPIO224 on G32R502 EVAL, CMP1HPMXSEL=0) is used as
//! the positive input
//! and the internal DAC is configured to provide the negative input at
//! VDDA/2. A PWM signal is generated at GPIO13/PWM7B and is tripped by
//! CTRIPH (PWM X-BAR TRIP4). CTRIPOUTH is routed to GPIO14 for observation.
//!
//! When a low input(VSS) is provided to CMP1_HP0,
//!     - Trip signal (GPIO14) output is low
//!     - PWM7B(GPIO13) gives a PWM signal
//!
//! When a high input(higher than VDDA/2) is provided to CMP1_HP0,
//!     - Trip signal (GPIO14) output turns high
//!     - PWM7B(GPIO13) gets tripped and outputs as high
//!
//! \b External \b Connections \n
//!  - Give input on ADCC C9 (GPIO224 on G32R502 EVAL, CMP1HPMXSEL=0)
//!  - Observe CTRIPOUTH on GPIO14 and PWM7B on GPIO13 with an oscilloscope
//!
//! \b Watch \b Variables \n
//!  - None
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
// Function Prototypes
//
void initPWM(void);

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
    // Set up PWM7 to take CTRIPH as TRIP4 for its DC trip input
    //
    initPWM();

    //
    // Board Initialization
    // - Configure GPIO14 to output CTRIPOUTH (routed through OUTPUTXBAR3)
    // - Setup the Output X-BAR to output CTRIPOUTH on OUTPUTXBAR3
    // - Configure the high comparator of COMP1
    // - Enable COMP and configure the negative input signal to come from
    //   the DAC
    // - Use VDDA as the reference for the DAC and set DAC value to midpoint for
    //   arbitrary reference.
    // - Configure the output signals. Both CTRIPH and CTRIPOUTH will be fed by
    //   the asynchronous comparator output.
    //
    Board_init();


    //
    // Configure GPIO13 as PWM7B (CTRIPH trip via PWM X-BAR TRIP4)
    //
    GPIO_setPinConfig(GPIO_13_PWM7_B);
    //
    // Configure GPIO13 as digital pins
    //
    GPIO_setAnalogMode(13U, GPIO_ANALOG_DISABLED);

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
        //
        // Trip flag is set when CTRIP signal is asserted
        //
        if((PWM_getTripZoneFlagStatus(PWM7_BASE) &
            PWM_TZ_FLAG_OST) != 0U)
        {
            //
            // Wait for comparator CTRIP to de-assert
            //
            while((COMP_getStatus(COMP1_BASE) & COMP_STS_HI_FILTOUT) != 0U)
            {
                ;
            }

            //
            // Clear trip flags
            //
            PWM_clearTripZoneFlag(PWM7_BASE, PWM_TZ_INTERRUPT |
                                   PWM_TZ_FLAG_OST);
        }
    }
}

//
// initPWM - Function to configure PWM7 and the PWM X-BAR to take CTRIPH as
//            the DC trip input
//
void initPWM(void)
{
    //
    // Disable the PWM time base clock before configuring the module
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Set the time base clock prescalers to /1
    //
    PWM_setClockPrescaler(PWM7_BASE, PWM_CLOCK_DIVIDER_1,
                           PWM_HSCLOCK_DIVIDER_1);

    //
    // Initializing dummy values for PWM counter and period
    //
    PWM_setTimeBaseCounter(PWM7_BASE, 0);
    PWM_setTimeBasePeriod(PWM7_BASE, 0xFFFF);

    //
    // Set-up compare
    //
    PWM_setCounterCompareValue(PWM7_BASE, PWM_COUNTER_COMPARE_B, 0x8000);

    //
    // Set actions
    //
    PWM_setActionQualifierAction(PWM7_BASE,
                                  PWM_AQ_OUTPUT_B,
                                  PWM_AQ_OUTPUT_HIGH,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

    PWM_setActionQualifierAction(PWM7_BASE,
                                  PWM_AQ_OUTPUT_B,
                                  PWM_AQ_OUTPUT_LOW,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

    //
    // Configure PWM7B to output high on TZB TRIP

    //
    PWM_setTripZoneAction(PWM7_BASE, PWM_TZ_ACTION_EVENT_TZB,
                           PWM_TZ_ACTION_HIGH);

    //
    // Trigger event when DCBH is high
    //
    PWM_setTripZoneDigitalCompareEventCondition(PWM7_BASE,
                                                 PWM_TZ_DC_OUTPUT_B1,
                                                 PWM_TZ_EVENT_DCXH_HIGH);

    //
    // Configure DCBH to use TRIP4 as an input
    //
    PWM_enableDigitalCompareTripCombinationInput(PWM7_BASE,
                                                  PWM_DC_COMBINATIONAL_TRIPIN4,
                                                  PWM_DC_TYPE_DCBH);

    //
    // Enable DCB as OST
    //
    PWM_enableTripZoneSignals(PWM7_BASE, PWM_TZ_SIGNAL_DCBEVT1);

    //
    // Configure the DCB path to be unfiltered and asynchronous
    //
    PWM_setDigitalCompareEventSource(PWM7_BASE,
                                      PWM_DC_MODULE_B,
                                      PWM_DC_EVENT_1,
                                      PWM_DC_EVENT_SOURCE_ORIG_SIGNAL);

    //
    // Sync the PWM time base clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure TRIP4 to be CTRIP1H using the PWM X-BAR
    //
    XBAR_setPWMMuxConfig(XBAR_TRIP4, XBAR_PWM_MUX00_COMP1_CTRIPH);
    XBAR_enablePWMMux(XBAR_TRIP4, XBAR_MUX00);

    //
    // Clear trip flags
    //
    PWM_clearTripZoneFlag(PWM7_BASE, PWM_TZ_INTERRUPT |
                           PWM_TZ_FLAG_OST);

    //
    // Put the time base counter into up-count mode
    //
    PWM_setTimeBaseCounterMode(PWM7_BASE, PWM_COUNTER_MODE_UP);
}


