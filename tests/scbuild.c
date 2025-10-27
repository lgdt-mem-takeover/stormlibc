#include <storm/build/scbuild.h>


int main(int argc, char *argv[])
{
	build.in = STR("test_arena.c");
	build.out = STR("arena_t");
	build.compiler = STR("gcc");

	SET_FLAGS(WALL, WPEDANTIC, MARCH_NATIVE, ALLSAN, STD_C99, OPTIM_1);

	stormc_build(argc, argv);
}
