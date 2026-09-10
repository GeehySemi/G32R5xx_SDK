//#############################################################################
//
// FILE:    interrupt_ex4_pwm_realtime_interrupt.c
//
// TITLE:   PWM Real-Time Interrupt
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//! \addtogroup driver_example_list
//! <h1> PWM Real-Time Interrupt </h1>
//!
//!  This example configures the PWM1 Timer and increments a counter each time
//!  the ISR is executed. PWM interrupt can be configured as time critical
//!  to demonstrate real-time mode functionality and real-time interrupt
//!  capability.
//!
//!  The example uses 2 LEDs - LED1 is toggled in the main loop and LED2 is
//!  toggled in the PWM Timer Interrupt. FREE_SOFT bits and DBGIER.INT3 bit
//!  must be set to enable PWM1 interrupt to be time critical and operational
//!  in real time mode after halt command
//!
//!  Run this example key points:
//!  - Add the watch variables as mentioned below and enable Continuous Refresh.
//!  - Enable real-time mode (Run->Advanced->Enable Silicon Real-time Mode)
//!  - Initially, the DBGIER register is set to 0 and the PWM emulation mode
//!    is set to PWM_EMULATION_STOP_AFTER_NEXT_TB (FREE_SOFT = 0)
//!  - When the application is running, you will find both LEDs toggling and
//!    the watch variables Pwm1TimerIntCount, Pwm1Regs.TBCTR getting updated.
//!  - When the application is halted, both LEDs stop toggling and the watch
//!    variables remain constant. PWM counter is stopped on debugger halt.
//!  - To enable PWM counter run during debugger halt, set emulation mode as
//!    PWM_EMULATION_FREE_RUN (FREE_SOFT = 2). You will find Pwm1Regs.TBCTR
//!    is running, but Pwm1TimerIntCount remains constant. This means,
//!    the PWM counter is running, but the ISRs are not getting serviced.
//!  - To enable real-time interrupts, set DBGIER.INT3 = 1 (PWM1 interrupt is
//!    part of NVIC Group 3). You will find that the Pwm1TimerIntCount is
//!    incrementing and the LED starts toggling. The PWM ISR is getting
//!    serviced even during a debugger halt.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - Pwm1TimerIntCount        - PWM1 ISR counter
//! - Pwm1Regs.TBCTR.TBCTR     - PWM1 Time Base counter
//! - Pwm1Regs.TBCTL.FREE_SOFT - Set this to 2 to enable free run
//! - DBGIER.INT3              - Set to 1 to enable real time interrupt
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2024 Geehy Semiconductor - http://www.geehy.com/
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//
// Modifications:
// - 2024-07-08: 
// 1. Modified some function and macro definition and variable names.
//
//###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define PWM1_TIMER_TBPRD   0x2000


//
// Globals
//
uint32_t Pwm1TimerIntCount;
uint16_t LEDcount;

//
// Function Prototypes
//
extern void SetDBGIER(uint16_t dbgier); // Defined in <device>_dbgier.asm file
void initPWM(void);
__interrupt void INT_PWM1_IRQHandler(void);

//
// Main
//
void example_main(void)
{
    //
    // Initializes device clock and peripherals
    //
    Device_init();

    //
    // Configures the GPIO pin as a push-pull output
    //
    Device_initGPIO();
    GPIO_setDrivingCapability(DEVICE_GPIO_PIN_LED1,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(DEVICE_GPIO_PIN_LED1, GPIO_CORE_CPU0);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_LED1, GPIO_QUAL_SYNC);
    GPIO_setDrivingCapability(DEVICE_GPIO_PIN_LED2,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(DEVICE_GPIO_PIN_LED2, GPIO_CORE_CPU0);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_LED2, GPIO_QUAL_SYNC);

    //
    // Initializes NVIC and clears NVIC registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initializes the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    Interrupt_register(INT_PWM1, &INT_PWM1_IRQHandler);

    //
    // Initialize PWM1
    //
    initPWM();

    //
    // Initialize counters
    //
    Pwm1TimerIntCount = 0;
    LEDcount = 0;

    //
    // Set the priority group to indicate the PREEMPT and SUB priortiy bits.
    //
    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_7_6_SUB_5_0);
    //
    // Set the global and group priority to allow CPU interrupts
    // with higher priority
    //
    Interrupt_setPriority(INT_PWM1,1,0);
    //
    // Enable PWM1 Interrupt
    //
    Interrupt_enable(INT_PWM1);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop forever
    //
    while(1)
    {
        //
        // Toggle LED1
        //
        GPIO_togglePin(DEVICE_GPIO_PIN_LED1);

        //
        // 200ms delay
        //
        DEVICE_DELAY_US(200000);
    }
}

void initPWM()
{
    //
    // Disable sync
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Initially disable Free/Soft Bits
    //
    PWM_setEmulationMode(PWM1_BASE, PWM_EMULATION_STOP_AFTER_NEXT_TB);

    //
    // Setup TBCLK
    //
    PWM_setTimeBasePeriod(PWM1_BASE, PWM1_TIMER_TBPRD);
    PWM_setTimeBaseCounterMode(PWM1_BASE, PWM_COUNTER_MODE_UP);
    PWM_setTimeBaseCounter(PWM1_BASE, 0U);

    //
    // CompareA event at half of period
    //
    PWM_setCounterCompareValue(PWM1_BASE, PWM_COUNTER_COMPARE_A,
                                PWM1_TIMER_TBPRD/2);

    //
    // Action Qualifiers : Set on CCOMPA, Clear on PERIOD
    //
    PWM_setActionQualifierAction(PWM1_BASE,
                                  PWM_AQ_OUTPUT_A,
                                  PWM_AQ_OUTPUT_HIGH,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    PWM_setActionQualifierAction(PWM1_BASE,
                                  PWM_AQ_OUTPUT_A,
                                  PWM_AQ_OUTPUT_LOW,
                                  PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);

    //
    // Configure interrupt on event TBCTR=ZERO
    //
    PWM_setInterruptSource(PWM1_BASE, PWM_INT_TBCTR_ZERO);
    PWM_enableInterrupt(PWM1_BASE);
    PWM_setInterruptEventCount(PWM1_BASE, 1);

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

__interrupt void INT_PWM1_IRQHandler(void)
{
    Pwm1TimerIntCount++;
    LEDcount++;

    //
    // Toggle LED2 when the count reaches 500
    //
    if (LEDcount == 500)
    {
        GPIO_togglePin(DEVICE_GPIO_PIN_LED2);
        LEDcount=0;
    }

    //
    // Clear INT flag for this timer
    //
    PWM_clearEventTriggerInterruptFlag(PWM1_BASE);
}

//
// End of File
//
