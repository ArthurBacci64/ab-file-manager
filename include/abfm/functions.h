#ifndef ABFM_FUNCTIONS
#define ABFM_FUNCTIONS

#include <dirent.h>

#include <stdbool.h>

// src/rmrf.c
void rmrf(const char *filepath);

// src/ls.c
struct dirent **ls(const char *filepath, bool sort_items);

// src/pwd.c
char *pwd(void);

#endif // #ifndef ABFMFUNCTIONS

