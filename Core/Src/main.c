#include "../Inc/init.h"
#include "../Src/init.c"
#include <stdint.h>

uint8_t f1 = 0;
uint8_t f2 = 0;
uint8_t f3 = 0;
uint8_t f4 = 0;
uint8_t CurLEDi = 0;
uint8_t CoOLED = 0;
uint8_t Mode = 0;
uint32_t Freq = 0;
uint32_t Timer = 0;

// первая кнопка: меняет светодиод; если горят все три, то выкл/вкл светодиоды.
// вторая кнопка: короткое нажатие - смена количества горящих светодиодов; длительное нажатие - смена режима работы (постоянное свечение; 0,5Гц; 1Гц; 2Гц; 5Гц).

void ResetLED(void)
    {
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR0 |GPIO_BSRR_BR7 | GPIO_BSRR_BR14 );
        if (f3 == 0)
            {
                for (uint8_t i = 0; i <=CoOLED; i++) 
                {
                    uint8_t led_index = ((CurLEDi + i) % 3);
                    switch (led_index) 
                    {
                    case 0:
                        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS0);
                        break;
                    case 1:
                        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS7);
                        break;
                    case 2:
                        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS14);
                        break;

                
                    }
                }
            }
    }
//#################################################################################################
//#################################################################################################
    void Blink182(void)
    {
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR0 |GPIO_BSRR_BR7 | GPIO_BSRR_BR14 );
        if (f4 == 0)
        {
            ResetLED();
            f4 = 1;
        }
        else
        {
            f4 = 0;
        }
    }
//#################################################################################################
//#################################################################################################
int main(void)
{
    GPIO_init_led_pb7_blue ();
    GPIO_init_led_pb14_red ();
    GPIO_init_led_pb0_green ();
    GPIO_button_input();
     
    while (1)
    {
//#################################################################################################
        if (BIT_READ(GPIOC_IDR, GPIO_PIN_12))
        {
            if (CoOLED == 2)
            {
                if (f3 == 0)
                {
                    f3 = 1;
                    f1 = 1;
                }
                else
                {
                    f3 = 0;
                    f1 = 0;
                }
            }
            else
            {
                CurLEDi = ((CurLEDi + 1) % 3);
            }
            ResetLED();
            for(volatile uint32_t i = 0; i < 250000; i++){}
        }
//#################################################################################################
        if (BIT_READ(GPIOC_IDR, GPIO_PIN_13))
        {
            if (f1 == 0)
            {
                CoOLED = ((CoOLED + 1) % 3);
            }
            ResetLED();
            Timer = 0;
            for(volatile uint32_t i = 0; i < 250000; i++){}
        }


        if (Freq != 0)
        {
            Blink182();
            for(volatile uint32_t i = 0; i < Freq; i++){}
        }
    }
}



// if (BIT_READ(GPIOC_IDR, GPIO_PIN_8))  
// {
//             timerbutton1++;
//             flag1 = 1;
//        }
//        else
//        {
//         if(timerbutton1>= 5)
//         {
//             if (led_count == 3)
//             {

//                UpdateLEDs(); 
//             }
//             else
//             {
//             led_count = ((led_count+1));
//             UpdateLEDs();
//             }
//         }
//         if(timerbutton1>= 1 && timerbutton1 < 5)
//         {
//             if(frequency_index<3){
//             frequency_index = (frequency_index+1);
//             avtodelay = frequencies[frequency_index];
//             }
//         }
        
//         timerbutton1 = 0;
//         flag1 = 0;
//        }
//        if (BIT_READ(GPIOC_IDR, GPIO_PIN_8))
//        {
//         timerbutton2++;
//         flag2 = 1;
//        }
//        else
//        {
//         if(timerbutton2>= 5)
//         {
//             if (led_count == 0)
//             {
//                UpdateLEDs(); 
//             }
//             else
//             {
//            led_count = ((led_count-1));
//             UpdateLEDs();
//             }
            
//         }
//         if(timerbutton2>= 1 && timerbutton2 < 5)
//         {
//             if(frequency_index>0){
//             frequency_index = (frequency_index-1);
//             avtodelay = frequencies[frequency_index];
//             }
//         }
//         timerbutton2 = 0;
//         flag2 = 0;
//        }
//        avtoper(avtodelay);
//        */