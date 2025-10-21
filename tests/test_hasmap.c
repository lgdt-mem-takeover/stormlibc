#pragma once
#include "storm.h"
#include "stormc_hash.h"

typedef struct Vec2 Vec2;

struct Vec2{
	f64 x, y;
};



static inline bool eq_int(int a, int b)
{
	return a == b;
}

static inline u64 hash_string(String key)
{
	u64 result;
	if (key.len >= 64){
		result = stormc_hash_v4u64(key.str, key.len);
		return result;
	}
	result = stormc_hash_scalar(key.str, key.len);
	return result;
}

static inline u64 hash_int(int key)
{
	u64 result;
	if (sizeof(key) >= 64){
		result = stormc_hash_v4u64(&key, sizeof(key));
		return result;
	}
	result = stormc_hash_scalar(&key, sizeof(key));
	return result;
}

static inline bool cmp_str(String target, String prob)
{
	if (target.len != prob.len) return false;

	for (u32 idx = 0; idx < target.len; idx++){
		if (target.str[idx] != prob.str[idx]) return false;
	}

	return true;
}

STORMC_MAKE_HMAP(str_to_u8, String, u8, 6, cmp_str, hash_string)
STORMC_MAKE_HMAP(int_to_vec2, int, Vec2, 6, eq_int, hash_int)

int main(void)
{
	str_to_u8 *hmap = stormc_emit_str_to_u8();
	String key = STR("Storm");
	u8 value = 69;

	int_to_vec2 *intmap = stormc_emit_int_to_vec2();

	stormc_int_to_vec2_add_entry(intmap, 2345, (Vec2){69, 420});

	printf("=== Duplicate key overwrite ===\n");
	stormc_str_to_u8_add_entry(hmap, STR("Storm"), 100);
	u8 result2 = stormc_str_to_u8_get(hmap, STR("Storm"));
	printf("Expected 100, got %u\n", result2);


	printf("\n=== Missing key ===\n");
	u8 missing = stormc_str_to_u8_get(hmap, STR("Nonexistent"));
	printf("Expected 0, got %u\n", missing);


	printf("\n=== Collision handling ===\n");


	for (int i = 0; i < 1000000; i++){
		String this;
		this.str = malloc(16);
		this.len = sprintf(this.str,"Key#%d", i);
		this.str[this.len] = '\0';

		stormc_str_to_u8_add_entry(hmap, this, (u8)i);
	}


	for (int i = 0; i < 1000000; i++) {
		String this;
		this.str = malloc(16);
		this.len = sprintf(this.str,"Key#%d", i);
		this.str[this.len] = '\0';
		u8 val = stormc_str_to_u8_get(hmap, this);
		if (val != (u8)i)
		printf("Mismatch: Key%d got %u\n", i, val);
	}


	return 0;
}
