//###########################################################################
//
// FILE:    gpio_ex1_setup.c
//
// TITLE:   Device GPIO Setup
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup bitfield_example_list
//! <h1>Device GPIO Setup</h1>
//!
//! Configures the G32R502 GPIO into two different pinout examples that
//! match the G32R502 pin-mux table (product brief section 3.3.1). Each
//! pin is assigned to at most one function. All IO (GPIO/AIO/AGPIO) default
//! to analog mode at power-up; clear GPxAMSEL for digital mode before pullup
//! or mux programming (product brief section 3.3.3).
//! This example only sets up GPIO and stops at a debug breakpoint.
//! Nothing is actually done with the pins after setup.
//! \b External \b Connections \n
//!  - None (GPIO setup exercise; use on-board LEDs/buttons as configured).
//!
//! \b Watch \b Variables \n
//!  - None.
//!
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
// 1. Updated device name to G32R502 and corrected file references.
// 2. Updated interrupt handling to use NVIC functions.
// 3. Resolved pin-mux conflicts; CANFDA-A and I2C-B moved off PWM pins.
// 4. Set GPxAMSEL digital mode before pullup on all configured pins.
//
//###########################################################################

//
// Included Files
//
#include "g32r502_project.h"

//
// Defines
// Select the example to compile in.  Only one example should be set as 1
// the rest should be set as 0.
//
#define EXAMPLE1 1  // Basic pinout configuration example
#define EXAMPLE2 0  // Communication pinout example

//
// Function Prototypes
//
void setup1GPIO(void);
void setup2GPIO(void);

//
// Main
//

void example_main(void)
{
    //
    //PLL, WatchDog,enabe Peripheral Clocks
    //This example function is found in the g32r502_sysctrl.c file.
    //
    InitSysCtrl();

    //
    //Initialize GPIO
    //
    InitGpio();

    //
    //Disable CPU __interrupts
    //
    DINT;

    //
    // Globally disable interrupts and clear all NVIC enable/pending bits
    //
    Interrupt_initModule();

    //
    // Initialize RAM vector table and set VTOR; unregistered IRQs use
    // Interrupt_defaultHandler until Interrupt_register() is called
    //
    Interrupt_initVectorTable();

    //
    //Step 4. User specific code:
    //
#if EXAMPLE1

    //
    //This example is a basic pinout
    //
    setup1GPIO();

#endif

#if EXAMPLE2

    //
    // This example is a communications pinout
    //
    setup2GPIO();

#endif

    while(1)
    {
        ESTOP0;
    }
}

//
// setup1GPIO - Is an example that demonstrates the basic pinout
//
void setup1GPIO(void)
{
    //
    // Example 1: Basic pinout (no pin reused for multiple functions).
    // PWM1-3, CAP1/2, TZ1-TZ3, SPI-A, QEP1, UART-A, CANFDA-A,
    // I2C-B, XINT1/2, and GPIO27 LPM wake.
    //

    WRPRT_DISABLE;

    //
    // PWM1-3 on GPIO0-GPIO5 (mux position 1)
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO0 = 0;   // Digital mode before pullup
    GpioCtrlRegs.GPAAMSEL.bit.GPIO1 = 0;
    GpioCtrlRegs.GPAAMSEL.bit.GPIO2 = 0;
    GpioCtrlRegs.GPAAMSEL.bit.GPIO3 = 0;
    GpioCtrlRegs.GPAAMSEL.bit.GPIO4 = 0;
    GpioCtrlRegs.GPAAMSEL.bit.GPIO5 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;   // Enable pullup on GPIO0
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;   // Enable pullup on GPIO1
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;   // Enable pullup on GPIO2
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;   // Enable pullup on GPIO3
    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;   // Enable pullup on GPIO4
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;   // Enable pullup on GPIO5
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;  // GPIO0 = PWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;  // GPIO1 = PWM1B
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;  // GPIO2 = PWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;  // GPIO3 = PWM2B
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;  // GPIO4 = PWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;  // GPIO5 = PWM3B

    //
    // GPIO6 output, set high (mux position 0)
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO6 = 0;   // Digital mode before pullup
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;
    GpioDataRegs.GPASET.bit.GPIO6 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;

    //
    // CAP1 on GPIO7 via INPUT7 (manual section 3.3.4)
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO7 = 0;   // Digital mode before pullup
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 0;
    InputXbarRegs.INPUT7SELECT = 7;
    Cap1Regs.ECCTL0.bit.INPUTSEL = 7;

    //
    // Trip Zone inputs TZ1-TZ3 on GPIO12-GPIO14 (INPUT1-3)
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO12 = 0; // Digital mode before pullup
    GpioCtrlRegs.GPAAMSEL.bit.GPIO13 = 0;
    GpioCtrlRegs.GPAAMSEL.bit.GPIO14 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3;
    InputXbarRegs.INPUT1SELECT = 12;
    InputXbarRegs.INPUT2SELECT = 13;
    InputXbarRegs.INPUT3SELECT = 14;

    //
    // SPI-A on GPIO8-GPIO11 (mux position 7)
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO8 = 0;   // Digital mode before pullup
    GpioCtrlRegs.GPAAMSEL.bit.GPIO9 = 0;
    GpioCtrlRegs.GPAAMSEL.bit.GPIO10 = 0;
    GpioCtrlRegs.GPAAMSEL.bit.GPIO11 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO8 = 3;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO9 = 3;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO10 = 3;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 3;
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 3;
    GpioCtrlRegs.GPAGMUX1.bit.GPIO8 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 3;
    GpioCtrlRegs.GPAGMUX1.bit.GPIO9 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 3;
    GpioCtrlRegs.GPAGMUX1.bit.GPIO10 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 3;
    GpioCtrlRegs.GPAGMUX1.bit.GPIO11 = 1;

    //
    // QEP1 on GPIO20, GPIO41, GPIO43 (mux positions 1 / 10 / 10)
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO20 = 0; // Digital mode before pullup
    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;
    GpioCtrlRegs.GPBAMSEL.bit.GPIO41 = 0;
    GpioCtrlRegs.GPBAMSEL.bit.GPIO43 = 0;
    GpioCtrlRegs.GPBPUD.bit.GPIO41 = 0;
    GpioCtrlRegs.GPBPUD.bit.GPIO43 = 0;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO20 = 0;
    GpioCtrlRegs.GPBQSEL1.bit.GPIO41 = 0;
    GpioCtrlRegs.GPBQSEL1.bit.GPIO43 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;
    GpioCtrlRegs.GPBGMUX1.bit.GPIO41 = 2;
    GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 2;
    GpioCtrlRegs.GPBGMUX1.bit.GPIO43 = 2;
    GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 2;

    //
    // CAP2 on GPIO24 via INPUT8
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO24 = 0;  // Digital mode before pullup
    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0;
    InputXbarRegs.INPUT8SELECT = 24;
    Cap2Regs.ECCTL0.bit.INPUTSEL = 8;

    //
    // Input qualification for GPIO25 and GPIO26 (6 samples, QUALPRD3)
    //
    GpioCtrlRegs.GPACTRL.bit.QUALPRD3 = 1;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 2;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 2;

    //
    // XINT1 / XINT2 on GPIO25 / GPIO26 (INPUT4 / INPUT5)
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO25 = 0;  // Digital mode before GPIO input
    GpioCtrlRegs.GPAAMSEL.bit.GPIO26 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;
    GPIO_SetupXINT1Gpio(25);
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;
    GPIO_SetupXINT2Gpio(26);

    //
    // GPIO27 LPM wake source
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO27 = 0;  // Digital mode before GPIO input
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;
    CpuSysRegs.GPIOLPMSEL0.bit.GPIO27 = 1;

    //
    // UART-A on GPIO28-GPIO29 (mux position 1)
    // Note: GPIO28 shares analog/COMP4; do not enable COMP4 when using UART RX.
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO28 = 0; // Digital mode before pullup
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;
    GpioCtrlRegs.GPAAMSEL.bit.GPIO29 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;

    //
    // CANFDA-A on GPIO30-GPIO31 (CANFDRXA / CANFDTXA, mux position 10)
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO30 = 0;  // Digital mode before pullup
    GpioCtrlRegs.GPAAMSEL.bit.GPIO31 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO30 = 0;   // Enable pullup on GPIO30
    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 0;   // Enable pullup on GPIO31
    GpioCtrlRegs.GPAQSEL2.bit.GPIO30 = 3; // Asynch input on CANFDRXA
    GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 2;  // GPIO30 = CANFDRXA
    GpioCtrlRegs.GPAGMUX2.bit.GPIO30 = 2;
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 2;  // GPIO31 = CANFDTXA
    GpioCtrlRegs.GPAGMUX2.bit.GPIO31 = 2;

    //
    // I2C-B on GPIO34 (SDA, mux 14) and GPIO227 (SCL, mux 1)
    //
    GpioCtrlRegs.GPBAMSEL.bit.GPIO34 = 0;  // Digital mode before pullup
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 2;
    GpioCtrlRegs.GPBGMUX1.bit.GPIO34 = 3;
    GpioCtrlRegs.GPBQSEL1.bit.GPIO34 = 3;
    GpioCtrlRegs.GPHAMSEL.bit.GPIO227 = 0; // Digital mode before pullup
    GpioCtrlRegs.GPHPUD.bit.GPIO227 = 0;
    GpioCtrlRegs.GPHQSEL1.bit.GPIO227 = 3;
    GpioCtrlRegs.GPHMUX1.bit.GPIO227 = 1;
    GpioCtrlRegs.GPHGMUX1.bit.GPIO227 = 0;

    WRPRT_ENABLE;
}

//
// setup2GPIO - Is an example that demonstrates the communications pinout
//
void setup2GPIO(void)
{
    //
    // Example 2: Communications pinout (alternate SPI-A pin group).
    // PWM1-3, CAP1/2, SPI-A on GPIO16-19, UART-A, CANFDA-A, I2C-B, XINT, LPM wake.
    // G32R502 provides one SPI port; this shows the GPIO16-19 SPI-A alternate.
    //

    WRPRT_DISABLE;

    //
    // PWM1-3 on GPIO0-GPIO5 (mux position 1)
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO0 = 0;   // Digital mode before pullup
    GpioCtrlRegs.GPAAMSEL.bit.GPIO1 = 0;
    GpioCtrlRegs.GPAAMSEL.bit.GPIO2 = 0;
    GpioCtrlRegs.GPAAMSEL.bit.GPIO3 = 0;
    GpioCtrlRegs.GPAAMSEL.bit.GPIO4 = 0;
    GpioCtrlRegs.GPAAMSEL.bit.GPIO5 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;   // Enable pullup on GPIO0
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;   // Enable pullup on GPIO1
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;   // Enable pullup on GPIO2
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;   // Enable pullup on GPIO3
    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;   // Enable pullup on GPIO4
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;   // Enable pullup on GPIO5
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;

    //
    // GPIO6 output
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO6 = 0;   // Digital mode before pullup
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;
    GpioDataRegs.GPASET.bit.GPIO6 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;

    //
    // CAP1 on GPIO7 via INPUT7
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO7 = 0;   // Digital mode before pullup
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 0;
    InputXbarRegs.INPUT7SELECT = 7;
    Cap1Regs.ECCTL0.bit.INPUTSEL = 7;

    //
    // SPI-A on GPIO16-GPIO19 (mux position 1)
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO16 = 0;  // Digital mode before pullup
    GpioCtrlRegs.GPAAMSEL.bit.GPIO17 = 0;
    GpioCtrlRegs.GPAAMSEL.bit.GPIO18 = 0;
    GpioCtrlRegs.GPAAMSEL.bit.GPIO19 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;

    //
    // CAP2 on GPIO24 via INPUT8
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO24 = 0;  // Digital mode before pullup
    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0;
    InputXbarRegs.INPUT8SELECT = 24;
    Cap2Regs.ECCTL0.bit.INPUTSEL = 8;

    //
    // Input qualification for GPIO25 and GPIO26
    //
    GpioCtrlRegs.GPACTRL.bit.QUALPRD3 = 1;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 2;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 2;

    //
    // XINT1 / XINT2 on GPIO25 / GPIO26
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO25 = 0;  // Digital mode before GPIO input
    GpioCtrlRegs.GPAAMSEL.bit.GPIO26 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;
    GPIO_SetupXINT1Gpio(25);
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;
    GPIO_SetupXINT2Gpio(26);

    //
    // GPIO27 LPM wake source
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO27 = 0;  // Digital mode before GPIO input
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;
    CpuSysRegs.GPIOLPMSEL0.bit.GPIO27 = 1;

    //
    // UART-A on GPIO28-GPIO29 (mux position 1)
    // Note: GPIO28 shares analog/COMP4; do not enable COMP4 when using UART RX.
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO28 = 0; // Digital mode before pullup
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;
    GpioCtrlRegs.GPAAMSEL.bit.GPIO29 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;

    //
    // CANFDA-A on GPIO30-GPIO31 (CANFDRXA / CANFDTXA, mux position 10)
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO30 = 0;  // Digital mode before pullup
    GpioCtrlRegs.GPAAMSEL.bit.GPIO31 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO30 = 0;   // Enable pullup on GPIO30
    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 0;   // Enable pullup on GPIO31
    GpioCtrlRegs.GPAQSEL2.bit.GPIO30 = 3; // Asynch input on CANFDRXA
    GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 2;  // GPIO30 = CANFDRXA
    GpioCtrlRegs.GPAGMUX2.bit.GPIO30 = 2;
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 2;  // GPIO31 = CANFDTXA
    GpioCtrlRegs.GPAGMUX2.bit.GPIO31 = 2;

    //
    // I2C-B on GPIO34 (SDA) and GPIO227 (SCL)
    //
    GpioCtrlRegs.GPBAMSEL.bit.GPIO34 = 0;  // Digital mode before pullup
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 2;
    GpioCtrlRegs.GPBGMUX1.bit.GPIO34 = 3;
    GpioCtrlRegs.GPBQSEL1.bit.GPIO34 = 3;
    GpioCtrlRegs.GPHAMSEL.bit.GPIO227 = 0; // Digital mode before pullup
    GpioCtrlRegs.GPHPUD.bit.GPIO227 = 0;
    GpioCtrlRegs.GPHQSEL1.bit.GPIO227 = 3;
    GpioCtrlRegs.GPHMUX1.bit.GPIO227 = 1;
    GpioCtrlRegs.GPHGMUX1.bit.GPIO227 = 0;

    WRPRT_ENABLE;
}
//
// End of File
//
