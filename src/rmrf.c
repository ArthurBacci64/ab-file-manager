#define _XOPEN_SOURCE 500
// nftw()
#include <ftw.h>

// remove()
#include <stdio.h>

int walker_function(const char *fpath, const struct stat *sb, int typeflag, struct FTW* ftwbuf)
{
    remove(fpath);
    
    return 0;
}

// Remove a directory and all it's contents
int rmrf(const char *filepath)
{
    nftw(filepath, walker_function, 1, FTW_DEPTH | FTW_PHYS);
    
    return 0;
}

