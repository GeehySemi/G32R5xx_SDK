//###########################################################################
//
// FILE:    sdf_ex5_filter_sync_fifo_cpuread.c
//
// TITLE:   SDF Type 1 Filter FIFO Example.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1> SDF Type 1 Filter FIFO </h1>
//!
//! This example configures SDF1 filter to demonstrate data read through
//! CPU in FIFO & non-FIFO mode. Data filter is configured in mode 0
//! to select SINC3 filter with OSR of 256. Filter output is configured
//! for 16-bit format and data shift of 10 is used.
//!
//! This example demonstrates the FIFO usage if enabled. FIFO length is set
//! at 16 and data ready interrupt is configured to be triggered when FIFO is
//! full. In this example, SDF filter data is read by CPU in SDF Data Ready
//! ISR routine.
//!
//! \b External \b Connections \n
//!    Connect Sigma-Delta streams to (SD-D1, SD-C1 to SD-D4,SD-C4)
//!    on GPIO24-GPIO31
//!
//! \b Watch \b Variables \n
//! -  \b filter1Result - Output of filter 1
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
#define FIFO_INT_NUM              16U
#define SDF_FILTER_ENABLE         0x2U

//
// Macro to enable FIFO mode. Make it zero to disable
// FIFO mode.
//
#define ENABLE_FIFO               1

//
// Globals
//
SECTION_SRAM1_SHARE_DATA int16_t  filter1Result[MAX_SAMPLES];

//
// Function Prototypes
//
void configureSDFPins(void);

//
// ISRs
//
void sdfFIFO1ISR(void);
void sdf1ErrorISR(void);

//
// Main
//
void example_main(void)
{
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
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_7_6_SUB_5_0);

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
    Interrupt_register(INT_SDF1DR1, sdfFIFO1ISR);
    Interrupt_register(INT_SDF1, sdf1ErrorISR);

    //
    // Enable SDF1 interrupts(Data Ready & Error interrupts)
    //
    Interrupt_enableMaster();
    Interrupt_enable(INT_SDF1DR1);
    Interrupt_enable(INT_SDF1);

    //
    // Configure GPIO pins as SDF pins
    //
    configureSDFPins();

    //
    // Input Control Unit
    //
    // Configure Input Control Unit: Modulator Clock rate = Modulator data rate
    //
    SDF_setupModulatorClock(SDF1_BASE, SDF_FILTER_1,
                             SDF_MODULATOR_CLK_EQUAL_DATA_RATE);

    //
    // Data Filter Unit
    //

    // Configure Data Filter Unit - filter type, OSR value and
    // enable / disable data filter
    //
    SDF_configDataFilter(SDF1_BASE, ((uint16_t)SDF_FILTER_1 | SDF_FILTER_SINC_3 |
           SDF_SET_OSR(256)), (SDF_DATA_FORMAT_16_BIT | SDF_FILTER_ENABLE |
           SDF_SHIFT_VALUE(0x000A)));

#if (ENABLE_FIFO)
        //
        // Set data ready interrupt source as fifo interrupt
        //
        SDF_setDataReadyInterruptSource(SDF1_BASE, SDF_FILTER_1,
                                         SDF_DATA_READY_SOURCE_FIFO);

        //
        // Enable FIFO and set the FIFO interrupt level
        //
        SDF_enableFIFOBuffer(SDF1_BASE, SDF_FILTER_1);

        SDF_setFIFOInterruptLevel(SDF1_BASE, SDF_FILTER_1, FIFO_INT_NUM);

        SDF_enableInterrupt(SDF1_BASE, SDF_FILTER_1,
                         (SDF_FIFO_INTERRUPT | SDF_FIFO_OVERFLOW_INTERRUPT));
#else
        //
        // Set data ready interrupt source as fifo interrupt
        //
        SDF_setDataReadyInterruptSource(SDF1_BASE, SDF_FILTER_1,
                                         SDF_DATA_READY_SOURCE_DIRECT);

        SDF_enableInterrupt(SDF1_BASE, SDF_FILTER_1,
                             SDF_DATA_FILTER_ACKNOWLEDGE_INTERRUPT);
#endif


    //
    // Enable Master filter bit: Unless this bit is set none of the filter
    // modules can be enabled. All the filter modules are synchronized when
    // master filter bit is enabled after individual filter modules are enabled.
    //
    SDF_enableMasterFilter(SDF1_BASE);

    //
    // PWM11.CMPC, PWM11.CMPD, PWM12.CMPC and PWM12.CMPD signals cannot
    // synchronize the filters. This option is not being used in this example.
    //
    SDF_disableExternalReset(SDF1_BASE, SDF_FILTER_1);

    //
    // Enable modulator failure interrupt, disable threshold interrupts
    //
    SDF_enableInterrupt(SDF1_BASE, SDF_FILTER_1,
                         SDF_MODULATOR_FAILURE_INTERRUPT);

    SDF_disableInterrupt(SDF1_BASE, SDF_FILTER_1,
                        (SDF_HIGH_LEVEL_THRESHOLD_INTERRUPT |
                         SDF_LOW_LEVEL_THRESHOLD_INTERRUPT));

    //
    // Enable master interrupt so that any of the filter interrupts can trigger
    // by SDF interrupt to CPU
    //
    SDF_enableMasterInterrupt(SDF1_BASE);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Wait for an interrupt
    //
    while(1);
}

//
// sdf1ErrorISR - SDF1 Error ISR
//
void sdf1ErrorISR(void)
{
    //
    // Clear SDF flag register (SDIFLG)
    //
    SDF_clearInterruptFlag(SDF1_BASE, SDF_MASTER_INTERRUPT_FLAG |
                            0xFFFF);
}


//
// sdfFIFO1ISR - SDF FIFO1 ISR
//
void sdfFIFO1ISR(void)
{
    uint16_t i;
    static uint16_t loopCounter1 = 0;

    SDF_setOutputDataFormat(SDF1_BASE, SDF_FILTER_1,
                             SDF_DATA_FORMAT_16_BIT);

    //
    // Read SDF flag register (SDIFLG)
    //
    if(loopCounter1 >= MAX_SAMPLES)
    {
        ESTOP0;
    }
    else if(SDF_getFIFOISRStatus(SDF1_BASE, SDF_FILTER_1) == 0x1U)
    {
        for(i = 0; i < FIFO_INT_NUM; i++)
        {
            filter1Result[loopCounter1++] =
                         (int16_t)(SDF_getFIFOData(SDF1_BASE,
                                                    SDF_FILTER_1) >> 16U);
        }

    }
    else if(SDF_getNewFilterDataStatus(SDF1_BASE, SDF_FILTER_1) == 0x1U)
    {
        filter1Result[loopCounter1++] =
               (int16_t)(SDF_getFilterData(SDF1_BASE, SDF_FILTER_1) >> 16U);
    }

    //
    // Clear SDF flag register (SDIFLG)
    //
    SDF_clearInterruptFlag(SDF1_BASE, SDF_MASTER_INTERRUPT_FLAG |
                           SDF_FILTER_1_FIFO_INTERRUPT_FLAG     |
                           SDF_FILTER_1_NEW_DATA_FLAG           |
                           SDF_FILTER_1_FIFO_OVERFLOW_FLAG);
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
// End of file
//
