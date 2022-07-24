/**
 * SERVO 180° ROTATION (WITH CUSTOM API)
 *
 * @author Pedro M. Botelho
 * @brief  Control the rotation of a servo
 * motor rotate with two buttons, and by using
 * a PWM signal. If you're using a buffer, like
 * a 7407, or similar, to pass a 5V signal to
 * the motor, just define "PWM_3V3" as 0. If
 * you're using the regular 3V3 PWM signal,
 * define it as 1.
 *
 * The buttons are mapped to PTD2 and PTA2, but
 * you can use the embedded buttons, by defining
 * INTERNAL_BUTTONS macro as 1. Otherwise, keep
 * it as 0.
 */

#include "project_select.h"
#if PROJECT == 4

// ====================================================================================
// LIBRARIES
// ====================================================================================

#include "K32L2B31A.h"

#include "k32l2b3/clock.h"
#include "k32l2b3/delay.h"
#include "k32l2b3/tpm.h"
#include "k32l2b3/port.h"
#include "k32l2b3/gpio.h"

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
#define PWM_INCREASE_RATE 		1
#define PWM_INCREASE_TIME_US 	(int) PWM_INCREASE_RATE*500

tpm_handler_t servo;

// ====================================================================================
// BUTTON CONTROL
// ====================================================================================

/**
 * Define if internal buttons of the board will be used (PTC3
 * and PTA4), with 1, or external buttons (PTD2 and PTA2), with 0.
 */
#define INTERNAL_BUTTONS 	0

pin_handler_t increase_button;

pin_handler_t decrease_button;

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

/**
 * Configure the two buttons used for controlling the servo.
 *
 * If INTERNAL_BUTTONS is 1 the internal buttons of the board
 * will be used (SW3 and SW1). If not, PTD2 and PTA2 will be
 * used as increase and decrease buttons, respectively.
 */
void initButtonComponents(void);

// ====================================================================================
// MAIN CODE
// ====================================================================================

int main(void) {
	initSystemClock();
	initServoComponent();
	initButtonComponents();
	while(1);
}

// ====================================================================================
// ISR IMPLEMENTATIONS
// ====================================================================================

void PORTC_PORTD_IRQHandler(void) {
	if(portCheckInterrupt(&increase_button)) {
		uint32_t channel_value = tpmGetChannelValue(&servo);
		while(!gpioPinRead(&increase_button) && channel_value < SERVO_MAX_VALUE) {
			tpmSetChannelValue(&servo, ++channel_value);
			delay_us(PWM_INCREASE_TIME_US);
		}
		portClearInterrupt(&increase_button);
	}
}

void PORTA_IRQHandler(void) {
	if(portCheckInterrupt(&decrease_button)) {
		uint32_t channel_value = tpmGetChannelValue(&servo);
		while(!gpioPinRead(&decrease_button) && channel_value > SERVO_MIN_VALUE) {
			tpmSetChannelValue(&servo, --channel_value);
			delay_us(PWM_INCREASE_TIME_US);
		}
		portClearInterrupt(&decrease_button);
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

void initButtonComponents(void) {
	#if INTERNAL_BUTTONS
		increase_button.port = pinPORT_C;
		increase_button.pin = 3;
		gpioPinInit(&increase_button, gpioINPUT);
		portConfigInterrupt(&increase_button, portINT_FALLING_EDGE);
		portConfigPullup(&increase_button);

		decrease_button.port = pinPORT_A;
		decrease_button.pin = 4;
		gpioPinInit(&decrease_button, gpioINPUT);
		portConfigInterrupt(&decrease_button, portINT_FALLING_EDGE);
		portConfigPullup(&decrease_button);
	#else
		increase_button.port = pinPORT_D;
		increase_button.pin = 2;
		gpioPinInit(&increase_button, gpioINPUT);
		portConfigInterrupt(&increase_button, portINT_FALLING_EDGE);
		portConfigPullup(&increase_button);

		decrease_button.port = pinPORT_A;
		decrease_button.pin = 2;
		gpioPinInit(&decrease_button, gpioINPUT);
		portConfigInterrupt(&decrease_button, portINT_FALLING_EDGE);
		portConfigPullup(&decrease_button);
	#endif
}

#endif
