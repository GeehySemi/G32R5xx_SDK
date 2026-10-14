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
    AS_init();
    DAC_init();

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
    //
    // DACA_OUT (G32R502 EVAL Expand A0 -> AIO231)
    //
    GPIO_setPinConfig(GPIO_231_GPIO231);
    GPIO_setAnalogMode(231, GPIO_ANALOG_ENABLED);

    //
    // VDAC reference (Expand A5 / C2 -> AIO244)
    //
    GPIO_setPinConfig(GPIO_244_GPIO244);
    GPIO_setAnalogMode(244, GPIO_ANALOG_ENABLED);
}

//*****************************************************************************
//
// AS Configurations
//
//*****************************************************************************
void AS_init(){
    // asysctl initialization
    // Disables the temperature sensor output to the ADC.
    AS_disableTemperatureSensor();
    // Set the analog voltage reference selection to external.
    AS_setAnalogReferenceExternal( AS_VREFHIA | AS_VREFHIC );
}
//*****************************************************************************
//
// DAC Configurations
//
//*****************************************************************************
void DAC_init(){
    // myDAC0 initialization
    // Set DAC reference voltage.
    DAC_setReferenceVoltage(myDAC0_BASE, DAC_REF_VDAC);
    // Set DAC load mode.
    DAC_setLoadMode(myDAC0_BASE, DAC_LOAD_SYSCLK);
    // Enable the DAC output
    DAC_enableOutput(myDAC0_BASE);
    // Set the DAC shadow output
    DAC_setShadowValue(myDAC0_BASE, 0U);

    // Delay for buffered DAC to power up.
    DEVICE_DELAY_US(500);

}

