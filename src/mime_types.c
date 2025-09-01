#include <magic.h>
#include <stdio.h>

magic_t init_magic() {
  magic_t magic = magic_open(MAGIC_MIME_TYPE);
  if (!magic) {
    perror("magic_open error");
    return NULL;
  }

  if (magic_load(magic, NULL) != 0) {
    fprintf(stderr, "magic_load failed: %s\n", magic_error(magic));
    magic_close(magic);
    return NULL;
  }

  return magic;
}

const char *get_mime_type(magic_t magic, const char *path) {
  const char *mime = magic_file(magic, path);
  if (!mime) {
    mime = "application/octet-stream";
  }

  return mime;
}

void free_mime(magic_t magic) {
  if (magic)
    magic_close(magic);
}
