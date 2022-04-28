/**
 * @author  Pedro Botelho
 * @file    Rainbow_Blinky.c
 * @brief   Light the RGB LED in all the 7 rainbow colors:
 * 			R			(Red)
 * 			G			(Green)
 * 			B			(Blue)
 * 			R + G 		(Yellow)
 * 			R + B 		(Magenta)
 * 			B + G 		(Cyan)
 * 			R + B + G 	(White)
 *
 * 			Use of Peripheral Registers.
 */

#include "Rainbow_Blinky.h"
#include "MKL25Z4.h"

int main(void) {
	init_pins();
	while(1){
		// Red Color:
		SetBit(GPIOB->PSOR, LED_RED_BIT);
		SetBit(GPIOB->PCOR, LED_GREEN_BIT);
		SetBit(GPIOD->PCOR, LED_BLUE_BIT);
		delay_ms(PULSE_WIDTH);

		// Green Color:
		SetBit(GPIOB->PCOR, LED_RED_BIT);
		SetBit(GPIOB->PSOR, LED_GREEN_BIT);
		SetBit(GPIOD->PCOR, LED_BLUE_BIT);
		delay_ms(PULSE_WIDTH);

		// Blue Color:
		SetBit(GPIOB->PCOR, LED_RED_BIT);
		SetBit(GPIOB->PCOR, LED_GREEN_BIT);
		SetBit(GPIOD->PSOR, LED_BLUE_BIT);
		delay_ms(PULSE_WIDTH);

		// Yellow Color:
		SetBit(GPIOB->PSOR, LED_RED_BIT);
		SetBit(GPIOB->PSOR, LED_GREEN_BIT);
		SetBit(GPIOD->PCOR, LED_BLUE_BIT);
		delay_ms(PULSE_WIDTH);

		// Magenta Color:
		SetBit(GPIOB->PSOR, LED_RED_BIT);
		SetBit(GPIOB->PCOR, LED_GREEN_BIT);
		SetBit(GPIOD->PSOR, LED_BLUE_BIT);
		delay_ms(PULSE_WIDTH);

		// Cyan Color:
		SetBit(GPIOB->PCOR, LED_RED_BIT);
		SetBit(GPIOB->PSOR, LED_GREEN_BIT);
		SetBit(GPIOD->PSOR, LED_BLUE_BIT);
		delay_ms(PULSE_WIDTH);

		// White Color:
		SetBit(GPIOB->PSOR, LED_RED_BIT);
		SetBit(GPIOB->PSOR, LED_GREEN_BIT);
		SetBit(GPIOD->PSOR, LED_BLUE_BIT);
		delay_ms(PULSE_WIDTH);
	}
}

void init_pins(void) {
	// Enable the clock for the PORTB and PORTD peripherals.
	SetBit(SIM->SCGC5, CLOCK_PORTB_BIT);
	SetBit(SIM->SCGC5, CLOCK_PORTD_BIT);

	// Select the GPIO function for pins PTB18, PTB19 and PTD1.
	SetBit(PORTB->PCR[LED_RED_BIT], MUX_GPIO_FUNCTION);
	SetBit(PORTB->PCR[LED_GREEN_BIT], MUX_GPIO_FUNCTION);
	SetBit(PORTD->PCR[LED_BLUE_BIT],  MUX_GPIO_FUNCTION);

	// Make PTB18, PTB19 and PTD1 OUTPUT pins.
	SetBit(GPIOB->PDDR, LED_RED_BIT);
	SetBit(GPIOB->PDDR, LED_GREEN_BIT);
	SetBit(GPIOD->PDDR, LED_BLUE_BIT);
}

void delay_ms(int ms) {
	int i, j;
	for(i = 0; i < ms; i++) {
		for(j = 0; j < 7000; j++);
	}
}
