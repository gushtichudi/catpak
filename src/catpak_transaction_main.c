#include "../include/catpak.h"

static inline const char *read_file_into_string(FILE *file) {
  const char *buf = malloc(sizeof(const char*));
  if (buf == NULL) {
    fprintf(stderr, "catpak: memory error: %s\n", strerror(errno));
    exit(-1);
  }

  int fd = fileno(file);
  if (fd == -1) {
    fprintf(stderr, "catpak: cannot open `%s`: %s\n", file, strerror(errno));
    free(buf);
    exit(-1);
  }

  if (read(fd, buf, sizeof(fd)) == -1) {
    fprintf(stderr, "catpak: cannot read `%s`: %s\n", file, strerror(errno));
    close(fd);
    free(buf);
    exit(-1);
  }

  close(fd);
  return buf;
}

void get_catpak_version(Transaction *tranasction) {
  const char *db = read_file_into_string(tranasction->db_fd);

  struct json_value_s *db_root = json_parse(db, strlen(db));
  // assert(db_root->type == json_type_object);

  struct json_object_s *object = (struct json_object_s*)db_root->payload;

  struct json_object_element_s *ver = object->start;

  struct json_string_s *vername = ver->name;
  assert(0 == strcmp(vername->string, "catpak-version"));
  assert(vername->string_size == strlen("catpak-version"));

  struct json_value_s *verval = ver->value;
  assert(verval->type == json_type_true);
  assert(verval->payload == NULL);

  printf("Catpak version %s\n", ver->value);

  free(db_root);
}