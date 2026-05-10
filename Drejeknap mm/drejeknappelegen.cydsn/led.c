#include "led.h"
#include "project.h"
#include "systick.h"

enum LEDOperation {
    LED_IDLE = 0,
    LED_KEYPAD_BLINK = 1,
    LED_SERVO_GREEN = 2,
    LED_SERVO_RED = 3,
    LED_TIMEOUT_BLINK = 4
};

static uint8_t current_op = LED_IDLE;
static uint32_t op_start_time = 0;
static uint8_t keypad_target_blinks = 0;
static uint8_t keypad_blink_count = 0;
static uint8_t led_state = 0;

void LED_Init(void)
{
    current_op = LED_IDLE;
    led_state = 0;
    Green_LED_Write(0);
    Red_LED_Write(0);
}

void LED_KeypadShowDigit(uint8_t digit)
{
    //if (digit == 0){digit = 10;}
    current_op = LED_KEYPAD_BLINK;
    keypad_target_blinks = digit;
    keypad_blink_count = 0;
    op_start_time = tick_ms;
    led_state = 0;
    Green_LED_Write(0);
}

void LED_ServoOpen(void)
{
    current_op = LED_SERVO_GREEN;
    op_start_time = tick_ms;
    led_state = 0;
    Green_LED_Write(1);
}

void LED_ServoClose(void)
{
    current_op = LED_SERVO_RED;
    op_start_time = tick_ms;
    led_state = 0;
    Red_LED_Write(1);
}

void LED_TimeoutBlink(void)
{
    current_op = LED_TIMEOUT_BLINK;
    op_start_time = tick_ms;
    led_state = 0;
    Red_LED_Write(1);
    Green_LED_Write(1);
}

static void UpdateKeypadBlink(void)
{
    uint32_t elapsed = tick_ms - op_start_time;
    uint32_t blink_phase_elapsed;
    uint32_t phase;

    if (keypad_blink_count >= keypad_target_blinks)
    {
        if (elapsed >= (keypad_target_blinks * 240 + 600))
        {
            current_op = LED_IDLE;
            Green_LED_Write(0);
            led_state = 0;
        }
        return;
    }

    blink_phase_elapsed = elapsed - (keypad_blink_count * 240);
    phase = blink_phase_elapsed / 120;

    if (phase == 0)
    {
        if (!led_state)
        {
            Green_LED_Write(1);
            led_state = 1;
        }
    }
    else if (phase >= 1)
    {
        if (led_state)
        {
            Green_LED_Write(0);
            led_state = 0;
            keypad_blink_count++;
        }
    }
}

static void UpdateServoGreen(void)
{
    uint32_t elapsed = tick_ms - op_start_time;

    if (elapsed < 500)
    {
        if (!led_state)
        {
            Green_LED_Write(1);
            led_state = 1;
        }
    }
    else
    {
        Green_LED_Write(0);
        current_op = LED_IDLE;
        led_state = 0;
    }
}

static void UpdateServoRed(void)
{
    uint32_t elapsed = tick_ms - op_start_time;

    if (elapsed < 500)
    {
        if (!led_state)
        {
            Red_LED_Write(1);
            led_state = 1;
        }
    }
    else if (elapsed < 1000)
    {
        if (led_state)
        {
            Red_LED_Write(0);
            led_state = 0;
        }
    }
    else
    {
        Red_LED_Write(0);
        current_op = LED_IDLE;
        led_state = 0;
    }
}

static void UpdateTimeoutBlink(void)
{
    uint32_t elapsed = tick_ms - op_start_time;

    if (elapsed < 400)
    {
        if (!led_state)
        {
            Red_LED_Write(1);
            Green_LED_Write(1);
            led_state = 1;
        }
    }
    else
    {
        Red_LED_Write(0);
        Green_LED_Write(0);
        current_op = LED_IDLE;
        led_state = 0;
    }
}

void LED_Update(void)
{
    switch (current_op)
    {
        case LED_KEYPAD_BLINK:
            UpdateKeypadBlink();
            break;
        case LED_SERVO_GREEN:
            UpdateServoGreen();
            break;
        case LED_SERVO_RED:
            UpdateServoRed();
            break;
        case LED_TIMEOUT_BLINK:
            UpdateTimeoutBlink();
            break;
        case LED_IDLE:
        default:
            break;
    }
}

