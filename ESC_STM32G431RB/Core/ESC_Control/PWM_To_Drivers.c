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
