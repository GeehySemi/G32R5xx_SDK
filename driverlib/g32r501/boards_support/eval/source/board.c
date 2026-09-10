//###########################################################################
//
// FILE:    board.c
//
// TITLE:   On-board driver definition and initialization.
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
    GPIO_setPinConfig(GPIO_23_GPIO23);
    GPIO_setPinConfig(GPIO_34_GPIO34);
}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init()
{
    //myGPIOOutput0 initialization
    GPIO_setDrivingCapability(myGPIOOutput_LED2,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setDirectionMode(myGPIOOutput_LED2, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(myGPIOOutput_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setMasterCore(myGPIOOutput_LED2, GPIO_CORE_CPU0);
    GPIO_setQualificationMode(myGPIOOutput_LED2, GPIO_QUAL_SYNC);
    
    GPIO_setDrivingCapability(myGPIOOutput_LED3,GPIO_DRIVE_LEVEL_VERY_HIGH);
    PIO_setDirectionMode(myGPIOOutput_LED3, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(myGPIOOutput_LED3, GPIO_PIN_TYPE_STD);
    GPIO_setMasterCore(myGPIOOutput_LED3, GPIO_CORE_CPU0);
    GPIO_setQualificationMode(myGPIOOutput_LED3, GPIO_QUAL_SYNC);
}
