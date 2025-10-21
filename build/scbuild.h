#pragma once
#include "stormc_buildsystem.h"
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


#define GREEN		"\033[32m"
#define RED		"\033[31m"
#define RESET_COL	"\033[0m"

#define STR(s) ((String){.str = s, .len = sizeof(s) - 1})

#define SET_COMPILER(name) (build.compiler = STR(name))

#define SET_FLAGS(...) \
	do{ \
		StormC_Commands cmds[] = {__VA_ARGS__, INVALID}; \
		set_flags(cmds); \
	}while(0)\

#define SET_LINK_PATH(...) \
	do{ \
		char *cmds[] = {__VA_ARGS__, NULL}; \
		set_link_path(cmds); \
	}while(0)\

#define SET_LINKED_FILES(...) \
	do{ \
		char *cmds[] = {__VA_ARGS__, NULL}; \
		set_linked_files(cmds); \
	}while(0)\

typedef struct{
	String		_args[32];
	u32		len;
}StormC_Main_Entry_Process;


typedef enum{
	INVALID,
	OPTIM_0,
	OPTIM_1,
	OPTIM_2,
	OPTIM_3,

	MARCH_SSE,
	MARCH_SSE2,
	MARCH_SSE3,
	MARCH_SSE4,
	MARCH_SSE42,
	MARCH_AVX1,
	MARCH_AVX2,
	MARCH_NATIVE,

	STD_C89,
	STD_C99,
	STD_C2X,

	STD_CPP98,
	STD_CPP03,
	STD_CPP11,
	STD_CPP14,
	STD_CPP17,
	STD_CPP20,
	STD_CPP23,

	ASAN,
	LSAN,
	UBSAN,
	TSAN,
	MEMSAN,
	ALLSAN,

	WALL,
	WEXTRA,
	WERROR,
	WPEDANTIC,
	STORMC_COMMANDS_COUNT,
}StormC_Commands;


String G_Commands_Map[STORMC_COMMANDS_COUNT] = {
	[INVALID] = STR(""),
	[OPTIM_0] = STR("-O0"),
	[OPTIM_1] = STR("-O1"),
	[OPTIM_2] = STR("-O2"),
	[OPTIM_3] = STR("-O3"),

	[MARCH_SSE] = STR("-msse"),
	[MARCH_SSE2] = STR("-msse2"),
	[MARCH_SSE3] = STR("-msse3"),
	[MARCH_SSE4] = STR("-msse4"),
	[MARCH_SSE42] = STR("-msse4.2"),
	[MARCH_AVX1] = STR("-mavx1"),
	[MARCH_AVX2] = STR("-mavx2"),
	[MARCH_NATIVE] = STR("-march=native"),

	[STD_C89] = STR("-std=c89"),
	[STD_C99] = STR("-std=c99"),
	[STD_C2X] = STR("-std=c2x"),

  [STD_CPP98] = STR("-std=c++98"),
	[STD_CPP03] = STR("-std=c++03"),
	[STD_CPP11] = STR("-std=c++11"),
	[STD_CPP14] = STR("-std=c++14"),
	[STD_CPP17] = STR("-std=c++17"),
	[STD_CPP20] = STR("-std=c++20"),
	[STD_CPP23] = STR("-std=c++23"),

	[ASAN]   =  STR("address"),
	[LSAN]   =  STR("leak"),
	[UBSAN]  =  STR("undefined"),
	[TSAN]   =  STR("thread"),
	[MEMSAN] =  STR("memory"),

	[WALL]      =STR("-Wall"),
	[WPEDANTIC] =STR("-Wpedantic"),
	[WERROR]    =STR("-Werror"),
	[WEXTRA]    =STR("-Wextra"),
};

typedef struct{
	String		in;
	String		out;

	String		compiler;

	StormC_Commands optimization;
	StormC_Commands version_std;
	StormC_Commands march;

	StormC_Commands warnings[16];
	u32		warnings_count;

	StormC_Commands fsan[16];
	u32		fsan_count;

	String		link_pathname;

	String		link_filenames[64];
	u32		link_filenames_count;


}StormC_Build;

StormC_Build build = {
	.optimization = INVALID,
	.version_std = INVALID,
	.march = INVALID,
	.warnings = {INVALID},
	.warnings_count = 0,
	.compiler = STR("clang"),
};


typedef struct{
	char **files;
}Stormc_Linked_Files;




static String *emit_file_names(char **filenames)
{
	String *pl = (String *)malloc(69);
	return pl;
}


typedef enum{
	RUN,
	BUILD,
	G_COMMAND_TYPES_COUNT,
}G_Command_Types;

String G_COMMANDS[G_COMMAND_TYPES_COUNT] = {
	[RUN] = STR("run"),
	[BUILD] = STR("build"),
};


static void stormc_build(int argc, char *argv[])
{
	u32 idx, cmd_count;

	cmd_count = 0;
	char path[256];
	snprintf(path, sizeof(path), "./%s", build.out.str);
	char *_cmd_run[] = {path, NULL};

	String cmds[16];

	while(cmd_count < argc) {
		cmds[cmd_count] = make_string(argv[cmd_count]);
		cmd_count++;
	}

	bool cmd_is_run = sstrcmpx(cmds[1], G_COMMANDS[RUN]);
	bool cmd_is_build = sstrcmpx(cmds[1], G_COMMANDS[BUILD]);
	bool cmd_is_build_run = cmd_is_build && sstrcmpx(cmds[2], G_COMMANDS[RUN]);

	u32 _cmd_build_count = 0;
	char *_cmd_build[128];

	if (build.compiler.len > 0) {
		_cmd_build[_cmd_build_count++] = build.compiler.str;
	} else {
		build.compiler = make_string("gcc");
	}


	if (G_Commands_Map[build.march].len > 0){
		_cmd_build[_cmd_build_count++] = G_Commands_Map[build.march].str;
	}

	if (G_Commands_Map[build.optimization].len > 0){
		_cmd_build[_cmd_build_count++] = G_Commands_Map[build.optimization].str;
	}

	if (G_Commands_Map[build.version_std].len > 0){
		_cmd_build[_cmd_build_count++] = G_Commands_Map[build.version_std].str;
	}

	for (idx = 0; idx < build.warnings_count; idx++){
		_cmd_build[_cmd_build_count++] = G_Commands_Map[build.warnings[idx]].str;
	}

	if (build.fsan_count > 0){
		char fsan_buf[256];
		size_t fsan_off = 0;
		if(build.fsan[0] == ALLSAN){
			snprintf(fsan_buf, sizeof(fsan_buf),
      "-fsanitize=%s,%s,%s",
			G_Commands_Map[ASAN].str,
			G_Commands_Map[LSAN].str,
			G_Commands_Map[UBSAN].str
			);
		} else {
			fsan_off += snprintf(fsan_buf, sizeof(fsan_buf), "-fsanitize=%s", G_Commands_Map[build.fsan[0]].str);
			for (idx = 0; idx < build.fsan_count; idx++){
				fsan_off += snprintf(fsan_buf + fsan_off, sizeof(fsan_buf) - fsan_off, ",%s",
				G_Commands_Map[build.fsan[idx]].str);
			}
		}
		_cmd_build[_cmd_build_count++] = fsan_buf;
	}


	if(build.link_pathname.str != NULL && build.link_pathname.str[0] != '\0'){
		_cmd_build[_cmd_build_count++] = build.link_pathname.str;
	}
	_cmd_build[_cmd_build_count++] = build.in.str;
	_cmd_build[_cmd_build_count++] = (char *)"-o";
	_cmd_build[_cmd_build_count++] = build.out.str;

	for (idx = 0; idx < build.link_filenames_count; idx++){
		_cmd_build[_cmd_build_count++] = build.link_filenames[idx].str;
	}

	_cmd_build[_cmd_build_count] = NULL;

	pid_t pid;
	int status;

	struct timespec start, end;
	printf("cmd build[0]: %s\n", _cmd_build[0]);
	printf("cmd build[1]: %s\n", _cmd_build[1]);
	printf("cmd build[2]: %s\n", _cmd_build[2]);
	if(cmd_is_build_run){
		clock_gettime(CLOCK_MONOTONIC, &start);
		printf(GREEN "[BUILDING] %s -> %s\n" RESET_COL, build.in.str, build.out.str);

		pid = fork();
		if (pid == 0){
			execvp(_cmd_build[0], _cmd_build);
			fprintf(stderr, "failed command %s\n", _cmd_build[0]);
			exit(EXIT_FAILURE);
		}

		waitpid(pid, &status, 0);

		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0){
			fprintf(stderr, RED "[BUILD FAILED]" RESET_COL "\n");
			fprintf(stderr, "failed command %s (exit code %d)\n",
				_cmd_build[0], WEXITSTATUS(status));
			exit(EXIT_FAILURE);
		}

		clock_gettime(CLOCK_MONOTONIC, &end);
		f64 ms = (end.tv_sec - start.tv_sec) * 1e3 +
			 (end.tv_nsec - start.tv_nsec) / 1e6;

		printf(GREEN "[BUILD COMPLETE] %.2f ms\n" RESET_COL, ms);

		printf(GREEN "[RUNNING] %s\n" RESET_COL, build.out.str);

		execvp(_cmd_run[0], _cmd_run);
		fprintf(stderr, RED "[BUILD FAILED]" RESET_COL "\n");
		fprintf(stderr, "failed command %s (exit code %d)\n",
			    _cmd_build[0], WEXITSTATUS(status));
		exit(EXIT_FAILURE);
	}

	if(cmd_is_run){
		printf(GREEN "[RUNNING] %s\n" RESET_COL, build.out.str);
		execvp(_cmd_run[0], _cmd_run);


		fprintf(stderr, RED "[RUN FAILED]" RESET_COL "\n");
		fprintf(stderr, "failed command %s (exit code %d)\n",
			    _cmd_build[0], WEXITSTATUS(status));
		exit(EXIT_FAILURE);
	}

	else if(cmd_is_build){
		clock_gettime(CLOCK_MONOTONIC, &start);
		printf(GREEN "[BUILDING] %s -> %s\n" RESET_COL, build.in.str, build.out.str);

		pid = fork();
		if (pid == 0){
			execvp(_cmd_build[0], _cmd_build);
			fprintf(stderr, RED "[BUILD FAILED]" RESET_COL "\n");
			fprintf(stderr, "failed command %s\n", _cmd_build[0]);
			exit(EXIT_FAILURE);

		}

		waitpid(pid, &status, 0);
		clock_gettime(CLOCK_MONOTONIC, &end);
		f64 ms = (end.tv_sec - start.tv_sec) * 1e3 +
			(end.tv_nsec - start.tv_nsec) / 1e6;

		printf(GREEN "[BUILD COMPLETE] %.2f ms\n" RESET_COL, ms);
	}

}



static void set_flags(StormC_Commands commands[])
{
	u32 cmd_count = 0;
MAIN:
	switch(commands[cmd_count]){
	default: __builtin_unreachable();
	case INVALID: return;
	case STD_C89:
	case STD_C99:
	case STD_C2X:
  case STD_CPP98:
	case STD_CPP03:
	case STD_CPP11:
	case STD_CPP14:
	case STD_CPP17:
	case STD_CPP20:
	case STD_CPP23:
		build.version_std = commands[cmd_count];
		goto LOOP;

	case OPTIM_0:
	case OPTIM_1:
	case OPTIM_2:
	case OPTIM_3:
		build.optimization = commands[cmd_count];
		goto LOOP;

	case MARCH_AVX2:
	case MARCH_AVX1:
	case MARCH_SSE:
		build.march = commands[cmd_count];
		goto LOOP;

	case ASAN:
	case LSAN:
	case UBSAN:
	case ALLSAN:
		build.fsan[build.fsan_count++] = commands[cmd_count];
		goto LOOP;

	case WALL:
	case WPEDANTIC:
	case WERROR:
		build.warnings[build.warnings_count++] = commands[cmd_count];
	}

LOOP:
	cmd_count++;
	goto MAIN;
}

static void set_link_path(char *link_path[])
{
	build.link_pathname.str = link_path[0];
}

static void set_linked_files(char *linked_files[])
{
	while (linked_files[++build.link_filenames_count]);

	u32 idx;
	for (idx = 0; idx < build.link_filenames_count; idx++){
		build.link_filenames[idx].str = linked_files[idx];
	}
}
