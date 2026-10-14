//#############################################################################
//
// FILE:    examples_setup.h
//
// TITLE:   Initialization routines for the VCU2 library examples
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//#############################################################################
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

#ifndef _VCU2_EXAMPLES_SETUP_H_
#define _VCU2_EXAMPLES_SETUP_H_
//*****************************************************************************
// includes
//*****************************************************************************
#include "g32r501_device.h"
#include "g32r501_examples.h"


#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************

//*****************************************************************************
// typedefs
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// function prototypes
//*****************************************************************************
// \brief Initialize system clocks
//
void VCU2_initSystemClocks(void);

// \brief Initialize Enhanced PIE
//
void VCU2_initEpie(void);

// \brief Disable Flash prefetch
//
extern void InitFlash_PrefetchCacheDisable(void);

// \brief Enable Flash prefetch
//
extern void InitFlash_PrefetchCacheEnable(void);

// \brief Set Flash wait states
// \param[in] waitStates The number of wait states
//
void SetupFlash(unsigned short waitStates);

// \brief autobot done()
//
void done(void);

#ifdef __cplusplus
}
#endif // extern "C"

#endif //end of _VCU2_EXAMPLES_SETUP_H_ definition
