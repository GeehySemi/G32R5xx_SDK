//###########################################################################
// 
// FILE:    SecureROMAPIs.h
//                                
// TITLE:   SecureROMAPIs header file
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

#ifndef SECURE_ROM_APIS_H
#define SECURE_ROM_APIS_H

#include <stdint.h>

extern uint16_t SafeCopyCodeZ1(uint16_t size, uint8_t *dst, uint8_t *src);
extern uint16_t SafeCopyCodeZ2(uint16_t size, uint8_t *dst, uint8_t *src);
extern uint16_t SafeCRCCalcZ1(uint16_t len_id, uint8_t *dst, uint8_t *src);
extern uint16_t SafeCRCCalcZ2(uint16_t len_id, uint8_t *dst, uint8_t *src);
extern uint32_t CPU1BROM_calculateCMAC(uint32_t startAddress, uint32_t endAddress, uint32_t tagAddress);

#endif  // end of SECURE_ROM_APIS_H definition
