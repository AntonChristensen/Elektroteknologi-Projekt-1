/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>

#define BNO_ADDR 0x4A
#define PACKET_MAX 128

uint8 buffer[PACKET_MAX];

int main(void)
{
    CyGlobalIntEnable;

    I2C_1_Start();
    
    USBUART_Start(0, USBUART_5V_OPERATION); // see datasheet
    while(0u == USBUART_GetConfiguration()){}  // see datasheet:
    
    CyDelay(100);
    
    for(;;)
    {
        uint8 header[4];
        
        if(I2C_1_MasterReadBuf(BNO_ADDR, header, 4, I2C_1_MODE_COMPLETE_XFER) == I2C_1_MSTR_NO_ERROR)
        {
            while((I2C_1_MasterStatus() & I2C_1_MSTAT_RD_CMPLT) == 0);

            uint16 length = header[0] | (header[1] << 8);
            length &= 0x7FFF; // fjern continuation bit

            uint8 channel = header[2];
            uint8 seq = header[3];

            if(length > PACKET_MAX) continue;

            uint16 payload_len = length - 4;

            // læs payload
            if(payload_len > 0)
            {
                if(I2C_1_MasterReadBuf(BNO_ADDR, buffer, payload_len, I2C_1_MODE_COMPLETE_XFER) == I2C_1_MSTR_NO_ERROR)
                {
                    while((I2C_1_MasterStatus() & I2C_1_MSTAT_RD_CMPLT) == 0);
                }
            }
        }
        else
        {
            CyDelay(100);
            USBUART_PutString("Ingenting\r\n");
            
        }
    
        
    }
}