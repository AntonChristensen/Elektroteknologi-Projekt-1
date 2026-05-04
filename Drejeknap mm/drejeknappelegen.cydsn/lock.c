#include "lock.h"
#include "servo.h"
#include "alarm.h"
#define PASSWORD 1234
void Lock_Handle(uint32_t code)
{
    if(code == PASSWORD)
    {
        if(Servo_Open()==SERVO_OK) Alarm_Stop(); else Alarm_Trigger();
    }
    else Alarm_Trigger();
}
