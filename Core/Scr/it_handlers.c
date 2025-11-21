#include "it_handlers.h"

volatile uint32_t MSTicks = 0;
volatile uint8_t CurLEDI = 0;
volatile uint8_t SpeedI = 0;
volatile uint8_t Running = 0;
volatile uint32_t DebugCounter = 0;

static volatile uint8_t g_btnDebounceActive = 0;
static volatile uint32_t g_btnDebounceDeadline = 0;
static volatile uint8_t g_btnStopDebounceActive = 0;
static volatile uint32_t g_btnStopDebounceDeadline = 0;

void EXTI0_IRQHandler(void) 
{
    if (EXTI->PR & EXTI_PR_PR0) 
    {
        EXTI->PR = EXTI_PR_PR0;
        
        // Определяем какая кнопка вызвала прерывание
        if (!(GPIOA->IDR & GPIO_IDR_ID0)) 
        {
            // Кнопка PA0 - запуск/смена скорости
            if (!g_btnDebounceActive) 
            {
                g_btnDebounceActive = 1;
                g_btnDebounceDeadline = MSTicks + 20;
                EXTI->IMR &= ~EXTI_IMR_MR0;
            }
        }
        else if (!(GPIOB->IDR & GPIO_IDR_ID0))
        {
            // Кнопка PB0 - остановка
            if (!g_btnStopDebounceActive) 
            {
                g_btnStopDebounceActive = 1;
                g_btnStopDebounceDeadline = MSTicks + 20;
                EXTI->IMR &= ~EXTI_IMR_MR0;
            }
        }
    }
}

void TIM2_IRQHandler(void) 
{
    if (TIM2->SR & TIM_SR_UIF) 
    {
        TIM2->SR &= ~TIM_SR_UIF;
        
        if (Running) 
        {
            OFF_LEDs();
            DebugCounter++;
            CurLEDI = (CurLEDI + 1) % 4;
            LED_OnIndex(CurLEDI);
        }
    }
}

void SysTick_Handler(void) 
{
    MSTicks++;
    
    // Обработка антидребезга для PA0 (запуск/смена скорости)
    if (g_btnDebounceActive && (int32_t)(MSTicks - g_btnDebounceDeadline) >= 0) 
    {
        g_btnDebounceActive = 0;
        
        if (!(GPIOA->IDR & GPIO_IDR_ID0)) 
        {
            if (!Running) 
            {
                Running = 1;
                CurLEDI = 0;
                SpeedI = 0;
                UpdFreqTIM2(SpeedI);
                OFF_LEDs();
                LED_OnIndex(CurLEDI);
                TIM2->CR1 |= TIM_CR1_CEN;
            } 
            else 
            {
                SpeedI = (SpeedI + 1) % 4;
                UpdFreqTIM2(SpeedI);
            }
        }
        
        EXTI->IMR |= EXTI_IMR_MR0;
    }
    
    // Обработка антидребезга для PB0 (остановка)
    if (g_btnStopDebounceActive && (int32_t)(MSTicks - g_btnStopDebounceDeadline) >= 0) 
    {
        g_btnStopDebounceActive = 0;
        
        if (!(GPIOB->IDR & GPIO_IDR_ID0)) 
        {
            // Останавливаем бегущий огонь, оставляя текущий светодиод включенным
            Running = 0;
            // Текущий светодиод остается включенным (не выключаем все)
        }
        
        EXTI->IMR |= EXTI_IMR_MR0;
    }
}


// #include "it_handlers.h"

// volatile uint32_t MSTicks = 0;
// volatile uint8_t CurLEDI = 0;
// volatile uint8_t SpeedI = 0;
// volatile uint8_t Running = 0;
// volatile uint32_t DebugCounter = 0;

// static volatile uint8_t g_btnDebounceActive = 0;
// static volatile uint32_t g_btnDebounceDeadline = 0;

// void EXTI0_IRQHandler(void) 
// {
//     if (EXTI->PR & EXTI_PR_PR0) 
//     {
//         EXTI->PR = EXTI_PR_PR0;
        
//         if (!g_btnDebounceActive) 
//         {
//             g_btnDebounceActive = 1;
//             g_btnDebounceDeadline = MSTicks + 20;
//             EXTI->IMR &= ~EXTI_IMR_MR0;
//         }
//     }
// }

// void TIM2_IRQHandler(void) 
// {
//     if (TIM2->SR & TIM_SR_UIF) 
//     {
//         TIM2->SR &= ~TIM_SR_UIF;
        
//         if (Running) 
//         {
//             OFF_LEDs();
//             DebugCounter++;
//             CurLEDI = (CurLEDI + 1) % 4;
//             LED_OnIndex(CurLEDI);
//         }
//     }
// }

// void SysTick_Handler(void) 
// {
//     MSTicks++;
    
//     if (g_btnDebounceActive && (int32_t)(MSTicks - g_btnDebounceDeadline) >= 0) 
//     {
//         g_btnDebounceActive = 0;
        
//         if (!(GPIOA->IDR & GPIO_IDR_ID0)) 
//         {
//             if (!Running) 
//             {
//                 Running = 1;
//                 CurLEDI = 0;
//                 SpeedI = 0;
//                 UpdFreqTIM2(SpeedI);
//                 OFF_LEDs();
//                 LED_OnIndex(CurLEDI);
//                 TIM2->CR1 |= TIM_CR1_CEN;
//             } 
//             else 
//             {
//                 SpeedI = (SpeedI + 1) % 4;
//                 UpdFreqTIM2(SpeedI);
//             }
//         }
        
//         EXTI->IMR |= EXTI_IMR_MR0;
//     }
// }



// // #include "it_handlers.h"

// // volatile uint32_t MSTicks = 0;
// // volatile uint8_t CurLEDI = 0;
// // volatile uint8_t SpeedI = 0;
// // volatile uint8_t Running = 0;
// // volatile uint32_t DebugCounter = 0;

// // static volatile uint8_t g_btnDebounceActive = 0;
// // static volatile uint32_t g_btnDebounceDeadline = 0;

// // void EXTI0_IRQHandler(void) 
// // {
// //     if (EXTI->PR & EXTI_PR_PR0) 
// //     {
// //         EXTI->PR = EXTI_PR_PR0;
        
// //         if (!g_btnDebounceActive) 
// //         {
// //             g_btnDebounceActive = 1;
// //             g_btnDebounceDeadline = MSTicks + 20;
// //             EXTI->IMR &= ~EXTI_IMR_MR0;
// //         }
// //     }
// // }

// // void TIM2_IRQHandler(void) 
// // {
// //     if (TIM2->SR & TIM_SR_UIF) 
// //     {
// //         TIM2->SR &= ~TIM_SR_UIF;
        
// //         if (Running) 
// //         {
// //             OFF_LEDs();
// //             DebugCounter++;
// //             CurLEDI = (CurLEDI + 1) % 4;
// //             LED_OnIndex(CurLEDI);
// //         }
// //     }
// // }

// // void SysTick_Handler(void) 
// // {
// //     MSTicks++;
    
// //     if (g_btnDebounceActive && (int32_t)(MSTicks - g_btnDebounceDeadline) >= 0) 
// //     {
// //         g_btnDebounceActive = 0;
        
// //         if (!(GPIOA->IDR & GPIO_IDR_ID0)) 
// //         {
// //             if (!Running) 
// //             {
// //                 Running = 1;
// //                 CurLEDI = 0;
// //                 SpeedI = 0;
// //                 UpdFreqTIM2(SpeedI);
// //                 OFF_LEDs();
// //                 LED_OnIndex(CurLEDI);
// //                 TIM2->CR1 |= TIM_CR1_CEN;
// //             } 
// //             else 
// //             {
// //                 SpeedI = (SpeedI + 1) % 4;
// //                 UpdFreqTIM2(SpeedI);
// //             }
// //         }
        
// //         EXTI->IMR |= EXTI_IMR_MR0;
// //     }
// // }
