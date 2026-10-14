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
void PWM_init(){
    PWM_setEmulationMode(myPWM1_BASE, PWM_EMULATION_FREE_RUN);    
    PWM_setClockPrescaler(myPWM1_BASE, PWM_CLOCK_DIVIDER_1, PWM_HSCLOCK_DIVIDER_1);    
    PWM_setTimeBasePeriod(myPWM1_BASE, 100);    
    PWM_setTimeBaseCounter(myPWM1_BASE, 0);    
    PWM_setTimeBaseCounterMode(myPWM1_BASE, PWM_COUNTER_MODE_UP_DOWN);    
    PWM_setCountModeAfterSync(myPWM1_BASE, PWM_COUNT_MODE_UP_AFTER_SYNC);    
    PWM_disablePhaseShiftLoad(myPWM1_BASE);    
    PWM_setPhaseShift(myPWM1_BASE, 0);    
    PWM_setSyncOutPulseMode(myPWM1_BASE, PWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);    
    PWM_setCounterCompareValue(myPWM1_BASE, PWM_COUNTER_COMPARE_A, 50);    
    PWM_setCounterCompareShadowLoadMode(myPWM1_BASE, PWM_COUNTER_COMPARE_A, PWM_COMP_LOAD_ON_CNTR_ZERO);    
    PWM_setCounterCompareValue(myPWM1_BASE, PWM_COUNTER_COMPARE_B, 50);    
    PWM_setCounterCompareShadowLoadMode(myPWM1_BASE, PWM_COUNTER_COMPARE_B, PWM_COMP_LOAD_ON_CNTR_ZERO);    
    PWM_disableActionQualifierShadowLoadMode(myPWM1_BASE, PWM_ACTION_QUALIFIER_A);    
    PWM_setActionQualifierShadowLoadMode(myPWM1_BASE, PWM_ACTION_QUALIFIER_A, PWM_AQ_LOAD_ON_CNTR_ZERO);    
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);    
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);    
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);    
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);    
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);    
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);    
    PWM_disableActionQualifierShadowLoadMode(myPWM1_BASE, PWM_ACTION_QUALIFIER_B);    
    PWM_setActionQualifierShadowLoadMode(myPWM1_BASE, PWM_ACTION_QUALIFIER_B, PWM_AQ_LOAD_ON_CNTR_ZERO);    
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);    
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);    
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);    
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);    
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);    
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);    
    PWM_setFallingEdgeDeadBandDelayInput(myPWM1_BASE, PWM_DB_INPUT_PWMB);    
    PWM_setDeadBandDelayPolarity(myPWM1_BASE, PWM_DB_FED, PWM_DB_POLARITY_ACTIVE_LOW);    
    PWM_setDeadBandDelayMode(myPWM1_BASE, PWM_DB_RED, true);    
    PWM_setRisingEdgeDelayCountShadowLoadMode(myPWM1_BASE, PWM_RED_LOAD_ON_CNTR_ZERO);    
    PWM_disableRisingEdgeDelayCountShadowLoadMode(myPWM1_BASE);    
    PWM_setDeadBandDelayMode(myPWM1_BASE, PWM_DB_FED, true);    
    PWM_setFallingEdgeDelayCountShadowLoadMode(myPWM1_BASE, PWM_FED_LOAD_ON_CNTR_ZERO);    
    PWM_disableFallingEdgeDelayCountShadowLoadMode(myPWM1_BASE);    
    PWM_setDeadBandControlShadowLoadMode(myPWM1_BASE, PWM_DB_LOAD_ON_CNTR_ZERO);    
    PWM_disableDeadBandControlShadowLoadMode(myPWM1_BASE);    
    HRPWM_setEmulationMode(myPWM2_BASE, PWM_EMULATION_FREE_RUN);    
    HRPWM_setClockPrescaler(myPWM2_BASE, PWM_CLOCK_DIVIDER_1, PWM_HSCLOCK_DIVIDER_1);    
    PWM_setTimeBasePeriod(myPWM2_BASE, 100);    
    HRPWM_setTimeBaseCounter(myPWM2_BASE, 0);    
    HRPWM_setTimeBaseCounterMode(myPWM2_BASE, PWM_COUNTER_MODE_UP_DOWN);    
    HRPWM_setCountModeAfterSync(myPWM2_BASE, PWM_COUNT_MODE_UP_AFTER_SYNC);    
    PWM_enablePhaseShiftLoad(myPWM2_BASE);
    PWM_setPhaseShift(myPWM2_BASE, 0);    
    PWM_setCounterCompareValue(myPWM2_BASE, PWM_COUNTER_COMPARE_A, 50);    
    HRPWM_setCounterCompareShadowLoadMode(myPWM2_BASE, PWM_COUNTER_COMPARE_A, PWM_COMP_LOAD_ON_CNTR_ZERO);    
    PWM_setCounterCompareValue(myPWM2_BASE, PWM_COUNTER_COMPARE_B, 50);    
    HRPWM_setCounterCompareShadowLoadMode(myPWM2_BASE, PWM_COUNTER_COMPARE_B, PWM_COMP_LOAD_ON_CNTR_ZERO);    
    HRPWM_disableActionQualifierShadowLoadMode(myPWM2_BASE, PWM_ACTION_QUALIFIER_A);    
    HRPWM_setActionQualifierShadowLoadMode(myPWM2_BASE, PWM_ACTION_QUALIFIER_A, PWM_AQ_LOAD_ON_CNTR_ZERO);    
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);    
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);    
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);    
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);    
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);    
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);    
    HRPWM_disableActionQualifierShadowLoadMode(myPWM2_BASE, PWM_ACTION_QUALIFIER_B);    
    HRPWM_setActionQualifierShadowLoadMode(myPWM2_BASE, PWM_ACTION_QUALIFIER_B, PWM_AQ_LOAD_ON_CNTR_ZERO);    
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);    
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);    
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);    
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);    
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);    
    HRPWM_setActionQualifierAction(myPWM2_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);    
    HRPWM_setFallingEdgeDeadBandDelayInput(myPWM2_BASE, PWM_DB_INPUT_PWMB);    
    HRPWM_setDeadBandDelayPolarity(myPWM2_BASE, PWM_DB_FED, PWM_DB_POLARITY_ACTIVE_LOW);    
    HRPWM_setDeadBandDelayMode(myPWM2_BASE, PWM_DB_RED, true);    
    HRPWM_setRisingEdgeDelayCountShadowLoadMode(myPWM2_BASE, PWM_RED_LOAD_ON_CNTR_ZERO);    
    HRPWM_disableRisingEdgeDelayCountShadowLoadMode(myPWM2_BASE);    
    HRPWM_setDeadBandDelayMode(myPWM2_BASE, PWM_DB_FED, true);    
    HRPWM_setFallingEdgeDelayCountShadowLoadMode(myPWM2_BASE, PWM_FED_LOAD_ON_CNTR_ZERO);    
    HRPWM_disableFallingEdgeDelayCountShadowLoadMode(myPWM2_BASE);    
    HRPWM_setDeadBandControlShadowLoadMode(myPWM2_BASE, PWM_DB_LOAD_ON_CNTR_ZERO);    
    HRPWM_disableDeadBandControlShadowLoadMode(myPWM2_BASE);    
    HRPWM_setDeadBandCounterClock(myPWM2_BASE, PWM_DB_COUNTER_CLOCK_HALF_CYCLE);    
    HRPWM_enableAutoConversion(myPWM2_BASE);    
    HRPWM_setDeadbandMEPEdgeSelect(myPWM2_BASE, HRPWM_DB_MEP_CTRL_RED_FED);
    PWM_setEmulationMode(myPWM3_BASE, PWM_EMULATION_FREE_RUN);    
    PWM_setClockPrescaler(myPWM3_BASE, PWM_CLOCK_DIVIDER_1, PWM_HSCLOCK_DIVIDER_1);    
    PWM_setTimeBasePeriod(myPWM3_BASE, 100);    
    PWM_setTimeBaseCounter(myPWM3_BASE, 0);    
    PWM_setTimeBaseCounterMode(myPWM3_BASE, PWM_COUNTER_MODE_UP_DOWN);    
    PWM_setCountModeAfterSync(myPWM3_BASE, PWM_COUNT_MODE_UP_AFTER_SYNC);    
    PWM_disablePhaseShiftLoad(myPWM3_BASE);    
    PWM_setPhaseShift(myPWM3_BASE, 0);    
    PWM_setSyncOutPulseMode(myPWM3_BASE, PWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);    
    PWM_setCounterCompareValue(myPWM3_BASE, PWM_COUNTER_COMPARE_A, 50);    
    PWM_setCounterCompareShadowLoadMode(myPWM3_BASE, PWM_COUNTER_COMPARE_A, PWM_COMP_LOAD_ON_CNTR_ZERO);    
    PWM_setCounterCompareValue(myPWM3_BASE, PWM_COUNTER_COMPARE_B, 50);    
    PWM_setCounterCompareShadowLoadMode(myPWM3_BASE, PWM_COUNTER_COMPARE_B, PWM_COMP_LOAD_ON_CNTR_ZERO);    
    PWM_disableActionQualifierShadowLoadMode(myPWM3_BASE, PWM_ACTION_QUALIFIER_A);    
    PWM_setActionQualifierShadowLoadMode(myPWM3_BASE, PWM_ACTION_QUALIFIER_A, PWM_AQ_LOAD_ON_CNTR_ZERO);    
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);    
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);    
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);    
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);    
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);    
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);    
    PWM_disableActionQualifierShadowLoadMode(myPWM3_BASE, PWM_ACTION_QUALIFIER_B);    
    PWM_setActionQualifierShadowLoadMode(myPWM3_BASE, PWM_ACTION_QUALIFIER_B, PWM_AQ_LOAD_ON_CNTR_ZERO);    
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);    
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);    
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);    
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);    
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);    
    PWM_setActionQualifierAction(myPWM3_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);    
    PWM_setFallingEdgeDeadBandDelayInput(myPWM3_BASE, PWM_DB_INPUT_PWMB);    
    PWM_setDeadBandDelayPolarity(myPWM3_BASE, PWM_DB_FED, PWM_DB_POLARITY_ACTIVE_LOW);    
    PWM_setDeadBandDelayMode(myPWM3_BASE, PWM_DB_RED, true);    
    PWM_setRisingEdgeDelayCountShadowLoadMode(myPWM3_BASE, PWM_RED_LOAD_ON_CNTR_ZERO);    
    PWM_disableRisingEdgeDelayCountShadowLoadMode(myPWM3_BASE);    
    PWM_setDeadBandDelayMode(myPWM3_BASE, PWM_DB_FED, true);    
    PWM_setFallingEdgeDelayCountShadowLoadMode(myPWM3_BASE, PWM_FED_LOAD_ON_CNTR_ZERO);    
    PWM_disableFallingEdgeDelayCountShadowLoadMode(myPWM3_BASE);    
    PWM_setDeadBandControlShadowLoadMode(myPWM3_BASE, PWM_DB_LOAD_ON_CNTR_ZERO);    
    PWM_disableDeadBandControlShadowLoadMode(myPWM3_BASE);    
    PWM_setEmulationMode(myPWM4_BASE, PWM_EMULATION_FREE_RUN);    
    PWM_setClockPrescaler(myPWM4_BASE, PWM_CLOCK_DIVIDER_1, PWM_HSCLOCK_DIVIDER_1);    
    PWM_setTimeBasePeriod(myPWM4_BASE, 100);    
    PWM_setTimeBaseCounter(myPWM4_BASE, 0);    
    PWM_setTimeBaseCounterMode(myPWM4_BASE, PWM_COUNTER_MODE_UP_DOWN);    
    PWM_setCountModeAfterSync(myPWM4_BASE, PWM_COUNT_MODE_UP_AFTER_SYNC);    
    PWM_disablePhaseShiftLoad(myPWM4_BASE);    
    PWM_setPhaseShift(myPWM4_BASE, 0);    
    PWM_setSyncOutPulseMode(myPWM4_BASE, PWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);    
    PWM_setCounterCompareValue(myPWM4_BASE, PWM_COUNTER_COMPARE_A, 50);    
    PWM_setCounterCompareShadowLoadMode(myPWM4_BASE, PWM_COUNTER_COMPARE_A, PWM_COMP_LOAD_ON_CNTR_ZERO);    
    PWM_setCounterCompareValue(myPWM4_BASE, PWM_COUNTER_COMPARE_B, 50);    
    PWM_setCounterCompareShadowLoadMode(myPWM4_BASE, PWM_COUNTER_COMPARE_B, PWM_COMP_LOAD_ON_CNTR_ZERO);    
    PWM_disableActionQualifierShadowLoadMode(myPWM4_BASE, PWM_ACTION_QUALIFIER_A);    
    PWM_setActionQualifierShadowLoadMode(myPWM4_BASE, PWM_ACTION_QUALIFIER_A, PWM_AQ_LOAD_ON_CNTR_ZERO);    
    PWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);    
    PWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);    
    PWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);    
    PWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);    
    PWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);    
    PWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);    
    PWM_disableActionQualifierShadowLoadMode(myPWM4_BASE, PWM_ACTION_QUALIFIER_B);    
    PWM_setActionQualifierShadowLoadMode(myPWM4_BASE, PWM_ACTION_QUALIFIER_B, PWM_AQ_LOAD_ON_CNTR_ZERO);    
    PWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);    
    PWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);    
    PWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);    
    PWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);    
    PWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_HIGH, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);    
    PWM_setActionQualifierAction(myPWM4_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_LOW, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);    
    PWM_setFallingEdgeDeadBandDelayInput(myPWM4_BASE, PWM_DB_INPUT_PWMB);    
    PWM_setDeadBandDelayPolarity(myPWM4_BASE, PWM_DB_FED, PWM_DB_POLARITY_ACTIVE_LOW);    
    PWM_setDeadBandDelayMode(myPWM4_BASE, PWM_DB_RED, true);    
    PWM_setRisingEdgeDelayCountShadowLoadMode(myPWM4_BASE, PWM_RED_LOAD_ON_CNTR_ZERO);    
    PWM_disableRisingEdgeDelayCountShadowLoadMode(myPWM4_BASE);    
    PWM_setDeadBandDelayMode(myPWM4_BASE, PWM_DB_FED, true);    
    PWM_setFallingEdgeDelayCountShadowLoadMode(myPWM4_BASE, PWM_FED_LOAD_ON_CNTR_ZERO);    
    PWM_disableFallingEdgeDelayCountShadowLoadMode(myPWM4_BASE);    
    PWM_setDeadBandControlShadowLoadMode(myPWM4_BASE, PWM_DB_LOAD_ON_CNTR_ZERO);    
    PWM_disableDeadBandControlShadowLoadMode(myPWM4_BASE);    

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
    // For PWM1, the sync input is: SYSCTL_SYNC_IN_SRC_EXTSYNCIN1
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_PWM4, SYSCTL_SYNC_IN_SRC_PWM1SYNCOUT);
    // SOCA
    SysCtl_enableExtADCSOCSource(0);
    // SOCB
    SysCtl_enableExtADCSOCSource(0);
}
