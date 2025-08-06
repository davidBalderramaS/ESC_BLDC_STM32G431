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
	// Enable COMPx Clk access
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	// Set PA1+ to Analog Mode
	GPIOA->MODER &= ~(0b11 << 2);
	GPIOA->MODER |= (0b11 << 2);
	// Set PA4- to Analog Mode
	GPIOA->MODER &= ~(0b11 << 8);
	GPIOA->MODER |= (0b11 << 8);

	// Disable pull-up/pull-down
	GPIOA->PUPDR &= ~(0b11 << 2);
	GPIOA->PUPDR &= ~(0b11 << 8);

	// Init COMP1
	// Clear CSR
	COMP1->CSR = 0;

	// Set COMP1_INP input to PA1
	COMP1->CSR &= ~(1 << 8);
	// Set COMP1_INM input to PA4
	COMP1->CSR |= (0b110 << 4);

	// Enable COMP1
	COMP1->CSR |= (1 << 0);
}

// COMP2_INP -> PA7+
// COMP2_INM -> PA5-
void COMP2_Init_v2(void){
	// Enable GPIOA Clk
	RCC->AHB2ENR |= (1 << 0);
	// Enable COMPx Clk access
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	// Set PA7+ to Analog Mode
	GPIOA->MODER &= ~(0b11 << 14);
	GPIOA->MODER |=  (0b11 << 14);
	// Set PA5- to Analog Mode
	GPIOA->MODER &= ~(0b11 << 10);
	GPIOA->MODER |=  (0b11 << 10);

	// Disable pull-up/pull-down
	GPIOA->PUPDR &= ~(0b11 << 10);
	GPIOA->PUPDR &= ~(0b11 << 14);


	// Init COMP2
	// Clear CSR
	COMP2->CSR = 0;

	// Set COMP2_INP input to PA7+
	COMP2->CSR |= (0 << 8);
	// Set COMP2_INM input to PA5-
	COMP2->CSR |= (0b110 << 4);

	// Enable COMP2
	COMP2->CSR |= (1 << 0);
}

// COMP3_INP -> PC1+
// COMP3_INM -> PC0-
void COMP3_Init_v2(void){
	// Enable GPIOC Clk
	RCC->AHB2ENR |= (1 << 2);
	// Enable COMPx Clk access
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	// Set PC1+ to Analog Mode
	GPIOC->MODER &= ~(0b11 << 2); // <-THIS
	GPIOC->MODER |= (0b11 << 2);
	// Set PC0- to Analog Mode
	GPIOC->MODER &= ~(0b11 << 0);
	GPIOC->MODER |= (0b11 << 0);

	// Disable pull-up/pull-down
	GPIOC->PUPDR &= ~(0b11 << 0);
	GPIOC->PUPDR &= ~(0b11 << 2);

	// Init COMP3
	// Clear CSR
	COMP3->CSR = 0;
	// Set COMP3_INP input to PC1+
	COMP3->CSR |= (1 << 8);
	// Set COMP3_INM input to PC0-
	COMP3->CSR |= (0b111 << 4);

	// Enable COMP3
	COMP3->CSR |= (1 << 0);
}

// COMP4_INP -> PB0+
// COMP4_INM -> PB2-
void COMP4_Init_v2(void){
	// Enable GPIOB Clk
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	// Enable COMPx Clk access
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	// Set PB0+ to Analog Mode
	GPIOB->MODER &= ~(0b11 << 0);
	GPIOB->MODER |= (0b11 << 0);
	// Set PB2- to Analog Mode
	GPIOB->MODER &= ~(0b11 << 4);
	GPIOB->MODER |= (0b11 << 4);

	// Disable pull-up/pull-down
	GPIOB->PUPDR &= ~(0b11 << 0);
	GPIOB->PUPDR &= ~(0b11 << 4);

	// Init COMP4
	// Clear CSR
	COMP4->CSR = 0;
	// Set COMP4_INP input to PB0+
	COMP4->CSR &= ~COMP_CSR_INPSEL;
	// Set COMP4_INM input to PB2-
	COMP4->CSR |= (0b111 << 4);

	// Enable COMP4
	COMP4->CSR |= (1 << 0);
}


/////////////////////////////////////////////////////////////////////////////
// SOLDER BRIDGE  -> MODIFY TO USE on nucleo board :(
// COMP2_INP -> PA3+
// COMP2_INM -> PA2-
void COMP2_Init(void){
	// Enable GPIOA Clk
	RCC->AHB2ENR |= (1 << 0);
	// Enable COMPx Clk access
	RCC->APB2ENR |= (1 << 0);

	// Set PA3 to Analog Mode -> +
	GPIOA->MODER &= ~(0b11 << 6);
	GPIOA->MODER |=  (0b11 << 6);
	// Set PA2 to Analog Mode -> -
	GPIOA->MODER &= ~(0b11 << 4);
	GPIOA->MODER |=  (0b11 << 4);

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
	// Enable GPIOF Clk
	RCC->AHB2ENR |= (1 << 5);
	// Enable COMPx Clk access
	RCC->APB2ENR |= (1 << 0);

	// Set PA0 to Analog Mode -> +
	GPIOA->MODER |= (0b11 << 0);
	// Set PF1 to Analog Mode -> -
	GPIOF->MODER |= (0b11 << 2);

	// Set internal pull-down register on PA0+
	//GPIOA->PUPDR |= (0b00 << 0);

	// Disable pull-up/pull-down
	GPIOA->PUPDR &= ~(0b11 << 1);   // <-- CHANGE LAST BIT
	GPIOF->PUPDR &= ~(0b11 << 1);

	// Init COMP3
	// Clear CSR
	COMP3->CSR = 0;
	// Set COMP3_INP input to PA0+
	COMP3->CSR &= ~(1 << 8);
	// Set COMP3_INM input to PF1-
	COMP3->CSR |= (0b110 << 4);

	// Enable COMP3
	COMP3->CSR |= (1 << 0);
}


