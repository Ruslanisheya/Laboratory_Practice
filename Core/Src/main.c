#include "../Inc/init.h"
#include "../Src/init.c"
#include <stdint.h>

uint8_t flag = 0;


void INIT (void)
{
    GPIO_InitLEDPB0 ();
    GPIO_InitBtnPC12();
}

int main(void)
{
    INIT();
    while(1)
    {
        if (BIT_READ(GPIOC_IDR, GPIO_PIN_12))
        {
            if (flag == 0)
            {
                flag = 1;    
            }
            else
            {
                flag = 0;
            }
            for(volatile uint32_t i = 0; i < 250000; i++){}
        }
        if (flag == 1)
        {
            SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS0);
        }
        else
        {
            SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR0);
        }
    }
    
}