#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "catpak_search.h"
#define CATPAK_LOCK

typedef struct Transaction {
  char *package;
  Lock *lock;
  FILE *db_fd;
} Transaction;

void get_catpak_version(Transaction *tranasction);