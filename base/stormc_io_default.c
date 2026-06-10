#ifdef _WIN32
thisfile HANDLE stc_open(struct stc_string8 path, DWORD desired_access, DWORD share_mode, DWORD creation_disposition, DWORD flags)
{
	if (path.str == NULL || path.len == MAX_UINT64) {
		return INVALID_HANDLE_VALUE;
	}

	char *path_z = (char *)stc_alloc(path.len + 1);
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
#else
thisfile int stc_open(struct stc_string8 path, u64 flags, u64 mode)
{
	if (path.str == NULL || path.len == MAX_UINT64) {
		return -1;
	}

	char *path_z = (char *)stc_alloc(path.len + 1);
	if (path_z == NULL) {
		return -1;
	}

	stc_memcpy(path_z, path.str, path.len);
	path_z[path.len] = 0;

	int result = open(path_z, (int)flags, (mode_t)mode);
	stc_free(path_z, path.len + 1);
	return result;
}
#endif
