#include <abfm/functions.h>

#include <stdio.h>
#include <stdlib.h>

int main()
{
    enable_raw_mode();

    char c;
    while ((c = get_from_stdin()) != 'q')
    {
        printf("%x\r\n", (unsigned char)c);
    }
    
    disable_raw_mode();

    return 0;
}

