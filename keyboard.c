#include "keyboard.h"
#include "io.h"
#include "common.h"
#include "display.h"
#include "interrupt.h"
#include "pic.h"

#define KBD_DATA_PORT   0x60

/** read_scan_code:
 *  Reads a scan code from the keyboard
 *
 *  @return The scan code (NOT an ASCII character!)
 */
uint8_t read_scan_code(void)
{
    return inb(KBD_DATA_PORT);
}

static void keyboard_handle_interrupt(cpu_state_t state, idt_info_t info, stack_state_t exec)
{
    UNUSED_ARGUMENT(state);
    UNUSED_ARGUMENT(info);
    UNUSED_ARGUMENT(exec);
    uint8_t sc = read_scan_code();

    if (sc == 0x1E) {
        sc = 'A';
    }
    write((int8_t *)&sc, 1);

    pic_acknowledge(info.idt_index);
}

void kbd_init(void)
{
    register_interrupt_handler(KBD_INT_IDX, keyboard_handle_interrupt);
}