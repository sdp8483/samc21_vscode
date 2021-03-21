#include <sam.h>

int main(void) {
	/* Initializes MCU, drivers and middleware */
	// atmel_start_init();	/* don't use Atmel Start Code */

	/* Initialize Clock ------------------------------------------------------*/
	NVMCTRL->CTRLB.bit.RWS = 1;	/* 1 wait state required for 48MHz clock */

	/* change 48MHz Oscillator divider from default of 0b1011, see pg214 of datasheet */
	OSCCTRL->OSC48MDIV.bit.DIV = 0b0000;

	/* enable clock output to a corresponding GCLK_IO[0] */
	GCLK->GENCTRL->bit.OE = 1;

	/* peripheral function H for PA14, this enables GCLK_IO output, pg29 and pg457 of datasheet */
	PORT->Group[0].PMUX[7].bit.PMUXE = 7;

	/* enable peripheral multiplexer selection */
	PORT->Group[0].PINCFG[14].bit.PMUXEN = 1;

	/* GPIO setup ------------------------------------------------------------*/
	PORT->Group[0].DIRSET.reg = PORT_PA15;	/* Set PA15 as output, onboard LED is connected */

	while (1) {
		/* this little LED of mine, I'm going to let it blink */
		PORT->Group[0].OUTTGL.reg = PORT_PA15;
		for(uint32_t i=0; i<5000000UL; i++);	/* delay */
	}
}
