//###########################################################################
//
// FILE:    sdf_ex3_filter_sync_dmaread.c
//
// TITLE:   SDF Filter Sync DMA Example.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1> SDF Filter Sync DMA </h1>
//!
//! In this example, SDF filter data is read by DMA. The
//! SDF configuration is shown below:
//!  - SDF1 used in this example.
//!  - MODE0 Input control mode selected
//!  - Comparator settings
//!      - Sinc3 filter selected
//!      - OSR = 32
//!      - hlt = 0x7FFF (Higher threshold setting)
//!      - llt  = 0x0000(Lower threshold setting)
//!  - Data filter settings
//!      - All the 4 filter modules enabled
//!      - Sinc3 filter selected
//!      - OSR = 256
//!      - All the 4 filters are synchronized by using MFE
//!       (Master Filter enable bit)
//!      - Filter output represented in 16 bit format
//!      - In order to convert 25 bit Data filter
//!        into 16 bit format user needs to right shift by 10 bits for
//!        Sinc3 filter with OSR = 256
//!  - Interrupt module settings for SDF filter
//!      - All the 4 higher threshold comparator interrupts disabled
//!      - All the 4 lower threshold comparator interrupts disabled
//!      - All the 4 modulator failure interrupts disabled
//!      - All the 4 filter will generate interrupt when a new filter
//!        data is available
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
#define MAX_SAMPLES                               1024

//
// Globals
//
uint32_t sdfInstance;

SECTION_SRAM1_SHARE_DATA int16_t  filter1Result[MAX_SAMPLES];
SECTION_SRAM1_SHARE_DATA int16_t  filter2Result[MAX_SAMPLES];
SECTION_SRAM1_SHARE_DATA int16_t  filter3Result[MAX_SAMPLES];
SECTION_SRAM1_SHARE_DATA int16_t  filter4Result[MAX_SAMPLES];

// Pointers for DMA source & destination addresses
int16_t *dma1SrcAddr, *dma1DestAddr;
int16_t *dma2SrcAddr, *dma2DestAddr;
int16_t *dma3SrcAddr, *dma3DestAddr;
int16_t *dma4SrcAddr, *dma4DestAddr;

// Variable to update DMA transfer status
volatile uint16_t dmaDone = 0;

//
// Function Prototypes
//
void dmaCh1ISR(void);
void dmaCh2ISR(void);
void dmaCh3ISR(void);
void dmaCh4ISR(void);
void initializeDMA(void);
void configureDMAChannels(void);
void configureSDFPins(void);

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
    Interrupt_setPriority(INT_DMA_CH1, 0, 0);
    Interrupt_setPriority(INT_DMA_CH2, 1, 0);
    Interrupt_setPriority(INT_DMA_CH3, 2, 0);
    Interrupt_setPriority(INT_DMA_CH4, 3, 0);

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    Interrupt_register(INT_DMA_CH1, dmaCh1ISR);
    Interrupt_register(INT_DMA_CH2, dmaCh2ISR);
    Interrupt_register(INT_DMA_CH3, dmaCh3ISR);
    Interrupt_register(INT_DMA_CH4, dmaCh4ISR);

    //
    // Enable DMA INTn in the NVIC: Group 7 __interrupt 1-6
    //
    Interrupt_enable(INT_DMA_CH1);
    Interrupt_enable(INT_DMA_CH2);
    Interrupt_enable(INT_DMA_CH3);
    Interrupt_enable(INT_DMA_CH4);

    //
    // Configure DMA for the transfer
    //
    initializeDMA();
    configureDMAChannels();

    //
    // Configure GPIO pins as SDF pins
    //
    configureSDFPins();

    sdfInstance = SDF1_BASE;

    //
    // Input Control Unit
    //
    // Configure Input Control Unit: Modulator Clock rate = Modulator data rate
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
    hlt = 0x7FFF;  // Over value threshold settings
    llt = 0x0000;  // Under value threshold settings

    //
    // Configure Comparator module's comparator filter type and comparator's
    // OSR value, higher threshold, lower threshold
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
    // Enable Master filter bit: Unless this bit is set none of the filter
    // modules can be enabled. All the filter modules are synchronized when
    // master filter bit is enabled after individual filter modules are enabled.
    //
    SDF_enableMasterFilter(sdfInstance);

    //
    // PWM11.CMPC, PWM11.CMPD signals can synchronize SDF1 filters and
    // PWM12.CMPC and PWM12.CMPD signals can synchronize SDF2 filters. This
    // option is not being used in this example for SDF1.
    //
    SDF_disableExternalReset(sdfInstance, SDF_FILTER_1);
    SDF_disableExternalReset(sdfInstance, SDF_FILTER_2);
    SDF_disableExternalReset(sdfInstance, SDF_FILTER_3);
    SDF_disableExternalReset(sdfInstance, SDF_FILTER_4);

    //
    // Enable interrupts
    //
    // Following SDF interrupts can be enabled / disabled using this function.
    //    Enable / disable comparator high threshold
    //    Enable / disable comparator low threshold
    //    Enable / disable modulator clock failure
    //    Enable / disable filter acknowledge
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
// dmaCh1ISR - DMA Channel 1 ISR
//
void dmaCh1ISR(void)
{
    dmaDone |= 0x0001;
    ESTOP0;
}

//
// dmaCh2ISR - DMA Channel 2 ISR
//
void dmaCh2ISR(void)
{
    dmaDone |= 0x0002;
    ESTOP0;
}

//
// dmaCh3ISR - DMA Channel 3 ISR
//
void dmaCh3ISR(void)
{
    dmaDone |= 0x0004;
    ESTOP0;
}

//
// dmaCh4ISR - DMA Channel 4 ISR
//
void dmaCh4ISR(void)
{
    dmaDone |= 0x0008;
    ESTOP0;
}

//
// initializeDMA - Initialize DMA through hard reset
//
void initializeDMA(void)
{
    //
    // Perform a hard reset on DMA
    //
    DMA_initController();

    //
    // Allow DMA to run free on emulation suspend
    //
    DMA_setEmulationMode(DMA_EMULATION_FREE_RUN);
}

//
// configureDMAChannels - Configure DMA channels 1,2,3, and 4
//
void configureDMAChannels(void)
{
    //
    // Initialize the DMA channel addresses
    //
    dma1SrcAddr = (int16_t *)(0x40003C2E);
    dma1DestAddr = &filter1Result[0];
    dma2SrcAddr = (int16_t *)(0x40003C4E);
    dma2DestAddr = &filter2Result[0];
    dma3SrcAddr = (int16_t *)(0x40003C6E);
    dma3DestAddr = &filter3Result[0];
    dma4SrcAddr = (int16_t *)(0x40003C8E);
    dma4DestAddr = &filter4Result[0];

    DMA_configAddresses(DMA_CH1_BASE, dma1DestAddr, dma1SrcAddr);
    DMA_configAddresses(DMA_CH2_BASE, dma2DestAddr, dma2SrcAddr);
    DMA_configAddresses(DMA_CH3_BASE, dma3DestAddr, dma3SrcAddr);
    DMA_configAddresses(DMA_CH4_BASE, dma4DestAddr, dma4SrcAddr);

    //
    // Set up to use 16-bit data size
    // Pointers are based on 16-bit words
    // Increment by 1 (16 16-bit words)
    //

    //
    // BURST size = 1 | Source step size = 0 | Dest step size += 1
    //
    DMA_configBurst(DMA_CH1_BASE, 1, 0, 1);
    DMA_configBurst(DMA_CH2_BASE, 1, 0, 1);
    DMA_configBurst(DMA_CH3_BASE, 1, 0, 1);
    DMA_configBurst(DMA_CH4_BASE, 1, 0, 1);

    //
    // Transfer size = 0x400 | Source step size = 0 | Dest step size += 1
    //
    DMA_configTransfer(DMA_CH1_BASE, 0x400, 0, 1);
    DMA_configTransfer(DMA_CH2_BASE, 0x400, 0, 1);
    DMA_configTransfer(DMA_CH3_BASE, 0x400, 0, 1);
    DMA_configTransfer(DMA_CH4_BASE, 0x400, 0, 1);

    //
    // Configure wrap for DMA channels 1-4
    //
    DMA_configWrap(DMA_CH1_BASE, 0xFFFF, 0, 0xFFFF, 0);
    DMA_configWrap(DMA_CH2_BASE, 0xFFFF, 0, 0xFFFF, 0);
    DMA_configWrap(DMA_CH3_BASE, 0xFFFF, 0, 0xFFFF, 0);
    DMA_configWrap(DMA_CH4_BASE, 0xFFFF, 0, 0xFFFF, 0);

    //
    // Configure mode for DMA channels 1-4
    //

    // DMA channel 1
    DMA_configMode(DMA_CH1_BASE, DMA_TRIGGER_SDF1FLT1,
                  (DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_DISABLE |
                   DMA_CFG_SIZE_16BIT));

    DMA_enableTrigger(DMA_CH1_BASE);
    DMA_disableOverrunInterrupt(DMA_CH1_BASE);
    DMA_setInterruptMode(DMA_CH1_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH1_BASE);

    // DMA channel 2
    DMA_configMode(DMA_CH2_BASE, DMA_TRIGGER_SDF1FLT2,
                  (DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_DISABLE |
                   DMA_CFG_SIZE_16BIT));

    DMA_enableTrigger(DMA_CH2_BASE);
    DMA_disableOverrunInterrupt(DMA_CH2_BASE);
    DMA_setInterruptMode(DMA_CH2_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH2_BASE);

    // DMA channel 3
    DMA_configMode(DMA_CH3_BASE, DMA_TRIGGER_SDF1FLT3,
                  (DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_DISABLE |
                   DMA_CFG_SIZE_16BIT));

    DMA_enableTrigger(DMA_CH3_BASE);
    DMA_disableOverrunInterrupt(DMA_CH3_BASE);
    DMA_setInterruptMode(DMA_CH3_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH3_BASE);

    // DMA channel 4
    DMA_configMode(DMA_CH4_BASE, DMA_TRIGGER_SDF1FLT4,
                  (DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_DISABLE |
                   DMA_CFG_SIZE_16BIT));

    DMA_enableTrigger(DMA_CH4_BASE);
    DMA_disableOverrunInterrupt(DMA_CH4_BASE);
    DMA_setInterruptMode(DMA_CH4_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH4_BASE);

    //
    // Start DMA channels
    //
    DMA_startChannel(DMA_CH1_BASE);
    DMA_startChannel(DMA_CH2_BASE);
    DMA_startChannel(DMA_CH3_BASE);
    DMA_startChannel(DMA_CH4_BASE);
}

//
// End of file
//
