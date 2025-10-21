#include "../core/stormc_random.h"
#include "../core/stormc_types.h"


thisfile inline u64 stormc_roll(u64 dice_count, u64 dice_sides)
{
	u64 pl, idx;

	pl = 0;
	for (idx = 0; idx < dice_count; idx++){
		pl += stormc_random_range(1, dice_sides);
	}
	return pl;
}

