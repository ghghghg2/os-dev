
extern interrupt_handler

global enable_interrupts
global disable_interrupts

%macro no_error_code_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	push	dword 0
	push	dword %1
	jmp		common_interrupt_handler
%endmacro

%macro error_code_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	push	dword %1
	jmp		common_interrupt_handler
%endmacro


section .text

common_interrupt_handler:
    push    esp
    ; BEWARE: DON'T ADD INSTRUCTIONS ABOVE THIS LINE IF YOU DON'T KNOW WHAT THE
    ;         INSTRUCTIONS FOLLOWING THIS COMMENT DOES!
    ; This step make the popped esp (below) ignore Error Code and Interrupt Number on the stack.
    add     DWORD [esp], 8
	push	eax
	push	ebx
	push	ecx
	push	edx
	push	ebp
	push	esi
	push	edi
	call	interrupt_handler
	pop	    edi
	pop	    esi
	pop	    ebp
	pop	    edx
	pop	    ecx
	pop	    ebx
	pop	    eax
	pop     esp
	iret

enable_interrupts:
    sti
    ret

disable_interrupts:
    cli
    ret

; /* Table 6-1. Protected-Mode Exceptions and Interrupts Intel® 64 and IA-32 Architectures
; Software Developer’s Manual Volume 3A: System Programming Guide, Part 1*/

; protected mode exceptions
no_error_code_handler 0
no_error_code_handler 1
no_error_code_handler 2
no_error_code_handler 3
no_error_code_handler 4
no_error_code_handler 5
no_error_code_handler 6
no_error_code_handler 7
error_code_handler 8
no_error_code_handler 9
error_code_handler 10
error_code_handler 11
error_code_handler 12
error_code_handler 13
error_code_handler 14
no_error_code_handler 15
no_error_code_handler 16
error_code_handler 17
no_error_code_handler 18
no_error_code_handler 19

; /* PIC interrupt */
; irqs
no_error_code_handler 32
no_error_code_handler 33
no_error_code_handler 34
no_error_code_handler 35
no_error_code_handler 36
no_error_code_handler 37
no_error_code_handler 38
no_error_code_handler 39
no_error_code_handler 40
no_error_code_handler 41
no_error_code_handler 42
no_error_code_handler 43
no_error_code_handler 44
no_error_code_handler 45
no_error_code_handler 46
no_error_code_handler 47