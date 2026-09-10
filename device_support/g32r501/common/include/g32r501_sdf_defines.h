//###########################################################################
//
// FILE:    g32r501_sdf_defines.h
//
// TITLE:   #defines used in sdf examples
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//###########################################################################
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
// 1. Updated header file title for G32R501 SDF definitions.
// 2. Changed file name to g32r501_sdf_defines.h to reflect the new architecture.
// 3. Modified filter data read macros to align with G32R501 specifications.
//
//###########################################################################

#ifndef G32R501_SDF_DEFINES_H
#define G32R501_SDF_DEFINES_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Macro to read the SDF1 filter data in 16 bit format
//
#define SDF1_READ_FILTER1_DATA_16BIT     (*(volatile int16 *)((uint32_t)0x40003C2E))
#define SDF1_READ_FILTER2_DATA_16BIT     (*(volatile int16 *)((uint32_t)0x40003C4E))
#define SDF1_READ_FILTER3_DATA_16BIT     (*(volatile int16 *)((uint32_t)0x40003C6E))
#define SDF1_READ_FILTER4_DATA_16BIT     (*(volatile int16 *)((uint32_t)0x40003C8E))

//
// Macro to read the SDF1 filter data in 32 bit format
//
#define SDF1_READ_FILTER1_DATA_32BIT    (*(volatile int32 *)((uint32_t)0x40003C2C))
#define SDF1_READ_FILTER2_DATA_32BIT    (*(volatile int32 *)((uint32_t)0x40003C4C))
#define SDF1_READ_FILTER3_DATA_32BIT    (*(volatile int32 *)((uint32_t)0x40003C6C))
#define SDF1_READ_FILTER4_DATA_32BIT    (*(volatile int32 *)((uint32_t)0x40003C8C))

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of G32R501_SDF_DEFINES_H

//
// End of file
//
