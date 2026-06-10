#pragma once
#include <stddef.h>

#ifndef _WIN32
	#include <unistd.h>
#endif





thisfile bool32
stc_c_string_cmp (
    const stc_byte * restrict a,
    const u64 alen,
    const stc_byte * restrict b,
    const u64 blen)
{
	if (blen != alen)
		return false;

	u64 i = 0;
	while (i < alen) {
		if (a[i] != b[i])
			return false;

		++i;
	}
	return true;
}


#define STRBLDR_TYPE_LIST(X)\
	X(SB_T_CHAR,		char, parse_char)\
	X(SB_T_U8,		u8, parse_u8)\
	X(SB_T_U16,		u16, parse_u16)\
	X(SB_T_U32, 		u32, parse_u32)\
	X(SB_T_U64, 		u64, parse_u64)\
	X(SB_T_I8,		i8, parse_i8)\
	X(SB_T_I16,		i16, parse_i16)\
	X(SB_T_I32, 		i32, parse_i32)\
	X(SB_T_I64, 		i64, parse_i64)\
	X(SB_T_F32, 		f32, parse_f32)\
	X(SB_T_F64, 		f64, parse_f64)\
	X(SB_T_POINTER, 	p, parse_pointer)\
	X(SB_T_HEX,		x, parse_hex)\
	X(SB_T_BINARY,		b, parse_binary)\
	X(SB_T_STC_STACK,	stc_stack, parse_stc_stack)\
	X(SB_T_STC_STRING8,	string, parse_stc_string8)\
	X(SB_T_STC_CSTRING,	cstring, parse_cstring)




#define X(name, ...) name,
enum strbldr_types {
	SB_T_NIL,
	STRBLDR_TYPE_LIST(X)
	SB_TYPES_COUNT
};
#undef X


static struct stc_string8 strbldr_types_lit[] = {
#ifdef __cplusplus
	STRING8_NULL,
#define X(index, name, ...) STR8LIT(#name),
	STRBLDR_TYPE_LIST(X)
#undef X
#else
#define X(index, name, ...) [index] = STR8LIT(#name),
	STRBLDR_TYPE_LIST(X)
#undef X
#endif
};





static void stc_string8_cpy(struct stc_string8 * restrict a, const u64 a_capacity, const struct stc_string8 * restrict b)
{
	const u64 remaining = (a_capacity >= a->len) ? a_capacity - a->len : 0;
	if (unlikely(remaining < b->len)) {
		stc_println_err("Could not copy string: not enough space remaining");
		return;
	}
	for (u64 i = 0; i < b->len; ++i) {
		a->str[i] = b->str[i];
	}
	a->len = b->len;
}


static u64 stc_string8_len(const stc_byte *stc_string8)
{
	if (stc_string8 == NULL) return 0;
	if(stc_string8[0] == '\0') return 0;
	u64 count = 0;
	while(stc_string8[++count]);
	return count;
}

thisfile int stc_memcmp(const void * restrict destination, const void * restrict src, u64 size)
{
	return __builtin_memcmp(destination, src, size);
}

thisfile inline struct stc_string8 make_string(stc_byte *ch)
{
	struct stc_string8 null_stub = STRING8_NULL;
	if (ch[0] == '\0')
		return null_stub;

	u64 len = stc_string8_len(ch);
	stc_byte *buf = (stc_byte *)stc_alloc(len);

	u64 idx = 0;
	while(idx < len) {
		buf[idx] = ch[idx];
		idx++;
	}
	buf[len] = '\0';

	return STC_STRUCT_LIT(stc_string8, buf, len);
}


#if defined(__AVX2__)
thisfile inline int sstrcpyx(struct stc_string8 * restrict dest, const struct stc_string8 * restrict source)
{
    u64 begin = 0;

    for(; begin + 32 < source->len; begin+=32)
    {
        simd_u8 source_v = _mm256_loadu_si256((const simd_u8 *)((const stc_byte *)source->str + begin));
        _mm256_storeu_si256((simd_u8 *)((stc_byte *)dest->str + begin), source_v);
    }

    for(; begin < source->len; begin++)
    {
        ((stc_byte *)dest->str)[begin] = ((const stc_byte*)source->str)[begin];
    }

    dest->len = source->len;
    return 0;
}
#endif

thisfile inline i64 stormc_find_substr(const struct stc_string8 haystack, const struct stc_string8 needle)
{

	u64 i;
	if (needle.len == 0 || haystack.len < needle.len) return false;

	if (haystack.len < 32) {
		for (i = 0; i <= (haystack.len - needle.len); i++) {
			u64 j = 0;

			while (j < needle.len && haystack.str[i + j] == needle.str[j])
				j++;

			if (j == needle.len)
				return i;
		}
		return -1;
	}

#if defined(__AVX2__)
	__m256i target = _mm256_setzero_si256();
	stc_memcpy(&target, needle.str, needle.len);

	for (i = 0; i <= haystack.len - 32; i++) {
		__m256i chunk = _mm256_loadu_si256((const __m256i*)(haystack.str + i));
		__m256i cmp = _mm256_cmpeq_epi8(chunk, target);
		u32 mask = _mm256_movemask_epi8(cmp);

		if ((mask & ((1 << needle.len) - 1)) == ((1 << needle.len) - 1)) {
			if (stc_memcmp(haystack.str + i, needle.str, needle.len) == 0) return i;
		}
	}

	for (i = haystack.len - 31; i <= haystack.len - needle.len; i++) {
		if (stc_memcmp(haystack.str + i, needle.str, needle.len) == 0) return i;
	}

	return -1;
#else
	return -1;
	#endif
}



static void stc_memcpy(void * restrict destination, const void * restrict source, u64 size)
{
	stc_byte *dest_start = (stc_byte*)destination;
	const stc_byte *start = (const stc_byte *)source;
	const stc_byte *end = (stc_byte*)source + size;

	while (start != end) {
		*dest_start = *start;
		++start;
		++dest_start;
	}
}

static void stc_memset(void * restrict destination, u64 value, u64 size)
{
	stc_byte *dest_start = (stc_byte*)destination;
	stc_byte *dest_end = dest_start + size;

	while (dest_start != dest_end) {
		(*dest_start) = value;
		++dest_start;
	}
}



static void stc_memmove(void *destination, const void *src, u64 size)
{
	stc_byte *dest_start = (stc_byte*)destination;
	const stc_byte *src_start = (const stc_byte*)src;

	if (dest_start == src_start || size == 0) {
		return;
	}

	if (dest_start < src_start) {
		stc_memcpy(dest_start, src_start, size);
	} else {
		dest_start += size;
		src_start += size;
		while (size--) {
			--dest_start;
			--src_start;
			*dest_start = *src_start;
		}
	}
}


static void stc_arena_string8_start(struct stc_arena_string8 *a)
{
	a->checkpoint = a->offset_mem;
}


static void stc_arena_string8_end(struct stc_arena_string8 *a)
{
	a->offset_mem = a->checkpoint;
}

static void stc_arena_string8_reset(struct stc_arena_string8 *a)
{
	a->offset_mem = 0;
}


static struct stc_string8_split stc_string8_split(struct stc_arena_string8 * restrict a, struct stc_string8 * restrict s, stc_byte delim)
{
	struct stc_string8_split pl = {0};

	stc_byte *start = s->str;
	stc_byte *end = s->str + s->len;
	pl.strings = stc_arena_string8_push(a, s->len);

	u64 len = 0;
	pl.strings[pl.ct_strings].str = start;
	while (start != end) {
		if ((*start) == delim) {
			pl.strings[pl.ct_strings].len = len;
			pl.ct_strings++;
			++start;
			pl.strings[pl.ct_strings].str = start;
			len = 0;
			continue;
		} else {
			len++;
		}
		++start;
	}
	pl.strings[pl.ct_strings].len = len;
	pl.ct_strings++;

	return pl;
}


static u64 stc_len_c_string(stc_byte *c_string)
{
	u64 len = 0;
	if (c_string == NULL)
		return 0;
	if (c_string[0] == '\0')
		return 0;

	while ((*c_string) != '\0') {
		len++;
		c_string++;
	}

	return len;
}


thisfile bool32 stc_is_whitespace(stc_byte c)
{
	return c == ' ' || c == '\r' || c == '\n' || c == '\t' || c == '\v' || c == '\f';
}

thisfile bool32 stc_is_alpha_upper(stc_byte c)
{
	return c >= 'A' && c <= 'Z';
}

thisfile bool32 stc_is_alpha_lower(stc_byte c)
{
	return c >= 'a' && c <= 'z';
}

thisfile bool32 stc_is_alpha(stc_byte c)
{
	return stc_is_alpha_lower(c) || stc_is_alpha_upper(c);
}

thisfile bool32 stc_is_digit(stc_byte c)
{
	return (c >= '0' && c <= '9');
}


thisfile bool32 stc_is_symbol(stc_byte c)
{
	return (c == '~' || c == '!'  || c == '$' || c == '%' || c == '^' ||
		c == '&' || c == '*'  || c == '-' || c == '=' || c == '+' ||
         	c == '<' || c == '.'  || c == '>' || c == '/' || c == '?' ||
         	c == '|' || c == '\\' || c == '{' || c == '}' || c == '(' ||
         	c == ')' || c == '\\' || c == '[' || c == ']' || c == '#' ||
         	c == ',' || c == ';'  || c == ':' || c == '@');
}



thisfile stc_byte stc_string8_to_u8(struct stc_string8 *string)
{
	stc_byte pl = 0;
	for (stc_byte *start = string->str, *end = string->str + string->len; start!= end; ++start) {
		if (!stc_is_digit(*start)) continue;
		pl = (pl * 10) + ((*start) ^ '0');
	}

	return pl;
}

thisfile u16 stc_string8_to_u16(struct stc_string8 *string)
{
	u16 pl = 0;
	for (stc_byte *start = string->str, *end = string->str + string->len; start!= end; ++start) {
		if (!stc_is_digit(*start)) continue;
		pl = (u16)((pl * 10) + ((*start) ^ '0'));
	}

	return pl;

}

thisfile u32 stc_string8_to_u32(struct stc_string8 *string)
{
	u32 pl = 0;
	for (stc_byte *start = string->str, *end = string->str + string->len; start!= end; ++start) {
		if (!stc_is_digit(*start)) continue;
		pl = (pl * 10) + (u32)((*start) ^ '0');
	}

	return pl;

}


thisfile u64 stc_string8_to_u64(struct stc_string8 *string)
{
	u64 pl = 0;
	for (stc_byte *start = string->str, *end = string->str + string->len; start!= end; ++start) {
		if (!stc_is_digit(*start)) continue;
		pl = (pl * 10) + (u64)((*start) ^ '0');
	}

	return pl;
}

thisfile i8 stc_string8_to_i8(struct stc_string8 *string)
{
	u8 pl = 0;
	bool is_negative = string->str[0] == '-';
	stc_byte *start;
	if (is_negative) {
		start = string->str + 1;
	} else {
		start = string->str;
	}
	for (stc_byte *end = string->str + string->len; start!= end; ++start) {
		if (!stc_is_digit(*start)) continue;
		pl = (u8)((pl * 10) + ((*start) ^ '0'));
	}

	return is_negative ? (i8)(0 - pl) : (i8)pl;
}

thisfile i16 stc_string8_to_i16(struct stc_string8 *string)
{
	u16 pl = 0;
	bool is_negative = string->str[0] == '-';
	stc_byte *start;
	if (is_negative) {
		start = string->str + 1;
	} else {
		start = string->str;
	}
	for (stc_byte *end = string->str + string->len; start!= end; ++start) {
		if (!stc_is_digit(*start)) continue;
		pl = (u16)((pl * 10) + ((*start) ^ '0'));
	}

	return is_negative ? (i16)(0 - pl) : (i16)pl;
}

thisfile i32 stc_string8_to_i32(struct stc_string8 *string)
{
	u32 pl = 0;
	bool is_negative = string->str[0] == '-';
	stc_byte *start;
	if (is_negative) {
		start = string->str + 1;
	} else {
		start = string->str;
	}
	for (stc_byte *end = string->str + string->len; start!= end; ++start) {
		if (!stc_is_digit(*start)) continue;
		pl = (pl * 10) + (u32)((*start) ^ '0');
	}

	return is_negative ? (i32)(0 - pl) : (i32)pl;
}

thisfile i64 stc_string8_to_i64(struct stc_string8 *string)
{
	u64 pl = 0;
	bool is_negative = string->str[0] == '-';
	stc_byte *start;
	if (is_negative) {
		start = string->str + 1;
	} else {
		start = string->str;
	}
	for (stc_byte *end = string->str + string->len; start!= end; ++start) {
		if (!stc_is_digit(*start)) continue;
		pl = (pl * 10) + (u64)((*start) ^ '0');
	}

	return is_negative ? (i64)(0 - pl) : (i64)pl;
}

thisfile f64 stc_string8_to_float(struct stc_string8 *string)
{

	f64 pl = 0.0f;

	bool is_negative = string->str[0] == '-';
	stc_byte *start;
	if (is_negative) {
		start = string->str + 1;
	} else {
		start = string->str;
	}

	stc_byte *end = string->str + string->len;

	for (; start != end && (*start) != '.'; ++start) {
		if (!stc_is_digit(*start)) continue;
		pl = (pl * 10) + ((*start) ^ '0');
	}
	if (start != end) ++start; /*eat dot '.' */

	f64 divisor = 10.0f;
	for (; start != end; ++start) {
		if (!stc_is_digit(*start)) continue;
		f64 fractional = (*start) ^ '0';
		pl = pl + fractional / divisor;
		divisor *= 10.0f;
	}


	return is_negative ? -pl : pl;
}

static inline bool stc_string8_cmp(const struct stc_string8 a, const struct stc_string8 b)
{
	if (a.len != b.len)
		return false;


	for (u64 i = 0; i < a.len; ++i) {
		if (a.str[i] != b.str[i])
			return false;
	}

	return true;
}



static struct stc_arena_string8 stc_arena_string8_init(u32 string_count_to_init)
{
	struct stc_arena_string8 pl = {0};
	u64 commit_size =  STC_ALIGN_UP((sizeof(struct stc_string8) * string_count_to_init), PAGESIZE);


	pl.mem = (stc_byte*)stc_os_mem_rsrv(DEFAULT_RESERVATION);
	stc_os_mem_cmt(pl.mem, commit_size);


	pl.strings = (struct stc_string8 *)pl.mem;
	pl.current_max_strings = string_count_to_init;
	pl.offset_mem = 0;


	pl.mem_cmtd = commit_size;
	pl.mem_rsrvd = DEFAULT_RESERVATION;

	return pl;
}

static struct stc_string8 *stc_arena_string8_push(struct stc_arena_string8 *a, u64 count)
{
	stc_byte *current_ptr = a->mem + a->offset_mem;
	u64 next_offset = a->offset_mem + (sizeof(struct stc_string8) * count);
	if (next_offset > a->mem_cmtd) {
		u64 delta_aligned = STC_ALIGN_UP(next_offset - a->mem_cmtd, PAGESIZE);
		stc_os_mem_cmt(current_ptr, delta_aligned);
		a->mem_cmtd += delta_aligned;
	}

	a->offset_mem = next_offset;

	return (struct stc_string8 *)current_ptr;
}


static void stc_string8_to_upper(struct stc_string8 *s)
{
	for (u64 i = 0; i < s->len; ++i) {
		if (stc_is_alpha_lower(s->str[i])) {
			s->str[i] -= 32;
		}
	}
}

static inline void stc_c_string_reverse (stc_byte *s, u64 len)
{
	--len;
	stc_byte *end = s + len;
	while (s < end) {
		*s ^= *end;
		*end ^= *s;
		*s ^= *end;
		++s;
		--end;
	}
}


thisfile inline u64 stc_utohex(u64 n, stc_byte *s)
{
	stc_byte *start = s;

	do {
		stc_byte digit = n & 0xF;
		(*s) = (digit < 10) ? (digit | '0') : (digit + ('a' - 10));
		++s;
		n >>= 4;
	} while(n);

	*s = '\0';
	stc_c_string_reverse(start, s - start);
	return s - start;
}

thisfile inline u64 stc_ftoa(f64 n, stc_byte *s)
{
	stc_byte *start = s;

	if (n < 0) {
		*s++ = '-';
		n = -n;
	}

	const i64 scale = 100000;

	i64 whole = (i64)n;
	i64 frac = (i64)((n - (f64)whole) * (f64)scale + 0.5);

	/* rounding can push 0.999999 to 1.00000 */
	if (frac >= scale) {
		whole += 1;
		frac -= scale;
	}

	s += stc_utoa((u64)whole, s);

	*s++ = '.';

	/* exactly 5 fractional digits, including leading zeroes */
	i64 div = scale / 10;
	while (div > 0) {
		*s++ = (stc_byte)('0' + ((frac / div) % 10));
		div /= 10;
	}

	*s = '\0';
	return (u64)(s - start);
}


static u64 stc_itoa(i64 n, stc_byte *s)
{
	stc_byte *start = s;
	bool is_negative = n < 0;
	u64 value = is_negative ? (0 - (u64)n) : (u64)n;

	do {
		(*s) = value % 10 + '0';
		++s;
	} while((value /= 10) > 0);

	if (is_negative) {
		*s = '-';
		++s;
	}

	*s = '\0';
	stc_c_string_reverse(start, s - start);
	return s - start;
}

static u64 stc_utobin(u64 n, stc_byte *s)
{
	stc_byte *start = s;
	bool started = false;

	for (int i = 63; i >= 0; --i) {
		u64 mask = 1ull << i;
		if (n & mask) {
			started = true;
			*s++ = '1';
		} else if (started) {
			*s++ = '0';
		}
	}

	if (!started) {
		*s++ = '0';
	}

	*s = '\0';
	return (u64)(s - start);
}

static u64 stc_utoa(u64 n, stc_byte *s)
{
#ifdef SASM
	return sasm_utoa64(s, n);
#else
	stc_byte *start = s;

	do {
		*s = (n % 10) + '0';
		++s;
	} while ((n /= 10) > 0);

	*s = '\0';
	stc_c_string_reverse(start, s - start);
	return s - start;
#endif
}




static struct stc_strbldr stc_strbldr_emit(u64 sz_rsrv, u64 sz_init)
{
	struct stc_strbldr pl = {0};

	sz_init = STC_ALIGN_UP(sz_init, PAGESIZE);

	pl.ptr = (stc_byte*)stc_os_mem_rsrv(sz_rsrv);

	if (stc_os_mem_cmt(pl.ptr, sz_init) == NULL) {
		stc_exit(1);
	}

	pl.rsrv = sz_rsrv;
	pl.cmt = sz_init;


	return pl;
}

static void stc_strbldr_free(struct stc_strbldr *b)
{
	stc_free(b->ptr, b->cmt);
}


static void check_alloc(struct stc_strbldr *b, u64 new_size)
{
	if (new_size > b->cmt) {
		u64 delta_aligned = STC_ALIGN_UP(new_size - b->cmt, PAGESIZE);
		if (stc_os_mem_cmt((b->ptr + b->cmt), delta_aligned) == NULL) {
			perror("mprotect");
			stc_exit(1);
		}
		b->cmt += delta_aligned;
	}
}


static void stc_strbldr_append(struct stc_strbldr *b, const stc_byte *s, ...)
{
	va_list args;
	va_start(args, s);
	stc_strbldr_add_v(b, s, args);
	va_end(args);
}


static void stc_strbldr_reset(struct stc_strbldr *b)
{
	stc_memset(b->ptr, 0, b->off);
	b->off = 0;
}

static void stc_strbldr_fprint_range(struct stc_strbldr *b, int start, int end)
{
	if ((end < start && end != -1) || (start < 0))
		return;

	const char *ptr_s = (const char *)(b->ptr + start);
	if (end == -1) {
		end = b->off;
	}
	u64 len = end - start;
	stc_println("{string}", STC_STRUCT_LIT(stc_string8, (stc_byte *)ptr_s, len));
}

static void stc_strbldr_add_v(struct stc_strbldr * restrict b, const stc_byte * restrict s, va_list args)
{
	u32 len = stc_string8_len((stc_byte*)s);
	u64 new_size = b->off + len;

	enum strbldr_types current_type = SB_T_NIL;


	const stc_byte *start = s;
	const stc_byte *end = s + len;
	const stc_byte *cur_cstr = NULL;
	struct stc_stack *fmt_stack = NULL;
	u32 len_cur_cstr = 0;
	i64 cur_signed_int = 0;
	u64 cur_unsigned_int = 0;
	u64 cur_hex = 0;
	double cur_float = 0.;
	stc_byte buff_digits[512] = {0};
	u64 len_buff_digits = 0;
	u64 rem = 0;

	check_alloc(b, new_size);

loop:
	if (start >= end) goto fin;
	current_type = SB_T_NIL;

	if (*start != '{') {
		b->ptr[b->off++] = *start;
		++start;
		goto loop;
	}
	++start;
	if (*start == '{') {
		while (*start != '}') {
			b->ptr[b->off++] = *start;
			++start;
		}
		b->ptr[b->off++] = *start;
		++start;
		if (*start != '}') {
			stc_println("Missing closing curly brace '}'");
			stc_exit(1);
		}
		++start;
		goto loop;
	}
	rem = (u64)(end - start);

#define X(_id, _type, _label)                                                   \
    if (rem >= strbldr_types_lit[_id].len &&                                    \
        stc_c_string_cmp(start,                                                 \
                         strbldr_types_lit[_id].len,                            \
                         strbldr_types_lit[_id].str,                            \
                         strbldr_types_lit[_id].len)) {                         \
	current_type = _id;							\
        goto _label;								\
    }
	STRBLDR_TYPE_LIST(X)
#undef X
	if (current_type == SB_T_NIL) {
		stc_println_err("Unknown type");
		stc_exit(1);
	}

	stc_unreachable;

advance:
	++start;
	len_buff_digits = 0;
	len_cur_cstr = 0;
	goto loop;



parse_binary:
	start += strbldr_types_lit[SB_T_BINARY].len;
	cur_unsigned_int = va_arg(args, u32);
	len_buff_digits = stc_utobin(cur_unsigned_int, buff_digits);
	new_size += len_buff_digits;
	check_alloc(b, new_size);
	stc_memcpy(b->ptr + b->off, buff_digits, len_buff_digits);
	b->off += len_buff_digits;
	if (unlikely(*start != '}')) {
		stc_println_err("Expected bracket '}' for formatting");
		stc_exit(1);
	}
	goto advance;

parse_stc_stack:
	start += strbldr_types_lit[SB_T_STC_STACK].len;
	fmt_stack = va_arg(args, struct stc_stack*);
	goto parse_stack_pretty;

parse_stack_pretty:
{
	static const struct stc_string8 stack_cur_baseoff_txt = STR8LIT("[Stack base offset: ");
	static const struct stc_string8 stack_cur_mem_rsrv   = STR8LIT("[Stack reserved memory: ");
	static const struct stc_string8 stack_cur_mem_cmt    = STR8LIT("[Stack committed memory: ");
	static const struct stc_string8 stack_cur_base_ptr   = STR8LIT("[Stack base pointer address: ");

	// base offset
	stc_memcpy(b->ptr + b->off, stack_cur_baseoff_txt.str, stack_cur_baseoff_txt.len);
	b->off += stack_cur_baseoff_txt.len;

	len_buff_digits = stc_utoa(fmt_stack->base_offset, buff_digits);
	new_size += len_buff_digits;
	check_alloc(b, new_size);
	stc_memcpy(b->ptr + b->off, buff_digits, len_buff_digits);
	b->off += len_buff_digits;

	b->ptr[b->off++] = ']';
	b->ptr[b->off++] = '\n';

	// reserved memory
	stc_memcpy(b->ptr + b->off, stack_cur_mem_rsrv.str, stack_cur_mem_rsrv.len);
	b->off += stack_cur_mem_rsrv.len;

	len_buff_digits = stc_utoa(fmt_stack->mem_rsrv, buff_digits);
	new_size += len_buff_digits;
	check_alloc(b, new_size);
	stc_memcpy(b->ptr + b->off, buff_digits, len_buff_digits);
	b->off += len_buff_digits;

	b->ptr[b->off++] = ']';
	b->ptr[b->off++] = '\n';

	// committed memory
	stc_memcpy(b->ptr + b->off, stack_cur_mem_cmt.str, stack_cur_mem_cmt.len);
	b->off += stack_cur_mem_cmt.len;

	len_buff_digits = stc_utoa(fmt_stack->mem_committed, buff_digits);
	new_size += len_buff_digits;
	check_alloc(b, new_size);
	stc_memcpy(b->ptr + b->off, buff_digits, len_buff_digits);
	b->off += len_buff_digits;

	b->ptr[b->off++] = ']';
	b->ptr[b->off++] = '\n';

	// base pointer
	stc_memcpy(b->ptr + b->off, stack_cur_base_ptr.str, stack_cur_base_ptr.len);
	b->off += stack_cur_base_ptr.len;

	len_buff_digits = stc_utohex((u64)fmt_stack->base, buff_digits);
	new_size += len_buff_digits + 2;
	check_alloc(b, new_size);

	b->ptr[b->off++] = '0';
	b->ptr[b->off++] = 'x';
	stc_memcpy(b->ptr + b->off, buff_digits, len_buff_digits);
	b->off += len_buff_digits;

	b->ptr[b->off++] = ']';
	b->ptr[b->off++] = '\n';

	if (unlikely(*start != '}')) {
		stc_println_err("Expected closing bracket '}' for formatting");
		stc_exit(1);
	}

	goto advance;
}

parse_i8:
	start += strbldr_types_lit[SB_T_I8].len;
	cur_signed_int = va_arg(args, int);
	goto parse_signed;

parse_i16:
	start += strbldr_types_lit[SB_T_I16].len;
	cur_signed_int = va_arg(args, int);
	goto parse_signed;

parse_i32:
	start += strbldr_types_lit[SB_T_I32].len;
	cur_signed_int = va_arg(args, int);
	goto parse_signed;

parse_i64:
	start += strbldr_types_lit[SB_T_I64].len;
	cur_signed_int = va_arg(args, i64);
	goto parse_signed;

parse_signed:
	len_buff_digits = stc_itoa(cur_signed_int, (stc_byte*)buff_digits);
	new_size += len_buff_digits;
	check_alloc(b, new_size);
	stc_memcpy(b->ptr + b->off, buff_digits, len_buff_digits);
	b->off += len_buff_digits;
	if (unlikely(*start != '}')) {
		stc_println_err("Expected closing bracket '}' for formatting");
		stc_exit(1);
	}
	goto advance;


parse_char:
	start += strbldr_types_lit[SB_T_CHAR].len;
	cur_unsigned_int = va_arg(args, int);
	check_alloc(b, new_size + 1);
	b->ptr[b->off++] = (stc_byte)cur_unsigned_int;
	if (unlikely(*start != '}')) {
		stc_println_err("Expected closing bracket '}' for formatting");
		stc_exit(1);
	}
	goto advance;

parse_u8:
	start += strbldr_types_lit[SB_T_U8].len;
	cur_unsigned_int = va_arg(args, int);
	goto parse_unsigned;

parse_u16:
	start += strbldr_types_lit[SB_T_U16].len;
	cur_unsigned_int = va_arg(args, int);
	goto parse_unsigned;

parse_u32:
	start += strbldr_types_lit[SB_T_U32].len;
	cur_unsigned_int = va_arg(args, u32);
	goto parse_unsigned;

parse_u64:
	start += strbldr_types_lit[SB_T_U64].len;
	cur_unsigned_int = va_arg(args, u64);
	goto parse_unsigned;

parse_unsigned:
	len_buff_digits = stc_utoa(cur_unsigned_int, (stc_byte*)buff_digits);
	new_size += len_buff_digits;
	check_alloc(b, new_size);
	stc_memcpy(b->ptr + b->off, buff_digits, len_buff_digits);
	b->off += len_buff_digits;
	if (unlikely(*start != '}')) {
		stc_println_err("Expected closing bracket '}' for formatting");
		stc_exit(1);
	}
	goto advance;


parse_f32:
	start += strbldr_types_lit[SB_T_F32].len;
	/*Floats are promoted to doubles in variadics*/
	cur_float = va_arg(args, f64);
	goto parse_float;
parse_f64:
	start += strbldr_types_lit[SB_T_F64].len;
	cur_float = va_arg(args, f64);
	goto parse_float;

parse_float:
	len_buff_digits = stc_ftoa(cur_float, (stc_byte*)buff_digits);
	new_size += len_buff_digits;
	check_alloc(b, new_size);
	stc_memcpy(b->ptr + b->off, buff_digits, len_buff_digits);
	b->off += len_buff_digits;
	if (unlikely(*start != '}')) {
		stc_println_err("Expected closing bracket '}' for formatting");
		stc_exit(1);
	}
	goto advance;



parse_cstring:
	start += strbldr_types_lit[SB_T_STC_CSTRING].len;
	cur_cstr = va_arg(args, stc_byte *);
	len_cur_cstr = stc_string8_len((stc_byte *)cur_cstr);
	goto parse_string_common;

parse_stc_string8: {
	struct stc_string8 str8;

	start += strbldr_types_lit[SB_T_STC_STRING8].len;
	str8 = va_arg(args, struct stc_string8);
	cur_cstr = str8.str;
	len_cur_cstr = str8.len;
	goto parse_string_common;
}

parse_string_common:
	new_size += len_cur_cstr;
	check_alloc(b, new_size);
	stc_memcpy(b->ptr + b->off, cur_cstr, len_cur_cstr);
	b->off += len_cur_cstr;
	if (unlikely(*start != '}')) {
		stc_println_err("Expected '}' for string formatting");
		stc_exit(1);
	}
	goto advance;


parse_pointer:
	start += strbldr_types_lit[SB_T_POINTER].len;
	cur_hex = (u64)va_arg(args, void *);
	goto parse_hex_pointer;
parse_hex:
	start += strbldr_types_lit[SB_T_HEX].len;
	cur_hex = va_arg(args, u32);
	goto parse_hex_pointer;

parse_hex_pointer:
	len_buff_digits = stc_utohex(cur_hex, (stc_byte*)buff_digits);
	new_size += len_buff_digits + 2;
	check_alloc(b, new_size);
	b->ptr[b->off++] = '0';
	b->ptr[b->off++] = 'x';
	stc_memcpy(b->ptr + b->off, buff_digits, len_buff_digits);
	b->off += len_buff_digits;
	if (unlikely(*start != '}')) {
		stc_println_err("Expected closing bracket '}' for formatting");
		stc_exit(1);
	}
	goto advance;
fin:
	return;
}
