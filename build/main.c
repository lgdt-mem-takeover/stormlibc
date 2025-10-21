#include "stormc_buildsystem.h"
#include "default_scbuild.h"

#define GREEN "\033[32m"
#define RESET_COL "\033[0m"

typedef enum{
	INIT,
	BUILD,
	RUN,

	CTAGS,
	EMBED,
	G_COMMAND_TYPES_COUNT,
}G_Command_Types;




String G_COMMANDS[G_COMMAND_TYPES_COUNT] = {
	[INIT] = (String){.str = "init", .len = 4},
	[BUILD] = (String){.str = "build", .len = 5},
	[RUN] = (String){.str = "run", .len = 3},
	[CTAGS] = (String){.str = "ctags", .len = 5},
	[EMBED] = (String){.str = "embed", .len = 5},
};


typedef struct{
	String		_args[32];
	u32		len;
}StormC_Main_Entry_Process;


extern const char default_scbuild_start[];

typedef enum{
	DEFAULT,
	SCBUILD_TEMPLATES_TYPES_COUNT,
}Scbuild_Templates_Types;

String Global_Templates_Scbuild[SCBUILD_TEMPLATES_TYPES_COUNT] = {
	[DEFAULT] = {.str = (char *)default_scbuild_c, .len = default_scbuild_c_len},
};



int main(int argc, char *argv[])
{
	int ret;
	int status;
	StormC_Main_Entry_Process sc_main = {0};

	while (sc_main.len < argc - 1){
		sc_main._args[sc_main.len] = make_string(argv[1 + sc_main.len]);
		sc_main.len++;
	}

	if (sstrcmpx(sc_main._args[0], G_COMMANDS[CTAGS])){
		char path_buf[256];
		snprintf(path_buf, sizeof(path_buf), "ctags -R . %s", sc_main._args[1].str);
		system(path_buf);
	} else if (sstrcmpx(sc_main._args[0], G_COMMANDS[INIT])) {
		int fd = open("scbuild.c", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (!fd) {
			perror("open");
			exit(1);
		}
		write(fd, Global_Templates_Scbuild[DEFAULT].str, Global_Templates_Scbuild[DEFAULT].len);
		close(fd);
	}
	else if(sstrcmpx(sc_main._args[0], G_COMMANDS[RUN])){
		ret = system("gcc -mavx2 scbuild.c -o scbuild && ./scbuild run");
		status = WEXITSTATUS(ret);
		if(ret == -1) perror("system");
		if (status != 0){
			printf("[RUN]Failed to run system()\nStatus: %d\n", status);
			exit(131);
		}
	}
	else if (sstrcmpx(sc_main._args[0], G_COMMANDS[BUILD])) {
		if (sstrcmpx(sc_main._args[1], G_COMMANDS[RUN])) {
			ret = system("gcc -mavx2 scbuild.c -o scbuild && ./scbuild build run");
			status = __WEXITSTATUS(ret);
			if (ret == -1) perror("system");

			if (status != 0){
				printf("[BUIILD RUN]Failed to run system()\nStatus: %d\n", status);
				exit(131);
			}


		}
		else{
			ret = system("gcc -mavx2 scbuild.c -o scbuild && ./scbuild build");
			status = WEXITSTATUS(ret);
			if(ret == -1) perror("system");
			if (status != 0){
				printf("[BUILD] Failed to run system()\nStatus: %d\n", status);
				exit(131);
			}
		}
	} else if (sstrcmpx(sc_main._args[0], G_COMMANDS[EMBED])){
		Storm_File *file_in = Storm_Open_File_RO(sc_main._args[1]);
		int file_out = open(sc_main._args[2].str, O_WRONLY | O_CREAT, S_IRWXU);
		if (file_out == -1){
			printf("failed to open file out\n");
			exit(1);
		}
		char var_name_buff[1024];
		char var_len_buff[1024];
		char fmt_file_name[1024];
		for (u32 idx_file_name = 0; idx_file_name < sc_main._args[1].len; idx_file_name++){
			if (sc_main._args[1].str[idx_file_name] == '.'){
				fmt_file_name[idx_file_name] = '_';
				continue;
			}
			fmt_file_name[idx_file_name] = sc_main._args[1].str[idx_file_name];
		}
		printf("%s\n", fmt_file_name);
		fflush(stdout);
		u32 buff_len = snprintf(var_name_buff, sizeof(var_name_buff), (char *)"const unsigned char %s[] = {\n", fmt_file_name);
		write(file_out, var_name_buff, buff_len);
		for (u64 idx_in = 0; idx_in < file_in->file_size; idx_in++) {
		    unsigned char byte = (unsigned char)file_in->content.str[idx_in];

		    char buf[8];
		    int len = snprintf(buf, sizeof buf, "\t0x%02x,", byte);
		    write(file_out, buf, len);

		    if ((idx_in + 1) % 12 == 0) {
			write(file_out, "\n", 1);
		    }
		}
		const char *footer = "\n};\n";
		write(file_out, footer, sstrlenx(footer));

		u32 len_var_len = snprintf(
			var_len_buff,
			sizeof(var_len_buff),
			(char *)"\n\nconst unsigned int %s_len = %lu;\n\n", fmt_file_name, file_in->file_size
		);

		write(file_out, var_len_buff, len_var_len);
	}


	return 0;
}
