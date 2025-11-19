#include "../Inc/it_handlers.h"
#include <stm32f4xx.h>

extern uint8_t Mode;
uint32_t holdTime = 0;
uint8_t btn2State = 0; 
extern uint8_t BtnFi;
extern uint32_t LiTi;
extern uint8_t BtnTwSh;
uint32_t button2PressTime = 0;
uint32_t ExternalInterruptTickCount = 0;
uint8_t button2_long_press_triggered = 0;

void EXTI0_IRQHandler(void)
{
    SET_BIT(EXTI->PR, EXTI_PR_PR0); 
    if (ExternalInterruptTickCount >= DELAY_BUTTON_FILTER)
    {
        BtnFi++;
        ExternalInterruptTickCount = 0;
    }
}

void EXTI3_IRQHandler(void)
{
    if (READ_BIT(EXTI->PR, EXTI_PR_PR3)) 
    {
        SET_BIT(EXTI->PR, EXTI_PR_PR3); 
        
        if (ExternalInterruptTickCount >= DELAY_BUTTON_FILTER)
        {
            if (btn2State == 0)
            {
                button2PressTime = ExternalInterruptTickCount;
                btn2State = 1;
                button2_long_press_triggered = 0; 
            }
            else
            {
                holdTime = ExternalInterruptTickCount - button2PressTime;
                
                if (holdTime > 100 && holdTime <= 2000 && !button2_long_press_triggered)
                {
                    BtnTwSh = 1;
                }
                
                btn2State = 0;
                ExternalInterruptTickCount = 0;
            }
        }
    }
}

void SysTick_Handler(void)
{
    ExternalInterruptTickCount++;
    LiTi++; 
    if (btn2State == 1 && !button2_long_press_triggered)
    {
        holdTime = ExternalInterruptTickCount - button2PressTime;
        if (holdTime > 2000) 
        {
            Mode = !Mode;
            LiTi = 0; 
            button2_long_press_triggered = 1; 
        }
    }
}