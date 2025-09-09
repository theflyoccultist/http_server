#include <magic.h>
#include <stdio.h>

magic_t init_magic() {
  magic_t magic_cookie = magic_open(MAGIC_MIME_TYPE);
  if (magic_cookie == NULL) {
    printf("Unable to initialize magic library\n");
    return NULL;
  }

  if (magic_load(magic_cookie, NULL) != 0) {
    fprintf(stderr, "Cannot load magic database: %s\n",
            magic_error(magic_cookie));
    magic_close(magic_cookie);
    return NULL;
  }

  return magic_cookie;
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
