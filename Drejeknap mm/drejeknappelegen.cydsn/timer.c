#include "systick.h"
#include "timer.h"

static uint8_t timeout_active = 0;
static uint32_t timeout_deadline = 0;

void Input_Timeout_Activate(void)
{
    timeout_active = 1;
    timeout_deadline = tick_ms + INPUT_TIMEOUT_MS;
}

void Input_Timeout_Deactivate(void)
{
    timeout_active = 0;
}

void Input_Timeout_Reset(void)
{
    if (timeout_active)
    {
        timeout_deadline = tick_ms + INPUT_TIMEOUT_MS;
    }
}

uint8_t Input_Timeout_HasExpired(void)
{
    return timeout_active && 
        ((int32_t)(tick_ms - timeout_deadline) >= 0);
}