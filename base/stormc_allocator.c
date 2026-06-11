#pragma once

#include "stormc_error_table.h"

#ifndef STC_GLOBAL_STACK_DEFAULT_RSRV
#define STC_GLOBAL_STACK_DEFAULT_RSRV GIGABYTE(1)
#endif


static struct stc_stack *stc_stack_gen(u64 rsrv)
{
	u64 min_rsrv = STC_ALIGN_UP(STACK_HEADER_SIZE, PAGESIZE) + PAGESIZE;
	if (rsrv < min_rsrv)
		rsrv = min_rsrv;

	if (!is_pow2(rsrv))
		rsrv = STC_ALIGN_UP(next_pow2(rsrv), PAGESIZE);

	stc_byte *block = (stc_byte *)stc_os_mem_rsrv(rsrv);
	stc_byte *stack_ptr_start = (stc_byte *)STC_ALIGN_UP((u64)block + STACK_HEADER_SIZE, PAGESIZE);
	if (stc_os_mem_cmt(block, STACK_HEADER_SIZE) == NULL) {
		stc_println("[{u32}]Failed block header size\n", __LINE__);
		perror("mprotect");
		stc_exit(1);
	}
	rsrv = ((u64)block + rsrv) - (u64)stack_ptr_start;
	if (stc_os_mem_cmt(stack_ptr_start, PAGESIZE) == NULL) {
		stc_println("[{u32}]Failed at stack ptr start\n", __LINE__);
		perror("mprotect");
		stc_exit(1);
	}

	struct stc_stack *pl = (struct stc_stack *)block;
	pl->base = stack_ptr_start;
	pl->mem_rsrv = rsrv;
	pl->mem_committed = PAGESIZE;
	pl->base_offset = 0;
	pl->free_list.ptr = (u64*)stc_os_mem_rsrv(sizeof(u64) * ILT64_CAPACITY);
	pl->free_list.size = (u64*)stc_os_mem_rsrv(sizeof(u64) * ILT64_CAPACITY);
	stc_os_mem_cmt(pl->free_list.ptr, sizeof(u64) * ILT64_CAPACITY);
	stc_os_mem_cmt(pl->free_list.size, sizeof(u64) * ILT64_CAPACITY);
	pl->free_list.used_count = 0;
	return pl;
}

static void *_stc_stack_push(struct stc_stack *s, u64 alignment, u64 total_size)
{
	if (!is_pow2(alignment))
		alignment = next_pow2(alignment);


	u64 start_old = (u64)s->base + s->base_offset;
	u64 start_new = STC_ALIGN_UP(start_old, alignment);
	u64 end_new = start_new + total_size;
	u64 size_new = end_new - (u64)s->base;


	if (s->free_list.used_count != 0) {
		u64 smallest_fit = MAX_UINT64;
		u64 smallest_fit_position = MAX_UINT64;
		for (u64 ml0_idx = 0; ml0_idx < ILT64_ML0; ++ml0_idx) {
			u64 word = s->free_list.ilt.ml0[ml0_idx];
			while (word) {
				u64 bit_idx = (u64)__builtin_ctzll(word);
				u64 real_idx = ml0_idx * 64ULL + bit_idx;
				if (((u64)(s->free_list.ptr[real_idx] & (alignment - 1)) == 0)) {
					if (s->free_list.size[real_idx] < smallest_fit && s->free_list.size[real_idx] >= total_size) {
						smallest_fit = s->free_list.size[real_idx];
						smallest_fit_position = real_idx;
					}
				}
				word &= word - 1;
			}
		}

		if (smallest_fit != MAX_UINT64) {
			ilt64_remove_idx(&s->free_list.ilt, smallest_fit_position);
			s->free_list.used_count--;
			return (void*)s->free_list.ptr[smallest_fit_position];
		}
	}

	/*s->mem_cmt always stays aligned to page boundary*/
	if (size_new > s->mem_committed) {
		u64 delta_commit = STC_ALIGN_UP(size_new - s->mem_committed, PAGESIZE);
		u64 new_total_commit = delta_commit + s->mem_committed;
		assert((s->mem_committed % 4096) == 0);
		if (stc_os_mem_cmt((stc_byte*)s->base + s->mem_committed, delta_commit) == NULL) {
			stc_print("[{u32}]", __LINE__);
			perror("mprotect");
			stc_exit(1);
		}
		assert((s->mem_committed % 4096) == 0);

		s->mem_committed = new_total_commit;
	}

	s->base_offset = size_new;

	return (void*)start_new;
}


static enum stc_err_code stc_stack_free(struct stc_stack *s, void* mem_addrs, u64 size)
{
	u64 next_index = ilt64_gen_idx(&s->free_list.ilt);
	if (unlikely(next_index == ILT64_NIL_IDX)) {
		printf("free_list ILT is full\nAborting\n");
		stc_exit(1);
	}
	s->free_list.ptr[next_index] = (u64)mem_addrs;
	s->free_list.size[next_index] = size;
	s->free_list.used_count++;
	return STC_ERR_OK;
}

static enum stc_err_code stc_stack_pop(struct stc_stack *stack, u64 size)
{
	bool cond = stack->base_offset >= size;
	if (unlikely(!cond)) {
		return STC_ERR_STACK_BASE_OFFSET_GREATER_THAN_SIZE;
	}
	u64 count_checked = SELECT(cond, stack->base_offset - size, stack->base_offset);
	stack->base_offset = count_checked;

	return STC_ERR_OK;
}


static enum stc_err_code stack_begin(struct stc_stack *s)
{
	s->checkpoint_offset = s->base_offset;
	return STC_ERR_OK;
}


static enum stc_err_code stack_end(struct stc_stack *s)
{
	s->base_offset = s->checkpoint_offset;
	return STC_ERR_OK;
}


static stc_threadlocal struct stc_stack *stc_tls_stack;

static void stc_global_stack_init(u64 reserve)
{
	if (stc_tls_stack == NULL) {
		stc_tls_stack = stc_stack_gen(reserve);
	}
}

static void *stc_global_alloc_raw(u64 alignment, u64 size)
{
	if (stc_tls_stack == NULL) {
		stc_global_stack_init(GIGABYTE(1));
	}

	return _stc_stack_push(stc_tls_stack, alignment, size);
}



static enum stc_err_code stc_global_stack_start(void)
{
	if (stc_tls_stack == NULL) {
		return STC_ERR_GLOBAL_ALLOCATOR_UNINITED;
	}
	stc_stack_start(stc_tls_stack);
	return STC_ERR_OK;
}

static enum stc_err_code stc_global_stack_end(void)
{
	if (stc_tls_stack == NULL) {
		return STC_ERR_GLOBAL_ALLOCATOR_UNINITED;
	}
	stc_stack_end(stc_tls_stack);
	return STC_ERR_OK;
}

static enum stc_err_code stc_global_stack_reset(void)
{
	if (stc_tls_stack == NULL) {
		return STC_ERR_GLOBAL_ALLOCATOR_UNINITED;
	}
	stc_tls_stack->base_offset = 0;
	return STC_ERR_OK;
}
