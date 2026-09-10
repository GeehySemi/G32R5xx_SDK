//#############################################################################
//
// FILE:    board.c
//
// TITLE:   Board source file
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
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
// 1. Modified function names and macro definition names.
//
//###########################################################################

#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules.
// Call this function in your application if you wish to do all module
// initialization.
// If you wish to not use some of the initializations, instead of the
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
    WRPRT_DISABLE;

    PinMux_init();
    INPUTXBAR_init();
    SYNC_init();
    COMP_init();
    PWM_init();
    PWMXBAR_init();
    GPIO_init();
    INTERRUPT_init();

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
    //
    // PinMux for modules assigned to CPU1
    //

    //
    // PWM1 -> myPWM1 Pinmux
    //
    GPIO_setPinConfig(myPWM1_PWMA_PIN_CONFIG);
    GPIO_setDrivingCapability(myPWM1_PWMA_GPIO,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(myPWM1_PWMA_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myPWM1_PWMA_GPIO, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(myPWM1_PWMB_PIN_CONFIG);
    GPIO_setDrivingCapability(myPWM1_PWMB_GPIO,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(myPWM1_PWMB_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myPWM1_PWMB_GPIO, GPIO_QUAL_SYNC);

    //
    // PWM2 -> myPWM2 Pinmux
    //
    GPIO_setPinConfig(myPWM2_PWMA_PIN_CONFIG);
    GPIO_setDrivingCapability(myPWM2_PWMA_GPIO,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(myPWM2_PWMA_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myPWM2_PWMA_GPIO, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(myPWM2_PWMB_PIN_CONFIG);
    GPIO_setDrivingCapability(myPWM2_PWMB_GPIO,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(myPWM2_PWMB_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myPWM2_PWMB_GPIO, GPIO_QUAL_SYNC);

    //
    // PWM3 -> myPWM3 Pinmux
    //
    GPIO_setPinConfig(myPWM3_PWMA_PIN_CONFIG);
    GPIO_setDrivingCapability(myPWM3_PWMA_GPIO,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(myPWM3_PWMA_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myPWM3_PWMA_GPIO, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(myPWM3_PWMB_PIN_CONFIG);
    GPIO_setDrivingCapability(myPWM3_PWMB_GPIO,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(myPWM3_PWMB_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myPWM3_PWMB_GPIO, GPIO_QUAL_SYNC);

    // GPIO6 -> myGPIO6 Pinmux
    GPIO_setPinConfig(GPIO_6_GPIO6);

}

//*****************************************************************************
//
// COMP Configurations
//
//*****************************************************************************
void COMP_init()
{
    //
    // Select the value for CMP1HPMXSEL.
    //
    AS_selectCMPHPMux(AS_CMPHPMUX_SELECT_1,0U);
    //
    // Select the value for CMP1LPMXSEL.
    //
    AS_selectCMPLPMux(AS_CMPLPMUX_SELECT_1,0U);
    //
    // Sets the configuration for the high comparator.
    //
    COMP_configHighComparator(myCOMP1_BASE,(COMP_INSRC_DAC));
    //
    // Sets the configuration for the low comparator.
    //
    COMP_configLowComparator(myCOMP1_BASE,(COMP_INSRC_DAC));
    //
    // Sets the configuration for the internal comparator DACs.
    //
    COMP_configDAC(myCOMP1_BASE,(COMP_DACVAL_SYSCLK | COMP_DACREF_VDDA | COMP_DACSRC_SHDW));
    //
    // Sets the value of the internal DAC of the high comparator.
    //
    COMP_setDACValueHigh(myCOMP1_BASE,2500U);
    //
    // Sets the value of the internal DAC of the low comparator.
    //
    COMP_setDACValueLow(myCOMP1_BASE,0U);
    //
    //  Configures the digital filter of the high comparator.
    //
    COMP_configFilterHigh(myCOMP1_BASE, 0U, 1U, 1U);
    //
    // Configures the digital filter of the low comparator.
    //
    COMP_configFilterLow(myCOMP1_BASE, 0U, 1U, 1U);
    //
    // Sets the output signal configuration for the high comparator.
    //
    COMP_configOutputsHigh(myCOMP1_BASE,(COMP_TRIPOUT_ASYNC_COMP | COMP_TRIP_ASYNC_COMP));
    //
    // Sets the output signal configuration for the low comparator.
    //
    COMP_configOutputsLow(myCOMP1_BASE,(COMP_TRIPOUT_ASYNC_COMP | COMP_TRIP_ASYNC_COMP));
    //
    // Sets the comparator hysteresis settings.
    //
    COMP_setHysteresis(myCOMP1_BASE,0U);
    //
    // Configures the comparator subsystem's ramp generator.
    //
    COMP_configRamp(myCOMP1_BASE,0U,0U,0U,1U,true);
    //
    // Disables reset of HIGH comparator digital filter output latch on PWMSYNC
    //
    COMP_disableLatchResetOnPWMSYNCHigh(myCOMP1_BASE);
    //
    // Disables reset of LOW comparator digital filter output latch on PWMSYNC
    //
    COMP_disableLatchResetOnPWMSYNCLow(myCOMP1_BASE);
    //
    // Sets the ePWM module blanking signal that holds trip in reset.
    //
    COMP_configBlanking(myCOMP1_BASE,1U);
    //
    // Disables an ePWM blanking signal from holding trip in reset.
    //
    COMP_disableBlanking(myCOMP1_BASE);
    //
    // Configures whether or not the digital filter latches are reset by PWMSYNC
    //
    COMP_configLatchOnPWMSYNC(myCOMP1_BASE,false,false);
    //
    // Enables the COMP module.
    //
    COMP_enableModule(myCOMP1_BASE);
    //
    // Delay for COMP DAC to power up.
    //
    DEVICE_DELAY_US(500);
}

//*****************************************************************************
//
// PWM Configurations
//
//*****************************************************************************
void PWM_init()
{
    PWM_enableGlobalLoad(myPWM1_BASE);
    PWM_enableGlobalLoadOneShotMode(myPWM1_BASE);
    PWM_setGlobalLoadOneShotLatch(myPWM1_BASE);
    PWM_setClockPrescaler(myPWM1_BASE, PWM_CLOCK_DIVIDER_1, PWM_HSCLOCK_DIVIDER_1);
    PWM_setTimeBasePeriod(myPWM1_BASE, 125);
    PWM_setTimeBaseCounter(myPWM1_BASE, 0);
    PWM_setTimeBaseCounterMode(myPWM1_BASE, PWM_COUNTER_MODE_UP_DOWN);
    PWM_disablePhaseShiftLoad(myPWM1_BASE);
    PWM_setPhaseShift(myPWM1_BASE, 0);
    PWM_setSyncOutPulseMode(myPWM1_BASE, PWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);
    PWM_setCounterCompareValue(myPWM1_BASE, PWM_COUNTER_COMPARE_A, 69);
    PWM_enableGlobalLoadRegisters(myPWM1_BASE, PWM_GL_REGISTER_CMPA_CMPAHR);
    PWM_setCounterCompareShadowLoadMode(myPWM1_BASE, PWM_COUNTER_COMPARE_A, PWM_COMP_LOAD_ON_CNTR_ZERO);
    PWM_setCounterCompareValue(myPWM1_BASE, PWM_COUNTER_COMPARE_B, 69);
    PWM_enableGlobalLoadRegisters(myPWM1_BASE, PWM_GL_REGISTER_CMPB_CMPBHR);
    PWM_setCounterCompareShadowLoadMode(myPWM1_BASE, PWM_COUNTER_COMPARE_B, PWM_COMP_LOAD_ON_CNTR_ZERO);
    PWM_enableGlobalLoadRegisters(myPWM1_BASE, PWM_GL_REGISTER_AQCTLA_AQCTLA2);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    PWM_enableGlobalLoadRegisters(myPWM1_BASE, PWM_GL_REGISTER_AQCTLB_AQCTLB2);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    PWM_setDeadBandDelayPolarity(myPWM1_BASE, PWM_DB_FED, PWM_DB_POLARITY_ACTIVE_LOW);
    PWM_setDeadBandDelayMode(myPWM1_BASE, PWM_DB_RED, true);
    PWM_setRisingEdgeDelayCountShadowLoadMode(myPWM1_BASE, PWM_RED_LOAD_ON_CNTR_ZERO);
    PWM_disableRisingEdgeDelayCountShadowLoadMode(myPWM1_BASE);
    PWM_setRisingEdgeDelayCount(myPWM1_BASE, 20);
    PWM_setDeadBandDelayMode(myPWM1_BASE, PWM_DB_FED, true);
    PWM_setFallingEdgeDelayCountShadowLoadMode(myPWM1_BASE, PWM_FED_LOAD_ON_CNTR_ZERO);
    PWM_disableFallingEdgeDelayCountShadowLoadMode(myPWM1_BASE);
    PWM_setFallingEdgeDelayCount(myPWM1_BASE, 20);
    PWM_enableInterrupt(myPWM1_BASE);
    PWM_setInterruptSource(myPWM1_BASE, PWM_INT_TBCTR_ZERO);
    PWM_setInterruptEventCount(myPWM1_BASE, 1);

    PWM_enableGlobalLoad(myPWM2_BASE);
    PWM_enableGlobalLoadOneShotMode(myPWM2_BASE);
    PWM_setGlobalLoadOneShotLatch(myPWM2_BASE);
    PWM_forceGlobalLoadOneShotEvent(myPWM2_BASE);
    PWM_setupPWMLinks(myPWM2_BASE, PWM_LINK_WITH_PWM_1, PWM_LINK_GLDCTL2);
    PWM_setClockPrescaler(myPWM2_BASE, PWM_CLOCK_DIVIDER_1, PWM_HSCLOCK_DIVIDER_1);
    PWM_setTimeBasePeriod(myPWM2_BASE, 125);
    PWM_setTimeBaseCounter(myPWM2_BASE, 0);
    PWM_setTimeBaseCounterMode(myPWM2_BASE, PWM_COUNTER_MODE_UP_DOWN);
    PWM_enablePhaseShiftLoad(myPWM2_BASE);
    PWM_setPhaseShift(myPWM2_BASE, 42);
    PWM_setSyncOutPulseMode(myPWM2_BASE, PWM_SYNC_OUT_PULSE_ON_PWMxSYNCIN);
    PWM_setCounterCompareValue(myPWM2_BASE, PWM_COUNTER_COMPARE_A, 69);
    PWM_enableGlobalLoadRegisters(myPWM2_BASE, PWM_GL_REGISTER_CMPA_CMPAHR);
    PWM_setCounterCompareShadowLoadMode(myPWM2_BASE, PWM_COUNTER_COMPARE_A, PWM_COMP_LOAD_ON_CNTR_ZERO);
    PWM_setupPWMLinks(myPWM2_BASE, PWM_LINK_WITH_PWM_1, PWM_LINK_COMP_A);
    PWM_setCounterCompareValue(myPWM2_BASE, PWM_COUNTER_COMPARE_B, 69);
    PWM_enableGlobalLoadRegisters(myPWM2_BASE, PWM_GL_REGISTER_CMPB_CMPBHR);
    PWM_setCounterCompareShadowLoadMode(myPWM2_BASE, PWM_COUNTER_COMPARE_B, PWM_COMP_LOAD_ON_CNTR_ZERO);
    PWM_setupPWMLinks(myPWM2_BASE, PWM_LINK_WITH_PWM_1, PWM_LINK_COMP_B);
    PWM_enableGlobalLoadRegisters(myPWM2_BASE, PWM_GL_REGISTER_AQCTLA_AQCTLA2);
    PWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    PWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    PWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    PWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    PWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    PWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    PWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    PWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    PWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    PWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    PWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    PWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    PWM_setDeadBandDelayPolarity(myPWM2_BASE, PWM_DB_FED, PWM_DB_POLARITY_ACTIVE_LOW);
    PWM_setDeadBandDelayMode(myPWM2_BASE, PWM_DB_RED, true);
    PWM_setRisingEdgeDelayCountShadowLoadMode(myPWM2_BASE, PWM_RED_LOAD_ON_CNTR_ZERO);
    PWM_disableRisingEdgeDelayCountShadowLoadMode(myPWM2_BASE);
    PWM_setRisingEdgeDelayCount(myPWM2_BASE, 20);
    PWM_setDeadBandDelayMode(myPWM2_BASE, PWM_DB_FED, true);
    PWM_setFallingEdgeDelayCountShadowLoadMode(myPWM2_BASE, PWM_FED_LOAD_ON_CNTR_ZERO);
    PWM_disableFallingEdgeDelayCountShadowLoadMode(myPWM2_BASE);
    PWM_setFallingEdgeDelayCount(myPWM2_BASE, 20);
    PWM_setTripZoneAction(myPWM2_BASE, PWM_TZ_ACTION_EVENT_TZA, PWM_TZ_ACTION_LOW);
    PWM_setTripZoneAction(myPWM2_BASE, PWM_TZ_ACTION_EVENT_TZB, PWM_TZ_ACTION_LOW);
    PWM_enableTripZoneSignals(myPWM2_BASE, PWM_TZ_SIGNAL_DCAEVT2);
    PWM_enableTripZoneInterrupt(myPWM2_BASE, PWM_TZ_INTERRUPT_CBC);
    PWM_selectDigitalCompareTripInput(myPWM2_BASE, PWM_DC_TRIP_TRIPIN4, PWM_DC_TYPE_DCAH);
    PWM_setTripZoneDigitalCompareEventCondition(myPWM2_BASE, PWM_TZ_DC_OUTPUT_A2, PWM_TZ_EVENT_DCXH_HIGH);

    PWM_enableGlobalLoad(myPWM3_BASE);
    PWM_enableGlobalLoadOneShotMode(myPWM3_BASE);
    PWM_setGlobalLoadOneShotLatch(myPWM3_BASE);
    PWM_forceGlobalLoadOneShotEvent(myPWM3_BASE);
    PWM_setupPWMLinks(myPWM3_BASE, PWM_LINK_WITH_PWM_1, PWM_LINK_GLDCTL2);
    PWM_setClockPrescaler(myPWM3_BASE, PWM_CLOCK_DIVIDER_1, PWM_HSCLOCK_DIVIDER_1);
    PWM_setTimeBasePeriod(myPWM3_BASE, 125);
    PWM_setTimeBaseCounter(myPWM3_BASE, 0);
    PWM_setTimeBaseCounterMode(myPWM3_BASE, PWM_COUNTER_MODE_UP_DOWN);
    PWM_enablePhaseShiftLoad(myPWM3_BASE);
    PWM_setPhaseShift(myPWM3_BASE, 83);
    PWM_setSyncOutPulseMode(myPWM3_BASE, PWM_SYNC_OUT_PULSE_ON_PWMxSYNCIN);
    PWM_setCounterCompareValue(myPWM3_BASE, PWM_COUNTER_COMPARE_A, 69);
    PWM_enableGlobalLoadRegisters(myPWM3_BASE, PWM_GL_REGISTER_CMPA_CMPAHR);
    PWM_setCounterCompareShadowLoadMode(myPWM3_BASE, PWM_COUNTER_COMPARE_A, PWM_COMP_LOAD_ON_CNTR_ZERO);
    PWM_setupPWMLinks(myPWM3_BASE, PWM_LINK_WITH_PWM_1, PWM_LINK_COMP_A);
    PWM_setCounterCompareValue(myPWM3_BASE, PWM_COUNTER_COMPARE_B, 69);
    PWM_enableGlobalLoadRegisters(myPWM3_BASE, PWM_GL_REGISTER_CMPB_CMPBHR);
    PWM_setCounterCompareShadowLoadMode(myPWM3_BASE, PWM_COUNTER_COMPARE_B, PWM_COMP_LOAD_ON_CNTR_ZERO);
    PWM_setupPWMLinks(myPWM3_BASE, PWM_LINK_WITH_PWM_1, PWM_LINK_COMP_B);
    PWM_enableGlobalLoadRegisters(myPWM3_BASE, PWM_GL_REGISTER_AQCTLA_AQCTLA2);
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    PWM_setDeadBandDelayPolarity(myPWM3_BASE, PWM_DB_FED, PWM_DB_POLARITY_ACTIVE_LOW);
    PWM_setDeadBandDelayMode(myPWM3_BASE, PWM_DB_RED, true);
    PWM_setRisingEdgeDelayCountShadowLoadMode(myPWM3_BASE, PWM_RED_LOAD_ON_CNTR_ZERO);
    PWM_disableRisingEdgeDelayCountShadowLoadMode(myPWM3_BASE);
    PWM_setRisingEdgeDelayCount(myPWM3_BASE, 20);
    PWM_setDeadBandDelayMode(myPWM3_BASE, PWM_DB_FED, true);
    PWM_setFallingEdgeDelayCountShadowLoadMode(myPWM3_BASE, PWM_FED_LOAD_ON_CNTR_ZERO);
    PWM_disableFallingEdgeDelayCountShadowLoadMode(myPWM3_BASE);
    PWM_setFallingEdgeDelayCount(myPWM3_BASE, 20);
    PWM_setTripZoneAction(myPWM3_BASE, PWM_TZ_ACTION_EVENT_TZA, PWM_TZ_ACTION_LOW);
    PWM_setTripZoneAction(myPWM3_BASE, PWM_TZ_ACTION_EVENT_TZB, PWM_TZ_ACTION_LOW);
    PWM_enableTripZoneSignals(myPWM3_BASE, PWM_TZ_SIGNAL_OSHT1);
    PWM_enableTripZoneInterrupt(myPWM3_BASE, PWM_TZ_INTERRUPT_OST);
}

//*****************************************************************************
//
// PWMXBAR Configurations
//
//*****************************************************************************
void PWMXBAR_init()
{
    XBAR_setPWMMuxConfig(myPWMXBAR4, XBAR_PWM_MUX00_COMP1_CTRIPH);
    XBAR_enablePWMMux(myPWMXBAR4, XBAR_MUX00);
}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init()
{
    GPIO_writePin(myGPIO6, 1);
    GPIO_setPadConfig(myGPIO6, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myGPIO6, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(myGPIO6, GPIO_DIR_MODE_IN);
    GPIO_setMasterCore(myGPIO6, GPIO_CORE_CPU0);
}


//*****************************************************************************
//
// INPUTXBAR Configurations
//
//*****************************************************************************
void INPUTXBAR_init()
{
    XBAR_setInputPin(myINPUTXBARINPUT0_INPUT, myINPUTXBARINPUT0_SOURCE);
    XBAR_lockInput(myINPUTXBARINPUT0_INPUT);
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init()
{
    // Interrupt Settings for INT_myPWM1_TZ
    Interrupt_register(INT_myPWM1_TZ, &INT_PWM1_IRQHandler);
    Interrupt_enable(INT_myPWM1_TZ);

    // Interrupt Settings for INT_myPWM2_TZ
    Interrupt_register(INT_myPWM2_TZ, &INT_PWM2_IRQHandler);
    Interrupt_enable(INT_myPWM2_TZ);

    // Interrupt Settings for INT_myPWM3_TZ
    Interrupt_register(INT_myPWM3_TZ, &INT_PWM3_IRQHandler);
    Interrupt_enable(INT_myPWM3_TZ);
}
//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************
void SYNC_init()
{
    SysCtl_setSyncOutputConfig(SYSCTL_SYNC_OUT_SRC_PWM1SYNCOUT);
    //
    // For PWM1, the sync input is: SYSCTL_SYNC_IN_SRC_EXTSYNCIN1
    //
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_PWM4, SYSCTL_SYNC_IN_SRC_PWM1SYNCOUT);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_PWM7, SYSCTL_SYNC_IN_SRC_PWM1SYNCOUT);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_CAP1, SYSCTL_SYNC_IN_SRC_PWM1SYNCOUT);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_CAP4, SYSCTL_SYNC_IN_SRC_PWM1SYNCOUT);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_CAP6, SYSCTL_SYNC_IN_SRC_PWM1SYNCOUT);
    //
    // SOCA
    //
    SysCtl_enableExtADCSOCSource(0);
    //
    // SOCB
    //
    SysCtl_enableExtADCSOCSource(0);
}

