#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>


typedef struct Storm_File Storm_File;


struct Storm_File{
    String      path;
    String      content;
    u64         count_words;
    u64         count_lines;
    u64         count_whitespace;
    u64         file_size;
    mode_t      flag_type_mode;
    int         fd;
    int         flag_type_open;
};


static Storm_File* Storm_Open_File_RO(String path)
{

  int fd = open(path.str, O_RDONLY);

  struct stat st;
  fstat(fd, &st);

  size_t storm_struct_size = sizeof(Storm_File);
  size_t file_path_size = (sstrlenx(path.str) * sizeof(char));
  size_t file_content_size = st.st_size;
  size_t sizes = storm_struct_size + file_path_size + file_content_size;
  Storm_File *output = (Storm_File*)mmap(NULL, sizes, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
  output->path.str = (char *)output + storm_struct_size;
  output->content.str = (char *)output + storm_struct_size + file_path_size;
  output->content.len = st.st_size;
  read(fd, output->content.str, st.st_size);



  output->flag_type_mode = st.st_mode;
  output->flag_type_open |= O_RDONLY;

  output->file_size = st.st_size;

  close(fd);

  return output;
}
