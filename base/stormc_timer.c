#ifdef _WIN32
#include <intrin.h>
#include <windows.h>

u64 stc_os_timer_freq(void)
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	return freq.QuadPart;
}

u64 stc_os_timer_read(void)
{
	LARGE_INTEGER value;
	QueryPerformanceCounter(&value);
	return value.QuadPart;
}

#else
#include <x86intrin.h>
#include <time.h>

u64 stc_os_timer_freq(void)
{
	return 1000000000llu;
}

u64 stc_os_timer_read(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return 1000000000llu * (u64)ts.tv_sec + (u64)ts.tv_nsec;
}
#endif

u64 stc_cpu_timer_read(void)
{
	return __rdtsc();
}


