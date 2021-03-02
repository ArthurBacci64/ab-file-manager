#include <unistd.h>
#include <stdio.h>

char get_from_stdin(void)
{
    char c;
    while (read(STDIN_FILENO, &c, 1) != 1)
        ;
    
    return c;
}

void clear_screen(void)
{
    printf("\033[2J\033[H");
    fflush(stdout);
}

void hide_cursor(void)
{
    fputs("\033[?25l", stdout);
}

void show_cursor(void)
{
    fputs("\033[?25h", stdout);
}

