#pragma once
#include "stormc_base.h"



typedef __m256d       simd_4_f64;
typedef __m256        simd_8_f32;
typedef __m128        simd_4_f32;
typedef __m256i       simd_8_i32;
typedef __m256i       simd_32_u8;
typedef __m128i       simd_16_u8;



typedef  unsigned long int	uintptr_t;
typedef  uint8_t		u8;
typedef  uint16_t  		u16;
typedef  uint32_t  		u32;
typedef  uint64_t  		u64;

typedef  int8_t    		i8;
typedef  int16_t   		i16;
typedef  int32_t   		i32;
typedef  int64_t   		i64;
typedef double			f64;
typedef float			f32;

typedef struct String String;


struct String{
    union
    {
        struct {
            char    *str;
            u64     len;
        };
        i8  err;
    };
};
