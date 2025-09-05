#include "html_file.h"
#include <stdio.h>
#include <stdlib.h>

struct html_file read_file(const char *path) {
  struct html_file hf = {0, NULL};

  FILE *fp = fopen(path, "rb");
  if (!fp) {
    perror("fopen error");
    return hf;
  }

  if (fseek(fp, 0, SEEK_END) != 0) {
    perror("fseek error");
    fclose(fp);
    return hf;
  }

  hf.filesize = ftell(fp);
  if (!hf.filesize) {
    perror("ftell error");
    fclose(fp);
    return hf;
  }

  rewind(fp);

  hf.file_buffer = malloc(hf.filesize);
  if (!hf.file_buffer) {
    perror("malloc error");
    fclose(fp);
    hf.filesize = 0;
    return hf;
  }

  if (fread(hf.file_buffer, 1, hf.filesize, fp) < hf.filesize) {
    perror("fread error");
    free(hf.file_buffer);
    hf.file_buffer = NULL;
    hf.filesize = 0;
  }

  fclose(fp);
  return hf;
}

void free_file(struct html_file *hf) {
  if (!hf)
    return;
  free(hf->file_buffer);
  hf->file_buffer = NULL;
  hf->filesize = 0;
}
