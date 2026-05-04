/***************************************************************************//**
* \file .h
* \version 3.20
*
* \brief
*  This file provides private function prototypes and constants for the 
*  USBFS component. It is not intended to be used in the user project.
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_USBUART_5V_OPERATION_pvt_H)
#define CY_USBFS_USBUART_5V_OPERATION_pvt_H

#include "USBUART_5V_OPERATION.h"
   
#ifdef USBUART_5V_OPERATION_ENABLE_AUDIO_CLASS
    #include "USBUART_5V_OPERATION_audio.h"
#endif /* USBUART_5V_OPERATION_ENABLE_AUDIO_CLASS */

#ifdef USBUART_5V_OPERATION_ENABLE_CDC_CLASS
    #include "USBUART_5V_OPERATION_cdc.h"
#endif /* USBUART_5V_OPERATION_ENABLE_CDC_CLASS */

#if (USBUART_5V_OPERATION_ENABLE_MIDI_CLASS)
    #include "USBUART_5V_OPERATION_midi.h"
#endif /* (USBUART_5V_OPERATION_ENABLE_MIDI_CLASS) */

#if (USBUART_5V_OPERATION_ENABLE_MSC_CLASS)
    #include "USBUART_5V_OPERATION_msc.h"
#endif /* (USBUART_5V_OPERATION_ENABLE_MSC_CLASS) */

#if (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA)
    #if (CY_PSOC4)
        #include <CyDMA.h>
    #else
        #include <CyDmac.h>
        #if ((USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO) && (USBUART_5V_OPERATION_EP_DMA_AUTO_OPT == 0u))
            #include "USBUART_5V_OPERATION_EP_DMA_Done_isr.h"
            #include "USBUART_5V_OPERATION_EP8_DMA_Done_SR.h"
            #include "USBUART_5V_OPERATION_EP17_DMA_Done_SR.h"
        #endif /* ((USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO) && (USBUART_5V_OPERATION_EP_DMA_AUTO_OPT == 0u)) */
    #endif /* (CY_PSOC4) */
#endif /* (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA) */

#if (USBUART_5V_OPERATION_DMA1_ACTIVE)
    #include "USBUART_5V_OPERATION_ep1_dma.h"
    #define USBUART_5V_OPERATION_EP1_DMA_CH     (USBUART_5V_OPERATION_ep1_dma_CHANNEL)
#endif /* (USBUART_5V_OPERATION_DMA1_ACTIVE) */

#if (USBUART_5V_OPERATION_DMA2_ACTIVE)
    #include "USBUART_5V_OPERATION_ep2_dma.h"
    #define USBUART_5V_OPERATION_EP2_DMA_CH     (USBUART_5V_OPERATION_ep2_dma_CHANNEL)
#endif /* (USBUART_5V_OPERATION_DMA2_ACTIVE) */

#if (USBUART_5V_OPERATION_DMA3_ACTIVE)
    #include "USBUART_5V_OPERATION_ep3_dma.h"
    #define USBUART_5V_OPERATION_EP3_DMA_CH     (USBUART_5V_OPERATION_ep3_dma_CHANNEL)
#endif /* (USBUART_5V_OPERATION_DMA3_ACTIVE) */

#if (USBUART_5V_OPERATION_DMA4_ACTIVE)
    #include "USBUART_5V_OPERATION_ep4_dma.h"
    #define USBUART_5V_OPERATION_EP4_DMA_CH     (USBUART_5V_OPERATION_ep4_dma_CHANNEL)
#endif /* (USBUART_5V_OPERATION_DMA4_ACTIVE) */

#if (USBUART_5V_OPERATION_DMA5_ACTIVE)
    #include "USBUART_5V_OPERATION_ep5_dma.h"
    #define USBUART_5V_OPERATION_EP5_DMA_CH     (USBUART_5V_OPERATION_ep5_dma_CHANNEL)
#endif /* (USBUART_5V_OPERATION_DMA5_ACTIVE) */

#if (USBUART_5V_OPERATION_DMA6_ACTIVE)
    #include "USBUART_5V_OPERATION_ep6_dma.h"
    #define USBUART_5V_OPERATION_EP6_DMA_CH     (USBUART_5V_OPERATION_ep6_dma_CHANNEL)
#endif /* (USBUART_5V_OPERATION_DMA6_ACTIVE) */

#if (USBUART_5V_OPERATION_DMA7_ACTIVE)
    #include "USBUART_5V_OPERATION_ep7_dma.h"
    #define USBUART_5V_OPERATION_EP7_DMA_CH     (USBUART_5V_OPERATION_ep7_dma_CHANNEL)
#endif /* (USBUART_5V_OPERATION_DMA7_ACTIVE) */

#if (USBUART_5V_OPERATION_DMA8_ACTIVE)
    #include "USBUART_5V_OPERATION_ep8_dma.h"
    #define USBUART_5V_OPERATION_EP8_DMA_CH     (USBUART_5V_OPERATION_ep8_dma_CHANNEL)
#endif /* (USBUART_5V_OPERATION_DMA8_ACTIVE) */


/***************************************
*     Private Variables
***************************************/

/* Generated external references for descriptors. */
extern const uint8 CYCODE USBUART_5V_OPERATION_DEVICE0_DESCR[18u];
extern const uint8 CYCODE USBUART_5V_OPERATION_DEVICE0_CONFIGURATION0_DESCR[67u];
extern const T_USBUART_5V_OPERATION_EP_SETTINGS_BLOCK CYCODE USBUART_5V_OPERATION_DEVICE0_CONFIGURATION0_EP_SETTINGS_TABLE[3u];
extern const uint8 CYCODE USBUART_5V_OPERATION_DEVICE0_CONFIGURATION0_INTERFACE_CLASS[2u];
extern const T_USBUART_5V_OPERATION_LUT CYCODE USBUART_5V_OPERATION_DEVICE0_CONFIGURATION0_TABLE[5u];
extern const T_USBUART_5V_OPERATION_LUT CYCODE USBUART_5V_OPERATION_DEVICE0_TABLE[3u];
extern const T_USBUART_5V_OPERATION_LUT CYCODE USBUART_5V_OPERATION_TABLE[1u];
extern const uint8 CYCODE USBUART_5V_OPERATION_SN_STRING_DESCRIPTOR[2];
extern const uint8 CYCODE USBUART_5V_OPERATION_STRING_DESCRIPTORS[159u];


extern const uint8 CYCODE USBUART_5V_OPERATION_MSOS_DESCRIPTOR[USBUART_5V_OPERATION_MSOS_DESCRIPTOR_LENGTH];
extern const uint8 CYCODE USBUART_5V_OPERATION_MSOS_CONFIGURATION_DESCR[USBUART_5V_OPERATION_MSOS_CONF_DESCR_LENGTH];
#if defined(USBUART_5V_OPERATION_ENABLE_IDSN_STRING)
    extern uint8 USBUART_5V_OPERATION_idSerialNumberStringDescriptor[USBUART_5V_OPERATION_IDSN_DESCR_LENGTH];
#endif /* (USBUART_5V_OPERATION_ENABLE_IDSN_STRING) */

extern volatile uint8 USBUART_5V_OPERATION_interfaceNumber;
extern volatile uint8 USBUART_5V_OPERATION_interfaceSetting[USBUART_5V_OPERATION_MAX_INTERFACES_NUMBER];
extern volatile uint8 USBUART_5V_OPERATION_interfaceSettingLast[USBUART_5V_OPERATION_MAX_INTERFACES_NUMBER];
extern volatile uint8 USBUART_5V_OPERATION_deviceAddress;
extern volatile uint8 USBUART_5V_OPERATION_interfaceStatus[USBUART_5V_OPERATION_MAX_INTERFACES_NUMBER];
extern const uint8 CYCODE *USBUART_5V_OPERATION_interfaceClass;

extern volatile T_USBUART_5V_OPERATION_EP_CTL_BLOCK USBUART_5V_OPERATION_EP[USBUART_5V_OPERATION_MAX_EP];
extern volatile T_USBUART_5V_OPERATION_TD USBUART_5V_OPERATION_currentTD;

#if (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA)
    #if (CY_PSOC4)
        extern const uint8 USBUART_5V_OPERATION_DmaChan[USBUART_5V_OPERATION_MAX_EP];
    #else
        extern uint8 USBUART_5V_OPERATION_DmaChan[USBUART_5V_OPERATION_MAX_EP];
        extern uint8 USBUART_5V_OPERATION_DmaTd  [USBUART_5V_OPERATION_MAX_EP];
    #endif /* (CY_PSOC4) */
#endif /* (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA) */

#if (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)
#if (CY_PSOC4)
    extern uint8  USBUART_5V_OPERATION_DmaEpBurstCnt   [USBUART_5V_OPERATION_MAX_EP];
    extern uint8  USBUART_5V_OPERATION_DmaEpLastBurstEl[USBUART_5V_OPERATION_MAX_EP];

    extern uint8  USBUART_5V_OPERATION_DmaEpBurstCntBackup  [USBUART_5V_OPERATION_MAX_EP];
    extern uint32 USBUART_5V_OPERATION_DmaEpBufferAddrBackup[USBUART_5V_OPERATION_MAX_EP];
    
    extern const uint8 USBUART_5V_OPERATION_DmaReqOut     [USBUART_5V_OPERATION_MAX_EP];    
    extern const uint8 USBUART_5V_OPERATION_DmaBurstEndOut[USBUART_5V_OPERATION_MAX_EP];
#else
    #if (USBUART_5V_OPERATION_EP_DMA_AUTO_OPT == 0u)
        extern uint8 USBUART_5V_OPERATION_DmaNextTd[USBUART_5V_OPERATION_MAX_EP];
        extern volatile uint16 USBUART_5V_OPERATION_inLength [USBUART_5V_OPERATION_MAX_EP];
        extern volatile uint8  USBUART_5V_OPERATION_inBufFull[USBUART_5V_OPERATION_MAX_EP];
        extern const uint8 USBUART_5V_OPERATION_epX_TD_TERMOUT_EN[USBUART_5V_OPERATION_MAX_EP];
        extern const uint8 *USBUART_5V_OPERATION_inDataPointer[USBUART_5V_OPERATION_MAX_EP];
    #endif /* (USBUART_5V_OPERATION_EP_DMA_AUTO_OPT == 0u) */
#endif /* CY_PSOC4 */
#endif /* (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO) */

extern volatile uint8 USBUART_5V_OPERATION_ep0Toggle;
extern volatile uint8 USBUART_5V_OPERATION_lastPacketSize;
extern volatile uint8 USBUART_5V_OPERATION_ep0Mode;
extern volatile uint8 USBUART_5V_OPERATION_ep0Count;
extern volatile uint16 USBUART_5V_OPERATION_transferByteCount;


/***************************************
*     Private Function Prototypes
***************************************/
void  USBUART_5V_OPERATION_ReInitComponent(void)            ;
void  USBUART_5V_OPERATION_HandleSetup(void)                ;
void  USBUART_5V_OPERATION_HandleIN(void)                   ;
void  USBUART_5V_OPERATION_HandleOUT(void)                  ;
void  USBUART_5V_OPERATION_LoadEP0(void)                    ;
uint8 USBUART_5V_OPERATION_InitControlRead(void)            ;
uint8 USBUART_5V_OPERATION_InitControlWrite(void)           ;
void  USBUART_5V_OPERATION_ControlReadDataStage(void)       ;
void  USBUART_5V_OPERATION_ControlReadStatusStage(void)     ;
void  USBUART_5V_OPERATION_ControlReadPrematureStatus(void) ;
uint8 USBUART_5V_OPERATION_InitControlWrite(void)           ;
uint8 USBUART_5V_OPERATION_InitZeroLengthControlTransfer(void) ;
void  USBUART_5V_OPERATION_ControlWriteDataStage(void)      ;
void  USBUART_5V_OPERATION_ControlWriteStatusStage(void)    ;
void  USBUART_5V_OPERATION_ControlWritePrematureStatus(void);
uint8 USBUART_5V_OPERATION_InitNoDataControlTransfer(void)  ;
void  USBUART_5V_OPERATION_NoDataControlStatusStage(void)   ;
void  USBUART_5V_OPERATION_InitializeStatusBlock(void)      ;
void  USBUART_5V_OPERATION_UpdateStatusBlock(uint8 completionCode) ;
uint8 USBUART_5V_OPERATION_DispatchClassRqst(void)          ;

void USBUART_5V_OPERATION_Config(uint8 clearAltSetting) ;
void USBUART_5V_OPERATION_ConfigAltChanged(void)        ;
void USBUART_5V_OPERATION_ConfigReg(void)               ;
void USBUART_5V_OPERATION_EpStateInit(void)             ;


const T_USBUART_5V_OPERATION_LUT CYCODE *USBUART_5V_OPERATION_GetConfigTablePtr(uint8 confIndex);
const T_USBUART_5V_OPERATION_LUT CYCODE *USBUART_5V_OPERATION_GetDeviceTablePtr(void)           ;
#if (USBUART_5V_OPERATION_BOS_ENABLE)
    const T_USBUART_5V_OPERATION_LUT CYCODE *USBUART_5V_OPERATION_GetBOSPtr(void)               ;
#endif /* (USBUART_5V_OPERATION_BOS_ENABLE) */
const uint8 CYCODE *USBUART_5V_OPERATION_GetInterfaceClassTablePtr(void)                    ;
uint8 USBUART_5V_OPERATION_ClearEndpointHalt(void)                                          ;
uint8 USBUART_5V_OPERATION_SetEndpointHalt(void)                                            ;
uint8 USBUART_5V_OPERATION_ValidateAlternateSetting(void)                                   ;

void USBUART_5V_OPERATION_SaveConfig(void)      ;
void USBUART_5V_OPERATION_RestoreConfig(void)   ;

#if (CY_PSOC3 || CY_PSOC5LP)
    #if (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO && (USBUART_5V_OPERATION_EP_DMA_AUTO_OPT == 0u))
        void USBUART_5V_OPERATION_LoadNextInEP(uint8 epNumber, uint8 mode)  ;
    #endif /* (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO && (USBUART_5V_OPERATION_EP_DMA_AUTO_OPT == 0u)) */
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

#if defined(USBUART_5V_OPERATION_ENABLE_IDSN_STRING)
    void USBUART_5V_OPERATION_ReadDieID(uint8 descr[])  ;
#endif /* USBUART_5V_OPERATION_ENABLE_IDSN_STRING */

#if defined(USBUART_5V_OPERATION_ENABLE_HID_CLASS)
    uint8 USBUART_5V_OPERATION_DispatchHIDClassRqst(void) ;
#endif /* (USBUART_5V_OPERATION_ENABLE_HID_CLASS) */

#if defined(USBUART_5V_OPERATION_ENABLE_AUDIO_CLASS)
    uint8 USBUART_5V_OPERATION_DispatchAUDIOClassRqst(void) ;
#endif /* (USBUART_5V_OPERATION_ENABLE_AUDIO_CLASS) */

#if defined(USBUART_5V_OPERATION_ENABLE_CDC_CLASS)
    uint8 USBUART_5V_OPERATION_DispatchCDCClassRqst(void) ;
#endif /* (USBUART_5V_OPERATION_ENABLE_CDC_CLASS) */

#if (USBUART_5V_OPERATION_ENABLE_MSC_CLASS)
    #if (USBUART_5V_OPERATION_HANDLE_MSC_REQUESTS)
        uint8 USBUART_5V_OPERATION_DispatchMSCClassRqst(void) ;
    #endif /* (USBUART_5V_OPERATION_HANDLE_MSC_REQUESTS) */
#endif /* (USBUART_5V_OPERATION_ENABLE_MSC_CLASS */

CY_ISR_PROTO(USBUART_5V_OPERATION_EP_0_ISR);
CY_ISR_PROTO(USBUART_5V_OPERATION_BUS_RESET_ISR);

#if (USBUART_5V_OPERATION_SOF_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_5V_OPERATION_SOF_ISR);
#endif /* (USBUART_5V_OPERATION_SOF_ISR_ACTIVE) */

#if (USBUART_5V_OPERATION_EP1_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_5V_OPERATION_EP_1_ISR);
#endif /* (USBUART_5V_OPERATION_EP1_ISR_ACTIVE) */

#if (USBUART_5V_OPERATION_EP2_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_5V_OPERATION_EP_2_ISR);
#endif /* (USBUART_5V_OPERATION_EP2_ISR_ACTIVE) */

#if (USBUART_5V_OPERATION_EP3_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_5V_OPERATION_EP_3_ISR);
#endif /* (USBUART_5V_OPERATION_EP3_ISR_ACTIVE) */

#if (USBUART_5V_OPERATION_EP4_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_5V_OPERATION_EP_4_ISR);
#endif /* (USBUART_5V_OPERATION_EP4_ISR_ACTIVE) */

#if (USBUART_5V_OPERATION_EP5_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_5V_OPERATION_EP_5_ISR);
#endif /* (USBUART_5V_OPERATION_EP5_ISR_ACTIVE) */

#if (USBUART_5V_OPERATION_EP6_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_5V_OPERATION_EP_6_ISR);
#endif /* (USBUART_5V_OPERATION_EP6_ISR_ACTIVE) */

#if (USBUART_5V_OPERATION_EP7_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_5V_OPERATION_EP_7_ISR);
#endif /* (USBUART_5V_OPERATION_EP7_ISR_ACTIVE) */

#if (USBUART_5V_OPERATION_EP8_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_5V_OPERATION_EP_8_ISR);
#endif /* (USBUART_5V_OPERATION_EP8_ISR_ACTIVE) */

#if (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA)
    CY_ISR_PROTO(USBUART_5V_OPERATION_ARB_ISR);
#endif /* (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA) */

#if (USBUART_5V_OPERATION_DP_ISR_ACTIVE)
    CY_ISR_PROTO(USBUART_5V_OPERATION_DP_ISR);
#endif /* (USBUART_5V_OPERATION_DP_ISR_ACTIVE) */

#if (CY_PSOC4)
    CY_ISR_PROTO(USBUART_5V_OPERATION_INTR_HI_ISR);
    CY_ISR_PROTO(USBUART_5V_OPERATION_INTR_MED_ISR);
    CY_ISR_PROTO(USBUART_5V_OPERATION_INTR_LO_ISR);
    #if (USBUART_5V_OPERATION_LPM_ACTIVE)
        CY_ISR_PROTO(USBUART_5V_OPERATION_LPM_ISR);
    #endif /* (USBUART_5V_OPERATION_LPM_ACTIVE) */
#endif /* (CY_PSOC4) */

#if (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO)
#if (CY_PSOC4)
    #if (USBUART_5V_OPERATION_DMA1_ACTIVE)
        void USBUART_5V_OPERATION_EP1_DMA_DONE_ISR(void);
    #endif /* (USBUART_5V_OPERATION_DMA1_ACTIVE) */

    #if (USBUART_5V_OPERATION_DMA2_ACTIVE)
        void USBUART_5V_OPERATION_EP2_DMA_DONE_ISR(void);
    #endif /* (USBUART_5V_OPERATION_DMA2_ACTIVE) */

    #if (USBUART_5V_OPERATION_DMA3_ACTIVE)
        void USBUART_5V_OPERATION_EP3_DMA_DONE_ISR(void);
    #endif /* (USBUART_5V_OPERATION_DMA3_ACTIVE) */

    #if (USBUART_5V_OPERATION_DMA4_ACTIVE)
        void USBUART_5V_OPERATION_EP4_DMA_DONE_ISR(void);
    #endif /* (USBUART_5V_OPERATION_DMA4_ACTIVE) */

    #if (USBUART_5V_OPERATION_DMA5_ACTIVE)
        void USBUART_5V_OPERATION_EP5_DMA_DONE_ISR(void);
    #endif /* (USBUART_5V_OPERATION_DMA5_ACTIVE) */

    #if (USBUART_5V_OPERATION_DMA6_ACTIVE)
        void USBUART_5V_OPERATION_EP6_DMA_DONE_ISR(void);
    #endif /* (USBUART_5V_OPERATION_DMA6_ACTIVE) */

    #if (USBUART_5V_OPERATION_DMA7_ACTIVE)
        void USBUART_5V_OPERATION_EP7_DMA_DONE_ISR(void);
    #endif /* (USBUART_5V_OPERATION_DMA7_ACTIVE) */

    #if (USBUART_5V_OPERATION_DMA8_ACTIVE)
        void USBUART_5V_OPERATION_EP8_DMA_DONE_ISR(void);
    #endif /* (USBUART_5V_OPERATION_DMA8_ACTIVE) */

#else
    #if (USBUART_5V_OPERATION_EP_DMA_AUTO_OPT == 0u)
        CY_ISR_PROTO(USBUART_5V_OPERATION_EP_DMA_DONE_ISR);
    #endif /* (USBUART_5V_OPERATION_EP_DMA_AUTO_OPT == 0u) */
#endif /* (CY_PSOC4) */
#endif /* (USBUART_5V_OPERATION_EP_MANAGEMENT_DMA_AUTO) */


/***************************************
*         Request Handlers
***************************************/

uint8 USBUART_5V_OPERATION_HandleStandardRqst(void) ;
uint8 USBUART_5V_OPERATION_DispatchClassRqst(void)  ;
uint8 USBUART_5V_OPERATION_HandleVendorRqst(void)   ;


/***************************************
*    HID Internal references
***************************************/

#if defined(USBUART_5V_OPERATION_ENABLE_HID_CLASS)
    void USBUART_5V_OPERATION_FindReport(void)            ;
    void USBUART_5V_OPERATION_FindReportDescriptor(void)  ;
    void USBUART_5V_OPERATION_FindHidClassDecriptor(void) ;
#endif /* USBUART_5V_OPERATION_ENABLE_HID_CLASS */


/***************************************
*    MIDI Internal references
***************************************/

#if defined(USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING)
    void USBUART_5V_OPERATION_MIDI_IN_EP_Service(void)  ;
#endif /* (USBUART_5V_OPERATION_ENABLE_MIDI_STREAMING) */


/***************************************
*    CDC Internal references
***************************************/

#if defined(USBUART_5V_OPERATION_ENABLE_CDC_CLASS)

    typedef struct
    {
        uint8  bRequestType;
        uint8  bNotification;
        uint8  wValue;
        uint8  wValueMSB;
        uint8  wIndex;
        uint8  wIndexMSB;
        uint8  wLength;
        uint8  wLengthMSB;
        uint8  wSerialState;
        uint8  wSerialStateMSB;
    } t_USBUART_5V_OPERATION_cdc_notification;

    uint8 USBUART_5V_OPERATION_GetInterfaceComPort(uint8 interface) ;
    uint8 USBUART_5V_OPERATION_Cdc_EpInit( const T_USBUART_5V_OPERATION_EP_SETTINGS_BLOCK CYCODE *pEP, uint8 epNum, uint8 cdcComNums) ;

    extern volatile uint8  USBUART_5V_OPERATION_cdc_dataInEpList[USBUART_5V_OPERATION_MAX_MULTI_COM_NUM];
    extern volatile uint8  USBUART_5V_OPERATION_cdc_dataOutEpList[USBUART_5V_OPERATION_MAX_MULTI_COM_NUM];
    extern volatile uint8  USBUART_5V_OPERATION_cdc_commInEpList[USBUART_5V_OPERATION_MAX_MULTI_COM_NUM];
#endif /* (USBUART_5V_OPERATION_ENABLE_CDC_CLASS) */


#endif /* CY_USBFS_USBUART_5V_OPERATION_pvt_H */


/* [] END OF FILE */
