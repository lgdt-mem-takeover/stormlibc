#pragma once

#ifdef _WIN32

#define STC_PERF_FLAG(id) (0ull)

static void stc_perf_init(void) {}
static void stc_perf_start(void) {}
static void stc_perf_end(void) {}
static void stc_perf_add_all(void) {}
static void stc_perf_close(void) {}
static void stc_perf_add_flags(u64 flags) { (void)flags; }
static void stc_perf_print(u64 flags)
{
	(void)flags;
	stc_println_err("stormc perf counters are unsupported on windows");
}

#else

#include <linux/perf_event.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdint.h>

extern long syscall(long number, ...);

enum stc_perf_type {
	STC_PERF_CPU_CYCLES,
	STC_PERF_INSTRUCTIONS,
	STC_PERF_CACHE_REFS,
	STC_PERF_CACHE_MISSES,
	STC_PERF_BRANCH_INSTRUCTIONS,
	STC_PERF_BRANCH_MISSES,
	STC_PERF_BUS_CYCLES,
	STC_PERF_REF_CPU_CYCLES,
	STC_PERF_CYCLES_FRONTEND,
	STC_PERF_CYCLES_BACKEND,
	STC_PERF_CPU_CLOCK,
	STC_PERF_TASK_CLOCK,
	STC_PERF_PAGE_FAULTS,
	STC_PERF_CONTEXT_SWITCHES,
	STC_PERF_CPU_MIGRATIONS,
	STC_PERF_PAGE_FAULTS_MIN,
	STC_PERF_PAGE_FAULTS_MAJ,
	STC_PERF_COUNT
};

static const char *stc_perf_table_literal[] = {
	"cpu cycles",
	"instructions",
	"cache refs",
	"cache misses",
	"branch instructions",
	"branch misses",
	"bus cycles",
	"ref cpu cycles",
	"cycles frontend",
	"cycles backend",
	"cpu clock",
	"task clock",
	"page faults",
	"context switches",
	"cpu migrations",
	"page faults min",
	"page faults maj",
};

struct stc_perf_counters {
	int group_fd;
	int fds[STC_PERF_COUNT];
	u32 ct_fds;
	u64 values[STC_PERF_COUNT];
};

struct stc_perf_event_desc {
	u32 type;
	u64 config;
};

static const struct stc_perf_event_desc stc_perf_linux_events[STC_PERF_COUNT] = {
	{PERF_TYPE_HARDWARE, PERF_COUNT_HW_CPU_CYCLES},
	{PERF_TYPE_HARDWARE, PERF_COUNT_HW_INSTRUCTIONS},
	{PERF_TYPE_HARDWARE, PERF_COUNT_HW_CACHE_REFERENCES},
	{PERF_TYPE_HARDWARE, PERF_COUNT_HW_CACHE_MISSES},
	{PERF_TYPE_HARDWARE, PERF_COUNT_HW_BRANCH_INSTRUCTIONS},
	{PERF_TYPE_HARDWARE, PERF_COUNT_HW_BRANCH_MISSES},
	{PERF_TYPE_HARDWARE, PERF_COUNT_HW_BUS_CYCLES},
	{PERF_TYPE_HARDWARE, PERF_COUNT_HW_REF_CPU_CYCLES},
	{PERF_TYPE_HARDWARE, PERF_COUNT_HW_STALLED_CYCLES_FRONTEND},
	{PERF_TYPE_HARDWARE, PERF_COUNT_HW_STALLED_CYCLES_BACKEND},
	{PERF_TYPE_SOFTWARE, PERF_COUNT_SW_CPU_CLOCK},
	{PERF_TYPE_SOFTWARE, PERF_COUNT_SW_TASK_CLOCK},
	{PERF_TYPE_SOFTWARE, PERF_COUNT_SW_PAGE_FAULTS},
	{PERF_TYPE_SOFTWARE, PERF_COUNT_SW_CONTEXT_SWITCHES},
	{PERF_TYPE_SOFTWARE, PERF_COUNT_SW_CPU_MIGRATIONS},
	{PERF_TYPE_SOFTWARE, PERF_COUNT_SW_PAGE_FAULTS_MIN},
	{PERF_TYPE_SOFTWARE, PERF_COUNT_SW_PAGE_FAULTS_MAJ},
};


#define STC_PERF_FLAG(id) (1llu << (id))

static int
perf_event_open(struct perf_event_attr *attr, pid_t pid, int cpu, int group_fd, unsigned long flags)
{
	return syscall(SYS_perf_event_open, attr, pid, cpu, group_fd, flags);
}

static struct stc_perf_counters stc_perf = {};


static void stc_perf_init(void)
{
	stc_perf.group_fd = -1;
	for (u64 i = 0; i < STC_PERF_COUNT; ++i) {
		stc_perf.fds[i] = -1;
		stc_perf.values[i] = 0;
	}
}

static void stc_perf_start(void)
{
	if (stc_perf.group_fd == -1) return;

      ioctl(stc_perf.group_fd, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
      ioctl(stc_perf.group_fd, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);

}


static void stc_perf_end(void)
{
	if (stc_perf.group_fd == -1) return;

	ioctl(stc_perf.group_fd, PERF_EVENT_IOC_DISABLE,  PERF_IOC_FLAG_GROUP);
	for (int i = 0; i < STC_PERF_COUNT; ++i) {
		if (stc_perf.fds[i] > 2) {
			read(stc_perf.fds[i], &stc_perf.values[i], sizeof(u64));
		}
	}
}


static void stc_perf_add(enum stc_perf_type id)
{
	if (id >= STC_PERF_COUNT) return;
	if (stc_perf.fds[id] != -1) return;

	struct perf_event_attr pe = {0};

	pe.type = stc_perf_linux_events[id].type;
	pe.size = sizeof(pe);
	pe.config = stc_perf_linux_events[id].config;
	pe.disabled = (stc_perf.group_fd == -1);
	pe.exclude_kernel = 1;
	pe.exclude_hv = 1;

	int fd = perf_event_open(&pe, 0, -1, stc_perf.group_fd, 0);
	if (fd == -1) {
		return;
	}

	if (stc_perf.group_fd == -1) {
		stc_perf.group_fd = fd;
	}

	stc_perf.fds[id] = fd;
	stc_perf.ct_fds++;
}


static void stc_perf_add_all(void)
{
	for (u64 i = 0; i < STC_PERF_COUNT; ++i) {
		stc_perf_add((enum stc_perf_type)i);
	}
}


static void stc_perf_close(void)
{
	for (int i = 0; i < STC_PERF_COUNT; ++i) {
		if (stc_perf.fds[i] != -1) {
			close(stc_perf.fds[i]);
			stc_perf.fds[i] = -1;
		}
	}

	stc_perf.group_fd = -1;
	stc_perf.ct_fds = 0;
}

static void stc_perf_print_counter(const char *label, u64 value)
{
	stc_println("  {cstring}{cstring}{cstring}: {u64}",
		    STC_ANSI_CYAN, label, STC_ANSI_RESET, value);
}


static void stc_perf_print(u64 flags)
{
#define HAS(id) (flags & STC_PERF_FLAG(id))

	stc_println("{cstring}stormc perf report{cstring}", STC_ANSI_BOLD, STC_ANSI_RESET);
	stc_println("{cstring}-----------------{cstring}", STC_ANSI_DIM, STC_ANSI_RESET);

	if (HAS(STC_PERF_CPU_CYCLES) || HAS(STC_PERF_REF_CPU_CYCLES) ||
	    HAS(STC_PERF_BUS_CYCLES) || HAS(STC_PERF_INSTRUCTIONS) ||
	    HAS(STC_PERF_CYCLES_FRONTEND) || HAS(STC_PERF_CYCLES_BACKEND)) {
		stc_println("");
		stc_println("{cstring}core{cstring}", STC_ANSI_BOLD, STC_ANSI_RESET);
	}

	if (HAS(STC_PERF_CPU_CYCLES))
		stc_perf_print_counter("cpu cycles", stc_perf.values[STC_PERF_CPU_CYCLES]);

	if (HAS(STC_PERF_REF_CPU_CYCLES))
		stc_perf_print_counter("ref cpu cycles", stc_perf.values[STC_PERF_REF_CPU_CYCLES]);

	if (HAS(STC_PERF_BUS_CYCLES))
		stc_perf_print_counter("bus cycles", stc_perf.values[STC_PERF_BUS_CYCLES]);

	if (HAS(STC_PERF_INSTRUCTIONS))
		stc_perf_print_counter("instructions", stc_perf.values[STC_PERF_INSTRUCTIONS]);

	if (HAS(STC_PERF_CYCLES_FRONTEND))
		stc_perf_print_counter("stalled cycles frontend", stc_perf.values[STC_PERF_CYCLES_FRONTEND]);

	if (HAS(STC_PERF_CYCLES_BACKEND))
		stc_perf_print_counter("stalled cycles backend", stc_perf.values[STC_PERF_CYCLES_BACKEND]);

	if (HAS(STC_PERF_CPU_CYCLES) && HAS(STC_PERF_INSTRUCTIONS)) {
		u64 cycles = stc_perf.values[STC_PERF_CPU_CYCLES];
		u64 instr = stc_perf.values[STC_PERF_INSTRUCTIONS];

		if (cycles != 0) {
			f64 ipc = (f64)instr / (f64)cycles;
			stc_println("  {cstring}IPC{cstring}: {cstring}{f64}{cstring}",
				    STC_ANSI_CYAN, STC_ANSI_RESET,
				    STC_ANSI_GREEN, ipc, STC_ANSI_RESET);
		}
	}

	if (HAS(STC_PERF_CPU_CYCLES) && HAS(STC_PERF_CYCLES_FRONTEND)) {
		u64 cycles = stc_perf.values[STC_PERF_CPU_CYCLES];
		u64 stalled = stc_perf.values[STC_PERF_CYCLES_FRONTEND];

		if (cycles != 0) {
			f64 pct = ((f64)stalled / (f64)cycles) * 100.0;
			stc_println("  {cstring}frontend stall rate{cstring}: {cstring}{f64}%{cstring}",
				    STC_ANSI_CYAN, STC_ANSI_RESET,
				    (pct > 30.0) ? STC_ANSI_RED : (pct > 10.0) ? STC_ANSI_YELLOW : STC_ANSI_GREEN,
				    pct, STC_ANSI_RESET);
		}
	}

	if (HAS(STC_PERF_CPU_CYCLES) && HAS(STC_PERF_CYCLES_BACKEND)) {
		u64 cycles = stc_perf.values[STC_PERF_CPU_CYCLES];
		u64 stalled = stc_perf.values[STC_PERF_CYCLES_BACKEND];

		if (cycles != 0) {
			f64 pct = ((f64)stalled / (f64)cycles) * 100.0;
			stc_println("  {cstring}backend stall rate{cstring}: {cstring}{f64}%{cstring}",
				    STC_ANSI_CYAN, STC_ANSI_RESET,
				    (pct > 30.0) ? STC_ANSI_RED : (pct > 10.0) ? STC_ANSI_YELLOW : STC_ANSI_GREEN,
				    pct, STC_ANSI_RESET);
		}
	}

	if (HAS(STC_PERF_CACHE_REFS) || HAS(STC_PERF_CACHE_MISSES)) {
		stc_println("");
		stc_println("{cstring}cache{cstring}", STC_ANSI_BOLD, STC_ANSI_RESET);
	}

	if (HAS(STC_PERF_CACHE_REFS))
		stc_perf_print_counter("cache refs", stc_perf.values[STC_PERF_CACHE_REFS]);

	if (HAS(STC_PERF_CACHE_MISSES))
		stc_perf_print_counter("cache misses", stc_perf.values[STC_PERF_CACHE_MISSES]);

	if (HAS(STC_PERF_CACHE_REFS) && HAS(STC_PERF_CACHE_MISSES)) {
		u64 refs = stc_perf.values[STC_PERF_CACHE_REFS];
		u64 misses = stc_perf.values[STC_PERF_CACHE_MISSES];

		if (refs != 0) {
			f64 pct = ((f64)misses / (f64)refs) * 100.0;
			stc_println("  {cstring}cache miss rate{cstring}: {cstring}{f64}%{cstring}",
				    STC_ANSI_CYAN, STC_ANSI_RESET,
				    (pct > 20.0) ? STC_ANSI_RED : (pct > 5.0) ? STC_ANSI_YELLOW : STC_ANSI_GREEN,
				    pct, STC_ANSI_RESET);
		}
	}

	if (HAS(STC_PERF_BRANCH_INSTRUCTIONS) || HAS(STC_PERF_BRANCH_MISSES)) {
		stc_println("");
		stc_println("{cstring}branches{cstring}", STC_ANSI_BOLD, STC_ANSI_RESET);
	}

	if (HAS(STC_PERF_BRANCH_INSTRUCTIONS))
		stc_perf_print_counter("branch instructions", stc_perf.values[STC_PERF_BRANCH_INSTRUCTIONS]);

	if (HAS(STC_PERF_BRANCH_MISSES))
		stc_perf_print_counter("branch misses", stc_perf.values[STC_PERF_BRANCH_MISSES]);

	if (HAS(STC_PERF_BRANCH_INSTRUCTIONS) && HAS(STC_PERF_BRANCH_MISSES)) {
		u64 refs = stc_perf.values[STC_PERF_BRANCH_INSTRUCTIONS];
		u64 misses = stc_perf.values[STC_PERF_BRANCH_MISSES];

		if (refs != 0) {
			f64 pct = ((f64)misses / (f64)refs) * 100.0;
			stc_println("  {cstring}branch miss rate{cstring}: {cstring}{f64}%{cstring}",
				    STC_ANSI_CYAN, STC_ANSI_RESET,
				    (pct > 5.0) ? STC_ANSI_RED : (pct > 1.0) ? STC_ANSI_YELLOW : STC_ANSI_GREEN,
				    pct, STC_ANSI_RESET);
		}
	}

	if (HAS(STC_PERF_CPU_CLOCK) || HAS(STC_PERF_TASK_CLOCK)) {
		stc_println("");
		stc_println("{cstring}time{cstring}", STC_ANSI_BOLD, STC_ANSI_RESET);
	}

	if (HAS(STC_PERF_CPU_CLOCK)) {
		u64 ns = stc_perf.values[STC_PERF_CPU_CLOCK];
		stc_perf_print_counter("cpu clock ns", ns);
		stc_println("  {cstring}cpu clock ms{cstring}: {f64}",
			    STC_ANSI_CYAN, STC_ANSI_RESET, (f64)ns / 1000000.0);
	}

	if (HAS(STC_PERF_TASK_CLOCK)) {
		u64 ns = stc_perf.values[STC_PERF_TASK_CLOCK];
		stc_perf_print_counter("task clock ns", ns);
		stc_println("  {cstring}task clock ms{cstring}: {f64}",
			    STC_ANSI_CYAN, STC_ANSI_RESET, (f64)ns / 1000000.0);
	}

	if (HAS(STC_PERF_PAGE_FAULTS) || HAS(STC_PERF_PAGE_FAULTS_MIN) ||
	    HAS(STC_PERF_PAGE_FAULTS_MAJ) || HAS(STC_PERF_CONTEXT_SWITCHES) ||
	    HAS(STC_PERF_CPU_MIGRATIONS)) {
		stc_println("");
		stc_println("{cstring}os{cstring}", STC_ANSI_BOLD, STC_ANSI_RESET);
	}

	if (HAS(STC_PERF_PAGE_FAULTS))
		stc_perf_print_counter("page faults", stc_perf.values[STC_PERF_PAGE_FAULTS]);

	if (HAS(STC_PERF_PAGE_FAULTS_MIN))
		stc_perf_print_counter("minor page faults", stc_perf.values[STC_PERF_PAGE_FAULTS_MIN]);

	if (HAS(STC_PERF_PAGE_FAULTS_MAJ))
		stc_perf_print_counter("major page faults", stc_perf.values[STC_PERF_PAGE_FAULTS_MAJ]);

	if (HAS(STC_PERF_CONTEXT_SWITCHES))
		stc_perf_print_counter("context switches", stc_perf.values[STC_PERF_CONTEXT_SWITCHES]);

	if (HAS(STC_PERF_CPU_MIGRATIONS))
		stc_perf_print_counter("cpu migrations", stc_perf.values[STC_PERF_CPU_MIGRATIONS]);

#undef HAS
}


static void stc_perf_add_flags(u64 flags)
{
	for (u64 i = 0; i < STC_PERF_COUNT; ++i) {
		if (flags & STC_PERF_FLAG(i)) {
			stc_perf_add((enum stc_perf_type)i);
		}
	}
}

#endif



#ifdef _WIN32

#include <intrin.h>
#include <windows.h>

static u64 get_os_timer_freq(void)
{
	LARGE_INTEGER Freq;
	QueryPerformanceFrequency(&Freq);
	return Freq.QuadPart;
}

static u64 read_os_timer(void)
{
	LARGE_INTEGER Value;
	QueryPerformanceCounter(&Value);
	return Value.QuadPart;
}

#else

#include <x86intrin.h>
#include <time.h>


static u64 get_os_timer_freq(void)
{
	return 1000000000llu;
}

static u64 read_os_timer(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);

	return get_os_timer_freq() * (u64)ts.tv_sec + (u64)ts.tv_nsec;
}

#endif

static inline u64 read_cpu_timer(void)
{
	return __rdtsc();
}


struct stc_perf_wclock {
	u64	os_freq;
	u64	os_start;
	u64	cpu_start;
	u64	cpu_end;
	u64	os_end;
};

static void stc_perf_wclock_start(struct stc_perf_wclock *w)
{
	w->os_freq = get_os_timer_freq();
	u64 wait = read_os_timer();
	while ((read_os_timer() - wait) < w->os_freq);


	w->os_start = read_os_timer();
	w->cpu_start = read_cpu_timer();
}


static void stc_perf_wclock_end(struct stc_perf_wclock *w)
{
	w->cpu_end = read_cpu_timer();
	w->os_end = read_os_timer();
}

static f64 stc_perf_wclock_report_ms(struct stc_perf_wclock *w)
{
	u64 os_elapsed = w->os_end - w->os_start;
	return ((f64)os_elapsed / (f64)w->os_freq) * 1000.f;
}

static u64 stc_perf_wclock_report_cpu_cycles(struct stc_perf_wclock *w)
{
	return w->cpu_end - w->cpu_start;
}
