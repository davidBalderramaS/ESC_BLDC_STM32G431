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

void COMP1_Init(void);
void COMP2_Init(void);
void COMP3_Init(void);

#endif /* BACK_EMF_COMPX_H_ */
