/**
 * DUAL LED PWM OSCILATION (WITH SDK):
 *
 * @author Pedro M. Botelho
 * @brief  Control the embedded green LED,
 * in PTD5, and red LED, PTE31, luminosity
 * levels, varying it between mininum and
 * maximum, where the luminosity of one
 * LED will be the inverse of the another.
 *
 * You can control the speed of the variation,
 * decrementing or incrementing LED_INCREASE_RATE
 * value.
 */

#include "project_select.h"
#if PROJECT == 2

// ====================================================================================
// LIBRARIES
// ====================================================================================

#include "K32L2B31A.h"

#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include "fsl_tpm.h"

#include <stdint.h>
#include <stdbool.h>

// ====================================================================================
// LED CONTROL
// ====================================================================================

#define LED_MAX_VALUE 		29999
#define LED_INCREASE_RATE 	1

// ====================================================================================
// FUNCTION PROTOTYPES
// ====================================================================================

/**
 * Configure PTD5 as PWM (Channel 5 of TPM0 module).
 */
void initLedPwm(void);

/**
 * Set the pulse width for the PWM.
 */
void setLedDutyCycle(uint16_t channel_value);

/**
 * Configure Core clock to MCGIRCLK, at 8 MHz, and enable HIRC.
 */
void setupInternalClock(void);

/**
 * Enable OSCERCLK, from the 32768 Hz oscillator.
 */
void setupExternalClock(void);

// ====================================================================================
// MAIN CODE
// ====================================================================================

int main(void) {

	setupInternalClock();

	initLedPwm();

	double channel_value = 0;
	bool increase_value = true;

	while(1) {
		if(increase_value) {
			channel_value += LED_INCREASE_RATE;
			if((int) channel_value > (LED_MAX_VALUE - 1)) {
				increase_value = false;
			}
		}
		else {
			channel_value -= LED_INCREASE_RATE;
			if((int) channel_value < 1) {
				increase_value = true;
			}
		}
		setLedDutyCycle((int) channel_value);
	}
}

// ====================================================================================
// FUNCTION IMPLEMENTATIONS
// ====================================================================================

void initLedPwm(void) {
	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortE);

	PORT_SetPinMux(PORTD, 5, kPORT_MuxAlt4);
	PORT_SetPinMux(PORTE, 31, kPORT_MuxAlt3);

	CLOCK_EnableClock(kCLOCK_Tpm0);

	// Select IRC48
	CLOCK_SetTpmClock(1);

	tpm_config_t tpm0_config;
	TPM_GetDefaultConfig(&tpm0_config);
	tpm0_config.prescale = kTPM_Prescale_Divide_32;
	TPM_Init(TPM0, &tpm0_config);

	tpm_chnl_pwm_signal_param_t tpm0_channel_config[2];

	tpm0_channel_config[0].chnlNumber = 4;
	tpm0_channel_config[0].dutyCyclePercent = 0;
	tpm0_channel_config[0].level = kTPM_LowTrue;

	tpm0_channel_config[1].chnlNumber = 5;
	tpm0_channel_config[1].dutyCyclePercent = 0;
	tpm0_channel_config[1].level = kTPM_LowTrue;

	TPM_SetupPwm(TPM0, tpm0_channel_config, 2, kTPM_EdgeAlignedPwm, 50, 48000000/32);

	TPM_StartTimer(TPM0, kTPM_SystemClock);
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setLedDutyCycle(uint16_t channel_value) {
	long duty_cycle = map(channel_value, 0, 29999, 0, 100);
	TPM_UpdatePwmDutycycle(TPM0, 4, kTPM_EdgeAlignedPwm, duty_cycle);
	TPM_UpdatePwmDutycycle(TPM0, 5, kTPM_EdgeAlignedPwm, 100 - duty_cycle);
}

void setupInternalClock(void) {
	mcglite_config_t mcglite_config;
	mcglite_config.outSrc = kMCGLITE_ClkSrcLirc;
	mcglite_config.ircs = kMCGLITE_Lirc8M;
	mcglite_config.irclkEnableMode = kMCGLITE_IrclkEnable | kMCGLITE_IrclkEnableInStop;
	mcglite_config.hircEnableInNotHircMode = true;
	mcglite_config.fcrdiv = kMCGLITE_LircDivBy1;
	mcglite_config.lircDiv2 = kMCGLITE_LircDivBy1;
	while(CLOCK_SetMcgliteConfig(&mcglite_config));
}

void setupExternalClock(void) {
	CLOCK_SetXtal0Freq(32768);
	osc_config_t osc_config;
	osc_config.freq = 32768;
	osc_config.capLoad = 0;
	osc_config.oscerConfig.enableMode = OSC_CR_ERCLKEN_MASK | OSC_CR_EREFSTEN_MASK;
	osc_config.workMode = kOSC_ModeOscLowPower;
	CLOCK_InitOsc0(&osc_config);
}

#endif
