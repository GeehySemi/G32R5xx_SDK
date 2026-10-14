//###########################################################################
//
// FILE:    board.h
//
// TITLE:   Board API for g32r501_eval CPU0
//
// VERSION: 1.0.0
//
// DATE:    2026-08-24
//
//###########################################################################
#ifndef BOARD_H
#define BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "driverlib.h"
#include "device.h"

void Board_init(void);
void Board_toggleLed1(void);
uint8_t Board_getLed1State(void);
void Board_uartWriteString(const char *msg);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
