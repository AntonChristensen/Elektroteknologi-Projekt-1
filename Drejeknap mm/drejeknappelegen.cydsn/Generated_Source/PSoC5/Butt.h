/*******************************************************************************
* File Name: Butt.h  
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

#if !defined(CY_PINS_Butt_H) /* Pins Butt_H */
#define CY_PINS_Butt_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Butt_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Butt__PORT == 15 && ((Butt__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Butt_Write(uint8 value);
void    Butt_SetDriveMode(uint8 mode);
uint8   Butt_ReadDataReg(void);
uint8   Butt_Read(void);
void    Butt_SetInterruptMode(uint16 position, uint16 mode);
uint8   Butt_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Butt_SetDriveMode() function.
     *  @{
     */
        #define Butt_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Butt_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Butt_DM_RES_UP          PIN_DM_RES_UP
        #define Butt_DM_RES_DWN         PIN_DM_RES_DWN
        #define Butt_DM_OD_LO           PIN_DM_OD_LO
        #define Butt_DM_OD_HI           PIN_DM_OD_HI
        #define Butt_DM_STRONG          PIN_DM_STRONG
        #define Butt_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Butt_MASK               Butt__MASK
#define Butt_SHIFT              Butt__SHIFT
#define Butt_WIDTH              1u

/* Interrupt constants */
#if defined(Butt__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Butt_SetInterruptMode() function.
     *  @{
     */
        #define Butt_INTR_NONE      (uint16)(0x0000u)
        #define Butt_INTR_RISING    (uint16)(0x0001u)
        #define Butt_INTR_FALLING   (uint16)(0x0002u)
        #define Butt_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Butt_INTR_MASK      (0x01u) 
#endif /* (Butt__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Butt_PS                     (* (reg8 *) Butt__PS)
/* Data Register */
#define Butt_DR                     (* (reg8 *) Butt__DR)
/* Port Number */
#define Butt_PRT_NUM                (* (reg8 *) Butt__PRT) 
/* Connect to Analog Globals */                                                  
#define Butt_AG                     (* (reg8 *) Butt__AG)                       
/* Analog MUX bux enable */
#define Butt_AMUX                   (* (reg8 *) Butt__AMUX) 
/* Bidirectional Enable */                                                        
#define Butt_BIE                    (* (reg8 *) Butt__BIE)
/* Bit-mask for Aliased Register Access */
#define Butt_BIT_MASK               (* (reg8 *) Butt__BIT_MASK)
/* Bypass Enable */
#define Butt_BYP                    (* (reg8 *) Butt__BYP)
/* Port wide control signals */                                                   
#define Butt_CTL                    (* (reg8 *) Butt__CTL)
/* Drive Modes */
#define Butt_DM0                    (* (reg8 *) Butt__DM0) 
#define Butt_DM1                    (* (reg8 *) Butt__DM1)
#define Butt_DM2                    (* (reg8 *) Butt__DM2) 
/* Input Buffer Disable Override */
#define Butt_INP_DIS                (* (reg8 *) Butt__INP_DIS)
/* LCD Common or Segment Drive */
#define Butt_LCD_COM_SEG            (* (reg8 *) Butt__LCD_COM_SEG)
/* Enable Segment LCD */
#define Butt_LCD_EN                 (* (reg8 *) Butt__LCD_EN)
/* Slew Rate Control */
#define Butt_SLW                    (* (reg8 *) Butt__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Butt_PRTDSI__CAPS_SEL       (* (reg8 *) Butt__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Butt_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Butt__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Butt_PRTDSI__OE_SEL0        (* (reg8 *) Butt__PRTDSI__OE_SEL0) 
#define Butt_PRTDSI__OE_SEL1        (* (reg8 *) Butt__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Butt_PRTDSI__OUT_SEL0       (* (reg8 *) Butt__PRTDSI__OUT_SEL0) 
#define Butt_PRTDSI__OUT_SEL1       (* (reg8 *) Butt__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Butt_PRTDSI__SYNC_OUT       (* (reg8 *) Butt__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Butt__SIO_CFG)
    #define Butt_SIO_HYST_EN        (* (reg8 *) Butt__SIO_HYST_EN)
    #define Butt_SIO_REG_HIFREQ     (* (reg8 *) Butt__SIO_REG_HIFREQ)
    #define Butt_SIO_CFG            (* (reg8 *) Butt__SIO_CFG)
    #define Butt_SIO_DIFF           (* (reg8 *) Butt__SIO_DIFF)
#endif /* (Butt__SIO_CFG) */

/* Interrupt Registers */
#if defined(Butt__INTSTAT)
    #define Butt_INTSTAT            (* (reg8 *) Butt__INTSTAT)
    #define Butt_SNAP               (* (reg8 *) Butt__SNAP)
    
	#define Butt_0_INTTYPE_REG 		(* (reg8 *) Butt__0__INTTYPE)
#endif /* (Butt__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Butt_H */


/* [] END OF FILE */
