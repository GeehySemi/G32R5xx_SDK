//#############################################################################
//
// FILE:    fastintdiv_examples_ref.c
//
// TITLE:   FastIntDiv Examples Reference Functions
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//#############################################################################
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
// $
//###########################################################################

#include "fastintdiv_examples_ref.h"

static uint64_t FastIntDiv_absI64(int64_t value)
{
    return (value < 0) ? ((uint64_t)(-(value + 1)) + 1U) : (uint64_t)value;
}

static int64_t FastIntDiv_negateMagnitude(uint64_t magnitude)
{
    if(magnitude == (1ULL << 63))
    {
        return (int64_t)(1ULL << 63);
    }

    return -(int64_t)magnitude;
}

static int64_t FastIntDiv_signedMagnitude(uint64_t magnitude, uint16_t negative)
{
    return (negative != 0U) ? FastIntDiv_negateMagnitude(magnitude) : (int64_t)magnitude;
}

FastIntDivSignedResult FastIntDiv_refTraditionalSigned(int64_t dividend, int64_t divisor)
{
    FastIntDivSignedResult result;
    uint64_t absDividend;
    uint64_t absDivisor;
    uint64_t absQuot;
    uint64_t absRem;
    uint16_t quotientNegative;
    uint16_t remainderNegative;

    if(divisor == 0)
    {
        result.quot = 0;
        result.rem = dividend;
        return result;
    }

    absDividend = FastIntDiv_absI64(dividend);
    absDivisor = FastIntDiv_absI64(divisor);
    absQuot = absDividend / absDivisor;
    absRem = absDividend % absDivisor;
    quotientNegative = ((dividend < 0) != (divisor < 0)) ? 1U : 0U;
    remainderNegative = (dividend < 0) ? 1U : 0U;

    result.quot = FastIntDiv_signedMagnitude(absQuot, quotientNegative);
    result.rem = FastIntDiv_signedMagnitude(absRem, remainderNegative);
    return result;
}

FastIntDivSignedResult FastIntDiv_refModuloSigned(int64_t dividend, int64_t divisor)
{
    FastIntDivSignedResult result;
    uint64_t absDividend;
    uint64_t absDivisor;
    uint64_t absQuot;
    uint64_t absRem;
    uint16_t signsDiffer;
    uint16_t divisorNegative;

    if(divisor == 0)
    {
        result.quot = 0;
        result.rem = dividend;
        return result;
    }

    absDividend = FastIntDiv_absI64(dividend);
    absDivisor = FastIntDiv_absI64(divisor);
    absQuot = absDividend / absDivisor;
    absRem = absDividend % absDivisor;
    signsDiffer = ((dividend < 0) != (divisor < 0)) ? 1U : 0U;
    divisorNegative = (divisor < 0) ? 1U : 0U;

    if((signsDiffer != 0U) && (absRem != 0U))
    {
        absQuot += 1U;
        absRem = absDivisor - absRem;
        result.quot = FastIntDiv_negateMagnitude(absQuot);
        result.rem = FastIntDiv_signedMagnitude(absRem, divisorNegative);
    }
    else
    {
        result.quot = FastIntDiv_signedMagnitude(absQuot, signsDiffer);
        result.rem = FastIntDiv_signedMagnitude(absRem, (dividend < 0) ? 1U : 0U);
    }

    return result;
}

FastIntDivSignedResult FastIntDiv_refEuclideanSigned(int64_t dividend, int64_t divisor)
{
    FastIntDivSignedResult result;
    uint64_t absDividend;
    uint64_t absDivisor;
    uint64_t absQuot;
    uint64_t absRem;
    uint16_t signsDiffer;

    if(divisor == 0)
    {
        result.quot = 0;
        result.rem = dividend;
        return result;
    }

    absDividend = FastIntDiv_absI64(dividend);
    absDivisor = FastIntDiv_absI64(divisor);
    absQuot = absDividend / absDivisor;
    absRem = absDividend % absDivisor;
    signsDiffer = ((dividend < 0) != (divisor < 0)) ? 1U : 0U;

    if((dividend < 0) && (absRem != 0U))
    {
        absQuot += 1U;
        absRem = absDivisor - absRem;
        result.quot = FastIntDiv_signedMagnitude(absQuot, (divisor > 0) ? 1U : 0U);
        result.rem = (int64_t)absRem;
    }
    else
    {
        result.quot = FastIntDiv_signedMagnitude(absQuot, signsDiffer);
        result.rem = (int64_t)absRem;
    }

    return result;
}

FastIntDivSignedResult FastIntDiv_refTraditionalSignedUnsigned(int64_t dividend, uint64_t divisor)
{
    FastIntDivSignedResult result;
    uint64_t absDividend;
    uint64_t absQuot;
    uint64_t absRem;
    uint16_t negative;

    if(divisor == 0U)
    {
        result.quot = 0;
        result.rem = dividend;
        return result;
    }

    absDividend = FastIntDiv_absI64(dividend);
    absQuot = absDividend / divisor;
    absRem = absDividend % divisor;
    negative = (dividend < 0) ? 1U : 0U;

    result.quot = FastIntDiv_signedMagnitude(absQuot, negative);
    result.rem = FastIntDiv_signedMagnitude(absRem, negative);
    return result;
}

FastIntDivSignedResult FastIntDiv_refModuloSignedUnsigned(int64_t dividend, uint64_t divisor)
{
    FastIntDivSignedResult result;
    uint64_t absDividend;
    uint64_t absQuot;
    uint64_t absRem;

    if(divisor == 0U)
    {
        result.quot = 0;
        result.rem = dividend;
        return result;
    }

    absDividend = FastIntDiv_absI64(dividend);
    absQuot = absDividend / divisor;
    absRem = absDividend % divisor;

    if((dividend < 0) && (absRem != 0U))
    {
        absQuot += 1U;
        absRem = divisor - absRem;
        result.quot = FastIntDiv_negateMagnitude(absQuot);
        result.rem = (int64_t)absRem;
    }
    else
    {
        result.quot = FastIntDiv_signedMagnitude(absQuot, (dividend < 0) ? 1U : 0U);
        result.rem = FastIntDiv_signedMagnitude(absRem, (dividend < 0) ? 1U : 0U);
    }

    return result;
}

FastIntDivSignedResult FastIntDiv_refEuclideanSignedUnsigned(int64_t dividend, uint64_t divisor)
{
    return FastIntDiv_refModuloSignedUnsigned(dividend, divisor);
}

FastIntDivUnsignedResult FastIntDiv_refTraditionalUnsigned(uint64_t dividend, uint64_t divisor)
{
    FastIntDivUnsignedResult result;

    if(divisor == 0U)
    {
        result.quot = 0U;
        result.rem = dividend;
        return result;
    }

    result.quot = dividend / divisor;
    result.rem = dividend % divisor;
    return result;
}

// End of File
