#include <PIT_Select.h>
#if PIT_PROJECT == 2

#include "MKL25Z4.h"
#include <PIT_KL25Z_SDK.h>

#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_pit.h"

/* INITIALIZES THE LEDS 01 AND 02 */
void LEDS_Init(void);

/* STARTS THE CHANNEL 0 OF PIT WITH 2s TO BLINK LED 01 */
void PIT0_Init(void);

/* STARTS THE CHANNEL 1 OF PIT WITH 8s TO BLINK LED 02 */
void PIT1_Init(void);

int main(void) {
	LEDS_Init();
	PIT0_Init();
	PIT1_Init();
	while(1);
}

void PIT_IRQHandler(void) {

	if(PIT_GetStatusFlags(PIT, 0) & kPIT_TimerFlag) {
		// CLEAR INTERRUPT FLAG
		PIT_ClearStatusFlags(PIT, 0, kPIT_TimerFlag);

		GPIO_TogglePinsOutput(LED_01_GPIO, LED_01_MASK);
	}
	else {
		// CLEAR INTERRUPT FLAG
		PIT_ClearStatusFlags(PIT, 1, kPIT_TimerFlag);

		GPIO_TogglePinsOutput(LED_02_GPIO, LED_02_MASK);
	}
}

void LEDS_Init(void) {
	CLOCK_EnableClock(LED_01_CLOCK);
	CLOCK_EnableClock(LED_02_CLOCK);

	PORT_SetPinMux(LED_01_PORT, LED_01, kPORT_MuxAsGpio);
	PORT_SetPinMux(LED_02_PORT, LED_02, kPORT_MuxAsGpio);

	gpio_pin_config_t led01 = {kGPIO_DigitalOutput, 0};
	GPIO_PinInit(LED_01_GPIO, LED_01, &led01);
	gpio_pin_config_t led02 = {kGPIO_DigitalOutput, 0};
	GPIO_PinInit(LED_02_GPIO, LED_02, &led02);
}

void PIT0_Init(void) {
	// ENABLE CLOCK FOR PIT
	CLOCK_EnableClock(kCLOCK_Pit0);

	static pit_config_t pit0_handle = {};
	PIT_GetDefaultConfig(&pit0_handle);
	pit0_handle.enableRunInDebug = true;
	PIT_Init(PIT, &pit0_handle);

	// SELECT 2s
	PIT_SetTimerPeriod(PIT, 0, PIT_PERIOD_2S);

	// ENABLE INTERRUPTS FOR PIT
	PIT_EnableInterrupts(PIT, 0, kPIT_TimerInterruptEnable);

	// ENABLE INTERRUPTS FOR PIT IN NVIC
	NVIC_EnableIRQ(PIT_IRQn);

	// START COUNT
	PIT_StartTimer(PIT, 0);
}

void PIT1_Init(void) {
	// ENABLE CLOCK FOR PIT
	CLOCK_EnableClock(kCLOCK_Pit0);

	static pit_config_t pit1_handle = {};
	PIT_GetDefaultConfig(&pit1_handle);
	pit1_handle.enableRunInDebug = true;
	PIT_Init(PIT, &pit1_handle);

	// SELECT 8s
	PIT_SetTimerPeriod(PIT, 1, PIT_PERIOD_8S);

	// ENABLE INTERRUPTS FOR PIT
	PIT_EnableInterrupts(PIT, 1, kPIT_TimerInterruptEnable);

	// ENABLE INTERRUPTS FOR LPTMR0 IN NVIC
	NVIC_EnableIRQ(PIT_IRQn);

	// START COUNT
	PIT_StartTimer(PIT, 1);
}

#endif
