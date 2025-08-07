/*
 * COMP_Loop_Config.h
 *
 *  Created on: Aug 3, 2025
 *      Author: David
 */

#ifndef ESC_CONTROL_COMP_LOOP_CONFIG_H_
#define ESC_CONTROL_COMP_LOOP_CONFIG_H_

#include "stm32g431xx.h"

extern volatile uint16_t COMP_Phase_State;

void Closed_Loop(void);

#endif /* ESC_CONTROL_COMP_LOOP_CONFIG_H_ */
