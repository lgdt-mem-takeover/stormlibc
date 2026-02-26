#pragma once
#include "../stormc_header.h"



/*
Implementation derived from XXHASH Spec
https://fossies.org/linux/xxHash/doc/xxhash_spec.md
Only tested on x86-64 ISA;
*/


#define XXH_PRIME64_1 0x9E3779B185EBCA87ULL
#define XXH_PRIME64_2 0xC2B2AE3D27D4EB4FULL
#define XXH_PRIME64_3 0x165667B19E3779F9ULL
#define XXH_PRIME64_4 0x85EBCA77C2B2AE63ULL
#define XXH_PRIME64_5 0x27D4EB2F165667C5ULL


typedef u64 v4u64 __attribute__((vector_size(32)));

thisfile u64 stc_rotateleft64(u64 value, u64 shift)
{
	return (value << shift) | (value >> (64 - shift));
}

thisfile inline u64 stormc_hash_scalar(struct hash_params params)
{
	u64 seed = params.seed;
	const void *value = params.data;
	u64 len = params.len;

	u64 idx, hash, acc0, acc1, acc2, acc3;
	u64 input0, input1, input2, input3;
	u8 byte;


	acc0 = seed + XXH_PRIME64_1 + XXH_PRIME64_2;
	acc1 = seed + XXH_PRIME64_2;
	acc2 = seed;
	acc3 = seed - XXH_PRIME64_1;
	u8 *ptr = (u8*)value;

	for (idx = 0; idx + 32 < len; idx += 32){
		input0 = *(u64*)(ptr + idx + 0);
		input1 = *(u64*)(ptr + idx + 8);
		input2 = *(u64*)(ptr + idx + 16);
		input3 = *(u64*)(ptr + idx + 24);

		acc0 += input0 * XXH_PRIME64_2;
		acc0 = stc_rotateleft64(acc0, 31);
		acc0 *= XXH_PRIME64_1;

		acc1 += input1 * XXH_PRIME64_2;
		acc1 = stc_rotateleft64(acc1, 31);
		acc1 *= XXH_PRIME64_1;

		acc2 += input2 * XXH_PRIME64_2;
		acc2 = stc_rotateleft64(acc2, 31);
		acc2 *= XXH_PRIME64_1;

		acc3 += input3 * XXH_PRIME64_2;
		acc3 = stc_rotateleft64(acc3, 31);
		acc3 *= XXH_PRIME64_1;
	}
	hash = stc_rotateleft64(acc0, 1) +
		stc_rotateleft64(acc1, 7) +
		stc_rotateleft64(acc2, 12) +
		stc_rotateleft64(acc3, 18);

	for (u64 i = idx; i < len; i++){
		u8 byte = *(u8*)(ptr + i);

		hash ^= byte * XXH_PRIME64_5;
		hash = stc_rotateleft64(hash, 11);
		hash *= XXH_PRIME64_1;
	}
	hash ^= hash >> 33;
	hash *= XXH_PRIME64_2;
	hash ^= hash >> 29;
	hash *= XXH_PRIME64_3;
	hash ^= hash >> 32;

	return hash;
}

thisfile inline v4u64 stormc_rotl64_v4u64(v4u64 x, u32 bits)
{
	return (x <<  bits) | (x >> (64 - bits));
}


thisfile inline u64 stormc_hash_v4u64(struct hash_params params)
{
	u64 seed = params.seed;
	const void *value = params.data;
	u64 len = params.len;
	u64 idx;

	v4u64 acc = {
		seed + XXH_PRIME64_1 + XXH_PRIME64_2,
		seed + XXH_PRIME64_2,
		seed,
		seed - XXH_PRIME64_1
	};

	u8 *ptr = (u8*)value;
	for (idx = 0; idx + 32 < len; idx += 32){
		v4u64 input = *(v4u64*)(ptr + idx);

		acc += input * XXH_PRIME64_2;
		acc = stormc_rotl64_v4u64(acc, 31);
		acc *= XXH_PRIME64_1;
	}

	u64 acc0 = acc[0];
	u64 acc1 = acc[1];
	u64 acc2 = acc[2];
	u64 acc3 = acc[3];

	u64 hash = stc_rotateleft64(acc0, 1) +
		stc_rotateleft64(acc1, 7) +
		stc_rotateleft64(acc2, 12) +
		stc_rotateleft64(acc3, 18);

	for (u64 i = idx; i < len; i++){
		u8 byte = *(u8*)(ptr + i);

		hash ^= byte * XXH_PRIME64_5;
		hash = stc_rotateleft64(hash, 11);
		hash *= XXH_PRIME64_1;
	}


	hash ^= hash >> 33;
	hash *= XXH_PRIME64_2;
	hash ^= hash >> 29;
	hash *= XXH_PRIME64_3;
	hash ^= hash >> 32;

	return hash;
}



