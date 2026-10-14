//###########################################################################
// 
// FILE:    FPUfastRTS.h
// 
// TITLE:   FPUfastRTS header file
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
#ifndef     FPU_FAST_RTS_H
#define     FPU_FAST_RTS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes *******************************************************************/
#include "fpu_types.h"

typedef unsigned char      uint8;
typedef unsigned short int       uint16;
typedef unsigned int      uint32;
typedef unsigned long uint64;

typedef signed int      int32;

typedef  union
{
        float             fract;
        signed int    integer;
}floatsize_u;

#ifdef __ZIDIAN_FCAU__

#define    sinf(X)                    sinf32(X)
#define    cosf(X)                   cosf32(X)
#define    sincosf(radian,PtrSin,PtrCos)               sincosf32(radian,PtrSin,PtrCos)
#define    asinf(X)                  asinf32(X)
#define    acosf(X)                 acosf32(X)
#define    atanf(X)                 atanf32(X)
#define    atan2f(Y,X)          atan2f32(Y,X)
#define    sqrtf(X)                  sqrtf32(X)
#define    isqrtf(X)                 isqrtf32(X)
#define    divf(Y,X)               divf32(Y,X)

#else
#define    sinf(X)                     sinf_1(X)
#define    cosf(X)                    cosf_1(X)
#define    sincosf(radian,PtrSin,PtrCos)               sincosf_1(radian,PtrSin,PtrCos)
#define    asinf(X)                   asinf_1(X)
#define    acosf(X)                  acosf_1(X)
#define    atanf(X)                  atanf_1(X)
#define    atan2f(Y,X)           atan2f_1(Y,X)
#define    sqrtf(X)                  sqrtf_1(X)
#define    isqrtf(X)                 isqrtf_1(X)
#define    divf(Y,X)               Y/X   
#endif

#define   expf(X)                   expf_1(X)
#define   logf(X)                     logf_1(X)
#define   powf(X,Y)              powf_1(X,Y)

float32_t sinf_1(float32_t X);
float32_t cosf_1(float32_t X);
void sincosf_1(float32_t radian, float32_t *PtrSin, float32_t *PtrCos);
float32_t sqrtf_1 (float32_t X);
float32_t isqrtf_1(float32_t X);
float32_t atanf_1(float32_t X);
float32_t atan2f_1 (float32_t Y, float32_t X);

float32_t asinf_1(float32_t X);

float32_t acosf_1(float32_t X);

float32_t expf_1 (float32_t X);
float32_t logf_1(float32_t X);   
float32_t powf_1(float32_t X, float32_t Y);


#if !__ARM_FEATURE_CDE
#error "CDE feature not supported"
#else
float sinf32(float X) __attribute__((always_inline));
float cosf32(float X) __attribute__((always_inline));
void sincosf32(float radian, float *PtrSin, float *PtrCos) __attribute__((always_inline));
float atanf32(float X) __attribute__((always_inline));
float atan2f32(float Y, float X) __attribute__((always_inline));
float sqrtf32(float X) __attribute__((always_inline));
float isqrtf32(float X) __attribute__((always_inline));
float divf32(float num, float denom) __attribute__((always_inline));
float asinf32(float X);
float acosf32(float X);
#endif /* __ARM_FEATURE_CDE  */

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif


