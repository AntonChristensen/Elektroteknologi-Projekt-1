#include "project.h"
#include "servo.h"
#include "led.h"
#include "systick.h"

#define SERVO_OPEN_PWM 20
#define SERVO_CLOSE_PWM 10
#define SERVO_OPEN_POS 2000
#define SERVO_CLOSE_POS 1200
#define SERVO_ACCEPTED_DELAY 500
#define TOL 100

static uint8_t servo_desired_open = 0;
static uint8_t servo_is_open = 0;

void Servo_Init(void)
{
    PWM_Servo_Start();
    ADC_ServoFB_Start();
}

uint16_t Servo_GetPosition(void)
{
    return ADC_ServoFB_CountsTo_mVolts(ADC_ServoFB_GetResult16());
}

void Servo_Open(void)
{
    PWM_Servo_WriteCompare(SERVO_OPEN_PWM);
    servo_desired_open = 1
    uint32_t movement_start = tick_ms
    LED_ServoOpen();
}

 void Servo_Close(void)
{
    PWM_Servo_WriteCompare(SERVO_CLOSE_PWM);
    servo_desired_open = 0
    uint32_t movement_start = tick_ms
    LED_ServoClose();
}

uint8_t Servo_IsOpen(void)
{
    return servo_is_open;
}

servo_status_t Servo_Update(void)
{
    if (servo_open == servo_desired_open)
    {
        return SERVO_OK;
    }
    if (servo_desired_open & (Servo_GetPosition(0) > SERVO_OPEN_POS))
    {
        servo_open = 1;
        return SERVO_OK;
    }
    if (!servo_desired_open & (Servo_GetPosition(0) < SERVO_CLOSE_POS))
    {
        servo_open = 0;
        return SERVO_OK;
    }
    uint32_t elapsed = tick_ms - movement_start
    if (elapsed > SERVO_ACCEPTED_DELAY )
    {
        return SERVO_ERROR;
    }
}
