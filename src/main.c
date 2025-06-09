#include "../include/catpak.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits/getopt_core.h>

struct Arguments {
  char *packagesToInstall;
};

int main(int argc, char **argv) {
  if (catpak_init(DEFAULT_DB_PATH) != 0) exit(-1);

  if (argc < 2) {
    fprintf(stderr, "* to install package: catpak -i <package>\n");
    fprintf(stderr, "* you need more commands\n");

    return -1;
  }

  struct Arguments *a = malloc(sizeof(struct Arguments*));
  if (a == NULL) {
    perror("struct Arguments *a\n");
    return -1;
  }

  int c;
  while ((c = getopt(argc, argv, "i:")) != -1) {
    switch (c) {
      case 'i':
        a->packagesToInstall = strdup(optarg);
        break;
    }
  }

  Lock *cd = lock_db(NULL);
  if (cd == NULL) {
    fprintf(stderr, "!!! struct *cd is empty!\n");
    exit(-1);
  }

  Transaction *transaction = malloc(sizeof(Transaction*) + (sizeof(char*) + sizeof(FILE*)));
  if (transaction == NULL) {
    fprintf(stderr, "catpak: memory error: %s\n", strerror(errno));
    free(a);
    free(cd);
    exit(-1);
  }

  transaction->package = strdup(a->packagesToInstall);
  transaction->lock = cd;
  transaction->db_fd = get_fd_to_db(transaction->lock);

  get_catpak_version(transaction);

  free(a);
  free(cd);

  fprintf(stderr, "\n* program finished without any errors\n");
  return 0;
}