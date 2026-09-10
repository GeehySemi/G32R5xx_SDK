/*!
 * @file        g32r501xxx_peripheral_memory.ld
 *
 * @brief       Linker script for G32R501 series peripheral
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
  ADCA            (rw): ORIGIN = 0x40020000, LENGTH = 0x400
  ADCB            (rw): ORIGIN = 0x40020400, LENGTH = 0x400
  ADCC            (rw): ORIGIN = 0x40020800, LENGTH = 0x400
  ADCA_RESULT     (rw): ORIGIN = 0x40020100, LENGTH = 0x30
  ADCB_RESULT     (rw): ORIGIN = 0x40000500, LENGTH = 0x30
  ADCC_RESULT     (rw): ORIGIN = 0x40000900, LENGTH = 0x30
  AS              (rw): ORIGIN = 0x50028000, LENGTH = 0x400
  CANA            (rw): ORIGIN = 0x50002000, LENGTH = 0x1000
  CANB            (rw): ORIGIN = 0x50104000, LENGTH = 0x1000
  CAP1            (rw): ORIGIN = 0x40002000, LENGTH = 0x400
  CAP2            (rw): ORIGIN = 0x40002400, LENGTH = 0x400
  CAP3            (rw): ORIGIN = 0x40002800, LENGTH = 0x400
  CAP4            (rw): ORIGIN = 0x40002C00, LENGTH = 0x400
  CAP5            (rw): ORIGIN = 0x40003000, LENGTH = 0x400
  CAP6            (rw): ORIGIN = 0x40003400, LENGTH = 0x400
  CAP7            (rw): ORIGIN = 0x40003800, LENGTH = 0x400
  CLK_CFG         (rw): ORIGIN = 0x50020800, LENGTH = 0x100
  COMP1           (rw): ORIGIN = 0x40011C00, LENGTH = 0x400
  COMP2           (rw): ORIGIN = 0x40012000, LENGTH = 0x400
  COMP3           (rw): ORIGIN = 0x40012400, LENGTH = 0x400
  COMP4           (rw): ORIGIN = 0x40012800, LENGTH = 0x400
  COMP5           (rw): ORIGIN = 0x40012C00, LENGTH = 0x400
  COMP6           (rw): ORIGIN = 0x40013000, LENGTH = 0x400
  COMP7           (rw): ORIGIN = 0x40013400, LENGTH = 0x400
  CPU_SYS         (rw): ORIGIN = 0x50020A00, LENGTH = 0x200
  DACA            (rw): ORIGIN = 0x50001800, LENGTH = 0x400
  DACB            (rw): ORIGIN = 0x50001C00, LENGTH = 0x400
  DCCOMP0         (rw): ORIGIN = 0x50101400, LENGTH = 0x400
  DCS_B0Z1        (rw): ORIGIN = 0x50024000, LENGTH = 0x60
  DCS_B0Z2        (rw): ORIGIN = 0x50024080, LENGTH = 0x60
  DCS_B1Z1        (rw): ORIGIN = 0x50024200, LENGTH = 0x60
  DCS_B1Z2        (rw): ORIGIN = 0x50024280, LENGTH = 0x60
  DCS_COMMON      (rw): ORIGIN = 0x500240E0, LENGTH = 0x20
  DEV_CFG         (rw): ORIGIN = 0x50020500, LENGTH = 0x300
  DMA_CHSEL       (rw): ORIGIN = 0x50020400, LENGTH = 0x100
  DMA             (rw): ORIGIN = 0x50110C00, LENGTH = 0x400
  EXTI            (rw): ORIGIN = 0x50111000, LENGTH = 0x3C
  FLASH0_CTRL     (rw): ORIGIN = 0x50010000, LENGTH = 0x304
  FLASH0_ECC      (rw): ORIGIN = 0x50010600, LENGTH = 0x60
  FLB1_DATA_EXCH  (rw): ORIGIN = 0x50102400, LENGTH = 0x400
  FLB2_DATA_EXCH  (rw): ORIGIN = 0x50102C00, LENGTH = 0x400
  FLB3_DATA_EXCH  (rw): ORIGIN = 0x50103400, LENGTH = 0x400
  FLB4_DATA_EXCH  (rw): ORIGIN = 0x50103C00, LENGTH = 0x400
  FLB1_LOGIC_CFG  (rw): ORIGIN = 0x50102000, LENGTH = 0x100
  FLB2_LOGIC_CFG  (rw): ORIGIN = 0x50102800, LENGTH = 0x100
  FLB3_LOGIC_CFG  (rw): ORIGIN = 0x50103000, LENGTH = 0x100
  FLB4_LOGIC_CFG  (rw): ORIGIN = 0x50103800, LENGTH = 0x100
  FLB1_LOGIC_CTRL (rw): ORIGIN = 0x50102200, LENGTH = 0x100
  FLB2_LOGIC_CTRL (rw): ORIGIN = 0x50102A00, LENGTH = 0x100
  FLB3_LOGIC_CTRL (rw): ORIGIN = 0x50103200, LENGTH = 0x100
  FLB4_LOGIC_CTRL (rw): ORIGIN = 0x50103A00, LENGTH = 0x100
  FLB_XBAR        (rw): ORIGIN = 0x40031240, LENGTH = 0x80
  GPIO_CTRL       (rw): ORIGIN = 0x40030000, LENGTH = 0x800
  GPIO_DATA       (rw): ORIGIN = 0x40030800, LENGTH = 0x400
  HRCAP6          (rw): ORIGIN = 0x40033440, LENGTH = 0x40
  HRCAP7          (rw): ORIGIN = 0x40033840, LENGTH = 0x40
  I2CA            (rw): ORIGIN = 0x50001400, LENGTH = 0x400
  INPUT_XBAR      (rw): ORIGIN = 0x40030C00, LENGTH = 0x80
  LINA            (rw): ORIGIN = 0x50000000, LENGTH = 0x400
  NMI             (rw): ORIGIN = 0x500264C0, LENGTH = 0x10
  OUTPUT_XBAR     (rw): ORIGIN = 0x400312C0, LENGTH = 0x80
  PERIPH_AC       (rw): ORIGIN = 0x50020C00, LENGTH = 0x400
  PMBUSA          (rw): ORIGIN = 0x50100800, LENGTH = 0x400
  PWM1            (rw): ORIGIN = 0x40000000, LENGTH = 0x400
  PWM2            (rw): ORIGIN = 0x40000400, LENGTH = 0x400
  PWM3            (rw): ORIGIN = 0x40000800, LENGTH = 0x400
  PWM4            (rw): ORIGIN = 0x40000C00, LENGTH = 0x400
  PWM5            (rw): ORIGIN = 0x40001000, LENGTH = 0x400
  PWM6            (rw): ORIGIN = 0x40001400, LENGTH = 0x400
  PWM7            (rw): ORIGIN = 0x40001800, LENGTH = 0x400
  PWM8            (rw): ORIGIN = 0x40001C00, LENGTH = 0x400
  PWM_XBAR        (rw): ORIGIN = 0x400311C0, LENGTH = 0x80
  QEP1            (rw): ORIGIN = 0x40013800, LENGTH = 0x400
  QEP2            (rw): ORIGIN = 0x40013C00, LENGTH = 0x400
  QSPI            (rw): ORIGIN = 0x50111000, LENGTH = 0x354
  SDF1            (rw): ORIGIN = 0x40003C00, LENGTH = 0x400
  SPIA            (rw): ORIGIN = 0x50001000, LENGTH = 0x400
  SPIB            (rw): ORIGIN = 0x50100400, LENGTH = 0x400
  SYNCSOC         (rw): ORIGIN = 0x40030C80, LENGTH = 0xC
  SYSCTL          (rw): ORIGIN = 0x50020000, LENGTH = 0x7C
  TMR0            (rw): ORIGIN = 0x50110000, LENGTH = 0x400
  TMR1            (rw): ORIGIN = 0x50110400, LENGTH = 0x400
  TMR2            (rw): ORIGIN = 0x50110800, LENGTH = 0x400
  UARTA           (rw): ORIGIN = 0x50000C00, LENGTH = 0x400
  UARTB           (rw): ORIGIN = 0x50100000, LENGTH = 0x400
  WDT             (rw): ORIGIN = 0x50026400, LENGTH = 0xC0
  XBAR            (rw): ORIGIN = 0x40031000, LENGTH = 0x40
}

SECTIONS
{
  .adca_section            (NOLOAD) : { *(.adca) } > ADCA
  .adcb_section            (NOLOAD) : { *(.adcb) } > ADCB
  .adcc_section            (NOLOAD) : { *(.adcc) } > ADCC
  .adca_result_section     (NOLOAD) : { *(.adca_result) } > ADCA_RESULT
  .adcb_result_section     (NOLOAD) : { *(.adcb_result) } > ADCB_RESULT
  .adcc_result_section     (NOLOAD) : { *(.adcc_result) } > ADCC_RESULT
  .as_section              (NOLOAD) : { *(.as) } > AS
  .cana_section            (NOLOAD) : { *(.cana) } > CANA
  .canb_section            (NOLOAD) : { *(.canb) } > CANB
  .cap1_section            (NOLOAD) : { *(.cap1) } > CAP1
  .cap2_section            (NOLOAD) : { *(.cap2) } > CAP2
  .cap3_section            (NOLOAD) : { *(.cap3) } > CAP3
  .cap4_section            (NOLOAD) : { *(.cap4) } > CAP4
  .cap5_section            (NOLOAD) : { *(.cap5) } > CAP5
  .cap6_section            (NOLOAD) : { *(.cap6) } > CAP6
  .cap7_section            (NOLOAD) : { *(.cap7) } > CAP7
  .clk_cfg_section         (NOLOAD) : { *(.clk_cfg) } > CLK_CFG
  .comp1_section           (NOLOAD) : { *(.comp1) } > COMP1
  .comp2_section           (NOLOAD) : { *(.comp2) } > COMP2
  .comp3_section           (NOLOAD) : { *(.comp3) } > COMP3
  .comp4_section           (NOLOAD) : { *(.comp4) } > COMP4
  .comp5_section           (NOLOAD) : { *(.comp5) } > COMP5
  .comp6_section           (NOLOAD) : { *(.comp6) } > COMP6
  .comp7_section           (NOLOAD) : { *(.comp7) } > COMP7
  .cpu_sys_section         (NOLOAD) : { *(.cpu_sys) } > CPU_SYS
  .daca_section            (NOLOAD) : { *(.daca) } > DACA
  .dacb_section            (NOLOAD) : { *(.dacb) } > DACB
  .dccomp0_section         (NOLOAD) : { *(.dccomp0) } > DCCOMP0
  .dcs_b0z1_section        (NOLOAD) : { *(.dcs_b0z1) } > DCS_B0Z1
  .dcs_b0z2_section        (NOLOAD) : { *(.dcs_b0z2) } > DCS_B0Z2
  .dcs_b1z1_section        (NOLOAD) : { *(.dcs_b1z1) } > DCS_B1Z1
  .dcs_b1z2_section        (NOLOAD) : { *(.dcs_b1z2) } > DCS_B1Z2
  .dcs_common_section      (NOLOAD) : { *(.dcs_common) } > DCS_COMMON
  .dev_cfg_section         (NOLOAD) : { *(.dev_cfg) } > DEV_CFG
  .dma_chsel_section       (NOLOAD) : { *(.dma_chsel) } > DMA_CHSEL
  .dma_section             (NOLOAD) : { *(.dma) } > DMA
  .exti_section            (NOLOAD) : { *(.exti) } > EXTI
  .flash0_ctrl_section     (NOLOAD) : { *(.flash0_ctrl) } > FLASH0_CTRL
  .flash0_ecc_section      (NOLOAD) : { *(.flash0_ecc) } > FLASH0_ECC
  .flb1_data_exch_section  (NOLOAD) : { *(.flb1_data_exch) } > FLB1_DATA_EXCH
  .flb2_data_exch_section  (NOLOAD) : { *(.flb2_data_exch) } > FLB2_DATA_EXCH
  .flb3_data_exch_section  (NOLOAD) : { *(.flb3_data_exch) } > FLB3_DATA_EXCH
  .flb4_data_exch_section  (NOLOAD) : { *(.flb4_data_exch) } > FLB4_DATA_EXCH
  .flb1_logic_cfg_section  (NOLOAD) : { *(.flb1_logic_cfg) } > FLB1_LOGIC_CFG
  .flb2_logic_cfg_section  (NOLOAD) : { *(.flb2_logic_cfg) } > FLB2_LOGIC_CFG
  .flb3_logic_cfg_section  (NOLOAD) : { *(.flb3_logic_cfg) } > FLB3_LOGIC_CFG
  .flb4_logic_cfg_section  (NOLOAD) : { *(.flb4_logic_cfg) } > FLB4_LOGIC_CFG
  .flb1_logic_ctrl_section (NOLOAD) : { *(.flb1_logic_ctrl) } > FLB1_LOGIC_CTRL
  .flb2_logic_ctrl_section (NOLOAD) : { *(.flb2_logic_ctrl) } > FLB2_LOGIC_CTRL
  .flb3_logic_ctrl_section (NOLOAD) : { *(.flb3_logic_ctrl) } > FLB3_LOGIC_CTRL
  .flb4_logic_ctrl_section (NOLOAD) : { *(.flb4_logic_ctrl) } > FLB4_LOGIC_CTRL
  .flb_xbar_section        (NOLOAD) : { *(.flb_xbar) } > FLB_XBAR
  .gpio_ctrl_section       (NOLOAD) : { *(.gpio_ctrl) } > GPIO_CTRL
  .gpio_data_section       (NOLOAD) : { *(.gpio_data) } > GPIO_DATA
  .hrcap6_section          (NOLOAD) : { *(.hrcap6) } > HRCAP6
  .hrcap7_section          (NOLOAD) : { *(.hrcap7) } > HRCAP7
  .i2ca_section            (NOLOAD) : { *(.i2ca) } > I2CA
  .input_xbar_section      (NOLOAD) : { *(.input_xbar) } > INPUT_XBAR
  .lina_section            (NOLOAD) : { *(.lina) } > LINA
  .nmi_section             (NOLOAD) : { *(.nmi) } > NMI
  .output_xbar_section     (NOLOAD) : { *(.output_xbar) } > OUTPUT_XBAR
  .periph_ac_section       (NOLOAD) : { *(.periph_ac) } > PERIPH_AC
  .pmbusa_section          (NOLOAD) : { *(.pmbusa) } > PMBUSA
  .pwm1_section            (NOLOAD) : { *(.pwm1) } > PWM1
  .pwm2_section            (NOLOAD) : { *(.pwm2) } > PWM2
  .pwm3_section            (NOLOAD) : { *(.pwm3) } > PWM3
  .pwm4_section            (NOLOAD) : { *(.pwm4) } > PWM4
  .pwm5_section            (NOLOAD) : { *(.pwm5) } > PWM5
  .pwm6_section            (NOLOAD) : { *(.pwm6) } > PWM6
  .pwm7_section            (NOLOAD) : { *(.pwm7) } > PWM7
  .pwm8_section            (NOLOAD) : { *(.pwm8) } > PWM8
  .pwm_xbar_section        (NOLOAD) : { *(.pwm_xbar) } > PWM_XBAR
  .qep1_section            (NOLOAD) : { *(.qep1) } > QEP1
  .qep2_section            (NOLOAD) : { *(.qep2) } > QEP2
  .qspi_section            (NOLOAD) : { *(.qspi) } > QSPI
  .sdf1_section            (NOLOAD) : { *(.sdf1) } > SDF1
  .spia_section            (NOLOAD) : { *(.spia) } > SPIA
  .spib_section            (NOLOAD) : { *(.spib) } > SPIB
  .syncsoc_section         (NOLOAD) : { *(.syncsoc) } > SYNCSOC
  .sysctl_section          (NOLOAD) : { *(.sysctl) } > SYSCTL
  .tmr0_section            (NOLOAD) : { *(.tmr0) } > TMR0
  .tmr1_section            (NOLOAD) : { *(.tmr1) } > TMR1
  .tmr2_section            (NOLOAD) : { *(.tmr2) } > TMR2
  .uarta_section           (NOLOAD) : { *(.uarta) } > UARTA
  .uartb_section           (NOLOAD) : { *(.uartb) } > UARTB
  .wdt_section             (NOLOAD) : { *(.wdt) } > WDT
  .xbar_section            (NOLOAD) : { *(.xbar) } > XBAR
}
