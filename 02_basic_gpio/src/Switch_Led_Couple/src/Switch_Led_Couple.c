/**
 * @author  Pedro Botelho
 * @file    Switch_Led_Couple.c
 * @brief   If SW1, in PTD4, is pressed, light LED_GREEN_D1, PTC8.
 * 			If SW2 is pressed, PTA12, light LED_GREEN_D3, PTA13.
 *
 * 			Use of Polling Technique and Peripheral Registers.
 */

#include "MKL25Z4.h"
#include "Switch_Led_Couple.h"

int main(void) {
	init_pins();
	while(1) {
		if(TestBit(GPIOD->PDDR, SW1_BIT)) {
			// If SW1 is pressed, toggle the level of LED D1.
			SetBit(GPIOC->PTOR, LED_GREEN_D1_BIT);
		}
		if(TestBit(GPIOD->PDDR, SW2_BIT)) {
			// If SW2 is pressed, toggle the level of LED D3.
			SetBit(GPIOC->PTOR, LED_GREEN_D3_BIT);
		}
	}
}

void init_pins(void) {
	// Enable the clock to the used ports.
	SetBit(SIM->SCGC5, CLOCK_PORTA_BIT);
	SetBit(SIM->SCGC5, CLOCK_PORTC_BIT);
	SetBit(SIM->SCGC5, CLOCK_PORTD_BIT);

	// Configures the pins as GPIO.
	SetBit(PORTC->PCR[LED_GREEN_D1_BIT], MUX_GPIO_FUNCTION);
	SetBit(PORTA->PCR[LED_GREEN_D3_BIT], MUX_GPIO_FUNCTION);
	SetBit(PORTD->PCR[SW1_BIT], MUX_GPIO_FUNCTION);
	SetBit(PORTA->PCR[SW2_BIT], MUX_GPIO_FUNCTION);

	// Configure the LED pins as OUTPUT.
	SetBit(GPIOC->PDDR, LED_GREEN_D1_BIT);
	SetBit(GPIOA->PDDR, LED_GREEN_D3_BIT);

	// Configure the SWITCH pins as INPUT.
	ClearBit(GPIOD->PDDR, SW1_BIT);
	ClearBit(GPIOA->PDDR, SW2_BIT);
}
