#include <linux/openat2.h>
#include <sys/syscall.h>

#ifndef AT_FDCWD
#define AT_FDCWD -100
#endif

#ifndef __NR_storm_openat_len
#define __NR_storm_openat_len 1000
#endif

extern long syscall(long number, ...);

static long storm_openat_len(int dfd, const char *path, size_t path_len,
			     const struct open_how *how, size_t how_size)
{
	return syscall(__NR_storm_openat_len, dfd, path, path_len, how, how_size);
}

thisfile int stc_open(struct stc_string8 path, u64 flags, u64 mode)
{
	if (path.str == NULL) {
		return -1;
	}

	struct open_how how = {
		.flags = flags,
		.mode = mode,
	};

	return (int)storm_openat_len(AT_FDCWD, path.str, path.len, &how, sizeof(how));
}
