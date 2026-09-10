//###########################################################################
//
// FILE:    adc_ex6_soc_continuous_dma.c
//
// TITLE:   ADC continuous conversions read by DMA.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1> ADC Continuous Conversions Read by DMA (adc_soc_continuous_dma)</h1>
//!
//! This example sets up two ADC channels to convert simultaneously. The
//! results will be transferred by the DMA into a buffer in RAM.
//!
//! \b External \b Connections \n
//!  - A3 & C3 pins should be connected to signals to convert
//!
//! \b Watch \b Variables \n
//! - \b myADC0DataBuffer \b: a digital representation of the voltage on pin A3\n
//! - \b myADC1DataBuffer \b: a digital representation of the voltage on pin C3\n
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
#include "board.h"

//
// Function Prototypes
//
void INT_ADCA1_IRQHandler(void);
void INT_DMA_CH1_IRQHandler(void);

void configurPWM(uint32_t pwmBase);
void initializeDMA(void);
void configureDMAChannels(void);

//
// Defines
//
#define RESULTS_BUFFER_SIZE     1024 //buffer for storing conversion results
                                //(size must be multiple of 16)

//
// Globals
//
__attribute__((section("sram3.share_data"))) uint16_t  myADC0DataBuffer[RESULTS_BUFFER_SIZE];
__attribute__((section("sram3.share_data"))) uint16_t  myADC1DataBuffer[RESULTS_BUFFER_SIZE];

#define RAMFUNC __attribute__((section("itcm.ramfunc")))

volatile uint16_t done;

void example_main(void)
{
    uint16_t resultsIndex;

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
    // Board Initializatrion
    // - Configure the ADCA & ADCC and power it up
    // - Setup the ADC for continuous conversions on channels A3 and C3
    // - Set up ISR for ADCA INT1 - occurs after first conversion
    // - Enable specific NVIC & CPU interrupts: ADCA INT1 - Group 1, interrupt 1
    //
    Board_init();

    //
    // Set up ISRs used by this example
    // ISR for DMA ch1 - occurs when DMA transfer is complete
    //
    Interrupt_register(INT_DMA_CH1, &INT_DMA_CH1_IRQHandler);

    //
    // Set the priority group to indicate the PREEMPT and SUB priortiy bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_7_6_SUB_5_0);

    //
    // Set the global and group priority to allow CPU interrupts
    // with higher priority
    //
    Interrupt_setPriority(INT_DMA_CH1, 2, 1);

    //
    // Enable specific NVIC & CPU interrupts:
    // DMA interrupt - Group 7, interrupt 1
    //
    Interrupt_enable(INT_DMA_CH1);

    //
    // Stop the PWM clock
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Call the set up function for PWM 2
    //
    configurPWM(PWM2_BASE);

    //
    // Start the PWM clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Initialize the DMA & configure DMA channels 1 & 2
    //
    initializeDMA();
    configureDMAChannels();

    //
    // Initialize results buffer
    //
    for(resultsIndex = 0; resultsIndex < RESULTS_BUFFER_SIZE; resultsIndex++)
    {
        myADC0DataBuffer[resultsIndex] = 0;
        myADC1DataBuffer[resultsIndex] = 0;
    }

    //
    // Clearing all pending interrupt flags
    //
    DMA_clearTriggerFlag(DMA_CH1_BASE);   // DMA channel 1
    DMA_clearTriggerFlag(DMA_CH2_BASE);   // DMA channel 2
    HWREGH(myADC0_BASE + ADC_O_INTFLGCLR) = 0x3U; // ADCA
    HWREGH(myADC1_BASE + ADC_O_INTFLGCLR) = 0x3U; // ADCC
    PWM_forceADCTriggerEventCountInit(PWM2_BASE, PWM_SOC_A); // PWM2 SOCA
    PWM_clearADCTriggerFlag(PWM2_BASE, PWM_SOC_A);    // PWM2 SOCA

    //
    // Enable continuous operation by setting the last SOC to re-trigger
    // the first
    //
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER0,    // ADCA
                               ADC_INT_SOC_TRIGGER_ADCINT2);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER0,    // ADCC
                               ADC_INT_SOC_TRIGGER_ADCINT2);

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    //
    // Start DMA
    //
    done = 0;
    DMA_startChannel(DMA_CH1_BASE);
    DMA_startChannel(DMA_CH2_BASE);

    //
    // Finally, enable the SOCA trigger from PWM. This will kick off
    // conversions at the next PWM event.
    //
    PWM_enableADCTrigger(PWM2_BASE, PWM_SOC_A);

    //
    // Loop until the ISR signals the transfer is complete
    //
    while(done == 0)
    {
        __asm(" NOP");
    }
    ESTOP0;
}

//
// adcA1ISR - This is called after the very first conversion and will disable
//                      the PWM SOC to avoid re-triggering problems.
//
RAMFUNC void INT_ADCA1_IRQHandler(void)
{
    //
    // Remove PWM trigger
    //
    PWM_disableADCTrigger(PWM2_BASE, PWM_SOC_A);

    //
    // Disable this interrupt from happening again
    //
    Interrupt_disable(INT_ADCA1);
}

//
// dmach1ISR - This is called at the end of the DMA transfer, the conversions
//              are stopped by removing the trigger of the first SOC from
//              the last.
//
RAMFUNC void INT_DMA_CH1_IRQHandler(void)
{
    //
    // Stop the ADC by removing the trigger for SOC0
    //
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER0,
                               ADC_INT_SOC_TRIGGER_NONE);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER0,
                               ADC_INT_SOC_TRIGGER_NONE);
    done = 1;
}

//
// configurPWM - Set up the PWM2 module so that the A output has a period
//                 of 40us with a 50% duty. The SOCA signal is coincident with
//                 the rising edge of this.
//
void configurPWM(uint32_t pwmBase)
{
    //
    // Make the timer count up with a period of 40us
    //
    HWREGH(pwmBase + PWM_O_TBCTL) = 0x0000U;
    PWM_setTimeBasePeriod(pwmBase, 4000U);

    //
    // Set the A output on zero and reset on CMPA
    //
    PWM_setActionQualifierAction(pwmBase, PWM_AQ_OUTPUT_A,
                                  PWM_AQ_OUTPUT_HIGH,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    PWM_setActionQualifierAction(pwmBase, PWM_AQ_OUTPUT_A,
                                  PWM_AQ_OUTPUT_LOW,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    //
    // Set CMPA to 20us to get a 50% duty
    //
    PWM_setCounterCompareValue(pwmBase, PWM_COUNTER_COMPARE_A, 2000U);

    //
    // Start ADC when timer equals zero (note: don't enable yet)
    //
    PWM_setADCTriggerSource(pwmBase, PWM_SOC_A, PWM_SOC_TBCTR_ZERO);
    PWM_setADCTriggerEventPrescale(pwmBase, PWM_SOC_A, 1U);

    //
    // Enable initialization of the SOCA event counter. Since we are
    // disabling the ETSEL.SOCAEN bit, we need a way to reset the SOCACNT.
    // Hence, enable the counter initialize control.
    //
    PWM_enableADCTriggerEventCountInit(pwmBase, PWM_SOC_A);
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
// configureDMAChannels - Initialize DMA ch 1 to transfer ADCA results
//                        and DMA ch 2 to transfer ADCB results
//
void configureDMAChannels(void)
{
    //
    // DMA channel 1 set up for ADCA
    //
    DMA_configAddresses(DMA_CH1_BASE, (uint16_t *)&myADC0DataBuffer,
                        (uint16_t *)ADCARESULT_BASE);

    //
    // Perform enough 16-word bursts to fill the results buffer. Data will be
    // transferred 32 bits at a time hence the address steps below.
    //
    DMA_configBurst(DMA_CH1_BASE, 16, 2, 2);
    DMA_configTransfer(DMA_CH1_BASE, (RESULTS_BUFFER_SIZE >> 4), -14, 2);
    DMA_configMode(DMA_CH1_BASE, DMA_TRIGGER_ADCA2,
                   (DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_DISABLE |
                    DMA_CFG_SIZE_32BIT));

    DMA_enableTrigger(DMA_CH1_BASE);
    DMA_disableOverrunInterrupt(DMA_CH1_BASE);
    DMA_setInterruptMode(DMA_CH1_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH1_BASE);

    //
    // DMA channel 2 set up for ADCC
    //
    DMA_configAddresses(DMA_CH2_BASE, (uint16_t *)&myADC1DataBuffer,
                        (uint16_t *)ADCCRESULT_BASE);

    //
    // Perform enough 16-word bursts to fill the results buffer. Data will be
    // transferred 32 bits at a time hence the address steps below.
    //
    DMA_configBurst(DMA_CH2_BASE, 16, 2, 2);
    DMA_configTransfer(DMA_CH2_BASE, (RESULTS_BUFFER_SIZE >> 4), -14, 2);
    DMA_configMode(DMA_CH2_BASE, DMA_TRIGGER_ADCA2,
                   (DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_DISABLE |
                    DMA_CFG_SIZE_32BIT));

    DMA_enableTrigger(DMA_CH2_BASE);
    DMA_disableOverrunInterrupt(DMA_CH2_BASE);
    DMA_setInterruptMode(DMA_CH2_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH2_BASE);
}

//
// End of file
//
