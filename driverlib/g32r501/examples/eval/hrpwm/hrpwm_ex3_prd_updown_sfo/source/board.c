//###########################################################################
//
// FILE:    board.c
//
// TITLE:   Board source file.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//###########################################################################
// $Copyright:
// Copyright (C) 2024 Geehy Semiconductor - http://www.geehy.com/
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
    PWM_init();

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
    // PWM1 -> myPWM1 Pinmux
    //
    GPIO_setPinConfig(GPIO_0_PWM1_A);
    GPIO_setPinConfig(GPIO_1_PWM1_B);
    //
    // PWM2 -> myPWM2 Pinmux
    //
    GPIO_setPinConfig(GPIO_2_PWM2_A);
    GPIO_setPinConfig(GPIO_3_PWM2_B);
    //
    // PWM3 -> myPWM3 Pinmux
    //
    GPIO_setPinConfig(GPIO_4_PWM3_A);
    GPIO_setPinConfig(GPIO_5_PWM3_B);
    //
    // PWM4 -> myPWM4 Pinmux
    //
    GPIO_setPinConfig(GPIO_6_PWM4_A);
    GPIO_setPinConfig(GPIO_7_PWM4_B);

}

//*****************************************************************************
//
// PWM Configurations
//
//*****************************************************************************
void PWM_init()
{
    HRPWM_setClockPrescaler(myPWM1_BASE, PWM_CLOCK_DIVIDER_1, PWM_HSCLOCK_DIVIDER_1);
    PWM_setTimeBasePeriod(myPWM1_BASE, 20);
    HRPWM_setTimeBaseCounter(myPWM1_BASE, 0);
    HRPWM_setTimeBaseCounterMode(myPWM1_BASE, PWM_COUNTER_MODE_UP_DOWN);
    HRPWM_disablePhaseShiftLoad(myPWM1_BASE);
    HRPWM_setPhaseShift(myPWM1_BASE, 0);
    HRPWM_setSyncOutPulseMode(myPWM1_BASE, PWM_SYNC_OUT_PULSE_DISABLED);
    PWM_forceSyncPulse(myPWM1_BASE);
    PWM_setCounterCompareValue(myPWM1_BASE, PWM_COUNTER_COMPARE_A, 10);
    HRPWM_setCounterCompareShadowLoadMode(myPWM1_BASE, PWM_COUNTER_COMPARE_A, PWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);
    PWM_setCounterCompareValue(myPWM1_BASE, PWM_COUNTER_COMPARE_B, 10);
    HRPWM_setCounterCompareShadowLoadMode(myPWM1_BASE, PWM_COUNTER_COMPARE_B, PWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_enableAutoConversion(myPWM1_BASE);
    HRPWM_setMEPEdgeSelect(myPWM1_BASE, HRPWM_CHANNEL_A, HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE);
    HRPWM_setCounterCompareShadowLoadEvent(myPWM1_BASE, HRPWM_CHANNEL_A, HRPWM_LOAD_ON_CNTR_ZERO_PERIOD);
    HRPWM_setMEPEdgeSelect(myPWM1_BASE, HRPWM_CHANNEL_B, HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE);
    HRPWM_setCounterCompareShadowLoadEvent(myPWM1_BASE, HRPWM_CHANNEL_B, HRPWM_LOAD_ON_CNTR_ZERO_PERIOD);
    HRPWM_enablePeriodControl(myPWM1_BASE);
    HRPWM_setClockPrescaler(myPWM2_BASE, PWM_CLOCK_DIVIDER_1, PWM_HSCLOCK_DIVIDER_1);
    PWM_setTimeBasePeriod(myPWM2_BASE, 20);
    HRPWM_setTimeBaseCounter(myPWM2_BASE, 0);
    HRPWM_setTimeBaseCounterMode(myPWM2_BASE, PWM_COUNTER_MODE_UP_DOWN);
    HRPWM_disablePhaseShiftLoad(myPWM2_BASE);
    HRPWM_setPhaseShift(myPWM2_BASE, 0);
    HRPWM_setSyncOutPulseMode(myPWM2_BASE, PWM_SYNC_OUT_PULSE_DISABLED);
    PWM_forceSyncPulse(myPWM2_BASE);
    PWM_setCounterCompareValue(myPWM2_BASE, PWM_COUNTER_COMPARE_A, 10);
    HRPWM_setCounterCompareShadowLoadMode(myPWM2_BASE, PWM_COUNTER_COMPARE_A, PWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);
    PWM_setCounterCompareValue(myPWM2_BASE, PWM_COUNTER_COMPARE_B, 10);
    HRPWM_setCounterCompareShadowLoadMode(myPWM2_BASE, PWM_COUNTER_COMPARE_B, PWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_enableAutoConversion(myPWM2_BASE);
    HRPWM_setMEPEdgeSelect(myPWM2_BASE, HRPWM_CHANNEL_A, HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE);
    HRPWM_setCounterCompareShadowLoadEvent(myPWM2_BASE, HRPWM_CHANNEL_A, HRPWM_LOAD_ON_CNTR_ZERO_PERIOD);
    HRPWM_setMEPEdgeSelect(myPWM2_BASE, HRPWM_CHANNEL_B, HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE);
    HRPWM_setCounterCompareShadowLoadEvent(myPWM2_BASE, HRPWM_CHANNEL_B, HRPWM_LOAD_ON_CNTR_ZERO_PERIOD);
    HRPWM_enablePeriodControl(myPWM2_BASE);
    HRPWM_setClockPrescaler(myPWM3_BASE, PWM_CLOCK_DIVIDER_1, PWM_HSCLOCK_DIVIDER_1);
    PWM_setTimeBasePeriod(myPWM3_BASE, 20);
    HRPWM_setTimeBaseCounter(myPWM3_BASE, 0);
    HRPWM_setTimeBaseCounterMode(myPWM3_BASE, PWM_COUNTER_MODE_UP_DOWN);
    HRPWM_disablePhaseShiftLoad(myPWM3_BASE);
    HRPWM_setPhaseShift(myPWM3_BASE, 0);
    HRPWM_setSyncOutPulseMode(myPWM3_BASE, PWM_SYNC_OUT_PULSE_DISABLED);
    PWM_forceSyncPulse(myPWM3_BASE);
    PWM_setCounterCompareValue(myPWM3_BASE, PWM_COUNTER_COMPARE_A, 10);
    HRPWM_setCounterCompareShadowLoadMode(myPWM3_BASE, PWM_COUNTER_COMPARE_A, PWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);
    PWM_setCounterCompareValue(myPWM3_BASE, PWM_COUNTER_COMPARE_B, 10);
    HRPWM_setCounterCompareShadowLoadMode(myPWM3_BASE, PWM_COUNTER_COMPARE_B, PWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);
    HRPWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_enableAutoConversion(myPWM3_BASE);
    HRPWM_setMEPEdgeSelect(myPWM3_BASE, HRPWM_CHANNEL_A, HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE);
    HRPWM_setCounterCompareShadowLoadEvent(myPWM3_BASE, HRPWM_CHANNEL_A, HRPWM_LOAD_ON_CNTR_ZERO_PERIOD);
    HRPWM_setMEPEdgeSelect(myPWM3_BASE, HRPWM_CHANNEL_B, HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE);
    HRPWM_setCounterCompareShadowLoadEvent(myPWM3_BASE, HRPWM_CHANNEL_B, HRPWM_LOAD_ON_CNTR_ZERO_PERIOD);
    HRPWM_enablePeriodControl(myPWM3_BASE);
    HRPWM_setClockPrescaler(myPWM4_BASE, PWM_CLOCK_DIVIDER_1, PWM_HSCLOCK_DIVIDER_1);
    PWM_setTimeBasePeriod(myPWM4_BASE, 20);
    HRPWM_setTimeBaseCounter(myPWM4_BASE, 0);
    HRPWM_setTimeBaseCounterMode(myPWM4_BASE, PWM_COUNTER_MODE_UP_DOWN);
    HRPWM_disablePhaseShiftLoad(myPWM4_BASE);
    HRPWM_setPhaseShift(myPWM4_BASE, 0);
    HRPWM_setSyncOutPulseMode(myPWM4_BASE, PWM_SYNC_OUT_PULSE_DISABLED);
    PWM_forceSyncPulse(myPWM4_BASE);
    PWM_setCounterCompareValue(myPWM4_BASE, PWM_COUNTER_COMPARE_A, 10);
    HRPWM_setCounterCompareShadowLoadMode(myPWM4_BASE, PWM_COUNTER_COMPARE_A, PWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);
    PWM_setCounterCompareValue(myPWM4_BASE, PWM_COUNTER_COMPARE_B, 10);
    HRPWM_setCounterCompareShadowLoadMode(myPWM4_BASE, PWM_COUNTER_COMPARE_B, PWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);
    HRPWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_enableAutoConversion(myPWM4_BASE);
    HRPWM_setMEPEdgeSelect(myPWM4_BASE, HRPWM_CHANNEL_A, HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE);
    HRPWM_setCounterCompareShadowLoadEvent(myPWM4_BASE, HRPWM_CHANNEL_A, HRPWM_LOAD_ON_CNTR_ZERO_PERIOD);
    HRPWM_setMEPEdgeSelect(myPWM4_BASE, HRPWM_CHANNEL_B, HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE);
    HRPWM_setCounterCompareShadowLoadEvent(myPWM4_BASE, HRPWM_CHANNEL_B, HRPWM_LOAD_ON_CNTR_ZERO_PERIOD);
    HRPWM_enablePeriodControl(myPWM4_BASE);
}

//*****************************************************************************
//
// INPUTXBAR Configurations
//
//*****************************************************************************
void INPUTXBAR_init()
{
    //myINPUTXBAR5 initialization
    XBAR_setInputPin(XBAR_INPUT5, 40);
    XBAR_setInputPin(XBAR_INPUT6, 40);
}

//*****************************************************************************
//
// SYNC Configurations
//
//*****************************************************************************
void SYNC_init()
{
    SysCtl_setSyncOutputConfig(SYSCTL_SYNC_OUT_SRC_PWM1SYNCOUT);
    // For PWM1, the sync input is: SYSCTL_SYNC_IN_SRC_EXTSYNCIN1
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_PWM4, SYSCTL_SYNC_IN_SRC_PWM1SYNCOUT);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_PWM7, SYSCTL_SYNC_IN_SRC_PWM1SYNCOUT);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_CAP1, SYSCTL_SYNC_IN_SRC_PWM1SYNCOUT);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_CAP4, SYSCTL_SYNC_IN_SRC_PWM1SYNCOUT);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_CAP6, SYSCTL_SYNC_IN_SRC_PWM1SYNCOUT);
    // SOCA
    SysCtl_enableExtADCSOCSource(0);
    // SOCB
    SysCtl_enableExtADCSOCSource(0);
}
