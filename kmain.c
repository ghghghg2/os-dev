#include "io.h"
#include "display.h"
#include "serial.h"
#include "gdt.h"
#include "keyboard.h"
#include "idt.h"
#include "interrupt.h"
#include "pic.h"

int kmain(void)
{
    char str[] = "Hello Serial.\n";
    char str2[] = "End Serial.\n";
    char str3[] = "Serial Log\n";

    gdt_initialize();
    idt_init();
    pic_init();
    kbd_init();

    enable_interrupts();
    

    serial_configure_baud_rate(SERIAL_COM1_BASE, 2);
    serial_configure_line(SERIAL_COM1_BASE);
    serial_configure_fifo(SERIAL_COM1_BASE);
    serial_configure_modem(SERIAL_COM1_BASE);

    write(str, sizeof(str)-1);
    serial_write(SERIAL_COM1_BASE, str3, sizeof(str3)-1);
    write(str2, sizeof(str2)-1);

    return 0xdeadbeef;
}