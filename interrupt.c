#include "idt.h"
#include "interrupt.h"
#include "serial.h"
#include "stddef.h"
#include "common.h"
#include "display.h"
#include "pic.h"

static interrupt_handler_t interrupt_handlers[IDT_NUM_ENTRIES];

uint32_t register_interrupt_handler(uint32_t int_idx, interrupt_handler_t handler)
{
    if (int_idx > 255) {
        return 1;
    }
    if (interrupt_handlers[int_idx] != NULL) {
        return 1;
    }

    interrupt_handlers[int_idx] = handler;
    return 0;
}

void __attribute__((cdecl)) interrupt_handler(cpu_state_t state, idt_info_t info, stack_state_t exec)
{

    // char str[] = " Unhandled Interrupt.\n";
    char a = info.idt_index + '0';
    if (interrupt_handlers[info.idt_index] != NULL) {
        interrupt_handlers[info.idt_index](state, info, exec);
    } else {
        write(&a, 1);
    }
    // pic_acknowledge();
}