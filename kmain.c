#include "io.h"
#include "display.h"

int kmain(void)
{
    char ch = 'A';
    // char str[] = "Hello, this is a demo message";
    for (int i = 0; i < 2005; i++) {
        // ch = 'A' + ((i / 80) % 26);
        ch = 'A' + (i % 26);
        write(&ch, 1);
    }

    return 0xdeafbeef;
}