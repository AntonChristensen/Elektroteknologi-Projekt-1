/*******************************************************************************
* File Name: systick_clock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_systick_clock_H)
#define CY_CLOCK_systick_clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void systick_clock_Start(void) ;
void systick_clock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void systick_clock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void systick_clock_StandbyPower(uint8 state) ;
void systick_clock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 systick_clock_GetDividerRegister(void) ;
void systick_clock_SetModeRegister(uint8 modeBitMask) ;
void systick_clock_ClearModeRegister(uint8 modeBitMask) ;
uint8 systick_clock_GetModeRegister(void) ;
void systick_clock_SetSourceRegister(uint8 clkSource) ;
uint8 systick_clock_GetSourceRegister(void) ;
#if defined(systick_clock__CFG3)
void systick_clock_SetPhaseRegister(uint8 clkPhase) ;
uint8 systick_clock_GetPhaseRegister(void) ;
#endif /* defined(systick_clock__CFG3) */

#define systick_clock_Enable()                       systick_clock_Start()
#define systick_clock_Disable()                      systick_clock_Stop()
#define systick_clock_SetDivider(clkDivider)         systick_clock_SetDividerRegister(clkDivider, 1u)
#define systick_clock_SetDividerValue(clkDivider)    systick_clock_SetDividerRegister((clkDivider) - 1u, 1u)
#define systick_clock_SetMode(clkMode)               systick_clock_SetModeRegister(clkMode)
#define systick_clock_SetSource(clkSource)           systick_clock_SetSourceRegister(clkSource)
#if defined(systick_clock__CFG3)
#define systick_clock_SetPhase(clkPhase)             systick_clock_SetPhaseRegister(clkPhase)
#define systick_clock_SetPhaseValue(clkPhase)        systick_clock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(systick_clock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define systick_clock_CLKEN              (* (reg8 *) systick_clock__PM_ACT_CFG)
#define systick_clock_CLKEN_PTR          ((reg8 *) systick_clock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define systick_clock_CLKSTBY            (* (reg8 *) systick_clock__PM_STBY_CFG)
#define systick_clock_CLKSTBY_PTR        ((reg8 *) systick_clock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define systick_clock_DIV_LSB            (* (reg8 *) systick_clock__CFG0)
#define systick_clock_DIV_LSB_PTR        ((reg8 *) systick_clock__CFG0)
#define systick_clock_DIV_PTR            ((reg16 *) systick_clock__CFG0)

/* Clock MSB divider configuration register. */
#define systick_clock_DIV_MSB            (* (reg8 *) systick_clock__CFG1)
#define systick_clock_DIV_MSB_PTR        ((reg8 *) systick_clock__CFG1)

/* Mode and source configuration register */
#define systick_clock_MOD_SRC            (* (reg8 *) systick_clock__CFG2)
#define systick_clock_MOD_SRC_PTR        ((reg8 *) systick_clock__CFG2)

#if defined(systick_clock__CFG3)
/* Analog clock phase configuration register */
#define systick_clock_PHASE              (* (reg8 *) systick_clock__CFG3)
#define systick_clock_PHASE_PTR          ((reg8 *) systick_clock__CFG3)
#endif /* defined(systick_clock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define systick_clock_CLKEN_MASK         systick_clock__PM_ACT_MSK
#define systick_clock_CLKSTBY_MASK       systick_clock__PM_STBY_MSK

/* CFG2 field masks */
#define systick_clock_SRC_SEL_MSK        systick_clock__CFG2_SRC_SEL_MASK
#define systick_clock_MODE_MASK          (~(systick_clock_SRC_SEL_MSK))

#if defined(systick_clock__CFG3)
/* CFG3 phase mask */
#define systick_clock_PHASE_MASK         systick_clock__CFG3_PHASE_DLY_MASK
#endif /* defined(systick_clock__CFG3) */

#endif /* CY_CLOCK_systick_clock_H */


/* [] END OF FILE */
