#include <assert.h>
#include <immintrin.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <stdio.h>



typedef __m256d       simd_4_f64;
typedef __m256        simd_8_f32;
typedef __m128        simd_4_f32;
typedef __m256i       simd_8_i32;
typedef __m256i       simd_32_u8;
typedef __m128i       simd_16_u8;



typedef  unsigned long int	uintptr_t;
typedef  uint8_t   u8;
typedef  uint16_t  u16;
typedef  uint32_t  u32;
typedef  uint64_t  u64;

typedef  int8_t    i8;
typedef  int16_t   i16;
typedef  int32_t   i32;
typedef  int64_t   i64;

typedef double f64;
typedef float f32;

// typedef struct Storm_AST Storm_AST;
typedef struct Storm_Uint_32_Members_With_Exprs_Array Storm_Uint_32_Members_With_Exprs_Array;
typedef struct Storm_Uint_32_Members_Array Storm_Uint_32_Members_Array;

typedef struct Storm_String8 Storm_String8;
typedef struct Storm_String16 Storm_String16;
typedef struct Storm_String32 Storm_String32;
typedef struct Storm_String64 Storm_String64;
typedef struct Storm_String128 Storm_String128;
typedef struct Storm_String256 Storm_String256;
typedef struct Storm_String512 Storm_String512;
typedef struct Storm_String1024 Storm_String1024;
typedef struct Storm_String2048 Storm_String2048;
typedef struct String String;
typedef struct Storm_Int_8_Array Storm_Int_8_Array;
typedef struct Storm_Int_16_Array Storm_Int_16_Array;
typedef struct Storm_Int_32_Array Storm_Int_32_Array;
typedef struct Storm_Int_64_Array Storm_Int_64_Array;

typedef struct Storm_Uint_8_Array Storm_Uint_8_Array;
typedef struct Storm_Uint_16_Array Storm_Uint_16_Array;
typedef struct Storm_Uint_32_Array Storm_Uint_32_Array;
typedef struct Storm_Uint_64_Array Storm_Uint_64_Array;

typedef struct Storm_Float_32_Array Storm_Float_32_Array;
typedef struct Storm_Float_64_Array Storm_Float_64_Array;

struct Storm_String8{
    char    str[8];
    u64     len;
};

struct Storm_String16{
    char    str[16];
    u64     len;
};

struct Storm_String32{
    char    str[32];
    u64     len;
};


struct Storm_String64{
    char    str[64];
    u64     len;
};

struct Storm_String128{
    char    str[128];
    u64     len;
};

struct Storm_String256{
    char    str[256];
    u64     len;
};

struct Storm_String512{
    char    str[512];
    u64     len;
};

struct Storm_String1024{
    char    str[1024];
    u64     len;
};

struct Storm_String2048{
    char    str[2048];
    u64     len;
};

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



struct Storm_Uint_8_Array{
    u64 len;
    u8  arr[];
};
struct Storm_Uint_16_Array{
    u64  len;
    u16  arr[];
};

struct Storm_Uint_32_Array{
    u64 len;
    u32  arr[];
};
struct Storm_Uint_64_Array{
    u64 len;
    u64  arr[];
};

struct Storm_Int_8_Array{
    u64 len;
    u8  arr[];
};
struct Storm_Int_16_Array{
    u64 len;
    u16  arr[];
};

struct Storm_Int_32_Array{
    u64 len;
    u32  arr[];
};
struct Storm_Int_64_Array{
    u64 len;
    u64  arr[];
};



struct Storm_Float_32_Array{
    u64 len;
    f32  arr[];
};
struct Storm_Float_64_Array{
    u64 len;
    f64  arr[];
};
