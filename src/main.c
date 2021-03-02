#include <abfm/defines.h>
#include <abfm/functions.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    enable_raw_mode();
    hide_cursor();
    
    char *workdir = pwd();
    int workdir_len = strlen(workdir);
    
    if (workdir_len > 1 && workdir[workdir_len - 1] != '/')
    {
        workdir[workdir_len++] = '/';
        workdir[workdir_len]   = '\0';
    }
    
    workdir = realloc(workdir, workdir_len + 1);
    
    int w, h;
    
    get_screen_size(&w, &h);
    
    char **items = strls(workdir, 1, 0);
    int len_items;
    
    // Calculates len_items
    for (len_items = 0; items[len_items]; len_items++)
        ;

    int selected = 0;

    char c;
    while (1)
    {
        clear_screen();
        for (int i = 0; items[i]; i++)
        {
            if (i == selected)
            {
                printf(COLOR_REVERSE "%s" COLOR_RESET "\r\n", items[i]);
            }
            else
            {
                printf("%s\r\n", items[i]);
            }
        }
        
        if ((c = get_from_stdin()) == CTRL_KEY_OF('c'))
        {
            break;
        }
        
        switch (c)
        {
            case CTRL_KEY_OF('n'):
            case 'j':
                if (selected < len_items - 1)
                    selected++;
                break;
            case CTRL_KEY_OF('p'):
            case 'k':
                if (selected > 0)
                    selected--;
                break;
            case '0':
                selected = 0;
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if (len_items > c - '1' + 1)
                    selected = c - '1' + 1;
                break;
        }
    }
    
    // Frees all items of items and items
    for (int i = 0; items[i]; i++)
    {
        free(items[i]);
    }
    free(items);
    
    show_cursor();
    
    disable_raw_mode();
    free(workdir);
    
    return 0;
}


