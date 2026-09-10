/*!
 * @file        g32r501xxx_dcs_memory.ld
 *
 * @brief       Linker script for G32R501 series dcs OTP region
 *
 * @version     V1.0.0
 *
 * @date        2025-01-15
 *
 * @attention
 *
 *  Copyright (C) 2025 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

MEMORY
{
  B0_DCS_OTP_Z1_LINKPOINTER    (rw): ORIGIN = 0x0810A000, LENGTH = 0x18
  B0_DCS_OTP_Z1_GPREG          (rw): ORIGIN = 0x0810A018, LENGTH = 0x8
  B0_DCS_OTP_Z1_PSWDLOCK       (rw): ORIGIN = 0x0810A020, LENGTH = 0x8
  B0_DCS_OTP_Z1_BOOTCTRL       (rw): ORIGIN = 0x0810A038, LENGTH = 0x8
  B0_DCS_ZSEL_Z1               (rw): ORIGIN = 0x0810A060, LENGTH = 0x20

  B0_DCS_OTP_Z2_LINKPOINTER    (rw): ORIGIN = 0x0810A400, LENGTH = 0x18
  B0_DCS_OTP_Z2_GPREG          (rw): ORIGIN = 0x0810A418, LENGTH = 0x8
  B0_DCS_OTP_Z2_PSWDLOCK       (rw): ORIGIN = 0x0810A420, LENGTH = 0x8
  B0_DCS_OTP_Z2_BOOTCTRL       (rw): ORIGIN = 0x0810A438, LENGTH = 0x8
  B0_DCS_ZSEL_Z2               (rw): ORIGIN = 0x0810A460, LENGTH = 0x20

  B1_DCS_OTP_Z1_LINKPOINTER    (rw): ORIGIN = 0x0810B000, LENGTH = 0x18
  B1_DCS_OTP_Z1_CMAC_KEY       (rw): ORIGIN = 0x0810B020, LENGTH = 0x10
  B1_DCS_ZSEL_Z1               (rw): ORIGIN = 0x0810B060, LENGTH = 0x20

  B1_DCS_OTP_Z2_LINKPOINTER    (rw): ORIGIN = 0x0810B400, LENGTH = 0x18
  B1_DCS_ZSEL_Z2               (rw): ORIGIN = 0x0810B460, LENGTH = 0x20
}

SECTIONS
{
  .b0_dcs_otp_z1_linkpointer_section : { KEEP(*(.b0_dcs_otp_z1_linkpointer)) } > B0_DCS_OTP_Z1_LINKPOINTER
  .b0_dcs_otp_z1_gpreg_section       : { KEEP(*(.b0_dcs_otp_z1_gpreg)) }       > B0_DCS_OTP_Z1_GPREG
  .b0_dcs_otp_z1_pswdlock_section    : { KEEP(*(.b0_dcs_otp_z1_pswdlock)) }    > B0_DCS_OTP_Z1_PSWDLOCK
  .b0_dcs_otp_z1_bootctrl_section    : { KEEP(*(.b0_dcs_otp_z1_bootctrl)) }    > B0_DCS_OTP_Z1_BOOTCTRL
  .b0_dcs_zsel_z1_section            : { KEEP(*(.b0_dcs_zsel_z1)) }            > B0_DCS_ZSEL_Z1

  .b0_dcs_otp_z2_linkpointer_section : { KEEP(*(.b0_dcs_otp_z2_linkpointer)) } > B0_DCS_OTP_Z2_LINKPOINTER
  .b0_dcs_otp_z2_gpreg_section       : { KEEP(*(.b0_dcs_otp_z2_gpreg)) }       > B0_DCS_OTP_Z2_GPREG
  .b0_dcs_otp_z2_pswdlock_section    : { KEEP(*(.b0_dcs_otp_z2_pswdlock)) }    > B0_DCS_OTP_Z2_PSWDLOCK
  .b0_dcs_otp_z2_bootctrl_section    : { KEEP(*(.b0_dcs_otp_z2_bootctrl)) }    > B0_DCS_OTP_Z2_BOOTCTRL
  .b0_dcs_zsel_z2_section            : { KEEP(*(.b0_dcs_zsel_z2)) }            > B0_DCS_ZSEL_Z2

  .b1_dcs_otp_z1_linkpointer_section : { KEEP(*(.b1_dcs_otp_z1_linkpointer)) } > B1_DCS_OTP_Z1_LINKPOINTER
  .b1_dcs_otp_z1_cmac_key_section    : { KEEP(*(.b1_dcs_otp_z1_cmac_key)) }    > B1_DCS_OTP_Z1_CMAC_KEY
  .b1_dcs_zsel_z1_section            : { KEEP(*(.b1_dcs_zsel_z1)) }            > B1_DCS_ZSEL_Z1

  .b1_dcs_otp_z2_linkpointer_section : { KEEP(*(.b1_dcs_otp_z2_linkpointer)) } > B1_DCS_OTP_Z2_LINKPOINTER
  .b1_dcs_zsel_z2_section            : { KEEP(*(.b1_dcs_zsel_z2)) }            > B1_DCS_ZSEL_Z2
}
