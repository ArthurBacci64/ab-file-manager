#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

int sort_function(const void *a, const void *b)
{
    const int alen = strlen((*(struct dirent **)a)->d_name);
    const int blen = strlen((*(struct dirent **)b)->d_name);
    
    char *lower_a, *lower_b;
    lower_a = malloc(alen + 1);
    lower_b = malloc(blen + 1);
    
    for (int i = 0; i <= alen; i++)
    {
        lower_a[i] = tolower(*(*(struct dirent **)a)->d_name);
    }
    for (int i = 0; i <= blen; i++)
    {
        lower_b[i] = tolower(*(*(struct dirent **)b)->d_name);
    }
    
    return strcmp(
        lower_a,
        lower_b
    );
}

// Returned data is NULL terminated
struct dirent **ls(const char *filepath, bool sort_items, bool show_hidden_files)
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
        if (
            (
                show_hidden_files ||
                *item->d_name != '.' ||
                strcmp(item->d_name, "..") == 0
            ) &&
            strcmp(item->d_name, ".") != 0
        )
        {
            items = realloc(items, (itemslen + 2) * sizeof *items);
            items[itemslen] = item;
            items[++itemslen] = NULL;
        }
    }
    
    if (sort_items)
    {
        // Sorts the items
        qsort(items, itemslen, sizeof *items, sort_function);
    }
    
    closedir(directory);
    
    return items;
}

