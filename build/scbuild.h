// #include "/data/stormlibc/core/stormc_types.h"
// #include "stc_utils.h"

#define STORMC_ALLOCATOR
#define STORMC_STRING

#include "/data/2026-projs/c/stormlibc/stormc_header.h"
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



#define STR_NULL (struct stc_string8){.str = NULL, .len = 0}

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

#define STRING8_NULL (struct stc_string8){.str = NULL, .len = 0}


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
		    "-I/%s ",
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

	cmd[off] = '\0';
	printf(GREEN"%s\n"RESET_COL, cmd);


	system(cmd);
}



#define STC_CODEGEN_ARRAY_INIT_TEMPLATE(__type_prefix)\
	"\n"\
	"static struct array_%.*s *stc_array_%.*s_emit(u64 reserve_size, u64 init_size)\n"\
	"{\n"\
	"\tstruct array_%.*s *pl;\n"\
	"\tinit_size = STC_ALIGN_UP(sizeof(*pl) + init_size, PAGESIZE);\n"\
	"\tu8 *block = (u8 *)stc_os_mem_rsrv(reserve_size + sizeof(*pl));\n"\
	"\tstc_os_mem_cmt(block, init_size);\n"\
	"\tpl = (struct array_%.*s *)block;\n"\
	"\tpl->ptr = (" __type_prefix "%.*s *)((u64)block + sizeof(*pl));\n"\
	"\tpl->mem_reserved = reserve_size;\n"\
	"\tpl->mem_committed = init_size;\n"\
	"\treturn pl;\n"\
	"}\n"



#define STC_CODEGEN_ARRAY_PUSH_TEMPLATE(__type_prefix)\
	"\n"\
	"static void stc_array_%.*s_push(struct array_%.*s *a, u64 count)\n"\
	"{\n"\
	"\tu64 next_count = a->len + count;\n"\
	"\tu64 size_in_bytes = next_count * sizeof(*a->ptr);\n"\
	"\tif (size_in_bytes > a->mem_committed) {\n"\
	"\t\tu64 delta = STC_ALIGN_UP(size_in_bytes - a->mem_committed, PAGESIZE);\n"\
	"\t\tstc_os_mem_cmt((u8*)a->ptr + a->mem_committed, delta);\n"\
	"\t\ta->mem_committed += delta;\n"\
	"\t}\n"\
	"}\n"



#define STC_CODEGEN_ARRAY_APPEND_TEMPLATE(__type_prefix)\
	"\n"\
	"static void stc_array_%.*s_append(struct array_%.*s *a, "__type_prefix"%.*s element)\n"\
	"{\n"\
	"\tu64 cur_max_elements = a->mem_committed / sizeof(*a->ptr);\n"\
	"\tif (cur_max_elements < (a->len + 1))\n"\
	"\t\tstc_array_%.*s_push(a, 1);\n"\
	"\ta->ptr[a->len] = element;\n"\
	"\ta->len++;\n"\
	"}\n"



#define STC_CODEGEN_ARRAY_SHRINK_TEMPLATE(__type_prefix)\
	"\n"\
	"static void stc_array_%.*s_shrink(struct array_%.*s *a, u64 count)\n"\
	"{\n"\
	"\tu64 new_len = (count >= a->len) ? 0 : (a->len - count);\n"\
	"\ta->len = new_len;\n"\
	"}\n"

#define STC_CODEGEN_ARRAY_TOP_TEMPLATE(__type_prefix)\
	"\n"\
	"static "__type_prefix"%.*s stc_array_%.*s_top(struct array_%.*s *a)\n"\
	"{\n"\
	"\treturn a->ptr[a->len - 1];\n"\
	"}\n"

#define STC_CODEGEN_ARRAY_STRUCT_INIT_TEMPLATE    STC_CODEGEN_ARRAY_INIT_TEMPLATE("struct ")
#define STC_CODEGEN_ARRAY_PRIMITIVE_INIT_TEMPLATE STC_CODEGEN_ARRAY_INIT_TEMPLATE("")
#define STC_CODEGEN_ARRAY_STRUCT_PUSH_TEMPLATE    STC_CODEGEN_ARRAY_PUSH_TEMPLATE("struct ")
#define STC_CODEGEN_ARRAY_PRIMITIVE_PUSH_TEMPLATE STC_CODEGEN_ARRAY_PUSH_TEMPLATE("")
#define STC_CODEGEN_ARRAY_STRUCT_APPEND_TEMPLATE    STC_CODEGEN_ARRAY_APPEND_TEMPLATE("struct ")
#define STC_CODEGEN_ARRAY_PRIMITIVE_APPEND_TEMPLATE STC_CODEGEN_ARRAY_APPEND_TEMPLATE("")
#define STC_CODEGEN_ARRAY_STRUCT_SHRINK_TEMPLATE    STC_CODEGEN_ARRAY_SHRINK_TEMPLATE("struct ")
#define STC_CODEGEN_ARRAY_PRIMITIVE_SHRINK_TEMPLATE STC_CODEGEN_ARRAY_SHRINK_TEMPLATE("")
#define STC_CODEGEN_ARRAY_STRUCT_TOP_TEMPLATE    STC_CODEGEN_ARRAY_TOP_TEMPLATE("struct ")
#define STC_CODEGEN_ARRAY_PRIMITIVE_TOP_TEMPLATE STC_CODEGEN_ARRAY_TOP_TEMPLATE("")





#define MAX_LAYOUTS 4096
#define INIT_SIZE (1 << 24)

#define stc_codegen_layout(...)\
	stc_codegen_layout_new((struct codegen_struct_layout){__VA_ARGS__})


enum codegen_type{
	CODEGEN_ARRAY_STRUCT,
	CODEGEN_ARRAY_PRIMITIVE,
	CODEGEN_TYPE_CT
};


struct codegen_struct_layout{
	struct stc_string8	struct_name;
	struct stc_string8	struct_field_type;
	struct stc_string8	struct_field_name;
	enum codegen_type	codegen_type;
};

struct codegen{
	struct stc_string8    in;
	struct stc_string8    out;
	u8            *codegen_start;
	u8            *codegen_end;
};
struct codegen c = {0};
struct codegen_struct_layout layouts[MAX_LAYOUTS];
static u64 ct_layouts;



void stc_codegen_layout_new(struct codegen_struct_layout layout)
{
	layouts[ct_layouts++] = layout;
}




static void stc_codegen_make_array_primitive(struct codegen_struct_layout *l)
{
	struct stc_arena_string8 a = stc_arena_string8_init(2048);
	stc_arena_string8_push(&a, 1024);

	c.out.len += snprintf(c.out.str + c.out.len, INIT_SIZE, "struct array_%.*s {\n", stc_string8_sized(l->struct_name));
	c.out.len += snprintf(c.out.str + c.out.len, INIT_SIZE, "\t%.*s\t*ptr;\n", stc_string8_sized(l->struct_name));
	c.out.len += snprintf(c.out.str + c.out.len, INIT_SIZE, "\tu64\tlen;\n");
	c.out.len += snprintf(c.out.str + c.out.len, INIT_SIZE, "\tu64\tmem_committed;\n");
	c.out.len += snprintf(c.out.str + c.out.len, INIT_SIZE, "\tu64\tmem_reserved;\n");
	c.out.len += snprintf(c.out.str + c.out.len, INIT_SIZE, "};\n");

	c.out.len += snprintf(c.out.str + c.out.len, INIT_SIZE, "\n");

	c.out.len += snprintf(
		c.out.str + c.out.len,
		INIT_SIZE,
		STC_CODEGEN_ARRAY_PRIMITIVE_INIT_TEMPLATE,
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name)
	    );

	c.out.len += snprintf(
		c.out.str + c.out.len,
		INIT_SIZE,
		STC_CODEGEN_ARRAY_PRIMITIVE_PUSH_TEMPLATE,
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name)
	    );


	c.out.len += snprintf(
		c.out.str + c.out.len,
		INIT_SIZE,
		STC_CODEGEN_ARRAY_PRIMITIVE_APPEND_TEMPLATE,
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name)
	    );

	c.out.len += snprintf(
		c.out.str + c.out.len,
		INIT_SIZE,
		STC_CODEGEN_ARRAY_PRIMITIVE_SHRINK_TEMPLATE,
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name)
	    );

	c.out.len += snprintf(
		c.out.str + c.out.len,
		INIT_SIZE,
		STC_CODEGEN_ARRAY_PRIMITIVE_TOP_TEMPLATE,
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name)
	    );
}

static void stc_codegen_make_array_struct(struct codegen_struct_layout *l)
{
	struct stc_arena_string8 a = stc_arena_string8_init(2048);
	stc_arena_string8_push(&a, 1024);

	struct stc_string8_split split_field_types = stc_string8_split(&a, &l->struct_field_type, ';');
	struct stc_string8_split split_field_names = stc_string8_split(&a, &l->struct_field_name, ';');

	if (split_field_types.ct_strings != split_field_names.ct_strings) {
		printf("Field types count do not match with field names count\n");
		exit(1);
	}


	c.out.len += snprintf(c.out.str + c.out.len, INIT_SIZE, "struct %.*s {\n", stc_string8_sized(l->struct_name));

	for (int i = 0; i < split_field_types.ct_strings; ++i) {
		c.out.len += snprintf(
		    c.out.str + c.out.len, INIT_SIZE,
		    "\t%.*s\t%.*s;\n",
		    stc_string8_sized(split_field_types.strings[i]),
		    stc_string8_sized(split_field_names.strings[i])
		    );
	}

	c.out.len += snprintf(c.out.str + c.out.len, INIT_SIZE, "};\n");


	c.out.len += snprintf(c.out.str + c.out.len, INIT_SIZE, "struct array_%.*s {\n", stc_string8_sized(l->struct_name));
	c.out.len += snprintf(c.out.str + c.out.len, INIT_SIZE, "\tstruct %.*s\t*ptr;\n", stc_string8_sized(l->struct_name));
	c.out.len += snprintf(c.out.str + c.out.len, INIT_SIZE, "\tu64\t\tlen;\n");
	c.out.len += snprintf(c.out.str + c.out.len, INIT_SIZE, "\tu64\t\tmem_committed;\n");
	c.out.len += snprintf(c.out.str + c.out.len, INIT_SIZE, "\tu64\t\tmem_reserved;\n");
	c.out.len += snprintf(c.out.str + c.out.len, INIT_SIZE, "};\n");

	c.out.len += snprintf(c.out.str + c.out.len, INIT_SIZE, "\n");

	c.out.len += snprintf(
		c.out.str + c.out.len,
		INIT_SIZE,
		STC_CODEGEN_ARRAY_STRUCT_INIT_TEMPLATE,
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name)
	    );

	c.out.len += snprintf(
		c.out.str + c.out.len,
		INIT_SIZE,
		STC_CODEGEN_ARRAY_STRUCT_PUSH_TEMPLATE,
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name)
	    );

	c.out.len += snprintf(
		c.out.str + c.out.len,
		INIT_SIZE,
		STC_CODEGEN_ARRAY_STRUCT_APPEND_TEMPLATE,
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name)
	    );

	c.out.len += snprintf(
		c.out.str + c.out.len,
		INIT_SIZE,
		STC_CODEGEN_ARRAY_STRUCT_SHRINK_TEMPLATE,
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name)
	    );

	c.out.len += snprintf(
		c.out.str + c.out.len,
		INIT_SIZE,
		STC_CODEGEN_ARRAY_STRUCT_TOP_TEMPLATE,
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name),
		stc_string8_sized(l->struct_name)
	    );
}




static void stc_codegen(struct stc_string8 codegen_in_file)
{
	c.out.str = (char *)stc_os_mem_rsrv(1llu << 35);
	stc_os_mem_cmt(c.out.str, INIT_SIZE);
	FILE *f = fopen(codegen_in_file.str, "w+");


	struct codegen_struct_layout *layout_current = layouts;
	struct codegen_struct_layout *layout_last = layouts + ct_layouts;

	c.out.len += snprintf(c.out.str + c.out.len, INIT_SIZE, "#include \"/data/2026-projs/c/stormlibc/stormc_header.h\"\n\n\n\n");
	while (layout_current != layout_last) {
		switch ((*layout_current).codegen_type) {
		case CODEGEN_ARRAY_PRIMITIVE:
			stc_codegen_make_array_primitive(layout_current);
			break;
		case CODEGEN_ARRAY_STRUCT:
			stc_codegen_make_array_struct(layout_current);
			break;
		}


		layout_current++;
	}

	fwrite(c.out.str, c.out.len, 1, f);
	fclose(f);
}
