//#############################################################################
//
// FILE:    board.c
//
// TITLE:   Board source file
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
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
// - 2026-06-30:
// 1. Modified function names and macro definition names.
//
//###########################################################################

#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules.
// Call this function in your application if you wish to do all module
// initialization.
// If you wish to not use some of the initializations, instead of the
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
    WRPRT_DISABLE;

    PinMux_init();
    SYSCTL_init();
    UART_init();

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
    //
    // UARTA -> myUART0 Pinmux (G32R502 Eval: GPIO28 RX, GPIO29 TX).
    // Baud measurement uses GPIO3 via CAP/INPUTXBAR in baud_tune_via_uart.c.
    //
    GPIO_setPinConfig(myUART0_UARTRX_PIN_CONFIG);
    GPIO_setAnalogMode(myUART0_UARTRX_GPIO, GPIO_ANALOG_DISABLED);
    GPIO_setDrivingCapability(myUART0_UARTRX_GPIO,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(myUART0_UARTRX_GPIO, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(myUART0_UARTRX_GPIO, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(myUART0_UARTTX_PIN_CONFIG);
    GPIO_setDrivingCapability(myUART0_UARTTX_GPIO,GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setPadConfig(myUART0_UARTTX_GPIO, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(myUART0_UARTTX_GPIO, GPIO_QUAL_ASYNC);

}

//*****************************************************************************
//
// UART Configurations
//
//*****************************************************************************
void UART_init()
{
    //myUART0 initialization
    UART_clearInterruptStatus(myUART0_BASE, UART_INT_TXFF | UART_INT_RXFF | UART_INT_RXERR | UART_INT_RXRDY_BRKDT | UART_INT_TXRDY | UART_INT_FE | UART_INT_OE | UART_INT_PE);
    UART_clearOverflowStatus(myUART0_BASE);

    UART_resetTxFIFO(myUART0_BASE);
    UART_resetRxFIFO(myUART0_BASE);
    UART_resetChannels(myUART0_BASE);

    UART_setConfig(myUART0_BASE, DEVICE_LSPCLK_FREQ, myUART0_BAUDRATE, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UART_disableLoopback(myUART0_BASE);
    UART_performSoftwareReset(myUART0_BASE);
    UART_setFIFOInterruptLevel(myUART0_BASE, UART_FIFO_TX0, UART_FIFO_RX0);
    UART_enableFIFO(myUART0_BASE);
    UART_enableModule(myUART0_BASE);
}

//*****************************************************************************
//
// SYSCTL Configurations
//
//*****************************************************************************
void SYSCTL_init()
{
    //
    // sysctl initialization
    //

    SysCtl_disableMCD();

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_HRPWM);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PWM7);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAP2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CAP3);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_QEP1);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANFD);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_COMP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_COMP2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_COMP3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_COMP4);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DACA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DACB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FLB1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FLB2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FLB3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FLB4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_LINA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PMBUSA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DCCOMP0);
}
