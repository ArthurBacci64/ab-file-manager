#include <stdlib.h>

#include <unistd.h>

// Result needs to be freed
char *pwd(void)
{
    char *workdir = malloc(1000);
    
    // I will not do any check here because usually paths does not have more than 1000 bytes
    getcwd(workdir, 1000);
    
    return workdir;
}

