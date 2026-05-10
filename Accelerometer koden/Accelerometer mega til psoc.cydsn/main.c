#include "project.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 7

uint8 i2cBuffer[BUFFER_SIZE];

int16 accelX_raw, accelY_raw, accelZ_raw;
int16 accelX, accelY, accelZ;

char usbBuffer[64];

int main(void)
{
    CyGlobalIntEnable;

    // Start I2C (slave)
    I2C_Start();
    I2C_SlaveInitWriteBuf(i2cBuffer, BUFFER_SIZE);
    I2C_SlaveSetAddress(8);

    // Start USB (CDC)
    USBUART_Start(0, USBUART_5V_OPERATION);
    while (0u == USBUART_GetConfiguration())
    {
        // Wait for configuration
    }

    CyDelay(5);
    
    //Reset NANO så de synkroniseres
    Reset_NANO_Write(0u);
    CyDelay(10);
    Reset_NANO_Write(1u);
    CyDelay(500);
    
    
    for (;;)
    {
        CyDelay(100);

        // Check if I2C write is complete
        if (I2C_SlaveStatus() & I2C_SSTAT_WR_CMPLT)
        {
            uint8 count = I2C_SlaveGetWriteBufSize();

            // Optional debug
            // sprintf(usbBuffer, "count: %d\r\n", count);
            // USBUART_PutString(usbBuffer);

            if (count == 7 && i2cBuffer[0] == 0xAA)
            {
                accelX_raw = (int16_t)((uint16_t)i2cBuffer[1] |
                                       ((uint16_t)i2cBuffer[2] << 8));

                accelY_raw = (int16_t)((uint16_t)i2cBuffer[3] |
                                       ((uint16_t)i2cBuffer[4] << 8));

                accelZ_raw = (int16_t)((uint16_t)i2cBuffer[5] |
                                       ((uint16_t)i2cBuffer[6] << 8));

                accelX = accelX_raw / 100;
                accelY = accelY_raw / 100;
                accelZ = accelZ_raw / 100;

                // Format text
                sprintf(usbBuffer, "X: %d Y: %d Z: %d\r\n", accelX_raw, accelY_raw, accelZ_raw);

                // Send via USB CDC
                USBUART_PutString(usbBuffer);
            }

            // Reset buffer
            I2C_SlaveClearWriteStatus();
            I2C_SlaveInitWriteBuf(i2cBuffer, BUFFER_SIZE);
        }        
    }
}