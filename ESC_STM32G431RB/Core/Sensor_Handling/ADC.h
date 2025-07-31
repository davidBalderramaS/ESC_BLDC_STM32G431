/*
 * ADC.h
 *
 *  Created on: Jul 28, 2025
 *      Author: David
 */

#ifndef SENSOR_HANDLING_ADC_H_
#define SENSOR_HANDLING_ADC_H_

#include "stm32g431xx.h"
#include <stdio.h>

extern volatile uint16_t ADC_Value_PA7;

void ADC_Poten_PA7_Init(void);
void ADC1_2_IRQHandler(void);
uint16_t ADC_Truncate(int ADC_Val_Poten);
uint16_t Duty_Cycle_Percent(uint16_t dutyCycleRange);

#endif /* SENSOR_HANDLING_ADC_H_ */
