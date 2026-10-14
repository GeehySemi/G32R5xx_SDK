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
#include "inc/hw_types.h"

//!
//! \defgroup DSP_EXAMPLES_SETUP DSP Examples Setup Code

//!
//! \ingroup DSP_EXAMPLES_SETUP
//@{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//defines
//*****************************************************************************
#define PWM_CLK            DEVICE_APBCLK_FREQ

#define PWM_CLKDIV         32UL        // TBCTL_CLKDIV(4)*TBCTL_HSPCLKDIV(8)

#define PWM1_FREQ          10000UL
#define PWM2_FREQ          1000UL
#define PWM1_PERIOD        (uint16_t)(PWM_CLK/(PWM_CLKDIV*PWM1_FREQ))
#define PWM2_PERIOD        (uint16_t)(PWM_CLK/(2UL*PWM_CLKDIV*PWM2_FREQ))
#define PWM2_DUTY_CYCLE    (PWM2_PERIOD/2)

//*****************************************************************************
// typedefs
//*****************************************************************************

//*****************************************************************************
//globals
//*****************************************************************************

//*****************************************************************************
// the function prototypes
//*****************************************************************************
//! \brief Setup system controls
//! 
extern void DSP_Example_setupSysCtrl( void );

//! \brief Function to disable pin locks and enable pullups on GPIOs.
//!
extern void DSP_Example_initGPIO(void);

//! \brief Setup flash
//! 
extern void DSP_Example_setupFlash( void );

//! \brief Run a particular Fast RTS routine
//! 
extern void DSP_runTest( void );

//! \brief Function indicating end of test (Autobot regression)
//!
extern void done( void );

#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif  // end of  _DSP_EXAMPLES_SETUP_H_ definition

// End of File
