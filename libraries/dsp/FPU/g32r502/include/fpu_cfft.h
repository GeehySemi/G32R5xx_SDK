//###########################################################################
//
// FILE:    fpu_cfft.h
//
// TITLE:   fpu cfft header file.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
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

#ifndef FPU_CFFT_H
#define FPU_CFFT_H


#ifdef __cplusplus
extern "C"
{
#endif

/* Includes *******************************************************************/

#include "fpu_types.h"

/* Exported macro *************************************************************/

#define TABLE_SIZE      (1024U)
#define TABLE_SIZE_LOG2 (10U)

#define   CFFT_f32ut(hndCFFT_F32)             CFFT_f32t(hndCFFT_F32)   
#define   CFFT_f32u(hndCFFT_F32)              CFFT_f32(hndCFFT_F32)    

/* Exported types *************************************************************/

/** 
  *@brief  Complex FFT structure
  */
typedef struct 
{
    float   *InPtr;                               //!< Pointer to the input buffer
    float   *OutPtr;                             //!< Pointer to the output buffer
    float   *CoefPtr;                           //!< Pointer to the twiddle factors
    float   *CurrentInPtr;                  //!< Points to input buffer at each FFT stage
    float   *CurrentOutPtr;                //!< Points to output buffer at each FFT stage
    uint16_t Stages;                             //!< Number of FFT stages
    uint16_t FFTSize;                           //!< Size of the FFT (number of complex data points)
} CFFT_F32_STRUCT;

/** 
  *@brief  Handle to the CFFT_F32 structure
  */
typedef CFFT_F32_STRUCT* CFFT_F32_STRUCT_Handle;

/* Exported variables *********************************************************/
extern float CFFT_f32_twiddleFactors[768];
extern uint16_t tableSize;
extern uint16_t tableStage;

/* Private functions **********************************************************/
void CFFT_f32_setInputPtr(CFFT_F32_STRUCT_Handle fh,const float *pi);
float * CFFT_f32_getInputPtr(CFFT_F32_STRUCT_Handle fh);
void CFFT_f32_setOutputPtr(CFFT_F32_STRUCT_Handle fh,const float *po);
float * CFFT_f32_getOutputPtr(CFFT_F32_STRUCT_Handle fh);
void CFFT_f32_setTwiddlesPtr(CFFT_F32_STRUCT_Handle fh,const float *pc);
float * CFFT_f32_getTwiddlesPtr(CFFT_F32_STRUCT_Handle fh);
void CFFT_f32_setCurrInputPtr(CFFT_F32_STRUCT_Handle fh,const float *pi);
float * CFFT_f32_getCurrInputPtr(CFFT_F32_STRUCT_Handle fh);
void CFFT_f32_setCurrOutputPtr(CFFT_F32_STRUCT_Handle fh,const float *po);
float * CFFT_f32_getCurrOutputPtr(CFFT_F32_STRUCT_Handle fh);
void CFFT_f32_setStages(CFFT_F32_STRUCT_Handle fh,const uint16_t st);
uint16_t CFFT_f32_getStages(CFFT_F32_STRUCT_Handle fh);
void CFFT_f32_setFFTSize(CFFT_F32_STRUCT_Handle fh,const uint16_t sz);
uint16_t CFFT_f32_getFFTSize(CFFT_F32_STRUCT_Handle fh);


/* Exported functions *********************************************************/
extern void CFFT_f32(CFFT_F32_STRUCT_Handle hndCFFT_F32);

extern void CFFT_f32_brev(CFFT_F32_STRUCT_Handle hndCFFT_F32);

extern void CFFT_f32i(CFFT_F32_STRUCT_Handle hndCFFT_F32);

extern void CFFT_f32t(CFFT_F32_STRUCT_Handle hndCFFT_F32);

extern void CFFT_f32it(CFFT_F32_STRUCT_Handle hndCFFT_F32);

extern void CFFT_f32u(CFFT_F32_STRUCT_Handle hndCFFT_F32);

extern void CFFT_f32ut(CFFT_F32_STRUCT_Handle hndCFFT_F32);

extern void CFFT_f32_sincostable(CFFT_F32_STRUCT_Handle hndCFFT_F32);

extern void CFFT_f32_win(float *pBuffer, const float *pWindow, const uint16_t size); 

extern void CFFT_f32_win_dual(float *pBuffer, const float *pWindow, const uint16_t size); 

extern void CFFT_f32_mag(CFFT_F32_STRUCT_Handle hndCFFT_F32);

extern void CFFT_f32s_mag(CFFT_F32_STRUCT_Handle hndCFFT_F32);

extern void CFFT_f32_phase(CFFT_F32_STRUCT_Handle hndCFFT_F32);

extern void CFFT_f32_unpack(CFFT_F32_STRUCT_Handle hndCFFT_F32);

extern void CFFT_f32_pack(CFFT_F32_STRUCT_Handle hndCFFT_F32);


#if !__ARM_FEATURE_CDE
#error "CDE feature not supported"
#else
extern void CFFT_f32_mag_TMU0(CFFT_F32_STRUCT_Handle hndCFFT_F32);

extern void CFFT_f32s_mag_TMU0(CFFT_F32_STRUCT_Handle hndCFFT_F32);

extern void CFFT_f32_phase_TMU0(CFFT_F32_STRUCT_Handle hndCFFT_F32);
#endif /* __ARM_FEATURE_CDE  */

extern void ICFFT_f32(CFFT_F32_STRUCT_Handle hndCFFT_F32);

extern void ICFFT_f32t(CFFT_F32_STRUCT_Handle hndCFFT_F32);


#ifdef __cplusplus
}
#endif

#endif /*FPU_CFFT_H */  

/********************************* END OF FILE *********************************/
