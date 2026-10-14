//#############################################################################
//
// FILE:    fastintdiv_div_16by16.c
//
// TITLE:   FastIntDiv 16 by 16 division example
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
#define FUNCTION_COUNT                  (4U)
#define TEST_COUNT                      (12U)

//*****************************************************************************
//
// Test Data and Expected Standard Values
//
//*****************************************************************************
static const FastIntDivSignedInput signed_i16_inputs[] =
{
    { 0, 1 },
    { 1, 1 },
    { -1, 1 },
    { 7, 3 },
    { -7, 3 },
    { 7, -3 },
    { -7, -3 },
    { 32767, 1 },
    { -32768, 1 },
    { 12345, 67 },
    { -12345, 67 },
    { 1000, 0 },
};

static const FastIntDivSignedMethodResults signed_i16_ref_values[] =
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
        { 2, 1 },
        { 2, 1 },
        { 2, 1 },
    },
    {
        { -2, -1 },
        { -3, 2 },
        { -3, 2 },
    },
    {
        { -2, 1 },
        { -3, -2 },
        { -2, 1 },
    },
    {
        { 2, -1 },
        { 2, -1 },
        { 3, 2 },
    },
    {
        { 32767, 0 },
        { 32767, 0 },
        { 32767, 0 },
    },
    {
        { -32768, 0 },
        { -32768, 0 },
        { -32768, 0 },
    },
    {
        { 184, 17 },
        { 184, 17 },
        { 184, 17 },
    },
    {
        { -184, -17 },
        { -185, 50 },
        { -185, 50 },
    },
    {
        { 0, 1000 },
        { 0, 1000 },
        { 0, 1000 },
    },
};

static const FastIntDivUnsignedInput unsigned_u16_inputs[] =
{
    { 0U, 1U },
    { 1U, 1U },
    { 65535U, 1U },
    { 65535U, 255U },
    { 65535U, 65535U },
    { 32768U, 3U },
    { 12345U, 67U },
    { 67U, 12345U },
    { 1000U, 7U },
    { 65535U, 0U },
    { 1025U, 32U },
    { 65535U, 17U },
};

static const FastIntDivUnsignedResult unsigned_u16_ref_values[] =
{
    { 0U, 0U },
    { 1U, 0U },
    { 65535U, 0U },
    { 257U, 0U },
    { 1U, 0U },
    { 10922U, 2U },
    { 184U, 17U },
    { 0U, 67U },
    { 142U, 6U },
    { 0U, 65535U },
    { 32U, 1U },
    { 3855U, 0U },
};

volatile FastIntDivSignedCompareRecord signed_i16_records[ARRAY_SIZE(signed_i16_inputs)];

volatile FastIntDivUnsignedCompareRecord unsigned_u16_records[ARRAY_SIZE(unsigned_u16_inputs)];

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
static void runTraditionalDivI16ByI16(void);
static void runModuloDivI16ByI16(void);
static void runEuclideanDivI16ByI16(void);
static void runTraditionalDivU16ByU16(void);

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

    runTraditionalDivI16ByI16();
    runModuloDivI16ByI16();
    runEuclideanDivI16ByI16();
    runTraditionalDivU16ByU16();
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

static void runTraditionalDivI16ByI16(void)
{
    uint32_t i;
    uint32_t cycles;
    FastIntDivSignedCompareRecord localRecord;
    __ldiv_t result;

    for(i = 0U; i < ARRAY_SIZE(signed_i16_inputs); i++)
    {
        currentFunctionIndex = 0U;
        currentTestIndex = (uint16_t)i;
        signed_i16_records[i].input = signed_i16_inputs[i];
        signed_i16_records[i].ref = signed_i16_ref_values[i];
        localRecord = signed_i16_records[i];

        GET_DWT_CYCLE_COUNT(cycles,
                            result = __traditional_div_i16byi16((int16_t)localRecord.input.dividend,
                                               (int16_t)localRecord.input.divisor));
        signed_i16_records[i].output.traditional.quot = (int64_t)result.quot;
        signed_i16_records[i].output.traditional.rem = (int64_t)result.rem;
        signed_i16_records[i].match.traditional =
            compareSigned(signed_i16_records[i].output.traditional,
                          signed_i16_records[i].ref.traditional);
        signed_i16_records[i].cycleCounts.traditional = cycles;
        updateCycleResult(0U, (uint16_t)i, cycles);
        updateCompareResult(0U, signed_i16_records[i].match.traditional);
        last_signed_record = signed_i16_records[i];
    }

    updateCycleAverage(0U, ARRAY_SIZE(signed_i16_inputs));
}

static void runModuloDivI16ByI16(void)
{
    uint32_t i;
    uint32_t cycles;
    FastIntDivSignedCompareRecord localRecord;
    __ldiv_t result;

    for(i = 0U; i < ARRAY_SIZE(signed_i16_inputs); i++)
    {
        currentFunctionIndex = 1U;
        currentTestIndex = (uint16_t)i;
        signed_i16_records[i].input = signed_i16_inputs[i];
        signed_i16_records[i].ref = signed_i16_ref_values[i];
        localRecord = signed_i16_records[i];

        GET_DWT_CYCLE_COUNT(cycles,
                            result = __modulo_div_i16byi16((int16_t)localRecord.input.dividend,
                                               (int16_t)localRecord.input.divisor));
        signed_i16_records[i].output.modulo.quot = (int64_t)result.quot;
        signed_i16_records[i].output.modulo.rem = (int64_t)result.rem;
        signed_i16_records[i].match.modulo =
            compareSigned(signed_i16_records[i].output.modulo,
                          signed_i16_records[i].ref.modulo);
        signed_i16_records[i].cycleCounts.modulo = cycles;
        updateCycleResult(1U, (uint16_t)i, cycles);
        updateCompareResult(1U, signed_i16_records[i].match.modulo);
        last_signed_record = signed_i16_records[i];
    }

    updateCycleAverage(1U, ARRAY_SIZE(signed_i16_inputs));
}

static void runEuclideanDivI16ByI16(void)
{
    uint32_t i;
    uint32_t cycles;
    FastIntDivSignedCompareRecord localRecord;
    __ldiv_t result;

    for(i = 0U; i < ARRAY_SIZE(signed_i16_inputs); i++)
    {
        currentFunctionIndex = 2U;
        currentTestIndex = (uint16_t)i;
        signed_i16_records[i].input = signed_i16_inputs[i];
        signed_i16_records[i].ref = signed_i16_ref_values[i];
        localRecord = signed_i16_records[i];

        GET_DWT_CYCLE_COUNT(cycles,
                            result = __euclidean_div_i16byi16((int16_t)localRecord.input.dividend,
                                               (int16_t)localRecord.input.divisor));
        signed_i16_records[i].output.euclidean.quot = (int64_t)result.quot;
        signed_i16_records[i].output.euclidean.rem = (int64_t)result.rem;
        signed_i16_records[i].match.euclidean =
            compareSigned(signed_i16_records[i].output.euclidean,
                          signed_i16_records[i].ref.euclidean);
        signed_i16_records[i].cycleCounts.euclidean = cycles;
        updateCycleResult(2U, (uint16_t)i, cycles);
        updateCompareResult(2U, signed_i16_records[i].match.euclidean);
        last_signed_record = signed_i16_records[i];
    }

    updateCycleAverage(2U, ARRAY_SIZE(signed_i16_inputs));
}

static void runTraditionalDivU16ByU16(void)
{
    uint32_t i;
    uint32_t cycles;
    FastIntDivUnsignedCompareRecord localRecord;
    __uldiv_t result;

    for(i = 0U; i < ARRAY_SIZE(unsigned_u16_inputs); i++)
    {
        currentFunctionIndex = 3U;
        currentTestIndex = (uint16_t)i;
        unsigned_u16_records[i].input = unsigned_u16_inputs[i];
        unsigned_u16_records[i].ref = unsigned_u16_ref_values[i];
        localRecord = unsigned_u16_records[i];

        GET_DWT_CYCLE_COUNT(cycles,
                            result = __traditional_div_u16byu16((uint16_t)localRecord.input.dividend,
                                               (uint16_t)localRecord.input.divisor));
        unsigned_u16_records[i].output.quot = (uint64_t)result.quot;
        unsigned_u16_records[i].output.rem = (uint64_t)result.rem;
        unsigned_u16_records[i].match = compareUnsigned(unsigned_u16_records[i].output, unsigned_u16_records[i].ref);
        unsigned_u16_records[i].cycleCounts = cycles;
        updateCycleResult(3U, (uint16_t)i, cycles);
        updateCompareResult(3U, unsigned_u16_records[i].match);
        last_unsigned_record = unsigned_u16_records[i];
    }

    updateCycleAverage(3U, ARRAY_SIZE(unsigned_u16_inputs));
}

// End of File
