/*
 * @file blinky.c
 *
 * @author: Pedro Botelho
 * @date:   06/04/2022
 *
 * @brief: Blink the on-board blue LED, of the
 * FRDM-KL25Z development board.
 */

#include <MKL25Z4.h>

#define BitSet(value, bit) ((value) |=  (1 << bit)) // Enable the bit in value.
#define BitClr(value, bit) ((value) &= ~(1 << bit)) // Clean the bit in value.

int main(void) {
	BitSet(SIM->SCGC5, 12);   // Enable the clock for PORTD.
	BitSet(PORTD->PCR[1], 8); // Select GPIO function to D1.
	BitSet(PTD->PDDR, 1);     // Set D1 to data OUTPUT.
	while(1) {
		BitSet(PTD->PDOR, 1);   // Turn ON the LED.
		delayMs(500);           // Wait 0,5s.
		BitClr(PTD->PDOR, 1);   // Turn OFF the LED.
		delayMs(500);           // Wait 0,5s.
	}
}

void delayMs(int ms) {
	int i, j;
	for(i = 0; i < ms; i++) {
		for(j = 0; j < 7000; j++);
	}
}