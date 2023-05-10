# x86 IN & OUT instructions
>Reference: [StackOverflow: What are IN & OUT instructions in x86 used for?](https://stackoverflow.com/questions/3215878/what-are-in-out-instructions-in-x86-used-for)  

You know how memory addressing works? There's an address bus, a data bus, and some control lines. The CPU puts the address of a byte (or a beginning byte) of memory on the address bus, then raises the READ signal, and some RAM chip hopefully returns the contents of memory at that address by raising or lowering individual lines (corresponding to bits in the byte(s)) on the data bus. This works for both RAM and ROM.

But then there are also I/O devices: Serial and parallel ports, the driver for a PC's tiny internal speaker, disk controllers, sound chips and so on. And those devices also get read from and written to. They also need to be addressed so the CPU accesses the correct device and (usually) the correct data location within a given device.

For some CPU models including the xxx86 series as found in most "modern" PCs, I/O devices share the address space with memory. Both RAM/ROM and IO devices are connected to the same address, data and control lines. For example, the serial port for COM1 is addressed starting at (hex) 03F8. But there's almost certainly memory at the same address.

Here's a really simple diagram:
![](https://hackmd.io/_uploads/Sk02xXtE3.png)


Clearly the CPU needs to talk to either memory or the I/O device, never both. To distinguish between the two, one of the control lines called "M/#IO" asserts whether the CPU wants to talk to memory (line=high) or an I/O device (line=low).

The IN instruction reads from an I/O device, OUT writes. When you use the IN or OUT instructions, the M/#IO is not asserted (held low), so memory doesn't respond and the I/O chip does. For the memory-oriented instructions, M/#IO is asserted so CPU talks to the RAM, and IO devices stay out of the communication.

Under certain conditions the IO devices can drive the data lines and the RAM can read them at the same time. And vice versa. It's called DMA.

Traditionally, serial and printer ports, as well as keyboard, mouse, temperature sensors and so forth were I/O devices. Disks were sort of in between; data transfers would be initiated by I/O commands but the disk controller would usually direct-deposit its data in system memory.

In modern operating systems like Windows or Linux, access to I/O ports is hidden away from "normal" user programs, and there are layers of software, privileged instructions and drivers to deal with the hardware. So in this century, most programmers don't deal with those instructions.