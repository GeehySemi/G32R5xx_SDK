//###########################################################################
//
// FILE:    g32r502_globalvariabledefs.c
//
// TITLE:   g32r502 Global Variables and Data Section Pragmas.
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

#include "g32r502_device.h"     // g32r502 Headerfile Include File
#include "hw_memmap.h"

#define __AT(ADDR)          __attribute__((section(".bss.ARM.__at_" #ADDR)))

#define AT_ADDR(ADDR)       __AT(ADDR)

//---------------------------------------------------------------------------
// Define Global Peripheral Variables:
//

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(ADCA_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".adca")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = ADCA_BASE
#endif
volatile struct ADC_REGS AdcaRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(ADCARESULT_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".adca_result")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = ADCARESULT_BASE
#endif
volatile  struct ADC_RESULT_REGS AdcaResultRegs;

#if defined (__ARMCC_VERSION)
    AT_ADDR(ADCC_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".adcc")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = ADCC_BASE
#endif
volatile struct ADC_REGS AdccRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(ADCCRESULT_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".adcc_result")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = ADCCRESULT_BASE
#endif
volatile  struct ADC_RESULT_REGS AdccResultRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(ANALOGSUBSYS_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".as")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = ANALOGSUBSYS_BASE
#endif
volatile struct AS_REGS ASRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(CANA_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".cana")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = CANA_BASE
#endif
volatile struct CAN_REGS CanaRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(CANFDA_DRIVER_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".canfda")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = CANFDA_DRIVER_BASE
#endif
volatile struct CANFD_REGS CanfdaRegs;


//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(CLKCFG_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".clk_cfg")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = CLKCFG_BASE
#endif
volatile struct CLK_REGS ClkCfgRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(COMP1_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".comp1")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = COMP1_BASE
#endif
volatile struct COMP_REGS Comp1Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(COMP2_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".comp2")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = COMP2_BASE
#endif
volatile struct COMP_REGS Comp2Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(COMP3_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".comp3")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = COMP3_BASE
#endif
volatile struct COMP_REGS Comp3Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(COMP4_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".comp4")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = COMP4_BASE
#endif
volatile struct COMP_REGS Comp4Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(TMR0_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".tmr0")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = TMR0_BASE
#endif
volatile struct TMR_REGS Timer0Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(TMR1_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".tmr1")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = TMR1_BASE
#endif
volatile struct TMR_REGS Timer1Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(TMR2_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".tmr2")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = TMR2_BASE
#endif
volatile struct TMR_REGS Timer2Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(CPUSYS_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".cpu_sys")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = CPUSYS_BASE
#endif
volatile struct CPU_REGS CpuSysRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(DACA_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".daca")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = DACA_BASE
#endif
volatile struct DAC_REGS DacaRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(DACB_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".dacb")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = DACB_BASE
#endif
volatile struct DAC_REGS DacbRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(DCCOMP0_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".dccomp0")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = DCCOMP0_BASE
#endif
volatile struct DCCOMP_REGS Dccomp0Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(DEVCFG_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".dev_cfg")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = DEVCFG_BASE
#endif
volatile struct DEV_REGS DevCfgRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(DMACHSEL_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".dma_chsel")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = DMACHSEL_BASE
#endif
volatile struct DMA_CH_SEL_REGS DmaChSelRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(DMA_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".dma")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = DMA_BASE
#endif
volatile struct DMA_REGS DmaRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(CAP1_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".cap1")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = CAP1_BASE
#endif
volatile struct CAP_REGS Cap1Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(CAP2_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".cap2")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = CAP2_BASE
#endif
volatile struct CAP_REGS Cap2Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(CAP3_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".cap3")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = CAP3_BASE
#endif
volatile struct CAP_REGS Cap3Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(PWM1_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".pwm1")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = PWM1_BASE
#endif
volatile struct PWM_REGS Pwm1Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(PWM2_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".pwm2")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = PWM2_BASE
#endif
volatile struct PWM_REGS Pwm2Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(PWM3_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".pwm3")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = PWM3_BASE
#endif
volatile struct PWM_REGS Pwm3Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(PWM4_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".pwm4")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = PWM4_BASE
#endif
volatile struct PWM_REGS Pwm4Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(PWM5_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".pwm5")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = PWM5_BASE
#endif
volatile struct PWM_REGS Pwm5Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(PWM6_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".pwm6")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = PWM6_BASE
#endif
volatile struct PWM_REGS Pwm6Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(PWM7_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".pwm7")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = PWM7_BASE
#endif
volatile struct PWM_REGS Pwm7Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(PWMXBAR_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".pwm_xbar")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = PWMXBAR_BASE
#endif
volatile struct PWM_XBAR_REGS PwmXbarRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(QEP1_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".qep1")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = QEP1_BASE
#endif
volatile struct QEP_REGS Qep1Regs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(GPIOCTRL_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".gpio_ctrl")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = GPIOCTRL_BASE
#endif
volatile struct GPIO_CTRL_REGS GpioCtrlRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(GPIODATA_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".gpio_data")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = GPIODATA_BASE
#endif
volatile struct GPIO_DATA_REGS GpioDataRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(I2CA_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".i2ca")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = I2CA_BASE
#endif
volatile struct I2C_REGS I2caRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(I2CB_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".i2cb")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = I2CB_BASE
#endif
volatile struct I2C_REGS I2cbRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(INPUTXBAR_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".input_xbar")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = INPUTXBAR_BASE
#endif
volatile struct INPUT_XBAR_REGS InputXbarRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(LINA_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".lina")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = LINA_BASE
#endif
volatile struct LIN_REGS LinaRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(NMI_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".nmi")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = NMI_BASE
#endif
volatile struct NMI_REGS NmiRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(OUTPUTXBAR_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".output_xbar")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = OUTPUTXBAR_BASE
#endif
volatile struct OUTPUT_XBAR_REGS OutputXbarRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(PERIPHAC_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".periph_ac")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = PERIPHAC_BASE
#endif
volatile struct  PERIPH_REGS SysPeriphAcRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(PMBUSA_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".pmbusa")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = PMBUSA_BASE
#endif
volatile struct PMBUS_REGS PmbusaRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(UARTA_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".uarta")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = UARTA_BASE
#endif
volatile struct UART_REGS UartaRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(UARTB_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".uartb")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = UARTB_BASE
#endif
volatile struct UART_REGS UartbRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(UARTC_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".uartc")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = UARTC_BASE
#endif
volatile struct UART_REGS UartcRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(SPIA_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".spia")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = SPIA_BASE
#endif
volatile struct SPI_REGS SpiaRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(SYNCSOC_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".syncsoc")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = SYNCSOC_BASE
#endif
volatile struct SYNC_SOC_REGS SyncSocRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(WDT_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".wdt")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = WDT_BASE
#endif
volatile struct WDT_REGS WdtRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(XBAR_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".xbar")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = XBAR_BASE
#endif
volatile struct XBAR_REGS XbarRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(EXTI_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".exti")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = EXTI_BASE
#endif
volatile struct EXTI_REGS ExtiRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(SYSCTL_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".sysctl")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = SYSCTL_BASE
#endif
volatile struct SPEC_REGS SysCtlRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(FLASH0CTRL_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".flash_ctrl")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = FLASH0CTRL_BASE
#endif
volatile struct FLASH_CTRL_REGS FlashCtrlRegs;

//----------------------------------------
#if defined (__ARMCC_VERSION)
    AT_ADDR(FLASH0ECC_BASE)
#elif defined (__GNUC__) && !defined (__ARMCC_VERSION)
    __attribute__((section(".flash_ecc")))
#elif defined (__CC_ARM) || defined (__ICCARM__)
    #pragma location = FLASH0ECC_BASE
#endif
volatile struct FLASH_ECC_REGS FlashEccRegs;


// G32R5xx extension module
