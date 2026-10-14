//###########################################################################
//
// FILE:    sdf_ex4_pwm_sync_cpuread.c
//
// TITLE:   SDF PWM Sync Example
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1> SDF PWM Sync </h1>
//!
//! In this example, SDF filter data is read by CPU in SDF ISR routine. The
//! SDF configuration is shown below:
//!     - SDF1 is used in this example.
//!     - MODE0 Input control mode selected
//!     - Comparator settings
//!         - Sinc3 filter selected
//!         - OSR = 32
//!         - hlt = 0x7FFF (Higher threshold setting)
//!         - llt  = 0x0000(Lower threshold setting)
//!  -  Data filter settings
//!      - All the 4 filter modules enabled
//!      - Sinc3 filter selected
//!      - OSR = 256
//!      - All the 4 filters are synchronized by using PWM
//!       (Master Filter enable bit)
//!      - Filter output represented in 16 bit format
//!      - In order to convert 25 bit Data filter
//!        into 16 bit format user needs to right shift by 10 bits for
//!        Sinc3 filter with OSR = 256
//!  - Interrupt module settings for SDF filter
//!      - All the 4 higher threshold comparator interrupts disabled
//!      - All the 4 lower threshold comparator interrupts disabled
//!      - All the 4 modulator failure interrupts disabled
//!      - All the 4 filter will generate interrupt when a new filter data
//!        is available
//!
//! \b External \b Connections \n
//!    Connect Sigma-Delta streams to (SD-D1, SD-C1 to SD-D4,SD-C4)
//!    on GPIO24-GPIO31
//!
//! \b Watch \b Variables \n
//! -  \b filter1Result - Output of filter 1
//! -  \b filter2Result - Output of filter 2
//! -  \b filter3Result - Output of filter 3
//! -  \b filter4Result - Output of filter 4
//!
//
//###########################################################################
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
// 1. Modified some function and macro definition and variable names.
// 2. Updated interrupt handling to use NVIC functions.
//
//###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define MAX_SAMPLES               1024
#define PWM_TIMER_TBPRD           65535  // PWM Period register

//
// Globals
//
uint32_t sdfInstance;
uint32_t pwmInstance = PWM8_BASE; // PWM 8 for synchronizing SDF1 filters

SECTION_SRAM1_SHARE_DATA int16_t  filter1Result[MAX_SAMPLES];
SECTION_SRAM1_SHARE_DATA int16_t  filter2Result[MAX_SAMPLES];
SECTION_SRAM1_SHARE_DATA int16_t  filter3Result[MAX_SAMPLES];
SECTION_SRAM1_SHARE_DATA int16_t  filter4Result[MAX_SAMPLES];

//
// Function Prototypes
//
void configureSDFPins(void);
void initPWM(uint32_t pwmInstance);
void sdf1ErrorISR(void);
void sdfDR1ISR(void);

//
// Main
//
void example_main(void)
{
    uint16_t  hlt, llt;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Setup GPIO by disabling pin locks and enabling pullups
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
    // Set the priority group to indicate the PREEMPT and SUB priority bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    //
    // Set the global and group interrupt priority to allow CPU interrupts
    // with higher priority
    //
    Interrupt_setPriority(INT_SDF1DR1, 1, 0);
    Interrupt_setPriority(INT_SDF1, 0, 0);

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    Interrupt_register(INT_SDF1DR1, sdfDR1ISR);
    Interrupt_register(INT_SDF1, sdf1ErrorISR);

    //
    // Enable SDF1 Error and DR interrupts
    //
    Interrupt_enable(INT_SDF1);
    Interrupt_enable(INT_SDF1DR1);

    //
    // Configure GPIO pins as SDF pins
    //
    configureSDFPins();

    //
    // Select SDF1
    //
    sdfInstance = SDF1_BASE;

    //
    // Input Control Module:
    // Configure Modulator Clock rate = Modulator data rate
    //
    SDF_setupModulatorClock(sdfInstance, SDF_FILTER_1,
                             SDF_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDF_setupModulatorClock(sdfInstance, SDF_FILTER_2,
                             SDF_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDF_setupModulatorClock(sdfInstance, SDF_FILTER_3,
                             SDF_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDF_setupModulatorClock(sdfInstance, SDF_FILTER_4,
                             SDF_MODULATOR_CLK_EQUAL_DATA_RATE);

    //
    // Comparator Module
    //
    hlt = 0x7FFF;    //Over value threshold settings
    llt = 0x0000;    //Under value threshold settings

    //
    // Configure Comparator module's comparator filter type and comparator's OSR
    // value, higher threshold, lower threshold
    //
    SDF_configComparator(sdfInstance,
        ((uint16_t)SDF_FILTER_1 | SDF_FILTER_SINC_3 | SDF_SET_OSR(32)),
        (SDF_GET_LOW_THRESHOLD(llt) | SDF_GET_HIGH_THRESHOLD(hlt)), 0);
    SDF_configComparator(sdfInstance,
        ((uint16_t)SDF_FILTER_2 | SDF_FILTER_SINC_3 | SDF_SET_OSR(32)),
        (SDF_GET_LOW_THRESHOLD(llt) | SDF_GET_HIGH_THRESHOLD(hlt)), 0);
    SDF_configComparator(sdfInstance,
        ((uint16_t)SDF_FILTER_3 | SDF_FILTER_SINC_3 | SDF_SET_OSR(32)),
        (SDF_GET_LOW_THRESHOLD(llt) | SDF_GET_HIGH_THRESHOLD(hlt)), 0);
    SDF_configComparator(sdfInstance,
        ((uint16_t)SDF_FILTER_4 | SDF_FILTER_SINC_3 | SDF_SET_OSR(32)),
        (SDF_GET_LOW_THRESHOLD(llt) | SDF_GET_HIGH_THRESHOLD(hlt)), 0);

    //
    // Data filter Module
    //
    // Configure Data filter modules filter type, OSR value and
    // enable / disable data filter
    //
    SDF_configDataFilter(sdfInstance, ((uint16_t)SDF_FILTER_1 | SDF_FILTER_SINC_3 |
           SDF_SET_OSR(256)), (SDF_DATA_FORMAT_16_BIT | SDF_FILTER_ENABLE |
           SDF_SHIFT_VALUE(0x000A)));

    SDF_configDataFilter(sdfInstance, ((uint16_t)SDF_FILTER_2 | SDF_FILTER_SINC_3 |
           SDF_SET_OSR(256)), (SDF_DATA_FORMAT_16_BIT | SDF_FILTER_ENABLE |
           SDF_SHIFT_VALUE(0x000A)));

    SDF_configDataFilter(sdfInstance, ((uint16_t)SDF_FILTER_3 | SDF_FILTER_SINC_3 |
           SDF_SET_OSR(256)), (SDF_DATA_FORMAT_16_BIT | SDF_FILTER_ENABLE |
           SDF_SHIFT_VALUE(0x000A)));

    SDF_configDataFilter(sdfInstance, ((uint16_t)SDF_FILTER_4 | SDF_FILTER_SINC_3 |
           SDF_SET_OSR(256)), (SDF_DATA_FORMAT_16_BIT | SDF_FILTER_ENABLE |
           SDF_SHIFT_VALUE(0x000A)));

    //
    // Enable Master filter bit: Unless this bit is set none of the filter modules
    // can be enabled. All the filter modules are synchronized when master filter
    // bit is enabled after individual filter modules are enabled.
    //
    SDF_enableMasterFilter(sdfInstance);

    //
    // PWM signals can synchronize SDF1 filters. Enabling PWM sync for SDF
    // filters.
    //
    SDF_enableExternalReset(sdfInstance, SDF_FILTER_1);
    SDF_enableExternalReset(sdfInstance, SDF_FILTER_2);
    SDF_enableExternalReset(sdfInstance, SDF_FILTER_3);
    SDF_enableExternalReset(sdfInstance, SDF_FILTER_4);

    SDF_setPWMSyncSource(sdfInstance, SDF_FILTER_1, SDF_SYNC_PWM8_SOCA);
    SDF_setPWMSyncSource(sdfInstance, SDF_FILTER_2, SDF_SYNC_PWM8_SOCA);
    SDF_setPWMSyncSource(sdfInstance, SDF_FILTER_3, SDF_SYNC_PWM8_SOCA);
    SDF_setPWMSyncSource(sdfInstance, SDF_FILTER_4, SDF_SYNC_PWM8_SOCA);

    //
    // Init PWMs
    //
    initPWM(pwmInstance);

    //
    // Enable interrupts
    //
    // Following SDF interrupts can be enabled / disabled using this function.
    //  Enable / disable comparator high threshold
    //  Enable / disable comparator low threshold
    //  Enable / disable modulator clock failure
    //  Enable / disable filter acknowledge
    //
    SDF_enableInterrupt(sdfInstance, SDF_FILTER_1,
            (SDF_MODULATOR_FAILURE_INTERRUPT |
             SDF_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDF_enableInterrupt(sdfInstance, SDF_FILTER_2,
            (SDF_MODULATOR_FAILURE_INTERRUPT |
             SDF_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDF_enableInterrupt(sdfInstance, SDF_FILTER_3,
            (SDF_MODULATOR_FAILURE_INTERRUPT |
             SDF_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDF_enableInterrupt(sdfInstance, SDF_FILTER_4,
            (SDF_MODULATOR_FAILURE_INTERRUPT |
             SDF_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDF_disableInterrupt(sdfInstance, SDF_FILTER_1,
            (SDF_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDF_LOW_LEVEL_THRESHOLD_INTERRUPT));

    SDF_disableInterrupt(sdfInstance, SDF_FILTER_2,
            (SDF_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDF_LOW_LEVEL_THRESHOLD_INTERRUPT));

    SDF_disableInterrupt(sdfInstance, SDF_FILTER_3,
            (SDF_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDF_LOW_LEVEL_THRESHOLD_INTERRUPT));

    SDF_disableInterrupt(sdfInstance, SDF_FILTER_4,
            (SDF_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDF_LOW_LEVEL_THRESHOLD_INTERRUPT));

    while((HWREGH(pwmInstance + PWM_O_TBCTR)) < 550);

    //
    // Enable master interrupt so that any of the filter interrupts can trigger
    // by SDF interrupt to CPU
    //
    SDF_enableMasterInterrupt(sdfInstance);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(1);
}

//
// sdf1ErrorISR - SDF1 Error ISR
//
void sdf1ErrorISR(void)
{
    //
    // Clear SDF flag register (INTFLG)
    //
    SDF_clearInterruptFlag(SDF1_BASE, SDF_MASTER_INTERRUPT_FLAG |
                            0xFFFF);
}

//
// sdfDR1ISR - SDF DR1 ISR
//
void sdfDR1ISR(void)
{
    static uint16_t loopCounter1 = 0;

    SDF_setOutputDataFormat(SDF1_BASE, SDF_FILTER_1,
                             SDF_DATA_FORMAT_16_BIT);

    //
    // Read SDF flag register (INTFLG)
    //
    if(loopCounter1 >= MAX_SAMPLES)
    {
        loopCounter1 = 0;;
    }

    while((HWREG(SDF1_BASE + SDF_O_SDIFLG) & 0xF000U) != 0xF000U)
    {
    }

    filter1Result[loopCounter1] =
           (int16_t)(SDF_getFilterData(SDF1_BASE, SDF_FILTER_1) >> 16U);
    filter2Result[loopCounter1] =
           (int16_t)(SDF_getFilterData(SDF1_BASE, SDF_FILTER_2) >> 16U);
    filter3Result[loopCounter1] =
           (int16_t)(SDF_getFilterData(SDF1_BASE, SDF_FILTER_3) >> 16U);
    filter4Result[loopCounter1++] =
           (int16_t)(SDF_getFilterData(SDF1_BASE, SDF_FILTER_4) >> 16U);


    //
    // Clear SDF flag register (INTFLG)
    //
    SDF_clearInterruptFlag(SDF1_BASE, SDF_MASTER_INTERRUPT_FLAG |
                            SDF_FILTER_1_NEW_DATA_FLAG            |
                            SDF_FILTER_2_NEW_DATA_FLAG            |
                            SDF_FILTER_3_NEW_DATA_FLAG            |
                            SDF_FILTER_4_NEW_DATA_FLAG);
}

//
// configureSDFPins - Configure SDF GPIOs
//
void configureSDFPins(void)
{
    uint16_t pin;
    for(pin = 24; pin <= 31; pin++)
    {
        GPIO_setDirectionMode(pin, GPIO_DIR_MODE_IN);
        GPIO_setMasterCore(pin, GPIO_CORE_CPU0);
        GPIO_setDrivingCapability(pin,GPIO_DRIVE_LEVEL_VERY_HIGH);
        GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(pin, GPIO_QUAL_ASYNC);
    }

    //
    // Configure GPIO16-GPIO31 as SDF pins
    //
    GPIO_setPinConfig(GPIO_24_SD1_D1);
    GPIO_setPinConfig(GPIO_25_SD1_C1);
    GPIO_setPinConfig(GPIO_26_SD1_D2);
    GPIO_setPinConfig(GPIO_27_SD1_C2);
    GPIO_setPinConfig(GPIO_28_SD1_D3);
    GPIO_setPinConfig(GPIO_29_SD1_C3);
    GPIO_setPinConfig(GPIO_30_SD1_D4);
    GPIO_setPinConfig(GPIO_31_SD1_C4);
}

//
// done - Function to halt debugger and stop application
//
void done(void)
{
    ESTOP0;
    for(;;);
}

//
// initPWM - Initialize specified PWM settings
//
void initPWM(uint32_t pwmInstance)
{
    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Setup TBCLK: Configure timer period = 801 TBCLKs, phase = 0 &
    // clear counter
    //
    PWM_setTimeBasePeriod(pwmInstance, PWM_TIMER_TBPRD);
    PWM_setPhaseShift(pwmInstance, 0U);
    PWM_setTimeBaseCounter(pwmInstance, 0U);

    //
    // Set CMPA value
    //
    PWM_setCounterCompareValue(pwmInstance, PWM_COUNTER_COMPARE_A, 200U);

    //
    // Setup counter mode
    //
    PWM_setTimeBaseCounterMode(pwmInstance, PWM_COUNTER_MODE_UP);
    PWM_setClockPrescaler(pwmInstance,
                           PWM_CLOCK_DIVIDER_1,
                           PWM_HSCLOCK_DIVIDER_1);

    //
    // Set actions:
    // Toggle PWMxA on event A, up-count
    // Toggle PWMxB on event A, up-count
    //
    PWM_setActionQualifierAction(PWM1_BASE,
                                 PWM_AQ_OUTPUT_A,
                                 PWM_AQ_OUTPUT_TOGGLE,
                                 PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    PWM_setActionQualifierAction(PWM1_BASE,
                                 PWM_AQ_OUTPUT_B,
                                 PWM_AQ_OUTPUT_TOGGLE,
                                 PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

    //
    // Configure SOCA signal
    //
    //
    PWM_setADCTriggerSource(PWM1_BASE, PWM_SOC_A, PWM_SOC_TBCTR_U_CMPA);
    PWM_setADCTriggerEventPrescale(PWM1_BASE, PWM_SOC_A, 1);

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

//
// End of file
//
