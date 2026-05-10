#include "project.h"
#include "lock.h"
#include "servo.h"
#include "alarm.h"
#include "timer.h"
#include "keypad.h"
#define PASSWORD 1010
static uint8_t attempts = 0;
void Lock_Handle(uint32_t code)
{
    if(code == PASSWORD)
    {
        Servo_Open();
        attempts = 0;
        Input_Timeout_Deactivate();
        Keypad_Reset();
    }
    else
    {
        Red_LED_Write(1);
        CyDelay(500);
        Red_LED_Write(0);
        Keypad_Reset();
        attempts++;
        if(attempts >= 5)
        {
            Alarm_Arm();
            Alarm_Trigger();
        }
    }
}
