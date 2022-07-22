#include "pwm_project.h"
#if PROJECT == 3

/**
 * @author Pedro M. Botelho
 * @brief  Obtains the digital data from the temperature sensor,
 * LM35, connected to an ADC, and shows the calculated temperature
 * in the Semihost Console.
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

adc_channel temperature_sensor;

#define ADC_MAX_VALUE 	65535

// ==========================================================================
// FUNCTIONS PROTOTYPES
// ==========================================================================

/**
 * Initialize the LM35 temperature sensor ADC in PTB1 (Channel 9 of ADC0 module).
 */
void initLm35Component(void);

// ==========================================================================
// MAIN CODE
// ==========================================================================

int main(void) {

	clkEnableClock(clkSOURCE_LIRCLK_8MHz);
	clkSetMainClock(clkSOURCE_LIRCLK_8MHz);

	initLm35Component();

	uint16_t sensor_input;
	uint32_t temperature;

	while(1) {
		sensor_input = adcReadInput(temperature_sensor);
		temperature = (sensor_input*330.0)/ADC_MAX_VALUE;
		printf("Temperature %d °C\n", temperature);
		delay_ms(100);
	}
}

// ==========================================================================
// FUNCTIONS IMPLEMENTATION
// ==========================================================================

void initLm35Component(void) {
	portSetPinMux(pinPORT_B, 1, pinMUX_ALT_0);

	temperature_sensor = adcCHANNEL_9;

	adc_config_t adc_module;
	adcGetDefaultConfig(&adc_module);
	adcInitModule(&adc_module);
}
#endif
