//#############################################################################
// FILE:    examples_setup.c
//
// TITLE:   nitialization routines for the VCU2 library examples
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
// includes
//*****************************************************************************
#include "examples_setup.h"
//*****************************************************************************
// defines
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************

void VCU2_initSystemClocks()
{
    InitSysCtrl();              //Enable peripheral clocks
}

void VCU2_initEpie()
{
    DINT;                                //Globally disable maskable CPU interrupts
    Interrupt_initModule();              //Clear and disable all PIE interrupts
    Interrupt_initVectorTable();         //Populate the PIE interrupt vector table with shell ISRs
}

void done(void)
{
    for(;;);
}
// End of file
