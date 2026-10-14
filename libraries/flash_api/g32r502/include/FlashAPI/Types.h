//###########################################################################
// 
// FILE:    Types.h
//                                
// TITLE:   Types used by the Flash API
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//###########################################################################
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

#ifndef FAPI_TYPES_H_
#define FAPI_TYPES_H_

//*****************************************************************************
//
// CPU and byte-order configuration macros used by the Flash API library.
//
//*****************************************************************************

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

#define CPU_TYPE            CPU_TYPE_32
#define CPU_BIT_ORDER       LSB_FIRST

#if defined(_LITTLE_ENDIAN)
#define CPU_BYTE_ORDER      LOW_BYTE_FIRST
#else
#define CPU_BYTE_ORDER      HIGH_BYTE_FIRST
#endif

//*****************************************************************************
//
//! Primitive and status types used by the Flash API.
//
//*****************************************************************************

typedef unsigned char           boolean;

typedef unsigned char           uint8;
typedef unsigned short          uint16;
typedef unsigned int            uint32;
typedef unsigned long long      uint64;

typedef unsigned short          uint16_least;
typedef unsigned int            uint32_least;

typedef signed short            sint16_least;
typedef signed int              sint32_least;

//*****************************************************************************
//
//! Raw FMSTAT register value returned by \b Fapi_getFsmStatus().
//
//*****************************************************************************
typedef uint32 Fapi_FlashStatusType;

//*****************************************************************************
//
//! Status word structure returned by blank-check, verify, and PSA operations.
//!
//! On failure, the meaning of \b au32StatusWord[] depends on the API that
//! populated the structure. See the corresponding function documentation in
//! \b Fapi.h for field usage.
//
//*****************************************************************************
typedef struct
{
  uint32 au32StatusWord[4];
} Fapi_FlashStatusWordType;

//*****************************************************************************
//
//! Values that can be passed to \b Fapi_issueProgrammingCommand() as the
//! \e oMode parameter to select the programming mode.
//
//*****************************************************************************
typedef enum
{
   Fapi_AutoEccGeneration, //!< Program data and auto-generate ECC
   Fapi_DataOnly,          //!< Program data only
   Fapi_EccOnly,           //!< Program ECC only
   Fapi_DataAndEcc         //!< Program both data and supplied ECC
} Fapi_FlashProgrammingCommandsType;

//*****************************************************************************
//
//! Values that can be passed to \b Fapi_setActiveFlashBank() to select the
//! active Flash bank.
//
//*****************************************************************************
typedef enum
{
   Fapi_FlashBank0,        //!< Flash bank 0
   Fapi_FlashBank1,        //!< Flash bank 1
} Fapi_FlashBankType;

//*****************************************************************************
//
//! Flash State Machine command identifiers.
//!
//! Not all commands are supported on every API entry point. See \b Fapi.h for
//! the supported command subset of each function.
//
//*****************************************************************************
typedef enum
{
   Fapi_ProgramData    = 0x0002, //!< Program data command
   Fapi_EraseSector    = 0x0006, //!< Erase sector command
   Fapi_EraseBank      = 0x0008, //!< Erase bank command
   Fapi_ValidateSector = 0x000E, //!< Validate sector command
   Fapi_ClearStatus    = 0x0010, //!< Clear FSM status command
   Fapi_ProgramResume  = 0x0014, //!< Resume program command
   Fapi_EraseResume    = 0x0016, //!< Resume erase command
   Fapi_ClearMore      = 0x0018  //!< Clear additional FSM status command
} Fapi_FlashStateCommandsType;

//*****************************************************************************
//
//! Flash read margin modes supported by PSA calculation APIs.
//!
//! On this device, only \b Fapi_NormalRead is applicable.
//
//*****************************************************************************
typedef enum
{
   Fapi_NormalRead = 0x0, //!< Normal read mode
   Fapi_RM0        = 0x1, //!< Read margin 0 mode
   Fapi_RM1        = 0x2  //!< Read margin 1 mode
} Fapi_FlashReadMarginModeType;

//*****************************************************************************
//
//! Status and error codes returned by Flash API functions.
//
//*****************************************************************************
typedef enum
{
   Fapi_Status_Success=0,           //!< Function completed successfully
   Fapi_Status_FsmBusy,             //!< FSM is busy
   Fapi_Status_FsmReady,            //!< FSM is ready
   Fapi_Status_AsyncBusy,           //!< Async operation is busy
   Fapi_Status_AsyncComplete,       //!< Async operation is complete
   Fapi_Error_Fail=500,             //!< Generic function failure
   Fapi_Error_StateMachineTimeout,  //!< FSM polling timed out
   Fapi_Error_OtpChecksumMismatch,  //!< OTP checksum mismatch
   Fapi_Error_InvalidDelayValue,    //!< Calculated RWAIT exceeds 15 (legacy)
   Fapi_Error_InvalidHclkValue,     //!< HCLK exceeds allowed Flash clock
   Fapi_Error_InvalidCpu,           //!< Specified CPU does not exist
   Fapi_Error_InvalidBank,          //!< Specified Flash bank does not exist
   Fapi_Error_InvalidAddress,       //!< Address is not in Flash or OTP space
   Fapi_Error_InvalidReadMode,      //!< Specified read mode does not exist
   Fapi_Error_AsyncIncorrectDataBufferLength, //!< Data buffer length is invalid
   Fapi_Error_AsyncIncorrectEccBufferLength,  //!< ECC buffer length is invalid
   Fapi_Error_AsyncDataEccBufferLengthMismatch, //!< Data and ECC lengths mismatch
   Fapi_Error_FeatureNotAvailable,  //!< Requested FMC feature is not available
   Fapi_Error_FlashRegsNotWritable  //!< Flash registers are not writable
} Fapi_StatusType;

//*****************************************************************************
//
//! Flash API library production status values read from OTP.
//
//*****************************************************************************
typedef enum
{
   Alpha_Internal,          //!< Internal alpha release
   Alpha,                   //!< Early engineering release
   Beta_Internal,           //!< Internal beta release
   Beta,                    //!< Beta release for validation
   Production               //!< Production-ready release
} Fapi_ApiProductionStatusType;

//*****************************************************************************
//
//! Flash API build and version information returned by
//! \b Fapi_getLibraryInfo().
//
//*****************************************************************************
typedef struct
{
   uint8  u8ApiMajorVersion;              //!< API major version
   uint8  u8ApiMinorVersion;              //!< API minor version
   uint8  u8ApiRevision;                  //!< API revision
   Fapi_ApiProductionStatusType oApiProductionStatus; //!< Production status
   uint32 u32ApiBuildNumber;              //!< API build number
   uint8  u8ApiTechnologyType;            //!< Flash technology type
   uint8  u8ApiTechnologyRevision;        //!< Flash technology revision
   uint8  u8ApiEndianness;                //!< API endianness
   uint32 u32ApiCompilerVersion;          //!< Compiler version used to build API
} Fapi_LibraryInfoType;

//*****************************************************************************
//
//! Values that can be passed to \b Fapi_optFlashBankModeConfig() and
//! \b Fapi_optConfig() with \b Fapi_OptionByte_BankMode.
//
//*****************************************************************************
typedef enum
{
  Fapi_SingleBank = 0x0, //!< Single-bank Flash mode
  Fapi_DualBank   = 0x1  //!< Dual-bank Flash mode
} Fapi_FlashBankModeType;

//*****************************************************************************
//
//! Values that can be passed to \b Fapi_optBankSwapConfig() and
//! \b Fapi_optConfig() with \b Fapi_OptionByte_BankSwap.
//
//*****************************************************************************
typedef enum
{
  Fapi_DefaultBankSwap = 0x0,  //!< Default bank mapping
  Fapi_ExchangeBankSwap = 0x1  //!< Exchanged bank mapping
} Fapi_FlashBankSwapType;

//*****************************************************************************
//
//! Values that can be passed to \b Fapi_optBankSwapEnnConfig() and
//! \b Fapi_optConfig() with \b Fapi_OptionByte_BankSwapEnn.
//
//*****************************************************************************
typedef enum
{
  Fapi_BankSwapEnable = 0x0,  //!< Bank swap enabled
  Fapi_BankSwapDisable = 0x1  //!< Bank swap disabled
} Fapi_FlashBankSwapEnnType;

//*****************************************************************************
//
//! Values that can be passed to \b Fapi_optConfig() as the \e oOptionByte
//! parameter to select which option-byte field to update.
//
//*****************************************************************************
typedef enum
{
  Fapi_OptionByte_CFGSMS,      //!< CFGSMS static configuration field (0 to 15)
  Fapi_OptionByte_BankSwap,    //!< Bank-swap configuration field
  Fapi_OptionByte_BankSwapEnn, //!< Bank-swap enable field
  Fapi_OptionByte_BankMode,    //!< Flash bank mode field
  Fapi_OptionByte_BootAddr,    //!< CPU boot address field
} Fapi_OptionByteType;

#endif /* FAPI_TYPES_H_ */
