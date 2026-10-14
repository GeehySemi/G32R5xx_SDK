//###########################################################################
//
// FILE:    vcu0_fft.h
//
// TITLE:   vcu0_fft header file.
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

#ifndef  VCU0_FFT_H
#define  VCU0_FFT_H


#ifdef __cplusplus
extern "C"
{
#endif

/* Includes *******************************************************************/
#include "vcu0_types.h"

/* Exported macro ************************************************************/

#define  rfft16_unpack (fft_hnd)  rfft16_unpack_asm (fft_hnd)

/**
  * @brief   Default values for the complex FFT structure for 64 sample points
  */
#define cfft16_64P_DEFAULTS    { (int16 *)NULL,\
        (int16 *)NULL,\
        (int16*)NULL,\
        64,\
        6,\
        8,\
        (int16 *)NULL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_64p_calc}

/**
  * @brief   Default values for the complex FFT structure for 64 sample points
  *              if using bit reversal lookup table (Deprecated)
  */
#define cfft16_64P_BREV_DEFAULTS    { (int16 *)NULL,\
        (int16 *)NULL,\
        (int16 *)NULL,\
        64,\
        6,\
        8,\
        BIT_REV_64_TBL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_64p_calc}

/**
  * @brief   Default values for the complex FFT structure for 128 sample points
  */
#define cfft16_128P_DEFAULTS    { (int16 *)NULL,\
        (int16 *)NULL,\
        (int16 *)NULL,\
        128,\
        7,\
        4,\
        (int16 *)NULL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_128p_calc}

/**
  * @brief   Default values for the complex FFT structure for 256 sample points
  */
#define cfft16_256P_DEFAULTS    { (int16 *)NULL,\
        (int16 *)NULL,\
        (int16*)NULL,\
        256,\
        8,\
        2,\
        (int16 *)NULL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_256p_calc}

/**
  * @brief   Default values for the complex FFT structure for 128 real sample points
  */
#define rfft16_128P_DEFAULTS    { (int16 *)NULL,\
        (int16 *)NULL,\
        (int16*)NULL,\
        64,\
        6,\
        4,\
        (int16 *)NULL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_64p_calc}

/**
  * @brief   Default values for the complex FFT structure for 256 real sample points
  */
#define rfft16_256P_DEFAULTS    { (int16 *)NULL,\
        (int16 *)NULL,\
        (int16 *)NULL,\
        128,\
        7,\
        4,\
        (int16 *)NULL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_128p_calc}

/**
  * @brief   Default values for the complex FFT structure for 512 real sample points
  */
#define rfft16_512P_DEFAULTS    { (int16 *)NULL,\
        (int16 *)NULL,\
        (int16 *)NULL,\
        256,\
        8,\
        1,\
        (int16 *)NULL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_256p_calc}

/**
  * @brief   Default values for the Real Inverse FFT structure for 64 points
  */
#define rifft16_64P_DEFAULTS   \
        cfft16_64P_DEFAULTS

/**
  * @brief   Default values for the Real Inverse FFT structure for 128 points
  */
#define rifft16_128P_DEFAULTS   \
        cfft16_128P_DEFAULTS

/**
  * @brief   Default values for the Real Inverse FFT structure for 256 points
  */
#define rifft16_256P_DEFAULTS   \
        cfft16_256P_DEFAULTS

#define cfft16_pack(fft_hnd)    \
        cfft16_pack_asm(fft_hnd)

#define cfft16_unpack(fft_hnd)  \
        cfft16_unpack_asm(fft_hnd)

/* Exported types *************************************************************/

/**
  * @brief   Complex FFT data structure
  */
typedef struct {
        int16 *ipcbptr;                     //!< input buffer pointer
        int16 *workptr;                     //!< work buffer pointer
        int16*tfptr;                        //!< twiddle factor table pointer
        int16 size;                         //!< Number of data points
        int16  nrstage;                     //!< Number of FFT stages
        int16 step;                         //!< Twiddle factor table search step
        int16 *brevptr;                     //!< Bit reversal table pointer
        void (*init)(void *);               //!< Function pointer to initialization routine
        void (*calc)(void *);               //!< Function pointer to calculation routine
        }cfft16_t;

typedef cfft16_t  *cfft16_handle_s;         //!< Handle to structure

/* Exported variables **********************************************************/

extern SINT16 CFFT16_64p_in_data[];             //!< Input fed into the simulator
extern SINT16 CFFT16_64p_out_data[];            //!< Output from the simulator
extern SINT16 CFFT16_64p_brev_in_data[];        //!< Input fed into the simulator
extern SINT16 CFFT16_64p_brev_out_data[];       //!< Output from the simulator
extern SINT16 CFFT16_128p_in_data[];            //!< Input fed into the simulator
extern SINT16 CFFT16_128p_out_data[];           //!< Output from the simulator
extern SINT16 CFFT16_256p_in_data[];            //!< Input fed into the simulator
extern SINT16 CFFT16_256p_out_data[];           //!< Output from the simulator
extern SINT16 RFFT16_128p_in_data[];            //!< Input fed into the simulator
extern SINT16 RFFT16_128p_out_data[];           //!< Output from the simulator
extern SINT16 RFFT16_256p_in_data[];            //!< Input fed into the simulator
extern SINT16 RFFT16_256p_out_data[];           //!< Output from the simulator
extern SINT16 RFFT16_512p_in_data[];            //!< Input fed into the simulator
extern SINT16 RFFT16_512p_out_data[];           //!< Output from the simulator
extern SINT16 RIFFT16_64p_in_data[];            //!< Input fed into the simulator
extern SINT16 RIFFT16_64p_out_data[];           //!< Output from the simulator
extern SINT16 RIFFT16_128p_in_data[];           //!< Input fed into the simulator
extern SINT16 RIFFT16_128p_out_data[];          //!< Output from the simulator
extern SINT16 RIFFT16_256p_in_data[];           //!< Input fed into the simulator
extern SINT16 RIFFT16_256p_out_data[];          //!< Output from the simulator
extern SINT16 BIT_REV_64_TBL[64];
extern SINT16 CFFT16_TF[];

/* Exported functions *********************************************************/

extern void cfft16_init(cfft16_t  *cfft16_handle_s);

extern void cfft16_brev(cfft16_t  *cfft16_handle_s);

extern void cfft16_flip_re_img(cfft16_t  *cfft16_handle_s);

#if !__ARM_FEATURE_CDE
#error "CDE feature not supported"
#else

extern void cfft16_flip_re_img_conj(cfft16_t  *cfft16_handle_s);

extern void cfft16_unpack(cfft16_t  *cfft16_handle_s);

extern void cifft16_pack(cfft16_t  *cfft16_handle_s);

extern void cfft16_64p_calc(cfft16_t  *cfft16_handle_s);

extern void cfft16_128p_calc(cfft16_t  *cfft16_handle_s);

extern void cfft16_256p_calc(cfft16_t  *cfft16_handle_s);

#endif /* __ARM_FEATURE_CDE  */

extern void cfft16_tbl_brev(cfft16_t  *cfft16_handle_s) __attribute__ ((__deprecated__));

#ifdef __cplusplus
}
#endif

#endif /*VCU0_FFT_H */

/********************************* END OF FILE *********************************/
