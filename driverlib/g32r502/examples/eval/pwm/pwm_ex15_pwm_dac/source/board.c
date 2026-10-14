//###########################################################################
//
// FILE:    board.c
//
// TITLE:   Board source file.
//
// VERSION: 1.0.0
//
// DATE:    2026-08-07
//
//###########################################################################
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
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
// Initializes PinMux and PWM for the PWM-DAC path.
//
//*****************************************************************************
void Board_init(void)
{
    WRPRT_DISABLE;

    PinMux_init();
    PWM_init();

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// PINMUX Configurations
// GPIO22 = PWM4A, GPIO31 = PWM1B
//
//*****************************************************************************
void PinMux_init(void)
{
    //
    // PWM4A -> GPIO22
    //
    GPIO_setPinConfig(myPWM4_PWMA_PIN_CONFIG);
    GPIO_setAnalogMode(myPWM4_PWMA_GPIO, GPIO_ANALOG_DISABLED);
    GPIO_setPadConfig(myPWM4_PWMA_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myPWM4_PWMA_GPIO, GPIO_QUAL_SYNC);
    GPIO_setDrivingCapability(myPWM4_PWMA_GPIO, GPIO_DRIVE_LEVEL_VERY_HIGH);

    //
    // PWM1B -> GPIO31
    //
    GPIO_setPinConfig(myPWM1_PWMB_PIN_CONFIG);
    GPIO_setAnalogMode(myPWM1_PWMB_GPIO, GPIO_ANALOG_DISABLED);
    GPIO_setPadConfig(myPWM1_PWMB_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myPWM1_PWMB_GPIO, GPIO_QUAL_SYNC);
    GPIO_setDrivingCapability(myPWM1_PWMB_GPIO, GPIO_DRIVE_LEVEL_VERY_HIGH);
}

//
// End of File
//
