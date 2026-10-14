#ifndef _FASTINTDIV_H_
#define _FASTINTDIV_H_

#include <stdint.h>
#include <stdlib.h>

//Return type is structure
//typedef struct
typedef struct {
	int32_t quot;		//quotient
    int32_t rem;        //remainder
} __ldiv_t;

typedef struct {
	uint32_t quot;      //quotient
    uint32_t rem;       //remainder
} __uldiv_t;

typedef struct {
	int64_t quot;      //quotient
    int64_t rem;       //remainder
} __lldiv_t;

typedef struct {
	uint64_t quot;      //quotient
    uint64_t rem;       //remainder
} __ulldiv_t;


/*;----------------------------------------------------------------------------------
;   @brief:	Euclidean Division i16/i16
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern  __ldiv_t __euclidean_div_i16byi16(int16_t dividend, int16_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Modulo Division i16/i16
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern  __ldiv_t __modulo_div_i16byi16(int16_t dividend, int16_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Traditional Division i16/i16
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern  __ldiv_t __traditional_div_i16byi16(int16_t dividend, int16_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Traditional Division u16/u16
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern __uldiv_t __traditional_div_u16byu16(uint16_t dividend, uint16_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Euclidean Division i32/i32
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern  __ldiv_t __euclidean_div_i32byi32(int32_t dividend, int32_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Modulo Division i32/i32
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern  __ldiv_t __modulo_div_i32byi32(int32_t dividend, int32_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Traditional Division i32/i32
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern  __ldiv_t __traditional_div_i32byi32(int32_t dividend, int32_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Euclidean Division i32/u32
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern  __ldiv_t __euclidean_div_i32byu32(int32_t dividend, uint32_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Modulo Division i32/u32
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern  __ldiv_t __modulo_div_i32byu32(int32_t dividend, uint32_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Traditional Division i32/u32
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern  __ldiv_t __traditional_div_i32byu32(int32_t dividend, uint32_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Traditional Division u32/u32
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern __uldiv_t __traditional_div_u32byu32(uint32_t dividend, uint32_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Euclidean Division i32/i16
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern  __ldiv_t __euclidean_div_i32byi16(int32_t dividend, int16_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Modulo Division i32/i16
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern  __ldiv_t __modulo_div_i32byi16(int32_t dividend, int16_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Traditional Division i32/i16
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern  __ldiv_t __traditional_div_i32byi16(int32_t dividend, int16_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Traditional Division u32/u16
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern __uldiv_t __traditional_div_u32byu16(uint32_t dividend, uint16_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Euclidean Division i64/i64
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern __lldiv_t __euclidean_div_i64byi64(int64_t dividend, int64_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Modulo Division i64/i64
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern __lldiv_t __modulo_div_i64byi64(int64_t dividend, int64_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Traditional Division i64/i64
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern __lldiv_t __traditional_div_i64byi64(int64_t dividend, int64_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Euclidean Division i64/u64
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern __lldiv_t __euclidean_div_i64byu64(int64_t dividend, uint64_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Modulo Division i64/u64
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern __lldiv_t __modulo_div_i64byu64(int64_t dividend, uint64_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Traditional Division i64/u64
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern __lldiv_t __traditional_div_i64byu64(int64_t dividend, uint64_t divisor);

/*;----------------------------------------------------------------------------------
;   @brief:	Traditional Division u64/u64
;   @param[in]	dividend (numerator)
;   @param[in]	divisor (denominator)
;   @return   	quotient & remainder
;----------------------------------------------------------------------------------*/
extern __ulldiv_t __traditional_div_u64byu64(uint64_t dividend, uint64_t divisor);


#endif
