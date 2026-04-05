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


#define STORMC_ERROR_FMT(_err_msg, _err_str) fprintf(stderr, _err_msg, (int)_err_str.len, _err_str.str)
#define STORMC_ERROR(_err_msg) fprintf(stderr, _err_msg)

#define STAG_USER_COMMANDS(ENTRY) \
	ENTRY(CTAGS,			"--ctags",		"-ct",		"run ctags",				"", true, ' ')\
	ENTRY(INIT,  			"init",    		"-i",  		"init project",				"", false, 0)\
	ENTRY(RUN,   			"run",     		"-r",  		"run build script",			"", false, 0)\
	ENTRY(BUILD, 			"build",   		"-b",  		"build target",				"", true, ' ')\
	ENTRY(EMBED, 			"embed",   		"-e",  		"embed file into c source",		"", true, ' ')\
	ENTRY(ASM,   			"asm",     		"-asm",		"dump asm",				"", true, ' ')\
	ENTRY(UF,    			"uf",      		"-uf", 		"disassemble function with gdb",	"", true, ' ')\
	ENTRY(REGISTER_PROJ_NAME,	"--register-proj",	"-rpn", 	"register project name",		"", true, '=')\
	ENTRY(REGISTER_PROJ_PATH,	"--register-proj-path",	"-rpp", 	"register project path",		"", true, '=')\
	ENTRY(PROJECT_ADD,		"add",			"-add", 	"add project to local dir",		"", true, ' ')\
	ENTRY(PROJECT_REMOVE,		"remove",		"-rm",		"remove local dir project",		"", true, ' ')\
	ENTRY(PROJECT_UPDATE,		"update",		"-update", 	"update project name for local path",	"", true, ' ')\
	ENTRY(LIST_PROJECTS,		"--list-projects",	"-lstp", 	"list projects",			"", false, 0)\
	ENTRY(GOTO_PROJ,		"goto",			"-g2p",		"go to project directory",		"", true, ' ')

#define STORMC_STAG
#define STORMC_ALLOCATOR
#define STORMC_STRING
#include "/data/2026-projs/c/stormlibc/stormc_header.h"
#include "stormc_buildsystem.h"
#include "defaults.h"



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
};

struct stormc_project_mapper {
	struct stag_string	config_file_location;


	struct stormc_config_payload	payload;
};


static struct stormc_project_mapper *stc_proj_mapper = NULL;



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
	[TEMPL_SCBUILD] = {.str = (char *)default_scbuild_c, .len = default_scbuild_c_len},
	[TEMPL_MAIN] = {.str = (char *)default_main_c, .len = default_main_c_len},
};


static int file_exists(const char *path)
{
	return access(path, F_OK) == 0;
}

static void exec_ctags(struct stag_string extra)
{
	char cmd[512] = {0};

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
	int ret = system("gcc -mavx2 scbuild.c -o scbuild && ./scbuild run");
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
		ret = system("gcc -mavx2 scbuild.c -o scbuild && ./scbuild build run");
	} else if (stag_strcmp(target, STAG_STR("asm"))) {
		ret = system("gcc -mavx2 scbuild.c -o scbuild && ./scbuild build asm");
	} else {
		char cmd[512];
		snprintf(cmd, sizeof(cmd),
			 "gcc -mavx2 scbuild.c -o scbuild && ./scbuild %.*s",
			 (int)target.len, target.str);
		ret = system(cmd);
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

	snprintf(in_path, sizeof(in_path), "%.*s", (int)in.len, in.str);
	snprintf(out_path, sizeof(out_path), "%.*s", (int)out.len, out.str);

	FILE *fin = fopen(in_path, "rb");
	if (!fin) {
		perror("fopen");
		exit(1);
	}

	unsigned char buffer_fd_in[4096];
	size_t file_size = fread(buffer_fd_in, 1, sizeof(buffer_fd_in), fin);
	fclose(fin);

	int file_out = open(out_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_out == -1) {
		perror("open");
		exit(1);
	}

	char var_name_buff[1024];
	char var_len_buff[1024];
	char fmt_file_name[1024];

	for (u32 i = 0; i < in.len && i < sizeof(fmt_file_name) - 1; ++i) {
		char c = in.str[i];
		fmt_file_name[i] = (c == '.') ? '_' : c;
	}
	fmt_file_name[in.len] = '\0';

	u32 buff_len = snprintf(var_name_buff, sizeof(var_name_buff),
				"const unsigned char %s[] = {\n", fmt_file_name);

	try(write, (file_out, var_name_buff, buff_len), {
		perror("write");
		exit(1);
	});

	for (u64 i = 0; i < file_size; ++i) {
		char buf[16];
		int len = snprintf(buf, sizeof(buf), "\t0x%02x,", buffer_fd_in[i]);
		try(write, (file_out, buf, len), {
			perror("write");
			exit(1);
		});

		if ((i + 1) % 12 == 0) {
			try(write, (file_out, "\n", 1), {
				perror("write");
				exit(1);
			});
		}
	}

	try(write, (file_out, "\n};\n", 4), {
		perror("write");
		exit(1);
	});

	u32 len_var_len = snprintf(var_len_buff, sizeof(var_len_buff),
				   "\nconst unsigned int %s_len = %lu;\n",
				   fmt_file_name, file_size);

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
		struct stag_string current = {.str = stc_proj_mapper->payload.projects[i].proj_path, .len = stc_proj_mapper->payload.projects[i].proj_path_len};
		if (stag_strcmp(proj_path, current)) {
			return true;
		}
	}
	return false;
}

stag_bool32 proj_exists(struct stag_string proj_name)
{
	for (u64 i = 0; i < stc_proj_mapper->payload.ct_projects; ++i) {
		struct stag_string current = {.str = stc_proj_mapper->payload.projects[i].proj_name, .len = stc_proj_mapper->payload.projects[i].proj_name_len};
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
	fprintf(stderr, "Missing project name\n");

}


void stormc_check_system(void)
{
	stc_proj_mapper = stc_alloc(sizeof(*stc_proj_mapper));
	stc_proj_mapper->config_file_location = DEFAULT_CONFIG_LOCATION;
	stc_proj_mapper->payload.magic = STORMC_CFG_META_MAGIC;
	stc_proj_mapper->payload.version = STORMC_CFG_META_VERSION;
	const char *home = getenv("HOME");
	if (!home) {
		fprintf(stderr, "Env variable HOME is not set\n");
		return;
	}
	char path[1024] = {0};
	snprintf(path, sizeof(path), "%s/.config/stormc/config.stc", home);
	char dir[1024] = {0};
	snprintf(dir, sizeof(dir), "%s/.config/stormc", home);
	mkdir(dir, 0755);

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
		fread(&stc_proj_mapper->payload, sizeof(stc_proj_mapper->payload), 1, f);
		fclose(f);
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
		struct stag_string current = {.str = stc_proj_mapper->payload.projects[i].proj_name, .len = stc_proj_mapper->payload.projects[i].proj_name_len};
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
	struct stag_string proj_path = get_project_path_from_name(proj_name);
	fprintf(stdout, "%.*s\n", (int)proj_path.len, proj_path.str);
}


void exec_add_proj(struct stag_array_string sarr)
{
	struct stag_string proj_name = sarr.strings[0];
	struct stag_string proj_path = sarr.strings[1];

	if (proj_name.len > 1024) {
		STORMC_ERROR_FMT("Project exceeds max length of 1024: %.*s\n", proj_name);
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
	struct stag_string old_name = sarr.strings[0];
	struct stag_string new_name = sarr.strings[1];
	for (u64 i = 0; i < stc_proj_mapper->payload.ct_projects; ++i) {
		struct stag_string current = {.str = stc_proj_mapper->payload.projects[i].proj_name, .len = stc_proj_mapper->payload.projects[i].proj_name_len};
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
		struct stag_string current = {.str = stc_proj_mapper->payload.projects[i].proj_name, .len = stc_proj_mapper->payload.projects[i].proj_name_len};
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



int main(int argc, char **argv)
{
	stormc_check_system();
	stag_run(argc, argv);

	stag_bool32 want_init  = false;
	stag_bool32 want_run   = false;
	stag_bool32 want_reg_proj = false;
	stag_bool32 want_list_proj = false;

	struct stag_string ctags_arg		= {0};
	struct stag_string build_arg 		= {0};
	struct stag_string embed_arg 		= {0};
	struct stag_string asm_arg   		= {0};
	struct stag_string uf_arg    		= {0};
	struct stag_string reg_proj_args	= {0};
	struct stag_string reg_proj_path	= {0};
	struct stag_string goto_proj		= {0};
	struct stag_array_string proj_add	= {0};
	struct stag_string proj_remove		= {0};
	struct stag_array_string proj_update	= {0};

	stag_bool32 running = true;
	while (running) {
		struct stag_cmd_array cmd = stag_next_cmd();

		switch (cmd.cmd) {
		default: break;
		case INIT:			want_init = true; break;
		case RUN:   			want_run = true; break;
		case CTAGS: 			ctags_arg = cmd.args; break;
		case BUILD: 			build_arg = cmd.args; break;
		case EMBED: 			embed_arg = cmd.args; break;
		case ASM:   			asm_arg = cmd.args; break;
		case UF:    			uf_arg = cmd.args; break;
		case LIST_PROJECTS:		want_list_proj = true; break;
		case GOTO_PROJ:			goto_proj = cmd.args; break;
		case PROJECT_ADD:
		{
			proj_add = stag_string_to_array_of_strings(cmd.args, '|');
			break;
		}
		case PROJECT_UPDATE:
		{
			proj_update = stag_string_to_array_of_strings(cmd.args, '|');
			break;
		}
		case PROJECT_REMOVE:
		{
			proj_remove = cmd.args;
			break;
		}
		case REGISTER_PROJ_NAME:
		{
			want_reg_proj = true;
			reg_proj_args = cmd.args;
			break;
		}
		case REGISTER_PROJ_PATH:
		{
			want_reg_proj = true;
			reg_proj_path = cmd.args;
			break;
		}
		case NIL:
			running = false;
			break;
		}
	}

	if (want_reg_proj)
		exec_reg_proj(reg_proj_args, reg_proj_path);


	if (want_init)
		exec_init();

	if (want_run)
		exec_run();

	if (ctags_arg.str)
		exec_ctags(ctags_arg);

	if (build_arg.str)
		exec_build(build_arg);

	if (embed_arg.str)
		exec_embed(embed_arg);

	if (asm_arg.str)
		exec_asm(asm_arg);

	if (uf_arg.str)
		exec_uf(uf_arg);

	if (want_list_proj)
		exec_list_projs();


	if (goto_proj.str) {
		exec_goto_dir(goto_proj);
	}


	if (proj_add.len == 2) {
		exec_add_proj(proj_add);
	}

	if (proj_update.len == 2) {
		exec_update_proj(proj_update);
	}

	if (proj_remove.str) {
		exec_remove_proj(proj_remove);
	}


	stormc_save_config();


	return 0;
}
