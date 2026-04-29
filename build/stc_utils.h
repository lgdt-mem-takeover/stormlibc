#pragma once

#include "../core/stormc_types.h"
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
#define unreachable __builtin_unreachable()
#define KILOBYTE(x) ((x) * 1024ull)
#define MEGABYTE(x) ((x) * 1024ull * 1024ull)
#define CACHELINE_SIZE 64

#define AS(cast_type, value) ((cast_type)value)
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

#define STR(x) (struct stc_string8){.str = x, .len = sizeof(x) - 1}
#define STR_RUNTIME(x) (struct stc_string8){.str = x, .len = stc_c_string_len(x)}


struct stc_string8{
	u8	*str;
	u64	len;
};


static u64 stc_c_string_len(u8 *s);
static bool stc_string8_cmp(struct stc_string8 a, struct stc_string8 b)
{
	bool is_equal = true;

	if (a.len == b.len) {
		u8 *end_a = a.str + a.len;
		while (a.str != end_a) {
			if (*a.str != *b.str) {
				is_equal = false;
				break;
			}
			a.str++;
			b.str++;
		}
	} else {
		return false;
	}
	return is_equal;
}




u64 stc_c_string_len(u8 *s)
{
	u8 *start = s;
	while((*start) != '\0') {
		start++;
	}

	return start - s;
}

thisfile inline i64 stormc_find_substr(const struct stc_string8 haystack, const struct stc_string8 needle)
{

	u32 i;
	if (needle.len == 0 || haystack.len < needle.len) return false;

	if (haystack.len < 32) {
		for (i = 0; i <= (haystack.len - needle.len); i++) {
			u32 j = 0;

			while (j < needle.len && haystack.str[i + j] == needle.str[j]) j++;
			if (j == needle.len) return i;
		}
		return -1;
	}

	__m256i target = _mm256_setzero_si256();
	__builtin_memcpy(&target, needle.str, needle.len);

	for (i = 0; i <= haystack.len - 32; i++) {
		__m256i chunk = _mm256_loadu_si256((const __m256i*)(haystack.str + i));
		__m256i cmp = _mm256_cmpeq_epi8(chunk, target);
		u32 mask = _mm256_movemask_epi8(cmp);

		if ((mask & ((1 << needle.len) - 1)) == ((1 << needle.len) - 1)) {
			if (__builtin_memcmp(haystack.str + i, needle.str, needle.len) == 0) return i;
		}
	}

	for (i = haystack.len - 31; i <= haystack.len - needle.len; i++) {
		if (__builtin_memcmp(haystack.str + i, needle.str, needle.len) == 0) return i;
	}

	return -1;
}

thisfile inline bool sstrcmpx(const struct stc_string8 a, const struct stc_string8 b)
{

    if(a.len != b.len) return false;

    u64 i = 0;

    for (;i + 32 <= a.len; i += 32) {
        simd_32_u8 a_load = _mm256_loadu_si256((const simd_32_u8 *)(a.str + i));
        simd_32_u8 b_load = _mm256_loadu_si256((const simd_32_u8 *)(b.str + i));
        simd_32_u8 cmp = _mm256_cmpeq_epi8(a_load, b_load);

        int mask = _mm256_movemask_epi8(cmp);
        if(mask != -1) return false;
    }

    for(;i < a.len; i++)
    {
        if (a.str[i] != b.str[i]) return false;
    }

    return true;
}

thisfile inline int sstrcpyx(struct stc_string8 * restrict dest, const struct stc_string8 * restrict source)
{
    int begin = 0;

    for(; begin + 32 < source->len; begin+=32)
    {
        simd_32_u8 source_v = _mm256_loadu_si256((const simd_32_u8 *)((const char *)source->str + begin));
        _mm256_storeu_si256((simd_32_u8 *)((char *)dest->str + begin), source_v);
    }

    for(; begin < source->len; begin++)
    {
        ((char *)dest->str)[begin] = ((const char*)source->str)[begin];
    }

    dest->len = source->len;
    return 0;
}


u32 sstrlenx(const char *stc_string8)
{
    if(stc_string8[0] == '\0') return 0;
    u32 count = 0;
    while(stc_string8[++count]);
    return count;
}
