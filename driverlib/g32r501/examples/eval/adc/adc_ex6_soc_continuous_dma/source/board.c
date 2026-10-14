//###########################################################################
//
// FILE:    board.c
//
// TITLE:   Board source file
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
    AS_init();
    ADC_init();
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

}

//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
void ADC_init()
{
    //myADC0 initialization

    // ADC Initialization: Write ADC configurations and power up the ADC
    // Configures the ADC module's offset trim
    ADC_setOffsetTrimAll(ADC_REFERENCE_INTERNAL,ADC_REFERENCE_3_3V);
    // Configures the analog-to-digital converter module prescaler.
    ADC_setPrescaler(myADC0_BASE, ADC_CLK_DIV_2_0);
    // Sets the timing of the end-of-conversion pulse
    ADC_setInterruptPulseMode(myADC0_BASE, ADC_PULSE_END_OF_CONV);
    // Powers up the analog-to-digital converter core.
    ADC_enableConverter(myADC0_BASE);
    // Delay for 1ms to allow ADC time to power up
    DEVICE_DELAY_US(5000);

    // SOC Configuration: Setup ADC PWM channel and trigger settings
    // Disables SOC burst mode.
    ADC_disableBurstMode(myADC0_BASE);
    // Sets the priority mode of the SOCs.
    ADC_setSOCPriority(myADC0_BASE, ADC_PRI_ALL_ROUND_ROBIN);
    // Start of Conversion 0 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 0
    //     Trigger          : ADC_TRIGGER_PWM2_SOCA
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_PWM2_SOCA, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 1 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 1
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 2 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 2
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER2, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 3 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 3
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER3, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 4 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 4
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER4, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 5 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 5
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER5, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 6 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 6
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER6, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 7 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 7
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER7, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 8 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 8
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER8, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER8, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 9 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 9
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER9, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER9, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 10 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 10
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER10, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER10, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 11 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 11
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER11, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER11, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 12 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 12
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER12, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER12, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 13 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 13
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER13, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER13, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 14 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 14
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER14, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER14, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 15 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 15
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER15, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER15, ADC_INT_SOC_TRIGGER_ADCINT1);
    // ADC Interrupt 1 Configuration
    //     SOC/EOC number  : 0
    //     Interrupt Source: enabled
    //     Continuous Mode : enabled
    ADC_setInterruptSource(myADC0_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_enableInterrupt(myADC0_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);
    ADC_enableContinuousMode(myADC0_BASE, ADC_INT_NUMBER1);
    // ADC Interrupt 2 Configuration
    //     SOC/EOC number  : 15
    //     Interrupt Source: enabled
    //     Continuous Mode : enabled
    ADC_setInterruptSource(myADC0_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER15);
    ADC_enableInterrupt(myADC0_BASE, ADC_INT_NUMBER2);
    ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER2);
    ADC_enableContinuousMode(myADC0_BASE, ADC_INT_NUMBER2);
    // ADC Interrupt 3 Configuration
    //     SOC/EOC number  : 0
    //     Interrupt Source: disabled
    //     Continuous Mode : disabled
    ADC_setInterruptSource(myADC0_BASE, ADC_INT_NUMBER3, ADC_SOC_NUMBER0);
    ADC_disableInterrupt(myADC0_BASE, ADC_INT_NUMBER3);
    ADC_disableContinuousMode(myADC0_BASE, ADC_INT_NUMBER3);
    // ADC Interrupt 4 Configuration
    //     SOC/EOC number  : 0
    //     Interrupt Source: disabled
    //     Continuous Mode : disabled
    ADC_setInterruptSource(myADC0_BASE, ADC_INT_NUMBER4, ADC_SOC_NUMBER0);
    ADC_disableInterrupt(myADC0_BASE, ADC_INT_NUMBER4);
    ADC_disableContinuousMode(myADC0_BASE, ADC_INT_NUMBER4);

    //myADC1 initialization

    // ADC Initialization: Write ADC configurations and power up the ADC
    // Configures the ADC module's offset trim
    ADC_setOffsetTrimAll(ADC_REFERENCE_INTERNAL,ADC_REFERENCE_3_3V);
    // Configures the analog-to-digital converter module prescaler.
    ADC_setPrescaler(myADC1_BASE, ADC_CLK_DIV_2_0);
    // Sets the timing of the end-of-conversion pulse
    ADC_setInterruptPulseMode(myADC1_BASE, ADC_PULSE_END_OF_CONV);
    // Powers up the analog-to-digital converter core.
    ADC_enableConverter(myADC1_BASE);
    // Delay for 1ms to allow ADC time to power up
    DEVICE_DELAY_US(5000);

    // SOC Configuration: Setup ADC PWM channel and trigger settings
    // Disables SOC burst mode.
    ADC_disableBurstMode(myADC1_BASE);
    // Sets the priority mode of the SOCs.
    ADC_setSOCPriority(myADC1_BASE, ADC_PRI_ALL_ROUND_ROBIN);
    // Start of Conversion 0 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 0
    //     Trigger          : ADC_TRIGGER_PWM2_SOCA
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_PWM2_SOCA, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 1 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 1
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 2 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 2
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER2, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 3 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 3
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER3, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 4 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 4
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER4, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 5 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 5
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER5, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 6 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 6
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER6, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 7 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 7
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER7, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 8 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 8
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER8, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER8, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 9 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 9
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER9, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER9, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 10 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 10
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER10, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER10, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 11 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 11
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER11, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER11, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 12 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 12
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER12, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER12, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 13 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 13
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER13, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER13, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 14 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 14
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER14, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER14, ADC_INT_SOC_TRIGGER_ADCINT1);
    // Start of Conversion 15 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 15
    //     Trigger          : ADC_TRIGGER_SW_ONLY
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER15, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER15, ADC_INT_SOC_TRIGGER_ADCINT1);
    // ADC Interrupt 1 Configuration
    //     SOC/EOC number  : 0
    //     Interrupt Source: enabled
    //     Continuous Mode : enabled
    ADC_setInterruptSource(myADC1_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_enableInterrupt(myADC1_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(myADC1_BASE, ADC_INT_NUMBER1);
    ADC_enableContinuousMode(myADC1_BASE, ADC_INT_NUMBER1);
    // ADC Interrupt 2 Configuration
    //     SOC/EOC number  : 15
    //     Interrupt Source: enabled
    //     Continuous Mode : enabled
    ADC_setInterruptSource(myADC1_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER15);
    ADC_enableInterrupt(myADC1_BASE, ADC_INT_NUMBER2);
    ADC_clearInterruptStatus(myADC1_BASE, ADC_INT_NUMBER2);
    ADC_enableContinuousMode(myADC1_BASE, ADC_INT_NUMBER2);
    // ADC Interrupt 3 Configuration
    //     SOC/EOC number  : 0
    //     Interrupt Source: disabled
    //     Continuous Mode : disabled
    ADC_setInterruptSource(myADC1_BASE, ADC_INT_NUMBER3, ADC_SOC_NUMBER0);
    ADC_disableInterrupt(myADC1_BASE, ADC_INT_NUMBER3);
    ADC_disableContinuousMode(myADC1_BASE, ADC_INT_NUMBER3);
    // ADC Interrupt 4 Configuration
    //     SOC/EOC number  : 0
    //     Interrupt Source: disabled
    //     Continuous Mode : disabled
    ADC_setInterruptSource(myADC1_BASE, ADC_INT_NUMBER4, ADC_SOC_NUMBER0);
    ADC_disableInterrupt(myADC1_BASE, ADC_INT_NUMBER4);
    ADC_disableContinuousMode(myADC1_BASE, ADC_INT_NUMBER4);
}

//*****************************************************************************
//
// AS Configurations
//
//*****************************************************************************
void AS_init()
{
    // asysctl initialization
    // Disables the temperature sensor output to the ADC.
    AS_disableTemperatureSensor();
    // Set the analog voltage reference selection to internal.
    AS_setAnalogReferenceInternal( AS_VREFHIA | AS_VREFHIB | AS_VREFHIC );
    // Set the internal analog voltage reference selection to 1.65V.
    AS_setAnalogReference1P65( AS_VREFHIA | AS_VREFHIB | AS_VREFHIC );
}
//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init()
{
    // Interrupt Setings for INT_myADC0_1
    Interrupt_register(INT_myADC0_1, &INT_ADCA1_IRQHandler);

    //
    // Set the priority group to indicate the PREEMPT and SUB priortiy bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    //
    // Set the global and group priority to allow CPU interrupts
    // with higher priority
    //
    Interrupt_setPriority(INT_DMA_CH1, 2, 0);

    Interrupt_enable(INT_myADC0_1);
}
