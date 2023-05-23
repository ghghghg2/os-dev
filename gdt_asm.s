global load_gdt_and_seg

section .text

SEG_KERNEL_CS equ 0x08
SEG_KERNEL_DS equ 0x10

load_gdt_and_seg:
    mov eax, [esp + 4]
    lgdt [eax]
    ; far jump to set cs
    jmp SEG_KERNEL_CS:.config_segment

.config_segment:
    ; we only use one segment for data
    mov     ax, SEG_KERNEL_DS
    mov     ds, ax
    mov     ss, ax
    mov     es, ax
    mov     gs, ax
    mov     fs, ax
    ret