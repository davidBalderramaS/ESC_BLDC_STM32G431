/*
 * Delay_Timer.h
 *
 *  Created on: Aug 1, 2025
 *      Author: David
 */

#ifndef UTILS_DELAY_TIMER_H_
#define UTILS_DELAY_TIMER_H_

#include "stm32g431xx.h"

void Delay_TIM3_Init(void);
void Delay_uS(uint16_t time_uS);
void Delay_mS(uint16_t time_mS);

#endif /* UTILS_DELAY_TIMER_H_ */
