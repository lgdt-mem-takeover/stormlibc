#include "stormc_base.h"


thisfile i64		 stc_io_read(struct stc_file *f, u8 *buffer, u64 size);
thisfile i64		 stc_io_write(struct stc_file *f, u8 *buffer, u64 size);
thisfile struct stc_file stc_io_open_r(const char *path);
thisfile struct stc_file stc_io_open_rw(const char *path);
thisfile struct stc_file stc_io_open_w(const char *path);
thisfile struct stc_file stc_io_open_w_new(const char *path);
thisfile struct stc_file stc_io_open_w_append(const char *path);
thisfile u64		 stc_io_get_file_size(const char *path);


#ifdef _WIN32
i64 stc_read(struct stc_file *f, void *ptr, u64 size)
{
	DWORD bytes_read = 0;
	DWORD to_read = (size > 0xffffffffu) ? 0xffffffffu : (DWORD)size;

	if (!ReadFile(f->fd.fd, ptr, to_read, &bytes_read, NULL)) {
		return -1;
	}

	return (i64)bytes_read;
}

i64 stc_write(struct stc_file *f, void *ptr, u64 size)
{
	DWORD bytes_written = 0;
	DWORD to_write = (size > 0xffffffffu) ? 0xffffffffu : (DWORD)size;

	if (!WriteFile(f->fd.fd, ptr, to_write, &bytes_written, NULL)) {
		return -1;
	}

	return (i64)bytes_written;
}

u64 stc_io_get_file_size(const char *path)
{
	WIN32_FILE_ATTRIBUTE_DATA data = {0};

	if (!GetFileAttributesExA(path, GetFileExInfoStandard, &data)) {
		return 0;
	}

	LARGE_INTEGER size = {0};
	size.LowPart = data.nFileSizeLow;
	size.HighPart = data.nFileSizeHigh;

	return (u64)size.QuadPart;
}

struct stc_file stc_io_open_r(const char *path)
{
	struct stc_file pl = {0};

	pl.fd.fd = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL,
			       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	pl.file_size = stc_io_get_file_size(path);

	return pl;
}

struct stc_file stc_io_open_rw(const char *path)
{
	struct stc_file pl = {0};

	pl.fd.fd = CreateFileA(path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL,
			       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	pl.file_size = stc_io_get_file_size(path);

	return pl;
}

struct stc_file stc_io_open_w(const char *path)
{
	struct stc_file pl = {0};

	pl.fd.fd = CreateFileA(path, GENERIC_WRITE, 0, NULL,
			       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	pl.file_size = stc_io_get_file_size(path);

	return pl;
}

struct stc_file stc_io_open_w_new(const char *path)
{
	struct stc_file pl = {0};

	pl.fd.fd = CreateFileA(path, GENERIC_WRITE, 0, NULL,
			       CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	pl.file_size = 0;

	return pl;
}

struct stc_file stc_io_open_w_append(const char *path)
{
	struct stc_file pl = {0};

	pl.fd.fd = CreateFileA(path, FILE_APPEND_DATA, FILE_SHARE_READ, NULL,
			       OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	pl.file_size = stc_io_get_file_size(path);

	return pl;
}

int stc_close(struct stc_file *f)
{
	return CloseHandle(f->fd.fd) ? 0 : -1;
}

#else
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
i64 stc_write(struct stc_file *f, void *ptr, u64 len)
{
	return write(f->fd.fd, ptr, len);
}

i64 stc_read(struct stc_file *f, void *ptr, u64 len)
{
	return read(f->fd.fd, ptr, len);
}


u64 stc_io_get_file_size(const char *path)
{
	struct stat st = {};
	stat(path, &st);
	return st.st_size;
}

struct stc_file stc_io_open_r(const char *path)
{
	struct stc_file pl = {};
	pl.fd.fd = open(path, O_RDONLY);
	pl.file_size = stc_io_get_file_size(path);
	return pl;
}

struct stc_file stc_io_open_rw(const char *path)
{
	struct stc_file pl = {};
	pl.fd.fd = open(path, O_RDWR, 0644);
	pl.file_size = stc_io_get_file_size(path);
	return pl;
}


int stc_close(struct stc_file *f)
{
	return close(f->fd.fd);
}
#endif



i64 stc_io_read(struct stc_file *f, u8 *buffer, u64 size)
{
	return stc_read(f, buffer, size);
}


i64 stc_io_write(struct stc_file *f, u8 *buffer, u64 size)
{
	return stc_write(f, buffer, size);
}




int stc_io_close(struct stc_file *f)
{
	return stc_close(f);
}
