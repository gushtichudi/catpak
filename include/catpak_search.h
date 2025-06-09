#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Lock {
  char *path;
  void *key;
} Lock;

#define CATPAK_MAX_RAND_BUFLEN 16

Lock *lock_db(char *db_path);
FILE *get_fd_to_db(Lock *lock);