//#############################################################################
//
// FILE:    board.c
//
// TITLE:   Board source file
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//#############################################################################
//
//
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
    GPIO_init();
    SPI_init();

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
    // GPIO11 -> SPI_CS_GPIO Pinmux
    GPIO_setPinConfig(GPIO_11_GPIO11);
    //
    // SPIA -> mySPI0 Pinmux
    //
    GPIO_setPinConfig(mySPI0_SPIPICO_PIN_CONFIG);
    GPIO_setDrivingCapability(mySPI0_SPIPICO_GPIO,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(mySPI0_SPIPICO_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(mySPI0_SPIPICO_GPIO, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(mySPI0_SPIPOCI_PIN_CONFIG);
    GPIO_setDrivingCapability(mySPI0_SPIPOCI_GPIO,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(mySPI0_SPIPOCI_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(mySPI0_SPIPOCI_GPIO, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(mySPI0_SPICLK_PIN_CONFIG);
    GPIO_setDrivingCapability(mySPI0_SPICLK_GPIO,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(mySPI0_SPICLK_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(mySPI0_SPICLK_GPIO, GPIO_QUAL_ASYNC);

}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init()
{
    //SPI_CS_GPIO initialization
    GPIO_setDrivingCapability(SPI_CS_GPIO,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(SPI_CS_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(SPI_CS_GPIO, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(SPI_CS_GPIO, GPIO_DIR_MODE_OUT);
}

//*****************************************************************************
//
// SPI Configurations
//
//*****************************************************************************
void SPI_init()
{
    //SPI_EEPROM initialization
    SPI_disableModule(SPI_EEPROM_BASE);
    SPI_setConfig(SPI_EEPROM_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA1,
                SPI_MODE_MASTER, 1000000, 8);
    SPI_setSTESignalPolarity(SPI_EEPROM_BASE, SPI_STE_ACTIVE_LOW);
    SPI_disableFIFO(SPI_EEPROM_BASE);
    SPI_disableLoopback(SPI_EEPROM_BASE);
    SPI_setEmulationMode(SPI_EEPROM_BASE, SPI_EMULATION_STOP_MIDWAY);
    SPI_enableModule(SPI_EEPROM_BASE);
}
