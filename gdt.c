#include "gdt.h"


static uint8_t idx = 1; /* 0 for null descriptor */
static seg_descriptor_t gdt[NUM_SEG_DESCRIPTORS];
static gdt_ptr_t gdt_ptr;


int8_t gdt_add_seg_descriptor(uint8_t pl, uint8_t type)
{
    if (idx >= NUM_SEG_DESCRIPTORS) {
        return -1;
    }
    gdt[idx].base_addr_low     = (SEG_BASE & 0xFFFF);
    gdt[idx].base_addr_mid     = (SEG_BASE >> 16) & 0xFF;
    gdt[idx].base_addr_high    = (SEG_BASE >> 24) & 0xFF;

    gdt[idx].seg_lim_low = SEG_LIMIT & 0xFFFF;
    gdt[idx].seg_lim_high = (SEG_LIMIT & 0xF0000U) >> 16;

    gdt[idx].seg_type = type;
    gdt[idx].descriptor_type = 1;
    gdt[idx].dpl = pl;
    gdt[idx].seg_present = 1;

    gdt[idx].default_op_size = 1;
    gdt[idx].granularity = 1;

    idx++;
    return (idx - 1);
}

void __attribute__((cdecl)) load_gdt_and_seg(uint32_t gdt_ptr);

/** gdt_initialize:
 *  Initialize the gdt with 2 segments (code and data).
 *  The flat model is used.
 */
void gdt_initialize(void)
{
    /* Flat Model */
    gdt_add_seg_descriptor(PL0, SEG_TYPE_RX); /* Code segment */
    gdt_add_seg_descriptor(PL0, SEG_TYPE_RW); /* Data segment */

    gdt_ptr.size = sizeof(gdt);
    gdt_ptr.address = (uint32_t)&gdt[0];

    load_gdt_and_seg((uint32_t)&gdt_ptr);
}