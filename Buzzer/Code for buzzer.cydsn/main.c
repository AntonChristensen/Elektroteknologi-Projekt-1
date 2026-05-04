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



//Clock_1_Start();
//Clock_2_Start();
//Clock_3_Start();

//AlarmSekvens_Start();


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    PWM_Start();
    PWM_WriteCompare(127);
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        Alarm_Write(0x01);

        CyDelay(1000);
        Alarm_Write(0x00);

        CyDelay(1000);
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
