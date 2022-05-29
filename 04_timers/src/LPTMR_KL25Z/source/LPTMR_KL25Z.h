#ifndef LPTMR_KL25Z_H
#define LPTMR_KL25Z_H

#define LED_01       			3
#define LED_01_PORT  			PORTB
#define LED_01_GPIO  			GPIOB
#define LED_01_CLOCK 			(1U << 10)
#define LED_01_MASK  			(1U << LED_01)

#define LED_02       			5
#define LED_02_PORT  			PORTD
#define LED_02_GPIO  			GPIOD
#define LED_02_CLOCK 			(1U << 12)
#define LED_02_MASK  			(1U << LED_02)

#define PORT_MUX_GPIO 			(1U << 8)

#define LPTMR0_CLOCK			(1U << 0)
#define LPTMR0_CLOCK_LPO 	 	(0b01U << 0)
#define LPTMR0_BYPASS_PRESCALER	(1U << 2)
#define LPTMR0_PRESCALER_4  	(0b0001U << 3)
#define LPTMR0_PRESCALER_8  	(0b0010U << 3)
#define LPTMR0_TIMER_ENABLE 	(1U << 0)
#define LPTMR0_INTERRUPT_ENABLE (1U << 6)
#define LPTMR0_INTERRUPT_FLAG   (1U << 7)

#define NVIC_ENABLE_LPTMR0 		(1U << 28)

#endif
