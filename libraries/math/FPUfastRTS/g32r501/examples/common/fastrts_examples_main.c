//#############################################################################
//
// FILE:    dsp_examples_main.c
//
// TITLE:   DSP Examples - The main()
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

//*****************************************************************************
// the includes
//*****************************************************************************
#include "fastrts_examples_setup.h"

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
int main(void)
{
    //
    // Setup the FLASH Banks
    //
    FastRTS_Example_setupFlash();

    //
    // Setup system clocking
    //
    FastRTS_Example_setupSysCtrl();

    //
    // Run the test
    //
    FastRTS_runTest();

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
