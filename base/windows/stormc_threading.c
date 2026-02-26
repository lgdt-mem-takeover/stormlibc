#pragma once

#include "../../stormc_header.h"


// windows/stormc_threading.c
#include "../../stormc_header.h"

void stc_threads_barrier_init(stc_barrier *restrict barrier, STC_T_ATTR restrict attr, u32 count)
{
    InitializeSynchronizationBarrier(barrier, count, -1);
    // attr ignored on Windows, -1 = default spin count
}

void stc_threads_barrier_wait(stc_barrier *barrier)
{
	EnterSynchronizationBarrier(barrier, 0);
    // 0 = flags (typically just 0)
}

void stc_threads_barrier_destroy(stc_barrier *barrier)
{
    DeleteSynchronizationBarrier(barrier);
}

void stc_threads_create(
    stc_thread *restrict thread,
    const STC_T_ATTR restrict attr,
    stc_thread_proc procedure,
    void *restrict arg)
{
    *thread = CreateThread(
        NULL,        // Security attributes (ignored, attr param unused)
        0,           // Default stack size
        procedure,
        arg,
        0,           // Start immediately
        NULL         // Don't need thread ID
    );
}

void stc_threads_destroy(stc_thread *thread)
{
    TerminateThread(*thread, 0);
    CloseHandle(*thread);
}

void stc_threads_join(stc_thread thread, void **thread_return)
{
    WaitForSingleObject(thread, INFINITE);
    // Note: Windows doesn't have direct equivalent to pthread's return value
    // If you need return values, would need GetExitCodeThread
    if (thread_return) {
        DWORD exit_code;
        GetExitCodeThread(thread, &exit_code);
        *thread_return = (void*)(uintptr_t)exit_code;
    }
    CloseHandle(thread);
}
