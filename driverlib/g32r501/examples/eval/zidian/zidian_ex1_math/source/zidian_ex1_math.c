//###########################################################################
//
// FILE:    zidian_ex1_math.c
//
// TITLE:   Zidian Math Example
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1>Zidian Math</h1>
//!
//! This example demonstrates how to ues the zidian_math.h. Only sqrtf(),
//! sinf(), cosf(), atanf() and atan2f() in math.h can be accelerated by
//! Zidian. Users can observe the effect of acceleration through the
//! \b traceTime.
//!
//! Please avoid directly using the compatible functions such as __sin(),
//! __cos() and __atan().
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - traceResult - The result of the calculation.
//!  - traceTime   - The time spent on calculation.
//!
//
//###########################################################################
//
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
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "zidian_math.h"
#include "system_g32r501_dwtmeasure.h"

//
// Defines
//
#define COUNT   100U
#define PI      3.1415926535f

//
// Globals
//
SECTION_DTCM_DATA
volatile float trace1Result[COUNT];
SECTION_DTCM_DATA
volatile float trace2Result[COUNT];
SECTION_DTCM_DATA
volatile float trace3Result[COUNT];
SECTION_DTCM_DATA
volatile float trace4Result[COUNT];
SECTION_DTCM_DATA
volatile float trace5Result[COUNT];

SECTION_DTCM_DATA
volatile uint32_t dwtCycleCounts[5];

//
// Main
//
void example_main(void)
{
    volatile float x, y;
    uint16_t i;

    //
    // Test1 sqrtf
    //
    x = 0.81f;

    GET_DWT_CYCLE_COUNT(dwtCycleCounts[0],trace1Result[0] = sqrtf(x));
    
    for(i = 0; i < COUNT; i++)    
    {                             
        trace1Result[i] = sqrtf(x);
    };

    //
    // Test2 sinf
    //
    x = PI / 2;
    GET_DWT_CYCLE_COUNT(dwtCycleCounts[1],trace2Result[1] = sinf(x));
    
    for(i = 0; i < COUNT; i++)   
    {                            
        trace2Result[i] = sinf(x);
    };

    //
    // Test3 cosf
    //
    x = PI / 4;
    GET_DWT_CYCLE_COUNT(dwtCycleCounts[2], trace3Result[2] = cosf(x));
    
    for(i = 0; i < COUNT; i++)   
    {                            
        trace3Result[i] = cosf(x);
    };

    //
    // Test4 atanf
    //
    x = 5.0f;
    GET_DWT_CYCLE_COUNT(dwtCycleCounts[3], trace4Result[3] = atanf(x));
    
    for(i = 0; i < COUNT; i++)    
    {                             
        trace4Result[i] = atanf(x);
    };

    //
    // Test5 atan2f
    //
    x = 5.0f;
    y = 10.0f;
    GET_DWT_CYCLE_COUNT(dwtCycleCounts[4], trace5Result[4] = atan2f(y, x));
    
    for(i = 0; i < COUNT; i++)
    {
        trace5Result[i] = atan2f(y, x);
    };

    //
    // Loop
    //
    for(;;)
    {
    }
}

//
// End of File
//
