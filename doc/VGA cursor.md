# VGA cursor
> Reference: 
> [Intel OpenSource HD Graphics PRM](https://01.org/sites/default/files/documentation/snb_ihd_os_vol3_part1_0.pdf)


The CRT controller registers are accessed by writing the index of the desired register into the CRT Controller Index Register at I/O address 3B4h or 3D4h, depending on whether the graphics system is configured for MDA or CGA emulation. The desired register is then accessed through the data port for the CRT controller registers located at I/O address 3B5h or 3D5h, again depending upon the choice of 
MDA or CGA emulation as per MSR[0].

> Reference: 
> [Hardware Level VGA and SVGA Video Programming Information Page **CRT Controller Registers** ](http://www.osdever.net/FreeVGA/vga/crtcreg.htm#0E)

The CRT Controller (CRTC) Registers are accessed via a pair of registers, the CRTC Address Register and the CRTC Data Register. See the Accessing the VGA Registers section for more details. The Address Register is located at port 3x4h and the Data Register is located at port 3x5h.  The value of the x in 3x4h and 3x5h is dependent on the state of the Input/Output Address Select field, which allows these registers to be mapped at 3B4h-3B5h or 3D4h-3D5h.   Note that when the CRTC Registers Protect Enable field is set to 1, writing to register indexes 00h-07h is prevented, with the exception of the Line Compare field of the Overflow Register.

Index 00h -- Horizontal Total Register
Index 01h -- End Horizontal Display Register
Index 02h -- Start Horizontal Blanking Register
Index 03h -- End Horizontal Blanking Register
Index 04h -- Start Horizontal Retrace Register
Index 05h -- End Horizontal Retrace Register
Index 06h -- Vertical Total Register
Index 07h -- Overflow Register
Index 08h -- Preset Row Scan Register
Index 09h -- Maximum Scan Line Register
Index 0Ah -- Cursor Start Register
Index 0Bh -- Cursor End Register
Index 0Ch -- Start Address High Register
Index 0Dh -- Start Address Low Register
Index 0Eh -- Cursor Location High Register
Index 0Fh -- Cursor Location Low Register
Index 10h -- Vertical Retrace Start Register
Index 11h -- Vertical Retrace End Register
Index 12h -- Vertical Display End Register
Index 13h -- Offset Register
Index 14h -- Underline Location Register
Index 15h -- Start Vertical Blanking Register
Index 16h -- End Vertical Blanking
Index 17h -- CRTC Mode Control Register
Index 18h -- Line Compare Register
