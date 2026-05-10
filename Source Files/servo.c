#include "project.h"
#include "servo.h"
#define SERVO_OPEN_PWM 2000
#define SERVO_CLOSE_PWM 1000
#define SERVO_OPEN_POS 3500
#define SERVO_CLOSE_POS 1500
#define TOL 100

void Servo_Init(void)
{
    PWM_Servo_Start();
}

servo_status_t Servo_Open(void)
{
    PWM_Servo_WriteCompare(SERVO_OPEN_PWM);
    CyDelay(500);
    return SERVO_OK;
}

servo_status_t Servo_Close(void)
{
    PWM_Servo_WriteCompare(SERVO_CLOSE_PWM);
    CyDelay(500);
    return SERVO_OK;
}
