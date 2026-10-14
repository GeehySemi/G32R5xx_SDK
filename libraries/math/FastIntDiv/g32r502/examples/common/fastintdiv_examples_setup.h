//#############################################################################
//
// FILE:    fastintdiv_examples_setup.h
//
// TITLE:   FastIntDiv Examples Common Code
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//#############################################################################
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

#ifndef _FASTINTDIV_EXAMPLES_SETUP_H_
#define _FASTINTDIV_EXAMPLES_SETUP_H_

//*****************************************************************************
//
// Included Files
//
//*****************************************************************************
#include <stdint.h>
#include "device.h"
#include "fastintdiv.h"

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
// Defines
//
//*****************************************************************************
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)                       (sizeof(x) / sizeof((x)[0]))
#endif

//*****************************************************************************
//
// Typedefs
//
//*****************************************************************************
typedef struct
{
    int64_t quot;
    int64_t rem;
} FastIntDivSignedResult;

typedef struct
{
    uint64_t quot;
    uint64_t rem;
} FastIntDivUnsignedResult;

typedef struct
{
    FastIntDivSignedResult traditional;
    FastIntDivSignedResult modulo;
    FastIntDivSignedResult euclidean;
} FastIntDivSignedMethodResults;

typedef struct
{
    uint32_t traditional;
    uint32_t modulo;
    uint32_t euclidean;
} FastIntDivSignedMethodCycles;

typedef struct
{
    uint16_t quot;
    uint16_t rem;
} FastIntDivResultMatch;

typedef struct
{
    FastIntDivResultMatch traditional;
    FastIntDivResultMatch modulo;
    FastIntDivResultMatch euclidean;
} FastIntDivSignedMethodMatch;

typedef struct
{
    int64_t dividend;
    int64_t divisor;
} FastIntDivSignedInput;

typedef struct
{
    int64_t dividend;
    uint64_t divisor;
} FastIntDivSignedUnsignedInput;

typedef struct
{
    uint64_t dividend;
    uint64_t divisor;
} FastIntDivUnsignedInput;

typedef struct
{
    FastIntDivSignedInput input;
    FastIntDivSignedMethodResults output;
    FastIntDivSignedMethodResults ref;
    FastIntDivSignedMethodMatch match;
    FastIntDivSignedMethodCycles cycleCounts;
} FastIntDivSignedCompareRecord;

typedef struct
{
    FastIntDivSignedUnsignedInput input;
    FastIntDivSignedMethodResults output;
    FastIntDivSignedMethodResults ref;
    FastIntDivSignedMethodMatch match;
    FastIntDivSignedMethodCycles cycleCounts;
} FastIntDivSignedUnsignedCompareRecord;

typedef struct
{
    FastIntDivUnsignedInput input;
    FastIntDivUnsignedResult output;
    FastIntDivUnsignedResult ref;
    FastIntDivResultMatch match;
    uint32_t cycleCounts;
} FastIntDivUnsignedCompareRecord;

//*****************************************************************************
//
// Globals
//
//*****************************************************************************
extern volatile uint16_t pass;
extern volatile uint16_t fail;

//*****************************************************************************
//
// Function Prototypes
//
//*****************************************************************************
extern void FastIntDiv_Example_setupSysCtrl(void);
extern void FastIntDiv_Example_setupFlash(void);
extern void FastIntDiv_runTest(void);
extern void done(void);

#ifdef __cplusplus
}
#endif

#endif

// End of File
