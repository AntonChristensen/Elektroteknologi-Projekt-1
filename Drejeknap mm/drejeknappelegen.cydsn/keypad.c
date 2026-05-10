#include "project.h"
#include "keypad.h"
#include "rotary.h"
#include "timer.h"
#include "servo.h"
#include "alarm.h"
#include "led.h"

static uint8_t keypad_active = 0;
static uint8_t digit = 0;
static uint32_t code = 0;
static uint8_t count = 0;

CY_ISR(isr_Button)
{
    if (Servo_IsOpen())
    {
        Servo_Close();
        Alarm_Arm();
        Alarm_Trigger();
        Keypad_Reset();
    }
    else if (keypad_active == 0)
    {
        Keypad_Activate();
    }
    else if (count < 4)
    {
        code = code * 10 + digit;
        count++;
        digit = 0;
    }
    Input_Timeout_Reset();
}

//static void ShowDigit(uint8 d)
//{
//    uint8 i;
//    for (i = 0; i < d; i++)
//    {
//        Green_LED_Write(1);
//        CyDelay(120);
//        Green_LED_Write(0);
//        CyDelay(120);
//    }
//    CyDelay(600);
//}

void Keypad_Init(void)
{
    Rotary_Init();
    isr_Button_StartEx(isr_Button);
}

void Keypad_Activate(void)
{
    keypad_active = 1;
    digit = 0;
    code = 0;
    count = 0;
    Input_Timeout_Activate();  // Start timeout
}

void Keypad_Update(void)
{
    int8_t rot = Rotary_GetDelta();
    if (rot != 0)
    {
        digit = (digit + rot + 10) % 10;
        LED_KeypadShowDigit(digit);
        Input_Timeout_Reset();  // Reset on rotary change
    }
}

uint8_t Keypad_IsComplete(void)
{
    return count == 4;
}

uint32_t Keypad_GetCode(void)
{
    return code;
}

uint8_t Keypad_isActive(void)
{
    return keypad_active;
}

void Keypad_Reset(void)
{
    keypad_active = 0;
    digit = 0;
    code = 0;
    count = 0;
    Input_Timeout_Deactivate();  // Stop timeout
}