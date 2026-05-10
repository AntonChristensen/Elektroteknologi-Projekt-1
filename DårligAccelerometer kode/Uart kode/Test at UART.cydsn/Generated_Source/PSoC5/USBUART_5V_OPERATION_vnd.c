/***************************************************************************//**
* \file USBUART_5V_OPERATION_vnd.c
* \version 3.20
*
* \brief
*  This file contains the  USB vendor request handler.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USBUART_5V_OPERATION_pvt.h"
#include "cyapicallbacks.h"

#if(USBUART_5V_OPERATION_EXTERN_VND == USBUART_5V_OPERATION_FALSE)

/***************************************
* Vendor Specific Declarations
***************************************/

/* `#START VENDOR_SPECIFIC_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: USBUART_5V_OPERATION_HandleVendorRqst
****************************************************************************//**
*
*  This routine provide users with a method to implement vendor specific
*  requests.
*
*  To implement vendor specific requests, add your code in this function to
*  decode and disposition the request.  If the request is handled, your code
*  must set the variable "requestHandled" to TRUE, indicating that the
*  request has been handled.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBUART_5V_OPERATION_HandleVendorRqst(void) 
{
    uint8 requestHandled = USBUART_5V_OPERATION_FALSE;

    /* Check request direction: D2H or H2D. */
    if (0u != (USBUART_5V_OPERATION_bmRequestTypeReg & USBUART_5V_OPERATION_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */
        
        switch (USBUART_5V_OPERATION_bRequestReg)
        {
            case USBUART_5V_OPERATION_GET_EXTENDED_CONFIG_DESCRIPTOR:
            #if defined(USBUART_5V_OPERATION_ENABLE_MSOS_STRING)
                USBUART_5V_OPERATION_currentTD.pData = (volatile uint8 *) &USBUART_5V_OPERATION_MSOS_CONFIGURATION_DESCR[0u];
                USBUART_5V_OPERATION_currentTD.count = USBUART_5V_OPERATION_MSOS_CONFIGURATION_DESCR[0u];
                requestHandled  = USBUART_5V_OPERATION_InitControlRead();
            #endif /* (USBUART_5V_OPERATION_ENABLE_MSOS_STRING) */
                break;
            
            default:
                break;
        }
    }

    /* `#START VENDOR_SPECIFIC_CODE` Place your vendor specific request here */

    /* `#END` */

#ifdef USBUART_5V_OPERATION_HANDLE_VENDOR_RQST_CALLBACK
    if (USBUART_5V_OPERATION_FALSE == requestHandled)
    {
        requestHandled = USBUART_5V_OPERATION_HandleVendorRqst_Callback();
    }
#endif /* (USBUART_5V_OPERATION_HANDLE_VENDOR_RQST_CALLBACK) */

    return (requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Vendor Specific Requests
********************************************************************************/

/* `#START VENDOR_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */


#endif /* USBUART_5V_OPERATION_EXTERN_VND */


/* [] END OF FILE */
