#include "LPTMR_Select.h"
#if LPTMR_PROJECT == 4

#include "MKL25Z4.h"
#include "LPTMR_KL25Z_SDK.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_lptmr.h"

void LEDS_Init(void);
void LPTMR0_Init(void);

int main(void) {
	LEDS_Init();
	LPTMR0_Init();
	while(1);
}

void LPTMR0_IRQHandler(void) {
	// CLEAR INTERRUPT FLAG
	LPTMR_ClearStatusFlags(LPTMR0, kLPTMR_TimerCompareFlag);

	// TOGGLE THE LEDS
	GPIO_TogglePinsOutput(LED_01_GPIO, LED_01_MASK);
	GPIO_TogglePinsOutput(LED_02_GPIO, LED_02_MASK);
}

void LEDS_Init(void) {
	// ENABLE THE CLOCK FOR THE TWO LEDS PORTS
	CLOCK_EnableClock(LED_01_CLOCK);
	CLOCK_EnableClock(LED_02_CLOCK);

	// SELECT GPIO FUNCTION FOR THE LEDS PINS
	PORT_SetPinMux(LED_01_PORT, LED_01, kPORT_MuxAsGpio);
	PORT_SetPinMux(LED_02_PORT, LED_02, kPORT_MuxAsGpio);

	// CONFIG THE LED PINS AS OUTPUT
	static const gpio_pin_config_t led01_handle = {kGPIO_DigitalOutput, 0};
	GPIO_PinInit(LED_01_GPIO, LED_01, &led01_handle);
	static const gpio_pin_config_t led02_handle = {kGPIO_DigitalOutput, 0};
	GPIO_PinInit(LED_02_GPIO, LED_02, &led02_handle);
}

void LPTMR0_Init(void) {
	// ENABLE CLOCK FOR LPTMR0
	CLOCK_EnableClock(kCLOCK_Lptmr0);

	// GET THE DEFAULT CONFIG FOR THE LPTMR
	static lptmr_config_t lptmr0_handle;
	LPTMR_GetDefaultConfig(&lptmr0_handle);

	// DIVIDE-BY-8 PRESCALER AND SELECT 1KHz LPO
	lptmr0_handle.bypassPrescaler = true;
	lptmr0_handle.prescalerClockSource = kLPTMR_PrescalerClock_1;

	// INITIALIZES THE LPTMR PERIPHERAL
	LPTMR_Init(LPTMR0, &lptmr0_handle);

	// CONFIGURES THE NUMBER OF COUNTS UTIL OVERFLOW
	// T = (1/1KHz) = 1ms
	// CMR = 1s/1ms = 1000 TICKS
	LPTMR_SetTimerPeriod(LPTMR0, 999);

	// ENABLE INTERRUPTS FOR LPTMR0
	LPTMR_EnableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);

	// START THE COUNT
	LPTMR_StartTimer(LPTMR0);

	// ENABLE INTERRUPTS FOR LPTMR0 IN NVIC
	NVIC_EnableIRQ(LPTMR0_IRQn);
}

#endif
