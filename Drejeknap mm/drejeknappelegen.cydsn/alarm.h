#ifndef ALARM_H
#define ALARM_H

#include <stdint.h>

void Alarm_Arm(void);
void Alarm_Trigger(void);
void Alarm_Stop(void);
uint8_t Alarm_IsArmed(void);
uint8_t Alarm_IsTriggered(void);
void Alarm_Run(void);

#endif
