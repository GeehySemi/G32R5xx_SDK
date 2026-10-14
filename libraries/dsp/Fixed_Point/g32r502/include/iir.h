//###########################################################################
//
// FILE:    fir.h
//
// TITLE:   Fixed Point FIR header file.
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
 
#ifndef IIR_H
#define IIR_H


#ifdef __cplusplus
extern "C"
{
#endif

/* Includes *******************************************************************/

#include <stdint.h>

/* Exported macro *************************************************************/

/** 
  * @brief   LPF co-efficients for IIR16 module  
  */
#define IIR16_LPF_COEFF {       \
    0,3794,0,307,307,           \
    -2159,7894,668,1335,668,    \
    -3483,8904,541,1082,541,    \
    -6131,10923,13364,26729,13364}

#define IIR16_LPF_ISF     4398
#define IIR16_LPF_NBIQ    4
#define IIR16_LPF_QFMAT   13

/** 
  * @brief   LPF co-efficients for IIR32 module  
  */
#define IIR32_LPF_COEFF {                               \
    0,248624377,0,20118017,20118017,                    \
    -141524868,517372703,43749199,87498398,43749199,    \
    -228291242,583544331,35450657,70901314,35450657,    \
    -401770939,715847129,875854244,1751708488,875854244}

#define IIR32_LPF_ISF   288246535
#define IIR32_LPF_NBIQ  4
#define IIR32_LPF_QFMAT 29

/** 
  * @brief   Initialization defaults for the 16-bit IIR filter   
  */
#define IIR5BIQ16_DEFAULTS {            \
    (void (*)(void *))IIR5BIQ16_init,   \
    (void (*)(void *))IIR5BIQ16_calc,   \
    (int16_t *)NULL,                    \
    (int16_t *)NULL,                    \
    0,                                  \
    0,                                  \
    0,                                  \
    0,                                  \
    0}    

/** 
  * @brief   Initialization defaults for the 32-bit IIR filter   
  */
#define IIR5BIQ32_DEFAULTS {            \
    (void (*)(void *))IIR5BIQ32_init,   \
    (void (*)(void *))IIR5BIQ32_calc,   \
    (int32_t *)NULL,                    \
    (int32_t *)NULL,                    \
    0,                                  \
    0,                                  \
    0,                                  \
    0,                                  \
    0,                                  \
    0}      

/* Exported types *************************************************************/

/** 
  * @brief   16-bit IIR filter structure   
  */
typedef struct 
{ 
    void (*init)(void *);       //!< Pointer to initialization function           
    void (*calc)(void *);      //!< Pointer to calculation function                  
    int16_t *coeff_ptr;               //!< Pointer to filter coefficients
    int16_t *dbuffer_ptr;           //!< Delay buffer Pointer             
    uint16_t nbiq;                        //!< Number of biquads
    int16_t input;                        //!< Latest input sample          
    int16_t isf;                             //!< Input scale factor            
    uint16_t qfmat;                     //!< Q format of coefficients            
    int16_t output;                     //!< Filter output                
} IIR5BIQ16;    

/** 
  * @brief   Handle to the IIR16 object   
  */
typedef IIR5BIQ16 *IIR5BIQ16_Handle;

/** 
  * @brief   32-bit IIR filter structure   
  */
typedef struct 
{
    void (*init)(void *);    //!< Pointer to initialization function 
    void (*calc)(void *);   //!< Pointer to calculation function    
    int32_t *coeff_ptr;            //!< Pointer to filter coefficients
    int32_t *dbuffer_ptr;       //!< Delay buffer Pointer             
    uint16_t nbiq;                   //!< Number of biquads
    int32_t input;                   //!< Latest input sample
    int32_t isf;                        //!< Input scale factor            
    int32_t output32;            //!< Filter output (Q30) 
    int16_t output16;            //!< Filter Output (Q15)
    uint16_t qfmat;               //!< Q format of coefficients  
} IIR5BIQ32;            

/** 
  * @brief   Handle to the IIR32 object   
  */
typedef IIR5BIQ32 *IIR5BIQ32_Handle;

                                                       
/* Exported functions *********************************************************/

void IIR5BIQ16_init(IIR5BIQ16 *IIR5BIQ16_Handle);
void IIR5BIQ16_calc(IIR5BIQ16 *IIR5BIQ16_Handle);

void IIR5BIQ32_init(IIR5BIQ32 *IIR5BIQ32_Handle);
void IIR5BIQ32_calc(IIR5BIQ32 *IIR5BIQ32_Handle);


#ifdef __cplusplus
}
#endif

#endif /*IIR_H */  

/********************************* END OF FILE *********************************/
