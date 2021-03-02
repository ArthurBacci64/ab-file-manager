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
    
    struct dirent **items = ls(workdir, 1, 0);
    
    for (int i = 0; items[i]; i++)
    {
        if (items[i]->d_type == DT_DIR)
        {
            printf("%s/\r\n", items[i]->d_name);
        }
        else
        {
            printf("%s\r\n", items[i]->d_name);
        }
    }
    
    free(items);
    
    get_from_stdin();
    
    disable_raw_mode();
    free(workdir);
    
    return 0;
}


