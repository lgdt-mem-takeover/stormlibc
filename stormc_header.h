#pragma once

#define MAX_UINT64 ((u64)-1)


#ifndef INF
#define INF __builtin_inf()
#endif






#ifdef __cplusplus
#define stc_byte char
#else
#define stc_byte u8
#endif

#ifdef _WIN32
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif

	#ifndef NOGDI
		#define NOGDI
	#endif

	#ifndef NOUSER
		#define NOUSER
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


#define defer(__end_func__, ...) \
	do{\
		__VA_ARGS__;\
		__end_func__;\
	}while(0)

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


#ifdef STORMC_WEBGPU
	#include "webgpu/wgpu.h"
#endif

#include "base/stormc_base.h"
#include <stdio.h>
#include <stdarg.h>

static const u32 SIGNF32 = 0x80000000;
static const u32 EXPONENTF32 = 0x7F800000;
static const u32 MANTISSAF32 = 0x7FFFFF;

#define defer_loop(start, end) for(int _i_ = ((start), 0); _i_ == 0; (_i_ += 1, (end)))

#define SELECT(cond, when_true, when_false) ((when_true) * (cond) | (when_false) * !(cond))
#define STRING8_NULL (struct stc_string8){.str = null, .len = 0}


struct stc_strbldr{
	stc_byte	*ptr;
	u64	off;
	u64	cmt;
	u64	rsrv;
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
	stc_byte			*mem;
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










/*@func decls old*/
thisfile inline bool sstrcmpx(const struct stc_string8 a, const struct stc_string8 b);
thisfile inline u32 sstrlenx(const stc_byte *stc_string8);

/*@func decls new*/
thisfile struct stc_string8 *stc_arena_string8_push(struct stc_arena_string8 *a, u64 count);
thisfile struct stc_string8 stc_arena_string8_push_copy(struct stc_arena_string8 *a, struct stc_string8 s);
thisfile void stc_memcpy(void * restrict destination, const void * restrict source, u64 size);
thisfile void stc_memset(void * restrict destination, u64 value, u64 size);
thisfile void stc_memmove(void *destination, const void *src, u64 size);
thisfile int stc_memcmp(const void * restrict destination, const void * restrict src, u64 size);
thisfile struct stc_string8_split stc_string8_split(struct stc_arena_string8 * restrict a, struct stc_string8 * restrict s, stc_byte delim);
thisfile u32 stc_len_c_string(stc_byte *c_string);
thisfile struct stc_arena_string8 stc_arena_string8_init(u32 string_count_to_init);
thisfile void stc_string8_to_upper(struct stc_string8 *s);
thisfile void stc_c_string_reverse (stc_byte *s, u64 len);
thisfile i64 stc_itoa(i64 n, stc_byte *s);
thisfile struct stc_strbldr stc_strbldr_emit(u64 sz_rsrv, u64 sz_init);
thisfile void check_alloc(struct stc_strbldr *b, u64 new_size);
thisfile void stc_strbldr_add_v(struct stc_strbldr * restrict b, stc_byte * restrict s, va_list args);

thisfile u64 stormc_diceroll(u64 count, u64 sides);
thisfile u64 stormc_random_xorshift(u64 init_state);
thisfile u64 stormc_random(u64 init_state);
thisfile u64 stormc_random_range(u64 min, u64 max, u64 init_state);





#ifndef DEFAULT_RESERVATION
#define DEFAULT_RESERVATION (1llu << 33)
#endif

#define STR8LIT(s) (struct stc_string8){.str = (stc_byte*)s, .len = sizeof(s) - 1}
#define STR(X) STR8LIT(X)
#define STR_RUNTIME(s) (struct stc_string8){.str = (stc_byte*)s, .len = sstrlenx(s)}

static inline u32 sla_u32(const u32 arg, stc_byte shift);
static inline u32 sra_u32(const u32 arg, stc_byte shift);
static inline u32 cmpnz_u32(const u32 arg);
static inline u32 select_u32(const u32 mask, const u32 arg1, const u32 arg2);


static void			stc_alloc_logged(struct stc_stack  *stack, u64 size, const stc_byte* file, int line);
static struct stc_stack		*stc_stack_gen(u64 rsrv);
static void			*stc_os_mem_rsrv(u64 size);
static void			*stc_os_mem_cmt(void *addrs, u64 size);
static void			*_stc_stack_push(struct stc_stack *stack, u64 alignment, u64 alloc_size);
static void			stc_stack_pop(struct stc_stack *stack, u64 size);
static void			stc_stack_start(struct stc_stack *s);
static void			stc_stack_end(struct stc_stack *s);
static void			stc_stack_free(struct stc_stack *stack, void* mem_addrs, u64 len);

#define stc_commit(addrs, size)\
	stc_os_mem_cmt(addrs, size)

#define stc_alloc(size)\
	stc_os_alloc_default(size)


#define STC_ALIGN_UP(x, align) (((x) + ((align)-1)) & ~((align)-1))
#define STC_ALIGN_DOWN(x, align) ((x) & ~((align)-1))







static bool is_prime(u64 n);
static inline u64 next_prime(u64 n);
static inline bool is_pow2(u64 n);
static inline u64 next_pow2(u64 n);
static inline bool f32_is_nan(f32 n);


bool f32_is_nan(f32 f)
{
	union {u32 u; f32 f;} x;
	x.f = f;
	return  ((x.u & EXPONENTF32) == EXPONENTF32) && ((x.u & MANTISSAF32) != 0);
}







/*@CORE START*/
#ifdef STORMC_ALLOCATOR
#include "base/stormc_allocator.c"
#endif

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
