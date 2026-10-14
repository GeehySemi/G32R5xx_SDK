//###########################################################################
//
// FILE:    g32r502_dma_defines.h
//
// TITLE:   #defines used in DMA examples
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
// 1. Updated header file title to reflect G32R502 DMA definitions.
// 2. Changed file name to g32r502_dma_defines.h to match the new device
//    architecture.
// 3. Modified definitions for peripheral sources to align with G32R502
//    DMA architecture.
// 4. Updated DMA event names and structure to reflect G32R502 specifications.
// 5. Retained existing DMA control definitions for compatibility, while
//    adapting for G32R502.
//
//###########################################################################

#ifndef G32R502_DMA_DEFINES_H_
#define G32R502_DMA_DEFINES_H_

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines
//

//
// PETSRCSEL bits
//
#define DMA_SOFTWARE        0
#define DMA_ADCAINT1        1
#define DMA_ADCAINT2        2
#define DMA_ADCAINT3        3
#define DMA_ADCAINT4        4
#define DMA_ADCAEVT         5

#define DMA_ADCCINT1       11
#define DMA_ADCCINT2       12
#define DMA_ADCCINT3       13
#define DMA_ADCCINT4       14
#define DMA_ADCCEVT        15

#define DMA_XINT1          29
#define DMA_XINT2          30
#define DMA_XINT3          31
#define DMA_XINT4          32
#define DMA_XINT5          33

#define DMA_PWM1SOCA       36 
#define DMA_PWM1SOCB       37 
#define DMA_PWM2SOCA       38 
#define DMA_PWM2SOCB       39 
#define DMA_PWM3SOCA       40 
#define DMA_PWM3SOCB       41 
#define DMA_PWM4SOCA       42 
#define DMA_PWM4SOCB       43 
#define DMA_PWM5SOCA       44 
#define DMA_PWM5SOCB       45 
#define DMA_PWM6SOCA       46 
#define DMA_PWM6SOCB       47 
#define DMA_PWM7SOCA       48 
#define DMA_PWM7SOCB       49 

#define DMA_TINT0          68
#define DMA_TINT1          69
#define DMA_TINT2          70

#define DMA_CAP1DMA        75
#define DMA_CAP2DMA        76
#define DMA_CAP3DMA        77

#define DMA_PMBUSTX        78
#define DMA_PMBUSRX        79

#define DMA_UARTATX        96
#define DMA_UARTARX        97
#define DMA_UARTBTX        98
#define DMA_UARTBRX        99

#define DMA_SPIATX        109
#define DMA_SPIARX        110
#define DMA_UARTCTX       111
#define DMA_UARTCRX       112

#define DMA_LINATXDMA     117
#define DMA_LINARXDMA     118

#define DMA_I2C0TX        123
#define DMA_I2C0RX        125

#define DMA_FLB1INT       127
#define DMA_FLB2INT       128
#define DMA_FLB3INT       129
#define DMA_FLB4INT       130

#define DMA_CANAIF1       167
#define DMA_CANAIF2       168
#define DMA_CANAIF3       169

#define DMA_I2C1RX        170
#define DMA_I2C1TX        171

//
// OVERINTE bit
//
#define OVRFLOW_DISABLE 0x0
#define OVEFLOW_ENABLE  0x1

//
// PETEN bit
//
#define PERINT_DISABLE  0x0
#define PERINT_ENABLE   0x1

//
// GCHINTCFG bits
//
#define CHINT_BEGIN      0x0
#define CHINT_END          0x1

//
// SIGDIS bits
//
#define SIGDIS_DISABLE 0x0
#define SIGDIS_ENABLE  0x1

//
// CONTINOUS bit
//
#define CONT_DISABLE    0x0
#define CONT_ENABLE     0x1

//
// SYNCE bit
//
#define SYNC_DISABLE    0x0
#define SYNC_ENABLE     0x1

//
// SYNCSEL bit
//
#define SYNC_SRC        0x0
#define SYNC_DST        0x1

//
// DSCFG bit
//
#define SIXTEEN_BIT     0x0
#define THIRTYTWO_BIT   0x1

//
// CHINTEN bit
//
#define CHINT_DISABLE   0x0
#define CHINT_ENABLE    0x1

#ifdef __cplusplus
}
#endif

#endif /*end of G32R502_DMA_DEFINES_H_ */
//
// End of file
//
