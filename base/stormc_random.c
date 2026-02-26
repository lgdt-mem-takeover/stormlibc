#pragma once
#include "../stormc_header.h"

global_persist u64 state = __TIME__[7] | __COUNTER__;

u64 stormc_random_xorshift(u64 init_state)
{
	if (init_state == 0)
		init_state = state;

	u64 pl;
	init_state ^= init_state << 13;
	init_state ^= init_state >> 7;
	init_state ^= init_state << 17;
	pl = state = init_state;


	return pl;
}

u64 stormc_random(u64 init_state)
{
	return stormc_random_xorshift(init_state);
}

u64 stormc_random_range(u64 min, u64 max, u64 init_state)
{
	if (init_state == 0)
		init_state = state;

	u64 pl;

	pl = stormc_random(init_state);

	pl = min + (pl % (max - min + 1));

	return pl;
}


