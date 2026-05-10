#ifndef SERVO_H
#define SERVO_H
#include <stdint.h>
typedef enum
{
    SERVO_OK,
    SERVO_ERROR
} servo_status_t;
void Servo_Init(void);
void Servo_Open(void);
void Servo_Close(void);
uint8_t Servo_IsOpen(void);
uint16_t Servo_GetPosition(void);
#endif
