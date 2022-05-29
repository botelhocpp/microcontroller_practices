#ifndef PIT_KL25Z_H
#define PIT_KL25Z_H

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

#define PIT_TIME_PERIOD(T)		((T*10485760) - 1)

#define PIT_PERIOD_1S    		(PIT_TIME_PERIOD(1))
#define PIT_PERIOD_2S    		(PIT_TIME_PERIOD(2))
#define PIT_PERIOD_4S    		(PIT_TIME_PERIOD(4))
#define PIT_PERIOD_8S    		(PIT_TIME_PERIOD(8))

#endif
