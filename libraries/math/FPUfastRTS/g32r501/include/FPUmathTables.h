//###########################################################################
// 
// FILE:    FPUmathTable.h
// 
// TITLE:   FPUmathTable header file
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

#ifndef _FPU_MATH_TABLES_H
#define _FPU_MATH_TABLES_H

#define  SINCOS_TABLE_SIZE    512
#define  COS_TABLE_OFFSET    SINCOS_TABLE_SIZE/4


#define  PI                                     3.14159265358979f
#define  PIDIV2                            1.570796326f

#define  RADIAN_RATIO1     0.012271846644531f      // 2*PI/SINCOS_TABLE_SIZE

#define RADIAN_RATIO        81.4873308630505f                 // SINCOS_TABLE_SIZE/(2*PI)

#define RADIAN_RATIO2    651.898646904404f    // SIN_TABLE_SIZE/(0.5*PI)

#define   LOG2                           0.693147180559f

#define ATAN2_TABLE_SIZE    64
#define LOG_TABLE_SIZE         32


extern const  float sincosTable[SINCOS_TABLE_SIZE + SINCOS_TABLE_SIZE/4 +1];

extern const float atan2Table[(ATAN2_TABLE_SIZE + 1) *3];

extern const float expTableCoff[6];
extern const float expTable[89];
extern const float logTable[(LOG_TABLE_SIZE + 1) *3];
#endif

