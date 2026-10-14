//###########################################################################
//
// FILE:    board.c
//
// TITLE:   Board source file.
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
    SYNC_init();
    CAP_init();
    OUTPUTXBAR_init();

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{

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

//
    // OUTPUTXBAR3 -> myOUTPUTXBAR0 Pinmux
    //
    GPIO_setPinConfig(myOUTPUTXBAR0_OUTPUTXBAR_PIN_CONFIG);
    //
    // OUTPUTXBAR4 -> myOUTPUTXBAR1 Pinmux
    //
    GPIO_setPinConfig(myOUTPUTXBAR1_OUTPUTXBAR_PIN_CONFIG);
}

//*****************************************************************************
//
// CAP Configurations
//
//*****************************************************************************
void CAP_init(){
    myCAP0_init();
    myCAP1_init();
}

void myCAP0_init(){
    //
    // Stops Time stamp counter.
    //
    CAP_stopCounter(myCAP0_BASE);
    //
    // Sets eCAP in APWM mode.
    //
    CAP_enableAPWMMode(myCAP0_BASE);
    //
    // Set eCAP APWM period.
    //
    CAP_setAPWMPeriod(myCAP0_BASE,12000U);
    //
    // Set eCAP APWM on or off time count.
    //
    CAP_setAPWMCompare(myCAP0_BASE,6000U);
    //
    // Set eCAP APWM polarity.
    //
    CAP_setAPWMPolarity(myCAP0_BASE,CAP_APWM_ACTIVE_LOW);
    //
    // Sets a phase shift value count.
    //
    CAP_setPhaseShiftCount(myCAP0_BASE,0U);
    //
    // Disable counter loading with phase shift value.
    //
    CAP_disableLoadCounter(myCAP0_BASE);
    //
    // Configures Sync out signal mode.
    //
    CAP_setSyncOutMode(myCAP0_BASE,CAP_SYNC_OUT_COUNTER_PRD);
    //
    // Configures emulation mode.
    //
    CAP_setEmulationMode(myCAP0_BASE,CAP_EMULATION_STOP);
    //
    // Set up the source for sync-in pulse..
    //
    CAP_setSyncInPulseSource(myCAP0_BASE,CAP_SYNC_IN_PULSE_SRC_DISABLE);
    //
    // Starts Time stamp counter for myCAP0.
    //
    CAP_startCounter(myCAP0_BASE);

}

//*****************************************************************************
//
// MY CAP1 Configurations
//
//*****************************************************************************
void myCAP1_init(){
    //
    // Stops Time stamp counter.
    //
    CAP_stopCounter(myCAP1_BASE);
    //
    // Sets eCAP in APWM mode.
    //
    CAP_enableAPWMMode(myCAP1_BASE);
    //
    // Set eCAP APWM period.
    //
    CAP_setAPWMPeriod(myCAP1_BASE,12000U);
    //
    // Set eCAP APWM on or off time count.
    //
    CAP_setAPWMCompare(myCAP1_BASE,6000U);
    //
    // Set eCAP APWM polarity.
    //
    CAP_setAPWMPolarity(myCAP1_BASE,CAP_APWM_ACTIVE_LOW);
    //
    // Sets a phase shift value count.
    //
    CAP_setPhaseShiftCount(myCAP1_BASE,3600U);
    //
    // Enable counter loading with phase shift value.
    //
    CAP_enableLoadCounter(myCAP1_BASE);
    //
    // Configures Sync out signal mode.
    //
    CAP_setSyncOutMode(myCAP1_BASE,CAP_SYNC_OUT_SYNCI);
    //
    // Configures emulation mode.
    //
    CAP_setEmulationMode(myCAP1_BASE,CAP_EMULATION_STOP);
    //
    // Set up the source for sync-in pulse..
    //
    CAP_setSyncInPulseSource(myCAP1_BASE,CAP_SYNC_IN_PULSE_SRC_SYNCOUT_CAP1);
    //
    // Starts Time stamp counter for myCAP1.
    //
    CAP_startCounter(myCAP1_BASE);

}



//*****************************************************************************
//
// OUTPUTXBAR Configurations
//
//*****************************************************************************
void OUTPUTXBAR_init(){
    myOUTPUTXBAR0_init();
    myOUTPUTXBAR1_init();
}

void myOUTPUTXBAR0_init(){
    XBAR_setOutputLatchMode(myOUTPUTXBAR0, false);
    XBAR_invertOutputSignal(myOUTPUTXBAR0, false);
        
    //
    //Mux configuration
    //
    XBAR_setOutputMuxConfig(myOUTPUTXBAR0, XBAR_OUT_MUX00_CAP1_OUT);
    XBAR_enableOutputMux(myOUTPUTXBAR0, XBAR_MUX00);
}

void myOUTPUTXBAR1_init(){
    XBAR_setOutputLatchMode(myOUTPUTXBAR1, false);
    XBAR_invertOutputSignal(myOUTPUTXBAR1, false);
        
    //
    //Mux configuration
    //
    XBAR_setOutputMuxConfig(myOUTPUTXBAR1, XBAR_OUT_MUX02_CAP2_OUT);
    XBAR_enableOutputMux(myOUTPUTXBAR1, XBAR_MUX02);
}
//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************
void SYNC_init(){
    SysCtl_setSyncOutputConfig(SYSCTL_SYNC_OUT_SRC_PWM1SYNCOUT);
    //
    // For PWM1, the sync input is: SYSCTL_SYNC_IN_SRC_EXTSYNCIN1
    //
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_PWM4, SYSCTL_SYNC_IN_SRC_PWM1SYNCOUT);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_PWM7, SYSCTL_SYNC_IN_SRC_PWM1SYNCOUT);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_CAP1, SYSCTL_SYNC_IN_SRC_PWM1SYNCOUT);

    //
    // SOCA
    //
    SysCtl_enableExtADCSOCSource(0);
    //
    // SOCB
    //
    SysCtl_enableExtADCSOCSource(0);
}
