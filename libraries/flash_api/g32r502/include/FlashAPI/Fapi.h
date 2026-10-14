//###########################################################################
// 
// FILE:    Fapi.h
//                                
// TITLE:   Main include file for Flash devices
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

#ifndef FAPI_H_
#define FAPI_H_

#include "Registers.h"
#include "Constants.h"

#define Fapi_writeCFGSMSConfig Fapi_optCFGSMSConfig
#define Fapi_writeFlashBankMode Fapi_optFlashBankModeConfig

//*****************************************************************************
//
//! \addtogroup fapi_api Flash API
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! Returns the value of the FMSTAT register.
//!
//! This function reads and returns the current Flash State Machine status
//! register (FMSTAT).
//!
//! \return The FMSTAT register value.
//
//*****************************************************************************
extern Fapi_FlashStatusType Fapi_getFsmStatus(void);

//*****************************************************************************
//
//! Checks whether the Flash State Machine is ready for a new command.
//!
//! This function polls the FMSTAT BUSY bit to determine if the FSM can accept
//! another operation.
//!
//! \return Returns \b Fapi_Status_FsmBusy if the FSM is busy, or
//! \b Fapi_Status_FsmReady if the FSM is idle and ready.
//
//*****************************************************************************
extern Fapi_StatusType Fapi_checkFsmForReady(void);

//*****************************************************************************
//
//! Initializes the FMC for erase and program operations on a Flash bank.
//!
//! \param oFlashBank is the Flash bank to activate. Valid values are
//! \b Fapi_FlashBank0 and \b Fapi_FlashBank1.
//!
//! This function validates the requested bank and, when OTP SMW trim data is
//! present and its checksum matches, loads Flash timing and SMW trim values
//! from OTP into FMC registers.
//!
//! \return Returns \b Fapi_Error_InvalidBank if \e oFlashBank is not
//! \b Fapi_FlashBank0 or \b Fapi_FlashBank1.
//! Returns \b Fapi_Error_OtpChecksumMismatch if OTP SMW trim is present but
//! its Fletcher checksum does not match.
//! Returns \b Fapi_Status_Success otherwise.
//
//*****************************************************************************
extern Fapi_StatusType Fapi_setActiveFlashBank(Fapi_FlashBankType oFlashBank);

//*****************************************************************************
//
//! Suspends an active program or erase operation.
//!
//! This function waits for the target Flash bank to become ready (subject to
//! a maximum wakeup timeout) when required, then issues the FSM suspend command.
//!
//! \return Returns \b Fapi_Status_Success.
//
//*****************************************************************************
extern Fapi_StatusType Fapi_issueFsmSuspendCommand(void);

//*****************************************************************************
//
//! Flushes the FMC pipeline and bus buffers.
//!
//! This function invalidates the instruction and data caches when enabled,
//! then pulses the FMC bus buffer clear control to ensure subsequent Flash
//! operations observe updated memory contents.
//!
//! \return None.
//
//*****************************************************************************
extern void Fapi_flushPipeline(void);

//*****************************************************************************
//
//! Remaps an ECC address to the corresponding main Flash address.
//!
//! \param u32EccAddress is the ECC-space address to remap.
//!
//! This function converts an address in ECC main or ECC info space to the
//! corresponding 64-bit-aligned main Flash or info Flash address. If
//! \e u32EccAddress is not in a valid ECC region, the returned pointer
//! corresponds to address \b 0xFFFFFFFF.
//!
//! \return Pointer to the remapped main Flash or info Flash address.
//
//*****************************************************************************
extern uint32 *Fapi_remapEccAddress(uint32 u32EccAddress);

//*****************************************************************************
//
//! Determines whether an address lies in Flash ECC address space.
//!
//! \param u32Address is the address to test.
//!
//! This function returns \b true when \e u32Address falls within ECC main
//! space or ECC info space.
//!
//! \return \b true if the address is in ECC space, \b false otherwise.
//
//*****************************************************************************
extern boolean Fapi_isAddressEcc(uint32 u32Address);

//*****************************************************************************
//
//! Issues an asynchronous erase command to a Flash sector address.
//!
//! \param oCommand is the FSM command to issue. Only \b Fapi_EraseSector is
//! supported by this function.
//! \param pu32StartAddress is the sector start address in program memory to
//! erase. The address must lie within main Flash bank 0 or bank 1
//! (0x08000000 through 0x0803FFFF).
//!
//! This function validates command, register writability, address, and FSM
//! readiness, applies bank-swap address remapping when configured, clears FSM
//! status, and starts the sector erase sequence.
//!
//! \return Returns \b Fapi_Error_FeatureNotAvailable if \e oCommand is not
//! \b Fapi_EraseSector.
//! Returns \b Fapi_Error_FlashRegsNotWritable if FMC registers are locked.
//! Returns \b Fapi_Error_InvalidAddress if the sector address is invalid.
//! Returns \b Fapi_Status_FsmBusy if the FSM is not ready.
//! Returns \b Fapi_Status_Success if the erase command was issued.
//
//*****************************************************************************
extern Fapi_StatusType Fapi_issueAsyncCommandWithAddress(
                                                        Fapi_FlashStateCommandsType oCommand,
                                                        uint32 *pu32StartAddress
                                                        );

//*****************************************************************************
//
//! Issues a synchronous Flash State Machine control command.
//!
//! \param oCommand is the FSM command to issue. Valid values are
//! \b Fapi_ClearStatus, \b Fapi_ClearMore, \b Fapi_ProgramResume, and
//! \b Fapi_EraseResume.
//!
//! This function verifies FSM readiness before writing the selected FMSTAT
//! control command. Resume commands also flush the FMC pipeline.
//!
//! \return Returns \b Fapi_Error_FeatureNotAvailable if \e oCommand is not
//! one of the supported values above.
//! Returns \b Fapi_Status_FsmBusy if the FSM is not ready.
//! Returns \b Fapi_Status_Success if the command was issued.
//
//*****************************************************************************
extern Fapi_StatusType Fapi_issueAsyncCommand(Fapi_FlashStateCommandsType oCommand);

//*****************************************************************************
//
//! Returns build and version information for this Flash API.
//!
//! This function reads Flash API metadata stored in OTP and returns it in a
//! \b Fapi_LibraryInfoType structure.
//!
//! \return A \b Fapi_LibraryInfoType structure containing API version,
//! production status, technology type, endianness, and compiler information.
//
//*****************************************************************************
extern Fapi_LibraryInfoType Fapi_getLibraryInfo(void);

//*****************************************************************************
//
//! Initializes the Flash API and validates the system clock configuration.
//!
//! \param poFlashControlRegister is a pointer to the FMC register block. This
//! parameter is reserved for API compatibility.
//! \param u32HclkFrequency is the SYSCLK frequency in MHz.
//!
//! This function compares \e u32HclkFrequency against the maximum Flash clock
//! implied by OTP Flash frequency trim and the current FMC RWAIT setting.
//! The HCLK value must not exceed
//! \b FlashClk * (\b FlashLatency + 1).
//!
//! \return Returns \b Fapi_Error_InvalidHclkValue if \e u32HclkFrequency
//! exceeds the allowed Flash clock for the current RWAIT setting.
//! Returns \b Fapi_Status_Success otherwise.
//
//*****************************************************************************
extern Fapi_StatusType Fapi_initializeAPI(
                                         Fapi_FmcRegistersType *poFlashControlRegister,
                                         uint32 u32HclkFrequency
                                         );

//*****************************************************************************
//
//! Checks whether a Flash or ECC region contains only erased values.
//!
//! \param pu32StartAddress is the start address of the region to check.
//! \param u32Length is the length of the region in 32-bit words.
//! \param poFlashStatusWord returns failure details when the check does not
//! succeed. On failure:
//! - \b au32StatusWord[0]: address of the first non-blank location
//! - \b au32StatusWord[1]: data read at that location
//! - \b au32StatusWord[2]: expected blank value (\b 0xFFFFFFFF)
//! - \b au32StatusWord[3]: always \b 0
//!
//! Both the start and end addresses must lie entirely within main/info Flash
//! space or entirely within ECC space.
//!
//! \return Returns \b Fapi_Status_Success if all locations read
//! \b 0xFFFFFFFF.
//! Returns \b Fapi_Error_Fail if a non-blank location is found.
//! Returns \b Fapi_Error_InvalidAddress if the address range is invalid.
//
//*****************************************************************************
extern Fapi_StatusType Fapi_doBlankCheck(
                                        uint32 *pu32StartAddress,
                                        uint32 u32Length,
                                        Fapi_FlashStatusWordType *poFlashStatusWord
                                        );

//*****************************************************************************
//
//! Verifies a Flash or ECC region against a supplied data buffer.
//!
//! \param pu32StartAddress is the start address of the region to verify.
//! \param u32Length is the length of the region in 32-bit words.
//! \param pu32CheckValueBuffer is the buffer containing expected 32-bit values.
//! \param poFlashStatusWord returns failure details when verification fails.
//! On failure:
//! - \b au32StatusWord[0]: address of the first mismatch
//! - \b au32StatusWord[1]: data read at that location
//! - \b au32StatusWord[2]: expected compare value from the buffer
//! - \b au32StatusWord[3]: always \b 0
//!
//! Both the start and end addresses must lie entirely within main/info Flash
//! space or entirely within ECC space.
//!
//! \return Returns \b Fapi_Status_Success if all locations match.
//! Returns \b Fapi_Error_Fail on the first mismatch.
//! Returns \b Fapi_Error_InvalidAddress if the address range is invalid.
//
//*****************************************************************************
extern Fapi_StatusType Fapi_doVerify(
                                    uint32 *pu32StartAddress,
                                    uint32 u32Length,
                                    uint32 *pu32CheckValueBuffer,
                                    Fapi_FlashStatusWordType *poFlashStatusWord
                                    );

//*****************************************************************************
//
//! Calculates the PSA value for a Flash region.
//!
//! \param pu32StartAddress is the start address of the region.
//! \param u32Length is the length of the region in 32-bit words.
//! \param u32PsaSeed is the initial PSA seed value.
//! \param oReadMode is the Flash read margin mode. Only \b Fapi_NormalRead is
//! applicable on this device; the parameter is reserved for compatibility.
//!
//! This function iterates over \e u32Length 32-bit words starting at
//! \e pu32StartAddress and returns the computed PSA signature.
//!
//! \return The calculated PSA value.
//
//*****************************************************************************
extern uint32 Fapi_calculatePsa(
                                uint32 *pu32StartAddress,
                                uint32 u32Length,
                                uint32 u32PsaSeed,
                                Fapi_FlashReadMarginModeType oReadMode
                                );

//*****************************************************************************
//
//! Verifies a Flash region against an expected PSA value.
//!
//! \param pu32StartAddress is the start address of the region to verify.
//! \param u32Length is the length of the region in 32-bit words.
//! \param u32PsaValue is the expected PSA signature.
//! \param poFlashStatusWord returns the computed PSA in
//! \b au32StatusWord[3] regardless of success or failure.
//!
//! This function calculates the PSA with seed \b 0 and compares it against
//! \e u32PsaValue.
//!
//! \return Returns \b Fapi_Status_Success if the calculated PSA matches
//! \e u32PsaValue.
//! Returns \b Fapi_Error_Fail if the PSA values differ.
//
//*****************************************************************************
extern Fapi_StatusType Fapi_doPsaVerify(
                                       uint32 *pu32StartAddress,
                                       uint32 u32Length,
                                       uint32 u32PsaValue,
                                       Fapi_FlashStatusWordType *poFlashStatusWord
                                       );

//*****************************************************************************
//
//! Issues a Flash programming command with selectable data and ECC modes.
//!
//! \param pu32StartAddress is the start address in Flash or DCSM OTP memory
//! to program.
//! \param pu32DataBuffer is a pointer to the 32-bit data buffer. May be
//! \b NULL when \e oMode is \b Fapi_EccOnly.
//! \param u32DataBufferSizeInWords is the number of 32-bit words in the data
//! buffer.
//! \param pu16EccBuffer is a pointer to the ECC buffer. May be \b NULL when
//! \e oMode is \b Fapi_DataOnly or \b Fapi_AutoEccGeneration.
//! \param u16EccBufferSizeInBytes is the number of 8-bit ECC bytes in the ECC
//! buffer.
//! \param oMode is the programming mode:
//! - \b Fapi_DataOnly: program data only
//! - \b Fapi_AutoEccGeneration: program data and auto-generate ECC
//! - \b Fapi_DataAndEcc: program both data and supplied ECC
//! - \b Fapi_EccOnly: program ECC only
//!
//! Valid program addresses are main Flash bank 0/1 or DCSM OTP regions. For
//! DCSM OTP, \b Fapi_EccOnly is not supported; link-pointer OTP addresses
//! force \b Fapi_DataOnly, and other DCSM OTP addresses convert
//! \b Fapi_DataOnly to \b Fapi_AutoEccGeneration.
//!
//! Mode-dependent restrictions apply within the current bank programming
//! window (16 bytes in dual-bank mode, 32 bytes in single-bank mix-bank
//! mode):
//!
//! - \b Fapi_DataOnly: \e u32DataBufferSizeInWords must be non-zero; start
//! address must be 4-byte aligned; data must not exceed the bank window.
//! - \b Fapi_AutoEccGeneration: \e u32DataBufferSizeInWords must be non-zero
//! and even; start address must be 8-byte aligned; data must not exceed the
//! bank window.
//! - \b Fapi_DataAndEcc: \e u32DataBufferSizeInWords must be non-zero and
//! even; \e u16EccBufferSizeInBytes must be non-zero and equal to
//! \e u32DataBufferSizeInWords / 2; start address must be 8-byte aligned;
//! data and ECC must each fit within the bank window.
//! - \b Fapi_EccOnly: \e u16EccBufferSizeInBytes must be non-zero; start
//! address must be 8-byte aligned; ECC must fit within the bank window.
//!
//! \return Returns \b Fapi_Error_FeatureNotAvailable for unsupported modes or
//! DCSM OTP restrictions.
//! Returns \b Fapi_Error_FlashRegsNotWritable if FMC registers are locked.
//! Returns \b Fapi_Error_AsyncIncorrectDataBufferLength,
//! \b Fapi_Error_AsyncIncorrectEccBufferLength, or
//! \b Fapi_Error_AsyncDataEccBufferLengthMismatch for buffer validation
//! failures.
//! Returns \b Fapi_Error_InvalidAddress for invalid or misaligned addresses.
//! Returns \b Fapi_Status_FsmBusy if the FSM is not ready.
//! Returns \b Fapi_Status_Success if the program command was issued.
//
//*****************************************************************************
extern Fapi_StatusType Fapi_issueProgrammingCommand(
                                            uint32 *pu32StartAddress,
                                            uint32 *pu32DataBuffer,
                                            uint32  u32DataBufferSizeInWords,
                                            uint16 *pu16EccBuffer,
                                            uint16  u16EccBufferSizeInBytes,
                                            Fapi_FlashProgrammingCommandsType oMode
                                            );

//*****************************************************************************
//
//! Programs ECC using an ECC-space start address.
//!
//! \param pu32StartAddress is the ECC-space start address to program.
//! \param pu16EccBuffer is a pointer to the ECC buffer.
//! \param u16EccBufferSizeInBytes is the number of 8-bit ECC bytes to program.
//!
//! This function remaps \e pu32StartAddress from ECC space to the
//! corresponding main Flash address and invokes
//! \b Fapi_issueProgrammingCommand() in \b Fapi_EccOnly mode.
//!
//! \return Same status codes as \b Fapi_issueProgrammingCommand().
//
//*****************************************************************************
extern Fapi_StatusType Fapi_issueProgrammingCommandForEccAddresses(
                                                           uint32 *pu32StartAddress,
                                                           uint16 *pu16EccBuffer,
                                                           uint16 u16EccBufferSizeInBytes
                                                           );

//*****************************************************************************
//
//! Calculates a Fletcher checksum over a 16-bit data block.
//!
//! \param pu16Data is the start address of the data to checksum.
//! \param u16Length is the number of 16-bit halfwords to include.
//!
//! This function computes a 32-bit Fletcher checksum. On little-endian
//! targets, each 16-bit value is byte-swapped before accumulation.
//!
//! \return The 32-bit Fletcher checksum.
//
//*****************************************************************************
extern uint32 Fapi_calculateFletcherChecksum(
                                            uint16 const * pu16Data,
                                            uint16 u16Length
                                            );

//*****************************************************************************
//
//! Calculates the 8-bit ECC value for a 64-bit Flash data word.
//!
//! \param u32Address is the Flash main or info address associated with the
//! 64-bit data word.
//! \param u64Data is the 64-bit data value in little-endian order.
//!
//! This function waits for FSM readiness, aligns \e u32Address down to a
//! 64-bit boundary, applies bank-swap remapping when required, loads the data
//! into FMC program registers, and reads the hardware-generated ECC encode
//! result. The address must lie in main Flash or info Flash space.
//!
//! \return The calculated 8-bit ECC value, or \b 0xFF if \e u32Address is
//! invalid.
//
//*****************************************************************************
extern uint8 Fapi_calculateEcc(
                              uint32 u32Address,
                              uint64 u64Data
                              );

//*****************************************************************************
//
//! Programs up to 512 bits with automatic ECC generation.
//!
//! \param pu32StartAddress is the 512-bit-aligned start address in Flash or
//! OTP memory.
//! \param pu32DataBuffer is a pointer to the 32-bit data buffer.
//! \param u16DataBufferSizeInWords is the number of valid 32-bit data words.
//! Must be in the range 1 to 16 inclusive.
//!
//! The start address must be 64-byte aligned. DCSM OTP link-pointer addresses
//! are not supported. Unused words within the 512-bit block are padded with
//! \b 0xFFFFFFFF before programming. The function splits the operation into
//! multiple \b Fapi_AutoEccGeneration program commands according to the
//! current bank mode (up to 8 words per command in single-bank mode, up to 4
//! words in dual-bank mode) and waits for FSM completion between chunks.
//!
//! \return Returns \b Fapi_Error_InvalidAddress for misaligned addresses,
//! unsupported link-pointer OTP addresses, or other address validation
//! failures from the underlying program command.
//! Returns \b Fapi_Error_AsyncIncorrectDataBufferLength if
//! \e u16DataBufferSizeInWords is zero or greater than 16.
//! Returns \b Fapi_Error_FlashRegsNotWritable, \b Fapi_Status_FsmBusy, or
//! other errors propagated from \b Fapi_issueProgrammingCommand().
//! Returns \b Fapi_Status_Success if all chunks were programmed.
//
//*****************************************************************************
extern Fapi_StatusType Fapi_issueAutoEcc512ProgrammingCommand(
                                                       uint32 *pu32StartAddress,
                                                       uint32 *pu32DataBuffer,
                                                       uint16 u16DataBufferSizeInWords
                                                       );

//*****************************************************************************
//
//! Programs up to 512 bits using supplied data and ECC buffers.
//!
//! \param pu32StartAddress is the 512-bit-aligned start address in Flash or
//! OTP memory.
//! \param pu32DataBuffer is a pointer to the 32-bit data buffer.
//! \param u16DataBufferSizeInWords is the number of 32-bit data words. Must be
//! non-zero, even, and the total data size must not exceed 64 bytes.
//! \param pu16EccBuffer is a pointer to the ECC buffer.
//! \param u16EccBufferSizeInBytes is the number of 8-bit ECC bytes. Must be
//! non-zero, and the total ECC size must not exceed 64 bytes. Must equal
//! \e u16DataBufferSizeInWords / 2.
//!
//! DCSM OTP link-pointer addresses are not supported. The start address must
//! be 64-byte aligned. Programming is performed in bank-mode-dependent
//! chunks using \b Fapi_DataAndEcc mode, waiting for FSM completion between
//! chunks.
//!
//! \return Returns \b Fapi_Error_InvalidAddress for unsupported addresses or
//! alignment errors.
//! Returns \b Fapi_Error_AsyncIncorrectDataBufferLength,
//! \b Fapi_Error_AsyncIncorrectEccBufferLength, or
//! \b Fapi_Error_AsyncDataEccBufferLengthMismatch for buffer validation
//! failures.
//! Returns errors propagated from \b Fapi_issueProgrammingCommand().
//! Returns \b Fapi_Status_Success if all chunks were programmed.
//
//*****************************************************************************
extern Fapi_StatusType Fapi_issueDataAndEcc512ProgrammingCommand(
                                            uint32 *pu32StartAddress,
                                            uint32 *pu32DataBuffer,
                                            uint16  u16DataBufferSizeInWords,
                                            uint16 *pu16EccBuffer,
                                            uint16  u16EccBufferSizeInBytes
                                            );

//*****************************************************************************
//
//! Programs up to 512 bits of data without ECC on main Flash.
//!
//! \param pu32StartAddress is the 512-bit-aligned start address in main Flash.
//! \param pu32DataBuffer is a pointer to the 32-bit data buffer.
//! \param u16DataBufferSizeInWords is the number of 32-bit data words. Must be
//! non-zero and the total data size must not exceed 64 bytes.
//!
//! DCSM OTP addresses are not supported. The start address must be 64-byte
//! aligned. Programming is performed in bank-mode-dependent chunks using
//! \b Fapi_DataOnly mode, waiting for FSM completion between chunks.
//!
//! \return Returns \b Fapi_Error_InvalidAddress for DCSM OTP addresses,
//! misaligned addresses, or other address validation failures.
//! Returns \b Fapi_Error_AsyncIncorrectDataBufferLength if
//! \e u16DataBufferSizeInWords is zero or the total size exceeds 64 bytes.
//! Returns errors propagated from \b Fapi_issueProgrammingCommand().
//! Returns \b Fapi_Status_Success if all chunks were programmed.
//
//*****************************************************************************
extern Fapi_StatusType Fapi_issueDataOnly512ProgrammingCommand(
                                                        uint32 *pu32StartAddress,
                                                        uint32 *pu32DataBuffer,
                                                        uint16  u16DataBufferSizeInWords
                                                        );

//*****************************************************************************
//
//! Programs up to 512 bits of ECC data on main Flash.
//!
//! \param pu32StartAddress is the 512-bit-aligned start address in main Flash.
//! \param pu16EccBuffer is a pointer to the ECC buffer.
//! \param u16EccBufferSizeInBytes is the number of 8-bit ECC bytes. Must be
//! non-zero and the total ECC size must not exceed 64 bytes.
//!
//! DCSM OTP addresses are not supported. The start address must be 64-byte
//! aligned. Programming is performed in bank-mode-dependent chunks using
//! \b Fapi_EccOnly mode, waiting for FSM completion between chunks.
//!
//! \return Returns \b Fapi_Error_InvalidAddress for DCSM OTP addresses,
//! misaligned addresses, or other address validation failures.
//! Returns \b Fapi_Error_AsyncIncorrectEccBufferLength if
//! \e u16EccBufferSizeInBytes is zero or the total size exceeds 64 bytes.
//! Returns errors propagated from \b Fapi_issueProgrammingCommand().
//! Returns \b Fapi_Status_Success if all chunks were programmed.
//
//*****************************************************************************
extern Fapi_StatusType Fapi_issueEccOnly64ProgrammingCommand(
                                                      uint32 *pu32StartAddress,
                                                      uint16 *pu16EccBuffer,
                                                      uint16  u16EccBufferSizeInBytes
                                                      );

//*****************************************************************************
//
//! Configures an option byte field and reprograms the option-byte sector.
//!
//! \param oOptionByte is the option byte field to update. Valid values are
//! \b Fapi_OptionByte_CFGSMS, \b Fapi_OptionByte_BankSwap,
//! \b Fapi_OptionByte_BankSwapEnn, \b Fapi_OptionByte_BankMode, and
//! \b Fapi_OptionByte_BootAddr.
//! \param u32OptionByteValue is the value to program into the selected field.
//!
//! Field-specific restrictions:
//! - \b Fapi_OptionByte_CFGSMS: value must be 0 to 15.
//! - \b Fapi_OptionByte_BankSwap: value must be \b Fapi_DefaultBankSwap or
//! \b Fapi_ExchangeBankSwap.
//! - \b Fapi_OptionByte_BankSwapEnn: value must be \b Fapi_BankSwapDisable or
//! \b Fapi_BankSwapEnable.
//! - \b Fapi_OptionByte_BankMode: value must be \b Fapi_SingleBank or
//! \b Fapi_DualBank.
//! - \b Fapi_OptionByte_BootAddr: only the boot-address field bits defined by
//! the option-byte layout are written; other bits in the word are preserved.
//!
//! This function reads current option-byte values, merges the requested
//! change, erases the info-bank option-byte sector, and reprograms the option
//! byte key and configuration words.
//!
//! \return Returns \b Fapi_Error_FlashRegsNotWritable if FMC registers are
//! locked.
//! Returns \b Fapi_Status_FsmBusy if the FSM is not ready.
//! Returns \b Fapi_Error_FeatureNotAvailable for unsupported option-byte
//! selections or out-of-range values.
//! Returns \b Fapi_Status_Success if programming completed.
//
//*****************************************************************************
extern Fapi_StatusType Fapi_optConfig(Fapi_OptionByteType oOptionByte, uint32 u32OptionByteValue);

//*****************************************************************************
//
//! Configures the bank-swap option byte.
//!
//! \param oBankswapCfg is the bank-swap configuration. Valid values are
//! \b Fapi_DefaultBankSwap and \b Fapi_ExchangeBankSwap.
//!
//! This function is a wrapper around \b Fapi_optConfig() for
//! \b Fapi_OptionByte_BankSwap.
//!
//! \return Same status codes as \b Fapi_optConfig().
//
//*****************************************************************************
extern Fapi_StatusType Fapi_optBankSwapConfig(Fapi_FlashBankSwapType oBankswapCfg);

//*****************************************************************************
//
//! Configures the bank-swap enable option byte.
//!
//! \param oBankswapEnnCfg is the bank-swap enable configuration. Valid values
//! are \b Fapi_BankSwapDisable and \b Fapi_BankSwapEnable.
//!
//! This function is a wrapper around \b Fapi_optConfig() for
//! \b Fapi_OptionByte_BankSwapEnn.
//!
//! \return Same status codes as \b Fapi_optConfig().
//
//*****************************************************************************
extern Fapi_StatusType Fapi_optBankSwapEnnConfig(Fapi_FlashBankSwapEnnType oBankswapEnnCfg);

//*****************************************************************************
//
//! Configures the Flash bank mode option byte.
//!
//! \param oBankMode is the bank mode to select. Valid values are
//! \b Fapi_SingleBank and \b Fapi_DualBank.
//!
//! This function is a wrapper around \b Fapi_optConfig() for
//! \b Fapi_OptionByte_BankMode.
//!
//! \return Same status codes as \b Fapi_optConfig().
//
//*****************************************************************************
extern Fapi_StatusType Fapi_optFlashBankModeConfig(Fapi_FlashBankModeType oBankMode);

//*****************************************************************************
//
//! Configures the CFGSMS option byte.
//!
//! \param u8CfgsmsCfg is the CFGSMS static configuration value in the range
//! 0 to 15.
//!
//! This function is a wrapper around \b Fapi_optConfig() for
//! \b Fapi_OptionByte_CFGSMS.
//!
//! \return Same status codes as \b Fapi_optConfig().
//
//*****************************************************************************
extern Fapi_StatusType Fapi_optCFGSMSConfig(uint8 u8CfgsmsCfg);

//*****************************************************************************
//
//! Configures the CPU boot address option byte.
//!
//! \param oBootAddr is the CPU boot address used in supervisor boot mode.
//! Only the boot-address field bits defined by the option-byte layout are
//! written.
//!
//! This function is a wrapper around \b Fapi_optConfig() for
//! \b Fapi_OptionByte_BootAddr.
//!
//! \return Same status codes as \b Fapi_optConfig().
//
//*****************************************************************************
extern Fapi_StatusType Fapi_optBootAddressConfig(uint32 oBootAddr);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

#endif /* FAPI_H_ */
