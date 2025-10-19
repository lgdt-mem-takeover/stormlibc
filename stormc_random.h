#pragma once
#include "storm.h"

global_persist uint_fast64_t state = __TIME__[7] | __COUNTER__;

thisfile inline u64 stormc_random_xorshift(void)
{
	u64 pl;
	state ^= state << 13;
	state ^= state >> 7;
	state ^= state << 17;
	pl = state;

	return pl;
}


thisfile inline u64 stormc_random_range(u64 min, u64 max)
{
	u64 pl;

	pl = stormc_random_xorshift();

	pl = min + (pl % (max - min + 1));

	return pl;
}
