//#############################################################################
//
// FILE:    fastintdiv_div_32by32.c
//
// TITLE:   FastIntDiv 32 by 32 division example
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
static const FastIntDivSignedInput signed_i32_i32_inputs[] =
{
    { 0, 1 },
    { 1, 1 },
    { -1, 1 },
    { 1, -1 },
    { -1, -1 },
    { 2147483647, 1 },
    { -2147483648LL, 1 },
    { -2147483648LL, 2 },
    { 2147483647, 2147483647 },
    { -2147483648LL, -2147483648LL },
    { 123456789, 12345 },
    { 2147483647, 0 },
};

static const FastIntDivSignedMethodResults signed_i32_i32_ref_values[] =
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
        { 2147483647, 0 },
        { 2147483647, 0 },
        { 2147483647, 0 },
    },
    {
        { -2147483648LL, 0 },
        { -2147483648LL, 0 },
        { -2147483648LL, 0 },
    },
    {
        { -1073741824, 0 },
        { -1073741824, 0 },
        { -1073741824, 0 },
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
        { 10000, 6789 },
        { 10000, 6789 },
        { 10000, 6789 },
    },
    {
        { 0, 2147483647 },
        { 0, 2147483647 },
        { 0, 2147483647 },
    },
};

static const FastIntDivSignedUnsignedInput signed_i32_u32_inputs[] =
{
    { 0, 1U },
    { 1, 1U },
    { -1, 1U },
    { 2147483647, 1U },
    { -2147483648LL, 1U },
    { -2147483648LL, 2U },
    { 2147483647, 4294967295U },
    { -2147483648LL, 4294967295U },
    { 123456789, 12345U },
    { -123456789, 12345U },
    { 123456789, 4000000000U },
    { 42, 0U },
};

static const FastIntDivSignedMethodResults signed_i32_u32_ref_values[] =
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
        { 2147483647, 0 },
        { 2147483647, 0 },
        { 2147483647, 0 },
    },
    {
        { -2147483648LL, 0 },
        { -2147483648LL, 0 },
        { -2147483648LL, 0 },
    },
    {
        { -1073741824, 0 },
        { -1073741824, 0 },
        { -1073741824, 0 },
    },
    {
        { 0, 2147483647 },
        { 0, 2147483647 },
        { 0, 2147483647 },
    },
    {
        { 0, -2147483648LL },
        { -1, 2147483647 },
        { -1, 2147483647 },
    },
    {
        { 10000, 6789 },
        { 10000, 6789 },
        { 10000, 6789 },
    },
    {
        { -10000, -6789 },
        { -10001, 5556 },
        { -10001, 5556 },
    },
    {
        { 0, 123456789 },
        { 0, 123456789 },
        { 0, 123456789 },
    },
    {
        { 0, 42 },
        { 0, 42 },
        { 0, 42 },
    },
};

static const FastIntDivUnsignedInput unsigned_u32_u32_inputs[] =
{
    { 0U, 1U },
    { 1U, 1U },
    { 4294967295U, 1U },
    { 4294967295U, 4294967295U },
    { 4294967295U, 255U },
    { 2147483648U, 3U },
    { 123456789U, 12345U },
    { 12345U, 54321U },
    { 1000U, 7U },
    { 4294967295U, 0U },
    { 65537U, 256U },
    { 4294967295U, 17U },
};

static const FastIntDivUnsignedResult unsigned_u32_u32_ref_values[] =
{
    { 0U, 0U },
    { 1U, 0U },
    { 4294967295U, 0U },
    { 1U, 0U },
    { 16843009U, 0U },
    { 715827882U, 2U },
    { 10000U, 6789U },
    { 0U, 12345U },
    { 142U, 6U },
    { 0U, 4294967295U },
    { 256U, 1U },
    { 252645135U, 0U },
};

volatile FastIntDivSignedCompareRecord signed_i32_i32_records[ARRAY_SIZE(signed_i32_i32_inputs)];

volatile FastIntDivSignedUnsignedCompareRecord signed_i32_u32_records[ARRAY_SIZE(signed_i32_u32_inputs)];

volatile FastIntDivUnsignedCompareRecord unsigned_u32_u32_records[ARRAY_SIZE(unsigned_u32_u32_inputs)];

//*****************************************************************************
//
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
static void runTraditionalDivI32ByI32(void);
static void runModuloDivI32ByI32(void);
static void runEuclideanDivI32ByI32(void);
static void runTraditionalDivI32ByU32(void);
static void runModuloDivI32ByU32(void);
static void runEuclideanDivI32ByU32(void);
static void runTraditionalDivU32ByU32(void);

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

    runTraditionalDivI32ByI32();
    runModuloDivI32ByI32();
    runEuclideanDivI32ByI32();
    runTraditionalDivI32ByU32();
    runModuloDivI32ByU32();
    runEuclideanDivI32ByU32();
    runTraditionalDivU32ByU32();
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

static void runTraditionalDivI32ByI32(void)
{
    uint32_t i;
    uint32_t cycles;
    FastIntDivSignedCompareRecord localRecord;
    __ldiv_t result;

    for(i = 0U; i < ARRAY_SIZE(signed_i32_i32_inputs); i++)
    {
        currentFunctionIndex = 0U;
        currentTestIndex = (uint16_t)i;
        signed_i32_i32_records[i].input = signed_i32_i32_inputs[i];
        signed_i32_i32_records[i].ref = signed_i32_i32_ref_values[i];
        localRecord = signed_i32_i32_records[i];

        GET_DWT_CYCLE_COUNT(cycles,
                            result = __traditional_div_i32byi32((int32_t)localRecord.input.dividend,
                                               (int32_t)localRecord.input.divisor));
        signed_i32_i32_records[i].output.traditional.quot = (int64_t)result.quot;
        signed_i32_i32_records[i].output.traditional.rem = (int64_t)result.rem;
        signed_i32_i32_records[i].match.traditional =
            compareSigned(signed_i32_i32_records[i].output.traditional,
                          signed_i32_i32_records[i].ref.traditional);
        signed_i32_i32_records[i].cycleCounts.traditional = cycles;
        updateCycleResult(0U, (uint16_t)i, cycles);
        updateCompareResult(0U, signed_i32_i32_records[i].match.traditional);
        last_signed_record = signed_i32_i32_records[i];
    }

    updateCycleAverage(0U, ARRAY_SIZE(signed_i32_i32_inputs));
}

static void runModuloDivI32ByI32(void)
{
    uint32_t i;
    uint32_t cycles;
    FastIntDivSignedCompareRecord localRecord;
    __ldiv_t result;

    for(i = 0U; i < ARRAY_SIZE(signed_i32_i32_inputs); i++)
    {
        currentFunctionIndex = 1U;
        currentTestIndex = (uint16_t)i;
        signed_i32_i32_records[i].input = signed_i32_i32_inputs[i];
        signed_i32_i32_records[i].ref = signed_i32_i32_ref_values[i];
        localRecord = signed_i32_i32_records[i];

        GET_DWT_CYCLE_COUNT(cycles,
                            result = __modulo_div_i32byi32((int32_t)localRecord.input.dividend,
                                               (int32_t)localRecord.input.divisor));
        signed_i32_i32_records[i].output.modulo.quot = (int64_t)result.quot;
        signed_i32_i32_records[i].output.modulo.rem = (int64_t)result.rem;
        signed_i32_i32_records[i].match.modulo =
            compareSigned(signed_i32_i32_records[i].output.modulo,
                          signed_i32_i32_records[i].ref.modulo);
        signed_i32_i32_records[i].cycleCounts.modulo = cycles;
        updateCycleResult(1U, (uint16_t)i, cycles);
        updateCompareResult(1U, signed_i32_i32_records[i].match.modulo);
        last_signed_record = signed_i32_i32_records[i];
    }

    updateCycleAverage(1U, ARRAY_SIZE(signed_i32_i32_inputs));
}

static void runEuclideanDivI32ByI32(void)
{
    uint32_t i;
    uint32_t cycles;
    FastIntDivSignedCompareRecord localRecord;
    __ldiv_t result;

    for(i = 0U; i < ARRAY_SIZE(signed_i32_i32_inputs); i++)
    {
        currentFunctionIndex = 2U;
        currentTestIndex = (uint16_t)i;
        signed_i32_i32_records[i].input = signed_i32_i32_inputs[i];
        signed_i32_i32_records[i].ref = signed_i32_i32_ref_values[i];
        localRecord = signed_i32_i32_records[i];

        GET_DWT_CYCLE_COUNT(cycles,
                            result = __euclidean_div_i32byi32((int32_t)localRecord.input.dividend,
                                               (int32_t)localRecord.input.divisor));
        signed_i32_i32_records[i].output.euclidean.quot = (int64_t)result.quot;
        signed_i32_i32_records[i].output.euclidean.rem = (int64_t)result.rem;
        signed_i32_i32_records[i].match.euclidean =
            compareSigned(signed_i32_i32_records[i].output.euclidean,
                          signed_i32_i32_records[i].ref.euclidean);
        signed_i32_i32_records[i].cycleCounts.euclidean = cycles;
        updateCycleResult(2U, (uint16_t)i, cycles);
        updateCompareResult(2U, signed_i32_i32_records[i].match.euclidean);
        last_signed_record = signed_i32_i32_records[i];
    }

    updateCycleAverage(2U, ARRAY_SIZE(signed_i32_i32_inputs));
}

static void runTraditionalDivI32ByU32(void)
{
    uint32_t i;
    uint32_t cycles;
    FastIntDivSignedUnsignedCompareRecord localRecord;
    __ldiv_t result;

    for(i = 0U; i < ARRAY_SIZE(signed_i32_u32_inputs); i++)
    {
        currentFunctionIndex = 3U;
        currentTestIndex = (uint16_t)i;
        signed_i32_u32_records[i].input = signed_i32_u32_inputs[i];
        signed_i32_u32_records[i].ref = signed_i32_u32_ref_values[i];
        localRecord = signed_i32_u32_records[i];

        GET_DWT_CYCLE_COUNT(cycles,
                            result = __traditional_div_i32byu32((int32_t)localRecord.input.dividend,
                                               (uint32_t)localRecord.input.divisor));
        signed_i32_u32_records[i].output.traditional.quot = (int64_t)result.quot;
        signed_i32_u32_records[i].output.traditional.rem = (int64_t)result.rem;
        signed_i32_u32_records[i].match.traditional =
            compareSigned(signed_i32_u32_records[i].output.traditional,
                          signed_i32_u32_records[i].ref.traditional);
        signed_i32_u32_records[i].cycleCounts.traditional = cycles;
        updateCycleResult(3U, (uint16_t)i, cycles);
        updateCompareResult(3U, signed_i32_u32_records[i].match.traditional);
        last_signed_unsigned_record = signed_i32_u32_records[i];
    }

    updateCycleAverage(3U, ARRAY_SIZE(signed_i32_u32_inputs));
}

static void runModuloDivI32ByU32(void)
{
    uint32_t i;
    uint32_t cycles;
    FastIntDivSignedUnsignedCompareRecord localRecord;
    __ldiv_t result;

    for(i = 0U; i < ARRAY_SIZE(signed_i32_u32_inputs); i++)
    {
        currentFunctionIndex = 4U;
        currentTestIndex = (uint16_t)i;
        signed_i32_u32_records[i].input = signed_i32_u32_inputs[i];
        signed_i32_u32_records[i].ref = signed_i32_u32_ref_values[i];
        localRecord = signed_i32_u32_records[i];

        GET_DWT_CYCLE_COUNT(cycles,
                            result = __modulo_div_i32byu32((int32_t)localRecord.input.dividend,
                                               (uint32_t)localRecord.input.divisor));
        signed_i32_u32_records[i].output.modulo.quot = (int64_t)result.quot;
        signed_i32_u32_records[i].output.modulo.rem = (int64_t)result.rem;
        signed_i32_u32_records[i].match.modulo =
            compareSigned(signed_i32_u32_records[i].output.modulo,
                          signed_i32_u32_records[i].ref.modulo);
        signed_i32_u32_records[i].cycleCounts.modulo = cycles;
        updateCycleResult(4U, (uint16_t)i, cycles);
        updateCompareResult(4U, signed_i32_u32_records[i].match.modulo);
        last_signed_unsigned_record = signed_i32_u32_records[i];
    }

    updateCycleAverage(4U, ARRAY_SIZE(signed_i32_u32_inputs));
}

static void runEuclideanDivI32ByU32(void)
{
    uint32_t i;
    uint32_t cycles;
    FastIntDivSignedUnsignedCompareRecord localRecord;
    __ldiv_t result;

    for(i = 0U; i < ARRAY_SIZE(signed_i32_u32_inputs); i++)
    {
        currentFunctionIndex = 5U;
        currentTestIndex = (uint16_t)i;
        signed_i32_u32_records[i].input = signed_i32_u32_inputs[i];
        signed_i32_u32_records[i].ref = signed_i32_u32_ref_values[i];
        localRecord = signed_i32_u32_records[i];

        GET_DWT_CYCLE_COUNT(cycles,
                            result = __euclidean_div_i32byu32((int32_t)localRecord.input.dividend,
                                               (uint32_t)localRecord.input.divisor));
        signed_i32_u32_records[i].output.euclidean.quot = (int64_t)result.quot;
        signed_i32_u32_records[i].output.euclidean.rem = (int64_t)result.rem;
        signed_i32_u32_records[i].match.euclidean =
            compareSigned(signed_i32_u32_records[i].output.euclidean,
                          signed_i32_u32_records[i].ref.euclidean);
        signed_i32_u32_records[i].cycleCounts.euclidean = cycles;
        updateCycleResult(5U, (uint16_t)i, cycles);
        updateCompareResult(5U, signed_i32_u32_records[i].match.euclidean);
        last_signed_unsigned_record = signed_i32_u32_records[i];
    }

    updateCycleAverage(5U, ARRAY_SIZE(signed_i32_u32_inputs));
}

static void runTraditionalDivU32ByU32(void)
{
    uint32_t i;
    uint32_t cycles;
    FastIntDivUnsignedCompareRecord localRecord;
    __uldiv_t result;

    for(i = 0U; i < ARRAY_SIZE(unsigned_u32_u32_inputs); i++)
    {
        currentFunctionIndex = 6U;
        currentTestIndex = (uint16_t)i;
        unsigned_u32_u32_records[i].input = unsigned_u32_u32_inputs[i];
        unsigned_u32_u32_records[i].ref = unsigned_u32_u32_ref_values[i];
        localRecord = unsigned_u32_u32_records[i];

        GET_DWT_CYCLE_COUNT(cycles,
                            result = __traditional_div_u32byu32((uint32_t)localRecord.input.dividend,
                                               (uint32_t)localRecord.input.divisor));
        unsigned_u32_u32_records[i].output.quot = (uint64_t)result.quot;
        unsigned_u32_u32_records[i].output.rem = (uint64_t)result.rem;
        unsigned_u32_u32_records[i].match = compareUnsigned(unsigned_u32_u32_records[i].output, unsigned_u32_u32_records[i].ref);
        unsigned_u32_u32_records[i].cycleCounts = cycles;
        updateCycleResult(6U, (uint16_t)i, cycles);
        updateCompareResult(6U, unsigned_u32_u32_records[i].match);
        last_unsigned_record = unsigned_u32_u32_records[i];
    }

    updateCycleAverage(6U, ARRAY_SIZE(unsigned_u32_u32_inputs));
}

// End of File
