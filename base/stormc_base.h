#pragma once


#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <immintrin.h>


#ifndef PAGESIZE
#define PAGESIZE 4096
#endif

#define asm __asm__
#define volatile __volatile__
#define inline __inline__
#define restrict __restrict__

#define thisfile static
#define global_persist static
#define local_persist static
#define ALIGNOF(type) __alignof__(type)
#define OFFSETOF(type, member) __builtin_offsetof(type, member)
#define TYPEOF(v) __typeof__(v)
#define unreachable __builtin_unreachable()
#define KILOBYTE(x) ((x) * 1024ull)
#define MEGABYTE(x) ((x) * 1024ull * 1024ull)
#define CACHELINE_SIZE 64

#define STC_CAST(cast_type, value) ((cast_type)value)
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

#define MIN(a, b) SELECT(a < b, a, b)
#define MAX(a, b) SELECT(a > b, a, b)

#define _SC_STR2(x) #x
#define _SC_STR(x) _SC_STR2(x)

#define STORMC_ERR_IF(cond, msg)\
  __attribute__((diagnose_if(cond, "STORMC: " msg " IN: " __FILE__ ":" _SC_STR(__LINE__), "error")))

#define STORMC_WARN_IF(cond, msg)\
  __attribute__((diagnose_if(cond, "STORMC: " msg " IN: " __FILE__ " " _SC_STR(__LINE__), "warning")))

#define ERR_IF(cond, msg)\
  __attribute__((diagnose_if(cond, msg " IN: " __FILE__ " " _SC_STR(__LINE__), "error")))

#define WARN_IF(cond, msg)\
  __attribute__((diagnose_if(cond, msg " IN: " __FILE__ " " _SC_STR(__LINE__), "warning")))

#define UNUSED __attribute__((unused))



#define STORM_BUILDINFO_MAGIC 0x53544F524D42494EULL
#define DATA_SECTION(name) __attribute__((section(name), used))


#include <stdbool.h>
#include <immintrin.h>
#include <inttypes.h>


typedef __m256d       simd_4_f64;
typedef __m256        simd_8_f32;
typedef __m128        simd_4_f32;
typedef __m256i       simd_8_i32;
typedef __m256i       simd_32_u8;
typedef __m128i       simd_16_u8;



typedef  uint8_t		u8;
typedef  uint16_t  		u16;
typedef  uint32_t  		u32;
typedef  uint64_t  		u64;

typedef  int8_t    		i8;
typedef  int16_t   		i16;
typedef  int32_t   		i32;
typedef  int64_t   		i64;
typedef  double			f64;
typedef  float			f32;



#ifndef bool16
	typedef u16 bool16;
#endif
#ifndef bool32
	typedef u32 bool32;
#endif
#ifndef bool64
	typedef u64 bool64;
#endif

typedef u8	uflags_8;
typedef u16	uflags_16;
typedef u32 	uflags_32;
typedef u64 	uflags_64;

typedef i8	iflags_8;
typedef i16	iflags_16;
typedef i32 	iflags_32;
typedef i64 	iflags_64;


// #define STR(name) (struct stormc_string){.str = name, .len = sizeof(name) - 1}
//
// struct stormc_string {
//     char		*str;
//     u64			len;
// };


struct stormc_buildinfo_date{
	u64	hour;
	u64	minutes;
	u64	seconds;
};

struct stormc_buildinfo {
	u64	magic;
	u64	version;
	u64	unix_time;

	char	sources[4096];
	u64	sources_len;

	char	compiler_name[64];
	u64	compiler_name_len;

	u64	flags_len;
	char	compiler_flags[4096];
};

