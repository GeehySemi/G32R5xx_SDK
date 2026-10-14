//###########################################################################
//
// FILE:    board.c
//
// TITLE:   Board source file.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//###########################################################################
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
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
// PWM1/2 A/B on GPIO0/1 and GPIO2/3.
//
//*****************************************************************************
void PinMux_init()
{
    //
    // PWM1 -> myPWM1 Pinmux
    //
    GPIO_setPinConfig(myPWM1_PWMA_PIN_CONFIG);
    GPIO_setDrivingCapability(myPWM1_PWMA_GPIO, GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(myPWM1_PWMA_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myPWM1_PWMA_GPIO, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(myPWM1_PWMB_PIN_CONFIG);
    GPIO_setDrivingCapability(myPWM1_PWMB_GPIO, GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(myPWM1_PWMB_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myPWM1_PWMB_GPIO, GPIO_QUAL_SYNC);

    //
    // PWM2 -> myPWM2 Pinmux
    //
    GPIO_setPinConfig(myPWM2_PWMA_PIN_CONFIG);
    GPIO_setDrivingCapability(myPWM2_PWMA_GPIO, GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(myPWM2_PWMA_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myPWM2_PWMA_GPIO, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(myPWM2_PWMB_PIN_CONFIG);
    GPIO_setDrivingCapability(myPWM2_PWMB_GPIO, GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(myPWM2_PWMB_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myPWM2_PWMB_GPIO, GPIO_QUAL_SYNC);
}

//*****************************************************************************
//
// PWM Configurations
//
//*****************************************************************************
void PWM_init()
{
    HRPWM_setEmulationMode(myPWM1_BASE, PWM_EMULATION_FREE_RUN);
    HRPWM_setClockPrescaler(myPWM1_BASE, PWM_CLOCK_DIVIDER_1, PWM_HSCLOCK_DIVIDER_1);
    PWM_setTimeBasePeriod(myPWM1_BASE, myPWM1_TBPRD);
    HRPWM_setTimeBaseCounter(myPWM1_BASE, 0);
    HRPWM_setTimeBaseCounterMode(myPWM1_BASE, PWM_COUNTER_MODE_UP);
    PWM_disablePhaseShiftLoad(myPWM1_BASE);
    PWM_setPhaseShift(myPWM1_BASE, 0);
    PWM_setCounterCompareValue(myPWM1_BASE, PWM_COUNTER_COMPARE_A, 0);
    HRPWM_setCounterCompareShadowLoadMode(myPWM1_BASE, PWM_COUNTER_COMPARE_A, PWM_COMP_LOAD_ON_CNTR_ZERO);
    PWM_setCounterCompareValue(myPWM1_BASE, PWM_COUNTER_COMPARE_B, 0);
    HRPWM_setCounterCompareShadowLoadMode(myPWM1_BASE, PWM_COUNTER_COMPARE_B, PWM_COMP_LOAD_ON_CNTR_ZERO);
    HRPWM_disableActionQualifierShadowLoadMode(myPWM1_BASE, PWM_ACTION_QUALIFIER_A);
    HRPWM_setActionQualifierShadowLoadMode(myPWM1_BASE, PWM_ACTION_QUALIFIER_A, PWM_AQ_LOAD_ON_CNTR_ZERO);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_disableActionQualifierShadowLoadMode(myPWM1_BASE, PWM_ACTION_QUALIFIER_B);
    HRPWM_setActionQualifierShadowLoadMode(myPWM1_BASE, PWM_ACTION_QUALIFIER_B, PWM_AQ_LOAD_ON_CNTR_ZERO);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_setRisingEdgeDelayCountShadowLoadMode(myPWM1_BASE, PWM_RED_LOAD_ON_CNTR_ZERO);
    HRPWM_disableRisingEdgeDelayCountShadowLoadMode(myPWM1_BASE);
    HRPWM_setFallingEdgeDelayCountShadowLoadMode(myPWM1_BASE, PWM_FED_LOAD_ON_CNTR_ZERO);
    HRPWM_disableFallingEdgeDelayCountShadowLoadMode(myPWM1_BASE);
    HRPWM_setDeadBandControlShadowLoadMode(myPWM1_BASE, PWM_DB_LOAD_ON_CNTR_ZERO);
    HRPWM_disableDeadBandControlShadowLoadMode(myPWM1_BASE);
    HRPWM_enableAutoConversion(myPWM1_BASE);
    HRPWM_setMEPEdgeSelect(myPWM1_BASE, HRPWM_CHANNEL_A, HRPWM_MEP_CTRL_FALLING_EDGE);
    HRPWM_setHiResCounterCompareValueOnly(myPWM1_BASE, HRPWM_COUNTER_COMPARE_A, 50);
    HRPWM_setMEPEdgeSelect(myPWM1_BASE, HRPWM_CHANNEL_B, HRPWM_MEP_CTRL_FALLING_EDGE);
    HRPWM_setHiResCounterCompareValueOnly(myPWM1_BASE, HRPWM_COUNTER_COMPARE_B, 50);

    HRPWM_setEmulationMode(myPWM2_BASE, PWM_EMULATION_FREE_RUN);
    HRPWM_setClockPrescaler(myPWM2_BASE, PWM_CLOCK_DIVIDER_1, PWM_HSCLOCK_DIVIDER_1);
    PWM_setTimeBasePeriod(myPWM2_BASE, myPWM2_TBPRD);
    HRPWM_setTimeBaseCounter(myPWM2_BASE, 0);
    HRPWM_setTimeBaseCounterMode(myPWM2_BASE, PWM_COUNTER_MODE_UP);
    PWM_disablePhaseShiftLoad(myPWM2_BASE);
    PWM_setPhaseShift(myPWM2_BASE, 0);
    PWM_setCounterCompareValue(myPWM2_BASE, PWM_COUNTER_COMPARE_A, 0);
    HRPWM_setCounterCompareShadowLoadMode(myPWM2_BASE, PWM_COUNTER_COMPARE_A, PWM_COMP_LOAD_ON_CNTR_ZERO);
    PWM_setCounterCompareValue(myPWM2_BASE, PWM_COUNTER_COMPARE_B, 0);
    HRPWM_setCounterCompareShadowLoadMode(myPWM2_BASE, PWM_COUNTER_COMPARE_B, PWM_COMP_LOAD_ON_CNTR_ZERO);
    HRPWM_disableActionQualifierShadowLoadMode(myPWM2_BASE, PWM_ACTION_QUALIFIER_A);
    HRPWM_setActionQualifierShadowLoadMode(myPWM2_BASE, PWM_ACTION_QUALIFIER_A, PWM_AQ_LOAD_ON_CNTR_ZERO);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_disableActionQualifierShadowLoadMode(myPWM2_BASE, PWM_ACTION_QUALIFIER_B);
    HRPWM_setActionQualifierShadowLoadMode(myPWM2_BASE, PWM_ACTION_QUALIFIER_B, PWM_AQ_LOAD_ON_CNTR_ZERO);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_setRisingEdgeDelayCountShadowLoadMode(myPWM2_BASE, PWM_RED_LOAD_ON_CNTR_ZERO);
    HRPWM_disableRisingEdgeDelayCountShadowLoadMode(myPWM2_BASE);
    HRPWM_setFallingEdgeDelayCountShadowLoadMode(myPWM2_BASE, PWM_FED_LOAD_ON_CNTR_ZERO);
    HRPWM_disableFallingEdgeDelayCountShadowLoadMode(myPWM2_BASE);
    HRPWM_setDeadBandControlShadowLoadMode(myPWM2_BASE, PWM_DB_LOAD_ON_CNTR_ZERO);
    HRPWM_disableDeadBandControlShadowLoadMode(myPWM2_BASE);
    HRPWM_enableAutoConversion(myPWM2_BASE);
    HRPWM_setMEPEdgeSelect(myPWM2_BASE, HRPWM_CHANNEL_A, HRPWM_MEP_CTRL_FALLING_EDGE);
    HRPWM_setHiResCounterCompareValueOnly(myPWM2_BASE, HRPWM_COUNTER_COMPARE_A, 50);
    HRPWM_setMEPEdgeSelect(myPWM2_BASE, HRPWM_CHANNEL_B, HRPWM_MEP_CTRL_FALLING_EDGE);
    HRPWM_setHiResCounterCompareValueOnly(myPWM2_BASE, HRPWM_COUNTER_COMPARE_B, 50);
}

//*****************************************************************************
//
// INPUTXBAR Configurations
//
// This example does not use INPUTXBAR; keep an empty init for Board_init().
//
//*****************************************************************************
void INPUTXBAR_init()
{
}

//*****************************************************************************
//
// SYNC Configurations
//
//*****************************************************************************
void SYNC_init()
{
    SysCtl_setSyncOutputConfig(SYSCTL_SYNC_OUT_SRC_PWM1SYNCOUT);
    SysCtl_enableExtADCSOCSource(0);
    SysCtl_enableExtADCSOCSource(0);
}
