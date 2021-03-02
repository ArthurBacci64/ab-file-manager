#ifndef ABFM_FUNCTIONS
#define ABFM_FUNCTIONS

#include <dirent.h>

#include <stdbool.h>

// src/rmrf.c
void rmrf(const char *filepath);

// src/ls.c
struct dirent **ls(const char *filepath, bool sort_items, bool show_hidden_files);
char **      strls(const char *filepath, bool sort_items, bool show_hidden_files);

// src/pwd.c
char *pwd(void);

// src/raw_mode.c
void enable_raw_mode(void);
void disable_raw_mode(void);

// src/io.c
char get_from_stdin(void);
void clear_screen(void);
void hide_cursor(void);
void show_cursor(void);
void get_screen_size(int *width, int *height);
void move(int x, int y);

#endif // #ifndef ABFMFUNCTIONS

