//###########################################################################
//
// FILE:    system_g32r501.c
//
// TITLE:   CMSIS-Core(M) Device System Source File for G32R501.
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

#include "g32r501.h"

//*****************************************************************************
//
// Define Clocks
//
//*****************************************************************************
#define INTOSC1   10000000U   // Backup Internal Oscillator
#define INTOSC2   10000000U   // Primary Internal Oscillator
#define XTAL      20000000U   // External Oscillator

//*****************************************************************************
//
// Define Watchdog Disable
//
//*****************************************************************************
#if defined (__CORE_CPU0__)
#define WD_DISABLE   1   // Set to 1 to disable WD for CPU0
#else
#define WD_DISABLE   0   // Set to 0 to ignore WD for CPU1
#endif

//*****************************************************************************
//
// Exception / Interrupt Vector Table
//
//*****************************************************************************
extern const PINT __VECTOR_TABLE[NVIC_RAM_VECTOR_SIZE];

//*****************************************************************************
//
// System Core Clock Variable
//
//*****************************************************************************
uint32_t SystemCoreClock = INTOSC2;

#if WD_DISABLE == 1
//*****************************************************************************
//
// Watchdog Disable Function
//
//*****************************************************************************
void WD_Disable(void)
{
    __wrprt_disable();

    //
    // Set WDDIS bit in WDCR to disable WD
    //
    WD->WDCR = (0x5U << WD_WDCR_WDCHK_Pos) |
               (0x1U << WD_WDCR_WDDIS_Pos);

    __wrprt_enable();
}
#endif

//*****************************************************************************
//
// System Initialization Function
//
//*****************************************************************************
void SystemInit(void)
{
#if defined (__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
    //
    // Configure the Vector Table Location
    //
    SCB->VTOR = (uint32_t)__VECTOR_TABLE;
#endif

#if defined (__FPU_USED) && (__FPU_USED == 1U)
    //
    // Enable CP10 and CP11 Full Access
    //
    SCB->CPACR |= ((3U << 10U*2U) | (3U << 11U*2U));
#endif

#if defined (__ARM_FEATURE_CDE)
    //
    // Enable CP0 Full Access and CP0 Non-secure Access
    //
    SCB->CPACR |= (3U << 0U*2U);
    SCB->NSACR |= (3U << 0U*2U);
#endif

    //
    // Enable WRPRT Protection COP
    //
    SCB->CPACR |= 0xC;

#ifdef UNALIGNED_SUPPORT_DISABLE
    SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
#endif

    __DSB();
    __ISB();

#if WD_DISABLE == 1
    //
    // Disable the Watchdog Timer
    //
    WD_Disable();
#endif
}

//*****************************************************************************
//
// System Core Clock Function
//
//*****************************************************************************
void SystemCoreClockUpdate(void)
{
    uint32_t temp;
    uint32_t oscSource;
    uint32_t clockOut;

    //
    // The PLL is bypassed and OSCCLK is connected to INTOSC1 if an MCD
    // failure is detected.
    //
    if((CLKCFG->MCDCR & CLKCFG_MCDCR_MCLKSTS_Msk) != 0U)
    {
        clockOut = INTOSC1;
    }
    else
    {
        //
        // Start from the known frequency
        //
        oscSource = CLKCFG->CLKSRCCTL1 & CLKCFG_CLKSRCCTL1_OSCCLKSRCSEL_Msk;

        if(oscSource == 0U)
        {
            clockOut = INTOSC2;
        }
        else if((oscSource == 2U) || (oscSource == 3U))
        {
            clockOut = INTOSC1;
        }
        else
        {
            clockOut = XTAL;
        }

        //
        // If the PLL is enabled calculate its effect on the clock
        //
        if((CLKCFG->SYSPLLCTL1 & (CLKCFG_SYSPLLCTL1_PLLEN_Msk |
                                  CLKCFG_SYSPLLCTL1_PLLCLKEN_Msk)) == 0x3U)
        {
            //
            // Calculate portion from fractional multiplier
            //
            temp = (clockOut * ((CLKCFG->SYSPLLMULT & CLKCFG_SYSPLLMULT_FMULT_Msk) >>
                                CLKCFG_SYSPLLMULT_FMULT_Pos)) / 4U;

            //
            // Calculate integer multiplier and fixed divide by 2
            //
            clockOut *= (CLKCFG->SYSPLLMULT & CLKCFG_SYSPLLMULT_IMULT_Msk);

            //
            // Add in fractional portion
            //
            clockOut += temp;

            //
            // Divide SYSPLL divider
            //
            clockOut /= (((CLKCFG->SYSPLLMULT & CLKCFG_SYSPLLMULT_ODIV_Msk) >>
                          CLKCFG_SYSPLLMULT_ODIV_Pos) + 1U);
        }
    }

    if((CLKCFG->SYSCLKDIVSEL & CLKCFG_SYSCLKDIVSEL_PLLSYSCLKDIV_Msk) != 0U)
    {
        clockOut /= ((CLKCFG->SYSCLKDIVSEL & CLKCFG_SYSCLKDIVSEL_PLLSYSCLKDIV_Msk) * 2U);
    }

    SystemCoreClock = clockOut;
}

//
// End of file
//
