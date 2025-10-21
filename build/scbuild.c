#include <storm/build/scbuild.h>


int main(int argc, char *argv[])
{
	build.in = STR("main.c");
	build.out = STR("main");
	build.compiler = STR("gcc");

	SET_FLAGS(MARCH_NATIVE, ALLSAN, STD_C99, OPTIM_1);

	stormc_build(argc, argv);
}
