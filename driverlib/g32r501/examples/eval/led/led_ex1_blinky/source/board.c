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
    SYSCTL_init();
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
    // GPIO23_VSW -> myBoardLED0_GPIO Pinmux
    GPIO_setPinConfig(GPIO_23_GPIO23);
}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init(){
    myBoardLED0_GPIO_init();
}

void myBoardLED0_GPIO_init(){
    GPIO_setDrivingCapability(myBoardLED0_GPIO,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(myBoardLED0_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myBoardLED0_GPIO, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(myBoardLED0_GPIO, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(myBoardLED0_GPIO, GPIO_CORE_CPU0);
}

//*****************************************************************************
//
// SYSCTL Configurations
//
//*****************************************************************************
void SYSCTL_init(){
    //
    // sysctl initialization
    //

    SysCtl_disableMCD();


    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCA, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCA, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCA, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCB, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCB, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCB, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCC, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCC, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_ADCC, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP1, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP1, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP1, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP2, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP2, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP2, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP3, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP3, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP3, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP4, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP4, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP4, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP5, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP5, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP5, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP6, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP6, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP6, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP7, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP7, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_COMP7, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_DACA, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_DACA, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_DACA, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_DACB, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_DACB, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_DACB, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM1, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM1, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM1, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM2, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM2, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM2, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM3, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM3, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM3, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM4, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM4, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM4, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM5, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM5, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM5, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM6, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM6, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM6, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM7, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM7, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM7, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM8, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM8, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PWM8, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_QEP1, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_QEP1, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_QEP1, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_QEP2, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_QEP2, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_QEP2, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP1, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP1, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP1, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP2, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP2, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP2, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP3, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP3, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP3, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP4, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP4, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP4, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP5, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP5, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP5, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP6, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP6, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP6, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP7, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP7, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CAP7, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SDF1, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SDF1, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SDF1, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_FLB1, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_FLB1, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_FLB2, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_FLB2, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_FLB3, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_FLB3, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_FLB4, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_FLB4, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SPIA, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SPIA, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SPIA, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SPIB, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SPIB, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_SPIB, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PMBUSA, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PMBUSA, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_PMBUSA, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_LINA, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_LINA, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_LINA, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CANA, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CANA, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CANB, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_CANB, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_HRPWMA, 
        SYSCTL_ACCESS_CPU0, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_HRPWMA, 
        SYSCTL_ACCESS_CPU1, SYSCTL_ACCESS_FULL);
    SysCtl_setPeripheralAccessControl(SYSCTL_ACCESS_HRPWMA, 
        SYSCTL_ACCESS_DMA1, SYSCTL_ACCESS_FULL);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_HRPWM);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM7);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM8);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAP2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAP3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAP4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAP5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAP6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAP7);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_QEP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_QEP2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SDF);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_COMP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_COMP2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_COMP3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_COMP4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_COMP5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_COMP6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_COMP7);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DACA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DACB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FLB1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FLB2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FLB3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FLB4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_LINA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PMBUSA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DCCOMP0);

}

