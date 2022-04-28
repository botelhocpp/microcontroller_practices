/**
 * @author  Pedro Botelho
 * @file    Rainbow_Blinky.h
 * @brief   Defines various macros, as well as functions,
 * 			to use in the project.
 */

#ifndef RAINBOW_BLINKY_H
#define RAINBOW_BLINKY_H

// Bit Manipulation Macros:
#define SetBit(value, bit) 	  (value |=  (1 << bit))
#define ClearBit(value, bit)  (value &= ~(1 << bit))
#define ToggleBit(value, bit) (value ^=  (1 << bit))
#define TestBit(value, bit)   (value &   (1 << bit))

// RGB LEDs Interface Bits:
#define LED_RED_BIT   18	//PTB18
#define LED_GREEN_BIT 19	//PTB19
#define LED_BLUE_BIT   1	//PTD1

// Pin Control Bits:
#define MUX_GPIO_FUNCTION 8

// Clock Activation Bits:
#define CLOCK_PORTA_BIT 9
#define CLOCK_PORTB_BIT 10
#define CLOCK_PORTC_BIT 11
#define CLOCK_PORTD_BIT 12
#define CLOCK_PORTE_BIT 13

// Time Constant for the Blinking:
#define PULSE_WIDTH 250

// Initializes the pins used in the project.
extern void init_pins(void);

// Wait the given value in mili-seconds.
extern void delay_ms(int ms);

#endif
