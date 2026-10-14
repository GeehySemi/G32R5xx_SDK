//#############################################################################
//
// FILE:    board.c
//
// TITLE:   Board source file
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
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
// 1. Modified function names and macro definition names.
// - 2026-08-18:
// 1. Recalculated PWM1/2/3 TBPRD, CMP, dead-band and phase for 500 kHz at 200 MHz AHB.
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
    // G32R502 EVAL analog pins
    //
    // A0 / DACA_OUT - AIO231
    GPIO_setPinConfig(GPIO_231_GPIO231);
    GPIO_setAnalogMode(231, GPIO_ANALOG_ENABLED);
    // A1 / DACB_OUT - AIO232
    GPIO_setPinConfig(GPIO_232_GPIO232);
    GPIO_setAnalogMode(232, GPIO_ANALOG_ENABLED);
    // C7 - AIO233
    GPIO_setPinConfig(GPIO_233_GPIO233);
    GPIO_setAnalogMode(233, GPIO_ANALOG_ENABLED);
    // A3 / C5 - GPIO242
    GPIO_setPinConfig(GPIO_242_GPIO242);
    GPIO_setAnalogMode(242, GPIO_ANALOG_ENABLED);
    // A4 / C14 - AIO225
    GPIO_setPinConfig(GPIO_225_GPIO225);
    GPIO_setAnalogMode(225, GPIO_ANALOG_ENABLED);
    // A5 / C2 - AIO244
    GPIO_setPinConfig(GPIO_244_GPIO244);
    GPIO_setAnalogMode(244, GPIO_ANALOG_ENABLED);
    // A6 - GPIO228
    GPIO_setPinConfig(GPIO_228_GPIO228);
    GPIO_setAnalogMode(228, GPIO_ANALOG_ENABLED);
    // A7 / C3 - AIO245
    GPIO_setPinConfig(GPIO_245_GPIO245);
    GPIO_setAnalogMode(245, GPIO_ANALOG_ENABLED);
    // A8 / C11 - AIO241
    GPIO_setPinConfig(GPIO_241_GPIO241);
    GPIO_setAnalogMode(241, GPIO_ANALOG_ENABLED);
    // A9 / C8 - GPIO227
    GPIO_setPinConfig(GPIO_227_GPIO227);
    GPIO_setAnalogMode(227, GPIO_ANALOG_ENABLED);
    // A10 / C10 - GPIO230
    GPIO_setPinConfig(GPIO_230_GPIO230);
    GPIO_setAnalogMode(230, GPIO_ANALOG_ENABLED);
    // A11 - AIO237
    GPIO_setPinConfig(GPIO_237_GPIO237);
    GPIO_setAnalogMode(237, GPIO_ANALOG_ENABLED);
    // A12 / C1 - AIO238
    GPIO_setPinConfig(GPIO_238_GPIO238);
    GPIO_setAnalogMode(238, GPIO_ANALOG_ENABLED);
    // A14 - AIO239
    GPIO_setPinConfig(GPIO_239_GPIO239);
    GPIO_setAnalogMode(239, GPIO_ANALOG_ENABLED);
    // A15 - GPIO21
    GPIO_setPinConfig(GPIO_21_GPIO21);
    GPIO_setAnalogMode(21, GPIO_ANALOG_ENABLED);
    // C4 - GPIO13
    GPIO_setPinConfig(GPIO_13_GPIO13);
    GPIO_setAnalogMode(13, GPIO_ANALOG_ENABLED);
    // C0 - GPIO20
    GPIO_setPinConfig(GPIO_20_GPIO20);
    GPIO_setAnalogMode(20, GPIO_ANALOG_ENABLED);
    // C6 - GPIO226
    GPIO_setPinConfig(GPIO_226_GPIO226);
    GPIO_setAnalogMode(226, GPIO_ANALOG_ENABLED);
    // C9 - GPIO224
    GPIO_setPinConfig(GPIO_224_GPIO224);
    GPIO_setAnalogMode(224, GPIO_ANALOG_ENABLED);
    // C15 - GPIO12
    GPIO_setPinConfig(GPIO_12_GPIO12);
    GPIO_setAnalogMode(12, GPIO_ANALOG_ENABLED);

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
    COMP_configDAC(myCOMP1_BASE,(COMP_DACVAL_SYSCLK | COMP_DACSRC_SHDW));
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
    // AHB 200 MHz, up-down, /1: TBPRD = 200000000 / (2 * 500000) = 200 -> 500 kHz
    PWM_setTimeBasePeriod(myPWM1_BASE, 200);
    PWM_setTimeBaseCounter(myPWM1_BASE, 0);
    PWM_setTimeBaseCounterMode(myPWM1_BASE, PWM_COUNTER_MODE_UP_DOWN);
    PWM_disablePhaseShiftLoad(myPWM1_BASE);
    PWM_setPhaseShift(myPWM1_BASE, 0);
    PWM_setSyncOutPulseMode(myPWM1_BASE, PWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);
    PWM_setCounterCompareValue(myPWM1_BASE, PWM_COUNTER_COMPARE_A, 110);
    PWM_enableGlobalLoadRegisters(myPWM1_BASE, PWM_GL_REGISTER_CMPA_CMPAHR);
    PWM_setCounterCompareShadowLoadMode(myPWM1_BASE, PWM_COUNTER_COMPARE_A, PWM_COMP_LOAD_ON_CNTR_ZERO);
    PWM_setCounterCompareValue(myPWM1_BASE, PWM_COUNTER_COMPARE_B, 110);
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
    PWM_setRisingEdgeDelayCount(myPWM1_BASE, 40);
    PWM_setDeadBandDelayMode(myPWM1_BASE, PWM_DB_FED, true);
    PWM_setFallingEdgeDelayCountShadowLoadMode(myPWM1_BASE, PWM_FED_LOAD_ON_CNTR_ZERO);
    PWM_disableFallingEdgeDelayCountShadowLoadMode(myPWM1_BASE);
    PWM_setFallingEdgeDelayCount(myPWM1_BASE, 40);
    PWM_enableInterrupt(myPWM1_BASE);
    PWM_setInterruptSource(myPWM1_BASE, PWM_INT_TBCTR_ZERO);
    PWM_setInterruptEventCount(myPWM1_BASE, 1);

    PWM_enableGlobalLoad(myPWM2_BASE);
    PWM_enableGlobalLoadOneShotMode(myPWM2_BASE);
    PWM_setGlobalLoadOneShotLatch(myPWM2_BASE);
    PWM_forceGlobalLoadOneShotEvent(myPWM2_BASE);
    PWM_setupPWMLinks(myPWM2_BASE, PWM_LINK_WITH_PWM_1, PWM_LINK_GLDCTL2);
    PWM_setClockPrescaler(myPWM2_BASE, PWM_CLOCK_DIVIDER_1, PWM_HSCLOCK_DIVIDER_1);
    PWM_setTimeBasePeriod(myPWM2_BASE, 200);
    PWM_setTimeBaseCounter(myPWM2_BASE, 0);
    PWM_setTimeBaseCounterMode(myPWM2_BASE, PWM_COUNTER_MODE_UP_DOWN);
    PWM_enablePhaseShiftLoad(myPWM2_BASE);
    PWM_setPhaseShift(myPWM2_BASE, 67);
    PWM_setSyncOutPulseMode(myPWM2_BASE, PWM_SYNC_OUT_PULSE_ON_PWMxSYNCIN);
    PWM_setCounterCompareValue(myPWM2_BASE, PWM_COUNTER_COMPARE_A, 110);
    PWM_enableGlobalLoadRegisters(myPWM2_BASE, PWM_GL_REGISTER_CMPA_CMPAHR);
    PWM_setCounterCompareShadowLoadMode(myPWM2_BASE, PWM_COUNTER_COMPARE_A, PWM_COMP_LOAD_ON_CNTR_ZERO);
    PWM_setupPWMLinks(myPWM2_BASE, PWM_LINK_WITH_PWM_1, PWM_LINK_COMP_A);
    PWM_setCounterCompareValue(myPWM2_BASE, PWM_COUNTER_COMPARE_B, 110);
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
    PWM_setRisingEdgeDelayCount(myPWM2_BASE, 40);
    PWM_setDeadBandDelayMode(myPWM2_BASE, PWM_DB_FED, true);
    PWM_setFallingEdgeDelayCountShadowLoadMode(myPWM2_BASE, PWM_FED_LOAD_ON_CNTR_ZERO);
    PWM_disableFallingEdgeDelayCountShadowLoadMode(myPWM2_BASE);
    PWM_setFallingEdgeDelayCount(myPWM2_BASE, 40);
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
    PWM_setTimeBasePeriod(myPWM3_BASE, 200);
    PWM_setTimeBaseCounter(myPWM3_BASE, 0);
    PWM_setTimeBaseCounterMode(myPWM3_BASE, PWM_COUNTER_MODE_UP_DOWN);
    PWM_enablePhaseShiftLoad(myPWM3_BASE);
    PWM_setPhaseShift(myPWM3_BASE, 133);
    PWM_setSyncOutPulseMode(myPWM3_BASE, PWM_SYNC_OUT_PULSE_ON_PWMxSYNCIN);
    PWM_setCounterCompareValue(myPWM3_BASE, PWM_COUNTER_COMPARE_A, 110);
    PWM_enableGlobalLoadRegisters(myPWM3_BASE, PWM_GL_REGISTER_CMPA_CMPAHR);
    PWM_setCounterCompareShadowLoadMode(myPWM3_BASE, PWM_COUNTER_COMPARE_A, PWM_COMP_LOAD_ON_CNTR_ZERO);
    PWM_setupPWMLinks(myPWM3_BASE, PWM_LINK_WITH_PWM_1, PWM_LINK_COMP_A);
    PWM_setCounterCompareValue(myPWM3_BASE, PWM_COUNTER_COMPARE_B, 110);
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
    PWM_setRisingEdgeDelayCount(myPWM3_BASE, 40);
    PWM_setDeadBandDelayMode(myPWM3_BASE, PWM_DB_FED, true);
    PWM_setFallingEdgeDelayCountShadowLoadMode(myPWM3_BASE, PWM_FED_LOAD_ON_CNTR_ZERO);
    PWM_disableFallingEdgeDelayCountShadowLoadMode(myPWM3_BASE);
    PWM_setFallingEdgeDelayCount(myPWM3_BASE, 40);
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

    //
    // SOCA
    //
    SysCtl_enableExtADCSOCSource(0);
    //
    // SOCB
    //
    SysCtl_enableExtADCSOCSource(0);
}

