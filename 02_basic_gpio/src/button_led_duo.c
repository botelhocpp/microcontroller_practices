/*
 * @file button_led_duo.c
 *
 * @author: Pedro Botelho
 * @date:   06/04/2022
 *
 * @brief: Light a LED, in C8, whenever a
 * button, in D4, is pressed.
 */

#include "MKL25Z4.h"

#define BitSet(valor, bit) ((valor) |=  (1 << bit))
#define BitClr(valor, bit) ((valor) &= ~(1 << bit))
#define BitTst(valor, bit) ((valor) &   (1 << bit))

/*
 * Proper pin configuration. Enable the clock to PORTC and
 * PORTD, select the GPIO function to the pins C8 and D4,
 * set the data direction of the C8, the LED, to OUTPUT,
 * and of D4, the button, to INPUT.
 */
void init_pins();

/*
 * Checks if the button is pressed. If so, turn on the LED.
 * If not, turn it off.
 */
int main(void) {
	//SETUP
	init_pins();

	//LOOP
	while(1) {
		if(BitTst(PTD->PDIR, 4)) {
			BitSet(PTC->PDOR, 8);
		}
		else {
			BitClr(PTC->PDOR, 8);
		}
	}
}

void init_pins() {
	//Enable the clock to PORTC and PORTD.
	BitSet(SIM->SCGC5, 11);
	BitSet(SIM->SCGC5, 12);
	
	//Set GPIO function in the MUX for C8,
	//D4.
	BitSet(PORTD->PCR[4], 8);
	BitSet(PORTC->PCR[8], 8);
 
	//Set OUTPUT orientation for C8, the LED.
	BitSet(PTC->PDDR, 8);

	//Set INPUT orientation for D4, the button.
	BitClr(PTD->PDDR, 4);
}
