#include "alarm.h"
#include "project.h"
#include "systick.h"

static uint8_t armed = 0;
static uint8_t triggered = 0;
static uint32_t blink_last_toggle = 0;
static uint8_t blink_led_state = 0;

void Alarm_Arm(void)
{
    armed = 1;
    triggered = 0;
}

void Alarm_Trigger(void)
{
    if (armed)
    {
        triggered = 1;
        blink_last_toggle = tick_ms;
        blink_led_state = 0;
    }
}

void Alarm_Stop(void)
{
    armed = 0;
    triggered = 0;
    alarm_LED_Write(0);
    Red_LED_Write(0);
    blink_led_state = 0;
}

uint8_t Alarm_IsArmed(void)
{
    return armed;
}

uint8_t Alarm_IsTriggered(void)
{
    return triggered;
}

void Alarm_Run(void)
{
    if (!triggered)
        return;

    uint32_t elapsed = tick_ms - blink_last_toggle;

    if (elapsed >= 200)
    {
        blink_led_state = !blink_led_state;
        alarm_LED_Write(blink_led_state);
        blink_last_toggle = tick_ms;
    }
}

