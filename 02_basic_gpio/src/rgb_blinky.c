/*
 * @file rgb_blinky.c
 *
 * @author: Pedro Botelho
 * @date:   06/04/2022
 *
 * @brief: Blinks the on-board RGB LEDs, of the
 * FRDM-KL25Z development board.
 */

#include <MKL25Z4.h>

#define BitSet(valor, bit) ((valor) |=  (1 << bit))
#define BitClr(valor, bit) ((valor) &= ~(1 << bit))

/*
 * Proper pin configuration. Enable the clock to PORTB and
 * PORTD, select the GPIO function to the pins B18, B19
 * and D1, and set the data direction of these three pins
 * to OUTPUT.
 */
void init_pins(void);

/*
 * Delay the execution by the given value, in microseconds.
 */
void delayMs(int ms);

/*
 * Turn on the three leds, wait 0,5s, turn then off, wait 
 * more 0,5s, then repeat.
 */
int main(void) {
	//SETUP
	init_pins();

	//LOOP
	while(1) {
		//Activate LEDs.
		BitSet(PTB->PDOR, 18);
		BitSet(PTB->PDOR, 19);
		BitSet(PTD->PDOR, 1);
		delayMs(500);

		//Deactivate LEDs.
		BitClr(PTB->PDOR, 18);
		BitClr(PTB->PDOR, 19);
		BitClr(PTD->PDOR, 1);
		delayMs(500);
	}
}

void init_pins(void) {
	//Enable the clock to PORTB and PORTD.
	BitSet(SIM->SCGC5, 10);
	BitSet(SIM->SCGC5, 12);

	//Set GPIO function in the MUX for B18,
	//B19 and D1.
	BitSet(PORTB->PCR[18], 8);
	BitSet(PORTB->PCR[19], 8);
	BitSet(PORTD->PCR[1], 8);

	//Set OUTPUT orientation for B18, B19
	//and D1.
	BitSet(PTB->PDDR, 18);
	BitSet(PTB->PDDR, 19);
	BitSet(PTD->PDDR, 1);
}

void delayMs(int ms) {
	int i, j;
	for(i = 0; i < ms; i++) {
		for(j = 0; j < 7000; j++);
	}
}