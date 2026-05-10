/*******************************************************************************
* File Name: SysTickTimer.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_SysTickTimer_H)
#define CY_TIMER_SysTickTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 SysTickTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define SysTickTimer_Resolution                 16u
#define SysTickTimer_UsingFixedFunction         1u
#define SysTickTimer_UsingHWCaptureCounter      0u
#define SysTickTimer_SoftwareCaptureMode        0u
#define SysTickTimer_SoftwareTriggerMode        0u
#define SysTickTimer_UsingHWEnable              0u
#define SysTickTimer_EnableTriggerMode          0u
#define SysTickTimer_InterruptOnCaptureCount    0u
#define SysTickTimer_RunModeUsed                0u
#define SysTickTimer_ControlRegRemoved          0u

#if defined(SysTickTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define SysTickTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (SysTickTimer_UsingFixedFunction)
    #define SysTickTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define SysTickTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End SysTickTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!SysTickTimer_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (SysTickTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!SysTickTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}SysTickTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    SysTickTimer_Start(void) ;
void    SysTickTimer_Stop(void) ;

void    SysTickTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   SysTickTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define SysTickTimer_GetInterruptSource() SysTickTimer_ReadStatusRegister()

#if(!SysTickTimer_UDB_CONTROL_REG_REMOVED)
    uint8   SysTickTimer_ReadControlRegister(void) ;
    void    SysTickTimer_WriteControlRegister(uint8 control) ;
#endif /* (!SysTickTimer_UDB_CONTROL_REG_REMOVED) */

uint16  SysTickTimer_ReadPeriod(void) ;
void    SysTickTimer_WritePeriod(uint16 period) ;
uint16  SysTickTimer_ReadCounter(void) ;
void    SysTickTimer_WriteCounter(uint16 counter) ;
uint16  SysTickTimer_ReadCapture(void) ;
void    SysTickTimer_SoftwareCapture(void) ;

#if(!SysTickTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (SysTickTimer_SoftwareCaptureMode)
        void    SysTickTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!SysTickTimer_UsingFixedFunction) */

    #if (SysTickTimer_SoftwareTriggerMode)
        void    SysTickTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (SysTickTimer_SoftwareTriggerMode) */

    #if (SysTickTimer_EnableTriggerMode)
        void    SysTickTimer_EnableTrigger(void) ;
        void    SysTickTimer_DisableTrigger(void) ;
    #endif /* (SysTickTimer_EnableTriggerMode) */


    #if(SysTickTimer_InterruptOnCaptureCount)
        void    SysTickTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (SysTickTimer_InterruptOnCaptureCount) */

    #if (SysTickTimer_UsingHWCaptureCounter)
        void    SysTickTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   SysTickTimer_ReadCaptureCount(void) ;
    #endif /* (SysTickTimer_UsingHWCaptureCounter) */

    void SysTickTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void SysTickTimer_Init(void)          ;
void SysTickTimer_Enable(void)        ;
void SysTickTimer_SaveConfig(void)    ;
void SysTickTimer_RestoreConfig(void) ;
void SysTickTimer_Sleep(void)         ;
void SysTickTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define SysTickTimer__B_TIMER__CM_NONE 0
#define SysTickTimer__B_TIMER__CM_RISINGEDGE 1
#define SysTickTimer__B_TIMER__CM_FALLINGEDGE 2
#define SysTickTimer__B_TIMER__CM_EITHEREDGE 3
#define SysTickTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define SysTickTimer__B_TIMER__TM_NONE 0x00u
#define SysTickTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define SysTickTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define SysTickTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define SysTickTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define SysTickTimer_INIT_PERIOD             23999u
#define SysTickTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << SysTickTimer_CTRL_CAP_MODE_SHIFT))
#define SysTickTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << SysTickTimer_CTRL_TRIG_MODE_SHIFT))
#if (SysTickTimer_UsingFixedFunction)
    #define SysTickTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << SysTickTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << SysTickTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define SysTickTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << SysTickTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << SysTickTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << SysTickTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (SysTickTimer_UsingFixedFunction) */
#define SysTickTimer_INIT_CAPTURE_COUNT      (2u)
#define SysTickTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << SysTickTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (SysTickTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define SysTickTimer_STATUS         (*(reg8 *) SysTickTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define SysTickTimer_STATUS_MASK    (*(reg8 *) SysTickTimer_TimerHW__SR0 )
    #define SysTickTimer_CONTROL        (*(reg8 *) SysTickTimer_TimerHW__CFG0)
    #define SysTickTimer_CONTROL2       (*(reg8 *) SysTickTimer_TimerHW__CFG1)
    #define SysTickTimer_CONTROL2_PTR   ( (reg8 *) SysTickTimer_TimerHW__CFG1)
    #define SysTickTimer_RT1            (*(reg8 *) SysTickTimer_TimerHW__RT1)
    #define SysTickTimer_RT1_PTR        ( (reg8 *) SysTickTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define SysTickTimer_CONTROL3       (*(reg8 *) SysTickTimer_TimerHW__CFG2)
        #define SysTickTimer_CONTROL3_PTR   ( (reg8 *) SysTickTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define SysTickTimer_GLOBAL_ENABLE  (*(reg8 *) SysTickTimer_TimerHW__PM_ACT_CFG)
    #define SysTickTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) SysTickTimer_TimerHW__PM_STBY_CFG)

    #define SysTickTimer_CAPTURE_LSB         (* (reg16 *) SysTickTimer_TimerHW__CAP0 )
    #define SysTickTimer_CAPTURE_LSB_PTR       ((reg16 *) SysTickTimer_TimerHW__CAP0 )
    #define SysTickTimer_PERIOD_LSB          (* (reg16 *) SysTickTimer_TimerHW__PER0 )
    #define SysTickTimer_PERIOD_LSB_PTR        ((reg16 *) SysTickTimer_TimerHW__PER0 )
    #define SysTickTimer_COUNTER_LSB         (* (reg16 *) SysTickTimer_TimerHW__CNT_CMP0 )
    #define SysTickTimer_COUNTER_LSB_PTR       ((reg16 *) SysTickTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define SysTickTimer_BLOCK_EN_MASK                     SysTickTimer_TimerHW__PM_ACT_MSK
    #define SysTickTimer_BLOCK_STBY_EN_MASK                SysTickTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define SysTickTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define SysTickTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define SysTickTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define SysTickTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define SysTickTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define SysTickTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << SysTickTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define SysTickTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define SysTickTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << SysTickTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define SysTickTimer_CTRL_MODE_SHIFT                 0x01u
        #define SysTickTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << SysTickTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define SysTickTimer_CTRL_RCOD_SHIFT        0x02u
        #define SysTickTimer_CTRL_ENBL_SHIFT        0x00u
        #define SysTickTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define SysTickTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << SysTickTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define SysTickTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << SysTickTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define SysTickTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << SysTickTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define SysTickTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << SysTickTimer_CTRL_RCOD_SHIFT))
        #define SysTickTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << SysTickTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define SysTickTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define SysTickTimer_RT1_MASK                        ((uint8)((uint8)0x03u << SysTickTimer_RT1_SHIFT))
    #define SysTickTimer_SYNC                            ((uint8)((uint8)0x03u << SysTickTimer_RT1_SHIFT))
    #define SysTickTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define SysTickTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << SysTickTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define SysTickTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << SysTickTimer_SYNCDSI_SHIFT))

    #define SysTickTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << SysTickTimer_CTRL_MODE_SHIFT))
    #define SysTickTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << SysTickTimer_CTRL_MODE_SHIFT))
    #define SysTickTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << SysTickTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define SysTickTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define SysTickTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define SysTickTimer_STATUS_TC_INT_MASK_SHIFT        (SysTickTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define SysTickTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (SysTickTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define SysTickTimer_STATUS_TC                       ((uint8)((uint8)0x01u << SysTickTimer_STATUS_TC_SHIFT))
    #define SysTickTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << SysTickTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define SysTickTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << SysTickTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define SysTickTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << SysTickTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define SysTickTimer_STATUS              (* (reg8 *) SysTickTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define SysTickTimer_STATUS_MASK         (* (reg8 *) SysTickTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define SysTickTimer_STATUS_AUX_CTRL     (* (reg8 *) SysTickTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define SysTickTimer_CONTROL             (* (reg8 *) SysTickTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(SysTickTimer_Resolution <= 8u) /* 8-bit Timer */
        #define SysTickTimer_CAPTURE_LSB         (* (reg8 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define SysTickTimer_CAPTURE_LSB_PTR       ((reg8 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define SysTickTimer_PERIOD_LSB          (* (reg8 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define SysTickTimer_PERIOD_LSB_PTR        ((reg8 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define SysTickTimer_COUNTER_LSB         (* (reg8 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define SysTickTimer_COUNTER_LSB_PTR       ((reg8 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(SysTickTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define SysTickTimer_CAPTURE_LSB         (* (reg16 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define SysTickTimer_CAPTURE_LSB_PTR       ((reg16 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define SysTickTimer_PERIOD_LSB          (* (reg16 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define SysTickTimer_PERIOD_LSB_PTR        ((reg16 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define SysTickTimer_COUNTER_LSB         (* (reg16 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define SysTickTimer_COUNTER_LSB_PTR       ((reg16 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define SysTickTimer_CAPTURE_LSB         (* (reg16 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define SysTickTimer_CAPTURE_LSB_PTR       ((reg16 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define SysTickTimer_PERIOD_LSB          (* (reg16 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define SysTickTimer_PERIOD_LSB_PTR        ((reg16 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define SysTickTimer_COUNTER_LSB         (* (reg16 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define SysTickTimer_COUNTER_LSB_PTR       ((reg16 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(SysTickTimer_Resolution <= 24u)/* 24-bit Timer */
        #define SysTickTimer_CAPTURE_LSB         (* (reg32 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define SysTickTimer_CAPTURE_LSB_PTR       ((reg32 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define SysTickTimer_PERIOD_LSB          (* (reg32 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define SysTickTimer_PERIOD_LSB_PTR        ((reg32 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define SysTickTimer_COUNTER_LSB         (* (reg32 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define SysTickTimer_COUNTER_LSB_PTR       ((reg32 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define SysTickTimer_CAPTURE_LSB         (* (reg32 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define SysTickTimer_CAPTURE_LSB_PTR       ((reg32 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define SysTickTimer_PERIOD_LSB          (* (reg32 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define SysTickTimer_PERIOD_LSB_PTR        ((reg32 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define SysTickTimer_COUNTER_LSB         (* (reg32 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define SysTickTimer_COUNTER_LSB_PTR       ((reg32 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define SysTickTimer_CAPTURE_LSB         (* (reg32 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define SysTickTimer_CAPTURE_LSB_PTR       ((reg32 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define SysTickTimer_PERIOD_LSB          (* (reg32 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define SysTickTimer_PERIOD_LSB_PTR        ((reg32 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define SysTickTimer_COUNTER_LSB         (* (reg32 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define SysTickTimer_COUNTER_LSB_PTR       ((reg32 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define SysTickTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) SysTickTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (SysTickTimer_UsingHWCaptureCounter)
        #define SysTickTimer_CAP_COUNT              (*(reg8 *) SysTickTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define SysTickTimer_CAP_COUNT_PTR          ( (reg8 *) SysTickTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define SysTickTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) SysTickTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define SysTickTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) SysTickTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (SysTickTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define SysTickTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define SysTickTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define SysTickTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define SysTickTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define SysTickTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define SysTickTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << SysTickTimer_CTRL_INTCNT_SHIFT))
    #define SysTickTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << SysTickTimer_CTRL_TRIG_MODE_SHIFT))
    #define SysTickTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << SysTickTimer_CTRL_TRIG_EN_SHIFT))
    #define SysTickTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << SysTickTimer_CTRL_CAP_MODE_SHIFT))
    #define SysTickTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << SysTickTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define SysTickTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define SysTickTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define SysTickTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define SysTickTimer_STATUS_TC_INT_MASK_SHIFT       SysTickTimer_STATUS_TC_SHIFT
    #define SysTickTimer_STATUS_CAPTURE_INT_MASK_SHIFT  SysTickTimer_STATUS_CAPTURE_SHIFT
    #define SysTickTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define SysTickTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define SysTickTimer_STATUS_FIFOFULL_INT_MASK_SHIFT SysTickTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define SysTickTimer_STATUS_TC                      ((uint8)((uint8)0x01u << SysTickTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define SysTickTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << SysTickTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define SysTickTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << SysTickTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define SysTickTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << SysTickTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define SysTickTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << SysTickTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define SysTickTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << SysTickTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define SysTickTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << SysTickTimer_STATUS_FIFOFULL_SHIFT))

    #define SysTickTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define SysTickTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define SysTickTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define SysTickTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define SysTickTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define SysTickTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_SysTickTimer_H */


/* [] END OF FILE */
