
#include "stm32g4xx.h"
//#include "stm32g4xx_hal.h"
#include <stdio.h>
#include <math.h>


void LED_PA10(void);

int main(void){

	LED_PA10();

	while (1){
		// Toggle LED_PA10
		GPIOA->ODR ^= (1 << 10);

		// Brute force delay function
		for (volatile uint16_t count = 0; count < 65500; count++);
	}
}

void LED_PA10(void){

	// init Clk to GPIOA
	RCC->AHB2ENR |= (1<<0);

	// Clear PA10
	GPIOA->MODER &= ~(0b11 << 20);

	// Set PA10 as output
	GPIOA->MODER |= (0b01 << 20);
}




