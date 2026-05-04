#ifndef ALARM_H
#define ALARM_H

#include <stdint.h>

void Alarm_Trigger(void);
void Alarm_Stop(void);
uint8_t Alarm_IsActive(void);
void Alarm_Run(void);

#endif
