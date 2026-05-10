/*******************************************************************************
* File Name: INTPin.h  
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

#if !defined(CY_PINS_INTPin_H) /* Pins INTPin_H */
#define CY_PINS_INTPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "INTPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 INTPin__PORT == 15 && ((INTPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    INTPin_Write(uint8 value);
void    INTPin_SetDriveMode(uint8 mode);
uint8   INTPin_ReadDataReg(void);
uint8   INTPin_Read(void);
void    INTPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   INTPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the INTPin_SetDriveMode() function.
     *  @{
     */
        #define INTPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define INTPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define INTPin_DM_RES_UP          PIN_DM_RES_UP
        #define INTPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define INTPin_DM_OD_LO           PIN_DM_OD_LO
        #define INTPin_DM_OD_HI           PIN_DM_OD_HI
        #define INTPin_DM_STRONG          PIN_DM_STRONG
        #define INTPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define INTPin_MASK               INTPin__MASK
#define INTPin_SHIFT              INTPin__SHIFT
#define INTPin_WIDTH              1u

/* Interrupt constants */
#if defined(INTPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in INTPin_SetInterruptMode() function.
     *  @{
     */
        #define INTPin_INTR_NONE      (uint16)(0x0000u)
        #define INTPin_INTR_RISING    (uint16)(0x0001u)
        #define INTPin_INTR_FALLING   (uint16)(0x0002u)
        #define INTPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define INTPin_INTR_MASK      (0x01u) 
#endif /* (INTPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define INTPin_PS                     (* (reg8 *) INTPin__PS)
/* Data Register */
#define INTPin_DR                     (* (reg8 *) INTPin__DR)
/* Port Number */
#define INTPin_PRT_NUM                (* (reg8 *) INTPin__PRT) 
/* Connect to Analog Globals */                                                  
#define INTPin_AG                     (* (reg8 *) INTPin__AG)                       
/* Analog MUX bux enable */
#define INTPin_AMUX                   (* (reg8 *) INTPin__AMUX) 
/* Bidirectional Enable */                                                        
#define INTPin_BIE                    (* (reg8 *) INTPin__BIE)
/* Bit-mask for Aliased Register Access */
#define INTPin_BIT_MASK               (* (reg8 *) INTPin__BIT_MASK)
/* Bypass Enable */
#define INTPin_BYP                    (* (reg8 *) INTPin__BYP)
/* Port wide control signals */                                                   
#define INTPin_CTL                    (* (reg8 *) INTPin__CTL)
/* Drive Modes */
#define INTPin_DM0                    (* (reg8 *) INTPin__DM0) 
#define INTPin_DM1                    (* (reg8 *) INTPin__DM1)
#define INTPin_DM2                    (* (reg8 *) INTPin__DM2) 
/* Input Buffer Disable Override */
#define INTPin_INP_DIS                (* (reg8 *) INTPin__INP_DIS)
/* LCD Common or Segment Drive */
#define INTPin_LCD_COM_SEG            (* (reg8 *) INTPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define INTPin_LCD_EN                 (* (reg8 *) INTPin__LCD_EN)
/* Slew Rate Control */
#define INTPin_SLW                    (* (reg8 *) INTPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define INTPin_PRTDSI__CAPS_SEL       (* (reg8 *) INTPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define INTPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) INTPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define INTPin_PRTDSI__OE_SEL0        (* (reg8 *) INTPin__PRTDSI__OE_SEL0) 
#define INTPin_PRTDSI__OE_SEL1        (* (reg8 *) INTPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define INTPin_PRTDSI__OUT_SEL0       (* (reg8 *) INTPin__PRTDSI__OUT_SEL0) 
#define INTPin_PRTDSI__OUT_SEL1       (* (reg8 *) INTPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define INTPin_PRTDSI__SYNC_OUT       (* (reg8 *) INTPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(INTPin__SIO_CFG)
    #define INTPin_SIO_HYST_EN        (* (reg8 *) INTPin__SIO_HYST_EN)
    #define INTPin_SIO_REG_HIFREQ     (* (reg8 *) INTPin__SIO_REG_HIFREQ)
    #define INTPin_SIO_CFG            (* (reg8 *) INTPin__SIO_CFG)
    #define INTPin_SIO_DIFF           (* (reg8 *) INTPin__SIO_DIFF)
#endif /* (INTPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(INTPin__INTSTAT)
    #define INTPin_INTSTAT            (* (reg8 *) INTPin__INTSTAT)
    #define INTPin_SNAP               (* (reg8 *) INTPin__SNAP)
    
	#define INTPin_0_INTTYPE_REG 		(* (reg8 *) INTPin__0__INTTYPE)
#endif /* (INTPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_INTPin_H */


/* [] END OF FILE */
