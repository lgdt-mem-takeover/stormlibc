#include <storm/scbuild.h>


int main(int argc, char *argv[])
{
	build.in = make_string("main.c");
	build.out = make_string("main");
	build.compiler = make_string("clang");

	SET_FLAGS(ALLSAN, MARCH_AVX2, STD_C99, OPTIM_3);

	stormc_build(argc, argv);
}
