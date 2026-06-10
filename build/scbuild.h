#define STORMC_ALLOCATOR
#define STORMC_STRING
#define STORMC_MATH
#define STORMC_IO

#include "../stormc_header.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <inttypes.h>

#define MAX_INCLUDES 4096
#define MAX_FILES 1024
#define MAX_DIRS 1024




#define INCLUDE_FREETYPE_LINUX\
	set_libraries(STR("$(pkg-config --cflags --libs freetype2)"));


#define INCLUDE_FREETYPE_WINDOWS\
	set_library_paths(\
	    STR("-L" STORMC_ROOT "/third_party/mxe/usr/x86_64-w64-mingw32.static/lib")\
	);\
	set_include_paths(\
	    STR(STORMC_ROOT "/third_party/mxe/usr/x86_64-w64-mingw32.static/include/freetype2")\
	);\
	set_libraries(\
	    STR("-lfreetype"),\
	    STR("-lpng"),\
	    STR("-lbrotlidec"),\
	    STR("-lbrotlicommon"),\
	    STR("-lharfbuzz"),\
	    STR("-lz"),\
	    STR("-lbz2")\
	)

#define INCLUDE_SDL3_LINUX\
	set_libraries(STR("-lSDL3"), STR("-lSDL3_image"), STR("-lSDL3_ttf"))

#define INCLUDE_SDL3_WINDOWS\
		set_libraries(STR("-lSDL3"), STR("-lSDL3_image"), STR("-lSDL3_ttf"));\
		set_library_paths(\
		    STR("-L" STORMC_ROOT "/third_party/SDL3-3.4.2/x86_64-w64-mingw32/lib"),\
		    STR("-L" STORMC_ROOT "/third_party/SDL3-3.4.2/SDL3_ttf-3.2.2/x86_64-w64-mingw32/lib"),\
		    STR("-L" STORMC_ROOT "/third_party/SDL3-3.4.2/SDL3_image-3.4.0/x86_64-w64-mingw32/lib")\
		);\
		set_include_paths(\
		    STR(STORMC_ROOT "/third_party/SDL3-3.4.2/x86_64-w64-mingw32/include"),\
		    STR(STORMC_ROOT "/third_party/SDL3-3.4.2/SDL3_ttf-3.2.2/x86_64-w64-mingw32/include"),\
		    STR(STORMC_ROOT "/third_party/SDL3-3.4.2/SDL3_image-3.4.0/x86_64-w64-mingw32/include")\
		);\
	INCLUDE_FREETYPE_WINDOWS

#define INCLUDE_RAYLIB_LINUX\
	set_libraries(\
	    STR("-Wl,-rpath,'$ORIGIN'"),\
	    STR("-L" STORMC_ROOT "/third_party/raylib/zig-out/lib/"),\
	    STR("-lraylib -lm -lGL -lpthread -ldl")\
	    );\
	set_include_paths(\
	    STR(STORMC_ROOT "/third_party/raylib/zig-out/include")\
	    )

#define INCLUDE_RAYLIB_WINDOWS\
	set_libraries(\
	    STR("-Wl,-rpath,'$ORIGIN'"),\
	    STR("-L" STORMC_ROOT "/third_party/raylib/zig-out/lib/"),\
	    STR("-lraylib -lgdi32 -lopengl32 -lwinmm")\
	    );\
	set_include_paths(\
	    STR(STORMC_ROOT "/third_party/raylib/zig-out/include")\
	    )



#define INCLUDE_SGL_WINDOWS\
	INCLUDE_FREETYPE_WINDOWS;\
	INCLUDE_SDL3_WINDOWS


#define INCLUDE_SGL_LINUX\
	INCLUDE_FREETYPE_LINUX;\
	INCLUDE_SDL3_LINUX

#define STR_NULL (struct stc_string8){.str = NULL, .len = 0}
#ifndef STORMC_ROOT
#define STORMC_ROOT "."
#endif

#define ARRAY_LEN(x) (sizeof(x) / sizeof(*x))

#define GREEN		"\033[32m"
#define RED		"\033[31m"
#define RESET_COL	"\033[0m"

enum compilers{
	C_GCC,
	C_CLANG,
	C_ZIGCC,
	C_MINGW64,
	C_MINGW32,
	C_CLANGPP,
	C_GCCPP,
	C_MINGW64PP,
	C_MXE_MINGW64PP,
	CT_COMPILERS
};


static struct stc_string8  table_compilers[] = {
	[C_GCC] = STR("gcc"),
	[C_CLANG] = STR("clang"),
	[C_ZIGCC] = STR("zig cc"),
	[C_MINGW64] = STR("x86_64-w64-mingw32-gcc"),
	[C_MINGW32] = STR("i686-mingw32-gcc"),
	[C_CLANGPP] = STR("clang++"),
	[C_GCCPP] = STR("gcc++"),
	[C_MINGW64PP] = STR("x86_64-w64-mingw32-g++"),
	[C_MXE_MINGW64PP] = STR("x86_64-w64-mingw32.shared-g++"),
};

enum extension{
	XT_DOT_C,
	XT_DOT_H,
	XT_DOT_CPP,
	XT_DOT_STC,
	CT_EXTENSION
};

static struct stc_string8  table_extension[] = {
	[XT_DOT_C] = STR(".c"),
	[XT_DOT_H] = STR(".h"),
	[XT_DOT_CPP] = STR(".cpp"),
	[XT_DOT_STC] = STR(".stc"),
};



typedef i32 stcbld_t;

enum stcb_cmplr_flags{
	INVALID,
	OPTIM_0,
	OPTIM_1,
	OPTIM_2,
	OPTIM_3,
	OMP,

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
	STD_C23,
	STD_C2X,
	STD_C2Y,
	STD_GNU99,
	STD_GNU11,

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
	WCOMMA,
	WPAREN,
	WLOGICALOP,
	NOSTDLIB,
	NOSTARTFILES,
	NODEFAULTLIBS,
	ENTRYY_START,
	FNO_STACK_PROTECTOR,
	FALLTHROUGH,
	FALLTHROUGH1,
	FALLTHROUGH2,
	FALLTHROUGH3,
	FPERMISSIVE,
	NONARROWING,

	STORMC_COMMANDS_COUNT,
};


struct stc_string8 G_Commands_Map[STORMC_COMMANDS_COUNT] = {
	[INVALID]			= STR(""),
	[OPTIM_0] 			= STR("-O0"),
	[OPTIM_1] 			= STR("-O1"),
	[OPTIM_2] 			= STR("-O2"),
	[OPTIM_3] 			= STR("-O3"),

	[MARCH_SSE]			= STR("-msse"),
	[MARCH_SSE2]			= STR("-msse2"),
	[MARCH_SSE3] 			= STR("-msse3"),
	[MARCH_SSE4] 			= STR("-msse4"),
	[MARCH_SSE42]			= STR("-msse4.2"),
	[MARCH_AVX1]			= STR("-mavx1"),
	[MARCH_AVX2] 			= STR("-mavx2"),
	[MARCH_NATIVE]			= STR("-march=native"),

	[STD_C89]			= STR("-std=c89"),
	[STD_C99]			= STR("-std=c99"),
	[STD_C23] 			= STR("-std=c23"),
	[STD_C2X] 			= STR("-std=c2x"),
	[STD_C2Y] 			= STR("-std=c2y"),
	[STD_GNU99] 			= STR("-std=gnu99"),
	[STD_GNU11] 			= STR("-std=gnu11"),

	[STD_CPP98]			= STR("-std=c++98"),
	[STD_CPP03] 			= STR("-std=c++03"),
	[STD_CPP11] 			= STR("-std=c++11"),
	[STD_CPP14] 			= STR("-std=c++14"),
	[STD_CPP17] 			= STR("-std=c++17"),
	[STD_CPP20] 			= STR("-std=c++20"),
	[STD_CPP23] 			= STR("-std=c++23"),

	[ASAN]				= STR("-fsanitize=address"),
	[LSAN]   			= STR("-fsanitize=leak"),
	[UBSAN]  			= STR("-fsanitize=undefined"),
	[TSAN]   			= STR("-fsanitize=thread"),
	[MEMSAN] 			= STR("-fsanitize=memory"),
	[ALLSAN] 			= STR("-fsanitize=address,leak,undefined"),

	[OMP]				= STR("-fopenmp"),
	[WALL]				= STR("-Wall"),
	[WPEDANTIC] 			= STR("-Wpedantic"),
	[WERROR]    			= STR("-Werror"),
	[WEXTRA]    			= STR("-Wextra"),
	[WPAREN]    			= STR("-Wparentheses"),
	[WLOGICALOP]			= STR("-Wlogical-op"),
	[WCOMMA]			= STR("-Wcomma"),
	[NOSTDLIB]			= STR("-nostdlib"),
	[NOSTARTFILES]			= STR("-nostartfiles"),
	[NODEFAULTLIBS]			= STR("-nodefaultlibs"),
	[ENTRYY_START]			= STR("-Wl,-e,_start"),
	[FNO_STACK_PROTECTOR]		= STR("-fno-stack-protector"),
	[FALLTHROUGH]			= STR("-Wimplicit-fallthrough"),
	[FALLTHROUGH1]			= STR("-Wimplicit-fallthrough=1"),
	[FALLTHROUGH2]			= STR("-Wimplicit-fallthrough=2"),
	[FALLTHROUGH3]			= STR("-Wimplicit-fallthrough=3"),
	[FPERMISSIVE]			= STR("-fpermissive"),
	[NONARROWING]			= STR("-Wno-c++11-narrowing"),
};


struct dir_flags{
	enum stcb_cmplr_flags		flags[128];
};


typedef enum{
	RUN,
	BUILD,
	G_COMMAND_TYPES_COUNT,
}G_Command_Types;

struct stc_string8 G_COMMANDS[G_COMMAND_TYPES_COUNT] = {
	[RUN] = STR("run"),
	[BUILD] = STR("build"),
};

#define BUILD(builds)\
	u32 len = ARRAY_LEN(builds);\
	stormc_build_packed(builds, len)

#define SET_FLAGS(...)\
	(enum stcb_cmplr_flags[]){__VA_ARGS__, INVALID}

#define SET_LIBS(...)\
	(struct stc_string8[]){__VA_ARGS__, STR_NULL}


#define SET_EXTRAS(...)\
	(struct stc_string8[]){__VA_ARGS__, STR_NULL}

#ifdef STC_EMIT_BUILD_META
#define SET_SOURCES(...)\
		__VA_ARGS__, STR(BUILDINFO_FILENAME), STR_NULL
#else
#define SET_SOURCES(...)\
		__VA_ARGS__, STR_NULL
#endif


#define SET_DIRS(...) \
	__VA_ARGS__, STR_NULL

#define SET_INCLUDE_PATHS(...)\
	(struct stc_string8[]){__VA_ARGS__, STR_NULL}



#define IS_RUN_AFTER_BUILD(argc, argv) \
    (((argc) > 1 && sstrcmpx(STR("run"), make_string((argv)[1]))) || \
     ((argc) > 2 && sstrcmpx(STR("run"), make_string((argv)[2]))))


#define MAX_SOURCES 64
#define MAX_INCLUDE_PATHS 64
#define MAX_OBJECTS 64
#define MAX_LIBRARIES 64
#define MAX_FLAGS 128

enum stcb_extra_capabilities{
	STCB_EXTRA_NIL = 0,
	STCB_EXTRA_RUN_AFTER_BUILD,
	STCB_EXTRA_EMIT_DEBUG_SYMBOLS,
	STCB_EXTRA_CAPABILITIES_CT
};

struct proj{
	enum compilers		compiler;
	struct stc_string8	out;

	struct stc_string8	sources[MAX_SOURCES];
	u64			ct_sources;

	u64			compiler_flags[MAX_SOURCES];
	u64			ct_compiler_flags;

	struct stc_string8	include_paths[MAX_INCLUDE_PATHS];
	u64			ct_include_paths;


	struct stc_string8	library_paths[MAX_INCLUDE_PATHS];
	u64			ct_library_paths;

	struct stc_string8	libraries[MAX_INCLUDE_PATHS];
	u64			ct_libraries;

	struct stc_string8	objects[MAX_INCLUDE_PATHS];
	u64			ct_objects;

	enum stcb_extra_capabilities	extras[STCB_EXTRA_CAPABILITIES_CT];
	u64				ct_extras;

	bool	emit_symbols;
};

struct proj proj = {};



void _set_sources(struct stc_string8 *s)
{
	struct stc_string8 *start = s;
	while (start->str != NULL) {
		proj.sources[proj.ct_sources++] = *start;
		start++;
	}
}

#define set_sources(...)\
	_set_sources((struct stc_string8[]){__VA_ARGS__, STRING8_NULL})



void _set_library_paths(struct stc_string8 *s)
{
	struct stc_string8 *start = s;
	while (start->str != NULL) {
		proj.library_paths[proj.ct_library_paths++] = *start;
		start++;
	}
}

#define set_library_paths(...)\
	_set_library_paths((struct stc_string8[]){__VA_ARGS__, STRING8_NULL})

void _set_objects(struct stc_string8 *s)
{
	struct stc_string8 *start = s;
	while (start->str != NULL) {
		proj.objects[proj.ct_objects++] = *start;
		start++;
	}
}


#define set_include_paths(...)\
	_set_include_paths((struct stc_string8[]){__VA_ARGS__, STRING8_NULL})

void _set_include_paths(struct stc_string8 *s)
{
	struct stc_string8 *start = s;
	while (start->str != NULL) {
		proj.include_paths[proj.ct_include_paths++] = *start;
		start++;
	}
}


#define set_libraries(...)\
	_set_libraries((struct stc_string8[]){__VA_ARGS__, STRING8_NULL})

void _set_libraries(struct stc_string8 *s)
{
	struct stc_string8 *start = s;
	while (start->str != NULL) {
		proj.libraries[proj.ct_libraries++] = *start;
		start++;
	}
}

#define set_objects(...)\
	_set_objects((struct stc_string8[]){__VA_ARGS__, STRING8_NULL})

void _set_flags(enum stcb_cmplr_flags *f)
{
	enum stcb_cmplr_flags *start = f;
	while (*start != INVALID) {
		proj.compiler_flags[proj.ct_compiler_flags++] = *start;
		// printf("%s\n", G_Commands_Map[*start].str);
		start++;
	}
}

#define set_flags(...)\
	_set_flags((enum stcb_cmplr_flags[]){__VA_ARGS__, INVALID})

void set_out_file(struct stc_string8 out)
{
	proj.out = out;
}


void build_proj()
{
	u8 cmd[4096];
	u64 off = 0;

	off += snprintf(
		(u8*)(cmd + off), sizeof(cmd) - off,
		"%s ",
		table_compilers[proj.compiler].str
	);

	off += snprintf(
	    (u8 *)(cmd + off), sizeof(cmd) - off,
	    "-DSTORMC_ROOT='\"%s\"' ",
	    STORMC_ROOT
	);

	for (u64 i = 0; i < proj.ct_compiler_flags; ++i) {
		off += snprintf(
		    (u8*)(cmd + off), sizeof(cmd) - off,
		    "%s ",
		    G_Commands_Map[proj.compiler_flags[i]].str
		    );
	}

	for (u64 i = 0; i < proj.ct_include_paths; ++i) {
		off += snprintf(
		    (u8*)(cmd + off), sizeof(cmd) - off,
		    "-I\"%s\" ",
		    proj.include_paths[i].str
		    );
	}

	for (u64 i = 0; i < proj.ct_sources; ++i) {
		off += snprintf(
			(u8*)(cmd + off), sizeof(cmd) - off,
			"%s ",
			proj.sources[i].str
		);
	}


	for (u64 i = 0; i < proj.ct_library_paths; ++i) {
		off += snprintf(
			(u8*)(cmd + off), sizeof(cmd) - off,
			"%s ",
			proj.library_paths[i].str
		);
	}

	for (u64 i = 0; i < proj.ct_objects; ++i) {
		off += snprintf(
			(u8*)(cmd + off), sizeof(cmd) - off,
			"%s ",
			proj.objects[i].str
		);
	}

	for (u64 i = 0; i < proj.ct_libraries; ++i) {
		off += snprintf(
			(u8*)(cmd + off), sizeof(cmd) - off,
			"%s ",
			proj.libraries[i].str
		);
	}



	if (proj.emit_symbols) {
		off += snprintf(
			(u8*)(cmd + off), sizeof(cmd) - off, "-g "
		);

	}

	off += snprintf(
		(u8*)(cmd + off), sizeof(cmd) - off,
		"-o %s",
		proj.out.str
	);



	// off += snprintf(
	//     (u8*)(cmd + off), sizeof(cmd) - off,
	//     " 2> build.err"
	//     );

	cmd[off] = '\0';

	printf("%s\n", cmd);

	system(cmd);
}





