//###########################################################################
//
// FILE:    g32r501_exti.h
//
// TITLE:   Definitions for theEXTI registers.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//###########################################################################
//
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
//###########################################################################

#ifndef G32R501_EXTI_H
#define G32R501_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
//  EXTI Individual Register Bit Definitions:

struct EXTI_RTEN_BITS {                  // bits description
    Uint32 RTEN0:1;                      // 0  Rising Trigger Event Enable and Interrupt of Line 0
    Uint32 RTEN1:1;                      // 1  Rising Trigger Event Enable and Interrupt of Line 1
    Uint32 RTEN2:1;                      // 2  Rising Trigger Event Enable and Interrupt of Line 2
    Uint32 RTEN3:1;                      // 3  Rising Trigger Event Enable and Interrupt of Line 3
    Uint32 RTEN4:1;                      // 4  Rising Trigger Event Enable and Interrupt of Line 4
    Uint32 RTEN5:1;                      // 5  Rising Trigger Event Enable and Interrupt of Line 5
    Uint32 RTEN6:1;                      // 6  Rising Trigger Event Enable and Interrupt of Line 6
    Uint32 RTEN7:1;                      // 7  Rising Trigger Event Enable and Interrupt of Line 7
    Uint32 RTEN8:1;                      // 8  Rising Trigger Event Enable and Interrupt of Line 8
    Uint32 RTEN9:1;                      // 9  Rising Trigger Event Enable and Interrupt of Line 9
    Uint32 RTEN10:1;                     // 10 Rising Trigger Event Enable and Interrupt of Line 10
    Uint32 RTEN11:1;                     // 11 Rising Trigger Event Enable and Interrupt of Line 11
    Uint32 RTEN12:1;                     // 12 Rising Trigger Event Enable and Interrupt of Line 12
    Uint32 RTEN13:1;                     // 13 Rising Trigger Event Enable and Interrupt of Line 13
    Uint32 RTEN14:1;                     // 14 Rising Trigger Event Enable and Interrupt of Line 14
    Uint32 RTEN15:1;                     // 15 Rising Trigger Event Enable and Interrupt of Line 15
    Uint32 rsvd:16;                      // 31:16 Reserved
};

union EXTI_RTEN_REG {
    Uint32  all;
    struct  EXTI_RTEN_BITS  bit;
};

struct EXTI_FTEN_BITS {                  // bits description
    Uint32 FTEN0:1;                      // 0 Falling Trigger Event Enable and Interrupt of Line 0
    Uint32 FTEN1:1;                      // 1 Falling Trigger Event Enable and Interrupt of Line 1
    Uint32 FTEN2:1;                      // 2 Falling Trigger Event Enable and Interrupt of Line 2
    Uint32 FTEN3:1;                      // 3 Falling Trigger Event Enable and Interrupt of Line 3
    Uint32 FTEN4:1;                      // 4 Falling Trigger Event Enable and Interrupt of Line 4
    Uint32 FTEN5:1;                      // 5 Falling Trigger Event Enable and Interrupt of Line 5
    Uint32 FTEN6:1;                      // 6 Falling Trigger Event Enable and Interrupt of Line 6
    Uint32 FTEN7:1;                      // 7 Falling Trigger Event Enable and Interrupt of Line 7
    Uint32 FTEN8:1;                      // 8 Falling Trigger Event Enable and Interrupt of Line 8
    Uint32 FTEN9:1;                      // 9 Falling Trigger Event Enable and Interrupt of Line 9
    Uint32 FTEN10:1;                     // 10 Falling Trigger Event Enable and Interrupt of Line 10
    Uint32 FTEN11:1;                     // 11 Falling Trigger Event Enable and Interrupt of Line 11
    Uint32 FTEN12:1;                     // 12 Falling Trigger Event Enable and Interrupt of Line 12
    Uint32 FTEN13:1;                     // 13 Falling Trigger Event Enable and Interrupt of Line 13
    Uint32 FTEN14:1;                     // 14 Falling Trigger Event Enable and Interrupt of Line 14
    Uint32 FTEN15:1;                     // 15 Falling Trigger Event Enable and Interrupt of Line 15
    Uint32 rsvd:16;                      // 31:16 Reserved
};

union EXTI_FTEN_REG {
    Uint32  all;
    struct  EXTI_FTEN_BITS  bit;
};

struct EXTI_SWINTE_BITS {                  // bits description
    Uint32 SWINTE0:1;                      // 0 Software Interrupt Event on Line 0
    Uint32 SWINTE1:1;                      // 1 Software Interrupt Event on Line 1
    Uint32 SWINTE2:1;                      // 2 Software Interrupt Event on Line 2
    Uint32 SWINTE3:1;                      // 3 Software Interrupt Event on Line 3
    Uint32 SWINTE4:1;                      // 4 Software Interrupt Event on Line 4
    Uint32 SWINTE5:1;                      // 5 Software Interrupt Event on Line 5
    Uint32 SWINTE6:1;                      // 6 Software Interrupt Event on Line 6
    Uint32 SWINTE7:1;                      // 7 Software Interrupt Event on Line 7
    Uint32 SWINTE8:1;                      // 8 Software Interrupt Event on Line 8
    Uint32 SWINTE9:1;                      // 9 Software Interrupt Event on Line 9
    Uint32 SWINTE10:1;                     // 10 Software Interrupt Event on Line 10
    Uint32 SWINTE11:1;                     // 11 Software Interrupt Event on Line 11
    Uint32 SWINTE12:1;                     // 12 Software Interrupt Event on Line 12
    Uint32 SWINTE13:1;                     // 13 Software Interrupt Event on Line 13
    Uint32 SWINTE14:1;                     // 14 Software Interrupt Event on Line 14
    Uint32 SWINTE15:1;                     // 15 Software Interrupt Event on Line 15
    Uint32 rsvd:16;                        // 31:16 Reserved
};

union EXTI_SWINTE_REG {
    Uint32  all;
    struct  EXTI_SWINTE_BITS  bit;
};

struct EXTI_GPIOSEL_BITS {                // bits description
    Uint32 GPIOSEL0:4;                    // 3:0   GPIO0-GPIO14 Trigger Select
    Uint32 GPIOSEL1:4;                    // 7:4   GPIO15-GPIO29 Trigger Select
    Uint32 GPIOSEL2:4;                    // 11:8  GPIO30-GPIO44 Trigger Select
    Uint32 GPIOSEL3:4;                    // 15:12  GPIO45-GPIO59 Trigger Select
    Uint32 rsvd:16;                       // 31:16 Reserved
};

union EXTI_GPIOSEL_REG {
    Uint32  all;
    struct  EXTI_GPIOSEL_BITS  bit;
};

struct EXTI_IMASK0_BITS {           // bits description
    Uint32 IMASK0:1;                    // 0 Interrupt Request Mask on Line 0 of CPU0
    Uint32 IMASK1:1;                    // 1 Interrupt Request Mask on Line 1 of CPU0
    Uint32 IMASK2:1;                    // 2 Interrupt Request Mask on Line 2 of CPU0
    Uint32 IMASK3:1;                    // 3 Interrupt Request Mask on Line 3 of CPU0
    Uint32 IMASK4:1;                    // 4 Interrupt Request Mask on Line 4 of CPU0
    Uint32 IMASK5:1;                    // 5 Interrupt Request Mask on Line 5 of CPU0
    Uint32 IMASK6:1;                    // 6 Interrupt Request Mask on Line 6 of CPU0
    Uint32 IMASK7:1;                    // 7 Interrupt Request Mask on Line 7 of CPU0
    Uint32 IMASK8:1;                    // 8 Interrupt Request Mask on Line 8 of CPU0
    Uint32 IMASK9:1;                    // 9 Interrupt Request Mask on Line 9 of CPU0
    Uint32 IMASK10:1;                   // 10 Interrupt Request Mask on Line 10 of CPU0
    Uint32 IMASK11:1;                   // 11 Interrupt Request Mask on Line 11 of CPU0
    Uint32 IMASK12:1;                   // 12 Interrupt Request Mask on Line 12 of CPU0
    Uint32 IMASK13:1;                   // 13 Interrupt Request Mask on Line 13 of CPU0
    Uint32 IMASK14:1;                   // 14 Interrupt Request Mask on Line 14 of CPU0
    Uint32 IMASK15:1;                   // 15 Interrupt Request Mask on Line 15 of CPU0
    Uint32 rsvd:16;                     // 31:16 Reserved
};

union EXTI_IMASK0_REG {
    Uint32  all;
    struct  EXTI_IMASK0_BITS  bit;
};

struct EXTI_EMASK0_BITS {          // bits description
    Uint32 EMASK0:1;                   // 0 Event Request Mask on Line 0 of CPU0
    Uint32 EMASK1:1;                   // 1 Event Request Mask on Line 1 of CPU0
    Uint32 EMASK2:1;                   // 2 Event Request Mask on Line 2 of CPU0
    Uint32 EMASK3:1;                   // 3 Event Request Mask on Line 3 of CPU0
    Uint32 EMASK4:1;                   // 4 Event Request Mask on Line 4 of CPU0
    Uint32 EMASK5:1;                   // 5 Event Request Mask on Line 5 of CPU0
    Uint32 EMASK6:1;                   // 6 Event Request Mask on Line 6 of CPU0
    Uint32 EMASK7:1;                   // 7 Event Request Mask on Line 7 of CPU0
    Uint32 EMASK8:1;                   // 8 Event Request Mask on Line 8 of CPU0
    Uint32 EMASK9:1;                   // 9 Event Request Mask on Line 9 of CPU0
    Uint32 EMASK10:1;                  // 10 Event Request Mask on Line 10 of CPU0
    Uint32 EMASK11:1;                  // 11 Event Request Mask on Line 11 of CPU0
    Uint32 EMASK12:1;                  // 12 Event Request Mask on Line 12 of CPU0
    Uint32 EMASK13:1;                  // 13 Event Request Mask on Line 13 of CPU0
    Uint32 EMASK14:1;                  // 14 Event Request Mask on Line 14 of CPU0
    Uint32 EMASK15:1;                  // 15 Event Request Mask on Line 15 of CPU0
    Uint32 rsvd:16;                    // 31:16 Reserved
};

union EXTI_EMASK0_REG {
    Uint32  all;
    struct  EXTI_EMASK0_BITS  bit;
};

struct EXTI_IPEND0_BITS {          // bits description (write 1 to clear, W1C)
    Uint32 IPEND0:1;                   // 0 Interrupt Pending Flag of Line 0 of CPU0
    Uint32 IPEND1:1;                   // 1 Interrupt Pending Flag of Line 1 of CPU0
    Uint32 IPEND2:1;                   // 2 Interrupt Pending Flag of Line 2 of CPU0
    Uint32 IPEND3:1;                   // 3 Interrupt Pending Flag of Line 3 of CPU0
    Uint32 IPEND4:1;                   // 4 Interrupt Pending Flag of Line 4 of CPU0
    Uint32 IPEND5:1;                   // 5 Interrupt Pending Flag of Line 5 of CPU0
    Uint32 IPEND6:1;                   // 6 Interrupt Pending Flag of Line 6 of CPU0
    Uint32 IPEND7:1;                   // 7 Interrupt Pending Flag of Line 7 of CPU0
    Uint32 IPEND8:1;                   // 8 Interrupt Pending Flag of Line 8 of CPU0
    Uint32 IPEND9:1;                   // 9 Interrupt Pending Flag of Line 9 of CPU0
    Uint32 IPEND10:1;                  // 10 Interrupt Pending Flag of Line 10 of CPU0
    Uint32 IPEND11:1;                  // 11 Interrupt Pending Flag of Line 11 of CPU0
    Uint32 IPEND12:1;                  // 12 Interrupt Pending Flag of Line 12 of CPU0
    Uint32 IPEND13:1;                  // 13 Interrupt Pending Flag of Line 13 of CPU0
    Uint32 IPEND14:1;                  // 14 Interrupt Pending Flag of Line 14 of CPU0
    Uint32 IPEND15:1;                  // 15 Interrupt Pending Flag of Line 15 of CPU0
    Uint32 rsvd:16;                    // 31:16 Reserved
};

union EXTI_IPEND0_REG {
    Uint32  all;
    struct  EXTI_IPEND0_BITS  bit;
};

struct EXTI_IMASK1_BITS {          // bits description
    Uint32 IMASK0:1;                   // 0 Interrupt Request Mask on Line 0 of CPU1
    Uint32 IMASK1:1;                   // 1 Interrupt Request Mask on Line 1 of CPU1
    Uint32 IMASK2:1;                   // 2 Interrupt Request Mask on Line 2 of CPU1
    Uint32 IMASK3:1;                   // 3 Interrupt Request Mask on Line 3 of CPU1
    Uint32 IMASK4:1;                   // 4 Interrupt Request Mask on Line 4 of CPU1
    Uint32 IMASK5:1;                   // 5 Interrupt Request Mask on Line 5 of CPU1
    Uint32 IMASK6:1;                   // 6 Interrupt Request Mask on Line 6 of CPU1
    Uint32 IMASK7:1;                   // 7 Interrupt Request Mask on Line 7 of CPU1
    Uint32 IMASK8:1;                   // 8 Interrupt Request Mask on Line 8 of CPU1
    Uint32 IMASK9:1;                   // 9 Interrupt Request Mask on Line 9 of CPU1
    Uint32 IMASK10:1;                  // 10 Interrupt Request Mask on Line 10 of CPU1
    Uint32 IMASK11:1;                  // 11 Interrupt Request Mask on Line 11 of CPU1
    Uint32 IMASK12:1;                  // 12 Interrupt Request Mask on Line 12 of CPU1
    Uint32 IMASK13:1;                  // 13 Interrupt Request Mask on Line 13 of CPU1
    Uint32 IMASK14:1;                  // 14 Interrupt Request Mask on Line 14 of CPU1
    Uint32 IMASK15:1;                  // 15 Interrupt Request Mask on Line 15 of CPU1
    Uint32 rsvd:16;                    // 31:16 Reserved
};

union EXTI_IMASK1_REG {
    Uint32  all;
    struct  EXTI_IMASK1_BITS  bit;
};

struct EXTI_EMASK1_BITS {           // bits description
    Uint32 EMASK0:1;                    // 0 Event Request Mask on Line 0 of CPU1
    Uint32 EMASK1:1;                    // 1 Event Request Mask on Line 1 of CPU1
    Uint32 EMASK2:1;                    // 2 Event Request Mask on Line 2 of CPU1
    Uint32 EMASK3:1;                    // 3 Event Request Mask on Line 3 of CPU1
    Uint32 EMASK4:1;                    // 4 Event Request Mask on Line 4 of CPU1
    Uint32 EMASK5:1;                    // 5 Event Request Mask on Line 5 of CPU1
    Uint32 EMASK6:1;                    // 6 Event Request Mask on Line 6 of CPU1
    Uint32 EMASK7:1;                    // 7 Event Request Mask on Line 7 of CPU1
    Uint32 EMASK8:1;                    // 8 Event Request Mask on Line 8 of CPU1
    Uint32 EMASK9:1;                    // 9 Event Request Mask on Line 9 of CPU1
    Uint32 EMASK10:1;                   // 10 Event Request Mask on Line 10 of CPU1
    Uint32 EMASK11:1;                   // 11 Event Request Mask on Line 11 of CPU1
    Uint32 EMASK12:1;                   // 12 Event Request Mask on Line 12 of CPU1
    Uint32 EMASK13:1;                   // 13 Event Request Mask on Line 13 of CPU1
    Uint32 EMASK14:1;                   // 14 Event Request Mask on Line 14 of CPU1
    Uint32 EMASK15:1;                   // 15 Event Request Mask on Line 15 of CPU1
    Uint32 rsvd:16;                     // 31:16 Reserved
};

union EXTI_EMASK1_REG {
    Uint32  all;
    struct  EXTI_EMASK1_BITS  bit;
};

struct EXTI_IPEND1_BITS {                // bits description (write 1 to clear, W1C)
    Uint32 IPEND0:1;                     // 0 Interrupt Pending Flag of Line 0 of CPU1
    Uint32 IPEND1:1;                     // 1 Interrupt Pending Flag of Line 1 of CPU1
    Uint32 IPEND2:1;                     // 2 Interrupt Pending Flag of Line 2 of CPU1
    Uint32 IPEND3:1;                     // 3 Interrupt Pending Flag of Line 3 of CPU1
    Uint32 IPEND4:1;                     // 4 Interrupt Pending Flag of Line 4 of CPU1
    Uint32 IPEND5:1;                     // 5 Interrupt Pending Flag of Line 5 of CPU1
    Uint32 IPEND6:1;                     // 6 Interrupt Pending Flag of Line 6 of CPU1
    Uint32 IPEND7:1;                     // 7 Interrupt Pending Flag of Line 7 of CPU1
    Uint32 IPEND8:1;                     // 8 Interrupt Pending Flag of Line 8 of CPU1
    Uint32 IPEND9:1;                     // 9 Interrupt Pending Flag of Line 9 of CPU1
    Uint32 IPEND10:1;                    // 10 Interrupt Pending Flag of Line 10 of CPU1
    Uint32 IPEND11:1;                    // 11 Interrupt Pending Flag of Line 11 of CPU1
    Uint32 IPEND12:1;                    // 12 Interrupt Pending Flag of Line 12 of CPU1
    Uint32 IPEND13:1;                    // 13 Interrupt Pending Flag of Line 13 of CPU1
    Uint32 IPEND14:1;                    // 14 Interrupt Pending Flag of Line 14 of CPU1
    Uint32 IPEND15:1;                    // 15 Interrupt Pending Flag of Line 15 of CPU1
    Uint32 rsvd:16;                      // 31:16 Reserved
};

union EXTI_IPEND1_REG {
    Uint32  all;
    struct  EXTI_IPEND1_BITS  bit;
};

struct EXTI_INT4CNT_BITS {           // bits description
    Uint32 INT4CNT:16;               //15: 0 Interrupt Line 4 Counter
    Uint32 rsvd:16;                  // 31:16 Reserved
};

union  EXTI_INT4CNT_REG {
    Uint32  all;
    struct  EXTI_INT4CNT_BITS  bit;
};

struct EXTI_INT5CNT_BITS {           // bits description
    Uint32 INT5CNT:16;               //15: 0 Interrupt Line 5 Counter
    Uint32 rsvd:16;                  // 31:16 Reserved
};

union  EXTI_INT5CNT_REG {
    Uint32  all;
    struct  EXTI_INT5CNT_BITS  bit;
};

struct EXTI_INT6CNT_BITS {           // bits description
    Uint32 INT6CNT:16;               //15: 0 Interrupt Line6 Counter
    Uint32 rsvd:16;                  // 31:16 Reserved
};

union  EXTI_INT6CNT_REG {
    Uint32  all;
    struct  EXTI_INT6CNT_BITS  bit;
};


struct EXTI_REGS {
    union   EXTI_RTEN_REG                    EXTI_RTEN;
    union   EXTI_FTEN_REG                    EXTI_FTEN;
    union   EXTI_SWINTE_REG                  EXTI_SWINTE;
    union   EXTI_GPIOSEL_REG                 EXTI_GPIOSEL;
    union   EXTI_IMASK0_REG                  EXTI_IMASK0;
    union   EXTI_EMASK0_REG                  EXTI_EMASK0;
    union   EXTI_IPEND0_REG                  EXTI_IPEND0;
    Uint32                                   rsvd1;
    union   EXTI_IMASK1_REG                  EXTI_IMASK1;
    union   EXTI_EMASK1_REG                  EXTI_EMASK1;
    union   EXTI_IPEND1_REG                  EXTI_IPEND1;
    Uint32                                   rsvd2;
    union   EXTI_INT4CNT_REG                 EXTI_INT4CNT;
    union   EXTI_INT5CNT_REG                 EXTI_INT5CNT;
    union   EXTI_INT6CNT_REG                 EXTI_INT6CNT;
};

//---------------------------------------------------------------------------
// EXTI External References & Function Declarations:
//
extern volatile struct EXTI_REGS ExtiRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
