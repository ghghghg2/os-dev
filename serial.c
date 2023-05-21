#include "serial.h"
#include "io.h"

#define SERIAL_DATA_PORT(base)          ((base))
#define SERIAL_FIFO_COMMAND_PORT(base)  ((base) + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  ((base) + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) ((base) + 4)
#define SERIAL_LINE_STATUS_PORT(base)   ((base) + 5)

/* The I/O port commands */

/* SERIAL_LINE_ENABLE_DLAB:
* Tells the serial port to expect first the highest 8 bits on the data port,
* then the lowest 8 bits will follow
*/
#define SERIAL_LINE_ENABLE_DLAB         0x80

/** serial_configure_baud_rate:
 *  Sets the speed of the data being sent. The default speed of a serial
 *  port is 115200 bits/s. The argument is a divisor of that number, hence
 *  the resulting speed becomes (115200 / divisor) bits/s.
 *
 *  @param com      The COM port to configure
 *  @param divisor  The divisor
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

/** serial_configure_line:
 *  Configures the line of the given serial port. The port is set to have a
 *  data length of 8 bits, no parity bits, one stop bit and break control
 *  disabled.
 *
 *  @param com  The serial port to configure
 */
void serial_configure_line(unsigned short com)
{
    /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
        * Content: | d | b | prty  | s | dl  |
        * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
        */
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}


/** serial_configure_fifo:
 *  Configures the fifo of the given serial port. 
 *  - Enables FIFO
 *  - Clear both receiver and transmission FIFO queues
 *  - Use 14 bytes as size of queue
 *
 *  @param com  The serial port to configure
 */

void serial_configure_fifo(unsigned short com)
{
    /* 
    *   Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
    *   Content: | lvl | bs | r | dma | clt | clr | e |
    */
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

/** serial_configure_modem:
 *  Configures the modem of the given serial port. 
 *  The modem control register is used for very simple hardware flow control via the Ready To Transmit (RTS) and 
 *  Data Terminal Ready (DTR) pins. When configuring the serial port we want RTS and DTR to be 1, which means 
 *  that we are ready to send data.
 *
 *  @param com  The serial port to configure
 */

void serial_configure_modem(unsigned short com)
{
    /* 
    *   Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
    *   Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
    */
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

/** serial_is_transmit_fifo_empty:
 *  Checks whether the transmit FIFO queue is empty or not for the given COM
 *  port.
 *
 *  @param  com The COM port
 *  @return 0 if the transmit FIFO queue is not empty
 *          1 if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty(unsigned int com)
{
    /* 0x20 = 0010 0000 */
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

/** serial_write:
 * Write the bytes in buffer to serial port.
 *
 *  @param  com The COM port
 *  @param  buf The buffer contains bytes to transmit.
 *  @param  len Num ber of bytes to transmit in buf.
 */
void serial_write(unsigned int com, char *buf, unsigned short len)
{
    for (int i = 0; i < len; i++) {
        while(serial_is_transmit_fifo_empty(com) == 0); /* Spinning */
        outb(SERIAL_DATA_PORT(com), buf[i]);
    }
}
