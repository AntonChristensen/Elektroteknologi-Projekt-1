/*******************************************************************************
* File Name: PWM_Buzzer_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_Buzzer.h"

static PWM_Buzzer_backupStruct PWM_Buzzer_backup;


/*******************************************************************************
* Function Name: PWM_Buzzer_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Buzzer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Buzzer_SaveConfig(void) 
{

    #if(!PWM_Buzzer_UsingFixedFunction)
        #if(!PWM_Buzzer_PWMModeIsCenterAligned)
            PWM_Buzzer_backup.PWMPeriod = PWM_Buzzer_ReadPeriod();
        #endif /* (!PWM_Buzzer_PWMModeIsCenterAligned) */
        PWM_Buzzer_backup.PWMUdb = PWM_Buzzer_ReadCounter();
        #if (PWM_Buzzer_UseStatus)
            PWM_Buzzer_backup.InterruptMaskValue = PWM_Buzzer_STATUS_MASK;
        #endif /* (PWM_Buzzer_UseStatus) */

        #if(PWM_Buzzer_DeadBandMode == PWM_Buzzer__B_PWM__DBM_256_CLOCKS || \
            PWM_Buzzer_DeadBandMode == PWM_Buzzer__B_PWM__DBM_2_4_CLOCKS)
            PWM_Buzzer_backup.PWMdeadBandValue = PWM_Buzzer_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_Buzzer_KillModeMinTime)
             PWM_Buzzer_backup.PWMKillCounterPeriod = PWM_Buzzer_ReadKillTime();
        #endif /* (PWM_Buzzer_KillModeMinTime) */

        #if(PWM_Buzzer_UseControl)
            PWM_Buzzer_backup.PWMControlRegister = PWM_Buzzer_ReadControlRegister();
        #endif /* (PWM_Buzzer_UseControl) */
    #endif  /* (!PWM_Buzzer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Buzzer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Buzzer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Buzzer_RestoreConfig(void) 
{
        #if(!PWM_Buzzer_UsingFixedFunction)
            #if(!PWM_Buzzer_PWMModeIsCenterAligned)
                PWM_Buzzer_WritePeriod(PWM_Buzzer_backup.PWMPeriod);
            #endif /* (!PWM_Buzzer_PWMModeIsCenterAligned) */

            PWM_Buzzer_WriteCounter(PWM_Buzzer_backup.PWMUdb);

            #if (PWM_Buzzer_UseStatus)
                PWM_Buzzer_STATUS_MASK = PWM_Buzzer_backup.InterruptMaskValue;
            #endif /* (PWM_Buzzer_UseStatus) */

            #if(PWM_Buzzer_DeadBandMode == PWM_Buzzer__B_PWM__DBM_256_CLOCKS || \
                PWM_Buzzer_DeadBandMode == PWM_Buzzer__B_PWM__DBM_2_4_CLOCKS)
                PWM_Buzzer_WriteDeadTime(PWM_Buzzer_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_Buzzer_KillModeMinTime)
                PWM_Buzzer_WriteKillTime(PWM_Buzzer_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Buzzer_KillModeMinTime) */

            #if(PWM_Buzzer_UseControl)
                PWM_Buzzer_WriteControlRegister(PWM_Buzzer_backup.PWMControlRegister);
            #endif /* (PWM_Buzzer_UseControl) */
        #endif  /* (!PWM_Buzzer_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Buzzer_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Buzzer_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Buzzer_Sleep(void) 
{
    #if(PWM_Buzzer_UseControl)
        if(PWM_Buzzer_CTRL_ENABLE == (PWM_Buzzer_CONTROL & PWM_Buzzer_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Buzzer_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Buzzer_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Buzzer_UseControl) */

    /* Stop component */
    PWM_Buzzer_Stop();

    /* Save registers configuration */
    PWM_Buzzer_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Buzzer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Buzzer_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Buzzer_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Buzzer_RestoreConfig();

    if(PWM_Buzzer_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Buzzer_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
