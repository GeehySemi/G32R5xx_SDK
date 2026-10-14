//###########################################################################
//
// FILE:    vcu0_crc.h
//
// TITLE:   vcu0_crc header file.
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

#ifndef   VCU0_CRC_H
#define   VCU0_CRC_H


#ifdef __cplusplus
extern "C"
{
#endif

/* Includes *******************************************************************/
#include "vcu0_types.h"

/* Exported macro ************************************************************/

#define INIT_CRC8      0x0                         //!< Initial CRC Register Value
#define INIT_CRC16     0x0                         //!< Initial CRC Register Value
#define INIT_CRC32     0x0                         //!< Initial CRC Register Value
#define POLYNOMIAL16_1 0x8005                      //!< CRC16 802.15.4 Polynomial
#define POLYNOMIAL16_2 0x1021                      //!< CRC16 Alternate Polynomial
#define POLYNOMIAL32   0x04c11db7                  //!< CRC32 PRIME Polynomial
#define POLYNOMIAL8    0x07                        //!< CRC8 PRIME Polynomial


/* Exported variables *********************************************************/
extern uint16 crc8_table[];
extern uint16 crc16p1_table[];
extern uint16 crc16p2_table[];
extern uint32 crc32_table[];

/* Exported functions *********************************************************/

#if !__ARM_FEATURE_CDE
#error "CDE feature not supported"
#else

extern uint8 getCRC8_vcu(uint32 input_crc8_accum, uint16 *msg, CRC_parity_e parity, uint16 rxLen);

extern uint16 getCRC16P1_vcu(uint32 input_crc16_accum, uint16 * msg, CRC_parity_e parity, uint16 rxLen);

extern uint16 getCRC16P2_vcu(uint32 input_crc16_accum, uint16 * msg, CRC_parity_e parity, uint16 rxLen);

extern uint32 getCRC32_vcu (uint32 input_crc32_accum, uint16 *msg, CRC_parity_e parity, uint16 rxLen);

#endif /* __ARM_FEATURE_CDE  */

extern void genCRC8Table();

extern void genCRC16P1Table();

extern void genCRC16P2Table();

extern void genCRC32Table();

uint16 getCRC8_cpu(uint16 input_crc8_accum, uint16 *msg, CRC_parity_e parity, uint16 rxLen);

uint16 getCRC16P1_cpu (uint16 input_crc16_accum, uint16 *msg, CRC_parity_e parity, uint16 rxLen);

uint16 getCRC16P2_cpu (uint16 input_crc16_accum, uint16 *msg, CRC_parity_e parity, uint16 rxLen);

uint32 getCRC32_cpu (uint32 input_crc32_accum, uint16 *msg, CRC_parity_e parity, uint16 rxLen);

#if !__ARM_FEATURE_CDE
#error "CDE feature not supported"
#else

void CRC_reset(void);

#endif /* __ARM_FEATURE_CDE  */

#ifdef __cplusplus
}
#endif

#endif /*VCU0_CRC_H */

/********************************* END OF FILE *********************************/
