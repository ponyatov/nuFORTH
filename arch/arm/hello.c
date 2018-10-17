// bare metal hello world for QEMU-arm (arm826 versatilepb)

#include <stdint.h>

// https://balau82.wordpress.com/2010/02/28/hello-world-for-bare-metal-arm-using-qemu/

volatile uint32_t *UART0DR = (uint32_t *)0x101f1000;	// UART0 data register

// QEMU model of the PL011 serial port ignores the transmit FIFO capabilities
// on real systems the `Transmit FIFO Full` flag must be checked
 
void print_uart0(const char *s) {
	while(*s != '\0') {					/* Loop until end of string */
		*UART0DR = (unsigned int)(*s);	/* Transmit char */
		s++;							/* Next char */
	}
}
 
void c_entry() {
	print_uart0("Hello world!\n");		// print message
}

