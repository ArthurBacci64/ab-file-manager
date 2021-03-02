#include <abfm/defines.h>
#include <abfm/functions.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    enable_raw_mode();
    
    char *workdir = pwd();
    int workdir_len = strlen(workdir);
    
    if (workdir_len > 1 && workdir[workdir_len - 1] != '/')
    {
        workdir[workdir_len++] = '/';
        workdir[workdir_len]   = '\0';
    }
    
    workdir = realloc(workdir, workdir_len + 1);
    
    clear_screen();
    
    char **items = strls(workdir, 1, 0);

    for (int i = 0; items[i]; i++)
    {
        printf("%s\r\n", items[i]);
        free(items[i]);
    }
    
    free(items);
    
    
    get_from_stdin();
    
    disable_raw_mode();
    free(workdir);
    
    return 0;
}


