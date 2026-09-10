//###########################################################################
//
// FILE:    g32r501_adc.c
//
// TITLE:   g32r501 ADC Support Functions.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//###########################################################################
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
// 1. Updated header file title for G32R501 ADC support functions.
// 2. Changed file name to g32r501_adc.c to reflect the new architecture.
// 3. Adjusted data types and memory addresses to match G32R501 specifics.
//
//###########################################################################

//
// Included Files
//
#include "g32r501_device.h"      // Header File Include File
#include "g32r501_examples.h"    // Examples Include File

//
// SetVREF - Set Vref mode. Function to select reference mode and offset trim.
// Offset trim for Internal VREF 3.3 is unique.  All other modes use the same
// offset trim. Also note that when the mode parameter is ADC_EXTERNAL, the
// ref parameter has no effect.
//
void SetVREF(int module, int mode, int ref)
{
    uint32_t *offset, offval;

    //
    // Define offset locations from OTP
    //
    offset = (uint32_t *)(0x0810BA1C + (module * 4));

    if((mode == ADC_INTERNAL) && (ref == ADC_VREF3P3))
    {
        offval = (*offset) >> 8;    // Internal / 1.65v mode offset
    }
    else
    {
        offval = (*offset) & 0xFF;  // All other modes
    }

    //
    // Write offset trim values and configure reference modes
    //
    WRPRT_DISABLE;
    switch(module)
    {
        case 0:
            AdcaRegs.ADCOFFTRIM.bit.OFFTRIM = offval;
            ASRegs.ANAREFCTL.bit.ANAREFASEL = mode;
            ASRegs.ANAREFCTL.bit.ANAREFA2P5SEL = ref;
            break;
        case 1:
            AdcbRegs.ADCOFFTRIM.bit.OFFTRIM = offval;
            ASRegs.ANAREFCTL.bit.ANAREFBSEL = mode;
            ASRegs.ANAREFCTL.bit.ANAREFB2P5SEL = ref;
            break;
        case 2:
            AdccRegs.ADCOFFTRIM.bit.OFFTRIM = offval;
            ASRegs.ANAREFCTL.bit.ANAREFCSEL = mode;
            ASRegs.ANAREFCTL.bit.ANAREFC2P5SEL = ref;
            break;
        default:
            break;
    }
    WRPRT_ENABLE;
}

//
// End of File
//
