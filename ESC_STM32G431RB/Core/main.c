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
#include "Utils/Utils.h"
#include "Sensor_Handling/ADC.h"
#include "Communication/USART_printf.h"
#include "ESC_Control/PWM_To_Drivers.h"

/*
 * -----> Branch_ADC_truncate <-----
 *
 */

int main(void){
	LED_PA10_Init();
	USART2_PA2_Init();
	ADC_Poten_PA7_Init();

	//COMP1_Init();     // PA1+ | PA4-  -> PB
	//COMP3_Init_v2();  // PC1+ | PC0-  -> PC
	COMP4_Init_v2();    // PB0+ | PB2-  -> PA

	PWM_PB7_TIM4_CH2_Init();
	PWM_PB6_TIM4_CH1_Init();
	PWM_PB3_TIM2_CH2_Init();
	PWM_PA15_TIM2_CH1_Init();

	//PWM_PA14_TIM8_CH2_Init();
	//PWM_PA13_TIM4_CH3_Init();

	while (1){

		//printf("%u%% \r\n", Duty_Cycle_Percent(ADC_Truncate(ADC_Value_PA7)));
		//Delay_Brute();

	}
}








