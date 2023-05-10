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

int kmain(void)
{
    fb_write_cell(0, 'A', FB_COLOR_GREEN, FB_COLOR_BLACK);
    return 0xdeafbeef;
}