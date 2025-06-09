#include "../include/catpak.h"
#include <string.h>
#include <sys/stat.h>

static inline bool file_exists(char *path) {
  if (access(path, F_OK) == 0) return true;
  return false;
}

bool lock_exists(char *db_path) {
  if (db_path == NULL) {
    fprintf(stderr, "* warning: `db_path` is not specified. using path `/var/db/catpak/pak.db`\n");
    db_path = strdup(DEFAULT_DB_PATH);
  }

  if (!file_exists(db_path)) return false;
  return true;
}

int create_db(char *destination) {
  FILE *db_fd = fopen(destination, "w");
  if (db_fd == NULL) {
    fprintf(stderr, "catpak: %s: %s\n", destination, strerror(errno));
    return -1;
  }

  fprintf(db_fd, "{\n\t\"catpak-version\": \"0.1\"\n}\n");
  fclose(db_fd);

  return 0;
}

int catpak_init(char *db_path) {
  if (lock_exists(db_path)) return 0;

  if (create_db(db_path) != 0) {
    fprintf(stderr, "Lock directories do not exist, creating...\n");

    // i don't care, it's just TOO hard in C
    if (system("mkdir -p /var/db/catpak") != 0) return -1;

    return 1;
  }

  return 0;
}