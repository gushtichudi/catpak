#include "../include/catpak.h"



Lock *lock_db(char *db_path) {
  Lock *l = malloc(sizeof(Lock*) * 2);
  if (l == NULL) {
    fprintf(stderr, "catpak: error: %s\n", strerror(errno));
    exit(-1);
  }

  if (db_path == NULL) {
    fprintf(stderr, "* warning: `db_path` is not specified. using path `%s`\n", DEFAULT_DB_PATH);
    db_path = strdup(DEFAULT_DB_PATH);
  }

  l->path = strdup(db_path);

  // obtain stream first
  FILE *db_file_stream = fopen(db_path, "w");
  if (db_file_stream == NULL) {
    fprintf(stderr, "catpak: %s: %s\n", db_path, strerror(errno));
    exit(-1);
  }

  int db_fd = fileno(db_file_stream);
  struct flock lock;

  lock.l_type = F_LOCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = 0;
  lock.l_len = 0;

  if (fcntl(db_fd, F_SETLK, &lock) == -1) {
    fprintf(stderr, "catpak: error: %s\n", strerror(errno));

    if (errno == EBADF) {
      fprintf(stderr, "\n* sysadmin hint: was %s ever properly created?\n\n", DEFAULT_DB_PATH);
    }

    fclose(db_file_stream);
    exit(-1);
  }

  // everything succeded, time to generate code
  void *unlock_code = malloc(sizeof(void*) * CATPAK_MAX_RAND_BUFLEN);
  if (unlock_code == NULL) {
    fprintf(stderr, "catpak: memory error: %s\n", strerror(errno));
    fclose(db_file_stream);
    exit(-1);
  }

  if (getentropy(unlock_code, CATPAK_MAX_RAND_BUFLEN) == -1) {
    fprintf(stderr, "catpak: cannot authenthicate: %s\n", strerror(errno));
    fclose(db_file_stream);
    exit(-1);
  }

  l->key = unlock_code;

  return l;
}

FILE *get_fd_to_db(Lock *lock) {
  if (lock->key == NULL) {
    fprintf(stderr, "\n* failed to authenticate you\n");
    exit(-1);
  }

  FILE *db_fd = fopen(lock->path, "r");
  if (db_fd == NULL) {
    fprintf(stderr, "catpak: error: %s\n", strerror(errno));
    exit(-1);
  }

  return db_fd;
}