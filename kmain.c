#include "io.h"
#include "display.h"

int kmain(void)
{
    char str[] = "Hello, this is a demo message1\n Hello, this is a demo message*\n";
    // char ch = 'A';
    // write(str, sizeof(str)-1);
    for (int i = 0; i < 10; i++) {
        write(str, sizeof(str)-1);
    }

    // for (int i = 0; i < 2005; i++) {
    //     // ch = 'A' + ((i / 80) % 26);
    //     ch = 'A' + (i % 26);
    //     write(&ch, 1);
    // }

    return 0xdeafbeef;
}