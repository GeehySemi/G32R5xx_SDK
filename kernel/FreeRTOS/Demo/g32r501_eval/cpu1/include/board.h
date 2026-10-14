//###########################################################################
//
// FILE:    board.h
//
// TITLE:   Board API for g32r501_eval CPU1
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
void Board_toggleLed2(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
