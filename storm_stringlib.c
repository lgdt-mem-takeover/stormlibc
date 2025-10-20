#pragma once
#include "storm.h"
#include <immintrin.h>


#define STR(x) (String){.str = (x), .len = sizeof((x)) - 1}

static inline u32 sstrlenx(const char *string)
{
    if(string[0] == '\0') return 0;
    u32 count = 0;
    while(string[++count]);
    return count;
}


static inline String make_string(char *ch)
{
    if(ch[0] == '\0') return (String){.err = -1};
    u64 len = sstrlenx(ch);
    char *buf = mmap(NULL, len + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

    u64 idx = 0;
    while(idx < len)
    {
        buf[idx] = ch[idx];
        idx++;
    }
    buf[len] = '\0';

    return (String){.str = buf, .len = len};

}

static inline String emit_empty_string_with_size(size_t size)
{
    char *buf = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1 , 0);

    return (String){.str = buf, .len = 0};
}





static inline void smemsetx_avx2(void * restrict target, u8 set_to, size_t size) {
    __m256i fill = _mm256_set1_epi8(set_to);
    u8 *ptr = (u8 *)target;
    size_t i = 0;
    for (; i + 32 <= size; i += 32) {
        _mm256_storeu_si256((__m256i *)(ptr + i), fill);
    }
    for (; i < size; i++) {
        ptr[i] = set_to;
    }
}

static inline bool sstrcmpx_8(const Storm_String8 a, const Storm_String8 b)
{

    simd_32_u8 a_load = _mm256_loadu_si256((const simd_32_u8*)a.str);
    simd_32_u8 b_load = _mm256_loadu_si256((const simd_32_u8*)b.str);
    simd_32_u8 cmp = _mm256_cmpeq_epi8(a_load, b_load);

    int mask = (1 << a.len) - 1;
    return (_mm256_movemask_epi8(cmp) & mask) == mask;
}

static inline bool sstrcmpx_16(const Storm_String16 a, const Storm_String16 b)
{


    simd_32_u8 a_load = _mm256_loadu_si256((const simd_32_u8*)a.str);
    simd_32_u8 b_load = _mm256_loadu_si256((const simd_32_u8*)b.str);
    simd_32_u8 cmp = _mm256_cmpeq_epi8(a_load, b_load);

    int mask = (1 << a.len) - 1;
    return (_mm256_movemask_epi8(cmp) & mask) == mask;
}

static inline bool sstrcmpx_32(const Storm_String32 a, const Storm_String32 b)
{

    simd_32_u8 a_load = _mm256_loadu_si256((const simd_32_u8 *)a.str);
    simd_32_u8 b_load = _mm256_loadu_si256((const simd_32_u8 *)b.str);
    simd_32_u8 cmp = _mm256_cmpeq_epi8(a_load, b_load);

    int mask = (1 << a.len) - 1;
    return (_mm256_movemask_epi8(cmp) & mask) == mask;
}

static inline bool sstrcmpx(const String a, const String b)
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

static inline bool is_alpha(char ch)
{
    return ('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z');
}


static inline bool is_string_digit(const String string) {
    u8 len = sstrlenx(string.str);
    if(len==0)return false;

    u8 idx;
    {
      for(idx = 0; idx < len; idx++){
          if(!('0'<=string.str[idx] && string.str[idx]<='9')){
              return false;
          }
      }
    }
    return true;
}



static inline bool is_null(char *  ptr)
{
    if ((uintptr_t)ptr == 0 || (uintptr_t)ptr == (uintptr_t)-1){
        return true;
    }
    return false;

}
static inline int sstrcpyx_8(Storm_String8 *dest, const Storm_String8 *source)
{

    if(sizeof(*dest) < sizeof(*source)) return -1;

    int begin = 0;
    while(begin < 8){
        dest->str[begin] = source->str[begin];
        begin++;
    }
    dest->len = source->len;
    return 0;
}


static inline int sstrcpyx_16(Storm_String16 *dest, const Storm_String16 *source)
{

    if(sizeof(*dest) < sizeof(*source)) return -1;

    int begin = 0;
    while(begin < 16){
        dest->str[begin] = source->str[begin];
        begin++;
    }
    dest->len = source->len;
    return 0;
}

static inline int sstrcpyx_32(Storm_String32 *dest, const Storm_String32 *source)
{

    if(sizeof(*dest) < sizeof(*source)) return -1;


    simd_32_u8 source_v = _mm256_loadu_si256((const simd_32_u8 *)((const char *)source));
    _mm256_storeu_si256((simd_32_u8 *)((char *)dest), source_v);

    dest->len = source->len;
    return 0;
}

static inline int sstrcpyx(String * restrict dest, const String * restrict source)
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






static inline bool is_char_digit(char ch)
{
 return '0'<=ch && ch<='9';
}

static inline int satoix(char const * restrict array)
{
    int result = 0;
    int i = 0;
    if(!is_char_digit(array[i])){
        printf("WARNING! SATOIX ATTEMPTED CONVERTING A NON-DIGIT! RETURNING 0\n");
        return result;
    }
    while(array[i] != '\0'){
        result = result * 10 + (array[i] ^ '0');
        i++;
    }
    return result;
}

static inline f64 satofx(char const * restrict array)
{
    f64 result = 0.0;
    f64 frac = 0.0;
    f64 frac_div = 10.0;
    u8 idx = 0;
    while(array[idx]!='\0' && array[idx] != '.'){
        result = result * 10 + (array[idx] ^ '0');
        idx++;
    }

    if(array[idx]=='.'){
        idx++;
        while(array[idx]!='\0'){
            frac += (array[idx]^'0') / frac_div;
            frac_div *= 10;
            idx++;
        }
    }

    return result + frac;
}

static inline bool is_alnum(char ch)
{
    return (is_char_digit(ch) || is_alpha(ch));
}


static inline bool find_substring_in_buff(const String haystack, const String needle)
{

  u32 i;
  if (needle.len == 0 || haystack.len < needle.len) return false;

  if (haystack.len < 32){

    for (i = 0; i <= (haystack.len - needle.len); i++) {
        u32 j = 0;
        while (j < needle.len && haystack.str[i + j] == needle.str[j]) j++;
        if (j == needle.len) return true;
    }
    return false;
  }

  __m256i target = _mm256_setzero_si256();
  __builtin_memcpy(&target, needle.str, needle.len);

    for (i = 0; i <= haystack.len - 32; i++) {
        __m256i chunk = _mm256_loadu_si256((const __m256i*)(haystack.str + i));
        __m256i cmp = _mm256_cmpeq_epi8(chunk, target);
        u32 mask = _mm256_movemask_epi8(cmp);

        if ((mask & ((1 << needle.len) - 1)) == ((1 << needle.len) - 1)) {
            if (__builtin_memcmp(haystack.str + i, needle.str, needle.len) == 0) return true;
        }
    }

    for (i = haystack.len - 31; i <= haystack.len - needle.len; i++) {
        if (__builtin_memcmp(haystack.str + i, needle.str, needle.len) == 0) return true;
    }

  return false;

}


