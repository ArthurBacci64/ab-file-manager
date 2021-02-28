#include <abfm/functions.h>

#include <stdio.h>

#include <dirent.h>
#include <sys/types.h>

int main()
{
    struct dirent **contents = ls("./", 1);
    
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

