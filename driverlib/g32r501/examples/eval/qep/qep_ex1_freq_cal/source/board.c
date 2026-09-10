//#############################################################################
//
// FILE:    board.c
//
// TITLE:   Board source file
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
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
// 1. Modified function names and macro definition names.
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
    QEP_init();

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
    // QEP1 -> myQEP0 Pinmux
    //
    GPIO_setPinConfig(myQEP0_QEPA_PIN_CONFIG);
    GPIO_setDrivingCapability(myQEP0_QEPA_GPIO,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(myQEP0_QEPA_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myQEP0_QEPA_GPIO, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(myQEP0_QEPB_PIN_CONFIG);
    GPIO_setDrivingCapability(myQEP0_QEPB_GPIO,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(myQEP0_QEPB_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myQEP0_QEPB_GPIO, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(myQEP0_QEPSTROBE_PIN_CONFIG);
    GPIO_setDrivingCapability(myQEP0_QEPSTROBE_GPIO,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(myQEP0_QEPSTROBE_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myQEP0_QEPSTROBE_GPIO, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(myQEP0_QEPINDEX_PIN_CONFIG);
    GPIO_setDrivingCapability(myQEP0_QEPINDEX_GPIO,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(myQEP0_QEPINDEX_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myQEP0_QEPINDEX_GPIO, GPIO_QUAL_SYNC);
}

//*****************************************************************************
//
// QEP Configurations
//
//*****************************************************************************
void QEP_init(){
    myQEP0_init();
}

void myQEP0_init(){
    //
    // Set the strobe input source of the QEP module.
    //
    QEP_setStrobeSource(myQEP0_BASE,QEP_STROBE_FROM_GPIO);
    //
    // Sets the polarity of the QEP module's input signals.
    //
    QEP_setInputPolarity(myQEP0_BASE,false,false,false,false);
    //
    // Configures QEP module's quadrature decoder unit.
    //
    QEP_setDecoderConfig(myQEP0_BASE, (QEP_CONFIG_UP_COUNT | QEP_CONFIG_2X_RESOLUTION | QEP_CONFIG_NO_SWAP | QEP_CONFIG_IGATE_DISABLE));
    //
    // Set the emulation mode of the QEP module.
    //
    QEP_setEmulationMode(myQEP0_BASE,QEP_EMULATIONMODE_RUNFREE);
    //
    // Configures QEP module position counter unit.
    //
    QEP_setPositionCounterConfig(myQEP0_BASE,QEP_POSITION_RESET_1ST_IDX,4294967295U);
    //
    // Sets the current encoder position.
    //
    QEP_setPosition(myQEP0_BASE,0U);
    //
    // Enables the QEP module unit timer.
    // The unit timer is set to 1000000U to maintain a 10ms interval
    // at 100MHz frequency, which corresponds to a 100Hz timer frequency.
    // This ensures consistency with the FREQ_SCALER_FR calculation in qep_ex1_calculation.c.
    //
    QEP_enableUnitTimer(myQEP0_BASE,1000000U);
    //
    // Disables the QEP module watchdog timer.
    //
    QEP_disableWatchdog(myQEP0_BASE);
    //
    // Configures the quadrature modes in which the position count can be latched.
    //
    QEP_setLatchMode(myQEP0_BASE,(QEP_LATCH_UNIT_TIME_OUT|QEP_LATCH_RISING_STROBE|QEP_LATCH_RISING_INDEX));
    //
    // Set the quadrature mode adapter (QMA) module mode.
    //
    QEP_setQMAModuleMode(myQEP0_BASE,QEP_QMA_MODE_BYPASS);
    //
    // Configures the mode in which the position counter is initialized.
    //
    QEP_setPositionInitMode(myQEP0_BASE,(QEP_INIT_DO_NOTHING));
    //
    // Sets the software initialization of the encoder position counter.
    //
    QEP_setSWPositionInit(myQEP0_BASE,true);
    //
    // Sets the init value for the encoder position counter.
    //
    QEP_setInitialPosition(myQEP0_BASE,0U);
    //
    // Enables the QEP module.
    //
    QEP_enableModule(myQEP0_BASE);
    //
    // Configures QEP module edge-capture unit.
    //
    QEP_setCaptureConfig(myQEP0_BASE,QEP_CAPTURE_CLK_DIV_128,QEP_UNIT_POS_EVNT_DIV_8);
    //
    // Enables the QEP module edge-capture unit.
    //
    QEP_enableCapture(myQEP0_BASE);
}
