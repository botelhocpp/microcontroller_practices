/**
 * STAR WARS "THE IMPERIAL MARCH" IN BUZZER (WITH CUSTOM API W/ BUZZER FUNCTIONS):
 *
 * @author Pedro M. Botelho
 * @brief  Plays the famous song "The
 * Imperial March", in a Buzzer piezo
 * connected to PTD3.
 */

#include "project_select.h"
#if PROJECT == 7

// ====================================================================================
// LIBRARIES
// ====================================================================================

#include "K32L2B31A.h"

#include "k32l2b3/clock.h"
#include "k32l2b3/port.h"
#include "k32l2b3/delay.h"
#include "k32l2b3/buzzer.h"

// ====================================================================================
// BUZZER CONTROL
// ====================================================================================

const uint8_t number_notes = 74;

const int32_t melody[] = {
		// FIRST SECTION
		NOTE_A4, NOTE_A4, NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4,
		NO_NOTE,
		NOTE_E5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_C5, NOTE_GS4, NOTE_F4, NOTE_C5, NOTE_A4,
		NO_NOTE,

		// SECOND SECTION
		NOTE_A5, NOTE_A4, NOTE_A4, NOTE_A5, NOTE_GS5, NOTE_GS4, NOTE_FS5, NOTE_F5, NOTE_FS5,
		NO_NOTE,
		NOTE_AS4, NOTE_DS5, NOTE_D5, NOTE_CS5, NOTE_C5, NOTE_B4, NOTE_C5,
		NO_NOTE,

		// THIRD SECTION
		NOTE_F4, NOTE_GS4, NOTE_F4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_E5,
		NO_NOTE,

		// SECOND SECTION (AGAIN)
		NOTE_A5, NOTE_A4, NOTE_A4, NOTE_A5, NOTE_GS5, NOTE_GS4, NOTE_FS5, NOTE_F5, NOTE_FS5,
		NO_NOTE,
		NOTE_AS4, NOTE_DS5, NOTE_D5, NOTE_CS5, NOTE_C5, NOTE_B4, NOTE_C5,
		NO_NOTE,

		// FOURTH SECTION
		NOTE_F4, NOTE_GS4, NOTE_F4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4,
		NO_NOTE
};

const uint16_t noteDurations[] = {
		500, 500, 500, 350, 150, 500, 350, 150, 650,
		500,
		500, 500, 500, 350, 150, 500, 350, 150, 650,
		500,

		500, 300, 150, 500, 325, 175, 125, 125, 250,
		325,
		250, 500, 325, 175, 125, 125, 250,
		350,

		250, 500, 350, 125, 500, 375, 125, 650,
		500,

		500, 300, 150, 500, 325, 175, 125, 125, 250,
		325,
		250, 500, 325, 175, 125, 125, 250,
		350,

		250, 500, 375, 125, 500, 375, 125, 650,
		650
};

buzzer_handler_t buzzer;

// ====================================================================================
// FUNCTION PROTOTYPES
// ====================================================================================

/**
 * Enable MCGIRCLK, at 8 MHz frequency, and set it to the core clock.
 */
void initSystemClock(void);

/**
 * Configure a PWM signal in PTD3 (Channel 3 of TPM0 module).
 */
void initBuzzerComponent(void);

/**
 * Plays the Star Wars "The Imperial March" song in the buzzer.
 */
void imperialMarchMelody(void);

// ====================================================================================
// MAIN CODE
// ====================================================================================

int main(void) {
	initSystemClock();
	initBuzzerComponent();
	imperialMarchMelody();
	while(1);
}

// ====================================================================================
// FUNCTION IMPLEMENTATIONS
// ====================================================================================

//PTD3 = TPM0_CH3
void initBuzzerComponent(void) {
	portSetPinMux(pinPORT_D, 3, pinMUX_ALT_4);
	buzzerGetDefaultConfig(&buzzer);
	buzzer.module = tpmMODULE_0;
	buzzer.channel = tpmCHANNEL_3;
	buzzerInitModule(&buzzer);
}

void imperialMarchMelody(void) {
	for (int thisNote = 0; thisNote < number_notes; thisNote++) {
		int noteDuration = noteDurations[thisNote]/8;
		int pauseBetweenNotes = noteDuration * 1.30;
		buzzerTone(&buzzer, melody[thisNote], noteDuration);
		delay_ms(pauseBetweenNotes);
	}
}

void initSystemClock(void) {
	clkEnableClock(clkSOURCE_LIRCLK_8MHz);
	clkSetMainClock(clkSOURCE_LIRCLK_8MHz);
}
#endif
