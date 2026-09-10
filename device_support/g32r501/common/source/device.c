//#############################################################################
//
// FILE:    device.c
//
// TITLE:   Device setup for examples.
//
// VERSION: 1.0.1
//
// DATE:    2025-04-15
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
// 1. Updated header file title for G32R501 device setup definitions.
// 2. Changed file name to g32r501_device.c to reflect the architecture.
// 3. Adjusted clock and peripheral initialization functions for G32R501.
// 4. Updated calls to use G32R501-specific structures and definitions.
//
//###########################################################################

//
// Included Files
//
#include "device.h"
#include "driverlib.h"

#define PASS 0
#define FAIL 1

uint32_t Example_PassCount = 0;
uint32_t Example_Fail = 0;

//*****************************************************************************
//
// Function to initialize the device. Primarily initializes system control to a
// known state by disabling the watchdog, setting up the SYSCLKOUT frequency,
// and enabling the clocks to the peripherals.
// The function also configures the GPIO pins 22 and 23 in digital mode.
// To configure these pins as analog pins, use the function GPIO_setAnalogMode
//
// Note : In case XTAL is used as the PLL source, it is recommended to invoke
// the Device_verifyXTAL() before configuring PLL
//
//*****************************************************************************
void Device_init(void)
{
    //
    // Disable the watchdog
    //
    SysCtl_disableWatchdog();

    //
    // Call Flash Initialization to setup flash waitstates. This function must
    // reside in RAM.
    //
    Flash_initModule(FLASH0CTRL_BASE, FLASH0ECC_BASE, DEVICE_FLASH_WAITSTATES);

    //
    // Set up PLL control and clock dividers
    //
    SysCtl_setClock(DEVICE_SETCLOCK_CFG);

    //
    // Set the APBCLK clock divider to 2 (divide by 2)
    //
    SysCtl_setAPBClock(SYSCTL_APBCLK_PRESCALE_2);

    //
    // Set the LSPCLK clock divider to 4 (divide by 4)
    //
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_4);

    //
    // Update SystemCoreClock variable
    //
    SystemCoreClockUpdate();

    //
    // These asserts will check that the #defines for the clock rates in
    // device.h match the actual rates that have been configured. If they do
    // not match, check that the calculations of DEVICE_SYSCLK_FREQ, DEVICE_APBCLK_FREQ and
    // DEVICE_LSPCLK_FREQ are accurate. Some examples will not perform as
    // expected if these are not correct.
    //
    ASSERT(SysCtl_getClock(DEVICE_OSCSRC_FREQ) == DEVICE_SYSCLK_FREQ);
    ASSERT(SysCtl_getAPBClock(DEVICE_OSCSRC_FREQ) == DEVICE_APBCLK_FREQ);
    ASSERT(SysCtl_getLowSpeedClock(DEVICE_OSCSRC_FREQ) == DEVICE_LSPCLK_FREQ);

    //
    // Call Device_cal function when run using debugger
    // This function is called as part of the Boot code. The function is called
    // in the Device_init function since during debug time resets, the boot code
    // will not be executed and the gel script will reinitialize all the
    // registers and the calibrated values will be lost.
    // Sysctl_deviceCal is a wrapper function for Device_Cal
    //
    SysCtl_deviceCal();

    //
    // Turn on all peripherals
    //
    Device_enableAllPeripherals();
}

//*****************************************************************************
//
// Function to turn on all peripherals, enabling reads and writes to the
// peripherals' registers.
//
// Note that to reduce power, unused peripherals should be disabled.
//
//*****************************************************************************
void Device_enableAllPeripherals(void)
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_HRPWM);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_QSPI);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM7);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM8);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAP2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAP3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAP4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAP5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAP6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAP7);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_QEP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_QEP2);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SDF);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTB);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIB);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CA);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANB);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCC);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_COMP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_COMP2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_COMP3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_COMP4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_COMP5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_COMP6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_COMP7);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DACA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DACB);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_LINA);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PMBUSA);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FLB1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FLB2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FLB3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FLB4);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DCCOMP0);
}

//*****************************************************************************
//
// Function to disable pin locks and enable pullups on GPIOs.
//
//*****************************************************************************
void Device_initGPIO(void)
{
    //
    // Disable pin locks.
    //
    GPIO_unlockPortConfig(GPIO_PORT_A, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_B, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_H, 0xFFFFFFFF);
}

//*****************************************************************************
//
// Function to verify the XTAL frequency
// freq is the XTAL frequency in MHz
// The function return true if the the actual XTAL frequency matches with the
// input value
//
// Note that this function assumes that the PLL is not already configured and
// hence uses SysClk freq = 10MHz for DCCOMP calculation
//
//*****************************************************************************
bool Device_verifyXTAL(float freq)
{
    //
    // Use DCCOMP to verify the XTAL frequency using INTOSC2 as reference clock
    //

    //
    // Turn on XTAL and wait for it to power up using X1CNT
    //

    //
    // Enable DCCOMP0 clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DCCOMP0);

    //
    // Insert atleast 5 cycles delay after enabling the peripheral clock
    //
    __asm("NOP");
    __asm("NOP");
    __asm("NOP");
    __asm("NOP");
    __asm("NOP");

    //
    // Configures XTAL as CLKSRC0 and INTOSC2 as CLKSRC1
    // Fclk0 = XTAL frequency (input parameter)
    // Fclk1 = INTOSC2 frequency = 10MHz
    //
    // Configuring DCCOMP error tolerance of +/-1%
    // INTOSC2 can have a variance in frequency of +/-10%
    //
    // Assuming PLL is not already configured, SysClk freq = 10MHz
    //
    // Note : Update the tolerance and INTOSC2 frequency variance as necessary.
    //
    return (DCCOMP_verifyClockFrequency(DCCOMP0_BASE,
                                     DCCOMP_COUNT1SRC_INTOSC2, 10.0F,
                                     DCCOMP_COUNT0SRC_XTAL, freq,
                                     1.0F, 10.0F, 10.0F));

}

//*****************************************************************************
//
// The function to achieve a delay in microseconds.
//
//*****************************************************************************
SECTION_ITCM_RAMFUNC
void DEVICE_DELAY_US(uint32_t x)
{
    SysCtl_delay((uint32_t)(((((long double)(x)) / (1000000.0L /  \
                              (long double)SystemCoreClock)) - 9.0L) / 5.0L));
}

//*****************************************************************************
//
// Error handling function to be called when an ASSERT is violated
//
//*****************************************************************************
void __error__(const char *filename, uint32_t line)
{
    //
    // An ASSERT condition was evaluated as false. You can use the filename and
    // line parameters to determine what went wrong.
    //
    ESTOP0;
}

//
// End of file
//
