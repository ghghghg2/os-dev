#ifndef GDT_H
#define GDT_H

#include "stdint.h"


#define NUM_SEG_DESCRIPTORS (3)

#define PL0 (0x0)
#define PL3 (0x3)
#define SEG_TYPE_RW (0x2)
#define SEG_TYPE_RX (0xA)

#define SEG_KERNEL_CS 0x08
#define SEG_KERNEL_DS 0x10


#define SEG_BASE    (0x0U)
#define SEG_LIMIT   (0xFFFFFU)

struct seg_descriptor_t {
    uint16_t seg_lim_low;
    uint16_t base_addr_low;
    uint8_t base_addr_mid;
    uint8_t seg_type: 4;
    uint8_t descriptor_type: 1; /* 0 = system; 1 = code or data */
    uint8_t dpl: 2; /* Descriptor privilege level */
    uint8_t seg_present: 1; /*  Segment present */
    uint8_t seg_lim_high: 4;
    uint8_t avl: 1; /* Available for use by system software */
    uint8_t L_flag: 1; /* 1 = 64 bit code */
    uint8_t default_op_size: 1;  /* 0 = 16-bit segment; 1 = 32-bit segment */
    uint8_t granularity: 1; /* Determines the scaling of the segment limit field. When the granularity flag is clear, the segment 
                            limit is interpreted in byte units; when flag is set, the segment limit is interpreted in 4-KByte units. */
    uint8_t base_addr_high;
}__attribute__((packed));
typedef struct seg_descriptor_t seg_descriptor_t;

struct gdt_ptr_t {
    uint16_t size;
    uint32_t address;
} __attribute__((packed));
typedef struct gdt_ptr_t gdt_ptr_t;

void gdt_initialize(void);

#endif