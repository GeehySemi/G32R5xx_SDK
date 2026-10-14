//###########################################################################
//
// FILE:    g32r502_device.h
//
// TITLE:   g32r502 Device Definitions.
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
// 1. Update register naming and access rules.
//
//###########################################################################

#ifndef G32R502_DEVICE_H
#define G32R502_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "g32r502.h"

//
// Common CPU Definitions:
//

//
// Define to enable interrupts
//
#ifndef EINT
#define EINT   __enable_irq()
#endif

//
// Define to disable interrupts
//
#ifndef DINT
#define DINT   __disable_irq()
#endif

//
// Define to enable debug events
//
#ifndef ERTM
#define ERTM   __NOP()
#endif

//
// Define to disable debug events
//
#ifndef DRTM
#define DRTM   __NOP()
#endif

//
// Define to allow writes to protected registers
//
#ifndef WRPRT_DISABLE
#define WRPRT_DISABLE   __wrprt_disable()
#endif // WRPRT_DISABLE

//
// Define to disable writes to protected registers
//
#ifndef WRPRT_ENABLE
#define WRPRT_ENABLE   __wrprt_enable()
#endif // WRPRT_ENABLE

//
// Define for emulation stop
//
#ifndef ESTOP0
#define ESTOP0 do                                                   \
               {                                                    \
                   if((DCB->DHCSR & DCB_DHCSR_C_DEBUGEN_Msk) != 0U) \
                   {                                                \
                       __BKPT(0);                                   \
                   }                                                \
               }                                                    \
               while((_Bool)0)
#endif

#define M_INT1  0x0001
#define M_INT2  0x0002
#define M_INT3  0x0004
#define M_INT4  0x0008
#define M_INT5  0x0010
#define M_INT6  0x0020
#define M_INT7  0x0040
#define M_INT8  0x0080
#define M_INT9  0x0100
#define M_INT10 0x0200
#define M_INT11 0x0400
#define M_INT12 0x0800
#define M_INT13 0x1000
#define M_INT14 0x2000
#define M_DLOG  0x4000
#define M_RTOS  0x8000

#define BIT0    0x00000001
#define BIT1    0x00000002
#define BIT2    0x00000004
#define BIT3    0x00000008
#define BIT4    0x00000010
#define BIT5    0x00000020
#define BIT6    0x00000040
#define BIT7    0x00000080
#define BIT8    0x00000100
#define BIT9    0x00000200
#define BIT10   0x00000400
#define BIT11   0x00000800
#define BIT12   0x00001000
#define BIT13   0x00002000
#define BIT14   0x00004000
#define BIT15   0x00008000
#define BIT16   0x00010000
#define BIT17   0x00020000
#define BIT18   0x00040000
#define BIT19   0x00080000
#define BIT20   0x00100000
#define BIT21   0x00200000
#define BIT22   0x00400000
#define BIT23   0x00800000
#define BIT24   0x01000000
#define BIT25   0x02000000
#define BIT26   0x04000000
#define BIT27   0x08000000
#define BIT28   0x10000000
#define BIT29   0x20000000
#define BIT30   0x40000000
#define BIT31   0x80000000

//
// For Portability, User Is Recommended To Use the C99 Standard integer types
//
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//
// C++ Bool Compatibility
//
#if defined(__cplusplus)
typedef bool _Bool;
#endif

//
// C99 defines boolean type to be _Bool, but this doesn't match the format of
// the other standard integer types.  bool_t has been defined to fill this gap.
//
typedef _Bool bool_t;

//
// Used for a bool function return status
//
typedef _Bool status_t;

typedef short                                   int16;
typedef int                                     int32;
typedef long long                               int64;
typedef unsigned short                          Uint16;
typedef unsigned int                            Uint32;
typedef unsigned long long                      Uint64;
typedef float                                   float32;
typedef long double                             float64;

//
// The following data types are for use with byte addressable peripherals.
// See compiler documentation on the byte_peripheral type attribute.
//
typedef unsigned short bp_16;
typedef unsigned int bp_32;

//
// Include All Peripheral Header Files:
//
#include "g32r502_adc.h"
#include "g32r502_as.h"
#include "g32r502_flbxbar.h"
#include "g32r502_comp.h"
#include "g32r502_tmr.h"
#include "g32r502_dac.h"
#include "g32r502_dma.h"
#include "g32r502_cap.h"
#include "g32r502_pwm.h"
#include "g32r502_pwm_xbar.h"
#include "g32r502_qep.h"
#include "g32r502_flash.h"
#include "g32r502_gpio.h"
#include "g32r502_i2c.h"
#include "g32r502_input_xbar.h"
#include "g32r502_nmi.h"
#include "g32r502_output_xbar.h"
#include "g32r502_pmbus.h"
#include "g32r502_uart.h"
#include "g32r502_spi.h"
#include "g32r502_sysctrl.h"
#include "g32r502_xbar.h"
#include "g32r502_exti.h"

//
// byte_peripheral attribute is only supported on the G32R502
//
#include "g32r502_can.h"
#include "g32r502_canfd.h"
#include "g32r502_dccomp.h"
#include "g32r502_lin.h"

//
// Include Peripheral Driverlib Header Files:
//
#include "interrupt.h"

#include "g32r502_device_ex.h"

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif                                  // end of G32R502_DEVICE_H definition

//===========================================================================
// End of file.
//===========================================================================
