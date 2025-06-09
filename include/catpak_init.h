#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/stat.h>

bool lock_exists(char *db_path);
int create_db(char *destination);
int catpak_init(char *db_path);