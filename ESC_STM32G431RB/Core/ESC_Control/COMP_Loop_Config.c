/*
 * COMP_Loop_Config.c
 *
 *  Created on: Aug 3, 2025
 *      Author: David
 */

#include "COMP_Loop_Config.h"

#include "stm32g431xx.h"

#include "../ESC_Control/PWM_To_Drivers.h"
#include "../Sensor_Handling/ADC.h"
#include "../Utils/Delay_Timer.h"
#include "../Communication/USART_printf.h"
#include "../Back_EMF/COMPx.h"


#define COMP_FLOATING          0         // Sets PWM duty cycle to 0
#define COMP_PHASE_DELAY_uS    3000
volatile uint16_t COMP_Phase_State = 6;  // Since Open_Loop ends off at step 6, start at 6


void COMP_Loop(void){

	switch(COMP_Phase_State){
		case 1:
			// Cycle 1 -> PhaseA -> High side ON
			//            PhaseB -> low side ON
			//            PhaseC -> FLOATING
			Set_DutyCycle_PB6_TIM4_CH1(ADC_Truncate(ADC_Value_PA7)); // M1H
			Set_DutyCycle_PB7_TIM4_CH2(ADC_Truncate(ADC_Value_PA7)); // M2L

			Set_DutyCycle_PB3_TIM2_CH2(COMP_FLOATING);  // M1L
			Set_DutyCycle_PA15_TIM2_CH1(COMP_FLOATING); // M2H
			Set_DutyCycle_PC2_TIM1_CH3(COMP_FLOATING);  // M3H
			Set_DutyCycle_PC3_TIM1_CH4(COMP_FLOATING);  // M3L

			//printf("Case: %u \r\n", Phase_State);
			//printf("ADC: %u \r\n\n", ADC_Truncate(ADC_Value_PA7));

			//Delay_mS(PHASE_DELAY_MS);
			//Delay_uS(COMP_PHASE_DELAY_uS);
			while(1){
				// if COMP1_INP > COMP1_INM
				if (COMP3->CSR & COMP_CSR_VALUE){
					// Next State
					COMP_Phase_State++;
				}
			}
			break;

		case 2:
			// Cycle 2 -> PhaseA -> High side ON
			//            PhaseB -> FLOATING
			//            PhaseC -> low side ON
			Set_DutyCycle_PB6_TIM4_CH1(ADC_Truncate(ADC_Value_PA7));  // M1H
			Set_DutyCycle_PC3_TIM1_CH4(ADC_Truncate(ADC_Value_PA7));  // M3L

			Set_DutyCycle_PB3_TIM2_CH2(COMP_FLOATING);  // M1L
			Set_DutyCycle_PA15_TIM2_CH1(COMP_FLOATING); // M2H
			Set_DutyCycle_PB7_TIM4_CH2(COMP_FLOATING);  // M2L
			Set_DutyCycle_PC2_TIM1_CH3(COMP_FLOATING);  // M3H

			//printf("Case: %u \r\n", Phase_State);
			//printf("ADC: %u \r\n\n", ADC_Truncate(ADC_Value_PA7));

			//Delay_mS(PHASE_DELAY_MS);
			//Delay_uS(COMP_PHASE_DELAY_uS);
			while(1){
				// if COMP1_INP > COMP1_INM
				if (COMP2->CSR & COMP_CSR_VALUE){
					// Next State
					COMP_Phase_State++;
				}
			}
			break;

		case 3:
			// Cycle 3 -> PhaseA -> FLOATING
			//            PhaseB -> High side ON
			//            PhaseC -> low side ON
			Set_DutyCycle_PA15_TIM2_CH1(ADC_Truncate(ADC_Value_PA7)); // M2H
			Set_DutyCycle_PC3_TIM1_CH4(ADC_Truncate(ADC_Value_PA7));  // M3L

			Set_DutyCycle_PB6_TIM4_CH1(COMP_FLOATING);  // M1H
			Set_DutyCycle_PB3_TIM2_CH2(COMP_FLOATING);  // M1L
			Set_DutyCycle_PB7_TIM4_CH2(COMP_FLOATING);  // M2L
			Set_DutyCycle_PC2_TIM1_CH3(COMP_FLOATING);  // M3H

			//printf("Case: %u \r\n", Phase_State);
			//printf("ADC: %u \r\n\n", ADC_Truncate(ADC_Value_PA7));

			//Delay_mS(PHASE_DELAY_MS);
			//Delay_uS(COMP_PHASE_DELAY_uS);
			while(1){
				// if COMP1_INP > COMP1_INM
				if (COMP1->CSR & COMP_CSR_VALUE){
					// Next State
					COMP_Phase_State++;
				}
			}
			break;

		case 4:
			// Cycle 4 -> PhaseA -> Low side ON
			//            PhaseB -> High side ON
			//            PhaseC -> FLOATING
			Set_DutyCycle_PA15_TIM2_CH1(ADC_Truncate(ADC_Value_PA7)); // M2H
			Set_DutyCycle_PB3_TIM2_CH2(ADC_Truncate(ADC_Value_PA7));  // M1L

			Set_DutyCycle_PB6_TIM4_CH1(COMP_FLOATING);  // M1H
			Set_DutyCycle_PB7_TIM4_CH2(COMP_FLOATING);  // M2L
			Set_DutyCycle_PC2_TIM1_CH3(COMP_FLOATING);  // M3H
			Set_DutyCycle_PC3_TIM1_CH4(COMP_FLOATING);  // M3L

			//printf("Case: %u \r\n", Phase_State);
			//printf("ADC: %u \r\n\n", ADC_Truncate(ADC_Value_PA7));

			//Delay_mS(PHASE_DELAY_MS);
			//Delay_uS(COMP_PHASE_DELAY_uS);
			while(1){
				// if COMP1_INP > COMP1_INM
				if (COMP3->CSR & COMP_CSR_VALUE){
					// Next State
					COMP_Phase_State++;
				}
			}
			break;

		case 5:
			// Cycle 5 -> PhaseA -> Low side ON
			//            PhaseB -> FLOATING
			//            PhaseC -> High side ON
			Set_DutyCycle_PC2_TIM1_CH3(ADC_Truncate(ADC_Value_PA7));  // M3H
			Set_DutyCycle_PB3_TIM2_CH2(ADC_Truncate(ADC_Value_PA7));  // M1L

			Set_DutyCycle_PB6_TIM4_CH1(COMP_FLOATING);  // M1H
			Set_DutyCycle_PA15_TIM2_CH1(COMP_FLOATING); // M2H
			Set_DutyCycle_PB7_TIM4_CH2(COMP_FLOATING);  // M2L
			Set_DutyCycle_PC3_TIM1_CH4(COMP_FLOATING);  // M3L

			//printf("Case: %u \r\n", Phase_State);
			//printf("ADC: %u \r\n\n", ADC_Truncate(ADC_Value_PA7));

			//Delay_mS(PHASE_DELAY_MS);
			//Delay_uS(COMP_PHASE_DELAY_uS);
			while(1){
				// if COMP1_INP > COMP1_INM
				if (COMP2->CSR & COMP_CSR_VALUE){
					// Next State
					COMP_Phase_State++;
				}
			}
			break;

		case 6:
			// Cycle 6 -> PhaseA -> FLOATING
			//            PhaseB -> LOW side ON
			//            PhaseC -> High side ON
			Set_DutyCycle_PC2_TIM1_CH3(ADC_Truncate(ADC_Value_PA7));  // M3H
			Set_DutyCycle_PB7_TIM4_CH2(ADC_Truncate(ADC_Value_PA7));  // M2L

			Set_DutyCycle_PB6_TIM4_CH1(COMP_FLOATING);  // M1H
			Set_DutyCycle_PB3_TIM2_CH2(COMP_FLOATING);  // M1L
			Set_DutyCycle_PA15_TIM2_CH1(COMP_FLOATING); // M2H
			Set_DutyCycle_PC3_TIM1_CH4(COMP_FLOATING);  // M3L

			//printf("Case: %u \r\n", Phase_State);
			//printf("ADC: %u \r\n\n", ADC_Truncate(ADC_Value_PA7));

			//Delay_mS(PHASE_DELAY_MS);
			//Delay_uS(COMP_PHASE_DELAY_uS);
			while(1){
				// if COMP1_INP > COMP1_INM
				if (COMP1->CSR & COMP_CSR_VALUE){
					// Next State
					COMP_Phase_State = 1;
				}
			}
			break;

		default:
			break;
	}
}
