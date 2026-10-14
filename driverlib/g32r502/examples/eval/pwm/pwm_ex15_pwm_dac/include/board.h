//###########################################################################
//
// FILE:    board.h
//
// TITLE:   Board header file.
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

#ifndef BOARD_H
#define BOARD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PWM-DAC timing (50 kHz, up-count)
// D=24% -> ~0.8 V, D=48% -> ~1.6 V after 3.3 V buffer
//
//*****************************************************************************
#define PWM_DAC_FREQ_HZ           50000UL
#define PWM_DAC_DUTY_PCT_CH22     24U
#define PWM_DAC_DUTY_PCT_CH31     48U
#define PWM_DAC_TBPRD             ((uint16_t)((DEVICE_AHBCLK_FREQ / PWM_DAC_FREQ_HZ) - 1UL))
#define PWM_DAC_CMPA_CH22         ((uint16_t)(((uint32_t)PWM_DAC_TBPRD + 1UL) * \
                                              PWM_DAC_DUTY_PCT_CH22 / 100UL))
#define PWM_DAC_CMPB_CH31         ((uint16_t)(((uint32_t)PWM_DAC_TBPRD + 1UL) * \
                                              PWM_DAC_DUTY_PCT_CH31 / 100UL))

//*****************************************************************************
//
// PWM4A on GPIO22
//
//*****************************************************************************
#define myPWM4_BASE               PWM4_BASE
#define GPIO_PIN_PWM4_A           22
#define myPWM4_PWMA_GPIO          22
#define myPWM4_PWMA_PIN_CONFIG    GPIO_22_PWM4_A

//*****************************************************************************
//
// PWM1B on GPIO31
//
//*****************************************************************************
#define myPWM1_BASE               PWM1_BASE
#define GPIO_PIN_PWM1_B           31
#define myPWM1_PWMB_GPIO          31
#define myPWM1_PWMB_PIN_CONFIG    GPIO_31_PWM1_B

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void Board_init(void);
void PinMux_init(void);
void PWM_init(void);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
