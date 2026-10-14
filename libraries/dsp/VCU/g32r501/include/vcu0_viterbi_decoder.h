//###########################################################################
//
// FILE:    vcu0_viterbi_decoder.h
//
// TITLE:   vcu0 viterbi decoder header file.
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
#ifndef VCU0_VITERBI_DECODER_H
#define VCU0_VITERBI_DECODER_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes *******************************************************************/
#include "vcu0_types.h"


/* Exported macro ************************************************************/
#define FRAME_LEN                   128
#define CODED_LEN                   (FRAME_LEN << 1)
#define ENCODER_LEN                 7
#define STATES                      64
#define LARGE_NEG_NUMBER            -8192

#define CNV_DEC_NUM_STATES          (1<<(G3_PHY_CNV_K -1))

/* When no overlap method is used */
/* Viterbi decodes maximum of 256 coded bits in 1 shot */
#define CNV_DEC_MAX_UBITS           128
#define CNV_DEC_MAX_CBITS           (CNV_DEC_MAX_UBITS << 1)

/* When overlap method is used */
/* Viterbi decodes in blocks of 128 coded bits */
#define CNV_DEC_BLK_UBITS           64
#define CNV_DEC_BLK_CBITS           (CNV_DEC_BLK_UBITS << 1)
#define CNV_DEC_BLK_CBITS_LOG2      7

#define CNV_DEC_BLK_UWORDS          4
#define CNV_DEC_METRIC_INIT              -16384
#define G3_PHY_CNV_K                                7

/* Exported types *************************************************************/

/**
  * @brief   Complex FFT data structure
  */
typedef enum
{
  CNV_DEC_MODE_DEC_ALL   = 0,       //!< Decodes all output bits
  CNV_DEC_MODE_OVLP_INIT = 1,       //!< Use window overlap method, only metrics and transitions update
  CNV_DEC_MODE_OVLP_DEC  = 2,     //!< Use window overlap method,
                                                                                   //!< update transitions/metrics/trace through current &
                                                                                   //!< previous blocks, decode previous block only
  CNV_DEC_MODE_OVLP_LAST = 3      //!< last block in overlap
}VITER_MODE_E;

/* Exported variables **********************************************************/

extern int16 VIT_in_data[];                         //!< Input fed into the C-model encoder
extern int16 VIT_quant_data[];                      //!< Output from the C-model encoder
extern int32 VIT_gold_vt_data[];                    //!< Golden trace history (VT0/VT1); can be used to verify functionality
extern Uint16 VIT_frame_len;

/* Exported functions *********************************************************/

extern void cnvDecInit(int16 nTranBits);

#if !__ARM_FEATURE_CDE
#error "CDE feature not supported"
#else
extern void cnvDec(int16 nBits, int16 *in_p, int16 *out_p, int16 flag);
#endif /* __ARM_FEATURE_CDE  */

extern void cnvDecMetricRescale(void);


#ifdef __cplusplus
}
#endif

#endif /*VCU0_VITERBI_DECODER_H */

/********************************* END OF FILE *********************************/
