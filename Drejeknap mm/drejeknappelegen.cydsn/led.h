#ifndef LED_H
#define LED_H
#include <stdint.h>

void LED_Init(void);
void LED_Update(void);

void LED_KeypadShowDigit(uint8_t digit);
void LED_ServoOpen(void);
void LED_ServoClose(void);
void LED_TimeoutBlink(void);

#endif
