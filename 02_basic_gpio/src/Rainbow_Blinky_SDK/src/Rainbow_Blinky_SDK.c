/**
 * @author  Pedro Botelho
 * @file    Rainbow_Blinky_SDK.c
 * @brief   Light the RGB LED in all the 7 rainbow colors:
 * 			R			(Red)
 * 			G			(Green)
 * 			B			(Blue)
 * 			R + G 		(Yellow)
 * 			R + B 		(Magenta)
 * 			B + G 		(Cyan)
 * 			R + B + G 	(White)
 *
 * 			Use of SDK functions.
 */

#include "MKL25Z4.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

#define RED_LED 	1 << 18
#define GREEN_LED 	1 << 19
#define BLUE_LED 	1 << 1
#define PULSE_WIDTH 250

/*
 * Delay the program in ms mili-seconds.
 */
void delay_ms(int ms);

/*
 * Initializes pins PTB18, PTB19 and PTD1 as digital output.
 */
void init_pins(void);

int main(void) {
	init_pins();
	while(1) {
		// Red Color:
		GPIO_ClearPinsOutput(GPIOB, RED_LED);
		GPIO_SetPinsOutput(GPIOB, GREEN_LED);
		GPIO_SetPinsOutput(GPIOD, BLUE_LED);
		delay_ms(PULSE_WIDTH);

		// Green Color:
		GPIO_SetPinsOutput(GPIOB, RED_LED);
		GPIO_ClearPinsOutput(GPIOB, GREEN_LED);
		GPIO_SetPinsOutput(GPIOD, BLUE_LED);
		delay_ms(PULSE_WIDTH);

		// Blue Color:
		GPIO_SetPinsOutput(GPIOB, RED_LED);
		GPIO_SetPinsOutput(GPIOB, GREEN_LED);
		GPIO_ClearPinsOutput(GPIOD, BLUE_LED);
		delay_ms(PULSE_WIDTH);

		// Yellow Color:
		GPIO_ClearPinsOutput(GPIOB, RED_LED);
		GPIO_ClearPinsOutput(GPIOB, GREEN_LED);
		GPIO_SetPinsOutput(GPIOD, BLUE_LED);
		delay_ms(PULSE_WIDTH);

		// Magenta Color:
		GPIO_ClearPinsOutput(GPIOB, RED_LED);
		GPIO_SetPinsOutput(GPIOB, GREEN_LED);
		GPIO_ClearPinsOutput(GPIOD, BLUE_LED);
		delay_ms(PULSE_WIDTH);

		// Cyan Color:
		GPIO_SetPinsOutput(GPIOB, RED_LED);
		GPIO_ClearPinsOutput(GPIOB, GREEN_LED);
		GPIO_ClearPinsOutput(GPIOD, BLUE_LED);
		delay_ms(PULSE_WIDTH);

		// White Color:
		GPIO_ClearPinsOutput(GPIOB, RED_LED);
		GPIO_ClearPinsOutput(GPIOB, GREEN_LED);
		GPIO_ClearPinsOutput(GPIOD, BLUE_LED);
		delay_ms(PULSE_WIDTH);
	}
}

void init_pins(void) {
	// Enable clock for PORTB and PORTD peripherals.
	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortD);

	// Select GPIO function for pins PTB18, PTB19 and PTD1.
	PORT_SetPinMux(PORTB, 18, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTB, 19, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTD,  1, kPORT_MuxAsGpio);

	// Config GPIO peripheral at PTB18 as OUTPUT.
	const gpio_pin_config_t ptb18_config = {kGPIO_DigitalOutput, 0};
	GPIO_PinInit(GPIOB, 18, &ptb18_config);

	// Config GPIO peripheral at PTB19 as OUTPUT.
	const gpio_pin_config_t ptb19_config = {kGPIO_DigitalOutput, 0};
	GPIO_PinInit(GPIOB, 19, &ptb19_config);

	// Config GPIO peripheral at PTD1 as OUTPUT.
	const gpio_pin_config_t ptd1_config =  {kGPIO_DigitalOutput, 0};
	GPIO_PinInit(GPIOD,  1, &ptd1_config);
}

void delay_ms(int ms) {
	int i, j;
	for(i = 0; i < ms; i++) {
		for(j = 0; j < 7000; j++);
	}
}
