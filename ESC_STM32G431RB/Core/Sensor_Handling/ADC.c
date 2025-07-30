/*
 * ADC.c
 *
 *  This source file hold all of the code for the init and function
 *  of the ADC for PA7
 *
 *  It uses GPIO, timer, and interrupt peripherals
 *
 *  This is for the potentiometer input pin that reads user input
 *  and modifies output PWM signal (duty cycle) into mosfet drivers
 *
 */

#include "ADC.h"

#include "stm32g4xx.h"
#include <stdio.h>
#include <math.h>

volatile uint16_t ADC_Value_PA7 = 0;

// Initializes GPIOA, Timer, and Interrupt peripherals for PA7
void ADC_Poten_PA7_Init(void){
	// Step 1: Init GPIOA
	// Enable GPIOA Clk access
	RCC->AHB2ENR |= (1<<0);

	// Set PA7 to analog mode
	GPIOA->MODER |= (0b11 << 14);


	// Step 2: Init Timer (TIM3_CH2 -> AF2)
    // Enable TIM3 clock
    RCC->APB1ENR1 |= (1 << 1);

    // Set prescaler and auto-reload for 10ms period (For 16 MHz Clk)
    TIM3->PSC = 16000 - 1;   // 16 MHz / 16000 = 1 kHz
    TIM3->ARR = 1000 - 1;    // 1 kHz / 1000 = 1 Hz (1s)

    // Set TIM3 to generate TRGO on update event
    TIM3->CR2 |= (0b010 << 4);

    // Enable timer
    TIM3->CR1 |= TIM_CR1_CEN;


    // Step 3: Init Interrupt (ADC2_IN4)
	// enable ADC2 Clk
	RCC->AHB2ENR |= (1 << 13);

    // Trigger from TIM2 TRGO
    ADC2->CFGR |= (0b01100 << 5);  // TIM3_TRGO (RM0440: Table 76)
    ADC2->CFGR |= (0b01 << 10);    // Trigger on rising edge

	// Regular channel sequence
	ADC2->SQR1 &= ~(0b1111 << 0);   // 1 conversion for CH0
	ADC2->SQR1 &= ~(0b1111 << 6);   // Channel 0

    // Set sample time for channel 0 -> 47.5 ADC Clk cycles
    ADC2->SMPR1 |= (0b100 << 0);

    // Enable end of conv interrupt EOCIN
    ADC2->IER |= (1 << 2);

    // Enable ADC interrupt in NVIC
    NVIC_EnableIRQ(ADC1_2_IRQn);

    // enable ADC
    ADC2->CR |= (1 << 0);
}

// ADC Interrupt thingy
void ADC_IRQHandler(void) {
    if (ADC2->ISR & ADC_ISR_EOC) {
    	// 12-bit result (0–4095)
    	ADC_Value_PA7 = ADC2->DR;
    }
}







