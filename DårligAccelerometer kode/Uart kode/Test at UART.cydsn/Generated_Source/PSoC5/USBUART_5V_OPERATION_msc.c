/***************************************************************************//**
* \file USBUART_5V_OPERATION_cdc.c
* \version 3.20
*
* \brief
*  This file contains the USB MSC Class request handler and global API for MSC 
*  class.
*
* Related Document:
*  Universal Serial Bus Class Definitions for Communication Devices Version 1.1
*
********************************************************************************
* \copyright
* Copyright 2012-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USBUART_5V_OPERATION_msc.h"
#include "USBUART_5V_OPERATION_pvt.h"
#include "cyapicallbacks.h"

#if (USBUART_5V_OPERATION_HANDLE_MSC_REQUESTS)

/***************************************
*          Internal variables
***************************************/

static uint8 USBUART_5V_OPERATION_lunCount = USBUART_5V_OPERATION_MSC_LUN_NUMBER;


/*******************************************************************************
* Function Name: USBUART_5V_OPERATION_DispatchMSCClassRqst
****************************************************************************//**
*   
*  \internal 
*  This routine dispatches MSC class requests.
*
* \return
*  Status of request processing: handled or not handled.
*
* \globalvars
*  USBUART_5V_OPERATION_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBUART_5V_OPERATION_DispatchMSCClassRqst(void) 
{
    uint8 requestHandled = USBUART_5V_OPERATION_FALSE;
    
    /* Get request data. */
    uint16 value  = USBUART_5V_OPERATION_GET_UINT16(USBUART_5V_OPERATION_wValueHiReg,  USBUART_5V_OPERATION_wValueLoReg);
    uint16 dataLength = USBUART_5V_OPERATION_GET_UINT16(USBUART_5V_OPERATION_wLengthHiReg, USBUART_5V_OPERATION_wLengthLoReg);
       
    /* Check request direction: D2H or H2D. */
    if (0u != (USBUART_5V_OPERATION_bmRequestTypeReg & USBUART_5V_OPERATION_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */
        
        if (USBUART_5V_OPERATION_MSC_GET_MAX_LUN == USBUART_5V_OPERATION_bRequestReg)
        {
            /* Check request fields. */
            if ((value  == USBUART_5V_OPERATION_MSC_GET_MAX_LUN_WVALUE) &&
                (dataLength == USBUART_5V_OPERATION_MSC_GET_MAX_LUN_WLENGTH))
            {
                /* Reply to Get Max LUN request: setup control read. */
                USBUART_5V_OPERATION_currentTD.pData = &USBUART_5V_OPERATION_lunCount;
                USBUART_5V_OPERATION_currentTD.count =  USBUART_5V_OPERATION_MSC_GET_MAX_LUN_WLENGTH;
                
                requestHandled  = USBUART_5V_OPERATION_InitControlRead();
            }
        }
    }
    else
    {
        /* Handle direction from host to device. */
        
        if (USBUART_5V_OPERATION_MSC_RESET == USBUART_5V_OPERATION_bRequestReg)
        {
            /* Check request fields. */
            if ((value  == USBUART_5V_OPERATION_MSC_RESET_WVALUE) &&
                (dataLength == USBUART_5V_OPERATION_MSC_RESET_WLENGTH))
            {
                /* Handle to Bulk-Only Reset request: no data control transfer. */
                USBUART_5V_OPERATION_currentTD.count = USBUART_5V_OPERATION_MSC_RESET_WLENGTH;
                
            #ifdef USBUART_5V_OPERATION_DISPATCH_MSC_CLASS_MSC_RESET_RQST_CALLBACK
                USBUART_5V_OPERATION_DispatchMSCClass_MSC_RESET_RQST_Callback();
            #endif /* (USBUART_5V_OPERATION_DISPATCH_MSC_CLASS_MSC_RESET_RQST_CALLBACK) */
                
                requestHandled = USBUART_5V_OPERATION_InitNoDataControlTransfer();
            }
        }
    }
    
    return (requestHandled);
}


/*******************************************************************************
* Function Name: USBUART_5V_OPERATION_MSC_SetLunCount
****************************************************************************//**
*
*  This function sets the number of logical units supported in the application. 
*  The default number of logical units is set in the component customizer.
*
*  \param lunCount: Count of the logical units. Valid range is between 1 and 16.
*
*
* \globalvars
*  USBUART_5V_OPERATION_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBUART_5V_OPERATION_MSC_SetLunCount(uint8 lunCount) 
{
    USBUART_5V_OPERATION_lunCount = (lunCount - 1u);
}


/*******************************************************************************
* Function Name: USBUART_5V_OPERATION_MSC_GetLunCount
****************************************************************************//**
*
*  This function returns the number of logical units.
*
* \return
*   Number of the logical units.
*
* \globalvars
*  USBUART_5V_OPERATION_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBUART_5V_OPERATION_MSC_GetLunCount(void) 
{
    return (USBUART_5V_OPERATION_lunCount + 1u);
}   

#endif /* (USBUART_5V_OPERATION_HANDLE_MSC_REQUESTS) */


/* [] END OF FILE */
