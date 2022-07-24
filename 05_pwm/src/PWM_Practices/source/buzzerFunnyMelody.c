/**
 * FUNNY MELODY IN BUZZER (WITH CUSTOM API):
 *
 * @author Pedro M. Botelho
 * @brief  Plays a silly little song, taken
 * from Arduino IDE examples, in a Buzzer piezo
 * connected to PTD3.
 */

#include "project_select.h"
#if PROJECT == 6

// ====================================================================================
// LIBRARIES
// ====================================================================================

#include "K32L2B31A.h"

#include "k32l2b3/tpm.h"
#include "k32l2b3/clock.h"
#include "k32l2b3/port.h"
#include "k32l2b3/delay.h"

// ====================================================================================
// BUZZER CONTROL
// ====================================================================================

#define NO_NOTE 0
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988

#define TPM0_CLOCK 62500

tpm_handler_t buzzer;

const uint8_t number_notes = 8;

/**
 * The melody note sequence.
 */
const uint32_t melody[] = {NOTE_C5, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NO_NOTE, NOTE_B4, NOTE_C5};

/*
 * Note durations:
 * - 4 = quarter note
 * - 8 = eighth note
 */
const uint8_t noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};

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
 * Plays a silly song taken from Arduino IDE examples.
 */
void funnyMelody(void);

// ====================================================================================
// MAIN CODE
// ====================================================================================

int main(void) {
	initSystemClock();
	initBuzzerComponent();
	funnyMelody();
	while(1);
}

// ====================================================================================
// FUNCTION IMPLEMENTATIONS
// ====================================================================================

void initBuzzerComponent(void) {
	portSetPinMux(pinPORT_D, 3, pinMUX_ALT_4);

	/* Configure Channel 3 of TPM0 to Generate a maximum 62,5 KHz PWM Signal */
	buzzer.module = tpmMODULE_0;
	buzzer.channel = tpmCHANNEL_3;
	buzzer.clk = tpmCLOCK_MCGIRCLK;
	buzzer.ps = tpmPRESCALER_128;
	buzzer.channel_mode = tpmCHANNEL_EDGE_ALIGNED_PWM_HT;
	tpmInitModule(&buzzer);

	/* Initialize the PWM to generate a 262 Hz square-wave signal */
	tpmSetModuleValue(&buzzer, TPM0_CLOCK/NOTE_C4);
	tpmSetChannelValue(&buzzer, tpmGetModuleValue(&buzzer)/2);
}

void funnyMelody(void) {
	for (int thisNote = 0; thisNote < number_notes; thisNote++) {
		int noteDuration = 200/noteDurations[thisNote];
		int pauseBetweenNotes = noteDuration * 1.30;

		if(melody[thisNote] != NO_NOTE) {
			tpmStartTimer(&buzzer);
			tpmSetModuleValue(&buzzer, TPM0_CLOCK/melody[thisNote]);
			tpmSetChannelValue(&buzzer, tpmGetModuleValue(&buzzer)/2);
			delay_ms(noteDuration);
			tpmStopTimer(&buzzer);
		}
		else {
			delay_ms(noteDuration);
		}

		delay_ms(pauseBetweenNotes);
	}
}

void initSystemClock(void) {
	clkEnableClock(clkSOURCE_LIRCLK_8MHz);
	clkSetMainClock(clkSOURCE_LIRCLK_8MHz);
}

#endif
