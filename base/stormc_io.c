#pragma once
#ifndef _GNU_SOURCE
	#define _GNU_SOURCE
#endif
#include "stormc_error_table.h"


static stc_threadlocal struct stc_strbldr _strbldr_print = {};


#ifdef _WIN32
thisfile inline i64 stc_read(struct stc_file *f, void *ptr, u64 size)
{
	DWORD bytes_read = 0;
	DWORD to_read = (size > 0xffffffffu) ? 0xffffffffu : (DWORD)size;

	if (!ReadFile(f->fd.fd, ptr, to_read, &bytes_read, NULL)) {
		return -1;
	}

	return (i64)bytes_read;
}

thisfile inline i64 stc_write(struct stc_file *f, void *ptr, u64 size)
{
	DWORD bytes_written = 0;
	DWORD to_write = (size > 0xffffffffu) ? 0xffffffffu : (DWORD)size;

	if (!WriteFile(f->fd.fd, ptr, to_write, &bytes_written, NULL)) {
		return -1;
	}

	return (i64)bytes_written;
}

thisfile inline int stc_close(struct stc_file *f)
{
	return CloseHandle(f->fd.fd) ? 0 : -1;
}

thisfile enum stc_err_code stc_io_get_file_size(struct stc_file *f, u64 *size_out)
{
	if (f == NULL || size_out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	LARGE_INTEGER size = {0};

	if (!GetFileSizeEx(f->fd.fd, &size)) {
		*size_out = 0;
		return STC_ERR_FILE_STAT_FAILED;
	}

	*size_out = (u64)size.QuadPart;
	return STC_ERR_OK;
}

thisfile HANDLE stc_open_len(struct stc_string8 path, DWORD desired_access, DWORD share_mode, DWORD creation_disposition, DWORD flags)
{
	if (path.str == NULL) {
		return INVALID_HANDLE_VALUE;
	}

	char *path_z = stc_alloc(path.len + 1);
	if (path_z == NULL) {
		return INVALID_HANDLE_VALUE;
	}

	stc_memcpy(path_z, path.str, path.len);
	path_z[path.len] = 0;

	HANDLE result = CreateFileA(path_z, desired_access, share_mode, NULL,
				    creation_disposition, flags, NULL);
	stc_free(path_z, path.len + 1);
	return result;
}

thisfile enum stc_err_code stc_io_open_r(struct stc_string8 path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd = stc_open_len(path, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL);
	if (out->fd == INVALID_HANDLE_VALUE) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	enum stc_err_code err = stc_io_get_file_size(out, &out->file_size);
	if (err != STC_ERR_OK) {
		stc_close(out);
		*out = STC_STRUCT_ZERO(stc_file);
	}
	return err;
}

thisfile enum stc_err_code stc_io_open_rw(struct stc_string8 path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd = stc_open_len(path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL);
	if (out->fd == INVALID_HANDLE_VALUE) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	enum stc_err_code err = stc_io_get_file_size(out, &out->file_size);
	if (err != STC_ERR_OK) {
		stc_close(out);
		*out = STC_STRUCT_ZERO(stc_file);
	}
	return err;
}

thisfile enum stc_err_code stc_io_open_w(struct stc_string8 path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd = stc_open_len(path, GENERIC_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL);
	if (out->fd == INVALID_HANDLE_VALUE) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	enum stc_err_code err = stc_io_get_file_size(out, &out->file_size);
	if (err != STC_ERR_OK) {
		stc_close(out);
		*out = STC_STRUCT_ZERO(stc_file);
	}
	return err;
}

thisfile enum stc_err_code stc_io_open_w_new(struct stc_string8 path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd = stc_open_len(path, GENERIC_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL);
	if (out->fd == INVALID_HANDLE_VALUE) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	out->file_size = 0;
	return STC_ERR_OK;
}

thisfile enum stc_err_code stc_io_open_w_append(struct stc_string8 path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd = stc_open_len(path, FILE_APPEND_DATA, FILE_SHARE_READ, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL);
	if (out->fd == INVALID_HANDLE_VALUE) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	enum stc_err_code err = stc_io_get_file_size(out, &out->file_size);
	if (err != STC_ERR_OK) {
		stc_close(out);
		*out = STC_STRUCT_ZERO(stc_file);
	}
	return err;
}

#else
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <linux/openat2.h>
#include <sys/syscall.h>

#ifndef AT_FDCWD
#define AT_FDCWD -100
#endif

#ifndef O_CLOEXEC
#define O_CLOEXEC 02000000
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

thisfile inline i64 stc_write(struct stc_file *f, void *ptr, u64 len)
{
	return write(f->fd, ptr, len);
}

thisfile inline i64 stc_read(struct stc_file *f, void *ptr, u64 len)
{
	return read(f->fd, ptr, len);
}

thisfile inline int stc_close(struct stc_file *f)
{
	return close(f->fd);
}

thisfile inline enum stc_err_code stc_io_get_file_size(struct stc_file *fin, u64 *size_out)
{
	if (fin == NULL || size_out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	struct stat st = {};
	if (fstat(fin->fd, &st) != 0) {
		*size_out = 0;
		return STC_ERR_FILE_STAT_FAILED;
	}

	if (st.st_size < 0) {
		*size_out = 0;
		return STC_ERR_FILE_STAT_FAILED;
	}

	*size_out = st.st_size;
	return STC_ERR_OK;
}

thisfile int stc_open_len(struct stc_string8 path, u64 flags, u64 mode)
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

thisfile enum stc_err_code stc_io_open_r(struct stc_string8 path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd = stc_open_len(path, O_RDONLY | O_CLOEXEC, 0);
	if (out->fd < 0) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	enum stc_err_code err = stc_io_get_file_size(out, &out->file_size);
	if (err != STC_ERR_OK) {
		stc_close(out);
		*out = STC_STRUCT_ZERO(stc_file);
	}
	return err;
}

thisfile enum stc_err_code stc_io_open_rw(struct stc_string8 path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd = stc_open_len(path, O_RDWR | O_CLOEXEC, 0);
	if (out->fd < 0) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	enum stc_err_code err = stc_io_get_file_size(out, &out->file_size);
	if (err != STC_ERR_OK) {
		stc_close(out);
		*out = STC_STRUCT_ZERO(stc_file);
	}
	return err;
}

thisfile enum stc_err_code stc_io_open_w(struct stc_string8 path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd = stc_open_len(path, O_WRONLY | O_CLOEXEC, 0);
	if (out->fd < 0) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	enum stc_err_code err = stc_io_get_file_size(out, &out->file_size);
	if (err != STC_ERR_OK) {
		stc_close(out);
		*out = STC_STRUCT_ZERO(stc_file);
	}
	return err;
}

thisfile enum stc_err_code stc_io_open_w_new(struct stc_string8 path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd = stc_open_len(path, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
	if (out->fd < 0) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	out->file_size = 0;
	return STC_ERR_OK;
}

thisfile enum stc_err_code stc_io_open_w_append(struct stc_string8 path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd = stc_open_len(path, O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC, 0644);
	if (out->fd < 0) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	enum stc_err_code err = stc_io_get_file_size(out, &out->file_size);
	if (err != STC_ERR_OK) {
		stc_close(out);
		*out = STC_STRUCT_ZERO(stc_file);
	}
	return err;
}

#endif



thisfile inline enum stc_err_code stc_io_read(
    struct stc_file *f, stc_byte *buffer, u64 size, u64 *size_out)
{
	if (size_out) {
		*size_out = 0;
	}
	if (f == NULL || buffer == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	i64 ret = stc_read(f, buffer, size);
	if (ret < 0) {
		return STC_ERR_FILE_READ_FAILED;
	}

	if (size_out) {
		*size_out = (u64)ret;
	}
	return STC_ERR_OK;
}


thisfile inline enum stc_err_code stc_io_write(struct stc_file *f, stc_byte *buffer, u64 size, u64 *size_out)
{
	if (size_out) {
		*size_out = 0;
	}
	if (f == NULL || buffer == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	i64 ret = stc_write(f, buffer, size);
	if (ret < 0) {
		return STC_ERR_FILE_WRITE_FAILED;
	}

	if (size_out) {
		*size_out = (u64)ret;
	}
	return STC_ERR_OK;
}
thisfile inline enum stc_err_code stc_io_close(struct stc_file *f)
{
	if (f == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	if (stc_close(f) != 0) {
		return STC_ERR_FILE_CLOSE_FAILED;
	}

	return STC_ERR_OK;
}


thisfile inline enum stc_err_code stc_io_file_to_string8(struct stc_file *f, struct stc_string8 *out, u64 *size_out)
{
	if (size_out) {
		*size_out = 0;
	}
	if (f == NULL || out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}
	if (out->str == NULL) {
		return STC_ERR_FILE_COPY_TO_STRING8_FAILED;
	}

	u64 bytes_read = 0;
	enum stc_err_code err = stc_io_read(f, out->str, f->file_size, &bytes_read);
	if (err != STC_ERR_OK) {
		out->len = 0;
		return err;
	}

	out->len = bytes_read;
	if (size_out) {
		*size_out = bytes_read;
	}
	return STC_ERR_OK;
}

thisfile void stc_print_init(void)
{
	_strbldr_print = stc_strbldr_emit(MEGABYTE(64), PAGESIZE);
}

thisfile void stc_print_os_stderr(void)
{
#ifdef _WIN32
	HANDLE stc_stderr = GetStdHandle(STD_ERROR_HANDLE);
	DWORD written = 0;
	WriteFile(stc_stderr, _strbldr_print.ptr, (DWORD)_strbldr_print.off, &written, NULL);
#else
	write(2, _strbldr_print.ptr, _strbldr_print.off);
#endif

	_strbldr_print.off = 0;
}

thisfile void stc_print_os_stdout(void)
{
#ifdef _WIN32
	HANDLE stc_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD written = 0;
	WriteFile(stc_stdout, _strbldr_print.ptr, (DWORD)_strbldr_print.off, &written, NULL);
#else
	write(1, _strbldr_print.ptr, _strbldr_print.off);
#endif
	_strbldr_print.off = 0;
}

thisfile void stc_print_err(const char *fmt, ...)
{
	if (unlikely(_strbldr_print.rsrv == 0)) {
		stc_print_init();
	}

	va_list vargs;
	va_start(vargs, fmt);
	stc_strbldr_add_v(&_strbldr_print, fmt, vargs);
	va_end(vargs);
	stc_print_os_stderr();
}

thisfile void stc_println_err(const char *fmt, ...)
{
	if (unlikely(_strbldr_print.rsrv == 0)) {
		stc_print_init();
	}

	va_list vargs;
	va_start(vargs, fmt);
	stc_print(STC_ANSI_BRIGHT_RED);
	stc_strbldr_add_v(&_strbldr_print, fmt, vargs);
	stc_print(STC_ANSI_RESET);
	va_end(vargs);
	stc_strbldr_append(&_strbldr_print, "\n");
	stc_print_os_stderr();
}

thisfile void stc_print(const char *fmt, ...)
{
	if (unlikely(_strbldr_print.rsrv == 0)) {
		stc_print_init();
	}

	va_list vargs;
	va_start(vargs, fmt);
	stc_strbldr_add_v(&_strbldr_print, fmt, vargs);
	va_end(vargs);
	stc_print_os_stdout();
}

thisfile void stc_println(const char *fmt, ...)
{
	if (unlikely(_strbldr_print.rsrv == 0)) {
		stc_print_init();
	}

	va_list va_args;
	va_start(va_args, fmt);
	stc_strbldr_add_v(&_strbldr_print, fmt, va_args);
	va_end(va_args);

	stc_strbldr_append(&_strbldr_print, "\n");
	stc_print_os_stdout();
}
