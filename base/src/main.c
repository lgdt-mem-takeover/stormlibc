#define STORMC_ALLOCATOR
#include "/data/2026-projs/c/stormlibc/stormc_header.h"

static u64 scalar_count_lt_i32(const i32 *a, const i32 v, const u64 len)
{
	u64 ct = 0;
	for (u64 i = 0; i < len; ++i) ct += (u64)(a[i] < v);
	return ct;
}

static u64 scalar_count_lt_f32(const f32 *a, const f32 v, const u64 len)
{
	u64 ct = 0;
	for (u64 i = 0; i < len; ++i) ct += (u64)(a[i] < v);
	return ct;
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	i32 hp[] = {130, 99, 80, 101, 76, 140, 22, 100, 5, 205, 99, 77};
	const u64 hp_len = (u64)(sizeof(hp) / sizeof(hp[0]));

	u64 simd_low_hp_ct = stc_simd_count_cmplt_scalar_i32(hp, 100, hp_len);
	u64 ref_low_hp_ct = scalar_count_lt_i32(hp, 100, hp_len);
	u64 first_low_hp = stc_simd_first_cmplt_scalar_i32(hp, 100, hp_len);
	u64 no_low_hp = stc_simd_first_cmplt_scalar_i32(hp, -1000, hp_len);

	i8 save_failed[] = {0, 0, 1, 0, 1, 1, 0, 0, 0, 1};
	const u64 save_len = (u64)(sizeof(save_failed) / sizeof(save_failed[0]));
	u64 failed_ct = stc_simd_count_true_i8(save_failed, save_len);
	u64 first_failed = stc_simd_first_true_i8(save_failed, save_len);

	f32 damage[] = {12.5f, 120.0f, 99.75f, 100.0f, 0.0f, 220.125f, 88.0f, -1.0f};
	const u64 dmg_len = (u64)(sizeof(damage) / sizeof(damage[0]));
	u64 simd_low_dmg_ct = stc_simd_count_cmplt_scalar_f32(damage, 100.0f, dmg_len);
	u64 ref_low_dmg_ct = scalar_count_lt_f32(damage, 100.0f, dmg_len);
	u64 first_low_dmg = stc_simd_first_cmplt_scalar_f32(damage, 100.0f, dmg_len);
	u64 no_low_dmg = stc_simd_first_cmplt_scalar_f32(damage, -1000.0f, dmg_len);
	u64 dmg_nonzero_ct = stc_simd_count_true_f32(damage, dmg_len);

	assert(simd_low_hp_ct == ref_low_hp_ct);
	assert(first_low_hp == 1);
	assert(no_low_hp == (u64)-1);
	assert(failed_ct == 4);
	assert(first_failed == 2);
	assert(stc_simd_any_true_i8(save_failed, save_len));
	assert(simd_low_dmg_ct == ref_low_dmg_ct);
	assert(first_low_dmg == 0);
	assert(no_low_dmg == (u64)-1);
	assert(dmg_nonzero_ct == 7);

	printf("SIMD reducers OK: hp_lt_100=%llu first_hp_lt_100=%llu failed_ct=%llu first_failed=%llu dmg_lt_100=%llu first_dmg_lt_100=%llu\n",
		(unsigned long long)simd_low_hp_ct,
		(unsigned long long)first_low_hp,
		(unsigned long long)failed_ct,
		(unsigned long long)first_failed,
		(unsigned long long)simd_low_dmg_ct,
		(unsigned long long)first_low_dmg);

	return 0;
}
