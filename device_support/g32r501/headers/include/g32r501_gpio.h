//###########################################################################
//
// FILE:    g32r501_gpio.h
//
// TITLE:   Definitions for the GPIO registers.
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
// - 2024-07-08:
// 1. Update register naming and access rules.
//
//###########################################################################

#ifndef G32R501_GPIO_H
#define G32R501_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// GPIO Individual Register Bit Definitions:

struct GPACTRL_BITS {                   // bits description
    Uint32 QUALPRD0:8;                       // 7:0 GPIO0 to GPIO7 sampling cycle
    Uint32 QUALPRD1:8;                       // 15:8 GPIO8 to GPIO15 sampling cycle
    Uint32 QUALPRD2:8;                       // 23:16 GPIO16 to GPIO23 sampling cycle
    Uint32 QUALPRD3:8;                       // 31:24 GPIO24 to GPIO31 sampling cycle
};

union GPACTRL_REG {
    Uint32  all;
    struct  GPACTRL_BITS  bit;
};

struct GPAQSEL1_BITS {                // bits description
    Uint32 GPIO0:2;                     // 1:0 GPIO0 Input  type
    Uint32 GPIO1:2;                     // 3:2 GPIO1 Input  type
    Uint32 GPIO2:2;                     // 5:4 GPIO2 Input  type
    Uint32 GPIO3:2;                     // 7:6 GPIO3 Input  type
    Uint32 GPIO4:2;                     // 9:8 GPIO4 Input  type
    Uint32 GPIO5:2;                     // 11:10 GPIO5 Input  type
    Uint32 GPIO6:2;                     // 13:12 GPIO6 Input  type
    Uint32 GPIO7:2;                     // 15:14 GPIO7 Input  type
    Uint32 GPIO8:2;                     // 17:16 GPIO8 Input  type
    Uint32 GPIO9:2;                     // 19:18 GPIO9 Input  type
    Uint32 GPIO10:2;                    // 21:20 GPIO10 Input  type
    Uint32 GPIO11:2;                    // 23:22 GPIO11 Input  type
    Uint32 GPIO12:2;                    // 25:24 GPIO12 Input  type
    Uint32 GPIO13:2;                    // 27:26 GPIO13 Input  type
    Uint32 GPIO14:2;                    // 29:28 GPIO14 Input  type
    Uint32 GPIO15:2;                    // 31:30 GPIO15 Input  type
};

union GPAQSEL1_REG {
    Uint32  all;
    struct  GPAQSEL1_BITS  bit;
};

struct GPAQSEL2_BITS {                // bits description
    Uint32 GPIO16:2;                    // 1:0 GPIO16 Input  type
    Uint32 GPIO17:2;                    // 3:2 GPIO17 Input  type
    Uint32 GPIO18:2;                    // 5:4 GPIO18 Input  type
    Uint32 GPIO19:2;                    // 7:6 GPIO19 Input  type
    Uint32 GPIO20:2;                    // 9:8 GPIO20 Input  type
    Uint32 GPIO21:2;                    // 11:10 GPIO21 Input  type
    Uint32 GPIO22:2;                    // 13:12 GPIO22 Input  type
    Uint32 GPIO23:2;                    // 15:14 GPIO23 Input  type
    Uint32 GPIO24:2;                    // 17:16 GPIO24 Input  type
    Uint32 GPIO25:2;                    // 19:18 GPIO25 Input  type
    Uint32 GPIO26:2;                    // 21:20 GPIO26 Input  type
    Uint32 GPIO27:2;                    // 23:22 GPIO27 Input  type
    Uint32 GPIO28:2;                    // 25:24 GPIO28 Input  type
    Uint32 GPIO29:2;                    // 27:26 GPIO29 Input  type
    Uint32 GPIO30:2;                    // 29:28 GPIO30 Input  type
    Uint32 GPIO31:2;                    // 31:30 GPIO31 Input  type
};

union GPAQSEL2_REG {
    Uint32  all;
    struct  GPAQSEL2_BITS  bit;
};

struct GPAMUX1_BITS {                // bits description
    Uint32 GPIO0:2;                     // 1:0 GPIO0 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO1:2;                     // 3:2 GPIO1 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO2:2;                     // 5:4 GPIO2 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO3:2;                     // 7:6 GPIO3 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO4:2;                     // 9:8 GPIO4 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO5:2;                     // 11:10 GPIO5 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO6:2;                     // 13:12 GPIO6 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO7:2;                     // 15:14 GPIO7 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO8:2;                     // 17:16 GPIO8 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO9:2;                     // 19:18 GPIO9 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO10:2;                    // 21:20 GPIO10 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO11:2;                    // 23:22 GPIO11 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO12:2;                    // 25:24 GPIO12 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO13:2;                    // 27:26 GPIO13 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO14:2;                    // 29:28 GPIO14 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO15:2;                    // 31:30 GPIO15 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
};

union GPAMUX1_REG {
    Uint32  all;
    struct  GPAMUX1_BITS  bit;
};

struct GPAMUX2_BITS {                // bits description
    Uint32 GPIO16:2;                    // 1:0 GPIO16 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO17:2;                    // 3:2 GPIO17 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO18:2;                    // 5:4 GPIO18 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO19:2;                    // 7:6 GPIO19 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO20:2;                    // 9:8 GPIO20 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO21:2;                    // 11:10 GPIO21 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO22:2;                    // 13:12 GPIO22 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO23:2;                    // 15:14 GPIO23 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO24:2;                    // 17:16 GPIO24 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO25:2;                    // 19:18 GPIO25 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO26:2;                    // 21:20 GPIO26 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO27:2;                    // 23:22 GPIO27 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO28:2;                    // 25:24 GPIO28 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO29:2;                    // 27:26 GPIO29 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO30:2;                    // 29:28 GPIO30 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
    Uint32 GPIO31:2;                    // 31:30 GPIO31 peripheral mux configuration in the low 2 bitsGPIO0 peripheral mux configuration in the low 2 bits
};

union GPAMUX2_REG {
    Uint32  all;
    struct  GPAMUX2_BITS  bit;
};

struct GPADIR_BITS {                    // bits description
    Uint32 GPIO0:1;                     // 0 GPIO0 Data direction
    Uint32 GPIO1:1;                     // 1 GPIO1 Data direction
    Uint32 GPIO2:1;                     // 2 GPIO2 Data direction
    Uint32 GPIO3:1;                     // 3 GPIO3 Data direction
    Uint32 GPIO4:1;                     // 4 GPIO4 Data direction
    Uint32 GPIO5:1;                     // 5 GPIO5 Data direction
    Uint32 GPIO6:1;                     // 6 GPIO6 Data direction
    Uint32 GPIO7:1;                     // 7 GPIO7 Data direction
    Uint32 GPIO8:1;                     // 8 GPIO8 Data direction
    Uint32 GPIO9:1;                     // 9 GPIO9 Data direction
    Uint32 GPIO10:1;                    // 10 GPIO10 Data direction
    Uint32 GPIO11:1;                    // 11 GPIO11 Data direction
    Uint32 GPIO12:1;                    // 12 GPIO12 Data direction
    Uint32 GPIO13:1;                    // 13 GPIO13 Data direction
    Uint32 GPIO14:1;                    // 14 GPIO14 Data direction
    Uint32 GPIO15:1;                    // 15 GPIO15 Data direction
    Uint32 GPIO16:1;                    // 16 GPIO16 Data direction
    Uint32 GPIO17:1;                    // 17 GPIO17 Data direction
    Uint32 GPIO18:1;                    // 18 GPIO18 Data direction
    Uint32 GPIO19:1;                    // 19 GPIO19 Data direction
    Uint32 GPIO20:1;                    // 20 GPIO20 Data direction
    Uint32 GPIO21:1;                    // 21 GPIO21 Data direction
    Uint32 GPIO22:1;                    // 22 GPIO22 Data direction
    Uint32 GPIO23:1;                    // 23 GPIO23 Data direction
    Uint32 GPIO24:1;                    // 24 GPIO24 Data direction
    Uint32 GPIO25:1;                    // 25 GPIO25 Data direction
    Uint32 GPIO26:1;                    // 26 GPIO26 Data direction
    Uint32 GPIO27:1;                    // 27 GPIO27 Data direction
    Uint32 GPIO28:1;                    // 28 GPIO28 Data direction
    Uint32 GPIO29:1;                    // 29 GPIO29 Data direction
    Uint32 GPIO30:1;                    // 30 GPIO30 Data direction
    Uint32 GPIO31:1;                    // 31 GPIO31 Data direction
};

union GPADIR_REG {
    Uint32  all;
    struct  GPADIR_BITS  bit;
};

struct GPAPUD_BITS {                    // bits description
    Uint32 GPIO0:1;                     // 0 GPIO0 Pull-up disable
    Uint32 GPIO1:1;                     // 1 GPIO1 Pull-up disable
    Uint32 GPIO2:1;                     // 2 GPIO2 Pull-up disable
    Uint32 GPIO3:1;                     // 3 GPIO3 Pull-up disable
    Uint32 GPIO4:1;                     // 4 GPIO4 Pull-up disable
    Uint32 GPIO5:1;                     // 5 GPIO5 Pull-up disable
    Uint32 GPIO6:1;                     // 6 GPIO6 Pull-up disable
    Uint32 GPIO7:1;                     // 7 GPIO7 Pull-up disable
    Uint32 GPIO8:1;                     // 8 GPIO8 Pull-up disable
    Uint32 GPIO9:1;                     // 9 GPIO9 Pull-up disable
    Uint32 GPIO10:1;                    // 10 GPIO10 Pull-up disable
    Uint32 GPIO11:1;                    // 11 GPIO11 Pull-up disable
    Uint32 GPIO12:1;                    // 12 GPIO12 Pull-up disable
    Uint32 GPIO13:1;                    // 13 GPIO13 Pull-up disable
    Uint32 GPIO14:1;                    // 14 GPIO14 Pull-up disable
    Uint32 GPIO15:1;                    // 15 GPIO15 Pull-up disable
    Uint32 GPIO16:1;                    // 16 GPIO16 Pull-up disable
    Uint32 GPIO17:1;                    // 17 GPIO17 Pull-up disable
    Uint32 GPIO18:1;                    // 18 GPIO18 Pull-up disable
    Uint32 GPIO19:1;                    // 19 GPIO19 Pull-up disable
    Uint32 GPIO20:1;                    // 20 GPIO20 Pull-up disable
    Uint32 GPIO21:1;                    // 21 GPIO21 Pull-up disable
    Uint32 GPIO22:1;                    // 22 GPIO22 Pull-up disable
    Uint32 GPIO23:1;                    // 23 GPIO23 Pull-up disable
    Uint32 GPIO24:1;                    // 24 GPIO24 Pull-up disable
    Uint32 GPIO25:1;                    // 25 GPIO25 Pull-up disable
    Uint32 GPIO26:1;                    // 26 GPIO26 Pull-up disable
    Uint32 GPIO27:1;                    // 27 GPIO27 Pull-up disable
    Uint32 GPIO28:1;                    // 28 GPIO28 Pull-up disable
    Uint32 GPIO29:1;                    // 29 GPIO29 Pull-up disable
    Uint32 GPIO30:1;                    // 30 GPIO30 Pull-up disable
    Uint32 GPIO31:1;                    // 31 GPIO31 Pull-up disable
};

union GPAPUD_REG {
    Uint32  all;
    struct  GPAPUD_BITS  bit;
};

struct GPAINV_BITS {                 // bits description
    Uint32 GPIO0:1;                     // 0 GPIO0 Input inversion
    Uint32 GPIO1:1;                     // 1 GPIO1 Input inversion
    Uint32 GPIO2:1;                     // 2 GPIO2 Input inversion
    Uint32 GPIO3:1;                     // 3 GPIO3 Input inversion
    Uint32 GPIO4:1;                     // 4 GPIO4 Input inversion
    Uint32 GPIO5:1;                     // 5 GPIO5 Input inversion
    Uint32 GPIO6:1;                     // 6 GPIO6 Input inversion
    Uint32 GPIO7:1;                     // 7 GPIO7 Input inversion
    Uint32 GPIO8:1;                     // 8 GPIO8 Input inversion
    Uint32 GPIO9:1;                     // 9 GPIO9 Input inversion
    Uint32 GPIO10:1;                    // 10 GPIO10 Input inversion
    Uint32 GPIO11:1;                    // 11 GPIO11 Input inversion
    Uint32 GPIO12:1;                    // 12 GPIO12 Input inversion
    Uint32 GPIO13:1;                    // 13 GPIO13 Input inversion
    Uint32 GPIO14:1;                    // 14 GPIO14 Input inversion
    Uint32 GPIO15:1;                    // 15 GPIO15 Input inversion
    Uint32 GPIO16:1;                    // 16 GPIO16 Input inversion
    Uint32 GPIO17:1;                    // 17 GPIO17 Input inversion
    Uint32 GPIO18:1;                    // 18 GPIO18 Input inversion
    Uint32 GPIO19:1;                    // 19 GPIO19 Input inversion
    Uint32 GPIO20:1;                    // 20 GPIO20 Input inversion
    Uint32 GPIO21:1;                    // 21 GPIO21 Input inversion
    Uint32 GPIO22:1;                    // 22 GPIO22 Input inversion
    Uint32 GPIO23:1;                    // 23 GPIO23 Input inversion
    Uint32 GPIO24:1;                    // 24 GPIO24 Input inversion
    Uint32 GPIO25:1;                    // 25 GPIO25 Input inversion
    Uint32 GPIO26:1;                    // 26 GPIO26 Input inversion
    Uint32 GPIO27:1;                    // 27 GPIO27 Input inversion
    Uint32 GPIO28:1;                    // 28 GPIO28 Input inversion
    Uint32 GPIO29:1;                    // 29 GPIO29 Input inversion
    Uint32 GPIO30:1;                    // 30 GPIO30 Input inversion
    Uint32 GPIO31:1;                    // 31 GPIO31 Input inversion
};

union GPAINV_REG {
    Uint32  all;
    struct  GPAINV_BITS  bit;
};

struct GPAODR_BITS {                 // bits description
    Uint32 GPIO0:1;                     // 0 GPIO0 Open-drain output mode
    Uint32 GPIO1:1;                     // 1 GPIO1 Open-drain output mode
    Uint32 GPIO2:1;                     // 2 GPIO2 Open-drain output mode
    Uint32 GPIO3:1;                     // 3 GPIO3 Open-drain output mode
    Uint32 GPIO4:1;                     // 4 GPIO4 Open-drain output mode
    Uint32 GPIO5:1;                     // 5 GPIO5 Open-drain output mode
    Uint32 GPIO6:1;                     // 6 GPIO6 Open-drain output mode
    Uint32 GPIO7:1;                     // 7 GPIO7 Open-drain output mode
    Uint32 GPIO8:1;                     // 8 GPIO8 Open-drain output mode
    Uint32 GPIO9:1;                     // 9 GPIO9 Open-drain output mode
    Uint32 GPIO10:1;                    // 10 GPIO10 Open-drain output mode
    Uint32 GPIO11:1;                    // 11 GPIO11 Open-drain output mode
    Uint32 GPIO12:1;                    // 12 GPIO12 Open-drain output mode
    Uint32 GPIO13:1;                    // 13 GPIO13 Open-drain output mode
    Uint32 GPIO14:1;                    // 14 GPIO14 Open-drain output mode
    Uint32 GPIO15:1;                    // 15 GPIO15 Open-drain output mode
    Uint32 GPIO16:1;                    // 16 GPIO16 Open-drain output mode
    Uint32 GPIO17:1;                    // 17 GPIO17 Open-drain output mode
    Uint32 GPIO18:1;                    // 18 GPIO18 Open-drain output mode
    Uint32 GPIO19:1;                    // 19 GPIO19 Open-drain output mode
    Uint32 GPIO20:1;                    // 20 GPIO20 Open-drain output mode
    Uint32 GPIO21:1;                    // 21 GPIO21 Open-drain output mode
    Uint32 GPIO22:1;                    // 22 GPIO22 Open-drain output mode
    Uint32 GPIO23:1;                    // 23 GPIO23 Open-drain output mode
    Uint32 GPIO24:1;                    // 24 GPIO24 Open-drain output mode
    Uint32 GPIO25:1;                    // 25 GPIO25 Open-drain output mode
    Uint32 GPIO26:1;                    // 26 GPIO26 Open-drain output mode
    Uint32 GPIO27:1;                    // 27 GPIO27 Open-drain output mode
    Uint32 GPIO28:1;                    // 28 GPIO28 Open-drain output mode
    Uint32 GPIO29:1;                    // 29 GPIO29 Open-drain output mode
    Uint32 GPIO30:1;                    // 30 GPIO30 Open-drain output mode
    Uint32 GPIO31:1;                    // 31 GPIO31 Open-drain output mode
};

union GPAODR_REG {
    Uint32  all;
    struct  GPAODR_BITS  bit;
};

struct GPAAMSEL_BITS {                  // bits description
    Uint32 rsvd1:1;                     // 0 Reserved
    Uint32 rsvd2:1;                     // 1 Reserved
    Uint32 rsvd3:1;                     // 2 Reserved
    Uint32 rsvd4:1;                     // 3 Reserved
    Uint32 rsvd5:1;                     // 4 Reserved
    Uint32 rsvd6:1;                     // 5 Reserved
    Uint32 rsvd7:1;                     // 6 Reserved
    Uint32 rsvd8:1;                     // 7 Reserved
    Uint32 rsvd9:1;                     // 8 Reserved
    Uint32 rsvd10:1;                    // 9 Reserved
    Uint32 rsvd11:1;                    // 10 Reserved
    Uint32 rsvd12:1;                    // 11 Reserved
    Uint32 rsvd13:1;                    // 12 Reserved
    Uint32 rsvd14:1;                    // 13 Reserved
    Uint32 rsvd15:1;                    // 14 Reserved
    Uint32 rsvd16:1;                    // 15 Reserved
    Uint32 rsvd17:1;                    // 16 Reserved
    Uint32 rsvd18:1;                    // 17 Reserved
    Uint32 rsvd19:1;                    // 18 Reserved
    Uint32 rsvd20:1;                    // 19 Reserved
    Uint32 rsvd21:1;                    // 20 Reserved
    Uint32 rsvd22:1;                    // 21 Reserved
    Uint32 GPIO22:1;                    // Analog mode select for GPIO22
    Uint32 GPIO23:1;                    // Analog mode select for GPIO23
    Uint32 rsvd23:1;                    // 24 Reserved
    Uint32 rsvd24:1;                    // 25 Reserved
    Uint32 rsvd25:1;                    // 26 Reserved
    Uint32 rsvd26:1;                    // 27 Reserved
    Uint32 rsvd27:1;                    // 28 Reserved
    Uint32 rsvd28:1;                    // 29 Reserved
    Uint32 rsvd29:1;                    // 30 Reserved
    Uint32 rsvd30:1;                    // 31 Reserved
};

union GPAAMSEL_REG {
    Uint32  all;
    struct  GPAAMSEL_BITS  bit;
};

struct GPADSEL1_BITS {                    // bits description
    Uint32 GPIO0:2;                     // 0 
    Uint32 GPIO1:2;                     // 1 
    Uint32 GPIO2:2;                     // 2 
    Uint32 GPIO3:2;                     // 3 
    Uint32 GPIO4:2;                     // 4 
    Uint32 GPIO5:2;                     // 5 
    Uint32 GPIO6:2;                     // 6 
    Uint32 GPIO7:2;                     // 7 
    Uint32 GPIO8:2;                     // 8 
    Uint32 GPIO9:2;                     // 9 
    Uint32 GPIO10:2;                    // 10
    Uint32 GPIO11:2;                    // 11
    Uint32 GPIO12:2;                    // 12 
    Uint32 GPIO13:2;                    // 13 
    Uint32 GPIO14:2;                    // 14 
    Uint32 GPIO15:2;                    // 15
};

union GPADSEL1_REG {
    Uint32  all;
    struct  GPADSEL1_BITS  bit;
};

struct GPADSEL2_BITS {                     // bits description
    Uint32 GPIO16:2;                     // 16 
    Uint32 GPIO17:2;                     // 17 
    Uint32 GPIO18:2;                     // 18 
    Uint32 GPIO19:2;                     // 19 
    Uint32 GPIO20:2;                     // 20 
    Uint32 GPIO21:2;                     // 21 
    Uint32 GPIO22:2;                     // 22 
    Uint32 GPIO23:2;                     // 23 
    Uint32 GPIO24:2;                     // 24 
    Uint32 GPIO25:2;                     // 25 
    Uint32 GPIO26:2;                     // 26
    Uint32 GPIO27:2;                     // 27
    Uint32 GPIO28:2;                     // 28 
    Uint32 GPIO29:2;                     // 29 
    Uint32 GPIO30:2;                     // 30 
    Uint32 GPIO31:2;                     // 31
};

union GPADSEL2_REG {
    Uint32  all;
    struct  GPADSEL2_BITS  bit;
};

struct GPAFEN_BITS {                     // bits description
    Uint32 GPIO0:1;                     // 0 
    Uint32 GPIO1:1;                     // 1 
    Uint32 GPIO2:1;                     // 2 
    Uint32 GPIO3:1;                     // 3 
    Uint32 GPIO4:1;                     // 4 
    Uint32 GPIO5:1;                     // 5 
    Uint32 GPIO6:1;                     // 6 
    Uint32 GPIO7:1;                     // 7 
    Uint32 GPIO8:1;                     // 8 
    Uint32 GPIO9:1;                     // 9 
    Uint32 GPIO10:1;                    // 10
    Uint32 GPIO11:1;                    // 11
    Uint32 GPIO12:1;                    // 12 
    Uint32 GPIO13:1;                    // 13 
    Uint32 GPIO14:1;                    // 14 
    Uint32 GPIO15:1;                    // 15
    Uint32 GPIO16:1;                     // 16 
    Uint32 GPIO17:1;                     // 17 
    Uint32 GPIO18:1;                     // 18 
    Uint32 GPIO19:1;                     // 19 
    Uint32 GPIO20:1;                     // 20 
    Uint32 GPIO21:1;                     // 21 
    Uint32 GPIO22:1;                     // 22 
    Uint32 GPIO23:1;                     // 23 
    Uint32 GPIO24:1;                     // 24 
    Uint32 GPIO25:1;                     // 25 
    Uint32 GPIO26:1;                     // 26
    Uint32 GPIO27:1;                     // 27
    Uint32 GPIO28:1;                     // 28 
    Uint32 GPIO29:1;                     // 29 
    Uint32 GPIO30:1;                     // 30 
    Uint32 GPIO31:1;                     // 31
};

union GPAFEN_REG {
    Uint32  all;
    struct  GPAFEN_BITS  bit;
};

struct GPAGMUX1_BITS {                // bits description
    Uint32 GPIO0:2;                     // 1:0 GPIO0 peripheral mux configuration in the High 2 bits
    Uint32 GPIO1:2;                     // 3:2 GPIO1 peripheral mux configuration in the High 2 bits
    Uint32 GPIO2:2;                     // 5:4 GPIO2 peripheral mux configuration in the High 2 bits
    Uint32 GPIO3:2;                     // 7:6 GPIO3 peripheral mux configuration in the High 2 bits
    Uint32 GPIO4:2;                     // 9:8 GPIO4 peripheral mux configuration in the High 2 bits
    Uint32 GPIO5:2;                     // 11:10 GPIO5 peripheral mux configuration in the High 2 bits
    Uint32 GPIO6:2;                     // 13:12 GPIO6 peripheral mux configuration in the High 2 bits
    Uint32 GPIO7:2;                     // 15:14 GPIO7 peripheral mux configuration in the High 2 bits
    Uint32 GPIO8:2;                     // 17:16 GPIO8 peripheral mux configuration in the High 2 bits
    Uint32 GPIO9:2;                     // 19:18 GPIO9 peripheral mux configuration in the High 2 bits
    Uint32 GPIO10:2;                    // 21:20 GPIO10 peripheral mux configuration in the High 2 bits
    Uint32 GPIO11:2;                    // 23:22 GPIO11 peripheral mux configuration in the High 2 bits
    Uint32 GPIO12:2;                    // 25:24 GPIO12 peripheral mux configuration in the High 2 bits
    Uint32 GPIO13:2;                    // 27:26 GPIO13 peripheral mux configuration in the High 2 bits
    Uint32 GPIO14:2;                    // 29:28 GPIO14 peripheral mux configuration in the High 2 bits
    Uint32 GPIO15:2;                    // 31:30 GPIO15 peripheral mux configuration in the High 2 bits
};

union GPAGMUX1_REG {
    Uint32  all;
    struct  GPAGMUX1_BITS  bit;
};

struct GPAGMUX2_BITS {                // bits description
    Uint32 GPIO16:2;                    // 1:0 GPIO16 peripheral mux configuration in the High 2 bits
    Uint32 GPIO17:2;                    // 3:2 GPIO17 peripheral mux configuration in the High 2 bits
    Uint32 GPIO18:2;                    // 5:4 GPIO18 peripheral mux configuration in the High 2 bits
    Uint32 GPIO19:2;                    // 7:6 GPIO19 peripheral mux configuration in the High 2 bits
    Uint32 GPIO20:2;                    // 9:8 GPIO20 peripheral mux configuration in the High 2 bits
    Uint32 GPIO21:2;                    // 11:10 GPIO21 peripheral mux configuration in the High 2 bits
    Uint32 GPIO22:2;                    // 13:12 GPIO22 peripheral mux configuration in the High 2 bits
    Uint32 GPIO23:2;                    // 15:14 GPIO23 peripheral mux configuration in the High 2 bits
    Uint32 GPIO24:2;                    // 17:16 GPIO24 peripheral mux configuration in the High 2 bits
    Uint32 GPIO25:2;                    // 19:18 GPIO25 peripheral mux configuration in the High 2 bits
    Uint32 GPIO26:2;                    // 21:20 GPIO26 peripheral mux configuration in the High 2 bits
    Uint32 GPIO27:2;                    // 23:22 GPIO27 peripheral mux configuration in the High 2 bits
    Uint32 GPIO28:2;                    // 25:24 GPIO28 peripheral mux configuration in the High 2 bits
    Uint32 GPIO29:2;                    // 27:26 GPIO29 peripheral mux configuration in the High 2 bits
    Uint32 GPIO30:2;                    // 29:28 GPIO30 peripheral mux configuration in the High 2 bits
    Uint32 GPIO31:2;                    // 31:30 GPIO31 peripheral mux configuration in the High 2 bits
};

union GPAGMUX2_REG {
    Uint32  all;
    struct  GPAGMUX2_BITS  bit;
};

struct GPACSEL1_BITS {                // bits description
    Uint32 GPIO0:4;                     // 3:0 GPIO0 Master core select
    Uint32 GPIO1:4;                     // 7:4 GPIO1 Master core select
    Uint32 GPIO2:4;                     // 11:8 GPIO2 Master core select
    Uint32 GPIO3:4;                     // 15:12 GPIO3 Master core select
    Uint32 GPIO4:4;                     // 19:16 GPIO4 Master core Select
    Uint32 GPIO5:4;                     // 23:20 GPIO5 Master core Select
    Uint32 GPIO6:4;                     // 27:24 GPIO6 Master core Select
    Uint32 GPIO7:4;                     // 31:28 GPIO7 Master core Select
};

union GPACSEL1_REG {
    Uint32  all;
    struct  GPACSEL1_BITS  bit;
};

struct GPACSEL2_BITS {                // bits description
    Uint32 GPIO8:4;                     // 3:0 GPIO8 Master core Select
    Uint32 GPIO9:4;                     // 7:4 GPIO9 Master core Select
    Uint32 GPIO10:4;                    // 11:8 GPIO10 Master core Select
    Uint32 GPIO11:4;                    // 15:12 GPIO11 Master core Select
    Uint32 GPIO12:4;                    // 19:16 GPIO12 Master core Select
    Uint32 GPIO13:4;                    // 23:20 GPIO13 Master core Select
    Uint32 GPIO14:4;                    // 27:24 GPIO14 Master core Select
    Uint32 GPIO15:4;                    // 31:28 GPIO15 Master core Select
};

union GPACSEL2_REG {
    Uint32  all;
    struct  GPACSEL2_BITS  bit;
};

struct GPACSEL3_BITS {                // bits description
    Uint32 GPIO16:4;                    // 3:0 GPIO16 Master core Select
    Uint32 GPIO17:4;                    // 7:4 GPIO17 Master core Select
    Uint32 GPIO18:4;                    // 11:8 GPIO18 Master core Select
    Uint32 GPIO19:4;                    // 15:12 GPIO19 Master core Select
    Uint32 GPIO20:4;                    // 19:16 GPIO20 Master core Select
    Uint32 GPIO21:4;                    // 23:20 GPIO21 Master core Select
    Uint32 GPIO22:4;                    // 27:24 GPIO22 Master core Select
    Uint32 GPIO23:4;                    // 31:28 GPIO23 Master core Select
};

union GPACSEL3_REG {
    Uint32  all;
    struct  GPACSEL3_BITS  bit;
};

struct GPACSEL4_BITS {                // bits description
    Uint32 GPIO24:4;                    // 3:0 GPIO24 Master core Select
    Uint32 GPIO25:4;                    // 7:4 GPIO25 Master core Select
    Uint32 GPIO26:4;                    // 11:8 GPIO26 Master core Select
    Uint32 GPIO27:4;                    // 15:12 GPIO27 Master core Select
    Uint32 GPIO28:4;                    // 19:16 GPIO28 Master core Select
    Uint32 GPIO29:4;                    // 23:20 GPIO29 Master core Select
    Uint32 GPIO30:4;                    // 27:24 GPIO30 Master core Select
    Uint32 GPIO31:4;                    // 31:28 GPIO31 Master core Select
};

union GPACSEL4_REG {
    Uint32  all;
    struct  GPACSEL4_BITS  bit;
};

struct GPALOCK_BITS {                   // bits description
    Uint32 GPIO0:1;                     // 0 GPIO0 Configuration lock
    Uint32 GPIO1:1;                     // 1 GPIO1 Configuration lock
    Uint32 GPIO2:1;                     // 2 GPIO2 Configuration lock
    Uint32 GPIO3:1;                     // 3 GPIO3 Configuration lock
    Uint32 GPIO4:1;                     // 4 GPIO4 Configuration lock
    Uint32 GPIO5:1;                     // 5 GPIO5 Configuration lock
    Uint32 GPIO6:1;                     // 6 GPIO6 Configuration lock
    Uint32 GPIO7:1;                     // 7 GPIO7 Configuration lock
    Uint32 GPIO8:1;                     // 8 GPIO8 Configuration lock
    Uint32 GPIO9:1;                     // 9 GPIO9 Configuration lock
    Uint32 GPIO10:1;                    // 10 GPIO10 Configuration lock
    Uint32 GPIO11:1;                    // 11 GPIO11 Configuration lock
    Uint32 GPIO12:1;                    // 12 GPIO12 Configuration lock
    Uint32 GPIO13:1;                    // 13 GPIO13 Configuration lock
    Uint32 GPIO14:1;                    // 14 GPIO14 Configuration lock
    Uint32 GPIO15:1;                    // 15 GPIO15 Configuration lock
    Uint32 GPIO16:1;                    // 16 GPIO16 Configuration lock
    Uint32 GPIO17:1;                    // 17 GPIO17 Configuration lock
    Uint32 GPIO18:1;                    // 18 GPIO18 Configuration lock
    Uint32 GPIO19:1;                    // 19 GPIO19 Configuration lock
    Uint32 GPIO20:1;                    // 20 GPIO20 Configuration lock
    Uint32 GPIO21:1;                    // 21 GPIO21 Configuration lock
    Uint32 GPIO22:1;                    // 22 GPIO22 Configuration lock
    Uint32 GPIO23:1;                    // 23 GPIO23 Configuration lock
    Uint32 GPIO24:1;                    // 24 GPIO24 Configuration lock
    Uint32 GPIO25:1;                    // 25 GPIO25 Configuration lock
    Uint32 GPIO26:1;                    // 26 GPIO26 Configuration lock
    Uint32 GPIO27:1;                    // 27 GPIO27 Configuration lock
    Uint32 GPIO28:1;                    // 28 GPIO28 Configuration lock
    Uint32 GPIO29:1;                    // 29 GPIO29 Configuration lock
    Uint32 GPIO30:1;                    // 30 GPIO30 Configuration lock
    Uint32 GPIO31:1;                    // 31 GPIO31 Configuration lock
};

union GPALOCK_REG {
    Uint32  all;
    struct  GPALOCK_BITS  bit;
};

struct GPACR_BITS {                     // bits description
    Uint32 GPIO0:1;                     // 0 GPIO0 lock is locked
    Uint32 GPIO1:1;                     // 1 GPIO1 lock is locked
    Uint32 GPIO2:1;                     // 2 GPIO2 lock is locked
    Uint32 GPIO3:1;                     // 3 GPIO3 lock is locked
    Uint32 GPIO4:1;                     // 4 GPIO4 lock is locked
    Uint32 GPIO5:1;                     // 5 GPIO5 lock is locked
    Uint32 GPIO6:1;                     // 6 GPIO6 lock is locked
    Uint32 GPIO7:1;                     // 7 GPIO7 lock is locked
    Uint32 GPIO8:1;                     // 8 GPIO8 lock is locked
    Uint32 GPIO9:1;                     // 9 GPIO9 lock is locked
    Uint32 GPIO10:1;                    // 10 GPIO10 lock is locked
    Uint32 GPIO11:1;                    // 11 GPIO11 lock is locked
    Uint32 GPIO12:1;                    // 12 GPIO12 lock is locked
    Uint32 GPIO13:1;                    // 13 GPIO13 lock is locked
    Uint32 GPIO14:1;                    // 14 GPIO14 lock is locked
    Uint32 GPIO15:1;                    // 15 GPIO15 lock is locked
    Uint32 GPIO16:1;                    // 16 GPIO16 lock is locked
    Uint32 GPIO17:1;                    // 17 GPIO17 lock is locked
    Uint32 GPIO18:1;                    // 18 GPIO18 lock is locked
    Uint32 GPIO19:1;                    // 19 GPIO19 lock is locked
    Uint32 GPIO20:1;                    // 20 GPIO20 lock is locked
    Uint32 GPIO21:1;                    // 21 GPIO21 lock is locked
    Uint32 GPIO22:1;                    // 22 GPIO22 lock is locked
    Uint32 GPIO23:1;                    // 23 GPIO23 lock is locked
    Uint32 GPIO24:1;                    // 24 GPIO24 lock is locked
    Uint32 GPIO25:1;                    // 25 GPIO25 lock is locked
    Uint32 GPIO26:1;                    // 26 GPIO26 lock is locked
    Uint32 GPIO27:1;                    // 27 GPIO27 lock is locked
    Uint32 GPIO28:1;                    // 28 GPIO28 lock is locked
    Uint32 GPIO29:1;                    // 29 GPIO29 lock is locked
    Uint32 GPIO30:1;                    // 30 GPIO30 lock is locked
    Uint32 GPIO31:1;                    // 31 GPIO31 lock is locked
};

union GPACR_REG {
    Uint32  all;
    struct  GPACR_BITS  bit;
};

struct GPBCTRL_BITS {              // bits description
    Uint32 QUALPRD0:8;                  // 7:0 GPIO32 to GPIO39 sampling cycle
    Uint32 QUALPRD1:8;                  // 15:8 GPIO40 to GPIO47 sampling cycle
    Uint32 QUALPRD2:8;                  // 23:16 GPIO48 to GPIO55 sampling cycle
    Uint32 QUALPRD3:8;                  // 31:24 GPIO56 to GPIO59 sampling cycle
};

union GPBCTRL_REG {
    Uint32  all;
    struct  GPBCTRL_BITS  bit;
};

struct GPBQSEL1_BITS {                // bits description
    Uint32 GPIO32:2;                    // 1:0 GPIO32 Input  type
    Uint32 GPIO33:2;                    // 3:2 GPIO33 Input  type
    Uint32 GPIO34:2;                    // 5:4 GPIO34 Input  type
    Uint32 GPIO35:2;                    // 7:6 GPIO35 Input  type
    Uint32 rsvd1:2;                     // 9:8 Reserved
    Uint32 GPIO37:2;                    // 11:10 GPIO37 Input  type
    Uint32 rsvd2:2;                     // 13:12 Reserved
    Uint32 GPIO39:2;                    // 15:14 GPIO39 Input  type
    Uint32 GPIO40:2;                    // 17:16 GPIO40 Input  type
    Uint32 GPIO41:2;                    // 19:18 GPIO41 Input  type
    Uint32 GPIO42:2;                    // 21:20 GPIO42 Input  type
    Uint32 GPIO43:2;                    // 23:22 GPIO43 Input  type
    Uint32 GPIO44:2;                    // 25:24 GPIO44 Input  type
    Uint32 GPIO45:2;                    // 27:26 GPIO45 Input  type
    Uint32 GPIO46:2;                    // 29:28 GPIO46 Input  type
    Uint32 GPIO47:2;                    // 31:30 GPIO47 Input  type
};

union GPBQSEL1_REG {
    Uint32  all;
    struct  GPBQSEL1_BITS  bit;
};

struct GPBQSEL2_BITS {                // bits description
    Uint32 GPIO48:2;                    // 1:0 GPIO48 Input  type
    Uint32 GPIO49:2;                    // 3:2 GPIO49 Input  type
    Uint32 GPIO50:2;                    // 5:4 GPIO50 Input  type
    Uint32 GPIO51:2;                    // 7:6 GPIO51 Input  type
    Uint32 GPIO52:2;                    // 9:8 GPIO52 Input  type
    Uint32 GPIO53:2;                    // 11:10 GPIO53 Input  type
    Uint32 GPIO54:2;                    // 13:12 GPIO54 Input  type
    Uint32 GPIO55:2;                    // 15:14 GPIO55 Input  type
    Uint32 GPIO56:2;                    // 17:16 GPIO56 Input  type
    Uint32 GPIO57:2;                    // 19:18 GPIO57 Input  type
    Uint32 GPIO58:2;                    // 21:20 GPIO58 Input  type
    Uint32 GPIO59:2;                    // 23:22 GPIO59 Input  type
    Uint32 rsvd1:2;                     // 25:24 Reserved
    Uint32 rsvd2:2;                     // 27:26 Reserved
    Uint32 rsvd3:2;                     // 29:28 Reserved
    Uint32 rsvd4:2;                     // 31:30 Reserved
};

union GPBQSEL2_REG {
    Uint32  all;
    struct  GPBQSEL2_BITS  bit;
};

struct GPBMUX1_BITS {                // bits description
    Uint32 GPIO32:2;                    // 1:0 GPIO32 peripheral mux configuration in the low 2 bits
    Uint32 GPIO33:2;                    // 3:2 GPIO33 peripheral mux configuration in the low 2 bits
    Uint32 GPIO34:2;                    // 5:4 GPIO34 peripheral mux configuration in the low 2 bits
    Uint32 GPIO35:2;                    // 7:6 GPIO35 peripheral mux configuration in the low 2 bits
    Uint32 rsvd1:2;                     // 9:8 Reserved
    Uint32 GPIO37:2;                    // 11:10 GPIO37 peripheral mux configuration in the low 2 bits
    Uint32 rsvd2:2;                     // 13:12 Reserved
    Uint32 GPIO39:2;                    // 15:14 GPIO39 peripheral mux configuration in the low 2 bits
    Uint32 GPIO40:2;                    // 17:16 GPIO40 peripheral mux configuration in the low 2 bits
    Uint32 GPIO41:2;                    // 19:18 GPIO41 peripheral mux configuration in the low 2 bits
    Uint32 GPIO42:2;                    // 21:20 GPIO42 peripheral mux configuration in the low 2 bits
    Uint32 GPIO43:2;                    // 23:22 GPIO43 peripheral mux configuration in the low 2 bits
    Uint32 GPIO44:2;                    // 25:24 GPIO44 peripheral mux configuration in the low 2 bits
    Uint32 GPIO45:2;                    // 27:26 GPIO45 peripheral mux configuration in the low 2 bits
    Uint32 GPIO46:2;                    // 29:28 GPIO46 peripheral mux configuration in the low 2 bits
    Uint32 GPIO47:2;                    // 31:30 GPIO47 peripheral mux configuration in the low 2 bits
};

union GPBMUX1_REG {
    Uint32  all;
    struct  GPBMUX1_BITS  bit;
};

struct GPBMUX2_BITS {                // bits description
    Uint32 GPIO48:2;                    // 1:0 GPIO48 peripheral mux configuration in the low 2 bits
    Uint32 GPIO49:2;                    // 3:2 GPIO49 peripheral mux configuration in the low 2 bits
    Uint32 GPIO50:2;                    // 5:4 GPIO50 peripheral mux configuration in the low 2 bits
    Uint32 GPIO51:2;                    // 7:6 GPIO51 peripheral mux configuration in the low 2 bits
    Uint32 GPIO52:2;                    // 9:8 GPIO52 peripheral mux configuration in the low 2 bits
    Uint32 GPIO53:2;                    // 11:10 GPIO53 peripheral mux configuration in the low 2 bits
    Uint32 GPIO54:2;                    // 13:12 GPIO54 peripheral mux configuration in the low 2 bits
    Uint32 GPIO55:2;                    // 15:14 GPIO55 peripheral mux configuration in the low 2 bits
    Uint32 GPIO56:2;                    // 17:16 GPIO56 peripheral mux configuration in the low 2 bits
    Uint32 GPIO57:2;                    // 19:18 GPIO57 peripheral mux configuration in the low 2 bits
    Uint32 GPIO58:2;                    // 21:20 GPIO58 peripheral mux configuration in the low 2 bits
    Uint32 GPIO59:2;                    // 23:22 GPIO59 peripheral mux configuration in the low 2 bits
    Uint32 rsvd1:2;                     // 25:24 Reserved
    Uint32 rsvd2:2;                     // 27:26 Reserved
    Uint32 rsvd3:2;                     // 29:28 Reserved
    Uint32 rsvd4:2;                     // 31:30 Reserved
};

union GPBMUX2_REG {
    Uint32  all;
    struct  GPBMUX2_BITS  bit;
};

struct GPBDIR_BITS {                 // bits description
    Uint32 GPIO32:1;                    // 0 GPIO32 Data direction
    Uint32 GPIO33:1;                    // 1 GPIO33 Data direction
    Uint32 GPIO34:1;                    // 2 GPIO34 Data direction
    Uint32 GPIO35:1;                    // 3 GPIO35 Data direction
    Uint32 rsvd1:1;                    // 4 Reserved
    Uint32 GPIO37:1;                    // 5 GPIO37 Data direction
    Uint32 rsvd2:1;                    // 6 Reserved
    Uint32 GPIO39:1;                    // 7 GPIO39 Data direction
    Uint32 GPIO40:1;                    // 8 GPIO40 Data direction
    Uint32 GPIO41:1;                    // 9 GPIO41 Data direction
    Uint32 GPIO42:1;                    // 10 GPIO42 Data direction
    Uint32 GPIO43:1;                    // 11 GPIO43 Data direction
    Uint32 GPIO44:1;                    // 12 GPIO44 Data direction
    Uint32 GPIO45:1;                    // 13 GPIO45 Data direction
    Uint32 GPIO46:1;                    // 14 GPIO46 Data direction
    Uint32 GPIO47:1;                    // 15 GPIO47 Data direction
    Uint32 GPIO48:1;                    // 16 GPIO48 Data direction
    Uint32 GPIO49:1;                    // 17 GPIO49 Data direction
    Uint32 GPIO50:1;                    // 18 GPIO50 Data direction
    Uint32 GPIO51:1;                    // 19 GPIO51 Data direction
    Uint32 GPIO52:1;                    // 20 GPIO52 Data direction
    Uint32 GPIO53:1;                    // 21 GPIO53 Data direction
    Uint32 GPIO54:1;                    // 22 GPIO54 Data direction
    Uint32 GPIO55:1;                    // 23 GPIO55 Data direction
    Uint32 GPIO56:1;                    // 24 GPIO56 Data direction
    Uint32 GPIO57:1;                    // 25 GPIO57 Data direction
    Uint32 GPIO58:1;                    // 26 GPIO58 Data direction
    Uint32 GPIO59:1;                    // 27 GPIO59 Data direction
    Uint32 rsvd3:1;                    // 28 Reserved
    Uint32 rsvd4:1;                    // 29 Reserved
    Uint32 rsvd5:1;                    // 30 Reserved
    Uint32 rsvd6:1;                    // 31 Reserved
};

union GPBDIR_REG {
    Uint32  all;
    struct  GPBDIR_BITS  bit;
};

struct GPBPUD_BITS {                 // bits description
    Uint32 GPIO32:1;                    // 0 GPIO32 Pull-up disable
    Uint32 GPIO33:1;                    // 1 GPIO33 Pull-up disable
    Uint32 GPIO34:1;                    // 2 GPIO34 Pull-up disable
    Uint32 GPIO35:1;                    // 3 GPIO35 Pull-up disable
    Uint32 rsvd1:1;                    // 4 Reserved
    Uint32 GPIO37:1;                    // 5 GPIO37 Pull-up disable
    Uint32 rsvd2:1;                    // 6 Reserved
    Uint32 GPIO39:1;                    // 7 GPIO39 Pull-up disable
    Uint32 GPIO40:1;                    // 8 GPIO40 Pull-up disable
    Uint32 GPIO41:1;                    // 9 GPIO41 Pull-up disable
    Uint32 GPIO42:1;                    // 10 GPIO42 Pull-up disable
    Uint32 GPIO43:1;                    // 11 GPIO43 Pull-up disable
    Uint32 GPIO44:1;                    // 12 GPIO44 Pull-up disable
    Uint32 GPIO45:1;                    // 13 GPIO45 Pull-up disable
    Uint32 GPIO46:1;                    // 14 GPIO46 Pull-up disable
    Uint32 GPIO47:1;                    // 15 GPIO47 Pull-up disable
    Uint32 GPIO48:1;                    // 16 GPIO48 Pull-up disable
    Uint32 GPIO49:1;                    // 17 GPIO49 Pull-up disable
    Uint32 GPIO50:1;                    // 18 GPIO50 Pull-up disable
    Uint32 GPIO51:1;                    // 19 GPIO51 Pull-up disable
    Uint32 GPIO52:1;                    // 20 GPIO52 Pull-up disable
    Uint32 GPIO53:1;                    // 21 GPIO53 Pull-up disable
    Uint32 GPIO54:1;                    // 22 GPIO54 Pull-up disable
    Uint32 GPIO55:1;                    // 23 GPIO55 Pull-up disable
    Uint32 GPIO56:1;                    // 24 GPIO56 Pull-up disable
    Uint32 GPIO57:1;                    // 25 GPIO57 Pull-up disable
    Uint32 GPIO58:1;                    // 26 GPIO58 Pull-up disable
    Uint32 GPIO59:1;                    // 27 GPIO59 Pull-up disable
    Uint32 rsvd3:1;                    // 28 Reserved
    Uint32 rsvd4:1;                    // 29 Reserved
    Uint32 rsvd5:1;                    // 30 Reserved
    Uint32 rsvd6:1;                    // 31 Reserved
};

union GPBPUD_REG {
    Uint32  all;
    struct  GPBPUD_BITS  bit;
};

struct GPBINV_BITS {                 // bits description
    Uint32 GPIO32:1;                    // 0 GPIO32 Input inversion
    Uint32 GPIO33:1;                    // 1 GPIO33 Input inversion
    Uint32 GPIO34:1;                    // 2 GPIO34 Input inversion
    Uint32 GPIO35:1;                    // 3 GPIO35 Input inversion
    Uint32 rsvd1:1;                      // 4 Reserved
    Uint32 GPIO37:1;                    // 5 GPIO37 Input inversion
    Uint32 rsvd2:1;                      // 6 Reserved
    Uint32 GPIO39:1;                    // 7 GPIO39 Input inversion
    Uint32 GPIO40:1;                    // 8 GPIO40 Input inversion
    Uint32 GPIO41:1;                    // 9 GPIO41 Input inversion
    Uint32 GPIO42:1;                    // 10 GPIO42 Input inversion
    Uint32 GPIO43:1;                    // 11 GPIO43 Input inversion
    Uint32 GPIO44:1;                    // 12 GPIO44 Input inversion
    Uint32 GPIO45:1;                    // 13 GPIO45 Input inversion
    Uint32 GPIO46:1;                    // 14 GPIO46 Input inversion
    Uint32 GPIO47:1;                    // 15 GPIO47 Input inversion
    Uint32 GPIO48:1;                    // 16 GPIO48 Input inversion
    Uint32 GPIO49:1;                    // 17 GPIO49 Input inversion
    Uint32 GPIO50:1;                    // 18 GPIO50 Input inversion
    Uint32 GPIO51:1;                    // 19 GPIO51 Input inversion
    Uint32 GPIO52:1;                    // 20 GPIO52 Input inversion
    Uint32 GPIO53:1;                    // 21 GPIO53 Input inversion
    Uint32 GPIO54:1;                    // 22 GPIO54 Input inversion
    Uint32 GPIO55:1;                    // 23 GPIO55 Input inversion
    Uint32 GPIO56:1;                    // 24 GPIO56 Input inversion
    Uint32 GPIO57:1;                    // 25 GPIO57 Input inversion
    Uint32 GPIO58:1;                    // 26 GPIO58 Input inversion
    Uint32 GPIO59:1;                    // 27 GPIO59 Input inversion
    Uint32 rsvd3:1;                      // 28 Reserved
    Uint32 rsvd4:1;                      // 29 Reserved
    Uint32 rsvd5:1;                      // 30 Reserved
    Uint32 rsvd6:1;                      // 31 Reserved
};

union GPBINV_REG {
    Uint32  all;
    struct  GPBINV_BITS  bit;
};

struct GPBODR_BITS {                 // bits description
    Uint32 GPIO32:1;                    // 0 GPIO32 Open-drain output mode
    Uint32 GPIO33:1;                    // 1 GPIO33 Open-drain output mode
    Uint32 GPIO34:1;                    // 2 GPIO34 Open-drain output mode
    Uint32 GPIO35:1;                    // 3 GPIO35 Open-drain output mode
    Uint32 rsvd1:1;                     // 4 Reserved
    Uint32 GPIO37:1;                    // 5 GPIO37 Open-drain output mode
    Uint32 rsvd2:1;                     // 6 Reserved
    Uint32 GPIO39:1;                    // 7 GPIO39 Open-drain output mode
    Uint32 GPIO40:1;                    // 8 GPIO40 Open-drain output mode
    Uint32 GPIO41:1;                    // 9 GPIO41 Open-drain output mode
    Uint32 GPIO42:1;                    // 10 GPIO42 Open-drain output mode
    Uint32 GPIO43:1;                    // 11 GPIO43 Open-drain output mode
    Uint32 GPIO44:1;                    // 12 GPIO44 Open-drain output mode
    Uint32 GPIO45:1;                    // 13 GPIO45 Open-drain output mode
    Uint32 GPIO46:1;                    // 14 GPIO46 Open-drain output mode
    Uint32 GPIO47:1;                    // 15 GPIO47 Open-drain output mode
    Uint32 GPIO48:1;                    // 16 GPIO48 Open-drain output mode
    Uint32 GPIO49:1;                    // 17 GPIO49 Open-drain output mode
    Uint32 GPIO50:1;                    // 18 GPIO50 Open-drain output mode
    Uint32 GPIO51:1;                    // 19 GPIO51 Open-drain output mode
    Uint32 GPIO52:1;                    // 20 GPIO52 Open-drain output mode
    Uint32 GPIO53:1;                    // 21 GPIO53 Open-drain output mode
    Uint32 GPIO54:1;                    // 22 GPIO54 Open-drain output mode
    Uint32 GPIO55:1;                    // 23 GPIO55 Open-drain output mode
    Uint32 GPIO56:1;                    // 24 GPIO56 Open-drain output mode
    Uint32 GPIO57:1;                    // 25 GPIO57 Open-drain output mode
    Uint32 GPIO58:1;                    // 26 GPIO58 Open-drain output mode
    Uint32 GPIO59:1;                    // 27 GPIO59 Open-drain output mode
    Uint32 rsvd3:1;                     // 28 Reserved
    Uint32 rsvd4:1;                     // 29 Reserved
    Uint32 rsvd5:1;                     // 30 Reserved
    Uint32 rsvd6:1;                     // 31 Reserved
};

union GPBODR_REG {
    Uint32  all;
    struct  GPBODR_BITS  bit;
};

struct GPBDSEL1_BITS {                 // bits description
    Uint32 GPIO32:2;                    // 0 GPIO32 
    Uint32 GPIO33:2;                    // 1 GPIO33 
    Uint32 GPIO34:2;                    // 2 GPIO34 
    Uint32 GPIO35:2;                    // 3 GPIO35 
    Uint32 rsvd1:2;                     // 4 Reserved
    Uint32 GPIO37:2;                    // 5 GPIO37 
    Uint32 rsvd2:2;                     // 6 Reserved
    Uint32 GPIO39:2;                    // 7 GPIO39 
    Uint32 GPIO40:2;                    // 8 GPIO40 
    Uint32 GPIO41:2;                    // 9 GPIO41 
    Uint32 GPIO42:2;                    // 10 GPIO42 
    Uint32 GPIO43:2;                    // 11 GPIO43 
    Uint32 GPIO44:2;                    // 12 GPIO44 
    Uint32 GPIO45:2;                    // 13 GPIO45 
    Uint32 GPIO46:2;                    // 14 GPIO46 
    Uint32 GPIO47:2;                    // 15 GPIO47 
};

union GPBDSEL1_REG {
    Uint32  all;
    struct  GPBDSEL1_BITS  bit;
};

struct GPBDSEL2_BITS {                 // bits description
    Uint32 GPIO48:2;                    // 16 GPIO48 
    Uint32 GPIO49:2;                    // 17 GPIO49 
    Uint32 GPIO50:2;                    // 18 GPIO50 
    Uint32 GPIO51:2;                    // 19 GPIO51 
    Uint32 GPIO52:2;                    // 20 GPIO52 
    Uint32 GPIO53:2;                    // 21 GPIO53 
    Uint32 GPIO54:2;                    // 22 GPIO54 
    Uint32 GPIO55:2;                    // 23 GPIO55 
    Uint32 GPIO56:2;                    // 24 GPIO56 
    Uint32 GPIO57:2;                    // 25 GPIO57 
    Uint32 GPIO58:2;                    // 26 GPIO58 
    Uint32 GPIO59:2;                    // 27 GPIO59 
    Uint32 rsvd3:2;                     // 28 Reserved
    Uint32 rsvd4:2;                     // 29 Reserved
    Uint32 rsvd5:2;                     // 30 Reserved
    Uint32 rsvd6:2;                     // 31 Reserved
};

union GPBDSEL2_REG {
    Uint32  all;
    struct  GPBDSEL2_BITS  bit;
};

struct GPBFEN_BITS {                 // bits description
    Uint32 GPIO32:1;                    // 0 GPIO32 
    Uint32 GPIO33:1;                    // 1 GPIO33 
    Uint32 GPIO34:1;                    // 2 GPIO34 
    Uint32 GPIO35:1;                    // 3 GPIO35 
    Uint32 rsvd1:1;                     // 4 Reserved
    Uint32 GPIO37:1;                    // 5 GPIO37 
    Uint32 rsvd2:1;                     // 6 Reserved
    Uint32 GPIO39:1;                    // 7 GPIO39 
    Uint32 GPIO40:1;                    // 8 GPIO40 
    Uint32 GPIO41:1;                    // 9 GPIO41 
    Uint32 GPIO42:1;                    // 10 GPIO42 
    Uint32 GPIO43:1;                    // 11 GPIO43 
    Uint32 GPIO44:1;                    // 12 GPIO44 
    Uint32 GPIO45:1;                    // 13 GPIO45 
    Uint32 GPIO46:1;                    // 14 GPIO46 
    Uint32 GPIO47:1;                    // 15 GPIO47 
    Uint32 GPIO48:1;                    // 16 GPIO48 
    Uint32 GPIO49:1;                    // 17 GPIO49 
    Uint32 GPIO50:1;                    // 18 GPIO50 
    Uint32 GPIO51:1;                    // 19 GPIO51 
    Uint32 GPIO52:1;                    // 20 GPIO52 
    Uint32 GPIO53:1;                    // 21 GPIO53 
    Uint32 GPIO54:1;                    // 22 GPIO54 
    Uint32 GPIO55:1;                    // 23 GPIO55 
    Uint32 GPIO56:1;                    // 24 GPIO56 
    Uint32 GPIO57:1;                    // 25 GPIO57 
    Uint32 GPIO58:1;                    // 26 GPIO58 
    Uint32 GPIO59:1;                    // 27 GPIO59 
    Uint32 rsvd3:1;                     // 28 Reserved
    Uint32 rsvd4:1;                     // 29 Reserved
    Uint32 rsvd5:1;                     // 30 Reserved
    Uint32 rsvd6:1;                     // 31 Reserved
};

union GPBFEN_REG {
    Uint32  all;
    struct  GPBFEN_BITS  bit;
};

struct GPBGMUX1_BITS {                  // bits description
    Uint32 GPIO32:2;                    // 1:0 GPIO32 peripheral mux configuration in the High 2 bits
    Uint32 GPIO33:2;                    // 3:2 GPIO33 peripheral mux configuration in the High 2 bits
    Uint32 GPIO34:2;                    // 5:4 GPIO34 peripheral mux configuration in the High 2 bits
    Uint32 GPIO35:2;                    // 7:6 GPIO35 peripheral mux configuration in the High 2 bits
    Uint32 rsvd1:2;                     // 9:8 Reserved
    Uint32 GPIO37:2;                    // 11:10 GPIO37 peripheral mux configuration in the High 2 bits
    Uint32 rsvd2:2;                     // 13:12 Reserved
    Uint32 GPIO39:2;                    // 15:14 GPIO39 peripheral mux configuration in the High 2 bits
    Uint32 GPIO40:2;                    // 17:16 GPIO40 peripheral mux configuration in the High 2 bits
    Uint32 GPIO41:2;                    // 19:18 GPIO41 peripheral mux configuration in the High 2 bits
    Uint32 GPIO42:2;                    // 21:20 GPIO42 peripheral mux configuration in the High 2 bits
    Uint32 GPIO43:2;                    // 23:22 GPIO43 peripheral mux configuration in the High 2 bits
    Uint32 GPIO44:2;                    // 25:24 GPIO44 peripheral mux configuration in the High 2 bits
    Uint32 GPIO45:2;                    // 27:26 GPIO45 peripheral mux configuration in the High 2 bits
    Uint32 GPIO46:2;                    // 29:28 GPIO46 peripheral mux configuration in the High 2 bits
    Uint32 GPIO47:2;                    // 31:30 GPIO47 peripheral mux configuration in the High 2 bits
};

union GPBGMUX1_REG {
    Uint32  all;
    struct  GPBGMUX1_BITS  bit;
};

struct GPBGMUX2_BITS {                  // bits description
    Uint32 GPIO48:2;                    // 1:0 GPIO48 peripheral mux configuration in the High 2 bits
    Uint32 GPIO49:2;                    // 3:2 GPIO49 peripheral mux configuration in the High 2 bits
    Uint32 GPIO50:2;                    // 5:4 GPIO50 peripheral mux configuration in the High 2 bits
    Uint32 GPIO51:2;                    // 7:6 GPIO51 peripheral mux configuration in the High 2 bits
    Uint32 GPIO52:2;                    // 9:8 GPIO52 peripheral mux configuration in the High 2 bits
    Uint32 GPIO53:2;                    // 11:10 GPIO53 peripheral mux configuration in the High 2 bits
    Uint32 GPIO54:2;                    // 13:12 GPIO54 peripheral mux configuration in the High 2 bits
    Uint32 GPIO55:2;                    // 15:14 GPIO55 peripheral mux configuration in the High 2 bits
    Uint32 GPIO56:2;                    // 17:16 GPIO56 peripheral mux configuration in the High 2 bits
    Uint32 GPIO57:2;                    // 19:18 GPIO57 peripheral mux configuration in the High 2 bits
    Uint32 GPIO58:2;                    // 21:20 GPIO58 peripheral mux configuration in the High 2 bits
    Uint32 GPIO59:2;                    // 23:22 GPIO59 peripheral mux configuration in the High 2 bits
    Uint32 rsvd1:2;                     // 25:24 Reserved
    Uint32 rsvd2:2;                     // 27:26 Reserved
    Uint32 rsvd3:2;                     // 29:28 Reserved
    Uint32 rsvd4:2;                     // 31:30 Reserved
};

union GPBGMUX2_REG {
    Uint32  all;
    struct  GPBGMUX2_BITS  bit;
};

struct GPBCSEL1_BITS {                // bits description
    Uint32 GPIO32:4;                    // 3:0 GPIO32 Master core select
    Uint32 GPIO33:4;                    // 7:4 GPIO33 Master core Select
    Uint32 GPIO34:4;                    // 11:8 GPIO34 Master core Select
    Uint32 GPIO35:4;                    // 15:12 GPIO35 Master core Select
    Uint32 rsvd1:4;                     // 19:16 Reserved
    Uint32 GPIO37:4;                    // 23:20 GPIO37 Master core Select
    Uint32 rsvd2:4;                     // 27:24 Reserved
    Uint32 GPIO39:4;                    // 31:28 GPIO39 Master core Select
};

union GPBCSEL1_REG {
    Uint32  all;
    struct  GPBCSEL1_BITS  bit;
};

struct GPBCSEL2_BITS {                // bits description
    Uint32 GPIO40:4;                    // 3:0 GPIO40 Master core Select
    Uint32 GPIO41:4;                    // 7:4 GPIO41 Master core Select
    Uint32 GPIO42:4;                    // 11:8 GPIO42 Master core Select
    Uint32 GPIO43:4;                    // 15:12 GPIO43 Master core Select
    Uint32 GPIO44:4;                    // 19:16 GPIO44 Master core Select
    Uint32 GPIO45:4;                    // 23:20 GPIO45 Master core Select
    Uint32 GPIO46:4;                    // 27:24 GPIO46 Master core Select
    Uint32 GPIO47:4;                    // 31:28 GPIO47 Master core Select
};

union GPBCSEL2_REG {
    Uint32  all;
    struct  GPBCSEL2_BITS  bit;
};

struct GPBCSEL3_BITS {                // bits description
    Uint32 GPIO48:4;                    // 3:0 GPIO48 Master core Select
    Uint32 GPIO49:4;                    // 7:4 GPIO49 Master core Select
    Uint32 GPIO50:4;                    // 11:8 GPIO50 Master core Select
    Uint32 GPIO51:4;                    // 15:12 GPIO51 Master core Select
    Uint32 GPIO52:4;                    // 19:16 GPIO52 Master core Select
    Uint32 GPIO53:4;                    // 23:20 GPIO53 Master core Select
    Uint32 GPIO54:4;                    // 27:24 GPIO54 Master core Select
    Uint32 GPIO55:4;                    // 31:28 GPIO55 Master core Select
};

union GPBCSEL3_REG {
    Uint32  all;
    struct  GPBCSEL3_BITS  bit;
};

struct GPBCSEL4_BITS {                // bits description
    Uint32 GPIO56:4;                    // 3:0 GPIO56 Master core Select
    Uint32 GPIO57:4;                    // 7:4 GPIO57 Master core Select
    Uint32 GPIO58:4;                    // 11:8 GPIO58 Master core Select
    Uint32 GPIO59:4;                    // 15:12 GPIO59 Master core Select
    Uint32 rsvd1:4;                     // 19:16 Reserved
    Uint32 rsvd2:4;                     // 23:20 Reserved
    Uint32 rsvd3:4;                     // 27:24 Reserved
    Uint32 rsvd4:4;                     // 31:28 Reserved
};

union GPBCSEL4_REG {
    Uint32  all;
    struct  GPBCSEL4_BITS  bit;
};

struct GPBLOCK_BITS {                   // bits description
    Uint32 GPIO32:1;                    // 0 GPIO32 Configuration lock
    Uint32 GPIO33:1;                    // 1 GPIO33 Configuration lock
    Uint32 GPIO34:1;                    // 2 GPIO34 Configuration lock
    Uint32 GPIO35:1;                    // 3 GPIO35 Configuration lock
    Uint32 rsvd1:1;                     // 4 Reserved
    Uint32 GPIO37:1;                    // 5 GPIO37 Configuration lock
    Uint32 rsvd2:1;                     // 6 Reserved
    Uint32 GPIO39:1;                    // 7 GPIO39 Configuration lock
    Uint32 GPIO40:1;                    // 8 GPIO40 Configuration lock
    Uint32 GPIO41:1;                    // 9 GPIO41 Configuration lock
    Uint32 GPIO42:1;                    // 10 GPIO42 Configuration lock
    Uint32 GPIO43:1;                    // 11 GPIO43 Configuration lock
    Uint32 GPIO44:1;                    // 12 GPIO44 Configuration lock
    Uint32 GPIO45:1;                    // 13 GPIO45 Configuration lock
    Uint32 GPIO46:1;                    // 14 GPIO46 Configuration lock
    Uint32 GPIO47:1;                    // 15 GPIO47 Configuration lock
    Uint32 GPIO48:1;                    // 16 GPIO48 Configuration lock
    Uint32 GPIO49:1;                    // 17 GPIO49 Configuration lock
    Uint32 GPIO50:1;                    // 18 GPIO50 Configuration lock
    Uint32 GPIO51:1;                    // 19 GPIO51 Configuration lock
    Uint32 GPIO52:1;                    // 20 GPIO52 Configuration lock
    Uint32 GPIO53:1;                    // 21 GPIO53 Configuration lock
    Uint32 GPIO54:1;                    // 22 GPIO54 Configuration lock
    Uint32 GPIO55:1;                    // 23 GPIO55 Configuration lock
    Uint32 GPIO56:1;                    // 24 GPIO56 Configuration lock
    Uint32 GPIO57:1;                    // 25 GPIO57 Configuration lock
    Uint32 GPIO58:1;                    // 26 GPIO58 Configuration lock
    Uint32 GPIO59:1;                    // 27 GPIO59 Configuration lock
    Uint32 rsvd3:1;                     // 28 Reserved
    Uint32 rsvd4:1;                     // 29 Reserved
    Uint32 rsvd5:1;                     // 30 Reserved
    Uint32 rsvd6:1;                     // 31 Reserved
};

union GPBLOCK_REG {
    Uint32  all;
    struct  GPBLOCK_BITS  bit;
};

struct GPBCR_BITS {                     // bits description
    Uint32 GPIO32:1;                    // 0 GPIO32 lock is locked
    Uint32 GPIO33:1;                    // 1 GPIO33 lock is locked
    Uint32 GPIO34:1;                    // 2 GPIO34 lock is locked
    Uint32 GPIO35:1;                    // 3 GPIO35 lock is locked
    Uint32 rsvd1:1;                     // 4 Reserved
    Uint32 GPIO37:1;                    // 5 GPIO37 lock is locked
    Uint32 rsvd2:1;                     // 6 Reserved
    Uint32 GPIO39:1;                    // 7 GPIO39 lock is locked
    Uint32 GPIO40:1;                    // 8 GPIO40 lock is locked
    Uint32 GPIO41:1;                    // 9 GPIO41 lock is locked
    Uint32 GPIO42:1;                    // 10 GPIO42 lock is locked
    Uint32 GPIO43:1;                    // 11 GPIO43 lock is locked
    Uint32 GPIO44:1;                    // 12 GPIO44 lock is locked
    Uint32 GPIO45:1;                    // 13 GPIO45 lock is locked
    Uint32 GPIO46:1;                    // 14 GPIO46 lock is locked
    Uint32 GPIO47:1;                    // 15 GPIO47 lock is locked
    Uint32 GPIO48:1;                    // 16 GPIO48 lock is locked
    Uint32 GPIO49:1;                    // 17 GPIO49 lock is locked
    Uint32 GPIO50:1;                    // 18 GPIO50 lock is locked
    Uint32 GPIO51:1;                    // 19 GPIO51 lock is locked
    Uint32 GPIO52:1;                    // 20 GPIO52 lock is locked
    Uint32 GPIO53:1;                    // 21 GPIO53 lock is locked
    Uint32 GPIO54:1;                    // 22 GPIO54 lock is locked
    Uint32 GPIO55:1;                    // 23 GPIO55 lock is locked
    Uint32 GPIO56:1;                    // 24 GPIO56 lock is locked
    Uint32 GPIO57:1;                    // 25 GPIO57 lock is locked
    Uint32 GPIO58:1;                    // 26 GPIO58 lock is locked
    Uint32 GPIO59:1;                    // 27 GPIO59 lock is locked
    Uint32 rsvd3:1;                     // 28 Reserved
    Uint32 rsvd4:1;                     // 29 Reserved
    Uint32 rsvd5:1;                     // 30 Reserved
    Uint32 rsvd6:1;                     // 31 Reserved
};

union GPBCR_REG {
    Uint32  all;
    struct  GPBCR_BITS  bit;
};

struct GPHCTRL_BITS {              // bits description
    Uint32 QUALPRD0:8;                  // 7:0 GPIO224 to GPIO231 sampling cycle
    Uint32 QUALPRD1:8;                  // 15:8 GPIO232 to GPIO239 sampling cycle
    Uint32 QUALPRD2:8;                  // 23:16 GPIO240 to GPIO247 sampling cycle
    Uint32 QUALPRD3:8;                  // 31:24 GPIO248 to GPIO254 sampling cycle
};

union GPHCTRL_REG {
    Uint32  all;
    struct  GPHCTRL_BITS  bit;
};

struct GPHQSEL1_BITS {                // bits description
    Uint32 GPIO224:2;                   // 1:0 GPIO224 Input  type
    Uint32 GPIO225:2;                   // 3:2 GPIO225 Input  type
    Uint32 GPIO226:2;                   // 5:4 GPIO226 Input  type
    Uint32 GPIO227:2;                   // 7:6 GPIO227 Input  type
    Uint32 GPIO228:2;                   // 9:8 GPIO228 Input  type
    Uint32 GPIO229:2;                   // 11:10 GPIO229 Input  type
    Uint32 GPIO230:2;                   // 13:12 GPIO230 Input  type
    Uint32 GPIO231:2;                   // 15:14 GPIO231 Input  type
    Uint32 GPIO232:2;                   // 17:16 GPIO232 Input  type
    Uint32 GPIO233:2;                   // 19:18 GPIO233 Input  type
    Uint32 GPIO234:2;                   // 21:20 GPIO234 Input  type
    Uint32 GPIO235:2;                   // 23:22 GPIO235 Input  type
    Uint32 GPIO236:2;                   // 25:24 GPIO236 Input  type
    Uint32 GPIO237:2;                   // 27:26 GPIO237 Input  type
    Uint32 GPIO238:2;                   // 29:28 GPIO238 Input  type
    Uint32 GPIO239:2;                   // 31:30 GPIO239 Input  type
};

union GPHQSEL1_REG {
    Uint32  all;
    struct  GPHQSEL1_BITS  bit;
};

struct GPHQSEL2_BITS {                  // bits description
    Uint32 GPIO240:2;                   // 1:0 GPIO240 Input  type
    Uint32 GPIO241:2;                   // 3:2 GPIO241 Input  type
    Uint32 GPIO242:2;                   // 5:4 GPIO242 Input  type
    Uint32 GPIO243:2;                   // 7:6 GPIO243 Input  type
    Uint32 GPIO244:2;                   // 9:8 GPIO244 Input  type
    Uint32 GPIO245:2;                   // 11:10 GPIO245 Input  type
    Uint32 GPIO246:2;                   // 13:12 GPIO246 Input  type
    Uint32 GPIO247:2;                   // 15:14 GPIO247 Input  type
    Uint32 GPIO248:2;                   // 17:16 GPIO248 Input  type
    Uint32 GPIO249:2;                   // 19:18 GPIO249 Input  type
    Uint32 GPIO250:2;                   // 21:20 GPIO250 Input  type
    Uint32 GPIO251:2;                   // 23:22 GPIO251 Input  type
    Uint32 GPIO252:2;                   // 25:24 GPIO252 Input  type
    Uint32 GPIO253:2;                   // 27:26 GPIO253 Input  type
    Uint32 GPIO254:2;                   // 29:28 GPIO254 Input  type
    Uint32 rsvd8:2;                     // 31:30 Reserved
};

union GPHQSEL2_REG {
    Uint32  all;
    struct  GPHQSEL2_BITS  bit;
};

struct GPHPUD_BITS {                 // bits description
    Uint32 GPIO224:1;                   // 0 GPIO224 Pull-up disable
    Uint32 GPIO225:1;                   // 1 GPIO225 Pull-up disable
    Uint32 GPIO226:1;                   // 2 GPIO226 Pull-up disable
    Uint32 GPIO227:1;                   // 3 GPIO227 Pull-up disable
    Uint32 GPIO228:1;                   // 4 GPIO228 Pull-up disable
    Uint32 GPIO229:1;                   // 5 GPIO229 Pull-up disable
    Uint32 GPIO230:1;                   // 6 GPIO230 Pull-up disable
    Uint32 GPIO231:1;                   // 7 GPIO231 Pull-up disable
    Uint32 GPIO232:1;                   // 8 GPIO232 Pull-up disable
    Uint32 GPIO233:1;                   // 9 GPIO233 Pull-up disable
    Uint32 GPIO234:1;                   // 10 GPIO234 Pull-up disable
    Uint32 GPIO235:1;                   // 11 GPIO235 Pull-up disable
    Uint32 GPIO236:1;                   // 12 GPIO236 Pull-up disable
    Uint32 GPIO237:1;                   // 13 GPIO237 Pull-up disable
    Uint32 GPIO238:1;                   // 14 GPIO238 Pull-up disable
    Uint32 GPIO239:1;                   // 15 GPIO239 Pull-up disable
    Uint32 GPIO240:1;                   // 16 GPIO240 Pull-up disable
    Uint32 GPIO241:1;                   // 17 GPIO241 Pull-up disable
    Uint32 GPIO242:1;                   // 18 GPIO242 Pull-up disable
    Uint32 GPIO243:1;                   // 19 GPIO243 Pull-up disable
    Uint32 GPIO244:1;                   // 20 GPIO244 Pull-up disable
    Uint32 GPIO245:1;                   // 21 GPIO245 Pull-up disable
    Uint32 GPIO246:1;                   // 22 GPIO246 Pull-up disable
    Uint32 GPIO247:1;                   // 23 GPIO247 Pull-up disable
    Uint32 GPIO248:1;                   // 24 GPIO248 Pull-up disable
    Uint32 GPIO249:1;                   // 25 GPIO249 Pull-up disable
    Uint32 GPIO250:1;                   // 26 GPIO250 Pull-up disable
    Uint32 GPIO251:1;                   // 27 GPIO251 Pull-up disable
    Uint32 GPIO252:1;                   // 28 GPIO252 Pull-up disable
    Uint32 GPIO253:1;                   // 29 GPIO253 Pull-up disable
    Uint32 GPIO254:1;                   // 30 GPIO254 Pull-up disable
    Uint32 rsvd8:1;                    // 31 Reserved
};

union GPHPUD_REG {
    Uint32  all;
    struct  GPHPUD_BITS  bit;
};

struct GPHINV_BITS {                    // bits description
    Uint32 GPIO224:1;                   // 0 GPIO224 Input inversion
    Uint32 GPIO225:1;                   // 1 GPIO225 Input inversion
    Uint32 GPIO226:1;                   // 2 GPIO226 Input inversion
    Uint32 GPIO227:1;                   // 3 GPIO226 Input inversion
    Uint32 GPIO228:1;                   // 4 GPIO228 Input inversion
    Uint32 GPIO229:1;                   // 5 GPIO229 Input inversion
    Uint32 GPIO230:1;                   // 6 GPIO230 Input inversion
    Uint32 GPIO231:1;                   // 7 GPIO231 Input inversion
    Uint32 GPIO232:1;                   // 8 GPIO232 Input inversion
    Uint32 GPIO233:1;                   // 9 GPIO233 Input inversion
    Uint32 GPIO234:1;                   // 10 GPIO234 Input inversion
    Uint32 GPIO235:1;                   // 11 GPIO235 Input inversion
    Uint32 GPIO236:1;                   // 12 GPIO236 Input inversion
    Uint32 GPIO237:1;                   // 13 GPIO237 Input inversion
    Uint32 GPIO238:1;                   // 14 GPIO238 Input inversion
    Uint32 GPIO239:1;                   // 15 GPIO239 Input inversion
    Uint32 GPIO240:1;                   // 16 GPIO240 Input inversion
    Uint32 GPIO241:1;                   // 17 GPIO241 Input inversion
    Uint32 GPIO242:1;                   // 18 GPIO242 Input inversion
    Uint32 GPIO243:1;                   // 19 GPIO243 Input inversion
    Uint32 GPIO244:1;                   // 20 GPIO244 Input inversion
    Uint32 GPIO245:1;                   // 21 GPIO245 Input inversion
    Uint32 GPIO246:1;                   // 22 GPIO246 Input inversion
    Uint32 GPIO247:1;                   // 23 GPIO247 Input inversion
    Uint32 GPIO248:1;                   // 24 GPIO248 Input inversion
    Uint32 GPIO249:1;                   // 25 GPIO249 Input inversion
    Uint32 GPIO250:1;                   // 26 GPIO250 Input inversion
    Uint32 GPIO251:1;                   // 27 GPIO251 Input inversion
    Uint32 GPIO252:1;                   // 28 GPIO252 Input inversion
    Uint32 GPIO253:1;                   // 29 GPIO253 Input inversion
    Uint32 GPIO254:1;                   // 30 GPIO254 Input inversion
    Uint32 rsvd8:1;                     // 31 Reserved
};

union GPHINV_REG {
    Uint32  all;
    struct  GPHINV_BITS  bit;
};

struct GPHAMSEL_BITS {                  // bits description
    Uint32 GPIO224:1;                   // 0 Analog mode select for GPIO224
    Uint32 GPIO225:1;                   // 1 Analog Mode select for GPIO225
    Uint32 GPIO226:1;                   // 2 Analog Mode select for GPIO226
    Uint32 GPIO227:1;                   // 3 Analog Mode select for GPIO227
    Uint32 GPIO228:1;                   // 4 Analog Mode select for GPIO228
    Uint32 GPIO229:1;                   // 5 Analog Mode select for GPIO229
    Uint32 GPIO230:1;                   // 6 Analog Mode select for GPIO230
    Uint32 GPIO231:1;                   // 7 Analog Mode select for GPIO231
    Uint32 GPIO232:1;                   // 8 Analog Mode select for GPIO232
    Uint32 GPIO233:1;                   // 9 Analog Mode select for GPIO233
    Uint32 GPIO234:1;                   // 10 Analog Mode select for GPIO234
    Uint32 GPIO235:1;                   // 11 Analog Mode select for GPIO235
    Uint32 GPIO236:1;                   // 12 Analog Mode select for GPIO236
    Uint32 GPIO237:1;                   // 13 Analog Mode select for GPIO237
    Uint32 GPIO238:1;                   // 14 Analog Mode select for GPIO238
    Uint32 GPIO239:1;                   // 15 Analog Mode select for GPIO239
    Uint32 GPIO240:1;                   // 16 Analog Mode select for GPIO240
    Uint32 GPIO241:1;                   // 17 Analog Mode select for GPIO241
    Uint32 GPIO242:1;                   // 18 Analog Mode select for GPIO242
    Uint32 GPIO243:1;                   // 19 Analog Mode select for GPIO243
    Uint32 GPIO244:1;                   // 20 Analog Mode select for GPIO244
    Uint32 GPIO245:1;                   // 21 Analog Mode select for GPIO245
    Uint32 GPIO246:1;                   // 22 Analog Mode select for GPIO246
    Uint32 GPIO247:1;                   // 23 Analog Mode select for GPIO247
    Uint32 GPIO248:1;                   // 24 Analog Mode select for GPIO248
    Uint32 GPIO249:1;                   // 25 Analog Mode select for GPIO249
    Uint32 GPIO250:1;                   // 26 Analog Mode select for GPIO250
    Uint32 GPIO251:1;                   // 27 Analog Mode select for GPIO251
    Uint32 GPIO252:1;                   // 28 Analog Mode select for GPIO252
    Uint32 GPIO253:1;                   // 29 Analog Mode select for GPIO253
    Uint32 GPIO254:1;                   // 30 Analog Mode select for GPIO254
    Uint32 rsvd8:1;                     // 31 Reserved
};

union GPHAMSEL_REG {
    Uint32  all;
    struct  GPHAMSEL_BITS  bit;
};

struct GPHLOCK_BITS {                   // bits description
    Uint32 GPIO224:1;                   // 0 GPIO224 Configuration lock
    Uint32 GPIO225:1;                   // 1 GPIO225 Configuration lock
    Uint32 GPIO226:1;                   // 2 GPIO226 Configuration lock
    Uint32 GPIO227:1;                   // 3 GPIO227 Configuration lock
    Uint32 GPIO228:1;                   // 4 GPIO228 Configuration lock
    Uint32 GPIO229:1;                   // 5 GPIO229 Configuration lock
    Uint32 GPIO230:1;                   // 6 GPIO230 Configuration lock
    Uint32 GPIO231:1;                   // 7 GPIO231 Configuration lock
    Uint32 GPIO232:1;                   // 8 GPIO232 Configuration lock
    Uint32 GPIO233:1;                   // 9 GPIO233 Configuration lock
    Uint32 GPIO234:1;                   // 10 GPIO234 Configuration lock
    Uint32 GPIO235:1;                   // 11 GPIO235 Configuration lock
    Uint32 GPIO236:1;                   // 12 GPIO236 Configuration lock
    Uint32 GPIO237:1;                   // 13 GPIO237 Configuration lock
    Uint32 GPIO238:1;                   // 14 GPIO238 Configuration lock
    Uint32 GPIO239:1;                   // 15 GPIO239 Configuration lock
    Uint32 GPIO240:1;                   // 16 GPIO240 Configuration lock
    Uint32 GPIO241:1;                   // 17 GPIO241 Configuration lock
    Uint32 GPIO242:1;                   // 18 GPIO242 Configuration lock
    Uint32 GPIO243:1;                   // 19 GPIO243 Configuration lock
    Uint32 GPIO244:1;                   // 20 GPIO244 Configuration lock
    Uint32 GPIO245:1;                   // 21 GPIO245 Configuration lock
    Uint32 GPIO246:1;                   // 22 GPIO246 Configuration lock
    Uint32 GPIO247:1;                   // 23 GPIO247 Configuration lock
    Uint32 GPIO248:1;                   // 24 GPIO248 Configuration lock
    Uint32 GPIO249:1;                   // 25 GPIO249 Configuration lock
    Uint32 GPIO250:1;                   // 26 GPIO250 Configuration lock
    Uint32 GPIO251:1;                   // 27 GPIO251 Configuration lock
    Uint32 GPIO252:1;                   // 28 GPIO252 Configuration lock
    Uint32 GPIO253:1;                   // 29 GPIO253 Configuration lock
    Uint32 GPIO254:1;                   // 30 GPIO254 Configuration lock
    Uint32 rsvd8:1;                     // 31 Reserved
};

union GPHLOCK_REG {
    Uint32  all;
    struct  GPHLOCK_BITS  bit;
};

struct GPHCR_BITS {                // bits description
    Uint32 GPIO224:1;                   // 0 GPIO224 lock is locked
    Uint32 GPIO225:1;                   // 1 GPIO225 lock is locked
    Uint32 GPIO226:1;                   // 2 GPIO226 lock is locked
    Uint32 GPIO227:1;                   // 3 GPIO227 lock is locked
    Uint32 GPIO228:1;                   // 4 GPIO228 lock is locked
    Uint32 GPIO229:1;                   // 5 GPIO229 lock is locked
    Uint32 GPIO230:1;                   // 6 GPIO230 lock is locked
    Uint32 GPIO231:1;                   // 7 GPIO231 lock is locked
    Uint32 GPIO232:1;                   // 8 GPIO232 lock is locked
    Uint32 GPIO233:1;                   // 9 GPIO233 lock is locked
    Uint32 GPIO234:1;                   // 10 GPIO234 lock is locked
    Uint32 GPIO235:1;                   // 11 GPIO235 lock is locked
    Uint32 GPIO236:1;                   // 12 GPIO236 lock is locked
    Uint32 GPIO237:1;                   // 13 GPIO237 lock is locked
    Uint32 GPIO238:1;                   // 14 GPIO238 lock is locked
    Uint32 GPIO239:1;                   // 15 GPIO239 lock is locked
    Uint32 GPIO240:1;                   // 16 GPIO240 lock is locked
    Uint32 GPIO241:1;                   // 17 GPIO241 lock is locked
    Uint32 GPIO242:1;                   // 18 GPIO242 lock is locked
    Uint32 GPIO243:1;                   // 19 GPIO243 lock is locked
    Uint32 GPIO244:1;                   // 20 GPIO244 lock is locked
    Uint32 GPIO245:1;                   // 21 GPIO245 lock is locked
    Uint32 GPIO246:1;                   // 22 GPIO246 lock is locked
    Uint32 GPIO247:1;                   // 23 GPIO247 lock is locked
    Uint32 GPIO248:1;                   // 24 GPIO248 lock is locked
    Uint32 GPIO249:1;                   // 25 GPIO249 lock is locked
    Uint32 GPIO250:1;                   // 26 GPIO250 lock is locked
    Uint32 GPIO251:1;                   // 27 GPIO251 lock is locked
    Uint32 GPIO252:1;                   // 28 GPIO252 lock is locked
    Uint32 GPIO253:1;                   // 29 GPIO253 lock is locked
    Uint32 GPIO254:1;                   // 30 GPIO254 lock is locked
    Uint32 rsvd8:1;                     // 31 Reserved
};

union GPHCR_REG {
    Uint32  all;
    struct  GPHCR_BITS  bit;
};

struct GPIO_CTRL_REGS {
    union   GPACTRL_REG                      GPACTRL;                      // GPIO A Qualification Sampling Period (GPIO0 to GPIO31)
    union   GPAQSEL1_REG                     GPAQSEL1;                     // GPIO A Qualification Type (GPIO0 to GPIO15)
    union   GPAQSEL2_REG                     GPAQSEL2;                     // GPIO A Qualification Type (GPIO16 to GPIO31)
    union   GPAMUX1_REG                      GPAMUX1;                      // GPIO A Peripheral Mux (GPIO0 to GPIO15)
    union   GPAMUX2_REG                      GPAMUX2;                      // GPIO A Peripheral Mux (GPIO16 to GPIO31)
    union   GPADIR_REG                       GPADIR;                       // GPIO A Direction (GPIO0 to GPIO31)
    union   GPAPUD_REG                       GPAPUD;                       // GPIO A Pull-Up Disable (GPIO0 to GPIO31)
    Uint16                                   rsvd1[2];                     // Reserved
    union   GPAINV_REG                       GPAINV;                       // GPIO A Input Inversion (GPIO0 to GPIO31)
    union   GPAODR_REG                       GPAODR;                       // GPIO A Open Drain Output Mode (GPIO0 to GPIO31)
    union   GPAAMSEL_REG                     GPAAMSEL;                     // GPIO A Analog Mode Select (GPIO0 to GPIO31)
    union   GPADSEL1_REG                     GPADSEL1;                     // Driver capability select for GPIO A (GPIO0 to GPIO15)
    union   GPADSEL2_REG                     GPADSEL2;                     // Driver capability select for GPIO A ((GPIO16 to GPIO31))
    union   GPAFEN_REG                       GPAFEN;                       // GPIO A Maximum Output Frequency Enable
    Uint16                                   rsvd2[4];                     // Reserved
    union   GPAGMUX1_REG                     GPAGMUX1;                     // GPIO A Peripheral Group Mux (GPIO0 to GPIO15)
    union   GPAGMUX2_REG                     GPAGMUX2;                     // GPIO A Peripheral Group Mux (GPIO16 to GPIO31)
    Uint16                                   rsvd3[4];                     // Reserved
    union   GPACSEL1_REG                     GPACSEL1;                     // GPIO A Master Core Select (GPIO0 to GPIO7)
    union   GPACSEL2_REG                     GPACSEL2;                     // GPIO A Master Core Select (GPIO8 to GPIO15)
    union   GPACSEL3_REG                     GPACSEL3;                     // GPIO A Master Core Select (GPIO16 to GPIO23)
    union   GPACSEL4_REG                     GPACSEL4;                     // GPIO A Master Core Select (GPIO24 to GPIO31)
    Uint16                                   rsvd4[12];                    // Reserved
    union   GPALOCK_REG                      GPALOCK;                      // GPIO A Lock Register (GPIO0 to GPIO31)
    union   GPACR_REG                        GPACR;                        // GPIO A Lock Commit Register (GPIO0 to GPIO31)
    union   GPBCTRL_REG                      GPBCTRL;                      // GPIO B Qualification Sampling Period (GPIO32 to GPIO59)
    union   GPBQSEL1_REG                     GPBQSEL1;                     // GPIO B Qualification Type (GPIO32 to GPIO47)
    union   GPBQSEL2_REG                     GPBQSEL2;                     // GPIO B Qualification Type (GPIO48 to GPIO63)
    union   GPBMUX1_REG                      GPBMUX1;                      // GPIO B Peripheral Mux (GPIO32 to GPIO47)
    union   GPBMUX2_REG                      GPBMUX2;                      // GPIO B Peripheral Mux (GPIO48 to GPIO63)
    union   GPBDIR_REG                       GPBDIR;                       // GPIO B Direction (GPIO32 to GPIO59)
    union   GPBPUD_REG                       GPBPUD;                       // GPIO B Pull-Up Disable (GPIO32 to GPIO59)
    Uint16                                   rsvd5[2];                     // Reserved
    union   GPBINV_REG                       GPBINV;                       // GPIO B Input Inversion (GPIO32 to GPIO59)
    union   GPBODR_REG                       GPBODR;                       // GPIO B Open Drain Output Mode (GPIO32 to GPIO59)
    Uint16                                   rsvd6[2];
    union   GPBDSEL1_REG                     GPBDSEL1;                     // Driver capability select for GPIO B (GPIO32 to GPIO47)
    union   GPBDSEL2_REG                     GPBDSEL2;                     // Driver capability select for GPIO B (GPIO48 to GPIO63)
    union   GPBFEN_REG                       GPBFEN;                       // GPIO B Maximum Output Frequency Enable
    Uint16                                   rsvd7[4];                    // Reserved
    union   GPBGMUX1_REG                     GPBGMUX1;                     // GPIO B Peripheral Group Mux (GPIO32 to GPIO47)
    union   GPBGMUX2_REG                     GPBGMUX2;                     // GPIO B Peripheral Group Mux (GPIO48 to GPIO63)
    Uint16                                   rsvd8[4];                     // Reserved
    union   GPBCSEL1_REG                     GPBCSEL1;                     // GPIO B Master Core Select (GPIO32 to GPIO39)
    union   GPBCSEL2_REG                     GPBCSEL2;                     // GPIO B Master Core Select (GPIO40 to GPIO47)
    union   GPBCSEL3_REG                     GPBCSEL3;                     // GPIO B Master Core Select (GPIO48 to GPIO55)
    union   GPBCSEL4_REG                     GPBCSEL4;                     // GPIO B Master Core Select (GPIO56 to GPIO63)
    Uint16                                   rsvd9[12];                    // Reserved
    union   GPBLOCK_REG                      GPBLOCK;                      // GPIO B Lock Register (GPIO32 to GPIO59)
    union   GPBCR_REG                        GPBCR;                        // GPIO B Lock Commit Register (GPIO32 to GPIO59)
    Uint16                                   rsvd10[320];                   // Reserved
    union   GPHCTRL_REG                      GPHCTRL;                      // GPIO H Qualification Sampling Period (GPIO224 to GPIO255)
    union   GPHQSEL1_REG                     GPHQSEL1;                     // GPIO H Qualification Type (GPIO224 to GPIO239)
    union   GPHQSEL2_REG                     GPHQSEL2;                     // GPIO H Qualification Type (GPIO240 to GPIO255)
    Uint16                                   rsvd11[6];                    // Reserved
    union   GPHPUD_REG                       GPHPUD;                       // GPIO H Pull-Up Disable (GPIO224 to GPIO255)
    Uint16                                   rsvd12[2];                    // Reserved
    union   GPHINV_REG                       GPHINV;                       // GPIO H Input Inversion (GPIO224 to GPIO255)
    Uint16                                   rsvd13[2];                    // Reserved
    union   GPHAMSEL_REG                     GPHAMSEL;                     // GPIO H Analog Mode Select (GPIO224 to GPIO255)
    Uint16                                   rsvd14[38];                   // Reserved
    union   GPHLOCK_REG                     GPHLOCK;                      // GPIO H Lock Register (GPIO224 to GPIO255)
    union   GPHCR_REG                       GPHCR;                        // GPIO H Lock Commit Register (GPIO224 to GPIO255)
};

struct GPADAT_BITS {                 // bits description
    Uint32 GPIO0:1;                     // 0 GPIO0 Read/Write Data Bit
    Uint32 GPIO1:1;                     // 1 GPIO1 Read/Write Data Bit
    Uint32 GPIO2:1;                     // 2 GPIO2 Read/Write Data Bit
    Uint32 GPIO3:1;                     // 3 GPIO3 Read/Write Data Bit
    Uint32 GPIO4:1;                     // 4 GPIO4 Read/Write Data Bit
    Uint32 GPIO5:1;                     // 5 GPIO5 Read/Write Data Bit
    Uint32 GPIO6:1;                     // 6 GPIO6 Read/Write Data Bit
    Uint32 GPIO7:1;                     // 7 GPIO7 Read/Write Data Bit
    Uint32 GPIO8:1;                     // 8 GPIO8 Read/Write Data Bit
    Uint32 GPIO9:1;                     // 9 GPIO9 Read/Write Data Bit
    Uint32 GPIO10:1;                    // 10 GPIO10 Read/Write Data Bit
    Uint32 GPIO11:1;                    // 11 GPIO11 Read/Write Data Bit
    Uint32 GPIO12:1;                    // 12 GPIO12 Read/Write Data Bit
    Uint32 GPIO13:1;                    // 13 GPIO13 Read/Write Data Bit
    Uint32 GPIO14:1;                    // 14 GPIO14 Read/Write Data Bit
    Uint32 GPIO15:1;                    // 15 GPIO15 Read/Write Data Bit
    Uint32 GPIO16:1;                    // 16 GPIO16 Read/Write Data Bit
    Uint32 GPIO17:1;                    // 17 GPIO17 Read/Write Data Bit
    Uint32 GPIO18:1;                    // 18 GPIO18 Read/Write Data Bit
    Uint32 GPIO19:1;                    // 19 GPIO19 Read/Write Data Bit
    Uint32 GPIO20:1;                    // 20 GPIO20 Read/Write Data Bit
    Uint32 GPIO21:1;                    // 21 GPIO21 Read/Write Data Bit
    Uint32 GPIO22:1;                    // 22 GPIO22 Read/Write Data Bit
    Uint32 GPIO23:1;                    // 23 GPIO23 Read/Write Data Bit
    Uint32 GPIO24:1;                    // 24 GPIO24 Read/Write Data Bit
    Uint32 GPIO25:1;                    // 25 GPIO25 Read/Write Data Bit
    Uint32 GPIO26:1;                    // 26 GPIO26 Read/Write Data Bit
    Uint32 GPIO27:1;                    // 27 GPIO27 Read/Write Data Bit
    Uint32 GPIO28:1;                    // 28 GPIO28 Read/Write Data Bit
    Uint32 GPIO29:1;                    // 29 GPIO29 Read/Write Data Bit
    Uint32 GPIO30:1;                    // 30 GPIO30 Read/Write Data Bit
    Uint32 GPIO31:1;                    // 31 GPIO31 Read/Write Data Bit
};

union GPADAT_REG {
    Uint32  all;
    struct  GPADAT_BITS  bit;
};

struct GPASET_BITS {                 // bits description
    Uint32 GPIO0:1;                     // 0 Set the GPIO0 output data latch
    Uint32 GPIO1:1;                     // 1 Set the GPIO1 output data latch
    Uint32 GPIO2:1;                     // 2 Set the GPIO2 output data latch
    Uint32 GPIO3:1;                     // 3 Set the GPIO3 output data latch
    Uint32 GPIO4:1;                     // 4 Set the GPIO4 output data latch
    Uint32 GPIO5:1;                     // 5 Set the GPIO5 output data latch
    Uint32 GPIO6:1;                     // 6 Set the GPIO6 output data latch
    Uint32 GPIO7:1;                     // 7 Set the GPIO7 output data latch
    Uint32 GPIO8:1;                     // 8 Set the GPIO8 output data latch
    Uint32 GPIO9:1;                     // 9 Set the GPIO9 output data latch
    Uint32 GPIO10:1;                    // 10 Set the GPIO10 output data latch
    Uint32 GPIO11:1;                    // 11 Set the GPIO11 output data latch
    Uint32 GPIO12:1;                    // 12 Set the GPIO12 output data latch
    Uint32 GPIO13:1;                    // 13 Set the GPIO13 output data latch
    Uint32 GPIO14:1;                    // 14 Set the GPIO14 output data latch
    Uint32 GPIO15:1;                    // 15 Set the GPIO15 output data latch
    Uint32 GPIO16:1;                    // 16 Set the GPIO16 output data latch
    Uint32 GPIO17:1;                    // 17 Set the GPIO17 output data latch
    Uint32 GPIO18:1;                    // 18 Set the GPIO18 output data latch
    Uint32 GPIO19:1;                    // 19 Set the GPIO19 output data latch
    Uint32 GPIO20:1;                    // 20 Set the GPIO20 output data latch
    Uint32 GPIO21:1;                    // 21 Set the GPIO21 output data latch
    Uint32 GPIO22:1;                    // 22 Set the GPIO22 output data latch
    Uint32 GPIO23:1;                    // 23 Set the GPIO23 output data latch
    Uint32 GPIO24:1;                    // 24 Set the GPIO24 output data latch
    Uint32 GPIO25:1;                    // 25 Set the GPIO25 output data latch
    Uint32 GPIO26:1;                    // 26 Set the GPIO26 output data latch
    Uint32 GPIO27:1;                    // 27 Set the GPIO27 output data latch
    Uint32 GPIO28:1;                    // 28 Set the GPIO28 output data latch
    Uint32 GPIO29:1;                    // 29 Set the GPIO29 output data latch
    Uint32 GPIO30:1;                    // 30 Set the GPIO30 output data latch
    Uint32 GPIO31:1;                    // 31 Set the GPIO31 output data latch
};

union GPASET_REG {
    Uint32  all;
    struct  GPASET_BITS  bit;
};

struct GPACLR_BITS {                  // bits description
    Uint32 GPIO0:1;                     // 0 Clear the GPIO0 output data latch
    Uint32 GPIO1:1;                     // 1 Clear the GPIO1 output data latch
    Uint32 GPIO2:1;                     // 2 Clear the GPIO2 output data latch
    Uint32 GPIO3:1;                     // 3 Clear the GPIO3 output data latch
    Uint32 GPIO4:1;                     // 4 Clear the GPIO4 output data latch
    Uint32 GPIO5:1;                     // 5 Clear the GPIO5 output data latch
    Uint32 GPIO6:1;                     // 6 Clear the GPIO6 output data latch
    Uint32 GPIO7:1;                     // 7 Clear the GPIO7 output data latch
    Uint32 GPIO8:1;                     // 8 Clear the GPIO8 output data latch
    Uint32 GPIO9:1;                     // 9 Clear the GPIO9 output data latch
    Uint32 GPIO10:1;                    // 10 Clear the GPIO10 output data latch
    Uint32 GPIO11:1;                    // 11 Clear the GPIO11 output data latch
    Uint32 GPIO12:1;                    // 12 Clear the GPIO12 output data latch
    Uint32 GPIO13:1;                    // 13 Clear the GPIO13 output data latch
    Uint32 GPIO14:1;                    // 14 Clear the GPIO14 output data latch
    Uint32 GPIO15:1;                    // 15 Clear the GPIO15 output data latch
    Uint32 GPIO16:1;                    // 16 Clear the GPIO16 output data latch
    Uint32 GPIO17:1;                    // 17 Clear the GPIO17 output data latch
    Uint32 GPIO18:1;                    // 18 Clear the GPIO18 output data latch
    Uint32 GPIO19:1;                    // 19 Clear the GPIO19 output data latch
    Uint32 GPIO20:1;                    // 20 Clear the GPIO20 output data latch
    Uint32 GPIO21:1;                    // 21 Clear the GPIO21 output data latch
    Uint32 GPIO22:1;                    // 22 Clear the GPIO22 output data latch
    Uint32 GPIO23:1;                    // 23 Clear the GPIO23 output data latch
    Uint32 GPIO24:1;                    // 24 Clear the GPIO24 output data latch
    Uint32 GPIO25:1;                    // 25 Clear the GPIO25 output data latch
    Uint32 GPIO26:1;                    // 26 Clear the GPIO26 output data latch
    Uint32 GPIO27:1;                    // 27 Clear the GPIO27 output data latch
    Uint32 GPIO28:1;                    // 28 Clear the GPIO28 output data latch
    Uint32 GPIO29:1;                    // 29 Clear the GPIO29 output data latch
    Uint32 GPIO30:1;                    // 30 Clear the GPIO30 output data latch
    Uint32 GPIO31:1;                    // 31 Clear the GPIO31 output data latch
};

union GPACLR_REG {
    Uint32  all;
    struct  GPACLR_BITS  bit;
};

struct GPATOGGLE_BITS {                 // bits description
    Uint32 GPIO0:1;                     // 0 Toggle the GPIO0 output data latch
    Uint32 GPIO1:1;                     // 1 Toggle the GPIO1 output data latch
    Uint32 GPIO2:1;                     // 2 Toggle the GPIO2 output data latch
    Uint32 GPIO3:1;                     // 3 Toggle the GPIO3 output data latch
    Uint32 GPIO4:1;                     // 4 Toggle the GPIO4 output data latch
    Uint32 GPIO5:1;                     // 5 Toggle the GPIO5 output data latch
    Uint32 GPIO6:1;                     // 6 Toggle the GPIO6 output data latch
    Uint32 GPIO7:1;                     // 7 Toggle the GPIO7 output data latch
    Uint32 GPIO8:1;                     // 8 Toggle the GPIO8 output data latch
    Uint32 GPIO9:1;                     // 9 Toggle the GPIO9 output data latch
    Uint32 GPIO10:1;                    // 10 Toggle the GPIO10 output data latch
    Uint32 GPIO11:1;                    // 11 Toggle the GPIO11 output data latch
    Uint32 GPIO12:1;                    // 12 Toggle the GPIO12 output data latch
    Uint32 GPIO13:1;                    // 13 Toggle the GPIO13 output data latch
    Uint32 GPIO14:1;                    // 14 Toggle the GPIO14 output data latch
    Uint32 GPIO15:1;                    // 15 Toggle the GPIO15 output data latch
    Uint32 GPIO16:1;                    // 16 Toggle the GPIO16 output data latch
    Uint32 GPIO17:1;                    // 17 Toggle the GPIO17 output data latch
    Uint32 GPIO18:1;                    // 18 Toggle the GPIO18 output data latch
    Uint32 GPIO19:1;                    // 19 Toggle the GPIO19 output data latch
    Uint32 GPIO20:1;                    // 20 Toggle the GPIO20 output data latch
    Uint32 GPIO21:1;                    // 21 Toggle the GPIO21 output data latch
    Uint32 GPIO22:1;                    // 22 Toggle the GPIO22 output data latch
    Uint32 GPIO23:1;                    // 23 Toggle the GPIO23 output data latch
    Uint32 GPIO24:1;                    // 24 Toggle the GPIO24 output data latch
    Uint32 GPIO25:1;                    // 25 Toggle the GPIO25 output data latch
    Uint32 GPIO26:1;                    // 26 Toggle the GPIO26 output data latch
    Uint32 GPIO27:1;                    // 27 Toggle the GPIO27 output data latch
    Uint32 GPIO28:1;                    // 28 Toggle the GPIO28 output data latch
    Uint32 GPIO29:1;                    // 29 Toggle the GPIO29 output data latch
    Uint32 GPIO30:1;                    // 30 Toggle the GPIO30 output data latch
    Uint32 GPIO31:1;                    // 31 Toggle the GPIO31 output data latch
};

union GPATOGGLE_REG {
    Uint32  all;
    struct  GPATOGGLE_BITS  bit;
};

struct GPBDAT_BITS {                    // bits description
    Uint32 GPIO32:1;                    // 0 GPIO32 Read/Write Data Bit
    Uint32 GPIO33:1;                    // 1 GPIO33 Read/Write Data Bit
    Uint32 GPIO34:1;                    // 2 GPIO34 Read/Write Data Bit
    Uint32 GPIO35:1;                    // 3 GPIO35 Read/Write Data Bit
    Uint32 rsvd1:1;                     // 4 Reserved
    Uint32 GPIO37:1;                    // 5 GPIO37 Read/Write Data Bit
    Uint32 rsvd2:1;                     // 6 Reserved
    Uint32 GPIO39:1;                    // 7 GPIO39 Read/Write Data Bit
    Uint32 GPIO40:1;                    // 8 GPIO40 Read/Write Data Bit
    Uint32 GPIO41:1;                    // 9 GPIO41 Read/Write Data Bit
    Uint32 GPIO42:1;                    // 10 GPIO42 Read/Write Data Bit
    Uint32 GPIO43:1;                    // 11 GPIO43 Read/Write Data Bit
    Uint32 GPIO44:1;                    // 12 GPIO44 Read/Write Data Bit
    Uint32 GPIO45:1;                    // 13 GPIO45 Read/Write Data Bit
    Uint32 GPIO46:1;                    // 14 GPIO46 Read/Write Data Bit
    Uint32 GPIO47:1;                    // 15 GPIO47 Read/Write Data Bit
    Uint32 GPIO48:1;                    // 16 GPIO48 Read/Write Data Bit
    Uint32 GPIO49:1;                    // 17 GPIO49 Read/Write Data Bit
    Uint32 GPIO50:1;                    // 18 GPIO50 Read/Write Data Bit
    Uint32 GPIO51:1;                    // 19 GPIO51 Read/Write Data Bit
    Uint32 GPIO52:1;                    // 20 GPIO52 Read/Write Data Bit
    Uint32 GPIO53:1;                    // 21 GPIO53 Read/Write Data Bit
    Uint32 GPIO54:1;                    // 22 GPIO54 Read/Write Data Bit
    Uint32 GPIO55:1;                    // 23 GPIO55 Read/Write Data Bit
    Uint32 GPIO56:1;                    // 24 GPIO56 Read/Write Data Bit
    Uint32 GPIO57:1;                    // 25 GPIO57 Read/Write Data Bit
    Uint32 GPIO58:1;                    // 26 GPIO58 Read/Write Data Bit
    Uint32 GPIO59:1;                    // 27 GPIO59 Read/Write Data Bit
    Uint32 rsvd3:1;                     // 28 Reserved
    Uint32 rsvd4:1;                     // 29 Reserved
    Uint32 rsvd5:1;                     // 30 Reserved
    Uint32 rsvd6:1;                     // 31 Reserved
};

union GPBDAT_REG {
    Uint32  all;
    struct  GPBDAT_BITS  bit;
};

struct GPBSET_BITS {                  // bits description
    Uint32 GPIO32:1;                    // 0 Set the GPIO32 output data latch
    Uint32 GPIO33:1;                    // 1 Set the GPIO33 output data latch
    Uint32 GPIO34:1;                    // 2 Set the GPIO34 output data latch
    Uint32 GPIO35:1;                    // 3 Set the GPIO35 output data latch
    Uint32 rsvd1:1;                    // 4 Reserved
    Uint32 GPIO37:1;                    // 5 Set the GPIO37 output data latch
    Uint32 rsvd2:1;                    // 6 Reserved
    Uint32 GPIO39:1;                    // 7 Set the GPIO39 output data latch
    Uint32 GPIO40:1;                    // 8 Set the GPIO40 output data latch
    Uint32 GPIO41:1;                    // 9 Set the GPIO41 output data latch
    Uint32 GPIO42:1;                    // 10 Set the GPIO42 output data latch
    Uint32 GPIO43:1;                    // 11 Set the GPIO43 output data latch
    Uint32 GPIO44:1;                    // 12 Set the GPIO44 output data latch
    Uint32 GPIO45:1;                    // 13 Set the GPIO45 output data latch
    Uint32 GPIO46:1;                    // 14 Set the GPIO46 output data latch
    Uint32 GPIO47:1;                    // 15 Set the GPIO47 output data latch
    Uint32 GPIO48:1;                    // 16 Set the GPIO48 output data latch
    Uint32 GPIO49:1;                    // 17 Set the GPIO49 output data latch
    Uint32 GPIO50:1;                    // 18 Set the GPIO50 output data latch
    Uint32 GPIO51:1;                    // 19 Set the GPIO51 output data latch
    Uint32 GPIO52:1;                    // 20 Set the GPIO52 output data latch
    Uint32 GPIO53:1;                    // 21 Set the GPIO53 output data latch
    Uint32 GPIO54:1;                    // 22 Set the GPIO54 output data latch
    Uint32 GPIO55:1;                    // 23 Set the GPIO55 output data latch
    Uint32 GPIO56:1;                    // 24 Set the GPIO56 output data latch
    Uint32 GPIO57:1;                    // 25 Set the GPIO57 output data latch
    Uint32 GPIO58:1;                    // 26 Set the GPIO58 output data latch
    Uint32 GPIO59:1;                    // 27 Set the GPIO59 output data latch
    Uint32 rsvd3:1;                    // 28 Reserved
    Uint32 rsvd4:1;                    // 29 Reserved
    Uint32 rsvd5:1;                    // 30 Reserved
    Uint32 rsvd6:1;                    // 31 Reserved
};

union GPBSET_REG {
    Uint32  all;
    struct  GPBSET_BITS  bit;
};

struct GPBCLR_BITS {                 // bits description
    Uint32 GPIO32:1;                    // 0 Clear the GPIO32 output data latch
    Uint32 GPIO33:1;                    // 1 Clear the GPIO33 output data latch
    Uint32 GPIO34:1;                    // 2 Clear the GPIO34 output data latch
    Uint32 GPIO35:1;                    // 3 Clear the GPIO35 output data latch
    Uint32 rsvd1:1;                    // 4 Reserved
    Uint32 GPIO37:1;                    // 5 Clear the GPIO37 output data latch
    Uint32 rsvd2:1;                    // 6 Reserved
    Uint32 GPIO39:1;                    // 7 Clear the GPIO39 output data latch
    Uint32 GPIO40:1;                    // 8 Clear the GPIO40 output data latch
    Uint32 GPIO41:1;                    // 9 Clear the GPIO41 output data latch
    Uint32 GPIO42:1;                    // 10 Clear the GPIO42 output data latch
    Uint32 GPIO43:1;                    // 11 Clear the GPIO43 output data latch
    Uint32 GPIO44:1;                    // 12 Clear the GPIO44 output data latch
    Uint32 GPIO45:1;                    // 13 Clear the GPIO45 output data latch
    Uint32 GPIO46:1;                    // 14 Clear the GPIO46 output data latch
    Uint32 GPIO47:1;                    // 15 Clear the GPIO47 output data latch
    Uint32 GPIO48:1;                    // 16 Clear the GPIO48 output data latch
    Uint32 GPIO49:1;                    // 17 Clear the GPIO49 output data latch
    Uint32 GPIO50:1;                    // 18 Clear the GPIO50 output data latch
    Uint32 GPIO51:1;                    // 19 Clear the GPIO51 output data latch
    Uint32 GPIO52:1;                    // 20 Clear the GPIO52 output data latch
    Uint32 GPIO53:1;                    // 21 Clear the GPIO53 output data latch
    Uint32 GPIO54:1;                    // 22 Clear the GPIO54 output data latch
    Uint32 GPIO55:1;                    // 23 Clear the GPIO55 output data latch
    Uint32 GPIO56:1;                    // 24 Clear the GPIO56 output data latch
    Uint32 GPIO57:1;                    // 25 Clear the GPIO57 output data latch
    Uint32 GPIO58:1;                    // 26 Clear the GPIO58 output data latch
    Uint32 GPIO59:1;                    // 27 Clear the GPIO59 output data latch
    Uint32 rsvd3:1;                    // 28 Reserved
    Uint32 rsvd4:1;                    // 29 Reserved
    Uint32 rsvd5:1;                    // 30 Reserved
    Uint32 rsvd6:1;                    // 31 Reserved
};

union GPBCLR_REG {
    Uint32  all;
    struct  GPBCLR_BITS  bit;
};

struct GPBTOGGLE_BITS {                  // bits description
    Uint32 GPIO32:1;                    // 0 Toggle  the GPIO32 output data latch
    Uint32 GPIO33:1;                    // 1 Toggle  the GPIO33 output data latch
    Uint32 GPIO34:1;                    // 2 Toggle  the GPIO34 output data latch
    Uint32 GPIO35:1;                    // 3 Toggle  the GPIO35 output data latch
    Uint32 rsvd1:1;                     // 4 Reserved
    Uint32 GPIO37:1;                    // 5 Toggle  the GPIO37 output data latch
    Uint32 rsvd2:1;                     // 6 Reserved
    Uint32 GPIO39:1;                    // 7 Toggle  the GPIO39 output data latch
    Uint32 GPIO40:1;                    // 8 Toggle  the GPIO40 output data latch
    Uint32 GPIO41:1;                    // 9 Toggle  the GPIO41 output data latch
    Uint32 GPIO42:1;                    // 10 Toggle  the GPIO42 output data latch
    Uint32 GPIO43:1;                    // 11 Toggle  the GPIO43 output data latch
    Uint32 GPIO44:1;                    // 12 Toggle  the GPIO44 output data latch
    Uint32 GPIO45:1;                    // 13 Toggle  the GPIO45 output data latch
    Uint32 GPIO46:1;                    // 14 Toggle  the GPIO46 output data latch
    Uint32 GPIO47:1;                    // 15 Toggle  the GPIO47 output data latch
    Uint32 GPIO48:1;                    // 16 Toggle  the GPIO48 output data latch
    Uint32 GPIO49:1;                    // 17 Toggle  the GPIO49 output data latch
    Uint32 GPIO50:1;                    // 18 Toggle  the GPIO50 output data latch
    Uint32 GPIO51:1;                    // 19 Toggle  the GPIO51 output data latch
    Uint32 GPIO52:1;                    // 20 Toggle  the GPIO52 output data latch
    Uint32 GPIO53:1;                    // 21 Toggle  the GPIO53 output data latch
    Uint32 GPIO54:1;                    // 22 Toggle  the GPIO54 output data latch
    Uint32 GPIO55:1;                    // 23 Toggle  the GPIO55 output data latch
    Uint32 GPIO56:1;                    // 24 Toggle  the GPIO56 output data latch
    Uint32 GPIO57:1;                    // 25 Toggle  the GPIO57 output data latch
    Uint32 GPIO58:1;                    // 26 Toggle  the GPIO58 output data latch
    Uint32 GPIO59:1;                    // 27 Toggle  the GPIO59 output data latch
    Uint32 rsvd3:1;                     // 28 Reserved
    Uint32 rsvd4:1;                     // 29 Reserved
    Uint32 rsvd5:1;                     // 30 Reserved
    Uint32 rsvd6:1;                     // 31 Reserved
};

union GPBTOGGLE_REG {
    Uint32  all;
    struct  GPBTOGGLE_BITS  bit;
};

struct GPHDAT_BITS {                 // bits description
    Uint32 GPIO224:1;                   // 0 GPIO224 Read/Write Data Bit
    Uint32 GPIO225:1;                   // 1 GPIO225 Read/Write Data Bit
    Uint32 GPIO226:1;                   // 2 GPIO226 Read/Write Data Bit
    Uint32 GPIO227:1;                   // 3 GPIO227 Read/Write Data Bit
    Uint32 GPIO228:1;                   // 4 GPIO228 Read/Write Data Bit
    Uint32 GPIO229:1;                   // 5 GPIO229 Read/Write Data Bit
    Uint32 GPIO230:1;                   // 6 GPIO230 Read/Write Data Bit
    Uint32 GPIO231:1;                   // 7 GPIO231 Read/Write Data Bit
    Uint32 GPIO232:1;                   // 8 GPIO232 Read/Write Data Bit
    Uint32 GPIO233:1;                   // 9 GPIO233 Read/Write Data Bit
    Uint32 GPIO234:1;                   // 10 GPIO234 Read/Write Data Bit
    Uint32 GPIO235:1;                   // 11 GPIO235 Read/Write Data Bit
    Uint32 GPIO236:1;                   // 12 GPIO236 Read/Write Data Bit
    Uint32 GPIO237:1;                   // 13 GPIO237 Read/Write Data Bit
    Uint32 GPIO238:1;                   // 14 GPIO238 Read/Write Data Bit
    Uint32 GPIO239:1;                   // 15 GPIO239 Read/Write Data Bit
    Uint32 GPIO240:1;                   // 16 GPIO240 Read/Write Data Bit
    Uint32 GPIO241:1;                   // 17 GPIO241 Read/Write Data Bit
    Uint32 GPIO242:1;                   // 18 GPIO242 Read/Write Data Bit
    Uint32 GPIO243:1;                   // 19 GPIO243 Read/Write Data Bit
    Uint32 GPIO244:1;                   // 20 GPIO244 Read/Write Data Bit
    Uint32 GPIO245:1;                   // 21 GPIO245 Read/Write Data Bit
    Uint32 GPIO246:1;                   // 22 GPIO246 Read/Write Data Bit
    Uint32 GPIO247:1;                   // 23 GPIO247 Read/Write Data Bit
    Uint32 GPIO248:1;                   // 24 GPIO248 Read/Write Data Bit
    Uint32 GPIO249:1;                   // 25 GPIO249 Read/Write Data Bit
    Uint32 GPIO250:1;                   // 26 GPIO250 Read/Write Data Bit
    Uint32 GPIO251:1;                   // 27 GPIO251 Read/Write Data Bit
    Uint32 GPIO252:1;                   // 28 GPIO252 Read/Write Data Bit
    Uint32 GPIO253:1;                   // 29 GPIO253 Read/Write Data Bit
    Uint32 GPIO254:1;                   // 30 GPIO254 Read/Write Data Bit
    Uint32 rsvd8:1;                     // 31 Reserved
};

union GPHDAT_REG {
    Uint32  all;
    struct  GPHDAT_BITS  bit;
};

struct GPIO_DATA_REGS {
    union   GPADAT_REG                    GPADAT;                       // GPIO A Data Register (GPIO0 to GPIO31)
    union   GPASET_REG                    GPASET;                       // GPIO A Output Set (GPIO0 to GPIO31)
    union   GPACLR_REG                    GPACLR;                       // GPIO A Output Clear (GPIO0 to GPIO31)
    union   GPATOGGLE_REG                 GPATOGGLE;                    // GPIO A Output Toggle (GPIO0 to GPIO31)
    union   GPBDAT_REG                    GPBDAT;                       // GPIO B Data Register (GPIO32 to GPIO59)
    union   GPBSET_REG                    GPBSET;                       // GPIO B Output Set (GPIO32 to GPIO59)
    union   GPBCLR_REG                    GPBCLR;                       // GPIO B Output Clear (GPIO32 to GPIO59)
    union   GPBTOGGLE_REG                 GPBTOGGLE;                    // GPIO B Output Toggle (GPIO32 to GPIO59)
    Uint16                                rsvd1[40];                    // Reserved
    union   GPHDAT_REG                    GPHDAT;                       // GPIO H Data Register (GPIO224 to GPIO254)
};

//---------------------------------------------------------------------------
// GPIO External References & Function Declarations:
//
extern volatile struct GPIO_CTRL_REGS GpioCtrlRegs;
extern volatile struct GPIO_DATA_REGS GpioDataRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
