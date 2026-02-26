#include "../text/stormc_string.h"



enum build_errors{
	SUCCESS,
	DIR_STR_IS_NULL,
	DIR_DOES_NOT_EXIST,
	TBL_BLDS_IS_NULL,
	MAIN_FILE_IS_NULL,
	OUT_FILE_IS_NULL,
	COMPILER_NAME_NOT_EXIST,
	CT_BUILD_ERRORS
};

thisfile struct stc_string8  table_stc_build_errs[] = {
	[SUCCESS] = STR("Build success"),
	[DIR_STR_IS_NULL] = STR("[Failed] directory path .dir.str is a null pointer"),
	[DIR_DOES_NOT_EXIST] = STR("[Failed] directory does not exist"),
	[TBL_BLDS_IS_NULL] = STR("[Failed] the field tbl->blds is a null pointer"),
	[MAIN_FILE_IS_NULL] = STR("[Failed] main file .str field is a null pointer"),
	[OUT_FILE_IS_NULL] = STR("[Failed] out file .str field is a null pointer"),
	[COMPILER_NAME_NOT_EXIST] = STR("[Failed] compiler does not exist"),
};

