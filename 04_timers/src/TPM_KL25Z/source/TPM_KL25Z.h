#ifndef TPM_KL25Z_H
#define TPM_KL25Z_H

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

#define TPM0_CLOCK				(1U << 24)
#define TPM1_CLOCK				(1U << 25)
#define TPM2_CLOCK				(1U << 26)

#define CLOCK_FLL				~(1U << 16)
#define CLOCK_PLL_DIV_2			(1U << 16)
#define CLOCK_FLL_PLL			(0b01U << 24)
#define CLOCK_OSCERCLK			(0b10U << 24)
#define CLOCK_MCGIRCLK			(0b11U << 24)
#define MCG_MCGIRCLK_ENABLE     (1U << 1)

#define TPM_INTERRUPT_ENABLE  	(1U << 6)
#define TPM_INTERRUPT_FLAG    	(1U << 7)
#define TPM_ENABLE_COUNTER   	(0b01U << 3)

#define TPM_PRESCALER_2    		(0b001U << 0)
#define TPM_PRESCALER_4    		(0b010U << 0)
#define TPM_PRESCALER_8    		(0b011U << 0)
#define TPM_PRESCALER_16    	(0b100U << 0)
#define TPM_PRESCALER_32    	(0b101U << 0)
#define TPM_PRESCALER_64    	(0b110U << 0)
#define TPM_PRESCALER_128    	(0b111U << 0)

#define NVIC_ENABLE_TPM0 		(1U << 17)
#define NVIC_ENABLE_TPM1 		(1U << 18)

#endif
