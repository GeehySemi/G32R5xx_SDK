//###########################################################################
//
// FILE:    tasks_app.h
//
// TITLE:   Tasks app
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
#ifndef TASKS_APP_H
#define TASKS_APP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void vLed1Task(void *pvParameters);
void vLed2Task(void *pvParameters);
void vUartLogTask(void *pvParameters);

uint8_t Board_getLed1State(void);
uint8_t Board_getLed2State(void);

#ifdef __cplusplus
}
#endif

#endif /* TASKS_APP_H */
