//###########################################################################
//
// FILE:    startup_g32r501.c
//
// TITLE:   CMSIS-Core(M) Device Startup File for G32R501.
//
// VERSION: 1.0.1
//
// DATE:    2025-04-15
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

#include "g32r501.h"

//*****************************************************************************
//
// External References
//
//*****************************************************************************
extern uint32_t __INITIAL_SP;
extern uint32_t __STACK_LIMIT;

extern __NO_RETURN void __PROGRAM_START(void);

//*****************************************************************************
//
// Internal References
//
//*****************************************************************************
__NO_RETURN void Reset_Handler    (void);
            void HardFault_Handler(void);
            void Default_Handler  (void);

//*****************************************************************************
//
// Exception / Interrupt Handler
//
//*****************************************************************************
//
// Exceptions
//
void NMI_Handler              (void) __attribute__ ((weak));
void HardFault_Handler        (void) __attribute__ ((weak));
void MemManage_Handler        (void) __attribute__ ((weak));
void BusFault_Handler         (void) __attribute__ ((weak));
void UsageFault_Handler       (void) __attribute__ ((weak));
void SecureFault_Handler      (void) __attribute__ ((weak));
void SVC_Handler              (void) __attribute__ ((weak));
void DebugMon_Handler         (void) __attribute__ ((weak));
void PendSV_Handler           (void) __attribute__ ((weak));
void SysTick_Handler          (void) __attribute__ ((weak));

//
// Interrupts
//
void DCCOMP_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void TMR1_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void TMR2_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void RAM_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void IPC_TE0_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void IPC_TE1_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void IPC_TE2_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void IPC_TE3_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void IPC_RF0_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void IPC_RF1_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void IPC_RF2_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void IPC_RF3_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void IPC_GP0_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void IPC_GP1_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void IPC_GP2_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void IPC_GP3_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCA1_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCB1_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCC1_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void TMR0_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void WAKE_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM1_TZ_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM2_TZ_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM3_TZ_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM4_TZ_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM5_TZ_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM6_TZ_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM7_TZ_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM8_TZ_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM1_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM2_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM3_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM4_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM5_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM6_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM7_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM8_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void CAP1_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void CAP2_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void CAP3_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void CAP4_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void CAP5_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void CAP6_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void CAP7_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void QEP1_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void QEP2_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void FLB1_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void FLB2_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void FLB3_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void FLB4_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void SPIA_RX_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void SPIA_TX_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void SPIB_RX_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void SPIB_TX_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_CH1_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_CH2_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_CH3_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_CH4_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_CH5_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_CH6_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void I2CA_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void I2CA_FIFO_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void QSPI_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void UARTA_RX_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void UARTA_TX_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void UARTB_RX_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void UARTB_TX_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void CANA0_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void CANA1_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void CANB0_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void CANB1_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCA_EVT_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCA2_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCA3_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCA4_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCB_EVT_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCB2_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCB3_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCB4_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE0_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE1_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE2_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE3_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE4_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE5_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE6_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE7_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE8_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE9_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE10_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE11_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE12_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE13_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE14_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE15_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_DZC_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_IDC_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_IOC_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_OFC_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_UFC_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_IXC_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void CAP6_2_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void CAP7_2_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void SDF1_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void SDF1DR1_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void SDF1DR2_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void SDF1DR3_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void SDF1DR4_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void LINA_0_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void LINA_1_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void PMBUSA_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCC_EVT_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCC2_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCC3_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCC4_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_CORR_ERR_Handler   (void) __attribute__ ((weak, alias("Default_Handler")));
void SYS_PLL_SLIP_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void CTI_0_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void CTI_1_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));

//*****************************************************************************
//
// Exception / Interrupt Vector Table
//
//*****************************************************************************
#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

const PINT __VECTOR_TABLE[NVIC_RAM_VECTOR_SIZE] __VECTOR_TABLE_ATTRIBUTE = {
    [0]   = (PINT)(&__INITIAL_SP),      //     Initial Stack Pointer
    [1]   = Reset_Handler,              //     Reset Handler (Code Start)
    [2]   = NMI_Handler,                // -14 NMI Handler
    [3]   = HardFault_Handler,          // -13 Hard Fault Handler
    [4]   = MemManage_Handler,          // -12 MPU Fault Handler
    [5]   = BusFault_Handler,           // -11 Bus Fault Handler
    [6]   = UsageFault_Handler,         // -10 Usage Fault Handler
    [7]   = SecureFault_Handler,        //  -9 Secure Fault Handler
    [11]  = SVC_Handler,                //  -5 SVCall Handler
    [12]  = DebugMon_Handler,           //  -4 Debug Monitor Handler
    [14]  = PendSV_Handler,             //  -2 PendSV Handler
    [15]  = SysTick_Handler,            //  -1 System Tick Handler

    //
    // Interrupts
    //
    [27]  = DCCOMP_Handler,             //  11 DCCOMP Handler
    [29]  = TMR1_Handler,               //  13 CPU Timer 1 Handler
    [30]  = TMR2_Handler,               //  14 CPU Timer 2 Handler
    [32]  = RAM_Handler,                //  16 RAM Handler
    [33]  = IPC_TE0_Handler,            //  17 IPC TE0 Handler
    [34]  = IPC_TE1_Handler,            //  18 IPC TE1 Handler
    [35]  = IPC_TE2_Handler,            //  19 IPC TE2 Handler
    [36]  = IPC_TE3_Handler,            //  20 IPC TE3 Handler
    [37]  = IPC_RF0_Handler,            //  21 IPC RF0 Handler
    [38]  = IPC_RF1_Handler,            //  22 IPC RF1 Handler
    [39]  = IPC_RF2_Handler,            //  23 IPC RF2 Handler
    [40]  = IPC_RF3_Handler,            //  24 IPC RF3 Handler
    [41]  = IPC_GP0_Handler,            //  25 IPC GP0 Handler
    [42]  = IPC_GP1_Handler,            //  26 IPC GP1 Handler
    [43]  = IPC_GP2_Handler,            //  27 IPC GP2 Handler
    [44]  = IPC_GP3_Handler,            //  28 IPC GP3 Handler
    [48]  = ADCA1_Handler,              //  32 ADCA Interrupt 1 Handler
    [49]  = ADCB1_Handler,              //  33 ADCB Interrupt 1 Handler
    [50]  = ADCC1_Handler,              //  34 ADCB Interrupt 1 Handler
    [54]  = TMR0_Handler,               //  38 Timer 0 Handler
    [55]  = WAKE_Handler,               //  39 Halt Wakeup/Watchdog Handler
    [56]  = PWM1_TZ_Handler,            //  40 PWM1 Trip Zone Handler
    [57]  = PWM2_TZ_Handler,            //  41 PWM2 Trip Zone Handler
    [58]  = PWM3_TZ_Handler,            //  42 PWM3 Trip Zone Handler
    [59]  = PWM4_TZ_Handler,            //  43 PWM4 Trip Zone Handler
    [60]  = PWM5_TZ_Handler,            //  44 PWM5 Trip Zone Handler
    [61]  = PWM6_TZ_Handler,            //  45 PWM6 Trip Zone Handler
    [62]  = PWM7_TZ_Handler,            //  46 PWM7 Trip Zone Handler
    [63]  = PWM8_TZ_Handler,            //  47 PWM8 Trip Zone Handler
    [64]  = PWM1_Handler,               //  48 PWM1 Handler
    [65]  = PWM2_Handler,               //  49 PWM2 Handler
    [66]  = PWM3_Handler,               //  50 PWM3 Handler
    [67]  = PWM4_Handler,               //  51 PWM4 Handler
    [68]  = PWM5_Handler,               //  52 PWM5 Handler
    [69]  = PWM6_Handler,               //  53 PWM6 Handler
    [70]  = PWM7_Handler,               //  54 PWM7 Handler
    [71]  = PWM8_Handler,               //  55 PWM8 Handler
    [72]  = CAP1_Handler,               //  56 CAP1 Handler
    [73]  = CAP2_Handler,               //  57 CAP2 Handler
    [74]  = CAP3_Handler,               //  58 CAP3 Handler
    [75]  = CAP4_Handler,               //  59 CAP4 Handler
    [76]  = CAP5_Handler,               //  60 CAP5 Handler
    [77]  = CAP6_Handler,               //  61 CAP6 Handler
    [78]  = CAP7_Handler,               //  62 CAP7 Handler
    [80]  = QEP1_Handler,               //  64 QEP1 Handler
    [81]  = QEP2_Handler,               //  65 QEP2 Handler
    [84]  = FLB1_Handler,               //  68 FLB1 (Reconfigurable Logic) Handler
    [85]  = FLB2_Handler,               //  69 FLB2 (Reconfigurable Logic) Handler
    [86]  = FLB3_Handler,               //  70 FLB3 (Reconfigurable Logic) Handler
    [87]  = FLB4_Handler,               //  71 FLB4 (Reconfigurable Logic) Handler
    [88]  = SPIA_RX_Handler,            //  72 SPIA Receive Handler
    [89]  = SPIA_TX_Handler,            //  73 SPIA Transmit Handler
    [90]  = SPIB_RX_Handler,            //  74 SPIB Receive Handler
    [91]  = SPIB_TX_Handler,            //  75 SPIB Transmit Handler
    [96]  = DMA_CH1_Handler,            //  80 DMA Channel 1 Handler
    [97]  = DMA_CH2_Handler,            //  81 DMA Channel 2 Handler
    [98]  = DMA_CH3_Handler,            //  82 DMA Channel 3 Handler
    [99]  = DMA_CH4_Handler,            //  83 DMA Channel 4 Handler
    [100] = DMA_CH5_Handler,            //  84 DMA Channel 5 Handler
    [101] = DMA_CH6_Handler,            //  85 DMA Channel 6 Handler
    [104] = I2CA_Handler,               //  88 I2CA Interrupt 1 Handler
    [105] = I2CA_FIFO_Handler,          //  89 I2CA Interrupt 2 Handler
    [106] = QSPI_Handler,               //  90 QSPI Handler
    [112] = UARTA_RX_Handler,           //  96 UARTA Receive Handler
    [113] = UARTA_TX_Handler,           //  97 UARTA Transmit Handler
    [114] = UARTB_RX_Handler,           //  98 UARTB Receive Handler
    [115] = UARTB_TX_Handler,           //  99 UARTB Transmit Handler
    [116] = CANA0_Handler,              // 100 CANA Interrupt 0 Handler
    [117] = CANA1_Handler,              // 101 CANA Interrupt 1 Handler
    [118] = CANB0_Handler,              // 102 CANB Interrupt 0 Handler
    [119] = CANB1_Handler,              // 103 CANB Interrupt 1 Handler
    [120] = ADCA_EVT_Handler,           // 104 ADCA Event Handler
    [121] = ADCA2_Handler,              // 105 ADCA Interrupt 2 Handler
    [122] = ADCA3_Handler,              // 106 ADCA Interrupt 3 Handler
    [123] = ADCA4_Handler,              // 107 ADCA Interrupt 4 Handler
    [124] = ADCB_EVT_Handler,           // 108 ADCB Event Handler
    [125] = ADCB2_Handler,              // 109 ADCB Interrupt 2 Handler
    [126] = ADCB3_Handler,              // 110 ADCB Interrupt 3 Handler
    [127] = ADCB4_Handler,              // 111 ADCB Interrupt 4 Handler
    [128] = EXTI_LINE0_Handler,         // 112 EXTI Line0 Handler
    [129] = EXTI_LINE1_Handler,         // 113 EXTI Line1 Handler
    [130] = EXTI_LINE2_Handler,         // 114 EXTI Line2 Handler
    [131] = EXTI_LINE3_Handler,         // 115 EXTI Line3 Handler
    [132] = EXTI_LINE4_Handler,         // 116 EXTI Line4 Handler
    [133] = EXTI_LINE5_Handler,         // 117 EXTI Line5 Handler
    [134] = EXTI_LINE6_Handler,         // 118 EXTI Line6 Handler
    [135] = EXTI_LINE7_Handler,         // 119 EXTI Line7 Handler
    [136] = EXTI_LINE8_Handler,         // 120 EXTI Line8 Handler
    [137] = EXTI_LINE9_Handler,         // 121 EXTI Line9 Handler
    [138] = EXTI_LINE10_Handler,        // 122 EXTI Line10 Handler
    [139] = EXTI_LINE11_Handler,        // 123 EXTI Line11 Handler
    [140] = EXTI_LINE12_Handler,        // 124 EXTI Line12 Handler
    [141] = EXTI_LINE13_Handler,        // 125 EXTI Line13 Handler
    [142] = EXTI_LINE14_Handler,        // 126 EXTI Line14 Handler
    [143] = EXTI_LINE15_Handler,        // 127 EXTI Line15 Handler
    [145] = FPU_DZC_Handler,            // 129 FPU DZC Handler
    [146] = FPU_IDC_Handler,            // 130 FPU IDC Handler
    [147] = FPU_IOC_Handler,            // 131 FPU IOC Handler
    [148] = FPU_OFC_Handler,            // 132 FPU OFC Handler
    [149] = FPU_UFC_Handler,            // 133 FPU UFC Handler
    [150] = FPU_IXC_Handler,            // 134 FPU IXC Handler
    [173] = CAP6_2_Handler,             // 157 CAP6_2 Handler
    [174] = CAP7_2_Handler,             // 158 CAP7_2 Handler
    [176] = SDF1_Handler,               // 160 SDF1 Handler
    [180] = SDF1DR1_Handler,            // 164 SDF1 DR Interrupt 1 Handler
    [181] = SDF1DR2_Handler,            // 165 SDF1 DR Interrupt 2 Handler
    [182] = SDF1DR3_Handler,            // 166 SDF1 DR Interrupt 3 Handler
    [183] = SDF1DR4_Handler,            // 167 SDF1 DR Interrupt 4 Handler
    [200] = LINA_0_Handler,             // 184 LINA Interrupt0 Handler
    [201] = LINA_1_Handler,             // 185 LINA Interrupt1 Handler
    [204] = PMBUSA_Handler,             // 188 PMBUSA Handler
    [216] = ADCC_EVT_Handler,           // 200 ADCC Event Handler
    [217] = ADCC2_Handler,              // 201 ADCC Interrupt 2 Handler
    [218] = ADCC3_Handler,              // 202 ADCC Interrupt 3 Handler
    [219] = ADCC4_Handler,              // 203 ADCC Interrupt 4 Handler
    [234] = FLASH_CORR_ERR_Handler,     // 218 Flash Correctable Error Handler
    [236] = SYS_PLL_SLIP_Handler,       // 220 System PLL Slip Handler
    [241] = CTI_0_Handler,              // 225 CTI Interrupt 0 Handler
    [242] = CTI_1_Handler               // 226 CTI Interrupt 1 Handler
};

#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif

//*****************************************************************************
//
// For the ICC compiler, copy data from Flash to ITCM RAM.
//
//*****************************************************************************
#if defined (__ICCARM__)
#pragma section = "itcm.ramfunc"
#pragma section = "itcm.ramfunc_init"
#pragma section = "itcm.instruction"
#pragma section = "itcm.instruction_init"
void ItcmData_Init(void)
{
    const uint8_t *romDataPtr;
    const uint8_t *romDataEndPtr;
    uint8_t *ramDataPtr;

    //
    // copy section itcm.ramfunc_init from Flash to RAM
    //
    romDataPtr    = __section_begin("itcm.ramfunc_init");
    romDataEndPtr = __section_end("itcm.ramfunc_init");
    ramDataPtr    = __section_begin("itcm.ramfunc");
    while (romDataEndPtr != romDataPtr)
    {
        *ramDataPtr++ = *romDataPtr++;
    }

    //
    // copy section itcm.instruction_init from Flash to RAM
    //
    romDataPtr    = __section_begin("itcm.instruction_init");
    romDataEndPtr = __section_end("itcm.instruction_init");
    ramDataPtr    = __section_begin("itcm.instruction");
    while (romDataEndPtr != romDataPtr)
    {
        *ramDataPtr++ = *romDataPtr++;
    }
}
#endif /* defined (__ICCARM__) */

#if defined (__clang__) && !defined (__ARMCC_VERSION)
extern int main(void);
void _start(void)
{
    extern void _start(void) __NO_RETURN;

    typedef struct __copy_table
    {
        uint32_t const* src;
        uint32_t* dest;
        uint32_t  wlen;
    } __copy_table_t;

    typedef struct __zero_table
    {
        uint32_t* dest;
        uint32_t  wlen;
    } __zero_table_t;

    extern const __copy_table_t __copy_table_start__;
    extern const __copy_table_t __copy_table_end__;
    extern const __zero_table_t __zero_table_start__;
    extern const __zero_table_t __zero_table_end__;

    for (__copy_table_t const* pTable = &__copy_table_start__; pTable < &__copy_table_end__; ++pTable)
    {
        for(uint32_t i = 0u; i < pTable->wlen; ++i)
        {
            pTable->dest[i] = pTable->src[i];
        }
    }

    for (__zero_table_t const* pTable = &__zero_table_start__; pTable < &__zero_table_end__; ++pTable)
    {
        for(uint32_t i = 0u; i < pTable->wlen; ++i)
        {
            pTable->dest[i] = 0u;
        }
    }

    main();
}
#endif /* defined (__clang__) && !defined (__ARMCC_VERSION) */

//*****************************************************************************
//
// Reset Handler called on controller reset
//
//*****************************************************************************
__NO_RETURN void Reset_Handler(void)
{
    //
    // Initialize main stack limit register
    //
    __set_PSP((uint32_t)(&__INITIAL_SP));

    __set_MSPLIM((uint32_t)(&__STACK_LIMIT));
    __set_PSPLIM((uint32_t)(&__STACK_LIMIT));

    //
    // CMSIS System Initialization
    //
    SystemInit();

#if defined(__ICCARM__)
    ItcmData_Init();
#endif

    //
    // Enter PreMain(__main) (C library entry point)
    //
    __PROGRAM_START();
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif

//*****************************************************************************
//
// Nonmaskable interrupt Handler
//
//*****************************************************************************
void NMI_Handler(void)
{
    while(1);
}

//*****************************************************************************
//
// Hard Fault Handler
//
//*****************************************************************************
void HardFault_Handler(void)
{
    while(1);
}

//*****************************************************************************
//
// Memory management fault Handler
//
//*****************************************************************************
void MemManage_Handler(void)
{
    while(1);
}

//*****************************************************************************
//
// Bus fault Handler
//
//*****************************************************************************
void BusFault_Handler(void)
{
    while(1);
}

//*****************************************************************************
//
// Usage fault Handler
//
//*****************************************************************************
void UsageFault_Handler(void)
{
    while(1);
}

//*****************************************************************************
//
// Secure fault Handler
//
//*****************************************************************************
void SecureFault_Handler(void)
{
    while(1);
}

//*****************************************************************************
//
// Supervisor Call Handler
//
//*****************************************************************************
void SVC_Handler(void)
{
    while(1);
}

//*****************************************************************************
//
// Debug monitor Handler
//
//*****************************************************************************
void DebugMon_Handler(void)
{
    while(1);
}

//*****************************************************************************
//
// Pendable Service Call Handler
//
//*****************************************************************************
void PendSV_Handler(void)
{
    while(1);
}

//*****************************************************************************
//
// System Tick Timer Handler
//
//*****************************************************************************
void SysTick_Handler(void)
{
    while(1);
}

//*****************************************************************************
//
// Default Handler for Exceptions / Interrupts
//
//*****************************************************************************
void Default_Handler(void)
{
    while(1);
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic pop
#endif

//
// End of file
//
