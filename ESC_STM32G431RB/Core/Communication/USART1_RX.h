/*
 * USART1_RX.h
 *
 *  Created on: Aug 3, 2025
 *      Author: David
 */

#ifndef COMMUNICATION_USART1_RX_H_
#define COMMUNICATION_USART1_RX_H_

#include "stm32g431xx.h"

void USART1_PA10_Init(void);
char USART1_ReadChar(void);
int __io_getchar(void);

#endif /* COMMUNICATION_USART1_RX_H_ */

// Cant use USART1 of nucleo, of course right?
// scanf("%hu ", &userInput);
