//#############################################################################
//
// FILE:    dsp_examples_setup.h
//
// TITLE:   DSP Examples Common Code
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

#ifndef _DSP_EXAMPLES_SETUP_H_
#define _DSP_EXAMPLES_SETUP_H_
//*****************************************************************************
// the includes
//*****************************************************************************
#include <stdint.h>
#include <float.h>
#include <math.h>
#include "device.h"

//!
//! \defgroup FASTRTS_EXAMPLES_SETUP Fast RTS Examples Setup Code

//!
//! \ingroup FASTRTS_EXAMPLES_SETUP
//@{

#ifdef __cplusplus

extern "C" {
#endif

//*****************************************************************************
//defines
//*****************************************************************************

//*****************************************************************************
// typedefs
//*****************************************************************************

//*****************************************************************************
//globals
//*****************************************************************************

// Each test will define these variables
extern volatile uint16_t pass, fail;

extern uint64_t toleranceLSBMantissa;

//*****************************************************************************
// the function prototypes
//*****************************************************************************
//! \brief Setup system controls
//! 
extern void FastRTS_Example_setupSysCtrl( void );


//! \brief Setup flash
//! 
extern void FastRTS_Example_setupFlash( void );

//! \brief Run a particular Fast RTS routine
//! 
extern void FastRTS_runTest( void );

//! \brief Function indicating end of test (Autobot regression)
//! 
extern void done( void );

#ifdef __cplusplus
{
#endif // extern "C"
//@}  // ingroup

#endif  // end of  _FASTRTS_EXAMPLES_SETUP_H_ definition

// End of File