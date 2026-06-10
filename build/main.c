#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <ftw.h>
#include <libgen.h>
#include <sys/sendfile.h>
#include <elf.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>


#define STAG_ARG_REST '\1'

#define STORMC_ERROR_FMT(_err_msg, _err_str) fprintf(stderr, _err_msg, (int)_err_str.len, _err_str.str)
#define STORMC_ERROR(_err_msg) fprintf(stderr, _err_msg)

#define STAG_USER_COMMANDS(ENTRY) \
	ENTRY(CTAGS,			"--ctags",		"-ct",		"run ctags",				"", true, ' ')\
	ENTRY(INIT,  			"init",    		"-i",  		"init project",				"", false, 0)\
	ENTRY(RUN,   			"run",     		"-r",  		"run build script",			"", false, 0)\
	ENTRY(BUILD, 			"build",   		"-b",  		"build target",				"", true, STAG_ARG_REST)\
	ENTRY(EMBED, 			"embed",   		"-e",  		"embed file into c source",		"", true, ' ')\
	ENTRY(ASM,   			"asm",     		"-asm",		"dump asm",				"", true, ' ')\
	ENTRY(UF,    			"uf",      		"-uf", 		"disassemble function with gdb",	"", true, ' ')\
	ENTRY(REGISTER_PROJ_NAME,	"--register-proj",	"-rpn", 	"register project name",		"", true, '=')\
	ENTRY(REGISTER_PROJ_PATH,	"--register-proj-path",	"-rpp", 	"register project path",		"", true, '=')\
	ENTRY(PROJECT_ADD,		"add",			"-add", 	"add project to local dir",		"", true, ' ')\
	ENTRY(PROJECT_REMOVE,		"remove",		"-rm",		"remove local dir project",		"", true, ' ')\
	ENTRY(PROJECT_UPDATE,		"update",		"-update", 	"update project name for local path",	"", true, ' ')\
	ENTRY(LIST_PROJECTS,		"--list-projects",	"-lstp", 	"list projects",			"", false, 0)\
	ENTRY(GOTO_PROJ,		"goto",			"-g2p",		"go to project directory",		"", true, ' ')\
	ENTRY(SEED,			"seed",			"-seed",	"reserved for now",			"", false, 0)\
	ENTRY(REBUILD,			"rebuild",		"-rbld",	"Stormc, rebuild yourself!",		"", false, 0)\
	ENTRY(NEIYEHALL,		"neiyeh-all",		"-nya",		"View all of Neiyeh",			"", false, 0)\
	ENTRY(NEIYEH,			"neiyeh",		"-ny",		"View random page from Neiyeh",		"", false, 0)

#define STORMC_STAG
#define STORMC_ALLOCATOR
#define STORMC_STRING
#define STORMC_IO
#include "../stormc_header.h"
#include "stormc_buildsystem.h"
#include "defaults.h"

#include "neiyeh.c"


#define DEFAULT_CONFIG_LOCATION STAG_STR("~/.config/stormc/config.stc")
#define STORMC_CFG_META_MAGIC		0xDEADFAEEllu
#define STORMC_CFG_META_VERSION		1llu
#define MAX_PROJECTS 1024


struct stormc_config_meta {
	u64			proj_name_len;
	char			proj_name[1024];

	u64			proj_path_len;
	char			proj_path[1024];
};


struct stormc_config_payload {
	u64				magic;
	u64				version;
	u64				ct_projects;
	bool64				config_is_set;
	struct stormc_config_meta	projects[MAX_PROJECTS];
	u64				stormc_root_len;
	char				stormc_root[1024];
};

struct stormc_project_mapper {
	struct stag_string	config_file_location;


	struct stormc_config_payload	payload;
};


static struct stormc_project_mapper *stc_proj_mapper = NULL;
static char stormc_root[PATH_MAX] = { 0 };

static void stormc_save_config(void);

static void stormc_reset_config_payload(void)
{
	stc_memset(&stc_proj_mapper->payload, 0, sizeof(stc_proj_mapper->payload));
	stc_proj_mapper->payload.magic = STORMC_CFG_META_MAGIC;
	stc_proj_mapper->payload.version = STORMC_CFG_META_VERSION;
}

static stag_bool32 stormc_config_payload_is_valid(void)
{
	if (stc_proj_mapper->payload.magic != STORMC_CFG_META_MAGIC) {
		return false;
	}
	if (stc_proj_mapper->payload.version != STORMC_CFG_META_VERSION) {
		return false;
	}
	if (stc_proj_mapper->payload.ct_projects > MAX_PROJECTS) {
		return false;
	}
	if (stc_proj_mapper->payload.stormc_root_len > sizeof(stc_proj_mapper->payload.stormc_root)) {
		return false;
	}

	for (u64 i = 0; i < stc_proj_mapper->payload.ct_projects; ++i) {
		if (stc_proj_mapper->payload.projects[i].proj_name_len > sizeof(stc_proj_mapper->payload.projects[i].proj_name)) {
			return false;
		}
		if (stc_proj_mapper->payload.projects[i].proj_path_len > sizeof(stc_proj_mapper->payload.projects[i].proj_path)) {
			return false;
		}
	}

	return true;
}

static int stormc_is_root_dir(const char *path)
{
	char header_path[PATH_MAX];
	char scbuild_path[PATH_MAX];

	snprintf(header_path, sizeof(header_path), "%s/stormc_header.h", path);
	snprintf(scbuild_path, sizeof(scbuild_path), "%s/build/scbuild.h", path);

	return access(header_path, F_OK) == 0 && access(scbuild_path, F_OK) == 0;
}

static int stormc_find_root_upward(const char *start_dir)
{
	char current[PATH_MAX];
	if (!realpath(start_dir, current))
		return 0;

	for (;;) {
		if (stormc_is_root_dir(current)) {
			snprintf(stormc_root, sizeof(stormc_root), "%s", current);
			return 1;
		}

		char parent_buf[PATH_MAX];
		snprintf(parent_buf, sizeof(parent_buf), "%s", current);
		char *parent = dirname(parent_buf);

		if (strcmp(parent, current) == 0)
			break;

		snprintf(current, sizeof(current), "%s", parent);
	}

	return 0;
}

static void stormc_store_root_in_config(void)
{
	u64 len = strlen(stormc_root);
	if (len >= sizeof(stc_proj_mapper->payload.stormc_root)) {
		fprintf(stderr, "stormc root path too long: %s\n", stormc_root);
		exit(1);
	}

	stc_memset(stc_proj_mapper->payload.stormc_root, 0, sizeof(stc_proj_mapper->payload.stormc_root));
	stc_memcpy(stc_proj_mapper->payload.stormc_root, stormc_root, len);
	stc_proj_mapper->payload.stormc_root_len = len;
	stc_proj_mapper->payload.config_is_set = true;
	stormc_save_config();
}

static int stormc_try_set_root(const char *path)
{
	char resolved[PATH_MAX];
	if (!path || !path[0] || !realpath(path, resolved))
		return 0;
	if (!stormc_is_root_dir(resolved))
		return 0;

	snprintf(stormc_root, sizeof(stormc_root), "%s", resolved);
	stormc_store_root_in_config();
	return 1;
}

static void stormc_set_root(const char *argv0)
{
	if (stormc_try_set_root(getenv("STORMC_ROOT")))
		return;

	if (stc_proj_mapper->payload.stormc_root_len > 0) {
		char saved_root[1024];
		snprintf(
			saved_root,
			sizeof(saved_root),
			"%.*s",
			(int)stc_proj_mapper->payload.stormc_root_len,
			stc_proj_mapper->payload.stormc_root
		);
		if (stormc_try_set_root(saved_root))
			return;
	}

	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) && stormc_find_root_upward(cwd)) {
		stormc_store_root_in_config();
		return;
	}

	char exe_path[PATH_MAX] = { 0 };
	ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);

	if (len > 0) {
		exe_path[len] = '\0';
	} else if (argv0 && realpath(argv0, exe_path)) {
		/* realpath filled exe_path */
	} else {
		fprintf(stderr, "Could not resolve stormc executable path\n");
		exit(1);
	}

	char dir_path[PATH_MAX];
	snprintf(dir_path, sizeof(dir_path), "%s", exe_path);

	char *bin_dir = dirname(dir_path);
	if (stormc_find_root_upward(bin_dir)) {
		stormc_store_root_in_config();
		return;
	}

	fprintf(stderr, "Could not find stormlibc root.\n");
	fprintf(stderr, "Run stormc once from inside the stormlibc checkout, or set STORMC_ROOT=/path/to/stormlibc.\n");
	exit(1);
}



void stc_proj_add_proj(struct stag_string proj_name, struct stag_string proj_path)
{
	if (unlikely(stc_proj_mapper->payload.ct_projects >= MAX_PROJECTS)) {
		fprintf(stderr, "Capacity reached. Cannot add more projects.\n");
		return;
	}

	stc_memcpy(stc_proj_mapper->payload.projects[stc_proj_mapper->payload.ct_projects].proj_name, proj_name.str, proj_name.len);
	stc_proj_mapper->payload.projects[stc_proj_mapper->payload.ct_projects].proj_name_len = proj_name.len;

	stc_memcpy(stc_proj_mapper->payload.projects[stc_proj_mapper->payload.ct_projects].proj_path, proj_path.str, proj_path.len);
	stc_proj_mapper->payload.projects[stc_proj_mapper->payload.ct_projects].proj_path_len = proj_path.len;

	++stc_proj_mapper->payload.ct_projects;
}


static struct stag_string stormc_trim_quotes(struct stag_string s)
{
	if (s.len >= 2) {
		char first = s.str[0];
		char last  = s.str[s.len - 1];

		if ((first == '"' && last == '"') ||
		    (first == '\'' && last == '\'')) {
			s.str += 1;
			s.len -= 2;
		}
	}
	return s;
}


u8 *ser_config_meta(u8 *data)
{
	u8 *pl = NULL;



	return pl;
}

u8 *deser_config_meta(u8 *data)
{
	u8 *pl = NULL;



	return pl;
}


typedef enum{
	TEMPL_SCBUILD,
	TEMPL_MAIN,
	SCBUILD_TEMPLATES_TYPES_COUNT,
}Scbuild_Templates_Types;

struct stc_string8 Global_Templates_Scbuild[SCBUILD_TEMPLATES_TYPES_COUNT] = {
	[TEMPL_SCBUILD] = { .str = (char *)default_scbuild_c, .len = default_scbuild_c_len},
	[TEMPL_MAIN] = { .str = (char *)default_main_c, .len = default_main_c_len},
};


static int file_exists(const char *path)
{
	return access(path, F_OK) == 0;
}

static void exec_init_clangd(void)
{
	if (file_exists(".clangd"))
		return;

	int fd = try_syscall(open, (".clangd", O_CREAT | O_WRONLY | O_TRUNC, 0644), {
		perror("open");
		exit(1);
	});

	char clangd[PATH_MAX + 512];
	int len = snprintf(
		clangd,
		sizeof(clangd),
		"CompileFlags:\n"
		"  Add:\n"
		"    - -I%s\n"
		"    - '-DSTORMC_ROOT=\"%s\"'\n"
		"    - -mavx2\n"
		"    - -std=c99\n",
		stormc_root,
		stormc_root
	);
	if (len < 0 || (u64)len >= sizeof(clangd)) {
		fprintf(stderr, "stormc root path too long for .clangd\n");
		try_syscall(close, (fd), {
			perror("close");
			exit(1);
		});
		exit(1);
	}

	try_syscall(write, (fd, clangd, len), {
		perror("write");
		exit(1);
	});

	try_syscall(close, (fd), {
		perror("close");
		exit(1);
	});

	try(printf, ("[INIT] Successfully created .clangd\n"), {
		perror("printf");
		exit(1);
	});
}

static void exec_ctags(struct stag_string extra)
{
	char cmd[512] = { 0};

	if (extra.str && extra.len) {
		snprintf(cmd, sizeof(cmd), "ctags -R . %.*s", (int)extra.len, extra.str);
	} else {
		snprintf(cmd, sizeof(cmd), "ctags -R .");
	}

	int ret = system(cmd);
	if (ret == -1) {
		perror("system");
		return;
	}
	if (WIFEXITED(ret) && WEXITSTATUS(ret) == 0) {
		printf("Command 'ctags' ran successfully\n");
	} else if (WIFEXITED(ret)) {
		printf("Command 'ctags' exited with code %d\n", WEXITSTATUS(ret));
	} else {
		printf("Command 'ctags' abnormal termination\n");
	}
}

static void exec_init(void)
{
	int fd = try_syscall(open, ("scbuild.c", O_WRONLY | O_CREAT | O_TRUNC, 0644), {
		perror("open");
		exit(1);
	});

	try(printf, ("[INIT] Successfully created scbuild.c\n"), {
		perror("printf");
		exit(1);
	});

	try_syscall(write, (fd, Global_Templates_Scbuild[TEMPL_SCBUILD].str, Global_Templates_Scbuild[TEMPL_SCBUILD].len), {
		perror("write");
		exit(1);
	});

	if (!file_exists("src")) {
		mkdir("src", 0755);
	}

	exec_init_clangd();

	if (!file_exists("src/main.c")) {
		int main_fd = try_syscall(open, ("src/main.c", O_CREAT | O_WRONLY | O_TRUNC, 0644), {
			perror("open");
			exit(1);
		});

		try(printf, ("[INIT] Successfully created src/main.c\n"), {
			perror("printf");
			exit(1);
		});

		try_syscall(write, (main_fd, Global_Templates_Scbuild[TEMPL_MAIN].str, Global_Templates_Scbuild[TEMPL_MAIN].len), {
			perror("write");
			exit(1);
		});

		try_syscall(close, (main_fd), {
			perror("close");
			exit(1);
		});
	}

	try_syscall(close, (fd), {
		perror("close");
		exit(1);
	});
}

static void exec_run(void)
{
	char cmd[PATH_MAX * 2];
	snprintf(
		cmd,
		sizeof(cmd),
		"gcc -std=gnu99 -mavx2 -I\"%s\" -DSTORMC_ROOT='\"%s\"' scbuild.c -o scbuild && ./scbuild run",
		stormc_root,
		stormc_root
	);

	int ret = system(cmd);
	if (ret == -1) {
		perror("system");
	}
}

static void exec_build(struct stag_string target)
{
	int ret;

	if (!target.str) {
		fprintf(stderr, "build requires an argument\n");
		exit(1);
	}


	if (stag_strcmp(target, STAG_STR("run"))) {
		char cmd[PATH_MAX * 2];
		snprintf(
			cmd,
			sizeof(cmd),
			"gcc -std=gnu99 -mavx2 -I\"%s\" -DSTORMC_ROOT='\"%s\"' -DSASM %s/obj_files/sasm_stringlib.o scbuild.c -o scbuild && ./scbuild build run",
			stormc_root,
			stormc_root,
			stormc_root
		);
		ret = system(cmd);
	} else if (stag_strcmp(target, STAG_STR("asm"))) {
		char cmd[PATH_MAX * 2];
		snprintf(
			cmd,
			sizeof(cmd),
			"gcc -std=gnu99 -mavx2 -I\"%s\" -DSTORMC_ROOT='\"%s\"' scbuild.c -o scbuild && ./scbuild build asm",
			stormc_root,
			stormc_root
		);
		ret = system(cmd);
	} else {
		char cmd[PATH_MAX * 2];
		snprintf(cmd, sizeof(cmd),
			 "gcc -std=gnu99 -mavx2 -I\"%s\" -DSTORMC_ROOT='\"%s\"' -DSASM %s/obj_files/sasm_stringlib.o scbuild.c -o scbuild && ./scbuild %.*s",
			 stormc_root,
			 stormc_root,
			 stormc_root,
			 (int)target.len, target.str);
		ret = system(cmd);
		// stc_println("executed: {cstring}", cmd);

	}

	if (ret == -1) {
		perror("system");
	}
}

static void exec_embed(struct stag_string spec)
{
	struct stag_array_string parts = stag_string_to_array_of_strings(spec, ' ');
	if (parts.len < 2) {
		fprintf(stderr, "embed requires: <input> <output>\n");
		exit(1);
	}

	struct stag_string in  = parts.strings[0];
	struct stag_string out = parts.strings[1];

	char in_path[1024];
	char out_path[1024];

	if (in.len >= sizeof(in_path)) {
		fprintf(stderr, "embed input path too long\n");
		exit(1);
	}
	if (out.len >= sizeof(out_path)) {
		fprintf(stderr, "embed output path too long\n");
		exit(1);
	}

	snprintf(in_path, sizeof(in_path), "%.*s", (int)in.len, in.str);
	snprintf(out_path, sizeof(out_path), "%.*s", (int)out.len, out.str);

	FILE *fin = fopen(in_path, "rb");
	if (!fin) {
		perror("fopen");
		exit(1);
	}

	unsigned char buffer_fd_in[4096];
	u64 file_size = 0;

	int file_out = open(out_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_out == -1) {
		perror("open");
		fclose(fin);
		exit(1);
	}

	char var_name_buff[1024];
	char var_len_buff[1024];
	char fmt_file_name[1024];

	for (u32 i = 0; i < in.len && i < sizeof(fmt_file_name) - 1; ++i) {
		char c = in.str[i];
		bool valid_ident = (c == '_') ||
			(c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z');
		bool valid_ident_tail = valid_ident || (c >= '0' && c <= '9');
		fmt_file_name[i] = (i == 0)
			? (valid_ident ? c : '_')
			: (valid_ident_tail ? c : '_');
	}
	fmt_file_name[in.len] = '\0';

	u32 buff_len = snprintf(var_name_buff, sizeof(var_name_buff),
				"const unsigned char %s[] = { \n", fmt_file_name);

	try(write, (file_out, var_name_buff, buff_len), {
		perror("write");
		exit(1);
	});

read_loop:
	{
		size_t bytes_read = fread(buffer_fd_in, 1, sizeof(buffer_fd_in), fin);
		if (bytes_read == 0) goto read_done;

		for (u64 i = 0; i < bytes_read; ++i) {
			char buf[16];
			int len = snprintf(buf, sizeof(buf), "\t0x%02x,", buffer_fd_in[i]);
			try(write, (file_out, buf, len), {
				perror("write");
				exit(1);
			});

			++file_size;
			if (file_size % 12 == 0) {
				try(write, (file_out, "\n", 1), {
					perror("write");
					exit(1);
				});
			}
		}

		goto read_loop;
	}

read_done:
	if (ferror(fin)) {
		perror("fread");
		fclose(fin);
		exit(1);
	}
	fclose(fin);

	try(write, (file_out, "\n};\n", 4), {
		perror("write");
		exit(1);
	});

	u32 len_var_len = snprintf(var_len_buff, sizeof(var_len_buff),
				   "\nconst unsigned int %s_len = %llu;\n",
				   fmt_file_name, (unsigned long long)file_size);

	try(write, (file_out, var_len_buff, len_var_len), {
		perror("write");
		exit(1);
	});

	close(file_out);
}

static void exec_asm(struct stag_string target)
{
	if (!target.str) {
		fprintf(stderr, "asm requires a target binary name\n");
		exit(1);
	}

	char cmd[1024];
	snprintf(cmd, sizeof(cmd),
		 "objdump -d -M intel ./%.*s > stormc_asm.log 2>&1",
		 (int)target.len, target.str);

	int ret = system(cmd);
	if (ret == -1) {
		perror("system");
	}
}

static void exec_uf(struct stag_string spec)
{
	struct stag_array_string parts = stag_string_to_array_of_strings(spec, ' ');
	if (parts.len < 2) {
		fprintf(stderr, "uf requires: <binary> <function>\n");
		exit(1);
	}

	struct stag_string bin  = parts.strings[0];
	struct stag_string func = parts.strings[1];

	char cmd[1024];
	snprintf(cmd, sizeof(cmd),
		"gdb -batch -ex 'set disassembly-flavor intel' "
		"-ex 'disassemble %.*s' %.*s > stormc_asm_%.*s_%.*s.log 2>&1",
		(int)func.len, func.str,
		(int)bin.len,  bin.str,
		(int)bin.len,  bin.str,
		(int)func.len, func.str);

	int ret = system(cmd);
	if (ret == -1) {
		perror("system");
	}
}


stag_bool32 path_exists(struct stag_string proj_path)
{

	for (u64 i = 0; i < stc_proj_mapper->payload.ct_projects; ++i) {
		struct stag_string current = { .str = stc_proj_mapper->payload.projects[i].proj_path, .len = stc_proj_mapper->payload.projects[i].proj_path_len};
		if (stag_strcmp(proj_path, current)) {
			return true;
		}
	}
	return false;
}

stag_bool32 proj_exists(struct stag_string proj_name)
{
	for (u64 i = 0; i < stc_proj_mapper->payload.ct_projects; ++i) {
		struct stag_string current = { .str = stc_proj_mapper->payload.projects[i].proj_name, .len = stc_proj_mapper->payload.projects[i].proj_name_len};
		if (stag_strcmp(proj_name, current)) {
			return true;
		}
	}
	return false;
}


void exec_reg_proj(struct stag_string proj_name, struct stag_string proj_path)
{
	if (proj_name.str != NULL && proj_name.len > 0) {
		if (proj_path.str != NULL && proj_path.len > 0) {
			fprintf(stdout, "Registered project name: %.*s\n", (int)proj_name.len, proj_name.str);
			fprintf(stdout, "Registered project path: %.*s\n", (int)proj_path.len, proj_path.str);

			if (!stc_proj_mapper->payload.config_is_set) {
				stc_proj_mapper->payload.config_is_set = true;
			}

			u64 *ct_projs = &stc_proj_mapper->payload.ct_projects;

			if (proj_name.len > 1024) {
				fprintf(stderr, "Project name %.*s exceeds maximum length of 1024\n", (int)proj_name.len, proj_name.str);
				goto finish;
			}
			if (proj_path.len > 1024) {
				fprintf(stderr, "Project path %.*s exceeds maximum length of 1024\n", (int)proj_path.len, proj_path.str);
				goto finish;
			}

			if (path_exists(proj_path)) {
				fprintf(stderr, "Project path %.*s already registered\n", (int)proj_path.len, proj_path.str);
				return;
			}

			if (proj_exists(proj_name)) {
				fprintf(stderr, "Project name %.*s already registered\n", (int)proj_name.len, proj_name.str);
				return;
			}

			stc_memcpy(stc_proj_mapper->payload.projects[*ct_projs].proj_name, proj_name.str, proj_name.len);
			stc_proj_mapper->payload.projects[*ct_projs].proj_name_len = proj_name.len;

			stc_memcpy(stc_proj_mapper->payload.projects[*ct_projs].proj_path, proj_path.str, proj_path.len);
			stc_proj_mapper->payload.projects[*ct_projs].proj_path_len = proj_path.len;

			++(*ct_projs);



			finish:
				return;
		}
		fprintf(stderr, "Missing project path for project name: %.*s\n", (int)proj_name.len, proj_name.str);
		return;
	}
	if (proj_name.str == NULL) {
		fprintf(stderr, "Missing project name\n");
	}
	if (proj_path.str == NULL) {
		fprintf(stderr, "Missing project path\n");
	}

}


void stormc_check_system(void)
{
	stc_proj_mapper = stc_alloc(sizeof(*stc_proj_mapper));
	stc_proj_mapper->config_file_location = DEFAULT_CONFIG_LOCATION;
	stormc_reset_config_payload();
	const char *home = getenv("HOME");
	if (!home) {
		fprintf(stderr, "Env variable HOME is not set\n");
		return;
	}
	char path[1024] = { 0};
	snprintf(path, sizeof(path), "%s/.config/stormc/config.stc", home);
	char config_parent[1024] = { 0};
	snprintf(config_parent, sizeof(config_parent), "%s/.config", home);
	char dir[1024] = { 0};
	snprintf(dir, sizeof(dir), "%s/.config/stormc", home);

	if (!file_exists(config_parent)) {
		mkdir(config_parent, 0755);
	}
	if (!file_exists(dir)) {
		mkdir(dir, 0755);
	}

	if (!file_exists(path)) {
		FILE *f = fopen(path, "w");
		if (f) {
			fclose(f);
		} else {
			perror("fopen");
			return;
		}
	}

	FILE *f = fopen(path, "rb");
	if (!f) {
		perror("fopen");
		return;
	} else {
		size_t bytes_read = fread(&stc_proj_mapper->payload, 1, sizeof(stc_proj_mapper->payload), f);
		if (ferror(f)) {
			perror("fread");
			stormc_reset_config_payload();
		} else if (bytes_read != 0 && bytes_read != sizeof(stc_proj_mapper->payload)) {
			fprintf(stderr, "Ignoring partial stormc config\n");
			stormc_reset_config_payload();
		} else if (bytes_read == sizeof(stc_proj_mapper->payload) && !stormc_config_payload_is_valid()) {
			fprintf(stderr, "Ignoring invalid stormc config\n");
			stormc_reset_config_payload();
		}
		if (fclose(f) != 0) {
			perror("fclose");
		}
	}
}


void exec_list_projs(void)
{
	for (u64 i = 0; i < stc_proj_mapper->payload.ct_projects; ++i) {
		printf("Project Name: %.*s\n", (int)stc_proj_mapper->payload.projects[i].proj_name_len, stc_proj_mapper->payload.projects[i].proj_name);
		printf("\t\t-->Project Path: %.*s\n", (int)stc_proj_mapper->payload.projects[i].proj_path_len, stc_proj_mapper->payload.projects[i].proj_path);
	}
}



struct stag_string get_project_path_from_name(struct stag_string proj_name)
{
	for (u64 i = 0; i < stc_proj_mapper->payload.ct_projects; ++i) {
		struct stag_string current = { .str = stc_proj_mapper->payload.projects[i].proj_name, .len = stc_proj_mapper->payload.projects[i].proj_name_len};
		if (stag_strcmp(proj_name, current)) {
			return (struct stag_string){
				.str = stc_proj_mapper->payload.projects[i].proj_path,
				.len = stc_proj_mapper->payload.projects[i].proj_path_len
			};
		}
	}

	return (struct stag_string){
		.str = NULL,
		.len = 0
	};
}




/*TODO: WORK IN PROGRESS FOR A STORMC SESSIN MANAGER*/
static void exec_start(void)
{
	char line[4096];

	for (;;) {
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd))) {
			printf("stormc:%s$ ", cwd);
		} else {
			printf("stormc$ ");
		}
		fflush(stdout);

		if (!fgets(line, sizeof(line), stdin)) {
			break; // EOF / Ctrl-D
		}

		// trim trailing newline
		size_t len = strlen(line);
		if (len && line[len - 1] == '\n') {
			line[len - 1] = '\0';
		}

		if (line[0] == '\0') {
			continue;
		}

		if (strcmp(line, "exit") == 0) {
			break;
		}

		if (strcmp(line, "pwd") == 0) {
			if (getcwd(cwd, sizeof(cwd))) {
				printf("%s\n", cwd);
			}
			continue;
		}

		if (strncmp(line, "cd ", 3) == 0) {
			char *path = line + 3;
			if (chdir(path) != 0) {
				perror("chdir");
			}
			continue;
		}

		if (strncmp(line, "goto ", 5) == 0) {
			struct stag_string proj = {
				.str = line + 5,
				.len = strlen(line + 5),
			};

			proj = stormc_trim_quotes(proj);

			struct stag_string path = get_project_path_from_name(proj);
			char buf[1024];
			snprintf(buf, sizeof(buf), "%.*s", (int)path.len, path.str);
			printf("executing %s\n", buf);

			if (chdir(buf) != 0) {
				perror("chdir");
			}
			continue;
		}

		// everything else: hand off to shell
		int ret = system(line);
		if (ret == -1) {
			perror("system");
		}
	}
}



void exec_goto_dir(struct stag_string proj_name)
{
	if (proj_name.str == NULL || proj_name.len == 0) {
		fprintf(stderr, "goto requires a project name\n");
		return;
	}

	struct stag_string proj_path = get_project_path_from_name(proj_name);
	if (proj_path.str == NULL) {
		fprintf(stderr, "Project not found: %.*s\n", (int)proj_name.len, proj_name.str);
		return;
	}

	fprintf(stdout, "%.*s\n", (int)proj_path.len, proj_path.str);
}


void exec_add_proj(struct stag_array_string sarr)
{
	if (sarr.len != 2 || sarr.strings[0].len == 0 || sarr.strings[1].len == 0) {
		fprintf(stderr, "add requires: <name>|<path>\n");
		return;
	}

	struct stag_string proj_name = sarr.strings[0];
	struct stag_string proj_path = sarr.strings[1];

	if (proj_name.len > 1024) {
		STORMC_ERROR_FMT("Project exceeds max length of 1024: %.*s\n", proj_name);
		return;
	}
	if (proj_path.len > 1024) {
		STORMC_ERROR_FMT("Project path exceeds max length of 1024: %.*s\n", proj_path);
		return;
	}
	if (!proj_exists(proj_name)) {
		stc_proj_add_proj(proj_name, proj_path);
		return;
	}
	STORMC_ERROR_FMT("Project already exists: %.*s\n", proj_name);
}

void exec_update_proj(struct stag_array_string sarr)
{
	if (sarr.len != 2 || sarr.strings[0].len == 0 || sarr.strings[1].len == 0) {
		fprintf(stderr, "update requires: <old_name>|<new_name>\n");
		return;
	}

	struct stag_string old_name = sarr.strings[0];
	struct stag_string new_name = sarr.strings[1];

	if (new_name.len > 1024) {
		STORMC_ERROR_FMT("Project exceeds max length of 1024: %.*s\n", new_name);
		return;
	}

	for (u64 i = 0; i < stc_proj_mapper->payload.ct_projects; ++i) {
		struct stag_string current = { .str = stc_proj_mapper->payload.projects[i].proj_name, .len = stc_proj_mapper->payload.projects[i].proj_name_len};
		if (stag_strcmp(old_name, current)) {
			stc_memcpy(stc_proj_mapper->payload.projects[i].proj_name, new_name.str, new_name.len);
			stc_proj_mapper->payload.projects[i].proj_name_len = new_name.len;
			break;
		}
	}
}




void exec_remove_proj(struct stag_string proj_name)
{
	for (u64 i = 0; i < stc_proj_mapper->payload.ct_projects; ++i) {
		struct stag_string current = { .str = stc_proj_mapper->payload.projects[i].proj_name, .len = stc_proj_mapper->payload.projects[i].proj_name_len};
		if (stag_strcmp(proj_name, current)) {
			stc_memmove(&stc_proj_mapper->payload.projects[i],
				    &stc_proj_mapper->payload.projects[i + 1],
				    (stc_proj_mapper->payload.ct_projects - i - 1) * sizeof(*stc_proj_mapper->payload.projects)
				    );
			--stc_proj_mapper->payload.ct_projects;
			stc_memset(&stc_proj_mapper->payload.projects[stc_proj_mapper->payload.ct_projects], 0,
			       sizeof(*stc_proj_mapper->payload.projects));
			break;
		}
	}
}


static void stormc_save_config(void)
{
	const char *home = getenv("HOME");
	if (!home) {
		fprintf(stderr, "HOME is not set\n");
		return;
	}

	char path[1024];
	snprintf(path, sizeof(path), "%s/.config/stormc/config.stc", home);

	FILE *fout = fopen(path, "wb");
	if (!fout) {
		perror("fopen");
		return;
	}

	fwrite(&stc_proj_mapper->payload, sizeof(stc_proj_mapper->payload), 1, fout);
	fclose(fout);
}



void exec_seed(void)
{
	char buff[1024] = { 0};
	if (!getcwd(buff, sizeof(buff) - 1)) {
		perror("getcwd");
	}
	printf("cwd: %s\n", buff);
}


void *exec_rebuild_self(struct stag_cmd_call *call)
{
	if (!file_exists("main.c")) {
		fprintf(stderr, "Cannot find main.c\nAborting!\n");
		exit(1);
	}

	if (system("clang -mavx2 main.c -O3 -o main") != 0) {
		perror("system");
		exit(1);
	}
	const char *home = getenv("HOME");
	if (!home) {
		fprintf(stderr, "HOME not set\n");
		exit(1);
	}

	char local_dir[1024] = {0};
	snprintf(local_dir, sizeof(local_dir), "%s/.local", home);

	char local_bin_dir[1024] = {0};
	snprintf(local_bin_dir, sizeof(local_bin_dir), "%s/.local/bin", home);

	if (!file_exists(local_dir)) {
		if (mkdir(local_dir, 0755) == -1) {
			perror("mkdir ~/.local");
			exit(1);
		}
	}

	if (!file_exists(local_bin_dir)) {
		if (mkdir(local_bin_dir, 0755) == -1) {
			perror("mkdir ~/.local/bin");
			exit(1);
		}
	}


	char stormc_path[1024] = { 0};
	snprintf(stormc_path, sizeof(stormc_path), "%s/.local/bin/stormc", home);
	char stormc_temp_path[1024] = { 0};
	snprintf(stormc_temp_path, sizeof(stormc_temp_path), "%s/.local/bin/stormc.tmp", home);


	char *main_path = "main";

	int stormc_bin_fd = open(stormc_temp_path, O_RDWR | O_CREAT | O_TRUNC, 0755);
	if (stormc_bin_fd == -1) {
		printf("stormc not found\n");
		perror("open");
		exit(1);
	}
	int main_fd = open(main_path, O_RDONLY);
	if (main_fd == -1) {
		printf("main not found\n");
		perror("open");
		exit(1);
	}

	struct stat main_stat = { };
	if(fstat(main_fd, &main_stat) == -1) {
		perror("fstat");
		exit(1);
	}

	if(ftruncate(stormc_bin_fd, main_stat.st_size) == -1) {
		perror("ftruncate");
		exit(1);
	}

	u8 *stormc_bin = (u8*)mmap(NULL, main_stat.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, stormc_bin_fd, 0);
	if (stormc_bin == MAP_FAILED) {
		printf("stormc bin failed\n");
		perror("mmap");
		exit(1);
	}

	u8 *main_bin = (u8*)mmap(NULL, main_stat.st_size, PROT_READ, MAP_PRIVATE, main_fd, 0);
	if (main_bin == MAP_FAILED) {
		printf("main bin failed\n");
		perror("mmap");
		exit(1);
	}


	stc_memcpy(stormc_bin, main_bin, main_stat.st_size);
	if (msync(stormc_bin, main_stat.st_size, MS_SYNC) == -1) {
		perror("msync");
		exit(1);
	}
	if (chmod(stormc_temp_path, 0755) == -1) {
		perror("chmod");
		exit(1);
	}
	if (rename(stormc_temp_path, stormc_path) == -1) {
		perror("rename");
		exit(1);
	}

	close(stormc_bin_fd);
	close(main_fd);
	munmap(stormc_bin, main_stat.st_size);
	munmap(main_bin, main_stat.st_size);
	return NULL;
}


void *cmd_init_cb(struct stag_cmd_call *call)
{
	(void)call;
	exec_init();
	return NULL;
}

void *cmd_run_cb(struct stag_cmd_call *call)
{
	(void)call;
	exec_run();
	return NULL;
}

void *cmd_build_cb(struct stag_cmd_call *call)
{
	struct stag_string *arg = call->args;
	exec_build(*arg);
	return NULL;
}

void *cmd_project_add_cb(struct stag_cmd_call *call)
{
	struct stag_array_string *arr = call->args;
	exec_add_proj(*arr);
	return NULL;
}

void *cmd_ctags_cb(struct stag_cmd_call *call)
{
	struct stag_string *arg = call->args;
	exec_ctags(*arg);
	return NULL;
}

void *cmd_embed_cb(struct stag_cmd_call *call)
{
	struct stag_string *arg = call->args;
	exec_embed(*arg);
	return NULL;
}

void *cmd_asm_cb(struct stag_cmd_call *call)
{
	struct stag_string *arg = call->args;
	exec_asm(*arg);
	return NULL;
}

void *cmd_uf_cb(struct stag_cmd_call *call)
{
	struct stag_string *arg = call->args;
	exec_uf(*arg);
	return NULL;
}

void *cmd_register_proj_name_cb(struct stag_cmd_call *call)
{
	struct stag_string *arg = call->args;
	exec_reg_proj(*arg, (struct stag_string){ 0});
	return NULL;
}

void *cmd_register_proj_path_cb(struct stag_cmd_call *call)
{
	struct stag_string *arg = call->args;
	exec_reg_proj((struct stag_string){ 0}, *arg);
	return NULL;
}

void *cmd_project_remove_cb(struct stag_cmd_call *call)
{
	struct stag_string *arg = call->args;
	exec_remove_proj(*arg);
	return NULL;
}

void *cmd_project_update_cb(struct stag_cmd_call *call)
{
	struct stag_array_string *arr = call->args;
	exec_update_proj(*arr);
	return NULL;
}

void *cmd_list_projects_cb(struct stag_cmd_call *call)
{
	(void)call;
	exec_list_projs();
	return NULL;
}

void *cmd_goto_proj_cb(struct stag_cmd_call *call)
{
	struct stag_string *arg = call->args;
	exec_goto_dir(*arg);
	return NULL;
}

void *cmd_seed_cb(struct stag_cmd_call *call)
{
	(void)call;
	exec_seed();
	return NULL;
}


void *exec_neiyeh_all(struct stag_cmd_call *call)
{
	(void)call;
	neiyeh_viewall();
	return NULL;

}

void *exec_neiyeh_random(struct stag_cmd_call *call)
{
	(void)call;
	neiyeh_random();
	return NULL;
}

static void register_stormc_callbacks(void)
{
	struct stag_callback_desc descs[] = {
		{ .cmd = CTAGS, .func = cmd_ctags_cb, .immediate = false },
		{ .cmd = INIT, .func = cmd_init_cb, .immediate = false },
		{ .cmd = RUN, .func = cmd_run_cb, .immediate = false },
		{ .cmd = BUILD, .func = cmd_build_cb, .immediate = false },
		{ .cmd = EMBED, .func = cmd_embed_cb, .immediate = false },
		{ .cmd = ASM, .func = cmd_asm_cb, .immediate = false },
		{ .cmd = UF, .func = cmd_uf_cb, .immediate = false },
		{ .cmd = REGISTER_PROJ_NAME, .func = cmd_register_proj_name_cb, .immediate = false },
		{ .cmd = REGISTER_PROJ_PATH, .func = cmd_register_proj_path_cb, .immediate = false },
		{ .cmd = PROJECT_ADD, .func = cmd_project_add_cb, .immediate = false },
		{ .cmd = PROJECT_REMOVE, .func = cmd_project_remove_cb, .immediate = false },
		{ .cmd = PROJECT_UPDATE, .func = cmd_project_update_cb, .immediate = false },
		{ .cmd = LIST_PROJECTS, .func = cmd_list_projects_cb, .immediate = false },
		{ .cmd = GOTO_PROJ, .func = cmd_goto_proj_cb, .immediate = false },
		{ .cmd = SEED, .func = cmd_seed_cb, .immediate = false },
		{ .cmd = REBUILD, .func = exec_rebuild_self, .immediate = false },
		{.cmd = NEIYEHALL, .func = exec_neiyeh_all, .immediate = true},
		{.cmd = NEIYEH, .func = exec_neiyeh_random, .immediate = true},
	};

	stag_register_callback_batch(descs, STAG_ARRCOUNT(descs));
}

static struct stc_stack *stack_cmd_call = NULL;
static struct stc_stack *stack_stag_strings = NULL;
static struct stc_stack *stack_stag_array_strings = NULL;
static void build_calls(void)
{
	for (;;) {
		struct stag_cmd_array cmd = stag_next_cmd();
		if (cmd.cmd == NIL) break;

		switch (cmd.cmd) {
		case INIT:
		case RUN:
		case LIST_PROJECTS:
		case SEED:
		case REBUILD:
		{
			struct stag_cmd_call *call = (struct stag_cmd_call*)stc_stack_push(stack_cmd_call, struct stag_cmd_call, 1);
			call->arg_count = 0;
			call->args = NULL;
			stag_register_deferred_args(cmd.cmd, call);
			break;
		}

		case BUILD:
		case CTAGS:
		case EMBED:
		case ASM:
		case UF:
		case GOTO_PROJ:
		case REGISTER_PROJ_NAME:
		case REGISTER_PROJ_PATH:
		case PROJECT_REMOVE:
		{
			struct stag_string *arg = (struct stag_string*)stc_stack_push(stack_stag_strings, struct stag_string, 1);
			*arg = cmd.args;

			struct stag_cmd_call *call = (struct stag_cmd_call*)stc_stack_push(stack_cmd_call, struct stag_cmd_call, 1);
			call->arg_count = 1;
			call->args = arg;
			stag_register_deferred_args(cmd.cmd, call);
			break;
		}

		case PROJECT_ADD:
		case PROJECT_UPDATE:
		{
			struct stag_array_string *arr = (struct stag_array_string*)stc_stack_push(stack_stag_array_strings, struct stag_array_string, 1);
			*arr = stag_string_to_array_of_strings(cmd.args, '|');

			struct stag_cmd_call *call = (struct stag_cmd_call *)stc_stack_push(stack_cmd_call, struct stag_cmd_call, 1);
			call->arg_count = arr->len;
			call->args = arr;
			stag_register_deferred_args(cmd.cmd, call);
			break;
		}

		default:
			break;
		}
	}
}


void stormc_init_stacks(void)
{
	stack_cmd_call = stc_stack_gen(1llu << 28);
	stack_stag_strings = stc_stack_gen(1llu << 28);
	stack_stag_array_strings = stc_stack_gen(1llu << 28);
}

int main(int argc, char **argv)
{
	stormc_check_system();
	stormc_set_root(argv[0]);
	stag_run(argc, argv);
	stormc_init_stacks();
	register_stormc_callbacks();
	build_calls();
	stag_deferred_flush();
	stormc_save_config();

	return 0;
}
