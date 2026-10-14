//#############################################################################
//
// FILE:    baud_tune_via_uart.c
//
// TITLE:   Tune Baud Rate Via UART.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//! \addtogroup driver_example_list
//! <h1>Tune Baud Rate via UART Example</h1>
//!
//! This example demonstrates the process of tuning the UART baud rate of a 
//! G32R502 device based on the UART input from another device. As UART does 
//! not have a clock signal, reliable communication requires baud rates to be 
//! reasonably matched. This example addresses cases where a clock mismatch 
//! between devices is greater than is acceptable for communications, requiring 
//! baud compensation between boards.
//!
//! To tune the baud rate of this device, UART data (of the desired baud rate) 
//! must be sent to this device. The input UART baud rate must be within the 
//! +/- MARGINPERCENT of the TARGETBAUD chosen below. These two variables are 
//! defined below and should be chosen based on the application requirements. 
//! Higher MARGINPERCENT will allow more data to be considered "correct" in 
//! noisy conditions, and may decrease accuracy. The TARGETBAUD is what was 
//! expected to be the baud rate, but due to clock differences, needs to be 
//! tuned for better communication robustness with the other device.
//!
//! For Eval and custom boards, CAP-based baud measurement uses the GPIO
//! selected by GPIO_USARTRX_NUMBER (routed to CAP1 via INPUTXBAR). UARTA
//! pinmux for post-tune TX/RX is configured in board.c (Eval default:
//! GPIO28 = UARTA RX, GPIO29 = UARTA TX). Change GPIO_USARTRX_NUMBER and/or
//! board.c PinMux_init() if your hardware uses different pins. Refer to the
//! Eval user guide for available GPIO and header routing.
//!
//! \b External \b Connections \n
//!  - Connect the external UART source TX to GPIO3 (CAP1 / INPUTXBAR7 input
//!    for baud measurement; see GPIO_USARTRX_NUMBER)
//!  - After tuning, observe UARTA TX on GPIO29 (Eval default; see board.c)
//!
//! \b Watch \b Variables \n
//!  - \b avgBaud - Baud rate that was detected and set after tuning
//!
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
// 1. Modified some function and macro definition and variable names.
// 2. Updated interrupt handling to use NVIC functions.
//
//###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Defines
//
// GPIO number for CAP/INPUTXBAR baud measurement (Eval: GPIO3 -> CAP1)
#define GPIO_USARTRX_NUMBER   3

//
// choose baud rate being received from target baud rate device
// closest baud rate to 9600 that can be set in register is 9601
//
#define TARGETBAUD          9601

//
// number of samples in the array (higher = better averaging, lower = faster)
//
#define NUMSAMPLES          32

//
// margin for what is considered a "good" pulse width:
// set this higher to allow more samples to be considered "good" data,
// if losing too much data set this lower to prevent "bad" samples to
// be discarded more strictly
//
#define MARGINPERCENT       0.05f

//
// at least this percentage of the samples array must be "good"
// to not flag an error
//
#define MINSAMPLEPERCENT    0.50f

//
// Globals
//
volatile uint32_t capCountArr[4];
volatile int capCountIter = 0;
volatile float sampleArr[NUMSAMPLES];
volatile uint16_t sampleArrIter = 0;
volatile uint16_t stopCaptures = 0;

//
// Function Prototypes
//
void initCAP(void);
void INT_CAP1_IRQHandler(void);
uint16_t arrTo1PulseWidth(volatile float arr[], int size, float targetWidth);
float computeAvgWidth(volatile float arr[], int size);
uint32_t getAverageBaud(volatile float arr[], int size, float targetBaudRate);


//
// Main
//
void example_main(void)
{
    stopCaptures = 0;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Globally disable interrupts and clear all NVIC enable/pending bits
    //
    Interrupt_initModule();

    //
    // Initialize RAM vector table and set VTOR; unregistered IRQs use
    // Interrupt_defaultHandler until Interrupt_register() is called
    //
    Interrupt_initVectorTable();

    //
    // Board Initialization
    //
    Board_init();

    //
    // Route GPIO_USARTRX_NUMBER to CAP1 (INPUTXBAR7) for RX edge capture
    //
    XBAR_setInputPin(XBAR_INPUT7, GPIO_USARTRX_NUMBER);

    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_CAP1, &INT_CAP1_IRQHandler);

    Interrupt_setPriorityGroup(INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0);

    Interrupt_setPriority(INT_CAP1,0,0);

    //
    // Initialize basic settings for CAP monitoring of USART RX
    //
    initCAP();

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_CAP1);

    //
    // Enable Global Interrupt (INTM) and Real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop forever. Suspend or place breakpoints to observe the buffers.
    //
    for (;;)
    {
        //
        // Array is filled, begin tuning
        //
        if (stopCaptures==1)
        {
            //
            // Get an average baud rate from the array of samples
            //
            uint32_t avgBaud = getAverageBaud(sampleArr,NUMSAMPLES,TARGETBAUD);

            //
            // if the baud function returns the error code '0', then flag an
            // error
            //
            if (avgBaud==0)
            {
                ESTOP0;
            }

            //
            // Update the device's baud rate to match the measured baud rate
            //
            UART_setBaud(myUART0_BASE, DEVICE_LSPCLK_FREQ, avgBaud);

            //
            // Wait for user to view the results in "Expressions" window
            //
            ESTOP0;

            //
            // (OPTIONAL) Continuously send data to USARTTX once tuning
            // is complete for external observation (by logic analyzer or
            // scope)
            //
            uint8_t *msg;
            while(1)
            {
                msg = (uint8_t*)("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\0");
                UART_writeCharArray(UARTA_BASE, msg, 51);
            }
        }
    }
}

//
// initCAP - Initialize CAP for this example.
//
void initCAP()
{
    //
    // Disable ,clear all capture flags and interrupts
    //
    CAP_disableInterrupt(CAP1_BASE,
                          (CAP_ISR_SOURCE_CAPTURE_EVENT_1  |
                           CAP_ISR_SOURCE_CAPTURE_EVENT_2  |
                           CAP_ISR_SOURCE_CAPTURE_EVENT_3  |
                           CAP_ISR_SOURCE_CAPTURE_EVENT_4  |
                           CAP_ISR_SOURCE_COUNTER_OVERFLOW |
                           CAP_ISR_SOURCE_COUNTER_PERIOD   |
                           CAP_ISR_SOURCE_COUNTER_COMPARE));
    CAP_clearInterrupt(CAP1_BASE,
                        (CAP_ISR_SOURCE_CAPTURE_EVENT_1  |
                         CAP_ISR_SOURCE_CAPTURE_EVENT_2  |
                         CAP_ISR_SOURCE_CAPTURE_EVENT_3  |
                         CAP_ISR_SOURCE_CAPTURE_EVENT_4  |
                         CAP_ISR_SOURCE_COUNTER_OVERFLOW |
                         CAP_ISR_SOURCE_COUNTER_PERIOD   |
                         CAP_ISR_SOURCE_COUNTER_COMPARE));

    //
    // Disable CAP1-CAP4 register loads
    //
    CAP_disableTimeStampCapture(CAP1_BASE);

    //
    // Configure CAP
    //    Enable capture mode.
    //    One shot mode, stop capture at event 4.
    //    Set polarity of the events to rising, falling, rising, falling edge.
    //    Set capture in time difference mode.
    //    Select input from XBAR7.
    //    Enable CAP module.
    //    Enable interrupt.
    //
    CAP_stopCounter(CAP1_BASE);
    CAP_enableCaptureMode(CAP1_BASE);

    CAP_setCaptureMode(CAP1_BASE, CAP_ONE_SHOT_CAPTURE_MODE, CAP_EVENT_4);

    CAP_setEventPolarity(CAP1_BASE, CAP_EVENT_1, CAP_EVNT_FALLING_EDGE);
    CAP_setEventPolarity(CAP1_BASE, CAP_EVENT_2, CAP_EVNT_RISING_EDGE);
    CAP_setEventPolarity(CAP1_BASE, CAP_EVENT_3, CAP_EVNT_FALLING_EDGE);
    CAP_setEventPolarity(CAP1_BASE, CAP_EVENT_4, CAP_EVNT_RISING_EDGE);

    CAP_enableCounterResetOnEvent(CAP1_BASE, CAP_EVENT_1);
    CAP_enableCounterResetOnEvent(CAP1_BASE, CAP_EVENT_2);
    CAP_enableCounterResetOnEvent(CAP1_BASE, CAP_EVENT_3);
    CAP_enableCounterResetOnEvent(CAP1_BASE, CAP_EVENT_4);

    CAP_selectCAPInput(CAP1_BASE, CAP_INPUT_INPUTXBAR7);

    CAP_enableLoadCounter(CAP1_BASE);
    CAP_setSyncOutMode(CAP1_BASE, CAP_SYNC_OUT_DISABLED);
    CAP_startCounter(CAP1_BASE);
    CAP_enableTimeStampCapture(CAP1_BASE);
    CAP_reArm(CAP1_BASE);

    CAP_enableInterrupt(CAP1_BASE, CAP_ISR_SOURCE_CAPTURE_EVENT_4);
}


//
// INT_CAP1_IRQHandler - NVIC interrupt handler for CAP1.
//
void INT_CAP1_IRQHandler(void)
{
    if (stopCaptures == 0)
    {
        //
        // Get the capture counts, interrupt every 4. Can be 1-bit or more
        // wide. Add one to account for partial CAP counts at higher baud
        // rates (for example: count = 40, but if had higher resolution, this
        // would be 40.5)
        capCountArr[0] = 1+CAP_getEventTimeStamp(CAP1_BASE, CAP_EVENT_1);
        capCountArr[1] = 1+CAP_getEventTimeStamp(CAP1_BASE, CAP_EVENT_2);
        capCountArr[2] = 1+CAP_getEventTimeStamp(CAP1_BASE, CAP_EVENT_3);
        capCountArr[3] = 1+CAP_getEventTimeStamp(CAP1_BASE, CAP_EVENT_4);

        //
        // Add samples to a buffer. Get average baud and tune if buffer filled.
        //
        capCountIter = 0;
        for (capCountIter = 0; capCountIter < 4; capCountIter++)
        {
            //
            // if we still have samples left to capture, add it to the
            // samples array
            //
            if (sampleArrIter < NUMSAMPLES)
            {
                sampleArr[sampleArrIter] = capCountArr[capCountIter];
                sampleArrIter++;
            }

            //
            // else, all samples were received, break to begin tuning
            //
            else
            {
                stopCaptures=1;
                break;
            }
        }
    }

    //
    // Clear interrupt flags for more interrupts.
    //
    CAP_clearInterrupt(CAP1_BASE,CAP_ISR_SOURCE_CAPTURE_EVENT_4);
    CAP_clearGlobalInterrupt(CAP1_BASE);

    //
    // Start CAP
    //
    CAP_reArm(CAP1_BASE);
}

//
// FUNCTION:    getAverageBaud
// PURPOSE:     get the average baud rate of the array
// INPUTS:      array of pulse widths (in number CAP counts),
//              size of array, and target baud rate
// RETURNS:     average baud rate
//
uint32_t getAverageBaud(volatile float arr[], int size, float targetBaudRate)
{
    //
    // clean up variable width array to single-bit-width array
    //
    float calcTargetWidth = (float)DEVICE_AHBCLK_FREQ / targetBaudRate;
    uint16_t pass = arrTo1PulseWidth(arr, size, calcTargetWidth);

    //
    // pass only if enough good samples provided
    //
    if (pass == 0)
    {
        return(0);
    }

    //
    // convert 2-bit width, 3-bit width, and so on to 1-bit width values by
    // dividing, and average these values. skip unrelated values
    //
    float averageBitWidth = computeAvgWidth(arr, size);

    //
    // CAP TSCTR runs at AHB/SYSCLK; convert average counts to UART baud (LSPCLK
    // is programmed separately via UART_setBaud).
    //
    return((uint32_t)(((float)DEVICE_AHBCLK_FREQ / (float)averageBitWidth) + 0.5f));
}

//
// FUNCTION:    arrTo1PulseWidth
// PURPOSE:     convert 2-bit and higher widths to 1-bit equivalent,
//              set "bad" values to zero
// INPUTS:      array of pulse widths in number CAP counts, size of array,
//              and target pulse-width (in number of CAP counts)
// RETURNS:     pass if enough "good" data received,
//              fail if not enough "good" data
//
uint16_t arrTo1PulseWidth(volatile float arr[], int size, float targetWidth)
{
    int iterator = 0, numBitWidths=0;
    uint16_t goodDataCount = 0, pass = 0;
    for (iterator = 0; iterator < size; iterator++)
    {

        //
        // if the item is less than 10 times the bit width,
        //
        if (arr[iterator] < targetWidth*10)
        {

            //
            // if the item is not within +/-MARGINPERCENT% of the targetWidth,
            // then it is a multiple of 1-bit
            //
            bool belowBound = arr[iterator] < targetWidth*(1.0f - MARGINPERCENT);
            bool aboveBound = arr[iterator] > targetWidth*(1.0f + MARGINPERCENT);
            if (belowBound || aboveBound)
            {

                //
                // estimate how many bit-widths this is
                //
                numBitWidths = (int)((arr[iterator]/targetWidth) + 0.5f);

                //
                // multiply the multi-bit baudrate value by the estimated
                // number of bits to make this a 1-bit baud estimate
                //
                arr[iterator] = arr[iterator] / numBitWidths;

                //
                // find if this new value is within the bounds
                //
                belowBound = arr[iterator] < targetWidth*(1.0f - MARGINPERCENT);
                aboveBound = arr[iterator] > targetWidth*(1.0f + MARGINPERCENT);
                if(belowBound || aboveBound)
                {
                    arr[iterator] = 0; // discard if not within margins
                }
                else
                {
                    goodDataCount++; // iterate good data counter
                }
            }
            else
            {

                //
                // this is a 1-bit value so increment the counter for it
                //
                goodDataCount++;
            }
        }
        else
        {
            arr[iterator] = 0;
        }
    }

    //
    // if at least MINSAMPLEPERCENT% of the sampled values
    // are "good" samples, then return a pass
    //
    if ((float)goodDataCount/(float)size > MINSAMPLEPERCENT)
    {
        pass=1;
    }
    return(pass); //return if the array had enough good samples or not
}

//
// FUNCTION:    computeAvgWidth
// PURPOSE:     average all non-zero items in the array
// INPUTS:      array of 1-bit pulse widths in number CAP counts,
//              and size of array
// RETURNS:     average width
//
float computeAvgWidth(volatile float arr[], int size)
{
    int iterator = 0, totSamples = 0;
    float total = 0;
    for(iterator = 0;iterator < size; iterator++)
    {
        //
        // if the item has not been removed
        //
        if(arr[iterator] != 0)
        {
            //
            // iterate the number of samples that are included in the total
            //
            totSamples++;
            //
            //add it to the moving average
            //
            total += arr[iterator];
        }
    }
    return(total/totSamples); //return the average
}
