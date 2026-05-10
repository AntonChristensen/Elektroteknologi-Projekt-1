/***************************************************************************//**
* \file USBUART_5V_OPERATION_episr.c
* \version 3.20
*
* \brief
*  This file contains the Data endpoint Interrupt Service Routines.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USBUART_5V_OPERATION_pvt.h"
#include "USBUART_5V_OPERATION_cydmac.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


#if (USBUART_5V_OPERATION_EP1_ISR_ACTIVE)
    /******************************************************************************
    * Function Name: USBUART_5V_OPERATION_EP_1_ISR
    ***************************************************************************//**
    *
    *  Endpoint 1 Interrupt Service Routine
    *
    ******************************************************************************/
    CY_ISR(USBUART_5V_OPERATION_EP_1_ISR)
    {

    #ifdef USBUART_5V_OPERATION_EP_1_ISR_ENTRY_CALLBACK
        USBUART_5V_OPERATION_EP_1_ISR_EntryCallback();
    #endif /* (USBUART_5V_OPERATION_EP_1_ISR_ENTRY_CALLBACK) */

        /* `#START EP1_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
        !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
    
        USBUART_5V_OPERATION_ClearSieEpInterruptSource(USBUART_5V_OPERATION_SIE_INT_EP1_INTR);
            
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to be read from endpoint buffer. 
        */
    #if (CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP1].addr & USBUART_5V_OPERATION_DIR_IN))
    #endif /* (CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO) */
        {
            /* Read CR0 register to clear SIE lock. */
            (void) USBUART_5V_OPERATION_SIE_EP_BASE.sieEp[USBUART_5V_OPERATION_EP1].epCr0;
            
            /* Toggle all endpoint types except ISOC. */
            if (USBUART_5V_OPERATION_GET_EP_TYPE(USBUART_5V_OPERATION_EP1) != USBUART_5V_OPERATION_EP_TYPE_ISOC)
            {
                USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP1].epToggle ^= USBUART_5V_OPERATION_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP1].apiEpState = USBUART_5V_OPERATION_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
            !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
            if (USBUART_5V_OPERATION_midi_out_ep == USBUART_5V_OPERATION_EP1)
            {
                USBUART_5V_OPERATION_MIDI_OUT_Service();
            }
        #endif /* (USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)) */
    
        /* `#START EP1_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef USBUART_5V_OPERATION_EP_1_ISR_EXIT_CALLBACK
        USBUART_5V_OPERATION_EP_1_ISR_ExitCallback();
    #endif /* (USBUART_5V_OPERATION_EP_1_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
        !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
    }

#endif /* (USBUART_5V_OPERATION_EP1_ISR_ACTIVE) */


#if (USBUART_5V_OPERATION_EP2_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: USBUART_5V_OPERATION_EP_2_ISR
    ****************************************************************************//**
    *
    *  Endpoint 2 Interrupt Service Routine.
    *
    *******************************************************************************/
    CY_ISR(USBUART_5V_OPERATION_EP_2_ISR)
    {
    #ifdef USBUART_5V_OPERATION_EP_2_ISR_ENTRY_CALLBACK
        USBUART_5V_OPERATION_EP_2_ISR_EntryCallback();
    #endif /* (USBUART_5V_OPERATION_EP_2_ISR_ENTRY_CALLBACK) */

        /* `#START EP2_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
        !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */

        USBUART_5V_OPERATION_ClearSieEpInterruptSource(USBUART_5V_OPERATION_SIE_INT_EP2_INTR);

        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to be read from endpoint buffer. 
        */
    #if (CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP2].addr & USBUART_5V_OPERATION_DIR_IN))
    #endif /* (CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO) */
        {            
            /* Read CR0 register to clear SIE lock. */
            (void) USBUART_5V_OPERATION_SIE_EP_BASE.sieEp[USBUART_5V_OPERATION_EP2].epCr0;
            
            /* Toggle all endpoint types except ISOC. */
            if (USBUART_5V_OPERATION_GET_EP_TYPE(USBUART_5V_OPERATION_EP2) != USBUART_5V_OPERATION_EP_TYPE_ISOC)
            {
                USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP2].epToggle ^= USBUART_5V_OPERATION_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP2].apiEpState = USBUART_5V_OPERATION_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
            !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
            if (USBUART_5V_OPERATION_midi_out_ep == USBUART_5V_OPERATION_EP2)
            {
                USBUART_5V_OPERATION_MIDI_OUT_Service();
            }
        #endif /* (USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)) */        
    
        /* `#START EP2_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef USBUART_5V_OPERATION_EP_2_ISR_EXIT_CALLBACK
        USBUART_5V_OPERATION_EP_2_ISR_ExitCallback();
    #endif /* (USBUART_5V_OPERATION_EP_2_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
        !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (USBUART_5V_OPERATION_EP2_ISR_ACTIVE) */


#if (USBUART_5V_OPERATION_EP3_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: USBUART_5V_OPERATION_EP_3_ISR
    ****************************************************************************//**
    *
    *  Endpoint 3 Interrupt Service Routine.
    *
    *******************************************************************************/
    CY_ISR(USBUART_5V_OPERATION_EP_3_ISR)
    {
    #ifdef USBUART_5V_OPERATION_EP_3_ISR_ENTRY_CALLBACK
        USBUART_5V_OPERATION_EP_3_ISR_EntryCallback();
    #endif /* (USBUART_5V_OPERATION_EP_3_ISR_ENTRY_CALLBACK) */

        /* `#START EP3_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
        !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */

        USBUART_5V_OPERATION_ClearSieEpInterruptSource(USBUART_5V_OPERATION_SIE_INT_EP3_INTR);    

        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to be read from endpoint buffer. 
        */
    #if (CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP3].addr & USBUART_5V_OPERATION_DIR_IN))
    #endif /* (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO) */
        {            
            /* Read CR0 register to clear SIE lock. */
            (void) USBUART_5V_OPERATION_SIE_EP_BASE.sieEp[USBUART_5V_OPERATION_EP3].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (USBUART_5V_OPERATION_GET_EP_TYPE(USBUART_5V_OPERATION_EP3) != USBUART_5V_OPERATION_EP_TYPE_ISOC)
            {
                USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP3].epToggle ^= USBUART_5V_OPERATION_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP3].apiEpState = USBUART_5V_OPERATION_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
            !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
            if (USBUART_5V_OPERATION_midi_out_ep == USBUART_5V_OPERATION_EP3)
            {
                USBUART_5V_OPERATION_MIDI_OUT_Service();
            }
        #endif /* (USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)) */        

        /* `#START EP3_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef USBUART_5V_OPERATION_EP_3_ISR_EXIT_CALLBACK
        USBUART_5V_OPERATION_EP_3_ISR_ExitCallback();
    #endif /* (USBUART_5V_OPERATION_EP_3_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
        !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (USBUART_5V_OPERATION_EP3_ISR_ACTIVE) */


#if (USBUART_5V_OPERATION_EP4_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: USBUART_5V_OPERATION_EP_4_ISR
    ****************************************************************************//**
    *
    *  Endpoint 4 Interrupt Service Routine.
    *
    *******************************************************************************/
    CY_ISR(USBUART_5V_OPERATION_EP_4_ISR)
    {
    #ifdef USBUART_5V_OPERATION_EP_4_ISR_ENTRY_CALLBACK
        USBUART_5V_OPERATION_EP_4_ISR_EntryCallback();
    #endif /* (USBUART_5V_OPERATION_EP_4_ISR_ENTRY_CALLBACK) */

        /* `#START EP4_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
        !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */

        USBUART_5V_OPERATION_ClearSieEpInterruptSource(USBUART_5V_OPERATION_SIE_INT_EP4_INTR);
        
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP4].addr & USBUART_5V_OPERATION_DIR_IN))
    #endif /* (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO) */
        {
            /* Read CR0 register to clear SIE lock. */
            (void) USBUART_5V_OPERATION_SIE_EP_BASE.sieEp[USBUART_5V_OPERATION_EP4].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (USBUART_5V_OPERATION_GET_EP_TYPE(USBUART_5V_OPERATION_EP4) != USBUART_5V_OPERATION_EP_TYPE_ISOC)
            {
                USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP4].epToggle ^= USBUART_5V_OPERATION_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP4].apiEpState = USBUART_5V_OPERATION_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
            !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
            if(USBUART_5V_OPERATION_midi_out_ep == USBUART_5V_OPERATION_EP4)
            {
                USBUART_5V_OPERATION_MIDI_OUT_Service();
            }
        #endif /* (USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)) */        

        /* `#START EP4_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef USBUART_5V_OPERATION_EP_4_ISR_EXIT_CALLBACK
        USBUART_5V_OPERATION_EP_4_ISR_ExitCallback();
    #endif /* (USBUART_5V_OPERATION_EP_4_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
        !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (USBUART_5V_OPERATION_EP4_ISR_ACTIVE) */


#if (USBUART_5V_OPERATION_EP5_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: USBUART_5V_OPERATION_EP_5_ISR
    ****************************************************************************//**
    *
    *  Endpoint 5 Interrupt Service Routine
    *
    *
    *******************************************************************************/
    CY_ISR(USBUART_5V_OPERATION_EP_5_ISR)
    {
    #ifdef USBUART_5V_OPERATION_EP_5_ISR_ENTRY_CALLBACK
        USBUART_5V_OPERATION_EP_5_ISR_EntryCallback();
    #endif /* (USBUART_5V_OPERATION_EP_5_ISR_ENTRY_CALLBACK) */

        /* `#START EP5_USER_CODE` Place your code here */

        /* `#END` */

    #if (defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && \
                 USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */

        USBUART_5V_OPERATION_ClearSieEpInterruptSource(USBUART_5V_OPERATION_SIE_INT_EP5_INTR);
    
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP5].addr & USBUART_5V_OPERATION_DIR_IN))
    #endif /* (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO) */
        {            
            /* Read CR0 register to clear SIE lock. */
            (void) USBUART_5V_OPERATION_SIE_EP_BASE.sieEp[USBUART_5V_OPERATION_EP5].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (USBUART_5V_OPERATION_GET_EP_TYPE(USBUART_5V_OPERATION_EP5) != USBUART_5V_OPERATION_EP_TYPE_ISOC)
            {
                USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP5].epToggle ^= USBUART_5V_OPERATION_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP5].apiEpState = USBUART_5V_OPERATION_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO))        
        #if (defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
            !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
            if (USBUART_5V_OPERATION_midi_out_ep == USBUART_5V_OPERATION_EP5)
            {
                USBUART_5V_OPERATION_MIDI_OUT_Service();
            }
        #endif /* (USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)) */

        /* `#START EP5_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef USBUART_5V_OPERATION_EP_5_ISR_EXIT_CALLBACK
        USBUART_5V_OPERATION_EP_5_ISR_ExitCallback();
    #endif /* (USBUART_5V_OPERATION_EP_5_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
        !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (USBUART_5V_OPERATION_EP5_ISR_ACTIVE) */


#if (USBUART_5V_OPERATION_EP6_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: USBUART_5V_OPERATION_EP_6_ISR
    ****************************************************************************//**
    *
    *  Endpoint 6 Interrupt Service Routine.
    *
    *
    *******************************************************************************/
    CY_ISR(USBUART_5V_OPERATION_EP_6_ISR)
    {
    #ifdef USBUART_5V_OPERATION_EP_6_ISR_ENTRY_CALLBACK
        USBUART_5V_OPERATION_EP_6_ISR_EntryCallback();
    #endif /* (USBUART_5V_OPERATION_EP_6_ISR_ENTRY_CALLBACK) */

        /* `#START EP6_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
        !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */

        USBUART_5V_OPERATION_ClearSieEpInterruptSource(USBUART_5V_OPERATION_SIE_INT_EP6_INTR);
        
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP6].addr & USBUART_5V_OPERATION_DIR_IN))
    #endif /* (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO) */
        {
            /* Read CR0 register to clear SIE lock. */
            (void) USBUART_5V_OPERATION_SIE_EP_BASE.sieEp[USBUART_5V_OPERATION_EP6].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (USBUART_5V_OPERATION_GET_EP_TYPE(USBUART_5V_OPERATION_EP6) != USBUART_5V_OPERATION_EP_TYPE_ISOC)
            {
                USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP6].epToggle ^= USBUART_5V_OPERATION_EPX_CNT_DATA_TOGGLE;
            }
            
            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP6].apiEpState = USBUART_5V_OPERATION_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
            !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
            if (USBUART_5V_OPERATION_midi_out_ep == USBUART_5V_OPERATION_EP6)
            {
                USBUART_5V_OPERATION_MIDI_OUT_Service();
            }
        #endif /* (USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)) */

        /* `#START EP6_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef USBUART_5V_OPERATION_EP_6_ISR_EXIT_CALLBACK
        USBUART_5V_OPERATION_EP_6_ISR_ExitCallback();
    #endif /* (USBUART_5V_OPERATION_EP_6_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
        !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (USBUART_5V_OPERATION_EP6_ISR_ACTIVE) */


#if (USBUART_5V_OPERATION_EP7_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: USBUART_5V_OPERATION_EP_7_ISR
    ****************************************************************************//**
    *
    *  Endpoint 7 Interrupt Service Routine.
    *
    *
    *******************************************************************************/
    CY_ISR(USBUART_5V_OPERATION_EP_7_ISR)
    {
    #ifdef USBUART_5V_OPERATION_EP_7_ISR_ENTRY_CALLBACK
        USBUART_5V_OPERATION_EP_7_ISR_EntryCallback();
    #endif /* (USBUART_5V_OPERATION_EP_7_ISR_ENTRY_CALLBACK) */

        /* `#START EP7_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
        !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
    
        USBUART_5V_OPERATION_ClearSieEpInterruptSource(USBUART_5V_OPERATION_SIE_INT_EP7_INTR);
        
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP7].addr & USBUART_5V_OPERATION_DIR_IN))
    #endif /* (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO) */
        {           
            /* Read CR0 register to clear SIE lock. */
            (void) USBUART_5V_OPERATION_SIE_EP_BASE.sieEp[USBUART_5V_OPERATION_EP7].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (USBUART_5V_OPERATION_GET_EP_TYPE(USBUART_5V_OPERATION_EP7) != USBUART_5V_OPERATION_EP_TYPE_ISOC)
            {
                USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP7].epToggle ^= USBUART_5V_OPERATION_EPX_CNT_DATA_TOGGLE;
            }
            
            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP7].apiEpState = USBUART_5V_OPERATION_EVENT_PENDING;
        }


    #if (!(CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
            !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
            if(USBUART_5V_OPERATION_midi_out_ep == USBUART_5V_OPERATION_EP7)
            {
                USBUART_5V_OPERATION_MIDI_OUT_Service();
            }
        #endif /* (USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)) */

        /* `#START EP7_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef USBUART_5V_OPERATION_EP_7_ISR_EXIT_CALLBACK
        USBUART_5V_OPERATION_EP_7_ISR_ExitCallback();
    #endif /* (USBUART_5V_OPERATION_EP_7_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
        !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (USBUART_5V_OPERATION_EP7_ISR_ACTIVE) */


#if (USBUART_5V_OPERATION_EP8_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: USBUART_5V_OPERATION_EP_8_ISR
    ****************************************************************************//**
    *
    *  Endpoint 8 Interrupt Service Routine
    *
    *
    *******************************************************************************/
    CY_ISR(USBUART_5V_OPERATION_EP_8_ISR)
    {
    #ifdef USBUART_5V_OPERATION_EP_8_ISR_ENTRY_CALLBACK
        USBUART_5V_OPERATION_EP_8_ISR_EntryCallback();
    #endif /* (USBUART_5V_OPERATION_EP_8_ISR_ENTRY_CALLBACK) */

        /* `#START EP8_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
        !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */

        USBUART_5V_OPERATION_ClearSieEpInterruptSource(USBUART_5V_OPERATION_SIE_INT_EP8_INTR);
        
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP8].addr & USBUART_5V_OPERATION_DIR_IN))
    #endif /* (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO) */
        {
            /* Read CR0 register to clear SIE lock. */
            (void) USBUART_5V_OPERATION_SIE_EP_BASE.sieEp[USBUART_5V_OPERATION_EP8].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (USBUART_5V_OPERATION_GET_EP_TYPE(USBUART_5V_OPERATION_EP8) != USBUART_5V_OPERATION_EP_TYPE_ISOC)
            {
                USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP8].epToggle ^= USBUART_5V_OPERATION_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_EP8].apiEpState = USBUART_5V_OPERATION_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
            !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
            if (USBUART_5V_OPERATION_midi_out_ep == USBUART_5V_OPERATION_EP8)
            {
                USBUART_5V_OPERATION_MIDI_OUT_Service();
            }
        #endif /* (USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)) */

        /* `#START EP8_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef USBUART_5V_OPERATION_EP_8_ISR_EXIT_CALLBACK
        USBUART_5V_OPERATION_EP_8_ISR_ExitCallback();
    #endif /* (USBUART_5V_OPERATION_EP_8_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
        !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (USBUART_5V_OPERATION_EP8_ISR_ACTIVE) */


#if (USBUART_5V_OPERATION_SOF_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: USBUART_5V_OPERATION_SOF_ISR
    ****************************************************************************//**
    *
    *  Start of Frame Interrupt Service Routine.
    *
    *
    *******************************************************************************/
    CY_ISR(USBUART_5V_OPERATION_SOF_ISR)
    {
    #ifdef USBUART_5V_OPERATION_SOF_ISR_ENTRY_CALLBACK
        USBUART_5V_OPERATION_SOF_ISR_EntryCallback();
    #endif /* (USBUART_5V_OPERATION_SOF_ISR_ENTRY_CALLBACK) */

        /* `#START SOF_USER_CODE` Place your code here */

        /* `#END` */

        USBUART_5V_OPERATION_ClearSieInterruptSource(USBUART_5V_OPERATION_INTR_SIE_SOF_INTR);

    #ifdef USBUART_5V_OPERATION_SOF_ISR_EXIT_CALLBACK
        USBUART_5V_OPERATION_SOF_ISR_ExitCallback();
    #endif /* (USBUART_5V_OPERATION_SOF_ISR_EXIT_CALLBACK) */
    }
#endif /* (USBUART_5V_OPERATION_SOF_ISR_ACTIVE) */


#if (USBUART_5V_OPERATION_BUS_RESET_ISR_ACTIVE)
/*******************************************************************************
* Function Name: USBUART_5V_OPERATION_BUS_RESET_ISR
****************************************************************************//**
*
*  USB Bus Reset Interrupt Service Routine.  Calls _Start with the same
*  parameters as the last USER call to _Start
*
*
*******************************************************************************/
CY_ISR(USBUART_5V_OPERATION_BUS_RESET_ISR)
{
#ifdef USBUART_5V_OPERATION_BUS_RESET_ISR_ENTRY_CALLBACK
    USBUART_5V_OPERATION_BUS_RESET_ISR_EntryCallback();
#endif /* (USBUART_5V_OPERATION_BUS_RESET_ISR_ENTRY_CALLBACK) */

    /* `#START BUS_RESET_USER_CODE` Place your code here */

    /* `#END` */

    USBUART_5V_OPERATION_ClearSieInterruptSource(USBUART_5V_OPERATION_INTR_SIE_BUS_RESET_INTR);

    USBUART_5V_OPERATION_ReInitComponent();

#ifdef USBUART_5V_OPERATION_BUS_RESET_ISR_EXIT_CALLBACK
    USBUART_5V_OPERATION_BUS_RESET_ISR_ExitCallback();
#endif /* (USBUART_5V_OPERATION_BUS_RESET_ISR_EXIT_CALLBACK) */
}
#endif /* (USBUART_5V_OPERATION_BUS_RESET_ISR_ACTIVE) */


#if (USBUART_5V_OPERATION_LPM_ACTIVE)
/***************************************************************************
* Function Name: USBUART_5V_OPERATION_INTR_LPM_ISR
************************************************************************//**
*
*   Interrupt Service Routine for LPM of the interrupt sources.
*
*
***************************************************************************/
CY_ISR(USBUART_5V_OPERATION_LPM_ISR)
{
#ifdef USBUART_5V_OPERATION_LPM_ISR_ENTRY_CALLBACK
    USBUART_5V_OPERATION_LPM_ISR_EntryCallback();
#endif /* (USBUART_5V_OPERATION_LPM_ISR_ENTRY_CALLBACK) */

    /* `#START LPM_BEGIN_USER_CODE` Place your code here */

    /* `#END` */

    USBUART_5V_OPERATION_ClearSieInterruptSource(USBUART_5V_OPERATION_INTR_SIE_LPM_INTR);

    /* `#START LPM_END_USER_CODE` Place your code here */

    /* `#END` */

#ifdef USBUART_5V_OPERATION_LPM_ISR_EXIT_CALLBACK
    USBUART_5V_OPERATION_LPM_ISR_ExitCallback();
#endif /* (USBUART_5V_OPERATION_LPM_ISR_EXIT_CALLBACK) */
}
#endif /* (USBUART_5V_OPERATION_LPM_ACTIVE) */


#if (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA && USBUART_5V_OPERATION_ARB_ISR_ACTIVE)
    /***************************************************************************
    * Function Name: USBUART_5V_OPERATION_ARB_ISR
    ************************************************************************//**
    *
    *  Arbiter Interrupt Service Routine.
    *
    *
    ***************************************************************************/
    CY_ISR(USBUART_5V_OPERATION_ARB_ISR)
    {
        uint8 arbIntrStatus;
        uint8 epStatus;
        uint8 ep = USBUART_5V_OPERATION_EP1;

    #ifdef USBUART_5V_OPERATION_ARB_ISR_ENTRY_CALLBACK
        USBUART_5V_OPERATION_ARB_ISR_EntryCallback();
    #endif /* (USBUART_5V_OPERATION_ARB_ISR_ENTRY_CALLBACK) */

        /* `#START ARB_BEGIN_USER_CODE` Place your code here */

        /* `#END` */

        /* Get pending ARB interrupt sources. */
        arbIntrStatus = USBUART_5V_OPERATION_ARB_INT_SR_REG;

        while (0u != arbIntrStatus)
        {
            /* Check which EP is interrupt source. */
            if (0u != (arbIntrStatus & 0x01u))
            {
                /* Get endpoint enable interrupt sources. */
                epStatus = (USBUART_5V_OPERATION_ARB_EP_BASE.arbEp[ep].epSr & USBUART_5V_OPERATION_ARB_EP_BASE.arbEp[ep].epIntEn);

                /* Handle IN endpoint buffer full event: happens only once when endpoint buffer is loaded. */
                if (0u != (epStatus & USBUART_5V_OPERATION_ARB_EPX_INT_IN_BUF_FULL))
                {
                    if (0u != (USBUART_5V_OPERATION_EP[ep].addr & USBUART_5V_OPERATION_DIR_IN))
                    {
                        /* Clear data ready status. */
                        USBUART_5V_OPERATION_ARB_EP_BASE.arbEp[ep].epCfg &= (uint8) ~USBUART_5V_OPERATION_ARB_EPX_CFG_IN_DATA_RDY;

                    #if (CY_PSOC3 || CY_PSOC5LP)
                        #if (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO && (USBUART_5V_OPERATION_EP_DMA_AUTO_OPT == 0u))
                            /* Set up common area DMA with rest of data. */
                            if(USBUART_5V_OPERATION_inLength[ep] > USBUART_5V_OPERATION_DMA_BYTES_PER_BURST)
                            {
                                USBUART_5V_OPERATION_LoadNextInEP(ep, 0u);
                            }
                            else
                            {
                                USBUART_5V_OPERATION_inBufFull[ep] = 1u;
                            }
                        #endif /* (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO && (USBUART_5V_OPERATION_EP_DMA_AUTO_OPT == 0u)) */
                    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

                        /* Arm IN endpoint. */
                        USBUART_5V_OPERATION_SIE_EP_BASE.sieEp[ep].epCr0 = USBUART_5V_OPERATION_EP[ep].epMode;

                    #if (defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_IN)
                        if (ep == USBUART_5V_OPERATION_midi_in_ep)
                        {
                            /* Clear MIDI input pointer. */
                            USBUART_5V_OPERATION_midiInPointer = 0u;
                        }
                    #endif /* (USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) */
                    }
                }

            #if (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_MANUAL)
                /* Handle DMA completion event for OUT endpoints. */
                if (0u != (epStatus & USBUART_5V_OPERATION_ARB_EPX_SR_DMA_GNT))
                {
                    if (0u == (USBUART_5V_OPERATION_EP[ep].addr & USBUART_5V_OPERATION_DIR_IN))
                    {
                        /* Notify user that data has been copied from endpoint buffer. */
                        USBUART_5V_OPERATION_EP[ep].apiEpState = USBUART_5V_OPERATION_NO_EVENT_PENDING;

                        /* DMA done coping data: OUT endpoint has to be re-armed by user. */
                    }
                }
            #endif /* (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_MANUAL) */

            #if (CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)
                /* Handle DMA completion event for OUT endpoints. */
                if (0u != (epStatus & USBUART_5V_OPERATION_ARB_EPX_INT_DMA_TERMIN))
                {
                    uint32 channelNum = USBUART_5V_OPERATION_DmaChan[ep];

                    /* Restore burst counter for endpoint. */
                    USBUART_5V_OPERATION_DmaEpBurstCnt[ep] = USBUART_5V_OPERATION_DMA_GET_BURST_CNT(USBUART_5V_OPERATION_DmaEpBurstCntBackup[ep]);

                    /* Disable DMA channel to restore descriptor configuration. The on-going transfer is aborted. */
                    USBUART_5V_OPERATION_CyDmaChDisable(channelNum);

                    /* Generate DMA tr_out signal to notify USB IP that DMA is done. This signal is not generated
                    * when transfer was aborted (it occurs when host writes less bytes than buffer size).
                    */
                    USBUART_5V_OPERATION_CyDmaTriggerOut(USBUART_5V_OPERATION_DmaBurstEndOut[ep]);

                    /* Restore destination address for output endpoint. */
                    USBUART_5V_OPERATION_CyDmaSetDstAddress(channelNum, USBUART_5V_OPERATION_DMA_DESCR0, (void*) ((uint32) USBUART_5V_OPERATION_DmaEpBufferAddrBackup[ep]));
                    USBUART_5V_OPERATION_CyDmaSetDstAddress(channelNum, USBUART_5V_OPERATION_DMA_DESCR1, (void*) ((uint32) USBUART_5V_OPERATION_DmaEpBufferAddrBackup[ep] +
                                                                                                                   USBUART_5V_OPERATION_DMA_BYTES_PER_BURST));

                    /* Restore number of data elements to transfer which was adjusted for last burst. */
                    if (0u != (USBUART_5V_OPERATION_DmaEpLastBurstEl[ep] & USBUART_5V_OPERATION_DMA_DESCR_REVERT))
                    {
                        USBUART_5V_OPERATION_CyDmaSetNumDataElements(channelNum, (USBUART_5V_OPERATION_DmaEpLastBurstEl[ep] >> USBUART_5V_OPERATION_DMA_DESCR_SHIFT),
                                                                             USBUART_5V_OPERATION_DMA_GET_MAX_ELEM_PER_BURST(USBUART_5V_OPERATION_DmaEpLastBurstEl[ep]));
                    }

                    /* Validate descriptor 0 and 1 (also reset current state). Command to start with descriptor 0. */
                    USBUART_5V_OPERATION_CyDmaValidateDescriptor(channelNum, USBUART_5V_OPERATION_DMA_DESCR0);
                    if (USBUART_5V_OPERATION_DmaEpBurstCntBackup[ep] > 1u)
                    {
                        USBUART_5V_OPERATION_CyDmaValidateDescriptor(channelNum, USBUART_5V_OPERATION_DMA_DESCR1);
                    }
                    USBUART_5V_OPERATION_CyDmaSetDescriptor0Next(channelNum);

                    /* Enable DMA channel: configuration complete. */
                    USBUART_5V_OPERATION_CyDmaChEnable(channelNum);
                    
                    
                    /* Read CR0 register to clear SIE lock. */
                    (void) USBUART_5V_OPERATION_SIE_EP_BASE.sieEp[ep].epCr0;
                    
                    /* Toggle all endpoint types except ISOC. */
                    if (USBUART_5V_OPERATION_GET_EP_TYPE(ep) != USBUART_5V_OPERATION_EP_TYPE_ISOC)
                    {
                        USBUART_5V_OPERATION_EP[ep].epToggle ^= USBUART_5V_OPERATION_EPX_CNT_DATA_TOGGLE;
                    }
            
                    /* Notify user that data has been copied from endpoint buffer. */
                    USBUART_5V_OPERATION_EP[ep].apiEpState = USBUART_5V_OPERATION_EVENT_PENDING;
                    
                #if (defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) && \
                    !defined(USBUART_5V_OPERATION_MAIN_SERVICE_MIDI_OUT) && USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT)
                    if (USBUART_5V_OPERATION_midi_out_ep == ep)
                    {
                        USBUART_5V_OPERATION_MIDI_OUT_Service();
                    }
                #endif /* (USBUART_5V_OPERATION_ISR_SERVICE_MIDI_OUT) */
                }
            #endif /* (CY_PSOC4 && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO) */


                /* `#START ARB_USER_CODE` Place your code here for handle Buffer Underflow/Overflow */

                /* `#END` */

            #ifdef USBUART_5V_OPERATION_ARB_ISR_CALLBACK
                USBUART_5V_OPERATION_ARB_ISR_Callback(ep, epStatus);
            #endif /* (USBUART_5V_OPERATION_ARB_ISR_CALLBACK) */

                /* Clear serviced endpoint interrupt sources. */
                USBUART_5V_OPERATION_ARB_EP_BASE.arbEp[ep].epSr = epStatus;
            }

            ++ep;
            arbIntrStatus >>= 1u;
        }

        /* `#START ARB_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef USBUART_5V_OPERATION_ARB_ISR_EXIT_CALLBACK
        USBUART_5V_OPERATION_ARB_ISR_ExitCallback();
    #endif /* (USBUART_5V_OPERATION_ARB_ISR_EXIT_CALLBACK) */
    }

#endif /*  (USBUART_5V_OPERATION_ARB_ISR_ACTIVE && USBUART_5V_OPERATION_EP_MANAGEMENT_DMA) */


#if (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)
#if (CY_PSOC4)

    /******************************************************************************
    * Function Name: USBUART_5V_OPERATION_EPxDmaDone
    ***************************************************************************//**
    *
    * \internal
    *  Endpoint  DMA Done Interrupt Service Routine basic function .
    *  
    *  \param dmaCh
    *  number of DMA channel
    *  
    *  \param ep
    *  number of USB end point
    *  
    *  \param dmaDone
    *  transfer completion flag
    *  
    *  \return
    *   updated transfer completion flag
    *
    ******************************************************************************/
    CY_INLINE static void USBUART_5V_OPERATION_EPxDmaDone(uint8 dmaCh, uint8 ep)
    {
        uint32 nextAddr;

        /* Manage data elements which remain to transfer. */
        if (0u != USBUART_5V_OPERATION_DmaEpBurstCnt[ep])
        {
            if(USBUART_5V_OPERATION_DmaEpBurstCnt[ep] <= 2u)
            {
                /* Adjust length of last burst. */
                USBUART_5V_OPERATION_CyDmaSetNumDataElements(dmaCh,
                                                    ((uint32) USBUART_5V_OPERATION_DmaEpLastBurstEl[ep] >> USBUART_5V_OPERATION_DMA_DESCR_SHIFT),
                                                    ((uint32) USBUART_5V_OPERATION_DmaEpLastBurstEl[ep] &  USBUART_5V_OPERATION_DMA_BURST_BYTES_MASK));
            }
            

            /* Advance source for input endpoint or destination for output endpoint. */
            if (0u != (USBUART_5V_OPERATION_EP[ep].addr & USBUART_5V_OPERATION_DIR_IN))
            {
                /* Change source for descriptor 0. */
                nextAddr = (uint32) USBUART_5V_OPERATION_CyDmaGetSrcAddress(dmaCh, USBUART_5V_OPERATION_DMA_DESCR0);
                nextAddr += (2u * USBUART_5V_OPERATION_DMA_BYTES_PER_BURST);
                USBUART_5V_OPERATION_CyDmaSetSrcAddress(dmaCh, USBUART_5V_OPERATION_DMA_DESCR0, (void *) nextAddr);

                /* Change source for descriptor 1. */
                nextAddr += USBUART_5V_OPERATION_DMA_BYTES_PER_BURST;
                USBUART_5V_OPERATION_CyDmaSetSrcAddress(dmaCh, USBUART_5V_OPERATION_DMA_DESCR1, (void *) nextAddr);
            }
            else
            {
                /* Change destination for descriptor 0. */
                nextAddr  = (uint32) USBUART_5V_OPERATION_CyDmaGetDstAddress(dmaCh, USBUART_5V_OPERATION_DMA_DESCR0);
                nextAddr += (2u * USBUART_5V_OPERATION_DMA_BYTES_PER_BURST);
                USBUART_5V_OPERATION_CyDmaSetDstAddress(dmaCh, USBUART_5V_OPERATION_DMA_DESCR0, (void *) nextAddr);

                /* Change destination for descriptor 1. */
                nextAddr += USBUART_5V_OPERATION_DMA_BYTES_PER_BURST;
                USBUART_5V_OPERATION_CyDmaSetDstAddress(dmaCh, USBUART_5V_OPERATION_DMA_DESCR1, (void *) nextAddr);
            }

            /* Enable DMA to execute transfer as it was disabled because there were no valid descriptor. */
            USBUART_5V_OPERATION_CyDmaValidateDescriptor(dmaCh, USBUART_5V_OPERATION_DMA_DESCR0);
            
            --USBUART_5V_OPERATION_DmaEpBurstCnt[ep];
            if (0u != USBUART_5V_OPERATION_DmaEpBurstCnt[ep])
            {
                USBUART_5V_OPERATION_CyDmaValidateDescriptor(dmaCh, USBUART_5V_OPERATION_DMA_DESCR1);
                --USBUART_5V_OPERATION_DmaEpBurstCnt[ep];
            }
            
            USBUART_5V_OPERATION_CyDmaChEnable (dmaCh);
            USBUART_5V_OPERATION_CyDmaTriggerIn(USBUART_5V_OPERATION_DmaReqOut[ep]);
        }
        else
        {
            /* No data to transfer. False DMA trig. Ignore.  */
        }

    }

    #if (USBUART_5V_OPERATION_DMA1_ACTIVE)
        /******************************************************************************
        * Function Name: USBUART_5V_OPERATION_EP1_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 1 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void USBUART_5V_OPERATION_EP1_DMA_DONE_ISR(void)
        {

            USBUART_5V_OPERATION_EPxDmaDone((uint8)USBUART_5V_OPERATION_EP1_DMA_CH,
                                                  USBUART_5V_OPERATION_EP1);
                
        }
    #endif /* (USBUART_5V_OPERATION_DMA1_ACTIVE) */


    #if (USBUART_5V_OPERATION_DMA2_ACTIVE)
        /******************************************************************************
        * Function Name: USBUART_5V_OPERATION_EP2_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 2 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void USBUART_5V_OPERATION_EP2_DMA_DONE_ISR(void)
        {

            USBUART_5V_OPERATION_EPxDmaDone((uint8)USBUART_5V_OPERATION_EP2_DMA_CH,
                                                  USBUART_5V_OPERATION_EP2);
        }
    #endif /* (USBUART_5V_OPERATION_DMA2_ACTIVE) */


    #if (USBUART_5V_OPERATION_DMA3_ACTIVE)
        /******************************************************************************
        * Function Name: USBUART_5V_OPERATION_EP3_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 3 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void USBUART_5V_OPERATION_EP3_DMA_DONE_ISR(void)
        {

            USBUART_5V_OPERATION_EPxDmaDone((uint8)USBUART_5V_OPERATION_EP3_DMA_CH,
                                                  USBUART_5V_OPERATION_EP3);
        }
    #endif /* (USBUART_5V_OPERATION_DMA3_ACTIVE) */


    #if (USBUART_5V_OPERATION_DMA4_ACTIVE)
        /******************************************************************************
        * Function Name: USBUART_5V_OPERATION_EP4_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 4 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void USBUART_5V_OPERATION_EP4_DMA_DONE_ISR(void)
        {

            USBUART_5V_OPERATION_EPxDmaDone((uint8)USBUART_5V_OPERATION_EP4_DMA_CH,
                                                  USBUART_5V_OPERATION_EP4);
        }
    #endif /* (USBUART_5V_OPERATION_DMA4_ACTIVE) */


    #if (USBUART_5V_OPERATION_DMA5_ACTIVE)
        /******************************************************************************
        * Function Name: USBUART_5V_OPERATION_EP5_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 5 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void USBUART_5V_OPERATION_EP5_DMA_DONE_ISR(void)
        {

            USBUART_5V_OPERATION_EPxDmaDone((uint8)USBUART_5V_OPERATION_EP5_DMA_CH,
                                                  USBUART_5V_OPERATION_EP5);
        }
    #endif /* (USBUART_5V_OPERATION_DMA5_ACTIVE) */


    #if (USBUART_5V_OPERATION_DMA6_ACTIVE)
        /******************************************************************************
        * Function Name: USBUART_5V_OPERATION_EP6_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 6 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void USBUART_5V_OPERATION_EP6_DMA_DONE_ISR(void)
        {

            USBUART_5V_OPERATION_EPxDmaDone((uint8)USBUART_5V_OPERATION_EP6_DMA_CH,
                                                  USBUART_5V_OPERATION_EP6);
        }
    #endif /* (USBUART_5V_OPERATION_DMA6_ACTIVE) */


    #if (USBUART_5V_OPERATION_DMA7_ACTIVE)
        /******************************************************************************
        * Function Name: USBUART_5V_OPERATION_EP7_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 7 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void USBUART_5V_OPERATION_EP7_DMA_DONE_ISR(void)
        {

            USBUART_5V_OPERATION_EPxDmaDone((uint8)USBUART_5V_OPERATION_EP7_DMA_CH,
                                                  USBUART_5V_OPERATION_EP7);
        }
    #endif /* (USBUART_5V_OPERATION_DMA7_ACTIVE) */


    #if (USBUART_5V_OPERATION_DMA8_ACTIVE)
        /******************************************************************************
        * Function Name: USBUART_5V_OPERATION_EP8_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 8 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void USBUART_5V_OPERATION_EP8_DMA_DONE_ISR(void)
        {

            USBUART_5V_OPERATION_EPxDmaDone((uint8)USBUART_5V_OPERATION_EP8_DMA_CH,
                                                  USBUART_5V_OPERATION_EP8);
        }
    #endif /* (USBUART_5V_OPERATION_DMA8_ACTIVE) */


#else
    #if (USBUART_5V_OPERATION_EP_DMA_AUTO_OPT == 0u)
        /******************************************************************************
        * Function Name: USBUART_5V_OPERATION_EP_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        CY_ISR(USBUART_5V_OPERATION_EP_DMA_DONE_ISR)
        {
            uint8 int8Status;
            uint8 int17Status;
            uint8 ep_status;
            uint8 ep = USBUART_5V_OPERATION_EP1;

        #ifdef USBUART_5V_OPERATION_EP_DMA_DONE_ISR_ENTRY_CALLBACK
            USBUART_5V_OPERATION_EP_DMA_DONE_ISR_EntryCallback();
        #endif /* (USBUART_5V_OPERATION_EP_DMA_DONE_ISR_ENTRY_CALLBACK) */

            /* `#START EP_DMA_DONE_BEGIN_USER_CODE` Place your code here */

            /* `#END` */

            /* Read clear on read status register with EP source of interrupt. */
            int17Status = USBUART_5V_OPERATION_EP17_DMA_Done_SR_Read() & USBUART_5V_OPERATION_EP17_SR_MASK;
            int8Status  = USBUART_5V_OPERATION_EP8_DMA_Done_SR_Read()  & USBUART_5V_OPERATION_EP8_SR_MASK;

            while (int8Status != 0u)
            {
                while (int17Status != 0u)
                {
                    if ((int17Status & 1u) != 0u)  /* If EpX interrupt present. */
                    {
                        /* Read Endpoint Status Register. */
                        ep_status = USBUART_5V_OPERATION_ARB_EP_BASE.arbEp[ep].epSr;

                        if ((0u == (ep_status & USBUART_5V_OPERATION_ARB_EPX_SR_IN_BUF_FULL)) &&
                            (0u ==USBUART_5V_OPERATION_inBufFull[ep]))
                        {
                            /* `#START EP_DMA_DONE_USER_CODE` Place your code here */

                            /* `#END` */

                        #ifdef USBUART_5V_OPERATION_EP_DMA_DONE_ISR_CALLBACK
                            USBUART_5V_OPERATION_EP_DMA_DONE_ISR_Callback();
                        #endif /* (USBUART_5V_OPERATION_EP_DMA_DONE_ISR_CALLBACK) */

                            /* Transfer again 2 last bytes into pre-fetch endpoint area. */
                            USBUART_5V_OPERATION_ARB_EP_BASE.arbEp[ep].rwWaMsb = 0u;
                            USBUART_5V_OPERATION_ARB_EP_BASE.arbEp[ep].rwWa = (USBUART_5V_OPERATION_DMA_BYTES_PER_BURST * ep) - USBUART_5V_OPERATION_DMA_BYTES_REPEAT;
                            USBUART_5V_OPERATION_LoadNextInEP(ep, 1u);

                            /* Set Data ready status to generate DMA request. */
                            USBUART_5V_OPERATION_ARB_EP_BASE.arbEp[ep].epCfg |= USBUART_5V_OPERATION_ARB_EPX_CFG_IN_DATA_RDY;
                        }
                    }

                    ep++;
                    int17Status >>= 1u;
                }

                int8Status >>= 1u;

                if (int8Status != 0u)
                {
                    /* Prepare pointer for EP8. */
                    ep = USBUART_5V_OPERATION_EP8;
                    int17Status = int8Status & 0x01u;
                }
            }

            /* `#START EP_DMA_DONE_END_USER_CODE` Place your code here */

            /* `#END` */

    #ifdef USBUART_5V_OPERATION_EP_DMA_DONE_ISR_EXIT_CALLBACK
        USBUART_5V_OPERATION_EP_DMA_DONE_ISR_ExitCallback();
    #endif /* (USBUART_5V_OPERATION_EP_DMA_DONE_ISR_EXIT_CALLBACK) */
        }
    #endif /* (USBUART_5V_OPERATION_EP_DMA_AUTO_OPT == 0u) */
#endif /* (CY_PSOC4) */
#endif /* (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO) */


#if (CY_PSOC4)
    /***************************************************************************
    * Function Name: USBUART_5V_OPERATION_IntrHandler
    ************************************************************************//**
    *
    *   Interrupt handler for Hi/Mid/Low ISRs.
    *
    *  regCause - The cause register of interrupt. One of the three variants:
    *       USBUART_5V_OPERATION_INTR_CAUSE_LO_REG - Low interrupts.
    *       USBUART_5V_OPERATION_INTR_CAUSE_MED_REG - Med interrupts.
    *       USBUART_5V_OPERATION_INTR_CAUSE_HI_REG - - High interrupts.
    *
    *
    ***************************************************************************/
    CY_INLINE static void USBUART_5V_OPERATION_IntrHandler(uint32 intrCause)
    {
        /* Array of pointers to component interrupt handlers. */
        static const cyisraddress USBUART_5V_OPERATION_isrCallbacks[] =
        {

        };

        uint32 cbIdx = 0u;

        /* Check arbiter interrupt source first. */
        if (0u != (intrCause & USBUART_5V_OPERATION_INTR_CAUSE_ARB_INTR))
        {
            USBUART_5V_OPERATION_isrCallbacks[USBUART_5V_OPERATION_ARB_EP_INTR_NUM]();
        }

        /* Check all other interrupt sources (except arbiter and resume). */
        intrCause = (intrCause  & USBUART_5V_OPERATION_INTR_CAUSE_CTRL_INTR_MASK) |
                    ((intrCause & USBUART_5V_OPERATION_INTR_CAUSE_EP1_8_INTR_MASK) >>
                                  USBUART_5V_OPERATION_INTR_CAUSE_EP_INTR_SHIFT);

        /* Call interrupt handlers for active interrupt sources. */
        while (0u != intrCause)
        {
            if (0u != (intrCause & 0x1u))
            {
                 USBUART_5V_OPERATION_isrCallbacks[cbIdx]();
            }

            intrCause >>= 1u;
            ++cbIdx;
        }
    }


    /***************************************************************************
    * Function Name: USBUART_5V_OPERATION_INTR_HI_ISR
    ************************************************************************//**
    *
    *   Interrupt Service Routine for the high group of the interrupt sources.
    *
    *
    ***************************************************************************/
    CY_ISR(USBUART_5V_OPERATION_INTR_HI_ISR)
    {
        USBUART_5V_OPERATION_IntrHandler(USBUART_5V_OPERATION_INTR_CAUSE_HI_REG);
    }

    /***************************************************************************
    * Function Name: USBUART_5V_OPERATION_INTR_MED_ISR
    ************************************************************************//**
    *
    *   Interrupt Service Routine for the medium group of the interrupt sources.
    *
    *
    ***************************************************************************/
    CY_ISR(USBUART_5V_OPERATION_INTR_MED_ISR)
    {
       USBUART_5V_OPERATION_IntrHandler(USBUART_5V_OPERATION_INTR_CAUSE_MED_REG);
    }

    /***************************************************************************
    * Function Name: USBUART_5V_OPERATION_INTR_LO_ISR
    ************************************************************************//**
    *
    *   Interrupt Service Routine for the low group of the interrupt sources.
    *
    *
    ***************************************************************************/
    CY_ISR(USBUART_5V_OPERATION_INTR_LO_ISR)
    {
        USBUART_5V_OPERATION_IntrHandler(USBUART_5V_OPERATION_INTR_CAUSE_LO_REG);
    }
#endif /* (CY_PSOC4) */


/* [] END OF FILE */
