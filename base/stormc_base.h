#pragma once


#include "stormc_error_table.h"

#ifdef __cplusplus
	#define stc_try(__call, __err, ...)\
		([&]() {\
			enum stc_err_code __err = (__call);\
			if (__err != (enum stc_err_code)STC_ERR_OK) {\
				__VA_ARGS__\
			}\
			return __err;\
		}())
#else
	#define stc_try(__call, __err, ...)\
		({\
			enum stc_err_code __err = (__call);\
			if (__err != STC_ERR_OK) {\
				__VA_ARGS__\
			}\
			__err;\
		})
#endif


#define STC_ANSI_RESET             "\x1b[0m"
#define STC_ANSI_BOLD              "\x1b[1m"
#define STC_ANSI_DIM               "\x1b[2m"
#define STC_ANSI_ITALIC            "\x1b[3m"
#define STC_ANSI_UNDERLINE         "\x1b[4m"
#define STC_ANSI_BLINK             "\x1b[5m"
#define STC_ANSI_REVERSE           "\x1b[7m"
#define STC_ANSI_HIDDEN            "\x1b[8m"
#define STC_ANSI_STRIKETHROUGH     "\x1b[9m"

#define STC_ANSI_BLACK             "\x1b[30m"
#define STC_ANSI_RED               "\x1b[31m"
#define STC_ANSI_GREEN             "\x1b[32m"
#define STC_ANSI_YELLOW            "\x1b[33m"
#define STC_ANSI_BLUE              "\x1b[34m"
#define STC_ANSI_MAGENTA           "\x1b[35m"
#define STC_ANSI_CYAN              "\x1b[36m"
#define STC_ANSI_WHITE             "\x1b[37m"
#define STC_ANSI_DEFAULT           "\x1b[39m"

#define STC_ANSI_BG_BLACK          "\x1b[40m"
#define STC_ANSI_BG_RED            "\x1b[41m"
#define STC_ANSI_BG_GREEN          "\x1b[42m"
#define STC_ANSI_BG_YELLOW         "\x1b[43m"
#define STC_ANSI_BG_BLUE           "\x1b[44m"
#define STC_ANSI_BG_MAGENTA        "\x1b[45m"
#define STC_ANSI_BG_CYAN           "\x1b[46m"
#define STC_ANSI_BG_WHITE          "\x1b[47m"
#define STC_ANSI_BG_DEFAULT        "\x1b[49m"

#define STC_ANSI_BRIGHT_BLACK      "\x1b[90m"
#define STC_ANSI_BRIGHT_RED        "\x1b[91m"
#define STC_ANSI_BRIGHT_GREEN      "\x1b[92m"
#define STC_ANSI_BRIGHT_YELLOW     "\x1b[93m"
#define STC_ANSI_BRIGHT_BLUE       "\x1b[94m"
#define STC_ANSI_BRIGHT_MAGENTA    "\x1b[95m"
#define STC_ANSI_BRIGHT_CYAN       "\x1b[96m"
#define STC_ANSI_BRIGHT_WHITE      "\x1b[97m"

#define STC_ANSI_BG_BRIGHT_BLACK   "\x1b[100m"
#define STC_ANSI_BG_BRIGHT_RED     "\x1b[101m"
#define STC_ANSI_BG_BRIGHT_GREEN   "\x1b[102m"
#define STC_ANSI_BG_BRIGHT_YELLOW  "\x1b[103m"
#define STC_ANSI_BG_BRIGHT_BLUE    "\x1b[104m"
#define STC_ANSI_BG_BRIGHT_MAGENTA "\x1b[105m"
#define STC_ANSI_BG_BRIGHT_CYAN    "\x1b[106m"
#define STC_ANSI_BG_BRIGHT_WHITE   "\x1b[107m"


#if defined(__GNUC__) || defined(__clang__)
#define stc_threadlocal __thread
#elif defined(_MSC_VER)
#define stc_threadlocal __declspec(thread)
#else
#define stc_threadlocal _Thread_local
#endif

#ifndef PAGESIZE
#define PAGESIZE 4096
#endif

#ifndef __cplusplus
	#define asm __asm__
	#define volatile __volatile__
	#define inline __inline__
	#define restrict __restrict__
#else
	#ifndef restrict
		#define restrict __restrict__
	#endif
#endif

#define thisfile static
#define global_persist static
#define local_persist static
#define ALIGNOF(type) __alignof__(type)
#define OFFSETOF(type, member) __builtin_offsetof(type, member)
#define TYPEOF(v) __typeof__(v)

#define stc_unreachable __builtin_unreachable()
#define KILOBYTE(x) ((x) * 1024ull)
#define MEGABYTE(x) ((x) * 1024ull * 1024ull)
#define GIGABYTE(x) ((x) * 1024ull * 1024ull * 1024ull)
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


#include <inttypes.h>
#if defined(__wasm_simd128__)
#include <wasm_simd128.h>
#endif

#if defined(__AVX2__)
#define STC_SIMD_ALIGN 32
#elif defined(__SSE4_2__) || defined(__wasm_simd128__)
#define STC_SIMD_ALIGN 16
#endif


#ifndef STC_SIMD_ALIGN
#define STC_SIMD_ALIGN 16
#endif

#define simd_align __attribute__((aligned(STC_SIMD_ALIGN)))

#if defined(__AVX2__) || defined(__SSE4_2__)
#include <immintrin.h>
#endif

#if defined(__wasm_simd128__)
typedef v128_t simd_i32;
typedef v128_t simd_u32;
typedef v128_t simd_i64;
typedef v128_t simd_u64;
typedef v128_t simd_f32;
typedef v128_t simd_f64;
typedef v128_t simd_i16;
typedef v128_t simd_u16;
typedef v128_t simd_i8;
typedef v128_t simd_u8;
#elif defined(__AVX2__)
typedef __m256i simd_i32;
typedef __m256i simd_u32;
typedef __m256i simd_i64;
typedef __m256i simd_u64;
typedef __m256  simd_f32;
typedef __m256d simd_f64;
typedef __m256i simd_i16;
typedef __m256i simd_u16;
typedef __m256i simd_i8;
typedef __m256i simd_u8;
#elif defined(__SSE4_2__)
typedef __m128i simd_i32;
typedef __m128i simd_u32;
typedef __m128i simd_i64;
typedef __m128i simd_u64;
typedef __m128  simd_f32;
typedef __m128d simd_f64;
typedef __m128i simd_i16;
typedef __m128i simd_u16;
typedef __m128i simd_i8;
typedef __m128i simd_u8;
#endif





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




enum stc_std_file {
	STC_STDIN,
	STC_STDOUT,
	STC_STDERR,
};


// struct stc_fd {
// };

struct stc_file {
	struct {
#ifdef _WIN32
		HANDLE	fd;
#else
		int fd;
#endif
	};
	u64		file_size;
};



thisfile void stc_exit(u32 code) __attribute__((noreturn));

thisfile void stc_exit(u32 code)
{
#ifdef _WIN32
	ExitProcess((UINT)code);
#else
	__asm__ volatile (
	    "syscall"
	    :
	    : "a"(60), "D"((u64)code)
	    : "rcx", "r11", "memory"
	    );
#endif
	stc_unreachable;
}


static bool f32_is_nan(f32 f)
{
	union {u32 u; f32 f;} x;
	x.f = f;
	return ((x.u & EXPONENTF32) == EXPONENTF32) && ((x.u & MANTISSAF32) != 0);
}

static bool is_prime(u64 n)
{
	if (n < 2) return false;
	if ((n & 1) == 0) return n == 2;
	for (u64 i = 3; i * i <= n; i += 2) {
		if (n % i == 0) return false;
	}
	return true;
}

static u64 next_prime(u64 n)
{
	if (n <= 2) return 2;
	if ((n & 1) == 0) n++;
	while (!is_prime(n)) n += 2;
	return n;
}

static bool is_pow2(u64 n)
{
	return (n != 0) && (n & (n - 1)) == 0;
}

static u64 next_pow2(u64 n)
{
	n--;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	n |= n >> 32;
	n++;
	return n;
}

static f32 stc_minf32(f32 a, f32 b)
{
	return (a < b) ? a : b;
}

static f32 stc_maxf32(f32 a, f32 b)
{
	return (a > b) ? a : b;
}


static u32 stc_maxu32(u32 a, u32 b)
{
	return (a > b) ? a : b;
}
