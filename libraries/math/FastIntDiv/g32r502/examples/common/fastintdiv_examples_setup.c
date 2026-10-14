//#############################################################################
//
// FILE:    fastintdiv_examples_setup.c
//
// TITLE:   FastIntDiv Examples Common Code
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//#############################################################################
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
// $
//###########################################################################

//*****************************************************************************
//
// Included Files
//
//*****************************************************************************
#include "fastintdiv_examples_setup.h"

//*****************************************************************************
//
// FastIntDiv_Example_setupSysCtrl
//
//*****************************************************************************
void FastIntDiv_Example_setupSysCtrl(void)
{
    SysCtl_disableWatchdog();
    SysCtl_setClock(DEVICE_SETCLOCK_CFG);
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_4);
}

//*****************************************************************************
//
// FastIntDiv_Example_setupFlash
//
//*****************************************************************************
void FastIntDiv_Example_setupFlash(void)
{
    Flash_initModule(FLASH0CTRL_BASE, FLASH0ECC_BASE, DEVICE_FLASH_WAITSTATES);
}

//*****************************************************************************
//
// done
//
//*****************************************************************************
void done(void)
{
    for(;;);
}

//*****************************************************************************
//
// __error__
//
//*****************************************************************************
void __error__(const char *filename, uint32_t line)
{
    ESTOP0;
}

// End of File
