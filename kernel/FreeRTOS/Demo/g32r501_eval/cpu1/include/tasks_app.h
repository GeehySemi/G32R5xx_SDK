//###########################################################################
//
// FILE:    tasks_app.h
//
// TITLE:   Application tasks for g32r501_eval CPU1
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

void vLed2Task(void *pvParameters);
void vIpcWorkerTask(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif /* TASKS_APP_H */
