#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

int sort_function(const void *a, const void *b)
{
    return strcmp(
        (*(struct dirent **)a)->d_name,
        (*(struct dirent **)b)->d_name
    );
}

// Returned data is NULL terminated
struct dirent **ls(const char *filepath, bool sort_items)
{
    DIR *directory = opendir(filepath);
    
    if (!directory)
    {
        return NULL;
    }
    
    struct dirent **items = malloc(sizeof *items);
    *items = NULL;
    
    int itemslen = 0;
    
    struct dirent *item;
    
    // If there are no more items, readdir returns NULL
    while (item = readdir(directory))
    {
        items = realloc(items, (itemslen + 2) * sizeof *items);
        items[itemslen] = item;
        items[++itemslen] = NULL;
    }
    
    if (sort_items)
    {
        // Sorts the items
        qsort(items, itemslen, sizeof *items, sort_function);
    }
    
    closedir(directory);
    
    return items;
}

