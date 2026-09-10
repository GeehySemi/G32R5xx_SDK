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
// 1. Modify some comments, macro definitions, and function names.
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
    CAP_init();
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
    // GPIO16 -> myGPIO0 Pinmux
    GPIO_setPinConfig(GPIO_16_GPIO16);
}

//*****************************************************************************
//
// CAP Configurations
//
//*****************************************************************************
void CAP_init(){
    myCAP0_init();
}

void myCAP0_init(){
    //
    // Disable ,clear all capture flags and interrupts
    //
    CAP_disableInterrupt(myCAP0_BASE,
        (CAP_ISR_SOURCE_CAPTURE_EVENT_1  |
        CAP_ISR_SOURCE_CAPTURE_EVENT_2  |
        CAP_ISR_SOURCE_CAPTURE_EVENT_3  |
        CAP_ISR_SOURCE_CAPTURE_EVENT_4  |
        CAP_ISR_SOURCE_COUNTER_OVERFLOW |
        CAP_ISR_SOURCE_COUNTER_PERIOD   |
        CAP_ISR_SOURCE_COUNTER_COMPARE));
    CAP_clearInterrupt(myCAP0_BASE,
        (CAP_ISR_SOURCE_CAPTURE_EVENT_1  |
        CAP_ISR_SOURCE_CAPTURE_EVENT_2  |
        CAP_ISR_SOURCE_CAPTURE_EVENT_3  |
        CAP_ISR_SOURCE_CAPTURE_EVENT_4  |
        CAP_ISR_SOURCE_COUNTER_OVERFLOW |
        CAP_ISR_SOURCE_COUNTER_PERIOD   |
        CAP_ISR_SOURCE_COUNTER_COMPARE));
    //
    // Disables time stamp capture.
    //
    CAP_disableTimeStampCapture(myCAP0_BASE);
    //
    // Stops Time stamp counter.
    //
    CAP_stopCounter(myCAP0_BASE);
    //
    // Sets eCAP in Capture mode.
    //
    CAP_enableCaptureMode(myCAP0_BASE);
    //
    // Sets the capture mode.
    //
    CAP_setCaptureMode(myCAP0_BASE,CAP_ONE_SHOT_CAPTURE_MODE,CAP_EVENT_4);
    //
    // Sets the Capture event prescaler.
    //
    CAP_setEventPrescaler(myCAP0_BASE, 0U);
    //
    // Sets the Capture event polarity.
    //
    CAP_setEventPolarity(myCAP0_BASE,CAP_EVENT_1,CAP_EVNT_FALLING_EDGE);
    CAP_setEventPolarity(myCAP0_BASE,CAP_EVENT_2,CAP_EVNT_RISING_EDGE);
    CAP_setEventPolarity(myCAP0_BASE,CAP_EVENT_3,CAP_EVNT_FALLING_EDGE);
    CAP_setEventPolarity(myCAP0_BASE,CAP_EVENT_4,CAP_EVNT_RISING_EDGE);
    //
    // Configure counter reset on events
    //
    CAP_enableCounterResetOnEvent(myCAP0_BASE,CAP_EVENT_1);
    CAP_enableCounterResetOnEvent(myCAP0_BASE,CAP_EVENT_2);
    CAP_enableCounterResetOnEvent(myCAP0_BASE,CAP_EVENT_3);
    CAP_enableCounterResetOnEvent(myCAP0_BASE,CAP_EVENT_4);
    //
    // Select eCAP input.
    //
    CAP_selectCAPInput(myCAP0_BASE,CAP_INPUT_INPUTXBAR7);
    //
    // Sets a phase shift value count.
    //
    CAP_setPhaseShiftCount(myCAP0_BASE,0U);
    //
    // Enable counter loading with phase shift value.
    //
    CAP_enableLoadCounter(myCAP0_BASE);
    //
    // Configures Sync out signal mode.
    //
    CAP_setSyncOutMode(myCAP0_BASE,CAP_SYNC_OUT_SYNCI);
    //
    // Configures emulation mode.
    //
    CAP_setEmulationMode(myCAP0_BASE,CAP_EMULATION_STOP);
    //
    // Starts Time stamp counter for myECAP0.
    //
    CAP_startCounter(myCAP0_BASE);
    //
    // Enables time stamp capture for myECAP0.
    //
    CAP_enableTimeStampCapture(myCAP0_BASE);
    //
    // Re-arms the eCAP module for myECAP0.
    //
    CAP_reArm(myCAP0_BASE);
    //
    // Enables interrupt source for myECAP0.
    //
    CAP_enableInterrupt(myCAP0_BASE,(CAP_ISR_SOURCE_CAPTURE_EVENT_4));

    //-----------------Signal Monitoring--------------------//
}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init(){
    myGPIO0_init();
}

void myGPIO0_init(){
    GPIO_setDrivingCapability(myGPIO0,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(myGPIO0, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myGPIO0, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(myGPIO0, GPIO_DIR_MODE_IN);
    GPIO_setMasterCore(myGPIO0, GPIO_CORE_CPU0);
}

//*****************************************************************************
//
// INPUTXBAR Configurations
//
//*****************************************************************************
void INPUTXBAR_init(){
    myINPUTXBARINPUT0_init();
}

void myINPUTXBARINPUT0_init(){
    XBAR_setInputPin(myINPUTXBARINPUT0_INPUT, myINPUTXBARINPUT0_SOURCE);
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init(){

    //
    // Set the priority group to indicate the PREEMPT and SUB priority bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_7_6_SUB_5_0);

    //
    // Set the global and group interrupt priority to allow CPU interrupts
    // with higher priority
    Interrupt_setPriority(INT_myCAP0, 0, 0);

    // Interrupt Setings for INT_myCAP0
    Interrupt_register(INT_myCAP0, &INT_myCAP0_ISR);
    Interrupt_enable(INT_myCAP0);
}

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************
void SYNC_init(){
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
