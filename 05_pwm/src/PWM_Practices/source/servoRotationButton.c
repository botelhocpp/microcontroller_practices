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
#if PROJECT == 5

// ====================================================================================
// LIBRARIES
// ====================================================================================

#include "K32L2B31A.h"

#include "k32l2b3/tpm.h"
#include "k32l2b3/clock.h"
#include "k32l2b3/delay.h"
#include "k32l2b3/servo.h"
#include "k32l2b3/port.h"
#include "k32l2b3/gpio.h"

#include <stdint.h>
#include <stdbool.h>

// ==========================================================================
// SERVO CONTROL
// ==========================================================================

/**
 * Configure the rate of change of the duty-cycle: 0.5x,
 * 1x, 2x, etc...
 */
#define SERVO_ROTATION_RATE 		1
#define SERVO_ROTATION_TIME_US 		(int) SERVO_ROTATION_RATE*500

servo_handler_t servo;

static uint16_t minimum_value;
static uint16_t maximum_value;

// ====================================================================================
// BUTTON CONTROL
// ====================================================================================

/**
 * Define if internal buttons of the board will be used (PTC3
 * and PTA4), with 1, or external buttons (PTD2 and PTA2), with 0.
 */
#define INTERNAL_BUTTONS 	1

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
		uint16_t servo_value = servoGetCurrentValue(&servo);
		while(!gpioPinRead(&increase_button) && servo_value < maximum_value) {
			servoWrite(&servo, ++servo_value);
			delay_us(SERVO_ROTATION_TIME_US);
		}
		portClearInterrupt(&increase_button);
	}
}

void PORTA_IRQHandler(void) {
	if(portCheckInterrupt(&decrease_button)) {
		uint16_t servo_value = servoGetCurrentValue(&servo);
		while(!gpioPinRead(&decrease_button) && servo_value > minimum_value) {
			servoWrite(&servo, --servo_value);
			delay_us(SERVO_ROTATION_TIME_US);
		}
		portClearInterrupt(&decrease_button);
	}
}

// ====================================================================================
// FUNCTION IMPLEMENTATIONS
// ====================================================================================

void initServoComponent(void) {
	portSetPinMux(pinPORT_E, 20, pinMUX_ALT_3);

	servoGetDefaultConfig(&servo);
	servo.module = tpmMODULE_1;
	servo.channel = tpmCHANNEL_0;
	servoInitModule(&servo);

	minimum_value = servoGetMinimumValue(&servo);
	maximum_value = servoGetMaximumValue(&servo);
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
