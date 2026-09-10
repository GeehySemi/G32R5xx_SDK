//###########################################################################
//
// FILE:    fft.h
//
// TITLE:   Fixed Point fft header file.
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
#ifndef FFT_H
#define FFT_H


#ifdef __cplusplus
extern "C"
{
#endif

/* Includes *******************************************************************/
 
#include <stdint.h>

/* Exported macro *************************************************************/

#define  Q31          31
#define  Q30         30

//#define  NULL    0

#define  TF_QFMAT         Q30

#define TABLE_SIZE      (4096U)
#define TABLE_SIZE_LOG2 (12U)

/** 
  * @brief   Initialization defaults for the 8-point complex FFT   
  */ 
#define CFFT32_8P_DEFAULTS    {     \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    8,                              \
    3,                              \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    0,                              \
    0,                              \
    128,                            \
    (void (*)(void *))FFT32_init,   \
    (void (*)(void *))FFT32_izero,  \
    (void (*)(void *))FFT32_calc,   \
    (void (*)(void *))CFFT32_mag,   \
    (void (*)(void *))CFFT32_win} 

/** 
  * @brief   Initialization defaults for the 16-point complex FFT   
  */
#define CFFT32_16P_DEFAULTS    {    \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    16,                             \
    4,                              \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    0,                              \
    0,                              \
    256,                            \
    (void (*)(void *))FFT32_init,   \
    (void (*)(void *))FFT32_izero,  \
    (void (*)(void *))FFT32_calc,   \
    (void (*)(void *))CFFT32_mag,   \
    (void (*)(void *))CFFT32_win} 

/** 
  * @brief   Initialization defaults for the 32-point complex FFT   
  */
#define CFFT32_32P_DEFAULTS    {    \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    32,                             \
    5,                              \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    0,                              \
    0,                              \
    128,                            \
    (void (*)(void *))FFT32_init,   \
    (void (*)(void *))FFT32_izero,  \
    (void (*)(void *))FFT32_calc,   \
    (void (*)(void *))CFFT32_mag,   \
    (void (*)(void *))CFFT32_win} 

/** 
  * @brief   Initialization defaults for the 64-point complex FFT   
  */
#define CFFT32_64P_DEFAULTS    {    \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    64,                             \
    6,                              \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    0,                              \
    0,                              \
    64,                             \
    (void (*)(void *))FFT32_init,   \
    (void (*)(void *))FFT32_izero,  \
    (void (*)(void *))FFT32_calc,   \
    (void (*)(void *))CFFT32_mag,   \
    (void (*)(void *))CFFT32_win} 

/** 
  * @brief   Initialization defaults for the 128-point complex FFT   
  */ 
#define CFFT32_128P_DEFAULTS    {   \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    128,                            \
    7,                              \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    0,                              \
    0,                              \
    32,                             \
    (void (*)(void *))FFT32_init,   \
    (void (*)(void *))FFT32_izero,  \
    (void (*)(void *))FFT32_calc,   \
    (void (*)(void *))CFFT32_mag,   \
    (void (*)(void *))CFFT32_win} 

/** 
  * @brief   Initialization defaults for the 256-point complex FFT   
  */
#define CFFT32_256P_DEFAULTS    {   \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    256,                            \
    8,                              \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    0,                              \
    0,                              \
    16,                             \
    (void (*)(void *))FFT32_init,   \
    (void (*)(void *))FFT32_izero,  \
    (void (*)(void *))FFT32_calc,   \
    (void (*)(void *))CFFT32_mag,   \
    (void (*)(void *))CFFT32_win} 
        
/** 
  * @brief   Initialization defaults for the 512-point complex FFT   
  */       
#define CFFT32_512P_DEFAULTS    {   \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    512,                            \
    9,                              \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    0,                              \
    0,                              \
    8,                              \
    (void (*)(void *))FFT32_init,   \
    (void (*)(void *))FFT32_izero,  \
    (void (*)(void *))FFT32_calc,   \
    (void (*)(void *))CFFT32_mag,   \
    (void (*)(void *))CFFT32_win}  

/** 
  * @brief   Initialization defaults for the 1024-point complex FFT   
  */   
#define CFFT32_1024P_DEFAULTS    {  \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    1024,                           \
    10,                             \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    0,                              \
    0,                              \
    4,                              \
    (void (*)(void *))FFT32_init,   \
    (void (*)(void *))FFT32_izero,  \
    (void (*)(void *))FFT32_calc,   \
    (void (*)(void *))CFFT32_mag,   \
    (void (*)(void *))CFFT32_win}   

/** 
  * @brief   Initialization defaults for the 2048-point complex FFT   
  */   
#define CFFT32_2048P_DEFAULTS    {  \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    2048,                           \
    11,                             \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    0,                              \
    0,                              \
    2,                              \
    (void (*)(void *))FFT32_init,   \
    (void (*)(void *))FFT32_izero,  \
    (void (*)(void *))FFT32_calc,   \
    (void (*)(void *))CFFT32_mag,   \
    (void (*)(void *))CFFT32_win}

/** 
  * @brief   Initialization defaults for the 4096-point complex FFT   
  */
#define CFFT32_4096P_DEFAULTS    {  \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    4096,                           \
    12,                             \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    0,                              \
    0,                              \
    1,                              \
    (void (*)(void *))FFT32_init,   \
    (void (*)(void *))FFT32_izero,  \
    (void (*)(void *))FFT32_calc,   \
    (void (*)(void *))CFFT32_mag,   \
    (void (*)(void *))CFFT32_win}

/** 
  * @brief   Initialization defaults for the real time bit-revered
  *             data acquisition module for the real FFT
  */
#define RFFT32_brev_RT_ACQ_DEFAULTS { \
    1,                                \
    0,                                \
    0,                                \
    (int32_t *)NULL,                  \
    (int32_t *)NULL,                  \
    0,                                \
    (void (*)(void *))RFFT32_brev_RT}

/** 
  * @brief   Initialization defaults for the 32-point real FFT
  */
#define RFFT32_32P_DEFAULTS    {    \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    16,                             \
    4,                              \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    0,                              \
    0,                              \
    256,                            \
    (void (*)(void *))FFT32_init,   \
    (void (*)(void *))FFT32_calc,   \
    (void (*)(void *))RFFT32_split, \
    (void (*)(void *))RFFT32_mag,   \
    (void (*)(void *))RFFT32_win}        

/** 
  * @brief   Initialization defaults for the 64-point real FFT
  */
#define RFFT32_64P_DEFAULTS    {    \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    32,                             \
    5,                              \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    0,                              \
    0,                              \
    128,                             \
    (void (*)(void *))FFT32_init,   \
    (void (*)(void *))FFT32_calc,   \
    (void (*)(void *))RFFT32_split, \
    (void (*)(void *))RFFT32_mag,   \
    (void (*)(void *))RFFT32_win}  

/** 
  * @brief   Initialization defaults for the 128-point real FFT
  */
#define RFFT32_128P_DEFAULTS    {   \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    64,                             \
    6,                              \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    0,                              \
    0,                              \
    64,                             \
    (void (*)(void *))FFT32_init,   \
    (void (*)(void *))FFT32_calc,   \
    (void (*)(void *))RFFT32_split, \
    (void (*)(void *))RFFT32_mag,   \
    (void (*)(void *))RFFT32_win} 

/** 
  * @brief   Initialization defaults for the 256-point real FFT
  */
#define RFFT32_256P_DEFAULTS    {   \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    128,                            \
    7,                              \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    0,                              \
    0,                              \
    32,                             \
    (void (*)(void *))FFT32_init,   \
    (void (*)(void *))FFT32_calc,   \
    (void (*)(void *))RFFT32_split, \
    (void (*)(void *))RFFT32_mag,   \
    (void (*)(void *))RFFT32_win} 

/** 
  * @brief   Initialization defaults for the 512-point real FFT
  */
#define RFFT32_512P_DEFAULTS    {   \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    256,                            \
    8,                              \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    0,                              \
    0,                              \
    16,                              \
    (void (*)(void *))FFT32_init,   \
    (void (*)(void *))FFT32_calc,   \
    (void (*)(void *))RFFT32_split, \
    (void (*)(void *))RFFT32_mag,   \
    (void (*)(void *))RFFT32_win} 

/** 
  * @brief   Initialization defaults for the 1024-point real FFT
  */
#define RFFT32_1024P_DEFAULTS    {  \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    512,                            \
    9,                              \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    0,                              \
    0,                              \
    8,                              \
    (void (*)(void *))FFT32_init,   \
    (void (*)(void *))FFT32_calc,   \
    (void (*)(void *))RFFT32_split, \
    (void (*)(void *))RFFT32_mag,   \
    (void (*)(void *))RFFT32_win}

/** 
  * @brief   Initialization defaults for the 2048-point real FFT
  */
#define RFFT32_2048P_DEFAULTS    {  \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    1024,                           \
    10,                             \
    (int32_t *)NULL,                \
    (int32_t *)NULL,                \
    0,                              \
    0,                              \
    4,                              \
    (void (*)(void *))FFT32_init,   \
    (void (*)(void *))FFT32_calc,   \
    (void (*)(void *))RFFT32_split, \
    (void (*)(void *))RFFT32_mag,   \
    (void (*)(void *))RFFT32_win} 

/** 
  * @brief   Initialization defaults for the 4096-point real FFT
  */
#define RFFT32_4096P_DEFAULTS    { \
    (int32_t *)NULL,               \
    (int32_t *)NULL,               \
    2048,                          \
    11,                            \
    (int32_t *)NULL,               \
    (int32_t *)NULL,               \
    0,                             \
    0,                             \
    2,                             \
    (void (*)(void *))FFT32_init,  \
    (void (*)(void *))FFT32_calc,  \
    (void (*)(void *))RFFT32_split,\
    (void (*)(void *))RFFT32_mag,  \
    (void (*)(void *))RFFT32_win} 

/* Exported types *************************************************************/

/** 
  * @brief   32-bit Complex FFT Structure
  */
typedef struct 
{   
    int32_t *ipcbptr;                          //!< Pointer to the input computation buffer
    int32_t *tfptr;                              //!< Pointer to the twiddle factor tables   
    int16_t size;                                  //!< Size of the FFT (a power of 2, max 4096)
    int16_t nrstage;                            //!< Number of FFT stages (=log2(size))  
    int32_t *magptr;                         //!< Pointer to the magnitude buffer
    int32_t *winptr;                          //!< Pointer to the window coefficients
    int32_t peakmag;                        //!< Peak spectral magnitude value
    int16_t peakfrq;                          //!< Frequency bin of the peak magnitude value
    int16_t ratio;                               //!< Twiddle factor table skip value
    void (*init)(void *);            //!< Pointer to the FFT initialization function
    void (*izero)(void *);         //!< Pointer to the "zero imaginary" function
    void (*calc)(void *);           //!< Pointer to the FFT calculation function
    void (*mag)(void *);          //!< Pointer to the FFT magnitude function
    void (*win)(void *);           //!< Pointer to the FFT windowing function
} CFFT32;

/** 
  * @brief   Handle to the CFFT32 object
  */
typedef struct CFFT32 *CFFT32_Handle;

/** 
  * @brief   32-bit Real FFT Structure
  */
typedef struct 
{   
    int32_t *ipcbptr;                         //!< Pointer to the input computation buffer
    int32_t *tfptr;                             //!< Pointer to the twiddle factor tables         
    int16_t size;                                 //!< Size of the FFT (a power of 2, max 4096)
    int16_t nrstage;                           //!< Number of FFT stages (=log2(size))       
    int32_t *magptr;                         //!< Pointer to the magnitude buffer
    int32_t *winptr;                          //!< Pointer to the window coefficients
    int32_t peakmag;                         //!< Peak spectral magnitude value
    int16_t peakfrq;                           //!< Frequency bin of the peak magnitude value
    int16_t ratio;                                //!< Twiddle factor table skip value
    void (*init)(void *);              //!< Pointer to the FFT initialization function
    void (*calc)(void *);             //!< Pointer to the FFT calculation function
    void (*split)(void *);            //!< Pointer to the split function
    void (*mag)(void *);            //!< Pointer to the FFT magnitude function
    void (*win)(void *);             //!< Pointer to the FFT windowing function
} RFFT32;               

/** 
  * @brief   Handle to the RFFT32 object
  */
typedef struct RFFT32 *RFFT32_Handle;

/** 
  * @brief   Structure for the real time bit-reversal acquisition module
  */ 
typedef struct 
{
    int16_t acqflag;                             //!< Acquisition Flag
    int16_t count;                                //!< Integer count of the samples acquired
    int32_t input;                                //!< Acquired sample
    int32_t *tempptr;                        //!< Temporary Pointer
    int32_t *buffptr;                         //!< Pointer to the buffer where the data is stored
    int16_t size;                                 //!< Size of the buffer (a power of 2)
    void (*update)(void *);       //!< Pointer to the update function that stores data in bit-reversed order
} RFFT32_brev_RT_ACQ; 

/** 
  * @brief   Handle to the RFFT32_brev_RT_ACQ object
  */ 
typedef struct RFFT32_brev_RT_ACQ *RFFT32_brev_RT_ACQ_Handle;

/* Exported variables *********************************************************/
extern const int32_t TF_4096P_CFFT[3072];

/* Exported functions *********************************************************/

void RFFT32_brev_RT(void *handle); 
void RFFT32_brev(int32_t *src, int32_t *dst, uint16_t size);
void RFFT32_win(void *handle); 
void RFFT32_split(void *handle); 
void RFFT32_mag(void *handle);

void CFFT32_brev(int32_t *src, int32_t *dst, uint16_t size); 
void CFFT32_win(void *handle); 
void CFFT32_win_dual(void *handle); 
void FFT32_izero(void *handle);
void CFFT32_mag(void *handle);

void FFT32_calc(void *handle); 
void FFT32_init(void *handle);

#ifdef __cplusplus
}
#endif

#endif /*FFT_H */  

/********************************* END OF FILE *********************************/
