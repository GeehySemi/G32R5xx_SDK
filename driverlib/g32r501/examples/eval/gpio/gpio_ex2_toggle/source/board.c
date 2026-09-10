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
    // GPIO23 -> myGPIOOutput0 Pinmux
    GPIO_setPinConfig(GPIO_23_GPIO23);

}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init(){
    myGPIOOutput0_init();
}

void myGPIOOutput0_init(){
    GPIO_setPadConfig(myGPIOOutput0, GPIO_PIN_TYPE_STD);
    GPIO_setDrivingCapability(myGPIOOutput0,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setQualificationMode(myGPIOOutput0, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(myGPIOOutput0, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(myGPIOOutput0, GPIO_CORE_CPU0);
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
