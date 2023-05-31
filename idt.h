#ifndef IDT_H
#define IDT_H

#include "stdint.h"

#define IDT_NUM_ENTRIES 256
void __attribute__((cdecl)) load_idt(uint32_t idt_ptr);
void idt_init(void);

#endif