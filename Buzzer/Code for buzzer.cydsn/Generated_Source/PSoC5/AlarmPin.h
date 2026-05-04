/*******************************************************************************
* File Name: AlarmPin.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_AlarmPin_H) /* Pins AlarmPin_H */
#define CY_PINS_AlarmPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "AlarmPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 AlarmPin__PORT == 15 && ((AlarmPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    AlarmPin_Write(uint8 value);
void    AlarmPin_SetDriveMode(uint8 mode);
uint8   AlarmPin_ReadDataReg(void);
uint8   AlarmPin_Read(void);
void    AlarmPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   AlarmPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the AlarmPin_SetDriveMode() function.
     *  @{
     */
        #define AlarmPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define AlarmPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define AlarmPin_DM_RES_UP          PIN_DM_RES_UP
        #define AlarmPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define AlarmPin_DM_OD_LO           PIN_DM_OD_LO
        #define AlarmPin_DM_OD_HI           PIN_DM_OD_HI
        #define AlarmPin_DM_STRONG          PIN_DM_STRONG
        #define AlarmPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define AlarmPin_MASK               AlarmPin__MASK
#define AlarmPin_SHIFT              AlarmPin__SHIFT
#define AlarmPin_WIDTH              1u

/* Interrupt constants */
#if defined(AlarmPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in AlarmPin_SetInterruptMode() function.
     *  @{
     */
        #define AlarmPin_INTR_NONE      (uint16)(0x0000u)
        #define AlarmPin_INTR_RISING    (uint16)(0x0001u)
        #define AlarmPin_INTR_FALLING   (uint16)(0x0002u)
        #define AlarmPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define AlarmPin_INTR_MASK      (0x01u) 
#endif /* (AlarmPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define AlarmPin_PS                     (* (reg8 *) AlarmPin__PS)
/* Data Register */
#define AlarmPin_DR                     (* (reg8 *) AlarmPin__DR)
/* Port Number */
#define AlarmPin_PRT_NUM                (* (reg8 *) AlarmPin__PRT) 
/* Connect to Analog Globals */                                                  
#define AlarmPin_AG                     (* (reg8 *) AlarmPin__AG)                       
/* Analog MUX bux enable */
#define AlarmPin_AMUX                   (* (reg8 *) AlarmPin__AMUX) 
/* Bidirectional Enable */                                                        
#define AlarmPin_BIE                    (* (reg8 *) AlarmPin__BIE)
/* Bit-mask for Aliased Register Access */
#define AlarmPin_BIT_MASK               (* (reg8 *) AlarmPin__BIT_MASK)
/* Bypass Enable */
#define AlarmPin_BYP                    (* (reg8 *) AlarmPin__BYP)
/* Port wide control signals */                                                   
#define AlarmPin_CTL                    (* (reg8 *) AlarmPin__CTL)
/* Drive Modes */
#define AlarmPin_DM0                    (* (reg8 *) AlarmPin__DM0) 
#define AlarmPin_DM1                    (* (reg8 *) AlarmPin__DM1)
#define AlarmPin_DM2                    (* (reg8 *) AlarmPin__DM2) 
/* Input Buffer Disable Override */
#define AlarmPin_INP_DIS                (* (reg8 *) AlarmPin__INP_DIS)
/* LCD Common or Segment Drive */
#define AlarmPin_LCD_COM_SEG            (* (reg8 *) AlarmPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define AlarmPin_LCD_EN                 (* (reg8 *) AlarmPin__LCD_EN)
/* Slew Rate Control */
#define AlarmPin_SLW                    (* (reg8 *) AlarmPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define AlarmPin_PRTDSI__CAPS_SEL       (* (reg8 *) AlarmPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define AlarmPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) AlarmPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define AlarmPin_PRTDSI__OE_SEL0        (* (reg8 *) AlarmPin__PRTDSI__OE_SEL0) 
#define AlarmPin_PRTDSI__OE_SEL1        (* (reg8 *) AlarmPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define AlarmPin_PRTDSI__OUT_SEL0       (* (reg8 *) AlarmPin__PRTDSI__OUT_SEL0) 
#define AlarmPin_PRTDSI__OUT_SEL1       (* (reg8 *) AlarmPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define AlarmPin_PRTDSI__SYNC_OUT       (* (reg8 *) AlarmPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(AlarmPin__SIO_CFG)
    #define AlarmPin_SIO_HYST_EN        (* (reg8 *) AlarmPin__SIO_HYST_EN)
    #define AlarmPin_SIO_REG_HIFREQ     (* (reg8 *) AlarmPin__SIO_REG_HIFREQ)
    #define AlarmPin_SIO_CFG            (* (reg8 *) AlarmPin__SIO_CFG)
    #define AlarmPin_SIO_DIFF           (* (reg8 *) AlarmPin__SIO_DIFF)
#endif /* (AlarmPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(AlarmPin__INTSTAT)
    #define AlarmPin_INTSTAT            (* (reg8 *) AlarmPin__INTSTAT)
    #define AlarmPin_SNAP               (* (reg8 *) AlarmPin__SNAP)
    
	#define AlarmPin_0_INTTYPE_REG 		(* (reg8 *) AlarmPin__0__INTTYPE)
#endif /* (AlarmPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_AlarmPin_H */


/* [] END OF FILE */
