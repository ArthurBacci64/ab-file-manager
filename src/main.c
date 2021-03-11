#include <abfm/defines.h>
#include <abfm/functions.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>

int calculate_scroll_y(int scroll_y, int selected, int rows)
{
    if (scroll_y <= selected - rows)
    {
        return selected - rows + 1;
    }
    if (selected < scroll_y)
    {
        return selected;
    }
    return scroll_y;
}

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
    
    int w, h;
    
    get_screen_size(&w, &h);
    
    char **items = strls(workdir, 1, 0);
    int len_items;
    
    // Calculates len_items
    for (len_items = 0; items[len_items]; len_items++)
        ;

    int scroll_y = 0;

    int selected = 0;

    char c;
    while (1)
    {
        clear_screen();
        scroll_y = calculate_scroll_y(scroll_y, selected, h - 2);
        
        for (int i = scroll_y; items[i] && i - scroll_y < h - 2; i++)
        {
            struct stat st;
            int plen;

            char abspath[1000];
            strcpy(abspath, workdir);
            strcat(abspath, items[i]);
            
            if (stat(abspath, &st) < 0)
            {
                plen = printf("err    ");
            }
            else
            {
                struct passwd *pwd = getpwuid(st.st_uid);
                char usrstr[1000];
                if (pwd)
                    strcpy(usrstr, pwd->pw_name);
                else
                    strcpy(usrstr, "err");

                struct group *grp = getgrgid(st.st_gid);
                char grpstr[1000];
                if (grp)
                    strcpy(grpstr, grp->gr_name);
                else
                    strcpy(grpstr, "err");
                
                plen = printf("%c%c%c%c%c%c%c%c%c%c %-10s %-10s    ",
                              S_ISDIR(st.st_mode)  ? 'd' : '-',
                              
                              st.st_mode & S_IRUSR ? 'r' : '-',
                              st.st_mode & S_IWUSR ? 'w' : '-',
                              st.st_mode & S_IXUSR ? 'x' : '-',
            
                              st.st_mode & S_IRGRP ? 'r' : '-',
                              st.st_mode & S_IWGRP ? 'w' : '-',
                              st.st_mode & S_IXGRP ? 'x' : '-',
            
                              st.st_mode & S_IROTH ? 'r' : '-',
                              st.st_mode & S_IWOTH ? 'w' : '-',
                              st.st_mode & S_IXOTH ? 'x' : '-',

                              usrstr,
                              grpstr
                    );
            }

            
            if (i == selected)
            {
                printf(COLOR_REVERSE "%-*s" COLOR_RESET "\r\n", w - plen, items[i]);
            }
            else
            {
                printf("%-*s\r\n", w - plen, items[i]);
            }
        }
        move(0, h - 1);
        printf("%s", workdir);
        fflush(stdout);
        
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
            case 'l':
            case 'h':
            {
                int item_len = strlen(items[selected]);
                if (item_len > 0 && items[selected][item_len - 1] == '/' || c == 'h')
                {
                    if (selected == 0 || c == 'h')
                    {
                        if (strcmp(workdir, "/") != 0)
                        {
                            workdir_len = strlen(workdir);
                            workdir[workdir_len - 1] = '\0';
                            char *pos = strrchr(workdir, '/');
                            if (pos != NULL)
                            {
                                pos[1] = '\0';
                            }
                            else
                            {
                                workdir[workdir_len - 1] = '/';
                            }
                        }
                    }
                    else
                    {
                        strcat(workdir, items[selected]);
                    }
                    
                    // Free items
                    for (int i = 0; items[i]; i++)
                    {
                        free(items[i]);
                    }
                    free(items);
                    
                    
                    items = strls(workdir, 1, 0);
                    
                    // Calculates len_items
                    for (len_items = 0; items[len_items]; len_items++)
                        ;
                    
                    selected = 0;
                    workdir_len = strlen(workdir);
                }
                break;
            }
            case 'D':
            {
                if (get_from_stdin() != 'd')
                    break;
                int itemlen = strlen(items[selected]);
                if (itemlen > 0 && items[selected][itemlen - 1] != '/')
                {
                    char fname[1000];
                    strcpy(fname, workdir);
                    strcat(fname, items[selected]);
                    remove(fname);
                }
                
                // Free items
                for (int i = 0; items[i]; i++)
                {
                    free(items[i]);
                }
                free(items);
                    
                    
                items = strls(workdir, 1, 0);
                    
                // Calculates len_items
                for (len_items = 0; items[len_items]; len_items++)
                    ;
                
                if (selected >= len_items)
                    selected = len_items - 1;
                break;
            }
        }
    }
    
    // Free items
    for (int i = 0; items[i]; i++)
    {
        free(items[i]);
    }
    free(items);
    
    clear_screen();
    show_cursor();
    
    disable_raw_mode();
    free(workdir);
    
    return 0;
}


