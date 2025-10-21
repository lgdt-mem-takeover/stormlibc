#include <storm/build/scbuild.h>


int main(int argc, char *argv[])
{
	build.in = STR("test_dice.c");
	build.out = STR("dice_t");
	build.compiler = STR("gcc");

	SET_FLAGS(WALL, WPEDANTIC, MARCH_NATIVE, ALLSAN, STD_C99, OPTIM_1);

	stormc_build(argc, argv);
}
