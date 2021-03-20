// #include <atmel_start.h>
#include <samc21.h>

#define REG_PORTA_PMUX7 (*(RwReg8 *) 0x41000037UL)	/* PortA pin mux register address for PA14 */
#define REG_PA14_PINCFG (*(RwReg8 *) 0x4100004eUL)	/* PortA pin config register addres for PA14 */

int main(void) {
	/* Initializes MCU, drivers and middleware */
	// atmel_start_init();

	/* change 48MHz Oscillator divider from default of 0b1011, see pg 214 of datasheet */
	REG_OSCCTRL_OSC48MDIV = 0b0001;
	while (REG_OSCCTRL_OSC48MSYNCBUSY != 0); // wait? may not be necessary

	/* Output GCLK to a GPIO so we can check the frequency 
	 * PA14 is used for GCLK_IO[0] peripheral function H (0x7), page 28 and 457 of datasheet
	 * By Default the internal 48MHz oscillator is divided by 12 so pin should cycle at a freqency of 4MHz when REG_OSCCTRL_OSC48MDIV = 0b1011
	 * When REG_OSCCTRL_OSC48MDIV = 0b0001 frequency should be 24MHz
	 * Setting REG_OSCCTRL_OSC48MDIV = 0b0000 should give full 48MHz
	 */
	REG_GCLK_GENCTRL0 |= (1 << 11);
	REG_PORTA_PMUX7 |= 0x7;
	REG_PA14_PINCFG |= 1;

	/* Set PA15 as output, onboard LED is connected */
	REG_PORT_DIR0 |= (1 << 15);

	while (1) {
		/* this little LED of mine, I'm going to let it blink */
		REG_PORT_OUTTGL0 |= (1 << 15);
		for(uint32_t i=0; i<5000000UL; i++);
	}
}
