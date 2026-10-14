//###########################################################################
//
// FILE:    board.c
//
// TITLE:   Board for g32r501_eval CPU0 (LED1 + UART-A)
//
// VERSION: 1.0.0
//
// DATE:    2026-08-24
//
//###########################################################################
#include "board.h"

static uint8_t s_led1State = 0U;

//
// Board_initLeds - Initializes evaluation board LED1 GPIO (CPU0 master)
//
static void Board_initLeds(void)
{
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED1);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(DEVICE_GPIO_PIN_LED1, GPIO_CORE_CPU0);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_LED1, GPIO_QUAL_SYNC);
    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 0U);
    s_led1State = 0U;
}

//
// Board_initUart - Initializes UART-A GPIO mux and module for console output (CPU0)
//
static void Board_initUart(void)
{
    GPIO_setMasterCore(DEVICE_GPIO_PIN_UARTRXDA, GPIO_CORE_CPU0);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_UARTRXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_UARTRXDA, GPIO_DIR_MODE_IN);
    GPIO_setDrivingCapability(DEVICE_GPIO_PIN_UARTRXDA, GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_UARTRXDA, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_UARTRXDA, GPIO_QUAL_ASYNC);

    GPIO_setMasterCore(DEVICE_GPIO_PIN_UARTTXDA, GPIO_CORE_CPU0);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_UARTTXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_UARTTXDA, GPIO_DIR_MODE_OUT);
    GPIO_setDrivingCapability(DEVICE_GPIO_PIN_UARTTXDA, GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_UARTTXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_UARTTXDA, GPIO_QUAL_ASYNC);

    UART_performSoftwareReset(UARTA_BASE);
    UART_setConfig(UARTA_BASE, DEVICE_LSPCLK_FREQ, 115200U,
                   (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UART_resetChannels(UARTA_BASE);
    UART_resetRxFIFO(UARTA_BASE);
    UART_resetTxFIFO(UARTA_BASE);
    UART_clearInterruptStatus(UARTA_BASE, UART_INT_TXFF | UART_INT_RXFF);
    UART_enableFIFO(UARTA_BASE);
    UART_enableModule(UARTA_BASE);
    UART_performSoftwareReset(UARTA_BASE);
}

//
// Board_init - Initializes board LED1 and console UART
//
void Board_init(void)
{
    WRPRT_DISABLE;
    Board_initLeds();
    Board_initUart();
    WRPRT_ENABLE;
}

//
// Board_toggleLed1 - Toggles LED1 output state
//
void Board_toggleLed1(void)
{
    s_led1State ^= 1U;
    GPIO_writePin(DEVICE_GPIO_PIN_LED1, s_led1State);
}

//
// Board_getLed1State - Returns the current LED1 output state (0 or 1)
//
uint8_t Board_getLed1State(void)
{
    return s_led1State;
}

//
// Board_uartWriteString - Writes a null-terminated string to UART-A
//
void Board_uartWriteString(const char *msg)
{
    const char *p = msg;

    if(msg == NULL)
    {
        return;
    }

    while(*p != '\0')
    {
        UART_writeCharBlockingNonFIFO(UARTA_BASE, (uint16_t)(uint8_t)(*p));
        p++;
    }
}
