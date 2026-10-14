//###########################################################################
//
// FILE:    g32r502_UART.h
//
// TITLE:   Definitions for the UART registers.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//###########################################################################
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
// 1. Update register naming and access rules.
//
//###########################################################################

#ifndef G32R502_UART_H
#define G32R502_UART_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// UART Individual Register Bit Definitions:

struct UARTCCR_BITS {                   // bits description
    Uint16 UARTCHAR:3;                  // 2:0 Character length control
    Uint16 ADDRIDLE_MODE:1;             // 3 ADDR/IDLE Mode control
    Uint16 LOOPBKENA:1;                 // 4 Loop Back enable
    Uint16 PARITYENA:1;                 // 5 Parity enable
    Uint16 PARITY:1;                    // 6 Even or Odd Parity
    Uint16 STOPBITS:1;                  // 7 Number of Stop Bits
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union UARTCCR_REG {
    Uint16  all;
    struct  UARTCCR_BITS  bit;
};

struct UARTCTL1_BITS {                  // bits description
    Uint16 RXENA:1;                     // 0 UART receiver enable
    Uint16 TXENA:1;                     // 1 UART transmitter enable
    Uint16 SLEEP:1;                     // 2 UART sleep
    Uint16 TXWAKE:1;                    // 3 Transmitter wakeup method
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 SWRESET:1;                   // 5 Software reset
    Uint16 RXERRINTENA:1;               // 6 Receive error interrupt enable
    Uint16 rsvd2:7;                     // 13:7 Reserved
    Uint16 RXDMAENA:1;                  // 14 UART receive DMA enable
    Uint16 TXDMAENA:1;                  // 15 UART transmit DMA enable
};

union UARTCTL1_REG {
    Uint16  all;
    struct  UARTCTL1_BITS  bit;
};

struct UARTHBAUD_BITS {                 // bits description
    Uint16 BAUD:8;                      // 7:0 UART 16-bit baud selection Registers UARTHBAUD
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union UARTHBAUD_REG {
    Uint16  all;
    struct  UARTHBAUD_BITS  bit;
};

struct UARTLBAUD_BITS {                 // bits description
    Uint16 BAUD:8;                      // 7:0 UART 16-bit baud selection Registers UARTLBAUD
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union UARTLBAUD_REG {
    Uint16  all;
    struct  UARTLBAUD_BITS  bit;
};

struct UARTCTL2_BITS {                  // bits description
    Uint16 TXINTENA:1;                  // 0 Transmit __interrupt enable
    Uint16 RXBKINTENA:1;                // 1 Receiver-buffer break enable
    Uint16 rsvd1:4;                     // 5:2 Reserved
    Uint16 TXEMPTY:1;                   // 6 Transmitter empty flag
    Uint16 TXRDY:1;                     // 7 Transmitter ready flag
    Uint16 rsvd2:8;                     // 15:8 Reserved
};

union UARTCTL2_REG {
    Uint16  all;
    struct  UARTCTL2_BITS  bit;
};

struct UARTRXST_BITS {                  // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 RXWAKE:1;                    // 1 Receiver wakeup detect flag
    Uint16 PE:1;                        // 2 Parity error flag
    Uint16 OE:1;                        // 3 Overrun error flag
    Uint16 FE:1;                        // 4 Framing error flag
    Uint16 BRKDT:1;                     // 5 Break-detect flag
    Uint16 RXRDY:1;                     // 6 Receiver ready flag
    Uint16 RXERROR:1;                   // 7 Receiver error flag
    Uint16 rsvd2:8;                     // 15:8 Reserved
};

union UARTRXST_REG {
    Uint16  all;
    struct  UARTRXST_BITS  bit;
};

struct UARTRXEMU_BITS {                 // bits description
    Uint16 ERXDT:8;                     // 7:0 Receive emulation buffer data
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union UARTRXEMU_REG {
    Uint16  all;
    struct  UARTRXEMU_BITS  bit;
};

struct UARTRXBUF_BITS {                 // bits description
    Uint16 SAR:8;                       // 7:0 Receive Character bits
    Uint16 rsvd1:6;                     // 13:8 Reserved
    Uint16 UARTFFPE:1;                  // 14 Receiver error flag
    Uint16 UARTFFFE:1;                  // 15 Receiver error flag
};

union UARTRXBUF_REG {
    Uint16  all;
    struct  UARTRXBUF_BITS  bit;
};

struct UARTTXBUF_BITS {                 // bits description
    Uint16 TXDT:8;                      // 7:0 Transmit data buffer
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union UARTTXBUF_REG {
    Uint16  all;
    struct  UARTTXBUF_BITS  bit;
};

struct UARTFFTX_BITS {                  // bits description
    Uint16 TXFFIL:5;                    // 4:0 Interrupt level
    Uint16 TXFFIENA:1;                  // 5 Interrupt enable
    Uint16 TXFFINTCLR:1;                // 6 Clear INT flag
    Uint16 TXFFINT:1;                   // 7 INT flag
    Uint16 TXFFST:5;                    // 12:8 FIFO status
    Uint16 TXFIFORESET:1;               // 13 FIFO reset
    Uint16 UARTFFENA:1;                 // 14 Enhancement enable
    Uint16 UARTRST:1;                   // 15 UART reset rx/tx channels
};

union UARTFFTX_REG {
    Uint16  all;
    struct  UARTFFTX_BITS  bit;
};

struct UARTFFRX_BITS {                  // bits description
    Uint16 RXFFIL:5;                    // 4:0 Interrupt level
    Uint16 RXFFIENA:1;                  // 5 Interrupt enable
    Uint16 RXFFINTCLR:1;                // 6 Clear INT flag
    Uint16 RXFFINT:1;                   // 7 INT flag
    Uint16 RXFFST:5;                    // 12:8 FIFO status
    Uint16 RXFIFORESET:1;               // 13 FIFO reset
    Uint16 RXFFOVRCLR:1;                // 14 Clear overflow
    Uint16 RXFFOVF:1;                   // 15 FIFO overflow
};

union UARTFFRX_REG {
    Uint16  all;
    struct  UARTFFRX_BITS  bit;
};

struct UARTFFCT_BITS {                  // bits description
    Uint16 FFTXDLY:8;                   // 7:0 FIFO transmit delay
    Uint16 rsvd1:5;                     // 12:8 Reserved
    Uint16 CDC:1;                       // 13 Auto baud mode enable
    Uint16 ABDCLR:1;                    // 14 Auto baud clear
    Uint16 ABD:1;                       // 15 Auto baud detect
};

union UARTFFCT_REG {
    Uint16  all;
    struct  UARTFFCT_BITS  bit;
};

struct UARTPRI_BITS {                   // bits description
    Uint16 rsvd1:3;                     // 2:0 Reserved
    Uint16 FREESOFT:2;                  // 4:3 Emulation modes
    Uint16 rsvd2:3;                     // 7:5 Reserved
    Uint16 rsvd3:8;                     // 15:8 Reserved
};

union UARTPRI_REG {
    Uint16  all;
    struct  UARTPRI_BITS  bit;
};

struct UART_REGS {
    union   UARTCCR_REG                      UARTCCR;                      // Communications control register
    union   UARTCTL1_REG                     UARTCTL1;                     // Control register 1
    union   UARTHBAUD_REG                    UARTHBAUD;                    // Baud rate (high) register
    union   UARTLBAUD_REG                    UARTLBAUD;                    // Baud rate (low) register
    union   UARTCTL2_REG                     UARTCTL2;                     // Control register 2
    union   UARTRXST_REG                     UARTRXST;                     // Receive status register
    union   UARTRXEMU_REG                    UARTRXEMU;                    // Receive emulation buffer register
    union   UARTRXBUF_REG                    UARTRXBUF;                    // Receive data buffer
    Uint16                                   rsvd1;                        // Reserved
    union   UARTTXBUF_REG                    UARTTXBUF;                    // Transmit data buffer
    union   UARTFFTX_REG                     UARTFFTX;                     // FIFO transmit register
    union   UARTFFRX_REG                     UARTFFRX;                     // FIFO receive register
    union   UARTFFCT_REG                     UARTFFCT;                     // FIFO control register
    Uint16                                   rsvd2[2];                     // Reserved
    union   UARTPRI_REG                      UARTPRI;                      // UART priority control
};

//---------------------------------------------------------------------------
// UART External References & Function Declarations:
//
extern volatile struct UART_REGS UartaRegs;
extern volatile struct UART_REGS UartbRegs;
extern volatile struct UART_REGS UartcRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
