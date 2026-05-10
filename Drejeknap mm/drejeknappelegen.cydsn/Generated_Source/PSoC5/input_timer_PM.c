/*******************************************************************************
* File Name: input_timer_PM.c
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

#include "input_timer.h"

static input_timer_backupStruct input_timer_backup;


/*******************************************************************************
* Function Name: input_timer_SaveConfig
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
*  input_timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void input_timer_SaveConfig(void) 
{
    #if (!input_timer_UsingFixedFunction)
        input_timer_backup.TimerUdb = input_timer_ReadCounter();
        input_timer_backup.InterruptMaskValue = input_timer_STATUS_MASK;
        #if (input_timer_UsingHWCaptureCounter)
            input_timer_backup.TimerCaptureCounter = input_timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!input_timer_UDB_CONTROL_REG_REMOVED)
            input_timer_backup.TimerControlRegister = input_timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: input_timer_RestoreConfig
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
*  input_timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void input_timer_RestoreConfig(void) 
{   
    #if (!input_timer_UsingFixedFunction)

        input_timer_WriteCounter(input_timer_backup.TimerUdb);
        input_timer_STATUS_MASK =input_timer_backup.InterruptMaskValue;
        #if (input_timer_UsingHWCaptureCounter)
            input_timer_SetCaptureCount(input_timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!input_timer_UDB_CONTROL_REG_REMOVED)
            input_timer_WriteControlRegister(input_timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: input_timer_Sleep
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
*  input_timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void input_timer_Sleep(void) 
{
    #if(!input_timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(input_timer_CTRL_ENABLE == (input_timer_CONTROL & input_timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            input_timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            input_timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    input_timer_Stop();
    input_timer_SaveConfig();
}


/*******************************************************************************
* Function Name: input_timer_Wakeup
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
*  input_timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void input_timer_Wakeup(void) 
{
    input_timer_RestoreConfig();
    #if(!input_timer_UDB_CONTROL_REG_REMOVED)
        if(input_timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                input_timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
