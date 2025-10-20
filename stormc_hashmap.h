#pragma once
#include "storm.h"
#include <string.h>
#include "stormc_hash.h"

#define COLL_RES_TABLE_SIZE 1 << 12
#define NO_FREE_SLOT (1lu << 63)
#define KEY_NOT_FOUND (1lu << 62)
typedef enum StormC_HashMap_State StormC_HashMap_State;







enum StormC_HashMap_State{
	FREE,
	TOMBSTONE,
	OCCUPIED,
};


#define STORMC_MAKE_HMAP(NAME, TYPE_KEY, TYPE_VALUE, STARTING_SIZE, CMP_FN, HASH_FN)		\
	typedef struct NAME NAME;								\
	struct NAME{										\
	 	StormC_HashMap_State	*state;							\
	 	TYPE_KEY		*key;							\
	 	TYPE_VALUE		*value;							\
	 	u64    ct_elems;								\
	 	u64    capacity;								\
	};											\
	thisfile void stormc_##NAME##_add_entry(NAME *hmap, TYPE_KEY key, TYPE_VALUE value);	\
	thisfile inline bool stormc_##NAME##_has_key(NAME *hmap, TYPE_KEY key)			\
	{											\
		u64 i, idx, cur_hash_id;							\
		bool exists = false;								\
		u64 hash = HASH_FN(key);							\
		u64 hash_id = hash % hmap->capacity;						\
		u64 step = 1 | (hash >> 16);							\
		for (i = 0; i < hmap->capacity; i++){						\
			idx = (hash_id + i) % hmap->capacity;					\
			if (CMP_FN(hmap->key[idx], key)){					\
				return true;							\
			}									\
		}										\
		return exists;									\
	}											\
												\
	thisfile void stormc_##NAME##_expand(NAME *hmap)					\
	{											\
		u64 old_cap = hmap->capacity;							\
		u64 new_cap = old_cap * 2;							\
		StormC_HashMap_State *old_state = hmap->state;					\
		TYPE_KEY *old_keys = hmap->key;							\
		TYPE_VALUE *old_values = hmap->value;						\
												\
		StormC_HashMap_State *new_state =						\
		(StormC_HashMap_State *)stormc_alloc(sizeof(*new_state) * new_cap);		\
		TYPE_KEY *new_keys = (TYPE_KEY *)stormc_alloc(sizeof(*new_keys) * new_cap);	\
		TYPE_VALUE *new_values =							\
		(TYPE_VALUE *)stormc_alloc(sizeof(*new_values) * new_cap);			\
		hmap->state = new_state;							\
		hmap->key = new_keys;								\
		hmap->value = new_values;							\
		hmap->capacity = new_cap;							\
		hmap->ct_elems = 0;								\
		for (u64 idx = 0; idx < old_cap; idx++){					\
			if (old_state[idx] == OCCUPIED){					\
			stormc_##NAME##_add_entry(hmap, old_keys[idx], old_values[idx]);	\
			}									\
		}										\
		stormc_free(old_state, sizeof(*old_state) * old_cap);				\
		stormc_free(old_keys, sizeof(*old_keys) * old_cap);				\
		stormc_free(old_values, sizeof(*old_values) * old_cap);				\
	}											\
												\
	thisfile void stormc_##NAME##_add_entry(NAME *hmap, TYPE_KEY key, TYPE_VALUE value)	\
	{											\
		u64 new_idx;									\
		u64 hash = HASH_FN(key);							\
		u64 hash_id = hash % hmap->capacity;						\
		u64 step = 1 | (hash >> 16);							\
		u64 i = 0;									\
		while (i < hmap->capacity){							\
			new_idx = (hash_id + i) % hmap->capacity;				\
			if (hmap->state[new_idx] == FREE){					\
				hmap->key[new_idx] = key;					\
				hmap->value[new_idx] = value;					\
				hmap->state[new_idx] = OCCUPIED;				\
				hmap->ct_elems++;						\
				break;								\
			}									\
			if (hmap->state[new_idx] == OCCUPIED &&					\
			    CMP_FN(hmap->key[new_idx], key)){					\
				hmap->value[new_idx] = value;					\
				break;								\
			}									\
			i++;									\
		}										\
		if (hmap->ct_elems >= (hmap->capacity * 0.70)){					\
			stormc_##NAME##_expand(hmap);						\
												\
		}										\
	}											\
	thisfile TYPE_VALUE stormc_##NAME##_get(NAME *hmap, TYPE_KEY key)			\
	{											\
		TYPE_VALUE empty_stub = {};							\
		u64 hash = HASH_FN(key);							\
		u64 hash_id = hash % hmap->capacity;						\
		u64 step = 1 | (hash >> 16);							\
		u64 i = 0;									\
		while (i < hmap->capacity){							\
			u64 idx = (hash_id + i) % hmap->capacity;				\
			if (CMP_FN(hmap->key[idx], key) && hmap->state[idx] == OCCUPIED) {	\
				return hmap->value[idx];					\
			}									\
			i++;									\
		}										\
		return empty_stub;								\
	}											\
	thisfile NAME *stormc_emit_##NAME(void)							\
	{											\
		u64 starting_size = STARTING_SIZE;						\
		NAME *pl = (NAME *)stormc_alloc(sizeof(NAME));					\
		pl->state =									\
		(StormC_HashMap_State*)stormc_alloc(						\
		sizeof(StormC_HashMap_State) * starting_size);					\
		pl->key = (TYPE_KEY*)stormc_alloc(sizeof(TYPE_KEY) * starting_size);		\
		pl->value = (TYPE_VALUE*)stormc_alloc(sizeof(TYPE_VALUE) * starting_size);	\
		pl->capacity = starting_size;							\
		pl->ct_elems = 0;								\
		return pl;									\
	}											\
