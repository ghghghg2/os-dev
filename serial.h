#ifndef SERIAL_H
#define SERIAL_H

/* https://wiki.osdev.org/Serial_Ports */

/* The I/O ports */

/* All the I/O ports are calculated relative to the data port. This is because
* all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
* order, but they start at different values.
*/

#define SERIAL_COM1_BASE                0x3F8      /* COM1 base port */

/** serial_configure_baud_rate:
 *  Sets the speed of the data being sent. The default speed of a serial
 *  port is 115200 bits/s. The argument is a divisor of that number, hence
 *  the resulting speed becomes (115200 / divisor) bits/s.
 *
 *  @param com      The COM port to configure
 *  @param divisor  The divisor
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

/** serial_configure_fifo:
 *  Configures the fifo of the given serial port. 
 *  - Enables FIFO
 *  - Clear both receiver and transmission FIFO queues
 *  - Use 14 bytes as size of queue
 *
 *  @param com  The serial port to configure
 */

/** serial_configure_line:
 *  Configures the line of the given serial port. The port is set to have a
 *  data length of 8 bits, no parity bits, one stop bit and break control
 *  disabled.
 *
 *  @param com  The serial port to configure
 */
void serial_configure_line(unsigned short com);

void serial_configure_fifo(unsigned short com);

/** serial_configure_modem:
 *  Configures the modem of the given serial port. 
 *  The modem control register is used for very simple hardware flow control via the Ready To Transmit (RTS) and 
 *  Data Terminal Ready (DTR) pins. When configuring the serial port we want RTS and DTR to be 1, which means 
 *  that we are ready to send data.
 *
 *  @param com  The serial port to configure
 */

void serial_configure_modem(unsigned short com);

/** serial_is_transmit_fifo_empty:
 *  Checks whether the transmit FIFO queue is empty or not for the given COM
 *  port.
 *
 *  @param  com The COM port
 *  @return 0 if the transmit FIFO queue is not empty
 *          1 if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty(unsigned int com);

/** serial_write:
 * Write the bytes in buffer to serial port.
 *
 *  @param  com The COM port
 *  @param  buf The buffer contains bytes to transmit.
 *  @param  len Num ber of bytes to transmit in buf.
 */
void serial_write(unsigned int com, char *buf, unsigned short len);

#endif