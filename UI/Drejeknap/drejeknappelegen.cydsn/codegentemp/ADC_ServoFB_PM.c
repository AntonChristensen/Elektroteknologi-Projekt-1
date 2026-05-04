/*******************************************************************************
* File Name: ADC_ServoFB_PM.c
* Version 3.10
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_ServoFB.h"


/***************************************
* Local data allocation
***************************************/

static ADC_ServoFB_BACKUP_STRUCT  ADC_ServoFB_backup =
{
    ADC_ServoFB_DISABLED
};


/*******************************************************************************
* Function Name: ADC_ServoFB_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_ServoFB_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_ServoFB_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_ServoFB_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_ServoFB_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The ADC_ServoFB_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_ServoFB_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void ADC_ServoFB_Sleep(void)
{
    if((ADC_ServoFB_PWRMGR_SAR_REG  & ADC_ServoFB_ACT_PWR_SAR_EN) != 0u)
    {
        if((ADC_ServoFB_SAR_CSR0_REG & ADC_ServoFB_SAR_SOF_START_CONV) != 0u)
        {
            ADC_ServoFB_backup.enableState = ADC_ServoFB_ENABLED | ADC_ServoFB_STARTED;
        }
        else
        {
            ADC_ServoFB_backup.enableState = ADC_ServoFB_ENABLED;
        }
        ADC_ServoFB_Stop();
    }
    else
    {
        ADC_ServoFB_backup.enableState = ADC_ServoFB_DISABLED;
    }
}


/*******************************************************************************
* Function Name: ADC_ServoFB_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  ADC_ServoFB_Sleep() was called. If the component was enabled before the
*  ADC_ServoFB_Sleep() function was called, the
*  ADC_ServoFB_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_ServoFB_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void ADC_ServoFB_Wakeup(void)
{
    if(ADC_ServoFB_backup.enableState != ADC_ServoFB_DISABLED)
    {
        ADC_ServoFB_Enable();
        #if(ADC_ServoFB_DEFAULT_CONV_MODE != ADC_ServoFB__HARDWARE_TRIGGER)
            if((ADC_ServoFB_backup.enableState & ADC_ServoFB_STARTED) != 0u)
            {
                ADC_ServoFB_StartConvert();
            }
        #endif /* End ADC_ServoFB_DEFAULT_CONV_MODE != ADC_ServoFB__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
