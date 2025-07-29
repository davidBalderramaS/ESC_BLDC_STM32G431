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
void Delay_Brute(void);


int main(void){
	LED_PA10_Init();
	//COMP1_Init();    // PA1+ | PA4-

	//COMP2_Init_v2(); // PA7+ | PA5-
	COMP3_Init_v2();   // PC1+ | PC0-


	while (1){
		if (COMP3->CSR & COMP_CSR_VALUE){
			// Set LED_PA10 HIGH
			GPIOA->ODR |= LED_PA10;
		}
		else {
			// Set LED_PA10 LOW
		    GPIOA->ODR &= ~LED_PA10;
		}
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

// Brute force delay function
void Delay_Brute(void){
	for (volatile uint16_t count = 0; count < 65500; count++);
}







