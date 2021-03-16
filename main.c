#include <atmel_start.h>

int main(void) {
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	REG_PORT_DIR0 |= (1 << 15);

	/* Replace with your application code */
	while (1) {
		REG_PORT_OUTTGL0 |= (1 << 15);
		for(uint32_t i=0; i<50000; i++);
	}
}
