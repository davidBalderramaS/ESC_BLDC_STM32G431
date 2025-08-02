/*
 * Delay_Timer.c
 *
 * This function uses TIM3 for an accurate delay function
 *
 */

#include "Delay_Timer.h"
#include "stm32g431xx.h"
#include <stdio.h>

void Delay_TIM3_Init(void){
	// Init Clk for TIM3
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;

	 // Wait for clock stabilization (optional, for robustness)
	 while (!(RCC->APB1ENR1 & RCC_APB1ENR1_TIM3EN)) {}

	// Set TIM3 prescaler
	     // freq = Sys_Clk / (PSC + 1)(ARR + 1)
	     // 1MHz = 16 Mhz / (16 + 1)(userInput + 1)
	     // 1MHz == 1 uS
	     // therefore, set PSC = 16 and ARR = userInput

	TIM3->PSC = (SystemCoreClock / 1000000) - 1;        // Clk pre-scaler -> 16MHz / 16 = 1MHz
	TIM3->ARR = 0xFFFF;        // Set maximum duty cycle == 1uS

    // Generate an update event to apply PSC and ARR
    TIM3->EGR |= TIM_EGR_UG;

    // Clear the counter
    TIM3->CNT = 0;

	// Enable the timer
	TIM3->CR1 |= TIM_CR1_CEN;
}

// 1,000,000 uS == 1 sec
void Delay_uS(uint16_t time_uS){
	// Reset the counter
	TIM3->CNT = 0;

	//while ((volatile uint16_t)TIM3->CNT < time_uS);
	while (TIM3->CNT < time_uS);
}

// 1,000 uS == 1 mS --> 1000 mS == 1 sec
void Delay_mS(uint16_t time_mS){

	for (uint16_t counter = 0; counter < time_mS; counter++){
		Delay_uS(1000);
	}
}




