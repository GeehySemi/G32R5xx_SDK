//###########################################################################
//
// FILE:    pwm_ex11_configure_signal.c
//
// TITLE:   Configure desired PWM frequency & duty
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1> PWM Configure Signal </h1>
//!
//! This example configures PWM1, PWM2, PWM3 to produce signal of desired
//! frequency and duty. It also configures phase between the configured
//! modules.
//!
//! Signal of 10kHz with duty of 0.5 is configured on PWMxA & PWMxB
//! with PWMxB inverted. Also, phase of 120 degree is configured between
//! PWM1 to PWM3 signals.
//!
//! During the test, monitor PWM1, PWM2, and/or PWM3 outputs
//! on an oscilloscope.
//!
//! - PWM1A is on GPIO0
//! - PWM1B is on GPIO1
//! - PWM2A is on GPIO2
//! - PWM2B is on GPIO3
//! - PWM3A is on GPIO4
//! - PWM3B is on GPIO5
//!
//! \b External \b Connections \n
//!  - Optional: probe EPWM outputs on the EVAL header.
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
// 1. Modified some function and macro definition and variable names.
// 2. Updated interrupt handling to use NVIC functions.
// 3. Added SysCtl_setSyncInputConfig for PWM2/PWM3 from PWM1 SYNCOUT.
//
//###########################################################################

#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Globals
//
PWM_SignalParams pwmSignal = {
    .freqInHz = 10000,
    .dutyValA = 0.5f,
    .dutyValB = 0.5f,
    .invertSignalB = true,
    .pwmClkInHz = DEVICE_AHBCLK_FREQ,
    .tbCtrMode = PWM_COUNTER_MODE_UP_DOWN,
    .tbClkDiv = PWM_CLOCK_DIVIDER_1,
    .tbHSClkDiv = PWM_HSCLOCK_DIVIDER_1,
};
//
//  Function Prototypes
//
void configurePhase(uint32_t base, uint32_t masterBase, uint16_t phaseVal);

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
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();

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
    // For this case just init GPIO pins for PWM1, PWM2, PWM3
    //
    Board_init();

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configuring PWM module for desired frequency and duty
    //
    PWM_configureSignal(myPWM1_BASE, &pwmSignal);
    PWM_configureSignal(myPWM2_BASE, &pwmSignal);
    PWM_configureSignal(myPWM3_BASE, &pwmSignal);

    //
    // Configure phase between PWM1, PWM2 & PWM3.
    // PWM1 is configured as master and PWM2 & 3
    // are configured as slaves.
    //
    PWM_disablePhaseShiftLoad(myPWM1_BASE);
    PWM_setPhaseShift(myPWM1_BASE, 0U);

    //
    // PWM1 SYNCO is generated on CTR=0
    //
    PWM_setSyncOutPulseMode(myPWM1_BASE, PWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);

    //
    // Configure phase shift for PWM2 & 3
    //
    configurePhase(myPWM2_BASE, myPWM1_BASE, 120);
    configurePhase(myPWM3_BASE, myPWM1_BASE, 240);

    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_PWM2, SYSCTL_SYNC_IN_SRC_PWM1SYNCOUT);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_PWM3, SYSCTL_SYNC_IN_SRC_PWM1SYNCOUT);

    PWM_enablePhaseShiftLoad(myPWM2_BASE);
    PWM_enablePhaseShiftLoad(myPWM3_BASE);

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_PWM1);

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for (;;)
    {
        __asm ("  NOP");
    }
}

//
// configurePhase - Configure PWMx Phase
//
void configurePhase(uint32_t base, uint32_t masterBase, uint16_t phaseVal)
{
    uint32_t readPrdVal, phaseRegVal=0;

    //
    // Read Period value to calculate value for Phase Register
    //
    readPrdVal = PWM_getTimeBasePeriod(masterBase);

    //
    // Caluclate phase register values based on Time Base counter mode
    //

    if ((HWREGH(base + PWM_O_TBCTL) & 0x3U) == PWM_COUNTER_MODE_UP_DOWN)
    {
        phaseRegVal = (2U * readPrdVal * phaseVal) / 360U;
    }
    else if ((HWREGH(base + PWM_O_TBCTL) & 0x3U) < PWM_COUNTER_MODE_UP_DOWN)
    {
        phaseRegVal = (readPrdVal * phaseVal) / 360U;
    }

    PWM_selectPeriodLoadEvent(base, PWM_SHADOW_LOAD_MODE_SYNC);
    PWM_setPhaseShift(base, phaseRegVal);
    PWM_setTimeBaseCounter(base, phaseRegVal);
}

//
// End of file
//
