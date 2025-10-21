#pragma once
#include "stormc_base.h"
#include "stormc_types.h"

#define STORMC_ALIGN_UP(x, align) (((x) + ((align)-1)) & ~((align)-1))
#define STORMC_ALIGN_DOWN(x, align) ((x) & ~((align)-1))
#define STORMC_ARENA_FULL(arena, count) ((arena)->offset + (count) > (arena)->capacity)

static inline void* stormc_alloc(size_t size)
{
#ifdef _WIN32
  return VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else
  return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1 , 0);
#endif
}

static inline void stormc_free(void *ptr, size_t size)
{
#ifdef _WIN32
    (void)size;               // size ignored on Windows
    VirtualFree(ptr, 0, MEM_RELEASE);
#else
    munmap(ptr, size);
#endif
}

static inline void *stormc_resize(void *ptr, size_t old_size, size_t new_size)
{
#ifdef _WIN32
	void *new_ptr = stormc_alloc(new_size);
	if (new_ptr && ptr) {
		memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);
		stormc_free(ptr, old_size);
	}
	return new_ptr;
#else
    return mremap(ptr, old_size, new_size, MREMAP_MAYMOVE);
#endif

}


typedef struct{
	u8	*block;
	size_t	offset;
	size_t	max_capacity;
}StormC_Arena;

static inline StormC_Arena *stormc_arena_emit(size_t max_cap)
{
	StormC_Arena *pl;

	pl = (StormC_Arena*)stormc_alloc(max_cap);


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
