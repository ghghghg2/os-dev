# Segmentation

> Ref:
> [Intel, Intel 64 and iA-32 architectures software developer’s manual vol. 3A ](http://www.intel.com/content/www/us/en/architecture-and-technology/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.html/)

## Overview
![](https://hackmd.io/_uploads/Bkf-YDqr2.png)

## Segment Descriptor
![](https://hackmd.io/_uploads/HkSatvqSh.png)


## Flat Model
The simplest memory model for a system is the basic “flat model,” in which the operating system and application programs have access to a continuous, unsegmented address space. To the greatest extent possible, this basic flat model hides the segmentation mechanism of the architecture from both the system designer and the application programmer.
To implement a basic flat memory model with the IA-32 architecture, at least two segment descriptors must be created, one for referencing a code segment and one for referencing a data segment (see Figure 3-2). Both of these segments, however, are mapped to the entire linear address space: that is, both segment descriptors have the same base address value of 0 and the same segment limit of 4 GBytes. By setting the segment limit to 4 GBytes, the segmentation mechanism is kept from generating exceptions for out of limit memory references, even if no physical memory resides at a particular address. ROM (EPROM) is generally located at the top of the physical address space, because the processor begins execution at FFFF_FFF0H. RAM (DRAM) is placed at the bottom of the address space because the initial base address for the DS data segment after reset initialization is 0.

## Privilege Level

> Ref: [Call Gates' Ring Transitioning in IA-32 Mode](https://rayanfam.com/topics/call-gates-ring-transitioning-in-ia-32-mode/)

**Current Privilege Level (CPL)**
CPL is stored in the selector of currently executing CS register. It represents the privilege level (PL) of the currently executing task. It is also PL in the descriptor of the code segment and designated as Task Privilege Level (TPL).

**Descriptor Privilege Level (DPL)**
It is the PL of the object which is being attempted to be accessed by the current task or in the other words, the least privilege level for the caller to use this gate.

**Requestor Privilege Level (RPL)**
It is the lowest two bits of any selector. It can be used to weaken the CPL if desired.

The Effective Privilege Level (EPL) is EPL = max (CPL, RPL) (here numbers) Thus the task becomes less privileged.

Note that PL refers to Privilege Level.

Keep in mind that the above concepts also applies in other Intel structures