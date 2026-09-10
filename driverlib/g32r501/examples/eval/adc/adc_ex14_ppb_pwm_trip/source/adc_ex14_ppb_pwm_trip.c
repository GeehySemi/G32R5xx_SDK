//###########################################################################
//
// FILE:    adc_ex14_ppb_pwm_trip.c
//
// TITLE:   ADC limits check and PWM trip in case of out of bound input.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1> ADC PPB PWM trip (adc_ppb_pwm_trip)</h1>
//!
//! This example demonstrates PWM tripping through ADC limit detection PPB
//! block. ADCAINT1 is configured to periodically trigger the ADCA channel 2
//! post initial software forced trigger. The limit detection post-processing
//! block(PPB) is configured and if the ADC results are outside of the
//! defined range, the post-processing block will generate an ADCxEVTy event.
//! This event is configured as PWM trip source through configuring PWM
//! XBAR and corresponding PWM's trip zone and digital compare sub-modules.
//! The example showcases
//!  - one-shot
//!  - cycle-by-cycle
//!  - and direct tripping of PWMs
//! through ADCAEVT1 source via Digital compare submodule.
//!
//! The default limits are 0LSBs and 3600LSBs. With VREFHI set to 3.3V, the
//! PPB will generate a trip event if the input voltage goes above about
//! 2.9V.
//!
//! \b External \b Connections \n
//!  - A2 should be connected to a signal to convert
//!  - Observe the following signals on an oscilloscope
//!    - PWM1(GPIO0 - GPIO1)
//!    - PWM2(GPIO2 - GPIO3)
//!    - PWM3(GPIO4 - GPIO5)
//!  -
//!
//! \b Watch \b Variables \n
//!  - adcA2Results - digital representation of the voltage on pin A2
//!
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
// 1. Modify some comments, macros, function names, and function contents.
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

// Uncomment to enable profiling
//#define ENABLE_PROFILING
#define RESULTS_BUFFER_SIZE     512U


//
// Globals
//
volatile uint16_t indexA = 0;                // Index into result buffer
volatile uint16_t bufferFull;                // Flag to indicate buffer is full
uint16_t adcA2Results[RESULTS_BUFFER_SIZE];  // ADC result buffer

//
// Characteristics of PWMs to be tripped
// PWM1 - frequency -> 10kHz, dutyA -> 50%, dutyB -> 50%, PWM1B - inverted
// PWM2 - frequency -> 2.5kHz, dutyA -> 20%, dutyB -> 50%, PWM2B - inverted
// PWM3 - frequency -> 5kHz, dutyA -> 70%, dutyB -> 50%, PWM3B - inverted
//
PWM_SignalParams pwmSignal1 =
            {10000, 0.5f, 0.5f, true, DEVICE_APBCLK_FREQ,
            PWM_COUNTER_MODE_UP_DOWN, PWM_CLOCK_DIVIDER_1,
            PWM_HSCLOCK_DIVIDER_1};

PWM_SignalParams pwmSignal2 =
            {25000, 0.2f, 0.5f, true, DEVICE_APBCLK_FREQ,
            PWM_COUNTER_MODE_UP_DOWN, PWM_CLOCK_DIVIDER_1,
            PWM_HSCLOCK_DIVIDER_1};

PWM_SignalParams pwmSignal3 =
            {5000, 0.7f, 0.5f, true, DEVICE_APBCLK_FREQ,
            PWM_COUNTER_MODE_UP_DOWN, PWM_CLOCK_DIVIDER_1,
            PWM_HSCLOCK_DIVIDER_1};

//
// Functional Prototypes
//

//
// ADC configuration related APIs
//
void configureADC(uint32_t adcBase);
void configureADCSOC(uint32_t adcBase, uint16_t channel);
void configureLimitDetectionPPB(uint16_t soc, uint16_t limitHigh,
                                uint16_t limitLow);

//
// PWM configuration related APIs
//
void initPWMGPIO(void);
void configureOSHTripSignal(uint32_t pwmBase);
void configureCBCTripSignal(uint32_t pwmBase);
void configureDirectTripSignal(uint32_t pwmBase);

#ifdef ENABLE_PROFILING
void setupProfileGpio(void);
#endif

//
// ISRs
//
void INT_ADCA1_IRQHandler(void);

void example_main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
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
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_ADCA1, &INT_ADCA1_IRQHandler);

#ifdef ENABLE_PROFILING
    //
    // Setup profiling GPIO
    //
    setupProfileGpio();
#endif

    //
    // For this case just init GPIO pins for PWM1, PWM2, PWM3
    //
    initPWMGPIO();

    //
    // Enable internal reference on ADCs
    //
    ADC_setVREF(ADCA_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);
    ADC_setVREF(ADCB_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);
    ADC_setVREF(ADCC_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);

    //
    // Configure the ADC and power it up
    //
    configureADC(ADCA_BASE);

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configuring PWM modules for desired frequency and duty
    //
    PWM_configureSignal(PWM1_BASE, &pwmSignal1);
    PWM_configureSignal(PWM2_BASE, &pwmSignal2);
    PWM_configureSignal(PWM3_BASE, &pwmSignal3);

    //
    // Configure ADCEVTx as one-shot trip signal for PWM1
    //
    configureOSHTripSignal(PWM1_BASE);

    //
    // Configure ADCEVTx as cycle-by-cycle trip signal for PWM2
    //
    configureCBCTripSignal(PWM2_BASE);

    //
    // Configure ADCEVTx as direct trip signal for PWM3
    //
    configureDirectTripSignal(PWM3_BASE);

    //
    // Setup the ADC for ADCAINT1 triggered conversions on channel 2
    //
    configureADCSOC(ADCA_BASE, 2U);

    //
    // Configure ADC post-processing limits
    // SOC0 will generate an interrupt if conversion is above or below limits
    //
    configureLimitDetectionPPB(0U, 3600U, 0U);

    //
    // Enable ADC interrupt
    //
    Interrupt_enable(INT_ADCA1);

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    //
    // Start PWM:
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Trigger ADC once through software
    //
    ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER0);

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    do
    {
    }
    while(1);
}

//
// configureOSHTripSignal - Configure ADCAEVT1 as one-shot trip signal for
//                          desired PWM instance
//
void configureOSHTripSignal(uint32_t pwmBase)
{
    //
    // Configure trip 7 input to be triggered by ADCAEVT1
    //
    XBAR_setPWMMuxConfig(XBAR_TRIP7, XBAR_PWM_MUX00_ADCAEVT1);

    //
    // Enable mux 0
    //
    XBAR_enablePWMMux(XBAR_TRIP7, XBAR_MUX00);

    //
    // Select Trip 7 input as input to DC module
    //
    PWM_selectDigitalCompareTripInput(pwmBase, PWM_DC_TRIP_TRIPIN7,
                                       PWM_DC_TYPE_DCAH);

    //
    // DCAEVT1 is generated when DCAH is high.
    //
    PWM_setTripZoneDigitalCompareEventCondition(pwmBase,PWM_TZ_DC_OUTPUT_A1,
                                                 PWM_TZ_EVENT_DCXH_HIGH);

    //
    // DCAEVT1 uses the unfiltered version of DCAEVT1
    //
    PWM_setDigitalCompareEventSource(pwmBase, PWM_DC_MODULE_A,
                            PWM_DC_EVENT_1, PWM_DC_EVENT_SOURCE_ORIG_SIGNAL);

    //
    // DCAEVT1 is asynchronous
    //
    PWM_setDigitalCompareEventSyncMode( pwmBase, PWM_DC_MODULE_A,
                              PWM_DC_EVENT_1,PWM_DC_EVENT_INPUT_NOT_SYNCED);

    //
    // Enable Trip zone signals
    //
    PWM_enableTripZoneSignals(pwmBase, PWM_TZ_ACTION_EVENT_DCAEVT1);

    //
    // Action on DCAEVT1
    // Force the PWMxA LOW and PWMxB HIGH
    //
    PWM_setTripZoneAction(pwmBase,
                           PWM_TZ_ACTION_EVENT_TZA,
                           PWM_TZ_ACTION_LOW);

    PWM_setTripZoneAction(pwmBase,
                           PWM_TZ_ACTION_EVENT_TZB,
                           PWM_TZ_ACTION_HIGH);

    //
    // Clear any spurious trip zone flags before enabling the interrupt
    //
    PWM_clearTripZoneFlag(pwmBase, PWM_TZ_ACTION_EVENT_DCAEVT1);

    PWM_clearOneShotTripZoneFlag(pwmBase, PWM_TZ_ACTION_EVENT_DCAEVT1);

    //
    // Enable TZ interrupt
    //
    PWM_enableTripZoneInterrupt(pwmBase, PWM_TZ_INTERRUPT_OST);
}

//
// configureCBCTripSignal - Configure ADCAEVT1 as cycle-by-cycle trip signal
//                          for desired PWM instance
//
void configureCBCTripSignal(uint32_t pwmBase)
{
    //
    // Configure trip 8 input to be triggered by ADCAEVT1
    //
    XBAR_setPWMMuxConfig(XBAR_TRIP8, XBAR_PWM_MUX00_ADCAEVT1);

    //
    // Enable mux 0
    //
    XBAR_enablePWMMux(XBAR_TRIP8, XBAR_MUX00);

    //
    // Select Trip 8 input as input to DC module
    //
    PWM_selectDigitalCompareTripInput(pwmBase, PWM_DC_TRIP_TRIPIN8,
                                       PWM_DC_TYPE_DCAH);

    //
    // DCAEVT2 is generated when DCAH is high.
    //
    PWM_setTripZoneDigitalCompareEventCondition(pwmBase, PWM_TZ_DC_OUTPUT_A2,
                                                 PWM_TZ_EVENT_DCXH_HIGH);

    //
    // DCAEVT2 uses the unfiltered version of DCAEVT2
    //
    PWM_setDigitalCompareEventSource(pwmBase, PWM_DC_MODULE_A,
                            PWM_DC_EVENT_2, PWM_DC_EVENT_SOURCE_ORIG_SIGNAL);

    //
    // DCAEVT2 is asynchronous
    //
    PWM_setDigitalCompareEventSyncMode(pwmBase, PWM_DC_MODULE_A,
                              PWM_DC_EVENT_2, PWM_DC_EVENT_INPUT_NOT_SYNCED);

    //
    // Enable Trip zone signals
    //
    PWM_enableTripZoneSignals(pwmBase, PWM_TZ_ACTION_EVENT_DCAEVT2);

    //
    // Configure CBC clear event
    //
    PWM_selectCycleByCycleTripZoneClearEvent(pwmBase,
                                       PWM_TZ_CBC_PULSE_CLR_CNTR_ZERO_PERIOD);

    //
    // Action on DCAEVT2
    // Force the PWMxA/PWMxB LOW
    //
    PWM_setTripZoneAction(pwmBase, PWM_TZ_ACTION_EVENT_TZA,
                           PWM_TZ_ACTION_LOW);

    PWM_setTripZoneAction(pwmBase, PWM_TZ_ACTION_EVENT_TZB,
                           PWM_TZ_ACTION_HIGH);

    //
    // Clear any spurious trip zone flags before enabling the interrupt
    //
    PWM_clearTripZoneFlag(pwmBase, PWM_TZ_ACTION_EVENT_DCAEVT2);

    PWM_clearCycleByCycleTripZoneFlag(pwmBase, PWM_TZ_ACTION_EVENT_DCAEVT2);

    //
    // Enable TZ interrupt
    //
    PWM_enableTripZoneInterrupt(pwmBase, PWM_TZ_INTERRUPT_CBC);
}

//
// configureDirectTripSignal - Configure ADCAEVT1 as direct trip signal for
//                             desired PWM instance
//
void configureDirectTripSignal(uint32_t pwmBase)
{
    //
    // Configure trip 9 input to be triggered by ADCAEVT1
    //
    XBAR_setPWMMuxConfig(XBAR_TRIP9, XBAR_PWM_MUX00_ADCAEVT1);

    //
    // Enable mux 0
    //
    XBAR_enablePWMMux(XBAR_TRIP9, XBAR_MUX00);

    //
    // Select Trip 9 input as input to DC module
    //
    PWM_selectDigitalCompareTripInput(pwmBase, PWM_DC_TRIP_TRIPIN9,
                                       PWM_DC_TYPE_DCAH);
    PWM_selectDigitalCompareTripInput(pwmBase, PWM_DC_TRIP_TRIPIN9,
                                       PWM_DC_TYPE_DCBH);

    //
    // DCAEVT1 is generated when DCAH is high. DCBEVT2 is generated when DCBH
    // is high
    //
    PWM_setTripZoneDigitalCompareEventCondition(pwmBase, PWM_TZ_DC_OUTPUT_A1,
                                                 PWM_TZ_EVENT_DCXH_HIGH);
    PWM_setTripZoneDigitalCompareEventCondition(pwmBase, PWM_TZ_DC_OUTPUT_B2,
                                                 PWM_TZ_EVENT_DCXH_HIGH);

    //
    // DCAEVT1/DCBEVT2 uses the unfiltered version of DCAEVT1/DCBEVT2
    //
    PWM_setDigitalCompareEventSource(pwmBase, PWM_DC_MODULE_A,
                            PWM_DC_EVENT_1, PWM_DC_EVENT_SOURCE_ORIG_SIGNAL);
    PWM_setDigitalCompareEventSource(pwmBase, PWM_DC_MODULE_B,
                            PWM_DC_EVENT_2, PWM_DC_EVENT_SOURCE_ORIG_SIGNAL);

    //
    // DCAEVT1/ DCBEVT2 is asynchronous
    //
    PWM_setDigitalCompareEventSyncMode(pwmBase, PWM_DC_MODULE_A,
                              PWM_DC_EVENT_1, PWM_DC_EVENT_INPUT_NOT_SYNCED);
    PWM_setDigitalCompareEventSyncMode(pwmBase, PWM_DC_MODULE_B,
                              PWM_DC_EVENT_2, PWM_DC_EVENT_INPUT_NOT_SYNCED);

    //
    // Action on TZA/TZB
    // Force the PWMxA LOW and PWMxB HIGH
    //
    PWM_setTripZoneAction(pwmBase,
                           PWM_TZ_ACTION_EVENT_DCAEVT1,
                           PWM_TZ_ACTION_LOW);

    PWM_setTripZoneAction(pwmBase,
                           PWM_TZ_ACTION_EVENT_DCAEVT2,
                           PWM_TZ_ACTION_HIGH);

    //
    // Clear any spurious trip zone flags before enabling the interrupt
    //
    PWM_clearTripZoneFlag(pwmBase, (PWM_TZ_ACTION_EVENT_DCAEVT1 |
                                      PWM_TZ_ACTION_EVENT_DCAEVT2));

    //
    // Enable TZ interrupt
    //
    PWM_enableTripZoneInterrupt(pwmBase, (PWM_TZ_ACTION_EVENT_DCAEVT1 |
                                            PWM_TZ_ACTION_EVENT_DCAEVT2));
}

//
// configureADC - Write ADC configurations and power up the ADC for both
//                ADC A and ADC B
//
void configureADC(uint32_t adcBase)
{
    //
    // Set ADCCLK divider to /2
    //
    ADC_setPrescaler(adcBase, ADC_CLK_DIV_2_0);


    //
    // Set pulse positions to late
    //
    ADC_setInterruptPulseMode(adcBase, ADC_PULSE_END_OF_CONV);

    //
    // Power up the ADCs and then delay for 1 ms
    //
    ADC_enableConverter(adcBase);

    //
    // Delay for 1ms to allow ADC time to power up
    //
    DEVICE_DELAY_US(1000);
}

//
// configureLimitDetectionPPB - Configure high and low limits for ADCPPB
//
void configureLimitDetectionPPB(uint16_t soc, uint16_t limitHigh,
                                uint16_t limitLow)
{
    //
    // Associate PPB1 with soc
    //
    ADC_setupPPB(ADCA_BASE, ADC_PPB_NUMBER1, (ADC_SOCNumber)soc);

    //
    // Set high and low limits
    //
    ADC_setPPBTripLimits(ADCA_BASE, ADC_PPB_NUMBER1, limitHigh, limitLow);

    //
    // Enable high and low limit PPB events
    //
    ADC_enablePPBEvent(ADCA_BASE, ADC_PPB_NUMBER1, (ADC_EVT_TRIPHI |
                                                    ADC_EVT_TRIPLO));

    //
    // Configure CBCEN
    //
    WRPRT_DISABLE;
    HWREGH(ADCA_BASE + ADC_O_PPB1CONFIG) |= ADC_PPB1CONFIG_CBCEN;
    WRPRT_ENABLE;
}

//
// configureADCSOC - Setup ADC PWM channel and trigger settings
//
void configureADCSOC(uint32_t adcBase, uint16_t channel)
{
    uint16_t acqps;

    //
    // Determine minimum acquisition window (in SYSCLKS)
    //
    acqps = 8; // 80ns
    //
    // - NOTE: A longer sampling window will be required if the ADC driving
    //   source is less than ideal (an ideal source would be a high bandwidth
    //   op-amp with a small series resistance). See TI application report
    //   SPRACT6 for guidance on ADC driver design.
    //

    //
    // Select the channels to convert and end of conversion flag
    // ADCA
    //
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)channel, acqps);

    //
    // Configure ADCINT1 as SOC0 trigger
    //
    ADC_setInterruptSOCTrigger(adcBase, ADC_SOC_NUMBER0,
                               ADC_INT_SOC_TRIGGER_ADCINT1);

    //
    // Enable continuous mode
    //
    ADC_enableContinuousMode(ADCA_BASE, ADC_INT_NUMBER1);

    //
    // Configure source as EOC1, clear & enable the interrupt
    //
    ADC_setInterruptSource(adcBase, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_clearInterruptStatus(adcBase, ADC_INT_NUMBER1);
    ADC_enableInterrupt(adcBase, ADC_INT_NUMBER1);
}

//
// adcA1ISR - ADC A Interrupt 1 ISR
//
void INT_ADCA1_IRQHandler(void)
{
#ifdef ENABLE_PROFILING
    //
    // Setting Profiling GPIO12 : Takes 3 cycles
    //
    HWREG(GPIODATA_BASE  + GPIO_O_GPASET) = 0x1000;
#endif

    //
    // Add the latest result to the buffer
    //
    adcA2Results[indexA++] = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);

    //
    // Set the bufferFull flag if the buffer is full
    //
    if(RESULTS_BUFFER_SIZE <= indexA)
    {
        indexA = 0;
    }

#ifdef ENABLE_PROFILING
    //
    // Resetting Profiling GPIO12
    //
    HWREG(GPIODATA_BASE  + GPIO_O_GPACLEAR) = 0x1000;
#endif
}

//
// initPWMGPIO - Configure PWM1-PWM3 GPIO
//
void initPWMGPIO(void)
{
    //
    // Disable pull up on GPIO0-5 and configure them as PWMs
    //
    GPIO_setDrivingCapability(0,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_0_PWM1A);

    GPIO_setDrivingCapability(1,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(1, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_1_PWM1B);

    GPIO_setDrivingCapability(2,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(2, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_2_PWM2A);

    GPIO_setDrivingCapability(3,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(3, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_3_PWM2B);

    GPIO_setDrivingCapability(4,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(4, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_4_PWM3A);

    GPIO_setDrivingCapability(5,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(5, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_5_PWM3B);
}

#ifdef ENABLE_PROFILING
void setupProfileGpio(void)
{
    GPIO_setDrivingCapability(12,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setDirectionMode(12,GPIO_DIR_MODE_OUT);
    GPIO_setQualificationMode(12,GPIO_QUAL_SYNC);
    GPIO_setPinConfig(GPIO_12_GPIO12);
    GPIO_writePin(12,0);
}

#endif
//
// End of file
//
