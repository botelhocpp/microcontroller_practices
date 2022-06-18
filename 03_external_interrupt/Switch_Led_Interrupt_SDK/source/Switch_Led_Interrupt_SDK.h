/**
 * @author  Pedro Botelho
 * @file    Switch_Led_Interrupt_SDK.h
 * @brief   Definition of the functions used in the main
 * 			function, as well as macros to facilitate
 * 			maintenance.
 */

#ifndef SW_LED_IRQHANDLER_H
#define SW_LED_IRQHANDLER_H

// Checks if the bit is high in value.
#define BitTst(value, bit) ((value) & (1 << bit))

// LED Interface pins.
#define LED_D1_PIN 8			// PTC8
#define LED_D3_PIN 13			// PTA13

#define LED_D1_PORT PORTC
#define LED_D3_PORT PORTA

#define LED_D1_GPIO GPIOC
#define LED_D3_GPIO GPIOA

// LED Interface masks.
#define LED_D1_MASK 1 << LED_D1_PIN
#define LED_D3_MASK 1 << LED_D3_PIN

// Switch Interface pins.
#define SW1_PIN 4				// PTD4
#define SW2_PIN 12				// PTA12

#define SW1_PORT PORTD
#define SW2_PORT PORTA

#define SW1_GPIO GPIOD
#define SW2_GPIO GPIOA

// Switch Interface masks.
#define SW1_MASK 1 << SW1_PIN
#define SW2_MASK 1 << SW2_PIN

/*
 * Initializes pins PTD4 and PTA12 as digital input,
 * as well as PTC8 and PTA13 as digital output.
 *
 * It also configures interrupt for the A and D ports,
 * to be enabled by rising and falling edge event.
 */
extern void init_pins(void);

/*
 * ISR for PORTA peripheral. Checks if PTA12 is high.
 * If so, toggle the level at PTA13.
 */
extern void PORTA_IRQHandler(void);

/*
 * ISR for PORTD peripheral. Checks if PTD4 is high.
 * If so, toggle the level at PTC8.
 */
extern void PORTD_IRQHandler(void);

#endif
