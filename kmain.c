#include "io.h"
#include "display.h"
#include "serial.h"

int kmain(void)
{
    char str[] = "Hello Serial.\n";
    char str2[] = "End Serial.\n";

    serial_configure_baud_rate(SERIAL_COM1_BASE, 2);
    serial_configure_line(SERIAL_COM1_BASE);
    serial_configure_fifo(SERIAL_COM1_BASE);
    serial_configure_modem(SERIAL_COM1_BASE);

    write(str, sizeof(str)-1);
    serial_write(SERIAL_COM1_BASE, str, sizeof(str)-1);
    write(str2, sizeof(str2)-1);

    return 0xdeafbeef;
}