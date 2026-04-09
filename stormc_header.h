#pragma once
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#ifdef __clang__
#pragma GCC diagnostic ignored "-Winitializer-overrides"
#pragma GCC diagnostic ignored "-Wc23-extensions"
#endif
#define MAX_UINT64 ((u64)-1)

#define FONT_PATH_DEVAJU_SANS "/data/2026-projs/c/stormlibc/assets/ttf/DejaVuSans.ttf"

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
	#ifndef _POSIX_C_SOURCE
		#define _POSIX_C_SOURCE 200112L
	#endif
	#include <fcntl.h>
	#include <unistd.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <pthread.h>
#endif
#include <assert.h>

#ifdef STORMC_STEAM
	#ifndef __cplusplus
		#error "steam api requires c++. compile with a c++ compiler from a .cpp file or disable stormc_steam"
	#endif
	#include "/data/site_packages/steamsdk/sdk/public/steam/steam_api.h"
#endif
#ifdef STORMC_RAYLIB
	#include "/data/site_packages/raylib/src/raylib.h"
	#include "/data/site_packages/raylib/src/rlgl.h"
	#include "/data/site_packages/raylib/src/raymath.h"
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
#ifdef STORMC_WEBGPU
	#include "webgpu/wgpu.h"
#endif

#define defer(__end_func__, ...) \
	do{\
		__VA_ARGS__;\
		__end_func__;\
	}while(0)


#include "base/stormc_base.h"
#include <stdio.h>
#include <stdarg.h>

static const u32 SIGNF32 = 0x80000000;
static const u32 EXPONENTF32 = 0x7F800000;
static const u32 MANTISSAF32 = 0x7FFFFF;

#define defer_loop(start, end) for(int _i_ = ((start), 0); _i_ == 0; (_i_ += 1, (end)))

#define SELECT(cond, when_true, when_false) ((when_true) * (cond) | (when_false) * !(cond))
#define STRING8_NULL (struct stc_string8){.str = NULL, .len = 0}


#define ILT_GROUPS_COUNT 64ULL
#define ILT_ML0_CT (ILT_GROUPS_COUNT * ILT_GROUPS_COUNT)
#define ILT_TOTAL_INDICES (ILT_ML0_CT * 64ULL)
#define ILT_NIL_REAL_IDX (~0ULL)


struct stc_ilt{
	u64	ml0[ILT_ML0_CT];
	u64	ml0_count;
	u64	ml1[ILT_GROUPS_COUNT];
	u64	ml1_count;
	u64	ml2;
	u64	used_count;
	u64	max;
};



struct ilt_ctx_frame{
	u64	ml1_idx;
	u64	ml1_group;
	u64	ml0_idx;
	u64	ml0_bit;
};

static u64 ilt_next_idx(struct stc_ilt *ilt);
static u64 ilt_top_idx(struct stc_ilt *ilt);
static bool32 ilt_is_empty(struct stc_ilt *ilt);
static bool32 ilt_is_full(struct stc_ilt *ilt);
static u64 ilt_get_ml0_idx(u64 ml1_idx, u64 ml1_current_full_groups);
static u64 ilt_get_real_idx(u64 ml1_idx, u64 ml1_current_full_groups, u64 ml0_bit_offset);
static void ilt_set_ml1_group(struct stc_ilt *ilt, u64 ml1_idx, u64 ml1_group);
static void ilt_unset_ml1_group(struct stc_ilt *ilt, u64 ml1_idx, u64 ml1_group);
static void ilt_count_inc(struct stc_ilt *ilt);
static void ilt_count_dec(struct stc_ilt *ilt);
static struct ilt_ctx_frame ilt_get_ctx_frame(struct stc_ilt *ilt);


struct stc_strbldr{
	stc_byte	*ptr;
	u64		off;
	u64		cmt;
	u64		rsrv;
};


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
	u64			offset_mem;
	u32			ct_strings;
	u32			current_max_strings;
	u64			mem_cmtd;
	u64			mem_rsrvd;
};

struct hash_params{
	const void *data;
	u64	len;
	u64	seed;
};

#define HASHSTR(string, n) \
	stormc_hash_v4u64((struct hash_params){.data = (const void *)string.str, .len = string.len, .seed = n})

#define HASHSTR_SCALAR(string, n) \
	stormc_hash_scalar((struct hash_params){.data = (const void *)string.str, .len = string.len, .seed = n})




u64 ilt_get_real_idx(u64 ml1_idx, u64 ml1_current_full_groups, u64 ml0_bit_offset)
{
	return ml1_idx * ILT_ML0_CT + ml1_current_full_groups * ILT_GROUPS_COUNT + ml0_bit_offset;
}


void ilt_set_ml1_group(struct stc_ilt *ilt, u64 ml1_idx, u64 ml1_group)
{
	ilt->ml1[ml1_idx] |= (1llu << ml1_group);

	if (ilt->ml1[ml1_idx] == ~0ULL) {
		ilt->ml2 |= (1llu << ml1_idx);
	}
}


void ilt_unset_ml1_group(struct stc_ilt *ilt, u64 ml1_idx, u64 ml1_group)
{
	ilt->ml1[ml1_idx] &= ~(1llu << ml1_group);

	if (ilt->ml1[ml1_idx] != ~0ULL) {
		ilt->ml2 &= ~(1llu << ml1_idx);
	}
}


u64 ilt_get_ml0_idx(u64 ml1_idx, u64 ml1_current_full_groups)
{
	return ml1_idx * ILT_GROUPS_COUNT + ml1_current_full_groups;
}

void ilt_count_inc(struct stc_ilt *ilt)
{
	ilt->used_count++;
}

void ilt_count_dec(struct stc_ilt *ilt)
{
	ilt->used_count--;
}


struct ilt_ctx_frame ilt_get_ctx_frame(struct stc_ilt *ilt)
{
	struct ilt_ctx_frame pl;
	u64 ml2_free_mask = ~ilt->ml2;
	if (!ml2_free_mask) {
		printf("ILT is full\nAborting\n");
		pl.ml0_bit = ~0ULL;
		pl.ml1_idx = ~0ULL;
		pl.ml0_idx = ~0ULL;
		pl.ml1_group = ~0ULL;
		return pl;
	}
	u64 ml1_idx = __builtin_ctzll(ml2_free_mask);
	u64 ml1_free_mask = ~ilt->ml1[ml1_idx];
	assert(ml1_free_mask != 0);
	u64 group = __builtin_ctzll(ml1_free_mask);
	u64 ml0_idx = ilt_get_ml0_idx(ml1_idx, group);
	u64 ml0_free_mask = ~ilt->ml0[ml0_idx];
	assert(ml0_free_mask != 0);
	u64 bit = __builtin_ctzll(ml0_free_mask);
	pl.ml1_idx = ml1_idx;
	pl.ml0_idx = ml0_idx;
	pl.ml0_bit = bit;
	pl.ml1_group = group;

	return pl;
}


bool32 ilt_is_full(struct stc_ilt *ilt)
{
	return ilt_top_idx(ilt) == ~0ULL;
}

inline bool32 ilt_is_empty(struct stc_ilt *ilt)
{
	return ilt->used_count == 0;
}


u64 ilt_top_idx(struct stc_ilt *ilt)
{
	struct ilt_ctx_frame frame = ilt_get_ctx_frame(ilt);
	if (frame.ml1_idx == ~0ULL)
		return ~0ULL;

	return ilt_get_real_idx(frame.ml1_idx, frame.ml1_group, frame.ml0_bit);
}

u64 ilt_next_idx(struct stc_ilt *ilt)
{
	u64 ml2_free = ~ilt->ml2;
	if (unlikely(ml2_free == 0)) {
		printf("ILT is full\nAborting\n");
		exit(1);
	}

	while(ml2_free) {
		u64 ml1_idx = __builtin_ctzll(ml2_free);
		ml2_free &= ml2_free - 1;
		u64 ml1_free = ~ilt->ml1[ml1_idx];
		if (!ml1_free) continue;

		u64 found = __builtin_ctzll(ml1_free);

		u64 ml0_idx = ilt_get_ml0_idx(ml1_idx, found);
		u64 ml0_free = ~ilt->ml0[ml0_idx];
		assert(ml0_free != 0);
		u64 next_ml0_idx = __builtin_ctzll(ml0_free);
		ilt->ml0[ml0_idx] |= (1ULL << next_ml0_idx);
		if (ilt->ml0[ml0_idx] == ~0ULL) {
			ilt_set_ml1_group(ilt, ml1_idx, found);
		}
		return ilt_get_real_idx(ml1_idx, found, next_ml0_idx);
	}

	return ~0ULL;
}



u32 stc_maxu32(u32 a, u32 b)
{
	return (a > b) ? a : b;
}


#ifndef DEFAULT_RESERVATION
#define DEFAULT_RESERVATION (1llu << 33)
#endif

#define STR8LIT(s) (struct stc_string8){.str = (stc_byte*)s, .len = sizeof(s) - 1}
#define STR(X) STR8LIT(X)
#define STR_RUNTIME(s) (struct stc_string8){.str = (stc_byte*)s, .len = sstrlenx(s)}


#define STC_ALIGN_UP(x, align) (((x) + ((align)-1)) & ~((align)-1))
#define STC_ALIGN_DOWN(x, align) ((x) & ~((align)-1))


/*@CORE START*/
#ifdef STORMC_ALLOCATOR
#include "base/stormc_allocator.c"
#endif

static inline bool is_prime(u64 n);
static inline u64 next_prime(u64 n);
static inline bool is_pow2(u64 n);
static inline u64 next_pow2(u64 n);
static inline bool f32_is_nan(f32 n);
static inline f32 minf(f32 a, f32 b);
#ifdef STORMC_MATH
#include "base/stormc_math.c"
#endif

#ifdef STORMC_IO
#include "base/stormc_io.c"
#endif

#ifdef STORMC_THREADING
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
#define STORMC_SDL3
#include "stormc_gfx/stc_gfx.h"
#endif
/*@STORMC_GFX END*/

thisfile u64 stc_diceroll(u64 count, u64 sides);
thisfile u64 stc_random_xorshift(void);
thisfile u64 stc_random(void);
thisfile u64 stc_random_range(u64 min, u64 max);
/*@STORMC RANDOM START*/
#ifdef STORMC_RANDOM
#include "base/stormc_random.c"
#endif
/*@STORMC RANDOM END*/


/*@STORMC_SGL START*/
#ifdef STORMC_SGL
#include "base/stormc_sgl.c"
#endif
/*@STORMC SGL END*/


/*@STORMC_STAG START*/
#ifdef STORMC_STAG
#include "utils/stag/stormc_argument_parser.h"
#endif
/*@STORMC_STAG END*/


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


#pragma GCC diagnostic pop
