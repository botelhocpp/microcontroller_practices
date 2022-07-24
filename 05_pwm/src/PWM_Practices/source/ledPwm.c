/**
 * LED PWM OSCILATION (WITH CONTROL REGISTERS):
 *
 * @author Pedro M. Botelho
 * @brief  Control the embedded green LED,
 * in PTD5, luminosity level, varying it
 * between mininum and maximum.
 *
 * You can control the speed of the variation,
 * decrementing or incrementing LED_INCREASE_RATE
 * value.
 */

#include "project_select.h"
#if PROJECT == 1

// ====================================================================================
// LIBRARIES
// ====================================================================================

#include "K32L2B31A.h"

#include <stdint.h>
#include <stdbool.h>

// ====================================================================================
// LED CONTROL
// ====================================================================================

#define LED_MAX_VALUE 		29999
#define LED_INCREASE_RATE 	1

// ====================================================================================
// FUNCTION PROTOTYPES
// ====================================================================================

/* Configure PTD5 as PWM (Channel 5 of TPM0 module). */
void initLedPwm(void);

/* Set the pulse width for the PWM. */
void setLedDutyCycle(uint16_t channel_value);

// ====================================================================================
// MAIN CODE
// ====================================================================================

int main(void) {

	initLedPwm();

	double channel_value = 0;
	bool increase_value = true;

	while(1) {
		if(increase_value) {
			channel_value += LED_INCREASE_RATE;
			if((int) channel_value > (LED_MAX_VALUE - 1)) {
				increase_value = false;
			}
		}
		else {
			channel_value -= LED_INCREASE_RATE;
			if((int) channel_value < 1) {
				increase_value = true;
			}
		}
		setLedDutyCycle((int) channel_value);
	}
}

// ====================================================================================
// FUNCTION IMPLEMENTATIONS
// ====================================================================================

void initLedPwm(void) {
	/* Enable MCGPCLK (HIRC) AS 48 MHz. */
	MCG->MC |= (1U << 7);

	/* Configure PTD5 as TPM0_CH5. */
	SIM->SCGC5 |= (1U << 12);
	PORTD->PCR[5] = (0b100U << 8);

	/* Configure MCGPCLK for TPM0. */
	SIM->SCGC6 |= (1U << 24);
	SIM->SOPT2 |= (0b01U << 24);

	/* Configure a divide-by-32 prescaler. */
	TPM0->SC = (0b101U << 0);

	/* Set a 50Hz Refresh Rate: (48MHz/32)/50Hz = 30000 - 1 */
	TPM0->MOD = 29999;

	/* Set the PWM to Low-true and Edge-aligned */
	// TPM0->CONTROLS[5].CnSC = (0b1001U << 2);
	TPM0->CONTROLS[5].CnSC = (0b1001U << 2);

	/* Initial Duty Cycle is 0% */
	TPM0->CONTROLS[5].CnV = 0;

	/* Initialize the counter. */
	TPM0->SC |= (0b01U << 3);
}

void setLedDutyCycle(uint16_t channel_value) {
	TPM0->CONTROLS[5].CnV = channel_value;
}

#endif
