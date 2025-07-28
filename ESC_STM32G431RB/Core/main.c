/*
 * ESC - Single Motor Driver
 * Using the stm32G431 microcontroller, back emf detection
 *
 * Author: David Balderrama S.
 * Start Date: 7/27/2025
 *
 */

#include "stm32g4xx.h"
#include <stdio.h>
#include <math.h>

#include "Back_EMF/COMPx.h"

#define LED_PA10 (1 << 10)

void LED_PA10_Init(void);


int main(void){

	LED_PA10_Init();
	COMP1_Init();
	COMP2_Init();

	while (1){
		if (COMP1->CSR & COMP_CSR_VALUE){
			// Set LED_PA10 HIGH
			GPIOA->ODR |= LED_PA10;
		}
		else {
			// Set LED_PA10 LOW
		    GPIOA->ODR &= ~LED_PA10;
		}

		// Brute force delay function
		//for (volatile uint16_t count = 0; count < 65500; count++);
	}
}

void LED_PA10_Init(void){
	// init Clk to GPIOA
	RCC->AHB2ENR |= (1<<0);

	// Clear PA10
	GPIOA->MODER &= ~(0b11 << 20);

	// Set PA10 as output
	GPIOA->MODER |= (0b01 << 20);
}

/*
 * What am I doing?
 *
 * Initializing COMPx_INP and COMPx_INM
 *
 * When COMPx_INP > COMPx_INM,
 * Then trigger the next commutational step
 *
 * In this case, set LED_PA10 to HIGH
 *
 */







