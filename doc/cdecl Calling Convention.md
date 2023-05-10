# cdecl Calling Convention
> Reference
> [x86 calling convention](https://en.wikipedia.org/wiki/X86_calling_conventions)

cdecl
The cdecl (which stands for C declaration) is a calling convention for the C programming language and is used by many C compilers for the x86 architecture.[1] In cdecl, subroutine arguments are passed on the stack. Integer values and memory addresses are returned in the EAX register, floating point values in the ST0 x87 register. Registers EAX, ECX, and EDX are caller-saved, and the rest are callee-saved. The x87 floating point registers ST0 to ST7 must be empty (popped or freed) when calling a new function, and ST1 to ST7 must be empty on exiting a function. ST0 must also be empty when not used for returning a value.

In the context of the C programming language, function arguments are pushed on the stack in the right-to-left order, i.e. the last argument is pushed first.

Consider the following C source code snippet:

```C=
int callee(int, int, int);

int caller(void)
{
	return callee(1, 2, 3) + 5;
}
```
On x86, it might produce the following assembly code (Intel syntax):
```Clike=
caller:
    ; make new call frame
    ; (some compilers may produce an 'enter' instruction instead)
    push    ebp       ; save old call frame
    mov     ebp, esp  ; initialize new call frame
    ; push call arguments, in reverse
    ; (some compilers may subtract the required space from the stack pointer,
    ; then write each argument directly, see below.
    ; The 'enter' instruction can also do something similar)
    ; sub esp, 12      : 'enter' instruction could do this for us
    ; mov [ebp-4], 3   : or mov [esp+8], 3
    ; mov [ebp-8], 2   : or mov [esp+4], 2
    ; mov [ebp-12], 1  : or mov [esp], 1
    push    3
    push    2
    push    1
    call    callee    ; call subroutine 'callee'
    add     esp, 12   ; remove call arguments from frame
    add     eax, 5    ; modify subroutine result
                      ; (eax is the return value of our callee,
                      ; so we don't have to move it into a local variable)
    ; restore old call frame
    ; (some compilers may produce a 'leave' instruction instead)
    mov     esp, ebp  ; most calling conventions dictate ebp be callee-saved,
                      ; i.e. it's preserved after calling the callee.
                      ; it therefore still points to the start of our stack frame.
                      ; we do need to make sure
                      ; callee doesn't modify (or restore) ebp, though,
                      ; so we need to make sure
                      ; it uses a calling convention which does this
    pop     ebp       ; restore old call frame
    ret               ; return
```

* ***Note***. 
`call` does 2 things: 
    1. Push return	address	on	stack	
    2. Jump to label