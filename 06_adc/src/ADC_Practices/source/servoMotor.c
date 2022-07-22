#include "pwm_project.h"
#if PROJECT == 2

/**
 * @author Pedro M. Botelho
 * @brief  Control a servo motor, via PWM signal, using a
 * 		   potentiometer connected to an ADC.
 * @date   2022-07-21
 */

// ==========================================================================
// LIBRARIES
// ==========================================================================
#include "K32L2B31A.h"

#include <stdbool.h>

#include "k32l2b3/clock.h"
#include "k32l2b3/adc.h"
#include "k32l2b3/tpm.h"
#include "k32l2b3/port.h"

// ==========================================================================
// ADC CONTROL
// ==========================================================================

adc_channel potentiometer;

#define POTENTIOMETER_MIN_VALUE		0
#define POTENTIOMETER_MAX_VALUE 	65535

// ==========================================================================
// PWM CONTROL
// ==========================================================================

#define SERVO_0_DEGREE 		62		// For 0.5ms: (2499*0.5)/20 = 62
#define SERVO_45_DEGREE 	125		// For 1.0ms: (2499*1.0)/20 = 125
#define SERVO_90_DEGREE 	187		// For 1.5ms: (2499*1.5)/20 = 187
#define SERVO_135_DEGREE 	250		// For 2.0ms: (2499*2.0)/20 = 250
#define SERVO_180_DEGREE 	312		// For 2.5ms: (2499*2.5)/20 = 312

#define SERVO_MIN_VALUE SERVO_0_DEGREE
#define SERVO_MAX_VALUE SERVO_180_DEGREE

tpm_handler_t servo;

// ==========================================================================
// FUNCTIONS PROTOTYPES
// ==========================================================================

/*
 * Initialize a Servo Motor PWM in PTE23 (Channel 1 of TPM2 module).
 */
void initServoComponent(void);

/**
 * Initialize a Potentiometer ADC in PTB1 (Channel 9 of ADC0 module).
 */
void initPotentiometerComponent(void);

/**
 * Map a given value, betwen in_min and in_max, to a value between out_min
 * and out_max.
 */
long map(long x, long in_min, long in_max, long out_min, long out_max);

// ==========================================================================
// MAIN CODE
// ==========================================================================

int main(void) {

	initServoComponent();
	initPotentiometerComponent();

	uint16_t potentiometer_input;
	uint32_t servo_output;

	while(1) {
		potentiometer_input = adcReadInput(potentiometer);

		servo_output = map(potentiometer_input,
						   POTENTIOMETER_MIN_VALUE,
						   POTENTIOMETER_MAX_VALUE,
						   SERVO_0_DEGREE,
						   SERVO_180_DEGREE);

		tpmSetChannelValue(&servo, servo_output);
	}
}

// ==========================================================================
// FUNCTIONS IMPLEMENTATION
// ==========================================================================

long map(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void initServoComponent(void) {
	clkEnableClock(clkSOURCE_LIRCLK_2MHz);

	portSetPinMux(pinPORT_E, 23, pinMUX_ALT_3);

	servo.module = tpmMODULE_2;
	servo.channel = tpmCHANNEL_1;
	servo.clk = tpmCLOCK_MCGIRCLK;
	servo.ps = tpmPRESCALER_16;
	servo.channel_mode = tpmCHANNEL_EDGE_ALIGNED_PWM_LT;
	tpmInitModule(&servo);

	// MOD = 20ms*(2MHz/16) = 2500 - 1
	tpmSetModuleValue(&servo, 2499);
	tpmSetChannelValue(&servo, SERVO_MIN_VALUE);

	tpmStartTimer(&servo);
}

void initPotentiometerComponent(void) {
	portSetPinMux(pinPORT_B, 1, pinMUX_ALT_0);

	potentiometer = adcCHANNEL_9;

	adc_config_t adc_module;
	adcGetDefaultConfig(&adc_module);
	adc_module.sample_number = adcSAMPLE_NUMBER_0;
	adcInitModule(&adc_module);
}
#endif
