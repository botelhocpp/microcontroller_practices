#include <TPM_Select.h>
#if TPM_PROJECT == 4

#include "MKL25Z4.h"
#include "fsl_tpm.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_clock.h"
#include <TPM_KL25Z_SDK.h>

/* INITIALIZES THE LEDS 01 AND 02 */
void LEDS_Init(void);

/* STARTS THE MODULE 0 OF TPM WITH 2s TO BLINK LED 01 */
void TPM0_Init(void);

/* STARTS THE MODULE 1 OF TPM WITH 8s TO BLINK LED 02 */
void TPM1_Init(void);

int main(void) {
	LEDS_Init();
	TPM0_Init();
	TPM1_Init();
	while(1);
}

void TPM0_IRQHandler(void) {
	TPM_ClearStatusFlags(TPM0, kTPM_TimeOverflowFlag);
	GPIO_TogglePinsOutput(LED_01_GPIO, LED_01_MASK);
}

void TPM1_IRQHandler(void) {
	TPM_ClearStatusFlags(TPM1, kTPM_TimeOverflowFlag);
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

void TPM0_Init(void) {
	// CONFIGURE THE INTERNAL REFERENCE CLOCK TO MCGIRCLK.
	// Slow internal reference clock selected
	// Fast IRC divider: divided by 1
	CLOCK_SetInternalRefClkConfig(kMCG_IrclkEnable, kMCG_IrcSlow, 0x0U);

	CLOCK_EnableClock(kCLOCK_Tpm0);

	// SET A DIVIDE-BY-32 PRESCALER
	static tpm_config_t tpm0_handle = {};
    TPM_GetDefaultConfig(&tpm0_handle);
    tpm0_handle.prescale = kTPM_Prescale_Divide_32;
    TPM_Init(TPM0, &tpm0_handle);

	// ENABLE CLOCK FOR TPM0
    CLOCK_SetTpmClock(3);

	// MOD = 2s * (32,768KHz/32) = 2048
    TPM_SetTimerPeriod(TPM0, 2047);

    TPM_EnableInterrupts(TPM0, kTPM_TimeOverflowInterruptEnable);

	// ENABLE INTERRUPTS FOR TMP0 IN NVIC
    NVIC_EnableIRQ(TPM0_IRQn);

	// ENABLE TPM TO COUNT
    TPM_StartTimer(TPM0, kTPM_SystemClock);
}

void TPM1_Init(void) {
	// CONFIGURE THE INTERNAL REFERENCE CLOCK TO MCGIRCLK.
	// Slow internal reference clock selected
	// Fast IRC divider: divided by 1
	CLOCK_SetInternalRefClkConfig(kMCG_IrclkEnable, kMCG_IrcSlow, 0x0U);

	CLOCK_EnableClock(kCLOCK_Tpm1);

	// SET A DIVIDE-BY-32 PRESCALER
	static tpm_config_t tpm1_handle = {};
    TPM_GetDefaultConfig(&tpm1_handle);
    tpm1_handle.prescale = kTPM_Prescale_Divide_32;
    TPM_Init(TPM1, &tpm1_handle);

	// ENABLE CLOCK FOR TPM0
    CLOCK_SetTpmClock(3);

	// MOD = 8s * (32,768KHz/32) = 8191
    TPM_SetTimerPeriod(TPM1, 8191);

    TPM_EnableInterrupts(TPM1, kTPM_TimeOverflowInterruptEnable);

	// ENABLE INTERRUPTS FOR TMP0 IN NVIC
    NVIC_EnableIRQ(TPM1_IRQn);

	// ENABLE TPM TO COUNT
    TPM_StartTimer(TPM1, kTPM_SystemClock);
}

#endif
