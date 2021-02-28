#include <abfm/functions.h>

#include <stdio.h>
#include <stdlib.h>

#include <dirent.h>
#include <sys/types.h>

int main()
{
    char *directory = pwd();

    struct dirent **contents = ls(directory, 1, 0);
    
    free(directory);
    
    if (contents == NULL)
        return 1;
    
    struct dirent *item;
    int i = 0;
    while (item = contents[i])
    {
        printf("%s\n", item->d_name);
        
        i++;
    }
    

    return 0;
}

