/*
 * This file is for the initialization of internal comparators
 * for the back EMF detection circuitry
 *
 * Goal: When COMPx_INP > COMPx_INM,
 *       then switch to the next commutational step in motor sequence.
 *       Pretty simple, eh?
 *
 */

#ifndef BACK_EMF_COMPX_H_
#define BACK_EMF_COMPX_H_

void COMP1_Init(void);   // PA1+ | PA4-
void COMP2_Init(void);   // PA3+ | PA2-
void COMP3_Init(void);   // PA0+ | PF1-

void COMP2_Init_v2(void); // PA7+ | PA5-
void COMP3_Init_v2(void); // PC1+ | PC0-

#endif /* BACK_EMF_COMPX_H_ */


/*
 * NOTES
 *
 * while (1){
		if (COMP3->CSR & COMP_CSR_VALUE){
			// Set LED_PA10 HIGH
			GPIOA->ODR |= LED_PA10;
		}
		else {
			// Set LED_PA10 LOW
		    GPIOA->ODR &= ~LED_PA10;
		}
	}
 *
 */
