/*
 * PWM_To_Drivers.c
 *
 *  Created on: Jul 31, 2025
 *      Author: David
 */

#include "PWM_To_Drivers.h"
#include "stm32g431xx.h"


/*  Pin Assignment
 *  Utils:
 *  PA7  -> TIM3_CH2    -> ADC for poteniometer
 *  PA10 -> GPIOA       -> Regular output signal for LED
 *  PA2  -> USART2      -> Printf()
 *	PA11 -> USB
 *	PA12 -> USB
 *
 *  PWMs:
 *  PB7  -> TIM4_CH2  -> M1H ✅
 *  PB6  -> TIM4_CH1  -> M1L ✅
 *  PB3  -> TIM2_CH2  -> M2H ✅
 *  PA15 -> TIM2_CH1  -> M2L ✅
 *  PA14 -> TIM8_CH2  -> M3H ✅
 *  PA13 -> TIM4_CH3  -> M3L ✅
 *
 *	COMPs:
 *	PA1+ -> COMP1_INP -> PB
 *	PA4- -> COMP1_INM -> VN
 *	PB0+ -> COMP4_INP -> PA    <- TEMP use only
 *	PB2- -> COMP4_INM -> VN    <- TEMP use only
 *	PC1+ -> COMP3_INP -> PC    <- TEMP use only
 *	PC0- -> COMP3_INM -> VN    <- TEMP use only
 *
 */

// PWM for PB7 (TIM4_CH2 -> AF2)
void PWM_PB7_TIM4_CH2_Init(void){
	// Config GPIO
	// Init Clk access to GPIOB
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	// Set PB7 output to Alt Funct Mode
	GPIOB->MODER &= ~(0b11 << 14);
	GPIOB->MODER |= (0b10 << 14);      // MODE7 = Alt Funct Mode
	GPIOB->AFR[0] &= ~(0b1111 << 28);
	GPIOB->AFR[0] |= (0b0010 << 28);   // AFSEL7 set to AF2

	// GPIO settings
	GPIOB->OSPEEDR |= (0b10 << 14);    // High speed pin
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT7; // No Push-pull
	GPIOB->PUPDR  &= ~(0b11 << 14);    // No pull-up/pull-down

	// Config Timer
	// Init Clk access to TIM4
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN;
	// Set TIM4 prescaler
	     // freq = Sys_Clk / (PSC + 1)(ARR + 1)
	     // 100k Hz = 16 Mhz / (0 + 1)(160 + 1)
	     // therefore, set PSC = 0 and ARR = 159

	TIM4->PSC = 0;                   // Clk pre-scaler -> 16MHz / 160 = 100k Hz
	TIM4->ARR = 160 - 1;             // Period     (cycle length)
	TIM4->CCR2 = 0;                 // Sets Duty Cycle (ON state) , CCR2 for CH2

	// Other timer settings
	TIM4->CCMR1 &= ~(0b111 << 12);
	TIM4->CCMR1 |=  (0b110 << 12);   // CH2 set to PWM mode 1
	TIM4->CCMR1 |= TIM_CCMR1_OC2PE;  // Enable pre-load register

	TIM4->CCER &= ~TIM_CCER_CC2P;    // set output polarity to active HIGH in CH2
	TIM4->CCER |= TIM_CCER_CC2E;     // Capture/Compare enabled for CH2

	TIM4->EGR |= TIM_EGR_UG;         // Update generation (re-init the counter)
	TIM4->CR1 |= TIM_CR1_ARPE;       // Auto reload preload enable
	TIM4->CR1 |= TIM_CR1_CEN;        // Enable counter on TIM4
}

// PWM for PB6 (TIM4_CH1 -> AF2)
void PWM_PB6_TIM4_CH1_Init(void){
	// Config GPIO
	// Init Clk access to GPIOB
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	// Set PB6 output to Alt Funct Mode
	GPIOB->MODER  &= ~(0b11 << 12);
	GPIOB->MODER  |= (0b10 << 12);    // MODE6 = Alt Funct Mode
	GPIOB->AFR[0] &= ~(0b1111 << 24);
	GPIOB->AFR[0] |= (0b0010 << 24);  // AFSEL6 set to AF2

	// GPIO settings
	GPIOB->OSPEEDR |= (0b10 << 12);    // High speed pin
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT6; // No Push-pull
	GPIOB->PUPDR  &= ~(0b11 << 12);    // No pull-up/pull-down

	// Config Timer
	// Init Clk access to TIM4
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN;
	// Set TIM4 prescaler
	     // freq = Sys_Clk / (PSC + 1)(ARR + 1)
	     // 100k Hz = 16 Mhz / (0 + 1)(160 + 1)
	     // therefore, set PSC = 0 and ARR = 159

	TIM4->PSC = 0;                   // Clk pre-scaler -> 16MHz / 160 = 100k Hz
	TIM4->ARR = 160 - 1;             // Period     (cycle length)
	TIM4->CCR1 = 0;                 // Sets Duty Cycle (ON state) , CCR1 for CH1

	// Other timer settings
	TIM4->CCMR1 &= ~(0b111 << 4);    // Alternate register
	TIM4->CCMR1 |=  (0b110 << 4);    // CH1 set to PWM mode 1
	TIM4->CCMR1 |= TIM_CCMR1_OC1PE;  // Enable pre-load register

	TIM4->CCER &= ~TIM_CCER_CC1P;    // set output polarity to active HIGH in CH1
	TIM4->CCER |= TIM_CCER_CC1E;     // Capture/Compare enabled for CH1

	TIM4->EGR |= TIM_EGR_UG;         // Update generation (re-init the counter)
	TIM4->CR1 |= TIM_CR1_ARPE;       // Auto reload preload enable
	TIM4->CR1 |= TIM_CR1_CEN;        // Enable counter on TIM4
}

// PWM for PB3 (TIM2_CH2 -> AF1)
void PWM_PB3_TIM2_CH2_Init(void){
	// Config GPIO
	// Init Clk access to GPIOB
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	// Set PB3 output to Alt Funct Mode
	GPIOB->MODER  &= ~(0b11 << 6);
	GPIOB->MODER  |= (0b10 << 6);    // MODE6 = Alt Funct Mode
	GPIOB->AFR[0] &= ~(0b1111 << 12);
	GPIOB->AFR[0] |= (0b0001 << 12);  // AFSEL3 set to AF1

	// GPIO settings
	GPIOB->OSPEEDR |= (0b10 << 6);    // High speed pin
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT3; // No Push-pull
	GPIOB->PUPDR  &= ~(0b11 << 6);    // No pull-up/pull-down

	// Config Timer
	// Init Clk access to TIM2
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	// Set TIM4 prescaler
	     // freq = Sys_Clk / (PSC + 1)(ARR + 1)
	     // 100k Hz = 16 Mhz / (0 + 1)(160 + 1)
	     // therefore, set PSC = 0 and ARR = 159

	TIM2->PSC = 0;                   // Clk pre-scaler -> 16MHz / 160 = 100k Hz
	TIM2->ARR = 160 - 1;             // Period     (cycle length)
	TIM2->CCR2 = 0;                 // Sets Duty Cycle (ON state) , CCR2 for CH2

	// Other timer settings
	TIM2->CCMR1 &= ~(0b111 << 12);   // Alternate register
	TIM2->CCMR1 |=  (0b110 << 12);   // CH2 set to PWM mode 1
	TIM2->CCMR1 |= TIM_CCMR1_OC2PE;  // Enable pre-load register CH2

	TIM2->CCER &= ~TIM_CCER_CC2P;    // set output polarity to active HIGH in CH2
	TIM2->CCER |= TIM_CCER_CC2E;     // Capture/Compare enabled for CH2

	TIM2->EGR |= TIM_EGR_UG;         // Update generation (re-init the counter)
	TIM2->CR1 |= TIM_CR1_ARPE;       // Auto reload preload enable
	TIM2->CR1 |= TIM_CR1_CEN;        // Enable counter on TIM1
}

// PWM for PA15 (TIM2_CH1 -> AF1)
void PWM_PA15_TIM2_CH1_Init(void){
	// Config GPIO
	// Init Clk access to GPIOA
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	// Set PA15 output to Alt Funct Mode
	GPIOA->MODER  &= ~(0b11 << 30);
	GPIOA->MODER  |= (0b10 << 30);     // MODE15 = Alt Funct Mode
	GPIOA->AFR[1] &= ~(0b1111 << 28);
	GPIOA->AFR[1] |= (0b0001 << 28);  // AFSEL15 set to AF1

	// GPIO settings
	GPIOA->OSPEEDR |= (0b10 << 30);     // High speed pin
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT15; // No Push-pull
	GPIOA->PUPDR  &= ~(0b11 << 30);     // No pull-up/pull-down

	// Config Timer
	// Init Clk access to TIM2
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	// Set TIM4 prescaler
	     // freq = Sys_Clk / (PSC + 1)(ARR + 1)
	     // 100k Hz = 16 Mhz / (0 + 1)(160 + 1)
	     // therefore, set PSC = 0 and ARR = 159

	TIM2->PSC = 0;                   // Clk pre-scaler -> 16MHz / 160 = 100k Hz
	TIM2->ARR = 160 - 1;             // Period     (cycle length)
	TIM2->CCR1 = 0;                 // Sets Duty Cycle (ON state) , CCR2 for CH2

	// Other timer settings
	TIM2->CCMR1 &= ~(0b111 << 4);    // Alternate register
	TIM2->CCMR1 |=  (0b110 << 4);    // CH1 set to PWM mode 1
	TIM2->CCMR1 |= TIM_CCMR1_OC1PE;  // Enable pre-load register CH1

	TIM2->CCER &= ~TIM_CCER_CC1P;    // set output polarity to active HIGH in CH1
	TIM2->CCER |= TIM_CCER_CC1E;     // Capture/Compare enabled for CH1

	TIM2->EGR |= TIM_EGR_UG;         // Update generation (re-init the counter)
	TIM2->CR1 |= TIM_CR1_ARPE;       // Auto reload preload enable
	TIM2->CR1 |= TIM_CR1_CEN;        // Enable counter on TIM1
}

// PWM for PC2 (TIM1_CH3 -> AF2)
void PWM_PC2_TIM1_CH3_Init(void){
	// Config GPIO
	// Init Clk access to GPIOC
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

	// Set PC2 output to Alt Funct Mode
	GPIOC->MODER  &= ~(0b11 << 4);
	GPIOC->MODER  |= (0b10 << 4);    // MODE2 = Alt Funct Mode
	GPIOC->AFR[0] &= ~(0b1111 << 8);
	GPIOC->AFR[0] |= (0b0010 << 8);  // AFSEL2 set to AF2

	// GPIO settings
	GPIOC->OSPEEDR |= (0b10 << 4);     // High speed pin
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT2; // No Push-pull
	GPIOC->PUPDR  &= ~(0b11 << 4);     // No pull-up/pull-down

	// Config Timer
	// Init Clk access to TIM1
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	// Set TIM4 prescaler
	     // freq = Sys_Clk / (PSC + 1)(ARR + 1)
	     // 100k Hz = 16 Mhz / (0 + 1)(160 + 1)
	     // therefore, set PSC = 0 and ARR = 159

	TIM1->PSC = 0;                   // Clk pre-scaler -> 16MHz / 160 = 100k Hz
	TIM1->ARR = 160 - 1;             // Period     (cycle length)
	TIM1->CCR3 = 0;                 // Sets Duty Cycle (ON state) , CCR3 for CH3

	// Other timer settings
	TIM1->CCMR2 &= ~(0b111 << 4);    // Alternate register
	TIM1->CCMR2 |=  (0b110 << 4);    // CH3 set to PWM mode 1
	TIM1->CCMR2 |= TIM_CCMR2_OC3PE;  // Enable pre-load register CH3

	TIM1->CCER &= ~TIM_CCER_CC3P;    // set output polarity to active HIGH in CH3
	TIM1->CCER |= TIM_CCER_CC3E;     // Capture/Compare enabled for CH3

	TIM1->EGR |= TIM_EGR_UG;         // Update generation (re-init the counter)
	TIM1->CR1 |= TIM_CR1_ARPE;       // Auto reload preload enable
	TIM1->CR1 |= TIM_CR1_CEN;        // Enable counter on TIM1
	//TIM1->BDTR |= TIM_BDTR_MOE;
}

// PWM for PC3 (TIM1_CH4 -> AF2)
void PWM_PC3_TIM1_CH4_Init(void){
	// Config GPIO
	// Init Clk access to GPIOC
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

	// Set PC2 output to Alt Funct Mode
	GPIOC->MODER  &= ~(0b11 << 6);
	GPIOC->MODER  |= (0b10 << 6);     // MODE2 = Alt Funct Mode
	GPIOC->AFR[0] &= ~(0b1111 << 12);
	GPIOC->AFR[0] |= (0b0010 << 12);  // AFSEL3 set to AF2

	// GPIO settings
	GPIOC->OSPEEDR |= (0b10 << 6);     // High speed pin
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT3; // No Push-pull
	GPIOC->PUPDR  &= ~(0b11 << 6);     // No pull-up/pull-down

	// Config Timer
	// Init Clk access to TIM1
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	// Set TIM4 prescaler
	     // freq = Sys_Clk / (PSC + 1)(ARR + 1)
	     // 100k Hz = 16 Mhz / (0 + 1)(160 + 1)
	     // therefore, set PSC = 0 and ARR = 159

	TIM1->PSC = 0;                   // Clk pre-scaler -> 16MHz / 160 = 100k Hz
	TIM1->ARR = 160 - 1;             // Period     (cycle length)
	TIM1->CCR4 = 0;                 // Sets Duty Cycle (ON state) , CCR2 for CH2

	// Other timer settings
	TIM1->CCMR2 &= ~(0b111 << 12);    // Alternate register
	TIM1->CCMR2 |=  (0b110 << 12);    // CH4 set to PWM mode 1
	TIM1->CCMR2 |= TIM_CCMR2_OC4PE;  // Enable pre-load register CH4

	TIM1->CCER &= ~TIM_CCER_CC4P;    // set output polarity to active HIGH in CH4
	TIM1->CCER |= TIM_CCER_CC4E;     // Capture/Compare enabled for CH4

	TIM1->EGR |= TIM_EGR_UG;         // Update generation (re-init the counter)
	TIM1->CR1 |= TIM_CR1_ARPE;       // Auto reload preload enable
	TIM1->CR1 |= TIM_CR1_CEN;        // Enable counter on TIM1
}

/////////////////////////////////////////////////////////////////
// PWM for PA14 (TIM8_CH2 -> AF5)
void PWM_PA14_TIM8_CH2_Init(void){
	// Config GPIO
	// Init Clk access to GPIOA
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	// Set PA14 output to Alt Funct Mode
	GPIOA->MODER  &= ~(0b11 << 28);
	GPIOA->MODER  |= (0b10 << 28);     // MODE14 = Alt Funct Mode
	GPIOA->AFR[1] &= ~(0b1111 << 24);
	GPIOA->AFR[1] |= (0b0101 << 24);  // AFSEL14 set to AF1

	// GPIO settings
	GPIOA->OSPEEDR |= (0b10 << 28);     // High speed pin
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT14; // No Push-pull
	GPIOA->PUPDR  &= ~(0b11 << 28);     // No pull-up/pull-down

	// Config Timer
	// Init Clk access to TIM2
	RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
	// Set TIM8 prescaler
	     // freq = Sys_Clk / (PSC + 1)(ARR + 1)
	     // 100k Hz = 16 Mhz / (0 + 1)(160 + 1)
	     // therefore, set PSC = 0 and ARR = 159

	TIM8->PSC = 0;                   // Clk pre-scaler -> 16MHz / 160 = 100k Hz
	TIM8->ARR = 160 - 1;             // Period     (cycle length)
	TIM8->CCR2 = 80;                 // Sets Duty Cycle (ON state) , CCR2 for CH2

	// Other timer settings
	TIM8->CCMR1 &= ~(0b111 << 12);    // Alternate register
	TIM8->CCMR1 |=  (0b110 << 12);    // CH2 set to PWM mode 1
	TIM8->CCMR1 |= TIM_CCMR1_OC2PE;  // Enable pre-load register CH2

	TIM8->CCER &= ~TIM_CCER_CC2P;    // set output polarity to active HIGH in CH1
	TIM8->CCER |= TIM_CCER_CC2E;     // Capture/Compare enabled for CH1

	TIM8->EGR |= TIM_EGR_UG;         // Update generation (re-init the counter)
	TIM8->CR1 |= TIM_CR1_ARPE;       // Auto reload preload enable
	TIM8->CR1 |= TIM_CR1_CEN;        // Enable counter on TIM8
}

// PWM for PA13 (TIM4_CH3 -> AF10)
void PWM_PA13_TIM4_CH3_Init(void){
	// Config GPIO
	// Init Clk access to GPIOA
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	// Set PA13 output to Alt Funct Mode
	GPIOA->MODER  &= ~(0b11 << 26);
	GPIOA->MODER  |= (0b10 << 26);     // MODE13 = Alt Funct Mode
	GPIOA->AFR[1] &= ~(0b1111 << 20);
	GPIOA->AFR[1] |=  (0b1010 << 20);  // AFSEL13 set to AF1

	// GPIO settings
	GPIOA->OSPEEDR |= (0b10 << 26);     // High speed pin
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT13; // No Push-pull
	GPIOA->PUPDR  &= ~(0b11 << 26);     // No pull-up/pull-down

	// Config Timer
	// Init Clk access to TIM4
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN;
	// Set TIM8 prescaler
	     // freq = Sys_Clk / (PSC + 1)(ARR + 1)
	     // 100k Hz = 16 Mhz / (0 + 1)(160 + 1)
	     // therefore, set PSC = 0 and ARR = 159

	TIM4->PSC = 0;                   // Clk pre-scaler -> 16MHz / 160 = 100k Hz
	TIM4->ARR = 160 - 1;             // Period     (cycle length)
	TIM4->CCR3 = 80;                 // Sets Duty Cycle (ON state) , CCR3 for CH3

	// Other timer settings
	TIM4->CCMR2 &= ~(0b111 << 12);    // Alternate register
	TIM4->CCMR2 |=  (0b110 << 12);    // CH3 set to PWM mode 1
	TIM4->CCMR2 |= TIM_CCMR2_OC3PE;  // Enable pre-load register CH3

	TIM4->CCER &= ~TIM_CCER_CC3P;    // set output polarity to active HIGH in CH3
	TIM4->CCER |= TIM_CCER_CC3E;     // Capture/Compare enabled for CH3

	TIM4->EGR |= TIM_EGR_UG;         // Update generation (re-init the counter)
	TIM4->CR1 |= TIM_CR1_ARPE;       // Auto reload preload enable
	TIM4->CR1 |= TIM_CR1_CEN;        // Enable counter on TIM4
}





