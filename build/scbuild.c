#include "scbuild.h"


int main(int argc, char **argv)
{
	enum compilers compiler = C_GCC;
	if (argc > 1) {
		struct stc_string8 arg = STR_RUNTIME(argv[1]);
		printf("[%s]\n", arg.str);
		printf("[%lu]\n", arg.len);
		if (stc_string8_cmp(arg, STR("mingw"))) compiler = C_MINGW64;
		else if (stc_string8_cmp(arg, STR("clang"))) compiler = C_CLANG;
		else if (stc_string8_cmp(arg, STR("mingw32"))) compiler = C_MINGW32;
		else if (stc_string8_cmp(arg, STR("mingwpp"))) compiler = C_MINGW64PP;
		else if (stc_string8_cmp(arg, STR("gcc"))) compiler = C_GCC;
		else if (stc_string8_cmp(arg, STR("zig"))) compiler = C_ZIGCC;
		else if (stc_string8_cmp(arg, STR("clangpp"))) compiler = C_CLANGPP;
		else if (stc_string8_cmp(arg, STR("gccgpp"))) compiler = C_GCCPP;
	}

	for (u64 i = 2; i < argc; ++i) {
		stc_println("{cstring}", argv[i]);
	}

	proj.compiler = compiler;
	set_include_paths(STR(STORMC_ROOT));
	set_sources(STR("src/main.c"));
	set_flags(STD_C99, OPTIM_3);
	set_out_file(STR("src/main"));

	bool linux_build = (compiler != C_MINGW64) && (compiler != C_MINGW32);
	if (linux_build) {
		set_objects(STR(STORMC_ROOT"/obj_files/sasm_stringlib.o"));
	} else {
		set_objects(STR(STORMC_ROOT"/obj_files/sasm_stringlib.obj"));
	}
	build_proj();

	if (IS_RUN_AFTER_BUILD(argc, argv)) {
		system("src/./main");
	}
	return 0;
}
