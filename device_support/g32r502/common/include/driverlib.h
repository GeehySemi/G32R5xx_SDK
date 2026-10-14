//#############################################################################
//
// FILE:    driverlib.h
//
// TITLE:   G32R502 Driverlib Header File
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//###########################################################################
//
//
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
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
// - 2026-06-30: 
// 1. Updated header file title to reflect G32R502 Driverlib.
// 2. Changed included files to match G32R502 architecture and peripherals.
// 3. Renamed or replaced some driver headers with G32R502-specific versions.
// 4. Added cortex.h, ipc.h, flash.h, zidian_cde.h for enhanced functionality.
// 5. Removed unnecessary or deprecated header files not used in G32R502.
//
//###########################################################################

#ifndef DRIVERLIB_H
#define DRIVERLIB_H

#include "g32r502.h"
#include "hw_types.h"
#include "hw_memmap.h"

#include "adc.h"
#include "as.h"
#include "can.h"
#include "canfd.h"
#include "comp.h"
#include "cpu.h"
#include "tmr.h"
#include "dac.h"
#include "dbgmcu.h"
#include "dccomp.h"
#include "debug.h"
#include "dma.h"
#include "cap.h"
#include "pwm.h"
#include "qep.h"
#include "gpio.h"
#include "hrpwm.h"
#include "i2c.h"
#include "interrupt.h"
#include "lin.h"
#include "pin_map.h"
#include "pin_map_legacy.h"
#include "pmbus.h"
#include "uart.h"
#include "spi.h"
#include "sysctl.h"
#include "version.h"
#include "xbar.h"
#include "cortex.h"

#include "exti.h"
#include "flash.h"

#ifdef __ARM_FEATURE_CDE
  #include "zidian_cde.h"
#endif

#include "driverlib_ex.h"

#endif  // end of DRIVERLIB_H definition

//
// End of file
//
