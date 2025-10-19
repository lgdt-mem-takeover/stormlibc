#pragma once
#include "storm.h"
#include "stormc_hash.h"
#include "stormc_hashmap.h"
#include "stormc_runtime.c"
#include <time.h>

typedef struct Vec2 Vec2;

struct Vec2{
	f64 x, y;
};

static inline bool eq_int(int a, int b)
{
	return a == b;
}

STORMC_MAKE_HMAP(str_to_u8, String, u8, 6, sstrcmpx, stormc_hash_v4u64)
STORMC_MAKE_HMAP(int_to_vec2, int, Vec2, 6, eq_int, stormc_hash_v4u64)

int main(void)
{
	str_to_u8 *hmap = stormc_emit_str_to_u8();
	String key = STR("Storm");
	u8 value = 69;
	stormc_str_to_u8_add_entry(hmap, key, value);
	u8 result = stormc_str_to_u8_get(hmap, key);
	printf("%u\n", result);


	int_to_vec2 *intmap = stormc_emit_int_to_vec2();
	Vec2 vec2 = {420.69, 69.420};
	int kint = 12394;
	stormc_int_to_vec2_add_entry(intmap, kint, vec2);
	Vec2 res = stormc_int_to_vec2_get(intmap, kint);
	printf("%f %f\n", res.x, res.y);
	return 0;
}
