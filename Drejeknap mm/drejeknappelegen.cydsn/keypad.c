#include "project.h"
#include "keypad.h"
#include "rotary.h"
static uint8_t digit = 0;
static uint32_t code = 0;
static uint8_t count = 0;
CY_ISR(isr_Button)
{
    if(count < 4)
    { code = code * 10 + digit; count++; }
}


static void ShowDigit(uint8 d)
{
    for (uint8 i = 0; i < d; i++)
    {
        Green_LED_Write(1);
        CyDelay(120);
        Green_LED_Write(0);
        CyDelay(120);
    }
    CyDelay(500);
}


void Keypad_Init(void)
{
    Rotary_Init();
    isr_Button_StartEx(isr_Button);
}

void Keypad_Update(void)
{
    int8 rot = Rotary_GetDelta();
    if (rot != 0)
    {
        digit = (digit + rot + 10) % 10;
        ShowDigit(digit);   // ✅ LED viser aktuelt ciffer
    }

}

uint8_t Keypad_IsComplete(void){ return count == 4; }
uint32_t Keypad_GetCode(void){ return code; }
void Keypad_Reset(void){ code = 0; count = 0; digit = 0; }
