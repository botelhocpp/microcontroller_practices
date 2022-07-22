#include "pwm_project.h"
#if PROJECT == 1

/**
 * @author Pedro M. Botelho
 * @brief  Obtains the digital data from a potentiometer,
 * connected to an ADC, and shows it in the Semihost Console.
 * @date   2022-07-21
 */

// ==========================================================================
// LIBRARIES
// ==========================================================================
#include "K32L2B31A.h"

#include <stdio.h>

#include <stdbool.h>

#include "k32l2b3/adc.h"
#include "k32l2b3/clock.h"
#include "k32l2b3/port.h"
#include "k32l2b3/delay.h"

// ==========================================================================
// ADC CONTROL
// ==========================================================================

adc_channel potentiometer;

#define POTENTIOMETER_MAX_VALUE 	65535

// ==========================================================================
// FUNCTIONS PROTOTYPES
// ==========================================================================

/**
 * Initialize a Potentiometer ADC in PTB1 (Channel 9 of ADC0 module).
 */
void initPotentiometerComponent(void);

// ==========================================================================
// MAIN CODE
// ==========================================================================

int main(void) {

	clkEnableClock(clkSOURCE_LIRCLK_8MHz);
	clkSetMainClock(clkSOURCE_LIRCLK_8MHz);

	initPotentiometerComponent();

	uint16_t potentiometer_input;
	uint32_t voltage;

	while(1) {
		potentiometer_input = adcReadInput(potentiometer);
		voltage = (potentiometer_input*3300)/POTENTIOMETER_MAX_VALUE;
		printf("Digital Input: %d\nAnalog Input: %d mV\n", potentiometer_input, voltage);
		delay_ms(100);
	}
}

// ==========================================================================
// FUNCTIONS IMPLEMENTATION
// ==========================================================================

void initPotentiometerComponent(void) {
	portSetPinMux(pinPORT_B, 1, pinMUX_ALT_0);

	potentiometer = adcCHANNEL_9;

	adc_config_t adc_module;
	adcGetDefaultConfig(&adc_module);
	adcInitModule(&adc_module);
}
#endif
