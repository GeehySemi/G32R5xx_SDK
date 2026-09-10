//#############################################################################
//
// FILE:    hrpwm_ex4_duty_updown_sfo.c
//
// TITLE:   HRPWM Duty Control with UPDOWN Mode.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1>HRPWM Duty Control with UPDOWN Mode</h1>
//!
//! This example calls the MEP Scale Factor Optimizer (SFO) software library
//! V1 functions:
//!
//! \b int \b SFO(); \n
//! - updates MEP_ScaleFactor dynamically when HRPWM is in use
//! - updates HRMSTEP register (exists only in Pwm1Regs register space)
//!   with MEP_ScaleFactor value
//! - returns 2 if error: MEP_ScaleFactor is greater than maximum value of 255
//!   (Auto-conversion may not function properly under this condition)
//! - returns 1 when complete for the specified channel
//! - returns 0 if not complete for the specified channel
//!
//! This example is intended to explain the HRPWM capabilities. The code can be
//! optimized for code efficiency.
//!
//! \b External \b Connections \n
//!  - Monitor PWM1/2/3/4 A/B pins on an oscilloscope.
//
//#############################################################################
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
// 1. Modified peripheral register names by Geehy Semiconductor.
//
//#############################################################################

#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "SFO_V1.h"

#define CHANNEL_B_AS_ZRO_PRD_REF    1
#define PWM_TIMER_TBPRD            100UL
#define MIN_HRPWM_DUTY_PERCENT      4.0/((float32_t)PWM_TIMER_TBPRD)*100.0
//
// Defines
//
#define LAST_PWM_INDEX_FOR_EXAMPLE    5

//
// Globals
//

float32_t dutyFine = 50.0;
uint16_t status;

int MEP_ScaleFactor; // Global variable used by the SFO library
                     // Result can be used for all HRPWM channels
                     // This variable is also copied to HRMSTEP
                     // register by SFO() function.

volatile uint32_t PWM[] =
    {0, myPWM1_BASE, myPWM2_BASE, myPWM3_BASE, myPWM4_BASE};
//
// Function Prototypes
//
void initHRPWM_ChannelB(uint32_t period);
void error(void);
//void pwm1ISR(void);
//void pwm2ISR(void);
//void pwm3ISR(void);
//void pwm4ISR(void);

//
// Main
//
void example_main(void)
{
    uint16_t i = 0;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull ups.
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
    // Assign the interrupt service routines to PWM interrupts
    //
    //Interrupt_register(INT_PWM1, &pwm1ISR);
    //Interrupt_register(INT_PWM2, &pwm2ISR);
    //Interrupt_register(INT_PWM3, &pwm3ISR);
    //Interrupt_register(INT_PWM4, &pwm4ISR);

    //
    // Calling SFO() updates the HRMSTEP register with calibrated MEP_ScaleFactor.
    // HRMSTEP must be populated with a scale factor value prior to enabling
    // high resolution period control.
    //
    while (status == SFO_INCOMPLETE)
    {
        status = SFO();
        if (status == SFO_ERROR)
        {
            error();   // SFO function returns 2 if an error occurs & # of MEP
        }              // steps/coarse step exceeds maximum of 255.
    }



    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Initialize the PWM GPIOs and change XBAR inputs from using GPIO0
    //
    Board_init();

    initHRPWM_ChannelB(PWM_TIMER_TBPRD);

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);


    // Enable PWM interrupts
    //
    //Interrupt_enable(INT_PWM1);
    //Interrupt_enable(INT_PWM2);
    //Interrupt_enable(INT_PWM3);
    //Interrupt_enable(INT_PWM4);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;


    for (;;)
    {
         //
         // Sweep DutyFine
         //
         for (dutyFine = MIN_HRPWM_DUTY_PERCENT; dutyFine < (100.0 - MIN_HRPWM_DUTY_PERCENT); dutyFine += 0.01)
         {
             DEVICE_DELAY_US(1000);
             for (i = 1; i < LAST_PWM_INDEX_FOR_EXAMPLE; i++)
             {
                 float32_t count = ((100.0 - dutyFine) * (float32_t)(PWM_TIMER_TBPRD << 8))/100.0;
                 uint32_t compCount = (uint32_t)(count);
                 uint32_t hrCompCount = (compCount & (0x000000FF));
                 if (hrCompCount == 0)
                 {
                     //
                     // Add 1 to not have CMPxHR = 0
                     //
                     compCount |= 0x00000001;
                 }
                 HRPWM_setCounterCompareValue(PWM[i], HRPWM_COUNTER_COMPARE_A, compCount);
#if CHANNEL_B_AS_ZRO_PRD_REF == 0
                 HRPWM_setCounterCompareValue(PWM[i], HRPWM_COUNTER_COMPARE_B, compCount);
#endif
             }

             //
             // Call the scale factor optimizer lib function SFO()
             // periodically to track for any change due to temp/voltage.
             // This function generates MEP_ScaleFactor by running the
             // MEP calibration module in the HRPWM logic. This scale
             // factor can be used for all HRPWM channels. The SFO()
             // function also updates the HRMSTEP register with the
             // scale factor value.
             //
             status = SFO(); // in background, MEP calibration module
                             // continuously updates MEP_ScaleFactor

             if (status == SFO_ERROR)
             {
                 error();   // SFO function returns 2 if an error occurs & #
                            // of MEP steps/coarse step
             }              // exceeds maximum of 255.
         }
     }
}

//
// pwm1ISR - PWM 1 ISR
//
//void pwm1ISR(void)
//{
//    PWM_clearEventTriggerInterruptFlag(PWM1_BASE);
//    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
//}

//
// pwm2ISR - PWM 2 ISR
//
//void pwm2ISR(void)
//{
//    PWM_clearEventTriggerInterruptFlag(PWM2_BASE);
//    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
//}

//
// pwm3ISR - PWM 3 ISR
//
//void pwm3ISR(void)
//{
//    PWM_clearEventTriggerInterruptFlag(PWM3_BASE);
//    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
//}

//
// pwm4ISR - PWM 4 ISR
//
//void pwm4ISR(void)
//{
//    PWM_clearEventTriggerInterruptFlag(PWM4_BASE);
//    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
//}


void initHRPWM_ChannelB(uint32_t period)
{

    uint16_t j;

    //
    // PWM channel register configuration with HRPWM
    // PWMxA / PWMxB toggle low/high with MEP control on Rising and Falling edges
    //
    for (j=1;j<LAST_PWM_INDEX_FOR_EXAMPLE;j++)
    {

#if CHANNEL_B_AS_ZRO_PRD_REF == 1
        //
        // Use B channel as the ZERO and PRD reference
        //
        PWM_setActionQualifierAction(PWM[j],
                                      PWM_AQ_OUTPUT_B,
                                      PWM_AQ_OUTPUT_HIGH,
                                      PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
        PWM_setActionQualifierAction(PWM[j],
                                      PWM_AQ_OUTPUT_B,
                                      PWM_AQ_OUTPUT_LOW,
                                      PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
#else
        PWM_setActionQualifierAction(PWM[j],
                                      PWM_AQ_OUTPUT_B,
                                      PWM_AQ_OUTPUT_HIGH,
                                      PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
        PWM_setActionQualifierAction(PWM[j],
                                      PWM_AQ_OUTPUT_B,
                                      PWM_AQ_OUTPUT_LOW,
                                      PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
#endif

#if CHANNEL_B_AS_ZRO_PRD_REF == 0
        HRPWM_setMEPEdgeSelect(PWM[j], HRPWM_CHANNEL_B, HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE);
        HRPWM_setMEPControlMode(PWM[j], HRPWM_CHANNEL_B, HRPWM_MEP_DUTY_PERIOD_CTRL);

        //
        // Set up shadowing
        // MUST BE CTR=(ZER & PRD)
        //
        HRPWM_setCounterCompareShadowLoadEvent(PWM[j], HRPWM_CHANNEL_B, HRPWM_LOAD_ON_CNTR_ZERO_PERIOD);
#endif

        //
        // Interrupt where we will change the Compare Values
        // Select INT on Time base counter zero event,
        // Enable INT, generate INT on 1st event
        //
        //PWM_setInterruptSource(PWM[j], PWM_INT_TBCTR_ZERO);
        //PWM_enableInterrupt(PWM[j]);
        //PWM_setInterruptEventCount(PWM[j], 1U);
    }

}

//
// error - Halt debugger when called
//
void error (void)
{
    ESTOP0;         // Stop here and handle error
}
