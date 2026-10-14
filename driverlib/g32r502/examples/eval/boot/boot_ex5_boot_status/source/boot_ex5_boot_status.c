//#############################################################################
//
// FILE:    boot_ex5_boot_status.c
//
// TITLE:   Boot ROM Status Example
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1>Boot ROM Status</h1>
//!
//! This example reads the Boot ROM status words written at 0x20000000 before
//! the C runtime initializes RAM, then prints the decoded result through UARTA.
//!
//! \b External \b Connections \n
//!  - GPIO28 connects to the PC RX pin
//!  - GPIO29 connects to the PC TX pin
//!  - UART terminal settings: 115200 baud, 8 data bits, no parity, 1 stop bit
//!
//! \b Notes \n
//!  - The project must define G32R502_DTCM_BOOT_STATUS_ENABLE so that
//!    Reset_Handler() calls G32R502_BootStatusEarlyHook().
//!  - The hook runs before SystemInit() and before the C runtime copies or
//!    clears RAM, so it can still see the Boot ROM data at 0x20000000.
//!  - This example reserves the last 0x20 bytes of DTCM (0x20005FE0..0x20005FFF)
//!    for a boot status snapshot. The BOOT status area at 0x20000000 is not
//!    reserved by the linker and is released to normal application use.
//!  - Running under a debugger may skip or alter the Boot ROM flow, so the
//!    status words at 0x20000000 may not reflect a full boot sequence.
//!    Run this example after a power-on reset (POR) for representative output.
//!  - Only the first 0x14 bytes are read from 0x20000000:
//!      0x00: Boot progress status
//!      0x04: BootMode
//!      0x08: MPOST result
//!      0x0C: Flash single-bit ECC low address
//!      0x10: Flash single-bit ECC high address
//!
//! \b Watch \b Variables \n
//!  - None.
//!
//#############################################################################
//
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
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
#include <stdio.h>

//
// Defines
//
#define BOOT_STATUS_SNAPSHOT_BASE       (0x20005FE0UL)
#define BOOT_STATUS_SNAPSHOT_MAGIC      (0x42535453UL)  // "BSTS"

//
// Boot progress status bits.
// These names follow the Boot ROM user guide, with SCI shown as UART and MCAN
// shown as CANFD to match the SDK naming used by G32R502 examples.
//
#define BOOT_STATUS_START_BOOT              (1UL << 0)
#define BOOT_STATUS_IN_FLASH_BOOT           (1UL << 1)
#define BOOT_STATUS_IN_CANFD_BOOT           (1UL << 2)
#define BOOT_STATUS_IN_RAM_BOOT             (1UL << 3)
#define BOOT_STATUS_IN_UART_BOOT            (1UL << 4)
#define BOOT_STATUS_IN_SPI_BOOT             (1UL << 5)
#define BOOT_STATUS_IN_I2C_BOOT             (1UL << 6)
#define BOOT_STATUS_IN_CAN_BOOT             (1UL << 7)
#define BOOT_STATUS_RAM_INIT_COMPLETE       (1UL << 8)
#define BOOT_STATUS_DCSM_INIT_DONE          (1UL << 9)
#define BOOT_STATUS_POR_MEM_TEST_DONE       (1UL << 10)
#define BOOT_STATUS_RESC_HANDLED            (1UL << 11)
#define BOOT_STATUS_HANDLED_XRSN            (1UL << 12)
#define BOOT_STATUS_HANDLED_POR             (1UL << 13)
#define BOOT_STATUS_BOOT_COMPLETE           (1UL << 15)
#define BOOT_STATUS_HWREG_WRITE_ERROR       (1UL << 16)
#define BOOT_STATUS_HWREG_READ_ERROR        (1UL << 17)
#define BOOT_STATUS_FLASH_UNCERR_NMI        (1UL << 20)
#define BOOT_STATUS_RAM_UNCERR_NMI          (1UL << 21)
#define BOOT_STATUS_MCLK_NMI                (1UL << 22)
#define BOOT_STATUS_MEM_FAULT               (1UL << 24)
#define BOOT_STATUS_BUS_FAULT               (1UL << 25)
#define BOOT_STATUS_USAGE_FAULT             (1UL << 26)
#define BOOT_STATUS_HARD_FAULT              (1UL << 27)
#define BOOT_STATUS_IN_HARDFAULT_HANDLER    (1UL << 31)

//
// Boot mode fields.
// BootMode[4:0] identifies the selected boot mode, while BootMode[7:5]
// carries the boot option selected by BOOTDEFx.
//
#define BOOT_MODE_MASK                      (0x1FUL)
#define BOOT_OPTION_MASK                    (0x07UL)
#define BOOT_OPTION_SHIFT                   (5U)

//
// MPOST fields.
// Bits [4:0] indicate whether each BIST was executed, bits [20:16] indicate
// pass/fail, and bits [28:24] indicate whether the BIST finished in time.
//
#define MPOST_EXEC_TCM                      (1UL << 0)
#define MPOST_EXEC_CANFD_RAM                (1UL << 1)
#define MPOST_EXEC_CANA_RAM                 (1UL << 2)
#define MPOST_EXEC_CACHE                    (1UL << 3)
#define MPOST_EXEC_ROM                      (1UL << 4)
#define MPOST_PASS_TCM                      (1UL << 16)
#define MPOST_PASS_CANFD_RAM                (1UL << 17)
#define MPOST_PASS_CANA_RAM                 (1UL << 18)
#define MPOST_PASS_CACHE                    (1UL << 19)
#define MPOST_PASS_ROM                      (1UL << 20)
#define MPOST_DONE_TCM                      (1UL << 24)
#define MPOST_DONE_CANFD_RAM                (1UL << 25)
#define MPOST_DONE_CANA_RAM                 (1UL << 26)
#define MPOST_DONE_CACHE                    (1UL << 27)
#define MPOST_DONE_ROM                      (1UL << 28)

//
// Types
//
typedef struct
{
    //
    // Magic is written last by the early hook. example_main() uses it to check
    // whether the snapshot is valid after C runtime initialization completes.
    //
    uint32_t magic;
    uint32_t bootProgress;          // ROM offset 0x00
    uint32_t bootMode;              // ROM offset 0x04
    uint32_t mpostResult;           // ROM offset 0x08
    uint32_t flashSingleBitErrorLowAddress;   // ROM offset 0x0C
    uint32_t flashSingleBitErrorHighAddress;  // ROM offset 0x10
    uint32_t reserved[2];
} BootStatusSnapshot;

//
// Globals
//
volatile BootStatusSnapshot * const bootStatusSnapshot =
    (volatile BootStatusSnapshot *)BOOT_STATUS_SNAPSHOT_BASE;

//
// Function Prototypes
//
void G32R502_BootStatusEarlyHook(const volatile uint8_t *bootStatus,
                                 uint32_t size);
void initUART(void);
uint32_t readLE32(const volatile uint8_t *data);
const char *getBootModeName(uint32_t mode);
void printFlag(uint32_t value, uint32_t mask, const char *name);
void printBootProgress(uint32_t status);
void printBootMode(uint32_t bootMode);
void printMpostItem(uint32_t value, uint32_t execMask, uint32_t doneMask,
                    uint32_t passMask, const char *name);
void printMpostResult(uint32_t mpost);

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
    // Globally disable interrupts and clear all NVIC enable/pending bits
    //
    Interrupt_initModule();

    //
    // Initialize RAM vector table and set VTOR; unregistered IRQs use
    // Interrupt_defaultHandler until Interrupt_register() is called
    //
    Interrupt_initVectorTable();

    //
    // Configure UARTA and GPIO for printf output
    //
    initUART();

    printf("\r\nG32R502 Boot Status Example\r\n");
    printf("Snapshot base: 0x%08lX\r\n", (unsigned long)BOOT_STATUS_SNAPSHOT_BASE);

    if(bootStatusSnapshot->magic != BOOT_STATUS_SNAPSHOT_MAGIC)
    {
        printf("Boot status snapshot is not valid. Check that "
               "G32R502_DTCM_BOOT_STATUS_ENABLE is defined.\r\n");
    }
    else
    {
        //
        // Print the Boot ROM status captured in Reset_Handler()
        //
        printBootProgress(bootStatusSnapshot->bootProgress);
        printBootMode(bootStatusSnapshot->bootMode);
        printMpostResult(bootStatusSnapshot->mpostResult);

        printf("\r\n[Flash single-bit ECC addresses]\r\n");
        printf("  low address   : 0x%08lX\r\n",
               (unsigned long)bootStatusSnapshot->flashSingleBitErrorLowAddress);
        printf("  high address  : 0x%08lX\r\n",
               (unsigned long)bootStatusSnapshot->flashSingleBitErrorHighAddress);
    }

    //
    // Loop forever
    //
    for(;;)
    {
        DEVICE_DELAY_US(1000000);
    }
}

//
// G32R502_BootStatusEarlyHook - Copy Boot ROM status before C runtime init
//
void G32R502_BootStatusEarlyHook(const volatile uint8_t *bootStatus,
                                 uint32_t size)
{
    if(size < DTCM_BOOT_STATUS_SIZE)
    {
        return;
    }

    //
    // Do not call any library function here. This hook runs before the C
    // runtime has initialized RAM and before UART or clocks are configured.
    //
    bootStatusSnapshot->bootProgress = readLE32(&bootStatus[0]);
    bootStatusSnapshot->bootMode = readLE32(&bootStatus[4]);
    bootStatusSnapshot->mpostResult = readLE32(&bootStatus[8]);
    bootStatusSnapshot->flashSingleBitErrorLowAddress = readLE32(&bootStatus[12]);
    bootStatusSnapshot->flashSingleBitErrorHighAddress = readLE32(&bootStatus[16]);
    bootStatusSnapshot->magic = BOOT_STATUS_SNAPSHOT_MAGIC;
}

//
// initUART - Configure UARTA for printf output
//
void initUART(void)
{
    Device_initGPIO();

    GPIO_setPinConfig(DEVICE_GPIO_CFG_UARTRXDA);
    GPIO_setAnalogMode(DEVICE_GPIO_PIN_UARTRXDA, GPIO_ANALOG_DISABLED);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_UARTRXDA, GPIO_DIR_MODE_IN);
    GPIO_setDrivingCapability(DEVICE_GPIO_PIN_UARTRXDA, GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_UARTRXDA, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_UARTRXDA, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_UARTTXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_UARTTXDA, GPIO_DIR_MODE_OUT);
    GPIO_setDrivingCapability(DEVICE_GPIO_PIN_UARTTXDA, GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_UARTTXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_UARTTXDA, GPIO_QUAL_ASYNC);

    UART_performSoftwareReset(UARTA_BASE);
    UART_setConfig(UARTA_BASE, DEVICE_LSPCLK_FREQ, 115200,
                   (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                    UART_CONFIG_PAR_NONE));
    UART_resetChannels(UARTA_BASE);
    UART_resetRxFIFO(UARTA_BASE);
    UART_resetTxFIFO(UARTA_BASE);
    UART_clearInterruptStatus(UARTA_BASE, UART_INT_TXFF | UART_INT_RXFF);
    UART_enableFIFO(UARTA_BASE);
    UART_enableModule(UARTA_BASE);
    UART_performSoftwareReset(UARTA_BASE);
}

//
// readLE32 - Read a little-endian 32-bit value from volatile byte data
//
uint32_t readLE32(const volatile uint8_t *data)
{
    uint32_t b0 = data[0];
    uint32_t b1 = data[1];
    uint32_t b2 = data[2];
    uint32_t b3 = data[3];

    return b0 | (b1 << 8U) | (b2 << 16U) | (b3 << 24U);
}

//
// getBootModeName - Return a descriptive string for the boot mode field
//
const char *getBootModeName(uint32_t mode)
{
    switch(mode & BOOT_MODE_MASK)
    {
        case 0x01U:
            return "UART/Wait boot";
        case 0x02U:
            return "CAN boot";
        case 0x03U:
            return "Flash boot";
        case 0x04U:
            return "Wait boot";
        case 0x05U:
            return "RAM boot";
        case 0x06U:
            return "SPI master boot";
        case 0x07U:
            return "I2C master boot";
        case 0x08U:
            return "CANFD boot";
        default:
            return "Unknown boot";
    }
}

//
// printFlag - Print one boot progress flag when its bit is set
//
void printFlag(uint32_t value, uint32_t mask, const char *name)
{
    if((value & mask) != 0U)
    {
        printf("  %-36s : SET\r\n", name);
    }
}

//
// printBootProgress - Decode and print boot progress status bits
//
void printBootProgress(uint32_t status)
{
    printf("\r\n[Boot progress] 0x%08lX\r\n", (unsigned long)status);
    printFlag(status, BOOT_STATUS_START_BOOT, "BOOTROM_START_BOOT");
    printFlag(status, BOOT_STATUS_IN_FLASH_BOOT, "BOOTROM_IN_FLASH_BOOT");
    printFlag(status, BOOT_STATUS_IN_CANFD_BOOT, "BOOTROM_IN_CAN_FD_BOOT");
    printFlag(status, BOOT_STATUS_IN_RAM_BOOT, "BOOTROM_IN_RAM_BOOT");
    printFlag(status, BOOT_STATUS_IN_UART_BOOT, "BOOTROM_IN_UART_BOOT");
    printFlag(status, BOOT_STATUS_IN_SPI_BOOT, "BOOTROM_IN_SPI_BOOT");
    printFlag(status, BOOT_STATUS_IN_I2C_BOOT, "BOOTROM_IN_I2C_BOOT");
    printFlag(status, BOOT_STATUS_IN_CAN_BOOT, "BOOTROM_IN_CAN_BOOT");
    printFlag(status, BOOT_STATUS_RAM_INIT_COMPLETE, "BOOTROM_RAM_INIT_COMPLETE");
    printFlag(status, BOOT_STATUS_DCSM_INIT_DONE, "BOOTROM_DCSM_INIT_DONE");
    printFlag(status, BOOT_STATUS_POR_MEM_TEST_DONE, "BOOTROM_POR_MEM_TEST_DONE");
    printFlag(status, BOOT_STATUS_RESC_HANDLED, "BOOTROM_RESC_HANDLED");
    printFlag(status, BOOT_STATUS_HANDLED_XRSN, "BOOTROM_HANDLED_XRSN");
    printFlag(status, BOOT_STATUS_HANDLED_POR, "BOOTROM_HANDLED_POR");
    printFlag(status, BOOT_STATUS_BOOT_COMPLETE, "BOOTROM_BOOT_COMPLETE");
    printFlag(status, BOOT_STATUS_HWREG_WRITE_ERROR, "BOOTROM_HWREG_WRITE_ERROR");
    printFlag(status, BOOT_STATUS_HWREG_READ_ERROR, "BOOTROM_HWREG_READ_ERROR");
    printFlag(status, BOOT_STATUS_FLASH_UNCERR_NMI, "BOOTROM_GOT_A_FLASH_UNCERR_NMI");
    printFlag(status, BOOT_STATUS_RAM_UNCERR_NMI, "BOOTROM_GOT_A_RAM_UNCERR_NMI");
    printFlag(status, BOOT_STATUS_MCLK_NMI, "BOOTROM_GOT_A_MCLK_NMI");
    printFlag(status, BOOT_STATUS_MEM_FAULT, "BOOTROM_GOT_A_MEM_FAULT");
    printFlag(status, BOOT_STATUS_BUS_FAULT, "BOOTROM_GOT_A_BUS_FAULT");
    printFlag(status, BOOT_STATUS_USAGE_FAULT, "BOOTROM_GOT_A_USAGE_FAULT");
    printFlag(status, BOOT_STATUS_HARD_FAULT, "BOOTROM_GOT_A_HARD_FAULT");
    printFlag(status, BOOT_STATUS_IN_HARDFAULT_HANDLER, "BOOTROM_IN_HARDFULT_HANDLER");
}

//
// printBootMode - Decode and print boot mode and boot option fields
//
void printBootMode(uint32_t bootMode)
{
    uint32_t mode = bootMode & BOOT_MODE_MASK;
    uint32_t option = (bootMode >> BOOT_OPTION_SHIFT) & BOOT_OPTION_MASK;

    printf("\r\n[Boot mode] 0x%08lX\r\n", (unsigned long)bootMode);
    printf("  Boot Mode   : 0x%02lX (%s)\r\n", (unsigned long)mode,
           getBootModeName(mode));
    printf("  Boot Option : 0x%02lX\r\n", (unsigned long)option);
}

//
// printMpostItem - Print executed, done, and pass bits for one MPOST target
//
void printMpostItem(uint32_t value, uint32_t execMask, uint32_t doneMask,
                    uint32_t passMask, const char *name)
{
    printf("  %-12s executed:%lu done:%lu pass:%lu\r\n",
           name,
           (unsigned long)((value & execMask) != 0U),
           (unsigned long)((value & doneMask) != 0U),
           (unsigned long)((value & passMask) != 0U));
}

//
// printMpostResult - Decode and print MPOST BIST results
//
void printMpostResult(uint32_t mpost)
{
    printf("\r\n[MPOST result] 0x%08lX\r\n", (unsigned long)mpost);
    printMpostItem(mpost, MPOST_EXEC_TCM, MPOST_DONE_TCM, MPOST_PASS_TCM, "TCM");
    printMpostItem(mpost, MPOST_EXEC_CANFD_RAM, MPOST_DONE_CANFD_RAM,
                   MPOST_PASS_CANFD_RAM, "CANFD RAM");
    printMpostItem(mpost, MPOST_EXEC_CANA_RAM, MPOST_DONE_CANA_RAM,
                   MPOST_PASS_CANA_RAM, "CANA RAM");
    printMpostItem(mpost, MPOST_EXEC_CACHE, MPOST_DONE_CACHE, MPOST_PASS_CACHE,
                   "CACHE");
    printMpostItem(mpost, MPOST_EXEC_ROM, MPOST_DONE_ROM, MPOST_PASS_ROM, "ROM");
}

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
//
// fputc - fputc.
//
int fputc(int ch, FILE* f)
{
    (void)f;
    UART_writeCharBlockingNonFIFO(UARTA_BASE, (uint8_t)ch);

    return ch;
}
#elif defined(__ICCARM__)
//
// __io_putchar - io putchar.
//
int __io_putchar(int ch)
{
    UART_writeCharBlockingNonFIFO(UARTA_BASE, (uint8_t)ch);

    return ch;
}

//
// __write - write.
//
int __write(int file, char* ptr, int len)
{
    int i;

    (void)file;

    for(i = 0; i < len; i++)
    {
        __io_putchar(*ptr++);
    }

    return len;
}
#elif defined(__clang__) && !defined(__ARMCC_VERSION)
//
// uart_putc - uart putc.
//
int uart_putc(char ch, FILE *file)
{
    (void)file;
    UART_writeCharBlockingNonFIFO(UARTA_BASE, (uint8_t)ch);

    return ch;
}

static FILE __stdio = FDEV_SETUP_STREAM(uart_putc, NULL, NULL, _FDEV_SETUP_WRITE);
FILE *const stdin = &__stdio;

__strong_reference(stdin, stdout);
__strong_reference(stdin, stderr);
#endif

//
// End of File
//
