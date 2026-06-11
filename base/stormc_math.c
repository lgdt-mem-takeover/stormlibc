#pragma once


#include "stc_simd_codegen.h"

static f32 stc_rsqrt_f32(f32 number)
{
	const f32 threehalfs = 1.5f;

	f32 x2 = number * 0.5f;
	f32 y = number;

	u32 i;
	__builtin_memcpy(&i, &y, sizeof(i));
	i = 0x5f3759df - (i >> 1);
	__builtin_memcpy(&y, &i, sizeof(y));

	y = y * (threehalfs - (x2 * y * y)); // 1 iteration

	return y;
}

static f32 stc_sqrt_f32(f32 x)
{
	return x * stc_rsqrt_f32(x);
}

static struct vec2 stc_sub2(struct vec2 a, struct vec2 b)
{
	return STC_STRUCT_LIT(vec2, a.x - b.x, a.y - b.y);
}

static struct vec2 stc_add2(struct vec2 a, struct vec2 b)
{
	return STC_STRUCT_LIT(vec2, a.x + b.x, a.y + b.y);
}
static struct vec2 stc_scale2(struct vec2 v, f32 s)
{
	return STC_STRUCT_LIT(vec2, v.x * s, v.y * s);
}

static f32 stc_len2_sq(struct vec2 v)
{
	return (v.x * v.x) + (v.y * v.y);
}

static f32 stc_len2(struct vec2 v)
{
	return stc_sqrt_f32(stc_len2_sq(v));
}

static struct vec2 stc_norm2(struct vec2 v)
{
	f32 len = stc_len2(v);
	if (len == 0.0f) return STC_STRUCT_ZERO(vec2);

	return STC_STRUCT_LIT(vec2, v.x / len, v.y / len);
}
