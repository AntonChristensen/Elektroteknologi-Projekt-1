#ifndef SERVO_H
#define SERVO_H
#include <stdint.h>
typedef enum { SERVO_OK, SERVO_ERROR } servo_status_t;
void Servo_Init(void);
servo_status_t Servo_Open(void);
servo_status_t Servo_Close(void);
uint16_t Servo_GetPosition(void);
#endif
