/*
 * OpenLoop_Config.h
 *
 *  Created on: Aug 1, 2025
 *      Author: David
 */

#ifndef ESC_CONTROL_OPENLOOP_CONFIG_H_
#define ESC_CONTROL_OPENLOOP_CONFIG_H_

#include "stm32g431xx.h"
#include "../Sensor_Handling/ADC.h"

#define PHASE_DELAY_MS 3     // 1000 uS = 1 mS
#define PHASE_DELAY_US 3000

void Open_Loop(void);

#endif /* ESC_CONTROL_OPENLOOP_CONFIG_H_ */
