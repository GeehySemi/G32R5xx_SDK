//###########################################################################
//
// FILE:    fpu_rfft.h
//
// TITLE:   fpu rfft header file.
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

#ifndef FPU_RFFT_H
#define FPU_RFFT_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes *******************************************************************/

#include "fpu_types.h"

/* Exported macro *************************************************************/

#define   RFFT_f32u(hndRFFT_F32)                                  RFFT_f32(hndRFFT_F32)  
#define   RFFT_adc_f32u(hndRFFT_ADC_F32)              RFFT_adc_f32(hndRFFT_ADC_F32)

/* Exported types *************************************************************/

/** 
  *@brief  Structure for the Real FFT
  */
typedef struct 
{
    float  *InBuf;                     //!< Pointer to the input buffer
    float  *OutBuf;            //!< Pointer to the output buffer
    float  *CosSinBuf;               //!< Pointer to the twiddle factors
    float  *MagBuf;                   //!< Pointer to the magnitude buffer
    float  *PhaseBuf;                //!< Pointer to the phase buffer
    uint16_t   FFTSize;                 //!< Size of the FFT (number of real data points)
    uint16_t   FFTStages;            //!< Number of FFT stages
} RFFT_F32_STRUCT;

/** 
  *@brief  Handle to the Real FFT object
  */
typedef RFFT_F32_STRUCT* RFFT_F32_STRUCT_Handle;

/** 
  *@brief  Structure for the Real FFT with ADC input
  */
typedef struct 
{
    uint16_t   *InBuf;                 //!< Pointer to the input buffer
    void         *Tail;                   //!< Null pointer to the OutBuf of RFFT_F32_STRUCT
} RFFT_ADC_F32_STRUCT;

/** 
  *@brief  Handle to the Real FFT (with ADC input) structure
  */
typedef RFFT_ADC_F32_STRUCT* RFFT_ADC_F32_STRUCT_Handle;

/* Exported variables *********************************************************/
extern float RFFT_f32_twiddleFactors[1020];
extern float FPU32RFFTtwiddleFactors[1020];

/* Private functions **********************************************************/
void RFFT_f32_setInputPtr(RFFT_F32_STRUCT_Handle fh, const float *pi);
float * RFFT_f32_getInputPtr(RFFT_F32_STRUCT_Handle fh);
void RFFT_f32_setOutputPtr(RFFT_F32_STRUCT_Handle fh, const float *po);
float * RFFT_f32_getOutputPtr(RFFT_F32_STRUCT_Handle fh);
void RFFT_f32_setTwiddlesPtr(RFFT_F32_STRUCT_Handle fh,const float *pc);
float * RFFT_f32_getTwiddlesPtr(RFFT_F32_STRUCT_Handle fh);
void RFFT_f32_setMagnitudePtr(RFFT_F32_STRUCT_Handle fh, const float *pm);
float * RFFT_f32_getMagnitudePtr(RFFT_F32_STRUCT_Handle fh);
void RFFT_f32_setPhasePtr(RFFT_F32_STRUCT_Handle fh, const float *pp);
float * RFFT_f32_getPhasePtr(RFFT_F32_STRUCT_Handle fh);
void RFFT_f32_setStages(RFFT_F32_STRUCT_Handle fh, const uint16_t st);
uint16_t RFFT_f32_getStages(RFFT_F32_STRUCT_Handle fh);
void RFFT_f32_setFFTSize(RFFT_F32_STRUCT_Handle fh, const uint16_t sz);
uint16_t RFFT_f32_getFFTSize(RFFT_F32_STRUCT_Handle fh);
void RFFT_ADC_f32_setInBufPtr(RFFT_ADC_F32_STRUCT_Handle fh, const uint16_t * pi);
uint16_t *RFFT_ADC_f32_getInBufPtr(RFFT_ADC_F32_STRUCT_Handle fh);
void RFFT_ADC_f32_setTailPtr(RFFT_ADC_F32_STRUCT_Handle fh, const void * pt);
void *RFFT_ADC_f32_getTailPtr(RFFT_ADC_F32_STRUCT_Handle fh);


/* Exported functions *********************************************************/
extern void RFFT_f32(RFFT_F32_STRUCT_Handle hndRFFT_F32);

extern void RFFT_f32u(RFFT_F32_STRUCT_Handle hndRFFT_F32);

extern void RFFT_adc_f32(RFFT_ADC_F32_STRUCT_Handle hndRFFT_ADC_F32);

extern void RFFT_adc_f32u(RFFT_ADC_F32_STRUCT_Handle hndRFFT_ADC_F32);

extern void RFFT_f32_win(float *pBuffer, const float *pWindow, const uint16_t size);

extern void RFFT_adc_f32_win(uint16_t *pBuffer, const uint16_t *pWindow, const uint16_t size);

extern void RFFT_f32_mag(RFFT_F32_STRUCT_Handle hndRFFT_F32);

extern void RFFT_f32s_mag(RFFT_F32_STRUCT_Handle hndRFFT_F32);

extern void RFFT_f32_phase(RFFT_F32_STRUCT_Handle hndRFFT_F32);

#if !__ARM_FEATURE_CDE
#error "CDE feature not supported"
#else
extern void RFFT_f32_mag_TMU0(RFFT_F32_STRUCT_Handle hndRFFT_F32);

extern void RFFT_f32s_mag_TMU0(RFFT_F32_STRUCT_Handle hndRFFT_F32);

extern void RFFT_f32_phase_TMU0(RFFT_F32_STRUCT_Handle hndRFFT_F32);

#endif /* __ARM_FEATURE_CDE  */

extern void RFFT_f32_sincostable(RFFT_F32_STRUCT_Handle hndRFFT_F32);


#ifdef __cplusplus
}
#endif

#endif /*FPU_RFFT_H */  

/********************************* END OF FILE *********************************/
