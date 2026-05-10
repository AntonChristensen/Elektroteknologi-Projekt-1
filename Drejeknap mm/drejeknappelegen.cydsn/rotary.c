#include "project.h"
#include "rotary.h"
#include "timer.h"
#include "keypad.h"

static volatile int8_t delta = 0;

CY_ISR(isr_Rot)
{
    if (Keypad_isActive() == 0)
    {
        Keypad_Activate();
    }
    else if (Status_Rot_B_Read() & 0x01)
    {
        delta++;
    }
    else
    {
        delta--;
    }
    Input_Timeout_Reset();
}

void Rotary_Init(void)
{
    isr_Rot_StartEx(isr_Rot);
}

int8_t Rotary_GetDelta(void)
{
    int8_t d = delta;
    delta = 0;
    return d;
}