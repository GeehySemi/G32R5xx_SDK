//###########################################################################
//
// FILE:    startup_g32r502.c
//
// TITLE:   CMSIS-Core(M) Device Startup File for G32R502.
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

#include "g32r502.h"

#if defined(G32R502_DTCM_BOOT_STATUS_ENABLE)
void G32R502_BootStatusEarlyHook(const volatile uint8_t *bootStatus,
                                 uint32_t size) __attribute__ ((weak));
void G32R502_BootStatusEarlyHook(const volatile uint8_t *bootStatus,
                                 uint32_t size)
{
    (void)bootStatus;
    (void)size;
}
#endif

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
void DCCOMP_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TMR1_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void TMR2_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void RAM_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCA1_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCC1_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void TMR0_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void WWDT_WAKE_Handler   (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM1_TRIP_ZONE_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM2_TRIP_ZONE_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM3_TRIP_ZONE_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM4_TRIP_ZONE_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM5_TRIP_ZONE_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM6_TRIP_ZONE_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM7_TRIP_ZONE_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM1_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM2_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM3_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM4_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM5_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM6_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM7_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void CAP1_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void CAP2_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void CAP3_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void QEP1_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void FLB1_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void FLB2_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void FLB3_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void FLB4_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void SPIA_RX_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void SPIA_TX_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_CH1_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_CH2_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_CH3_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_CH4_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_CH5_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA_CH6_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void I2CA_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void I2CA_FIFO_Handler   (void) __attribute__ ((weak, alias("Default_Handler")));
void I2CB_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void I2CB_FIFO_Handler   (void) __attribute__ ((weak, alias("Default_Handler")));
void UARTA_RX_Handler    (void) __attribute__ ((weak, alias("Default_Handler")));
void UARTA_TX_Handler    (void) __attribute__ ((weak, alias("Default_Handler")));
void UARTB_RX_Handler    (void) __attribute__ ((weak, alias("Default_Handler")));
void UARTB_TX_Handler    (void) __attribute__ ((weak, alias("Default_Handler")));
void CANA_INT0_Handler   (void) __attribute__ ((weak, alias("Default_Handler")));
void CANA_INT1_Handler   (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCA_EVENT_Handler  (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCA2_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCA3_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCA4_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE0_Handler  (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE1_Handler  (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE2_Handler  (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE3_Handler  (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE4_Handler  (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE5_Handler  (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE6_Handler  (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE7_Handler  (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE8_Handler  (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE9_Handler  (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE10_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE11_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI_LINE12_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_DZC_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_IDC_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_IOC_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_OFC_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_UFC_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_IXC_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void CANFDA_INT0_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void CANFDA_INT1_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void CANFDA_BEC_INT_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void CANFDA_BEU_INT_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void CANFDA_WAKE_UP_INT_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void LINA_INT1_Handler   (void) __attribute__ ((weak, alias("Default_Handler")));
void LINA_INT2_Handler   (void) __attribute__ ((weak, alias("Default_Handler")));
void UARTC_RX_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void UARTC_TX_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void PMBUSA_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCC_EVENT_Handler  (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCC2_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCC3_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCC4_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_ECC_ERR_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void SYS_PLL_SLIP_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void CTI_INT0_Handler    (void) __attribute__ ((weak, alias("Default_Handler")));
void CTI_INT1_Handler    (void) __attribute__ ((weak, alias("Default_Handler")));

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
    [27]  = DCCOMP_Handler,             //  11 DCCOMP Interrupt
    [29]  = TMR1_Handler,               //  13 CPU Timer 1 Interrupt
    [30]  = TMR2_Handler,               //  14 CPU Timer 2 Interrupt
    [32]  = RAM_Handler,                //  16 System Memory Interrupt
    [48]  = ADCA1_Handler,              //  32 ADCA1 Interrupt
    [50]  = ADCC1_Handler,              //  34 ADCC1 Interrupt
    [54]  = TMR0_Handler,               //  38 Timer 0 Interrupt
    [55]  = WWDT_WAKE_Handler,          //  39 WWDT interrupt & LPM wakeup Interrupt
    [56]  = PWM1_TRIP_ZONE_Handler,     //  40 PWM1 TRIP ZONE Interrupt
    [57]  = PWM2_TRIP_ZONE_Handler,     //  41 PWM2 TRIP ZONE Interrupt
    [58]  = PWM3_TRIP_ZONE_Handler,     //  42 PWM3 TRIP ZONE Interrupt
    [59]  = PWM4_TRIP_ZONE_Handler,     //  43 PWM4 TRIP ZONE Interrupt
    [60]  = PWM5_TRIP_ZONE_Handler,     //  44 PWM5 TRIP ZONE Interrupt
    [61]  = PWM6_TRIP_ZONE_Handler,     //  45 PWM6 TRIP ZONE Interrupt
    [62]  = PWM7_TRIP_ZONE_Handler,     //  46 PWM7 TRIP ZONE Interrupt
    [64]  = PWM1_Handler,               //  48 PWM1 Interrupt
    [65]  = PWM2_Handler,               //  49 PWM2 Interrupt
    [66]  = PWM3_Handler,               //  50 PWM3 Interrupt
    [67]  = PWM4_Handler,               //  51 PWM4 Interrupt
    [68]  = PWM5_Handler,               //  52 PWM5 Interrupt
    [69]  = PWM6_Handler,               //  53 PWM6 Interrupt
    [70]  = PWM7_Handler,               //  54 PWM7 Interrupt
    [72]  = CAP1_Handler,               //  56 CAP1 Interrupt
    [73]  = CAP2_Handler,               //  57 CAP2 Interrupt
    [74]  = CAP3_Handler,               //  58 CAP3 Interrupt
    [80]  = QEP1_Handler,               //  64 QEP1 Interrupt
    [84]  = FLB1_Handler,               //  68 FLB1 Interrupt
    [85]  = FLB2_Handler,               //  69 FLB2 Interrupt
    [86]  = FLB3_Handler,               //  70 FLB3 Interrupt
    [87]  = FLB4_Handler,               //  71 FLB4 Interrupt
    [88]  = SPIA_RX_Handler,            //  72 SPIA Receive Interrupt
    [89]  = SPIA_TX_Handler,            //  73 SPIA Transmit Interrupt
    [96]  = DMA_CH1_Handler,            //  80 DMA Channel 1 Interrupt
    [97]  = DMA_CH2_Handler,            //  81 DMA Channel 2 Interrupt
    [98]  = DMA_CH3_Handler,            //  82 DMA Channel 3 Interrupt
    [99]  = DMA_CH4_Handler,            //  83 DMA Channel 4 Interrupt
    [100] = DMA_CH5_Handler,            //  84 DMA Channel 5 Interrupt
    [101] = DMA_CH6_Handler,            //  85 DMA Channel 6 Interrupt
    [104] = I2CA_Handler,               //  88 I2CA Interrupt
    [105] = I2CA_FIFO_Handler,          //  89 I2CA FIFO Interrupt
    [107] = I2CB_Handler,               //  91 I2CB Interrupt
    [108] = I2CB_FIFO_Handler,          //  92 I2CB FIFO Interrupt
    [112] = UARTA_RX_Handler,           //  96 UARTA Receive Interrupt
    [113] = UARTA_TX_Handler,           //  97 UARTA Transmit Interrupt
    [114] = UARTB_RX_Handler,           //  98 UARTB Receive Interrupt
    [115] = UARTB_TX_Handler,           //  99 UARTB Transmit Interrupt
    [116] = CANA_INT0_Handler,          // 100 CANA INT0
    [117] = CANA_INT1_Handler,          // 101 CANA INT1
    [120] = ADCA_EVENT_Handler,         // 104 ADCA EVENT Interrupt
    [121] = ADCA2_Handler,              // 105 ADCA Interrupt 2
    [122] = ADCA3_Handler,              // 106 ADCA Interrupt 3
    [123] = ADCA4_Handler,              // 107 ADCA Interrupt 4
    [128] = EXTI_LINE0_Handler,         // 112 EXTI LINE0 Interrupt
    [129] = EXTI_LINE1_Handler,         // 113 EXTI LINE1 Interrupt
    [130] = EXTI_LINE2_Handler,         // 114 EXTI LINE2 Interrupt
    [131] = EXTI_LINE3_Handler,         // 115 EXTI LINE3 Interrupt
    [132] = EXTI_LINE4_Handler,         // 116 EXTI LINE4 Interrupt
    [133] = EXTI_LINE5_Handler,         // 117 EXTI LINE5 Interrupt
    [134] = EXTI_LINE6_Handler,         // 118 EXTI LINE6 Interrupt
    [135] = EXTI_LINE7_Handler,         // 119 EXTI LINE7 Interrupt
    [136] = EXTI_LINE8_Handler,         // 120 EXTI LINE8 Interrupt
    [137] = EXTI_LINE9_Handler,         // 121 EXTI LINE9 Interrupt
    [138] = EXTI_LINE10_Handler,        // 122 EXTI LINE10 Interrupt
    [139] = EXTI_LINE11_Handler,        // 123 EXTI LINE11 Interrupt
    [140] = EXTI_LINE12_Handler,        // 124 EXTI LINE12 Interrupt
    [145] = FPU_DZC_Handler,            // 129 FPU DZC Interrupt
    [146] = FPU_IDC_Handler,            // 130 FPU IDC Interrupt
    [147] = FPU_IOC_Handler,            // 131 FPU IOC Interrupt
    [148] = FPU_OFC_Handler,            // 132 FPU OFC Interrupt
    [149] = FPU_UFC_Handler,            // 133 FPU UFC Interrupt
    [150] = FPU_IXC_Handler,            // 134 FPU IXC Interrupt
    [185] = CANFDA_INT0_Handler,        // 169 CANFDA INT0
    [186] = CANFDA_INT1_Handler,        // 170 CANFDA INT1
    [187] = CANFDA_BEC_INT_Handler,     // 171 CANFDA BEC INT
    [188] = CANFDA_BEU_INT_Handler,     // 172 CANFDA BEU INT
    [189] = CANFDA_WAKE_UP_INT_Handler, // 173 CANFDA WAKE UP INT
    [200] = LINA_INT1_Handler,          // 184 LINA INT1
    [201] = LINA_INT2_Handler,          // 185 LINA INT2
    [202] = UARTC_RX_Handler,           // 186 UART RX Interrupt
    [203] = UARTC_TX_Handler,           // 187 UART TX Interrupt
    [204] = PMBUSA_Handler,             // 188 PMBUSA Interrupt
    [216] = ADCC_EVENT_Handler,         // 200 ADCC EVENT Interrupt
    [217] = ADCC2_Handler,              // 201 ADCC2 Interrupt
    [218] = ADCC3_Handler,              // 202 ADCC3 Interrupt
    [219] = ADCC4_Handler,              // 203 ADCC4 Interrupt

    [234] = FLASH_ECC_ERR_Handler,      // 218 FLASH ECC ERR Interrupt
    [236] = SYS_PLL_SLIP_Handler,       // 220 System PLL Slip Interrupt
    [241] = CTI_INT0_Handler,           // 225 CTI INT0
    [242] = CTI_INT1_Handler            // 226 CTI INT1
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
#if defined(G32R502_DTCM_BOOT_STATUS_ENABLE)
    G32R502_BootStatusEarlyHook((const volatile uint8_t *)DTCM_BOOT_STATUS_BASE,
                                DTCM_BOOT_STATUS_SIZE);
#endif

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
