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
    myCAP1_init();
    myCAP2_init();
    myCAP3_init();
}

void myCAP1_init(){
    //
    // Disables time stamp capture.
    //
    CAP_disableTimeStampCapture(myCAP1_BASE);
    //
    // Stops Time stamp counter.
    //
    CAP_stopCounter(myCAP1_BASE);
    //
    // Sets eCAP in Capture mode.
    //
    CAP_enableCaptureMode(myCAP1_BASE);
    //
    // Sets the capture mode.
    //
    CAP_setCaptureMode(myCAP1_BASE,CAP_ONE_SHOT_CAPTURE_MODE,CAP_EVENT_4);
    //
    // Sets the Capture event prescaler.
    //
    CAP_setEventPrescaler(myCAP1_BASE, 0U);
    //
    // Sets the Capture event polarity.
    //
    CAP_setEventPolarity(myCAP1_BASE,CAP_EVENT_1,CAP_EVNT_FALLING_EDGE);
    CAP_setEventPolarity(myCAP1_BASE,CAP_EVENT_2,CAP_EVNT_RISING_EDGE);
    CAP_setEventPolarity(myCAP1_BASE,CAP_EVENT_3,CAP_EVNT_FALLING_EDGE);
    CAP_setEventPolarity(myCAP1_BASE,CAP_EVENT_4,CAP_EVNT_RISING_EDGE);
    //
    // Configure counter reset on events
    //
    CAP_enableCounterResetOnEvent(myCAP1_BASE,CAP_EVENT_1);
    CAP_enableCounterResetOnEvent(myCAP1_BASE,CAP_EVENT_2);
    CAP_enableCounterResetOnEvent(myCAP1_BASE,CAP_EVENT_3);
    CAP_enableCounterResetOnEvent(myCAP1_BASE,CAP_EVENT_4);
    //
    // Select CAP input.
    //
    CAP_selectCAPInput(myCAP1_BASE,CAP_INPUT_INPUTXBAR7);
    //
    // Sets a phase shift value count.
    //
    CAP_setPhaseShiftCount(myCAP1_BASE,0U);
    //
    // Enable counter loading with phase shift value.
    //
    CAP_enableLoadCounter(myCAP1_BASE);
    //
    // Load time stamp counter.
    //
    CAP_loadCounter(myCAP1_BASE);
    //
    // Configures Sync out signal mode.
    //
    CAP_setSyncOutMode(myCAP1_BASE,CAP_SYNC_OUT_SYNCI);
    //
    // Configures emulation mode.
    //
    CAP_setEmulationMode(myCAP1_BASE,CAP_EMULATION_STOP);
    //
    // Starts Time stamp counter for myCAP1.
    //
    CAP_startCounter(myCAP1_BASE);
    //
    // Enables time stamp capture for myCAP1.
    //
    CAP_enableTimeStampCapture(myCAP1_BASE);
    //
    // Re-arms the eCAP module for myCAP1.
    //
    CAP_reArm(myCAP1_BASE);
}
void myCAP2_init(){
    //
    // Disables time stamp capture.
    //
    CAP_disableTimeStampCapture(myCAP2_BASE);
    //
    // Stops Time stamp counter.
    //
    CAP_stopCounter(myCAP2_BASE);
    //
    // Sets eCAP in Capture mode.
    //
    CAP_enableCaptureMode(myCAP2_BASE);
    //
    // Sets the capture mode.
    //
    CAP_setCaptureMode(myCAP2_BASE,CAP_ONE_SHOT_CAPTURE_MODE,CAP_EVENT_4);
    //
    // Sets the Capture event prescaler.
    //
    CAP_setEventPrescaler(myCAP2_BASE, 0U);
    //
    // Sets the Capture event polarity.
    //
    CAP_setEventPolarity(myCAP2_BASE,CAP_EVENT_1,CAP_EVNT_FALLING_EDGE);
    CAP_setEventPolarity(myCAP2_BASE,CAP_EVENT_2,CAP_EVNT_RISING_EDGE);
    CAP_setEventPolarity(myCAP2_BASE,CAP_EVENT_3,CAP_EVNT_FALLING_EDGE);
    CAP_setEventPolarity(myCAP2_BASE,CAP_EVENT_4,CAP_EVNT_RISING_EDGE);
    //
    // Configure counter reset on events
    //
    CAP_enableCounterResetOnEvent(myCAP2_BASE,CAP_EVENT_1);
    CAP_enableCounterResetOnEvent(myCAP2_BASE,CAP_EVENT_2);
    CAP_enableCounterResetOnEvent(myCAP2_BASE,CAP_EVENT_3);
    CAP_enableCounterResetOnEvent(myCAP2_BASE,CAP_EVENT_4);
    //
    // Select CAP input.
    //
    CAP_selectCAPInput(myCAP2_BASE,CAP_INPUT_INPUTXBAR7);
    //
    // Sets a phase shift value count.
    //
    CAP_setPhaseShiftCount(myCAP2_BASE,0U);
    //
    // Enable counter loading with phase shift value.
    //
    CAP_enableLoadCounter(myCAP2_BASE);
    //
    // Configures Sync out signal mode.
    //
    CAP_setSyncOutMode(myCAP2_BASE,CAP_SYNC_OUT_SYNCI);
    //
    // Configures emulation mode.
    //
    CAP_setEmulationMode(myCAP2_BASE,CAP_EMULATION_STOP);
    //
    // Starts Time stamp counter for myCAP2.
    //
    CAP_startCounter(myCAP2_BASE);
    //
    // Enables time stamp capture for myCAP2.
    //
    CAP_enableTimeStampCapture(myCAP2_BASE);
    //
    // Re-arms the eCAP module for myCAP2.
    //
    CAP_reArm(myCAP2_BASE);
}
void myCAP3_init(){
    //
    // Disable ,clear all capture flags and interrupts
    //
    CAP_disableInterrupt(myCAP3_BASE,
        (CAP_ISR_SOURCE_CAPTURE_EVENT_1  |
        CAP_ISR_SOURCE_CAPTURE_EVENT_2  |
        CAP_ISR_SOURCE_CAPTURE_EVENT_3  |
        CAP_ISR_SOURCE_CAPTURE_EVENT_4  |
        CAP_ISR_SOURCE_COUNTER_OVERFLOW |
        CAP_ISR_SOURCE_COUNTER_PERIOD   |
        CAP_ISR_SOURCE_COUNTER_COMPARE));
    CAP_clearInterrupt(myCAP3_BASE,
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
    CAP_disableTimeStampCapture(myCAP3_BASE);
    //
    // Stops Time stamp counter.
    //
    CAP_stopCounter(myCAP3_BASE);
    //
    // Sets eCAP in Capture mode.
    //
    CAP_enableCaptureMode(myCAP3_BASE);
    //
    // Sets the capture mode.
    //
    CAP_setCaptureMode(myCAP3_BASE,CAP_ONE_SHOT_CAPTURE_MODE,CAP_EVENT_4);
    //
    // Sets the Capture event prescaler.
    //
    CAP_setEventPrescaler(myCAP3_BASE, 0U);
    //
    // Sets the Capture event polarity.
    //
    CAP_setEventPolarity(myCAP3_BASE,CAP_EVENT_1,CAP_EVNT_FALLING_EDGE);
    CAP_setEventPolarity(myCAP3_BASE,CAP_EVENT_2,CAP_EVNT_RISING_EDGE);
    CAP_setEventPolarity(myCAP3_BASE,CAP_EVENT_3,CAP_EVNT_FALLING_EDGE);
    CAP_setEventPolarity(myCAP3_BASE,CAP_EVENT_4,CAP_EVNT_RISING_EDGE);
    //
    // Configure counter reset on events
    //
    CAP_enableCounterResetOnEvent(myCAP3_BASE,CAP_EVENT_1);
    CAP_enableCounterResetOnEvent(myCAP3_BASE,CAP_EVENT_2);
    CAP_enableCounterResetOnEvent(myCAP3_BASE,CAP_EVENT_3);
    CAP_enableCounterResetOnEvent(myCAP3_BASE,CAP_EVENT_4);
    //
    // Select CAP input.
    //
    CAP_selectCAPInput(myCAP3_BASE,CAP_INPUT_INPUTXBAR7);
    //
    // Sets a phase shift value count.
    //
    CAP_setPhaseShiftCount(myCAP3_BASE,0U);
    //
    // Enable counter loading with phase shift value.
    //
    CAP_enableLoadCounter(myCAP3_BASE);
    //
    // Configures Sync out signal mode.
    //
    CAP_setSyncOutMode(myCAP3_BASE,CAP_SYNC_OUT_SYNCI);
    //
    // Configures emulation mode.
    //
    CAP_setEmulationMode(myCAP3_BASE,CAP_EMULATION_STOP);
    //
    // Starts Time stamp counter for myCAP3.
    //
    CAP_startCounter(myCAP3_BASE);
    //
    // Enables time stamp capture for myCAP3.
    //
    CAP_enableTimeStampCapture(myCAP3_BASE);
    //
    // Re-arms the eCAP module for myCAP3.
    //
    CAP_reArm(myCAP3_BASE);
    //
    // Enables interrupt source for myCAP3.
    //
    CAP_enableInterrupt(myCAP3_BASE,(CAP_ISR_SOURCE_CAPTURE_EVENT_4));
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
    Interrupt_setPriority(INT_myCAP3, 0, 0);

    // Interrupt Setings for INT_myCAP3
    Interrupt_register(INT_myCAP3, &INT_myCAP3_ISR);
    Interrupt_enable(INT_myCAP3);
}
//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************
void SYNC_init(){
    SysCtl_setSyncOutputConfig(SYSCTL_SYNC_OUT_SRC_PWM1SYNCOUT);
    //
    // For EPWM1, the sync input is: SYSCTL_SYNC_IN_SRC_EXTSYNCIN1
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
//*****************************************************************************
//
// Clock switch Configurations
//
//*****************************************************************************
void Clockswitch()
{
    //
    // Reset up PLL control and clock dividers
    //
    SysCtl_setClock(CAP_SETCLOCK_CFG);

    //
    // Reset the APBCLK clock divider to 1 (divide by 1)
    //
    SysCtl_setAPBClock(SYSCTL_APBCLK_PRESCALE_1);

    //
    // These asserts will check that the #defines for the clock rates in
    // board.h match the actual rates that have been configured. Ensure
    // that the CAP can operate at 100Mhz.
    //
    ASSERT(SysCtl_getClock(DEVICE_OSCSRC_FREQ) == CAP_SYSCLK_FREQ);
    ASSERT(SysCtl_getAPBClock(DEVICE_OSCSRC_FREQ) == CAP_APBCLK_FREQ);
}
