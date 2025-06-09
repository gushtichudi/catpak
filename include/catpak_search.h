#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CATPAK_MAX_RAND_BUFLEN 64

#ifndef CATPAK_LOCK
#define CATPAK_LOCK
typedef struct Lock {
  char *path;
  void *key;
} Lock;

Lock *lock_db(char *db_path);
FILE *get_fd_to_db(Lock *lock);
#endif // CATPAK_LOCK