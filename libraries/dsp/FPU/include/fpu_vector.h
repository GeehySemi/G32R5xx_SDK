//###########################################################################
//
// FILE:    fpu_vector.h
//
// TITLE:   fpu vector header file.
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

#ifndef FPU_VECTOR_H
#define FPU_VECTOR_H



#ifdef __cplusplus
extern "C"
{
#endif

/* Includes *******************************************************************/
#include "fpu_types.h"


/* Exported macro *************************************************************/

//#ifdef USE_TMU
//#define abs_SP_CV(y,x,N)     abs_SP_CV_TMU0(y,x,N)
//#define iabs_SP_CV(y,x,N)    iabs_SP_CV_TMU0(y,x,N)

//#else

//#define abs_SP_CV(y,x,N)     abs_SP_CV(y,x,N)
//#define iabs_SP_CV(y,x,N)    iabs_SP_CV(y,x,N)

//#endif
#define   memcpy_fast_far(dst, src,N)               memcpy_fast(dst, src,N)

/* Exported functions *********************************************************/
extern void abs_SP_CV(float *y, const complex_float *x, const uint16_t N);

extern void abs_SP_CV_2(float *y, const complex_float *x, const uint16_t N);

#if !__ARM_FEATURE_CDE
#error "CDE feature not supported"
#else
extern void abs_SP_CV_TMU0(float *y, const complex_float *x, const uint16_t N);
#endif /* __ARM_FEATURE_CDE  */

extern void add_SP_CSxCV(complex_float *y, const complex_float *x, const complex_float c, const uint16_t N);

extern void add_SP_CVxCV(complex_float *y, const complex_float *w, const complex_float *x, const uint16_t N);

extern void iabs_SP_CV(float *y, const complex_float *x, const uint16_t N);

extern void iabs_SP_CV_2(float *y, const complex_float *x, const uint16_t N);

#if !__ARM_FEATURE_CDE
#error "CDE feature not supported"
#else
extern void iabs_SP_CV_TMU0(float *y, const complex_float *x, const uint16_t N);
#endif /* __ARM_FEATURE_CDE  */

extern complex_float mac_SP_CVxCV(const complex_float *w, const complex_float *x, const uint16_t N);

extern complex_float mac_SP_RVxCV(const complex_float *w, const float *x, const uint16_t N);

extern complex_float mac_SP_i16RVxCV(const complex_float *w, const int16_t *x, const uint16_t N);

extern uint16_t maxidx_SP_RV_2(const float *x, const uint16_t N);

extern complex_float mean_SP_CV_2(const complex_float *x, const uint16_t N);

extern float median_noreorder_SP_RV(const float *x, const uint16_t N);

extern float median_SP_RV(float *x, const uint16_t N);

extern void memcpy_fast(void *dst, const void *src, const uint16_t N);

extern void memset_fast(void* dst, const int16_t value, const uint16_t N);

extern complex_float mpy_SP_CSxCS(const complex_float w, const complex_float x);

extern void mpy_SP_CVxCV(complex_float *y, const complex_float *w, const complex_float *x, const uint16_t N);

extern void mpy_SP_CVxCVC(complex_float *y, const complex_float *w, const complex_float *x, const uint16_t N);

extern void mpy_SP_RMxRM(float *y, const float *w, const float *x,
                         const uint16_t m, const uint16_t n, const uint16_t p);

extern void mpy_SP_RMxRM_2(float *y, const float *w, const float *x,
                        const uint16_t m, const uint16_t n, const uint16_t p);

extern void mpy_SP_RSxRV_2(float *y, const float *x, const float c, const uint16_t N);

extern void mpy_SP_RSxRVxRV_2(float *y, const float *w, const float *x, const float c, const uint16_t N);

extern void mpy_SP_RVxCV(complex_float *y, const complex_float *w,
                         const float *x, const uint16_t N);

extern void mpy_SP_RVxRV_2(float *y, const float *w, const float *x,
                           const uint16_t N);

extern void qsort_SP_RV(void *x, const uint16_t N);

extern float rnd_SP_RS(const float x);

extern void sub_SP_CSxCV(complex_float *y, const complex_float *x, const complex_float c, const uint16_t N);

extern void sub_SP_CVxCV(complex_float *y, const complex_float *w, const complex_float *x, const uint16_t N);



#ifdef __cplusplus
}
#endif

#endif /*FPU_VECTOR_H */

/********************************* END OF FILE *********************************/
