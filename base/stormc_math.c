#pragma once

#include "../stormc_header.h"

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


