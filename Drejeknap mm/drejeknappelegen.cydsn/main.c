#include "project.h"
#include "keypad.h"
#include "lock.h"
#include "alarm.h"
#include "accel.h"
#include "servo.h"
int main(void)
{
    CyGlobalIntEnable;
    Servo_Init();
    Alarm_Run();
    Alarm_Stop();
    Accel_Init();
    Keypad_Init();
    for(;;)
    {
        Keypad_Update();
        if(Keypad_IsComplete())
        {
            Lock_Handle(Keypad_GetCode());
            Keypad_Reset();
        }
        if(Alarm_IsActive() && Accel_MovementDetected())
        {
            Alarm_Trigger();
        }
    }
}
