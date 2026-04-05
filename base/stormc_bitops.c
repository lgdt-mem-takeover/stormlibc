#pragma once
#include "/data/2026-projs/c/stormlibc/stormc_header.h"

static inline u32 sla_u32(const u32 arg, stc_byte shift);
static inline u32 sra_u32(const u32 arg, stc_byte shift);
static inline u32 cmpnz_u32(const u32 arg);
static inline u32 select_u32(const u32 mask, const u32 arg1, const u32 arg2);


u32 sla_u32(const u32 arg, stc_byte shift)
{
	return (u32)((i32)arg << shift);
}

u32 sra_u32(const u32 arg, stc_byte shift)
{
	return (u32)((i32)arg >> shift);
}


u32 cmpnz_u32(const u32 arg)
{
	const u32 arg_snz = (arg) | (-arg);

	const u32 arg_snz_sat = sra_u32(arg_snz, 31);

	return arg_snz_sat;
}


u32 select_u32(const u32 mask, const u32 arg1, const u32 arg2)
{
	return ((arg1 & mask ) | (arg2 & ~(mask)));
}

u64 sla_u64(const u64 arg, stc_byte shift)
{
	return (u64)((i64)arg << shift);
}

u64 sra_u64(const u64 arg, stc_byte shift)
{
	return (u64)((i64)arg >> shift);
}

u64 cmpnz_u64(const u64 arg)
{
	const u64 arg_snz = (arg) | (-(i64)arg);
	const u64 arg_snz_sat = sra_u64(arg_snz, 63);
	return arg_snz_sat;
}

u64 select_u64(const u64 mask, const u64 arg1, const u64 arg2)
{
	return ((arg1 & mask) | (arg2 & ~(mask)));
}
