# IA-32 Interrupt

## INTERRUPT DESCRIPTOR TABLE (IDT)
The interrupt descriptor table (IDT) associates each exception or interrupt vector with a gate descriptor for the procedure or task used to service the associated exception or interrupt. Like the GDT and LDTs, the IDT is an array of 8-byte descriptors (in protected mode). Unlike the GDT, the first entry of the IDT may contain a descriptor. To form an index into the IDT, the processor scales the exception or interrupt vector by eight (the number of bytes in a gate descriptor). Because there are only 256 interrupt or exception vectors, the IDT need not contain more than 256 descriptors. It can contain fewer than 256 descriptors, because descriptors are required only for the interrupt and exception vectors that may occur. All empty descriptor slots in the IDT should have the present flag for the Descriptor set to 0. The base addresses of the IDT should be aligned on an 8-byte boundary to maximize performance of cache line fills. The limit value is expressed in bytes and is added to the base address to get the address of the last valid byte. A limit value of 0 results in exactly 1 valid byte. Because IDT entries are always eight bytes long, the limit should always be one less than an integral multiple of eight (that is, 8N – 1).The IDT may reside anywhere in the linear address space. As shown in Figure 6-1, the processor locates the IDT 
using the IDTR register. This register holds both a 32-bit base address and 16-bit limit for the IDT.The LIDT (load IDT register) and SIDT (store IDT register) instructions load and store the contents of the IDTR register, respectively. The LIDT instruction loads the IDTR register with the base address and limit held in a memory operand. This instruction can be executed only when the CPL is 0. It normally is used by the initialization code of an operating system when creating an IDT. An operating system also may use it to change from one IDT to another. The SIDT instruction copies the base and limit value stored in IDTR to memory. This instruction can be executed at any privilege level. If a vector references a descriptor beyond the limit of the IDT, a general-protection exception (#GP) is generated.

![](https://hackmd.io/_uploads/HyLDjlbUh.png)

## Interrupt Procedure
An interrupt gate or trap gate references an exception- or interrupt-handler procedure that runs in the context of the currently executing task (see Figure 6-3). The segment selector for the gate points to a segment descriptor for an executable code segment in either the GDT or the current LDT. The offset field of the gate descriptor points to the beginning of the exception- or interrupt-handling procedure.  

![](https://hackmd.io/_uploads/Hk9GJ4z82.png)

When the processor performs a call to the exception- or interrupt-handler procedure:
**If the handler procedure is going to be executed at a numerically lower privilege level, a stack switch occurs. When the stack switch occurs**: 
1. The segment selector and stack pointer for the stack to be used by the handler are obtained from the TSS for the currently executing task. **On this new stack**, the processor pushes the stack segment selector and stack pointer of the interrupted procedure.  
2. The processor then saves the current state of the EFLAGS, CS, and EIP registers on the new stack (see Figures 6-4).  
3. If an exception causes an error code to be saved, it is pushed on the new stack after the EIP value.  

**If the handler procedure is going to be executed at the same privilege level as the interrupted procedure**:
1. The processor saves the current state of the EFLAGS, CS, and EIP registers on the current stack (see Figures 6-4).  
2. If an exception causes an error code to be saved, it is pushed on the current stack after the EIP value.  

![](https://hackmd.io/_uploads/Hk1hgEzU2.png)

To return from an exception- or interrupt-handler procedure, the handler must use the IRET (or IRETD) instruction. The IRET instruction is similar to the RET instruction except that it restores the saved flags into the EFLAGS register. The IOPL field of the EFLAGS register is restored only if the CPL is 0. The IF flag is changed only if the CPL is less than or equal to the IOPL.  

If a stack switch occurred when calling the handler procedure, the IRET instruction switches back to the interrupted procedure’s stack on the return.