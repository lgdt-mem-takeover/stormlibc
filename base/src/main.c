#define STORMC_ALLOCATOR
#include "/data/2026-projs/c/stormlibc/stormc_header.h"

#define ALIGN_SIMD __attribute__((aligned(STC_SIMD_ALIGN)))
#define ARRAY_LEN(x) ((u64)(sizeof(x) / sizeof((x)[0])))

static u32 f32_bits(f32 x)
{
	union { f32 f; u32 u; } v;
	v.f = x;
	return v.u;
}

static f32 f32_from_bits(u32 x)
{
	union { f32 f; u32 u; } v;
	v.u = x;
	return v.f;
}

static u64 mask_from_bools(const bool *flags, const u64 len)
{
	u64 mask = 0;
	for (u64 i = 0; i < len; ++i) {
		mask |= ((u64)flags[i] << i);
	}
	return mask;
}

static void test_i8(void)
{
	ALIGN_SIMD i8 a[LANES_I8], b[LANES_I8], out[LANES_I8];
	bool cmp_lt[LANES_I8];
	for (u64 i = 0; i < LANES_I8; ++i) {
		a[i] = (i8)((i % 7) - 3);
		b[i] = (i8)(((i * 3) % 7) - 3);
	}

	stc_simd_splat_i8(out, 7, LANES_I8);
	for (u64 i = 0; i < LANES_I8; ++i) assert(out[i] == 7);

	stc_simd_add_i8(out, a, b, LANES_I8);
	for (u64 i = 0; i < LANES_I8; ++i) assert(out[i] == (i8)(a[i] + b[i]));

	stc_simd_sub_i8(out, a, b, LANES_I8);
	for (u64 i = 0; i < LANES_I8; ++i) assert(out[i] == (i8)(a[i] - b[i]));

	for (u64 i = 0; i < LANES_I8; ++i) a[i] = (i8)(i + 1);
	stc_simd_shl_i8(out, a, 1, LANES_I8);
	for (u64 i = 0; i < LANES_I8; ++i) assert(out[i] == (i8)(a[i] << 1));
	stc_simd_shr_i8(out, a, 1, LANES_I8);
	for (u64 i = 0; i < LANES_I8; ++i) assert(out[i] == (i8)(a[i] >> 1));

	for (u64 i = 0; i < LANES_I8; ++i) {
		a[i] = (i8)(0x11 + (i & 7));
		b[i] = (i8)(0x3c - (i & 3));
	}
	stc_simd_and_i8(out, a, b, LANES_I8);
	for (u64 i = 0; i < LANES_I8; ++i) assert(out[i] == (i8)(a[i] & b[i]));
	stc_simd_or_i8(out, a, b, LANES_I8);
	for (u64 i = 0; i < LANES_I8; ++i) assert(out[i] == (i8)(a[i] | b[i]));
	stc_simd_xor_i8(out, a, b, LANES_I8);
	for (u64 i = 0; i < LANES_I8; ++i) assert(out[i] == (i8)(a[i] ^ b[i]));
	stc_simd_andnot_i8(out, a, b, LANES_I8);
	for (u64 i = 0; i < LANES_I8; ++i) assert(out[i] == (i8)((~a[i]) & b[i]));
	stc_simd_not_i8(out, a, LANES_I8);
	for (u64 i = 0; i < LANES_I8; ++i) assert(out[i] == (i8)(~a[i]));

	for (u64 i = 0; i < LANES_I8; ++i) {
		a[i] = (i8)((i % 5) - 2);
		b[i] = (i8)(((i + 2) % 5) - 2);
		cmp_lt[i] = a[i] < b[i];
	}
	stc_simd_cmpeq_i8(out, a, b, LANES_I8);
	for (u64 i = 0; i < LANES_I8; ++i) assert(out[i] == (a[i] == b[i] ? (i8)-1 : (i8)0));
	stc_simd_cmpne_i8(out, a, b, LANES_I8);
	for (u64 i = 0; i < LANES_I8; ++i) assert(out[i] == (a[i] != b[i] ? (i8)-1 : (i8)0));
	stc_simd_cmplt_i8(out, a, b, LANES_I8);
	for (u64 i = 0; i < LANES_I8; ++i) assert(out[i] == (cmp_lt[i] ? (i8)-1 : (i8)0));
	stc_simd_cmpgt_i8(out, a, b, LANES_I8);
	for (u64 i = 0; i < LANES_I8; ++i) assert(out[i] == (a[i] > b[i] ? (i8)-1 : (i8)0));
	stc_simd_cmple_i8(out, a, b, LANES_I8);
	for (u64 i = 0; i < LANES_I8; ++i) assert(out[i] == (a[i] <= b[i] ? (i8)-1 : (i8)0));
	stc_simd_cmpge_i8(out, a, b, LANES_I8);
	for (u64 i = 0; i < LANES_I8; ++i) assert(out[i] == (a[i] >= b[i] ? (i8)-1 : (i8)0));

	{
		stc_simd_cmplt_i8(out, a, b, LANES_I8);
		u64 expected_mask = mask_from_bools(cmp_lt, LANES_I8);
		assert(stc_simd_bitmask_i8(out, LANES_I8) == expected_mask);
		assert(stc_simd_any_true_i8(out, LANES_I8) == (expected_mask != 0));
		assert(stc_simd_all_true_i8(out, LANES_I8) == (expected_mask == ((1ull << LANES_I8) - 1ull)));
		stc_simd_splat_i8(out, 0, LANES_I8);
		assert(stc_simd_any_true_i8(out, LANES_I8) == false);
		stc_simd_splat_i8(out, -1, LANES_I8);
		assert(stc_simd_all_true_i8(out, LANES_I8) == true);
	}

	{
		ALIGN_SIMD i8 truthy[LANES_I8 + 3];
		const u64 len = ARRAY_LEN(truthy);
		u64 count = 0;
		u64 first = (u64)-1;
		u64 count_eq0 = 0;
		u64 first_eq0 = (u64)-1;
		u64 count_lt1 = 0;
		u64 first_lt1 = (u64)-1;
		u64 count_gt1 = 0;
		u64 first_gt1 = (u64)-1;
		u64 count_le0 = 0;
		u64 first_le0 = (u64)-1;
		u64 count_ge0 = 0;
		u64 first_ge0 = (u64)-1;
		for (u64 i = 0; i < len; ++i) {
			truthy[i] = (i8)(((i * 3) % 7) - 3);
		}
		for (u64 i = 0; i < len; ++i) {
			if (truthy[i] != 0) {
				++count;
				if (first == (u64)-1) first = i;
			}
			if (truthy[i] == 0) {
				++count_eq0;
				if (first_eq0 == (u64)-1) first_eq0 = i;
			}
			if (truthy[i] < 1) {
				++count_lt1;
				if (first_lt1 == (u64)-1) first_lt1 = i;
			}
			if (truthy[i] > 1) {
				++count_gt1;
				if (first_gt1 == (u64)-1) first_gt1 = i;
			}
			if (truthy[i] <= 0) {
				++count_le0;
				if (first_le0 == (u64)-1) first_le0 = i;
			}
			if (truthy[i] >= 0) {
				++count_ge0;
				if (first_ge0 == (u64)-1) first_ge0 = i;
			}
		}
		assert(stc_simd_count_true_i8(truthy, len) == count);
		assert(stc_simd_first_true_i8(truthy, len) == first);
		assert(stc_simd_count_cmpeq_scalar_i8(truthy, 0, len) == count_eq0);
		assert(stc_simd_first_cmpeq_scalar_i8(truthy, 0, len) == first_eq0);
		assert(stc_simd_count_cmpne_scalar_i8(truthy, 0, len) == count);
		assert(stc_simd_first_cmpne_scalar_i8(truthy, 0, len) == first);
		assert(stc_simd_count_cmplt_scalar_i8(truthy, 1, len) == count_lt1);
		assert(stc_simd_first_cmplt_scalar_i8(truthy, 1, len) == first_lt1);
		assert(stc_simd_count_cmpgt_scalar_i8(truthy, 1, len) == count_gt1);
		assert(stc_simd_first_cmpgt_scalar_i8(truthy, 1, len) == first_gt1);
		assert(stc_simd_count_cmple_scalar_i8(truthy, 0, len) == count_le0);
		assert(stc_simd_first_cmple_scalar_i8(truthy, 0, len) == first_le0);
		assert(stc_simd_count_cmpge_scalar_i8(truthy, 0, len) == count_ge0);
		assert(stc_simd_first_cmpge_scalar_i8(truthy, 0, len) == first_ge0);
	}

	{
		ALIGN_SIMD i8 values[LANES_I8 + 5];
		i8 sum = 0;
		for (u64 i = 0; i < ARRAY_LEN(values); ++i) {
			values[i] = (i8)((i % 5) - 2);
			sum = (i8)(sum + values[i]);
		}
		assert(stc_simd_reduce_add_i8(values, ARRAY_LEN(values)) == sum);
	}
}

static void test_i16(void)
{
	ALIGN_SIMD i16 a[LANES_I16], b[LANES_I16], out[LANES_I16];
	bool cmp_lt[LANES_I16];
	for (u64 i = 0; i < LANES_I16; ++i) {
		a[i] = (i16)((i % 9) - 4);
		b[i] = (i16)(((i * 2) % 9) - 4);
	}
	stc_simd_splat_i16(out, 13, LANES_I16);
	for (u64 i = 0; i < LANES_I16; ++i) assert(out[i] == 13);
	stc_simd_add_i16(out, a, b, LANES_I16);
	for (u64 i = 0; i < LANES_I16; ++i) assert(out[i] == (i16)(a[i] + b[i]));
	stc_simd_sub_i16(out, a, b, LANES_I16);
	for (u64 i = 0; i < LANES_I16; ++i) assert(out[i] == (i16)(a[i] - b[i]));
	for (u64 i = 0; i < LANES_I16; ++i) {
		a[i] = (i16)((i % 4) + 1);
		b[i] = (i16)((i % 3) + 2);
	}
	stc_simd_mul_i16(out, a, b, LANES_I16);
	for (u64 i = 0; i < LANES_I16; ++i) assert(out[i] == (i16)(a[i] * b[i]));
	stc_simd_shl_i16(out, a, 2, LANES_I16);
	for (u64 i = 0; i < LANES_I16; ++i) assert(out[i] == (i16)(a[i] << 2));
	stc_simd_shr_i16(out, a, 1, LANES_I16);
	for (u64 i = 0; i < LANES_I16; ++i) assert(out[i] == (i16)(a[i] >> 1));
	for (u64 i = 0; i < LANES_I16; ++i) {
		a[i] = (i16)(0x1111 + i);
		b[i] = (i16)(0x00f0 + (i * 3));
	}
	stc_simd_and_i16(out, a, b, LANES_I16);
	for (u64 i = 0; i < LANES_I16; ++i) assert(out[i] == (i16)(a[i] & b[i]));
	stc_simd_or_i16(out, a, b, LANES_I16);
	for (u64 i = 0; i < LANES_I16; ++i) assert(out[i] == (i16)(a[i] | b[i]));
	stc_simd_xor_i16(out, a, b, LANES_I16);
	for (u64 i = 0; i < LANES_I16; ++i) assert(out[i] == (i16)(a[i] ^ b[i]));
	stc_simd_andnot_i16(out, a, b, LANES_I16);
	for (u64 i = 0; i < LANES_I16; ++i) assert(out[i] == (i16)((~a[i]) & b[i]));
	stc_simd_not_i16(out, a, LANES_I16);
	for (u64 i = 0; i < LANES_I16; ++i) assert(out[i] == (i16)(~a[i]));
	for (u64 i = 0; i < LANES_I16; ++i) {
		a[i] = (i16)((i % 6) - 3);
		b[i] = (i16)(((i + 3) % 6) - 3);
		cmp_lt[i] = a[i] < b[i];
	}
	stc_simd_cmpeq_i16(out, a, b, LANES_I16);
	for (u64 i = 0; i < LANES_I16; ++i) assert(out[i] == (a[i] == b[i] ? (i16)-1 : (i16)0));
	stc_simd_cmpne_i16(out, a, b, LANES_I16);
	for (u64 i = 0; i < LANES_I16; ++i) assert(out[i] == (a[i] != b[i] ? (i16)-1 : (i16)0));
	stc_simd_cmplt_i16(out, a, b, LANES_I16);
	for (u64 i = 0; i < LANES_I16; ++i) assert(out[i] == (cmp_lt[i] ? (i16)-1 : (i16)0));
	stc_simd_cmpgt_i16(out, a, b, LANES_I16);
	for (u64 i = 0; i < LANES_I16; ++i) assert(out[i] == (a[i] > b[i] ? (i16)-1 : (i16)0));
	stc_simd_cmple_i16(out, a, b, LANES_I16);
	for (u64 i = 0; i < LANES_I16; ++i) assert(out[i] == (a[i] <= b[i] ? (i16)-1 : (i16)0));
	stc_simd_cmpge_i16(out, a, b, LANES_I16);
	for (u64 i = 0; i < LANES_I16; ++i) assert(out[i] == (a[i] >= b[i] ? (i16)-1 : (i16)0));
	{
		stc_simd_cmplt_i16(out, a, b, LANES_I16);
		u64 expected_mask = mask_from_bools(cmp_lt, LANES_I16);
		assert(stc_simd_bitmask_i16(out, LANES_I16) == expected_mask);
		assert(stc_simd_any_true_i16(out, LANES_I16) == (expected_mask != 0));
		assert(stc_simd_all_true_i16(out, LANES_I16) == false);
	}
	{
		ALIGN_SIMD i16 values[LANES_I16 + 3];
		const u64 len = ARRAY_LEN(values);
		u64 count_true = 0;
		u64 first_true = (u64)-1;
		u64 count_eq2 = 0, first_eq2 = (u64)-1;
		u64 count_lt1 = 0, first_lt1 = (u64)-1;
		u64 count_gt1 = 0, first_gt1 = (u64)-1;
		u64 count_le0 = 0, first_le0 = (u64)-1;
		u64 count_ge2 = 0, first_ge2 = (u64)-1;
		for (u64 i = 0; i < len; ++i) values[i] = (i16)(((i * 5) % 17) - 8);
		for (u64 i = 0; i < len; ++i) {
			if (values[i] != 0) {
				++count_true;
				if (first_true == (u64)-1) first_true = i;
			}
			if (values[i] == 2) {
				++count_eq2;
				if (first_eq2 == (u64)-1) first_eq2 = i;
			}
			if (values[i] < 1) {
				++count_lt1;
				if (first_lt1 == (u64)-1) first_lt1 = i;
			}
			if (values[i] > 1) {
				++count_gt1;
				if (first_gt1 == (u64)-1) first_gt1 = i;
			}
			if (values[i] <= 0) {
				++count_le0;
				if (first_le0 == (u64)-1) first_le0 = i;
			}
			if (values[i] >= 2) {
				++count_ge2;
				if (first_ge2 == (u64)-1) first_ge2 = i;
			}
		}
		assert(stc_simd_count_true_i16(values, len) == count_true);
		assert(stc_simd_first_true_i16(values, len) == first_true);
		assert(stc_simd_count_cmpeq_scalar_i16(values, 2, len) == count_eq2);
		assert(stc_simd_first_cmpeq_scalar_i16(values, 2, len) == first_eq2);
		assert(stc_simd_count_cmpne_scalar_i16(values, 0, len) == count_true);
		assert(stc_simd_first_cmpne_scalar_i16(values, 0, len) == first_true);
		assert(stc_simd_count_cmplt_scalar_i16(values, 1, len) == count_lt1);
		assert(stc_simd_first_cmplt_scalar_i16(values, 1, len) == first_lt1);
		assert(stc_simd_count_cmpgt_scalar_i16(values, 1, len) == count_gt1);
		assert(stc_simd_first_cmpgt_scalar_i16(values, 1, len) == first_gt1);
		assert(stc_simd_count_cmple_scalar_i16(values, 0, len) == count_le0);
		assert(stc_simd_first_cmple_scalar_i16(values, 0, len) == first_le0);
		assert(stc_simd_count_cmpge_scalar_i16(values, 2, len) == count_ge2);
		assert(stc_simd_first_cmpge_scalar_i16(values, 2, len) == first_ge2);
	}
	{
		ALIGN_SIMD i16 sum_vals[LANES_I16 + 2];
		ALIGN_SIMD i16 mul_vals[LANES_I16 + 1];
		i16 sum = 0;
		i16 prod = 1;
		for (u64 i = 0; i < ARRAY_LEN(sum_vals); ++i) {
			sum_vals[i] = (i16)((i % 6) - 2);
			sum = (i16)(sum + sum_vals[i]);
		}
		for (u64 i = 0; i < ARRAY_LEN(mul_vals); ++i) {
			mul_vals[i] = (i16)((i % 3) + 1);
			prod = (i16)(prod * mul_vals[i]);
		}
		assert(stc_simd_reduce_add_i16(sum_vals, ARRAY_LEN(sum_vals)) == sum);
		assert(stc_simd_reduce_mul_i16(mul_vals, ARRAY_LEN(mul_vals)) == prod);
	}
}

static void test_i32(void)
{
	ALIGN_SIMD i32 a[LANES_I32], b[LANES_I32], out[LANES_I32];
	bool cmp_lt[LANES_I32];
	for (u64 i = 0; i < LANES_I32; ++i) {
		a[i] = (i32)((i % 9) - 4);
		b[i] = (i32)(((i * 2) % 9) - 4);
	}	stc_simd_splat_i32(out, 29, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == 29);
	stc_simd_add_i32(out, a, b, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == a[i] + b[i]);
	stc_simd_sub_i32(out, a, b, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == a[i] - b[i]);
	for (u64 i = 0; i < LANES_I32; ++i) {
		a[i] = (i32)((i % 5) + 1);
		b[i] = (i32)((i % 3) + 2);
	}
	stc_simd_mul_i32(out, a, b, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == a[i] * b[i]);
	stc_simd_shl_i32(out, a, 3, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == (a[i] << 3));
	stc_simd_shr_i32(out, a, 1, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == (a[i] >> 1));
	for (u64 i = 0; i < LANES_I32; ++i) {
		a[i] = 0x11111111 + (i32)i;
		b[i] = 0x00ff00f0 + (i32)(i * 17);
	}
	stc_simd_and_i32(out, a, b, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == (a[i] & b[i]));
	stc_simd_or_i32(out, a, b, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == (a[i] | b[i]));
	stc_simd_xor_i32(out, a, b, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == (a[i] ^ b[i]));
	stc_simd_andnot_i32(out, a, b, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == ((~a[i]) & b[i]));
	stc_simd_not_i32(out, a, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == (~a[i]));
	for (u64 i = 0; i < LANES_I32; ++i) {
		a[i] = (i32)((i % 7) - 3);
		b[i] = (i32)(((i + 3) % 7) - 3);
		cmp_lt[i] = a[i] < b[i];
	}
	stc_simd_cmpeq_i32(out, a, b, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == (a[i] == b[i] ? -1 : 0));
	stc_simd_cmpne_i32(out, a, b, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == (a[i] != b[i] ? -1 : 0));
	stc_simd_cmplt_i32(out, a, b, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == (cmp_lt[i] ? -1 : 0));
	stc_simd_cmpgt_i32(out, a, b, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == (a[i] > b[i] ? -1 : 0));
	stc_simd_cmple_i32(out, a, b, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == (a[i] <= b[i] ? -1 : 0));
	stc_simd_cmpge_i32(out, a, b, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == (a[i] >= b[i] ? -1 : 0));
	{
		stc_simd_cmplt_i32(out, a, b, LANES_I32);
		u64 expected_mask = mask_from_bools(cmp_lt, LANES_I32);
		assert(stc_simd_bitmask_i32(out, LANES_I32) == expected_mask);
		assert(stc_simd_any_true_i32(out, LANES_I32) == (expected_mask != 0));
		assert(stc_simd_all_true_i32(out, LANES_I32) == false);
	}
	stc_simd_min_i32(out, a, b, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == (a[i] < b[i] ? a[i] : b[i]));
	stc_simd_max_i32(out, a, b, LANES_I32);
	for (u64 i = 0; i < LANES_I32; ++i) assert(out[i] == (a[i] > b[i] ? a[i] : b[i]));
	{
		ALIGN_SIMD i32 values[LANES_I32 + 5];
		const u64 len = ARRAY_LEN(values);
		u64 count_true = 0;
		u64 first_true = (u64)-1;
		u64 count_lt = 0;
		u64 first_lt = (u64)-1;
		u64 count_eq99 = 0, first_eq99 = (u64)-1;
		u64 count_ne100 = 0, first_ne100 = (u64)-1;
		u64 count_gt100 = 0, first_gt100 = (u64)-1;
		u64 count_le100 = 0, first_le100 = (u64)-1;
		u64 count_ge100 = 0, first_ge100 = (u64)-1;
		for (u64 i = 0; i < len; ++i) values[i] = (i32)((i * 31) % 207);
		values[1] = 99;
		values[3] = 101;
		values[7] = 100;
		values[10] = 99;
		for (u64 i = 0; i < len; ++i) {
			if (values[i] != 0) {
				++count_true;
				if (first_true == (u64)-1) first_true = i;
			}
			if (values[i] == 99) {
				++count_eq99;
				if (first_eq99 == (u64)-1) first_eq99 = i;
			}
			if (values[i] != 100) {
				++count_ne100;
				if (first_ne100 == (u64)-1) first_ne100 = i;
			}
			if (values[i] < 100) {
				++count_lt;
				if (first_lt == (u64)-1) first_lt = i;
			}
			if (values[i] > 100) {
				++count_gt100;
				if (first_gt100 == (u64)-1) first_gt100 = i;
			}
			if (values[i] <= 100) {
				++count_le100;
				if (first_le100 == (u64)-1) first_le100 = i;
			}
			if (values[i] >= 100) {
				++count_ge100;
				if (first_ge100 == (u64)-1) first_ge100 = i;
			}
		}
		assert(stc_simd_count_true_i32(values, len) == count_true);
		assert(stc_simd_first_true_i32(values, len) == first_true);
		assert(stc_simd_count_cmpeq_scalar_i32(values, 99, len) == count_eq99);
		assert(stc_simd_first_cmpeq_scalar_i32(values, 99, len) == first_eq99);
		assert(stc_simd_count_cmpne_scalar_i32(values, 100, len) == count_ne100);
		assert(stc_simd_first_cmpne_scalar_i32(values, 100, len) == first_ne100);
		assert(stc_simd_count_cmplt_scalar_i32(values, 100, len) == count_lt);
		assert(stc_simd_first_cmplt_scalar_i32(values, 100, len) == first_lt);
		assert(stc_simd_count_cmpgt_scalar_i32(values, 100, len) == count_gt100);
		assert(stc_simd_first_cmpgt_scalar_i32(values, 100, len) == first_gt100);
		assert(stc_simd_count_cmple_scalar_i32(values, 100, len) == count_le100);
		assert(stc_simd_first_cmple_scalar_i32(values, 100, len) == first_le100);
		assert(stc_simd_count_cmpge_scalar_i32(values, 100, len) == count_ge100);
		assert(stc_simd_first_cmpge_scalar_i32(values, 100, len) == first_ge100);
	}
	{
		ALIGN_SIMD i32 add_vals[LANES_I32 + 3];
		ALIGN_SIMD i32 mul_vals[LANES_I32 + 2];
		ALIGN_SIMD i32 minmax_vals[LANES_I32 + 4];
		i32 sum = 0;
		i32 prod = 1;
		i32 minv = 0;
		i32 maxv = 0;
		for (u64 i = 0; i < ARRAY_LEN(add_vals); ++i) {
			add_vals[i] = (i32)((i % 6) - 2);
			sum += add_vals[i];
		}
		for (u64 i = 0; i < ARRAY_LEN(mul_vals); ++i) {
			mul_vals[i] = (i32)((i % 3) + 1);
			prod *= mul_vals[i];
		}
		for (u64 i = 0; i < ARRAY_LEN(minmax_vals); ++i) {
			minmax_vals[i] = (i32)((i % 11) - 5);
			if (i == 0 || minmax_vals[i] < minv) minv = minmax_vals[i];
			if (i == 0 || minmax_vals[i] > maxv) maxv = minmax_vals[i];
		}
		assert(stc_simd_reduce_add_i32(add_vals, ARRAY_LEN(add_vals)) == sum);
		assert(stc_simd_reduce_mul_i32(mul_vals, ARRAY_LEN(mul_vals)) == prod);
		assert(stc_simd_reduce_min_i32(minmax_vals, ARRAY_LEN(minmax_vals)) == minv);
		assert(stc_simd_reduce_max_i32(minmax_vals, ARRAY_LEN(minmax_vals)) == maxv);
	}
}

static void test_i64(void)
{
	ALIGN_SIMD i64 a[LANES_I64], b[LANES_I64], out[LANES_I64];
	bool cmp_lt[LANES_I64];
	for (u64 i = 0; i < LANES_I64; ++i) {
		a[i] = (i64)((i % 9) - 4);
		b[i] = (i64)(((i * 2) % 9) - 4);
	}	stc_simd_splat_i64(out, 41, LANES_I64);
	for (u64 i = 0; i < LANES_I64; ++i) assert(out[i] == 41);
	stc_simd_add_i64(out, a, b, LANES_I64);
	for (u64 i = 0; i < LANES_I64; ++i) assert(out[i] == a[i] + b[i]);
	stc_simd_sub_i64(out, a, b, LANES_I64);
	for (u64 i = 0; i < LANES_I64; ++i) assert(out[i] == a[i] - b[i]);
	for (u64 i = 0; i < LANES_I64; ++i) a[i] = (i64)(i + 1);
	stc_simd_shl_i64(out, a, 2, LANES_I64);
	for (u64 i = 0; i < LANES_I64; ++i) assert(out[i] == (a[i] << 2));
	stc_simd_shr_i64(out, a, 1, LANES_I64);
	for (u64 i = 0; i < LANES_I64; ++i) assert(out[i] == (a[i] >> 1));
	for (u64 i = 0; i < LANES_I64; ++i) {
		a[i] = 0x1111111111111111ll + (i64)i;
		b[i] = 0x00ff00f000ff00f0ll + (i64)(i * 257);
	}
	stc_simd_and_i64(out, a, b, LANES_I64);
	for (u64 i = 0; i < LANES_I64; ++i) assert(out[i] == (a[i] & b[i]));
	stc_simd_or_i64(out, a, b, LANES_I64);
	for (u64 i = 0; i < LANES_I64; ++i) assert(out[i] == (a[i] | b[i]));
	stc_simd_xor_i64(out, a, b, LANES_I64);
	for (u64 i = 0; i < LANES_I64; ++i) assert(out[i] == (a[i] ^ b[i]));
	stc_simd_andnot_i64(out, a, b, LANES_I64);
	for (u64 i = 0; i < LANES_I64; ++i) assert(out[i] == ((~a[i]) & b[i]));
	stc_simd_not_i64(out, a, LANES_I64);
	for (u64 i = 0; i < LANES_I64; ++i) assert(out[i] == (~a[i]));
	for (u64 i = 0; i < LANES_I64; ++i) {
		a[i] = (i64)((i % 5) - 2);
		b[i] = (i64)(((i + 2) % 5) - 2);
		cmp_lt[i] = a[i] < b[i];
	}
	stc_simd_cmpeq_i64(out, a, b, LANES_I64);
	for (u64 i = 0; i < LANES_I64; ++i) assert(out[i] == (a[i] == b[i] ? -1ll : 0ll));
	stc_simd_cmpne_i64(out, a, b, LANES_I64);
	for (u64 i = 0; i < LANES_I64; ++i) assert(out[i] == (a[i] != b[i] ? -1ll : 0ll));
	stc_simd_cmplt_i64(out, a, b, LANES_I64);
	for (u64 i = 0; i < LANES_I64; ++i) assert(out[i] == (cmp_lt[i] ? -1ll : 0ll));
	stc_simd_cmpgt_i64(out, a, b, LANES_I64);
	for (u64 i = 0; i < LANES_I64; ++i) assert(out[i] == (a[i] > b[i] ? -1ll : 0ll));
	stc_simd_cmple_i64(out, a, b, LANES_I64);
	for (u64 i = 0; i < LANES_I64; ++i) assert(out[i] == (a[i] <= b[i] ? -1ll : 0ll));
	stc_simd_cmpge_i64(out, a, b, LANES_I64);
	for (u64 i = 0; i < LANES_I64; ++i) assert(out[i] == (a[i] >= b[i] ? -1ll : 0ll));
	{
		stc_simd_cmplt_i64(out, a, b, LANES_I64);
		u64 expected_mask = mask_from_bools(cmp_lt, LANES_I64);
		assert(stc_simd_bitmask_i64(out, LANES_I64) == expected_mask);
		assert(stc_simd_any_true_i64(out, LANES_I64) == (expected_mask != 0));
		assert(stc_simd_all_true_i64(out, LANES_I64) == false);
	}
	{
		ALIGN_SIMD i64 values[LANES_I64 + 5];
		const u64 len = ARRAY_LEN(values);
		u64 count_true = 0;
		u64 first_true = (u64)-1;
		u64 count_eq2 = 0;
		u64 first_eq2 = (u64)-1;
		u64 count_lt1 = 0, first_lt1 = (u64)-1;
		u64 count_gt1 = 0, first_gt1 = (u64)-1;
		u64 count_le0 = 0, first_le0 = (u64)-1;
		u64 count_ge2 = 0, first_ge2 = (u64)-1;
		i64 sum = 0;
		for (u64 i = 0; i < len; ++i) values[i] = (i64)(((i * 7) % 19) - 9);
		for (u64 i = 0; i < len; ++i) {
			if (values[i] != 0) {
				++count_true;
				if (first_true == (u64)-1) first_true = i;
			}
			if (values[i] == 2) {
				++count_eq2;
				if (first_eq2 == (u64)-1) first_eq2 = i;
			}
			if (values[i] < 1) {
				++count_lt1;
				if (first_lt1 == (u64)-1) first_lt1 = i;
			}
			if (values[i] > 1) {
				++count_gt1;
				if (first_gt1 == (u64)-1) first_gt1 = i;
			}
			if (values[i] <= 0) {
				++count_le0;
				if (first_le0 == (u64)-1) first_le0 = i;
			}
			if (values[i] >= 2) {
				++count_ge2;
				if (first_ge2 == (u64)-1) first_ge2 = i;
			}
			sum += values[i];
		}
		assert(stc_simd_count_true_i64(values, len) == count_true);
		assert(stc_simd_first_true_i64(values, len) == first_true);
		assert(stc_simd_count_cmpeq_scalar_i64(values, 2, len) == count_eq2);
		assert(stc_simd_first_cmpeq_scalar_i64(values, 2, len) == first_eq2);
		assert(stc_simd_count_cmpne_scalar_i64(values, 0, len) == count_true);
		assert(stc_simd_first_cmpne_scalar_i64(values, 0, len) == first_true);
		assert(stc_simd_count_cmplt_scalar_i64(values, 1, len) == count_lt1);
		assert(stc_simd_first_cmplt_scalar_i64(values, 1, len) == first_lt1);
		assert(stc_simd_count_cmpgt_scalar_i64(values, 1, len) == count_gt1);
		assert(stc_simd_first_cmpgt_scalar_i64(values, 1, len) == first_gt1);
		assert(stc_simd_count_cmple_scalar_i64(values, 0, len) == count_le0);
		assert(stc_simd_first_cmple_scalar_i64(values, 0, len) == first_le0);
		assert(stc_simd_count_cmpge_scalar_i64(values, 2, len) == count_ge2);
		assert(stc_simd_first_cmpge_scalar_i64(values, 2, len) == first_ge2);
		assert(stc_simd_reduce_add_i64(values, len) == sum);
	}
}

static void test_f32(void)
{
	ALIGN_SIMD f32 a[LANES_F32], b[LANES_F32], out[LANES_F32];
	bool cmp_lt[LANES_F32];
	for (u64 i = 0; i < LANES_F32; ++i) {
		a[i] = ((f32)i * 1.25f) - 3.0f;
		b[i] = ((f32)(i % 5) * 0.75f) - 1.5f;
		if (b[i] == 0.0f) b[i] = 2.0f;
	}	stc_simd_splat_f32(out, 3.5f, LANES_F32);
	for (u64 i = 0; i < LANES_F32; ++i) assert(out[i] == 3.5f);
	stc_simd_add_f32(out, a, b, LANES_F32);
	for (u64 i = 0; i < LANES_F32; ++i) assert(out[i] == a[i] + b[i]);
	stc_simd_sub_f32(out, a, b, LANES_F32);
	for (u64 i = 0; i < LANES_F32; ++i) assert(out[i] == a[i] - b[i]);
	stc_simd_mul_f32(out, a, b, LANES_F32);
	for (u64 i = 0; i < LANES_F32; ++i) assert(out[i] == a[i] * b[i]);
	stc_simd_div_f32(out, a, b, LANES_F32);
	for (u64 i = 0; i < LANES_F32; ++i) assert(out[i] == a[i] / b[i]);
	{
		ALIGN_SIMD f32 bit_a[LANES_F32], bit_b[LANES_F32], bit_out[LANES_F32];
		for (u64 i = 0; i < LANES_F32; ++i) {
			bit_a[i] = f32_from_bits(0x3f800000u + (u32)(i * 0x00110011u));
			bit_b[i] = f32_from_bits(0x0f0f0f0fu + (u32)(i * 0x00010001u));
		}
		stc_simd_and_f32(bit_out, bit_a, bit_b, LANES_F32);
		for (u64 i = 0; i < LANES_F32; ++i) assert(f32_bits(bit_out[i]) == (f32_bits(bit_a[i]) & f32_bits(bit_b[i])));
		stc_simd_or_f32(bit_out, bit_a, bit_b, LANES_F32);
		for (u64 i = 0; i < LANES_F32; ++i) assert(f32_bits(bit_out[i]) == (f32_bits(bit_a[i]) | f32_bits(bit_b[i])));
		stc_simd_xor_f32(bit_out, bit_a, bit_b, LANES_F32);
		for (u64 i = 0; i < LANES_F32; ++i) assert(f32_bits(bit_out[i]) == (f32_bits(bit_a[i]) ^ f32_bits(bit_b[i])));
		stc_simd_andnot_f32(bit_out, bit_a, bit_b, LANES_F32);
		for (u64 i = 0; i < LANES_F32; ++i) assert(f32_bits(bit_out[i]) == ((~f32_bits(bit_a[i])) & f32_bits(bit_b[i])));
		stc_simd_not_f32(bit_out, bit_a, LANES_F32);
		for (u64 i = 0; i < LANES_F32; ++i) assert(f32_bits(bit_out[i]) == (~f32_bits(bit_a[i])));
	}
	for (u64 i = 0; i < LANES_F32; ++i) {
		a[i] = ((f32)i * 1.5f) - 4.0f;
		b[i] = ((f32)(i % 4) * 1.0f) - 1.0f;
		cmp_lt[i] = a[i] < b[i];
	}
	stc_simd_cmpeq_f32(out, a, b, LANES_F32);
	for (u64 i = 0; i < LANES_F32; ++i) assert(f32_bits(out[i]) == (a[i] == b[i] ? 0xffffffffu : 0u));
	stc_simd_cmpne_f32(out, a, b, LANES_F32);
	for (u64 i = 0; i < LANES_F32; ++i) assert(f32_bits(out[i]) == (a[i] != b[i] ? 0xffffffffu : 0u));
	stc_simd_cmplt_f32(out, a, b, LANES_F32);
	for (u64 i = 0; i < LANES_F32; ++i) assert(f32_bits(out[i]) == (cmp_lt[i] ? 0xffffffffu : 0u));
	stc_simd_cmpgt_f32(out, a, b, LANES_F32);
	for (u64 i = 0; i < LANES_F32; ++i) assert(f32_bits(out[i]) == (a[i] > b[i] ? 0xffffffffu : 0u));
	stc_simd_cmple_f32(out, a, b, LANES_F32);
	for (u64 i = 0; i < LANES_F32; ++i) assert(f32_bits(out[i]) == (a[i] <= b[i] ? 0xffffffffu : 0u));
	stc_simd_cmpge_f32(out, a, b, LANES_F32);
	for (u64 i = 0; i < LANES_F32; ++i) assert(f32_bits(out[i]) == (a[i] >= b[i] ? 0xffffffffu : 0u));
	{
		stc_simd_cmplt_f32(out, a, b, LANES_F32);
		u64 expected_mask = mask_from_bools(cmp_lt, LANES_F32);
		assert(stc_simd_bitmask_f32(out, LANES_F32) == expected_mask);
		assert(stc_simd_any_true_f32(out, LANES_F32) == (expected_mask != 0));
		assert(stc_simd_all_true_f32(out, LANES_F32) == false);
	}
	stc_simd_min_f32(out, a, b, LANES_F32);
	for (u64 i = 0; i < LANES_F32; ++i) assert(out[i] == (a[i] < b[i] ? a[i] : b[i]));
	stc_simd_max_f32(out, a, b, LANES_F32);
	for (u64 i = 0; i < LANES_F32; ++i) assert(out[i] == (a[i] > b[i] ? a[i] : b[i]));
	{
		ALIGN_SIMD f32 values[LANES_F32 + 5];
		const u64 len = ARRAY_LEN(values);
		u64 count_true = 0;
		u64 first_true = (u64)-1;
		u64 count_lt = 0;
		u64 first_lt = (u64)-1;
		u64 count_eq100 = 0, first_eq100 = (u64)-1;
		u64 count_gt100 = 0, first_gt100 = (u64)-1;
		u64 count_le0 = 0, first_le0 = (u64)-1;
		u64 count_ge100 = 0, first_ge100 = (u64)-1;
		for (u64 i = 0; i < len; ++i) values[i] = ((f32)((i * 11) % 17) * 17.5f) - 35.0f;
		values[1] = 120.0f;
		values[2] = 99.75f;
		values[3] = 100.0f;
		values[4] = 0.0f;
		values[9] = 100.0f;
		for (u64 i = 0; i < len; ++i) {
			if (values[i] != 0.0f) {
				++count_true;
				if (first_true == (u64)-1) first_true = i;
			}
			if (values[i] == 100.0f) {
				++count_eq100;
				if (first_eq100 == (u64)-1) first_eq100 = i;
			}
			if (values[i] < 100.0f) {
				++count_lt;
				if (first_lt == (u64)-1) first_lt = i;
			}
			if (values[i] > 100.0f) {
				++count_gt100;
				if (first_gt100 == (u64)-1) first_gt100 = i;
			}
			if (values[i] <= 0.0f) {
				++count_le0;
				if (first_le0 == (u64)-1) first_le0 = i;
			}
			if (values[i] >= 100.0f) {
				++count_ge100;
				if (first_ge100 == (u64)-1) first_ge100 = i;
			}
		}
		assert(stc_simd_count_true_f32(values, len) == count_true);
		assert(stc_simd_first_true_f32(values, len) == first_true);
		assert(stc_simd_count_cmpeq_scalar_f32(values, 100.0f, len) == count_eq100);
		assert(stc_simd_first_cmpeq_scalar_f32(values, 100.0f, len) == first_eq100);
		assert(stc_simd_count_cmpne_scalar_f32(values, 0.0f, len) == count_true);
		assert(stc_simd_first_cmpne_scalar_f32(values, 0.0f, len) == first_true);
		assert(stc_simd_count_cmplt_scalar_f32(values, 100.0f, len) == count_lt);
		assert(stc_simd_first_cmplt_scalar_f32(values, 100.0f, len) == first_lt);
		assert(stc_simd_count_cmpgt_scalar_f32(values, 100.0f, len) == count_gt100);
		assert(stc_simd_first_cmpgt_scalar_f32(values, 100.0f, len) == first_gt100);
		assert(stc_simd_count_cmple_scalar_f32(values, 0.0f, len) == count_le0);
		assert(stc_simd_first_cmple_scalar_f32(values, 0.0f, len) == first_le0);
		assert(stc_simd_count_cmpge_scalar_f32(values, 100.0f, len) == count_ge100);
		assert(stc_simd_first_cmpge_scalar_f32(values, 100.0f, len) == first_ge100);
	}
	{
		ALIGN_SIMD f32 add_vals[LANES_F32 + 4];
		ALIGN_SIMD f32 mul_vals[LANES_F32 + 1];
		ALIGN_SIMD f32 minmax_vals[LANES_F32 + 3];
		f32 sum = 0.0f;
		f32 prod = 1.0f;
		f32 minv = 0.0f;
		f32 maxv = 0.0f;
		for (u64 i = 0; i < ARRAY_LEN(add_vals); ++i) {
			add_vals[i] = ((f32)i * 0.5f) - 1.5f;
			sum += add_vals[i];
		}
		for (u64 i = 0; i < ARRAY_LEN(mul_vals); ++i) {
			mul_vals[i] = 1.0f + ((f32)(i % 4) * 0.25f);
			prod *= mul_vals[i];
		}
		for (u64 i = 0; i < ARRAY_LEN(minmax_vals); ++i) {
			minmax_vals[i] = ((f32)((i * 7) % 13) * 0.5f) - 3.0f;
			if (i == 0 || minmax_vals[i] < minv) minv = minmax_vals[i];
			if (i == 0 || minmax_vals[i] > maxv) maxv = minmax_vals[i];
		}
		assert(stc_simd_reduce_add_f32(add_vals, ARRAY_LEN(add_vals)) == sum);
		assert(stc_simd_reduce_mul_f32(mul_vals, ARRAY_LEN(mul_vals)) == prod);
		assert(stc_simd_reduce_min_f32(minmax_vals, ARRAY_LEN(minmax_vals)) == minv);
		assert(stc_simd_reduce_max_f32(minmax_vals, ARRAY_LEN(minmax_vals)) == maxv);
	}
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	test_i8();
	test_i16();
	test_i32();
	test_i64();
	test_f32();

	printf("SIMD full sweep OK on AVX2\n");
	return 0;
}
