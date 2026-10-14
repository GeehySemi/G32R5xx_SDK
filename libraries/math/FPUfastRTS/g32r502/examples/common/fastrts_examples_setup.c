//#############################################################################
//
// FILE:    fastrts_examples_setup.c
//
// TITLE:   DSP Examples Common Code
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//#############################################################################
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

//*****************************************************************************
// the includes
//*****************************************************************************
#include "fastrts_examples_setup.h"

//*****************************************************************************
// the globals
//*****************************************************************************

//*****************************************************************************
// the function definitions
//*****************************************************************************

//=============================================================================
// FastRTS_Example_setupSysCtrl()
//=============================================================================
void FastRTS_Example_setupSysCtrl( void )
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
    
    
}

//=============================================================================
// FastRTS_Example_setupFlash()
//=============================================================================
void FastRTS_Example_setupFlash( void )
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