/*******************************************************************************
* File Name: SysTickTimer_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "SysTickTimer.h"

static SysTickTimer_backupStruct SysTickTimer_backup;


/*******************************************************************************
* Function Name: SysTickTimer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SysTickTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void SysTickTimer_SaveConfig(void) 
{
    #if (!SysTickTimer_UsingFixedFunction)
        SysTickTimer_backup.TimerUdb = SysTickTimer_ReadCounter();
        SysTickTimer_backup.InterruptMaskValue = SysTickTimer_STATUS_MASK;
        #if (SysTickTimer_UsingHWCaptureCounter)
            SysTickTimer_backup.TimerCaptureCounter = SysTickTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!SysTickTimer_UDB_CONTROL_REG_REMOVED)
            SysTickTimer_backup.TimerControlRegister = SysTickTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: SysTickTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SysTickTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void SysTickTimer_RestoreConfig(void) 
{   
    #if (!SysTickTimer_UsingFixedFunction)

        SysTickTimer_WriteCounter(SysTickTimer_backup.TimerUdb);
        SysTickTimer_STATUS_MASK =SysTickTimer_backup.InterruptMaskValue;
        #if (SysTickTimer_UsingHWCaptureCounter)
            SysTickTimer_SetCaptureCount(SysTickTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!SysTickTimer_UDB_CONTROL_REG_REMOVED)
            SysTickTimer_WriteControlRegister(SysTickTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: SysTickTimer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SysTickTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void SysTickTimer_Sleep(void) 
{
    #if(!SysTickTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(SysTickTimer_CTRL_ENABLE == (SysTickTimer_CONTROL & SysTickTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            SysTickTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            SysTickTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    SysTickTimer_Stop();
    SysTickTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: SysTickTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SysTickTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void SysTickTimer_Wakeup(void) 
{
    SysTickTimer_RestoreConfig();
    #if(!SysTickTimer_UDB_CONTROL_REG_REMOVED)
        if(SysTickTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                SysTickTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
