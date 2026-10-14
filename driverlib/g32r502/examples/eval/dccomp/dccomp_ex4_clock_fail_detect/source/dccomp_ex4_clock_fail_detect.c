//#############################################################################
//
// FILE:    dccomp_ex4_clock_fail_detect.c
//
// TITLE:   DCCOMP Clock Fail Detection
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1>DCCOMP Detection of clock failure</h1>
//!
//! This program demonstrates XTAL clock-loss detection with DCCOMP0.
//! DCCOMP compares a live INTOSC1 (clock1) against XTAL (clock0). XTAL is
//! turned off with XTALCR.OSCOFF while it is still the OSCCLK source.
//! Missing-clock detection keeps SYSCLK on INTOSC1 so the CPU can run the
//! DCCOMP error interrupt. PASS requires the DCCOMP ISR, not the NMI alone.
//! Observe result, pass, isr_enter, and nmi_enter in the debugger.
//!
//! \note The XTAL is expected to be a resonator in crystal mode. If an
//! SE crystal is used, the clock must be disconnected on the board.
//!
//! Please refer to the TRM for details on counter seed values to be set.
//! Note : When running in flash configuration it is good to do a reset
//! and restart after loading the example to remove any stale flags/states.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - \b result - Status of the clock failure detection
//!  - \b pass / \b isr_enter - Set when DCCOMP_ISR runs
//!  - \b nmi_enter - Set on CLOCKFAIL NMI (not a PASS condition)
//!
//
//###########################################################################
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
// 1. Modify some comments, macros, function names, and function contents.
// 2. Monitor INTOSC1 against XTAL with MCD enabled. Turn off XTAL while
//    it is still OSCCLK, and re-arm DCCOMP if the first window does not error.
// 3. Skip OSCOFF if DCCOMP already reports error during healthy monitoring.
// 4. PASS follows the DCCOMP ISR. CLOCKFAIL NMI only clears NMI flags.
// 5. Observe PASS/FAIL with Watch variables and ESTOP0.
//
//###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Defines
//
#define PASS 0
#define FAIL 1

//
// Wait up to ~2 s for DCCOMP_ISR after OSCOFF (1 ms slices).
// Timeout lets FAIL set result for the debugger.
//
#define DCCOMP_EX4_ISR_WAIT_US_MAX   (2000000UL)
#define DCCOMP_EX4_ISR_WAIT_SLICE_US (1000UL)

//
// Healthy-monitor gate before OSCOFF: one DCCOMP window at the seeds
// below is tens of microseconds. 100 us covers several windows.
//
#define DCCOMP_EX4_HEALTHY_WAIT_US   (100UL)

//
// Globals
//
volatile uint32_t result = FAIL, isr_enter = 0;
volatile uint16_t pass = 0;
volatile uint32_t nmi_enter = 0;

//
// Function Prototypes
//
void DCCOMP_ISR();
void NMI_Handler(void);
static void DCCOMP_EX4_waitForIsr(uint32_t timeout_us);

//
// Main
//
void example_main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Board_init (no pinmux required for this example)
    //
    Board_init();

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
    // Clear Error & Done Flag
    //
    DCCOMP_clearErrorFlag(DCCOMP0_BASE);
    DCCOMP_clearDoneFlag(DCCOMP0_BASE);

    //
    // Set the priority group to indicate the PREEMPT and SUB priority bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    //
    // CLOCKFAIL NMI must return after OSCOFF, or the NMI watchdog resets
    // the device before DCCOMP_ISR can run.
    //
    SysCtl_clearAllNMIFlags();
    Interrupt_register(NonMaskableInt_IRQn, &NMI_Handler);
    Interrupt_setPriority(NonMaskableInt_IRQn, 0, 0);
    SysCtl_enableNMIGlobalInterrupt();
    Interrupt_enable(NonMaskableInt_IRQn);

    //
    // Set the global and group interrupt priority to allow CPU interrupts
    // with higher priority
    //
    Interrupt_setPriority(INT_DCCOMP, 0, 0);

    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_DCCOMP, &DCCOMP_ISR);

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_DCCOMP);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Keep MCD enabled. Turning off XTAL while it is still OSCCLK relies
    // on hardware switching SYSCLK to INTOSC1.
    //
    SysCtl_enableMCD();

    //
    // Continuous monitor of INTOSC1 using XTAL as reference clock.
    // SYSCLK is still XTAL->PLL (~200 MHz) so OSCOFF can stop clock0.
    // Clk1 = INTOSC1 (Frequency = 10MHz)
    // Clk0 = XTAL    (Frequency = 20MHz)
    // Tolerance = 10%
    // Allowable Frequency Tolerance = 0%
    // SysClk Freq = 200MHz
    //
    DCCOMP_continuousMonitor(DCCOMP0_BASE,
                             DCCOMP_COUNT1SRC_INTOSC1, 10.0f,
                             DCCOMP_COUNT0SRC_XTAL, 20.0f,
                             10.0f, 0.0f, 200.0f);

    //
    // Healthy monitoring must not raise an error before XTAL is turned off.
    //
    DEVICE_DELAY_US(DCCOMP_EX4_HEALTHY_WAIT_US);

    if (isr_enter == 0x1U)
    {
        result = FAIL;
        ESTOP0;
        while(1)
        {
        }
    }

    //
    // Turn off XTAL to simulate a missing clock. XTAL is still OSCCLK.
    //
    WRPRT_DISABLE;
    HWREGH(CLKCFG_BASE + SYSCTL_O_XTALCR) |= SYSCTL_XTALCR_OSCOFF;
    WRPRT_ENABLE;

    //
    // Allow MCD to move SYSCLK and the in-flight DCCOMP window to finish.
    //
    DCCOMP_EX4_waitForIsr(DCCOMP_EX4_ISR_WAIT_US_MAX / 4U);

    if (isr_enter != 0x1U)
    {
        SysCtl_selectOscSource(SYSCTL_OSCSRC_OSC1);
        SysCtl_delay(11U);

        DCCOMP_continuousMonitor(DCCOMP0_BASE,
                                 DCCOMP_COUNT1SRC_INTOSC1, 10.0f,
                                 DCCOMP_COUNT0SRC_XTAL, 20.0f,
                                 10.0f, 0.0f, 10.0f);

        DCCOMP_EX4_waitForIsr(DCCOMP_EX4_ISR_WAIT_US_MAX);
    }

    //
    // Status of the clock failure detection
    //
    if (pass == 0)
    {
        result = FAIL;
    }
    else
    {
        result = PASS;
    }

    ESTOP0;

    while(1)
    {
    }
}

//
// DCCOMP ISR triggered on an error
//
void DCCOMP_ISR()
{
    //
    // Shows that the ISR was called
    //
    isr_enter = 1;

    //
    // A clock failure was detected
    //
    pass++;

    if (DCCOMP_getErrorStatus(DCCOMP0_BASE) == 1U)
    {
        //
        // Clear the Error flag
        //
        DCCOMP_clearErrorFlag(DCCOMP0_BASE);
    }
}

//
// CLOCKFAIL NMI: keep the CPU alive after OSCOFF. Not a PASS condition.
//
void NMI_Handler(void)
{
    nmi_enter = 1U;
    SysCtl_clearAllNMIFlags();
}

//
// Wait for DCCOMP_ISR with a software timeout
//
static void DCCOMP_EX4_waitForIsr(uint32_t timeout_us)
{
    uint32_t wait_us = 0U;

    while((isr_enter != 0x1U) && (wait_us < timeout_us))
    {
        DEVICE_DELAY_US(DCCOMP_EX4_ISR_WAIT_SLICE_US);
        wait_us += DCCOMP_EX4_ISR_WAIT_SLICE_US;
    }
}
