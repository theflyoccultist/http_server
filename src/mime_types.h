#ifndef MIME_TYPES_H
#define MIME_TYPES_H

#include <magic.h>

magic_t init_magic();
const char *get_mime_type(magic_t magic, const char *path);
void free_mime(magic_t magic);

#endif // !MIME_TYPES_H
