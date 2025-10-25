#pragma once
#include "stormc_base.h"
#include "stormc_types.h"

#define _GNU_SOURCE 1
#include <sys/mman.h>

#define STORMC_ALIGN_UP(x, align) (((x) + ((align)-1)) & ~((align)-1))
#define STORMC_ALIGN_DOWN(x, align) ((x) & ~((align)-1))
#define STORMC_ARENA_FULL(arena, count) ((arena)->offset + (count) > (arena)->max_capacity)


static inline void * stormc_get_rawptr(void *ptr)
{
	void *raw;
	raw = (u8*)ptr - sizeof(size_t);
	return raw;
}

static inline size_t stormc_get_alloc_size(void *ptr)
{
	size_t pl;
	void *raw = stormc_get_rawptr(ptr);
	pl = *(size_t*)raw;
	return pl;
}

static inline void* stormc_alloc(size_t size)
{
	void *raw;
	size_t total  = size + sizeof(size_t);
#ifdef _WIN32
	raw = VirtualAlloc(NULL, total, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else

	raw = mmap(NULL, total, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1 , 0);
#endif
	*(size_t*)raw = total;
	return (u8*)raw + sizeof(size_t);
}

static inline void stormc_free(void *ptr)
{
	size_t size;
	void * raw;
	size = stormc_get_alloc_size(ptr);
	raw = stormc_get_rawptr(ptr);

	#ifdef _WIN32
	    VirtualFree(raw, 0, MEM_RELEASE);
	#else
	munmap(raw, size);
	#endif
}

static inline void *stormc_resize(void *ptr, size_t new_size)
{
	void *raw;
	void *next_raw;
	size_t old_total, new_total;

	raw = stormc_get_rawptr(ptr);
	old_total = stormc_get_alloc_size(ptr);
	new_total = new_size + sizeof(size_t);
#ifdef _WIN32
	void *new_ptr = stormc_alloc(new_size);
	if (new_ptr && ptr) {
		memcpy(new_ptr, ptr, old_total < new_size ? old_total : new_size);
		stormc_free(ptr);
	}
	return new_ptr;
#else
	next_raw = mremap(raw, old_total, new_total, MREMAP_MAYMOVE);
	if (next_raw == MAP_FAILED) return NULL;
	*(size_t*)next_raw = new_total;
	return (u8*)next_raw + sizeof(size_t);
#endif

}

static inline void* stormc_calloc(size_t n, size_t sz)
{
    size_t total = n * sz;
    if (__builtin_mul_overflow(n, sz, &total)) return NULL;
    void *p = stormc_alloc(total);
    if (p) memset(p, 0, total);
    return p;
}


typedef struct{
	u8	*block;
	size_t	offset;
	size_t	max_capacity;
}StormC_Arena;

static inline StormC_Arena *stormc_arena_emit(size_t max_cap)
{
	StormC_Arena *pl;

	pl = (StormC_Arena*)stormc_alloc(max_cap + sizeof(StormC_Arena));


	pl->block = (u8*)pl + sizeof(StormC_Arena);
	pl->offset = 0;
	pl->max_capacity = max_cap;
	return pl;
}

static inline void stormc_arena_reset(StormC_Arena *a)
{
	a->offset = 0;
}

                                                                                         \
#define STORMC_SETUP_ARENA_TYPE(NAME, TYPE)                                              \
static inline TYPE *stormc_alloc_arena_##NAME(StormC_Arena *a, size_t count_elem)        \
{                                                                                        \
	const size_t type_size = sizeof(TYPE);                                           \
	const size_t type_align = __alignof(TYPE);                                       \
                                                                                         \
	count_elem = (count_elem == 0 ? 1 : count_elem) * type_size;                     \
	TYPE *pl;                                                                        \
	size_t offset = STORMC_ALIGN_UP(a->offset, type_align);		                 \
                                                                                         \
	if ((offset + count_elem) > a->max_capacity) return NULL;			 \
                                                                                         \
	a->offset = offset + count_elem;	                                         \
	pl = (TYPE*)(a->block + offset);                                                 \
                                                                                         \
	return pl;                                                                       \
}
