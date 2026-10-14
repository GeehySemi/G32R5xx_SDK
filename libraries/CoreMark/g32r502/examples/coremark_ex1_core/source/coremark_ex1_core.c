//#############################################################################
// FILE:    coremark_ex1_core.c
//
// TITLE:   G32R502 CoreMark Benchmark Example
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
// This example runs the EEMBC CoreMark benchmark on G32R502 EVAL board.
// Results are printed via UARTA on GPIO29 (TX) / GPIO28 (RX).
// SysTick provides the timing tick for CoreMark.
//
//! \addtogroup driver_example_list
//! <h1> G32R502 CoreMark Benchmark </h1>
//!
//! \b External \b Connections \n
//! - GPIO28/UARTA_RX to USB-UART adapter TX
//! - GPIO29/UARTA_TX to USB-UART adapter RX
//! - UART: 115200-8-N-1
//!
//! \b Watch \b Variables \n
//! - CoreMark score printed on UART after benchmark completes
//
//#############################################################################
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
// 1. Modified peripheral register names by Geehy Semiconductor.
//
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include <stdio.h>

unsigned int system_tick = 0;

extern void CoreMark_main(void);

#if defined(G32R502_RUN_IN_CBUS_FLASH)
  #define CURRENT_RUN_REGION_NAME  "CBUS Flash"

#elif defined(G32R502_RUN_IN_ITCM_RAM)
  #define CURRENT_RUN_REGION_NAME  "ITCM RAM"

#else
  #error "Please define one of: G32R502_RUN_IN_CBUS_FLASH, G32R502_RUN_IN_ITCM_RAM"
#endif


//
// Function Prototypes
//
void UART_Init(void);

//
// Main
//
void example_main(void)
{
    //
    // Initializes system control, device clock, and peripherals
    //
    Device_init();
    
    // Enable Instruction Cache
    SCB_EnableICache();

    // Enable Data Cache
    SCB_EnableDCache();

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
    // Board Initialization
    //
    Board_init();

    //
    // Enables CPU interrupts
    //
    Interrupt_enableMaster();
    
    
    SysTick_Config(SystemCoreClock / 1000);
    
    //
    // UART initialize
    //
    UART_Init();

    printf("\r\n");
    printf("\r\n");
    printf("******************************************\r\n");
    printf("G32R502 CoreMark \r\n");
    printf("Run Region: %s \r\n",CURRENT_RUN_REGION_NAME);
    printf("SystemCoreClock: %d Hz\r\n",SystemCoreClock);
    printf("******************************************\r\n");

    CoreMark_main();

    //
    // Loop.
    //
    for(;;)
    {
        GPIO_togglePin(myGPIOOutput0);
        DEVICE_DELAY_US(1000000);
    }
}

//
// UART initialize
//
void UART_Init(void)
{
    //
    // GPIO28 is the UART Rx pin.
    //
    GPIO_setPinConfig(GPIO_28_UARTA_RX);
    GPIO_setDirectionMode(28U, GPIO_DIR_MODE_IN);
    GPIO_setDrivingCapability(28U, GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(28U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(28U, GPIO_QUAL_ASYNC);

    //
    // GPIO29 is the UART Tx pin.
    //
    GPIO_setPinConfig(GPIO_29_UARTA_TX);
    GPIO_setDirectionMode(29U, GPIO_DIR_MODE_OUT);
    GPIO_setDrivingCapability(29U, GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(29U, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(29U, GPIO_QUAL_ASYNC);

    //
    // Initialize UARTA and its FIFO.
    //
    UART_performSoftwareReset(UARTA_BASE);

    //
    // Configure UARTA for printf output.
    //
    UART_setConfig(UARTA_BASE, DEVICE_LSPCLK_FREQ, 115200, (UART_CONFIG_WLEN_8 |
                                                        UART_CONFIG_STOP_ONE |
                                                        UART_CONFIG_PAR_NONE));
    UART_resetChannels(UARTA_BASE);
    UART_resetRxFIFO(UARTA_BASE);
    UART_resetTxFIFO(UARTA_BASE);
    UART_clearInterruptStatus(UARTA_BASE, UART_INT_TXFF | UART_INT_RXFF);
    UART_enableFIFO(UARTA_BASE);
    UART_enableModule(UARTA_BASE);
    UART_performSoftwareReset(UARTA_BASE);
}


/*!
 * @brief       Decrements the system_tick
 *
 * @param       None
 *
 * @retval      None
 */
void system_tick_fun(void)
{
    system_tick++;
}

/*!
 * @brief   This function handles SysTick Handler
 *
 * @param   None
 *
 * @retval  None
 *
 */
void SysTick_Handler(void)
{
    system_tick_fun();
}


#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
//
// Redefine the fputc function to the serial port
//
int fputc(int ch, FILE* f)
{
    UART_writeCharBlockingNonFIFO(UARTA_BASE, (uint8_t)ch);

    return (ch);
}
#elif defined(__ICCARM__)
int __io_putchar(int ch)
{
    UART_writeCharBlockingNonFIFO(UARTA_BASE, (uint8_t)ch);

    return (ch);
}

//
// __write - write.
//
int __write(int file, char* ptr, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        __io_putchar(*ptr++);
    }

    return len;
}
#elif defined (__clang__) && !defined (__ARMCC_VERSION)
//
// uart_putc - uart putc.
//
int uart_putc(char ch, FILE *file)
{
    UART_writeCharBlockingNonFIFO(UARTA_BASE, (uint8_t)ch);

    return (ch);
}

static FILE __stdio = FDEV_SETUP_STREAM(uart_putc, NULL, NULL, _FDEV_SETUP_WRITE);
FILE *const stdin = &__stdio;

__strong_reference(stdin, stdout);
__strong_reference(stdin, stderr);

#elif defined (__GNUC__)

/*!
* @brief       Redirect C Library function printf to serial port.
*              After Redirection, you can use printf function.
*
* @param       ch:  The characters that need to be send.
*
* @retval      The characters that need to be send.
*
* @note
*/
int __io_putchar(int ch)
{
    UART_writeCharBlockingNonFIFO(UARTA_BASE, (uint8_t)ch);

    return ch;
}

/*!
* @brief       Redirect C Library function printf to serial port.
*              After Redirection, you can use printf function.
*
* @param       file:  Meaningless in this function.
*
* @param       *ptr:  Buffer pointer for data to be sent.
*
* @param       len:  Length of data to be sent.
*
* @retval      The characters that need to be send.
*
* @note
*/
int _write(int file, char* ptr, int len)
{
    int i;

    (void)(file);

    for (i = 0; i < len; i++)
    {
        __io_putchar(*ptr++);
    }

    return len;
}

#endif

//
// End of File
//

