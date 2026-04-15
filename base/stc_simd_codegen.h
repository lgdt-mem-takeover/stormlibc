#pragma once

#if defined(__wasm_simd128__)
#define LANES_U8	16
#define LANES_U16	8
#define LANES_U32	4
#define LANES_U64	2
#define LANES_I8	16
#define LANES_I16	8
#define LANES_I32	4
#define LANES_I64	2
#define LANES_F32	4
#elif defined(__AVX2__)
#define LANES_U8	32
#define LANES_U16	16
#define LANES_U32	8
#define LANES_U64	4
#define LANES_I8	32
#define LANES_I16	16
#define LANES_I32	8
#define LANES_I64	4
#define LANES_F32	8
#elif defined(__SSE4_2__)
#define LANES_U8	16
#define LANES_U16	8
#define LANES_U32	4
#define LANES_U64	2
#define LANES_I8	16
#define LANES_I16	8
#define LANES_I32	4
#define LANES_I64	2
#define LANES_F32	4
#else
#  error "No SIMD backend enabled"
#endif

static inline i8 *stc_simd_add_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len);
static inline i8 *stc_simd_sub_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len);
static inline i16 *stc_simd_add_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len);
static inline i16 *stc_simd_mul_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len);
static inline i16 *stc_simd_sub_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len);
static inline i32 *stc_simd_add_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len);
static inline i32 *stc_simd_mul_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len);
static inline i32 *stc_simd_sub_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len);
static inline i64 *stc_simd_add_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len);
static inline i64 *stc_simd_sub_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len);
static inline f32 *stc_simd_add_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len);
static inline f32 *stc_simd_mul_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len);
static inline f32 *stc_simd_sub_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len);
static inline f32 *stc_simd_div_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len);
static inline i8 *stc_simd_shl_i8(i8 * restrict out, const i8 * restrict a, const u32 shift_by, const u64 len);
static inline i8 *stc_simd_shr_i8(i8 * restrict out, const i8 * restrict a, const u32 shift_by, const u64 len);
static inline i16 *stc_simd_shl_i16(i16 * restrict out, const i16 * restrict a, const u32 shift_by, const u64 len);
static inline i16 *stc_simd_shr_i16(i16 * restrict out, const i16 * restrict a, const u32 shift_by, const u64 len);
static inline i32 *stc_simd_shl_i32(i32 * restrict out, const i32 * restrict a, const u32 shift_by, const u64 len);
static inline i32 *stc_simd_shr_i32(i32 * restrict out, const i32 * restrict a, const u32 shift_by, const u64 len);
static inline i64 *stc_simd_shl_i64(i64 * restrict out, const i64 * restrict a, const u32 shift_by, const u64 len);
static inline i64 *stc_simd_shr_i64(i64 * restrict out, const i64 * restrict a, const u32 shift_by, const u64 len);
static inline i8 *stc_simd_and_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len);
static inline i8 *stc_simd_or_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len);
static inline i8 *stc_simd_xor_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len);
static inline i8 *stc_simd_andnot_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len);
static inline i16 *stc_simd_and_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len);
static inline i16 *stc_simd_or_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len);
static inline i16 *stc_simd_xor_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len);
static inline i16 *stc_simd_andnot_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len);
static inline i32 *stc_simd_and_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len);
static inline i32 *stc_simd_or_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len);
static inline i32 *stc_simd_xor_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len);
static inline i32 *stc_simd_andnot_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len);
static inline i64 *stc_simd_and_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len);
static inline i64 *stc_simd_or_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len);
static inline i64 *stc_simd_xor_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len);
static inline i64 *stc_simd_andnot_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len);
static inline f32 *stc_simd_and_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len);
static inline f32 *stc_simd_or_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len);
static inline f32 *stc_simd_xor_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len);
static inline f32 *stc_simd_andnot_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len);
static inline i8 *stc_simd_not_i8(i8 * restrict out, const i8 * restrict a, const u64 len);
static inline i16 *stc_simd_not_i16(i16 * restrict out, const i16 * restrict a, const u64 len);
static inline i32 *stc_simd_not_i32(i32 * restrict out, const i32 * restrict a, const u64 len);
static inline i64 *stc_simd_not_i64(i64 * restrict out, const i64 * restrict a, const u64 len);
static inline f32 *stc_simd_not_f32(f32 * restrict out, const f32 * restrict a, const u64 len);
static inline i8 *stc_simd_cmpeq_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len);
static inline i8 *stc_simd_cmpne_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len);
static inline i8 *stc_simd_cmplt_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len);
static inline i8 *stc_simd_cmpgt_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len);
static inline i8 *stc_simd_cmple_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len);
static inline i8 *stc_simd_cmpge_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len);
static inline i16 *stc_simd_cmpeq_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len);
static inline i16 *stc_simd_cmpne_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len);
static inline i16 *stc_simd_cmplt_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len);
static inline i16 *stc_simd_cmpgt_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len);
static inline i16 *stc_simd_cmple_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len);
static inline i16 *stc_simd_cmpge_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len);
static inline i32 *stc_simd_cmpeq_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len);
static inline i32 *stc_simd_cmpne_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len);
static inline i32 *stc_simd_cmplt_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len);
static inline i32 *stc_simd_cmpgt_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len);
static inline i32 *stc_simd_cmple_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len);
static inline i32 *stc_simd_cmpge_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len);
static inline i64 *stc_simd_cmpeq_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len);
static inline i64 *stc_simd_cmpne_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len);
static inline i64 *stc_simd_cmplt_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len);
static inline i64 *stc_simd_cmpgt_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len);
static inline i64 *stc_simd_cmple_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len);
static inline i64 *stc_simd_cmpge_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len);
static inline f32 *stc_simd_cmpeq_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len);
static inline f32 *stc_simd_cmpne_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len);
static inline f32 *stc_simd_cmplt_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len);
static inline f32 *stc_simd_cmpgt_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len);
static inline f32 *stc_simd_cmple_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len);
static inline f32 *stc_simd_cmpge_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len);
static inline i8 *stc_simd_splat_i8(i8 * restrict out, const i8 value, const u64 len);
static inline i16 *stc_simd_splat_i16(i16 * restrict out, const i16 value, const u64 len);
static inline i32 *stc_simd_splat_i32(i32 * restrict out, const i32 value, const u64 len);
static inline i64 *stc_simd_splat_i64(i64 * restrict out, const i64 value, const u64 len);
static inline f32 *stc_simd_splat_f32(f32 * restrict out, const f32 value, const u64 len);
static inline u64 stc_simd_bitmask_i8(const i8 * restrict a, const u64 len);
static inline u64 stc_simd_bitmask_i16(const i16 * restrict a, const u64 len);
static inline u64 stc_simd_bitmask_i32(const i32 * restrict a, const u64 len);
static inline u64 stc_simd_bitmask_i64(const i64 * restrict a, const u64 len);
static inline u64 stc_simd_bitmask_f32(const f32 * restrict a, const u64 len);
static inline bool stc_simd_all_true_i8(const i8 * restrict a, const u64 len);
static inline bool stc_simd_all_true_i16(const i16 * restrict a, const u64 len);
static inline bool stc_simd_all_true_i32(const i32 * restrict a, const u64 len);
static inline bool stc_simd_all_true_i64(const i64 * restrict a, const u64 len);
static inline bool stc_simd_all_true_f32(const f32 * restrict a, const u64 len);
static inline bool stc_simd_any_true_i8(const i8 * restrict a, const u64 len);
static inline bool stc_simd_any_true_i16(const i16 * restrict a, const u64 len);
static inline bool stc_simd_any_true_i32(const i32 * restrict a, const u64 len);
static inline bool stc_simd_any_true_i64(const i64 * restrict a, const u64 len);
static inline bool stc_simd_any_true_f32(const f32 * restrict a, const u64 len);
static inline i32 *stc_simd_min_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len);
static inline i32 *stc_simd_max_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len);
static inline f32 *stc_simd_min_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len);
static inline f32 *stc_simd_max_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len);
static inline u64 stc_simd_count_true_i8(const i8 * restrict a, const u64 len);
static inline u64 stc_simd_count_true_i16(const i16 * restrict a, const u64 len);
static inline u64 stc_simd_count_true_i32(const i32 * restrict a, const u64 len);
static inline u64 stc_simd_count_true_i64(const i64 * restrict a, const u64 len);
static inline u64 stc_simd_count_true_f32(const f32 * restrict a, const u64 len);
static inline u64 stc_simd_first_true_i8(const i8 * restrict a, const u64 len);
static inline u64 stc_simd_first_true_i16(const i16 * restrict a, const u64 len);
static inline u64 stc_simd_first_true_i32(const i32 * restrict a, const u64 len);
static inline u64 stc_simd_first_true_i64(const i64 * restrict a, const u64 len);
static inline u64 stc_simd_first_true_f32(const f32 * restrict a, const u64 len);
static inline u64 stc_simd_count_cmpeq_scalar_i8(const i8 * restrict a, const i8 value, const u64 len);
static inline u64 stc_simd_count_cmpne_scalar_i8(const i8 * restrict a, const i8 value, const u64 len);
static inline u64 stc_simd_count_cmplt_scalar_i8(const i8 * restrict a, const i8 value, const u64 len);
static inline u64 stc_simd_count_cmpgt_scalar_i8(const i8 * restrict a, const i8 value, const u64 len);
static inline u64 stc_simd_count_cmple_scalar_i8(const i8 * restrict a, const i8 value, const u64 len);
static inline u64 stc_simd_count_cmpge_scalar_i8(const i8 * restrict a, const i8 value, const u64 len);
static inline u64 stc_simd_count_cmpeq_scalar_i16(const i16 * restrict a, const i16 value, const u64 len);
static inline u64 stc_simd_count_cmpne_scalar_i16(const i16 * restrict a, const i16 value, const u64 len);
static inline u64 stc_simd_count_cmplt_scalar_i16(const i16 * restrict a, const i16 value, const u64 len);
static inline u64 stc_simd_count_cmpgt_scalar_i16(const i16 * restrict a, const i16 value, const u64 len);
static inline u64 stc_simd_count_cmple_scalar_i16(const i16 * restrict a, const i16 value, const u64 len);
static inline u64 stc_simd_count_cmpge_scalar_i16(const i16 * restrict a, const i16 value, const u64 len);
static inline u64 stc_simd_count_cmpeq_scalar_i32(const i32 * restrict a, const i32 value, const u64 len);
static inline u64 stc_simd_count_cmpne_scalar_i32(const i32 * restrict a, const i32 value, const u64 len);
static inline u64 stc_simd_count_cmplt_scalar_i32(const i32 * restrict a, const i32 value, const u64 len);
static inline u64 stc_simd_count_cmpgt_scalar_i32(const i32 * restrict a, const i32 value, const u64 len);
static inline u64 stc_simd_count_cmple_scalar_i32(const i32 * restrict a, const i32 value, const u64 len);
static inline u64 stc_simd_count_cmpge_scalar_i32(const i32 * restrict a, const i32 value, const u64 len);
static inline u64 stc_simd_count_cmpeq_scalar_i64(const i64 * restrict a, const i64 value, const u64 len);
static inline u64 stc_simd_count_cmpne_scalar_i64(const i64 * restrict a, const i64 value, const u64 len);
static inline u64 stc_simd_count_cmplt_scalar_i64(const i64 * restrict a, const i64 value, const u64 len);
static inline u64 stc_simd_count_cmpgt_scalar_i64(const i64 * restrict a, const i64 value, const u64 len);
static inline u64 stc_simd_count_cmple_scalar_i64(const i64 * restrict a, const i64 value, const u64 len);
static inline u64 stc_simd_count_cmpge_scalar_i64(const i64 * restrict a, const i64 value, const u64 len);
static inline u64 stc_simd_count_cmpeq_scalar_f32(const f32 * restrict a, const f32 value, const u64 len);
static inline u64 stc_simd_count_cmpne_scalar_f32(const f32 * restrict a, const f32 value, const u64 len);
static inline u64 stc_simd_count_cmplt_scalar_f32(const f32 * restrict a, const f32 value, const u64 len);
static inline u64 stc_simd_count_cmpgt_scalar_f32(const f32 * restrict a, const f32 value, const u64 len);
static inline u64 stc_simd_count_cmple_scalar_f32(const f32 * restrict a, const f32 value, const u64 len);
static inline u64 stc_simd_count_cmpge_scalar_f32(const f32 * restrict a, const f32 value, const u64 len);
static inline u64 stc_simd_first_cmpeq_scalar_i8(const i8 * restrict a, const i8 value, const u64 len);
static inline u64 stc_simd_first_cmpne_scalar_i8(const i8 * restrict a, const i8 value, const u64 len);
static inline u64 stc_simd_first_cmplt_scalar_i8(const i8 * restrict a, const i8 value, const u64 len);
static inline u64 stc_simd_first_cmpgt_scalar_i8(const i8 * restrict a, const i8 value, const u64 len);
static inline u64 stc_simd_first_cmple_scalar_i8(const i8 * restrict a, const i8 value, const u64 len);
static inline u64 stc_simd_first_cmpge_scalar_i8(const i8 * restrict a, const i8 value, const u64 len);
static inline u64 stc_simd_first_cmpeq_scalar_i16(const i16 * restrict a, const i16 value, const u64 len);
static inline u64 stc_simd_first_cmpne_scalar_i16(const i16 * restrict a, const i16 value, const u64 len);
static inline u64 stc_simd_first_cmplt_scalar_i16(const i16 * restrict a, const i16 value, const u64 len);
static inline u64 stc_simd_first_cmpgt_scalar_i16(const i16 * restrict a, const i16 value, const u64 len);
static inline u64 stc_simd_first_cmple_scalar_i16(const i16 * restrict a, const i16 value, const u64 len);
static inline u64 stc_simd_first_cmpge_scalar_i16(const i16 * restrict a, const i16 value, const u64 len);
static inline u64 stc_simd_first_cmpeq_scalar_i32(const i32 * restrict a, const i32 value, const u64 len);
static inline u64 stc_simd_first_cmpne_scalar_i32(const i32 * restrict a, const i32 value, const u64 len);
static inline u64 stc_simd_first_cmplt_scalar_i32(const i32 * restrict a, const i32 value, const u64 len);
static inline u64 stc_simd_first_cmpgt_scalar_i32(const i32 * restrict a, const i32 value, const u64 len);
static inline u64 stc_simd_first_cmple_scalar_i32(const i32 * restrict a, const i32 value, const u64 len);
static inline u64 stc_simd_first_cmpge_scalar_i32(const i32 * restrict a, const i32 value, const u64 len);
static inline u64 stc_simd_first_cmpeq_scalar_i64(const i64 * restrict a, const i64 value, const u64 len);
static inline u64 stc_simd_first_cmpne_scalar_i64(const i64 * restrict a, const i64 value, const u64 len);
static inline u64 stc_simd_first_cmplt_scalar_i64(const i64 * restrict a, const i64 value, const u64 len);
static inline u64 stc_simd_first_cmpgt_scalar_i64(const i64 * restrict a, const i64 value, const u64 len);
static inline u64 stc_simd_first_cmple_scalar_i64(const i64 * restrict a, const i64 value, const u64 len);
static inline u64 stc_simd_first_cmpge_scalar_i64(const i64 * restrict a, const i64 value, const u64 len);
static inline u64 stc_simd_first_cmpeq_scalar_f32(const f32 * restrict a, const f32 value, const u64 len);
static inline u64 stc_simd_first_cmpne_scalar_f32(const f32 * restrict a, const f32 value, const u64 len);
static inline u64 stc_simd_first_cmplt_scalar_f32(const f32 * restrict a, const f32 value, const u64 len);
static inline u64 stc_simd_first_cmpgt_scalar_f32(const f32 * restrict a, const f32 value, const u64 len);
static inline u64 stc_simd_first_cmple_scalar_f32(const f32 * restrict a, const f32 value, const u64 len);
static inline u64 stc_simd_first_cmpge_scalar_f32(const f32 * restrict a, const f32 value, const u64 len);
static inline i8 stc_simd_reduce_add_i8(const i8 * restrict a, const u64 len);
static inline i16 stc_simd_reduce_add_i16(const i16 * restrict a, const u64 len);
static inline i16 stc_simd_reduce_mul_i16(const i16 * restrict a, const u64 len);
static inline i32 stc_simd_reduce_add_i32(const i32 * restrict a, const u64 len);
static inline i32 stc_simd_reduce_mul_i32(const i32 * restrict a, const u64 len);
static inline i32 stc_simd_reduce_min_i32(const i32 * restrict a, const u64 len);
static inline i32 stc_simd_reduce_max_i32(const i32 * restrict a, const u64 len);
static inline i64 stc_simd_reduce_add_i64(const i64 * restrict a, const u64 len);
static inline f32 stc_simd_reduce_add_f32(const f32 * restrict a, const u64 len);
static inline f32 stc_simd_reduce_mul_f32(const f32 * restrict a, const u64 len);
static inline f32 stc_simd_reduce_min_f32(const f32 * restrict a, const u64 len);
static inline f32 stc_simd_reduce_max_f32(const f32 * restrict a, const u64 len);

#if defined(__wasm_simd128__)
static inline i8 *stc_simd_add_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 vb = wasm_v128_load((const simd_i8*)(b + i));
        simd_i8 vr = wasm_i8x16_add(va, vb);
        wasm_v128_store((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] + b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_sub_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 vb = wasm_v128_load((const simd_i8*)(b + i));
        simd_i8 vr = wasm_i8x16_sub(va, vb);
        wasm_v128_store((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] - b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_shl_i8(i8 * restrict out, const i8 * restrict a, const u32 shift_by, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 vr = wasm_i8x16_shl(va, shift_by);
        wasm_v128_store((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] << shift_by;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_shr_i8(i8 * restrict out, const i8 * restrict a, const u32 shift_by, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 vr = wasm_i8x16_shr(va, shift_by);
        wasm_v128_store((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] >> shift_by;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_and_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 vb = wasm_v128_load((const simd_i8*)(b + i));
        simd_i8 vr = wasm_v128_and(va, vb);
        wasm_v128_store((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_or_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 vb = wasm_v128_load((const simd_i8*)(b + i));
        simd_i8 vr = wasm_v128_or(va, vb);
        wasm_v128_store((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] | b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_xor_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 vb = wasm_v128_load((const simd_i8*)(b + i));
        simd_i8 vr = wasm_v128_xor(va, vb);
        wasm_v128_store((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] ^ b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_andnot_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 vb = wasm_v128_load((const simd_i8*)(b + i));
        simd_i8 vr = wasm_v128_andnot(va, vb);
        wasm_v128_store((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (~a[i]) & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_not_i8(i8 * restrict out, const i8 * restrict a, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 vr = wasm_v128_not(va);
        wasm_v128_store((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = ~a[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_cmpeq_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 vb = wasm_v128_load((const simd_i8*)(b + i));
        simd_i8 vr = wasm_i8x16_eq(va, vb);
        wasm_v128_store((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] == b[i]) ? (i8)~0 : (i8)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_cmpne_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 vb = wasm_v128_load((const simd_i8*)(b + i));
        simd_i8 vr = wasm_i8x16_ne(va, vb);
        wasm_v128_store((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] != b[i]) ? (i8)~0 : (i8)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_cmplt_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 vb = wasm_v128_load((const simd_i8*)(b + i));
        simd_i8 vr = wasm_i8x16_lt(va, vb);
        wasm_v128_store((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] < b[i]) ? (i8)~0 : (i8)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_cmpgt_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 vb = wasm_v128_load((const simd_i8*)(b + i));
        simd_i8 vr = wasm_i8x16_gt(va, vb);
        wasm_v128_store((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] > b[i]) ? (i8)~0 : (i8)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_cmple_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 vb = wasm_v128_load((const simd_i8*)(b + i));
        simd_i8 vr = wasm_i8x16_le(va, vb);
        wasm_v128_store((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] <= b[i]) ? (i8)~0 : (i8)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_cmpge_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 vb = wasm_v128_load((const simd_i8*)(b + i));
        simd_i8 vr = wasm_i8x16_ge(va, vb);
        wasm_v128_store((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] >= b[i]) ? (i8)~0 : (i8)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_splat_i8(i8 * restrict out, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i8 vv = wasm_i8x16_splat(value);
    for (; (i + width) <= len; i += width) {
        wasm_v128_store((simd_i8*)(out + i), vv);
    }

    while (rem) {
        out[i] = value;
        ++i;
        --rem;
    }

    return out;
}
static inline u64 stc_simd_bitmask_i8(const i8 * restrict a, const u64 len)
{
    u64 out_mask = 0;
    const u64 n = len < 64 ? len : 64;
    for (u64 i = 0; i < n; ++i) {
        out_mask |= ((u64)((((u8)a[i]) >> (8 - 1)) & 1u) << i);
    }
    return out_mask;
}
static inline bool stc_simd_all_true_i8(const i8 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (!a[i]) return false;
    }
    return true;
}
static inline bool stc_simd_any_true_i8(const i8 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i]) return true;
    }
    return false;
}
static inline u64 stc_simd_count_true_i8(const i8 * restrict a, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] != 0);
    }
    return ct;
}
static inline u64 stc_simd_first_true_i8(const i8 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] != 0) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_count_cmpeq_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    u64 ct = 0;
    const simd_i8 vv = wasm_i8x16_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_eq(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i8*)(a + i + width));
        mask = wasm_i8x16_eq(va, vv);
        bits = (u32)(wasm_i8x16_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_eq(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] == value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpne_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    u64 ct = 0;
    const simd_i8 vv = wasm_i8x16_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_ne(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i8*)(a + i + width));
        mask = wasm_i8x16_ne(va, vv);
        bits = (u32)(wasm_i8x16_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_ne(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] != value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmplt_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    u64 ct = 0;
    const simd_i8 vv = wasm_i8x16_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_lt(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i8*)(a + i + width));
        mask = wasm_i8x16_lt(va, vv);
        bits = (u32)(wasm_i8x16_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_lt(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] < value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpgt_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    u64 ct = 0;
    const simd_i8 vv = wasm_i8x16_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_gt(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i8*)(a + i + width));
        mask = wasm_i8x16_gt(va, vv);
        bits = (u32)(wasm_i8x16_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_gt(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] > value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmple_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    u64 ct = 0;
    const simd_i8 vv = wasm_i8x16_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_le(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i8*)(a + i + width));
        mask = wasm_i8x16_le(va, vv);
        bits = (u32)(wasm_i8x16_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_le(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] <= value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpge_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    u64 ct = 0;
    const simd_i8 vv = wasm_i8x16_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_ge(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i8*)(a + i + width));
        mask = wasm_i8x16_ge(va, vv);
        bits = (u32)(wasm_i8x16_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_ge(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] >= value);
    }

    return ct;
}
static inline u64 stc_simd_first_cmpeq_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    const simd_i8 vv = wasm_i8x16_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_eq(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i8*)(a + i + width));
        mask = wasm_i8x16_eq(va, vv);
        bits = (u32)(wasm_i8x16_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_eq(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] == value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpne_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    const simd_i8 vv = wasm_i8x16_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_ne(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i8*)(a + i + width));
        mask = wasm_i8x16_ne(va, vv);
        bits = (u32)(wasm_i8x16_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_ne(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] != value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmplt_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    const simd_i8 vv = wasm_i8x16_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_lt(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i8*)(a + i + width));
        mask = wasm_i8x16_lt(va, vv);
        bits = (u32)(wasm_i8x16_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_lt(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] < value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpgt_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    const simd_i8 vv = wasm_i8x16_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_gt(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i8*)(a + i + width));
        mask = wasm_i8x16_gt(va, vv);
        bits = (u32)(wasm_i8x16_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_gt(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] > value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmple_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    const simd_i8 vv = wasm_i8x16_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_le(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i8*)(a + i + width));
        mask = wasm_i8x16_le(va, vv);
        bits = (u32)(wasm_i8x16_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_le(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] <= value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpge_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    const simd_i8 vv = wasm_i8x16_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_ge(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i8*)(a + i + width));
        mask = wasm_i8x16_ge(va, vv);
        bits = (u32)(wasm_i8x16_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        simd_i8 mask = wasm_i8x16_ge(va, vv);
        u32 bits = (u32)(wasm_i8x16_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] >= value) return i;
    }
    return (u64)-1;
}
static inline i8 stc_simd_reduce_add_i8(const i8 * restrict a, const u64 len)
{
    if (!len) return (i8)0;

    const u64 width = 16;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) i8 tmp[LANES_I8];
    simd_i8 vacc = wasm_i8x16_splat(0);

    for (; (i + width) <= len; i += width) {
        simd_i8 va = wasm_v128_load((const simd_i8*)(a + i));
        vacc = wasm_i8x16_add(vacc, va);
    }

    wasm_v128_store((simd_i8*)tmp, vacc);
    i8 acc = (i8)0;
    for (u64 lane = 0; lane < LANES_I8; ++lane) {
        acc = acc + tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc + a[i];
    }

    return acc;
}
static inline i16 *stc_simd_add_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 vb = wasm_v128_load((const simd_i16*)(b + i));
        simd_i16 vr = wasm_i16x8_add(va, vb);
        wasm_v128_store((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] + b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_mul_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 vb = wasm_v128_load((const simd_i16*)(b + i));
        simd_i16 vr = wasm_i16x8_mul(va, vb);
        wasm_v128_store((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] * b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_sub_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 vb = wasm_v128_load((const simd_i16*)(b + i));
        simd_i16 vr = wasm_i16x8_sub(va, vb);
        wasm_v128_store((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] - b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_shl_i16(i16 * restrict out, const i16 * restrict a, const u32 shift_by, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 vr = wasm_i16x8_shl(va, shift_by);
        wasm_v128_store((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] << shift_by;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_shr_i16(i16 * restrict out, const i16 * restrict a, const u32 shift_by, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 vr = wasm_i16x8_shr(va, shift_by);
        wasm_v128_store((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] >> shift_by;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_and_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 vb = wasm_v128_load((const simd_i16*)(b + i));
        simd_i16 vr = wasm_v128_and(va, vb);
        wasm_v128_store((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_or_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 vb = wasm_v128_load((const simd_i16*)(b + i));
        simd_i16 vr = wasm_v128_or(va, vb);
        wasm_v128_store((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] | b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_xor_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 vb = wasm_v128_load((const simd_i16*)(b + i));
        simd_i16 vr = wasm_v128_xor(va, vb);
        wasm_v128_store((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] ^ b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_andnot_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 vb = wasm_v128_load((const simd_i16*)(b + i));
        simd_i16 vr = wasm_v128_andnot(va, vb);
        wasm_v128_store((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (~a[i]) & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_not_i16(i16 * restrict out, const i16 * restrict a, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 vr = wasm_v128_not(va);
        wasm_v128_store((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = ~a[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_cmpeq_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 vb = wasm_v128_load((const simd_i16*)(b + i));
        simd_i16 vr = wasm_i16x8_eq(va, vb);
        wasm_v128_store((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] == b[i]) ? (i16)~0 : (i16)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_cmpne_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 vb = wasm_v128_load((const simd_i16*)(b + i));
        simd_i16 vr = wasm_i16x8_ne(va, vb);
        wasm_v128_store((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] != b[i]) ? (i16)~0 : (i16)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_cmplt_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 vb = wasm_v128_load((const simd_i16*)(b + i));
        simd_i16 vr = wasm_i16x8_lt(va, vb);
        wasm_v128_store((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] < b[i]) ? (i16)~0 : (i16)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_cmpgt_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 vb = wasm_v128_load((const simd_i16*)(b + i));
        simd_i16 vr = wasm_i16x8_gt(va, vb);
        wasm_v128_store((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] > b[i]) ? (i16)~0 : (i16)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_cmple_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 vb = wasm_v128_load((const simd_i16*)(b + i));
        simd_i16 vr = wasm_i16x8_le(va, vb);
        wasm_v128_store((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] <= b[i]) ? (i16)~0 : (i16)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_cmpge_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 vb = wasm_v128_load((const simd_i16*)(b + i));
        simd_i16 vr = wasm_i16x8_ge(va, vb);
        wasm_v128_store((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] >= b[i]) ? (i16)~0 : (i16)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_splat_i16(i16 * restrict out, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i16 vv = wasm_i16x8_splat(value);
    for (; (i + width) <= len; i += width) {
        wasm_v128_store((simd_i16*)(out + i), vv);
    }

    while (rem) {
        out[i] = value;
        ++i;
        --rem;
    }

    return out;
}
static inline u64 stc_simd_bitmask_i16(const i16 * restrict a, const u64 len)
{
    u64 out_mask = 0;
    const u64 n = len < 64 ? len : 64;
    for (u64 i = 0; i < n; ++i) {
        out_mask |= ((u64)((((u16)a[i]) >> (16 - 1)) & 1u) << i);
    }
    return out_mask;
}
static inline bool stc_simd_all_true_i16(const i16 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (!a[i]) return false;
    }
    return true;
}
static inline bool stc_simd_any_true_i16(const i16 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i]) return true;
    }
    return false;
}
static inline u64 stc_simd_count_true_i16(const i16 * restrict a, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] != 0);
    }
    return ct;
}
static inline u64 stc_simd_first_true_i16(const i16 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] != 0) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_count_cmpeq_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_i16 vv = wasm_i16x8_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_eq(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i16*)(a + i + width));
        mask = wasm_i16x8_eq(va, vv);
        bits = (u32)(wasm_i16x8_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_eq(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] == value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpne_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_i16 vv = wasm_i16x8_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_ne(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i16*)(a + i + width));
        mask = wasm_i16x8_ne(va, vv);
        bits = (u32)(wasm_i16x8_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_ne(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] != value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmplt_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_i16 vv = wasm_i16x8_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_lt(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i16*)(a + i + width));
        mask = wasm_i16x8_lt(va, vv);
        bits = (u32)(wasm_i16x8_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_lt(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] < value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpgt_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_i16 vv = wasm_i16x8_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_gt(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i16*)(a + i + width));
        mask = wasm_i16x8_gt(va, vv);
        bits = (u32)(wasm_i16x8_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_gt(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] > value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmple_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_i16 vv = wasm_i16x8_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_le(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i16*)(a + i + width));
        mask = wasm_i16x8_le(va, vv);
        bits = (u32)(wasm_i16x8_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_le(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] <= value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpge_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_i16 vv = wasm_i16x8_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_ge(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i16*)(a + i + width));
        mask = wasm_i16x8_ge(va, vv);
        bits = (u32)(wasm_i16x8_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_ge(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] >= value);
    }

    return ct;
}
static inline u64 stc_simd_first_cmpeq_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_i16 vv = wasm_i16x8_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_eq(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i16*)(a + i + width));
        mask = wasm_i16x8_eq(va, vv);
        bits = (u32)(wasm_i16x8_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_eq(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] == value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpne_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_i16 vv = wasm_i16x8_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_ne(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i16*)(a + i + width));
        mask = wasm_i16x8_ne(va, vv);
        bits = (u32)(wasm_i16x8_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_ne(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] != value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmplt_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_i16 vv = wasm_i16x8_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_lt(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i16*)(a + i + width));
        mask = wasm_i16x8_lt(va, vv);
        bits = (u32)(wasm_i16x8_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_lt(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] < value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpgt_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_i16 vv = wasm_i16x8_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_gt(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i16*)(a + i + width));
        mask = wasm_i16x8_gt(va, vv);
        bits = (u32)(wasm_i16x8_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_gt(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] > value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmple_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_i16 vv = wasm_i16x8_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_le(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i16*)(a + i + width));
        mask = wasm_i16x8_le(va, vv);
        bits = (u32)(wasm_i16x8_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_le(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] <= value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpge_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_i16 vv = wasm_i16x8_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_ge(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i16*)(a + i + width));
        mask = wasm_i16x8_ge(va, vv);
        bits = (u32)(wasm_i16x8_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        simd_i16 mask = wasm_i16x8_ge(va, vv);
        u32 bits = (u32)(wasm_i16x8_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] >= value) return i;
    }
    return (u64)-1;
}
static inline i16 stc_simd_reduce_add_i16(const i16 * restrict a, const u64 len)
{
    if (!len) return (i16)0;

    const u64 width = 8;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) i16 tmp[LANES_I16];
    simd_i16 vacc = wasm_i16x8_splat(0);

    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        vacc = wasm_i16x8_add(vacc, va);
    }

    wasm_v128_store((simd_i16*)tmp, vacc);
    i16 acc = (i16)0;
    for (u64 lane = 0; lane < LANES_I16; ++lane) {
        acc = acc + tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc + a[i];
    }

    return acc;
}
static inline i16 stc_simd_reduce_mul_i16(const i16 * restrict a, const u64 len)
{
    if (!len) return (i16)1;

    const u64 width = 8;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) i16 tmp[LANES_I16];
    simd_i16 vacc = wasm_i16x8_splat(1);

    for (; (i + width) <= len; i += width) {
        simd_i16 va = wasm_v128_load((const simd_i16*)(a + i));
        vacc = wasm_i16x8_mul(vacc, va);
    }

    wasm_v128_store((simd_i16*)tmp, vacc);
    i16 acc = (i16)1;
    for (u64 lane = 0; lane < LANES_I16; ++lane) {
        acc = acc * tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc * a[i];
    }

    return acc;
}
static inline i32 *stc_simd_add_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 vb = wasm_v128_load((const simd_i32*)(b + i));
        simd_i32 vr = wasm_i32x4_add(va, vb);
        wasm_v128_store((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] + b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_mul_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 vb = wasm_v128_load((const simd_i32*)(b + i));
        simd_i32 vr = wasm_i32x4_mul(va, vb);
        wasm_v128_store((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] * b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_sub_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 vb = wasm_v128_load((const simd_i32*)(b + i));
        simd_i32 vr = wasm_i32x4_sub(va, vb);
        wasm_v128_store((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] - b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_shl_i32(i32 * restrict out, const i32 * restrict a, const u32 shift_by, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 vr = wasm_i32x4_shl(va, shift_by);
        wasm_v128_store((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] << shift_by;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_shr_i32(i32 * restrict out, const i32 * restrict a, const u32 shift_by, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 vr = wasm_i32x4_shr(va, shift_by);
        wasm_v128_store((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] >> shift_by;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_and_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 vb = wasm_v128_load((const simd_i32*)(b + i));
        simd_i32 vr = wasm_v128_and(va, vb);
        wasm_v128_store((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_or_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 vb = wasm_v128_load((const simd_i32*)(b + i));
        simd_i32 vr = wasm_v128_or(va, vb);
        wasm_v128_store((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] | b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_xor_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 vb = wasm_v128_load((const simd_i32*)(b + i));
        simd_i32 vr = wasm_v128_xor(va, vb);
        wasm_v128_store((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] ^ b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_andnot_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 vb = wasm_v128_load((const simd_i32*)(b + i));
        simd_i32 vr = wasm_v128_andnot(va, vb);
        wasm_v128_store((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (~a[i]) & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_not_i32(i32 * restrict out, const i32 * restrict a, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 vr = wasm_v128_not(va);
        wasm_v128_store((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = ~a[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_cmpeq_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 vb = wasm_v128_load((const simd_i32*)(b + i));
        simd_i32 vr = wasm_i32x4_eq(va, vb);
        wasm_v128_store((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] == b[i]) ? (i32)~0 : (i32)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_cmpne_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 vb = wasm_v128_load((const simd_i32*)(b + i));
        simd_i32 vr = wasm_i32x4_ne(va, vb);
        wasm_v128_store((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] != b[i]) ? (i32)~0 : (i32)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_cmplt_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 vb = wasm_v128_load((const simd_i32*)(b + i));
        simd_i32 vr = wasm_i32x4_lt(va, vb);
        wasm_v128_store((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] < b[i]) ? (i32)~0 : (i32)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_cmpgt_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 vb = wasm_v128_load((const simd_i32*)(b + i));
        simd_i32 vr = wasm_i32x4_gt(va, vb);
        wasm_v128_store((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] > b[i]) ? (i32)~0 : (i32)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_cmple_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 vb = wasm_v128_load((const simd_i32*)(b + i));
        simd_i32 vr = wasm_i32x4_le(va, vb);
        wasm_v128_store((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] <= b[i]) ? (i32)~0 : (i32)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_cmpge_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 vb = wasm_v128_load((const simd_i32*)(b + i));
        simd_i32 vr = wasm_i32x4_ge(va, vb);
        wasm_v128_store((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] >= b[i]) ? (i32)~0 : (i32)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_splat_i32(i32 * restrict out, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i32 vv = wasm_i32x4_splat(value);
    for (; (i + width) <= len; i += width) {
        wasm_v128_store((simd_i32*)(out + i), vv);
    }

    while (rem) {
        out[i] = value;
        ++i;
        --rem;
    }

    return out;
}
static inline u64 stc_simd_bitmask_i32(const i32 * restrict a, const u64 len)
{
    u64 out_mask = 0;
    const u64 n = len < 64 ? len : 64;
    for (u64 i = 0; i < n; ++i) {
        out_mask |= ((u64)((((u32)a[i]) >> (32 - 1)) & 1u) << i);
    }
    return out_mask;
}
static inline bool stc_simd_all_true_i32(const i32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (!a[i]) return false;
    }
    return true;
}
static inline bool stc_simd_any_true_i32(const i32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i]) return true;
    }
    return false;
}
static inline i32 *stc_simd_min_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 vb = wasm_v128_load((const simd_i32*)(b + i));
        simd_i32 vr = wasm_i32x4_min(va, vb);
        wasm_v128_store((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] < b[i] ? a[i] : b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_max_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 vb = wasm_v128_load((const simd_i32*)(b + i));
        simd_i32 vr = wasm_i32x4_max(va, vb);
        wasm_v128_store((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] > b[i] ? a[i] : b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline u64 stc_simd_count_true_i32(const i32 * restrict a, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] != 0);
    }
    return ct;
}
static inline u64 stc_simd_first_true_i32(const i32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] != 0) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_count_cmpeq_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_i32 vv = wasm_i32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_eq(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i32*)(a + i + width));
        mask = wasm_i32x4_eq(va, vv);
        bits = (u32)(wasm_i32x4_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_eq(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] == value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpne_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_i32 vv = wasm_i32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_ne(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i32*)(a + i + width));
        mask = wasm_i32x4_ne(va, vv);
        bits = (u32)(wasm_i32x4_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_ne(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] != value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmplt_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_i32 vv = wasm_i32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_lt(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i32*)(a + i + width));
        mask = wasm_i32x4_lt(va, vv);
        bits = (u32)(wasm_i32x4_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_lt(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] < value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpgt_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_i32 vv = wasm_i32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_gt(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i32*)(a + i + width));
        mask = wasm_i32x4_gt(va, vv);
        bits = (u32)(wasm_i32x4_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_gt(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] > value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmple_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_i32 vv = wasm_i32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_le(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i32*)(a + i + width));
        mask = wasm_i32x4_le(va, vv);
        bits = (u32)(wasm_i32x4_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_le(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] <= value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpge_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_i32 vv = wasm_i32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_ge(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i32*)(a + i + width));
        mask = wasm_i32x4_ge(va, vv);
        bits = (u32)(wasm_i32x4_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_ge(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] >= value);
    }

    return ct;
}
static inline u64 stc_simd_first_cmpeq_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_i32 vv = wasm_i32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_eq(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i32*)(a + i + width));
        mask = wasm_i32x4_eq(va, vv);
        bits = (u32)(wasm_i32x4_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_eq(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] == value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpne_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_i32 vv = wasm_i32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_ne(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i32*)(a + i + width));
        mask = wasm_i32x4_ne(va, vv);
        bits = (u32)(wasm_i32x4_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_ne(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] != value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmplt_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_i32 vv = wasm_i32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_lt(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i32*)(a + i + width));
        mask = wasm_i32x4_lt(va, vv);
        bits = (u32)(wasm_i32x4_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_lt(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] < value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpgt_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_i32 vv = wasm_i32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_gt(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i32*)(a + i + width));
        mask = wasm_i32x4_gt(va, vv);
        bits = (u32)(wasm_i32x4_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_gt(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] > value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmple_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_i32 vv = wasm_i32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_le(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i32*)(a + i + width));
        mask = wasm_i32x4_le(va, vv);
        bits = (u32)(wasm_i32x4_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_le(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] <= value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpge_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_i32 vv = wasm_i32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_ge(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i32*)(a + i + width));
        mask = wasm_i32x4_ge(va, vv);
        bits = (u32)(wasm_i32x4_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        simd_i32 mask = wasm_i32x4_ge(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] >= value) return i;
    }
    return (u64)-1;
}
static inline i32 stc_simd_reduce_add_i32(const i32 * restrict a, const u64 len)
{
    if (!len) return (i32)0;

    const u64 width = 4;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) i32 tmp[LANES_I32];
    simd_i32 vacc = wasm_i32x4_splat(0);

    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        vacc = wasm_i32x4_add(vacc, va);
    }

    wasm_v128_store((simd_i32*)tmp, vacc);
    i32 acc = (i32)0;
    for (u64 lane = 0; lane < LANES_I32; ++lane) {
        acc = acc + tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc + a[i];
    }

    return acc;
}
static inline i32 stc_simd_reduce_mul_i32(const i32 * restrict a, const u64 len)
{
    if (!len) return (i32)1;

    const u64 width = 4;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) i32 tmp[LANES_I32];
    simd_i32 vacc = wasm_i32x4_splat(1);

    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        vacc = wasm_i32x4_mul(vacc, va);
    }

    wasm_v128_store((simd_i32*)tmp, vacc);
    i32 acc = (i32)1;
    for (u64 lane = 0; lane < LANES_I32; ++lane) {
        acc = acc * tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc * a[i];
    }

    return acc;
}
static inline i32 stc_simd_reduce_min_i32(const i32 * restrict a, const u64 len)
{
    if (!len) return (i32)0;

    const u64 width = 4;
    u64 i = 1;
    __attribute__((aligned(STC_SIMD_ALIGN))) i32 tmp[LANES_I32];
    simd_i32 vacc = wasm_i32x4_splat(a[0]);

    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        vacc = wasm_i32x4_min(vacc, va);
    }

    wasm_v128_store((simd_i32*)tmp, vacc);
    i32 acc = a[0];
    for (u64 lane = 0; lane < LANES_I32; ++lane) {
        acc = acc < tmp[lane] ? acc : tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc < a[i] ? acc : a[i];
    }

    return acc;
}
static inline i32 stc_simd_reduce_max_i32(const i32 * restrict a, const u64 len)
{
    if (!len) return (i32)0;

    const u64 width = 4;
    u64 i = 1;
    __attribute__((aligned(STC_SIMD_ALIGN))) i32 tmp[LANES_I32];
    simd_i32 vacc = wasm_i32x4_splat(a[0]);

    for (; (i + width) <= len; i += width) {
        simd_i32 va = wasm_v128_load((const simd_i32*)(a + i));
        vacc = wasm_i32x4_max(vacc, va);
    }

    wasm_v128_store((simd_i32*)tmp, vacc);
    i32 acc = a[0];
    for (u64 lane = 0; lane < LANES_I32; ++lane) {
        acc = acc > tmp[lane] ? acc : tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc > a[i] ? acc : a[i];
    }

    return acc;
}
static inline i64 *stc_simd_add_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 vb = wasm_v128_load((const simd_i64*)(b + i));
        simd_i64 vr = wasm_i64x2_add(va, vb);
        wasm_v128_store((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] + b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_sub_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 vb = wasm_v128_load((const simd_i64*)(b + i));
        simd_i64 vr = wasm_i64x2_sub(va, vb);
        wasm_v128_store((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] - b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_shl_i64(i64 * restrict out, const i64 * restrict a, const u32 shift_by, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 vr = wasm_i64x2_shl(va, shift_by);
        wasm_v128_store((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] << shift_by;
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_shr_i64(i64 * restrict out, const i64 * restrict a, const u32 shift_by, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 vr = wasm_i64x2_shr(va, shift_by);
        wasm_v128_store((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] >> shift_by;
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_and_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 vb = wasm_v128_load((const simd_i64*)(b + i));
        simd_i64 vr = wasm_v128_and(va, vb);
        wasm_v128_store((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_or_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 vb = wasm_v128_load((const simd_i64*)(b + i));
        simd_i64 vr = wasm_v128_or(va, vb);
        wasm_v128_store((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] | b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_xor_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 vb = wasm_v128_load((const simd_i64*)(b + i));
        simd_i64 vr = wasm_v128_xor(va, vb);
        wasm_v128_store((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] ^ b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_andnot_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 vb = wasm_v128_load((const simd_i64*)(b + i));
        simd_i64 vr = wasm_v128_andnot(va, vb);
        wasm_v128_store((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = (~a[i]) & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_not_i64(i64 * restrict out, const i64 * restrict a, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 vr = wasm_v128_not(va);
        wasm_v128_store((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = ~a[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_cmpeq_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 vb = wasm_v128_load((const simd_i64*)(b + i));
        simd_i64 vr = wasm_i64x2_eq(va, vb);
        wasm_v128_store((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] == b[i]) ? (i64)~0 : (i64)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_cmpne_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 vb = wasm_v128_load((const simd_i64*)(b + i));
        simd_i64 vr = wasm_i64x2_ne(va, vb);
        wasm_v128_store((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] != b[i]) ? (i64)~0 : (i64)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_cmplt_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = (a[i] < b[i]) ? (i64)~0 : (i64)0;
    }
    return out;
}
static inline i64 *stc_simd_cmpgt_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = (a[i] > b[i]) ? (i64)~0 : (i64)0;
    }
    return out;
}
static inline i64 *stc_simd_cmple_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = (a[i] <= b[i]) ? (i64)~0 : (i64)0;
    }
    return out;
}
static inline i64 *stc_simd_cmpge_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = (a[i] >= b[i]) ? (i64)~0 : (i64)0;
    }
    return out;
}
static inline i64 *stc_simd_splat_i64(i64 * restrict out, const i64 value, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i64 vv = wasm_i64x2_splat(value);
    for (; (i + width) <= len; i += width) {
        wasm_v128_store((simd_i64*)(out + i), vv);
    }

    while (rem) {
        out[i] = value;
        ++i;
        --rem;
    }

    return out;
}
static inline u64 stc_simd_bitmask_i64(const i64 * restrict a, const u64 len)
{
    u64 out_mask = 0;
    const u64 n = len < 64 ? len : 64;
    for (u64 i = 0; i < n; ++i) {
        out_mask |= ((u64)((((u64)a[i]) >> (64 - 1)) & 1u) << i);
    }
    return out_mask;
}
static inline bool stc_simd_all_true_i64(const i64 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (!a[i]) return false;
    }
    return true;
}
static inline bool stc_simd_any_true_i64(const i64 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i]) return true;
    }
    return false;
}
static inline u64 stc_simd_count_true_i64(const i64 * restrict a, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] != 0);
    }
    return ct;
}
static inline u64 stc_simd_first_true_i64(const i64 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] != 0) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_count_cmpeq_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 2;
    u64 i = 0;
    u64 ct = 0;
    const simd_i64 vv = wasm_i64x2_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 mask = wasm_i64x2_eq(va, vv);
        u32 bits = (u32)(wasm_i64x2_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i64*)(a + i + width));
        mask = wasm_i64x2_eq(va, vv);
        bits = (u32)(wasm_i64x2_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 mask = wasm_i64x2_eq(va, vv);
        u32 bits = (u32)(wasm_i64x2_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] == value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpne_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 2;
    u64 i = 0;
    u64 ct = 0;
    const simd_i64 vv = wasm_i64x2_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 mask = wasm_i64x2_ne(va, vv);
        u32 bits = (u32)(wasm_i64x2_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const simd_i64*)(a + i + width));
        mask = wasm_i64x2_ne(va, vv);
        bits = (u32)(wasm_i64x2_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 mask = wasm_i64x2_ne(va, vv);
        u32 bits = (u32)(wasm_i64x2_bitmask(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] != value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmplt_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] < value);
    }
    return ct;
}
static inline u64 stc_simd_count_cmpgt_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] > value);
    }
    return ct;
}
static inline u64 stc_simd_count_cmple_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] <= value);
    }
    return ct;
}
static inline u64 stc_simd_count_cmpge_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] >= value);
    }
    return ct;
}
static inline u64 stc_simd_first_cmpeq_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 2;
    u64 i = 0;
    const simd_i64 vv = wasm_i64x2_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 mask = wasm_i64x2_eq(va, vv);
        u32 bits = (u32)(wasm_i64x2_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i64*)(a + i + width));
        mask = wasm_i64x2_eq(va, vv);
        bits = (u32)(wasm_i64x2_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 mask = wasm_i64x2_eq(va, vv);
        u32 bits = (u32)(wasm_i64x2_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] == value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpne_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 2;
    u64 i = 0;
    const simd_i64 vv = wasm_i64x2_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 mask = wasm_i64x2_ne(va, vv);
        u32 bits = (u32)(wasm_i64x2_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const simd_i64*)(a + i + width));
        mask = wasm_i64x2_ne(va, vv);
        bits = (u32)(wasm_i64x2_bitmask(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        simd_i64 mask = wasm_i64x2_ne(va, vv);
        u32 bits = (u32)(wasm_i64x2_bitmask(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] != value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmplt_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] < value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpgt_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] > value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmple_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] <= value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpge_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] >= value) return i;
    }
    return (u64)-1;
}
static inline i64 stc_simd_reduce_add_i64(const i64 * restrict a, const u64 len)
{
    if (!len) return (i64)0;

    const u64 width = 2;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) i64 tmp[LANES_I64];
    simd_i64 vacc = wasm_i64x2_splat(0);

    for (; (i + width) <= len; i += width) {
        simd_i64 va = wasm_v128_load((const simd_i64*)(a + i));
        vacc = wasm_i64x2_add(vacc, va);
    }

    wasm_v128_store((simd_i64*)tmp, vacc);
    i64 acc = (i64)0;
    for (u64 lane = 0; lane < LANES_I64; ++lane) {
        acc = acc + tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc + a[i];
    }

    return acc;
}
static inline f32 *stc_simd_add_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 vb = wasm_v128_load((const f32*)(b + i));
        simd_f32 vr = wasm_f32x4_add(va, vb);
        wasm_v128_store((f32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] + b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_mul_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 vb = wasm_v128_load((const f32*)(b + i));
        simd_f32 vr = wasm_f32x4_mul(va, vb);
        wasm_v128_store((f32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] * b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_sub_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 vb = wasm_v128_load((const f32*)(b + i));
        simd_f32 vr = wasm_f32x4_sub(va, vb);
        wasm_v128_store((f32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] - b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_div_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 vb = wasm_v128_load((const f32*)(b + i));
        simd_f32 vr = wasm_f32x4_div(va, vb);
        wasm_v128_store((f32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] / b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_and_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 vb = wasm_v128_load((const f32*)(b + i));
        simd_f32 vr = wasm_v128_and(va, vb);
        wasm_v128_store((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ua, ub, ur;
        ua.f = a[i];
        ub.f = b[i];
        ur.u = ua.u & ub.u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_or_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 vb = wasm_v128_load((const f32*)(b + i));
        simd_f32 vr = wasm_v128_or(va, vb);
        wasm_v128_store((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ua, ub, ur;
        ua.f = a[i];
        ub.f = b[i];
        ur.u = ua.u | ub.u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_xor_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 vb = wasm_v128_load((const f32*)(b + i));
        simd_f32 vr = wasm_v128_xor(va, vb);
        wasm_v128_store((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ua, ub, ur;
        ua.f = a[i];
        ub.f = b[i];
        ur.u = ua.u ^ ub.u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_andnot_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 vb = wasm_v128_load((const f32*)(b + i));
        simd_f32 vr = wasm_v128_andnot(va, vb);
        wasm_v128_store((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ua, ub, ur;
        ua.f = a[i];
        ub.f = b[i];
        ur.u = (~ua.u) & ub.u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_not_f32(f32 * restrict out, const f32 * restrict a, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 vr = wasm_v128_not(va);
        wasm_v128_store((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ua, ur;
        ua.f = a[i];
        ur.u = ~ua.u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_cmpeq_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 vb = wasm_v128_load((const f32*)(b + i));
        simd_f32 vr = wasm_f32x4_eq(va, vb);
        wasm_v128_store((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ur;
        ur.u = (a[i] == b[i]) ? 0xffffffffu : 0u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_cmpne_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 vb = wasm_v128_load((const f32*)(b + i));
        simd_f32 vr = wasm_f32x4_ne(va, vb);
        wasm_v128_store((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ur;
        ur.u = (a[i] != b[i]) ? 0xffffffffu : 0u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_cmplt_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 vb = wasm_v128_load((const f32*)(b + i));
        simd_f32 vr = wasm_f32x4_lt(va, vb);
        wasm_v128_store((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ur;
        ur.u = (a[i] < b[i]) ? 0xffffffffu : 0u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_cmpgt_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 vb = wasm_v128_load((const f32*)(b + i));
        simd_f32 vr = wasm_f32x4_gt(va, vb);
        wasm_v128_store((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ur;
        ur.u = (a[i] > b[i]) ? 0xffffffffu : 0u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_cmple_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 vb = wasm_v128_load((const f32*)(b + i));
        simd_f32 vr = wasm_f32x4_le(va, vb);
        wasm_v128_store((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ur;
        ur.u = (a[i] <= b[i]) ? 0xffffffffu : 0u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_cmpge_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 vb = wasm_v128_load((const f32*)(b + i));
        simd_f32 vr = wasm_f32x4_ge(va, vb);
        wasm_v128_store((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ur;
        ur.u = (a[i] >= b[i]) ? 0xffffffffu : 0u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_splat_f32(f32 * restrict out, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    const simd_f32 vv = wasm_f32x4_splat(value);
    for (; (i + width) <= len; i += width) {
        wasm_v128_store((f32*)(out + i), vv);
    }

    while (rem) {
        out[i] = value;
        ++i;
        --rem;
    }

    return out;
}
static inline u64 stc_simd_bitmask_f32(const f32 * restrict a, const u64 len)
{
    u64 out_mask = 0;
    const u64 n = len < 64 ? len : 64;
    for (u64 i = 0; i < n; ++i) {
        union { f32 f; u32 u; } bits;
        bits.f = a[i];
        out_mask |= ((u64)((bits.u >> 31) & 1u) << i);
    }
    return out_mask;
}
static inline bool stc_simd_all_true_f32(const f32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (!a[i]) return false;
    }
    return true;
}
static inline bool stc_simd_any_true_f32(const f32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i]) return true;
    }
    return false;
}
static inline f32 *stc_simd_min_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 vb = wasm_v128_load((const f32*)(b + i));
        simd_f32 vr = wasm_f32x4_min(va, vb);
        wasm_v128_store((f32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] < b[i] ? a[i] : b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_max_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 vb = wasm_v128_load((const f32*)(b + i));
        simd_f32 vr = wasm_f32x4_max(va, vb);
        wasm_v128_store((f32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] > b[i] ? a[i] : b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline u64 stc_simd_count_true_f32(const f32 * restrict a, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] != 0);
    }
    return ct;
}
static inline u64 stc_simd_first_true_f32(const f32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] != 0) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_count_cmpeq_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_f32 vv = wasm_f32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_eq(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const f32*)(a + i + width));
        mask = wasm_f32x4_eq(va, vv);
        bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_eq(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] == value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpne_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_f32 vv = wasm_f32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_ne(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const f32*)(a + i + width));
        mask = wasm_f32x4_ne(va, vv);
        bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_ne(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] != value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmplt_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_f32 vv = wasm_f32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_lt(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const f32*)(a + i + width));
        mask = wasm_f32x4_lt(va, vv);
        bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_lt(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] < value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpgt_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_f32 vv = wasm_f32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_gt(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const f32*)(a + i + width));
        mask = wasm_f32x4_gt(va, vv);
        bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_gt(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] > value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmple_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_f32 vv = wasm_f32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_le(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const f32*)(a + i + width));
        mask = wasm_f32x4_le(va, vv);
        bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_le(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] <= value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpge_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_f32 vv = wasm_f32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_ge(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = wasm_v128_load((const f32*)(a + i + width));
        mask = wasm_f32x4_ge(va, vv);
        bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_ge(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] >= value);
    }

    return ct;
}
static inline u64 stc_simd_first_cmpeq_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_f32 vv = wasm_f32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_eq(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const f32*)(a + i + width));
        mask = wasm_f32x4_eq(va, vv);
        bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_eq(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] == value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpne_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_f32 vv = wasm_f32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_ne(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const f32*)(a + i + width));
        mask = wasm_f32x4_ne(va, vv);
        bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_ne(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] != value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmplt_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_f32 vv = wasm_f32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_lt(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const f32*)(a + i + width));
        mask = wasm_f32x4_lt(va, vv);
        bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_lt(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] < value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpgt_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_f32 vv = wasm_f32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_gt(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const f32*)(a + i + width));
        mask = wasm_f32x4_gt(va, vv);
        bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_gt(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] > value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmple_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_f32 vv = wasm_f32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_le(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const f32*)(a + i + width));
        mask = wasm_f32x4_le(va, vv);
        bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_le(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] <= value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpge_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_f32 vv = wasm_f32x4_splat(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_ge(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = wasm_v128_load((const f32*)(a + i + width));
        mask = wasm_f32x4_ge(va, vv);
        bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        simd_f32 mask = wasm_f32x4_ge(va, vv);
        u32 bits = (u32)(wasm_i32x4_bitmask((simd_i32)mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] >= value) return i;
    }
    return (u64)-1;
}
static inline f32 stc_simd_reduce_add_f32(const f32 * restrict a, const u64 len)
{
    if (!len) return (f32)0;

    const u64 width = 4;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) f32 tmp[LANES_F32];
    simd_f32 vacc = wasm_f32x4_splat(0);

    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        vacc = wasm_f32x4_add(vacc, va);
    }

    wasm_v128_store((f32*)tmp, vacc);
    f32 acc = (f32)0;
    for (u64 lane = 0; lane < LANES_F32; ++lane) {
        acc = acc + tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc + a[i];
    }

    return acc;
}
static inline f32 stc_simd_reduce_mul_f32(const f32 * restrict a, const u64 len)
{
    if (!len) return (f32)1;

    const u64 width = 4;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) f32 tmp[LANES_F32];
    simd_f32 vacc = wasm_f32x4_splat(1);

    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        vacc = wasm_f32x4_mul(vacc, va);
    }

    wasm_v128_store((f32*)tmp, vacc);
    f32 acc = (f32)1;
    for (u64 lane = 0; lane < LANES_F32; ++lane) {
        acc = acc * tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc * a[i];
    }

    return acc;
}
static inline f32 stc_simd_reduce_min_f32(const f32 * restrict a, const u64 len)
{
    if (!len) return (f32)0;

    const u64 width = 4;
    u64 i = 1;
    __attribute__((aligned(STC_SIMD_ALIGN))) f32 tmp[LANES_F32];
    simd_f32 vacc = wasm_f32x4_splat(a[0]);

    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        vacc = wasm_f32x4_min(vacc, va);
    }

    wasm_v128_store((f32*)tmp, vacc);
    f32 acc = a[0];
    for (u64 lane = 0; lane < LANES_F32; ++lane) {
        acc = acc < tmp[lane] ? acc : tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc < a[i] ? acc : a[i];
    }

    return acc;
}
static inline f32 stc_simd_reduce_max_f32(const f32 * restrict a, const u64 len)
{
    if (!len) return (f32)0;

    const u64 width = 4;
    u64 i = 1;
    __attribute__((aligned(STC_SIMD_ALIGN))) f32 tmp[LANES_F32];
    simd_f32 vacc = wasm_f32x4_splat(a[0]);

    for (; (i + width) <= len; i += width) {
        simd_f32 va = wasm_v128_load((const f32*)(a + i));
        vacc = wasm_f32x4_max(vacc, va);
    }

    wasm_v128_store((f32*)tmp, vacc);
    f32 acc = a[0];
    for (u64 lane = 0; lane < LANES_F32; ++lane) {
        acc = acc > tmp[lane] ? acc : tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc > a[i] ? acc : a[i];
    }

    return acc;
}

#elif defined(__AVX2__)
static inline i8 *stc_simd_add_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 32;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 vb = _mm256_load_si256((const simd_i8*)(b + i));
        simd_i8 vr = _mm256_add_epi8(va, vb);
        _mm256_store_si256((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] + b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_sub_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 32;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 vb = _mm256_load_si256((const simd_i8*)(b + i));
        simd_i8 vr = _mm256_sub_epi8(va, vb);
        _mm256_store_si256((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] - b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_shl_i8(i8 * restrict out, const i8 * restrict a, const u32 shift_by, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = a[i] << shift_by;
    }
    return out;
}
static inline i8 *stc_simd_shr_i8(i8 * restrict out, const i8 * restrict a, const u32 shift_by, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = a[i] >> shift_by;
    }
    return out;
}
static inline i8 *stc_simd_and_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 32;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 vb = _mm256_load_si256((const simd_i8*)(b + i));
        simd_i8 vr = _mm256_and_si256(va, vb);
        _mm256_store_si256((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_or_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 32;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 vb = _mm256_load_si256((const simd_i8*)(b + i));
        simd_i8 vr = _mm256_or_si256(va, vb);
        _mm256_store_si256((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] | b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_xor_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 32;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 vb = _mm256_load_si256((const simd_i8*)(b + i));
        simd_i8 vr = _mm256_xor_si256(va, vb);
        _mm256_store_si256((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] ^ b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_andnot_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 32;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 vb = _mm256_load_si256((const simd_i8*)(b + i));
        simd_i8 vr = _mm256_andnot_si256(va, vb);
        _mm256_store_si256((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (~a[i]) & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_not_i8(i8 * restrict out, const i8 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = ~a[i];
    }
    return out;
}
static inline i8 *stc_simd_cmpeq_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 32;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 vb = _mm256_load_si256((const simd_i8*)(b + i));
        simd_i8 vr = _mm256_cmpeq_epi8(va, vb);
        _mm256_store_si256((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] == b[i]) ? (i8)~0 : (i8)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_cmpne_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 32;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i8 all_ones = _mm256_set1_epi8(-1);
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 vb = _mm256_load_si256((const simd_i8*)(b + i));
        simd_i8 vr = _mm256_xor_si256(_mm256_cmpeq_epi8(va, vb), all_ones);
        _mm256_store_si256((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] != b[i]) ? (i8)~0 : (i8)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_cmplt_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 32;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 vb = _mm256_load_si256((const simd_i8*)(b + i));
        simd_i8 vr = _mm256_cmpgt_epi8(vb, va);
        _mm256_store_si256((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] < b[i]) ? (i8)~0 : (i8)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_cmpgt_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 32;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 vb = _mm256_load_si256((const simd_i8*)(b + i));
        simd_i8 vr = _mm256_cmpgt_epi8(va, vb);
        _mm256_store_si256((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] > b[i]) ? (i8)~0 : (i8)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_cmple_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 32;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i8 all_ones = _mm256_set1_epi8(-1);
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 vb = _mm256_load_si256((const simd_i8*)(b + i));
        simd_i8 vr = _mm256_xor_si256(_mm256_cmpgt_epi8(va, vb), all_ones);
        _mm256_store_si256((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] <= b[i]) ? (i8)~0 : (i8)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_cmpge_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 32;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i8 all_ones = _mm256_set1_epi8(-1);
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 vb = _mm256_load_si256((const simd_i8*)(b + i));
        simd_i8 vr = _mm256_xor_si256(_mm256_cmpgt_epi8(vb, va), all_ones);
        _mm256_store_si256((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] >= b[i]) ? (i8)~0 : (i8)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_splat_i8(i8 * restrict out, const i8 value, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = value;
    }
    return out;
}
static inline u64 stc_simd_bitmask_i8(const i8 * restrict a, const u64 len)
{
    u64 out_mask = 0;
    const u64 n = len < 64 ? len : 64;
    for (u64 i = 0; i < n; ++i) {
        out_mask |= ((u64)((((u8)a[i]) >> (8 - 1)) & 1u) << i);
    }
    return out_mask;
}
static inline bool stc_simd_all_true_i8(const i8 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (!a[i]) return false;
    }
    return true;
}
static inline bool stc_simd_any_true_i8(const i8 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i]) return true;
    }
    return false;
}
static inline u64 stc_simd_count_true_i8(const i8 * restrict a, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] != 0);
    }
    return ct;
}
static inline u64 stc_simd_first_true_i8(const i8 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] != 0) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_count_cmpeq_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 32;
    u64 i = 0;
    u64 ct = 0;
    const simd_i8 vv = _mm256_set1_epi8(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_cmpeq_epi8(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm256_load_si256((const simd_i8*)(a + i + width));
        mask = _mm256_cmpeq_epi8(va, vv);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_cmpeq_epi8(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] == value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpne_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 32;
    u64 i = 0;
    u64 ct = 0;
    const simd_i8 vv = _mm256_set1_epi8(value);
    const simd_i8 all_ones = _mm256_set1_epi8(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_xor_si256(_mm256_cmpeq_epi8(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm256_load_si256((const simd_i8*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpeq_epi8(va, vv), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_xor_si256(_mm256_cmpeq_epi8(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] != value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmplt_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 32;
    u64 i = 0;
    u64 ct = 0;
    const simd_i8 vv = _mm256_set1_epi8(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_cmpgt_epi8(vv, va);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm256_load_si256((const simd_i8*)(a + i + width));
        mask = _mm256_cmpgt_epi8(vv, va);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_cmpgt_epi8(vv, va);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] < value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpgt_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 32;
    u64 i = 0;
    u64 ct = 0;
    const simd_i8 vv = _mm256_set1_epi8(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_cmpgt_epi8(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm256_load_si256((const simd_i8*)(a + i + width));
        mask = _mm256_cmpgt_epi8(va, vv);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_cmpgt_epi8(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] > value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmple_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 32;
    u64 i = 0;
    u64 ct = 0;
    const simd_i8 vv = _mm256_set1_epi8(value);
    const simd_i8 all_ones = _mm256_set1_epi8(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_xor_si256(_mm256_cmpgt_epi8(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm256_load_si256((const simd_i8*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpgt_epi8(va, vv), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_xor_si256(_mm256_cmpgt_epi8(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] <= value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpge_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 32;
    u64 i = 0;
    u64 ct = 0;
    const simd_i8 vv = _mm256_set1_epi8(value);
    const simd_i8 all_ones = _mm256_set1_epi8(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_xor_si256(_mm256_cmpgt_epi8(vv, va), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm256_load_si256((const simd_i8*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpgt_epi8(vv, va), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_xor_si256(_mm256_cmpgt_epi8(vv, va), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] >= value);
    }

    return ct;
}
static inline u64 stc_simd_first_cmpeq_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 32;
    u64 i = 0;
    const simd_i8 vv = _mm256_set1_epi8(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_cmpeq_epi8(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm256_load_si256((const simd_i8*)(a + i + width));
        mask = _mm256_cmpeq_epi8(va, vv);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_cmpeq_epi8(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] == value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpne_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 32;
    u64 i = 0;
    const simd_i8 vv = _mm256_set1_epi8(value);
    const simd_i8 all_ones = _mm256_set1_epi8(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_xor_si256(_mm256_cmpeq_epi8(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm256_load_si256((const simd_i8*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpeq_epi8(va, vv), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_xor_si256(_mm256_cmpeq_epi8(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] != value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmplt_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 32;
    u64 i = 0;
    const simd_i8 vv = _mm256_set1_epi8(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_cmpgt_epi8(vv, va);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm256_load_si256((const simd_i8*)(a + i + width));
        mask = _mm256_cmpgt_epi8(vv, va);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_cmpgt_epi8(vv, va);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] < value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpgt_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 32;
    u64 i = 0;
    const simd_i8 vv = _mm256_set1_epi8(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_cmpgt_epi8(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm256_load_si256((const simd_i8*)(a + i + width));
        mask = _mm256_cmpgt_epi8(va, vv);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_cmpgt_epi8(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] > value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmple_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 32;
    u64 i = 0;
    const simd_i8 vv = _mm256_set1_epi8(value);
    const simd_i8 all_ones = _mm256_set1_epi8(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_xor_si256(_mm256_cmpgt_epi8(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm256_load_si256((const simd_i8*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpgt_epi8(va, vv), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_xor_si256(_mm256_cmpgt_epi8(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] <= value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpge_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 32;
    u64 i = 0;
    const simd_i8 vv = _mm256_set1_epi8(value);
    const simd_i8 all_ones = _mm256_set1_epi8(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_xor_si256(_mm256_cmpgt_epi8(vv, va), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm256_load_si256((const simd_i8*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpgt_epi8(vv, va), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        simd_i8 mask = _mm256_xor_si256(_mm256_cmpgt_epi8(vv, va), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] >= value) return i;
    }
    return (u64)-1;
}
static inline i8 stc_simd_reduce_add_i8(const i8 * restrict a, const u64 len)
{
    if (!len) return (i8)0;

    const u64 width = 32;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) i8 tmp[LANES_I8];
    simd_i8 vacc = _mm256_set1_epi8(0);

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm256_load_si256((const simd_i8*)(a + i));
        vacc = _mm256_add_epi8(vacc, va);
    }

    _mm256_store_si256((simd_i8*)tmp, vacc);
    i8 acc = (i8)0;
    for (u64 lane = 0; lane < LANES_I8; ++lane) {
        acc = acc + tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc + a[i];
    }

    return acc;
}
static inline i16 *stc_simd_add_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 vb = _mm256_load_si256((const simd_i16*)(b + i));
        simd_i16 vr = _mm256_add_epi16(va, vb);
        _mm256_store_si256((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] + b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_mul_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 vb = _mm256_load_si256((const simd_i16*)(b + i));
        simd_i16 vr = _mm256_mullo_epi16(va, vb);
        _mm256_store_si256((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] * b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_sub_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 vb = _mm256_load_si256((const simd_i16*)(b + i));
        simd_i16 vr = _mm256_sub_epi16(va, vb);
        _mm256_store_si256((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] - b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_shl_i16(i16 * restrict out, const i16 * restrict a, const u32 shift_by, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 vr = _mm256_slli_epi16(va, shift_by);
        _mm256_store_si256((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] << shift_by;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_shr_i16(i16 * restrict out, const i16 * restrict a, const u32 shift_by, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 vr = _mm256_srai_epi16(va, shift_by);
        _mm256_store_si256((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] >> shift_by;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_and_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 vb = _mm256_load_si256((const simd_i16*)(b + i));
        simd_i16 vr = _mm256_and_si256(va, vb);
        _mm256_store_si256((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_or_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 vb = _mm256_load_si256((const simd_i16*)(b + i));
        simd_i16 vr = _mm256_or_si256(va, vb);
        _mm256_store_si256((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] | b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_xor_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 vb = _mm256_load_si256((const simd_i16*)(b + i));
        simd_i16 vr = _mm256_xor_si256(va, vb);
        _mm256_store_si256((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] ^ b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_andnot_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 vb = _mm256_load_si256((const simd_i16*)(b + i));
        simd_i16 vr = _mm256_andnot_si256(va, vb);
        _mm256_store_si256((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (~a[i]) & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_not_i16(i16 * restrict out, const i16 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = ~a[i];
    }
    return out;
}
static inline i16 *stc_simd_cmpeq_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 vb = _mm256_load_si256((const simd_i16*)(b + i));
        simd_i16 vr = _mm256_cmpeq_epi16(va, vb);
        _mm256_store_si256((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] == b[i]) ? (i16)~0 : (i16)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_cmpne_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i16 all_ones = _mm256_set1_epi16(-1);
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 vb = _mm256_load_si256((const simd_i16*)(b + i));
        simd_i16 vr = _mm256_xor_si256(_mm256_cmpeq_epi16(va, vb), all_ones);
        _mm256_store_si256((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] != b[i]) ? (i16)~0 : (i16)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_cmplt_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 vb = _mm256_load_si256((const simd_i16*)(b + i));
        simd_i16 vr = _mm256_cmpgt_epi16(vb, va);
        _mm256_store_si256((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] < b[i]) ? (i16)~0 : (i16)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_cmpgt_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 vb = _mm256_load_si256((const simd_i16*)(b + i));
        simd_i16 vr = _mm256_cmpgt_epi16(va, vb);
        _mm256_store_si256((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] > b[i]) ? (i16)~0 : (i16)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_cmple_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i16 all_ones = _mm256_set1_epi16(-1);
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 vb = _mm256_load_si256((const simd_i16*)(b + i));
        simd_i16 vr = _mm256_xor_si256(_mm256_cmpgt_epi16(va, vb), all_ones);
        _mm256_store_si256((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] <= b[i]) ? (i16)~0 : (i16)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_cmpge_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i16 all_ones = _mm256_set1_epi16(-1);
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 vb = _mm256_load_si256((const simd_i16*)(b + i));
        simd_i16 vr = _mm256_xor_si256(_mm256_cmpgt_epi16(vb, va), all_ones);
        _mm256_store_si256((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] >= b[i]) ? (i16)~0 : (i16)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_splat_i16(i16 * restrict out, const i16 value, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = value;
    }
    return out;
}
static inline u64 stc_simd_bitmask_i16(const i16 * restrict a, const u64 len)
{
    u64 out_mask = 0;
    const u64 n = len < 64 ? len : 64;
    for (u64 i = 0; i < n; ++i) {
        out_mask |= ((u64)((((u16)a[i]) >> (16 - 1)) & 1u) << i);
    }
    return out_mask;
}
static inline bool stc_simd_all_true_i16(const i16 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (!a[i]) return false;
    }
    return true;
}
static inline bool stc_simd_any_true_i16(const i16 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i]) return true;
    }
    return false;
}
static inline u64 stc_simd_count_true_i16(const i16 * restrict a, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] != 0);
    }
    return ct;
}
static inline u64 stc_simd_first_true_i16(const i16 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] != 0) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_count_cmpeq_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    u64 ct = 0;
    const simd_i16 vv = _mm256_set1_epi16(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_cmpeq_epi16(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));

        va = _mm256_load_si256((const simd_i16*)(a + i + width));
        mask = _mm256_cmpeq_epi16(va, vv);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_cmpeq_epi16(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] == value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpne_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    u64 ct = 0;
    const simd_i16 vv = _mm256_set1_epi16(value);
    const simd_i16 all_ones = _mm256_set1_epi16(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_xor_si256(_mm256_cmpeq_epi16(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));

        va = _mm256_load_si256((const simd_i16*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpeq_epi16(va, vv), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_xor_si256(_mm256_cmpeq_epi16(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] != value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmplt_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    u64 ct = 0;
    const simd_i16 vv = _mm256_set1_epi16(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_cmpgt_epi16(vv, va);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));

        va = _mm256_load_si256((const simd_i16*)(a + i + width));
        mask = _mm256_cmpgt_epi16(vv, va);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_cmpgt_epi16(vv, va);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] < value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpgt_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    u64 ct = 0;
    const simd_i16 vv = _mm256_set1_epi16(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_cmpgt_epi16(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));

        va = _mm256_load_si256((const simd_i16*)(a + i + width));
        mask = _mm256_cmpgt_epi16(va, vv);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_cmpgt_epi16(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] > value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmple_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    u64 ct = 0;
    const simd_i16 vv = _mm256_set1_epi16(value);
    const simd_i16 all_ones = _mm256_set1_epi16(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_xor_si256(_mm256_cmpgt_epi16(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));

        va = _mm256_load_si256((const simd_i16*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpgt_epi16(va, vv), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_xor_si256(_mm256_cmpgt_epi16(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] <= value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpge_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    u64 ct = 0;
    const simd_i16 vv = _mm256_set1_epi16(value);
    const simd_i16 all_ones = _mm256_set1_epi16(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_xor_si256(_mm256_cmpgt_epi16(vv, va), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));

        va = _mm256_load_si256((const simd_i16*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpgt_epi16(vv, va), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_xor_si256(_mm256_cmpgt_epi16(vv, va), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] >= value);
    }

    return ct;
}
static inline u64 stc_simd_first_cmpeq_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    const simd_i16 vv = _mm256_set1_epi16(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_cmpeq_epi16(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);

        va = _mm256_load_si256((const simd_i16*)(a + i + width));
        mask = _mm256_cmpeq_epi16(va, vv);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_cmpeq_epi16(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; i < len; ++i) {
        if (a[i] == value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpne_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    const simd_i16 vv = _mm256_set1_epi16(value);
    const simd_i16 all_ones = _mm256_set1_epi16(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_xor_si256(_mm256_cmpeq_epi16(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);

        va = _mm256_load_si256((const simd_i16*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpeq_epi16(va, vv), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_xor_si256(_mm256_cmpeq_epi16(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; i < len; ++i) {
        if (a[i] != value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmplt_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    const simd_i16 vv = _mm256_set1_epi16(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_cmpgt_epi16(vv, va);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);

        va = _mm256_load_si256((const simd_i16*)(a + i + width));
        mask = _mm256_cmpgt_epi16(vv, va);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_cmpgt_epi16(vv, va);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; i < len; ++i) {
        if (a[i] < value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpgt_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    const simd_i16 vv = _mm256_set1_epi16(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_cmpgt_epi16(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);

        va = _mm256_load_si256((const simd_i16*)(a + i + width));
        mask = _mm256_cmpgt_epi16(va, vv);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_cmpgt_epi16(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; i < len; ++i) {
        if (a[i] > value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmple_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    const simd_i16 vv = _mm256_set1_epi16(value);
    const simd_i16 all_ones = _mm256_set1_epi16(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_xor_si256(_mm256_cmpgt_epi16(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);

        va = _mm256_load_si256((const simd_i16*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpgt_epi16(va, vv), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_xor_si256(_mm256_cmpgt_epi16(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; i < len; ++i) {
        if (a[i] <= value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpge_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    const simd_i16 vv = _mm256_set1_epi16(value);
    const simd_i16 all_ones = _mm256_set1_epi16(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_xor_si256(_mm256_cmpgt_epi16(vv, va), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);

        va = _mm256_load_si256((const simd_i16*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpgt_epi16(vv, va), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        simd_i16 mask = _mm256_xor_si256(_mm256_cmpgt_epi16(vv, va), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; i < len; ++i) {
        if (a[i] >= value) return i;
    }
    return (u64)-1;
}
static inline i16 stc_simd_reduce_add_i16(const i16 * restrict a, const u64 len)
{
    if (!len) return (i16)0;

    const u64 width = 16;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) i16 tmp[LANES_I16];
    simd_i16 vacc = _mm256_set1_epi16(0);

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        vacc = _mm256_add_epi16(vacc, va);
    }

    _mm256_store_si256((simd_i16*)tmp, vacc);
    i16 acc = (i16)0;
    for (u64 lane = 0; lane < LANES_I16; ++lane) {
        acc = acc + tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc + a[i];
    }

    return acc;
}
static inline i16 stc_simd_reduce_mul_i16(const i16 * restrict a, const u64 len)
{
    if (!len) return (i16)1;

    const u64 width = 16;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) i16 tmp[LANES_I16];
    simd_i16 vacc = _mm256_set1_epi16(1);

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm256_load_si256((const simd_i16*)(a + i));
        vacc = _mm256_mullo_epi16(vacc, va);
    }

    _mm256_store_si256((simd_i16*)tmp, vacc);
    i16 acc = (i16)1;
    for (u64 lane = 0; lane < LANES_I16; ++lane) {
        acc = acc * tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc * a[i];
    }

    return acc;
}
static inline i32 *stc_simd_add_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 vb = _mm256_load_si256((const simd_i32*)(b + i));
        simd_i32 vr = _mm256_add_epi32(va, vb);
        _mm256_store_si256((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] + b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_mul_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 vb = _mm256_load_si256((const simd_i32*)(b + i));
        simd_i32 vr = _mm256_mullo_epi32(va, vb);
        _mm256_store_si256((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] * b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_sub_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 vb = _mm256_load_si256((const simd_i32*)(b + i));
        simd_i32 vr = _mm256_sub_epi32(va, vb);
        _mm256_store_si256((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] - b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_shl_i32(i32 * restrict out, const i32 * restrict a, const u32 shift_by, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 vr = _mm256_slli_epi32(va, shift_by);
        _mm256_store_si256((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] << shift_by;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_shr_i32(i32 * restrict out, const i32 * restrict a, const u32 shift_by, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 vr = _mm256_srai_epi32(va, shift_by);
        _mm256_store_si256((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] >> shift_by;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_and_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 vb = _mm256_load_si256((const simd_i32*)(b + i));
        simd_i32 vr = _mm256_and_si256(va, vb);
        _mm256_store_si256((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_or_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 vb = _mm256_load_si256((const simd_i32*)(b + i));
        simd_i32 vr = _mm256_or_si256(va, vb);
        _mm256_store_si256((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] | b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_xor_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 vb = _mm256_load_si256((const simd_i32*)(b + i));
        simd_i32 vr = _mm256_xor_si256(va, vb);
        _mm256_store_si256((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] ^ b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_andnot_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 vb = _mm256_load_si256((const simd_i32*)(b + i));
        simd_i32 vr = _mm256_andnot_si256(va, vb);
        _mm256_store_si256((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (~a[i]) & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_not_i32(i32 * restrict out, const i32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = ~a[i];
    }
    return out;
}
static inline i32 *stc_simd_cmpeq_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 vb = _mm256_load_si256((const simd_i32*)(b + i));
        simd_i32 vr = _mm256_cmpeq_epi32(va, vb);
        _mm256_store_si256((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] == b[i]) ? (i32)~0 : (i32)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_cmpne_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i32 all_ones = _mm256_set1_epi32(-1);
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 vb = _mm256_load_si256((const simd_i32*)(b + i));
        simd_i32 vr = _mm256_xor_si256(_mm256_cmpeq_epi32(va, vb), all_ones);
        _mm256_store_si256((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] != b[i]) ? (i32)~0 : (i32)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_cmplt_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 vb = _mm256_load_si256((const simd_i32*)(b + i));
        simd_i32 vr = _mm256_cmpgt_epi32(vb, va);
        _mm256_store_si256((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] < b[i]) ? (i32)~0 : (i32)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_cmpgt_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 vb = _mm256_load_si256((const simd_i32*)(b + i));
        simd_i32 vr = _mm256_cmpgt_epi32(va, vb);
        _mm256_store_si256((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] > b[i]) ? (i32)~0 : (i32)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_cmple_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i32 all_ones = _mm256_set1_epi32(-1);
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 vb = _mm256_load_si256((const simd_i32*)(b + i));
        simd_i32 vr = _mm256_xor_si256(_mm256_cmpgt_epi32(va, vb), all_ones);
        _mm256_store_si256((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] <= b[i]) ? (i32)~0 : (i32)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_cmpge_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i32 all_ones = _mm256_set1_epi32(-1);
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 vb = _mm256_load_si256((const simd_i32*)(b + i));
        simd_i32 vr = _mm256_xor_si256(_mm256_cmpgt_epi32(vb, va), all_ones);
        _mm256_store_si256((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] >= b[i]) ? (i32)~0 : (i32)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_splat_i32(i32 * restrict out, const i32 value, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = value;
    }
    return out;
}
static inline u64 stc_simd_bitmask_i32(const i32 * restrict a, const u64 len)
{
    u64 out_mask = 0;
    const u64 n = len < 64 ? len : 64;
    for (u64 i = 0; i < n; ++i) {
        out_mask |= ((u64)((((u32)a[i]) >> (32 - 1)) & 1u) << i);
    }
    return out_mask;
}
static inline bool stc_simd_all_true_i32(const i32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (!a[i]) return false;
    }
    return true;
}
static inline bool stc_simd_any_true_i32(const i32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i]) return true;
    }
    return false;
}
static inline i32 *stc_simd_min_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 vb = _mm256_load_si256((const simd_i32*)(b + i));
        simd_i32 vr = _mm256_min_epi32(va, vb);
        _mm256_store_si256((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] < b[i] ? a[i] : b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_max_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 vb = _mm256_load_si256((const simd_i32*)(b + i));
        simd_i32 vr = _mm256_max_epi32(va, vb);
        _mm256_store_si256((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] > b[i] ? a[i] : b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline u64 stc_simd_count_true_i32(const i32 * restrict a, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] != 0);
    }
    return ct;
}
static inline u64 stc_simd_first_true_i32(const i32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] != 0) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_count_cmpeq_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_i32 vv = _mm256_set1_epi32(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_cmpeq_epi32(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));

        va = _mm256_load_si256((const simd_i32*)(a + i + width));
        mask = _mm256_cmpeq_epi32(va, vv);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_cmpeq_epi32(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] == value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpne_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_i32 vv = _mm256_set1_epi32(value);
    const simd_i32 all_ones = _mm256_set1_epi32(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_xor_si256(_mm256_cmpeq_epi32(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));

        va = _mm256_load_si256((const simd_i32*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpeq_epi32(va, vv), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_xor_si256(_mm256_cmpeq_epi32(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] != value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmplt_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_i32 vv = _mm256_set1_epi32(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_cmpgt_epi32(vv, va);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));

        va = _mm256_load_si256((const simd_i32*)(a + i + width));
        mask = _mm256_cmpgt_epi32(vv, va);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_cmpgt_epi32(vv, va);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] < value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpgt_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_i32 vv = _mm256_set1_epi32(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_cmpgt_epi32(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));

        va = _mm256_load_si256((const simd_i32*)(a + i + width));
        mask = _mm256_cmpgt_epi32(va, vv);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_cmpgt_epi32(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] > value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmple_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_i32 vv = _mm256_set1_epi32(value);
    const simd_i32 all_ones = _mm256_set1_epi32(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_xor_si256(_mm256_cmpgt_epi32(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));

        va = _mm256_load_si256((const simd_i32*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpgt_epi32(va, vv), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_xor_si256(_mm256_cmpgt_epi32(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] <= value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpge_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_i32 vv = _mm256_set1_epi32(value);
    const simd_i32 all_ones = _mm256_set1_epi32(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_xor_si256(_mm256_cmpgt_epi32(vv, va), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));

        va = _mm256_load_si256((const simd_i32*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpgt_epi32(vv, va), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_xor_si256(_mm256_cmpgt_epi32(vv, va), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] >= value);
    }

    return ct;
}
static inline u64 stc_simd_first_cmpeq_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_i32 vv = _mm256_set1_epi32(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_cmpeq_epi32(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);

        va = _mm256_load_si256((const simd_i32*)(a + i + width));
        mask = _mm256_cmpeq_epi32(va, vv);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_cmpeq_epi32(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; i < len; ++i) {
        if (a[i] == value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpne_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_i32 vv = _mm256_set1_epi32(value);
    const simd_i32 all_ones = _mm256_set1_epi32(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_xor_si256(_mm256_cmpeq_epi32(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);

        va = _mm256_load_si256((const simd_i32*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpeq_epi32(va, vv), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_xor_si256(_mm256_cmpeq_epi32(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; i < len; ++i) {
        if (a[i] != value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmplt_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_i32 vv = _mm256_set1_epi32(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_cmpgt_epi32(vv, va);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);

        va = _mm256_load_si256((const simd_i32*)(a + i + width));
        mask = _mm256_cmpgt_epi32(vv, va);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_cmpgt_epi32(vv, va);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; i < len; ++i) {
        if (a[i] < value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpgt_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_i32 vv = _mm256_set1_epi32(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_cmpgt_epi32(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);

        va = _mm256_load_si256((const simd_i32*)(a + i + width));
        mask = _mm256_cmpgt_epi32(va, vv);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_cmpgt_epi32(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; i < len; ++i) {
        if (a[i] > value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmple_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_i32 vv = _mm256_set1_epi32(value);
    const simd_i32 all_ones = _mm256_set1_epi32(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_xor_si256(_mm256_cmpgt_epi32(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);

        va = _mm256_load_si256((const simd_i32*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpgt_epi32(va, vv), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_xor_si256(_mm256_cmpgt_epi32(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; i < len; ++i) {
        if (a[i] <= value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpge_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_i32 vv = _mm256_set1_epi32(value);
    const simd_i32 all_ones = _mm256_set1_epi32(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_xor_si256(_mm256_cmpgt_epi32(vv, va), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);

        va = _mm256_load_si256((const simd_i32*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpgt_epi32(vv, va), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        simd_i32 mask = _mm256_xor_si256(_mm256_cmpgt_epi32(vv, va), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; i < len; ++i) {
        if (a[i] >= value) return i;
    }
    return (u64)-1;
}
static inline i32 stc_simd_reduce_add_i32(const i32 * restrict a, const u64 len)
{
    if (!len) return (i32)0;

    const u64 width = 8;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) i32 tmp[LANES_I32];
    simd_i32 vacc = _mm256_set1_epi32(0);

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        vacc = _mm256_add_epi32(vacc, va);
    }

    _mm256_store_si256((simd_i32*)tmp, vacc);
    i32 acc = (i32)0;
    for (u64 lane = 0; lane < LANES_I32; ++lane) {
        acc = acc + tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc + a[i];
    }

    return acc;
}
static inline i32 stc_simd_reduce_mul_i32(const i32 * restrict a, const u64 len)
{
    if (!len) return (i32)1;

    const u64 width = 8;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) i32 tmp[LANES_I32];
    simd_i32 vacc = _mm256_set1_epi32(1);

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        vacc = _mm256_mullo_epi32(vacc, va);
    }

    _mm256_store_si256((simd_i32*)tmp, vacc);
    i32 acc = (i32)1;
    for (u64 lane = 0; lane < LANES_I32; ++lane) {
        acc = acc * tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc * a[i];
    }

    return acc;
}
static inline i32 stc_simd_reduce_min_i32(const i32 * restrict a, const u64 len)
{
    if (!len) return (i32)0;

    const u64 width = 8;
    u64 i = 1;
    __attribute__((aligned(STC_SIMD_ALIGN))) i32 tmp[LANES_I32];
    simd_i32 vacc = _mm256_set1_epi32(a[0]);

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        vacc = _mm256_min_epi32(vacc, va);
    }

    _mm256_store_si256((simd_i32*)tmp, vacc);
    i32 acc = a[0];
    for (u64 lane = 0; lane < LANES_I32; ++lane) {
        acc = acc < tmp[lane] ? acc : tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc < a[i] ? acc : a[i];
    }

    return acc;
}
static inline i32 stc_simd_reduce_max_i32(const i32 * restrict a, const u64 len)
{
    if (!len) return (i32)0;

    const u64 width = 8;
    u64 i = 1;
    __attribute__((aligned(STC_SIMD_ALIGN))) i32 tmp[LANES_I32];
    simd_i32 vacc = _mm256_set1_epi32(a[0]);

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm256_load_si256((const simd_i32*)(a + i));
        vacc = _mm256_max_epi32(vacc, va);
    }

    _mm256_store_si256((simd_i32*)tmp, vacc);
    i32 acc = a[0];
    for (u64 lane = 0; lane < LANES_I32; ++lane) {
        acc = acc > tmp[lane] ? acc : tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc > a[i] ? acc : a[i];
    }

    return acc;
}
static inline i64 *stc_simd_add_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 vb = _mm256_load_si256((const simd_i64*)(b + i));
        simd_i64 vr = _mm256_add_epi64(va, vb);
        _mm256_store_si256((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] + b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_sub_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 vb = _mm256_load_si256((const simd_i64*)(b + i));
        simd_i64 vr = _mm256_sub_epi64(va, vb);
        _mm256_store_si256((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] - b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_shl_i64(i64 * restrict out, const i64 * restrict a, const u32 shift_by, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 vr = _mm256_slli_epi64(va, shift_by);
        _mm256_store_si256((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] << shift_by;
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_shr_i64(i64 * restrict out, const i64 * restrict a, const u32 shift_by, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = a[i] >> shift_by;
    }
    return out;
}
static inline i64 *stc_simd_and_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 vb = _mm256_load_si256((const simd_i64*)(b + i));
        simd_i64 vr = _mm256_and_si256(va, vb);
        _mm256_store_si256((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_or_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 vb = _mm256_load_si256((const simd_i64*)(b + i));
        simd_i64 vr = _mm256_or_si256(va, vb);
        _mm256_store_si256((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] | b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_xor_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 vb = _mm256_load_si256((const simd_i64*)(b + i));
        simd_i64 vr = _mm256_xor_si256(va, vb);
        _mm256_store_si256((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] ^ b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_andnot_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 vb = _mm256_load_si256((const simd_i64*)(b + i));
        simd_i64 vr = _mm256_andnot_si256(va, vb);
        _mm256_store_si256((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = (~a[i]) & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_not_i64(i64 * restrict out, const i64 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = ~a[i];
    }
    return out;
}
static inline i64 *stc_simd_cmpeq_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 vb = _mm256_load_si256((const simd_i64*)(b + i));
        simd_i64 vr = _mm256_cmpeq_epi64(va, vb);
        _mm256_store_si256((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] == b[i]) ? (i64)~0 : (i64)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_cmpne_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i64 all_ones = _mm256_set1_epi64x(-1);
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 vb = _mm256_load_si256((const simd_i64*)(b + i));
        simd_i64 vr = _mm256_xor_si256(_mm256_cmpeq_epi64(va, vb), all_ones);
        _mm256_store_si256((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] != b[i]) ? (i64)~0 : (i64)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_cmplt_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 vb = _mm256_load_si256((const simd_i64*)(b + i));
        simd_i64 vr = _mm256_cmpgt_epi64(vb, va);
        _mm256_store_si256((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] < b[i]) ? (i64)~0 : (i64)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_cmpgt_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 vb = _mm256_load_si256((const simd_i64*)(b + i));
        simd_i64 vr = _mm256_cmpgt_epi64(va, vb);
        _mm256_store_si256((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] > b[i]) ? (i64)~0 : (i64)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_cmple_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i64 all_ones = _mm256_set1_epi64x(-1);
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 vb = _mm256_load_si256((const simd_i64*)(b + i));
        simd_i64 vr = _mm256_xor_si256(_mm256_cmpgt_epi64(va, vb), all_ones);
        _mm256_store_si256((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] <= b[i]) ? (i64)~0 : (i64)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_cmpge_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i64 all_ones = _mm256_set1_epi64x(-1);
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 vb = _mm256_load_si256((const simd_i64*)(b + i));
        simd_i64 vr = _mm256_xor_si256(_mm256_cmpgt_epi64(vb, va), all_ones);
        _mm256_store_si256((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] >= b[i]) ? (i64)~0 : (i64)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_splat_i64(i64 * restrict out, const i64 value, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = value;
    }
    return out;
}
static inline u64 stc_simd_bitmask_i64(const i64 * restrict a, const u64 len)
{
    u64 out_mask = 0;
    const u64 n = len < 64 ? len : 64;
    for (u64 i = 0; i < n; ++i) {
        out_mask |= ((u64)((((u64)a[i]) >> (64 - 1)) & 1u) << i);
    }
    return out_mask;
}
static inline bool stc_simd_all_true_i64(const i64 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (!a[i]) return false;
    }
    return true;
}
static inline bool stc_simd_any_true_i64(const i64 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i]) return true;
    }
    return false;
}
static inline u64 stc_simd_count_true_i64(const i64 * restrict a, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] != 0);
    }
    return ct;
}
static inline u64 stc_simd_first_true_i64(const i64 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] != 0) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_count_cmpeq_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_i64 vv = _mm256_set1_epi64x(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_cmpeq_epi64(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));

        va = _mm256_load_si256((const simd_i64*)(a + i + width));
        mask = _mm256_cmpeq_epi64(va, vv);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_cmpeq_epi64(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] == value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpne_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_i64 vv = _mm256_set1_epi64x(value);
    const simd_i64 all_ones = _mm256_set1_epi64x(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_xor_si256(_mm256_cmpeq_epi64(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));

        va = _mm256_load_si256((const simd_i64*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpeq_epi64(va, vv), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_xor_si256(_mm256_cmpeq_epi64(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] != value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmplt_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_i64 vv = _mm256_set1_epi64x(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_cmpgt_epi64(vv, va);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));

        va = _mm256_load_si256((const simd_i64*)(a + i + width));
        mask = _mm256_cmpgt_epi64(vv, va);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_cmpgt_epi64(vv, va);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] < value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpgt_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_i64 vv = _mm256_set1_epi64x(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_cmpgt_epi64(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));

        va = _mm256_load_si256((const simd_i64*)(a + i + width));
        mask = _mm256_cmpgt_epi64(va, vv);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_cmpgt_epi64(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] > value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmple_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_i64 vv = _mm256_set1_epi64x(value);
    const simd_i64 all_ones = _mm256_set1_epi64x(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_xor_si256(_mm256_cmpgt_epi64(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));

        va = _mm256_load_si256((const simd_i64*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpgt_epi64(va, vv), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_xor_si256(_mm256_cmpgt_epi64(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] <= value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpge_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_i64 vv = _mm256_set1_epi64x(value);
    const simd_i64 all_ones = _mm256_set1_epi64x(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_xor_si256(_mm256_cmpgt_epi64(vv, va), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));

        va = _mm256_load_si256((const simd_i64*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpgt_epi64(vv, va), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_xor_si256(_mm256_cmpgt_epi64(vv, va), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] >= value);
    }

    return ct;
}
static inline u64 stc_simd_first_cmpeq_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_i64 vv = _mm256_set1_epi64x(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_cmpeq_epi64(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);

        va = _mm256_load_si256((const simd_i64*)(a + i + width));
        mask = _mm256_cmpeq_epi64(va, vv);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_cmpeq_epi64(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; i < len; ++i) {
        if (a[i] == value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpne_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_i64 vv = _mm256_set1_epi64x(value);
    const simd_i64 all_ones = _mm256_set1_epi64x(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_xor_si256(_mm256_cmpeq_epi64(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);

        va = _mm256_load_si256((const simd_i64*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpeq_epi64(va, vv), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_xor_si256(_mm256_cmpeq_epi64(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; i < len; ++i) {
        if (a[i] != value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmplt_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_i64 vv = _mm256_set1_epi64x(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_cmpgt_epi64(vv, va);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);

        va = _mm256_load_si256((const simd_i64*)(a + i + width));
        mask = _mm256_cmpgt_epi64(vv, va);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_cmpgt_epi64(vv, va);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; i < len; ++i) {
        if (a[i] < value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpgt_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_i64 vv = _mm256_set1_epi64x(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_cmpgt_epi64(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);

        va = _mm256_load_si256((const simd_i64*)(a + i + width));
        mask = _mm256_cmpgt_epi64(va, vv);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_cmpgt_epi64(va, vv);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; i < len; ++i) {
        if (a[i] > value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmple_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_i64 vv = _mm256_set1_epi64x(value);
    const simd_i64 all_ones = _mm256_set1_epi64x(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_xor_si256(_mm256_cmpgt_epi64(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);

        va = _mm256_load_si256((const simd_i64*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpgt_epi64(va, vv), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_xor_si256(_mm256_cmpgt_epi64(va, vv), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; i < len; ++i) {
        if (a[i] <= value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpge_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_i64 vv = _mm256_set1_epi64x(value);
    const simd_i64 all_ones = _mm256_set1_epi64x(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_xor_si256(_mm256_cmpgt_epi64(vv, va), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);

        va = _mm256_load_si256((const simd_i64*)(a + i + width));
        mask = _mm256_xor_si256(_mm256_cmpgt_epi64(vv, va), all_ones);
        bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        simd_i64 mask = _mm256_xor_si256(_mm256_cmpgt_epi64(vv, va), all_ones);
        u32 bits = (u32)(_mm256_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; i < len; ++i) {
        if (a[i] >= value) return i;
    }
    return (u64)-1;
}
static inline i64 stc_simd_reduce_add_i64(const i64 * restrict a, const u64 len)
{
    if (!len) return (i64)0;

    const u64 width = 4;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) i64 tmp[LANES_I64];
    simd_i64 vacc = _mm256_set1_epi64x(0);

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm256_load_si256((const simd_i64*)(a + i));
        vacc = _mm256_add_epi64(vacc, va);
    }

    _mm256_store_si256((simd_i64*)tmp, vacc);
    i64 acc = (i64)0;
    for (u64 lane = 0; lane < LANES_I64; ++lane) {
        acc = acc + tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc + a[i];
    }

    return acc;
}
static inline f32 *stc_simd_add_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm256_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm256_add_ps(va, vb);
        _mm256_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] + b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_mul_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm256_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm256_mul_ps(va, vb);
        _mm256_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] * b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_sub_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm256_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm256_sub_ps(va, vb);
        _mm256_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] - b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_div_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm256_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm256_div_ps(va, vb);
        _mm256_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] / b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_and_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm256_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm256_and_ps(va, vb);
        _mm256_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ua, ub, ur;
        ua.f = a[i];
        ub.f = b[i];
        ur.u = ua.u & ub.u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_or_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm256_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm256_or_ps(va, vb);
        _mm256_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ua, ub, ur;
        ua.f = a[i];
        ub.f = b[i];
        ur.u = ua.u | ub.u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_xor_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm256_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm256_xor_ps(va, vb);
        _mm256_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ua, ub, ur;
        ua.f = a[i];
        ub.f = b[i];
        ur.u = ua.u ^ ub.u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_andnot_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm256_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm256_andnot_ps(va, vb);
        _mm256_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ua, ub, ur;
        ua.f = a[i];
        ub.f = b[i];
        ur.u = (~ua.u) & ub.u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_not_f32(f32 * restrict out, const f32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        union { u32 u; f32 f; } ua, ur;
        ua.f = a[i];
        ur.u = ~ua.u;
        out[i] = ur.f;
    }
    return out;
}
static inline f32 *stc_simd_cmpeq_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm256_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm256_cmp_ps(va, vb, _CMP_EQ_OQ);
        _mm256_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ur;
        ur.u = (a[i] == b[i]) ? 0xffffffffu : 0u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_cmpne_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm256_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm256_cmp_ps(va, vb, _CMP_NEQ_OQ);
        _mm256_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ur;
        ur.u = (a[i] != b[i]) ? 0xffffffffu : 0u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_cmplt_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm256_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm256_cmp_ps(va, vb, _CMP_LT_OQ);
        _mm256_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ur;
        ur.u = (a[i] < b[i]) ? 0xffffffffu : 0u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_cmpgt_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm256_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm256_cmp_ps(va, vb, _CMP_GT_OQ);
        _mm256_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ur;
        ur.u = (a[i] > b[i]) ? 0xffffffffu : 0u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_cmple_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm256_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm256_cmp_ps(va, vb, _CMP_LE_OQ);
        _mm256_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ur;
        ur.u = (a[i] <= b[i]) ? 0xffffffffu : 0u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_cmpge_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm256_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm256_cmp_ps(va, vb, _CMP_GE_OQ);
        _mm256_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ur;
        ur.u = (a[i] >= b[i]) ? 0xffffffffu : 0u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_splat_f32(f32 * restrict out, const f32 value, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = value;
    }
    return out;
}
static inline u64 stc_simd_bitmask_f32(const f32 * restrict a, const u64 len)
{
    u64 out_mask = 0;
    const u64 n = len < 64 ? len : 64;
    for (u64 i = 0; i < n; ++i) {
        union { f32 f; u32 u; } bits;
        bits.f = a[i];
        out_mask |= ((u64)((bits.u >> 31) & 1u) << i);
    }
    return out_mask;
}
static inline bool stc_simd_all_true_f32(const f32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (!a[i]) return false;
    }
    return true;
}
static inline bool stc_simd_any_true_f32(const f32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i]) return true;
    }
    return false;
}
static inline f32 *stc_simd_min_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm256_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm256_min_ps(va, vb);
        _mm256_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] < b[i] ? a[i] : b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_max_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm256_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm256_max_ps(va, vb);
        _mm256_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] > b[i] ? a[i] : b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline u64 stc_simd_count_true_f32(const f32 * restrict a, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] != 0);
    }
    return ct;
}
static inline u64 stc_simd_first_true_f32(const f32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] != 0) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_count_cmpeq_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_f32 vv = _mm256_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_EQ_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm256_load_ps((const f32*)(a + i + width));
        mask = _mm256_cmp_ps(va, vv, _CMP_EQ_OQ);
        bits = (u32)(_mm256_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_EQ_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] == value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpne_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_f32 vv = _mm256_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_NEQ_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm256_load_ps((const f32*)(a + i + width));
        mask = _mm256_cmp_ps(va, vv, _CMP_NEQ_OQ);
        bits = (u32)(_mm256_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_NEQ_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] != value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmplt_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_f32 vv = _mm256_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_LT_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm256_load_ps((const f32*)(a + i + width));
        mask = _mm256_cmp_ps(va, vv, _CMP_LT_OQ);
        bits = (u32)(_mm256_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_LT_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] < value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpgt_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_f32 vv = _mm256_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_GT_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm256_load_ps((const f32*)(a + i + width));
        mask = _mm256_cmp_ps(va, vv, _CMP_GT_OQ);
        bits = (u32)(_mm256_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_GT_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] > value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmple_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_f32 vv = _mm256_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_LE_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm256_load_ps((const f32*)(a + i + width));
        mask = _mm256_cmp_ps(va, vv, _CMP_LE_OQ);
        bits = (u32)(_mm256_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_LE_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] <= value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpge_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_f32 vv = _mm256_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_GE_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm256_load_ps((const f32*)(a + i + width));
        mask = _mm256_cmp_ps(va, vv, _CMP_GE_OQ);
        bits = (u32)(_mm256_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_GE_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] >= value);
    }

    return ct;
}
static inline u64 stc_simd_first_cmpeq_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_f32 vv = _mm256_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_EQ_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm256_load_ps((const f32*)(a + i + width));
        mask = _mm256_cmp_ps(va, vv, _CMP_EQ_OQ);
        bits = (u32)(_mm256_movemask_ps(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_EQ_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] == value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpne_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_f32 vv = _mm256_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_NEQ_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm256_load_ps((const f32*)(a + i + width));
        mask = _mm256_cmp_ps(va, vv, _CMP_NEQ_OQ);
        bits = (u32)(_mm256_movemask_ps(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_NEQ_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] != value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmplt_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_f32 vv = _mm256_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_LT_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm256_load_ps((const f32*)(a + i + width));
        mask = _mm256_cmp_ps(va, vv, _CMP_LT_OQ);
        bits = (u32)(_mm256_movemask_ps(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_LT_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] < value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpgt_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_f32 vv = _mm256_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_GT_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm256_load_ps((const f32*)(a + i + width));
        mask = _mm256_cmp_ps(va, vv, _CMP_GT_OQ);
        bits = (u32)(_mm256_movemask_ps(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_GT_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] > value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmple_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_f32 vv = _mm256_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_LE_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm256_load_ps((const f32*)(a + i + width));
        mask = _mm256_cmp_ps(va, vv, _CMP_LE_OQ);
        bits = (u32)(_mm256_movemask_ps(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_LE_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] <= value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpge_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_f32 vv = _mm256_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_GE_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm256_load_ps((const f32*)(a + i + width));
        mask = _mm256_cmp_ps(va, vv, _CMP_GE_OQ);
        bits = (u32)(_mm256_movemask_ps(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm256_cmp_ps(va, vv, _CMP_GE_OQ);
        u32 bits = (u32)(_mm256_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] >= value) return i;
    }
    return (u64)-1;
}
static inline f32 stc_simd_reduce_add_f32(const f32 * restrict a, const u64 len)
{
    if (!len) return (f32)0;

    const u64 width = 8;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) f32 tmp[LANES_F32];
    simd_f32 vacc = _mm256_set1_ps(0);

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        vacc = _mm256_add_ps(vacc, va);
    }

    _mm256_store_ps((f32*)tmp, vacc);
    f32 acc = (f32)0;
    for (u64 lane = 0; lane < LANES_F32; ++lane) {
        acc = acc + tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc + a[i];
    }

    return acc;
}
static inline f32 stc_simd_reduce_mul_f32(const f32 * restrict a, const u64 len)
{
    if (!len) return (f32)1;

    const u64 width = 8;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) f32 tmp[LANES_F32];
    simd_f32 vacc = _mm256_set1_ps(1);

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        vacc = _mm256_mul_ps(vacc, va);
    }

    _mm256_store_ps((f32*)tmp, vacc);
    f32 acc = (f32)1;
    for (u64 lane = 0; lane < LANES_F32; ++lane) {
        acc = acc * tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc * a[i];
    }

    return acc;
}
static inline f32 stc_simd_reduce_min_f32(const f32 * restrict a, const u64 len)
{
    if (!len) return (f32)0;

    const u64 width = 8;
    u64 i = 1;
    __attribute__((aligned(STC_SIMD_ALIGN))) f32 tmp[LANES_F32];
    simd_f32 vacc = _mm256_set1_ps(a[0]);

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        vacc = _mm256_min_ps(vacc, va);
    }

    _mm256_store_ps((f32*)tmp, vacc);
    f32 acc = a[0];
    for (u64 lane = 0; lane < LANES_F32; ++lane) {
        acc = acc < tmp[lane] ? acc : tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc < a[i] ? acc : a[i];
    }

    return acc;
}
static inline f32 stc_simd_reduce_max_f32(const f32 * restrict a, const u64 len)
{
    if (!len) return (f32)0;

    const u64 width = 8;
    u64 i = 1;
    __attribute__((aligned(STC_SIMD_ALIGN))) f32 tmp[LANES_F32];
    simd_f32 vacc = _mm256_set1_ps(a[0]);

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm256_load_ps((const f32*)(a + i));
        vacc = _mm256_max_ps(vacc, va);
    }

    _mm256_store_ps((f32*)tmp, vacc);
    f32 acc = a[0];
    for (u64 lane = 0; lane < LANES_F32; ++lane) {
        acc = acc > tmp[lane] ? acc : tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc > a[i] ? acc : a[i];
    }

    return acc;
}

#elif defined(__SSE4_2__)
static inline i8 *stc_simd_add_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 vb = _mm_load_si128((const simd_i8*)(b + i));
        simd_i8 vr = _mm_add_epi8(va, vb);
        _mm_store_si128((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] + b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_sub_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 vb = _mm_load_si128((const simd_i8*)(b + i));
        simd_i8 vr = _mm_sub_epi8(va, vb);
        _mm_store_si128((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] - b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_shl_i8(i8 * restrict out, const i8 * restrict a, const u32 shift_by, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = a[i] << shift_by;
    }
    return out;
}
static inline i8 *stc_simd_shr_i8(i8 * restrict out, const i8 * restrict a, const u32 shift_by, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = a[i] >> shift_by;
    }
    return out;
}
static inline i8 *stc_simd_and_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 vb = _mm_load_si128((const simd_i8*)(b + i));
        simd_i8 vr = _mm_and_si128(va, vb);
        _mm_store_si128((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_or_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 vb = _mm_load_si128((const simd_i8*)(b + i));
        simd_i8 vr = _mm_or_si128(va, vb);
        _mm_store_si128((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] | b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_xor_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 vb = _mm_load_si128((const simd_i8*)(b + i));
        simd_i8 vr = _mm_xor_si128(va, vb);
        _mm_store_si128((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] ^ b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_andnot_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 vb = _mm_load_si128((const simd_i8*)(b + i));
        simd_i8 vr = _mm_andnot_si128(va, vb);
        _mm_store_si128((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (~a[i]) & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_not_i8(i8 * restrict out, const i8 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = ~a[i];
    }
    return out;
}
static inline i8 *stc_simd_cmpeq_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 vb = _mm_load_si128((const simd_i8*)(b + i));
        simd_i8 vr = _mm_cmpeq_epi8(va, vb);
        _mm_store_si128((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] == b[i]) ? (i8)~0 : (i8)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_cmpne_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i8 all_ones = _mm_set1_epi8(-1);
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 vb = _mm_load_si128((const simd_i8*)(b + i));
        simd_i8 vr = _mm_xor_si128(_mm_cmpeq_epi8(va, vb), all_ones);
        _mm_store_si128((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] != b[i]) ? (i8)~0 : (i8)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_cmplt_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 vb = _mm_load_si128((const simd_i8*)(b + i));
        simd_i8 vr = _mm_cmpgt_epi8(vb, va);
        _mm_store_si128((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] < b[i]) ? (i8)~0 : (i8)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_cmpgt_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 vb = _mm_load_si128((const simd_i8*)(b + i));
        simd_i8 vr = _mm_cmpgt_epi8(va, vb);
        _mm_store_si128((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] > b[i]) ? (i8)~0 : (i8)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_cmple_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i8 all_ones = _mm_set1_epi8(-1);
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 vb = _mm_load_si128((const simd_i8*)(b + i));
        simd_i8 vr = _mm_xor_si128(_mm_cmpgt_epi8(va, vb), all_ones);
        _mm_store_si128((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] <= b[i]) ? (i8)~0 : (i8)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_cmpge_i8(i8 * restrict out, const i8 * restrict a, const i8 * restrict b, const u64 len)
{
    const u64 width = 16;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i8 all_ones = _mm_set1_epi8(-1);
    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 vb = _mm_load_si128((const simd_i8*)(b + i));
        simd_i8 vr = _mm_xor_si128(_mm_cmpgt_epi8(vb, va), all_ones);
        _mm_store_si128((simd_i8*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] >= b[i]) ? (i8)~0 : (i8)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i8 *stc_simd_splat_i8(i8 * restrict out, const i8 value, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = value;
    }
    return out;
}
static inline u64 stc_simd_bitmask_i8(const i8 * restrict a, const u64 len)
{
    u64 out_mask = 0;
    const u64 n = len < 64 ? len : 64;
    for (u64 i = 0; i < n; ++i) {
        out_mask |= ((u64)((((u8)a[i]) >> (8 - 1)) & 1u) << i);
    }
    return out_mask;
}
static inline bool stc_simd_all_true_i8(const i8 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (!a[i]) return false;
    }
    return true;
}
static inline bool stc_simd_any_true_i8(const i8 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i]) return true;
    }
    return false;
}
static inline u64 stc_simd_count_true_i8(const i8 * restrict a, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] != 0);
    }
    return ct;
}
static inline u64 stc_simd_first_true_i8(const i8 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] != 0) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_count_cmpeq_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    u64 ct = 0;
    const simd_i8 vv = _mm_set1_epi8(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_cmpeq_epi8(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm_load_si128((const simd_i8*)(a + i + width));
        mask = _mm_cmpeq_epi8(va, vv);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_cmpeq_epi8(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] == value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpne_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    u64 ct = 0;
    const simd_i8 vv = _mm_set1_epi8(value);
    const simd_i8 all_ones = _mm_set1_epi8(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_xor_si128(_mm_cmpeq_epi8(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm_load_si128((const simd_i8*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpeq_epi8(va, vv), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_xor_si128(_mm_cmpeq_epi8(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] != value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmplt_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    u64 ct = 0;
    const simd_i8 vv = _mm_set1_epi8(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_cmpgt_epi8(vv, va);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm_load_si128((const simd_i8*)(a + i + width));
        mask = _mm_cmpgt_epi8(vv, va);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_cmpgt_epi8(vv, va);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] < value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpgt_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    u64 ct = 0;
    const simd_i8 vv = _mm_set1_epi8(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_cmpgt_epi8(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm_load_si128((const simd_i8*)(a + i + width));
        mask = _mm_cmpgt_epi8(va, vv);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_cmpgt_epi8(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] > value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmple_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    u64 ct = 0;
    const simd_i8 vv = _mm_set1_epi8(value);
    const simd_i8 all_ones = _mm_set1_epi8(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_xor_si128(_mm_cmpgt_epi8(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm_load_si128((const simd_i8*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpgt_epi8(va, vv), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_xor_si128(_mm_cmpgt_epi8(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] <= value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpge_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    u64 ct = 0;
    const simd_i8 vv = _mm_set1_epi8(value);
    const simd_i8 all_ones = _mm_set1_epi8(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_xor_si128(_mm_cmpgt_epi8(vv, va), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm_load_si128((const simd_i8*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpgt_epi8(vv, va), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_xor_si128(_mm_cmpgt_epi8(vv, va), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] >= value);
    }

    return ct;
}
static inline u64 stc_simd_first_cmpeq_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    const simd_i8 vv = _mm_set1_epi8(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_cmpeq_epi8(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm_load_si128((const simd_i8*)(a + i + width));
        mask = _mm_cmpeq_epi8(va, vv);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_cmpeq_epi8(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] == value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpne_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    const simd_i8 vv = _mm_set1_epi8(value);
    const simd_i8 all_ones = _mm_set1_epi8(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_xor_si128(_mm_cmpeq_epi8(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm_load_si128((const simd_i8*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpeq_epi8(va, vv), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_xor_si128(_mm_cmpeq_epi8(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] != value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmplt_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    const simd_i8 vv = _mm_set1_epi8(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_cmpgt_epi8(vv, va);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm_load_si128((const simd_i8*)(a + i + width));
        mask = _mm_cmpgt_epi8(vv, va);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_cmpgt_epi8(vv, va);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] < value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpgt_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    const simd_i8 vv = _mm_set1_epi8(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_cmpgt_epi8(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm_load_si128((const simd_i8*)(a + i + width));
        mask = _mm_cmpgt_epi8(va, vv);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_cmpgt_epi8(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] > value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmple_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    const simd_i8 vv = _mm_set1_epi8(value);
    const simd_i8 all_ones = _mm_set1_epi8(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_xor_si128(_mm_cmpgt_epi8(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm_load_si128((const simd_i8*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpgt_epi8(va, vv), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_xor_si128(_mm_cmpgt_epi8(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] <= value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpge_scalar_i8(const i8 * restrict a, const i8 value, const u64 len)
{
    const u64 width = 16;
    u64 i = 0;
    const simd_i8 vv = _mm_set1_epi8(value);
    const simd_i8 all_ones = _mm_set1_epi8(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_xor_si128(_mm_cmpgt_epi8(vv, va), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm_load_si128((const simd_i8*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpgt_epi8(vv, va), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        simd_i8 mask = _mm_xor_si128(_mm_cmpgt_epi8(vv, va), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] >= value) return i;
    }
    return (u64)-1;
}
static inline i8 stc_simd_reduce_add_i8(const i8 * restrict a, const u64 len)
{
    if (!len) return (i8)0;

    const u64 width = 16;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) i8 tmp[LANES_I8];
    simd_i8 vacc = _mm_set1_epi8(0);

    for (; (i + width) <= len; i += width) {
        simd_i8 va = _mm_load_si128((const simd_i8*)(a + i));
        vacc = _mm_add_epi8(vacc, va);
    }

    _mm_store_si128((simd_i8*)tmp, vacc);
    i8 acc = (i8)0;
    for (u64 lane = 0; lane < LANES_I8; ++lane) {
        acc = acc + tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc + a[i];
    }

    return acc;
}
static inline i16 *stc_simd_add_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 vb = _mm_load_si128((const simd_i16*)(b + i));
        simd_i16 vr = _mm_add_epi16(va, vb);
        _mm_store_si128((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] + b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_mul_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 vb = _mm_load_si128((const simd_i16*)(b + i));
        simd_i16 vr = _mm_mullo_epi16(va, vb);
        _mm_store_si128((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] * b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_sub_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 vb = _mm_load_si128((const simd_i16*)(b + i));
        simd_i16 vr = _mm_sub_epi16(va, vb);
        _mm_store_si128((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] - b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_shl_i16(i16 * restrict out, const i16 * restrict a, const u32 shift_by, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 vr = _mm_slli_epi16(va, shift_by);
        _mm_store_si128((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] << shift_by;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_shr_i16(i16 * restrict out, const i16 * restrict a, const u32 shift_by, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 vr = _mm_srai_epi16(va, shift_by);
        _mm_store_si128((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] >> shift_by;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_and_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 vb = _mm_load_si128((const simd_i16*)(b + i));
        simd_i16 vr = _mm_and_si128(va, vb);
        _mm_store_si128((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_or_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 vb = _mm_load_si128((const simd_i16*)(b + i));
        simd_i16 vr = _mm_or_si128(va, vb);
        _mm_store_si128((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] | b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_xor_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 vb = _mm_load_si128((const simd_i16*)(b + i));
        simd_i16 vr = _mm_xor_si128(va, vb);
        _mm_store_si128((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] ^ b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_andnot_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 vb = _mm_load_si128((const simd_i16*)(b + i));
        simd_i16 vr = _mm_andnot_si128(va, vb);
        _mm_store_si128((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (~a[i]) & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_not_i16(i16 * restrict out, const i16 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = ~a[i];
    }
    return out;
}
static inline i16 *stc_simd_cmpeq_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 vb = _mm_load_si128((const simd_i16*)(b + i));
        simd_i16 vr = _mm_cmpeq_epi16(va, vb);
        _mm_store_si128((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] == b[i]) ? (i16)~0 : (i16)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_cmpne_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i16 all_ones = _mm_set1_epi16(-1);
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 vb = _mm_load_si128((const simd_i16*)(b + i));
        simd_i16 vr = _mm_xor_si128(_mm_cmpeq_epi16(va, vb), all_ones);
        _mm_store_si128((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] != b[i]) ? (i16)~0 : (i16)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_cmplt_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 vb = _mm_load_si128((const simd_i16*)(b + i));
        simd_i16 vr = _mm_cmpgt_epi16(vb, va);
        _mm_store_si128((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] < b[i]) ? (i16)~0 : (i16)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_cmpgt_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 vb = _mm_load_si128((const simd_i16*)(b + i));
        simd_i16 vr = _mm_cmpgt_epi16(va, vb);
        _mm_store_si128((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] > b[i]) ? (i16)~0 : (i16)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_cmple_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i16 all_ones = _mm_set1_epi16(-1);
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 vb = _mm_load_si128((const simd_i16*)(b + i));
        simd_i16 vr = _mm_xor_si128(_mm_cmpgt_epi16(va, vb), all_ones);
        _mm_store_si128((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] <= b[i]) ? (i16)~0 : (i16)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_cmpge_i16(i16 * restrict out, const i16 * restrict a, const i16 * restrict b, const u64 len)
{
    const u64 width = 8;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i16 all_ones = _mm_set1_epi16(-1);
    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 vb = _mm_load_si128((const simd_i16*)(b + i));
        simd_i16 vr = _mm_xor_si128(_mm_cmpgt_epi16(vb, va), all_ones);
        _mm_store_si128((simd_i16*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] >= b[i]) ? (i16)~0 : (i16)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i16 *stc_simd_splat_i16(i16 * restrict out, const i16 value, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = value;
    }
    return out;
}
static inline u64 stc_simd_bitmask_i16(const i16 * restrict a, const u64 len)
{
    u64 out_mask = 0;
    const u64 n = len < 64 ? len : 64;
    for (u64 i = 0; i < n; ++i) {
        out_mask |= ((u64)((((u16)a[i]) >> (16 - 1)) & 1u) << i);
    }
    return out_mask;
}
static inline bool stc_simd_all_true_i16(const i16 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (!a[i]) return false;
    }
    return true;
}
static inline bool stc_simd_any_true_i16(const i16 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i]) return true;
    }
    return false;
}
static inline u64 stc_simd_count_true_i16(const i16 * restrict a, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] != 0);
    }
    return ct;
}
static inline u64 stc_simd_first_true_i16(const i16 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] != 0) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_count_cmpeq_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_i16 vv = _mm_set1_epi16(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_cmpeq_epi16(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));

        va = _mm_load_si128((const simd_i16*)(a + i + width));
        mask = _mm_cmpeq_epi16(va, vv);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_cmpeq_epi16(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] == value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpne_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_i16 vv = _mm_set1_epi16(value);
    const simd_i16 all_ones = _mm_set1_epi16(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_xor_si128(_mm_cmpeq_epi16(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));

        va = _mm_load_si128((const simd_i16*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpeq_epi16(va, vv), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_xor_si128(_mm_cmpeq_epi16(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] != value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmplt_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_i16 vv = _mm_set1_epi16(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_cmpgt_epi16(vv, va);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));

        va = _mm_load_si128((const simd_i16*)(a + i + width));
        mask = _mm_cmpgt_epi16(vv, va);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_cmpgt_epi16(vv, va);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] < value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpgt_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_i16 vv = _mm_set1_epi16(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_cmpgt_epi16(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));

        va = _mm_load_si128((const simd_i16*)(a + i + width));
        mask = _mm_cmpgt_epi16(va, vv);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_cmpgt_epi16(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] > value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmple_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_i16 vv = _mm_set1_epi16(value);
    const simd_i16 all_ones = _mm_set1_epi16(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_xor_si128(_mm_cmpgt_epi16(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));

        va = _mm_load_si128((const simd_i16*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpgt_epi16(va, vv), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_xor_si128(_mm_cmpgt_epi16(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] <= value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpge_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    u64 ct = 0;
    const simd_i16 vv = _mm_set1_epi16(value);
    const simd_i16 all_ones = _mm_set1_epi16(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_xor_si128(_mm_cmpgt_epi16(vv, va), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));

        va = _mm_load_si128((const simd_i16*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpgt_epi16(vv, va), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_xor_si128(_mm_cmpgt_epi16(vv, va), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 2));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] >= value);
    }

    return ct;
}
static inline u64 stc_simd_first_cmpeq_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_i16 vv = _mm_set1_epi16(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_cmpeq_epi16(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);

        va = _mm_load_si128((const simd_i16*)(a + i + width));
        mask = _mm_cmpeq_epi16(va, vv);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_cmpeq_epi16(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; i < len; ++i) {
        if (a[i] == value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpne_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_i16 vv = _mm_set1_epi16(value);
    const simd_i16 all_ones = _mm_set1_epi16(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_xor_si128(_mm_cmpeq_epi16(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);

        va = _mm_load_si128((const simd_i16*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpeq_epi16(va, vv), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_xor_si128(_mm_cmpeq_epi16(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; i < len; ++i) {
        if (a[i] != value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmplt_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_i16 vv = _mm_set1_epi16(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_cmpgt_epi16(vv, va);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);

        va = _mm_load_si128((const simd_i16*)(a + i + width));
        mask = _mm_cmpgt_epi16(vv, va);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_cmpgt_epi16(vv, va);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; i < len; ++i) {
        if (a[i] < value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpgt_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_i16 vv = _mm_set1_epi16(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_cmpgt_epi16(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);

        va = _mm_load_si128((const simd_i16*)(a + i + width));
        mask = _mm_cmpgt_epi16(va, vv);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_cmpgt_epi16(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; i < len; ++i) {
        if (a[i] > value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmple_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_i16 vv = _mm_set1_epi16(value);
    const simd_i16 all_ones = _mm_set1_epi16(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_xor_si128(_mm_cmpgt_epi16(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);

        va = _mm_load_si128((const simd_i16*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpgt_epi16(va, vv), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_xor_si128(_mm_cmpgt_epi16(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; i < len; ++i) {
        if (a[i] <= value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpge_scalar_i16(const i16 * restrict a, const i16 value, const u64 len)
{
    const u64 width = 8;
    u64 i = 0;
    const simd_i16 vv = _mm_set1_epi16(value);
    const simd_i16 all_ones = _mm_set1_epi16(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_xor_si128(_mm_cmpgt_epi16(vv, va), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);

        va = _mm_load_si128((const simd_i16*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpgt_epi16(vv, va), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        simd_i16 mask = _mm_xor_si128(_mm_cmpgt_epi16(vv, va), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 2);
    }

    for (; i < len; ++i) {
        if (a[i] >= value) return i;
    }
    return (u64)-1;
}
static inline i16 stc_simd_reduce_add_i16(const i16 * restrict a, const u64 len)
{
    if (!len) return (i16)0;

    const u64 width = 8;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) i16 tmp[LANES_I16];
    simd_i16 vacc = _mm_set1_epi16(0);

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        vacc = _mm_add_epi16(vacc, va);
    }

    _mm_store_si128((simd_i16*)tmp, vacc);
    i16 acc = (i16)0;
    for (u64 lane = 0; lane < LANES_I16; ++lane) {
        acc = acc + tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc + a[i];
    }

    return acc;
}
static inline i16 stc_simd_reduce_mul_i16(const i16 * restrict a, const u64 len)
{
    if (!len) return (i16)1;

    const u64 width = 8;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) i16 tmp[LANES_I16];
    simd_i16 vacc = _mm_set1_epi16(1);

    for (; (i + width) <= len; i += width) {
        simd_i16 va = _mm_load_si128((const simd_i16*)(a + i));
        vacc = _mm_mullo_epi16(vacc, va);
    }

    _mm_store_si128((simd_i16*)tmp, vacc);
    i16 acc = (i16)1;
    for (u64 lane = 0; lane < LANES_I16; ++lane) {
        acc = acc * tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc * a[i];
    }

    return acc;
}
static inline i32 *stc_simd_add_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 vb = _mm_load_si128((const simd_i32*)(b + i));
        simd_i32 vr = _mm_add_epi32(va, vb);
        _mm_store_si128((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] + b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_mul_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 vb = _mm_load_si128((const simd_i32*)(b + i));
        simd_i32 vr = _mm_mullo_epi32(va, vb);
        _mm_store_si128((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] * b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_sub_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 vb = _mm_load_si128((const simd_i32*)(b + i));
        simd_i32 vr = _mm_sub_epi32(va, vb);
        _mm_store_si128((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] - b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_shl_i32(i32 * restrict out, const i32 * restrict a, const u32 shift_by, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 vr = _mm_slli_epi32(va, shift_by);
        _mm_store_si128((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] << shift_by;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_shr_i32(i32 * restrict out, const i32 * restrict a, const u32 shift_by, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 vr = _mm_srai_epi32(va, shift_by);
        _mm_store_si128((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] >> shift_by;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_and_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 vb = _mm_load_si128((const simd_i32*)(b + i));
        simd_i32 vr = _mm_and_si128(va, vb);
        _mm_store_si128((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_or_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 vb = _mm_load_si128((const simd_i32*)(b + i));
        simd_i32 vr = _mm_or_si128(va, vb);
        _mm_store_si128((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] | b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_xor_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 vb = _mm_load_si128((const simd_i32*)(b + i));
        simd_i32 vr = _mm_xor_si128(va, vb);
        _mm_store_si128((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] ^ b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_andnot_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 vb = _mm_load_si128((const simd_i32*)(b + i));
        simd_i32 vr = _mm_andnot_si128(va, vb);
        _mm_store_si128((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (~a[i]) & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_not_i32(i32 * restrict out, const i32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = ~a[i];
    }
    return out;
}
static inline i32 *stc_simd_cmpeq_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 vb = _mm_load_si128((const simd_i32*)(b + i));
        simd_i32 vr = _mm_cmpeq_epi32(va, vb);
        _mm_store_si128((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] == b[i]) ? (i32)~0 : (i32)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_cmpne_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i32 all_ones = _mm_set1_epi32(-1);
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 vb = _mm_load_si128((const simd_i32*)(b + i));
        simd_i32 vr = _mm_xor_si128(_mm_cmpeq_epi32(va, vb), all_ones);
        _mm_store_si128((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] != b[i]) ? (i32)~0 : (i32)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_cmplt_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 vb = _mm_load_si128((const simd_i32*)(b + i));
        simd_i32 vr = _mm_cmpgt_epi32(vb, va);
        _mm_store_si128((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] < b[i]) ? (i32)~0 : (i32)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_cmpgt_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 vb = _mm_load_si128((const simd_i32*)(b + i));
        simd_i32 vr = _mm_cmpgt_epi32(va, vb);
        _mm_store_si128((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] > b[i]) ? (i32)~0 : (i32)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_cmple_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i32 all_ones = _mm_set1_epi32(-1);
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 vb = _mm_load_si128((const simd_i32*)(b + i));
        simd_i32 vr = _mm_xor_si128(_mm_cmpgt_epi32(va, vb), all_ones);
        _mm_store_si128((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] <= b[i]) ? (i32)~0 : (i32)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_cmpge_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i32 all_ones = _mm_set1_epi32(-1);
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 vb = _mm_load_si128((const simd_i32*)(b + i));
        simd_i32 vr = _mm_xor_si128(_mm_cmpgt_epi32(vb, va), all_ones);
        _mm_store_si128((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] >= b[i]) ? (i32)~0 : (i32)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_splat_i32(i32 * restrict out, const i32 value, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = value;
    }
    return out;
}
static inline u64 stc_simd_bitmask_i32(const i32 * restrict a, const u64 len)
{
    u64 out_mask = 0;
    const u64 n = len < 64 ? len : 64;
    for (u64 i = 0; i < n; ++i) {
        out_mask |= ((u64)((((u32)a[i]) >> (32 - 1)) & 1u) << i);
    }
    return out_mask;
}
static inline bool stc_simd_all_true_i32(const i32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (!a[i]) return false;
    }
    return true;
}
static inline bool stc_simd_any_true_i32(const i32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i]) return true;
    }
    return false;
}
static inline i32 *stc_simd_min_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 vb = _mm_load_si128((const simd_i32*)(b + i));
        simd_i32 vr = _mm_min_epi32(va, vb);
        _mm_store_si128((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] < b[i] ? a[i] : b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i32 *stc_simd_max_i32(i32 * restrict out, const i32 * restrict a, const i32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 vb = _mm_load_si128((const simd_i32*)(b + i));
        simd_i32 vr = _mm_max_epi32(va, vb);
        _mm_store_si128((simd_i32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] > b[i] ? a[i] : b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline u64 stc_simd_count_true_i32(const i32 * restrict a, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] != 0);
    }
    return ct;
}
static inline u64 stc_simd_first_true_i32(const i32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] != 0) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_count_cmpeq_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_i32 vv = _mm_set1_epi32(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_cmpeq_epi32(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));

        va = _mm_load_si128((const simd_i32*)(a + i + width));
        mask = _mm_cmpeq_epi32(va, vv);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_cmpeq_epi32(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] == value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpne_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_i32 vv = _mm_set1_epi32(value);
    const simd_i32 all_ones = _mm_set1_epi32(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_xor_si128(_mm_cmpeq_epi32(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));

        va = _mm_load_si128((const simd_i32*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpeq_epi32(va, vv), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_xor_si128(_mm_cmpeq_epi32(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] != value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmplt_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_i32 vv = _mm_set1_epi32(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_cmpgt_epi32(vv, va);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));

        va = _mm_load_si128((const simd_i32*)(a + i + width));
        mask = _mm_cmpgt_epi32(vv, va);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_cmpgt_epi32(vv, va);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] < value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpgt_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_i32 vv = _mm_set1_epi32(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_cmpgt_epi32(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));

        va = _mm_load_si128((const simd_i32*)(a + i + width));
        mask = _mm_cmpgt_epi32(va, vv);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_cmpgt_epi32(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] > value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmple_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_i32 vv = _mm_set1_epi32(value);
    const simd_i32 all_ones = _mm_set1_epi32(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_xor_si128(_mm_cmpgt_epi32(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));

        va = _mm_load_si128((const simd_i32*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpgt_epi32(va, vv), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_xor_si128(_mm_cmpgt_epi32(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] <= value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpge_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_i32 vv = _mm_set1_epi32(value);
    const simd_i32 all_ones = _mm_set1_epi32(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_xor_si128(_mm_cmpgt_epi32(vv, va), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));

        va = _mm_load_si128((const simd_i32*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpgt_epi32(vv, va), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_xor_si128(_mm_cmpgt_epi32(vv, va), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 4));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] >= value);
    }

    return ct;
}
static inline u64 stc_simd_first_cmpeq_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_i32 vv = _mm_set1_epi32(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_cmpeq_epi32(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);

        va = _mm_load_si128((const simd_i32*)(a + i + width));
        mask = _mm_cmpeq_epi32(va, vv);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_cmpeq_epi32(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; i < len; ++i) {
        if (a[i] == value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpne_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_i32 vv = _mm_set1_epi32(value);
    const simd_i32 all_ones = _mm_set1_epi32(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_xor_si128(_mm_cmpeq_epi32(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);

        va = _mm_load_si128((const simd_i32*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpeq_epi32(va, vv), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_xor_si128(_mm_cmpeq_epi32(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; i < len; ++i) {
        if (a[i] != value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmplt_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_i32 vv = _mm_set1_epi32(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_cmpgt_epi32(vv, va);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);

        va = _mm_load_si128((const simd_i32*)(a + i + width));
        mask = _mm_cmpgt_epi32(vv, va);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_cmpgt_epi32(vv, va);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; i < len; ++i) {
        if (a[i] < value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpgt_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_i32 vv = _mm_set1_epi32(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_cmpgt_epi32(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);

        va = _mm_load_si128((const simd_i32*)(a + i + width));
        mask = _mm_cmpgt_epi32(va, vv);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_cmpgt_epi32(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; i < len; ++i) {
        if (a[i] > value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmple_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_i32 vv = _mm_set1_epi32(value);
    const simd_i32 all_ones = _mm_set1_epi32(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_xor_si128(_mm_cmpgt_epi32(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);

        va = _mm_load_si128((const simd_i32*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpgt_epi32(va, vv), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_xor_si128(_mm_cmpgt_epi32(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; i < len; ++i) {
        if (a[i] <= value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpge_scalar_i32(const i32 * restrict a, const i32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_i32 vv = _mm_set1_epi32(value);
    const simd_i32 all_ones = _mm_set1_epi32(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_xor_si128(_mm_cmpgt_epi32(vv, va), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);

        va = _mm_load_si128((const simd_i32*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpgt_epi32(vv, va), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        simd_i32 mask = _mm_xor_si128(_mm_cmpgt_epi32(vv, va), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 4);
    }

    for (; i < len; ++i) {
        if (a[i] >= value) return i;
    }
    return (u64)-1;
}
static inline i32 stc_simd_reduce_add_i32(const i32 * restrict a, const u64 len)
{
    if (!len) return (i32)0;

    const u64 width = 4;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) i32 tmp[LANES_I32];
    simd_i32 vacc = _mm_set1_epi32(0);

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        vacc = _mm_add_epi32(vacc, va);
    }

    _mm_store_si128((simd_i32*)tmp, vacc);
    i32 acc = (i32)0;
    for (u64 lane = 0; lane < LANES_I32; ++lane) {
        acc = acc + tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc + a[i];
    }

    return acc;
}
static inline i32 stc_simd_reduce_mul_i32(const i32 * restrict a, const u64 len)
{
    if (!len) return (i32)1;

    const u64 width = 4;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) i32 tmp[LANES_I32];
    simd_i32 vacc = _mm_set1_epi32(1);

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        vacc = _mm_mullo_epi32(vacc, va);
    }

    _mm_store_si128((simd_i32*)tmp, vacc);
    i32 acc = (i32)1;
    for (u64 lane = 0; lane < LANES_I32; ++lane) {
        acc = acc * tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc * a[i];
    }

    return acc;
}
static inline i32 stc_simd_reduce_min_i32(const i32 * restrict a, const u64 len)
{
    if (!len) return (i32)0;

    const u64 width = 4;
    u64 i = 1;
    __attribute__((aligned(STC_SIMD_ALIGN))) i32 tmp[LANES_I32];
    simd_i32 vacc = _mm_set1_epi32(a[0]);

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        vacc = _mm_min_epi32(vacc, va);
    }

    _mm_store_si128((simd_i32*)tmp, vacc);
    i32 acc = a[0];
    for (u64 lane = 0; lane < LANES_I32; ++lane) {
        acc = acc < tmp[lane] ? acc : tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc < a[i] ? acc : a[i];
    }

    return acc;
}
static inline i32 stc_simd_reduce_max_i32(const i32 * restrict a, const u64 len)
{
    if (!len) return (i32)0;

    const u64 width = 4;
    u64 i = 1;
    __attribute__((aligned(STC_SIMD_ALIGN))) i32 tmp[LANES_I32];
    simd_i32 vacc = _mm_set1_epi32(a[0]);

    for (; (i + width) <= len; i += width) {
        simd_i32 va = _mm_load_si128((const simd_i32*)(a + i));
        vacc = _mm_max_epi32(vacc, va);
    }

    _mm_store_si128((simd_i32*)tmp, vacc);
    i32 acc = a[0];
    for (u64 lane = 0; lane < LANES_I32; ++lane) {
        acc = acc > tmp[lane] ? acc : tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc > a[i] ? acc : a[i];
    }

    return acc;
}
static inline i64 *stc_simd_add_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 vb = _mm_load_si128((const simd_i64*)(b + i));
        simd_i64 vr = _mm_add_epi64(va, vb);
        _mm_store_si128((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] + b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_sub_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 vb = _mm_load_si128((const simd_i64*)(b + i));
        simd_i64 vr = _mm_sub_epi64(va, vb);
        _mm_store_si128((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] - b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_shl_i64(i64 * restrict out, const i64 * restrict a, const u32 shift_by, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 vr = _mm_slli_epi64(va, shift_by);
        _mm_store_si128((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] << shift_by;
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_shr_i64(i64 * restrict out, const i64 * restrict a, const u32 shift_by, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = a[i] >> shift_by;
    }
    return out;
}
static inline i64 *stc_simd_and_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 vb = _mm_load_si128((const simd_i64*)(b + i));
        simd_i64 vr = _mm_and_si128(va, vb);
        _mm_store_si128((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_or_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 vb = _mm_load_si128((const simd_i64*)(b + i));
        simd_i64 vr = _mm_or_si128(va, vb);
        _mm_store_si128((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] | b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_xor_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 vb = _mm_load_si128((const simd_i64*)(b + i));
        simd_i64 vr = _mm_xor_si128(va, vb);
        _mm_store_si128((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] ^ b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_andnot_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 vb = _mm_load_si128((const simd_i64*)(b + i));
        simd_i64 vr = _mm_andnot_si128(va, vb);
        _mm_store_si128((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = (~a[i]) & b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_not_i64(i64 * restrict out, const i64 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = ~a[i];
    }
    return out;
}
static inline i64 *stc_simd_cmpeq_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 vb = _mm_load_si128((const simd_i64*)(b + i));
        simd_i64 vr = _mm_cmpeq_epi64(va, vb);
        _mm_store_si128((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] == b[i]) ? (i64)~0 : (i64)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_cmpne_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i64 all_ones = _mm_set1_epi64x(-1);
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 vb = _mm_load_si128((const simd_i64*)(b + i));
        simd_i64 vr = _mm_xor_si128(_mm_cmpeq_epi64(va, vb), all_ones);
        _mm_store_si128((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] != b[i]) ? (i64)~0 : (i64)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_cmplt_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 vb = _mm_load_si128((const simd_i64*)(b + i));
        simd_i64 vr = _mm_cmpgt_epi64(vb, va);
        _mm_store_si128((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] < b[i]) ? (i64)~0 : (i64)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_cmpgt_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 vb = _mm_load_si128((const simd_i64*)(b + i));
        simd_i64 vr = _mm_cmpgt_epi64(va, vb);
        _mm_store_si128((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] > b[i]) ? (i64)~0 : (i64)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_cmple_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i64 all_ones = _mm_set1_epi64x(-1);
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 vb = _mm_load_si128((const simd_i64*)(b + i));
        simd_i64 vr = _mm_xor_si128(_mm_cmpgt_epi64(va, vb), all_ones);
        _mm_store_si128((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] <= b[i]) ? (i64)~0 : (i64)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_cmpge_i64(i64 * restrict out, const i64 * restrict a, const i64 * restrict b, const u64 len)
{
    const u64 width = 2;
    u64 rem = len % width;
    u64 i = 0;
    const simd_i64 all_ones = _mm_set1_epi64x(-1);
    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 vb = _mm_load_si128((const simd_i64*)(b + i));
        simd_i64 vr = _mm_xor_si128(_mm_cmpgt_epi64(vb, va), all_ones);
        _mm_store_si128((simd_i64*)(out + i), vr);
    }

    while (rem) {
        out[i] = (a[i] >= b[i]) ? (i64)~0 : (i64)0;
        ++i;
        --rem;
    }

    return out;
}
static inline i64 *stc_simd_splat_i64(i64 * restrict out, const i64 value, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = value;
    }
    return out;
}
static inline u64 stc_simd_bitmask_i64(const i64 * restrict a, const u64 len)
{
    u64 out_mask = 0;
    const u64 n = len < 64 ? len : 64;
    for (u64 i = 0; i < n; ++i) {
        out_mask |= ((u64)((((u64)a[i]) >> (64 - 1)) & 1u) << i);
    }
    return out_mask;
}
static inline bool stc_simd_all_true_i64(const i64 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (!a[i]) return false;
    }
    return true;
}
static inline bool stc_simd_any_true_i64(const i64 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i]) return true;
    }
    return false;
}
static inline u64 stc_simd_count_true_i64(const i64 * restrict a, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] != 0);
    }
    return ct;
}
static inline u64 stc_simd_first_true_i64(const i64 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] != 0) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_count_cmpeq_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 2;
    u64 i = 0;
    u64 ct = 0;
    const simd_i64 vv = _mm_set1_epi64x(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_cmpeq_epi64(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));

        va = _mm_load_si128((const simd_i64*)(a + i + width));
        mask = _mm_cmpeq_epi64(va, vv);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_cmpeq_epi64(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] == value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpne_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 2;
    u64 i = 0;
    u64 ct = 0;
    const simd_i64 vv = _mm_set1_epi64x(value);
    const simd_i64 all_ones = _mm_set1_epi64x(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_xor_si128(_mm_cmpeq_epi64(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));

        va = _mm_load_si128((const simd_i64*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpeq_epi64(va, vv), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_xor_si128(_mm_cmpeq_epi64(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] != value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmplt_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 2;
    u64 i = 0;
    u64 ct = 0;
    const simd_i64 vv = _mm_set1_epi64x(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_cmpgt_epi64(vv, va);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));

        va = _mm_load_si128((const simd_i64*)(a + i + width));
        mask = _mm_cmpgt_epi64(vv, va);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_cmpgt_epi64(vv, va);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] < value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpgt_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 2;
    u64 i = 0;
    u64 ct = 0;
    const simd_i64 vv = _mm_set1_epi64x(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_cmpgt_epi64(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));

        va = _mm_load_si128((const simd_i64*)(a + i + width));
        mask = _mm_cmpgt_epi64(va, vv);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_cmpgt_epi64(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] > value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmple_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 2;
    u64 i = 0;
    u64 ct = 0;
    const simd_i64 vv = _mm_set1_epi64x(value);
    const simd_i64 all_ones = _mm_set1_epi64x(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_xor_si128(_mm_cmpgt_epi64(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));

        va = _mm_load_si128((const simd_i64*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpgt_epi64(va, vv), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_xor_si128(_mm_cmpgt_epi64(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] <= value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpge_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 2;
    u64 i = 0;
    u64 ct = 0;
    const simd_i64 vv = _mm_set1_epi64x(value);
    const simd_i64 all_ones = _mm_set1_epi64x(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_xor_si128(_mm_cmpgt_epi64(vv, va), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));

        va = _mm_load_si128((const simd_i64*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpgt_epi64(vv, va), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_xor_si128(_mm_cmpgt_epi64(vv, va), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        ct += (u64)((__builtin_popcount((u32)bits) / 8));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] >= value);
    }

    return ct;
}
static inline u64 stc_simd_first_cmpeq_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 2;
    u64 i = 0;
    const simd_i64 vv = _mm_set1_epi64x(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_cmpeq_epi64(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);

        va = _mm_load_si128((const simd_i64*)(a + i + width));
        mask = _mm_cmpeq_epi64(va, vv);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_cmpeq_epi64(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; i < len; ++i) {
        if (a[i] == value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpne_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 2;
    u64 i = 0;
    const simd_i64 vv = _mm_set1_epi64x(value);
    const simd_i64 all_ones = _mm_set1_epi64x(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_xor_si128(_mm_cmpeq_epi64(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);

        va = _mm_load_si128((const simd_i64*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpeq_epi64(va, vv), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_xor_si128(_mm_cmpeq_epi64(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; i < len; ++i) {
        if (a[i] != value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmplt_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 2;
    u64 i = 0;
    const simd_i64 vv = _mm_set1_epi64x(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_cmpgt_epi64(vv, va);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);

        va = _mm_load_si128((const simd_i64*)(a + i + width));
        mask = _mm_cmpgt_epi64(vv, va);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_cmpgt_epi64(vv, va);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; i < len; ++i) {
        if (a[i] < value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpgt_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 2;
    u64 i = 0;
    const simd_i64 vv = _mm_set1_epi64x(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_cmpgt_epi64(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);

        va = _mm_load_si128((const simd_i64*)(a + i + width));
        mask = _mm_cmpgt_epi64(va, vv);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_cmpgt_epi64(va, vv);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; i < len; ++i) {
        if (a[i] > value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmple_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 2;
    u64 i = 0;
    const simd_i64 vv = _mm_set1_epi64x(value);
    const simd_i64 all_ones = _mm_set1_epi64x(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_xor_si128(_mm_cmpgt_epi64(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);

        va = _mm_load_si128((const simd_i64*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpgt_epi64(va, vv), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_xor_si128(_mm_cmpgt_epi64(va, vv), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; i < len; ++i) {
        if (a[i] <= value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpge_scalar_i64(const i64 * restrict a, const i64 value, const u64 len)
{
    const u64 width = 2;
    u64 i = 0;
    const simd_i64 vv = _mm_set1_epi64x(value);
    const simd_i64 all_ones = _mm_set1_epi64x(-1);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_xor_si128(_mm_cmpgt_epi64(vv, va), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);

        va = _mm_load_si128((const simd_i64*)(a + i + width));
        mask = _mm_xor_si128(_mm_cmpgt_epi64(vv, va), all_ones);
        bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return (i + width) + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        simd_i64 mask = _mm_xor_si128(_mm_cmpgt_epi64(vv, va), all_ones);
        u32 bits = (u32)(_mm_movemask_epi8(mask));
        if (bits) return i + (u64)(__builtin_ctz((u32)bits) / 8);
    }

    for (; i < len; ++i) {
        if (a[i] >= value) return i;
    }
    return (u64)-1;
}
static inline i64 stc_simd_reduce_add_i64(const i64 * restrict a, const u64 len)
{
    if (!len) return (i64)0;

    const u64 width = 2;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) i64 tmp[LANES_I64];
    simd_i64 vacc = _mm_set1_epi64x(0);

    for (; (i + width) <= len; i += width) {
        simd_i64 va = _mm_load_si128((const simd_i64*)(a + i));
        vacc = _mm_add_epi64(vacc, va);
    }

    _mm_store_si128((simd_i64*)tmp, vacc);
    i64 acc = (i64)0;
    for (u64 lane = 0; lane < LANES_I64; ++lane) {
        acc = acc + tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc + a[i];
    }

    return acc;
}
static inline f32 *stc_simd_add_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm_add_ps(va, vb);
        _mm_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] + b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_mul_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm_mul_ps(va, vb);
        _mm_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] * b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_sub_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm_sub_ps(va, vb);
        _mm_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] - b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_div_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm_div_ps(va, vb);
        _mm_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] / b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_and_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm_and_ps(va, vb);
        _mm_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ua, ub, ur;
        ua.f = a[i];
        ub.f = b[i];
        ur.u = ua.u & ub.u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_or_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm_or_ps(va, vb);
        _mm_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ua, ub, ur;
        ua.f = a[i];
        ub.f = b[i];
        ur.u = ua.u | ub.u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_xor_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm_xor_ps(va, vb);
        _mm_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ua, ub, ur;
        ua.f = a[i];
        ub.f = b[i];
        ur.u = ua.u ^ ub.u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_andnot_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm_andnot_ps(va, vb);
        _mm_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ua, ub, ur;
        ua.f = a[i];
        ub.f = b[i];
        ur.u = (~ua.u) & ub.u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_not_f32(f32 * restrict out, const f32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        union { u32 u; f32 f; } ua, ur;
        ua.f = a[i];
        ur.u = ~ua.u;
        out[i] = ur.f;
    }
    return out;
}
static inline f32 *stc_simd_cmpeq_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm_cmpeq_ps(va, vb);
        _mm_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ur;
        ur.u = (a[i] == b[i]) ? 0xffffffffu : 0u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_cmpne_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm_cmpneq_ps(va, vb);
        _mm_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ur;
        ur.u = (a[i] != b[i]) ? 0xffffffffu : 0u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_cmplt_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm_cmplt_ps(va, vb);
        _mm_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ur;
        ur.u = (a[i] < b[i]) ? 0xffffffffu : 0u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_cmpgt_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm_cmpgt_ps(va, vb);
        _mm_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ur;
        ur.u = (a[i] > b[i]) ? 0xffffffffu : 0u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_cmple_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm_cmple_ps(va, vb);
        _mm_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ur;
        ur.u = (a[i] <= b[i]) ? 0xffffffffu : 0u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_cmpge_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm_cmpge_ps(va, vb);
        _mm_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        union { u32 u; f32 f; } ur;
        ur.u = (a[i] >= b[i]) ? 0xffffffffu : 0u;
        out[i] = ur.f;
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_splat_f32(f32 * restrict out, const f32 value, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        out[i] = value;
    }
    return out;
}
static inline u64 stc_simd_bitmask_f32(const f32 * restrict a, const u64 len)
{
    u64 out_mask = 0;
    const u64 n = len < 64 ? len : 64;
    for (u64 i = 0; i < n; ++i) {
        union { f32 f; u32 u; } bits;
        bits.f = a[i];
        out_mask |= ((u64)((bits.u >> 31) & 1u) << i);
    }
    return out_mask;
}
static inline bool stc_simd_all_true_f32(const f32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (!a[i]) return false;
    }
    return true;
}
static inline bool stc_simd_any_true_f32(const f32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i]) return true;
    }
    return false;
}
static inline f32 *stc_simd_min_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm_min_ps(va, vb);
        _mm_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] < b[i] ? a[i] : b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline f32 *stc_simd_max_f32(f32 * restrict out, const f32 * restrict a, const f32 * restrict b, const u64 len)
{
    const u64 width = 4;
    u64 rem = len % width;
    u64 i = 0;
    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 vb = _mm_load_ps((const f32*)(b + i));
        simd_f32 vr = _mm_max_ps(va, vb);
        _mm_store_ps((f32*)(out + i), vr);
    }

    while (rem) {
        out[i] = a[i] > b[i] ? a[i] : b[i];
        ++i;
        --rem;
    }

    return out;
}
static inline u64 stc_simd_count_true_f32(const f32 * restrict a, const u64 len)
{
    u64 ct = 0;
    for (u64 i = 0; i < len; ++i) {
        ct += (u64)(a[i] != 0);
    }
    return ct;
}
static inline u64 stc_simd_first_true_f32(const f32 * restrict a, const u64 len)
{
    for (u64 i = 0; i < len; ++i) {
        if (a[i] != 0) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_count_cmpeq_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_f32 vv = _mm_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmpeq_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm_load_ps((const f32*)(a + i + width));
        mask = _mm_cmpeq_ps(va, vv);
        bits = (u32)(_mm_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmpeq_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] == value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpne_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_f32 vv = _mm_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmpneq_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm_load_ps((const f32*)(a + i + width));
        mask = _mm_cmpneq_ps(va, vv);
        bits = (u32)(_mm_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmpneq_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] != value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmplt_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_f32 vv = _mm_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmplt_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm_load_ps((const f32*)(a + i + width));
        mask = _mm_cmplt_ps(va, vv);
        bits = (u32)(_mm_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmplt_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] < value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpgt_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_f32 vv = _mm_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmpgt_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm_load_ps((const f32*)(a + i + width));
        mask = _mm_cmpgt_ps(va, vv);
        bits = (u32)(_mm_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmpgt_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] > value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmple_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_f32 vv = _mm_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmple_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm_load_ps((const f32*)(a + i + width));
        mask = _mm_cmple_ps(va, vv);
        bits = (u32)(_mm_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmple_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] <= value);
    }

    return ct;
}
static inline u64 stc_simd_count_cmpge_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    u64 ct = 0;
    const simd_f32 vv = _mm_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmpge_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));

        va = _mm_load_ps((const f32*)(a + i + width));
        mask = _mm_cmpge_ps(va, vv);
        bits = (u32)(_mm_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmpge_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        ct += (u64)(__builtin_popcount((u32)bits));
    }

    for (; i < len; ++i) {
        ct += (u64)(a[i] >= value);
    }

    return ct;
}
static inline u64 stc_simd_first_cmpeq_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_f32 vv = _mm_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmpeq_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm_load_ps((const f32*)(a + i + width));
        mask = _mm_cmpeq_ps(va, vv);
        bits = (u32)(_mm_movemask_ps(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmpeq_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] == value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpne_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_f32 vv = _mm_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmpneq_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm_load_ps((const f32*)(a + i + width));
        mask = _mm_cmpneq_ps(va, vv);
        bits = (u32)(_mm_movemask_ps(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmpneq_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] != value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmplt_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_f32 vv = _mm_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmplt_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm_load_ps((const f32*)(a + i + width));
        mask = _mm_cmplt_ps(va, vv);
        bits = (u32)(_mm_movemask_ps(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmplt_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] < value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpgt_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_f32 vv = _mm_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmpgt_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm_load_ps((const f32*)(a + i + width));
        mask = _mm_cmpgt_ps(va, vv);
        bits = (u32)(_mm_movemask_ps(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmpgt_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] > value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmple_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_f32 vv = _mm_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmple_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm_load_ps((const f32*)(a + i + width));
        mask = _mm_cmple_ps(va, vv);
        bits = (u32)(_mm_movemask_ps(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmple_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] <= value) return i;
    }
    return (u64)-1;
}
static inline u64 stc_simd_first_cmpge_scalar_f32(const f32 * restrict a, const f32 value, const u64 len)
{
    const u64 width = 4;
    u64 i = 0;
    const simd_f32 vv = _mm_set1_ps(value);

    for (; (i + (2 * width)) <= len; i += (2 * width)) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmpge_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);

        va = _mm_load_ps((const f32*)(a + i + width));
        mask = _mm_cmpge_ps(va, vv);
        bits = (u32)(_mm_movemask_ps(mask));
        if (bits) return (i + width) + (u64)__builtin_ctz((u32)bits);
    }

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        simd_f32 mask = _mm_cmpge_ps(va, vv);
        u32 bits = (u32)(_mm_movemask_ps(mask));
        if (bits) return i + (u64)__builtin_ctz((u32)bits);
    }

    for (; i < len; ++i) {
        if (a[i] >= value) return i;
    }
    return (u64)-1;
}
static inline f32 stc_simd_reduce_add_f32(const f32 * restrict a, const u64 len)
{
    if (!len) return (f32)0;

    const u64 width = 4;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) f32 tmp[LANES_F32];
    simd_f32 vacc = _mm_set1_ps(0);

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        vacc = _mm_add_ps(vacc, va);
    }

    _mm_store_ps((f32*)tmp, vacc);
    f32 acc = (f32)0;
    for (u64 lane = 0; lane < LANES_F32; ++lane) {
        acc = acc + tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc + a[i];
    }

    return acc;
}
static inline f32 stc_simd_reduce_mul_f32(const f32 * restrict a, const u64 len)
{
    if (!len) return (f32)1;

    const u64 width = 4;
    u64 i = 0;
    __attribute__((aligned(STC_SIMD_ALIGN))) f32 tmp[LANES_F32];
    simd_f32 vacc = _mm_set1_ps(1);

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        vacc = _mm_mul_ps(vacc, va);
    }

    _mm_store_ps((f32*)tmp, vacc);
    f32 acc = (f32)1;
    for (u64 lane = 0; lane < LANES_F32; ++lane) {
        acc = acc * tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc * a[i];
    }

    return acc;
}
static inline f32 stc_simd_reduce_min_f32(const f32 * restrict a, const u64 len)
{
    if (!len) return (f32)0;

    const u64 width = 4;
    u64 i = 1;
    __attribute__((aligned(STC_SIMD_ALIGN))) f32 tmp[LANES_F32];
    simd_f32 vacc = _mm_set1_ps(a[0]);

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        vacc = _mm_min_ps(vacc, va);
    }

    _mm_store_ps((f32*)tmp, vacc);
    f32 acc = a[0];
    for (u64 lane = 0; lane < LANES_F32; ++lane) {
        acc = acc < tmp[lane] ? acc : tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc < a[i] ? acc : a[i];
    }

    return acc;
}
static inline f32 stc_simd_reduce_max_f32(const f32 * restrict a, const u64 len)
{
    if (!len) return (f32)0;

    const u64 width = 4;
    u64 i = 1;
    __attribute__((aligned(STC_SIMD_ALIGN))) f32 tmp[LANES_F32];
    simd_f32 vacc = _mm_set1_ps(a[0]);

    for (; (i + width) <= len; i += width) {
        simd_f32 va = _mm_load_ps((const f32*)(a + i));
        vacc = _mm_max_ps(vacc, va);
    }

    _mm_store_ps((f32*)tmp, vacc);
    f32 acc = a[0];
    for (u64 lane = 0; lane < LANES_F32; ++lane) {
        acc = acc > tmp[lane] ? acc : tmp[lane];
    }

    for (; i < len; ++i) {
        acc = acc > a[i] ? acc : a[i];
    }

    return acc;
}

#endif
