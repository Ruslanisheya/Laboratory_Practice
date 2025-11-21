#include "init.h"
#include "it_handlers.h"

uint32_t adc = 0;

void INIT (void)
{
    InitClock168MHz();
    InitSystemTick1ms();
    InitGPIOEXTI();
    InitTIM2();
    InitTIM1_PWM();
    ADC_Init();
}

int main(void) 
{
    INIT();
    OFF_LEDs();
    Running = 0;
    CurLEDI = 0;
    SpeedI = 0;

    while (1) 
    {
        SET_BIT(ADC1->CR2, ADC_CR2_SWSTART); 
        adc =  ADC1->DR;
        // В будущем можно использовать adc значение для управления яркостью
        // SetLEDBrightness(CurLEDI, adc >> 6);  // Пример: преобразование 12-битного ADC в 0-1000
    }
}


// #include "init.h"
// #include "it_handlers.h"

// uint32_t adc = 0;

// void INIT (void)
// {
//     InitClock168MHz();
//     InitSystemTick1ms();
//     InitGPIOEXTI();
//     InitTIM2();
//     InitTIM1_PWM();  // Добавлена инициализация ШИМ
//     ADC_Init();
// }

// int main(void) 
// {
//     INIT();
//     OFF_LEDs();
//     Running = 0;
//     CurLEDI = 0;
//     SpeedI = 0;

//     while (1) 
//     {
//         SET_BIT(ADC1->CR2, ADC_CR2_SWSTART); 
//         adc =  ADC1->DR;
//         // В будущем можно использовать adc значение для управления яркостью
//         // SetLEDBrightness(CurLEDI, adc >> 6);  // Пример: преобразование 12-битного ADC в 0-1000
//     }
// }


// // #include "init.h"
// // #include "it_handlers.h"

// // uint32_t adc = 0;


// // void INIT (void)
// // {
// //     InitClock168MHz();
// //     InitSystemTick1ms();
// //     InitGPIOEXTI();
// //     InitTIM2();
// //     ADC_Init();
// // }

// // int main(void) 
// // {
// //     INIT();
// //     OFF_LEDs();
// //     Running = 0;
// //     CurLEDI = 0;
// //     SpeedI = 0;

// //     while (1) 
// //     {
// //         SET_BIT(ADC1->CR2, ADC_CR2_SWSTART); 
// //         adc =  ADC1->DR;
// //     }
// // }
