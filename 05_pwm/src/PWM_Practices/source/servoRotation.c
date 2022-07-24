/**
 * SERVO 180° ROTATION (WITH CUSTOM API)
 *
 * @author Pedro M. Botelho
 * @brief  Make a servo motor rotate from 0°
 * to 180°, and back to 0°, by using a PWM
 * signal. If you're using a buffer, like a
 * 7407, or similar, to pass a 5V signal to
 * the motor, just define "PWM_3V3" as 0. If
 * you're using the regular 3V3 PWM signal,
 * define it as 1.
 */

#include "project_select.h"
#if PROJECT == 3

// ====================================================================================
// LIBRARIES
// ====================================================================================

#include "K32L2B31A.h"

#include "k32l2b3/clock.h"
#include "k32l2b3/delay.h"
#include "k32l2b3/tpm.h"
#include "k32l2b3/port.h"

#include <stdint.h>
#include <stdbool.h>

// ==========================================================================
// PWM CONTROL
// ==========================================================================

/**
 * Define if is using a buffer to attain a 5V PWM,
 * like the one in the image, for 0, or is using
 * the direct 3V3 output from the pin, for 1.
 */
#define PWM_3V3				0

#define SERVO_0_DEGREE 		62		// For 0.5ms: (2499*0.5)/20 = 62
#define SERVO_45_DEGREE 	125		// For 1.0ms: (2499*1.0)/20 = 125
#define SERVO_90_DEGREE 	187		// For 1.5ms: (2499*1.5)/20 = 187
#define SERVO_135_DEGREE 	250		// For 2.0ms: (2499*2.0)/20 = 250
#define SERVO_180_DEGREE 	312		// For 2.5ms: (2499*2.5)/20 = 312

#define SERVO_MIN_VALUE 	SERVO_0_DEGREE
#define SERVO_MAX_VALUE 	SERVO_180_DEGREE

/**
 * Configure the rate of change of the duty-cycle: 0.5x,
 * 1x, 2x, etc...
 */
#define PWM_INCREASE_RATE 	1

tpm_handler_t servo;

// ====================================================================================
// FUNCTION PROTOTYPES
// ====================================================================================

/*
 * Initialize a Servo Motor PWM in PTE20 (Channel 0 of TPM1 module).
 */
void initServoComponent(void);

/**
 * Enable MCGIRCLK, at 8 MHz frequency, and set it to the core clock.
 */
void initSystemClock(void);

// ====================================================================================
// MAIN CODE
// ====================================================================================

int main(void) {
	initSystemClock();

	initServoComponent();

	double channel_value = SERVO_MIN_VALUE;
	bool increase_value = true;

	while(1) {
		if(increase_value) {
			channel_value += PWM_INCREASE_RATE;
			if(channel_value > (uint32_t) SERVO_MAX_VALUE) {
				increase_value = false;
			}
		}
		else {
			channel_value -= PWM_INCREASE_RATE;
			if(channel_value < (uint32_t) SERVO_MIN_VALUE) {
				increase_value = true;
			}
		}
		tpmSetChannelValue(&servo, (uint32_t) channel_value);

		/* Wait the motor to attain position */
		delay_us(1000);
	}
}

// ====================================================================================
// FUNCTION IMPLEMENTATIONS
// ====================================================================================

void initServoComponent(void) {
	portSetPinMux(pinPORT_E, 20, pinMUX_ALT_3);

	servo.module = tpmMODULE_1;
	servo.channel = tpmCHANNEL_0;
	servo.clk = tpmCLOCK_MCGIRCLK;
	servo.ps = tpmPRESCALER_64;

	#if PWM_3V3
		servo.channel_mode = tpmCHANNEL_EDGE_ALIGNED_PWM_HT;
	#else
		servo.channel_mode = tpmCHANNEL_EDGE_ALIGNED_PWM_LT;
	#endif

	tpmInitModule(&servo);

	// MOD = 20ms*(8MHz/64) = 2500 - 1
	tpmSetModuleValue(&servo, 2499);
	tpmSetChannelValue(&servo, SERVO_MIN_VALUE);

	tpmStartTimer(&servo);
}

void initSystemClock(void) {
	clkEnableClock(clkSOURCE_LIRCLK_8MHz);
	clkSetMainClock(clkSOURCE_LIRCLK_8MHz);
}

#endif
