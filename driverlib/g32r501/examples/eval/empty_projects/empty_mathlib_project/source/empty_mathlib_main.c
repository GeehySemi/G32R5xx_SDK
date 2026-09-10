//#############################################################################
//
// FILE:    empty_mathlib_main.c
//
// TITLE:   Empty Project
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
// Empty Project Example
//
// This example is an empty project setup for Driverlib development.
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

//
// Included Files
//
#include "g32r501_examples.h"
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "FPUfastRTS.h"

void test_powf(void)
{
    uint16_t i = 0;
    volatile float tmp;

     float const Test_PowInputA[63] = 
    {
        1.50 ,1.50 ,1.50 ,1.50 ,1.50 ,1.50 ,1.50 ,1.50 ,1.50 ,1.50 ,1.50 ,1.50 ,1.50 ,1.50 ,1.50 ,1.50 ,
        1.50 ,1.50 ,1.50 ,1.50 ,1.50 ,3.20 ,3.20 ,3.20 ,3.20 ,3.20 ,3.20 ,3.20 ,3.20 ,3.20 ,3.20 ,3.20 ,
        3.20 ,3.20 ,3.20 ,3.20 ,3.20 ,3.20 ,3.20 ,3.20 ,3.20 ,3.20 ,5.45 ,5.45 ,5.45 ,5.45 ,5.45 ,5.45 ,
        5.45 ,5.45 ,5.45 ,5.45 ,5.45 ,5.45 ,5.45 ,5.45 ,5.45 ,5.45 ,5.45 ,5.45 ,5.45 ,5.45 ,5.45 
    };

      float const Test_PowInputB[63] = 
    {
        0.0000100 ,0.0002000 ,0.0030000 ,0.0400000 ,0.5000000 ,0.7500000 ,1.0000000 ,2.0000000 ,
        3.0000000 ,4.0000000 ,5.0000000 ,6.0000000 ,7.0000000 ,8.0000000 ,9.0000000 ,10.0000000 ,
        10.2500000 ,10.5000000 ,10.7500000 ,11.0000000 ,13.1500000 ,0.0000100 ,0.0002000 ,0.0030000 ,
        0.0400000 ,0.5000000 ,0.7500000 ,1.0000000 ,2.0000000 ,3.0000000 ,4.0000000 ,5.0000000 ,
        6.0000000 ,7.0000000 ,8.0000000 ,9.0000000 ,10.0000000 ,10.2500000 ,10.5000000 ,10.7500000 ,
        11.0000000 ,13.1500000 ,0.0000100 ,0.0002000 ,0.0030000 ,0.0400000 ,0.5000000 ,0.7500000 ,
        1.0000000 ,2.0000000 ,3.0000000 ,4.0000000 ,5.0000000 ,6.0000000 ,7.0000000 ,8.0000000 ,
        9.0000000 ,10.0000000 ,10.2500000 ,10.5000000 ,10.7500000 ,11.0000000 ,13.1500000 
    };
      for(i = 0;i < sizeof(Test_PowInputA)/sizeof(float);i++)
    {
       //Eliminate Warnings
       (void)tmp;
       tmp = powf(Test_PowInputA[i],Test_PowInputB[i]);
       //tmp = powf(Test_PowInputA[i],Test_PowInputB[i]);
       //printf("%1.10f                        %u\r\n",tmp,delta);
    }
}

//
// Main
//
void example_main(void)
{
    //
    // Initializes system control, device clock, and peripherals
    //
    Device_init();

    //
    // Initializes NVIC and clears NVIC registers. Disables CPU interrupts.
    // and clear all CPU interrupt flags.
    //
    Interrupt_initModule();

    //
    // Initializes the NVIC vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Board Initialization
    //
    Board_init();

    GPIO_writePin(myGPIOOutput_LED3,1);
    GPIO_writePin(myGPIOOutput_LED2,1);
    
    //
    // Enables CPU interrupts
    //
    Interrupt_enableMaster();

    //
    // Loop.
    //
    for(;;)
    {
        GPIO_togglePin(myGPIOOutput_LED2);
        DEVICE_DELAY_US(1000000);
    }
}


//
// End of File
//

