//###########################################################################
// @copyright  Copyright(c)2026 GEEHY MICROELECTRONICS INC.ALL RIGHTS RESERVED.
//
// @file       vcu0_types.h
//
// @brief      vcu0_types header file.
//
// @version    V1.0.0
//
// @date       2026-06-30
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

#ifndef VCU0_TYPES_H
#define VCU0_TYPES_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes *******************************************************************/
#include <limits.h>
#include <stdint.h>

/* Exported macro ************************************************************/

#ifndef TRUE
#define TRUE                    (1)
#define FALSE                   (0)
#endif /* TRUE */

#define PARITY(a) ((a) % 2)

#define ALIGN16(len)    (((len) + 1) & ~1)

/* size of, in octets */
#define OCTETS(x)   ((sizeof(x)) * (CHAR_BIT >> 3))

#define SIZEOF_SINT16         2
#define SIZEOF_UINT16         2
#define SIZEOF_SINT32         4
#define SIZEOF_UINT32         4

/* Exported types *************************************************************/

/** 
  * @brief   Parity enumeration   
  */  
typedef enum 
{
    CRC_parity_even = 0,        //!< Even parity, CRC starts at the low byte of the first word
    CRC_parity_odd  = 1         //!< Odd parity, CRC starts at the high byte of the first word
} CRC_parity_e;

typedef unsigned char       uint8;
typedef unsigned short int  uint16;
typedef unsigned int        uint32;
typedef unsigned long       uint64;
typedef short int           int16;
typedef int                 int32;
typedef long                int64;
typedef unsigned short int  Uint16;
typedef unsigned int        Uint32;
typedef unsigned long       Uint64;
typedef float               float32;
typedef long double         float64;

#ifndef VCU0_TYPES
#define VCU0_TYPES
typedef long               RCODE;

/* Read-Write Data Types */
typedef signed short int     SINT16;   //!< Signed 16-bit integer (15-bit magnitude)
typedef unsigned short int   UINT16;   //!< Unsigned 16-bit integer
typedef signed int           SINT32;   //!< Signed 32-bit integer (31-bit magnitude)
typedef unsigned int         UINT32;   //!< Unsigned 32-bit integer
typedef signed long          SINT64;   //!< Signed 64-bit integer
typedef unsigned long        UINT64;   //!< Unsigned 64-bit integer
typedef short int            BOOL;     //!< Only TRUE/FALSE applied

/* All pointers are 32 bits long */
typedef SINT16               *PSINT16;  //!< Pointer to SINT16
typedef UINT16               *PUINT16;  //!< Pointer to UINT16
typedef SINT32               *PSINT32;  //!< Pointer to SINT32
typedef UINT32               *PUINT32;  //!< Pointer to UINT32

#if 1
/** 
  * @brief   Complex data   
  */
typedef struct
{
    SINT16 imag; 			//!< Real Part
    SINT16 real; 			//!< Imaginary Part
} ComplexShort;

typedef struct
{
    SINT32 imag; 			//!< Real Part
    SINT32 real; 			//!< Imaginary Part
} ComplexInt;


typedef struct
{
   SINT32 L_int32; 			//!< Real Part
   SINT32 H_int32; 			//!< Imaginary Part
}LongInt;
#endif


#endif /* VCU0_TYPES */

#ifdef __cplusplus
}
#endif

#endif /*VCU0_TYPES_H */  

/********************************* END OF FILE *********************************/
