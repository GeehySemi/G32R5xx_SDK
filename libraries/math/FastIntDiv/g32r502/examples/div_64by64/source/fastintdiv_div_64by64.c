//#############################################################################
//
// FILE:    fastintdiv_div_64by64.c
//
// TITLE:   FastIntDiv 64 by 64 division example
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
// This example shows the FastIntDiv library output, expected standard values,
// pass/fail status and DWT cycle count for each division API.
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

//*****************************************************************************
//
// Included Files
//
//*****************************************************************************
#include "fastintdiv_examples_setup.h"
#include "fastintdiv.h"
#include "system_dwtmeasure.h"

//*****************************************************************************
//
// Defines
//
//*****************************************************************************
#define FUNCTION_COUNT                  (7U)
#define TEST_COUNT                      (12U)

//*****************************************************************************
//
// Test Data and Expected Standard Values
//
//*****************************************************************************
static const FastIntDivSignedInput signed_i64_i64_inputs[] =
{
    { 0, 1 },
    { 1, 1 },
    { -1, 1 },
    { 1, -1 },
    { -1, -1 },
    { INT64_MAX, 1 },
    { INT64_MIN, 1 },
    { INT64_MIN, 2 },
    { INT64_MAX, INT64_MAX },
    { INT64_MIN, INT64_MIN },
    { 123456789012345LL, 12345 },
    { INT64_MAX, 0 },
};

static const FastIntDivSignedMethodResults signed_i64_i64_ref_values[] =
{
    {
        { 0, 0 },
        { 0, 0 },
        { 0, 0 },
    },
    {
        { 1, 0 },
        { 1, 0 },
        { 1, 0 },
    },
    {
        { -1, 0 },
        { -1, 0 },
        { -1, 0 },
    },
    {
        { -1, 0 },
        { -1, 0 },
        { -1, 0 },
    },
    {
        { 1, 0 },
        { 1, 0 },
        { 1, 0 },
    },
    {
        { INT64_MAX, 0 },
        { INT64_MAX, 0 },
        { INT64_MAX, 0 },
    },
    {
        { INT64_MIN, 0 },
        { INT64_MIN, 0 },
        { INT64_MIN, 0 },
    },
    {
        { -4611686018427387904LL, 0 },
        { -4611686018427387904LL, 0 },
        { -4611686018427387904LL, 0 },
    },
    {
        { 1, 0 },
        { 1, 0 },
        { 1, 0 },
    },
    {
        { 1, 0 },
        { 1, 0 },
        { 1, 0 },
    },
    {
        { 10000549940LL, 3045 },
        { 10000549940LL, 3045 },
        { 10000549940LL, 3045 },
    },
    {
        { 0, INT64_MAX },
        { 0, INT64_MAX },
        { 0, INT64_MAX },
    },
};

static const FastIntDivSignedUnsignedInput signed_i64_u64_inputs[] =
{
    { 0, 1U },
    { 1, 1U },
    { -1, 1U },
    { INT64_MAX, 1U },
    { INT64_MIN, 1U },
    { INT64_MIN, 2U },
    { INT64_MAX, UINT64_MAX },
    { -123456789012345LL, UINT64_MAX },
    { 123456789012345LL, 12345U },
    { -123456789012345LL, 12345U },
    { 123456789012345LL, 4000000000000000000ULL },
    { 42, 0U },
};

static const FastIntDivSignedMethodResults signed_i64_u64_ref_values[] =
{
    {
        { 0, 0 },
        { 0, 0 },
        { 0, 0 },
    },
    {
        { 1, 0 },
        { 1, 0 },
        { 1, 0 },
    },
    {
        { -1, 0 },
        { -1, 0 },
        { -1, 0 },
    },
    {
        { INT64_MAX, 0 },
        { INT64_MAX, 0 },
        { INT64_MAX, 0 },
    },
    {
        { INT64_MIN, 0 },
        { INT64_MIN, 0 },
        { INT64_MIN, 0 },
    },
    {
        { -4611686018427387904LL, 0 },
        { -4611686018427387904LL, 0 },
        { -4611686018427387904LL, 0 },
    },
    {
        { 0, INT64_MAX },
        { 0, INT64_MAX },
        { 0, INT64_MAX },
    },
    {
        { 0, -123456789012345LL },
        { -1, (int64_t)18446620616920539270ULL },
        { -1, (int64_t)18446620616920539270ULL },
    },
    {
        { 10000549940LL, 3045 },
        { 10000549940LL, 3045 },
        { 10000549940LL, 3045 },
    },
    {
        { -10000549940LL, -3045 },
        { -10000549941LL, 9300 },
        { -10000549941LL, 9300 },
    },
    {
        { 0, 123456789012345LL },
        { 0, 123456789012345LL },
        { 0, 123456789012345LL },
    },
    {
        { 0, 42 },
        { 0, 42 },
        { 0, 42 },
    },
};

static const FastIntDivUnsignedInput unsigned_u64_u64_inputs[] =
{
    { 0U, 1U },
    { 1U, 1U },
    { UINT64_MAX, 1U },
    { UINT64_MAX, UINT64_MAX },
    { UINT64_MAX, 255U },
    { 9223372036854775808ULL, 3U },
    { 123456789012345ULL, 12345U },
    { 12345U, 54321U },
    { 1000U, 7U },
    { UINT64_MAX, 0U },
    { 65537U, 256U },
    { UINT64_MAX, 17U },
};

static const FastIntDivUnsignedResult unsigned_u64_u64_ref_values[] =
{
    { 0U, 0U },
    { 1U, 0U },
    { UINT64_MAX, 0U },
    { 1U, 0U },
    { 72340172838076673ULL, 0U },
    { 3074457345618258602ULL, 2U },
    { 10000549940ULL, 3045U },
    { 0U, 12345U },
    { 142U, 6U },
    { 0U, UINT64_MAX },
    { 256U, 1U },
    { 1085102592571150095ULL, 0U },
};

volatile FastIntDivSignedCompareRecord signed_i64_i64_records[ARRAY_SIZE(signed_i64_i64_inputs)];

volatile FastIntDivSignedUnsignedCompareRecord signed_i64_u64_records[ARRAY_SIZE(signed_i64_u64_inputs)];

volatile FastIntDivUnsignedCompareRecord unsigned_u64_u64_records[ARRAY_SIZE(unsigned_u64_u64_inputs)];

// Globals
//
//*****************************************************************************
volatile uint16_t pass = 0U;
volatile uint16_t fail = 0U;
volatile uint16_t functionPass[FUNCTION_COUNT] = {0U};
volatile uint16_t functionFail[FUNCTION_COUNT] = {0U};
volatile uint16_t currentFunctionIndex = 0U;
volatile uint16_t currentTestIndex = 0U;
volatile uint32_t currentCycleCount = 0U;
volatile uint32_t functionCycleCounts[FUNCTION_COUNT][TEST_COUNT] = {0U};
volatile uint32_t functionCycleTotal[FUNCTION_COUNT] = {0U};
volatile uint32_t functionCycleAverage[FUNCTION_COUNT] = {0U};
volatile FastIntDivSignedCompareRecord last_signed_record;
volatile FastIntDivSignedUnsignedCompareRecord last_signed_unsigned_record;
volatile FastIntDivUnsignedCompareRecord last_unsigned_record;

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************
// Local Function Declarations
//
//*****************************************************************************
static FastIntDivResultMatch compareSigned(FastIntDivSignedResult output,
                                           FastIntDivSignedResult ref);
static FastIntDivResultMatch compareUnsigned(FastIntDivUnsignedResult output,
                                             FastIntDivUnsignedResult ref);
static void updateCompareResult(uint16_t functionIndex,
                                FastIntDivResultMatch match);
static void updateCycleResult(uint16_t functionIndex,
                              uint16_t testIndex,
                              uint32_t cycles);
static void updateCycleAverage(uint16_t functionIndex, uint32_t testCount);
static void runTraditionalDivI64ByI64(void);
static void runModuloDivI64ByI64(void);
static void runEuclideanDivI64ByI64(void);
static void runTraditionalDivI64ByU64(void);
static void runModuloDivI64ByU64(void);
static void runEuclideanDivI64ByU64(void);
static void runTraditionalDivU64ByU64(void);

//*****************************************************************************
//
// FastIntDiv_runTest
//
//*****************************************************************************
void FastIntDiv_runTest(void)
{
    uint32_t i;
    uint32_t j;

    pass = 0U;
    fail = 0U;
    currentFunctionIndex = 0U;
    currentTestIndex = 0U;
    currentCycleCount = 0U;

    for(i = 0U; i < FUNCTION_COUNT; i++)
    {
        functionPass[i] = 0U;
        functionFail[i] = 0U;
        functionCycleTotal[i] = 0U;
        functionCycleAverage[i] = 0U;

        for(j = 0U; j < TEST_COUNT; j++)
        {
            functionCycleCounts[i][j] = 0U;
        }
    }

    runTraditionalDivI64ByI64();
    runModuloDivI64ByI64();
    runEuclideanDivI64ByI64();
    runTraditionalDivI64ByU64();
    runModuloDivI64ByU64();
    runEuclideanDivI64ByU64();
    runTraditionalDivU64ByU64();
}

//*****************************************************************************
//
// Local Function Implementations
//
//*****************************************************************************
static FastIntDivResultMatch compareSigned(FastIntDivSignedResult output,
                                           FastIntDivSignedResult ref)
{
    FastIntDivResultMatch match;

    match.quot = (output.quot == ref.quot) ? 1U : 0U;
    match.rem = (output.rem == ref.rem) ? 1U : 0U;

    return match;
}

static FastIntDivResultMatch compareUnsigned(FastIntDivUnsignedResult output,
                                             FastIntDivUnsignedResult ref)
{
    FastIntDivResultMatch match;

    match.quot = (output.quot == ref.quot) ? 1U : 0U;
    match.rem = (output.rem == ref.rem) ? 1U : 0U;

    return match;
}

static void updateCompareResult(uint16_t functionIndex,
                                FastIntDivResultMatch match)
{
    if((match.quot != 0U) && (match.rem != 0U))
    {
        functionPass[functionIndex]++;
        pass++;
    }
    else
    {
        functionFail[functionIndex]++;
        fail++;
    }
}

static void updateCycleResult(uint16_t functionIndex,
                              uint16_t testIndex,
                              uint32_t cycles)
{
    currentCycleCount = cycles;
    functionCycleCounts[functionIndex][testIndex] = cycles;
    functionCycleTotal[functionIndex] += cycles;
}

static void updateCycleAverage(uint16_t functionIndex, uint32_t testCount)
{
    functionCycleAverage[functionIndex] =
        (testCount == 0U) ? 0U : (functionCycleTotal[functionIndex] / testCount);
}

static void runTraditionalDivI64ByI64(void)
{
    uint32_t i;
    uint32_t cycles;
    FastIntDivSignedCompareRecord localRecord;
    __lldiv_t result;

    for(i = 0U; i < ARRAY_SIZE(signed_i64_i64_inputs); i++)
    {
        currentFunctionIndex = 0U;
        currentTestIndex = (uint16_t)i;
        signed_i64_i64_records[i].input = signed_i64_i64_inputs[i];
        signed_i64_i64_records[i].ref = signed_i64_i64_ref_values[i];
        localRecord = signed_i64_i64_records[i];

        GET_DWT_CYCLE_COUNT(cycles,
                            result = __traditional_div_i64byi64((int64_t)localRecord.input.dividend,
                                               (int64_t)localRecord.input.divisor));
        signed_i64_i64_records[i].output.traditional.quot = (int64_t)result.quot;
        signed_i64_i64_records[i].output.traditional.rem = (int64_t)result.rem;
        signed_i64_i64_records[i].match.traditional =
            compareSigned(signed_i64_i64_records[i].output.traditional,
                          signed_i64_i64_records[i].ref.traditional);
        signed_i64_i64_records[i].cycleCounts.traditional = cycles;
        updateCycleResult(0U, (uint16_t)i, cycles);
        updateCompareResult(0U, signed_i64_i64_records[i].match.traditional);
        last_signed_record = signed_i64_i64_records[i];
    }

    updateCycleAverage(0U, ARRAY_SIZE(signed_i64_i64_inputs));
}

static void runModuloDivI64ByI64(void)
{
    uint32_t i;
    uint32_t cycles;
    FastIntDivSignedCompareRecord localRecord;
    __lldiv_t result;

    for(i = 0U; i < ARRAY_SIZE(signed_i64_i64_inputs); i++)
    {
        currentFunctionIndex = 1U;
        currentTestIndex = (uint16_t)i;
        signed_i64_i64_records[i].input = signed_i64_i64_inputs[i];
        signed_i64_i64_records[i].ref = signed_i64_i64_ref_values[i];
        localRecord = signed_i64_i64_records[i];

        GET_DWT_CYCLE_COUNT(cycles,
                            result = __modulo_div_i64byi64((int64_t)localRecord.input.dividend,
                                               (int64_t)localRecord.input.divisor));
        signed_i64_i64_records[i].output.modulo.quot = (int64_t)result.quot;
        signed_i64_i64_records[i].output.modulo.rem = (int64_t)result.rem;
        signed_i64_i64_records[i].match.modulo =
            compareSigned(signed_i64_i64_records[i].output.modulo,
                          signed_i64_i64_records[i].ref.modulo);
        signed_i64_i64_records[i].cycleCounts.modulo = cycles;
        updateCycleResult(1U, (uint16_t)i, cycles);
        updateCompareResult(1U, signed_i64_i64_records[i].match.modulo);
        last_signed_record = signed_i64_i64_records[i];
    }

    updateCycleAverage(1U, ARRAY_SIZE(signed_i64_i64_inputs));
}

static void runEuclideanDivI64ByI64(void)
{
    uint32_t i;
    uint32_t cycles;
    FastIntDivSignedCompareRecord localRecord;
    __lldiv_t result;

    for(i = 0U; i < ARRAY_SIZE(signed_i64_i64_inputs); i++)
    {
        currentFunctionIndex = 2U;
        currentTestIndex = (uint16_t)i;
        signed_i64_i64_records[i].input = signed_i64_i64_inputs[i];
        signed_i64_i64_records[i].ref = signed_i64_i64_ref_values[i];
        localRecord = signed_i64_i64_records[i];

        GET_DWT_CYCLE_COUNT(cycles,
                            result = __euclidean_div_i64byi64((int64_t)localRecord.input.dividend,
                                               (int64_t)localRecord.input.divisor));
        signed_i64_i64_records[i].output.euclidean.quot = (int64_t)result.quot;
        signed_i64_i64_records[i].output.euclidean.rem = (int64_t)result.rem;
        signed_i64_i64_records[i].match.euclidean =
            compareSigned(signed_i64_i64_records[i].output.euclidean,
                          signed_i64_i64_records[i].ref.euclidean);
        signed_i64_i64_records[i].cycleCounts.euclidean = cycles;
        updateCycleResult(2U, (uint16_t)i, cycles);
        updateCompareResult(2U, signed_i64_i64_records[i].match.euclidean);
        last_signed_record = signed_i64_i64_records[i];
    }

    updateCycleAverage(2U, ARRAY_SIZE(signed_i64_i64_inputs));
}

static void runTraditionalDivI64ByU64(void)
{
    uint32_t i;
    uint32_t cycles;
    FastIntDivSignedUnsignedCompareRecord localRecord;
    __lldiv_t result;

    for(i = 0U; i < ARRAY_SIZE(signed_i64_u64_inputs); i++)
    {
        currentFunctionIndex = 3U;
        currentTestIndex = (uint16_t)i;
        signed_i64_u64_records[i].input = signed_i64_u64_inputs[i];
        signed_i64_u64_records[i].ref = signed_i64_u64_ref_values[i];
        localRecord = signed_i64_u64_records[i];

        GET_DWT_CYCLE_COUNT(cycles,
                            result = __traditional_div_i64byu64((int64_t)localRecord.input.dividend,
                                               (uint64_t)localRecord.input.divisor));
        signed_i64_u64_records[i].output.traditional.quot = (int64_t)result.quot;
        signed_i64_u64_records[i].output.traditional.rem = (int64_t)result.rem;
        signed_i64_u64_records[i].match.traditional =
            compareSigned(signed_i64_u64_records[i].output.traditional,
                          signed_i64_u64_records[i].ref.traditional);
        signed_i64_u64_records[i].cycleCounts.traditional = cycles;
        updateCycleResult(3U, (uint16_t)i, cycles);
        updateCompareResult(3U, signed_i64_u64_records[i].match.traditional);
        last_signed_unsigned_record = signed_i64_u64_records[i];
    }

    updateCycleAverage(3U, ARRAY_SIZE(signed_i64_u64_inputs));
}

static void runModuloDivI64ByU64(void)
{
    uint32_t i;
    uint32_t cycles;
    FastIntDivSignedUnsignedCompareRecord localRecord;
    __lldiv_t result;

    for(i = 0U; i < ARRAY_SIZE(signed_i64_u64_inputs); i++)
    {
        currentFunctionIndex = 4U;
        currentTestIndex = (uint16_t)i;
        signed_i64_u64_records[i].input = signed_i64_u64_inputs[i];
        signed_i64_u64_records[i].ref = signed_i64_u64_ref_values[i];
        localRecord = signed_i64_u64_records[i];

        GET_DWT_CYCLE_COUNT(cycles,
                            result = __modulo_div_i64byu64((int64_t)localRecord.input.dividend,
                                               (uint64_t)localRecord.input.divisor));
        signed_i64_u64_records[i].output.modulo.quot = (int64_t)result.quot;
        signed_i64_u64_records[i].output.modulo.rem = (int64_t)result.rem;
        signed_i64_u64_records[i].match.modulo =
            compareSigned(signed_i64_u64_records[i].output.modulo,
                          signed_i64_u64_records[i].ref.modulo);
        signed_i64_u64_records[i].cycleCounts.modulo = cycles;
        updateCycleResult(4U, (uint16_t)i, cycles);
        updateCompareResult(4U, signed_i64_u64_records[i].match.modulo);
        last_signed_unsigned_record = signed_i64_u64_records[i];
    }

    updateCycleAverage(4U, ARRAY_SIZE(signed_i64_u64_inputs));
}

static void runEuclideanDivI64ByU64(void)
{
    uint32_t i;
    uint32_t cycles;
    FastIntDivSignedUnsignedCompareRecord localRecord;
    __lldiv_t result;

    for(i = 0U; i < ARRAY_SIZE(signed_i64_u64_inputs); i++)
    {
        currentFunctionIndex = 5U;
        currentTestIndex = (uint16_t)i;
        signed_i64_u64_records[i].input = signed_i64_u64_inputs[i];
        signed_i64_u64_records[i].ref = signed_i64_u64_ref_values[i];
        localRecord = signed_i64_u64_records[i];

        GET_DWT_CYCLE_COUNT(cycles,
                            result = __euclidean_div_i64byu64((int64_t)localRecord.input.dividend,
                                               (uint64_t)localRecord.input.divisor));
        signed_i64_u64_records[i].output.euclidean.quot = (int64_t)result.quot;
        signed_i64_u64_records[i].output.euclidean.rem = (int64_t)result.rem;
        signed_i64_u64_records[i].match.euclidean =
            compareSigned(signed_i64_u64_records[i].output.euclidean,
                          signed_i64_u64_records[i].ref.euclidean);
        signed_i64_u64_records[i].cycleCounts.euclidean = cycles;
        updateCycleResult(5U, (uint16_t)i, cycles);
        updateCompareResult(5U, signed_i64_u64_records[i].match.euclidean);
        last_signed_unsigned_record = signed_i64_u64_records[i];
    }

    updateCycleAverage(5U, ARRAY_SIZE(signed_i64_u64_inputs));
}

static void runTraditionalDivU64ByU64(void)
{
    uint32_t i;
    uint32_t cycles;
    FastIntDivUnsignedCompareRecord localRecord;
    __ulldiv_t result;

    for(i = 0U; i < ARRAY_SIZE(unsigned_u64_u64_inputs); i++)
    {
        currentFunctionIndex = 6U;
        currentTestIndex = (uint16_t)i;
        unsigned_u64_u64_records[i].input = unsigned_u64_u64_inputs[i];
        unsigned_u64_u64_records[i].ref = unsigned_u64_u64_ref_values[i];
        localRecord = unsigned_u64_u64_records[i];

        GET_DWT_CYCLE_COUNT(cycles,
                            result = __traditional_div_u64byu64((uint64_t)localRecord.input.dividend,
                                               (uint64_t)localRecord.input.divisor));
        unsigned_u64_u64_records[i].output.quot = (uint64_t)result.quot;
        unsigned_u64_u64_records[i].output.rem = (uint64_t)result.rem;
        unsigned_u64_u64_records[i].match = compareUnsigned(unsigned_u64_u64_records[i].output, unsigned_u64_u64_records[i].ref);
        unsigned_u64_u64_records[i].cycleCounts = cycles;
        updateCycleResult(6U, (uint16_t)i, cycles);
        updateCompareResult(6U, unsigned_u64_u64_records[i].match);
        last_unsigned_record = unsigned_u64_u64_records[i];
    }

    updateCycleAverage(6U, ARRAY_SIZE(unsigned_u64_u64_inputs));
}

// End of File
