//###########################################################################
//
// FILE:    iar_dlib_lock.c
//
// TITLE:   Iar dlib lock
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
/*
 * IAR DLib thread-safe lock hooks for FreeRTOS (GRuntimeLibThreads=1).
 */

#include "FreeRTOS.h"
#include "semphr.h"

typedef void *__iar_Rmtx;

static void iar_mtx_init(__iar_Rmtx *lock)
{
    *lock = (void *)xSemaphoreCreateRecursiveMutex();
}

static void iar_mtx_destroy(__iar_Rmtx *lock)
{
    if(*lock != NULL)
    {
        vSemaphoreDelete((SemaphoreHandle_t)(*lock));
        *lock = NULL;
    }
}

static void iar_mtx_lock(__iar_Rmtx *lock)
{
    (void)xSemaphoreTakeRecursive((SemaphoreHandle_t)(*lock), portMAX_DELAY);
}

static void iar_mtx_unlock(__iar_Rmtx *lock)
{
    (void)xSemaphoreGiveRecursive((SemaphoreHandle_t)(*lock));
}

void __iar_system_Mtxinit(__iar_Rmtx *lock)
{
    iar_mtx_init(lock);
}

void __iar_system_Mtxdst(__iar_Rmtx *lock)
{
    iar_mtx_destroy(lock);
}

void __iar_system_Mtxlock(__iar_Rmtx *lock)
{
    iar_mtx_lock(lock);
}

void __iar_system_Mtxunlock(__iar_Rmtx *lock)
{
    iar_mtx_unlock(lock);
}

void __iar_file_Mtxinit(__iar_Rmtx *lock)
{
    iar_mtx_init(lock);
}

void __iar_file_Mtxdst(__iar_Rmtx *lock)
{
    iar_mtx_destroy(lock);
}

void __iar_file_Mtxlock(__iar_Rmtx *lock)
{
    iar_mtx_lock(lock);
}

void __iar_file_Mtxunlock(__iar_Rmtx *lock)
{
    iar_mtx_unlock(lock);
}
