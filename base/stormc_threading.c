#pragma once
#include "../stormc_header.h"


enum stc_threading_phase_cmd {
	STC_PHASE_CONTINUE,
	STC_PHASE_EXIT,
};


#ifdef _WIN32
	#define stc_thread HANDLE
	#define stc_barrier SYNCHRONIZATION_BARRIER
	#define STC_T_FUN(name, param) DWORD WINAPI name(LPVOID param)
	#define STC_T_ATTR void *
	#define STC_T_PARAMS LPVOID
	#define STC_T_RETURN void **
	typedef LPTHREAD_START_ROUTINE stc_thread_proc;

#else
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
	u64			mem_commit[THREADING_MAX_GROUPS];
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
	u64		accumulator[THREADING_MAX_THREADS_PER_GROUPS];
	struct {
		enum stc_threading_phase_cmd		request[THREADING_MAX_THREADS_PER_GROUPS];
	}phase;
	u64		ct_active_threads;
};
static stc_threadlocal u64 __stc_lane_id;
static stc_threadlocal u64 __stc_group_id;


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



static struct stc_threading_init_pl __stc_thread_init = {0};
static struct stc_threading_ctx __stc_thread_ctx[THREADING_MAX_GROUPS];
static u64 __stc_thread_ctx_group_count = 0;



static void stc_threading_prepare_parallel(u64 array_len);
static u64 stc_parallel_start(void);
static u64 stc_sum_lanes_return_value_u64(u64 group_id);
static u64 stc_parallel_end(void);
static void stc_threading_setup_thread_identity(void* param);
static stc_threading_group_t stc_threading_create_new_group(void);
static void stc_threading_thread_data_for_group(stc_threading_group_t group_id, u64 commit, u64 rsrv, u32 number_of_threads);
static void stc_threading_append_ensure_capacity(u64 group_id, u64 thread_id, void *data, u64 size);
static void stc_threading_init_func_ret(stc_threading_group_t group_id, u64 threads_count, u64 rsrv_size, u64 initial_size);
static void stc_threading_begin(void);
static void stc_threading_end(void);
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


static void stc_threading_phase_clear_request(void)
{
	struct stc_threading_ctx *ctx = &__stc_thread_ctx[stc_group_id()];

	ctx->phase.request[stc_lane_id()] = STC_PHASE_CONTINUE;
	stc_barrier_wait(stc_group_id());
}

static bool32 stc_threading_phase_any_exit(void)
{
	struct stc_threading_ctx *ctx = &__stc_thread_ctx[stc_group_id()];
	for (u64 i = 0; i < ctx->ct_active_threads; ++i) {
		if (ctx->phase.request[i] == STC_PHASE_EXIT) {
			return true;
		}
	}
	return false;
}

static void stc_threading_phase_request(enum stc_threading_phase_cmd phase)
{
	__stc_thread_ctx[stc_group_id()].phase.request[stc_lane_id()] = phase;
}


static void stc_threading_init_func_ret(stc_threading_group_t group_id, u64 threads_count, u64 reservation_size, u64 initial_size_func_ret_array)
{

	if (!is_pow2(initial_size_func_ret_array)) {
		initial_size_func_ret_array = next_pow2(initial_size_func_ret_array);
		fprintf(stderr, "[FUNC RET ARRAY] Thread init size has to be a power of 2\nNew size assigned: %lu\n", initial_size_func_ret_array);
		// exit(1);
	}

	if (!is_pow2(reservation_size)) {
		reservation_size = next_pow2(reservation_size);
		fprintf(stderr, "[RESERVATION] Thread init size has to be a power of 2\nNew size assigned: %lu\n", initial_size_func_ret_array);
		// exit(1);
	}

	u64 per_thread_reservation = STC_ALIGN_UP(reservation_size / threads_count, PAGESIZE);
	u8 *block = (u8*)stc_os_mem_rsrv(per_thread_reservation * threads_count);

	for (u64 idx = 0; idx < threads_count; ++idx) {
		void *base = block + (idx * per_thread_reservation);
		__stc_thread_ctx[group_id].func_ret[idx] = base;
		__stc_thread_ctx[group_id].off_bytes_func_ret[idx] = initial_size_func_ret_array;
		if (stc_os_mem_cmt(__stc_thread_ctx[group_id].func_ret[idx], initial_size_func_ret_array) == NULL) {
			printf("Func Ret Commit failed\n");
			exit(1);
		}
	}

	__stc_thread_ctx[group_id].ct_active_threads = threads_count;
}



static void stc_init_thread_groups(stc_threading_group_t groups_count)
{
	__stc_thread_ctx_group_count = groups_count;
}



static void stc_threading_begin(void)
{
	stc_init_thread_groups(__stc_thread_init.groups_count);
	for (u64 idx_group = 0; idx_group < __stc_thread_init.groups_count; ++idx_group) {
		u64 threads_count = __stc_thread_init.threads[idx_group];
		u64 thread_mem_rsrv = __stc_thread_init.mem_rsrv[idx_group];
		u64 thread_mem_cmt = __stc_thread_init.mem_commit[idx_group];
		stc_threading_init_func_ret(idx_group, threads_count, thread_mem_rsrv, thread_mem_cmt);
		stc_threads_barrier_init(&__stc_thread_ctx[idx_group].barrier, NULL, threads_count);
		for (u64 thread_idx = 1; thread_idx < threads_count; ++thread_idx) {
			u64 param = (idx_group << 32) | (thread_idx << 0);
			stc_threads_create(&__stc_thread_ctx[idx_group].handle[thread_idx], NULL, STC_ENTRY_POINT, (void*)param);
		}
	}
	u64 param = (0llu << 32) | 0;
	STC_ENTRY_POINT((void*)param);
}


static void stc_threading_end(void)
{
	for (u64 idx_group = 0; idx_group < __stc_thread_init.groups_count; ++idx_group) {
		u64 threads_count = __stc_thread_init.threads[idx_group];
		for (u64 thread_idx = 1; thread_idx < threads_count; ++thread_idx) {
			stc_threads_join(__stc_thread_ctx[idx_group].handle[thread_idx], NULL);
		}
		stc_threads_barrier_destroy(&__stc_thread_ctx[idx_group].barrier);
	}

}


static void stc_threading_append_ensure_capacity(u64 group_id, u64 thread_id, void *data, u64 size)
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

static void stc_threading_setup_thread_identity(void *param)
{
	__stc_lane_id = (u64)(u64)param & LANEID_MASK;
	__stc_group_id = (u64)(u64)param >> 32;
}

static stc_threading_group_t stc_threading_create_new_group(void)
{
	return __stc_thread_init.groups_count++;
}

static void stc_threading_thread_data_for_group(stc_threading_group_t group_id, u64 commit, u64 rsrv, u32 number_of_threads)
{
	if (!is_pow2(commit))
		commit = next_pow2(commit);

	if (!is_pow2(rsrv))
		rsrv = next_pow2(rsrv);

	__stc_thread_init.threads[group_id] = number_of_threads;
	__stc_thread_init.mem_rsrv[group_id] = rsrv;
	__stc_thread_init.mem_commit[group_id] = commit;
}



static void stc_threading_prepare_parallel(u64 array_len)
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


static u64 stc_parallel_start(void)
{

	return __stc_thread_ctx[stc_group_id()].parallel_work_start[stc_lane_id()];
}



static u64 stc_parallel_end(void)
{

	return __stc_thread_ctx[stc_group_id()].parallel_work_end[stc_lane_id()];
}


static u64 stc_sum_lanes_return_value_u64(u64 group_id)
{
	u64 accum = 0;
	for (u64 i = 0; i < stc_total_lanes_in_group(group_id); ++i) {
		accum += *(u64*)stc_lane_return_value(group_id, i);
	}

	return accum;
}

static void stc_threading_write_return(u64 group_id, u64 lane_id, void *v, u64 size)
{
	stc_memcpy(__stc_thread_ctx[group_id].func_ret[lane_id], v, size);
}

static void *stc_threading_read_return(u64 group_id, u64 lane_id)
{
	return stc_lane_return_value(group_id, lane_id);
}


static void stc_threading_lane_accumulator(u64 group_id, u64 lane_id)
{
	__stc_thread_ctx[group_id].accumulator[lane_id]++;
}

static u64 stc_threading_sum_group_accumulator(u64 group_index)
{
	u64 accum = 0;

	for (u64 thread_index = 0; thread_index < __stc_thread_ctx->ct_active_threads; ++thread_index) {
		accum += __stc_thread_ctx[group_index].accumulator[thread_index];
	}

	return accum;
}

static void stc_threading_group_reset_accumulator(u64 group_index)
{
	for (u64 thread_index = 0; thread_index < __stc_thread_ctx->ct_active_threads; ++thread_index) {
		__stc_thread_ctx[group_index].accumulator[thread_index] = 0;
	}

}

static void stc_threading_lane_reset_accumulator(u64 group_index, u64 lane_idx)
{
	__stc_thread_ctx[group_index].accumulator[lane_idx] = 0;

}
