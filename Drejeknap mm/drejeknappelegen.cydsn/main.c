#include <stdio.h>
#include "project.h"
#include "keypad.h"
#include "lock.h"
#include "alarm.h"
#include "accel.h"
#include "servo.h"
#include "timer.h"
#include "systick.h"
#include "led.h"
int main(void)
{
    SysTick_Init();
    Servo_Init();
    Alarm_Stop();
    Accel_Init();
    Keypad_Init();
    CyGlobalIntEnable;

    for (;;)
    {
        Alarm_Run();
        LED_Update();

        if (Keypad_isActive())
        {
            Keypad_Update();
            if (Keypad_IsComplete())
            {
                Lock_Handle(Keypad_GetCode());
            }
        }

        if (Input_Timeout_HasExpired())
        {
            Keypad_Reset();
            Input_Timeout_Deactivate();
            Red_LED_Write(1);
            Green_LED_Write(1);
            CyDelay(400);
            Red_LED_Write(0);
            Green_LED_Write(0);
        }
        
        if ((Servo_Update == SERVO_ERROR) && Alarm_IsArmed() && !Alarm_IsTriggered())
        {
            Alarm_Trigger();
        }

        if (Alarm_IsArmed() && !Alarm_IsTriggered() && Accel_MovementDetected())
        {
            Alarm_Trigger();
        }
    }
}