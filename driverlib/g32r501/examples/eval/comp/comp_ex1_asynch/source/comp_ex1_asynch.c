//#############################################################################
//
// FILE:    comp_ex1_asynch.c
//
// TITLE:   COMP Asynchronous Trip
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1> COMP Asynchronous Trip </h1>
//!
//! This example enables the COMP1 COMPH comparator and feeds the asynchronous
//! CTRIPOUTH signal to the GPIO14/OUTPUTXBAR3 pin and CTRIPH to GPIO15/PWM8B.
//!
//! COMP is configured to generate trip signals to trip the PWM signals.
//! CMPIN1P is used to give positive input and internal DAC is configured
//! to provide the negative input. Internal DAC is configured to provide a
//! signal at VDD/2. An PWM signal is generated at GPIO15 and is configured
//! to be tripped by CTRIPOUTH.
//!
//! When a low input(VSS) is provided to CMPIN1P,
//!     - Trip signal(GPIO14) output is low
//!     - PWM8B(GPIO15) gives a PWM signal
//!
//! When a high input(higher than VDD/2) is provided to CMPIN1P,
//!     - Trip signal(GPIO14) output turns high
//!     - PWM8B(GPIO15) gets tripped and outputs as high
//!
//! \b External \b Connections \n
//!  - Give input on CMPIN1P (The pin is shared with ADCINB6)
//!  - Outputs can be observed on GPIO14 and GPIO15 using an oscilloscope
//!
//! \b Watch \b Variables \n
//!  - None
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
    // Initialize NVIC and clears NVIC registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Set up PWM8 to take CTRIPH as TRIP4 for its DC trip input
    //
    initPWM();

    //
    // Board Initialization
    // - Configure GPIO14 to output CTRIPOUT1H (routed through XBAROUTPUT3)
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
    // Configure GPIO15 to output CTRIPH (routed through PWM TRIP4 and PWM8)
    //
    GPIO_setPinConfig(GPIO_15_PWM8B);

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
        if((PWM_getTripZoneFlagStatus(PWM8_BASE) &
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
            PWM_clearTripZoneFlag(PWM8_BASE, PWM_TZ_INTERRUPT |
                                   PWM_TZ_FLAG_OST);
        }
    }
}

//
// initPWM - Function to configure PWM8 and the PWM X-BAR to take CTRIPH as
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
    PWM_setClockPrescaler(PWM8_BASE, PWM_CLOCK_DIVIDER_1,
                           PWM_HSCLOCK_DIVIDER_1);

    //
    // Initializing dummy values for PWM counter and period
    //
    PWM_setTimeBaseCounter(PWM8_BASE, 0);
    PWM_setTimeBasePeriod(PWM8_BASE, 0xFFFF);

    //
    // Set-up compare
    //
    PWM_setCounterCompareValue(PWM8_BASE, PWM_COUNTER_COMPARE_B, 0x8000);

    //
    // Set actions
    //
    PWM_setActionQualifierAction(PWM8_BASE,
                                  PWM_AQ_OUTPUT_B,
                                  PWM_AQ_OUTPUT_HIGH,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

    PWM_setActionQualifierAction(PWM8_BASE,
                                  PWM_AQ_OUTPUT_B,
                                  PWM_AQ_OUTPUT_LOW,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

    //
    // Configure PWM8B to output high on TZB TRIP

    //
    PWM_setTripZoneAction(PWM8_BASE, PWM_TZ_ACTION_EVENT_TZB,
                           PWM_TZ_ACTION_HIGH);

    //
    // Trigger event when DCBH is high
    //
    PWM_setTripZoneDigitalCompareEventCondition(PWM8_BASE,
                                                 PWM_TZ_DC_OUTPUT_B1,
                                                 PWM_TZ_EVENT_DCXH_HIGH);

    //
    // Configure DCBH to use TRIP4 as an input
    //
    PWM_enableDigitalCompareTripCombinationInput(PWM8_BASE,
                                                  PWM_DC_COMBINATIONAL_TRIPIN4,
                                                  PWM_DC_TYPE_DCBH);

    //
    // Enable DCB as OST
    //
    PWM_enableTripZoneSignals(PWM8_BASE, PWM_TZ_SIGNAL_DCBEVT1);

    //
    // Configure the DCB path to be unfiltered and asynchronous
    //
    PWM_setDigitalCompareEventSource(PWM8_BASE,
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
    PWM_clearTripZoneFlag(PWM8_BASE, PWM_TZ_INTERRUPT |
                           PWM_TZ_FLAG_OST);

    //
    // Put the time base counter into up-count mode
    //
    PWM_setTimeBaseCounterMode(PWM8_BASE, PWM_COUNTER_MODE_UP);
}


