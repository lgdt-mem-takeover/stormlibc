#pragma once
#include "../stormc_header.h"


u64 stormc_diceroll(u64 count, u64 sides)
{
	u64 idx, pl;

	pl = 0;
	for (idx = 0; idx < count; idx++){
		pl += stormc_random_range(1, sides, 0);
	}

	return pl;
}
