/*******************************************************************************
* File Name: Servo_FB.h  
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

#if !defined(CY_PINS_Servo_FB_H) /* Pins Servo_FB_H */
#define CY_PINS_Servo_FB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Servo_FB_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Servo_FB__PORT == 15 && ((Servo_FB__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Servo_FB_Write(uint8 value);
void    Servo_FB_SetDriveMode(uint8 mode);
uint8   Servo_FB_ReadDataReg(void);
uint8   Servo_FB_Read(void);
void    Servo_FB_SetInterruptMode(uint16 position, uint16 mode);
uint8   Servo_FB_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Servo_FB_SetDriveMode() function.
     *  @{
     */
        #define Servo_FB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Servo_FB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Servo_FB_DM_RES_UP          PIN_DM_RES_UP
        #define Servo_FB_DM_RES_DWN         PIN_DM_RES_DWN
        #define Servo_FB_DM_OD_LO           PIN_DM_OD_LO
        #define Servo_FB_DM_OD_HI           PIN_DM_OD_HI
        #define Servo_FB_DM_STRONG          PIN_DM_STRONG
        #define Servo_FB_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Servo_FB_MASK               Servo_FB__MASK
#define Servo_FB_SHIFT              Servo_FB__SHIFT
#define Servo_FB_WIDTH              1u

/* Interrupt constants */
#if defined(Servo_FB__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Servo_FB_SetInterruptMode() function.
     *  @{
     */
        #define Servo_FB_INTR_NONE      (uint16)(0x0000u)
        #define Servo_FB_INTR_RISING    (uint16)(0x0001u)
        #define Servo_FB_INTR_FALLING   (uint16)(0x0002u)
        #define Servo_FB_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Servo_FB_INTR_MASK      (0x01u) 
#endif /* (Servo_FB__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Servo_FB_PS                     (* (reg8 *) Servo_FB__PS)
/* Data Register */
#define Servo_FB_DR                     (* (reg8 *) Servo_FB__DR)
/* Port Number */
#define Servo_FB_PRT_NUM                (* (reg8 *) Servo_FB__PRT) 
/* Connect to Analog Globals */                                                  
#define Servo_FB_AG                     (* (reg8 *) Servo_FB__AG)                       
/* Analog MUX bux enable */
#define Servo_FB_AMUX                   (* (reg8 *) Servo_FB__AMUX) 
/* Bidirectional Enable */                                                        
#define Servo_FB_BIE                    (* (reg8 *) Servo_FB__BIE)
/* Bit-mask for Aliased Register Access */
#define Servo_FB_BIT_MASK               (* (reg8 *) Servo_FB__BIT_MASK)
/* Bypass Enable */
#define Servo_FB_BYP                    (* (reg8 *) Servo_FB__BYP)
/* Port wide control signals */                                                   
#define Servo_FB_CTL                    (* (reg8 *) Servo_FB__CTL)
/* Drive Modes */
#define Servo_FB_DM0                    (* (reg8 *) Servo_FB__DM0) 
#define Servo_FB_DM1                    (* (reg8 *) Servo_FB__DM1)
#define Servo_FB_DM2                    (* (reg8 *) Servo_FB__DM2) 
/* Input Buffer Disable Override */
#define Servo_FB_INP_DIS                (* (reg8 *) Servo_FB__INP_DIS)
/* LCD Common or Segment Drive */
#define Servo_FB_LCD_COM_SEG            (* (reg8 *) Servo_FB__LCD_COM_SEG)
/* Enable Segment LCD */
#define Servo_FB_LCD_EN                 (* (reg8 *) Servo_FB__LCD_EN)
/* Slew Rate Control */
#define Servo_FB_SLW                    (* (reg8 *) Servo_FB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Servo_FB_PRTDSI__CAPS_SEL       (* (reg8 *) Servo_FB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Servo_FB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Servo_FB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Servo_FB_PRTDSI__OE_SEL0        (* (reg8 *) Servo_FB__PRTDSI__OE_SEL0) 
#define Servo_FB_PRTDSI__OE_SEL1        (* (reg8 *) Servo_FB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Servo_FB_PRTDSI__OUT_SEL0       (* (reg8 *) Servo_FB__PRTDSI__OUT_SEL0) 
#define Servo_FB_PRTDSI__OUT_SEL1       (* (reg8 *) Servo_FB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Servo_FB_PRTDSI__SYNC_OUT       (* (reg8 *) Servo_FB__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Servo_FB__SIO_CFG)
    #define Servo_FB_SIO_HYST_EN        (* (reg8 *) Servo_FB__SIO_HYST_EN)
    #define Servo_FB_SIO_REG_HIFREQ     (* (reg8 *) Servo_FB__SIO_REG_HIFREQ)
    #define Servo_FB_SIO_CFG            (* (reg8 *) Servo_FB__SIO_CFG)
    #define Servo_FB_SIO_DIFF           (* (reg8 *) Servo_FB__SIO_DIFF)
#endif /* (Servo_FB__SIO_CFG) */

/* Interrupt Registers */
#if defined(Servo_FB__INTSTAT)
    #define Servo_FB_INTSTAT            (* (reg8 *) Servo_FB__INTSTAT)
    #define Servo_FB_SNAP               (* (reg8 *) Servo_FB__SNAP)
    
	#define Servo_FB_0_INTTYPE_REG 		(* (reg8 *) Servo_FB__0__INTTYPE)
#endif /* (Servo_FB__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Servo_FB_H */


/* [] END OF FILE */
