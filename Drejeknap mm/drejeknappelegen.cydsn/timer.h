#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>

#define INPUT_TIMEOUT_MS 5000u

extern volatile uint32_t tick_ms;

void Input_Timeout_Activate(void);
void Input_Timeout_Deactivate(void);
void Input_Timeout_Reset(void);
uint8_t Input_Timeout_HasExpired(void);

#endif