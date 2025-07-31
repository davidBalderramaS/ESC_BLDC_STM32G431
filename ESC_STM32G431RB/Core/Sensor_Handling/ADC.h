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

#endif /* SENSOR_HANDLING_ADC_H_ */
