#pragma once
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#ifdef __clang__
#pragma GCC diagnostic ignored "-Winitializer-overrides"
#pragma GCC diagnostic ignored "-Wc23-extensions"
#endif

#define stc_cc(...)		(void)0
#define stc_fin(...)		(void)0
#define stc_fout(...)		(void)0
#define stc_run(...)		(void)0
#define stc_nasm(...)		(void)0
#define stc_objs(...)		(void)0
#define stc_defs(...)		(void)0
#define stc_inc_files(...)	(void)0
#define stc_optim(...)		(void)0
#define stc_inc_paths(...)	(void)0
#define stc_inc_libs(...)	(void)0
#define stc_arch(...)		(void)0
#define stc_std(...)		(void)0


#define MAX_UINT64 ((u64)-1)
#define MAX_U(type) ((type)-1)

#ifndef STORMC_ROOT
	#define STORMC_ROOT "."
#endif

#ifndef FONT_PATH_DEJAVU_SANS
	#define FONT_PATH_DEJAVU_SANS STORMC_ROOT "/assets/ttf/DejaVuSans.ttf"
#endif

#ifndef INF
#define INF __builtin_inf()
#endif

#ifdef __cplusplus
#define stc_byte char
#else
#define stc_byte char
#endif

#ifdef _WIN32
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif

	#ifndef NOMINMAX
		#define NOMINMAX
	#endif

    	#include <windows.h>
#else
	#ifndef _XOPEN_SOURCE
		#define _XOPEN_SOURCE 600
	#endif
#endif

#include <assert.h>

#ifdef STORMC_STEAM
	#ifndef __cplusplus
		#error "steam api requires c++. compile with a c++ compiler from a .cpp file or disable stormc_steam"
	#endif
	#ifndef STORMC_STEAM_API_H
		#define STORMC_STEAM_API_H "third_party/steam/public/steam/steam_api.h"
	#endif
	#include STORMC_STEAM_API_H
#endif
#ifdef STORMC_RAYLIB
	#ifndef STORMC_RAYLIB_H
		#define STORMC_RAYLIB_H "third_party/raylib/zig-out/include/raylib.h"
	#endif
	#ifndef STORMC_RLGL_H
		#define STORMC_RLGL_H "third_party/raylib/zig-out/include/rlgl.h"
	#endif
	#ifndef STORMC_RAYMATH_H
		#define STORMC_RAYMATH_H "third_party/raylib/zig-out/include/raymath.h"
	#endif
	#include STORMC_RAYLIB_H
	#include STORMC_RLGL_H
	#include STORMC_RAYMATH_H
#endif



#ifdef STORMC_GFX
	#define STORMC_SDL3
#endif

#ifdef STORMC_SDL3
	#include <SDL3/SDL.h>
	#include <SDL3_image/SDL_image.h>
	#include <SDL3_ttf/SDL_ttf.h>
	#include <SDL3_ttf/SDL_textengine.h>
	#include <SDL3/SDL_error.h>
	#include <SDL3/SDL_gpu.h>
	#include <SDL3/SDL_log.h>
	#include <SDL3/SDL_surface.h>
#endif

#define STC_ARRCOUNT(x) (sizeof(x) / sizeof(*(x)))
#ifdef __cplusplus
#define STC_STATIC_ASSERT static_assert
#else
#define STC_STATIC_ASSERT _Static_assert
#endif
#ifdef STORMC_WEBGPU
	#include "webgpu/wgpu.h"
#endif


#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
typedef  uint8_t		u8;
typedef  uint16_t  		u16;
typedef  uint32_t  		u32;
typedef  uint64_t  		u64;

typedef  int8_t    		i8;
typedef  int16_t   		i16;
typedef  int32_t   		i32;
typedef  int64_t   		i64;
typedef  double			f64;
typedef  float			f32;


extern i32 sasm_atoi32(const char *string, u32 len);
extern i64 sasm_atoi64(const char *string, u32 len);
extern u32 sasm_atou32(const char *string, u32 len);
extern u64 sasm_atou64(const char *string, u32 len);

extern u32 sasm_utoa32(char *buff_out, u32 value);
extern u32 sasm_itoa32(char *buff_out, u32 value);
extern u64 sasm_utoa64(char *buff_out, u64 value);
extern u64 sasm_itoa64(char *buff_out, u64 value);



#ifndef __cplusplus
#ifndef bool
	typedef u8 bool;
#endif
#ifndef true
	#define true 1
#endif

#ifndef false
	#define false 0
#endif
#endif



#ifndef bool16
	typedef u16 bool16;
#endif
#ifndef bool32
	typedef u32 bool32;
#endif
#ifndef bool64
	typedef u64 bool64;
#endif

static const u32 SIGNF32 = 0x80000000;
static const u32 EXPONENTF32 = 0x7F800000;
static const u32 MANTISSAF32 = 0x7FFFFF;

static u32 stc_maxu32(u32 a, u32 b);
static f32 stc_min_f32(f32 a, f32 b);
static f32 stc_max_f32(f32 a, f32 b);
static bool is_prime(u64 n);
static u64 next_prime(u64 n);
static bool is_pow2(u64 n);
static u64 next_pow2(u64 n);
static f32 minf(f32 a, f32 b);
static f32 maxf(f32 a, f32 b);

#include "base/stormc_base.h"


#define STC_ARRAY(__name, _type) \
struct __name {\
	_type	*ptr;\
	u64	len;\
	u64	cap;\
}



#define array_make(_array, _max_cap) \
	do{\
		_array.ptr = stc_global_alloc(TYPEOF(*_array.ptr), _max_cap);\
		_array.cap = _max_cap;\
	}while(0)

#define array_make_with_allocator(_array, _max_cap) \
	do{\
		_array.ptr = allocator(TYPEOF(*_array.ptr), _max_cap);\
		_array.cap = _max_cap;\
	}while(0)


#define array_push(_array, _value) \
	do{\
		if (_array.len >= _array.cap) {\
			stc_println_err("[{u64}]Cannot push more values to array", __LINE__);\
			break;\
		}\
		_array.ptr[_array.len++] = _value;\
	}while(0)

#define array_reset(_array) \
	do{\
		_array.len = 0;\
	}while(0)



#define loop_iter(_array, _value, _index, ...) \
	do{\
		TYPEOF(*_array.ptr) *start = _array.ptr;\
		TYPEOF(*_array.ptr) *end = _array.ptr + _array.len;\
		while (start != end) {\
			TYPEOF(*_array.ptr) *_value = start;\
			u64 _index = start - _array.ptr;\
			__VA_ARGS__ ;\
			++start;\
		}\
	}while(0);


#ifdef STC_SIMD
#include "base/stc_simd_codegen.h"
#endif




struct mat4 {
	f32 v[16];
};

struct rect{
	f32 x, y, w, h;
};

struct vec2 {
	f32 x, y;
};

struct vec2i {
	i32 x, y;
};

struct vec2u {
	i32 x, y;
};

struct vec2lu {
	i32 x, y;
};

struct vec3 {
	f32 x, y, z;
};

struct vec3i {
	i32 x, y, z;
};

struct stc_stack;

struct stc_string8 {
	stc_byte *str;
	u64 len;
};

struct stc_string16{
	u64 len;
	u16 *str;
};

struct stc_string32{
	u64 len;
	u32 *str;
};

struct stc_string8_split{
	struct stc_string8	*strings;
	u64			ct_strings;
};

struct stc_arena_string8{
	struct stc_string8	*strings;
	stc_byte		*mem;
	u64			checkpoint;
	u64			offset_mem;
	u32			ct_strings;
	u32			current_max_strings;
	u64			mem_cmtd;
	u64			mem_rsrvd;
};

struct stc_strbldr{
	stc_byte	*ptr;
	u64		off;
	u64		cmt;
	u64		rsrv;
};

#ifdef __cplusplus
	#define STC_STRUCT_ZERO(name) name{}
	#define STC_STRUCT_LIT(name, ...) name{__VA_ARGS__}
#else
	#define STC_STRUCT_ZERO(name) (struct name){0}
	#define STC_STRUCT_LIT(name, ...) (struct name){__VA_ARGS__}
#endif


static void			stc_alloc_logged(struct stc_stack  *stack, u64 size, const stc_byte* file, int line);
static struct stc_stack		*stc_stack_gen(u64 rsrv);
static void			*stc_os_mem_rsrv(u64 size);
static void			*stc_os_mem_cmt(void *addrs, u64 size);
static void			*_stc_stack_push(struct stc_stack *stack, u64 alignment, u64 alloc_size);
static enum stc_err_code	stc_stack_pop(struct stc_stack *stack, u64 size);
static enum stc_err_code	stc_stack_start(struct stc_stack *s);
static enum stc_err_code	stc_stack_end(struct stc_stack *s);
static enum stc_err_code	stc_stack_free(struct stc_stack *stack, void* mem_addrs, u64 len);
static void			*stc_os_alloc_default(u64 size);
static enum stc_err_code	stc_os_mem_free(void *mem, u64 size);




#define stc_global_alloc(__type, __count) \
	((__type *)stc_global_alloc_raw(ALIGNOF(__type), sizeof(__type) * (__count)))

#define stc_rsrv(__size)\
	stc_os_mem_rsrv(__size)

#define stc_commit(__addrs, __size)\
	stc_os_mem_cmt(__addrs, __size)

#define stc_alloc(__size)\
	stc_os_alloc_default(__size)

#define stc_free(__ptr, __size)\
	stc_os_mem_free(__ptr, __size);



#define STACK_HEADER_SIZE sizeof(struct stc_stack)

#define stc_stack_start(stack)\
	stack->checkpoint_offset = stack->base_offset

#define stc_stack_end(stack)\
	stack->base_offset = stack->checkpoint_offset

#define stc_stack_push(__stack, __type, __count)\
	_stc_stack_push((__stack), ALIGNOF(__type), (sizeof(__type) * (__count)))

#define stc_stack_push_simd(__stack, __type, __count) \
	_stc_stack_push((__stack), STC_SIMD_ALIGN, sizeof(__type) * (__count))


/*@FUNCS_MATH SIGNATURES*/
static f32 stc_clamp_f32(f32 x, f32 min, f32 max);
static f32 stc_lerp_f32(f32 a, f32 b, f32 t);
static f32 stc_inv_lerp_f32(f32 a, f32 b, f32 v);
static f32 stc_remap_f32(f32 in_min, f32 in_max, f32 out_min, f32 out_max, f32 v);
static f32 stc_abs_f32(f32 x);
static f32 stc_sign_f32(f32 x);
static f32 stc_sqrt_f32(f32 x);
static f32 stc_rsqrt_f32(f32 x);
static f32 stc_floor_f32(f32 x);
static f32 stc_ceil_f32(f32 x);
static f32 stc_round_f32(f32 x);
static f32 stc_mod_f32(f32 x, f32 y);
static f32 stc_fract_f32(f32 x);
static f32 stc_sin(f32 x);
static f32 stc_cos(f32 x);
static f32 stc_tan(f32 x);
static f32 stc_asin(f32 x);
static f32 stc_acos(f32 x);
static f32 stc_atan(f32 x);
static f32 stc_atan2(f32 y, f32 x);
static f32 stc_pow(f32 base, f32 exp);
static f32 stc_exp(f32 x);
static f32 stc_log(f32 x);
static f32 stc_log2(f32 x);
static f32 stc_log10(f32 x);
static struct vec2 stc_vec2(f32 x, f32 y);
static struct vec2 stc_add2(struct vec2 a, struct vec2 b);
static struct vec2 stc_sub2(struct vec2 a, struct vec2 b);
static struct vec2 stc_mul2(struct vec2 a, struct vec2 b);
static struct vec2 stc_scale2(struct vec2 v, f32 s);
static f32  stc_dot2(struct vec2 a, struct vec2 b);
static f32  stc_len2(struct vec2 v);
static f32  stc_len2_sq(struct vec2 v);
static struct vec2 stc_norm2(struct vec2 v);
static struct vec2 stc_lerp2(struct vec2 a, struct vec2 b, f32 t);
static struct vec3 stc_vec3(f32 x, f32 y, f32 z);
static struct vec3 stc_add3(struct vec3 a, struct vec3 b);
static struct vec3 stc_sub3(struct vec3 a, struct vec3 b);
static struct vec3 stc_mul3(struct vec3 a, struct vec3 b);
static struct vec3 stc_scale3(struct vec3 v, f32 s);
static f32  stc_dot3(struct vec3 a, struct vec3 b);
static struct vec3 stc_cross3(struct vec3 a, struct vec3 b);
static f32  stc_len3(struct vec3 v);
static struct vec3 stc_norm3(struct vec3 v);
static struct vec3 stc_lerp3(struct vec3 a, struct vec3 b, f32 t);
static struct vec4 stc_add4(struct vec4 a, struct vec4 b);
static struct vec4 stc_scale4(struct vec4 v, f32 s);
static struct vec4 stc_lerp4(struct vec4 a, struct vec4 b, f32 t);

static struct mat4 stc_mat4_identity(void);
static struct mat4 stc_mat4_mul(struct mat4 a, struct mat4 b);
static struct mat4 stc_mat4_translate(struct vec3 t);
static struct mat4 stc_mat4_scale(struct vec3 s);
static struct mat4 stc_mat4_rotate_z(f32 angle);
static struct mat4 stc_mat4_ortho(f32 l, f32 r, f32 b, f32 t, f32 n, f32 f);
static f32 stc_smoothstep(f32 edge0, f32 edge1, f32 x);
static f32 stc_step(f32 edge, f32 x);
static f32 stc_deg_to_rad(f32 deg);
static f32 stc_rad_to_deg(f32 rad);
static bool f32_is_nan(f32 f);


static u64 stc_os_timer_freq(void);
static inline u64 stc_cpu_timer_read(void);
static u64 stc_os_timer_read(void);


#define defer_loop(start, end) for(int _i_ = ((start), 0); _i_ == 0; (_i_ += 1, (end)))

#define SELECT(cond, when_true, when_false) ((when_true) * (cond) | (when_false) * !(cond))
#ifdef __cplusplus
#define STRING8_NULL stc_string8{NULL, 0}
#else
#define STRING8_NULL (struct stc_string8){.str = NULL, .len = 0}
#endif


#define stc_string8_sized(s) ((int)((s).len)), ((s).str)
#define stc_print_string(__string) printf("%.*s\n", (int)__string.len, __string.str)

/* compatibility aliases */
#define sstrcmpx  stc_string8_cmp
#define sstrlenx  stc_len_c_string
#define stc_c_string_len stc_len_c_string
/*@func decls new*/
thisfile inline bool stc_string8_cmp(const struct stc_string8 a, const struct stc_string8 b);
thisfile inline bool stc_string8_cmp_simd(const struct stc_string8 a, const struct stc_string8 b);
thisfile struct stc_string8 *stc_arena_string8_push(struct stc_arena_string8 *a, u64 count);
thisfile struct stc_string8 stc_arena_string8_push_copy(struct stc_arena_string8 *a, struct stc_string8 s);
thisfile void stc_string8_cpy(struct stc_string8 * restrict a, const u64 a_capacity, const struct stc_string8 * restrict b);
thisfile void stc_memcpy(void * restrict destination, const void * restrict source, u64 size);
thisfile void stc_memset(void * restrict destination, u64 value, u64 size);
thisfile void stc_memmove(void *destination, const void *src, u64 size);
thisfile int stc_memcmp(const void * restrict destination, const void * restrict src, u64 size);
thisfile struct stc_string8_split stc_string8_split(struct stc_arena_string8 * restrict a, struct stc_string8 * restrict s, stc_byte delim);
thisfile u64 stc_c_string_len(stc_byte *c_string);
thisfile struct stc_arena_string8 stc_arena_string8_init(u32 string_count_to_init);
thisfile void stc_string8_to_upper(struct stc_string8 *s);
thisfile void stc_c_string_reverse (stc_byte *s, u64 len);
thisfile bool32 stc_c_string_cmp (const stc_byte * restrict a, const u64 alen, const stc_byte * restrict b, const u64 blen);
thisfile u64 stc_itoa(i64 n, stc_byte *s);
thisfile u64 stc_utoa(u64 n, stc_byte *s);
thisfile struct stc_strbldr stc_strbldr_emit(u64 sz_rsrv, u64 sz_init);
thisfile void check_alloc(struct stc_strbldr *b, u64 new_size);
thisfile void stc_strbldr_add_v(struct stc_strbldr * restrict b, const stc_byte * restrict s, va_list args);
thisfile void stc_strbldr_append(struct stc_strbldr *b, const stc_byte *s, ...);
thisfile void stc_strbldr_fprint_range(struct stc_strbldr *b, int start, int end);
thisfile void stc_strbldr_reset(struct stc_strbldr *b);

thisfile enum stc_err_code		stc_io_read(struct stc_file *f, stc_byte *buffer, u64 size, u64 *size_out);
thisfile enum stc_err_code 		stc_io_write(struct stc_file *f, stc_byte *buffer, u64 size, u64 *size_out);
thisfile enum stc_err_code 		stc_io_open_r(struct stc_string8 path, struct stc_file *out);
thisfile enum stc_err_code 		stc_io_open_rw(struct stc_string8 path, struct stc_file *out);
thisfile enum stc_err_code 		stc_io_open_w(struct stc_string8 path, struct stc_file *out);
thisfile enum stc_err_code 		stc_io_open_w_new(struct stc_string8 path, struct stc_file *out);
thisfile enum stc_err_code 		stc_io_open_w_append(struct stc_string8 path, struct stc_file *out);
thisfile enum stc_err_code  		stc_io_get_file_size(struct stc_file *f, u64 *size_out);
thisfile enum stc_err_code		stc_io_file_to_string8(struct stc_file *f, struct stc_string8 *out, u64 *size_out);
thisfile void stc_print_init(void);
thisfile void stc_print_os_stderr(void);
thisfile void stc_print_os_stdout(void);
thisfile void stc_print(const char *fmt, ...);
thisfile void stc_println(const char *fmt, ...);
thisfile void stc_print_err(const char *fmt, ...);
thisfile void stc_println_err(const char *fmt, ...);

thisfile u64 stc_diceroll(u64 count, u64 sides);
thisfile u64 stc_random_xorshift(void);
thisfile u64 stc_random(void);
thisfile u64 stc_random_range(u64 min, u64 max);

struct hash_params{
	const void *data;
	u64	len;
	u64	seed;
};

#define HASHSTR(string, n) \
	stormc_hash_v4u64((struct hash_params){.data = (const void *)string.str, .len = string.len, .seed = n})

#define HASHSTR_SCALAR(string, n) \
	stormc_hash_scalar((struct hash_params){.data = (const void *)string.str, .len = string.len, .seed = n})



#define ILT_CAT2_(a, b) a##b
#define ILT_CAT2(a, b)  ILT_CAT2_(a, b)
#define ILT_CAT3_(a, b, c) a##b##c
#define ILT_CAT3(a, b, c)  ILT_CAT3_(a, b, c)

#define ILT_U(width)        ILT_CAT2(u, width)
#define ILT_UINT_MAX(width) ILT_CAT3(UINT, width, _MAX)

#define STC_MAKE_ILT(width)                                                      \
	STC_STATIC_ASSERT(                                                           \
		(width) == 16 || (width) == 32 || (width) == 64,                        \
		"STC_MAKE_ILT(width): width must be one of 16, 32, 64"                  \
	);                                                                           \
                                                                                 \
	enum {                                                                       \
		ILT##width##_ML2 = 1,                                                    \
		ILT##width##_ML1 = ILT##width##_ML2 * (width),                           \
		ILT##width##_ML0 = ILT##width##_ML1 * (width),                           \
		ILT##width##_CAPACITY = ILT##width##_ML0 * (width),                     \
		ILT##width##_SHIFT = ((width) == 16 ? 4 : ((width) == 32 ? 5 : 6)),     \
		ILT##width##_MASK = (width) - 1,                                         \
		ILT##width##_NIL_IDX = ILT##width##_CAPACITY                             \
	};                                                                           \
                                                                                 \
	struct ILT_CAT2(ilt, width) {                                                \
		ILT_U(width) ml0[ILT##width##_ML0];                                      \
		ILT_U(width) ml1[ILT##width##_ML1];                                      \
		ILT_U(width) ml2;                                                        \
	};                                                                           \
                                                                                 \
	static inline ILT_U(width) ILT_CAT3(stc_ctz_u, width, )(ILT_U(width) n)      \
	{                                                                            \
		return n ? (ILT_U(width))__builtin_ctzll((unsigned long long)n)          \
		         : (ILT_U(width))(width);                                        \
	}                                                                            \
                                                                                 \
	static inline ILT_U(width) ILT_CAT3(ilt, width, _get_ml2_from_idx)(ILT_U(width) idx) \
	{                                                                            \
		return idx >> (ILT##width##_SHIFT * 3u);                                 \
	}                                                                            \
                                                                                 \
	static inline ILT_U(width) ILT_CAT3(ilt, width, _get_ml1_from_idx)(ILT_U(width) idx) \
	{                                                                            \
		return idx >> (ILT##width##_SHIFT * 2u);                                 \
	}                                                                            \
                                                                                 \
	static inline ILT_U(width) ILT_CAT3(ilt, width, _get_ml0_from_idx)(ILT_U(width) idx) \
	{                                                                            \
		return idx >> ILT##width##_SHIFT;                                        \
	}                                                                            \
                                                                                 \
	static inline ILT_U(width) ILT_CAT3(ilt, width, _get_ml0_bit_offset_from_idx)(ILT_U(width) idx) \
	{                                                                            \
		return idx & (ILT_U(width))ILT##width##_MASK;                            \
	}                                                                            \
                                                                                 \
	static inline ILT_U(width) ILT_CAT3(ilt, width, _get_ml1_bit_offset_from_ml0)(ILT_U(width) ml0) \
	{                                                                            \
		return ml0 & (ILT_U(width))ILT##width##_MASK;                            \
	}                                                                            \
                                                                                 \
	static inline ILT_U(width) ILT_CAT3(ilt, width, _get_ml2_bit_offset_from_ml1)(ILT_U(width) ml1) \
	{                                                                            \
		return ml1 & (ILT_U(width))ILT##width##_MASK;                            \
	}                                                                            \
                                                                                 \
	static inline ILT_U(width) ILT_CAT3(ilt, width, _gen_idx)(struct ILT_CAT2(ilt, width) *i) \
	{                                                                            \
		if (i->ml2 == (ILT_U(width))ILT_UINT_MAX(width)) {                       \
			return (ILT_U(width))ILT##width##_NIL_IDX;                           \
		}                                                                        \
                                                                                 \
		ILT_U(width) ml1_idx = ILT_CAT3(stc_ctz_u, width, )((ILT_U(width))~i->ml2); \
		ILT_U(width) ml1_word = i->ml1[ml1_idx];                                 \
		ILT_U(width) ml1_bit_offset = ILT_CAT3(stc_ctz_u, width, )((ILT_U(width))~ml1_word); \
		ILT_U(width) ml0_idx = (ml1_idx * (ILT_U(width))(width)) + ml1_bit_offset; \
		ILT_U(width) ml0_word = i->ml0[ml0_idx];                                 \
		ILT_U(width) ml0_bit_offset = ILT_CAT3(stc_ctz_u, width, )((ILT_U(width))~ml0_word); \
                                                                                 \
		i->ml0[ml0_idx] |= ((ILT_U(width))1u << ml0_bit_offset);                 \
                                                                                 \
		if (i->ml0[ml0_idx] == (ILT_U(width))ILT_UINT_MAX(width)) {              \
			i->ml1[ml1_idx] |= ((ILT_U(width))1u << ml1_bit_offset);             \
			if (i->ml1[ml1_idx] == (ILT_U(width))ILT_UINT_MAX(width)) {          \
				i->ml2 |= ((ILT_U(width))1u << ml1_idx);                         \
			}                                                                    \
		}                                                                        \
                                                                                 \
		return (ml0_idx * (ILT_U(width))(width)) + ml0_bit_offset;              \
	}                                                                            \
                                                                                 \
	static inline void ILT_CAT3(ilt, width, _remove_idx)(struct ILT_CAT2(ilt, width) *i, ILT_U(width) idx) \
	{                                                                            \
		ILT_U(width) ml1 = ILT_CAT3(ilt, width, _get_ml1_from_idx)(idx);        \
		ILT_U(width) ml0 = ILT_CAT3(ilt, width, _get_ml0_from_idx)(idx);        \
		ILT_U(width) ml0_bit_offset = ILT_CAT3(ilt, width, _get_ml0_bit_offset_from_idx)(idx); \
		ILT_U(width) ml1_bit_offset = ILT_CAT3(ilt, width, _get_ml1_bit_offset_from_ml0)(ml0); \
                                                                                 \
		i->ml0[ml0] &= ~((ILT_U(width))1u << ml0_bit_offset);                    \
		i->ml1[ml1] &= ~((ILT_U(width))1u << ml1_bit_offset);                    \
		i->ml2 &= ~((ILT_U(width))1u << ml1);                                    \
	}

STC_MAKE_ILT(64)


struct free_list {
	struct ilt64	ilt;
	u64		*ptr;
	u64		*size;
	u64		used_count;
};

//@STACK STC RUNTIME
struct stc_stack {
	struct free_list	free_list;
	u64			mem_rsrv;
	u64			mem_committed;
	u64			base_offset;
	u64			checkpoint_offset;
	stc_byte		*base;
};




#ifndef DEFAULT_RESERVATION
#define DEFAULT_RESERVATION (1llu << 33)
#endif

#ifdef __cplusplus
#define STR8LIT(s) stc_string8{(stc_byte*)s, sizeof(s) - 1}
#define STR_RUNTIME(s) stc_string8{(stc_byte*)s, sstrlenx(s)}
#else
#define STR8LIT(s) (struct stc_string8){.str = (stc_byte*)s, .len = sizeof(s) - 1}
#define STR_RUNTIME(s) (struct stc_string8){.str = (stc_byte*)s, .len = sstrlenx(s)}
#endif
#define STR(X) STR8LIT(X)


#define STC_ALIGN_UP(x, align) (((x) + ((align)-1)) & ~((align)-1))
#define STC_ALIGN_DOWN(x, align) ((x) & ~((align)-1))




#ifdef STORMC_ALGORITHMS
#define make_qsort(name, type, idx_t, less, greater)                  \
	_Static_assert(((idx_t)-1) < 0, "idx_t must be signed");           \
	void name(type *arr, idx_t low, idx_t high)                        \
	{                                                                  \
		while (low < high) {                                       \
			type pivot = arr[low + ((high - low) >> 1)];       \
                                                                       \
			idx_t lt = low;                                    \
			idx_t i  = low;                                    \
			idx_t gt = high;                                   \
                                                                       \
			while (i <= gt) {                                  \
				if (arr[i] less pivot) {                    \
					if (lt != i) {                       \
						type tmp = arr[lt];          \
						arr[lt] = arr[i];            \
						arr[i] = tmp;                \
					}                                  \
					++lt;                              \
					++i;                               \
				} else if (arr[i] greater pivot) {     \
					if (i != gt) {                     \
						type tmp = arr[i];         \
						arr[i] = arr[gt];          \
						arr[gt] = tmp;             \
					}                                  \
					--gt;                              \
				} else {                               \
					++i;                               \
				}                                      \
			}                                              \
                                                                       \
			/* recurse smaller side first, iterate larger side */   \
			idx_t left_size  = lt - low;                          \
			idx_t right_size = high - gt;                         \
                                                                       \
			if (left_size < right_size) {                         \
				if (low < lt - 1) {                           \
					name(arr, low, lt - 1);               \
				}                                              \
				low = gt + 1;                                  \
			} else {                                           \
				if (gt + 1 < high) {                        \
					name(arr, gt + 1, high);             \
				}                                              \
				high = lt - 1;                                 \
			}                                                  \
		}                                                          \
	}

#define STC_INTROSORT_INSERTION_THRESHOLD 24
#define make_introsort(name, type, idx_t, less, greater)                                      \
	_Static_assert(((idx_t)-1) < 0, "idx_t must be signed");                                   \
                                                                                               \
	static inline void name##_swap(type *a, type *b)                                           \
	{                                                                                          \
		type tmp = *a;                                                                     \
		*a = *b;                                                                           \
		*b = tmp;                                                                           \
	}                                                                                          \
                                                                                               \
	static inline void name##_insertion(type *arr, idx_t low, idx_t high)                     \
	{                                                                                          \
		for (idx_t i = low + 1; i <= high; ++i) {                                          \
			type x = arr[i];                                                            \
			idx_t j = i - 1;                                                           \
			while (j >= low && (x less arr[j])) {                                       \
				arr[j + 1] = arr[j];                                                \
				--j;                                                                 \
			}                                                                          \
			arr[j + 1] = x;                                                            \
		}                                                                                  \
	}                                                                                          \
                                                                                               \
	static inline void name##_sift_down(type *arr, idx_t base, idx_t root, idx_t end)         \
	{                                                                                          \
		for (;;) {                                                                         \
			idx_t child = (root << 1) + 1;                                            \
			if (child > end) break;                                                    \
			idx_t swap_idx = root;                                                     \
			if (arr[base + swap_idx] less arr[base + child]) swap_idx = child;         \
			if (child + 1 <= end && (arr[base + swap_idx] less arr[base + child + 1])) \
				swap_idx = child + 1;                                              \
			if (swap_idx == root) break;                                               \
			name##_swap(&arr[base + root], &arr[base + swap_idx]);                     \
			root = swap_idx;                                                           \
		}                                                                                  \
	}                                                                                          \
                                                                                               \
	static inline void name##_heapsort(type *arr, idx_t low, idx_t high)                      \
	{                                                                                          \
		idx_t n = high - low + 1;                                                         \
		if (n <= 1) return;                                                                \
		for (idx_t start = (n - 2) >> 1;; --start) {                                      \
			name##_sift_down(arr, low, start, n - 1);                                 \
			if (start == 0) break;                                                     \
		}                                                                                  \
		for (idx_t end = n - 1; end > 0; --end) {                                         \
			name##_swap(&arr[low], &arr[low + end]);                                  \
			name##_sift_down(arr, low, 0, end - 1);                                   \
		}                                                                                  \
	}                                                                                          \
                                                                                               \
	static inline idx_t name##_floor_log2_u64(unsigned long long x)                           \
	{                                                                                          \
		idx_t r = 0;                                                                      \
		while (x >>= 1) ++r;                                                              \
		return r;                                                                         \
	}                                                                                          \
                                                                                               \
	void name(type *arr, idx_t low, idx_t high)                                               \
	{                                                                                          \
		if (low >= high) return;                                                           \
                                                                                               \
		idx_t depth_limit = 2 * name##_floor_log2_u64((unsigned long long)(high - low + 1)); \
                                                                                               \
		while (low < high) {                                                               \
			idx_t n = high - low + 1;                                                  \
                                                                                               \
			if (n <= STC_INTROSORT_INSERTION_THRESHOLD) {                               \
				name##_insertion(arr, low, high);                                   \
				return;                                                             \
			}                                                                          \
                                                                                               \
			if (depth_limit == 0) {                                                     \
				name##_heapsort(arr, low, high);                                    \
				return;                                                             \
			}                                                                          \
			--depth_limit;                                                              \
                                                                                               \
			idx_t mid = low + ((high - low) >> 1);                                     \
                                                                                               \
			if (arr[mid] less arr[low])  name##_swap(&arr[mid],  &arr[low]);           \
			if (arr[high] less arr[mid]) name##_swap(&arr[high], &arr[mid]);           \
			if (arr[mid] less arr[low])  name##_swap(&arr[mid],  &arr[low]);           \
                                                                                               \
			type pivot = arr[mid];                                                      \
                                                                                               \
			idx_t lt = low;                                                             \
			idx_t i  = low;                                                             \
			idx_t gt = high;                                                            \
                                                                                               \
			while (i <= gt) {                                                           \
				if (arr[i] less pivot) {                                            \
					if (lt != i) name##_swap(&arr[lt], &arr[i]);                  \
					++lt;                                                          \
					++i;                                                           \
				} else if (arr[i] greater pivot) {                                   \
					if (i != gt) name##_swap(&arr[i], &arr[gt]);                  \
					--gt;                                                          \
				} else {                                                             \
					++i;                                                           \
				}                                                                    \
			}                                                                          \
                                                                                               \
			idx_t left_size  = lt - low;                                                \
			idx_t right_size = high - gt;                                               \
                                                                                               \
			if (left_size < right_size) {                                               \
				if (low < lt - 1) name(arr, low, lt - 1);                          \
				low = gt + 1;                                                       \
			} else {                                                                   \
				if (gt + 1 < high) name(arr, gt + 1, high);                        \
				high = lt - 1;                                                      \
			}                                                                          \
		}                                                                                  \
	}

#endif


/* Feature dependency normalization. Keep implementation includes ordered below. */

#ifdef STORMC_STRING
	#ifndef STORMC_ALLOCATOR
		#define STORMC_ALLOCATOR
	#endif
#endif

#ifdef STORMC_PROFILE
	#ifndef STORMC_STRING
		#define STORMC_STRING
	#endif
	#ifndef STORMC_ALLOCATOR
		#define STORMC_ALLOCATOR
	#endif
	#ifndef STORMC_TIMER
		#define STORMC_TIMER
	#endif
#endif

#ifdef STORMC_THREADING
	#ifndef STORMC_ALLOCATOR
		#define STORMC_ALLOCATOR
	#endif
	#ifndef STORMC_STRING
		#define STORMC_STRING
	#endif
#endif

#ifdef STORMC_IO
	#ifndef STORMC_ALLOCATOR
		#define STORMC_ALLOCATOR
	#endif
	#ifndef STORMC_STRING
		#define STORMC_STRING
	#endif
#endif

#ifdef STORMC_SGL
	#ifndef STORMC_ALLOCATOR
		#define STORMC_ALLOCATOR
	#endif
	#ifndef STORMC_STRING
		#define STORMC_STRING
	#endif
	#ifndef STORMC_MATH
		#define STORMC_MATH
	#endif
	#ifndef STORMC_HASHFUNC
		#define STORMC_HASHFUNC
	#endif
	#ifndef STORMC_IO
		#define STORMC_IO
	#endif
#endif

#ifdef STORMC_GFX
	#ifndef STORMC_ALLOCATOR
		#define STORMC_ALLOCATOR
	#endif
#endif

#ifdef STORMC_HASHMAP
	#ifndef STORMC_ALLOCATOR
		#define STORMC_ALLOCATOR
	#endif
	#ifndef STORMC_HASHFUNC
		#define STORMC_HASHFUNC
	#endif
#endif

/*@CORE START*/
#ifdef STORMC_ALLOCATOR
#ifdef _WIN32
	#include "base/windows/stormc_allocator.c"
#else
	#include "base/linux/stormc_allocator.c"
#endif
#include "base/stormc_allocator.c"
#endif

#ifdef STORMC_MATH
#include "base/stormc_math.c"
#endif

#ifdef STORMC_THREADING
#ifndef _WIN32
	#include <pthread.h>
#endif
#include "base/stormc_threading.c"
#endif

#ifdef STORMC_ASYNC
#include "base/stormc_async.c"
#endif

#ifdef STORMC_SOCKETS
#include "base/stormc_sockets.c"
#endif

/*CORE END*/

/*@TEXT START*/
#ifdef STORMC_STRING
#include "text/stormc_string.c"
#endif
/*@TEXT END*/

#ifdef STORMC_IO
#include "base/stormc_io.c"
#endif


/*@PROFILE START*/
#ifdef STORMC_PROFILE
#include "base/stormc_profile.c"
#endif
/*@PROFILE END*/

/*@HASH START*/
#ifdef STORMC_HASHFUNC
#include "containers/stormc_hash.c"
#endif
#ifdef STORMC_HASHMAP
#include "containers/stormc_hashmap.c"
#endif
/*@HASH END*/

/*@STORMC_GFX START*/
#ifdef STORMC_GFX
#include "stormc_gfx/stc_gfx.h"
#endif
/*@STORMC_GFX END*/

/*@STORMC RANDOM START*/
#ifdef STORMC_RANDOM
#include "base/stormc_random.c"
#endif
/*@STORMC RANDOM END*/




/*@STORMC_STAG START*/
#ifdef STORMC_STAG
#include "utils/stormc_argument_parser.h"
#endif
/*@STORMC_STAG END*/


/*@STORMC_SGL START*/
#ifdef STORMC_SGL
	#include "base/stormc_sgl.c"
#endif
/*@STORMC SGL END*/


/*@STORMC_TIMER START*/
#ifdef STORMC_TIMER
	#include "base/stormc_timer.c"
#endif
/*@STORMC_TIMER END*/

#pragma GCC diagnostic pop
