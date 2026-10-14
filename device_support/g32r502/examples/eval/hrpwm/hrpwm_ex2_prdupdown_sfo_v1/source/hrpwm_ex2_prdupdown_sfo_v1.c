//#############################################################################
//
// FILE:    hrpwm_ex2_prdupdown_sfo_V1.c
//
// TITLE:   HRPWM SFO V1 High-Resolution Period (Up-Down Count) example
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup bitfield_example_list
//! <h1>HRPWM Period Up-Down Count (hrpwm_ex2_prdupdown_sfo_v1)</h1>
//!
//! PWM1 operates in up-down count mode with high-resolution period control
//! (TBPRDHR, autoconversion enabled). SFO V1 calibrates \b MEP_ScaleFactor;
//! \b PeriodFine (Q16) is written to TBPRDHR to fine-tune the effective
//! period. Unlike \b hrpwm_ex1_duty_sfo_v1, this example sweeps period, not
//! CMPA/CMPB duty.
//!
//! At 200 MHz SYSCLK and TBPRD = 20, the coarse PWM frequency is about
//! 5 MHz (f = fTBCLK / (2 * TBPRD)). \b PeriodFine sweeps from 0x3333 to
//! 0xFFBF (about 0.2 to 1.0 in Q16).
//!
//! Use MDK real-time debug when running under the debugger (ERTM).
//!
//! \b External \b Connections \n
//!  - Oscilloscope on GPIO0 (PWM1A / G32R502 EVAL). Optional: GPIO1 (PWM1B).
//!
//! \b Watch \b Variables \n
//!  - \b status
//!  - \b UpdateFine - 1: HR period steps via TBPRDHR; 0: TBPRDHR = 0
//!  - \b PeriodFine
//!  - \b MEP_ScaleFactor
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
// 1. Updated file name to hrpwm_ex2_prdupdown_sfo_V1.c and title to 
//    HRPWM SFO V1 Example.
// 2. Updated interrupt handling to use NVIC functions.
// 3. Set GPAAMSEL GPIO0/1 to digital mode before PWM1 pinmux.
// 4. Updated file-header notes for G32R502 GPIO0/1, 200 MHz, and Watch list.
//
//###########################################################################

//
// Included Files
//
#include "g32r502_examples.h"
#include "g32r502_device.h"
#include "SFO_V1.h"

//
// Defines
//
#define PWM_CH            2        // # of PWM channels - 1
#define STATUS_SUCCESS    1
#define STATUS_FAIL       0

//
// Globals
//
uint16_t UpdateFine, PeriodFine, status;
int MEP_ScaleFactor; // Global variable used by the SFO library
                     // Result can be used for all HRPWM channels
                     // This variable is also copied to HRMSTEP
                     // register by SFO(0) function.

// Used by SFO library (PWM[0] is a dummy value that isn't used)
volatile struct PWM_REGS *PWM[PWM_CH] = {&Pwm1Regs, &Pwm1Regs};

//
// Function Prototypes
//
void initHRPWM1GPIO(void);
void configHRPWM(uint16_t period);
void error(void);

//
// Main
//
void example_main(void)
{
    uint16_t i;

    //
    // Initialize device clock and peripherals
    //
    InitSysCtrl();

    //
    // Initialize GPIO
    //
    InitGpio();
    initHRPWM1GPIO();

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
    // Setup example variables
    //
    UpdateFine = 1;
    PeriodFine = 0;
    status = SFO_INCOMPLETE;

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // PWM and HRPWM register initialization
    //
    for(i=1; i<PWM_CH; i++)
    {
        // Change clock divider to /1
        // (PWM clock needs to be > 60MHz)
        (*PWM[i]).TBCTL.bit.HSPCLKDIV = 0;
    }
    configHRPWM(20);

    //
    // Calling SFO() updates the HRMSTEP register with calibrated MEP_ScaleFactor.
    // HRMSTEP must be populated with a scale factor value prior to enabling
    // high resolution period control.
    //
    while(status == SFO_INCOMPLETE)
    {
        status = SFO();
        if (status == SFO_ERROR)
        {
            error();    // SFO function returns 2 if an error occurs & # of MEP
        }               // steps/coarse step exceeds maximum of 255.
    }

    for(;;)
    {
        //
        // Sweep PeriodFine in Q16 (0x3333 to 0xFFBF, about 0.2 to 1.0)
        //
        for(PeriodFine = 0x3333; PeriodFine < 0xFFBF; PeriodFine++)
        {
            if(UpdateFine)
            {
                //
                // Because auto-conversion is enabled, the desired
                // fractional period must be written directly to the
                // TBPRDHR register in Q16 format
                // (lower 8-bits are ignored)
                //
                // Pwm1Regs.TBPRDHR = PeriodFine;
                //
                // The hardware will automatically scale
                // the fractional period by the MEP_ScaleFactor
                // in the HRMSTEP register (which is updated
                // by the SFO calibration software).
                //
                // Hardware conversion:
                // MEP delay movement = ((TBPRDHR(15:0) >> 8) *  HRMSTEP(7:0) +
                //                       0x80) >> 8
                //
                for(i=1; i<PWM_CH; i++)
                {
                    (*PWM[i]).TBPRDHR = PeriodFine; //In Q16 format
                }
            }
            else
            {
                //
                // No high-resolution movement on TBPRDHR.
                //
                for(i=1; i<PWM_CH; i++)
                {
                    (*PWM[i]).TBPRDHR = 0;
                }
            }

            //
            // Call the scale factor optimizer lib function SFO(0)
            // periodically to track for any change due to temp/voltage.
            // This function generates MEP_ScaleFactor by running the
            // MEP calibration module in the HRPWM logic. This scale
            // factor can be used for all HRPWM channels. HRMSTEP
            // register is automatically updated by the SFO function.
            //
            status = SFO(); // in background, MEP calibration module
                            // continuously updates MEP_ScaleFactor

            if(status == SFO_ERROR)
            {
                error();   // SFO function returns 2 if an error occurs & # of
                           // MEP steps/coarse step exceeds maximum of 255.
            }
        } // end PeriodFine for loop
    } // end infinite for loop
}

//
// configHRPWM - Configures all PWM channels and sets up HRPWM
//                on PWMxA channels &  PWMxB channels
//
void configHRPWM(uint16_t period)
{
    uint16_t j;

    //
    // PWM channel register configuration with HRPWM
    // PWMxA toggle low/high with MEP control on Rising edge
    //
    WRPRT_DISABLE;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;   // Disable TBCLK within the PWM
    WRPRT_ENABLE;

    for(j=1; j<PWM_CH; j++)
    {
        (*PWM[j]).TBCTL.bit.PRDLD = TB_SHADOW;  // set Shadow load
        (*PWM[j]).TBPRD = period;               // PWM frequency = 1/(2*TBPRD)
        (*PWM[j]).CMPA.bit.CMPA = period / 2;   // set duty 50% initially
        (*PWM[j]).CMPA.bit.CMPAHR = (1 << 8);   // initialize HRPWM extension
        (*PWM[j]).CMPB.bit.CMPB = period / 2;   // set duty 50% initially
        (*PWM[j]).CMPB.all |= 1;
        (*PWM[j]).TBPHS.all = 0;
        (*PWM[j]).TBCTR = 0;

        (*PWM[j]).TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Select up-down
                                                        // count mode
        (*PWM[j]).TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
        (*PWM[j]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
        (*PWM[j]).TBCTL.bit.CLKDIV = TB_DIV1;          // TBCLK = SYSCLKOUT
        (*PWM[j]).TBCTL.bit.FREE_SOFT = 0b11;

        (*PWM[j]).CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // LOAD CMPA on CTR = 0
        (*PWM[j]).CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
        (*PWM[j]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
        (*PWM[j]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;

        (*PWM[j]).AQCTLA.bit.CAU = AQ_SET;             // PWM toggle high/low
        (*PWM[j]).AQCTLA.bit.CAD = AQ_CLEAR;
        (*PWM[j]).AQCTLB.bit.CBU = AQ_SET;             // PWM toggle high/low
        (*PWM[j]).AQCTLB.bit.CBD = AQ_CLEAR;

        WRPRT_DISABLE;
        (*PWM[j]).HRCNFG.all = 0x0;
        (*PWM[j]).HRCNFG.bit.EDGMODE = HR_BEP;          // MEP control on
                                                         // both edges.
        (*PWM[j]).HRCNFG.bit.CTLMODE = HR_CMP;          // CMPAHR and TBPRDHR
                                                         // HR control.
        (*PWM[j]).HRCNFG.bit.HRLOAD = HR_CTR_ZERO_PRD;  // load on CTR = 0
                                                         // and CTR = TBPRD
        (*PWM[j]).HRCNFG.bit.EDGMODEB = HR_BEP;         // MEP control on
                                                         // both edges
        (*PWM[j]).HRCNFG.bit.CTLMODEB = HR_CMP;         // CMPBHR and TBPRDHR
                                                         // HR control
        (*PWM[j]).HRCNFG.bit.HRLOADB = HR_CTR_ZERO_PRD; // load on CTR = 0
                                                         // and CTR = TBPRD
        (*PWM[j]).HRCNFG.bit.AUTOCONV = 1;        // Enable autoconversion for
                                                   // HR period

        (*PWM[j]).HRPCTL.bit.TBPHSHRLOADE = 1;    // Enable TBPHSHR sync
                                                   // (required for updwn
                                                   //  count HR control)
        (*PWM[j]).HRPCTL.bit.HRPE = 1;            // Turn on high-resolution
                                                   // period control.

        CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;      // Enable TBCLK within
                                                   // the PWM
        (*PWM[j]).TBCTL.bit.SWFSYNC = 1;          // Synchronize high
                                                   // resolution phase to
                                                   // start HR period
        WRPRT_ENABLE;
    }
}

//
// initHRPWM1GPIO - Initialize HRPWM1 GPIOs
//
void initHRPWM1GPIO(void)
{
    WRPRT_DISABLE;

    //
    // Digital mode before pull-up and pinmux (G32R502 AMSEL reset = analog)
    //
    GpioCtrlRegs.GPAAMSEL.bit.GPIO0 = 0;    // GPIO0 (PWM1A)
    GpioCtrlRegs.GPAAMSEL.bit.GPIO1 = 0;    // GPIO1 (PWM1B)

    //
    // Disable internal pull-up for the selected output pins
    // for reduced power consumption
    // Pull-ups can be enabled or disabled by the user.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;    // Disable pull-up on GPIO0 (PWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;    // Disable pull-up on GPIO1 (PWM1B)

    //
    // Configure PWM-1 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be PWM1 functional
    // pins.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as PWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as PWM1B

    WRPRT_ENABLE;
}

//
// error - Halt debugger when error occurs
//
void error (void)
{
    ESTOP0;         // Stop here and handle error
}

//
// End of file
//
