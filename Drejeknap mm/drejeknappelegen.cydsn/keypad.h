#ifndef KEYPAD_H
#define KEYPAD_H
#include <stdint.h>
void Keypad_Init(void);
void Keypad_Activate(void);
void Keypad_Update(void);
uint8_t Keypad_IsComplete(void);
uint32_t Keypad_GetCode(void);
uint8_t Keypad_isActive(void);
void Keypad_Reset(void);
#endif
