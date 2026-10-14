//###########################################################################
//
// FILE:    board.c
//
// TITLE:   Board source file
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//###########################################################################
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
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
// - 2026-06-30:
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
    AS_init();
    ADC_init();
    GPIO_init();

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{    // GPIO0 -> myGPIO0 Pinmux
    GPIO_setPinConfig(GPIO_0_GPIO0);
    //

    //
    // G32R502 EVAL analog pins
    //
    // A0 / DACA_OUT - AIO231
    GPIO_setPinConfig(GPIO_231_GPIO231);
    GPIO_setAnalogMode(231, GPIO_ANALOG_ENABLED);
    // A1 / DACB_OUT - AIO232
    GPIO_setPinConfig(GPIO_232_GPIO232);
    GPIO_setAnalogMode(232, GPIO_ANALOG_ENABLED);
    // C7 - AIO233
    GPIO_setPinConfig(GPIO_233_GPIO233);
    GPIO_setAnalogMode(233, GPIO_ANALOG_ENABLED);
    // A3 / C5 - GPIO242
    GPIO_setPinConfig(GPIO_242_GPIO242);
    GPIO_setAnalogMode(242, GPIO_ANALOG_ENABLED);
    // A4 / C14 - AIO225
    GPIO_setPinConfig(GPIO_225_GPIO225);
    GPIO_setAnalogMode(225, GPIO_ANALOG_ENABLED);
    // A5 / C2 - AIO244
    GPIO_setPinConfig(GPIO_244_GPIO244);
    GPIO_setAnalogMode(244, GPIO_ANALOG_ENABLED);
    // A6 - GPIO228
    GPIO_setPinConfig(GPIO_228_GPIO228);
    GPIO_setAnalogMode(228, GPIO_ANALOG_ENABLED);
    // A7 / C3 - AIO245
    GPIO_setPinConfig(GPIO_245_GPIO245);
    GPIO_setAnalogMode(245, GPIO_ANALOG_ENABLED);
    // A8 / C11 - AIO241
    GPIO_setPinConfig(GPIO_241_GPIO241);
    GPIO_setAnalogMode(241, GPIO_ANALOG_ENABLED);
    // A9 / C8 - GPIO227
    GPIO_setPinConfig(GPIO_227_GPIO227);
    GPIO_setAnalogMode(227, GPIO_ANALOG_ENABLED);
    // A10 / C10 - GPIO230
    GPIO_setPinConfig(GPIO_230_GPIO230);
    GPIO_setAnalogMode(230, GPIO_ANALOG_ENABLED);
    // A11 - AIO237
    GPIO_setPinConfig(GPIO_237_GPIO237);
    GPIO_setAnalogMode(237, GPIO_ANALOG_ENABLED);
    // A12 / C1 - AIO238
    GPIO_setPinConfig(GPIO_238_GPIO238);
    GPIO_setAnalogMode(238, GPIO_ANALOG_ENABLED);
    // A14 - AIO239
    GPIO_setPinConfig(GPIO_239_GPIO239);
    GPIO_setAnalogMode(239, GPIO_ANALOG_ENABLED);
    // A15 - GPIO21
    GPIO_setPinConfig(GPIO_21_GPIO21);
    GPIO_setAnalogMode(21, GPIO_ANALOG_ENABLED);
    // C4 - GPIO13
    GPIO_setPinConfig(GPIO_13_GPIO13);
    GPIO_setAnalogMode(13, GPIO_ANALOG_ENABLED);
    // C0 - GPIO20
    GPIO_setPinConfig(GPIO_20_GPIO20);
    GPIO_setAnalogMode(20, GPIO_ANALOG_ENABLED);
    // C6 - GPIO226
    GPIO_setPinConfig(GPIO_226_GPIO226);
    GPIO_setAnalogMode(226, GPIO_ANALOG_ENABLED);
    // C9 - GPIO224
    GPIO_setPinConfig(GPIO_224_GPIO224);
    GPIO_setAnalogMode(224, GPIO_ANALOG_ENABLED);
    // C15 - GPIO12
    GPIO_setPinConfig(GPIO_12_GPIO12);
    GPIO_setAnalogMode(12, GPIO_ANALOG_ENABLED);
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
    // ADCCLK = AHB / 4 = 50 MHz (max ADCCLK 50 MHz @ DEVICE_AHBCLK_FREQ 200 MHz)
    ADC_setPrescaler(myADC0_BASE, ADC_CLK_DIV_4_0);
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
    //     Trigger          : ADC_TRIGGER_GPIO
    //     Channel          : ADC_CH_ADCIN1
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_GPIO, ADC_CH_ADCIN1, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 1 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 1
    //     Trigger          : ADC_TRIGGER_GPIO
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_GPIO, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_NONE);
    // ADC Interrupt 1 Configuration
    //     SOC/EOC number  : 1
    //     Interrupt Source: enabled
    //     Continuous Mode : disabled
    ADC_setInterruptSource(myADC0_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER1);
    ADC_enableInterrupt(myADC0_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);
    ADC_disableContinuousMode(myADC0_BASE, ADC_INT_NUMBER1);

    //myADC1 initialization

    // ADC Initialization: Write ADC configurations and power up the ADC
    // Configures the ADC module's offset trim
    ADC_setOffsetTrimAll(ADC_REFERENCE_INTERNAL,ADC_REFERENCE_3_3V);
    // ADCCLK = AHB / 4 = 50 MHz (max ADCCLK 50 MHz @ DEVICE_AHBCLK_FREQ 200 MHz)
    ADC_setPrescaler(myADC1_BASE, ADC_CLK_DIV_4_0);
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
    //     Trigger          : ADC_TRIGGER_GPIO
    //     Channel          : ADC_CH_ADCIN2
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_GPIO, ADC_CH_ADCIN2, 8U);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 1 Configuration
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //     SOC number       : 1
    //     Trigger          : ADC_TRIGGER_GPIO
    //     Channel          : ADC_CH_ADCIN3
    //     Sample Window    : 8 SYSCLK cycles
    //     Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_GPIO, ADC_CH_ADCIN3, 8U);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_NONE);

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
    // EVAL default: internal reference (ADCA/ADCC same mode).
    // Full-scale behaves as ~3.3 V; do not use external mode unless VREFHI is driven.
    AS_setAnalogReferenceInternal(AS_VREFHIA | AS_VREFHIC);
}
//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init()
{

    //myGPIO0 initialization
    GPIO_setDrivingCapability(myGPIO0,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setDirectionMode(myGPIO0, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(myGPIO0, GPIO_PIN_TYPE_STD);    GPIO_setQualificationMode(myGPIO0, GPIO_QUAL_SYNC);
    GPIO_writePin(myGPIO0, 0);
}

//*****************************************************************************
//
// INPUTXBAR Configurations
//
//*****************************************************************************
void INPUTXBAR_init()
{

    //myINPUTXBAR0 initialization
    XBAR_setInputPin(XBAR_INPUT5, 0);
}
