//#############################################################################
//
// FILE:    cap_ex1_apwm.c
//
// TITLE:   CAP APWM Example
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup bitfield_example_list
//! <h1>CAP APWM Example</h1>
//!
//! This program sets up the CAP module in APWM mode. The PWM waveform will
//! come out on GPIO5. The frequency of PWM is configured to vary between 5Hz
//! and 10Hz using the shadow registers to load the next period/compare values.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - None.
//!
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
// 1. Updated file name to cap_ex1_apwm.c and title to CAP APWM Example.
// 2. Replaced eCAP references with CAP.
// 3. Updated interrupt handling to use NVIC functions.
//
//###########################################################################

//
// Included Files
//
#include "g32r501_project.h"

//
// Function Prototypes
//
void InitAPwm1Gpio(void);

//
// Globals
//
uint16_t direction = 0;

void example_main(void)
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the g32r501_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the g32r501_Gpio.c file and
    // illustrates how to set the GPIO to its default state.
    //
    // InitGpio();  // Skipped for this example

    //
    // Select CAP1OUT on OUTPUTXBAR3's MUX 0.
    // Make GPIO5 CAP1OUT for PWM output.
    //
    InitAPwm1Gpio();

    //
    // Step 3. Clear all __interrupts and initialize NVIC vector table:
    // Disable CPU __interrupts
    //
    DINT;

    //
    //Initialize the NVIC control registers to their default state.
    //The default state is all NVIC interrupts disabled and flags
    //are cleared.
    //
    Interrupt_initModule();

    //
    // Initialize the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the __interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in g32r501_DefaultIsr.c.
    // This function is found in g32r501_PieVect.c.
    //
    Interrupt_initVectorTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    // No __interrupts used for this example.
    //

    //
    // Step 4. User specific code
    //
    //
    // Setup APWM mode on CAP1, set period and compare registers
    //
    WRPRT_DISABLE;
    Cap1Regs.ECCTL2.bit.CAP_APWM = 1;    // Enable APWM mode
    Cap1Regs.CAP1 = 20000000;            // Set Period value
    Cap1Regs.CAP2 = 10000000;            // Set Compare value
    Cap1Regs.ECCLR.all = 0x0FF;          // Clear pending __interrupts
    Cap1Regs.ECEINT.bit.CTR_EQ_CMP = 1;  // enable Compare Equal Int

    //
    // Start counters
    //
    Cap1Regs.ECCTL2.bit.TSCTRSTOP = 1;

    WRPRT_ENABLE;
    for(;;)
    {
        //
        // set next duty cycle to 50%
        //
        Cap1Regs.CAP4 = Cap1Regs.CAP1 >> 1;
        //
        // vary freq
        //
        if(Cap1Regs.CAP1 >= 20000000)
        {
            direction = 0;
        }
        else if (Cap1Regs.CAP1 <= 10000000)
        {
            direction = 1;
        }

        if(direction == 0)
        {
            Cap1Regs.CAP3 = Cap1Regs.CAP1 - 500000;
        }
        else
        {
            Cap1Regs.CAP3 = Cap1Regs.CAP1 + 500000;
        }
    }
}

//
// InitAPwm1Gpio
// Select CAP1OUT on OUTPUTXBAR3's MUX 0. Make GPIO5 CAP1OUT for PWM output
//
void InitAPwm1Gpio()
{
    WRPRT_DISABLE;
    OutputXbarRegs.OUTPUT3MUX0TO15CFG.bit.MUX0 = 3; // Select CAP1.OUT on Mux0
    OutputXbarRegs.OUTPUT3MUXENABLE.bit.MUX0 = 1;  // Enable MUX0 for CAP1.OUT
    GpioCtrlRegs.GPAGMUX1.bit.GPIO5 = 0; // Select OUTPUTXBAR3 on GPIO5
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 3;
    WRPRT_ENABLE;
}
//
// End of File
//
