
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

