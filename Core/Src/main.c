#include "../Inc/init.h"
#include "../Src/init.c"
#include <stdint.h>

// int main (void)
// {
//     return 0;
// }



// uint8_t f1 = 0;
// uint8_t f2 = 0;
// uint8_t f3 = 0;
// uint8_t f4 = 0;
// uint8_t CurLEDi = 0;
// uint8_t CoOLED = 2;
// uint8_t Mode = 0;
// uint32_t Freq = 0;
// uint32_t Timer = 0;

// // первая кнопка: меняет светодиод; если горят все три, то выкл/вкл светодиоды.
// // вторая кнопка: короткое нажатие - смена количества горящих светодиодов; длительное нажатие - смена режима работы (постоянное свечение; 0,5Гц; 1Гц; 2Гц; 5Гц).

// void ResetLED(void)
//     {
//         SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR0 |GPIO_BSRR_BR7 | GPIO_BSRR_BR14 );
//         if (f3 == 0)
//             {
//                 for (uint8_t i = 0; i <=CoOLED; i++) 
//                 {
//                     uint8_t led_index = ((CurLEDi + i) % 3);
//                     switch (led_index) 
//                     {
//                     case 0:
//                         SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS0);
//                         break;
//                     case 1:
//                         SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS7);
//                         break;
//                     case 2:
//                         SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS14);
//                         break;

                
//                     }
//                 }
//             }
//     }
// //#################################################################################################
// //#################################################################################################
//     void Blink182(void)
//     {
//         for(volatile uint32_t i = 0; i < Freq; i++){}
//         SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR0 |GPIO_BSRR_BR7 | GPIO_BSRR_BR14 );
//         if (f4 == 0)
//         {
//             ResetLED();
//             f4 = 1;
//         }
//         else
//         {
//             f4 = 0;
//         }
//     }
// //#################################################################################################
// //#################################################################################################
// int main(void)
// {
//     GPIO_init_led_pb7_blue ();
//     GPIO_init_led_pb14_red ();
//     GPIO_init_led_pb0_green ();
//     GPIO_button_input();
     
//     while (1)
//     {
// //#################################################################################################
//         if (BIT_READ(GPIOC_IDR, GPIO_PIN_12))
//         {
//             if (CoOLED == 2)
//             {
//                 if (f3 == 0)
//                 {
//                     f3 = 1;
//                     f1 = 1;
//                 }
//                 else
//                 {
//                     f3 = 0;
//                     f1 = 0;
//                 }
//             }
//             else
//             {
//                 CurLEDi = ((CurLEDi + 1) % 3);
//             }
//             ResetLED();
//             for(volatile uint32_t i = 0; i < 250000; i++){}
//         }
// //#################################################################################################
//         while (BIT_READ(GPIOC_IDR, GPIO_PIN_13))
//             {
//                 Timer++;
//             }
//             if (Timer>= 500000)
//             {
//                 Mode = ((Mode + 1) % 5);
//                 Timer=0;
//             }
//             else if(Timer>0 && Timer<500000)
//             {
//             if (f1 == 0)
//             {
//                 CoOLED = ((CoOLED + 1) % 3);
//             }
//             ResetLED();
//             Timer=0;
//             for(volatile uint32_t i = 0; i < 250000; i++){}
//             }

//         switch (Mode)
//         {
//             case 0:
//                 Freq = 0;
//                 break;
//             case 1:
//                 Freq = 1000000;
//                 break;
//             case 2:
//                 Freq = 500000;
//                 break;
//             case 3:
//                 Freq = 300000;
//                 break;
//             case 4:
//                 Freq = 50000;
//                 break;
//         }

//         if (Freq != 0)
//         {
//             Blink182();
//         }
//     }
// }
