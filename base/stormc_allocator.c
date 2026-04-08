#pragma once

#include "stormc_math.c"
#include "/data/2026-projs/c/stormlibc/stormc_header.h"

struct free_list {
	struct stc_ilt	ilt;
	u64		*ptr;
	u64		*size;
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

static void			stc_alloc_logged(struct stc_stack  *stack, u64 size, const stc_byte* file, int line);
static struct stc_stack		*stc_stack_gen(u64 rsrv);
static void			*stc_os_mem_rsrv(u64 size);
static void			*stc_os_mem_cmt(void *addrs, u64 size);
static void			*_stc_stack_push(struct stc_stack *stack, u64 alignment, u64 alloc_size);
static void			stc_stack_pop(struct stc_stack *stack, u64 size);
static void			stc_stack_start(struct stc_stack *s);
static void			stc_stack_end(struct stc_stack *s);
static void			stc_stack_free(struct stc_stack *stack, void* mem_addrs, u64 len);
static void			*stc_os_alloc_default(u64 size);
static void			stc_os_mem_free(void *mem, u64 size);


#define stc_rsrv(size)\
	stc_os_mem_rsrv(size)

#define stc_commit(addrs, size)\
	stc_os_mem_cmt(addrs, size)

#define stc_alloc(size)\
	stc_os_alloc_default(size)

#define stc_free(ptr, size)\
	stc_os_mem_free(ptr, size);

#ifdef _WIN32
	#include "windows/stormc_allocator.c"
#else
	#include "linux/stormc_allocator.c"
#endif


#define STACK_HEADER_SIZE sizeof(struct stc_stack)

#define stc_stack_start(stack)\
	stack->checkpoint_offset = stack->base_offset

#define stc_stack_end(stack)\
	stack->base_offset = stack->checkpoint_offset

#define stc_stack_push(__stack, __type, __count)\
	_stc_stack_push((__stack), ALIGNOF(__type), (sizeof(__type) * (__count)))


struct stc_stack *stc_stack_gen(u64 rsrv)
{

	if (!is_pow2(rsrv))
		rsrv = STC_ALIGN_UP(next_pow2(rsrv), PAGESIZE);

	stc_byte *block = (stc_byte *)stc_os_mem_rsrv(rsrv);
	stc_byte *stack_ptr_start = (stc_byte *)STC_ALIGN_UP((u64)block + STACK_HEADER_SIZE, PAGESIZE);
	if (stc_os_mem_cmt(block, STACK_HEADER_SIZE) == NULL) {
		printf("Failed block header size\n");
		perror("mprotect");
		exit(1);
	}
	rsrv = ((u64)block + rsrv) - (u64)stack_ptr_start;
	if (stc_os_mem_cmt(stack_ptr_start, PAGESIZE) == NULL) {
		printf("Failed at stack ptr start\n");
		perror("mprotect");
		exit(1);
	}

	struct stc_stack *pl = (struct stc_stack *)block;
	pl->base = stack_ptr_start;
	pl->mem_rsrv = rsrv;
	pl->mem_committed = PAGESIZE;
	pl->base_offset = 0;
	pl->free_list.ptr = (u64*)stc_os_mem_rsrv(sizeof(u64) * ILT_TOTAL_INDICES);
	pl->free_list.size = (u64*)stc_os_mem_rsrv(sizeof(u64) * ILT_TOTAL_INDICES);
	stc_os_mem_cmt(pl->free_list.ptr, sizeof(u64) * PAGESIZE);
	stc_os_mem_cmt(pl->free_list.size, sizeof(u64) * PAGESIZE);
	pl->free_list.ilt.max = ILT_TOTAL_INDICES;
	return pl;
}

void *_stc_stack_push(struct stc_stack *s, u64 alignment, u64 total_size)
{
	if (!is_pow2(alignment))
		alignment = next_pow2(alignment);


	u64 start_old = (u64)s->base + s->base_offset;
	u64 start_new = STC_ALIGN_UP(start_old, alignment);
	u64 end_new = start_new + total_size;
	u64 size_new = end_new - (u64)s->base;


	if (!ilt_is_empty(&s->free_list.ilt)) {
		u64 smallest_fit = MAX_UINT64;
		u64 smallest_fit_position = MAX_UINT64;
		for (u64 ml1_indx = 0; ml1_indx < 64; ++ml1_indx) {
			for (u64 ml1_group = 0; ml1_group < 64; ++ml1_group) {
				u64 ml0_idx = ilt_get_ml0_idx((u64)ml1_indx, ml1_group);

				if (s->free_list.ilt.ml0[ml0_idx] != 0) {
					int bit_idx = 0;
					while (bit_idx < 64) {
						if (!(s->free_list.ilt.ml0[ml0_idx] & (1llu << bit_idx))) {
							++bit_idx;
							continue;
						}
						u64 real_idx = ilt_get_real_idx(ml1_indx, ml1_group, (u64)bit_idx);
						if (((u64)(s->free_list.ptr[real_idx] & (alignment - 1)) == 0)) {
							if (s->free_list.size[real_idx] < smallest_fit && s->free_list.size[real_idx] >= total_size) {
								smallest_fit = s->free_list.size[real_idx];
								smallest_fit_position = real_idx;
							}
						}
						++bit_idx;
					}
				}
			}
		}

		if (smallest_fit != MAX_UINT64) {
			u64 best_ml1_idx = smallest_fit_position / ILT_ML0_CT;
			u64 best_ml1_group = (smallest_fit_position / ILT_GROUPS_COUNT) % ILT_GROUPS_COUNT;
			s->free_list.ilt.ml0[(smallest_fit_position / ILT_GROUPS_COUNT)] &= ~(1llu << (smallest_fit_position % ILT_GROUPS_COUNT));
			ilt_unset_ml1_group(&s->free_list.ilt, best_ml1_idx, best_ml1_group);
			s->free_list.ilt.used_count--;
			return (void*)s->free_list.ptr[smallest_fit_position];
		}
	}

	/*s->mem_cmt always stays aligned to page boundary*/
	if (size_new > s->mem_committed) {
		u64 delta_commit = STC_ALIGN_UP(size_new - s->mem_committed, PAGESIZE);
		u64 new_total_commit = delta_commit + s->mem_committed;
		assert((s->mem_committed % 4096) == 0);
		if (stc_os_mem_cmt((stc_byte*)s->base + s->mem_committed, delta_commit) == NULL) {
			perror("mprotect");
			exit(1);
		}
		assert((s->mem_committed % 4096) == 0);

		s->mem_committed = new_total_commit;
	}

	s->base_offset = size_new;

	return (void*)start_new;
}


void stc_stack_free(struct stc_stack *s, void* mem_addrs, u64 size)
{
	u64 next_index = ilt_next_idx(&s->free_list.ilt);
	s->free_list.ptr[next_index] = (u64)mem_addrs;
	s->free_list.size[next_index] = size;
	ilt_count_inc(&s->free_list.ilt);
}

void stc_stack_pop(struct stc_stack *stack, u64 size)
{
	bool cond = stack->base_offset >= size;
	// if (unlikely(!cond)) {
	// 	fprintf(stdout, "Tried to pop %lu bytes, but offset is %lu\n", size, stack->base_offset);
	// }
	u64 count_checked = SELECT(cond, stack->base_offset - size, stack->base_offset);
	stack->base_offset = count_checked;
}


void stack_begin(struct stc_stack *s)
{
	s->checkpoint_offset = s->base_offset;
}


void stack_end(struct stc_stack *s)
{
	s->base_offset = s->checkpoint_offset;
}


