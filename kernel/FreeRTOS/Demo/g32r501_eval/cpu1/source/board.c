//###########################################################################
//
// FILE:    board.c
//
// TITLE:   Board for g32r501_eval CPU1 (LED2)
//
// VERSION: 1.0.0
//
// DATE:    2026-08-24
//
//###########################################################################
#include "board.h"

static uint8_t s_led2State = 0U;

//
// Board_init - Initializes board LED2 GPIO (CPU1 master)
//
void Board_init(void)
{
    WRPRT_DISABLE;

    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED2);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(DEVICE_GPIO_PIN_LED2, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_LED2, GPIO_QUAL_SYNC);
    GPIO_writePin(DEVICE_GPIO_PIN_LED2, 0U);
    s_led2State = 0U;

    WRPRT_ENABLE;
}

//
// Board_toggleLed2 - Toggles LED2 output state
//
void Board_toggleLed2(void)
{
    s_led2State ^= 1U;
    GPIO_writePin(DEVICE_GPIO_PIN_LED2, s_led2State);
}
