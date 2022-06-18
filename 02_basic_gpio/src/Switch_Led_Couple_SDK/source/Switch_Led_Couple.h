#ifndef SWITCH_LED_COUPLE_H
#define SWITCH_LED_COUPLE_H

// Bit Manipulation Macros:
#define SetBit(value, bit) 	  (value |=  (1 << bit))
#define ClearBit(value, bit)  (value &= ~(1 << bit))
#define ToggleBit(value, bit) (value ^=  (1 << bit))
#define TestBit(value, bit)   (value &   (1 << bit))

// RGB LEDs Interface Bits:
#define LED_RED_BIT   18	//PTB18
#define LED_GREEN_BIT 19	//PTB19
#define LED_BLUE_BIT   1	//PTD1

// Green LEDs Interface Bits:
#define LED_GREEN_D1_BIT  8		//PTC8
#define LED_GREEN_D2_BIT  9		//PTC9
#define LED_GREEN_D3_BIT 13		//PTA13
#define LED_GREEN_D4_BIT  5		//PTD5

// Switch Interface Bits:
#define SW1_BIT  4		//PTD4
#define SW2_BIT 12		//PTA12
#define SW3_BIT  4		//PTA4
#define SW4_BIT  5		//PTA5

// Pin Control Bits:
#define MUX_GPIO_FUNCTION 8

// Clock Activation Bits:
#define CLOCK_PORTA_BIT 9
#define CLOCK_PORTB_BIT 10
#define CLOCK_PORTC_BIT 11
#define CLOCK_PORTD_BIT 12
#define CLOCK_PORTE_BIT 13

// Initializes the pins used in the project.
extern void init_pins(void);

// Wait the given value in mili-seconds.
extern void delay_ms(int ms);

#endif
