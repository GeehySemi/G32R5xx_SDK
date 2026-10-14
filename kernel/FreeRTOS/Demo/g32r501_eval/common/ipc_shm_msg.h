//###########################################################################
//
// FILE:    ipc_shm_msg.h
//
// TITLE:   Shared-RAM request/response protocol for g32r501_eval dual-core
//
// VERSION: 1.1.0
//
// DATE:    2026-08-24
//
//###########################################################################
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
#ifndef IPC_SHM_MSG_H
#define IPC_SHM_MSG_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//
// IpcOpId - IPC operation identifiers (CPU1 worker dispatch)
//
typedef enum
{
    IPC_OP_SINF = 1   // sinf(arg0) via Zidian on CPU1
} IpcOpId;

//
// IpcBufStatus - Shared-RAM buffer handshake state (both banks)
//
typedef enum
{
    IPC_BUF_IDLE  = 0,  // Buffer owned by consumer / safe to fill
    IPC_BUF_READY = 1,  // Producer finished; consumer may read
    IPC_BUF_BUSY  = 2,  // Consumer is processing the request
    IPC_BUF_ERROR = 3   // Reserved for fault reporting
} IpcBufStatus;

//
// IPC mailbox doorbell word layout: upper 16 bits magic, lower 16 bits seq
//
#define IPC_DOOR_REQ_MAGIC   (0xA5A50000UL)  // CPU0 -> CPU1 request doorbell
#define IPC_DOOR_RSP_MAGIC   (0x5A5A0000UL)  // CPU1 -> CPU0 response doorbell
#define IPC_DOOR_SEQ_MASK    (0x0000FFFFUL)  // Sequence number in doorbell word

//
// Demo waveform timing: 64 samples per 2*pi, 10 ms between IPC requests
//
#define IPC_DEMO_PI              (3.1415926535f)
#define IPC_DEMO_TWO_PI          (6.283185307f)
#define IPC_DEMO_SIN_SAMPLES     (64U)
#define IPC_DEMO_PHASE_STEP      (IPC_DEMO_TWO_PI / (float)IPC_DEMO_SIN_SAMPLES)
#define IPC_DEMO_IPC_PERIOD_MS   (10U)

//
// IpcReqBank - Shared SRAM1 request bank (CPU0 writes, CPU1 reads)
//
typedef struct
{
    volatile uint32_t status;    // IpcBufStatus handshake
    volatile uint32_t seq;       // Monotonic request sequence number
    volatile uint32_t op;        // IpcOpId operation to perform
    volatile uint32_t reserved;  // Padding / reserved for future fields
    volatile float    arg0;      // Operation argument (phase in radians for sinf)
} IpcReqBank;

//
// IpcRspBank - Shared SRAM2 response bank (CPU1 writes, CPU0 reads)
//
typedef struct
{
    volatile uint32_t status;    // IpcBufStatus handshake
    volatile uint32_t seq;       // Matches the request sequence number
    volatile uint32_t op;        // Echo of request IpcOpId
    volatile uint32_t err;       // 0 = success, non-zero = unsupported op or fault
    volatile float    arg0;      // Echo of request phase (for UART logging)
    volatile float    result;    // Computed result (sinf output from CPU1)
} IpcRspBank;

//
// IpcResultMsg - CPU0 local queue item: IPC result plus CPU0-side ref/abs_err
//
typedef struct
{
    uint32_t seq;      // Request sequence number
    float    phase;    // Phase in radians (echo from response bank)
    float    result;   // sinf result from CPU1
    float    ref;      // CPU0 reference sinf(phase) for error check
    float    absErr;   // |result - ref|
    uint32_t err;      // CPU1 error flag (0 = success)
} IpcResultMsg;

#ifdef __cplusplus
}
#endif

#endif /* IPC_SHM_MSG_H */
