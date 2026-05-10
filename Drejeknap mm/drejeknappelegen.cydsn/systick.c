#include "project.h"
#include "systick.h"
volatile uint32_t tick_ms = 0;

CY_ISR(systick_isr)
{
    SysTickTimer_ReadStatusRegister();
    tick_ms++;
}

void SysTick_Init(void)
{
    SysTickTimer_Start();
    systick_isr_StartEx(systick_isr);
}