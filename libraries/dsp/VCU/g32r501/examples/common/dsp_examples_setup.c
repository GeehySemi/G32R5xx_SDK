//#############################################################################
//
// FILE:    dsp_examples_setup.c
//
// TITLE:   DSP Examples Common Code
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//#############################################################################
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

//*****************************************************************************
// the includes
//*****************************************************************************
#include "dsp_examples_setup.h"
#include "sysctl.h"


//=============================================================================
// DSP_Example_setupSysCtrl()
//=============================================================================
void DSP_Example_setupSysCtrl( void )
{
    //
    // Disable the watchdog
    //
    SysCtl_disableWatchdog();

    //
    // Set up PLL control and clock dividers
    //
    SysCtl_setClock(DEVICE_SETCLOCK_CFG);

    //
    // Make sure the LSPCLK divider is set to the default (divide by 4)
    //
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_4);
/*
    NOTE: This section needs to be uncommented if the examples are using the CM
    //
    // Set up AUXPLL control and clock dividers needed for CMCLK
    //
    SysCtl_setAuxClock(DEVICE_AUXSETCLOCK_CFG);

    //
    // Set up CMCLK to use AUXPLL as the clock source and set the
    // clock divider to 1.
    //
    SysCtl_setCMClk(SYSCTL_CMCLKOUT_DIV_1,SYSCTL_SOURCE_AUXPLL);
    //
*/
    // Enable Peripherals
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);


}

//=============================================================================
// DSP_Example_initGPIO()
//=============================================================================
void DSP_Example_initGPIO(void)
{
    //
    // Disable pin locks.
    //
   GPIO_unlockPortConfig(GPIO_PORT_A, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_B, 0xFFFFFFFF);
  //  GPIO_unlockPortConfig(GPIO_PORT_C, 0xFFFFFFFF); //Needs to be uncommented out for f2838x
}

//=============================================================================
// DSP_Example_setupFlash()
//=============================================================================
void DSP_Example_setupFlash( void )
{
    //
    // Call Flash Initialization to setup flash waitstates. This function must
    // reside in RAM.
    //
    Flash_initModule(FLASH0CTRL_BASE, FLASH0ECC_BASE, DEVICE_FLASH_WAITSTATES);
}

//=============================================================================
// done()
//=============================================================================
void done( void )
{
    for(;;);
}

//=============================================================================
// __error__()
//=============================================================================
void __error__(const char *filename, uint32_t line)
{
    ESTOP0;
}

// End of File
