#include <stdbool.h>
#include <stdio.h>
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
    
    for (int i = 0; i < alen; i++)
    {
        lower_a[i] = tolower(*(*(struct dirent **)a)->d_name);
    }
    for (int i = 0; i < blen; i++)
    {
        lower_b[i] = tolower(*(*(struct dirent **)b)->d_name);
    }
    lower_a[alen] = '\0';
    lower_b[blen] = '\0';
    
    int r = strcmp(
        lower_a,
        lower_b
    );
    
    free(lower_a);
    free(lower_b);
    
    return r;
}

// Returned data is NULL terminated
struct dirent **ls(const char *filepath, bool sort_items, bool show_hidden_files)
{
    DIR *directory = opendir(filepath);
    
    if (!directory)
    {
        return NULL;
    }
    
    struct dirent **items = malloc(2 * sizeof *items);
    *items = NULL;
    
    int itemslen = 0;
    
    struct dirent *item;
    
    // If there are no more items, readdir returns NULL
    while (item = readdir(directory))
    {
        if (
            (
                show_hidden_files ||
                *item->d_name != '.'
            ) &&
            strcmp(item->d_name, ".") != 0 &&
            strcmp(item->d_name, "..") != 0 &&
            item->d_name
        )
        {
            items = realloc(items, (itemslen + 2) * sizeof *items);
            items[itemslen] = malloc(sizeof *item);
            memcpy(items[itemslen], item, sizeof *item);
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

char **strls(const char *filepath, bool sort_items, bool show_hidden_files)
{
    struct dirent **items = ls(filepath, sort_items, show_hidden_files);

    if (!items)
        return NULL;
    
    char **r = malloc(2 * sizeof *r);
    r[0] = malloc(1000);
    strcpy(r[0], "../");
    
    int i = 0;
    for (i = 0; items[i]; i++)
    {
        r = realloc(r, (i + 3) * sizeof *r);
        r[i + 1] = malloc(1000);

        if (items[i]->d_type == DT_DIR)
        {
            snprintf(r[i + 1], 1000, "%s/", items[i]->d_name);
        }
        else
        {
            snprintf(r[i + 1], 1000, "%s", items[i]->d_name);
        }
        free(items[i]);
    }
    r[i + 1] = NULL;
    
    free(items);
    return r;
}

