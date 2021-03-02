#include <unistd.h>

char get_from_stdin(void)
{
    char c;
    while (read(STDIN_FILENO, &c, 1) != 1)
        ;
    
    return c;
}

