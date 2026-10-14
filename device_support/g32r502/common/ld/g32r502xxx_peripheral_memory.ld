/*!
 * @file        g32r502xxx_peripheral_memory.ld
 *
 * @brief       Linker script for G32R502 peripheral register emulation (device_support bitfield)
 *
 * @version     V1.0.0
 *
 * @date        2026-06-30
 *
 */

MEMORY
{
  DCCOMP0            (rw): ORIGIN = 0x40000000, LENGTH = 0x400
  LINA               (rw): ORIGIN = 0x40000400, LENGTH = 0x400
  UARTA              (rw): ORIGIN = 0x40000800, LENGTH = 0x400
  UARTB              (rw): ORIGIN = 0x40000C00, LENGTH = 0x400
  UARTC              (rw): ORIGIN = 0x40001000, LENGTH = 0x400
  SPIA               (rw): ORIGIN = 0x40001400, LENGTH = 0x400
  I2CA               (rw): ORIGIN = 0x40001800, LENGTH = 0x400
  I2CB               (rw): ORIGIN = 0x40001C00, LENGTH = 0x400
  PMBUSA             (rw): ORIGIN = 0x40002000, LENGTH = 0x400
  CANA               (rw): ORIGIN = 0x40002400, LENGTH = 0x800
  CANFDA             (rw): ORIGIN = 0x40002C00, LENGTH = 0x800
  CANFDA_SRAM        (rw): ORIGIN = 0x40003400, LENGTH = 0x1000

  WDT                (rw): ORIGIN = 0x40010000, LENGTH = 0xC0
  NMI                (rw): ORIGIN = 0x400100C0, LENGTH = 0x340
  EXTI               (rw): ORIGIN = 0x40010400, LENGTH = 0x400
  DCS_B0Z1           (rw): ORIGIN = 0x40010800, LENGTH = 0x80
  DCS_B0Z2           (rw): ORIGIN = 0x40010880, LENGTH = 0x60
  DCS_COMMON         (rw): ORIGIN = 0x400108E0, LENGTH = 0x120
  DCS_B1Z1           (rw): ORIGIN = 0x40010A00, LENGTH = 0x80
  DCS_B1Z2           (rw): ORIGIN = 0x40010A80, LENGTH = 0x60
  SYSCTL             (rw): ORIGIN = 0x40012C00, LENGTH = 0x400
  DMA_CHSEL          (rw): ORIGIN = 0x40013000, LENGTH = 0x100
  DEV_CFG            (rw): ORIGIN = 0x40013100, LENGTH = 0x300
  CLK_CFG            (rw): ORIGIN = 0x40013400, LENGTH = 0x200
  CPU_SYS            (rw): ORIGIN = 0x40013600, LENGTH = 0x200
  PERIPH_AC          (rw): ORIGIN = 0x40013800, LENGTH = 0x400
  AS                 (rw): ORIGIN = 0x40016C00, LENGTH = 0x400
  TMR0               (rw): ORIGIN = 0x40017000, LENGTH = 0x400
  TMR1               (rw): ORIGIN = 0x40017400, LENGTH = 0x400
  TMR2               (rw): ORIGIN = 0x40017800, LENGTH = 0x400
  FLASH_CTRL         (rw): ORIGIN = 0x40017C00, LENGTH = 0x600
  FLASH_ECC          (rw): ORIGIN = 0x40018200, LENGTH = 0x200
  DMA                (rw): ORIGIN = 0x40018400, LENGTH = 0x400

  QEP1               (rw): ORIGIN = 0x40020000, LENGTH = 0x400
  CAP1               (rw): ORIGIN = 0x40020400, LENGTH = 0x400
  CAP2               (rw): ORIGIN = 0x40020800, LENGTH = 0x400
  CAP3               (rw): ORIGIN = 0x40020C00, LENGTH = 0x400
  COMP1              (rw): ORIGIN = 0x40021000, LENGTH = 0x400
  COMP2              (rw): ORIGIN = 0x40021400, LENGTH = 0x400
  COMP3              (rw): ORIGIN = 0x40021800, LENGTH = 0x400
  COMP4              (rw): ORIGIN = 0x40021C00, LENGTH = 0x400
  FLB1_LOGIC_CFG     (rw): ORIGIN = 0x40022000, LENGTH = 0x200
  FLB1_LOGIC_CTRL    (rw): ORIGIN = 0x40022200, LENGTH = 0x200
  FLB1_DATA_EXCH     (rw): ORIGIN = 0x40022400, LENGTH = 0x400
  FLB2_LOGIC_CFG     (rw): ORIGIN = 0x40022800, LENGTH = 0x200
  FLB2_LOGIC_CTRL    (rw): ORIGIN = 0x40022A00, LENGTH = 0x200
  FLB2_DATA_EXCH     (rw): ORIGIN = 0x40022C00, LENGTH = 0x400
  FLB3_LOGIC_CFG     (rw): ORIGIN = 0x40023000, LENGTH = 0x200
  FLB3_LOGIC_CTRL    (rw): ORIGIN = 0x40023200, LENGTH = 0x200
  FLB3_DATA_EXCH     (rw): ORIGIN = 0x40023400, LENGTH = 0x400
  FLB4_LOGIC_CFG     (rw): ORIGIN = 0x40023800, LENGTH = 0x200
  FLB4_LOGIC_CTRL    (rw): ORIGIN = 0x40023A00, LENGTH = 0x200
  FLB4_DATA_EXCH     (rw): ORIGIN = 0x40023C00, LENGTH = 0x400
  DACA               (rw): ORIGIN = 0x40024000, LENGTH = 0x400
  DACB               (rw): ORIGIN = 0x40024400, LENGTH = 0x400

  GPIO_CTRL          (rw): ORIGIN = 0x40030000, LENGTH = 0x800
  GPIO_DATA          (rw): ORIGIN = 0x40030800, LENGTH = 0x400
  INPUT_XBAR         (rw): ORIGIN = 0x40030C00, LENGTH = 0x80
  SYNCSOC            (rw): ORIGIN = 0x40030C80, LENGTH = 0x380
  XBAR               (rw): ORIGIN = 0x40031000, LENGTH = 0x40
  PWM_XBAR           (rw): ORIGIN = 0x400311C0, LENGTH = 0x80
  FLB_XBAR           (rw): ORIGIN = 0x40031240, LENGTH = 0x80
  OUTPUT_XBAR        (rw): ORIGIN = 0x400312C0, LENGTH = 0x140

  PWM1               (rw): ORIGIN = 0x50000000, LENGTH = 0x400
  PWM2               (rw): ORIGIN = 0x50000400, LENGTH = 0x400
  PWM3               (rw): ORIGIN = 0x50000800, LENGTH = 0x400
  PWM4               (rw): ORIGIN = 0x50000C00, LENGTH = 0x400
  PWM5               (rw): ORIGIN = 0x50001000, LENGTH = 0x400
  PWM6               (rw): ORIGIN = 0x50001400, LENGTH = 0x400
  PWM7               (rw): ORIGIN = 0x50001800, LENGTH = 0x400
  ADCA               (rw): ORIGIN = 0x50001C00, LENGTH = 0x100
  ADCA_RESULT        (rw): ORIGIN = 0x50001D00, LENGTH = 0x300
  ADCC               (rw): ORIGIN = 0x50002000, LENGTH = 0x100
  ADCC_RESULT        (rw): ORIGIN = 0x50002100, LENGTH = 0x30
}

SECTIONS
{
  .adca_section                  (NOLOAD) : { *(.adca) } > ADCA
  .adca_result_section           (NOLOAD) : { *(.adca_result) } > ADCA_RESULT
  .adcc_section                  (NOLOAD) : { *(.adcc) } > ADCC
  .adcc_result_section           (NOLOAD) : { *(.adcc_result) } > ADCC_RESULT
  .as_section                    (NOLOAD) : { *(.as) } > AS
  .cana_section                  (NOLOAD) : { *(.cana) } > CANA
  .canfda_section                (NOLOAD) : { *(.canfda) } > CANFDA
  .flb_xbar_section              (NOLOAD) : { *(.flb_xbar) } > FLB_XBAR
  .clk_cfg_section               (NOLOAD) : { *(.clk_cfg) } > CLK_CFG
  .comp1_section                 (NOLOAD) : { *(.comp1) } > COMP1
  .comp2_section                 (NOLOAD) : { *(.comp2) } > COMP2
  .comp3_section                 (NOLOAD) : { *(.comp3) } > COMP3
  .comp4_section                 (NOLOAD) : { *(.comp4) } > COMP4
  .tmr0_section                  (NOLOAD) : { *(.tmr0) } > TMR0
  .tmr1_section                  (NOLOAD) : { *(.tmr1) } > TMR1
  .tmr2_section                  (NOLOAD) : { *(.tmr2) } > TMR2
  .cpu_sys_section               (NOLOAD) : { *(.cpu_sys) } > CPU_SYS
  .daca_section                  (NOLOAD) : { *(.daca) } > DACA
  .dacb_section                  (NOLOAD) : { *(.dacb) } > DACB
  .dccomp0_section               (NOLOAD) : { *(.dccomp0) } > DCCOMP0
  .dev_cfg_section               (NOLOAD) : { *(.dev_cfg) } > DEV_CFG
  .dma_chsel_section             (NOLOAD) : { *(.dma_chsel) } > DMA_CHSEL
  .dma_section                   (NOLOAD) : { *(.dma) } > DMA
  .cap1_section                  (NOLOAD) : { *(.cap1) } > CAP1
  .cap2_section                  (NOLOAD) : { *(.cap2) } > CAP2
  .cap3_section                  (NOLOAD) : { *(.cap3) } > CAP3
  .pwm1_section                  (NOLOAD) : { *(.pwm1) } > PWM1
  .pwm2_section                  (NOLOAD) : { *(.pwm2) } > PWM2
  .pwm3_section                  (NOLOAD) : { *(.pwm3) } > PWM3
  .pwm4_section                  (NOLOAD) : { *(.pwm4) } > PWM4
  .pwm5_section                  (NOLOAD) : { *(.pwm5) } > PWM5
  .pwm6_section                  (NOLOAD) : { *(.pwm6) } > PWM6
  .pwm7_section                  (NOLOAD) : { *(.pwm7) } > PWM7
  .pwm_xbar_section              (NOLOAD) : { *(.pwm_xbar) } > PWM_XBAR
  .qep1_section                  (NOLOAD) : { *(.qep1) } > QEP1
  .gpio_ctrl_section             (NOLOAD) : { *(.gpio_ctrl) } > GPIO_CTRL
  .gpio_data_section             (NOLOAD) : { *(.gpio_data) } > GPIO_DATA
  .i2ca_section                  (NOLOAD) : { *(.i2ca) } > I2CA
  .i2cb_section                  (NOLOAD) : { *(.i2cb) } > I2CB
  .input_xbar_section            (NOLOAD) : { *(.input_xbar) } > INPUT_XBAR
  .lina_section                  (NOLOAD) : { *(.lina) } > LINA
  .nmi_section                   (NOLOAD) : { *(.nmi) } > NMI
  .output_xbar_section           (NOLOAD) : { *(.output_xbar) } > OUTPUT_XBAR
  .periph_ac_section             (NOLOAD) : { *(.periph_ac) } > PERIPH_AC
  .pmbusa_section                (NOLOAD) : { *(.pmbusa) } > PMBUSA
  .uarta_section                 (NOLOAD) : { *(.uarta) } > UARTA
  .uartb_section                 (NOLOAD) : { *(.uartb) } > UARTB
  .uartc_section                 (NOLOAD) : { *(.uartc) } > UARTC
  .spia_section                  (NOLOAD) : { *(.spia) } > SPIA
  .syncsoc_section               (NOLOAD) : { *(.syncsoc) } > SYNCSOC
  .wdt_section                   (NOLOAD) : { *(.wdt) } > WDT
  .xbar_section                  (NOLOAD) : { *(.xbar) } > XBAR
  .exti_section                  (NOLOAD) : { *(.exti) } > EXTI
  .sysctl_section                (NOLOAD) : { *(.sysctl) } > SYSCTL
  .flash_ctrl_section            (NOLOAD) : { *(.flash_ctrl) } > FLASH_CTRL
  .flash_ecc_section             (NOLOAD) : { *(.flash_ecc) } > FLASH_ECC
  .flb1_data_exch_section        (NOLOAD) : { *(.flb1_data_exch) } > FLB1_DATA_EXCH
  .flb2_data_exch_section        (NOLOAD) : { *(.flb2_data_exch) } > FLB2_DATA_EXCH
  .flb3_data_exch_section        (NOLOAD) : { *(.flb3_data_exch) } > FLB3_DATA_EXCH
  .flb4_data_exch_section        (NOLOAD) : { *(.flb4_data_exch) } > FLB4_DATA_EXCH
  .flb1_logic_cfg_section        (NOLOAD) : { *(.flb1_logic_cfg) } > FLB1_LOGIC_CFG
  .flb2_logic_cfg_section        (NOLOAD) : { *(.flb2_logic_cfg) } > FLB2_LOGIC_CFG
  .flb3_logic_cfg_section        (NOLOAD) : { *(.flb3_logic_cfg) } > FLB3_LOGIC_CFG
  .flb4_logic_cfg_section        (NOLOAD) : { *(.flb4_logic_cfg) } > FLB4_LOGIC_CFG
  .flb1_logic_ctrl_section       (NOLOAD) : { *(.flb1_logic_ctrl) } > FLB1_LOGIC_CTRL
  .flb2_logic_ctrl_section       (NOLOAD) : { *(.flb2_logic_ctrl) } > FLB2_LOGIC_CTRL
  .flb3_logic_ctrl_section       (NOLOAD) : { *(.flb3_logic_ctrl) } > FLB3_LOGIC_CTRL
  .flb4_logic_ctrl_section       (NOLOAD) : { *(.flb4_logic_ctrl) } > FLB4_LOGIC_CTRL
  .dcs_b0z1_section              (NOLOAD) : { *(.dcs_b0z1) } > DCS_B0Z1
  .dcs_b0z2_section              (NOLOAD) : { *(.dcs_b0z2) } > DCS_B0Z2
  .dcs_b1z1_section              (NOLOAD) : { *(.dcs_b1z1) } > DCS_B1Z1
  .dcs_b1z2_section              (NOLOAD) : { *(.dcs_b1z2) } > DCS_B1Z2
  .dcs_common_section            (NOLOAD) : { *(.dcs_common) } > DCS_COMMON
}
