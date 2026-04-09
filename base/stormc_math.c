#pragma once


#include "../stormc_header.h"
#include "stc_simd_codegen.h"

struct mat4 {
	f32 v[16];
};

struct rect{
	f32 x, y, w, h;
};

struct vec2 {
	f32 x, y;
};

struct vec2i {
	i32 x, y;
};

struct vec2u {
	i32 x, y;
};

struct vec2lu {
	i32 x, y;
};

struct vec3 {
	f32 x, y, z;
};

struct vec3i {
	i32 x, y, z;
};

/*@FUNCS_MATH SIGNATURES*/
static f32 stc_min_f32(f32 a, f32 b);
static f32 stc_max_f32(f32 a, f32 b);
static f32 stc_clamp_f32(f32 x, f32 min, f32 max);
static f32 stc_lerp_f32(f32 a, f32 b, f32 t);
static f32 stc_inv_lerp_f32(f32 a, f32 b, f32 v);
static f32 stc_remap_f32(f32 in_min, f32 in_max, f32 out_min, f32 out_max, f32 v);
static f32 stc_abs_f32(f32 x);
static f32 stc_sign_f32(f32 x);
static f32 stc_sqrt_f32(f32 x);
static f32 stc_rsqrt_f32(f32 x);
static f32 stc_floor_f32(f32 x);
static f32 stc_ceil_f32(f32 x);
static f32 stc_round_f32(f32 x);
static f32 stc_mod_f32(f32 x, f32 y);
static f32 stc_fract_f32(f32 x);
static f32 stc_sin(f32 x);
static f32 stc_cos(f32 x);
static f32 stc_tan(f32 x);
static f32 stc_asin(f32 x);
static f32 stc_acos(f32 x);
static f32 stc_atan(f32 x);
static f32 stc_atan2(f32 y, f32 x);
static f32 stc_pow(f32 base, f32 exp);
static f32 stc_exp(f32 x);
static f32 stc_log(f32 x);
static f32 stc_log2(f32 x);
static f32 stc_log10(f32 x);
static struct vec2 stc_vec2(f32 x, f32 y);
static struct vec2 stc_add2(struct vec2 a, struct vec2 b);
static struct vec2 stc_sub2(struct vec2 a, struct vec2 b);
static struct vec2 stc_mul2(struct vec2 a, struct vec2 b);
static struct vec2 stc_scale2(struct vec2 v, f32 s);
static f32  stc_dot2(struct vec2 a, struct vec2 b);
static f32  stc_len2(struct vec2 v);
static f32  stc_len2_sq(struct vec2 v);
struct vec2 stc_norm2(struct vec2 v);
struct vec2 stc_lerp2(struct vec2 a, struct vec2 b, f32 t);
static struct vec3 stc_vec3(f32 x, f32 y, f32 z);
static struct vec3 stc_add3(struct vec3 a, struct vec3 b);
static struct vec3 stc_sub3(struct vec3 a, struct vec3 b);
static struct vec3 stc_mul3(struct vec3 a, struct vec3 b);
static struct vec3 stc_scale3(struct vec3 v, f32 s);
static f32  stc_dot3(struct vec3 a, struct vec3 b);
static struct vec3 stc_cross3(struct vec3 a, struct vec3 b);
static f32  stc_len3(struct vec3 v);
static struct vec3 stc_norm3(struct vec3 v);
static struct vec3 stc_lerp3(struct vec3 a, struct vec3 b, f32 t);
static struct vec4 stc_add4(struct vec4 a, struct vec4 b);
static struct vec4 stc_scale4(struct vec4 v, f32 s);
static struct vec4 stc_lerp4(struct vec4 a, struct vec4 b, f32 t);

static struct mat4 stc_mat4_identity(void);
static struct mat4 stc_mat4_mul(struct mat4 a, struct mat4 b);
static struct mat4 stc_mat4_translate(struct vec3 t);
static struct mat4 stc_mat4_scale(struct vec3 s);
static struct mat4 stc_mat4_rotate_z(f32 angle);
static struct mat4 stc_mat4_ortho(f32 l, f32 r, f32 b, f32 t, f32 n, f32 f);
static f32 stc_smoothstep(f32 edge0, f32 edge1, f32 x);
static f32 stc_step(f32 edge, f32 x);
static f32 stc_deg_to_rad(f32 deg);
static f32 stc_rad_to_deg(f32 rad);

static inline bool is_prime(u64 n);
static inline u64 next_prime(u64 n);
static inline bool is_pow2(u64 n);
static inline u64 next_pow2(u64 n);
static inline bool f32_is_nan(f32 n);
static inline f32 minf(f32 a, f32 b);
static inline f32 maxf(f32 a, f32 b);

inline bool f32_is_nan(f32 f)
{
	union {u32 u; f32 f;} x;
	x.f = f;
	return  ((x.u & EXPONENTF32) == EXPONENTF32) && ((x.u & MANTISSAF32) != 0);
}

inline bool is_prime(u64 n) {
	if (n < 2) return false;
	if ((n & 1) == 0) return n == 2;
	for (u64 i = 3; i * i <= n; i += 2)
		if (n % i == 0) return false;
	return true;
}

inline u64 next_prime(u64 n) {
	if (n <= 2) return 2;
	if ((n & 1) == 0) n++;
	while (!is_prime(n)) n += 2;
	return n;
}

inline bool is_pow2(u64 n)
{
	return (n != 0) && (n & (n-1)) == 0;
}

inline u64 next_pow2(u64 n)
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


inline f32 minf(f32 a, f32 b)
{
	return (a < b) ? a : b;
}

inline f32 maxf(f32 a, f32 b)
{
	return (a > b) ? a : b;
}


f32 stc_rsqrt_f32(f32 number)
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

f32 stc_sqrt_f32(f32 x)
{
	return x * stc_rsqrt_f32(x);
}

struct vec2 stc_sub2(struct vec2 a, struct vec2 b)
{
	return (struct vec2){a.x - b.x, a.y - b.y};
}

struct vec2 stc_add2(struct vec2 a, struct vec2 b)
{
	return (struct vec2){a.x + b.x, a.y + b.y};
}
struct vec2 stc_scale2(struct vec2 v, f32 s)
{
	return (struct vec2){v.x *s, v.y * s};
}

f32 stc_len2(struct vec2 v)
{
	return stc_sqrt_f32((v.x * v.x) + (v.y * v.y));
}

struct vec2 stc_norm2(struct vec2 v)
{
	f32 len = stc_len2(v);
	if (len == 0.0f) return (struct vec2){0};

	return (struct vec2){ v.x / len, v.y / len };
}




