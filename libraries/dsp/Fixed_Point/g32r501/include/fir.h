//###########################################################################
//
// FILE:    fir.h
//
// TITLE:   Fixed Point FIR header file.
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

#ifndef FIR_H
#define FIR_H


#ifdef __cplusplus
extern "C"
{
#endif

/* Includes *******************************************************************/
 
#include <stdint.h>

/* Exported macro *************************************************************/

#define      FIR16_alt_init               FIR16_init
#define      FIR16_alt_calc             FIR16_calc


/** 
  * @brief   Initialization defaults for the 16-bit FIR filter   
  */
#define FIR16_DEFAULTS {              \
    (int32_t *)NULL,                  \
    (int32_t *)NULL,                  \
    0,                                \
    6,                                \
    0,                                \
    0,                                \
    (void (*)(void *))FIR16_init,     \
    (void (*)(void *))FIR16_calc}    

/** 
  * @brief   Initialization defaults for the 16-bit Alternate FIR filter   
  */
#define FIR16_ALT_DEFAULTS {          \
    (int32_t *)NULL,                  \
    (int32_t *)NULL,                  \
    0,                                \
    6,                                \
    0,                                \
    0,                                \
    (void (*)(void *))FIR16_alt_init, \
    (void (*)(void *))FIR16_alt_calc}

/** 
  * @brief   Initialization defaults for the 32-bit FIR filter   
  */
#define FIR32_DEFAULTS {              \
    (int32_t *)NULL,                  \
    (int32_t *)NULL,                  \
    0,                                \
    6,                                \
    0,                                \
    0,                                \
    (void (*)(void *))FIR32_init,     \
    (void (*)(void *))FIR32_calc} 

/** 
  * @brief   Initialization defaults for the 32-bit Alternate FIR filter   
  */             
#define FIR32_ALT_DEFAULTS {          \
    (int32_t *)NULL,                  \
    (int32_t *)NULL,                  \
    0,                                \
    6,                                \
    0,                                \
    0,                                \
    (void (*)(void *))FIR32_alt_init, \
    (void (*)(void *))FIR32_alt_calc}


/* Exported types *************************************************************/

/** 
  * @brief   16-bit FIR filter structure   
  */
typedef struct { 
    int32_t *coeff_ptr;     //!< Pointer to Filter coefficients
    int32_t * dbuffer_ptr;  //!< Delay buffer pointer              
    int16_t cbindex;        //!< Circular Buffer Index         
    int16_t order;          //!< Order of the Filter           
    int16_t input;          //!< Latest Input sample            
    int16_t output;         //!< Filter Output                 
    void (*init)(void *);   //!< Pointer to initialization function           
    void (*calc)(void *);   //!< Pointer to calculation function              
}FIR16; 

/** 
  * @brief    Handle to the FIR16 object   
  */
typedef FIR16 *FIR16_Handle;

/** 
  * @brief    32-bit FIR filter structure   
  */
typedef struct { 
    int32_t *coeff_ptr;     //!< Pointer to Filter coefficient 
    int32_t * dbuffer_ptr;  //!< Delay buffer pointer              
    int16_t cbindex;        //!< Circular Buffer Index         
    int16_t order;          //!< Order of the Filter           
    int32_t input;          //!< Latest Input sample            
    int32_t output;         //!< Filter Output                 
    void (*init)(void *);   //!< Pointer to initialization function         
    void (*calc)(void *);   //!< Pointer to calculation function                  
}FIR32; 

/** 
  * @brief    Handle to the FIR32 object   
  */
typedef FIR32 *FIR32_Handle;
                                                      
/* Exported functions *********************************************************/

void FIR16_init(void *handle);
void FIR16_calc(void *handle);

void FIR32_init(void *handle);

#if __ARM_BIG_ENDIAN
#error "MVE intrinsics are not supported in Big-Endian mode."
#elif !__ARM_FEATURE_MVE
#error "MVE feature not supported"
#else
void FIR32_calc(void *handle);
#endif /* __ARM_FEATURE_MVE  */

void FIR32_alt_init(void *handle);
void FIR32_alt_calc(void *handle);

#ifdef __cplusplus
}
#endif

#endif /*FIR_H */  

/********************************* END OF FILE *********************************/
