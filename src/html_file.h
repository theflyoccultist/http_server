#ifndef HTML_FILE_H
#define HTML_FILE_H

#include <stddef.h>

struct html_file {
  size_t filesize;
  char *file_buffer;
};

struct html_file read_file(const char *path);
void free_file(struct html_file *hf);

#endif // !HTML_FILE_H
