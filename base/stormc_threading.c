#pragma once
#include "../stormc_header.h"

#ifdef _WIN32
	#define stc_thread HANDLE
	#define stc_barrier SYNCHRONIZATION_BARRIER
	#define stc_thread_local __thread
	#define STC_T_FUN(name, param) DWORD WINAPI name(LPVOID param)
	#define STC_T_ATTR void *
	#define STC_T_PARAMS LPVOID
	#define STC_T_RETURN void **
	typedef LPTHREAD_START_ROUTINE stc_thread_proc;

#else
	#define stc_thread_local _Thread_local
	#define STC_T_FUN(name, param) void* name(void *param)
	#define STC_T_ATTR void *
	#define STC_T_PARAMS void *
	#define STC_T_RETURN void **
	typedef void *(*stc_thread_proc)(void *);
	#define stc_thread pthread_t
	#define stc_barrier pthread_barrier_t
#endif


typedef u64 stc_threading_group_t;

#define THREADING_MAX_GROUPS 64
#define THREADING_MAX_THREADS_PER_GROUPS 32
struct stc_threading_init_pl{
	stc_threading_group_t	groups_count;
	u32			threads[THREADING_MAX_GROUPS];
	u32			mem_commit[THREADING_MAX_GROUPS];
	u64			mem_rsrv[THREADING_MAX_GROUPS];
};


struct stc_threading_ctx{
	stc_barrier	barrier;
	stc_thread	handle[THREADING_MAX_THREADS_PER_GROUPS];
	u32		work_per_lane[THREADING_MAX_THREADS_PER_GROUPS];
	u32		ct_workers_on_this_job[THREADING_MAX_THREADS_PER_GROUPS];
	u32		parallel_work_start[THREADING_MAX_THREADS_PER_GROUPS];
	u32		parallel_work_end[THREADING_MAX_THREADS_PER_GROUPS];
	u64		off_bytes_func_ret[THREADING_MAX_THREADS_PER_GROUPS];
	void		*func_ret[THREADING_MAX_THREADS_PER_GROUPS];
	u8*		group_ret; /*atomic return value, currently unused and unimplemented for windows, although works on linux*/
	u64		ct_active_threads;
};
static stc_thread_local u64 __stc_lane_id;
static stc_thread_local u64 __stc_group_id;



static struct stc_threading_init_pl __stc_thread_init = {0};
static struct stc_threading_ctx __stc_thread_ctx[THREADING_MAX_GROUPS];
static u64 __stc_thread_ctx_group_count = 0;

#define LANEID_MASK 0xffffffff
#define THREADING_GROUP_COUNT __stc_thread_ctx_group_count
#define thread(which_thread) if(__stc_lane_id == which_thread)
#define thread_group(which_group) if(__stc_group_id == which_group)
#define stc_init_ctx_group_thread_count(groupid) __stc_thread_init.threads[groupid]
#define stc_get_group_barrier(groupid) &__stc_thread_ctx[groupid].barrier
#define stc_barrier_wait(groupid) stc_threads_barrier_wait(stc_get_group_barrier(groupid))



#define stc_lane_id() __stc_lane_id
#define stc_group_id() __stc_group_id
#define stc_lane_return_value(__group_id, __lane_id) __stc_thread_ctx[__group_id].func_ret[__lane_id]
#define stc_total_lanes_in_group(__group_id) __stc_thread_ctx[__group_id].ct_active_threads

static void stc_threading_prepare_parallel(u64 array_len);
static u64 stc_parallel_start(void);
static u64 stc_sum_lanes_return_value_u64(u64 group_id);
static u64 stc_parallel_end(void);
static void stc_threading_setup_thread_identity(void* param);
static stc_threading_group_t stc_threading_create_new_group(void);
static void stc_threading_thread_data_for_group(stc_threading_group_t group_id, u32 commit, u64 rsrv, u32 number_of_threads);
static void stc_threading_append_ensure_capacity(u64 group_id, u64 thread_id, void *data, u64 size);
static void stc_threading_init_func_ret(stc_threading_group_t group_id, u64 threads_count, u64 rsrv_size, u64 initial_size);
static void stc_threading_system_begin(void);
static void stc_threading_system_end(void);
static void stc_init_thread_groups(stc_threading_group_t groups_count);
static void stc_threads_barrier_init(stc_barrier *restrict barrier, STC_T_ATTR restrict attr, u32 count);
static void stc_threads_barrier_wait(stc_barrier *barrier);
static void stc_threads_barrier_destroy(stc_barrier *barrier);
static void stc_threads_create(
    stc_thread *restrict thread,
    const STC_T_ATTR restrict attr,
    stc_thread_proc procedure,
    void * restrict arg);
static void stc_threads_destroy(stc_thread *thread);
static void stc_threads_join(stc_thread thread, void **thread_return);

#ifndef STC_ENTRY_POINT
	#define STC_ENTRY_POINT stormc_main
#endif

static STC_T_FUN(STC_ENTRY_POINT, param);

#ifdef _WIN32
	#include "windows/stormc_threading.c"
#else
	#include "linux/stormc_threading.c"
#endif



void stc_threading_init_func_ret(stc_threading_group_t group_id, u64 threads_count, u64 reservation_size, u64 initial_size_func_ret_array)
{
	initial_size_func_ret_array = STC_ALIGN_UP(initial_size_func_ret_array*2, PAGESIZE);
	reservation_size = STC_ALIGN_UP(reservation_size + initial_size_func_ret_array, PAGESIZE);

	u64 alloted_per_thread = STC_ALIGN_UP(reservation_size / threads_count, PAGESIZE);
	reservation_size = threads_count * alloted_per_thread;
	u8 *block = (u8*)stc_os_mem_rsrv(reservation_size);

	u64 offset = 0;
	for (u64 idx = 0; idx < threads_count; ++idx) {
		__stc_thread_ctx[group_id].func_ret[idx] = block + offset;
		__stc_thread_ctx[group_id].off_bytes_func_ret[idx] = initial_size_func_ret_array;
		if (stc_os_mem_cmt(__stc_thread_ctx[group_id].func_ret[idx], initial_size_func_ret_array) == NULL) {
			printf("Func Ret Commit failed\n");
			exit(1);
		}
		offset += alloted_per_thread;
	}
	__stc_thread_ctx[group_id].group_ret = block + offset;
	if (stc_os_mem_cmt(__stc_thread_ctx[group_id].group_ret, initial_size_func_ret_array) == NULL) {
		printf("Group ret commit failed\n");
		exit(1);
	}
	__stc_thread_ctx[group_id].ct_active_threads = threads_count;
}



void stc_init_thread_groups(stc_threading_group_t groups_count)
{
	__stc_thread_ctx_group_count = groups_count;
}



void stc_threading_system_begin(void)
{
	stc_init_thread_groups(__stc_thread_init.groups_count);
	for (u64 idx_group = 0; idx_group < __stc_thread_init.groups_count; ++idx_group) {
		u64 threads_count = __stc_thread_init.threads[idx_group];
		u64 thread_mem_rsrv = __stc_thread_init.mem_rsrv[idx_group];
		u64 thread_mem_cmt = __stc_thread_init.mem_commit[idx_group];
		stc_threading_init_func_ret(idx_group, threads_count, thread_mem_rsrv, thread_mem_cmt);
		stc_threads_barrier_init(&__stc_thread_ctx[idx_group].barrier, NULL, threads_count);
		for (u64 thread_idx = 0; thread_idx < threads_count; ++thread_idx) {
			u64 param = (idx_group << 32) | (thread_idx << 0);
			stc_threads_create(&__stc_thread_ctx[idx_group].handle[thread_idx], NULL, STC_ENTRY_POINT, (void*)param);
		}
	}
}


void stc_threading_system_end(void)
{
	for (u64 idx_group = 0; idx_group < __stc_thread_init.groups_count; ++idx_group) {
		u64 threads_count = __stc_thread_init.threads[idx_group];
		for (u64 thread_idx = 0; thread_idx < threads_count; ++thread_idx) {
			stc_threads_join(__stc_thread_ctx[idx_group].handle[thread_idx], NULL);
		}
		stc_threads_barrier_destroy(&__stc_thread_ctx[idx_group].barrier);
	}

}


void stc_threading_append_ensure_capacity(u64 group_id, u64 thread_id, void *data, u64 size)
{
	u64 *current_size = &__stc_thread_ctx[group_id].off_bytes_func_ret[thread_id];
	if (size > *current_size) {
		u64 delta = STC_ALIGN_UP(size - *current_size, PAGESIZE);
		stc_os_mem_cmt(
		    (u8*)__stc_thread_ctx[group_id].func_ret[thread_id] + (*current_size), delta);
		(*current_size) += delta;
	}
	stc_memcpy(__stc_thread_ctx[group_id].func_ret[thread_id], data, size);
}

void stc_threading_setup_thread_identity(void *param)
{
	__stc_lane_id = (u64)(u64)param & LANEID_MASK;
	__stc_group_id = (u64)(u64)param >> 32;
}

stc_threading_group_t stc_threading_create_new_group(void)
{
	return __stc_thread_init.groups_count++;
}

void stc_threading_thread_data_for_group(stc_threading_group_t group_id, u32 commit, u64 rsrv, u32 number_of_threads)
{
	__stc_thread_init.threads[group_id] = number_of_threads;
	__stc_thread_init.mem_rsrv[group_id] = rsrv;
	__stc_thread_init.mem_commit[group_id] = commit;
}



void stc_threading_prepare_parallel(u64 array_len)
{
	u64 values_for_work = array_len / __stc_thread_ctx[stc_group_id()].ct_active_threads;
	u64 rem_work = array_len % __stc_thread_ctx[stc_group_id()].ct_active_threads;
	bool32 should_take_leftover = stc_lane_id() < rem_work;
	u64 leftover_taken_so_far = should_take_leftover ? stc_lane_id() : rem_work;

	int start = (values_for_work * stc_lane_id()) + leftover_taken_so_far;
	int end = start + values_for_work + should_take_leftover;

	__stc_thread_ctx[stc_group_id()].parallel_work_start[stc_lane_id()] = start;
	__stc_thread_ctx[stc_group_id()].parallel_work_end[stc_lane_id()] = end;
}


u64 stc_parallel_start(void)
{

	return __stc_thread_ctx[stc_group_id()].parallel_work_start[stc_lane_id()];
}



u64 stc_parallel_end(void)
{

	return __stc_thread_ctx[stc_group_id()].parallel_work_end[stc_lane_id()];
}


u64 stc_sum_lanes_return_value_u64(u64 group_id)
{
	u64 accum = 0;
	for (u64 i = 0; i < stc_total_lanes_in_group(group_id); ++i) {
		accum += *(u64*)stc_lane_return_value(group_id, i);
	}

	return accum;
}


