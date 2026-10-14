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
// 2. PinMux_init: keep GPIO5 OUTPUTXBAR3 only (CAP1 APWM output).
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
    GPIO_setPinConfig(myOUTPUTXBAR0_OUTPUTXBAR_PIN_CONFIG);
}

//*****************************************************************************
//
// CAP Configurations
//
//*****************************************************************************
void CAP_init(){
    myCAP0_init();
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
    //
    // Set eCAP APWM period (DEVICE_AHBCLK_FREQ / 5).
    //
    CAP_setAPWMPeriod(myCAP0_BASE, (DEVICE_AHBCLK_FREQ / 5U));
    //
    // Set eCAP APWM on or off time count.
    //
    CAP_setAPWMCompare(myCAP0_BASE, (DEVICE_AHBCLK_FREQ / 10U));
    //
    // Set eCAP APWM polarity.
    //
    CAP_setAPWMPolarity(myCAP0_BASE,CAP_APWM_ACTIVE_HIGH);
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
    CAP_setSyncOutMode(myCAP0_BASE,CAP_SYNC_OUT_SYNCI);
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
    XBAR_setOutputMuxConfig(myOUTPUTXBAR0, XBAR_OUT_MUX00_CAP1_OUT);
    XBAR_enableOutputMux(myOUTPUTXBAR0, XBAR_MUX00);
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
