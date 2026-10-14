//#############################################################################
//
// FILE:    fastintdiv_examples_ref.h
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

#ifndef _FASTINTDIV_EXAMPLES_REF_H_
#define _FASTINTDIV_EXAMPLES_REF_H_

#include "fastintdiv_examples_setup.h"

#ifdef __cplusplus
extern "C" {
#endif

extern FastIntDivSignedResult FastIntDiv_refTraditionalSigned(int64_t dividend, int64_t divisor);
extern FastIntDivSignedResult FastIntDiv_refModuloSigned(int64_t dividend, int64_t divisor);
extern FastIntDivSignedResult FastIntDiv_refEuclideanSigned(int64_t dividend, int64_t divisor);
extern FastIntDivSignedResult FastIntDiv_refTraditionalSignedUnsigned(int64_t dividend, uint64_t divisor);
extern FastIntDivSignedResult FastIntDiv_refModuloSignedUnsigned(int64_t dividend, uint64_t divisor);
extern FastIntDivSignedResult FastIntDiv_refEuclideanSignedUnsigned(int64_t dividend, uint64_t divisor);
extern FastIntDivUnsignedResult FastIntDiv_refTraditionalUnsigned(uint64_t dividend, uint64_t divisor);

#ifdef __cplusplus
}
#endif

#endif

// End of File
