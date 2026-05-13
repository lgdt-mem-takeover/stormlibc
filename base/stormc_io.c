#include "stormc_base.h"
#include "stormc_error_table.h"



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

static enum stc_err_code stc_io_get_file_size(const char *path, u64 *size_out)
{
	if (size_out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	WIN32_FILE_ATTRIBUTE_DATA data = {0};

	if (!GetFileAttributesExA(path, GetFileExInfoStandard, &data)) {
		*size_out = 0;
		return STC_ERR_FILE_STAT_FAILED;
	}

	LARGE_INTEGER size = {0};
	size.LowPart = data.nFileSizeLow;
	size.HighPart = data.nFileSizeHigh;

	*size_out = (u64)size.QuadPart;
	return STC_ERR_OK;
}

static enum stc_err_code stc_io_open_r(const char *path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd.fd = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL,
			       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (out->fd.fd == INVALID_HANDLE_VALUE) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	return stc_io_get_file_size(path, &out->file_size);
}

static enum stc_err_code stc_io_open_rw(const char *path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd.fd = CreateFileA(path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL,
			       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (out->fd.fd == INVALID_HANDLE_VALUE) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	return stc_io_get_file_size(path, &out->file_size);
}

static enum stc_err_code stc_io_open_w(const char *path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd.fd = CreateFileA(path, GENERIC_WRITE, 0, NULL,
			       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (out->fd.fd == INVALID_HANDLE_VALUE) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	return stc_io_get_file_size(path, &out->file_size);
}

static enum stc_err_code stc_io_open_w_new(const char *path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd.fd = CreateFileA(path, GENERIC_WRITE, 0, NULL,
			       CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (out->fd.fd == INVALID_HANDLE_VALUE) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	out->file_size = 0;
	return STC_ERR_OK;
}

static enum stc_err_code stc_io_open_w_append(const char *path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd.fd = CreateFileA(path, FILE_APPEND_DATA, FILE_SHARE_READ, NULL,
			       OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (out->fd.fd == INVALID_HANDLE_VALUE) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	return stc_io_get_file_size(path, &out->file_size);
}

thisfile inline int stc_close(struct stc_file *f)
{
	return CloseHandle(f->fd.fd) ? 0 : -1;
}

#else
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
thisfile inline i64 stc_write(struct stc_file *f, void *ptr, u64 len)
{
	return write(f->fd.fd, ptr, len);
}

thisfile inline i64 stc_read(struct stc_file *f, void *ptr, u64 len)
{
	return read(f->fd.fd, ptr, len);
}


thisfile inline enum stc_err_code stc_io_get_file_size(const char *path, u64 *size_out)
{
	if (size_out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	struct stat st = {};
	if (stat(path, &st) != 0) {
		*size_out = 0;
		return STC_ERR_FILE_STAT_FAILED;
	}

	*size_out = st.st_size;
	return STC_ERR_OK;
}

static enum stc_err_code stc_io_open_r(const char *path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd.fd = open(path, O_RDONLY);
	if (out->fd.fd < 0) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	return stc_io_get_file_size(path, &out->file_size);
}

static enum stc_err_code stc_io_open_rw(const char *path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd.fd = open(path, O_RDWR, 0644);
	if (out->fd.fd < 0) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	return stc_io_get_file_size(path, &out->file_size);
}

static enum stc_err_code stc_io_open_w(const char *path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd.fd = open(path, O_WRONLY);
	if (out->fd.fd < 0) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	return stc_io_get_file_size(path, &out->file_size);
}

static enum stc_err_code stc_io_open_w_new(const char *path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd.fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out->fd.fd < 0) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	out->file_size = 0;
	return STC_ERR_OK;
}

static enum stc_err_code stc_io_open_w_append(const char *path, struct stc_file *out)
{
	if (out == NULL) {
		return STC_ERR_INVALID_ARGUMENT;
	}

	*out = STC_STRUCT_ZERO(stc_file);
	out->fd.fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out->fd.fd < 0) {
		return STC_ERR_FILE_OPEN_FAILED;
	}

	return stc_io_get_file_size(path, &out->file_size);
}


thisfile inline int stc_close(struct stc_file *f)
{
	return close(f->fd.fd);
}
#endif



thisfile inline enum stc_err_code stc_io_read(struct stc_file *f, stc_byte *buffer, u64 size, u64 *size_out)
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
