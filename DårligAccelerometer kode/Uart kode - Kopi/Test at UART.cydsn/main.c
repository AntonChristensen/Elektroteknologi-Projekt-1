// brug software real term
#include "project.h"
#include <string.h>

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
  
    const char8 occ[] = "Hej";
    
    USBUART_Start(0, USBUART_5V_OPERATION); // see datasheet
    UART_Start(); // see datasheet

    while(0u == USBUART_GetConfiguration()){}
    CyDelay(5);
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

for(;;)
{
    CyDelay(1); 
    

    UART_PutString(occ);
    
    if(UART_ReadTxStatus() & UART_TX_STS_COMPLETE) {
        if(USBUART_CDCIsReady()){
            USBUART_PutString("Send\r\n");
        }
    } else {
        if(USBUART_CDCIsReady()){
            USBUART_PutString("Not Send\r\n");
        }
}
    
}
}