//###########################################################################
//
// FILE:    fpu_types.h
//
// TITLE:   fpu type define header file.
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

#ifndef FPU_TYPES_H
#define FPU_TYPES_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes *******************************************************************/
#include <stdint.h>
#include "float.h"



/* Exported macro *************************************************************/

#define USE_LEGACY_NAMES    (0U)

/* Exported types *************************************************************/

/** 
  *@brief  Complex Float data type for the single precision DSP library
  */
typedef struct 
{
    float dat[2];                   //!< dat[0] is the real portion while dat[1] is the imaginary part.
} complex_float;

typedef struct
{
  float  real;                    //!< Real Part
  float  imag;            //!< Imaginary Part
}ComplexFloat;

typedef union
{
    uint32_t    ui32; //!< Unsigned long representation
    int32_t     i32;  //!< Signed long represntaion 
    float       f32;  //!< Single precision (32-bit) representation
}float32u_t;


typedef float         float32_t;
typedef double        float64_t;
typedef void (*v_pfn_v)(void *);


#ifdef __cplusplus
}
#endif

#endif /*FPU_TYPES_H */  

/********************************* END OF FILE *********************************/
