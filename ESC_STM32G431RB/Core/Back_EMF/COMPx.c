/*
 * This file is for the initialization of internal comparators
 * for the back EMF detection circuitry
 *
 * Goal: When COMPx_INP > COMPx_INM,
 *       then switch to the next commutational step in motor sequence.
 *       Pretty simple, eh?
 *
 */

#include "COMPx.h"

#include "stm32g4xx.h"
#include <stdio.h>

// COMP1_INP -> PA1+
// COMP1_INM -> PA4-
void COMP1_Init(void){
	// Enable GPIOA Clk
	RCC->AHB2ENR |= (1 << 0);
	// Enable COMPx Clk access   //<-- i changed this
	RCC->APB2ENR |=  (1 << 0);

	// Set PA1 to Analog Mode -> +
	GPIOA->MODER |= (0b11 << 2);
	// Set PA4 to Analog Mode -> -
	GPIOA->MODER |= (0b11 << 8);

	// Set internal pull-down register on PA1+
	GPIOA->PUPDR |= (0b10 << 2);

	// Init COMP1
	// Set COMP1_INP input to PA1  <-- Verify this?
	COMP1->CSR &= ~(0 << 8);
	// Set COMP1_INM input to PA4
	COMP1->CSR |= (0b110 << 4);

	// Enable COMP1
	COMP1->CSR |= (1 << 0);
}

// COMP2_INP -> PA3+
// COMP2_INM -> PA2-
void COMP2_Init(void){
	// Enable GPIOA Clk
	RCC->AHB2ENR |= (1 << 0);
	// Enable COMPx Clk access
	RCC->APB2ENR |=  (1 << 0);

	// Set PA3 to Analog Mode -> +
	GPIOA->MODER |= (0b11 << 6);
	// Set PA2 to Analog Mode -> -
	GPIOA->MODER |= (0b11 << 4);

	// Set internal pull-down register on PA3+
	GPIOA->PUPDR |= (0b10 << 6);

	// Init COMP2
	// Clear CSR
	COMP2->CSR = 0;

	// Set COMP2_INP input to PA3+
	COMP2->CSR |= (1 << 8);
	// Set COMP2_INM input to PA2-
	COMP2->CSR |= (0b111 << 4);

	// Enable COMP2
	COMP2->CSR |= (1 << 0);
}

// COMP3_INP -> PA0+
// COMP3_INM -> PF1-
void COMP3_Init(void){
	// Enable GPIOA Clk
	RCC->AHB2ENR |= (1 << 0);
	// Enable COMPx Clk access
	RCC->APB2ENR |=  (1 << 0);

	// Set PA1 to Analog Mode -> +
	GPIOA->MODER |= (0b11 << 2);
	// Set PA4 to Analog Mode -> -
	GPIOA->MODER |= (0b11 << 8);

	// Set internal pull-down register on PA0+
	//GPIOA->PUPDR |= (0b10 << 0);

	// Init COMP1
	// Set COMP1_INP input to PA1
	COMP1->CSR |= (0 << 8);
	// Set COMP1_INM input to PA4
	COMP1->CSR |= (0b110 << 4);

	// Enable COMP1
	COMP1->CSR |= (1 << 0);
}


