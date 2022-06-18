/**
 * @author  Pedro Botelho
 * @file    Switch_Led_Interrupt_SDK.c
 * @brief   If SW1, in PTD4, is pressed, light LED_GREEN_D1, PTC8.
 * 			If SW2 is pressed, PTA12, light LED_GREEN_D3, PTA13.
 *
 * 			Use of Interrupt Technique and SDK Functions.
 */

#include <Switch_Led_Interrupt_SDK.h>
#include "MKL25Z4.h"
#include "fsl_port.h"
#include "fsl_gpio.h"


int main(void) {
    init_pins();
    while(1) {

    }
}

void init_pins(void) {
	// Enable Clock
	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortE);

	// Set IO Function
	PORT_SetPinMux(SW1_PORT, SW1_PIN,    kPORT_MuxAsGpio);
	PORT_SetPinMux(SW2_PORT, SW2_PIN,    kPORT_MuxAsGpio);
	PORT_SetPinMux(LED_D1_PORT, LED_D1_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(LED_D3_PORT, LED_D3_PIN, kPORT_MuxAsGpio);

	// Configuration variables
	const gpio_pin_config_t sw1_config    = {kGPIO_DigitalInput,  0};
	const gpio_pin_config_t sw2_config    = {kGPIO_DigitalInput,  0};
	const gpio_pin_config_t led_d1_config = {kGPIO_DigitalOutput, 0};
	const gpio_pin_config_t led_d3_config = {kGPIO_DigitalOutput, 0};

	// Initialize Pins
	GPIO_PinInit(SW1_GPIO, SW1_PIN,    &sw1_config);
	GPIO_PinInit(SW2_GPIO, SW2_PIN,    &sw2_config);
	GPIO_PinInit(LED_D1_GPIO, LED_D1_PIN, &led_d1_config);
	GPIO_PinInit(LED_D3_GPIO, LED_D3_PIN, &led_d3_config);

	// Config Interrupt for SW2
	PORT_SetPinInterruptConfig(SW2_PORT, SW2_PIN, kPORT_InterruptEitherEdge);
	NVIC_EnableIRQ(PORTA_IRQn);

	PORT_SetPinInterruptConfig(SW1_PORT, SW1_PIN, kPORT_InterruptEitherEdge);
	NVIC_EnableIRQ(PORTD_IRQn);
}

void PORTA_IRQHandler(void) {
	if(BitTst(PORT_GetPinsInterruptFlags(SW2_PORT), SW2_PIN)) {
		PORT_ClearPinsInterruptFlags(SW2_PORT, SW2_MASK);
		GPIO_TogglePinsOutput(LED_D3_GPIO, LED_D3_MASK);
	}
}

void PORTD_IRQHandler(void) {
	if(BitTst(PORT_GetPinsInterruptFlags(SW1_PORT), SW1_PIN)) {
		PORT_ClearPinsInterruptFlags(SW1_PORT, SW1_MASK);
		GPIO_TogglePinsOutput(LED_D1_GPIO, LED_D1_MASK);
	}
}
