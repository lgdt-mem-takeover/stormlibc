#pragma once
#include "../stormc_header.h"

/**
 *  XXH64 implementation derived from the official xxHash specification:
 *  - XXH64 algorithm description
 *  - little-endian reads
 *  - 32-byte stripe path
 *  - short-input path for len < 32
 *  - merge rounds
 *  - length addition
 *  - 8/4/1-byte tail handling
 *
 * Reference:
 * https://github.com/Cyan4973/xxHash/blob/dev/doc/xxhash_spec.md
**/

#define XXH_PRIME64_1 0x9E3779B185EBCA87ULL
#define XXH_PRIME64_2 0xC2B2AE3D27D4EB4FULL
#define XXH_PRIME64_3 0x165667B19E3779F9ULL
#define XXH_PRIME64_4 0x85EBCA77C2B2AE63ULL
#define XXH_PRIME64_5 0x27D4EB2F165667C5ULL

thisfile inline u64 stc_rotateleft64(u64 value, u32 shift)
{
	return (value << shift) | (value >> (64 - shift));
}

/**
 *  Portable little-endian loads.
 *  Avoids type-punning / alignment UB from direct casts like *(u64 *)ptr.
**/
thisfile inline u32 stc_read32_le(const void *src)
{
	const u8 *p = (const u8 *)src;
	return ((u32)p[0]      ) |
		((u32)p[1] <<  8) |
		((u32)p[2] << 16) |
		((u32)p[3] << 24);
}

thisfile inline u64 stc_read64_le(const void *src)
{
	const u8 *p = (const u8 *)src;
	return ((u64)p[0]      ) |
		((u64)p[1] <<  8) |
		((u64)p[2] << 16) |
		((u64)p[3] << 24) |
		((u64)p[4] << 32) |
		((u64)p[5] << 40) |
		((u64)p[6] << 48) |
		((u64)p[7] << 56);
}

thisfile inline u64 stc_xxh64_round(u64 acc, u64 input)
{
	acc += input * XXH_PRIME64_2;
	acc = stc_rotateleft64(acc, 31);
	acc *= XXH_PRIME64_1;
	return acc;
}

thisfile inline u64 stc_xxh64_merge_round(u64 hash, u64 acc)
{
	acc = stc_xxh64_round(0, acc);
	hash ^= acc;
	hash = hash * XXH_PRIME64_1 + XXH_PRIME64_4;
	return hash;
}

thisfile inline u64 stc_xxh64_avalanche(u64 hash)
{
	hash ^= hash >> 33;
	hash *= XXH_PRIME64_2;
	hash ^= hash >> 29;
	hash *= XXH_PRIME64_3;
	hash ^= hash >> 32;
	return hash;
}

thisfile inline u64 stormc_hash_scalar(struct hash_params params)
{
	if (params.data == NULL && params.len == 0) {
		u64 hash = params.seed + XXH_PRIME64_5;
		return stc_xxh64_avalanche(hash);
	}
	const u8 *ptr = (const u8 *)params.data;
	u64 len = params.len;
	u64 seed = params.seed;

	const u8 *p = ptr;
	const u8 *const end = ptr + len;
	u64 hash;

	if (len >= 32) {
		const u8 *const limit = end - 32;

		u64 acc0 = seed + XXH_PRIME64_1 + XXH_PRIME64_2;
		u64 acc1 = seed + XXH_PRIME64_2;
		u64 acc2 = seed + 0;
		u64 acc3 = seed - XXH_PRIME64_1;

		do {
			acc0 = stc_xxh64_round(acc0, stc_read64_le(p + 0));
			acc1 = stc_xxh64_round(acc1, stc_read64_le(p + 8));
			acc2 = stc_xxh64_round(acc2, stc_read64_le(p + 16));
			acc3 = stc_xxh64_round(acc3, stc_read64_le(p + 24));
			p += 32;
		} while (p <= limit);

		hash =
			stc_rotateleft64(acc0, 1) +
			stc_rotateleft64(acc1, 7) +
			stc_rotateleft64(acc2, 12) +
			stc_rotateleft64(acc3, 18);

		hash = stc_xxh64_merge_round(hash, acc0);
		hash = stc_xxh64_merge_round(hash, acc1);
		hash = stc_xxh64_merge_round(hash, acc2);
		hash = stc_xxh64_merge_round(hash, acc3);
	}
	else {
		hash = seed + XXH_PRIME64_5;
	}

	hash += len;

	while ((p + 8) <= end) {
		u64 k1 = stc_read64_le(p);
		k1 *= XXH_PRIME64_2;
		k1 = stc_rotateleft64(k1, 31);
		k1 *= XXH_PRIME64_1;
		hash ^= k1;
		hash = stc_rotateleft64(hash, 27) * XXH_PRIME64_1 + XXH_PRIME64_4;
		p += 8;
	}

	if ((p + 4) <= end) {
		hash ^= (u64)stc_read32_le(p) * XXH_PRIME64_1;
		hash = stc_rotateleft64(hash, 23) * XXH_PRIME64_2 + XXH_PRIME64_3;
		p += 4;
	}

	while (p < end) {
		hash ^= (u64)(*p) * XXH_PRIME64_5;
		hash = stc_rotateleft64(hash, 11) * XXH_PRIME64_1;
		++p;
	}

	return stc_xxh64_avalanche(hash);
}

typedef u64 v4u64 __attribute__((vector_size(32)));

thisfile inline v4u64 stormc_rotl64_v4u64(v4u64 x, u32 bits)
{
	return (x << bits) | (x >> (64 - bits));
}

thisfile inline u64 stormc_hash_v4u64(struct hash_params params)
{
	if (params.data == NULL && params.len == 0) {
		u64 hash = params.seed + XXH_PRIME64_5;
		return stc_xxh64_avalanche(hash);
	}
	const u8 *ptr = (const u8 *)params.data;
	const u8 *p = ptr;
	const u8 *end = ptr + params.len;
	u64 len = params.len;
	u64 seed = params.seed;
	u64 hash;

	if (len >= 32) {
		const u8 *limit = end - 32;

		v4u64 acc = {
			seed + XXH_PRIME64_1 + XXH_PRIME64_2,
			seed + XXH_PRIME64_2,
			seed + 0,
			seed - XXH_PRIME64_1
		};

		v4u64 prime1 = { XXH_PRIME64_1, XXH_PRIME64_1, XXH_PRIME64_1, XXH_PRIME64_1 };
		v4u64 prime2 = { XXH_PRIME64_2, XXH_PRIME64_2, XXH_PRIME64_2, XXH_PRIME64_2 };

		do {
			v4u64 input = {
				stc_read64_le(p + 0),
				stc_read64_le(p + 8),
				stc_read64_le(p + 16),
				stc_read64_le(p + 24)
			};

			acc += input * prime2;
			acc = stormc_rotl64_v4u64(acc, 31);
			acc *= prime1;

			p += 32;
		} while (p <= limit);

		u64 acc0 = acc[0];
		u64 acc1 = acc[1];
		u64 acc2 = acc[2];
		u64 acc3 = acc[3];

		hash =
			stc_rotateleft64(acc0, 1) +
			stc_rotateleft64(acc1, 7) +
			stc_rotateleft64(acc2, 12) +
			stc_rotateleft64(acc3, 18);

		hash = stc_xxh64_merge_round(hash, acc0);
		hash = stc_xxh64_merge_round(hash, acc1);
		hash = stc_xxh64_merge_round(hash, acc2);
		hash = stc_xxh64_merge_round(hash, acc3);
	}
	else {
		hash = seed + XXH_PRIME64_5;
	}

	hash += len;

	while ((p + 8) <= end) {
		u64 k1 = stc_read64_le(p);
		k1 *= XXH_PRIME64_2;
		k1 = stc_rotateleft64(k1, 31);
		k1 *= XXH_PRIME64_1;
		hash ^= k1;
		hash = stc_rotateleft64(hash, 27) * XXH_PRIME64_1 + XXH_PRIME64_4;
		p += 8;
	}

	if ((p + 4) <= end) {
		hash ^= (u64)stc_read32_le(p) * XXH_PRIME64_1;
		hash = stc_rotateleft64(hash, 23) * XXH_PRIME64_2 + XXH_PRIME64_3;
		p += 4;
	}

	while (p < end) {
		hash ^= (u64)(*p) * XXH_PRIME64_5;
		hash = stc_rotateleft64(hash, 11) * XXH_PRIME64_1;
		++p;
	}

	return stc_xxh64_avalanche(hash);
}
