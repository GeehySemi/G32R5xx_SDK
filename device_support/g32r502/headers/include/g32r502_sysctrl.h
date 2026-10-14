//###########################################################################
//
// FILE:    g32r502_sysctrl.h
//
// TITLE:   Definitions for the SYSCTRL registers.
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
// 1. Update register naming and access rules.
//
//###########################################################################
#ifndef G32R502_SYSCTRL_H
#define G32R502_SYSCTRL_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// SYSCTRL Individual Register Bit Definitions:

struct PARTIDL_BITS {                   // bits description
    Uint32 rsvd1:3;                     // 2:0 Reserved
    Uint32 rsvd2:2;                     // 4:3 Reserved
    Uint32 rsvd3:1;                     // 5 Reserved
    Uint32 QUAL:2;                      // 7:6 Qualification Status
    Uint32 PIN_COUNT:3;                 // 10:8 Device Pin Count
    Uint32 rsvd4:1;                     // 11 Reserved
    Uint32 rsvd5:1;                     // 12 Reserved
    Uint32 INSTASPIN:2;                 // 14:13 Instaspin feature set
    Uint32 rsvd6:1;                     // 15 Reserved
    Uint32 FLASH_SIZE:8;                // 23:16 Flash size in KB
    Uint32 rsvd7:4;                     // 27:24 Reserved
    Uint32 rsvd8:4;                     // 31:28 Reserved
};

union PARTIDL_REG {
    Uint32  all;
    struct  PARTIDL_BITS  bit;
};

struct PARTIDH_BITS {                   // bits description
    Uint32 rsvd1:4;                     // 3:0 Reserved
    Uint32 rsvd2:4;                     // 7:4 Reserved
    Uint32 FAMILY:8;                    // 15:8 Device family
    Uint32 PARTNO:8;                    // 23:16 Device part number
    Uint32 DEVICE_CLASS_ID:8;           // 31:24 Device class ID
};

union PARTIDH_REG {
    Uint32  all;
    struct  PARTIDH_BITS  bit;
};

struct REVID_BITS {                     // bits description
    Uint32 REVID:16;                    // 15:0 Device Revision ID. This is specific to the Device
    Uint32 rsvd1:16;                    // 31:16 Reserved
};

union REVID_REG {
    Uint32  all;
    struct  REVID_BITS  bit;
};

struct DC3_BITS {                       // bits description
    Uint32 PWM1:1;                      // 0 PWM1 function
    Uint32 PWM2:1;                      // 1 PWM2 function
    Uint32 PWM3:1;                      // 2 PWM3 function
    Uint32 PWM4:1;                      // 3 PWM4 function
    Uint32 PWM5:1;                      // 4 PWM5 function
    Uint32 PWM6:1;                      // 5 PWM6 function
    Uint32 PWM7:1;                      // 6 PWM7 function
    Uint32 rsvd1:25;                    // 31:7 Reserved
};

union DC3_REG {
    Uint32  all;
    struct  DC3_BITS  bit;
};

struct DC4_BITS {                       // bits description
    Uint32 CAP1:1;                      // 0 CAP1 function
    Uint32 CAP2:1;                      // 1 CAP2 function
    Uint32 CAP3:1;                      // 2 CAP3 function
    Uint32 rsvd1:29;                    // 31:3 Reserved
};

union DC4_REG {
    Uint32  all;
    struct  DC4_BITS  bit;
};

struct DC5_BITS {                       // bits description
    Uint32 QEP1:1;                      // 0 QEP1 function
    Uint32 rsvd1:31;                    // 31:1 Reserved
};

union DC5_REG {
    Uint32  all;
    struct  DC5_BITS  bit;
};

struct DC8_BITS {                       // bits description
    Uint32 UART_A:1;                    // 0 UARTA function
    Uint32 UART_B:1;                    // 1 UARTB function
    Uint32 UART_C:1;                    // 2 UARTC function
    Uint32 rsvd1:29;                    // 31:3 Reserved
};

union DC8_REG {
    Uint32  all;
    struct  DC8_BITS  bit;
};

struct DC9_BITS {                       // bits description
    Uint32 SPI_A:1;                     // 0 SPIA function
    Uint32 rsvd1:31;                    // 31:1 Reserved
};

union DC9_REG {
    Uint32  all;
    struct  DC9_BITS  bit;
};

struct DC10_BITS {                      // bits description
    Uint32 I2C_A:1;                     // 0 I2CA function
    Uint32 I2C_B:1;                     // 1 I2CB function
    Uint32 rsvd1:30;                    // 31:2 Reserved
};

union DC10_REG {
    Uint32  all;
    struct  DC10_BITS  bit;
};

struct DC11_BITS {                      // bits description
    Uint32 CAN_A:1;                     // 0 CANA function
    Uint32 rsvd1:3;                     // 3:1 Reserved
    Uint32 CANFD_A:1;                   // 4 CANFDA function
    Uint32 rsvd2:27;                    // 31:5 Reserved
};

union DC11_REG {
    Uint32  all;
    struct  DC11_BITS  bit;
};

struct DC14_BITS {                      // bits description
    Uint32 ADC_A:1;                     // 0 ADCA function
    Uint32 rsvd1:1;                     // 1 Reserved
    Uint32 ADC_C:1;                     // 2 ADCC function
    Uint32 rsvd2:29;                    // 31:3 Reserved
};

union DC14_REG {
    Uint32  all;
    struct  DC14_BITS  bit;
};

struct DC15_BITS {                      // bits description
    Uint32 COMP1:1;                     // 0 COMP1 function
    Uint32 COMP2:1;                     // 1 COMP2 function
    Uint32 COMP3:1;                     // 2 COMP3 function
    Uint32 COMP4:1;                     // 3 COMP4 function
    Uint32 rsvd1:28;                    // 31:4 Reserved
};

union DC15_REG {
    Uint32  all;
    struct  DC15_BITS  bit;
};

struct DC17_BITS {                      // bits description
    Uint32 rsvd1:16;                    // 15:0 Reserved
    Uint32 DAC_A:1;                     // 16 DACA function
    Uint32 DAC_B:1;                     // 17 DACB function
    Uint32 rsvd2:14;                    // 31:18 Reserved
};

union DC17_REG {
    Uint32  all;
    struct  DC17_BITS  bit;
};

struct DC21_BITS {                      // bits description
    Uint32 FLB1:1;                      // 0 FLB1 function
    Uint32 FLB2:1;                      // 1 FLB2 function
    Uint32 FLB3:1;                      // 2 FLB3 function
    Uint32 FLB4:1;                      // 3 FLB4 function
    Uint32 rsvd1:28;                    // 31:4 Reserved
};

union DC21_REG {
    Uint32  all;
    struct  DC21_BITS  bit;
};

struct DC23_BITS {                      // bits description
    Uint32 LIN_A:1;                     // 0 LINA function
    Uint32 rsvd1:31;                    // 31:1 Reserved
};

union DC23_REG {
    Uint32  all;
    struct  DC23_BITS  bit;
};

struct DC24_BITS {                      // bits description
    Uint32 PMBUS_A:1;                   // 0 PMBUSA function
    Uint32 rsvd1:31;                    // 31:1 Reserved
};

union DC24_REG {
    Uint32  all;
    struct  DC24_BITS  bit;
};

struct DC25_BITS {                      // bits description
    Uint32 DCC_0:1;                     // 0 DCC function
    Uint32 rsvd1:31;                    // 31:1 Reserved
};

union DC25_REG {
    Uint32  all;
    struct  DC25_BITS  bit;
};

struct SOFTPRES2_BITS {                 // bits description
    Uint32 PWM1:1;                      // 0 PWM1 software reset bit
    Uint32 PWM2:1;                      // 1 PWM2 software reset bit
    Uint32 PWM3:1;                      // 2 PWM3 software reset bit
    Uint32 PWM4:1;                      // 3 PWM4 software reset bit
    Uint32 PWM5:1;                      // 4 PWM5 software reset bit
    Uint32 PWM6:1;                      // 5 PWM6 software reset bit
    Uint32 PWM7:1;                      // 6 PWM7 software reset bit
    Uint32 rsvd1:25;                    // 31:7 Reserved
};

union SOFTPRES2_REG {
    Uint32  all;
    struct  SOFTPRES2_BITS  bit;
};

struct SOFTPRES3_BITS {                 // bits description
    Uint32 CAP1:1;                      // 0 CAP1 software reset bit
    Uint32 CAP2:1;                      // 1 CAP2 software reset bit
    Uint32 CAP3:1;                      // 2 CAP3 software reset bit
    Uint32 rsvd1:29;                    // 31:3 Reserved
};

union SOFTPRES3_REG {
    Uint32  all;
    struct  SOFTPRES3_BITS  bit;
};

struct SOFTPRES4_BITS {                 // bits description
    Uint32 QEP1:1;                      // 0 QEP1 software reset bit
    Uint32 rsvd1:31;                    // 31:1 Reserved
};

union SOFTPRES4_REG {
    Uint32  all;
    struct  SOFTPRES4_BITS  bit;
};

struct SOFTPRES7_BITS {                 // bits description
    Uint32 UART_A:1;                    // 0 UART_A software reset bit
    Uint32 UART_B:1;                    // 1 UART_B software reset bit
    Uint32 UART_C:1;                    // 2 UART_C software reset bit
    Uint32 rsvd1:29;                    // 31:3 Reserved
};

union SOFTPRES7_REG {
    Uint32  all;
    struct  SOFTPRES7_BITS  bit;
};

struct SOFTPRES8_BITS {                 // bits description
    Uint32 SPI_A:1;                     // 0 SPI_A software reset bit
    Uint32 rsvd1:31;                    // 31:1 Reserved
};

union SOFTPRES8_REG {
    Uint32  all;
    struct  SOFTPRES8_BITS  bit;
};

struct SOFTPRES9_BITS {                 // bits description
    Uint32 I2C_A:1;                     // 0 I2C_A software reset bit
    Uint32 I2C_B:1;                     // 1 I2C_B software reset bit
    Uint32 rsvd1:30;                    // 31:2 Reserved
};

union SOFTPRES9_REG {
    Uint32  all;
    struct  SOFTPRES9_BITS  bit;
};

struct SOFTPRES10_BITS {                // bits description
    Uint32 CAN_A:1;                     // 0 CAN_A software reset bit
    Uint32 rsvd1:3;                     // 3:1 Reserved
    Uint32 CANFD_A:1;                   // 4 CANFDA software reset bit
    Uint32 rsvd2:27;                    // 31:5 Reserved
};

union SOFTPRES10_REG {
    Uint32  all;
    struct  SOFTPRES10_BITS  bit;
};

struct SOFTPRES13_BITS {                // bits description
    Uint32 ADC_A:1;                     // 0 ADC_A software reset bit
    Uint32 rsvd1:1;                     // 1 Reserved
    Uint32 ADC_C:1;                     // 2 ADC_C software reset bit
    Uint32 rsvd2:29;                    // 31:3 Reserved
};

union SOFTPRES13_REG {
    Uint32  all;
    struct  SOFTPRES13_BITS  bit;
};

struct SOFTPRES14_BITS {                // bits description
    Uint32 COMP1:1;                     // 0 COMP1 software reset bit
    Uint32 COMP2:1;                     // 1 COMP2 software reset bit
    Uint32 COMP3:1;                     // 2 COMP3 software reset bit
    Uint32 COMP4:1;                     // 3 COMP4 software reset bit
    Uint32 rsvd1:28;                    // 31:4 Reserved
};

union SOFTPRES14_REG {
    Uint32  all;
    struct  SOFTPRES14_BITS  bit;
};

struct SOFTPRES16_BITS {                // bits description
    Uint32 rsvd1:16;                    // 15:0 Reserved
    Uint32 DAC_A:1;                     // 16 Buffered_DAC_A software reset bit
    Uint32 DAC_B:1;                     // 17 Buffered_DAC_B software reset bit
    Uint32 rsvd2:14;                    // 31:18 Reserved
};

union SOFTPRES16_REG {
    Uint32  all;
    struct  SOFTPRES16_BITS  bit;
};

struct SOFTPRES17_BITS {                // bits description
    Uint32 FLB1:1;                      // 0 FLB1 software reset bit
    Uint32 FLB2:1;                      // 1 FLB2 software reset bit
    Uint32 FLB3:1;                      // 2 FLB3 software reset bit
    Uint32 FLB4:1;                      // 3 FLB4 software reset bit
    Uint32 rsvd1:28;                    // 31:4 Reserved
};

union SOFTPRES17_REG {
    Uint32  all;
    struct  SOFTPRES17_BITS  bit;
};

struct SOFTPRES19_BITS {                // bits description
    Uint32 LIN_A:1;                     // 0 LIN_A software reset bit
    Uint32 rsvd1:31;                    // 31:1 Reserved
};

union SOFTPRES19_REG {
    Uint32  all;
    struct  SOFTPRES19_BITS  bit;
};

struct SOFTPRES20_BITS {                // bits description
    Uint32 PMBUS_A:1;                   // 0 PMBUS_A software reset bit
    Uint32 rsvd1:31;                    // 31:1 Reserved
};

union SOFTPRES20_REG {
    Uint32  all;
    struct  SOFTPRES20_BITS  bit;
};

struct PACKSEL_BITS {                   // bits description
    Uint32 PACKSEL:4;                   // 3:0 Chip Package Select
    Uint32 rsvd1:28;                    // 31:4 Reserved
};

union PACKSEL_REG {
    Uint32  all;
    struct  PACKSEL_BITS  bit;
};

struct DEV_REGS {
    Uint16                                rsvd1[8];                  // Reserved
    union   PARTIDL_REG                   PARTIDL;                   // Lower 32-bit of Device PART Identification Number
    union   PARTIDH_REG                   PARTIDH;                   // Upper 32-bit of Device PART Identification Number
    union   REVID_REG                     REVID;                     // Device Revision Number
    Uint16                                rsvd2[8];                  // Reserved
    union   DC3_REG                       DC3;                       // Device Capability Register
    union   DC4_REG                       DC4;                       // Device Capability Register
    union   DC5_REG                       DC5;                       // Device Capability Register
    Uint16                                rsvd3[4];                  // Reserved
    union   DC8_REG                       DC8;                       // Device Capability Register
    union   DC9_REG                       DC9;                       // Device Capability Register
    union   DC10_REG                      DC10;                      // Device Capability Register
    union   DC11_REG                      DC11;                      // Device Capability Register
    Uint16                                rsvd4[4];                  // Reserved
    union   DC14_REG                      DC14;                      // Device Capability Register
    union   DC15_REG                      DC15;                      // Device Capability Register
    Uint16                                rsvd5[2] ;                 // Reserved
    union   DC17_REG                      DC17;                      // Device Capability Register
    Uint16                                rsvd6[6];                  // Reserved
    union   DC21_REG                      DC21;                      // Device Capability Register
    Uint16                                rsvd7[2];                  // Reserved
    union   DC23_REG                      DC23;                      // Device Capability Register
    union   DC24_REG                      DC24;                      // Device Capability Register
    union   DC25_REG                      DC25;                      // Device Capability Register
    Uint16                                rsvd8[66];                 // Reserved
    union   SOFTPRES2_REG                 SOFTPRES2;                 // Peripheral Software Reset register
    union   SOFTPRES3_REG                 SOFTPRES3;                 // Peripheral Software Reset register
    union   SOFTPRES4_REG                 SOFTPRES4;                 // Peripheral Software Reset register
    Uint16                                rsvd9[4];                  // Reserved
    union   SOFTPRES7_REG                 SOFTPRES7;                 // Peripheral Software Reset register
    union   SOFTPRES8_REG                 SOFTPRES8;                 // Peripheral Software Reset register
    union   SOFTPRES9_REG                 SOFTPRES9;                 // Peripheral Software Reset register
    union   SOFTPRES10_REG                SOFTPRES10;                // Peripheral Software Reset register
    Uint16                                rsvd10[4];                 // Reserved
    union   SOFTPRES13_REG                SOFTPRES13;                // Peripheral Software Reset register
    union   SOFTPRES14_REG                SOFTPRES14;                // Peripheral Software Reset register
    Uint16                                rsvd11[2];                 // Reserved
    union   SOFTPRES16_REG                SOFTPRES16;                // Peripheral Software Reset register
    union   SOFTPRES17_REG                SOFTPRES17;                // Peripheral Software Reset register
    Uint16                                rsvd12[2];                 // Reserved
    union   SOFTPRES19_REG                SOFTPRES19;                // Peripheral Software Reset register
    union   SOFTPRES20_REG                SOFTPRES20;                // Peripheral Software Reset register
    Uint16                                rsvd13[38];                // Reserved
    Uint16                                rsvd14[92];                // Reserved
    union   PACKSEL_REG                   PACKSEL;                   // Chip Package Select
};

struct CLKCFGLOCK1_BITS {               // bits description
    Uint32 CLKSRCCTL1:1;                // 0 Lock bit for CLKSRCCTL1 register
    Uint32 CLKSRCCTL2:1;                // 1 Lock bit for CLKSRCCTL2 register
    Uint32 CLKSRCCTL3:1;                // 2 Lock bit for CLKSRCCTL3 register
    Uint32 SYSPLLCTL1:1;                // 3 Lock bit for SYSPLLCTL1 register
    Uint32 rsvd1:1;                     // 4 Reserved
    Uint32 rsvd2:1;                     // 5 Reserved
    Uint32 SYSPLLMULT:1;                // 6 Lock bit for SYSPLLMULT register
    Uint32 rsvd3:1;                     // 7 Reserved
    Uint32 rsvd4:1;                     // 8 Reserved
    Uint32 rsvd5:1;                     // 9 Reserved
    Uint32 rsvd6:1;                     // 10 Reserved
    Uint32 SYSCLKDIVSEL:1;              // 11 Lock bit for SYSCLKDIVSEL register
    Uint32 rsvd7:1;                     // 12 Reserved
    Uint32 rsvd8:1;                     // 13 Reserved
    Uint32 rsvd9:1;                     // 14 Reserved
    Uint32 LOSPCP:1;                    // 15 Lock bit for LOSPCP register
    Uint32 XTALCR:1;                    // 16 Lock bit for XTALCR register
    Uint32 rsvd10:15;                   // 31:17 Reserved
};

union CLKCFGLOCK1_REG {
    Uint32  all;
    struct  CLKCFGLOCK1_BITS  bit;
};

struct CLKSRCCTL1_BITS {                // bits description
    Uint32 OSCCLKSRCSEL:2;              // 1:0 OSCCLK Source Select Bit
    Uint32 rsvd1:1;                     // 2 Reserved
    Uint32 INTOSC2OFF:1;                // 3 Internal Oscillator 2 Off Bit
    Uint32 rsvd2:1;                     // 4 Reserved
    Uint32 WDHALTI:1;                   // 5 Watchdog HALT Mode Ignore Bit
    Uint32 rsvd3:10;                    // 15:6 Reserved
    Uint32 rsvd4:16;                    // 31:16 Reserved
};

union CLKSRCCTL1_REG {
    Uint32  all;
    struct  CLKSRCCTL1_BITS  bit;
};

struct CLKSRCCTL2_BITS {                // bits description
    Uint32 rsvd1:2;                     // 1:0 Reserved
    Uint32 CANABCLKSEL:2;               // 3:2 CANA Bit Clock Source Select Bit
    Uint32 CANFDABCLKSEL:2;              // 5:4 CANFDA Bit Clock Source Select Bit
    Uint32 rsvd2:2;                     // 7:6 Reserved
    Uint32 rsvd3:2;                     // 9:8 Reserved
    Uint32 rsvd4:6;                     // 15:10 Reserved
    Uint32 rsvd5:16;                    // 31:16 Reserved
};

union CLKSRCCTL2_REG {
    Uint32  all;
    struct  CLKSRCCTL2_BITS  bit;
};

struct CLKSRCCTL3_BITS {                // bits description
    Uint32 XCLKOUTSEL:3;                // 2:0 XCLKOUT Source Select Bit
    Uint32 rsvd1:13;                    // 15:3 Reserved
    Uint32 rsvd2:16;                    // 31:16 Reserved
};

union CLKSRCCTL3_REG {
    Uint32  all;
    struct  CLKSRCCTL3_BITS  bit;
};

struct SYSPLLCTL1_BITS {                // bits description
    Uint32 PLLEN:1;                     // 0 SYSPLL enable/disable bit
    Uint32 PLLCLKEN:1;                  // 1 SYSPLL bypassed or included in the PLLSYSCLK path
    Uint32 rsvd1:14;                    // 15:2 Reserved
    Uint32 rsvd2:16;                    // 31:16 Reserved
};

union SYSPLLCTL1_REG {
    Uint32  all;
    struct  SYSPLLCTL1_BITS  bit;
};

struct SYSPLLMULT_BITS {                // bits description
    Uint32 IMULT:7;                     // 6:0 SYSPLL Integer Multiplier
    Uint32 rsvd1:1;                     // 7 Reserved
    Uint32 FMULT:2;                     // 9:8 SYSPLL Fractional Multiplier
    Uint32 rsvd2:6;                     // 15:10 Reserved
    Uint32 ODIV:3;                      // 18:16 Output Clock Divider
    Uint32 rsvd3:5;                     // 23:19 Reserved
    Uint32 rsvd4:6;                     // 29:24 Reserved
    Uint32 rsvd5:2;                     // 31:30 Reserved
};

union SYSPLLMULT_REG {
    Uint32  all;
    struct  SYSPLLMULT_BITS  bit;
};

struct SYSPLLSTS_BITS {                 // bits description
    Uint32 LOCKS:1;                     // 0 SYSPLL Lock Status Bit
    Uint32 SLIPS:1;                     // 1 SYSPLL Slip Status Bit
    Uint32 rsvd1:14;                    // 15:2 Reserved
    Uint32 rsvd2:16;                    // 31:16 Reserved
};

union SYSPLLSTS_REG {
    Uint32  all;
    struct  SYSPLLSTS_BITS  bit;
};

struct SYSCLKDIVSEL_BITS {              // bits description
    Uint32 PLLSYSCLKDIV:6;              // 5:0 PLLSYSCLK Divide Select
    Uint32 rsvd1:10;                    // 15:6 Reserved
    Uint32 rsvd2:16;                    // 31:16 Reserved
};

union SYSCLKDIVSEL_REG {
    Uint32  all;
    struct  SYSCLKDIVSEL_BITS  bit;
};

struct XCLKOUTDIVSEL_BITS {             // bits description
    Uint32 XCLKOUTDIV:2;                // 1:0 XCLKOUT Divide Select
    Uint32 rsvd1:14;                    // 15:2 Reserved
    Uint32 rsvd2:16;                    // 31:16 Reserved
};

union XCLKOUTDIVSEL_REG {
    Uint32  all;
    struct  XCLKOUTDIVSEL_BITS  bit;
};

struct LOSPCP_BITS {                    // bits description
    Uint32 LSPCLKDIV:3;                 // 2:0 LSPCLK Divide Select
    Uint32 rsvd1:13;                    // 15:3 Reserved
    Uint32 rsvd2:16;                    // 31:16 Reserved
};

union LOSPCP_REG {
    Uint32  all;
    struct  LOSPCP_BITS  bit;
};

struct MCDCR_BITS {                     // bits description
    Uint32 MCLKSTS:1;                   // 0 Missing Clock Status Bit
    Uint32 MCLKCLR:1;                   // 1 Missing Clock Clear Bit
    Uint32 MCLKOFF:1;                   // 2 Missing Clock Detect Off Bit
    Uint32 OSCOFF:1;                    // 3 Oscillator Clock Off Bit
    Uint32 rsvd1:12;                    // 15:4 Reserved
    Uint32 rsvd2:16;                    // 31:16 Reserved
};

union MCDCR_REG {
    Uint32  all;
    struct  MCDCR_BITS  bit;
};

struct X1CNT_BITS {                     // bits description
    Uint32 X1CNT:10;                    // 9:0 X1 Counter
    Uint32 rsvd1:6;                     // 15:10 Reserved
    Uint32 CLR:1;                       // 16 X1 Counter Clear
    Uint32 rsvd2:15;                    // 31:17 Reserved
};

union X1CNT_REG {
    Uint32  all;
    struct  X1CNT_BITS  bit;
};

struct XTALCR_BITS {                    // bits description
    Uint32 OSCOFF:1;                    // 0 XTAL Oscillator powered-down
    Uint32 SE:1;                        // 1 XTAL Oscilator in Single-Ended mode
    Uint32 rsvd1:1;                     // 2 Reserved
    Uint32 rsvd2:13;                    // 15:3 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union XTALCR_REG {
    Uint32  all;
    struct  XTALCR_BITS  bit;
};

struct CLK_REGS {
    Uint16                                   rsvd1[2];                     // Reserved
    union   CLKCFGLOCK1_REG                  CLKCFGLOCK1;                  // Lock bit for CLKCFG registers
    Uint16                                   rsvd2[4];                     // Reserved
    union   CLKSRCCTL1_REG                   CLKSRCCTL1;                   // Clock Source Control register-1
    union   CLKSRCCTL2_REG                   CLKSRCCTL2;                   // Clock Source Control register-2
    union   CLKSRCCTL3_REG                   CLKSRCCTL3;                   // Clock Source Control register-3
    union   SYSPLLCTL1_REG                   SYSPLLCTL1;                   // SYSPLL Control register-1
    Uint16                                   rsvd3[4];                     // Reserved
    union   SYSPLLMULT_REG                   SYSPLLMULT;                   // SYSPLL Multiplier register
    union   SYSPLLSTS_REG                    SYSPLLSTS;                    // SYSPLL Status register
    Uint16                                   rsvd4[10];                    // Reserved
    union   SYSCLKDIVSEL_REG                 SYSCLKDIVSEL;                 // System Clock Divider Select register
    Uint16                                   rsvd5[4];                     // Reserved
    union   XCLKOUTDIVSEL_REG                XCLKOUTDIVSEL;                // XCLKOUT Divider Select register
    Uint16                                   rsvd6[2];                     // Reserved
    union   LOSPCP_REG                       LOSPCP;                       // Low Speed Clock Source Prescalar
    union   MCDCR_REG                        MCDCR;                        // Missing Clock Detect Control Register
    union   X1CNT_REG                        X1CNT;                        // 10-bit Counter on X1 Clock
    union   XTALCR_REG                       XTALCR;                       // XTAL Control Register
};

struct CPUSYSLOCK1_BITS {               // bits description
    Uint32 rsvd1:1;                     // 0 Reserved
    Uint32 rsvd2:1;                     // 1 Reserved
    Uint32 rsvd3:1;                     // 2 Reserved
    Uint32 PCLKCR0:1;                   // 3 Lock bit for PCLKCR0 Register
    Uint32 PCLKCR1:1;                   // 4 Lock bit for PCLKCR1 Register
    Uint32 PCLKCR2:1;                   // 5 Lock bit for PCLKCR2 Register
    Uint32 PCLKCR3:1;                   // 6 Lock bit for PCLKCR3 Register
    Uint32 PCLKCR4:1;                   // 7 Lock bit for PCLKCR4 Register
    Uint32 rsvd4:2;                     // 9:8 Reserved
    Uint32 PCLKCR7:1;                   // 10 Lock bit for PCLKCR7 Register
    Uint32 PCLKCR8:1;                   // 11 Lock bit for PCLKCR8 Register
    Uint32 PCLKCR9:1;                   // 12 Lock bit for PCLKCR9 Register
    Uint32 PCLKCR10:1;                  // 13 Lock bit for PCLKCR10 Register
    Uint32 rsvd5:1;                     // 14 Reserved
    Uint32 rsvd6:1;                     // 15 Reserved
    Uint32 PCLKCR13:1;                  // 16 Lock bit for PCLKCR13 Register
    Uint32 PCLKCR14:1;                  // 17 Lock bit for PCLKCR14 Register
    Uint32 rsvd7:1;                     // 18 Reserved
    Uint32 PCLKCR16:1;                  // 19 Lock bit for PCLKCR16 Register
    Uint32 rsvd8:1;                     // 20 Reserved
    Uint32 LPMCR:1;                     // 21 Lock bit for LPMCR Register
    Uint32 GPIOLPMSEL0:1;               // 22 Lock bit for GPIOLPMSEL0 Register
    Uint32 GPIOLPMSEL1:1;               // 23 Lock bit for GPIOLPMSEL1 Register
    Uint32 PCLKCR17:1;                  // 24 Lock bit for PCLKCR17 Register
    Uint32 PCLKCR18:1;                  // 25 Lock bit for PCLKCR18 Register
    Uint32 PCLKCR19:1;                  // 26 Lock bit for PCLKCR19 Register
    Uint32 PCLKCR20:1;                  // 27 Lock bit for PCLKCR20 Register
    Uint32 PCLKCR21:1;                  // 28 Lock bit for PCLKCR21 Register
    Uint32 rsvd9:1;                     // 29 Reserved
    Uint32 rsvd10:1;                    // 30 Reserved
    Uint32 rsvd11:1;                    // 31 Reserved
};

union CPUSYSLOCK1_REG {
    Uint32  all;
    struct  CPUSYSLOCK1_BITS  bit;
};

struct PCLKCR0_BITS {                   // bits description
    Uint32 rsvd1:1;                     // 0 Reserved
    Uint32 rsvd2:1;                     // 1 Reserved
    Uint32 DMA:1;                       // 2 DMA Clock Enable bit
    Uint32 TIMER0:1;                    // 3 TIMER0 Clock Enable bit
    Uint32 TIMER1:1;                    // 4 TIMER1 Clock Enable bit
    Uint32 TIMER2:1;                    // 5 TIMER2 Clock Enable bit
    Uint32 rsvd3:10;                    // 15:6 Reserved
    Uint32 HRPWM:1;                     // 16 HRPWM Clock Enable Bit
    Uint32 rsvd4:1;                     // 17 Reserved
    Uint32 TBCLKSYNC:1;                 // 18 PWM Time Base Clock sync
    Uint32 rsvd5:1;                     // 19 Reserved
    Uint32 rsvd6:12;                    // 31:20 Reserved
};

union PCLKCR0_REG {
    Uint32  all;
    struct  PCLKCR0_BITS  bit;
};

struct PCLKCR2_BITS {                   // bits description
    Uint32 PWM1:1;                      // 0 PWM1 Clock Enable bit
    Uint32 PWM2:1;                      // 1 PWM2 Clock Enable bit
    Uint32 PWM3:1;                      // 2 PWM3 Clock Enable bit
    Uint32 PWM4:1;                      // 3 PWM4 Clock Enable bit
    Uint32 PWM5:1;                      // 4 PWM5 Clock Enable bit
    Uint32 PWM6:1;                      // 5 PWM6 Clock Enable bit
    Uint32 PWM7:1;                      // 6 PWM7 Clock Enable bit
    Uint32 rsvd1:1;                     // 7 Reserved
    Uint32 rsvd2:8;                     // 15:8 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union PCLKCR2_REG {
    Uint32  all;
    struct  PCLKCR2_BITS  bit;
};

struct PCLKCR3_BITS {                   // bits description
    Uint32 CAP1:1;                      // 0 CAP1 Clock Enable bit
    Uint32 CAP2:1;                      // 1 CAP2 Clock Enable bit
    Uint32 CAP3:1;                      // 2 CAP3 Clock Enable bit
    Uint32 rsvd1:13;                    // 15:3 Reserved
    Uint32 rsvd2:16;                    // 31:16 Reserved
};

union PCLKCR3_REG {
    Uint32  all;
    struct  PCLKCR3_BITS  bit;
};

struct PCLKCR4_BITS {                   // bits description
    Uint32 QEP1:1;                      // 0 QEP1 Clock Enable bit
    Uint32 rsvd1:15;                    // 15:1 Reserved
    Uint32 rsvd2:16;                    // 31:16 Reserved
};

union PCLKCR4_REG {
    Uint32  all;
    struct  PCLKCR4_BITS  bit;
};

struct PCLKCR7_BITS {                   // bits description
    Uint32 UART_A:1;                    // 0 UART_A Clock Enable bit
    Uint32 UART_B:1;                    // 1 UART_B Clock Enable bit
    Uint32 UART_C:1;                    // 2 UART_C Clock Enable bit
    Uint32 rsvd2:1;                     // 3 Reserved
    Uint32 rsvd3:12;                    // 15:4 Reserved
    Uint32 rsvd4:16;                    // 31:16 Reserved
};

union PCLKCR7_REG {
    Uint32  all;
    struct  PCLKCR7_BITS  bit;
};

struct PCLKCR8_BITS {                   // bits description
    Uint32 SPI_A:1;                     // 0 SPI_A Clock Enable bit
    Uint32 rsvd1:15;                    // 15:1 Reserved
    Uint32 rsvd2:16;                    // 31:16 Reserved
};

union PCLKCR8_REG {
    Uint32  all;
    struct  PCLKCR8_BITS  bit;
};

struct PCLKCR9_BITS {                   // bits description
    Uint32 I2C_A:1;                     // 0 I2C_A Clock Enable bit
    Uint32 I2C_B:1;                     // 1 I2C_B Clock Enable bit
    Uint32 rsvd2:14;                    // 15:2 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union PCLKCR9_REG {
    Uint32  all;
    struct  PCLKCR9_BITS  bit;
};

struct PCLKCR10_BITS {                  // bits description
    Uint32 CAN_A:1;                     // 0 CAN_A Clock Enable bit
    Uint32 rsvd1:3;                     // 3:1 Reserved
    Uint32 CANFD_A:1;                   // 4 CANFDA Clock Enable bit
    Uint32 rsvd2:11;                    // 15:5 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union PCLKCR10_REG {
    Uint32  all;
    struct  PCLKCR10_BITS  bit;
};

struct PCLKCR13_BITS {                  // bits description
    Uint32 ADC_A:1;                     // 0 ADC_A Clock Enable bit
    Uint32 rsvd1:1;                     // 1 Reserved
    Uint32 ADC_C:1;                     // 2 ADC_C Clock Enable bit
    Uint32 rsvd2:1;                     // 3 Reserved
    Uint32 rsvd3:12;                    // 15:4 Reserved
    Uint32 rsvd4:16;                    // 31:16 Reserved
};

union PCLKCR13_REG {
    Uint32  all;
    struct  PCLKCR13_BITS  bit;
};

struct PCLKCR14_BITS {                  // bits description
    Uint32 COMP1:1;                     // 0 COMP1 Clock Enable bit
    Uint32 COMP2:1;                     // 1 COMP2 Clock Enable bit
    Uint32 COMP3:1;                     // 2 COMP3 Clock Enable bit
    Uint32 COMP4:1;                     // 3 COMP4 Clock Enable bit
    Uint32 rsvd1:12;                    // 15:4 Reserved
    Uint32 rsvd2:16;                    // 31:16 Reserved
};

union PCLKCR14_REG {
    Uint32  all;
    struct  PCLKCR14_BITS  bit;
};

struct PCLKCR16_BITS {                  // bits description
    Uint32 rsvd1:1;                     // 0 Reserved
    Uint32 rsvd2:1;                     // 1 Reserved
    Uint32 rsvd3:1;                     // 2 Reserved
    Uint32 rsvd4:1;                     // 3 Reserved
    Uint32 rsvd5:12;                    // 15:4 Reserved
    Uint32 DAC_A:1;                     // 16 Buffered_DAC_A Clock Enable Bit
    Uint32 DAC_B:1;                     // 17 Buffered_DAC_B Clock Enable Bit
    Uint32 rsvd6:1;                     // 18 Reserved
    Uint32 rsvd7:1;                     // 19 Reserved
    Uint32 rsvd8:12;                    // 31:20 Reserved
};

union PCLKCR16_REG {
    Uint32  all;
    struct  PCLKCR16_BITS  bit;
};

struct PCLKCR17_BITS {                  // bits description
    Uint32 FLB1:1;                      // 0 FLB1 Clock Enable bit
    Uint32 FLB2:1;                      // 1 FLB2 Clock Enable bit
    Uint32 FLB3:1;                      // 2 FLB3 Clock Enable bit
    Uint32 FLB4:1;                      // 3 FLB4 Clock Enable bit
    Uint32 rsvd1:12;                    // 15:4 Reserved
    Uint32 rsvd2:16;                    // 31:16 Reserved
};

union PCLKCR17_REG {
    Uint32  all;
    struct  PCLKCR17_BITS  bit;
};

struct PCLKCR19_BITS {                  // bits description
    Uint32 LIN_A:1;                     // 0 LIN_A Clock Enable bit
    Uint32 rsvd1:1;                     // 1 Reserved
    Uint32 rsvd2:1;                     // 2 Reserved
    Uint32 rsvd3:1;                     // 3 Reserved
    Uint32 rsvd4:12;                    // 15:4 Reserved
    Uint32 rsvd5:16;                    // 31:16 Reserved
};

union PCLKCR19_REG {
    Uint32  all;
    struct  PCLKCR19_BITS  bit;
};

struct PCLKCR20_BITS {                  // bits description
    Uint32 PMBUS_A:1;                   // 0 PMBUS_A Clock Enable bit
    Uint32 rsvd1:1;                     // 1 Reserved
    Uint32 rsvd2:14;                    // 15:2 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union PCLKCR20_REG {
    Uint32  all;
    struct  PCLKCR20_BITS  bit;
};

struct PCLKCR21_BITS {                  // bits description
    Uint32 DCC_0:1;                     // 0 DCC_0 Clock Enable Bit
    Uint32 rsvd1:15;                    // 15:1 Reserved
    Uint32 rsvd2:16;                    // 31:16 Reserved
};

union PCLKCR21_REG {
    Uint32  all;
    struct  PCLKCR21_BITS  bit;
};

struct LPMCR_BITS {                     // bits description
    Uint32 LPM:2;                       // 1:0 Low Power Mode setting
    Uint32 rsvd1:6;                     // 7:2 Reserved
    Uint32 rsvd2:7;                     // 14:8 Reserved
    Uint32 rsvd3:1;                     // 15 Reserved
    Uint32 rsvd4:2;                     // 17:16 Reserved
    Uint32 rsvd5:13;                    // 30:18 Reserved
    Uint32 rsvd6:1;                     // 31 Reserved
};

union LPMCR_REG {
    Uint32  all;
    struct  LPMCR_BITS  bit;
};

struct GPIOLPMSEL0_BITS {               // bits description
    Uint32 GPIO0:1;                     // 0 GPIO0 Enable for LPM Wakeup
    Uint32 GPIO1:1;                     // 1 GPIO1 Enable for LPM Wakeup
    Uint32 GPIO2:1;                     // 2 GPIO2 Enable for LPM Wakeup
    Uint32 GPIO3:1;                     // 3 GPIO3 Enable for LPM Wakeup
    Uint32 GPIO4:1;                     // 4 GPIO4 Enable for LPM Wakeup
    Uint32 GPIO5:1;                     // 5 GPIO5 Enable for LPM Wakeup
    Uint32 GPIO6:1;                     // 6 GPIO6 Enable for LPM Wakeup
    Uint32 GPIO7:1;                     // 7 GPIO7 Enable for LPM Wakeup
    Uint32 GPIO8:1;                     // 8 GPIO8 Enable for LPM Wakeup
    Uint32 GPIO9:1;                     // 9 GPIO9 Enable for LPM Wakeup
    Uint32 GPIO10:1;                    // 10 GPIO10 Enable for LPM Wakeup
    Uint32 GPIO11:1;                    // 11 GPIO11 Enable for LPM Wakeup
    Uint32 GPIO12:1;                    // 12 GPIO12 Enable for LPM Wakeup
    Uint32 GPIO13:1;                    // 13 GPIO13 Enable for LPM Wakeup
    Uint32 GPIO14:1;                    // 14 GPIO14 Enable for LPM Wakeup
    Uint32 GPIO15:1;                    // 15 GPIO15 Enable for LPM Wakeup
    Uint32 GPIO16:1;                    // 16 GPIO16 Enable for LPM Wakeup
    Uint32 GPIO17:1;                    // 17 GPIO17 Enable for LPM Wakeup
    Uint32 GPIO18:1;                    // 18 GPIO18 Enable for LPM Wakeup
    Uint32 GPIO19:1;                    // 19 GPIO19 Enable for LPM Wakeup
    Uint32 GPIO20:1;                    // 20 GPIO20 Enable for LPM Wakeup
    Uint32 GPIO21:1;                    // 21 GPIO21 Enable for LPM Wakeup
    Uint32 GPIO22:1;                    // 22 GPIO22 Enable for LPM Wakeup
    Uint32 GPIO23:1;                    // 23 GPIO23 Enable for LPM Wakeup
    Uint32 GPIO24:1;                    // 24 GPIO24 Enable for LPM Wakeup
    Uint32 GPIO25:1;                    // 25 GPIO25 Enable for LPM Wakeup
    Uint32 GPIO26:1;                    // 26 GPIO26 Enable for LPM Wakeup
    Uint32 GPIO27:1;                    // 27 GPIO27 Enable for LPM Wakeup
    Uint32 GPIO28:1;                    // 28 GPIO28 Enable for LPM Wakeup
    Uint32 GPIO29:1;                    // 29 GPIO29 Enable for LPM Wakeup
    Uint32 GPIO30:1;                    // 30 GPIO30 Enable for LPM Wakeup
    Uint32 GPIO31:1;                    // 31 GPIO31 Enable for LPM Wakeup
};

union GPIOLPMSEL0_REG {
    Uint32  all;
    struct  GPIOLPMSEL0_BITS  bit;
};

struct GPIOLPMSEL1_BITS {               // bits description
    Uint32 GPIO32:1;                    // 0 GPIO32 Enable for LPM Wakeup
    Uint32 GPIO33:1;                    // 1 GPIO33 Enable for LPM Wakeup
    Uint32 GPIO34:1;                    // 2 GPIO34 Enable for LPM Wakeup
    Uint32 GPIO35:1;                    // 3 GPIO35 Enable for LPM Wakeup
    Uint32 GPIO36:1;                    // 4 GPIO36 Enable for LPM Wakeup
    Uint32 GPIO37:1;                    // 5 GPIO37 Enable for LPM Wakeup
    Uint32 GPIO38:1;                    // 6 GPIO38 Enable for LPM Wakeup
    Uint32 GPIO39:1;                    // 7 GPIO39 Enable for LPM Wakeup
    Uint32 GPIO40:1;                    // 8 GPIO40 Enable for LPM Wakeup
    Uint32 GPIO41:1;                    // 9 GPIO41 Enable for LPM Wakeup
    Uint32 GPIO42:1;                    // 10 GPIO42 Enable for LPM Wakeup
    Uint32 GPIO43:1;                    // 11 GPIO43 Enable for LPM Wakeup
    Uint32 GPIO44:1;                    // 12 GPIO44 Enable for LPM Wakeup
    Uint32 GPIO45:1;                    // 13 GPIO45 Enable for LPM Wakeup
    Uint32 GPIO46:1;                    // 14 GPIO46 Enable for LPM Wakeup
    Uint32 GPIO47:1;                    // 15 GPIO47 Enable for LPM Wakeup
    Uint32 GPIO48:1;                    // 16 GPIO48 Enable for LPM Wakeup
    Uint32 GPIO49:1;                    // 17 GPIO49 Enable for LPM Wakeup
    Uint32 GPIO50:1;                    // 18 GPIO50 Enable for LPM Wakeup
    Uint32 GPIO51:1;                    // 19 GPIO51 Enable for LPM Wakeup
    Uint32 GPIO52:1;                    // 20 GPIO52 Enable for LPM Wakeup
    Uint32 GPIO53:1;                    // 21 GPIO53 Enable for LPM Wakeup
    Uint32 GPIO54:1;                    // 22 GPIO54 Enable for LPM Wakeup
    Uint32 GPIO55:1;                    // 23 GPIO55 Enable for LPM Wakeup
    Uint32 GPIO56:1;                    // 24 GPIO56 Enable for LPM Wakeup
    Uint32 GPIO57:1;                    // 25 GPIO57 Enable for LPM Wakeup
    Uint32 GPIO58:1;                    // 26 GPIO58 Enable for LPM Wakeup
    Uint32 GPIO59:1;                    // 27 GPIO59 Enable for LPM Wakeup
    Uint32 GPIO60:1;                    // 28 GPIO60 Enable for LPM Wakeup
    Uint32 GPIO61:1;                    // 29 GPIO61 Enable for LPM Wakeup
    Uint32 GPIO62:1;                    // 30 GPIO62 Enable for LPM Wakeup
    Uint32 GPIO63:1;                    // 31 GPIO63 Enable for LPM Wakeup
};

union GPIOLPMSEL1_REG {
    Uint32  all;
    struct  GPIOLPMSEL1_BITS  bit;
};

struct TMR2CLKCTL_BITS {                // bits description
    Uint32 TMR2CLKSRCSEL:3;             // 2:0 CPU Timer 2 Clock Source Select Bit
    Uint32 TMR2CLKPRESCALE:3;           // 5:3 CPU Timer 2 Clock Pre-Scale Value
    Uint32 rsvd1:10;                    // 15:6 Reserved
    Uint32 rsvd2:16;                    // 31:16 Reserved
};

union TMR2CLKCTL_REG {
    Uint32  all;
    struct  TMR2CLKCTL_BITS  bit;
};

struct RESCCLR_BITS {                   // bits description
    Uint32 rsvd1:2;                     // 1:0 Reserved
    Uint32 WDRSn:1;                     // 2 WDRSn Reset Cause Indication Bit
    Uint32 NMIWDRSn:1;                  // 3 NMIWDRSn Reset Cause Indication Bit
    Uint32 rsvd2:1;                     // 4 Reserved
    Uint32 rsvd3:1;                     // 5 Reserved
    Uint32 rsvd4:1;                     // 6 Reserved
    Uint32 rsvd5:1;                     // 7 Reserved
    Uint32 SCCRESETn:1;                 // 8 SCCRESETn Reset Cause Indication Bit
    Uint32 rsvd6:7;                     // 15:9 Reserved
    Uint32 rsvd7:16;                    // 31:16 Reserved
};

union RESCCLR_REG {
    Uint32  all;
    struct  RESCCLR_BITS  bit;
};

struct RESC_BITS {                      // bits description
    Uint32 rsvd1:2;                     // 1:0 Reserved
    Uint32 WDRSn:1;                     // 2 WDRSn Reset Cause Indication Bit
    Uint32 NMIWDRSn:1;                  // 3 NMIWDRSn Reset Cause Indication Bit
    Uint32 rsvd2:1;                     // 4 Reserved
    Uint32 rsvd3:1;                     // 5 Reserved
    Uint32 rsvd4:1;                     // 6 Reserved
    Uint32 rsvd5:1;                     // 7 Reserved
    Uint32 SCCRESETn:1;                 // 8 SCCRESETn Reset Cause Indication Bit
    Uint32 rsvd6:7;                     // 15:9 Reserved
    Uint32 rsvd7:14;                    // 29:16 Reserved
    Uint32 XRSn_pin_status:1;           // 30 XRSN Pin Status
    Uint32 DCON:1;                      // 31 Debugger conntion status to C28x
};

union RESC_REG {
    Uint32  all;
    struct  RESC_BITS  bit;
};

struct CPU_REGS {
    union   CPUSYSLOCK1_REG                  CPUSYSLOCK1;                  // Lock bit for CPUSYS registers
    Uint16                                   rsvd1[32];                    // Reserved
    union   PCLKCR0_REG                      PCLKCR0;                      // Peripheral Clock Gating Registers
    Uint16                                   rsvd2[2];                     // Reserved
    union   PCLKCR2_REG                      PCLKCR2;                      // Peripheral Clock Gating Registers
    union   PCLKCR3_REG                      PCLKCR3;                      // Peripheral Clock Gating Registers
    union   PCLKCR4_REG                      PCLKCR4;                      // Peripheral Clock Gating Registers
    Uint16                                   rsvd3[4];                     // Reserved
    union   PCLKCR7_REG                      PCLKCR7;                      // Peripheral Clock Gating Registers
    union   PCLKCR8_REG                      PCLKCR8;                      // Peripheral Clock Gating Registers
    union   PCLKCR9_REG                      PCLKCR9;                      // Peripheral Clock Gating Registers
    union   PCLKCR10_REG                     PCLKCR10;                     // Peripheral Clock Gating Registers
    Uint16                                   rsvd4[4];                     // Reserved
    union   PCLKCR13_REG                     PCLKCR13;                     // Peripheral Clock Gating Registers
    union   PCLKCR14_REG                     PCLKCR14;                     // Peripheral Clock Gating Registers
    Uint16                                   rsvd5[2];                     // Reserved
    union   PCLKCR16_REG                     PCLKCR16;                     // Peripheral Clock Gating Registers
    union   PCLKCR17_REG                     PCLKCR17;                     // Peripheral Clock Gating Registers
    Uint16                                   rsvd6[2];                     // Reserved
    union   PCLKCR19_REG                     PCLKCR19;                     // Peripheral Clock Gating Registers
    union   PCLKCR20_REG                     PCLKCR20;                     // Peripheral Clock Gating Registers
    union   PCLKCR21_REG                     PCLKCR21;                     // Peripheral Clock Gating Registers
    Uint16                                   rsvd7[40];                    // Reserved
    union   LPMCR_REG                        LPMCR;                        // LPM Control Register
    union   GPIOLPMSEL0_REG                  GPIOLPMSEL0;                  // GPIO LPM Wakeup select registers
    union   GPIOLPMSEL1_REG                  GPIOLPMSEL1;                  // GPIO LPM Wakeup select registers
    union   TMR2CLKCTL_REG                   TMR2CLKCTL;                   // Timer2 Clock Measurement functionality control register
    union   RESCCLR_REG                      RESCCLR;                      // Reset Cause Clear Register
    union   RESC_REG                         RESC;                         // Reset Cause register
};

struct SCSR_BITS {                      // bits description
    Uint16 WDOVERRIDE:1;                // 0 WD Override for WDDIS bit
    Uint16 WDENINT:1;                   // 1 WD Interrupt Enable
    Uint16 WDINTS:1;                    // 2 WD Interrupt Status
    Uint16 rsvd1:13;                    // 15:3 Reserved
};

union SCSR_REG {
    Uint16  all;
    struct  SCSR_BITS  bit;
};

struct WDCNTR_BITS {                    // bits description
    Uint16 WDCNTR:8;                    // 7:0 WD Counter
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union WDCNTR_REG {
    Uint16  all;
    struct  WDCNTR_BITS  bit;
};

struct WDKEY_BITS {                     // bits description
    Uint16 WDKEY:8;                     // 7:0 Key to pet the watchdog timer.
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union WDKEY_REG {
    Uint16  all;
    struct  WDKEY_BITS  bit;
};

struct WDCR_BITS {                      // bits description
    Uint16 WDPS:3;                      // 2:0 WD Clock Prescalar
    Uint16 WDCHK:3;                     // 5:3 WD Check Bits
    Uint16 WDDIS:1;                     // 6 WD Disable
    Uint16 WDFLG:1;                     // 7 WD reset status flag bit
    Uint16 WDPRECLKDIV:4;               // 11:8 WD Pre Clock Divider
    Uint16 rsvd2:4;                     // 15:12 Reserved
};

union WDCR_REG {
    Uint16  all;
    struct  WDCR_BITS  bit;
};

struct WDWCR_BITS {                     // bits description
    Uint16 MIN:8;                       // 7:0 WD Min Threshold setting for Windowed Watchdog functionality
    Uint16 FIRSTKEY:1;                  // 8 First valid WDKEY detected
    Uint16 rsvd2:7;                     // 15:9 Reserved
};

union WDWCR_REG {
    Uint16  all;
    struct  WDWCR_BITS  bit;
};

struct WDT_REGS {
    Uint16                                   rsvd1[34];                    // Reserved
    union   SCSR_REG                         SCSR;                         // System Control & Status Register
    union   WDCNTR_REG                       WDCNTR;                       // Watchdog Counter Register
    Uint16                                   rsvd2;                        // Reserved
    union   WDKEY_REG                        WDKEY;                        // Watchdog Reset Key Register
    Uint16                                   rsvd3[3];                     // Reserved
    union   WDCR_REG                         WDCR;                         // Watchdog Control Register
    union   WDWCR_REG                        WDWCR;                        // Watchdog Windowed Control Register
    Uint16                                   rsvd4;                        // Reserved, due to IAR Lp028 (4-byte object size)
};

struct DMACHSRCSELLOCK_BITS {           // bits description
    Uint32 DMACHSRCSEL1:1;              // 0 DMACHSRCSEL1 Register Lock bit
    Uint32 DMACHSRCSEL2:1;              // 1 DMACHSRCSEL2 Register Lock bit
    Uint32 rsvd1:14;                    // 15:2 Reserved
    Uint32 rsvd2:16;                    // 31:16 Reserved
};

union DMACHSRCSELLOCK_REG {
    Uint32  all;
    struct  DMACHSRCSELLOCK_BITS  bit;
};

struct DMACHSRCSEL1_BITS {              // bits description
    Uint32 CH1:8;                       // 7:0 Selects the Trigger and Sync Source CH1 of DMA
    Uint32 CH2:8;                       // 15:8 Selects the Trigger and Sync Source CH2 of DMA
    Uint32 CH3:8;                       // 23:16 Selects the Trigger and Sync Source CH3 of DMA
    Uint32 CH4:8;                       // 31:24 Selects the Trigger and Sync Source CH4 of DMA
};

union DMACHSRCSEL1_REG {
    Uint32  all;
    struct  DMACHSRCSEL1_BITS  bit;
};

struct DMACHSRCSEL2_BITS {              // bits description
    Uint32 CH5:8;                       // 7:0 Selects the Trigger and Sync Source CH5 of DMA
    Uint32 CH6:8;                       // 15:8 Selects the Trigger and Sync Source CH6 of DMA
    Uint32 rsvd1:16;                    // 31:16 Reserved
};

union DMACHSRCSEL2_REG {
    Uint32  all;
    struct  DMACHSRCSEL2_BITS  bit;
};

struct DMA_CH_SEL_REGS {
    Uint16                                rsvd1[4];                  // Reserved
    union   DMACHSRCSELLOCK_REG           DMACHSRCSELLOCK;           // DMA Channel Triger Source Select Lock Register
    Uint16                                rsvd2[16];                 // Reserved
    union   DMACHSRCSEL1_REG              DMACHSRCSEL1;              // DMA Channel Trigger Source Select Register-1
    union   DMACHSRCSEL2_REG              DMACHSRCSEL2;              // DMA Channel Trigger Source Select Register-2
};

struct ADCA_AC_BITS {                   // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union ADCA_AC_REG {
    Uint32  all;
    struct  ADCA_AC_BITS  bit;
};

struct ADCC_AC_BITS {                   // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union ADCC_AC_REG {
    Uint32  all;
    struct  ADCC_AC_BITS  bit;
};

struct COMP1_AC_BITS {                 // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union COMP1_AC_REG {
    Uint32  all;
    struct  COMP1_AC_BITS  bit;
};

struct COMP2_AC_BITS {                 // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union COMP2_AC_REG {
    Uint32  all;
    struct  COMP2_AC_BITS  bit;
};

struct COMP3_AC_BITS {                 // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union COMP3_AC_REG {
    Uint32  all;
    struct  COMP3_AC_BITS  bit;
};

struct COMP4_AC_BITS {                 // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union COMP4_AC_REG {
    Uint32  all;
    struct  COMP4_AC_BITS  bit;
};

struct DACA_AC_BITS {                   // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union DACA_AC_REG {
    Uint32  all;
    struct  DACA_AC_BITS  bit;
};

struct DACB_AC_BITS {                   // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union DACB_AC_REG {
    Uint32  all;
    struct  DACB_AC_BITS  bit;
};

struct PWM1_AC_BITS {                  // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union PWM1_AC_REG {
    Uint32  all;
    struct  PWM1_AC_BITS  bit;
};

struct PWM2_AC_BITS {                  // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union PWM2_AC_REG {
    Uint32  all;
    struct  PWM2_AC_BITS  bit;
};

struct PWM3_AC_BITS {                  // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union PWM3_AC_REG {
    Uint32  all;
    struct  PWM3_AC_BITS  bit;
};

struct PWM4_AC_BITS {                  // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union PWM4_AC_REG {
    Uint32  all;
    struct  PWM4_AC_BITS  bit;
};

struct PWM5_AC_BITS {                  // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union PWM5_AC_REG {
    Uint32  all;
    struct  PWM5_AC_BITS  bit;
};

struct PWM6_AC_BITS {                  // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union PWM6_AC_REG {
    Uint32  all;
    struct  PWM6_AC_BITS  bit;
};

struct PWM7_AC_BITS {                  // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union PWM7_AC_REG {
    Uint32  all;
    struct  PWM7_AC_BITS  bit;
};

struct QEP1_AC_BITS {                  // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union QEP1_AC_REG {
    Uint32  all;
    struct  QEP1_AC_BITS  bit;
};

struct CAP1_AC_BITS {                  // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union CAP1_AC_REG {
    Uint32  all;
    struct  CAP1_AC_BITS  bit;
};

struct CAP2_AC_BITS {                  // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union CAP2_AC_REG {
    Uint32  all;
    struct  CAP2_AC_BITS  bit;
};

struct CAP3_AC_BITS {                  // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union CAP3_AC_REG {
    Uint32  all;
    struct  CAP3_AC_BITS  bit;
};

struct FLB1_AC_BITS {                   // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:4;                     // 5:2 Reserved
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union FLB1_AC_REG {
    Uint32  all;
    struct  FLB1_AC_BITS  bit;
};

struct FLB2_AC_BITS {                   // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:4;                     // 5:2 Reserved
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union FLB2_AC_REG {
    Uint32  all;
    struct  FLB2_AC_BITS  bit;
};

struct FLB3_AC_BITS {                   // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:4;                     // 5:2 Reserved
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union FLB3_AC_REG {
    Uint32  all;
    struct  FLB3_AC_BITS  bit;
};

struct FLB4_AC_BITS {                   // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:4;                     // 5:2 Reserved
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union FLB4_AC_REG {
    Uint32  all;
    struct  FLB4_AC_BITS  bit;
};

struct SPIA_AC_BITS {                   // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union SPIA_AC_REG {
    Uint32  all;
    struct  SPIA_AC_BITS  bit;
};

struct PMBUS_A_AC_BITS {                // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union PMBUS_A_AC_REG {
    Uint32  all;
    struct  PMBUS_A_AC_BITS  bit;
};

struct LIN_A_AC_BITS {                  // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union LIN_A_AC_REG {
    Uint32  all;
    struct  LIN_A_AC_BITS  bit;
};

struct CANA_AC_BITS {                  // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union CANA_AC_REG {
    Uint32  all;
    struct  CANA_AC_BITS  bit;
};

struct CANFDA_AC_BITS {                // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union CANFDA_AC_REG {
    Uint32  all;
    struct  CANFDA_AC_BITS  bit;
};

struct HRPWM_A_AC_BITS {               // bits description
    Uint32 CPU_ACC:2;                  // 1:0 CPU Access conditions to peripheral
    Uint32 rsvd1:2;                    // 3:2 Reserved
    Uint32 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint32 rsvd2:10;                    // 15:6 Reserved
    Uint32 rsvd3:16;                    // 31:16 Reserved
};

union HRPWM_A_AC_REG {
    Uint32  all;
    struct  HRPWM_A_AC_BITS  bit;
};

struct PERIPH_AC_LOCK_BITS {            // bits description
    Uint32 LOCK_AC_WR:1;                // 0  Lock control for Access control registers write.
    Uint32 rsvd1:15;                    // 15:1 Reserved
    Uint32 rsvd2:16;                    // 31:16 Reserved
};

union PERIPH_AC_LOCK_REG {
    Uint32  all;
    struct  PERIPH_AC_LOCK_BITS  bit;
};

struct PERIPH_REGS {
    union   ADCA_AC_REG                     ADCA_AC;                    // ADCA Master Access Control Register
    Uint16                                  rsvd1[2];                   // Reserved
    union   ADCC_AC_REG                     ADCC_AC;                    // ADCC Master Access Control Register
    Uint16                                  rsvd2[10];                  // Reserved
    union   COMP1_AC_REG                    COMP1AC;                    // COMP1 Master Access Control Register
    union   COMP2_AC_REG                    COMP2AC;                    // COMP2 Master Access Control Register
    union   COMP3_AC_REG                    COMP3AC;                    // COMP3 Master Access Control Register
    union   COMP4_AC_REG                    COMP4AC;                    // COMP4 Master Access Control Register
    Uint16                                  rsvd3[16];                  // Reserved
    union   DACA_AC_REG                     DACA_AC;                    // DACA Master Access Control Register
    union   DACB_AC_REG                     DACB_AC;                    // DACB Master Access Control Register
    Uint16                                  rsvd4[28];                  // Reserved
    union   PWM1_AC_REG                     PWM1_AC;                    // PWM1 Master Access Control Register
    union   PWM2_AC_REG                     PWM2_AC;                    // PWM2 Master Access Control Register
    union   PWM3_AC_REG                     PWM3_AC;                    // PWM3 Master Access Control Register
    union   PWM4_AC_REG                     PWM4_AC;                    // PWM4 Master Access Control Register
    union   PWM5_AC_REG                     PWM5_AC;                    // PWM5 Master Access Control Register
    union   PWM6_AC_REG                     PWM6_AC;                    // PWM6 Master Access Control Register
    union   PWM7_AC_REG                     PWM7_AC;                    // PWM7 Master Access Control Register
    Uint16                                  rsvd5[26];                  // Reserved
    union   QEP1_AC_REG                     QEP1_AC;                    // QEP1 Master Access Control Register
    Uint16                                  rsvd6[14];                  // Reserved
    union   CAP1_AC_REG                     CAP1AC;                     // CAP1 Master Access Control Register
    union   CAP2_AC_REG                     CAP2AC;                     // CAP2 Master Access Control Register
    union   CAP3_AC_REG                     CAP3AC;                     // CAP3 Master Access Control Register
    Uint16                                  rsvd7[42];                  // Reserved
    union   FLB1_AC_REG                     FLB1_AC;                    // FLB1 Master Access Control Register
    union   FLB2_AC_REG                     FLB2_AC;                    // FLB2 Master Access Control Register
    union   FLB3_AC_REG                     FLB3_AC;                    // FLB3 Master Access Control Register
    union   FLB4_AC_REG                     FLB4_AC;                    // FLB4 Master Access Control Register
    Uint16                                  rsvd8[88];                  // Reserved
    union   SPIA_AC_REG                     SPIA_AC;                    // SPIA Master Access Control Register
    Uint16                                  rsvd9[30];                  // Reserved
    union   PMBUS_A_AC_REG                  PMBUS_A_AC;                 // PMBUSA Master Access Control Register
    Uint16                                  rsvd10[6];                  // Reserved
    union   LIN_A_AC_REG                    LIN_A_AC;                   // LINA Master Access Control Register
    Uint16                                  rsvd11[6];                  // Reserved
    union   CANA_AC_REG                     CANA_AC;                    // CANA Master Access Control Register
    Uint16                                  rsvd12[6];                  // Reserved
    union   CANFDA_AC_REG                   CANFDA_AC;                  // CANFDA Master Access Control Register
    Uint16                                  rsvd13[96];                 // Reserved
    union   HRPWM_A_AC_REG                  HRPWM_A_AC;                 // HRPWM Master Access Control Register
    Uint16                                  rsvd14[82];                 // Reserved
    union   PERIPH_AC_LOCK_REG              PERIPH_AC_LOCK;             // Lock Register to stop Write access to peripheral Access register.
};

struct SYNCSELECT0_BITS {               // bits description
    Uint32 rsvd1:16;                   // 15:0 Reserved
    Uint32 rsvd2:8;                    // 23:16 Reserved
    Uint32 SYNCOUT:5;                  // 28:24 Select Syncout Source
    Uint32 rsvd3:3;                    // 31:29 Reserved
};

union SYNCSELECT0_REG {
    Uint32  all;
    struct  SYNCSELECT0_BITS  bit;
};

struct ADCSOCOUTSELECT_BITS {           // bits description
    Uint32 PWM1SOCAEN:1;                // 0 PWM1SOCAEN Enable for ADCSOCAOn
    Uint32 PWM2SOCAEN:1;                // 1 PWM2SOCAEN Enable for ADCSOCAOn
    Uint32 PWM3SOCAEN:1;                // 2 PWM3SOCAEN Enable for ADCSOCAOn
    Uint32 PWM4SOCAEN:1;                // 3 PWM4SOCAEN Enable for ADCSOCAOn
    Uint32 PWM5SOCAEN:1;                // 4 PWM5SOCAEN Enable for ADCSOCAOn
    Uint32 PWM6SOCAEN:1;                // 5 PWM6SOCAEN Enable for ADCSOCAOn
    Uint32 PWM7SOCAEN:1;                // 6 PWM7SOCAEN Enable for ADCSOCAOn
    Uint32 rsvd1:2;                     // 8:7 Reserved
    Uint32 rsvd2:1;                     // 9 Reserved
    Uint32 rsvd3:1;                     // 10 Reserved
    Uint32 rsvd4:1;                     // 11 Reserved
    Uint32 rsvd5:4;                     // 15:12 Reserved
    Uint32 PWM1SOCBEN:1;                // 16 PWM1SOCBEN Enable for ADCSOCBOn
    Uint32 PWM2SOCBEN:1;                // 17 PWM2SOCBEN Enable for ADCSOCBOn
    Uint32 PWM3SOCBEN:1;                // 18 PWM3SOCBEN Enable for ADCSOCBOn
    Uint32 PWM4SOCBEN:1;                // 19 PWM4SOCBEN Enable for ADCSOCBOn
    Uint32 PWM5SOCBEN:1;                // 20 PWM5SOCBEN Enable for ADCSOCBOn
    Uint32 PWM6SOCBEN:1;                // 21 PWM6SOCBEN Enable for ADCSOCBOn
    Uint32 PWM7SOCBEN:1;                // 22 PWM7SOCBEN Enable for ADCSOCBOn
    Uint32 rsvd6:2;                     // 24:23 Reserved
    Uint32 rsvd7:1;                     // 25 Reserved
    Uint32 rsvd8:1;                     // 26 Reserved
    Uint32 rsvd9:1;                     // 27 Reserved
    Uint32 rsvd10:4;                    // 31:28 Reserved
};

union ADCSOCOUTSELECT_REG {
    Uint32  all;
    struct  ADCSOCOUTSELECT_BITS  bit;
};

struct SYNCSOCLOCK_BITS {               // bits description
    Uint16 SYNCSELECT0:1;               // 0 SYNCSEL Register 0 Lock bit
    Uint16 ADCSOCOUTSELECT:1;           // 1 ADCSOCOUTSELECT Register Lock bit
    Uint16 SYNCSELECT1:1;               // 2 SYNCSEL Register 1 Lock bit
    Uint16 SYNCSELECT2:1;               // 3 SYNCSEL Register 2 Lock bit
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 SYNCSELECT5:1;               // 6 SYNCSEL Register 5 Lock bit
    Uint16 rsvd2:9;                     // 15:7 Reserved
};

union SYNCSOCLOCK_REG {
    Uint16  all;
    struct  SYNCSOCLOCK_BITS  bit;
};

struct SYNCSELECT1_BITS {               // bits description
    Uint32 PWM1SYNCIN:5;                // 4:0 PWM1 Sync Input SourceSelect
    Uint32 rsvd1:3;                     // 7:5 Reserved
    Uint32 PWM2SYNCIN:5;                // 12:8 PWM2 Sync Input SourceSelect
    Uint32 rsvd2:3;                     // 15:13 Reserved
    Uint32 PWM3SYNCIN:5;                // 20:16 PWM3 Sync Input SourceSelect
    Uint32 rsvd3:3;                     // 23:21 Reserved
    Uint32 PWM4SYNCIN:5;                // 28:24 PWM4 Sync Input SourceSelect
    Uint32 rsvd4:3;                     // 31:29 Reserved
};

union SYNCSELECT1_REG {
    Uint32  all;
    struct  SYNCSELECT1_BITS  bit;
};

struct SYNCSELECT2_BITS {               // bits description
    Uint32 PWM5SYNCIN:5;                // 4:0 PWM5 Sync Input SourceSelect
    Uint32 rsvd1:3;                     // 7:5 Reserved
    Uint32 PWM6SYNCIN:5;                // 12:8 PWM6  Sync Input SourceSelect
    Uint32 rsvd2:3;                     // 15:13 Reserved
    Uint32 PWM7SYNCIN:5;                // 20:16 PWM7 Sync Input SourceSelect
    Uint32 rsvd3:11;                    // 31:21 Reserved
};

union SYNCSELECT2_REG {
    Uint32  all;
    struct  SYNCSELECT2_BITS  bit;
};

struct SYNCSELECT5_BITS {               // bits description
    Uint32 CAP1SYNCIN:5;                // 4:0 CAP1 Sync Input SourceSelect
    Uint32 rsvd1:3;                     // 7:5 Reserved
    Uint32 CAP2SYNCIN:5;                // 12:8 CAP2 Sync Input SourceSelect
    Uint32 rsvd2:3;                     // 15:13 Reserved
    Uint32 CAP3SYNCIN:5;                // 20:16 CAP3 Sync Input SourceSelect
    Uint32 rsvd3:11;                    // 31:21 Reserved
};

union SYNCSELECT5_REG {
    Uint32  all;
    struct  SYNCSELECT5_BITS  bit;
};

struct SYNC_SOC_REGS {
    union   SYNCSELECT0_REG                  SYNCSELECT0;                   // Sync Input and Output Select Register 0
    union   ADCSOCOUTSELECT_REG              ADCSOCOUTSELECT;               // External ADCSOC Select Register
    union   SYNCSOCLOCK_REG                  SYNCSOCLOCK;                   // SYNCSEL and EXTADCSOC Select Lock register
    Uint16                                   rsvd0;                         // Reserved
    union   SYNCSELECT1_REG                  SYNCSELECT1;                   // Sync Input and Output Select Register 1
    union   SYNCSELECT2_REG                  SYNCSELECT2;                   // Sync Input and Output Select Register 2
    Uint16                                   rsvd1[4];                      // Reserved   
    union   SYNCSELECT5_REG                  SYNCSELECT5;                   // Sync Input and Output Select Register 5
};

struct EMUBOOTPINCFG_BITS {         // bits description
    Uint32 BOOTSEL0 : 8;            // 7:0 Boot Mode Select Pin 0
    Uint32 BOOTSEL1 : 8;            // 15:8 Boot Mode Select Pin 1
    Uint32 BOOTSEL2 : 8;            // 23:16 Boot Mode Select Pin 2
    Uint32 KEY : 8;                 // 31:24 Key Word
};

union EMUBOOTPINCFG_REG {
    Uint32  all;
    struct  EMUBOOTPINCFG_BITS  bit;
};

struct EMUBOOTDEFL_BITS {         // bits description
    Uint32 BOOTDEF0 : 8;          // 7:0 BOOT_DEF0 Mode/Options
    Uint32 BOOTDEF1 : 8;          // 15:8 BOOT_DEF1 Mode/Options
    Uint32 BOOTDEF2 : 8;          // 23:16 BOOT_DEF2 Mode/Options
    Uint32 BOOTDEF3 : 8;          // 31:24 BOOT_DEF3 Mode/Options
};

union EMUBOOTDEFL_REG {
    Uint32  all;
    struct  EMUBOOTDEFL_BITS  bit;
};

struct EMUBOOTDEFH_BITS {         // bits description
    Uint32 BOOTDEF4 : 8;          // 7:0 BOOT_DEF4 Mode/Options
    Uint32 BOOTDEF5 : 8;          // 15:8 BOOT_DEF5 Mode/Options
    Uint32 BOOTDEF6 : 8;          // 23:16 BOOT_DEF6 Mode/Options
    Uint32 BOOTDEF7 : 8;          // 31:24 BOOT_DEF7 Mode/Options
};

union EMUBOOTDEFH_REG {
    Uint32  all;
    struct  EMUBOOTDEFH_BITS  bit;
};

struct CFGSMSSEL_BITS {              // bits description
    Uint32 CFGSMSSEL : 4;            // 3:0 CFGSMS Static configuration Select
    Uint32 rsvd : 28;                // 31:4 Reserved
};

union CFGSMSSEL_REG {
    Uint32  all;
    struct  CFGSMSSEL_BITS  bit;
};

struct APBCLKDIVCFG_BITS {               // bits description
    Uint32 APBCLKDIVCFG : 5;             // 4:0 APB clock divide configure
    Uint32 rsvd : 27;                    // 31:5 Reserved
};

union APBCLKDIVCFG_REG {
    Uint32  all;
    struct  APBCLKDIVCFG_BITS  bit;
};

struct VOS_BITS {                // bits description
    Uint32 VOSEN : 1;            // 0 VOS Enable
    Uint32 LDOVSCACFG : 3;       // 3:1 LDO voltage scaling configure
    Uint32 rsvd : 28;            // 31:4 Reserved
};

union VOS_REG {
    Uint32 all;
    struct VOS_BITS  bit;
};

struct SPEC_REGS {
    union        EMUBOOTPINCFG_REG  EMUBOOTPINCFG;
    union        EMUBOOTDEFL_REG    EMUBOOTDEFL;
    union        EMUBOOTDEFH_REG    EMUBOOTDEFH;
    Uint16                          rsvd1[36];
    Uint16                          rsvd2[8];
    union        CFGSMSSEL_REG      CFGSMSSEL;
    Uint16                          rsvd3[6];
    union        APBCLKDIVCFG_REG   APBCLKDIVCFG;
    union        VOS_REG            VOS;
};

//---------------------------------------------------------------------------
// SYSCTRL External References & Function Declarations:
//
extern volatile struct SYNC_SOC_REGS SyncSocRegs;
extern volatile struct WDT_REGS WdtRegs;
extern volatile struct DMA_CH_SEL_REGS DmaChSelRegs;
extern volatile struct DEV_REGS DevCfgRegs;
extern volatile struct CLK_REGS ClkCfgRegs;
extern volatile struct CPU_REGS CpuSysRegs;
extern volatile struct PERIPH_REGS SysPeriphAcRegs;
extern volatile struct SPEC_REGS SysCtlRegs;

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
