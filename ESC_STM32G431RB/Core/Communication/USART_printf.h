/*
 * USART_printf.h
 *
 *  Created on: Jul 29, 2025
 *      Author: David
 */

#ifndef COMMUNICATION_USART_PRINTF_H_
#define COMMUNICATION_USART_PRINTF_H_

#include "stm32g431xx.h"

#define BAUD_RATE  9600
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

//void USART1_PA9_Init(void);
//void USART1_Write(char ch);
//int __io_putchar(int ch);

//void USART2_PA14_Init(void);
void USART2_PA2_Init(void);
void USART2_Write(char ch);
int __io_putchar(int ch);

#endif /* COMMUNICATION_USART_PRINTF_H_ */
