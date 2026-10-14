//###########################################################################
//
// FILE:    system_dwtmeasure.h
//
// TITLE:   DWT Measurement Functions for G32R5xx Devices.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//###########################################################################
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

#ifndef SYSTEM_DWTMEASURE_H
#define SYSTEM_DWTMEASURE_H

#include <stdint.h>
#include "core_cm52.h"  // Include CMSIS core header file

// Macro to enable or disable DWT measurement
#ifndef ENABLE_DWT_MEASURE
#define ENABLE_DWT_MEASURE 1 // Default to enable if not defined by the user
#endif

// Macro to enable or disable interrupt disabling during DWT measurement
#ifndef DISABLE_INTERRUPTS_WHILE_MEASURE
#define DISABLE_INTERRUPTS_WHILE_MEASURE 1 // Default to enable if not defined by the user
#endif

// Macro to define the size of the dwtCycleCounts array
#ifndef DWT_CYCLE_COUNTS_SIZE
#define DWT_CYCLE_COUNTS_SIZE 30 // Default size if not defined by the user
#endif

#if ENABLE_DWT_MEASURE

// Enable DWT counter
#define ENABLE_DWT_CYCCNT()  do { DCB->DEMCR |= DCB_DEMCR_TRCENA_Msk; DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; } while (0)

// Reset DWT counter
#define RESET_DWT_CYCCNT()   do { DWT->CYCCNT = 0; } while (0)

// Macro to get DWT cycle count
// cycle_count: variable to store DWT cycle count
// code_to_run: code block whose DWT cycle count needs to be measured 

// The maximum time that can be measured depends on the clock speed of the processor and the width of the DWT_CYCCNT register. 
// For a 32-bit wide DWT_CYCCNT register:
// - If the processor clock speed is 100 MHz, the maximum measurable time would be approximately 42.94 seconds (2^32 / 100,000,000).
// - If the processor clock speed is 200 MHz, the maximum measurable time would be approximately 21.47 seconds (2^32 / 200,000,000).
// The formula to calculate the maximum measurable time is: (2^32 / processor_clock_speed).
//
// Note: Interrupts can affect the accuracy of the DWT cycle count measurement. 
// When an interrupt occurs, the processor may switch to executing the interrupt service routine (ISR), 
// causing additional cycles to be counted in the DWT_CYCCNT register. 
// To ensure accurate measurement of the DWT cycle count for the given code block, 
// interrupts can be disabled during the measurement period. However, disabling interrupts may not be suitable 
// for all applications, especially those with time-critical interrupts. 
// The DISABLE_INTERRUPTS_WHILE_MEASURE macro can be used to control whether interrupts are disabled during the measurement.
//
// To convert the measured clock cycles to time in seconds, use the following formula:
// time_in_seconds = cycle_count / processor_clock_speed
// For example, if the processor clock speed is 200 MHz and cycle_count is 5000000 cycles, 
// then the execution time in seconds would be:
// time_in_seconds = 5000000 / 200,000,000 = 0.025 seconds

#if DISABLE_INTERRUPTS_WHILE_MEASURE
    #define GET_DWT_CYCLE_COUNT(cycle_count, code_to_run) \
        do { \
            uint32_t _dwt_saved_primask = __get_PRIMASK(); \
            __disable_irq(); \
            ENABLE_DWT_CYCCNT(); \
            RESET_DWT_CYCCNT(); \
            code_to_run; \
            cycle_count = DWT->CYCCNT; \
            __set_PRIMASK(_dwt_saved_primask); \
        } while (0)
#else
    #define GET_DWT_CYCLE_COUNT(cycle_count, code_to_run) \
        do { \
            ENABLE_DWT_CYCCNT(); \
            RESET_DWT_CYCCNT(); \
            code_to_run; \
            cycle_count = DWT->CYCCNT; \
        } while (0)
#endif

#else // ENABLE_DWT_MEASURE

// If DWT measurement is disabled, provide empty macros
#define ENABLE_DWT_CYCCNT()  // No operation
#define RESET_DWT_CYCCNT()   // No operation
#define GET_DWT_CYCLE_COUNT(cycle_count, code_to_run) code_to_run; cycle_count = 0;

#endif // ENABLE_DWT_MEASURE

#endif // SYSTEM_DWTMEASURE_H

//
// End of file
//
