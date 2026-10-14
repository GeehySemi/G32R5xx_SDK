//#############################################################################
//
// FILE:    pwm_ex9_dma.c
//
// TITLE:   PWM Using DMA.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1>PWM DMA</h1>
//!
//! This example configures PWM1 and DMA as follows:
//!  - PWM1 is set up to generate PWM waveforms
//!  - DMA5 is set up to update the CMPAHR, CMPA, CMPBHR and CMPB every period
//!    with the next value in the configuration array. This allows the user to
//!    create a DMA enabled fifo for all the CMPx and CMPxHR registers to
//!    generate unconventional PWM waveforms.
//!  - DMA6 is set up to update the TBPHSHR, TBPHS, TBPRDHR and TBPRD every
//!    period with the next value in the configuration array.
//!  - Other registers such as AQCTL can be controlled through the DMA as well
//!    by following the same procedure. (Not used in this example)
//!
//! \b External \b Connections \n
//! - GPIO0 PWM1A
//! - GPIO1 PWM1B
//!
//! \b Watch \b Variables \n
//! - None.
//
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
// 1. Modified some function and macro definition and variable names.
// 2. Updated interrupt handling to use NVIC functions.
//
//###########################################################################

#include "driverlib.h"
#include "device.h"
#include "board.h"

#define PWM_TIMER_TBPRD    20000UL

//
// Defines
//
#define BURST       4              // 4 words per transfer
#define TRANSFER    4              // 4 transfers (different configs)

//
// Globals
//
__attribute__((section("sram3.share_data"))) uint16_t phasePeriodConfigs[TRANSFER*BURST] = {
//  TBPHSHR ,   TBPHS   ,  TBPRDHR ,   TBPRD,
    9  << 8 ,    17U    ,  13 << 8 ,   2000U,
    10 << 8 ,    18U    ,  14 << 8 ,   4000U,
    11 << 8 ,    19U    ,  15 << 8 ,   6000U,
    12 << 8 ,    20U    ,  16 << 8 ,   8000U,
};

__attribute__((section("sram3.share_data"))) uint16_t compareConfigs[TRANSFER*BURST] = {
//  CMPAHR  ,   CMPA   ,   CMPBHR  ,   CMPB ,
    1 << 8  ,  1001U   ,   5 << 8  ,   1000U,
    2 << 8  ,  2001U   ,   6 << 8  ,   2000U,
    3 << 8  ,  3001U   ,   7 << 8  ,   3000U,
    4 << 8  ,  4001U   ,   8 << 8  ,   4000U,
};

//
// Function Prototypes
//
void initDMA(void);
void initPWM(uint32_t base);

void INT_DMA_CH5_IRQHandler(void);
void INT_DMA_CH6_IRQHandler(void);
void INT_PWM1_IRQHandler(void);

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
    // Disable pin locks and enable internal pull ups.
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
    // Assign the interrupt service routines to PWM interrupts
    //
    Interrupt_register(INT_PWM1, &INT_PWM1_IRQHandler);
    Interrupt_register(INT_DMA_CH5, &INT_DMA_CH5_IRQHandler);
    Interrupt_register(INT_DMA_CH6, &INT_DMA_CH6_IRQHandler);

    //
    // Configure PWM and Input X-BAR Pins
    //
    Board_init();

    //
    // Disable sync(Freeze clock to PWM as well). GTBCLKSYNC is applicable
    // only for multiple core devices. Uncomment the below statement if
    // applicable.
    //
    // SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_GTBCLKSYNC);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    Interrupt_setPriority(INT_PWM1,2,0);
    Interrupt_setPriority(INT_DMA_CH5,1,0);
    Interrupt_setPriority(INT_DMA_CH6,0,0);

    initDMA();
    initPWM(myPWM1_BASE);

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);


    // Enable PWM interrupts
    //
    Interrupt_enable(INT_PWM1);
    Interrupt_enable(INT_DMA_CH5);
    Interrupt_enable(INT_DMA_CH6);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    WRPRT_DISABLE;
    DMA_startChannel(DMA_CH5_BASE);
    DMA_startChannel(DMA_CH6_BASE);

    //
    // IDLE loop. Just sit and loop forever (optional):
    //

    for (;;)
    {

    }
}


//
// DMA setup channels.
//
void initDMA()
{
    //
    // Initialize DMA
    //
    DMA_initController();

    //
    // DMA CH5
    //
    DMA_configAddresses(DMA_CH5_BASE, (uint16_t *)(myPWM1_BASE + PWM_O_CMPA),
                        compareConfigs);
    DMA_configBurst(DMA_CH5_BASE, BURST, 1, 1);
    DMA_configTransfer(DMA_CH5_BASE, TRANSFER, 1, 1-BURST);
    DMA_configMode(DMA_CH5_BASE, DMA_TRIGGER_PWM1SOCA, DMA_CFG_ONESHOT_DISABLE |
                   DMA_CFG_CONTINUOUS_ENABLE | DMA_CFG_SIZE_16BIT);

    //
    // Configure DMA Ch5 interrupts
    //
    DMA_setInterruptMode(DMA_CH5_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH5_BASE);
    DMA_enableTrigger(DMA_CH5_BASE);

    //
    // DMA CH6
    //
    DMA_configAddresses(DMA_CH6_BASE, (uint16_t *)(myPWM1_BASE + PWM_O_TBPHS),
                        phasePeriodConfigs);
    DMA_configBurst(DMA_CH6_BASE, BURST, 1, 1);
    DMA_configTransfer(DMA_CH6_BASE, TRANSFER, 1, 1-BURST);
    DMA_configMode(DMA_CH6_BASE, DMA_TRIGGER_PWM1SOCA, DMA_CFG_ONESHOT_DISABLE |
                   DMA_CFG_CONTINUOUS_ENABLE | DMA_CFG_SIZE_16BIT);

    //
    // Configure DMA Ch6 interrupts
    //
    DMA_setInterruptMode(DMA_CH6_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH6_BASE);
    DMA_enableTrigger(DMA_CH6_BASE);

}

//
// DMA Channel 5 ISR
//
void INT_DMA_CH5_IRQHandler(void)
{
    return;
}

//
// DMA Channel 6 ISR
//
void INT_DMA_CH6_IRQHandler(void)
{
    return;
}


//
// pwm1ISR - PWM 1 ISR
//
void INT_PWM1_IRQHandler(void)
{
    //
    // Un-comment below to check the status of each register after CTR=0
    //
    // ESTOP0;

    //
    // Clear INT flag for this timer
    //
    PWM_clearEventTriggerInterruptFlag(myPWM1_BASE);
}


void initPWM(uint32_t base)
{
    PWM_setEmulationMode(base, PWM_EMULATION_STOP_AFTER_FULL_CYCLE);

    //
    // Set-up TBCLK
    //
    PWM_setTimeBasePeriod(base, PWM_TIMER_TBPRD);
    PWM_setPhaseShift(base, 0U);
    PWM_setTimeBaseCounter(base, 0U);

    //
    // Set Compare values
    //
    PWM_setCounterCompareValue(base,
                                PWM_COUNTER_COMPARE_A,
                                PWM_TIMER_TBPRD/2);
    PWM_setCounterCompareValue(base,
                                PWM_COUNTER_COMPARE_B,
                                PWM_TIMER_TBPRD/2);

    //
    // Set up counter mode
    //
    PWM_setTimeBaseCounterMode(base, PWM_COUNTER_MODE_UP);
    PWM_disablePhaseShiftLoad(base);
    PWM_setClockPrescaler(base,
                           PWM_CLOCK_DIVIDER_64,
                           PWM_HSCLOCK_DIVIDER_1);

    //
    // Set up shadowing
    //
    PWM_setCounterCompareShadowLoadMode(base,
                                         PWM_COUNTER_COMPARE_A,
                                         PWM_COMP_LOAD_ON_CNTR_ZERO);
    PWM_setCounterCompareShadowLoadMode(base,
                                         PWM_COUNTER_COMPARE_B,
                                         PWM_COMP_LOAD_ON_CNTR_ZERO);

    //
    // Set actions
    //

    PWM_setActionQualifierAction(base,
                                  PWM_AQ_OUTPUT_A,
                                  PWM_AQ_OUTPUT_HIGH,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);


    PWM_setActionQualifierAction(base,
                                  PWM_AQ_OUTPUT_B,
                                  PWM_AQ_OUTPUT_HIGH,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

    PWM_setActionQualifierAction(base,
                                  PWM_AQ_OUTPUT_A,
                                  PWM_AQ_OUTPUT_LOW,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    PWM_setActionQualifierAction(base,
                                  PWM_AQ_OUTPUT_B,
                                  PWM_AQ_OUTPUT_LOW,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);


    //
    // Interrupt where we will change the Compare Values
    // Select INT on Time base counter zero event,
    // Enable INT, generate INT on 1st event
    //
    PWM_setInterruptSource(base, PWM_INT_TBCTR_ZERO);
    PWM_enableInterrupt(base);
    PWM_setInterruptEventCount(base, 1U);

    PWM_enableADCTrigger(base, PWM_SOC_A);
    PWM_setADCTriggerSource(base,
                             PWM_SOC_A,
                             PWM_SOC_TBCTR_ZERO);
    PWM_setADCTriggerEventPrescale(base,
                                    PWM_SOC_A,
                                       1);
    PWM_clearADCTriggerFlag(base,
                             PWM_SOC_A);
}

