#include "Switch_Led_Couple.h"

#include "MKL25Z4.h"

#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_clock.h"

int main(void) {

	init_pins();
	while(1) {
		if(GPIO_ReadPinInput(GPIOD, SW1_BIT)) {
			GPIO_TogglePinsOutput(GPIOC, 1 << LED_GREEN_D1_BIT);
		}
		if(GPIO_ReadPinInput(GPIOA, SW2_BIT)) {
			GPIO_TogglePinsOutput(GPIOA, 1 << LED_GREEN_D3_BIT);
		}
	}
}

void init_pins(void) {
	// Enable the clock to the used ports.
	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortD);

	// Configures the pins as GPIO.
	PORT_SetPinMux(PORTC, LED_GREEN_D1_BIT, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTA, LED_GREEN_D3_BIT, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTD, SW1_BIT, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTA, SW2_BIT, kPORT_MuxAsGpio);

	// Configure the LED pins as OUTPUT.
	gpio_pin_config_t led_green_d1 = {kGPIO_DigitalOutput, 0};
	GPIO_PinInit(GPIOC, LED_GREEN_D1_BIT, &led_green_d1);
	gpio_pin_config_t led_green_d3 = {kGPIO_DigitalOutput, 0};
	GPIO_PinInit(GPIOA, LED_GREEN_D3_BIT, &led_green_d3);

	// Configure the SWITCH pins as INPUT.
	gpio_pin_config_t sw1 = {kGPIO_DigitalInput, 0};
	GPIO_PinInit(GPIOD, SW1_BIT, &sw1);
	gpio_pin_config_t sw2 = {kGPIO_DigitalInput, 0};
	GPIO_PinInit(GPIOA, SW2_BIT, &sw2);
}
