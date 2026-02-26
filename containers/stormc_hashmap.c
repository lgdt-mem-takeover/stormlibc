#pragma once
#include "../core/stormc_types.h"
#include "../math/stormc_math.h"
#include "../core/stormc_allocator.h"
#include "stormc_hash.h"

#define NO_FREE_SLOT (1lu << 63)
#define KEY_NOT_FOUND (1lu << 62)




//TODO: Since I changed the allocator, I need to adjust this.


typedef enum{
	FREE,
	TOMBSTONE,
	OCCUPIED,
}StormC_HashMap_State;


#define STORMC_MAKE_HMAP(NAME, TYPE_KEY, TYPE_VALUE, SENTINEL_VALUE, STARTING_SIZE, CMP_FN, HASH_FN, LOAD_FACTOR)	\
	typedef struct NAME NAME;									\
	struct NAME{											\
	 	StormC_HashMap_State	*state;								\
	 	TYPE_KEY		*key;								\
	 	TYPE_VALUE		*value;								\
	 	u64    ct_elems;									\
	 	u64    capacity;									\
	};												\
	thisfile void stormc_##NAME##_add_entry(NAME *hmap, TYPE_KEY key, TYPE_VALUE value);		\
	thisfile inline bool stormc_##NAME##_has_key(NAME *hmap, TYPE_KEY key)				\
	{												\
		u64 i, idx;										\
		bool exists = false;									\
		u64 hash = HASH_FN(key);								\
		u64 hash_id = hash & (hmap->capacity - 1);						\
		for (i = 0; i < hmap->capacity; i++){							\
			idx = (hash_id + i) & (hmap->capacity - 1);					\
			if (CMP_FN(hmap->key[idx], key)){						\
				return true;								\
			}										\
		}											\
		return exists;										\
	}												\
													\
	thisfile void stormc_##NAME##_expand(NAME *hmap)						\
	{												\
		u64 old_cap = hmap->capacity;								\
		u64 new_cap = old_cap * 2;								\
		StormC_HashMap_State *old_state = hmap->state;						\
		TYPE_KEY *old_keys = hmap->key;								\
		TYPE_VALUE *old_values = hmap->value;							\
													\
		StormC_HashMap_State *new_state =							\
		(StormC_HashMap_State *)STORMC_ALLOC(sizeof(*new_state) * new_cap);			\
		TYPE_KEY *new_keys = (TYPE_KEY *)STORMC_ALLOC(sizeof(*new_keys) * new_cap);		\
		TYPE_VALUE *new_values =								\
		(TYPE_VALUE *)STORMC_ALLOC(sizeof(*new_values) * new_cap);				\
		hmap->state = new_state;								\
		hmap->key = new_keys;									\
		hmap->value = new_values;								\
		hmap->capacity = new_cap;								\
		hmap->ct_elems = 0;									\
		for (u64 idx = 0; idx < old_cap; idx++){						\
			if (old_state[idx] == OCCUPIED){						\
			stormc_##NAME##_add_entry(hmap, old_keys[idx], old_values[idx]);		\
			}										\
		}											\
		stormc_free(old_state);									\
		stormc_free(old_keys);									\
		stormc_free(old_values);								\
	}												\
													\
	thisfile void stormc_##NAME##_add_entry(NAME *hmap, TYPE_KEY key, TYPE_VALUE value)		\
	{												\
		u64 new_idx;										\
		u64 hash = HASH_FN(key);								\
		u64 hash_id = hash & (hmap->capacity - 1);						\
		u64 i = 0;										\
		while (i < hmap->capacity){								\
			new_idx = (hash_id + i) & (hmap->capacity - 1);					\
			if (hmap->state[new_idx] == FREE){						\
				hmap->key[new_idx] = key;						\
				hmap->value[new_idx] = value;						\
				hmap->state[new_idx] = OCCUPIED;					\
				hmap->ct_elems++;							\
				break;									\
			}										\
			if (hmap->state[new_idx] == OCCUPIED &&						\
			    CMP_FN(hmap->key[new_idx], key)){						\
				hmap->value[new_idx] = value;						\
				break;									\
			}										\
			i++;										\
		}											\
		if (hmap->ct_elems >= (hmap->capacity * LOAD_FACTOR)){					\
			stormc_##NAME##_expand(hmap);							\
													\
		}											\
	}												\
	thisfile TYPE_VALUE stormc_##NAME##_get(NAME *hmap, TYPE_KEY key)				\
	{												\
		u64 hash = HASH_FN(key);								\
		u64 hash_id = hash & (hmap->capacity - 1);						\
		u64 i = 0;										\
		while (i < hmap->capacity){								\
			u64 idx = (hash_id + i) & (hmap->capacity - 1);					\
			if (CMP_FN(hmap->key[idx], key) && hmap->state[idx] == OCCUPIED) {		\
				return hmap->value[idx];						\
			}										\
			i++;										\
		}											\
		return SENTINEL_VALUE;									\
	}												\
	thisfile NAME *stormc_emit_##NAME(void)								\
	{												\
		u64 starting_size = STARTING_SIZE;							\
		bool size_is_pow2 = is_pow2(starting_size);						\
		u64 nextpow2 = next_pow2(starting_size);						\
		starting_size = SELECT(size_is_pow2, starting_size, nextpow2);				\
		NAME *pl = (NAME *)STORMC_ALLOC(sizeof(NAME));						\
		pl->state =										\
		(StormC_HashMap_State*)STORMC_ALLOC(							\
		sizeof(StormC_HashMap_State) * starting_size);						\
		pl->key = (TYPE_KEY*)STORMC_ALLOC(sizeof(TYPE_KEY) * starting_size);			\
		pl->value = (TYPE_VALUE*)STORMC_ALLOC(sizeof(TYPE_VALUE) * starting_size);		\
		pl->capacity = starting_size;								\
		pl->ct_elems = 0;									\
		return pl;										\
	}												\
