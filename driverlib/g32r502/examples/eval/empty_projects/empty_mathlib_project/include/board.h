//#############################################################################
//
// FILE:    board.h
//
// TITLE:   Board header file
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

// Eval board user LED on GPIO23 (VSW)
#define myGPIOOutput_LED1 DEVICE_GPIO_PIN_LED1
#define myGPIOOutput_LED2 DEVICE_GPIO_PIN_LED2

void Board_init(void);
void GPIO_init(void);
void PinMux_init(void);

#ifdef __cplusplus
}
#endif

#endif
