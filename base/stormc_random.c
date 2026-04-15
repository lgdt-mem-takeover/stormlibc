#pragma once
#include "../stormc_header.h"
#include <stdint.h>

#if defined(__x86_64__) || defined(__i386__)
#include <immintrin.h>
#define STC_X86 1
#else
#define STC_X86 0
#endif

global_persist u64 state = 0;



#if STC_X86 && (defined(__GNUC__) || defined(__clang__))
__attribute__((target("rdseed")))
static int stc_try_rdseed64(u64 *out)
{
	unsigned long long v;
	if (_rdseed64_step(&v)) {
		*out = (u64)v;
		return 1;
	}
	return 0;
}

__attribute__((target("rdrnd")))
static int stc_try_rdrand64(u64 *out)
{
	unsigned long long v;
	if (_rdrand64_step(&v)) {
		*out = (u64)v;
		return 1;
	}
	return 0;
}
#endif

static int stc_get_hw_seed64(u64 *out)
{
#if STC_X86 && (defined(__GNUC__) || defined(__clang__))
	if (__builtin_cpu_supports("rdseed")) {
		for (int i = 0; i < 32; ++i)
			if (stc_try_rdseed64(out))
				return 1;
	}

	if (__builtin_cpu_supports("rdrnd")) {
		for (int i = 0; i < 16; ++i)
			if (stc_try_rdrand64(out))
				return 1;
	}
#endif

	return 0;
}




void stc_random_seed(u64 seed)
{
	if (seed == 0) {
		if (!stc_get_hw_seed64(&state)) {
			state = 88172645463325252ull;
		}
	} else {
		state = seed;
	}
}

u64 stc_random_xorshift(void)
{
	if (unlikely(state == 0)) {
		stc_random_seed(0);
	}

	state ^= state << 13;
	state ^= state >> 7;
	state ^= state << 17;


	return state;
}


u64 stc_random_range(u64 min, u64 max)
{
	u64 pl;

	pl = min + (stc_random_xorshift() % (max - min + 1));

	return pl;
}


u64 stc_diceroll(u64 count, u64 sides)
{
	u64 idx, pl;

	pl = 0;
	for (idx = 0; idx < count; idx++){
		pl += stc_random_range(1, sides);
	}

	return pl;
}
