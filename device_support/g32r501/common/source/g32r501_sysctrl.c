//###########################################################################
//
// FILE:    g32r501_sysctrl.c
//
// TITLE:   g32r501 Device System Control Initialization & Support Functions.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
// DESCRIPTION:  Example initialization of system resources.
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
// 1. Updated header file title for G32R501 DMA initialization functions.
// 2. Changed file name to g32r501_sysctrl.c to reflect the new architecture.
// 3. Adjusted PLL and DCCOMP initialization functions to align with G32R501
//    specifics.
// 4. Updated register accesses and initialization logic for G32R501 device.
//
//###########################################################################

//
// Included Files
//
#include "g32r501_device.h"     // Headerfile Include File
#include "g32r501_examples.h"   // Examples Include File
#ifdef __cplusplus
using std::memcpy;
#endif

//
// The following values are used to validate PLL Frequency using DCCOMP
//
#define   PLL_RETRIES              100
#define   PLL_LOCK_TIMEOUT         2000
#define   DCCOMP_COUNTER0_WINDOW   100

//
// Macro used for adding delay between 2 consecutive writes to CLKSRCCTL1
// register.
// Delay = 300 NOPs
//
#define SYSCTRL_CLKSRCCTL1_DELAY    __asm volatile ( \
                                    "MOV R1,LR \n" \
                                    "MOV LR,#149 \n" \
                                    "nop_loop: \n" \
                                    "NOP \n" \
                                    "SUBS LR, LR, #1 \n" \
                                    "BNE nop_loop \n" \
                                    "MOV LR,R1 \n" \
                                    )

//
// Delays for a fixed number of cycles.
//
SECTION_ITCM_RAMFUNC
NO_OPTIMIZE
void G32R5xx_usDelay(uint32_t count)
{
    __asm volatile
    (
                                          "MOV R1, LR \n"
                                          "MOV LR, R0 \n"
           "delay_loop: \n"
                                          "NOP \n"
                                          "NOP \n"
                                          "NOP \n"
                                          "NOP \n"
                                          "SUBS LR, LR, #1 \n"
                                          "BNE delay_loop \n"
            "delay_end: \n"
                                          "NOP \n"
                                          "NOP \n"
                                          "MOV LR, R1 \n"
    );
}

//
// InitSysCtrl - Initialization of system resources.
//
void
InitSysCtrl(void)
{
    //
    // Disable the watchdog
    //
    DisableDog();

    //
    // Call Flash Initialization to setup flash waitstates
    // This function must reside in RAM
    //
    InitFlash();

    //
    // PLLSYSCLK = (XTAL_OSC) * (IMULT + FMULT) / (PLLSYSCLKDIV) = 20M * 10 / 1 = 200M
    //
    InitSysPll(XTAL_OSC, IMULT_10, FMULT_0, PLLCLK_BY_1);

    WRPRT_DISABLE;
    //
    // Set the APBCLK clock divider to 2 (divide by 2)
    //
    SysCtlRegs.APBCLKDIVCFG.bit.APBCLKDIVCFG = 1;

    //
    // Set the LSPCLK clock divider to 4 (divide by 4)
    //
    ClkCfgRegs.LOSPCP.bit.LSPCLKDIV = 2;
    WRPRT_ENABLE;

    //
    // Call Device_cal function when run using debugger
    // This function is called as part of the Boot code. The function is called
    // in the InitSysCtrl function since during debug time resets, the boot code
    // will not be executed and the initialization script will reinitialize all the
    // registers and the calibrated values will be lost.
    //
    Device_cal();

    //
    // Turn on all peripherals
    //
    InitPeripheralClocks();
}

//
// InitPeripheralClocks - This function initializes the clocks for the
// peripherals. Note: In order to reduce power consumption, turn off the
// clocks to any peripheral that is not specified for your part-number or is
// not used in the application
//
void
InitPeripheralClocks()
{
    WRPRT_DISABLE;

    CpuSysRegs.PCLKCR0.bit.DMA = 1;
    CpuSysRegs.PCLKCR0.bit.TIMER0 = 1;
    CpuSysRegs.PCLKCR0.bit.TIMER1 = 1;
    CpuSysRegs.PCLKCR0.bit.TIMER2 = 1;
    CpuSysRegs.PCLKCR0.bit.HRPWM = 1;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;

    CpuSysRegs.PCLKCR2.bit.PWM1 = 1;
    CpuSysRegs.PCLKCR2.bit.PWM2 = 1;
    CpuSysRegs.PCLKCR2.bit.PWM3 = 1;
    CpuSysRegs.PCLKCR2.bit.PWM4 = 1;
    CpuSysRegs.PCLKCR2.bit.PWM5 = 1;
    CpuSysRegs.PCLKCR2.bit.PWM6 = 1;
    CpuSysRegs.PCLKCR2.bit.PWM7 = 1;
    CpuSysRegs.PCLKCR2.bit.PWM8 = 1;

    CpuSysRegs.PCLKCR3.bit.CAP1 = 1;
    CpuSysRegs.PCLKCR3.bit.CAP2 = 1;
    CpuSysRegs.PCLKCR3.bit.CAP3 = 1;
    CpuSysRegs.PCLKCR3.bit.CAP4 = 1;
    CpuSysRegs.PCLKCR3.bit.CAP5 = 1;
    CpuSysRegs.PCLKCR3.bit.CAP6 = 1;
    CpuSysRegs.PCLKCR3.bit.CAP7 = 1;

    CpuSysRegs.PCLKCR4.bit.QEP1 = 1;
    CpuSysRegs.PCLKCR4.bit.QEP2 = 1;

    CpuSysRegs.PCLKCR6.bit.SD1 = 1;

    CpuSysRegs.PCLKCR7.bit.UART_A = 1;
    CpuSysRegs.PCLKCR7.bit.UART_B = 1;

    CpuSysRegs.PCLKCR8.bit.SPI_A = 1;
    CpuSysRegs.PCLKCR8.bit.SPI_B = 1;

    CpuSysRegs.PCLKCR9.bit.I2C_A = 1;

    CpuSysRegs.PCLKCR10.bit.CAN_A = 1;
    CpuSysRegs.PCLKCR10.bit.CAN_B = 1;

    CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
    CpuSysRegs.PCLKCR13.bit.ADC_B = 1;
    CpuSysRegs.PCLKCR13.bit.ADC_C = 1;

    CpuSysRegs.PCLKCR14.bit.COMP1 = 1;
    CpuSysRegs.PCLKCR14.bit.COMP2 = 1;
    CpuSysRegs.PCLKCR14.bit.COMP3 = 1;
    CpuSysRegs.PCLKCR14.bit.COMP4 = 1;
    CpuSysRegs.PCLKCR14.bit.COMP5 = 1;
    CpuSysRegs.PCLKCR14.bit.COMP6 = 1;
    CpuSysRegs.PCLKCR14.bit.COMP7 = 1;

    CpuSysRegs.PCLKCR16.bit.DAC_A = 1;
    CpuSysRegs.PCLKCR16.bit.DAC_B = 1;

    CpuSysRegs.PCLKCR19.bit.LIN_A = 1;

    CpuSysRegs.PCLKCR20.bit.PMBUS_A = 1;

    CpuSysRegs.PCLKCR21.bit.DCC_0 = 1;

    WRPRT_ENABLE;
}

//
// DisablePeripheralClocks -
//
void
DisablePeripheralClocks()
{
    WRPRT_DISABLE;

    CpuSysRegs.PCLKCR0.all = 0;
    CpuSysRegs.PCLKCR2.all = 0;
    CpuSysRegs.PCLKCR3.all = 0;
    CpuSysRegs.PCLKCR4.all = 0;
    CpuSysRegs.PCLKCR6.all = 0;
    CpuSysRegs.PCLKCR7.all = 0;
    CpuSysRegs.PCLKCR8.all = 0;
    CpuSysRegs.PCLKCR9.all = 0;
    CpuSysRegs.PCLKCR10.all = 0;
    CpuSysRegs.PCLKCR13.all = 0;
    CpuSysRegs.PCLKCR14.all = 0;
    CpuSysRegs.PCLKCR16.all = 0;
    CpuSysRegs.PCLKCR18.all = 0;
    CpuSysRegs.PCLKCR19.all = 0;
    CpuSysRegs.PCLKCR20.all = 0;
    CpuSysRegs.PCLKCR21.all = 0;

    WRPRT_ENABLE;
}

//
// InitFlash - This function initializes the Flash Control registers
//                  CAUTION
// This function MUST be executed out of RAM. Executing it
// out of OTP/Flash will yield unpredictable results
//
__attribute__((section("itcm.ramfunc")))
void
InitFlash(void)
{
    WRPRT_DISABLE;

    //
    // Set the bank fallback power modes to active.
    //
    Flash0CtrlRegs.FBFALLBACK.bit.BNKPWR0 = 0x3;
    Flash0CtrlRegs.FBFALLBACK.bit.BNKPWR0 = 0x3;

    //
    // Disable Cache and prefetch mechanism before changing wait states
    //
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.FACC0_icen = 0;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.FACC0_dcen = 0;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.FACC1_icen = 0;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.FACC1_dcen = 0;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.FACC0_prften = 0;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.FACC1_prften = 0;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.Bus_prften = 0;

    //
    // Set waitstates according to frequency
    //                CAUTION
    // Minimum waitstates required for the flash operating
    // at a given CPU rate must be characterized by G32R501.
    // Refer to the datasheet for the latest information.
    //
    Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x05;

    //
    // Enable Cache and prefetch mechanism to improve performance
    // of code executed from Flash.
    //
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.FACC0_icen = 1;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.FACC0_dcen = 1;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.FACC1_icen = 1;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.FACC1_dcen = 1;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.FACC0_prften = 1;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.FACC1_prften = 1;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.Bus_prften = 1;

    //
    // At reset, ECC is enabled. If it is disabled by application software
    // and if application again wants to enable ECC
    //
    Flash0EccRegs.ECC_ENABLE.bit.DECODE_ENABLE = 0xA;

    WRPRT_ENABLE;

    //
    // Force a pipeline flush to ensure that the write to
    // the last register configured occurs before returning.
    //
    for (int i = 0; i < 7; i++)
    {
        __NOP();
    }
}

//
// FlashOff - This function powers down the flash
//                   CAUTION
// This function MUST be executed out of RAM. Executing it
// out of OTP/Flash will yield unpredictable results.
// Note: a flash access after the flash banks are powered down will
// wake the bank
//
__attribute__((section("itcm.ramfunc")))
void
FlashOff(void)
{
    WRPRT_DISABLE;

    //
    // Configure the fallback power mode as standby
    //
    Flash0CtrlRegs.FBFALLBACK.bit.BNKPWR0 = 0x1;
    Flash0CtrlRegs.FBFALLBACK.bit.BNKPWR0 = 0x1;

    WRPRT_ENABLE;
}

//
// ServiceDog - This function resets the watchdog timer.
// Enable this function for using ServiceDog in the application
//
void
ServiceDog(void)
{
    WRPRT_DISABLE;
    WdtRegs.WDKEY.bit.WDKEY = 0x0055;
    WdtRegs.WDKEY.bit.WDKEY = 0x00AA;
    WRPRT_ENABLE;
}

//
// DisableDog - This function disables the watchdog timer.
//
void
DisableDog(void)
{
    volatile Uint16 temp;
    WRPRT_DISABLE;

    //
    // Grab the clock config so we don't clobber it
    //
    temp = WdtRegs.WDCR.all & 0x0007;
    WdtRegs.WDCR.all = 0x0068 | temp;
    WRPRT_ENABLE;
}

//
// InitPll - This function initializes the PLL registers.
//
// Note: This function uses the DCCOMP to check that the PLLRAWCLK is running at
// the expected rate. If you are using the DCCOMP, you must back up its
// configuration before calling this function and restore it afterward.
//
// Attention : After modifying the CLKSRCCTL1 register, please reconfigure the 
// SYSPLLMULT register to prevent abnormal display of the SYSPLLMULT register.
//
void
InitSysPll(Uint16 clock_source, Uint16 imult, Uint16 fmult, Uint16 divsel)
{
    Uint32 timeout, retries, temp_syspllmult, pllLockStatus;
    bool status;

    if(((clock_source & 0x3) == ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL)    &&
       (((clock_source & 0x4) >> 2) == ClkCfgRegs.XTALCR.bit.SE)           &&
                     (imult  == ClkCfgRegs.SYSPLLMULT.bit.IMULT)           &&
                     (fmult  == ClkCfgRegs.SYSPLLMULT.bit.FMULT)           &&
                     (divsel == ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV))
    {
        //
        // Everything is set as required, so just return
        //
        return;
    }

    if(((clock_source & 0x3) != ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL) ||
       (((clock_source & 0x4) >> 2) != ClkCfgRegs.XTALCR.bit.SE))
    {
        switch (clock_source)
        {
            case INT_OSC1:
                SysIntOsc1Sel();
                break;

            case INT_OSC2:
                SysIntOsc2Sel();
                break;

            case XTAL_OSC:
                SysXtalOscSel();
                break;

            case XTAL_OSC_SE:
                SysXtalOscSESel();
                break;
        }
    }

    WRPRT_DISABLE;

    //
    // First modify the PLL multipliers
    //
    if(imult != ClkCfgRegs.SYSPLLMULT.bit.IMULT ||
       fmult != ClkCfgRegs.SYSPLLMULT.bit.FMULT)
    {
        //
        // Bypass PLL and set dividers to /1
        //
        ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 0;

        //
        // Delay of at least 60 OSCCLK cycles required post PLL bypass
        //
        for (int i = 0; i < 60; i++)
        {
            __NOP();
        }

        ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = 0;

        //
        // Evaluate PLL multipliers
        //
        temp_syspllmult = ((fmult << 8U) | imult);

        //
        // Loop to retry locking the PLL should the DCCOMP module indicate
        // that it was not successful.
        //
        for(retries = 0; (retries < PLL_RETRIES); retries++)
        {
            WRPRT_DISABLE;

            //
            // Disable SYSPLL (Turn off PLL)
            //
            ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 0;

            //
            // Atleast 60 cycle delay between powerdown to powerup
            //
            for (int i = 0; i < 60; i++)
            {
                __NOP();
            }

            //
            // Program PLL multipliers
            //
            ClkCfgRegs.SYSPLLMULT.all = temp_syspllmult;

            //
            // Enable SYSPLL
            //
            ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 1;

            timeout = PLL_LOCK_TIMEOUT;
            pllLockStatus = ClkCfgRegs.SYSPLLSTS.bit.LOCKS;

            //
            // Wait for the SYSPLL lock
            //
            while((pllLockStatus != 1) && (timeout != 0U))
            {
                pllLockStatus = ClkCfgRegs.SYSPLLSTS.bit.LOCKS;
                timeout--;
            }

            WRPRT_ENABLE;

            status = IsPLLValid(clock_source, imult, fmult);

            //
            // Check DCCOMP Status, if no error break the loop
            //
            if(status)
            {
                break;
            }
        }
    }
    else
    {
        status = true;
    }

    if(status)
    {
        WRPRT_DISABLE;
        //
        // Set divider to produce slower output frequency to limit current increase
        //
        if(divsel != PLLCLK_BY_126)
        {
            ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = divsel + 1;
        }
        else
        {
            ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = divsel;
        }

        //
        // Enable PLLSYSCLK is fed from system PLL clock
        //
        ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 1;

        //
        // Small 100 cycle delay
        //
        for (int i = 0; i < 100; i++)
        {
            __NOP();
        }

        //
        // Set the divider to user value
        //
        ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = divsel;
        WRPRT_ENABLE;
    }
}

//
// SysIntOsc1Sel - This function switches to Internal Oscillator 1 and turns
// off all other clock sources to minimize power consumption
//
// Attention : After modifying the CLKSRCCTL1 register, please reconfigure the 
// SYSPLLMULT register to prevent abnormal display of the SYSPLLMULT register.
//
void
SysIntOsc1Sel (void)
{
    WRPRT_DISABLE;
    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 2; // Clk Src = INTOSC1
    ClkCfgRegs.XTALCR.bit.OSCOFF=1;             // Turn off XTALOSC
    WRPRT_ENABLE;
}

//
// SysIntOsc2Sel - This function switches to Internal oscillator 2 from
// External Oscillator and turns off all other clock sources to minimize
// power consumption
// NOTE: If there is no external clock connection, when switching from
//       INTOSC1 to INTOSC2, EXTOSC and XLCKIN must be turned OFF prior
//       to switching to internal oscillator 1
//
// Attention : After modifying the CLKSRCCTL1 register, please reconfigure the 
// SYSPLLMULT register to prevent abnormal display of the SYSPLLMULT register.
//
NO_OPTIMIZE
void
SysIntOsc2Sel (void)
{
    WRPRT_DISABLE;
    ClkCfgRegs.CLKSRCCTL1.bit.INTOSC2OFF=0;         // Turn on INTOSC2
    SYSCTRL_CLKSRCCTL1_DELAY;
    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 0;     // Clk Src = INTOSC2
    ClkCfgRegs.XTALCR.bit.OSCOFF=1;                 // Turn off XTALOSC
    WRPRT_ENABLE;
}

//
// PollX1Counter - Clear the X1CNT counter and then wait for it to saturate
// four times.
//
static void
PollX1Counter(void)
{
    Uint16 loopCount = 0;

    //
    // Delay for 1 ms while the XTALCR powers up
    //
    // 2000 loops, 5 cycles per loop + 9 cycles overhead = 10009 cycles
    //
    for (uint32_t i = 0; i < 2000; i++)
    {
        __NOP();
    }

    //
    // Clear and saturate X1CNT 4 times to guarantee operation
    //
    do
    {
        //
        // Keep clearing the counter until it is no longer saturated
        //
        while(ClkCfgRegs.X1CNT.all > 0x1FF)
        {
            ClkCfgRegs.X1CNT.all |= 0x10000;
        }

        //
        // Wait for the X1 clock to saturate
        //
        while(ClkCfgRegs.X1CNT.all != 0x3FFU)
        {
            ;
        }

        //
        // Increment the counter
        //
        loopCount++;
    }while(loopCount < 4);
}

//
// SysXtalOscSel - This function switches to External CRYSTAL oscillator and
// turns off all other clock sources to minimize power consumption. This option
// may not be available on all device packages
//
// Attention : After modifying the CLKSRCCTL1 register, please reconfigure the 
// SYSPLLMULT register to prevent abnormal display of the SYSPLLMULT register.
//
void
SysXtalOscSel (void)
{
    WRPRT_DISABLE;
    ClkCfgRegs.XTALCR.bit.OSCOFF = 0;     // Turn on XTALOSC
    ClkCfgRegs.XTALCR.bit.SE = 0;         // Select crystal mode
    WRPRT_ENABLE;

    //
    // Wait for the X1 clock to saturate
    //
    PollX1Counter();

    //
    // Select XTALCR as the oscillator source
    //
    WRPRT_DISABLE;
    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 1;
    WRPRT_ENABLE;

    //
    // If a missing clock failure was detected, try waiting for the X1 counter
    // to saturate again. Consider modifying this code to add a 10ms timeout.
    //
    while(ClkCfgRegs.MCDCR.bit.MCLKSTS != 0)
    {
        WRPRT_DISABLE;
        ClkCfgRegs.MCDCR.bit.MCLKCLR = 1;
        WRPRT_ENABLE;

        //
        // Wait for the X1 clock to saturate
        //
        PollX1Counter();

        //
        // Select XTALCR as the oscillator source
        //
        WRPRT_DISABLE;
        ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 1;
        WRPRT_ENABLE;
    }
}

//
// SysXtalOscSESel - This function switches to external oscillator in
// single-ended mode and turns off all other clock sources to minimize power
// consumption. This option may not be available on all device packages
//
// Attention : After modifying the CLKSRCCTL1 register, please reconfigure the 
// SYSPLLMULT register to prevent abnormal display of the SYSPLLMULT register.
//
void
SysXtalOscSESel (void)
{
    WRPRT_DISABLE;
    ClkCfgRegs.XTALCR.bit.OSCOFF = 0;     // Turn on XTALOSC
    ClkCfgRegs.XTALCR.bit.SE = 1;         // Select single-ended mode
    WRPRT_ENABLE;

    //
    // Wait for the X1 clock to saturate
    //
    PollX1Counter();

    //
    // Select XTALOSC as the oscillator source
    //
    WRPRT_DISABLE;
    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 1;
    WRPRT_ENABLE;

    //
    // If missing clock detected, there is something wrong with the oscillator
    // module.
    //
    if(ClkCfgRegs.MCDCR.bit.MCLKSTS != 0)
    {
        ESTOP0;
    }
}

//
// IDLE - Enter IDLE mode
//
void
IDLE()
{
    WRPRT_DISABLE;
    CpuSysRegs.LPMCR.bit.LPM = LPM_IDLE;
    WRPRT_ENABLE;
    __asm(" WFE");
}

//
// HALT - Enter HALT mode
//
void
HALT()
{
    WRPRT_DISABLE;
    CpuSysRegs.LPMCR.bit.LPM = LPM_HALT;
    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 0;
    ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 0;
    WRPRT_ENABLE;
    __asm(" WFE");
}

//*****************************************************************************
//
// SysCtl_isPLLValid()
//
//*****************************************************************************
bool
IsPLLValid(Uint16 oscSource, Uint16 imult, Uint16 fmult)
{
    Uint32 dccCounterSeed0, dccCounterSeed1, dccValidSeed0;

    //
    // Setting Counter0 & Valid Seed Value with +/-12% tolerance
    //
    dccCounterSeed0 = DCCOMP_COUNTER0_WINDOW - 12U;
    dccValidSeed0 = 24U;

    //
    // Multiplying Counter-0 window with PLL Integer Multiplier
    //
    dccCounterSeed1 = DCCOMP_COUNTER0_WINDOW * imult;

    //
    // Multiplying Counter-0 window with PLL Fractional Multiplier
    //
    switch(fmult)
    {
        case FMULT_0pt25:
            //
            // FMULT * CNTR0 Window = 0.25 * 100 = 25, gets added to cntr0
            // seed value
            //
            dccCounterSeed1 = dccCounterSeed1 + 25U;
            break;
        case FMULT_0pt5:
            //
            // FMULT * CNTR0 Window = 0.5 * 100 = 50, gets added to cntr0
            // seed value
            //
            dccCounterSeed1 = dccCounterSeed1 + 50U;
            break;
        case FMULT_0pt75:
            //
            // FMULT * CNTR0 Window = 0.75 * 100 = 75, gets added to cntr0
            // seed value
            //
            dccCounterSeed1 = dccCounterSeed1 + 75U;
            break;
        default:
            //
            // No fractional multiplier
            //
            dccCounterSeed1 = dccCounterSeed1 + 0;
            break;
    }

    //
    // Enable Peripheral Clock Domain PCLKCR21 for DCCOMP
    //
    WRPRT_DISABLE;
    CpuSysRegs.PCLKCR21.bit.DCC_0 = 1;

    //
    // Clear Error & Done Flag
    //
    Dccomp0Regs.DCCOMPFLG.bit.ERRFLG = 1;
    Dccomp0Regs.DCCOMPFLG.bit.SIGDONEFLG = 1;

    //
    // Disable DCCOMP
    //
    Dccomp0Regs.DCCOMPCTRL.bit.DCCOMPEN = 0x5;

    //
    // Disable Error Signal
    //
    Dccomp0Regs.DCCOMPCTRL.bit.ERREN = 0x5;

    //
    // Disable Done Signal
    //
    Dccomp0Regs.DCCOMPCTRL.bit.DONEEN = 0x5;

    //
    // Configure Clock Source0 to whatever is set as a clock source for PLL
    //
    switch(oscSource)
    {
        case INT_OSC1:
            Dccomp0Regs.DCCOMPCLKSRCSEL0.bit.CLKSRCSEL0 = 1; // Clk Src0 = INTOSC1
            break;

        case INT_OSC2:
            Dccomp0Regs.DCCOMPCLKSRCSEL0.bit.CLKSRCSEL0 = 2; // Clk Src0 = INTOSC2
            break;

        case XTAL_OSC:
        case XTAL_OSC_SE:
            Dccomp0Regs.DCCOMPCLKSRCSEL0.bit.CLKSRCSEL0 = 0; // Clk Src0 = XTALCR
            break;
    }

    //
    // Configure Clock Source1 to PLL
    //
    Dccomp0Regs.DCCOMPCLKSRCSEL1.bit.CLKSRCWEN = 0xA; // Clk Src1 Key to enable clock source selection for count1
    Dccomp0Regs.DCCOMPCLKSRCSEL1.bit.CLKSRCSEL1 = 0; // Clk Src1 = PLL

    //
    // Configure COUNTER-0, COUNTER-1 & Valid Window
    //
    Dccomp0Regs.DCCOMPCNTSEED0.bit.CNTSEED0 = dccCounterSeed0; // Loaded Counter0 Value
    Dccomp0Regs.DCCOMPVALSEED0.bit.VALSEED0 = dccValidSeed0;  // Loaded Valid Value
    Dccomp0Regs.DCCOMPCNTSEED1.bit.CNTSEED1 = dccCounterSeed1; // Loaded Counter1 Value

    //
    // Enable Single Shot Mode
    //
    Dccomp0Regs.DCCOMPCTRL.bit.SIGEN = 0xA;

    //
    // Enable Error Signal
    //
    Dccomp0Regs.DCCOMPCTRL.bit.ERREN = 0xA;

    //
    // Enable Done Signal
    //
    Dccomp0Regs.DCCOMPCTRL.bit.DONEEN = 0xA;

    //
    // Enable DCCOMP to start counting
    //
    Dccomp0Regs.DCCOMPCTRL.bit.DCCOMPEN = 0xA;
    WRPRT_ENABLE;

    //
    // Set time out for the loop
    //
    uint32_t timeout = dccCounterSeed1;

    //
    // Wait until Error or Done Flag is generated
    //
    while(((Dccomp0Regs.DCCOMPFLG.all & 3) == 0) && (timeout != 0U))
    {
        timeout--;
    }

    //
    // Returns true if DCCOMP completes without error
    //
    return(((Dccomp0Regs.DCCOMPFLG.all & 3) == 2) && (Dccomp0Regs.DCCOMPCLKSRCCNT0.all == 0) &&
           (Dccomp0Regs.DCCOMPCLKSRCVAL0.all == 0) && (Dccomp0Regs.DCCOMPCLKSRCCNT1.all == 0));
}

//
// End of File
//
