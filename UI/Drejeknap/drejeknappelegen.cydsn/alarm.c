#include "alarm.h"
#include "project.h"
static uint8_t active = 0;
void Alarm_Trigger(void)
{
    active = 1;
}
void Alarm_Stop(void)
{
    active = 0;
    Red_LED_Write(0);
}
uint8_t Alarm_IsActive(void)
{
    return active;
}


void Alarm_Run(void)
{
    if (active)
    {
        Red_LED_Write(1);
        CyDelay(200);
        Red_LED_Write(0);
        CyDelay(200);
    }
}
