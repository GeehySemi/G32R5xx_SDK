//###########################################################################
//
// FILE:    board.c
//
// TITLE:   Board source file.
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
    COMP_init();
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
    //
    // OUTPUTXBAR3 -> myOUTPUTXBAR0 Pinmux
    //
    GPIO_setPinConfig(myOUTPUTXBAR0_OUTPUTXBAR_PIN_CONFIG);

}

//*****************************************************************************
//
// COMP Configurations
//
//*****************************************************************************
void COMP_init(){
    myCOMP0_init();
}

void myCOMP0_init(){
    //
    // Select the value for CMP1HPMXSEL.
    //
    AS_selectCMPHPMux(AS_CMPHPMUX_SELECT_1,0U);
    //
    // Select the value for CMP1LPMXSEL.
    //
    AS_selectCMPLPMux(AS_CMPLPMUX_SELECT_1,0U);
    //
    // Sets the configuration for the high comparator.
    //
    COMP_configHighComparator(myCOMP0_BASE,(COMP_INSRC_DAC));
    //
    // Sets the configuration for the low comparator.
    //
    COMP_configLowComparator(myCOMP0_BASE,(COMP_INSRC_DAC));
    //
    // Sets the configuration for the internal comparator DACs.
    //
    COMP_configDAC(myCOMP0_BASE,(COMP_DACVAL_SYSCLK | COMP_DACREF_VDDA | COMP_DACSRC_SHDW));
    //
    // Sets the value of the internal DAC of the high comparator.
    //
    COMP_setDACValueHigh(myCOMP0_BASE,2048U);
    //
    // Sets the value of the internal DAC of the low comparator.
    //
    COMP_setDACValueLow(myCOMP0_BASE,0U);
    //
    //  Configures the digital filter of the high comparator.
    //
    COMP_configFilterHigh(myCOMP0_BASE, 1023U, 32U, 31U);
    //
    // Configures the digital filter of the low comparator.
    //
    COMP_configFilterLow(myCOMP0_BASE, 0U, 1U, 1U);
    //
    // Initializes the digital filter of the high comparator.
    //
    COMP_initFilterHigh(myCOMP0_BASE);
    //
    // Sets the output signal configuration for the high comparator.
    //
    COMP_configOutputsHigh(myCOMP0_BASE,(COMP_TRIPOUT_FILTER | COMP_TRIP_FILTER));
    //
    // Sets the output signal configuration for the low comparator.
    //
    COMP_configOutputsLow(myCOMP0_BASE,(COMP_TRIPOUT_ASYNC_COMP | COMP_TRIP_ASYNC_COMP));
    //
    // Sets the comparator hysteresis settings.
    //
    COMP_setHysteresis(myCOMP0_BASE,0U);
    //
    // Configures the comparator subsystem's ramp generator.
    //
    COMP_configRamp(myCOMP0_BASE,0U,0U,0U,1U,true);
    //
    // Disables reset of HIGH comparator digital filter output latch on PWMSYNC
    //
    COMP_disableLatchResetOnPWMSYNCHigh(myCOMP0_BASE);
    //
    // Disables reset of LOW comparator digital filter output latch on PWMSYNC
    //
    COMP_disableLatchResetOnPWMSYNCLow(myCOMP0_BASE);
    //
    // Sets the ePWM module blanking signal that holds trip in reset.
    //
    COMP_configBlanking(myCOMP0_BASE,1U);
    //
    // Disables an ePWM blanking signal from holding trip in reset.
    //
    COMP_disableBlanking(myCOMP0_BASE);
    //
    // Configures whether or not the digital filter latches are reset by PWMSYNC
    //
    COMP_configLatchOnPWMSYNC(myCOMP0_BASE,false,false);
    //
    // Enables the COMP module.
    //
    COMP_enableModule(myCOMP0_BASE);
    //
    // Delay for COMP DAC to power up.
    //
    DEVICE_DELAY_US(500);
}

//*****************************************************************************
//
// OUTPUTXBAR Configurations
//
//*****************************************************************************
void OUTPUTXBAR_init(){
    myOUTPUTXBAR0_init();
}

void myOUTPUTXBAR0_init(){
    XBAR_setOutputLatchMode(myOUTPUTXBAR0, false);
    XBAR_invertOutputSignal(myOUTPUTXBAR0, false);

    //
    //Mux configuration
    //
    XBAR_setOutputMuxConfig(myOUTPUTXBAR0, XBAR_OUT_MUX00_COMP1_CTRIPOUTH);
    XBAR_enableOutputMux(myOUTPUTXBAR0, XBAR_MUX00);
}
