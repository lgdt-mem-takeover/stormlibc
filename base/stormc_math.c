#pragma once


#include "../stormc_header.h"
#include "stc_simd_codegen.h"

static f32 stc_rsqrt_f32(f32 number)
{
	const f32 threehalfs = 1.5f;

	f32 x2 = number * 0.5f;
	f32 y = number;

	u32 i = *(u32*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(f32*)&i;

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

static f32 stc_len2(struct vec2 v)
{
	return stc_sqrt_f32((v.x * v.x) + (v.y * v.y));
}

static struct vec2 stc_norm2(struct vec2 v)
{
	f32 len = stc_len2(v);
	if (len == 0.0f) return STC_STRUCT_ZERO(vec2);

	return STC_STRUCT_LIT(vec2, v.x / len, v.y / len);
}


