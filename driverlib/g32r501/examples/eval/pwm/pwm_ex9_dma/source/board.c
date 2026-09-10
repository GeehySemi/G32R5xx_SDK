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

}

//*****************************************************************************
//
// PWM Configurations
//
//*****************************************************************************
void PWM_init()
{
    PWM_setClockPrescaler(myPWM1_BASE, PWM_CLOCK_DIVIDER_1, PWM_HSCLOCK_DIVIDER_2);
    PWM_setTimeBasePeriod(myPWM1_BASE, 0);
    PWM_setTimeBaseCounter(myPWM1_BASE, 0);
    PWM_setTimeBaseCounterMode(myPWM1_BASE, PWM_COUNTER_MODE_STOP_FREEZE);
    PWM_disablePhaseShiftLoad(myPWM1_BASE);
    PWM_setPhaseShift(myPWM1_BASE, 0);
    PWM_setCounterCompareValue(myPWM1_BASE, PWM_COUNTER_COMPARE_A, 0);
    PWM_setCounterCompareShadowLoadMode(myPWM1_BASE, PWM_COUNTER_COMPARE_A, PWM_COMP_LOAD_ON_CNTR_ZERO);
    PWM_setCounterCompareValue(myPWM1_BASE, PWM_COUNTER_COMPARE_B, 0);
    PWM_setCounterCompareShadowLoadMode(myPWM1_BASE, PWM_COUNTER_COMPARE_B, PWM_COMP_LOAD_ON_CNTR_ZERO);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_A, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    PWM_setActionQualifierAction(myPWM1_BASE, PWM_AQ_OUTPUT_B, PWM_AQ_OUTPUT_NO_CHANGE, PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    PWM_setRisingEdgeDelayCountShadowLoadMode(myPWM1_BASE, PWM_RED_LOAD_ON_CNTR_ZERO);
    PWM_disableRisingEdgeDelayCountShadowLoadMode(myPWM1_BASE);
    PWM_setFallingEdgeDelayCountShadowLoadMode(myPWM1_BASE, PWM_FED_LOAD_ON_CNTR_ZERO);
    PWM_disableFallingEdgeDelayCountShadowLoadMode(myPWM1_BASE);
}

//*****************************************************************************
//
// InputXbar Configurations
//
//*****************************************************************************
void INPUTXBAR_init()
{
    //myINPUTXBAR5 initialization
    XBAR_setInputPin(XBAR_INPUT5, 56);
    XBAR_setInputPin(XBAR_INPUT6, 56);
}

//*****************************************************************************
//
// Sync Configurations
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
