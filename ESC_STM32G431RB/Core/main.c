/*
 * ESC - Single Motor Driver
 * Using the stm32G431 microcontroller, back emf detection
 *
 * Author: David Balderrama S.
 * Start Date: 7/27/2025
 *
 */

#include "stm32g4xx.h"
#include "stm32g431xx.h"
#include <stdio.h>
#include <math.h>

#include "Back_EMF/COMPx.h"
#include "Sensor_Handling/ADC.h"
#include "Communication/USART_printf.h"
#include "ESC_Control/PWM_To_Drivers.h"
#include "ESC_Control/OpenLoop_Config.h"
#include "Utils/Delay_Timer.h"
#include "Utils/Utils.h"


int main(void){
	LED_PA10_Init();
	USART2_PA2_Init();
	ADC_Poten_PA7_Init(); // <- TIMER3
	Delay_TIM17_Init();

	//COMP1_Init();     // PA1+ | PA4-  -> PB
	//COMP3_Init_v2();  // PC1+ | PC0-  -> PC
	//COMP4_Init_v2();  // PB0+ | PB2-  -> PA

	PWM_PB6_TIM4_CH1_Init();  // M1H
	PWM_PB3_TIM2_CH2_Init();  // M1L

	PWM_PA15_TIM2_CH1_Init(); // M2H
	PWM_PB7_TIM4_CH2_Init();  // M2L

	PWM_PC2_TIM1_CH3_Init();  // M3H
	PWM_PC3_TIM1_CH4_Init();  // M3L


	while (1){

		Open_Loop();


		// TEST #1: Truncate Function
		//temp = ADC_Truncate(ADC_Value_PA7);
		//printf("ADC: %u \r\n", temp);
		//Delay_mS(100);

		// TEST 2: print truncated value thats passed onto the Set_DutyCycle Funct
		//Set_DutyCycle_PB6_TIM4_CH1(ADC_Value_PA7);
		//Delay_mS(100);

		// TEST 3: Truncated value BEFORE passing it onto the Set_DutyCycle Funct
		//Set_DutyCycle_PB6_TIM4_CH1(ADC_Truncate(ADC_Value_PA7));
		//Delay_mS(100);
	}
}








