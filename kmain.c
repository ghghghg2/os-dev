#include "io.h"


/* Frame Buffer Data Layout */
/* The framebuffer has 80 columns and 25 rows */
/*
Bit:     | 15 14 13 12 11 10 9 8 | 7 6 5 4 | 3 2 1 0 |
Content: | ASCII                 | FG      | BG      |
*/
/* Constant */
#define FB_BASE_ADDRESS (0x000B8000)
#define FB_COLOR_BLACK (0)
#define FB_COLOR_BLUE (1)
#define FB_COLOR_GREEN (2)
#define FB_COLOR_CYAN (3)
#define FB_COLOR_RED (4)
#define FB_COLOR_BROWN (6)
#define FB_COLOR_LIGHT_GREY (7)
#define FB_COLOR_LIGHT_RED (12)
#define FB_COLOR_LIGHT_BROWN (14)
#define FB_COLOR_WHITE (15)

/* Data */
static char *fb = (char *)FB_BASE_ADDRESS;

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
static void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

int kmain(void)
{
    fb_write_cell(0, 'A', FB_COLOR_GREEN, FB_COLOR_BLACK);
    fb_move_cursor(5);
    return 0xdeafbeef;
}