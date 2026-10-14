//###########################################################################
//
// FILE:    board.h
//
// TITLE:   Board header file.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//###########################################################################
#ifndef BOARD_H
#define BOARD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "driverlib.h"
#include "device.h"

#define GPIO_PIN_CANA_RX DEVICE_GPIO_PIN_CANRXA
#define GPIO_PIN_CANA_TX DEVICE_GPIO_PIN_CANTXA

#define myCAN0_BASE CANA_BASE

#define myCAN0_MessageObj1_ID 5
#define myCAN0_MessageObj2_ID 5
#define myCAN0_MessageObj3_ID 7

void    Board_init();
void    CAN_init();
void    PinMux_init();

#ifdef __cplusplus
}
#endif

#endif
