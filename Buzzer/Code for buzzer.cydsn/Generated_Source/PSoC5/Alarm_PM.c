/*******************************************************************************
* File Name: Alarm_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Alarm.h"

/* Check for removal by optimization */
#if !defined(Alarm_Sync_ctrl_reg__REMOVED)

static Alarm_BACKUP_STRUCT  Alarm_backup = {0u};

    
/*******************************************************************************
* Function Name: Alarm_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Alarm_SaveConfig(void) 
{
    Alarm_backup.controlState = Alarm_Control;
}


/*******************************************************************************
* Function Name: Alarm_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void Alarm_RestoreConfig(void) 
{
     Alarm_Control = Alarm_backup.controlState;
}


/*******************************************************************************
* Function Name: Alarm_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Alarm_Sleep(void) 
{
    Alarm_SaveConfig();
}


/*******************************************************************************
* Function Name: Alarm_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Alarm_Wakeup(void)  
{
    Alarm_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
