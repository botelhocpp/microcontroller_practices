#ifndef LPTMR_KL25Z_H
#define LPTMR_KL25Z_H

#define LED_01       			3
#define LED_01_PORT  			PORTB
#define LED_01_GPIO  			GPIOB
#define LED_01_CLOCK 			kCLOCK_PortB
#define LED_01_MASK  			(1U << LED_01)

#define LED_02       			5
#define LED_02_PORT  			PORTD
#define LED_02_GPIO  			GPIOD
#define LED_02_CLOCK 			kCLOCK_PortD
#define LED_02_MASK  			(1U << LED_02)

#endif
