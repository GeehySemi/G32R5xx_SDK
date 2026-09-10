//#############################################################################
//
// FILE:    ipc_ex2_mailbox_polling_cpu1.c
//
// TITLE:   IPC Mailbox with Polling Example
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1> IPC Mailbox with Polling </h1>
//!
//! This example demonstrates how to use the mailbox mechanism of the Inter-Processor 
//! Communication (IPC) module, to send and receive data between two CPUs in polling mode.
//!
//! In this example:
//! 1. CPU0 sends a message to CPU1 via the IPC module in polling mode.
//! 2. CPU1 sends a message back to CPU0 in polling mode.
//! 3. CPU0 receives the message sent from CPU1 in polling mode, and so on.
//!
//! \note Note: The IPC example includes both CPU0 and CPU1 projects. 
//!             Please compile the CPU1 project before compiling the CPU0 project.
//!
//! \b Running \b the \b Application
//!  Open a COM port with the following settings using a terminal:
//!  -  Find correct COM port
//!  -  Bits per second = 115200
//!  -  Data Bits = 8
//!  -  Parity = None
//!  -  Stop Bits = 1
//!  -  Hardware Control = None
//!
//! \b External \b Connections \n
//!  Connect the UART-A port to a PC via a transceiver and cable.
//!  - GPIO28 is UART_RXD (Connect to Pin3, PC-TX, of serial DB9 cable)
//!  - GPIO29 is UART_TXD (Connect to Pin2, PC-RX, of serial DB9 cable)
//!
//! \b Watch \b Variables \n
//!  - None.
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2024 Geehy Semiconductor - http://www.geehy.com/
//
// You may not use this file except in compliance with the
// GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
//
// The program is only for reference, which is distributed in the hope
// that it will be useful and instructional for customers to develop
// their software. Unless required by applicable law or agreed to in
// writing, the program is distributed on an "AS IS" BASIS, WITHOUT
// ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
// See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
// and limitations under the License.
// $
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include <stdio.h>

//
// How many message is used to test mailbox sending and receiving
//
#define MESSAGE_LENGTH      4U

//
// Variables
//
static uint32_t g_msgRecv[MESSAGE_LENGTH];

//
// Function Prototypes
//
void clearMsgRecv(void);
void UART_Init(void);


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
    // Initialize NVIC and clear NVIC registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
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

    //
    // UART initialize
    //
    UART_Init();

    //
    // CPU1 Print information
    //
    printf("CPU1 has completed booting.\r\n");

    //
    // Clear the g_msgRecv array before receive
    //
    clearMsgRecv();

    //
    // CPU1 receive message from CPU0
    //
    while (IPC_isRxBufferFull(IPC_RX_0) != true);
    g_msgRecv[0] = IPC_receive32Bits(IPC_RX_0);

    while (IPC_isRxBufferFull(IPC_RX_1) != true);
    g_msgRecv[1] = IPC_receive32Bits(IPC_RX_1);

    while (IPC_isRxBufferFull(IPC_RX_2) != true);
    g_msgRecv[2] = IPC_receive32Bits(IPC_RX_2);

    while (IPC_isRxBufferFull(IPC_RX_3) != true);
    g_msgRecv[3] = IPC_receive32Bits(IPC_RX_3);

    //
    // CPU1 send message back to CPU0
    //
    while (IPC_isTxBufferEmpty(IPC_TX_0) != true);
    IPC_transmit32Bits(IPC_TX_0, g_msgRecv[0]);

    while (IPC_isTxBufferEmpty(IPC_TX_1) != true);
    IPC_transmit32Bits(IPC_TX_1, g_msgRecv[1]);

    while (IPC_isTxBufferEmpty(IPC_TX_2) != true);
    IPC_transmit32Bits(IPC_TX_2, g_msgRecv[2]);

    while (IPC_isTxBufferEmpty(IPC_TX_3) != true);
    IPC_transmit32Bits(IPC_TX_3, g_msgRecv[3]);

    //
    // Loop.
    //
    for(;;)
    {
        DEVICE_DELAY_US(500000);
        GPIO_togglePin(myGPIOOutput_LED2);
    }
}


//
// Function to clear the g_msgRecv array.
// This function set g_msgRecv to be 0.
//
void clearMsgRecv(void)
{
    uint32_t i;
    for (i = 0U; i < MESSAGE_LENGTH; i++)
    {
        g_msgRecv[i] = 0U;
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
    GPIO_setMasterCore(DEVICE_GPIO_PIN_UARTRXDA, GPIO_CORE_CPU1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_UARTRXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_UARTRXDA, GPIO_DIR_MODE_IN);
    GPIO_setDrivingCapability(DEVICE_GPIO_PIN_UARTRXDA,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_UARTRXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_UARTRXDA, GPIO_QUAL_ASYNC);

    //
    // GPIO29 is the UART Tx pin.
    //
    GPIO_setMasterCore(DEVICE_GPIO_PIN_UARTTXDA, GPIO_CORE_CPU1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_UARTTXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_UARTTXDA, GPIO_DIR_MODE_OUT);
    GPIO_setDrivingCapability(DEVICE_GPIO_PIN_UARTTXDA,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_UARTTXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_UARTTXDA, GPIO_QUAL_ASYNC);

    //
    // Initialize UARTA and its FIFO.
    //
    UART_performSoftwareReset(UARTA_BASE);

    //
    // Configure UARTA for echoback.
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

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
//
// Redefine the fputc function to the serial port
//
int fputc(int ch, FILE* f)
{
    if (ch == '\n')
    {
        UART_writeCharBlockingNonFIFO(UARTA_BASE, (uint8_t)'\r');
    }

    UART_writeCharBlockingNonFIFO(UARTA_BASE, (uint8_t)ch);

    return (ch);
}
#elif defined(__ICCARM__)
int __io_putchar(int ch)
{
    if (ch == '\n')
    {
        UART_writeCharBlockingNonFIFO(UARTA_BASE, (uint8_t)'\r');
    }

    UART_writeCharBlockingNonFIFO(UARTA_BASE, (uint8_t)ch);

    return (ch);
}

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
int uart_putc(char ch, FILE *file)
{
    if (ch == '\n')
    {
        UART_writeCharBlockingNonFIFO(UARTA_BASE, (uint8_t)'\r');
    }

    UART_writeCharBlockingNonFIFO(UARTA_BASE, (uint8_t)ch);

    return (ch);
}

static FILE __stdio = FDEV_SETUP_STREAM(uart_putc, NULL, NULL, _FDEV_SETUP_WRITE);
FILE *const stdin = &__stdio;

__strong_reference(stdin, stdout);
__strong_reference(stdin, stderr);

#endif

//
// End of File
//
