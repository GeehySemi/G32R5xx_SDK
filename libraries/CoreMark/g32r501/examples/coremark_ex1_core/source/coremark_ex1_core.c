//#############################################################################
// FILE:    coremark_ex1_core.c
//
// TITLE:   G32R501 CoreMark Benchmark Example
//
// VERSION: 1.0.0
//
// DATE:    2026-08-28
//
// This example runs the EEMBC CoreMark benchmark on G32R501 EVAL board.
// Results are printed via UARTA on GPIO29 (TX) / GPIO28 (RX).
// SysTick provides the timing tick for CoreMark.
//
//! \addtogroup driver_example_list
//! <h1> G32R501 CoreMark Benchmark </h1>
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
//   Neither the name of Geehy Semiconductor nor the names of
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
//#############################################################################

#include "driverlib.h"
#include "device.h"
#include "board.h"
#include <stdio.h>

/* SysTick counter must live in DTCM: on ITCM-RAM builds plain .bss lands in
 * cacheable SRAM3, so DCache can hide ISR updates from CoreMark timing. */
SECTION_DTCM_BSS volatile unsigned int system_tick = 0;

extern void CoreMark_main(void);

#if defined(G32R501_RUN_IN_CBUS_FLASH)
  #define CURRENT_RUN_REGION_NAME  "CBUS Flash"
  #define CURRENT_RUN_MACRO_NAME   "G32R501_RUN_IN_CBUS_FLASH"
#elif defined(G32R501_RUN_IN_ITCM_FLASH)
  #define CURRENT_RUN_REGION_NAME  "ITCM Flash"
  #define CURRENT_RUN_MACRO_NAME   "G32R501_RUN_IN_ITCM_FLASH"
#elif defined(G32R501_RUN_IN_ITCM_RAM)
  #define CURRENT_RUN_REGION_NAME  "ITCM RAM"
  #define CURRENT_RUN_MACRO_NAME   "G32R501_RUN_IN_ITCM_RAM"
#else
  #error "Please define one of: G32R501_RUN_IN_CBUS_FLASH, G32R501_RUN_IN_ITCM_FLASH, G32R501_RUN_IN_ITCM_RAM"
#endif

void UART_Init(void);

void example_main(void)
{
    Device_init();

    SCB_EnableICache();
    SCB_EnableDCache();

    Interrupt_initModule();
    Interrupt_initVectorTable();

    Board_init();

    Interrupt_enableMaster();

    SysTick_Config(SystemCoreClock / 1000U);

    UART_Init();

    printf("\r\n");
    printf("\r\n");
    printf("******************************************\r\n");
    printf("G32R501 CoreMark \r\n");
    printf("Run Region: %s \r\n", CURRENT_RUN_REGION_NAME);
    printf("Run Macro: %s \r\n", CURRENT_RUN_MACRO_NAME);
    printf("Opt Level: -O2 \r\n");
    printf("SystemCoreClock: %lu Hz\r\n", (unsigned long)SystemCoreClock);
    printf("******************************************\r\n");

    CoreMark_main();

    for(;;)
    {
        GPIO_togglePin(myGPIOOutput0);
        DEVICE_DELAY_US(1000000);
    }
}

void UART_Init(void)
{
    GPIO_setPinConfig(GPIO_28_UARTA_RX);
    GPIO_setDirectionMode(28U, GPIO_DIR_MODE_IN);
    GPIO_setDrivingCapability(28U, GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(28U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(28U, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(GPIO_29_UARTA_TX);
    GPIO_setDirectionMode(29U, GPIO_DIR_MODE_OUT);
    GPIO_setDrivingCapability(29U, GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(29U, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(29U, GPIO_QUAL_ASYNC);

    UART_performSoftwareReset(UARTA_BASE);

    UART_setConfig(UARTA_BASE, DEVICE_LSPCLK_FREQ, 115200,
                   (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UART_resetChannels(UARTA_BASE);
    UART_resetRxFIFO(UARTA_BASE);
    UART_resetTxFIFO(UARTA_BASE);
    UART_clearInterruptStatus(UARTA_BASE, UART_INT_TXFF | UART_INT_RXFF);
    UART_enableFIFO(UARTA_BASE);
    UART_enableModule(UARTA_BASE);
    UART_performSoftwareReset(UARTA_BASE);
}

void system_tick_fun(void)
{
    system_tick++;
}

void SysTick_Handler(void)
{
    system_tick_fun();
}

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
int fputc(int ch, FILE* f)
{
    (void)f;
    UART_writeCharBlockingNonFIFO(UARTA_BASE, (uint8_t)ch);
    return (ch);
}
#elif defined(__ICCARM__)
int __io_putchar(int ch)
{
    UART_writeCharBlockingNonFIFO(UARTA_BASE, (uint8_t)ch);
    return (ch);
}

int __write(int file, char* ptr, int len)
{
    int i;
    (void)file;
    for (i = 0; i < len; i++)
    {
        __io_putchar(*ptr++);
    }
    return len;
}
#elif defined (__clang__) && !defined (__ARMCC_VERSION)
int uart_putc(char ch, FILE *file)
{
    (void)file;
    UART_writeCharBlockingNonFIFO(UARTA_BASE, (uint8_t)ch);
    return (ch);
}

static FILE __stdio = FDEV_SETUP_STREAM(uart_putc, NULL, NULL, _FDEV_SETUP_WRITE);
FILE *const stdin = &__stdio;

__strong_reference(stdin, stdout);
__strong_reference(stdin, stderr);

#elif defined (__GNUC__)
int __io_putchar(int ch)
{
    UART_writeCharBlockingNonFIFO(UARTA_BASE, (uint8_t)ch);
    return ch;
}

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
