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
    CAP_init();
    GPIO_init();
    OTHER_init();
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
    // GPIO2 -> myGPIO0 Pinmux
    GPIO_setPinConfig(GPIO_2_GPIO2);
    //
    // OTHER -> myOTHER0 Pinmux
    //
    GPIO_setPinConfig(myOTHER0_XCLKOUT_PIN_CONFIG);
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
    // HRCAP module configuration for myCAP0_HR_BASE (part of myCAP0_BASE).
    //
    // Enable High resolution clock
    //
    HRCAP_enableHighResolutionClock(myCAP0_HR_BASE);
    DEVICE_DELAY_US(1); // 1us delay as mentioned in HRCAP chapter of TRM
    //
    // Enable High Resolution module
    //
    HRCAP_enableHighResolution(myCAP0_HR_BASE);
    DEVICE_DELAY_US(1); // 1us delay as mentioned in HRCAP chapter of TRM
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
    CAP_setEventPolarity(myCAP0_BASE,CAP_EVENT_1,CAP_EVNT_RISING_EDGE);
    CAP_setEventPolarity(myCAP0_BASE,CAP_EVENT_2,CAP_EVNT_FALLING_EDGE);
    CAP_setEventPolarity(myCAP0_BASE,CAP_EVENT_3,CAP_EVNT_RISING_EDGE);
    CAP_setEventPolarity(myCAP0_BASE,CAP_EVENT_4,CAP_EVNT_FALLING_EDGE);
    //
    // Configure counter reset on events
    //
    CAP_disableCounterResetOnEvent(myCAP0_BASE,CAP_EVENT_1);
    CAP_disableCounterResetOnEvent(myCAP0_BASE,CAP_EVENT_2);
    CAP_disableCounterResetOnEvent(myCAP0_BASE,CAP_EVENT_3);
    CAP_disableCounterResetOnEvent(myCAP0_BASE,CAP_EVENT_4);
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
    // Resets eCAP counters and flags.
    //
    CAP_resetCounters(myCAP0_BASE);
    //
    // Configures emulation mode.
    //
    CAP_setEmulationMode(myCAP0_BASE,CAP_EMULATION_STOP);
    //
    // Starts Time stamp counter for myCAP0.
    //
    CAP_startCounter(myCAP0_BASE);
    //
    // Enables time stamp capture for myCAP0.
    //
    CAP_enableTimeStampCapture(myCAP0_BASE);
    //
    // Re-arms the eCAP module for myCAP0.
    //
    CAP_reArm(myCAP0_BASE);
    //
    // Enables interrupt source for myCAP0.
    //
    CAP_enableInterrupt(myCAP0_BASE,(CAP_ISR_SOURCE_CAPTURE_EVENT_4));
    //
    // myCAP0_HR_BASE Calibration Settings
    //
    // Set calibration period (register is in SYSCLK cycles), 1.6ms recommended
    //
    HWREG(myCAP0_HR_BASE + HRCAP_O_HRCALPRD) = (uint32_t) (100e9 * (1.6/1000));
    //
    // Configure in continuous calibration mode
    //
    HRCAP_setCalibrationMode(myCAP0_HR_BASE);
    //
    // Enable HRCAP calibration interrupts
    //
    HRCAP_enableCalibrationInterrupt(myCAP0_HR_BASE, (HRCAP_CALIBRATION_DONE
         | HRCAP_CALIBRATION_PERIOD_OVERFLOW));
    //
    // Start HR calibration
    //
    HRCAP_startCalibration(myCAP0_HR_BASE);

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
    GPIO_setPadConfig(myGPIO0, GPIO_PIN_TYPE_STD);
    GPIO_setDrivingCapability(myGPIO0,GPIO_DRIVE_LEVEL_VERY_HIGH);
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
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    //
    // Set the global and group interrupt priority to allow CPU interrupts
    // with higher priority
    Interrupt_setPriority(INT_myCAP0, 1, 0);
    Interrupt_setPriority(INT_myCAP0_HR, 0, 0);

    // Interrupt Setings for INT_myCAP0
    Interrupt_register(INT_myCAP0, &INT_myCAP0_ISR);
    Interrupt_enable(INT_myCAP0);

    // Interrupt Setings for INT_myCAP0_HR
    Interrupt_register(INT_myCAP0_HR, &INT_myCAP0_HR_ISR);
    Interrupt_enable(INT_myCAP0_HR);
}
//*****************************************************************************
//
// OTHER Configurations
//
//*****************************************************************************
void OTHER_init(){
    //myOTHER0 initialization

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
