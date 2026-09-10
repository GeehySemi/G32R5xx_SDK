//#############################################################################
//
// FILE:    device.h
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
// 1. Updated device configuration definitions and peripheral register 
//    mappings for G32R501.
// 2. Adjusted clock configuration parameters for improved performance.
// 3. Changed GPIO pin assignments to match the G32R501 eval specifications.
// 4. Optimized delay macros for better timing accuracy in microsecond delays.
//
//###########################################################################


#ifndef __DEVICE_H__
#define __DEVICE_H__

#ifdef __cplusplus
extern "C"
{
#endif
//
// Included Files
//
#include "driverlib.h"

//*****************************************************************************
//
// Defines for pin numbers and other GPIO configuration
//
//*****************************************************************************
#ifdef G32R501_EVAL
//
// EVAL Board
//

//
// LEDs
//
#define DEVICE_GPIO_PIN_LED1        23U  // GPIO number for LD1
#define DEVICE_GPIO_PIN_LED2        34U  // GPIO number for LD2
#define DEVICE_GPIO_CFG_LED1        GPIO_23_GPIO23  // "pinConfig" for LD1
#define DEVICE_GPIO_CFG_LED2        GPIO_34_GPIO34  // "pinConfig" for LD2

//
// CANA
//
#define DEVICE_GPIO_PIN_CANTXA      32U  // GPIO number for CANTXA
#define DEVICE_GPIO_PIN_CANRXA      33U  // GPIO number for CANRXA
#define DEVICE_GPIO_CFG_CANRXA      GPIO_33_CANA_RX  // "pinConfig" for CANA RX
#define DEVICE_GPIO_CFG_CANTXA      GPIO_32_CANA_TX  // "pinConfig" for CANA TX

//
// CAN External Loopback
//
#define DEVICE_GPIO_CFG_CANRXB      GPIO_10_CANB_RX  // "pinConfig" for CANB RX
#define DEVICE_GPIO_CFG_CANTXB      GPIO_8_CANB_TX   // "pinConfig" for CANB TX


//
// LINA
//
#define DEVICE_GPIO_CFG_LINTXA      GPIO_37_LINA_TX  // "pinConfig" for LINA TX
#define DEVICE_GPIO_CFG_LINRXA      GPIO_35_LINA_RX  // "pinConfig" for LINA RX

//
// SPI
//
#define DEVICE_GPIO_PIN_SPICLKA     56U  // GPIO number for SPI CLKA
#define DEVICE_GPIO_PIN_SPISIMOA    16U  // GPIO number for SPI SIMOA
#define DEVICE_GPIO_PIN_SPISOMIA    17U  // GPIO number for SPI SOMIA
#define DEVICE_GPIO_PIN_SPISTEA     57U  // GPIO number for SPI STEA
#define DEVICE_GPIO_CFG_SPICLKA     GPIO_56_SPIA_CLK   // "pinConfig" for SPI CLKA
#define DEVICE_GPIO_CFG_SPISIMOA    GPIO_16_SPIA_SIMO  // "pinConfig" for SPI SIMOA
#define DEVICE_GPIO_CFG_SPISOMIA    GPIO_17_SPIA_SOMI  // "pinConfig" for SPI SOMIA
#define DEVICE_GPIO_CFG_SPISTEA     GPIO_57_SPIA_STE   // "pinConfig" for SPI STEA
#define DEVICE_GPIO_PIN_SPICLKB     22U  // GPIO number for SPI CLKB
#define DEVICE_GPIO_PIN_SPISIMOB    24U  // GPIO number for SPI SIMOB
#define DEVICE_GPIO_PIN_SPISOMIB    31U  // GPIO number for SPI SOMIB
#define DEVICE_GPIO_PIN_SPISTEB     27U  // GPIO number for SPI STEB
#define DEVICE_GPIO_CFG_SPICLKB     GPIO_22_SPIB_CLK   // "pinConfig" for SPI CLKB
#define DEVICE_GPIO_CFG_SPISIMOB    GPIO_24_SPIB_SIMO  // "pinConfig" for SPI SIMOB
#define DEVICE_GPIO_CFG_SPISOMIB    GPIO_31_SPIB_SOMI  // "pinConfig" for SPI SOMIB
#define DEVICE_GPIO_CFG_SPISTEB     GPIO_27_SPIB_STE   // "pinConfig" for SPI STEB

//
// I2C
//
#define DEVICE_GPIO_PIN_SDAA        35U  // GPIO number for I2C SDAA
#define DEVICE_GPIO_PIN_SCLA        37U  // GPIO number for I2C SCLA
#define DEVICE_GPIO_CFG_SDAA        GPIO_35_I2CA_SDA  // "pinConfig" for I2C SDAA
#define DEVICE_GPIO_CFG_SCLA        GPIO_37_I2CA_SCL  // "pinConfig" for I2C SCLA

//
// QEP
//
#define DEVICE_GPIO_PIN_QEP1A      35U  // GPIO number for QEP 1A
#define DEVICE_GPIO_PIN_QEP1B      37U  // GPIO number for QEP 1B
#define DEVICE_GPIO_PIN_QEP1I      59U  // GPIO number for QEP 1I
#define DEVICE_GPIO_CFG_QEP1A      GPIO_35_QEP1_A  // "pinConfig" for QEP 1A
#define DEVICE_GPIO_CFG_QEP1B      GPIO_37_QEP1_B  // "pinConfig" for QEP 1B
#define DEVICE_GPIO_CFG_QEP1I      GPIO_59_QEP1_INDEX  // "pinConfig" for QEP 1I

//
// PWM
//
#define DEVICE_PERIPHERAL_BASE_PWM PWM6_BASE  // Base peripheral PWM 6
#define DEVICE_PERIPHERAL_INT_PWM  INT_PWM6   // Base peripheral PWM 6 interrupt
#define DEVICE_GPIO_PIN_PWMxA      10U  // GPIO number for PWM6A
#define DEVICE_GPIO_PIN_PWMxB      11U  // GPIO number for PWM6B
#define DEVICE_GPIO_PIN_IOINDEX    8U   // GPIO number for IO Index
#define DEVICE_GPIO_CFG_PWMxA      GPIO_10_PWM6_A  // "pinConfig" for PWM6A
#define DEVICE_GPIO_CFG_PWMxB      GPIO_11_PWM6_B  // "pinConfig" for PWM6B
#define DEVICE_GPIO_CFG_IOINDEX    GPIO_8_GPIO8    // "pinConfig" for IO Index

#endif

#define DEVICE_GPIO_CFG_PWM1A      GPIO_0_PWM1_A  // "pinConfig" for PWM1A
#define DEVICE_GPIO_PIN_PWM1A      0U              // GPIO number for PWM1A
//
// UART for USB-to-UART adapter on FTDI chip
//
#define DEVICE_GPIO_PIN_UARTRXDA     28U               // GPIO number for UART RX
#define DEVICE_GPIO_PIN_UARTTXDA     29U               // GPIO number for UART TX
#define DEVICE_GPIO_CFG_UARTRXDA     GPIO_28_UARTA_RX // "pinConfig" for UART RX
#define DEVICE_GPIO_CFG_UARTTXDA     GPIO_29_UARTA_TX // "pinConfig" for UART TX

//*****************************************************************************
//
// Defines related to clock configuration
//
//*****************************************************************************
//
// 20MHz XTAL on EVAL Board. For use with SysCtl_getClock().
//
#define DEVICE_OSCSRC_FREQ          20000000U

//
// Define to pass to SysCtl_setClock(). Will configure the clock as follows:
// PLLSYSCLK = 20MHz (XTAL_OSC) * (10 (IMULT) + 0.0 (FMULT)) / (1 (ODIV) * 1 (SYSDIV))
//
#define DEVICE_SETCLOCK_CFG         (SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(10) | \
                                     SYSCTL_FMULT_NONE | SYSCTL_ODIV(1) | SYSCTL_SYSDIV(1) | \
                                     SYSCTL_PLL_ENABLE)

//
// 200MHz SYSCLK frequency based on the above DEVICE_SETCLOCK_CFG. Update the
// code below if a different clock configuration is used!
//
#define DEVICE_SYSCLK_FREQ          ((DEVICE_OSCSRC_FREQ * 10) / (1 * 1))

//
// 125MHz APBCLK frequency based on the above DEVICE_SYSCLK_FREQ and a default
// APB peripheral clock divider of 2. Update the code below if a
// different LSPCLK divider is used!
//
#define DEVICE_APBCLK_FREQ          (DEVICE_SYSCLK_FREQ / 2)

//
// 31.25MHz LSPCLK frequency based on the above DEVICE_APBCLK_FREQ and a default
// low speed peripheral clock divider of 4. Update the code below if a
// different LSPCLK divider is used!
//
#define DEVICE_LSPCLK_FREQ          (DEVICE_APBCLK_FREQ / 4)

//*****************************************************************************
//
// Defines, Globals, and Header Includes related to Flash Support
//
//*****************************************************************************
#define DEVICE_FLASH_WAITSTATES 5


extern uint32_t Example_PassCount;
extern uint32_t Example_Fail;

//*****************************************************************************
//
// Function Prototypes
//
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//
//! \addtogroup device_api
//! @{
//
//***
//*****************************************************************************
//
//! @brief Function to initialize the device. Primarily initializes system control to a
//! known state by disabling the watchdog, setting up the SYSCLKOUT frequency,
//! and enabling the clocks to the peripherals.
//! The function also configures the GPIO pins 22 and 23 in digital mode.
//! To configure these pins as analog pins, use the function GPIO_setAnalogMode
//!
//! \return None
//
//*****************************************************************************
extern void Device_init(void);

//*****************************************************************************
//
//!
//! @brief Function to verify the XTAL frequency
//! \param freq is the XTAL frequency in MHz
//! \return The function return true if the the actual XTAL frequency matches with the
//! input value
//
//*****************************************************************************
extern bool Device_verifyXTAL(float freq);

//*****************************************************************************
//!
//!
//! @brief Function to turn on all peripherals, enabling reads and writes to the
//! peripherals' registers.
//!
//! Note that to reduce power, unused peripherals should be disabled.
//!
//! \return None
//
//*****************************************************************************
extern void Device_enableAllPeripherals(void);

//*****************************************************************************
//!
//!
//! @brief Function to disable pin locks and enable pullups on GPIOs.
//!
//! \return None
//
//*****************************************************************************
extern void Device_initGPIO(void);

//*****************************************************************************
//!
//! @brief DEVICE_DELAY_US to call SysCtl_delay() to achieve a delay in microseconds.
//! The DEVICE_DELAY_US will convert the desired delay in microseconds to the count
//! value expected by the function.
//! \param x is the number of microseconds to delay.
//! \return None
//
//*****************************************************************************
extern void DEVICE_DELAY_US(uint32_t x);

//*****************************************************************************
//!
//! @brief Error handling function to be called when an ASSERT is violated
//!
//! \param *filename File name in which the error has occurred
//! \param line Line number within the file
//! \return None
//
//*****************************************************************************
extern void __error__(const char *filename, uint32_t line);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

#ifdef __cplusplus
}
#endif

#endif // __DEVICE_H__

//
// End of file
//
