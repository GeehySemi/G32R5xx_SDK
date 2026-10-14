//###########################################################################
//
// FILE:    board.c
//
// TITLE:   Board
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
//###########################################################################
//
#include "board.h"

static uint8_t s_led1State = 0U;
static uint8_t s_led2State = 0U;

//
// Board_initLeds - Initializes evaluation board LED GPIO pins.
//
static void Board_initLeds(void)
{
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED1);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 0U);
    s_led1State = 0U;

    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED2);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);
    GPIO_writePin(DEVICE_GPIO_PIN_LED2, 0U);
    s_led2State = 0U;
}

//
// Board_initUart - Initializes UART-A GPIO mux and module for console output.
//
static void Board_initUart(void)
{
    GPIO_setPinConfig(DEVICE_GPIO_CFG_UARTRXDA);
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
// Board_init - Initializes board LEDs and console UART
//
void Board_init(void)
{
    Board_initLeds();
    Board_initUart();
}

//
// Board_setLed1 - Sets LED1 on (1) or off (0)
//
void Board_setLed1(uint8_t on)
{
    s_led1State = (on != 0U) ? 1U : 0U;
    GPIO_writePin(DEVICE_GPIO_PIN_LED1, s_led1State);
}

//
// Board_setLed2 - Sets LED2 on (1) or off (0)
//
void Board_setLed2(uint8_t on)
{
    s_led2State = (on != 0U) ? 1U : 0U;
    GPIO_writePin(DEVICE_GPIO_PIN_LED2, s_led2State);
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
// Board_toggleLed2 - Toggles LED2 output state
//
void Board_toggleLed2(void)
{
    s_led2State ^= 1U;
    GPIO_writePin(DEVICE_GPIO_PIN_LED2, s_led2State);
}

//
// Board_getLed1State - Returns the current LED1 output state (0 or 1).
//
uint8_t Board_getLed1State(void)
{
    return s_led1State;
}

//
// Board_getLed2State - Returns the current LED2 output state (0 or 1).
//
uint8_t Board_getLed2State(void)
{
    return s_led2State;
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
