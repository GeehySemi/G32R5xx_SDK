//###########################################################################
// 
// FILE:    Types.h
//                                
// TITLE:   Types used by the Flash API
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//###########################################################################
// $Copyright:
// Copyright (C) 2024 Geehy Semiconductor - http://www.geehy.com/
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

#ifndef FAPI_TYPES_H_
#define FAPI_TYPES_H_

/*****************************************************************************/
/* GLOBAL DEFINITIONS                                                        */
/*****************************************************************************/
#define CPU_TYPE_8          8
#define CPU_TYPE_16         16
#define CPU_TYPE_32         32

#define MSB_FIRST           0
#define LSB_FIRST           1

#define HIGH_BYTE_FIRST     0
#define LOW_BYTE_FIRST      1

#ifndef TRUE
#define TRUE                1
#endif

#ifndef FALSE
#define FALSE               0
#endif

/*****************************************************************************/
/* REGISTER WIDTH                                                            */
/*****************************************************************************/
#define CPU_TYPE            CPU_TYPE_32

/*****************************************************************************/
/* ENDIANESS                                                                 */
/*****************************************************************************/
#define CPU_BIT_ORDER       LSB_FIRST

#if defined(_LITTLE_ENDIAN)
#define CPU_BYTE_ORDER      LOW_BYTE_FIRST
#else
#define CPU_BYTE_ORDER      HIGH_BYTE_FIRST
#endif

/*****************************************************************************/
/* TYPE DEFINITIONS                                                          */
/*****************************************************************************/
typedef unsigned char           boolean;

typedef unsigned char           uint8;
typedef unsigned short          uint16;
typedef unsigned int            uint32;
typedef unsigned long long      uint64;

typedef unsigned short          uint16_least;
typedef unsigned int            uint32_least;

typedef signed short            sint16_least;
typedef signed int              sint32_least;

typedef struct
{
  uint32 au32StatusWord[4];
} Fapi_FlashStatusWordType;

/*!
    \brief This contains all the possible modes used in the Fapi_IssueAsyncProgrammingCommand().
*/
typedef enum
{
   Fapi_AutoEccGeneration, /* This is the default mode for the command and will auto generate the ecc for the provided data buffer */
   Fapi_DataOnly,          /* Command will only process the data buffer */
   Fapi_EccOnly,           /* Command will only process the ecc buffer */
   Fapi_DataAndEcc         /* Command will process data and ecc buffers */
} Fapi_FlashProgrammingCommandsType;

/*!
    \brief This is used to indicate which Flash bank is being used.
*/
typedef enum
{
   Fapi_FlashBank0,
   Fapi_FlashBank1,
} Fapi_FlashBankType;

/*!
    \brief This contains all the possible Flash State Machine commands.
*/
typedef enum
{
   Fapi_ProgramData    = 0x0002,
   Fapi_EraseSector    = 0x0006,
   Fapi_EraseBank      = 0x0008,
   Fapi_ValidateSector = 0x000E,
   Fapi_ClearStatus    = 0x0010,
   Fapi_ProgramResume  = 0x0014,
   Fapi_EraseResume    = 0x0016,
   Fapi_ClearMore      = 0x0018
} Fapi_FlashStateCommandsType;

typedef uint32 Fapi_FlashStatusType;

/*!
    \brief This contains all the possible Flash State Machine commands.
*/
typedef enum
{
   Fapi_NormalRead = 0x0,
   Fapi_RM0        = 0x1,
   Fapi_RM1        = 0x2
} Fapi_FlashReadMarginModeType;

/*!
    \brief This is the master type containing all possible returned status codes.
*/
typedef enum
{
   Fapi_Status_Success=0,           /* Function completed successfully */
   Fapi_Status_FsmBusy,             /* FSM is Busy */
   Fapi_Status_FsmReady,            /* FSM is Ready */
   Fapi_Status_AsyncBusy,           /* Async function operation is Busy */
   Fapi_Status_AsyncComplete,       /* Async function operation is Complete */
   Fapi_Error_Fail=500,             /* Generic Function Fail code */
   Fapi_Error_StateMachineTimeout,  /* State machine polling never returned ready and timed out */
   Fapi_Error_OtpChecksumMismatch,  /* Returned if OTP checksum does not match expected value */
   Fapi_Error_InvalidDelayValue,    /* Returned if the Calculated RWAIT value exceeds 15  - Legacy Error */
   Fapi_Error_InvalidHclkValue,     /* Returned if FClk is above max FClk value - FClk is a calculated from HClk and RWAIT/EWAIT */
   Fapi_Error_InvalidCpu,           /* Returned if the specified Cpu does not exist */
   Fapi_Error_InvalidBank,          /* Returned if the specified bank does not exist */
   Fapi_Error_InvalidAddress,       /* Returned if the specified Address does not exist in Flash or OTP */
   Fapi_Error_InvalidReadMode,      /* Returned if the specified read mode does not exist */
   Fapi_Error_AsyncIncorrectDataBufferLength,
   Fapi_Error_AsyncIncorrectEccBufferLength,
   Fapi_Error_AsyncDataEccBufferLengthMismatch,
   Fapi_Error_FeatureNotAvailable,  /* FMC feature is not available on this device */
   Fapi_Error_FlashRegsNotWritable  /* Returned if Flash registers are not writable due to security */
} Fapi_StatusType;

typedef enum
{
   Alpha_Internal,          /* For internal use only.  Not intended to be used by customers */
   Alpha,                   /* Early Engineering release.  May not be functionally complete */
   Beta_Internal,           /* For internal use only.  Not intended to be used by customers */
   Beta,                    /* Functionally complete, to be used for testing and validation */
   Production               /* Fully validated, functionally complete, ready for production use */
} Fapi_ApiProductionStatusType;

typedef struct
{
   uint8  u8ApiMajorVersion;
   uint8  u8ApiMinorVersion;
   uint8  u8ApiRevision;
   Fapi_ApiProductionStatusType oApiProductionStatus;
   uint32 u32ApiBuildNumber;
   uint8  u8ApiTechnologyType;
   uint8  u8ApiTechnologyRevision;
   uint8  u8ApiEndianness;
   uint32 u32ApiCompilerVersion;
} Fapi_LibraryInfoType;

typedef enum
{
    Fapi_DualBank   = 0x0,
    Fapi_SingleBank = 0x1
} Fapi_FlashBankModeType;

#endif /* FAPI_TYPES_H_ */
