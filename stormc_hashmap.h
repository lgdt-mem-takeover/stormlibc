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

static inline bool is_power_of_2(u64 n)
{
	return (n != 0) && (n & (n-1)) == 0;
}
static inline u64 next_power_of_2(u64 n)
{
	n--;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	n |= n >> 32;
	n++;
	return n;
}

#define STORMC_MAKE_HMAP(NAME, TYPE_KEY, TYPE_VALUE, STARTING_SIZE, CMP_FN, HASH_FN)		\
	typedef struct NAME NAME;								\
	struct NAME{										\
	 	StormC_HashMap_State	*state;							\
	 	TYPE_KEY		*key;							\
	 	TYPE_VALUE		*value;							\
	 	u64    ct_elems;								\
	 	u64    capacity;								\
	};											\
	thisfile inline bool stormc_##NAME##_has_key(NAME *hmap, TYPE_KEY key)			\
	{											\
		u64 idx, cur_hash_id;								\
		bool exists = false;								\
		for (idx = 0; idx < hmap->capacity; idx++){					\
			if (CMP_FN(hmap->key[idx], key)){					\
				return true;							\
			}									\
		}										\
		return exists;									\
	}											\
	thisfile NAME *stormc_##NAME##_expand(NAME *hmap)					\
	{											\
		u8 *temp;									\
		u64 cur_elements = hmap->ct_elems;						\
		size_t old_size = hmap->capacity;						\
		size_t new_size = hmap->capacity * 2;						\
		u64 offset = 0;									\
		size_t old_size_state = sizeof(StormC_HashMap_State) * old_size;		\
		size_t old_size_keys = sizeof(TYPE_KEY) * old_size;				\
		size_t old_size_values = sizeof(TYPE_VALUE) * old_size;				\
		size_t old_size_final = old_size_state + old_size_keys + old_size_values;	\
		size_t new_size_state = sizeof(StormC_HashMap_State) * new_size;		\
		size_t new_size_keys = sizeof(TYPE_KEY) * new_size;				\
		size_t new_size_values = sizeof(TYPE_VALUE) * new_size;				\
		size_t new_size_final = new_size_state + new_size_keys + new_size_values;	\
		temp = (u8*)stormc_alloc(new_size_final);					\
		memcpy(temp, hmap->state, old_size_state);					\
		memcpy(temp + new_size_state, hmap->key, old_size_keys);			\
		memcpy(temp + new_size_state + new_size_keys, hmap->value, old_size_values);	\
		munmap(hmap, old_size_final);							\
		hmap = (NAME*)temp;								\
		hmap->state = (StormC_HashMap_State*)(temp + offset);				\
		offset += new_size_state;							\
		hmap->key = (TYPE_KEY*)(temp + offset);						\
		offset += new_size_keys;							\
		hmap->value = (TYPE_VALUE*)(temp + offset);					\
		offset += new_size_values;							\
		hmap->capacity = new_size;							\
		hmap->ct_elems = cur_elements;							\
		return hmap;									\
	}											\
	thisfile void stormc_##NAME##_add_entry(NAME *hmap, TYPE_KEY key, TYPE_VALUE value)	\
	{											\
		u64 hash_id = HASH_FN(&key, sizeof(TYPE_KEY)) & (hmap->capacity - 1);	\
		bool key_exists = false;							\
		if (hmap->state[hash_id] == OCCUPIED){						\
			key_exists = true;							\
		}										\
		if (key_exists){								\
			u64 i = 1;								\
			u64 new_idx = (hash_id + i * i) & (hmap->capacity - 1);			\
			while (hmap->state[new_idx] == OCCUPIED && i < hmap->capacity){		\
				new_idx = (hash_id + i * i) & (hmap->capacity - 1);		\
				i++;								\
			}									\
			if (i >= hmap->capacity){						\
				stormc_##NAME##_expand(hmap);					\
				i = 1;								\
				new_idx = (hash_id + i * i) & (hmap->capacity - 1);		\
				while (hmap->state[new_idx] == OCCUPIED){			\
					i++;							\
					new_idx = (hash_id + i * i) & (hmap->capacity - 1);	\
				}								\
			}									\
			hmap->key[new_idx] = key;						\
			hmap->value[new_idx] = value;						\
			hmap->state[new_idx] = OCCUPIED;					\
			hmap->ct_elems++;							\
		}										\
		if (!key_exists){								\
			hmap->key[hash_id] = key;						\
			hmap->value[hash_id] = value;						\
			hmap->state[hash_id] = OCCUPIED;					\
			hmap->ct_elems++;							\
		}										\
	}											\
	thisfile TYPE_VALUE stormc_##NAME##_get(NAME *hmap, TYPE_KEY key)			\
	{											\
		TYPE_VALUE empty_stub = {};							\
		u64 hash_id = HASH_FN(&key, sizeof(TYPE_KEY)) & (hmap->capacity - 1);		\
		u64 i = 0;									\
		while (hmap->state[hash_id] == OCCUPIED){					\
			if (CMP_FN(hmap->key[hash_id], key)) return hmap->value[hash_id];	\
			i++;									\
			hash_id = (hash_id + i * i) & (hmap->capacity - 1);			\
		}										\
		return empty_stub;								\
	}											\
	thisfile NAME *stormc_emit_##NAME(void)							\
	{											\
		u64 starting_size = STARTING_SIZE;						\
		if (!is_power_of_2(STARTING_SIZE)){						\
			starting_size = next_power_of_2(STARTING_SIZE);				\
		}										\
		size_t size_final, size_key, size_value, size_state;				\
		u64 offset;									\
		size_state = sizeof(StormC_HashMap_State) * starting_size;			\
		size_key = sizeof(TYPE_KEY) * starting_size;					\
		size_value =  sizeof(TYPE_VALUE) * starting_size;				\
		size_final = size_key + size_value + starting_size;				\
		NAME *pl =									\
		(NAME*)stormc_alloc(sizeof(NAME) + size_final);					\
		offset = sizeof(NAME);								\
		pl->state = (StormC_HashMap_State*)((u8*)pl + offset);				\
		offset += size_state;								\
		pl->key = (TYPE_KEY*)((u8*)pl + offset);					\
		offset += size_key;								\
		pl->value = (TYPE_VALUE*)((u8*)pl + offset);					\
		offset += size_value;								\
		pl->capacity = STARTING_SIZE;							\
		pl->ct_elems = 0;								\
		return pl;									\
	}											\
