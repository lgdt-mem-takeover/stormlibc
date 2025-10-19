#include <storm/scbuild.h>


int main(int argc, char *argv[])
{
	build.in = make_string("test.c");
	build.out = make_string("test");
	build.compiler = make_string("clang");

	SET_FLAGS(ALLSAN, MARCH_AVX2, STD_C99, OPTIM_3);

	stormc_build(argc, argv);
}
