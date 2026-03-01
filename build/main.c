#ifndef _XOPEN_SOURCE
	#define _XOPEN_SOURCE 500
#endif
#include <stdio.h>
#include "/data/2026-projs/c/stormlibc/stormc_header.h"
#include "/data/2026-projs/c/stormlibc/base/stormc_allocator.c"
#include "/data/2026-projs/c/stormlibc/text/stormc_string.c"

#include "stormc_buildsystem.h"
#include "defaults.h"
#include <assert.h>
#include <sys/stat.h>
#include <time.h>

#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ftw.h>
#include <libgen.h>
#include <sys/sendfile.h>
#include <elf.h>
// #include "stc_codegen_impl.h"

typedef enum{
	INIT,
	BUILD,
	RUN,

	CTAGS,
	EMBED,

	ASM,
	STCLIB_SYNC,
	BUILDINFO,
	CODEGEN,
	UF,
	G_COMMAND_TYPES_COUNT,
}G_Command_Types;




struct stc_string8 G_COMMANDS[G_COMMAND_TYPES_COUNT] = {
	[INIT]		= STR("init"),
	[BUILD]		= STR("build"),
	[RUN]		= STR("run"),
	[CTAGS]		= STR("ctags"),
	[EMBED] 	= STR("embed"),
	[ASM]		= STR("asm"),
	[STCLIB_SYNC]	= STR("stclib_sync"),
	[BUILDINFO]	= STR("buildinfo"),
	[CODEGEN]	= STR("codegen"),
	[UF]		= STR("uf"),
};


typedef struct{
	struct stc_string8		_args[32];
	u32				len;
}StormC_Main_Entry_Process;


extern const char default_scbuild_start[];

typedef enum{
	TEMPL_SCBUILD,
	TEMPL_MAIN,
	SCBUILD_TEMPLATES_TYPES_COUNT,
}Scbuild_Templates_Types;

struct stc_string8 Global_Templates_Scbuild[SCBUILD_TEMPLATES_TYPES_COUNT] = {
	[TEMPL_SCBUILD] = {.str = (char *)default_scbuild_c, .len = default_scbuild_c_len},
	[TEMPL_MAIN] = {.str = (char *)default_main_c, .len = default_main_c_len},
};


static int file_exists(const char *path)
{
	return access(path, F_OK) == 0;
}

static void exec_ctags(StormC_Main_Entry_Process sc_main)
{
	char path_buf[256];
	snprintf(path_buf, sizeof(path_buf), "ctags -R . %s", sc_main._args[1].str);
	int ret = system(path_buf);
	if (ret == -1) perror("system");
	else if (WIFEXITED(ret)) {
		int status = WEXITSTATUS(ret);
		if (status == 0) printf("Command 'ctags' ran successfully\n");
		else {
			printf("Command 'ctags' exited with code %d\n", status);
		}
	} else {
		printf("Command 'ctags' abnormal termination\n");
	}

}

static void exec_init(StormC_Main_Entry_Process sc_main)
{
	int fd = try_syscall(open, ("scbuild.c", O_WRONLY | O_CREAT | O_TRUNC, 0644), {
		perror("open");
		exit(1);
	});
	try(printf, ("[INIT] Succesfully created scbuild.c\n"),{
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
	if (!file_exists("src/main.c")){
		int main = try_syscall(open,("src/main.c", O_CREAT | O_WRONLY, 0644),{
			perror("open");
			exit(1);
		});
		try(printf, ("[INIT] Succesfully created main.c\n"), {
			perror("printf");
			exit(1);
		});
		try_syscall(write, (main, Global_Templates_Scbuild[TEMPL_MAIN].str, Global_Templates_Scbuild[TEMPL_MAIN].len), {
			perror("write");
			exit(1);
		});
		try_syscall(close,(main),{
			perror("close");
			exit(1);
		});
	}
	try_syscall(close,(fd),{
		perror("close");
		exit(1);
	});

}

static void exec_run(void)
{
	int ret = system("gcc -mavx2 scbuild.c -o scbuild && ./scbuild run");
	int status = WEXITSTATUS(ret);
	if(ret == -1) perror("system");
}


static void exec_build(StormC_Main_Entry_Process sc_main)
{
	int ret, status;
	if (sstrcmpx(sc_main._args[1], G_COMMANDS[RUN])) {
		ret = system("gcc -mavx2 scbuild.c -o scbuild && ./scbuild build run");
		status = __WEXITSTATUS(ret);
		if (ret == -1) perror("system");

	}
	else if (sstrcmpx(sc_main._args[1], G_COMMANDS[ASM])) {
		char cmd[1024];
		u32 len = snprintf(cmd, sizeof(cmd), "objdump -d -M intel ./%.*s > stormc_asm.log 2>&1", (int)sc_main._args[2].len, sc_main._args[2].str);
		cmd[len] = '\0';
		ret = system(cmd);
		status = __WEXITSTATUS(ret);
		if (ret == -1) perror("system");

	}
	else {
		char cmd[64];
		u32 len = snprintf(cmd, sizeof(cmd), "gcc -mavx2 scbuild.c -o scbuild && ./scbuild %s", sc_main._args[1].str);
		ret = system(cmd);
		status = WEXITSTATUS(ret);
		if(ret == -1) perror("system");
	}

}


static void exec_embed(StormC_Main_Entry_Process sc_main)
{
	FILE *fin = fopen(sc_main._args[1].str, "r+");
	char buffer_fd_in[4096];
	size_t file_size = 0;
	file_size = fread(buffer_fd_in, 1, sizeof(buffer_fd_in), fin);
	int file_out = open(sc_main._args[2].str, O_WRONLY | O_CREAT, 0644);
	if (file_out == -1){
		printf("failed to open file out\n");
		exit(1);
	}
	char var_name_buff[1024];
	char var_len_buff[1024];
	char fmt_file_name[1024];
	for (u32 idx_file_name = 0; idx_file_name < sc_main._args[1].len; idx_file_name++){
		if (sc_main._args[1].str[idx_file_name] == '.'){
			fmt_file_name[idx_file_name] = '_';
			continue;
		}
		fmt_file_name[idx_file_name] = sc_main._args[1].str[idx_file_name];
	}
	fmt_file_name[sc_main._args[1].len] = '\0';
	printf("%s\n", fmt_file_name);
	fflush(stdout);
	u32 buff_len = snprintf(var_name_buff, sizeof(var_name_buff), (char *)"const unsigned char %s[] = {\n", fmt_file_name);
	try(write, (file_out, var_name_buff, buff_len), {
		perror("write");
	});
	for (u64 idx_in = 0; idx_in < file_size; idx_in++) {
	    unsigned char byte = buffer_fd_in[idx_in];

	    char buf[8];
	    int len = snprintf(buf, sizeof buf, "\t0x%02x,", byte);
	    try(write, (file_out, buf, len), {
		perror("write");
	    });

	    if ((idx_in + 1) % 12 == 0) {
		try(write, (file_out, "\n", 1),{
			perror("write");
		});
	    }
	}
	const char *footer = "\n};\n";
	try(write, (file_out, footer, sstrlenx(footer)),{
		perror("write");
	});

	u32 len_var_len = snprintf(
		var_len_buff,
		sizeof(var_len_buff),
		(char *)"\n\nconst unsigned int %s_len = %lu;\n\n", fmt_file_name, file_size
	);

	try(write, (file_out, var_len_buff, len_var_len), {
		perror("write");
	});
}


static void exec_asm(StormC_Main_Entry_Process sc_main)
{
	int ret, status;
	char cmd[1024];
	u32 len = snprintf(cmd, sizeof(cmd), "objdump -d -M intel ./%.*s > stormc_asm.log 2>&1", (int)sc_main._args[1].len, sc_main._args[1].str);
	cmd[len] = '\0';
	ret = system(cmd);
	status = __WEXITSTATUS(ret);
	if (ret == -1) perror("system");


}


// #define MAX_RSYNC_PATHS 4096
// #define MAX_RSYNC_PATH_HEADER 2048
// #define RSYNC_STACK_RSRV (1lu << 32)
// struct rsync_cmd_payload{
// 	struct stc_string8	path_in[MAX_RSYNC_PATHS];
// 	struct stc_string8	path_out[MAX_RSYNC_PATHS];
// 	u64			ct_paths;
// };
//
//
// static struct rsync_cmd_payload rsync_cmdpl = {0};
//
//
// static int visit(const char *path, const struct stat *st, int type, struct FTW *ftwbuf)
// {
// 	enum blacklist_types{GIT, EXAMPLES, SCRIPTS, TESTS, BLACKLIST_COUNT};
// 	struct stc_string8 blacklist[] = {
// 		[GIT]		= STR("/.git"),
// 		[EXAMPLES]	= STR("/examples"),
// 		[SCRIPTS]	= STR("/scripts"),
// 		[TESTS]		= STR("/tests")
// 	};
// 	struct stc_string8 needle = STR(".h");
// 	bool is_blacklisted;
// 	u64 path_len = sstrlenx(path);
// 	struct stc_string8 haystack = {.str = (char *)path, .len = path_len};
// 	for (u64 i = 0; i < BLACKLIST_COUNT; i++) {
// 		is_blacklisted = stormc_find_substr(haystack, blacklist[i]) >= 0;
// 		if (likely(is_blacklisted)) goto FINISH;
// 	}
// 	bool is_header = stormc_find_substr(haystack, STR(".h")) != -1;
// 	bool is_object = stormc_find_substr(haystack, STR(".o")) != -1;
// 	struct stc_string8 stormc_infix = STR("stormlibc/");
// 	struct stc_string8 stringed_path = {.str = (char *)path, .len = path_len};
// 	char buff_concat[MAX_RSYNC_PATH_HEADER];
// 	const char *prefix = "/usr/include/storm/";
// 	u8 prefix_len = sizeof("/usr/include/storm/") - 1;
// 	if (is_header) {
// 		struct stc_string8 stringed_path = {.str = (char *)path, .len = path_len};
// 		u64 len = stormc_find_substr(stringed_path, stormc_infix);
// 		struct stc_string8 dir = {
// 			.str = stringed_path.str + len + stormc_infix.len,
// 			.len = stringed_path.len - len - stormc_infix.len
// 		};
// 		__builtin_memcpy(buff_concat, prefix, prefix_len);
// 		__builtin_memcpy(buff_concat + prefix_len, dir.str, dir.len);
// 		u64 total_concat_len = prefix_len + dir.len;
// 		buff_concat[total_concat_len] = '\0';
// 		u64 next_fwslsh = stormc_find_substr(dir, STR("/"));
// 		struct stc_string8 dir_sliced = {
// 			.str = dir.str,
// 			.len = next_fwslsh
// 		};
// 		char concat_out_dir_sliced[2048];
// 		__builtin_memcpy(concat_out_dir_sliced, prefix, prefix_len);
// 		__builtin_memcpy(concat_out_dir_sliced + prefix_len, dir_sliced.str, dir_sliced.len);
// 		u64 len_cnct_dir_sliced = prefix_len + dir_sliced.len;
// 		concat_out_dir_sliced[len_cnct_dir_sliced] = '\0';
// 		if (unlikely(!file_exists(concat_out_dir_sliced))) {
// 			int ret = mkdir(concat_out_dir_sliced, 0755);
// 			if (unlikely(ret < 0)) {
// 				perror("mkdir");
// 				exit(1);
// 			}
// 		}
// 		dir.str = buff_concat;
// 		dir.len = prefix_len + dir.len;
// 		sstrcpyx(&rsync_cmdpl.path_in[rsync_cmdpl.ct_paths], &stringed_path);
// 		sstrcpyx(&rsync_cmdpl.path_out[rsync_cmdpl.ct_paths], &dir);
// 		// printf("IN:  \t%s\n", rsync_cmdpl.path_in[rsync_cmdpl.ct_paths].str);
// 		// printf("OUT: \t%s\n", rsync_cmdpl.path_out[rsync_cmdpl.ct_paths].str);
//
// 		rsync_cmdpl.ct_paths++;
// 	}
//
// FINISH:
// 	return 0;
// }

// static void exec_stclib_sync(StormC_Main_Entry_Process sc_main)
// {
// 	const char *path = "/data/2025-2026-projs/c-projs/stormlibc";
// 	if (!file_exists(path)) {
// 		printf("Stormlibc path needs updating!\n");
// 		exit(1);
// 	}
// 	printf("[OPENING] %s\n", path);
// 	struct stc_stack *stack = stc_stack_gen(RSYNC_STACK_RSRV);
// 	for (u64 i = 0; i < MAX_RSYNC_PATHS; i++) {
// 		rsync_cmdpl.path_in[i].str = stc_stack_push(stack, char, MAX_RSYNC_PATH_HEADER);
// 		rsync_cmdpl.path_out[i].str = stc_stack_push(stack, char, MAX_RSYNC_PATH_HEADER);
// 	}
// 	nftw(path, visit, 32, FTW_PHYS);
//
// 	const u64 max_len = rsync_cmdpl.ct_paths * MAX_RSYNC_PATH_HEADER;
//
// 	struct packed_fds{
// 		int fd_in[MAX_RSYNC_PATHS];
// 		int fd_out[MAX_RSYNC_PATHS];
// 		u32 ct_fds;
// 	};
// 	struct packed_fds fds = {0};
//
// 	struct stat st = {0};
// 	for (u64 i = 0; i < rsync_cmdpl.ct_paths; i++) {
// 		fds.fd_in[fds.ct_fds] = open(rsync_cmdpl.path_in[i].str, O_RDONLY);
// 		fds.fd_out[fds.ct_fds] = open(rsync_cmdpl.path_out[i].str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 		if(!(file_exists(rsync_cmdpl.path_in[i].str))) {
// 			printf("File does not exist %s\n", rsync_cmdpl.path_in[i].str);
// 			exit(1);
// 		}
// 		int ret = stat(rsync_cmdpl.path_in[i].str, &st);
// 		if (unlikely(ret < 0)) {
// 			perror("stat");
// 		}
// 		if (unlikely(fds.fd_in[fds.ct_fds] < 0)) {
// 			printf("Attempting to open: %s\n", rsync_cmdpl.path_in[i].str);
// 			perror("open");
// 		}
// 		if (unlikely(fds.fd_out[fds.ct_fds] < 0)) {
// 			printf("Attempting to open: %s\n", rsync_cmdpl.path_out[i].str);
// 			perror("open");
//
// 		}
//
// 		u64 copied = sendfile(fds.fd_out[fds.ct_fds], fds.fd_in[fds.ct_fds], 0, st.st_size);
// 		// printf("[COPYING] %s to %s\n",
// 		// 	rsync_cmdpl.path_in[i].str,
// 		// 	rsync_cmdpl.path_out[i].str
// 		// );
// 		if (copied < 0) {
// 			perror("sendfile");
// 		}
// 		fds.ct_fds++;
// 	}
//
// 	for (u64 i = 0; i < rsync_cmdpl.ct_paths; i++) {
// 		close(fds.fd_in[i]);
// 		close(fds.fd_out[i]);
// 	}
//
// }


// static void exec_stcbi(StormC_Main_Entry_Process s)
// {
// 	int fd = try_syscall(open, (s._args[1].str, O_RDONLY), {
// 		printf("%s\n", s._args[0].str);
// 		fflush(stdout);
// 		perror("open");
// 	});
//
// 	Elf64_Ehdr eh;
// 	pread(fd, &eh, sizeof(eh), 0);
// 	if (memcmp(eh.e_ident, ELFMAG, SELFMAG) != 0) return;
// 	if (eh.e_ident[EI_CLASS] != ELFCLASS64) return;
//
//
// 	size_t shdr_bytes = eh.e_shentsize * eh.e_shnum;
// 	Elf64_Shdr *shdrs = (Elf64_Shdr*)malloc(shdr_bytes);
// 	pread(fd, shdrs, shdr_bytes, eh.e_shoff);
//
//
// 	Elf64_Shdr shstr = shdrs[eh.e_shstrndx];
// 	char *shrstrtab = (char*)malloc(shstr.sh_size);
// 	pread(fd, shrstrtab, shstr.sh_size, shstr.sh_offset);
// 	Elf64_Shdr *target = NULL;
//
// 	for (Elf64_Half i = 0; i < eh.e_shnum; i++) {
// 		const char *name = shrstrtab + shdrs[i].sh_name;
// 		if (strcmp(name, ".stcbi") == 0) {
// 			target = &shdrs[i];
// 			break;
// 		}
// 	}
//
//
// 	if (!target) {
// 		fprintf(stderr, "Did not find .stcbi section\n");
// 		goto FINISH;
// 	}
//
// 	unsigned char *data = malloc(target->sh_size);
// 	pread(fd, data, target->sh_size,  target->sh_offset);
// 	struct stormc_buildinfo *bi = (struct stormc_buildinfo *)data;
//
// 	time_t tt = (time_t)bi->unix_time;
// 	struct tm tm = {0};
// 	localtime_r(&tt, &tm);
//
// 	char time_buf[64];
// 	strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", &tm);
//
// 	fprintf(stdout, "Compiler:\n%.*s\n", (int)bi->compiler_name_len, bi->compiler_name);
// 	fprintf(stdout, "%s\n", "---------------------------");
// 	fprintf(stdout, "Flags: ");
// 	char *flags = malloc(bi->flags_len * sizeof(char) + 1);
// 	strcpy(flags, bi->compiler_flags);
// 	flags[bi->flags_len] = '\0';
// 	fprintf(stdout, "%s", flags);
// 	fprintf(stdout, "%s\n", "---------------------------");
// 	fprintf(stdout, "Compiled Date(YYYY-MM-DD):\n%s\n", time_buf);
// 	fprintf(stdout, "%s\n", "---------------------------");
//
// FINISH:
//
// 	free(shdrs);
// 	free(data);
// 	try_syscall(close, (fd), {
// 		perror("close");
// 	});
//
// }




// RIP Terry
static void exec_uf(StormC_Main_Entry_Process s)
{
	int ret, status;
	char cmd[1024];
	u32 len = snprintf(cmd, sizeof(cmd),
	"gdb -batch -ex 'set disassembly-flavor intel' -ex 'disassemble %.*s' %.*s > stormc_asm_%.*s_%.*s.log 2>&1",
		    (int)s._args[2].len, s._args[2].str,
		    (int)s._args[1].len, s._args[1].str,
		    (int)s._args[1].len, s._args[1].str,
		    (int)s._args[2].len, s._args[2].str
		    );
	cmd[len] = '\0';
	ret = system(cmd);
	status = __WEXITSTATUS(ret);
	if (ret == -1) perror("system");

}

int main(int argc, char **argv)
{
	int ret;
	int status;
	StormC_Main_Entry_Process sc_main = {0};
	if (argc > 32) {
		printf("List of arguments is too long: %d\n", argc);
		exit(1);
	}

	while (sc_main.len < argc - 1){
		sc_main._args[sc_main.len] = STR_RUNTIME(argv[1 + sc_main.len]);
		sc_main.len++;
	}

	if (sstrcmpx(sc_main._args[0], G_COMMANDS[CTAGS]))		exec_ctags(sc_main);
	else if (sstrcmpx(sc_main._args[0], G_COMMANDS[INIT]))		exec_init(sc_main);
	else if(sstrcmpx(sc_main._args[0], G_COMMANDS[RUN]))		exec_run();
	else if (sstrcmpx(sc_main._args[0], G_COMMANDS[BUILD])) 	exec_build(sc_main);
	else if (sstrcmpx(sc_main._args[0], G_COMMANDS[EMBED])) 	exec_embed(sc_main);
	else if (sstrcmpx(sc_main._args[0], G_COMMANDS[ASM]))		exec_asm(sc_main);
	// else if (sstrcmpx(sc_main._args[0], G_COMMANDS[STCLIB_SYNC]))	exec_stclib_sync(sc_main);
	// else if (sstrcmpx(sc_main._args[0], G_COMMANDS[BUILDINFO]))	exec_stcbi(sc_main);
	else if (sstrcmpx(sc_main._args[0], G_COMMANDS[UF]))		exec_uf(sc_main);
	// else if (sstrcmpx(sc_main._args[0], G_COMMANDS[CODEGEN])){
	// 	if (file_exists(sc_main._args[1].str)) {
	// 		exec_codegen(sc_main._args[1].str);
	// 	} else {
	// 		fprintf(stderr, "File %.*s does not exist\nExiting\n", STRING_SIZED(sc_main._args[1]));
	// 	}
	//
	// }
	else {
		fprintf(stderr, "Unknown command: '%.*s'\n", (int)sc_main._args[0].len, sc_main._args[0].str);
	}

	return 0;
}
