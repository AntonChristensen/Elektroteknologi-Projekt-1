/*******************************************************************************
* File Name: systick_isr.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_systick_isr_H)
#define CY_ISR_systick_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void systick_isr_Start(void);
void systick_isr_StartEx(cyisraddress address);
void systick_isr_Stop(void);

CY_ISR_PROTO(systick_isr_Interrupt);

void systick_isr_SetVector(cyisraddress address);
cyisraddress systick_isr_GetVector(void);

void systick_isr_SetPriority(uint8 priority);
uint8 systick_isr_GetPriority(void);

void systick_isr_Enable(void);
uint8 systick_isr_GetState(void);
void systick_isr_Disable(void);

void systick_isr_SetPending(void);
void systick_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the systick_isr ISR. */
#define systick_isr_INTC_VECTOR            ((reg32 *) systick_isr__INTC_VECT)

/* Address of the systick_isr ISR priority. */
#define systick_isr_INTC_PRIOR             ((reg8 *) systick_isr__INTC_PRIOR_REG)

/* Priority of the systick_isr interrupt. */
#define systick_isr_INTC_PRIOR_NUMBER      systick_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable systick_isr interrupt. */
#define systick_isr_INTC_SET_EN            ((reg32 *) systick_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the systick_isr interrupt. */
#define systick_isr_INTC_CLR_EN            ((reg32 *) systick_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the systick_isr interrupt state to pending. */
#define systick_isr_INTC_SET_PD            ((reg32 *) systick_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the systick_isr interrupt. */
#define systick_isr_INTC_CLR_PD            ((reg32 *) systick_isr__INTC_CLR_PD_REG)


#endif /* CY_ISR_systick_isr_H */


/* [] END OF FILE */
