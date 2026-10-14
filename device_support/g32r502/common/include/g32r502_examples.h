//###########################################################################
//
// FILE:    g32r502_examples.h
//
// TITLE:   g32r502 Device Definitions.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//###########################################################################
//
//
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//
// Modifications:
// - 2026-06-30: 
// 1. Updated header file title to reflect G32R502 device definitions.
// 2. Changed file name to g32r502_examples.h to match the new device 
//    architecture.
// 3. Adjusted PLL integer multiplier definitions for G32R502 compatibility.
// 4. Updated CPU rate definition to support 200MHz clock speed.
// 5. Modified function pointer for ADC calibration to match G32R502 
//    specifications.
// 6. Included G32R502-specific header files for GPIO, PWM, and timer operations.
// 7. Retained existing structure of timer operations while adapting to G32R502.
//
//###########################################################################

#ifndef G32R502_EXAMPLES_H
#define G32R502_EXAMPLES_H

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// The following are values that can be passed to the
// InitSysPll() to select SYSPLL integer multiplier
//*****************************************************************************

#define   IMULT_0         0
#define   IMULT_1         1
#define   IMULT_2         2
#define   IMULT_3         3
#define   IMULT_4         4
#define   IMULT_5         5
#define   IMULT_6         6
#define   IMULT_7         7
#define   IMULT_8         8
#define   IMULT_9         9
#define   IMULT_10        10
#define   IMULT_11        11
#define   IMULT_12        12
#define   IMULT_13        13
#define   IMULT_14        14
#define   IMULT_15        15
#define   IMULT_16        16
#define   IMULT_17        17
#define   IMULT_18        18
#define   IMULT_19        19
#define   IMULT_20        20
#define   IMULT_21        21
#define   IMULT_22        22
#define   IMULT_23        23
#define   IMULT_24        24
#define   IMULT_25        25
#define   IMULT_26        26
#define   IMULT_27        27
#define   IMULT_28        28
#define   IMULT_29        29
#define   IMULT_30        30
#define   IMULT_31        31
#define   IMULT_32        32
#define   IMULT_33        33
#define   IMULT_34        34
#define   IMULT_35        35
#define   IMULT_36        36
#define   IMULT_37        37
#define   IMULT_38        38
#define   IMULT_39        39
#define   IMULT_40        40
#define   IMULT_41        41
#define   IMULT_42        42
#define   IMULT_43        43
#define   IMULT_44        44
#define   IMULT_45        45
#define   IMULT_46        46
#define   IMULT_47        47
#define   IMULT_48        48
#define   IMULT_49        49
#define   IMULT_50        50
#define   IMULT_51        51
#define   IMULT_52        52
#define   IMULT_53        53
#define   IMULT_54        54
#define   IMULT_55        55
#define   IMULT_56        56
#define   IMULT_57        57
#define   IMULT_58        58
#define   IMULT_59        59
#define   IMULT_60        60
#define   IMULT_61        61
#define   IMULT_62        62
#define   IMULT_63        63
#define   IMULT_64        64
#define   IMULT_65        65
#define   IMULT_66        66
#define   IMULT_67        67
#define   IMULT_68        68
#define   IMULT_69        69
#define   IMULT_70        70
#define   IMULT_71        71
#define   IMULT_72        72
#define   IMULT_73        73
#define   IMULT_74        74
#define   IMULT_75        75
#define   IMULT_76        76
#define   IMULT_77        77
#define   IMULT_78        78
#define   IMULT_79        79
#define   IMULT_80        80
#define   IMULT_81        81
#define   IMULT_82        82
#define   IMULT_83        83
#define   IMULT_84        84
#define   IMULT_85        85
#define   IMULT_86        86
#define   IMULT_87        87
#define   IMULT_88        88
#define   IMULT_89        89
#define   IMULT_90        90
#define   IMULT_91        91
#define   IMULT_92        92
#define   IMULT_93        93
#define   IMULT_94        94
#define   IMULT_95        95
#define   IMULT_96        96
#define   IMULT_97        97
#define   IMULT_98        98
#define   IMULT_99        99
#define   IMULT_100       100
#define   IMULT_101       101
#define   IMULT_102       102
#define   IMULT_103       103
#define   IMULT_104       104
#define   IMULT_105       105
#define   IMULT_106       106
#define   IMULT_107       107
#define   IMULT_108       108
#define   IMULT_109       109
#define   IMULT_110       110
#define   IMULT_111       111
#define   IMULT_112       112
#define   IMULT_113       113
#define   IMULT_114       114
#define   IMULT_115       115
#define   IMULT_116       116
#define   IMULT_117       117
#define   IMULT_118       118
#define   IMULT_119       119
#define   IMULT_120       120
#define   IMULT_121       121
#define   IMULT_122       122
#define   IMULT_123       123
#define   IMULT_124       124
#define   IMULT_125       125
#define   IMULT_126       126
#define   IMULT_127       127

//*****************************************************************************
// The following are values that can be passed to the
// InitSysPll() to select SYSPLL fractional multiplier
//*****************************************************************************

#define   FMULT_0         0
#define   FMULT_0pt25     1
#define   FMULT_0pt5      2
#define   FMULT_0pt75     3

//*****************************************************************************
// The following are values that can be passed to the
// InitSysPll() to select divsel for SYSPLL
//*****************************************************************************

#define   PLLCLK_BY_1      0
#define   PLLCLK_BY_2      1
#define   PLLCLK_BY_4      2
#define   PLLCLK_BY_6      3
#define   PLLCLK_BY_8      4
#define   PLLCLK_BY_10     5
#define   PLLCLK_BY_12     6
#define   PLLCLK_BY_14     7
#define   PLLCLK_BY_16     8
#define   PLLCLK_BY_18     9
#define   PLLCLK_BY_20     10
#define   PLLCLK_BY_22     11
#define   PLLCLK_BY_24     12
#define   PLLCLK_BY_26     13
#define   PLLCLK_BY_28     14
#define   PLLCLK_BY_30     15
#define   PLLCLK_BY_32     16
#define   PLLCLK_BY_34     17
#define   PLLCLK_BY_36     18
#define   PLLCLK_BY_38     19
#define   PLLCLK_BY_40     20
#define   PLLCLK_BY_42     21
#define   PLLCLK_BY_44     22
#define   PLLCLK_BY_46     23
#define   PLLCLK_BY_48     24
#define   PLLCLK_BY_50     25
#define   PLLCLK_BY_52     26
#define   PLLCLK_BY_54     27
#define   PLLCLK_BY_56     28
#define   PLLCLK_BY_58     29
#define   PLLCLK_BY_60     30
#define   PLLCLK_BY_62     31
#define   PLLCLK_BY_64     32
#define   PLLCLK_BY_66     33
#define   PLLCLK_BY_68     34
#define   PLLCLK_BY_70     35
#define   PLLCLK_BY_72     36
#define   PLLCLK_BY_74     37
#define   PLLCLK_BY_76     38
#define   PLLCLK_BY_78     39
#define   PLLCLK_BY_80     40
#define   PLLCLK_BY_82     41
#define   PLLCLK_BY_84     42
#define   PLLCLK_BY_86     43
#define   PLLCLK_BY_88     44
#define   PLLCLK_BY_90     45
#define   PLLCLK_BY_92     46
#define   PLLCLK_BY_94     47
#define   PLLCLK_BY_96     48
#define   PLLCLK_BY_98     49
#define   PLLCLK_BY_100    50
#define   PLLCLK_BY_102    51
#define   PLLCLK_BY_104    52
#define   PLLCLK_BY_106    53
#define   PLLCLK_BY_108    54
#define   PLLCLK_BY_110    55
#define   PLLCLK_BY_112    56
#define   PLLCLK_BY_114    57
#define   PLLCLK_BY_116    58
#define   PLLCLK_BY_118    59
#define   PLLCLK_BY_120    60
#define   PLLCLK_BY_122    61
#define   PLLCLK_BY_124    62
#define   PLLCLK_BY_126    63

//*****************************************************************************
// The following are values that can be passed to the
// InitSysPll() to select clock source
//*****************************************************************************

#define   INT_OSC2       0  // Internal oscillator 2
#define   XTAL_OSC       1  // External oscillator, crystal mode
#define   INT_OSC1       2  // Internal oscillator 1
#define   XTAL_OSC_SE    5  // External oscillator, single-ended mode

/*-----------------------------------------------------------------------------
    Specify the clock rate of the CPU (SYSCLKOUT) in nS.

    Take into account the input clock frequency and the PLL multiplier
    selected in step 1.

    Use one of the values provided, or define your own.
    The trailing L is required tells the compiler to treat
    the number as a 64-bit value.

    Only one statement should be uncommented.

    Example:   200 MHz devices:
             CLKIN is a 20 MHz crystal or internal 10 MHz oscillator

             In step 1 the user specified the PLL multiplier = 10 for a
             200 MHz CPU clock (SYSCLKOUT = 200 MHz).

             In this case, the CPU_RATE will be 200000000.0L
             Uncomment the line: #define CPU_RATE 200000000.0L

-----------------------------------------------------------------------------*/
#define CPU_RATE          (200000000.0f)   // for a 200MHz CPU clock speed

//
// The following pointer to a function call calibrates the ADC reference,
// DAC offset, and internal oscillators
//
#define Device_cal ((void (*)(void))((uintptr_t)0x10002BFF)) 
//
// Include Example Header Files:
//

#include "g32r502_device.h"
#include "g32r502_globalprototypes.h"  //Prototypes for global functions
                                       //within the .c files.
#include "g32r502_adc_defines.h"
#include "g32r502_tmrvars.h"
#include "g32r502_pwm_defines.h"
#include "g32r502_gpio_defines.h"       // Macros used for GPIO support code
#include "g32r502_sysctrl_defines.h"    // Macros used for LPM support code
#include "g32r502_dma_defines.h"        // Macros used for DMA support code


extern void G32R5xx_usDelay(uint32_t count);
// DO NOT MODIFY THIS LINE.
// G32R502 has no DP FPU; delay count uses float32_t scaling (see DEVICE_DELAY_US).
#define DELAY_US(A) G32R5xx_usDelay((uint32_t)(((((float32_t)(A)) / (1000000.0f /  \
                              (float32_t)CPU_RATE)) - 9.0f) / 5.0f))

//
// Useful Timer Operations
//

//
// Start Timer:
//
#define StartTimer0()   Timer0Regs.TCR.bit.TSS = 0

//
// Stop Timer:
//
#define StopTimer0()   Timer0Regs.TCR.bit.TSS = 1

//
// Reload Timer With period Value:
//
#define ReloadTimer0() Timer0Regs.TCR.bit.TRB = 1

//
// Read 32-Bit Timer Value:
//
#define ReadTimer0Counter() Timer0Regs.TIM.all

//
// Read 32-Bit Period Value:
//
#define ReadTimer0Period() Timer0Regs.PRD.all

//
// Start Timer:
//
#define StartTimer1()   Timer1Regs.TCR.bit.TSS = 0
#define StartTimer2()   Timer2Regs.TCR.bit.TSS = 0

//
// Stop Timer:
//
#define StopTimer1()   Timer1Regs.TCR.bit.TSS = 1
#define StopTimer2()   Timer2Regs.TCR.bit.TSS = 1

//
// Reload Timer With period Value:
//
#define ReloadTimer1() Timer1Regs.TCR.bit.TRB = 1
#define ReloadTimer2() Timer2Regs.TCR.bit.TRB = 1

//
// Read 32-Bit Timer Value:
//
#define ReadTimer1Counter() Timer1Regs.TIM.all
#define ReadTimer2Counter() Timer2Regs.TIM.all

//
// Read 32-Bit Period Value:
//
#define ReadTimer1Period() Timer1Regs.PRD.all
#define ReadTimer2Period() Timer2Regs.PRD.all

//
// DMA address offsets (CPU pointer -> DMA programming view; >>1 in DMA API)
//
#define DMA_ITCM_ADDR_OFFSET        0xA0000000UL
#define DMA_DTCM_ADDR_OFFSET        0x80100000UL

#define DMA_ADDR_ITCM(cpuPtr)       ((uint32_t)(cpuPtr) + DMA_ITCM_ADDR_OFFSET)
#define DMA_ADDR_DTCM(cpuPtr)       ((uint32_t)(cpuPtr) + DMA_DTCM_ADDR_OFFSET)

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of G32R502_EXAMPLES_H definition

//
// End of file.
//
