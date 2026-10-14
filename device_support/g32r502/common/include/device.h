//#############################################################################
//
// FILE:    device.h
//
// TITLE:   Device setup for examples.
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
// 1. Updated device configuration definitions and peripheral register 
//    mappings for G32R502.
// 2. Adjusted clock configuration parameters for improved performance.
// 3. Changed GPIO pin assignments to match the G32R502 eval specifications.
// 4. Optimized delay macros for better timing accuracy in microsecond delays.
// 5. Aligned G32R502_EVAL GPIO macros with G32R502 EVAL V1.0 schematic
//    (docs/develop/eval_board); replaced legacy G32R501-style pinout.
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
#ifdef G32R502_EVAL
//
// EVAL Board
//

//
// LEDs
//
#define DEVICE_GPIO_PIN_LED1        35U  // GPIO number for LD1
#define DEVICE_GPIO_PIN_LED2        49U  // GPIO number for LD2
#define DEVICE_GPIO_CFG_LED1        GPIO_35_GPIO35  // "pinConfig" for LD1
#define DEVICE_GPIO_CFG_LED2        GPIO_49_GPIO49  // "pinConfig" for LD2

//
// CANA
//
#define DEVICE_GPIO_PIN_CANTXA      4U  // GPIO number for CANTXA
#define DEVICE_GPIO_PIN_CANRXA      5U  // GPIO number for CANRXA
#define DEVICE_GPIO_CFG_CANRXA      GPIO_5_CANA_RX  // "pinConfig" for CANA RX
#define DEVICE_GPIO_CFG_CANTXA      GPIO_4_CANA_TX  // "pinConfig" for CANA TX

//
// CANFD
//
#define DEVICE_GPIO_PIN_CANFDTXA    4U  // GPIO number for CANFDTXA
#define DEVICE_GPIO_PIN_CANFDRXA    5U  // GPIO number for CANFDRXA
#define DEVICE_GPIO_CFG_CANFDRXA    GPIO_5_CANFD_RX  // "pinConfig" for CANFD RX
#define DEVICE_GPIO_CFG_CANFDTXA    GPIO_4_CANFD_TX  // "pinConfig" for CANFD TX

//
// UARTB
//
#define DEVICE_GPIO_PIN_UARTRXDB     23U               // GPIO number for UARTB RX
#define DEVICE_GPIO_PIN_UARTTXDB     40U               // GPIO number for UARTB TX
#define DEVICE_GPIO_CFG_UARTRXDB     GPIO_23_UARTB_RX  // "pinConfig" for UARTB RX
#define DEVICE_GPIO_CFG_UARTTXDB     GPIO_40_UARTB_TX  // "pinConfig" for UARTB TX

//
// LINA
//
#define DEVICE_GPIO_PIN_LINTXA      28U  // GPIO number for LINA TX
#define DEVICE_GPIO_PIN_LINRXA      29U  // GPIO number for LINA RX
#define DEVICE_GPIO_CFG_LINTXA      GPIO_28_LINA_TX  // "pinConfig" for LINA TX
#define DEVICE_GPIO_CFG_LINRXA      GPIO_29_LINA_RX  // "pinConfig" for LINA RX

//
// SPIA
//
#define DEVICE_GPIO_PIN_SPISIMOA    8U  // GPIO number for SPI SIMOA
#define DEVICE_GPIO_PIN_SPICLKA     9U  // GPIO number for SPI CLKA
#define DEVICE_GPIO_PIN_SPISOMIA    10U  // GPIO number for SPI SOMIA
#define DEVICE_GPIO_PIN_SPISTEA     11U  // GPIO number for SPI STEA
#define DEVICE_GPIO_CFG_SPISIMOA    GPIO_8_SPIA_SIMO   // "pinConfig" for SPI SIMOA
#define DEVICE_GPIO_CFG_SPICLKA     GPIO_9_SPIA_CLK    // "pinConfig" for SPI CLKA
#define DEVICE_GPIO_CFG_SPISOMIA    GPIO_10_SPIA_SOMI  // "pinConfig" for SPI SOMIA
#define DEVICE_GPIO_CFG_SPISTEA     GPIO_11_SPIA_STE   // "pinConfig" for SPI STEA

//
// I2CA
//
#define DEVICE_GPIO_PIN_SDAA        26U  // GPIO number for I2CA SDA
#define DEVICE_GPIO_PIN_SCLA        27U  // GPIO number for I2CA SCL
#define DEVICE_GPIO_CFG_SDAA        GPIO_26_I2CA_SDA  // "pinConfig" for I2CA SDA
#define DEVICE_GPIO_CFG_SCLA        GPIO_27_I2CA_SCL  // "pinConfig" for I2CA SCL

//
// I2CB
//
#define DEVICE_GPIO_PIN_SDAB        2U   // GPIO number for I2CB SDA
#define DEVICE_GPIO_PIN_SCLB        3U   // GPIO number for I2CB SCL
#define DEVICE_GPIO_CFG_SDAB        GPIO_2_I2CB_SDA   // "pinConfig" for I2CB SDA
#define DEVICE_GPIO_CFG_SCLB        GPIO_3_I2CB_SCL   // "pinConfig" for I2CB SCL

//
// QEP1
//
#define DEVICE_GPIO_PIN_QEP1A      20U  // GPIO number for QEP1 A
#define DEVICE_GPIO_PIN_QEP1B      41U  // GPIO number for QEP1 B
#define DEVICE_GPIO_PIN_QEP1I      43U  // GPIO number for QEP1 INDEX
#define DEVICE_GPIO_CFG_QEP1A      GPIO_20_QEP1_A      // "pinConfig" for QEP1 A
#define DEVICE_GPIO_CFG_QEP1B      GPIO_41_QEP1_B      // "pinConfig" for QEP1 B
#define DEVICE_GPIO_CFG_QEP1I      GPIO_43_QEP1_INDEX  // "pinConfig" for QEP1 INDEX

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
// UARTA
//
#define DEVICE_GPIO_PIN_UARTRXDA     28U               // GPIO number for UARTA RX
#define DEVICE_GPIO_PIN_UARTTXDA     29U               // GPIO number for UARTA TX
#define DEVICE_GPIO_CFG_UARTRXDA     GPIO_28_UARTA_RX // "pinConfig" for UARTA RX
#define DEVICE_GPIO_CFG_UARTTXDA     GPIO_29_UARTA_TX // "pinConfig" for UARTA TX


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
// AHB bus clock on G32R502 equals SYSCLK (200 MHz at default eval PLL).
// Use DEVICE_AHBCLK_FREQ for AHB-mounted peripheral time-base and period math.
//
#define DEVICE_AHBCLK_FREQ          DEVICE_SYSCLK_FREQ

//
// 100MHz APBCLK frequency based on the above DEVICE_SYSCLK_FREQ and a default
// APB peripheral clock divider of 2. Update the code below if a
// different APBCLK divider is used!
//
#define DEVICE_APBCLK_FREQ          (DEVICE_SYSCLK_FREQ / 2)

//
// 25MHz LSPCLK frequency based on the above DEVICE_APBCLK_FREQ and a default
// low speed peripheral clock divider of 4. Update the code below if a
// different LSPCLK divider is used!
//
#define DEVICE_LSPCLK_FREQ          (DEVICE_APBCLK_FREQ / 4)

//
// DMA address offsets (CPU pointer -> DMA programming view; >>1 in DMA API)
//
#define DMA_ITCM_ADDR_OFFSET        0xA0000000UL
#define DMA_DTCM_ADDR_OFFSET        0x80100000UL

#define DMA_ADDR_ITCM(cpuPtr)       ((uint32_t)(cpuPtr) + DMA_ITCM_ADDR_OFFSET)
#define DMA_ADDR_DTCM(cpuPtr)       ((uint32_t)(cpuPtr) + DMA_DTCM_ADDR_OFFSET)

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
