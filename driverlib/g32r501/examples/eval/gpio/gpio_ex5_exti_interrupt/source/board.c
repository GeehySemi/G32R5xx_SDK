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
//
// You may not use this file except in compliance with the
// GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
//
// The program is only for reference, which is distributed in the hope
// that it will be useful and instructional for customers to develop
// their software. Unless required by applicable law or agreed to in
// writing, the program is distributed on an "AS IS" BASIS, WITHOUT
// ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
// See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
// and limitations under the License.
// $
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
    // PinMux for modules assigned to CPU0
    //

    // GPIO28 -> myGPIOInputInterrupt0 Pinmux
    GPIO_setPinConfig(GPIO_28_GPIO28);
    // GPIO13 -> myGPIOOutput0 Pinmux
    GPIO_setPinConfig(GPIO_13_GPIO13);
}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init(){
    myGPIOInputInterrupt0_init();
    myGPIOOutput0_init();
}

void myGPIOInputInterrupt0_init(){
    GPIO_setPadConfig(myGPIOInputInterrupt0, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    GPIO_setDrivingCapability(myGPIOInputInterrupt0,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setQualificationMode(myGPIOInputInterrupt0, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(myGPIOInputInterrupt0, GPIO_DIR_MODE_IN);
    GPIO_setMasterCore(myGPIOInputInterrupt0, GPIO_CORE_CPU0);
}
void myGPIOOutput0_init(){
    GPIO_setPadConfig(myGPIOOutput0, GPIO_PIN_TYPE_STD);
    GPIO_setDrivingCapability(myGPIOOutput0,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setQualificationMode(myGPIOOutput0, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(myGPIOOutput0, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(myGPIOOutput0, GPIO_CORE_CPU0);
}
