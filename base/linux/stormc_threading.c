#pragma once

#include "../../stormc_header.h"

static void stc_threads_barrier_init(stc_barrier *restrict barrier, STC_T_ATTR restrict attr, u32 count)
{
    pthread_barrier_init(barrier, (pthread_barrierattr_t*)attr, count);
}

static void stc_threads_barrier_wait(stc_barrier *barrier)
{
    pthread_barrier_wait(barrier);
}

static void stc_threads_barrier_destroy(stc_barrier *barrier)
{
    pthread_barrier_destroy(barrier);
}

static void stc_threads_create(
    stc_thread *restrict thread,
    const STC_T_ATTR restrict attr,
    stc_thread_proc procedure,
    void *restrict arg)
{
    pthread_create(thread, (pthread_attr_t*)attr, procedure, arg);
}

static void stc_threads_destroy(stc_thread *thread)
{
    pthread_cancel(*thread);
}

static void stc_threads_join(stc_thread thread, void **thread_return)
{
    pthread_join(thread, thread_return);
}
