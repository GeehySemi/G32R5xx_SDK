//###########################################################################
//
// FILE:    board.c
//
// TITLE:   Board source file.
//
// VERSION: 1.0.0
//
// DATE:    2026-08-28
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

void Board_init()
{
    WRPRT_DISABLE;

    PinMux_init();
    SYSCTL_init();
    GPIO_init();

    WRPRT_ENABLE;
}

void PinMux_init()
{
    GPIO_setPinConfig(GPIO_23_GPIO23);
}

void GPIO_init()
{
    myGPIOOutput0_init();
}

void myGPIOOutput0_init()
{
    GPIO_setPadConfig(myGPIOOutput0, GPIO_PIN_TYPE_STD);
    GPIO_setDrivingCapability(myGPIOOutput0, GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setQualificationMode(myGPIOOutput0, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(myGPIOOutput0, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(myGPIOOutput0, GPIO_CORE_CPU0);
}

void SYSCTL_init()
{
    SysCtl_disableMCD();

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTB);
}
