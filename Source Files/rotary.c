#include "project.h"
#include "rotary.h"
static volatile int8_t delta = 0;
CY_ISR(isr_Rot)
{
    if(Status_Rot_B_Read() & 0x01) delta++; else delta--;
}
void Rotary_Init(void)
{
    isr_Rot_StartEx(isr_Rot);
}
int8_t Rotary_GetDelta(void)
{
    int8_t d = delta; delta = 0; return d;
}
