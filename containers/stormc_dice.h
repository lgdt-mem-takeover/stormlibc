#pragma once
#include "../core/stormc_random.h"


thisfile u64 stormc_diceroll(u64 count, u64 sides)
{
	u64 idx, pl;

	pl = 0;
	for (idx = 0; idx < count; idx++){
		pl += stormc_random_range(1, sides);
	}

	return pl;
}
