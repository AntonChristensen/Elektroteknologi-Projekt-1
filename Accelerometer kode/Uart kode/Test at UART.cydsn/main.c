// brug software real term
#include "project.h"
#include <string.h>

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    uint32 signal;
    char TransmitBuffer[64u];
    
//USBUART_Start(0, USBUART_5V_OPERATION); // see datasheet
UART_1_Start(0, UART_1_5V_OPERATION); // see datasheet
while(0u == USBUART_GetConfiguration()){}  // see datasheet:

CyDelay(5);
    
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

for(;;)
{
    signal += 1;
       
    sprintf(TransmitBuffer, "%ld\r\n", signal);
        
    CyDelay(100); 

    USBUART_PutString(TransmitBuffer);
    
    CyDelay(400); 
    
}
}