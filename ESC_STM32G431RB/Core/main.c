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

/*
 * -----> Branch_ADC_truncate <-----
 *
 */

int main(void){
	LED_PA10_Init();

	COMP1_Init();     // PA1+ | PA4-
	COMP2_Init_v2();  // PA7+ | PA5-
	COMP3_Init_v2();  // PC1+ | PC0-

	USART2_PA2_Init();

	ADC_Poten_PA7_Init();

	while (1){

		printf("%u%% \r\n", Duty_Cycle_Percent(ADC_Truncate(ADC_Value_PA7)));
		Delay_Brute();

	}
}








