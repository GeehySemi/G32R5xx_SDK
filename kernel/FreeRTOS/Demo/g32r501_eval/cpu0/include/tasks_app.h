//###########################################################################
//
// FILE:    tasks_app.h
//
// TITLE:   Application tasks for g32r501_eval CPU0
//
// VERSION: 1.0.0
//
// DATE:    2026-08-24
//
//###########################################################################
#ifndef TASKS_APP_H
#define TASKS_APP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "ipc_shm_msg.h"

void vLed1Task(void *pvParameters);
void vIpcCmdTask(void *pvParameters);
void vIpcRspTask(void *pvParameters);
void vUartLogTask(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif /* TASKS_APP_H */
