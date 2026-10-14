//#############################################################################
//
// FILE:    dsp_examples_main.c
//
// TITLE:   DSP Examples - The main()
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


//*****************************************************************************
// the includes
//*****************************************************************************
#include "dsp_examples_setup.h"

//*****************************************************************************
// the globals
//*****************************************************************************

//*****************************************************************************
// the function definitions
//*****************************************************************************

/*******************************************************************************
* Function Name  : main
* Description    : Main fuction of this program
*******************************************************************************/
int main()
{
    //
    // Setup the FLASH Banks
    //
    DSP_Example_setupFlash();

    //
    // Setup system clocking
    //
    DSP_Example_setupSysCtrl();

    //
    // Run the test
    //
    DSP_runTest();

    //
    //
    // End Test - loop forever
    //
    done();

    //
    // Code does not get to this point
    //
    return(1);
}

//
// End of File
//
