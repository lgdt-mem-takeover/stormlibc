#pragma once

#include "stormc_bitops.c"
#include "stormc_math.c"
#include "/data/2026-projs/c/stormlibc/stormc_header.h"



#ifdef _WIN32
	#include "windows/stormc_allocator.c"
#else
	#include "linux/stormc_allocator.c"
#endif


#define MAX_FREE_LIST_ELEMENTS 65535
struct free_list {
	void	*ptr[MAX_FREE_LIST_ELEMENTS];
	u64	size[MAX_FREE_LIST_ELEMENTS];
	u64	ct_ptrs;
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
#define STACK_HEADER_SIZE sizeof(struct stc_stack)

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
	return pl;
}


void *_stc_stack_push(struct stc_stack *s, u64 alignment, u64 total_size)
{
	if (!is_pow2(alignment))
		alignment = next_pow2(alignment);


	u64 start_old = (u64)s->base + s->base_offset;
	u64 start_new = STC_ALIGN_UP(start_old, alignment);
	u64 end_new = STC_ALIGN_UP(start_new + total_size, alignment);
	u64 delta_offset = end_new - (u64)s->base;


	if (s->free_list.ct_ptrs > 0 && s->free_list.ct_ptrs < MAX_FREE_LIST_ELEMENTS) {
		void *return_ptr = NULL;
		u64 found_idx = 0;
		u64 smallest_fit_size = MAX_UINT64;
		for (u64 i = 0; i < s->free_list.ct_ptrs; ++i) {
			u64 ptr_base_aligned = STC_ALIGN_UP((u64)s->free_list.ptr[i], alignment);
			u64 ptr_aligned_dist_relative_to_base_pointer = ptr_base_aligned - (u64)s->free_list.ptr[i];
			u64 size_after_aligning = s->free_list.size[i] - ptr_aligned_dist_relative_to_base_pointer;
			if (smallest_fit_size >= size_after_aligning && size_after_aligning >= total_size) {
				smallest_fit_size = size_after_aligning;
				return_ptr = (void*)ptr_base_aligned;
				found_idx = i;
			}
		}

		if (return_ptr != NULL) {
			void *temp_ptr = s->free_list.ptr[s->free_list.ct_ptrs - 1];
			s->free_list.ptr[s->free_list.ct_ptrs - 1] = s->free_list.ptr[found_idx];
			s->free_list.ptr[found_idx] = temp_ptr;

			u64 temp_size = s->free_list.size[s->free_list.ct_ptrs - 1];
			s->free_list.size[s->free_list.ct_ptrs - 1] = s->free_list.size[found_idx];
			s->free_list.size[found_idx] = temp_size;
			s->free_list.ct_ptrs--;
			return return_ptr;
		}
	}

	/*s->mem_cmt always stays aligned to page boundary*/
	if (delta_offset > s->mem_committed) {
		u64 delta_commit = STC_ALIGN_UP(delta_offset - s->mem_committed, PAGESIZE);
		u64 new_total_commit = delta_commit + s->mem_committed;
		if (stc_os_mem_cmt((stc_byte*)s->base + s->mem_committed, delta_commit) == NULL) {
			perror("mprotect");
			exit(1);
		}

		s->mem_committed = new_total_commit;
	}

	s->base_offset = delta_offset;

	return (void*)start_new;
}


void stc_stack_free(struct stc_stack *s, void* mem_addrs, u64 size)
{

	if (s->free_list.ct_ptrs < MAX_FREE_LIST_ELEMENTS) {
		s->free_list.ptr[s->free_list.ct_ptrs] = mem_addrs;
		s->free_list.size[s->free_list.ct_ptrs] = size;
		s->free_list.ct_ptrs++;
	}
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
