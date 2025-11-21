#include "init.h"

static const uint16_t FreqContainer[] = {9999, 1999, 999, 499};

// Обновленная функция выключения всех светодиодов через ШИМ
void OFF_LEDs(void)
{
    TIM1->CCR1 = 0;  // PE9
    TIM1->CCR2 = 0;  // PE11
    TIM1->CCR3 = 0;  // PE13
    TIM1->CCR4 = 0;  // PE14
}

// Обновленная функция включения конкретного светодиода
void LED_OnIndex(uint8_t index)
{
    OFF_LEDs();  // Сначала выключаем все
    
    // Включаем выбранный светодиод на полную яркость
    switch(index) {
        case 0: TIM1->CCR1 = 1000; break;  // PE9
        case 1: TIM1->CCR2 = 1000; break;  // PE11
        case 2: TIM1->CCR3 = 1000; break;  // PE13
        case 3: TIM1->CCR4 = 1000; break;  // PE14
    }
}

// Новая функция для управления яркостью конкретного светодиода
void SetLEDBrightness(uint8_t index, uint16_t brightness)
{
    // Ограничиваем яркость максимальным значением таймера
    if(brightness > 1000) brightness = 1000;
    
    switch(index) {
        case 0: TIM1->CCR1 = brightness; break;  // PE9
        case 1: TIM1->CCR2 = brightness; break;  // PE11
        case 2: TIM1->CCR3 = brightness; break;  // PE13
        case 3: TIM1->CCR4 = brightness; break;  // PE14
    }
}

void InitGPIOEXTI(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOBEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // Настройка кнопки PA0
    GPIOA->MODER &= ~GPIO_MODER_MODER0;
    GPIOA->PUPDR = (GPIOA->PUPDR & ~GPIO_PUPDR_PUPDR0) | GPIO_PUPDR_PUPDR0_0;

    // Настройка PB0 для остановки
    GPIOB->MODER &= ~GPIO_MODER_MODER0;  // input mode
    GPIOB->PUPDR = (GPIOB->PUPDR & ~GPIO_PUPDR_PUPDR0) | GPIO_PUPDR_PUPDR0_0;  // pull-up

    // Настройка PB1
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODER1, GPIO_MODER_MODER1);
    MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPDR1, 0);

    // Конфигурация EXTI для кнопки PA0
    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;
    EXTI->IMR |= EXTI_IMR_MR0;
    EXTI->FTSR |= EXTI_FTSR_TR0;
    EXTI->RTSR &= ~EXTI_RTSR_TR0;
    EXTI->PR = EXTI_PR_PR0;

    // Конфигурация EXTI для кнопки PB0 (остановка)
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PB;  // PB0 connected to EXTI0
    EXTI->IMR |= EXTI_IMR_MR0;
    EXTI->FTSR |= EXTI_FTSR_TR0;
    EXTI->RTSR &= ~EXTI_RTSR_TR0;
    EXTI->PR = EXTI_PR_PR0;

    NVIC_SetPriority(EXTI0_IRQn, 1);
    NVIC_EnableIRQ(EXTI0_IRQn);
}

// Новая функция инициализации ШИМ на TIM1
void InitTIM1_PWM(void)
{
    // Включаем тактирование порта E и TIM1
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    // Настройка выводов PE9, PE11, PE13, PE14 как альтернативной функции
    GPIOE->MODER &= ~(GPIO_MODER_MODER9 | GPIO_MODER_MODER11 | 
                      GPIO_MODER_MODER13 | GPIO_MODER_MODER14);
    GPIOE->MODER |= (GPIO_MODER_MODER9_1 | GPIO_MODER_MODER11_1 | 
                     GPIO_MODER_MODER13_1 | GPIO_MODER_MODER14_1);
    
    // Выбор альтернативной функции TIM1 (AF1)
    GPIOE->AFR[1] &= ~(GPIO_AFRH_AFSEL9 | GPIO_AFRH_AFSEL11 | 
                       GPIO_AFRH_AFSEL13 | GPIO_AFRH_AFSEL14);
    GPIOE->AFR[1] |= (1 << (4*(9-8))) | (1 << (4*(11-8))) | 
                     (1 << (4*(13-8))) | (1 << (4*(14-8)));

    // Настройка TIM1 для ШИМ
    TIM1->PSC = 168 - 1;    // Предделитель: 168 МГц / 168 = 1 МГц
    TIM1->ARR = 1000 - 1;   // Период: 1000 тактов = 1 кГц ШИМ
    
    // Настройка каналов 1-4 в режиме PWM1
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 |  // PWM mode 1, канал 1
                   TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;   // PWM mode 1, канал 2
    TIM1->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 |  // PWM mode 1, канал 3
                   TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;   // PWM mode 1, канал 4
    
    // Включение выходов каналов
    TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | 
                  TIM_CCER_CC3E | TIM_CCER_CC4E;
    
    // Включение основного выхода и таймера
    TIM1->BDTR |= TIM_BDTR_MOE;
    TIM1->CR1 |= TIM_CR1_CEN;
}

void InitTIM2(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    TIM2->CR1 = 0;
    TIM2->CNT = 0;
    TIM2->PSC = 8399;
    TIM2->ARR = FreqContainer[0];
    TIM2->DIER |= TIM_DIER_UIE;

    NVIC_SetPriority(TIM2_IRQn, 2);
    NVIC_EnableIRQ(TIM2_IRQn);
}

void UpdFreqTIM2(uint8_t index)
{
    uint8_t freq_index = (index > 3) ? 0 : index;
    TIM2->ARR = FreqContainer[freq_index];
    TIM2->EGR |= TIM_EGR_UG;
}

void InitSystemTick1ms(void)
{
    SysTick->LOAD = (SystemCoreClock / 1000) - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void ADC_Init(void)
{
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC1EN);

    CLEAR_BIT(ADC1->CR2, ADC_CR2_ADON); //adc off
    SET_BIT(ADC->CCR, ADC_CCR_ADCPRE_0); // devide by 4
    MODIFY_REG(ADC1->SQR1, ADC_SQR1_L, 0); //num of channels
    MODIFY_REG(ADC1->SQR3, ADC_SQR3_SQ1, 9 << ADC_SQR3_SQ1_Pos); //first read 
    MODIFY_REG(ADC1->SMPR2, ADC_SMPR2_SMP9, 4 << ADC_SMPR2_SMP9_Pos); // charging cyles
    SET_BIT(ADC1->CR2, ADC_CR2_ADON); // adc on
}

void InitClock168MHz(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;

    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));

    FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY) | FLASH_ACR_LATENCY_5WS;

    RCC->CFGR = (RCC->CFGR & ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2))
                | RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2;

    RCC->PLLCFGR = (8 << RCC_PLLCFGR_PLLM_Pos)
                  | (336 << RCC_PLLCFGR_PLLN_Pos)
                  | RCC_PLLCFGR_PLLSRC_HSE
                  | (7 << RCC_PLLCFGR_PLLQ_Pos);

    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));

    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

    RCC->CR &= ~RCC_CR_HSION;
    SystemCoreClock = 168000000;
}


// #include "init.h"


// static const uint16_t FreqContainer[] = {9999, 1999, 999, 499};

// void OFF_LEDs(void)
// {
//     GPIOF->BSRR = GPIO_BSRR_BR7 | GPIO_BSRR_BR8 | GPIO_BSRR_BR9;
//     GPIOG->BSRR = GPIO_BSRR_BR1;
// }

// void LED_OnIndex(uint8_t index)
// {
//     uint32_t bsrr_value = 0;
    
//     if (index == 0) bsrr_value = GPIO_BSRR_BS7;
//     else if (index == 1) bsrr_value = GPIO_BSRR_BS8;
//     else if (index == 2) bsrr_value = GPIO_BSRR_BS9;
//     else if (index == 3) bsrr_value = GPIO_BSRR_BS1;
    
//     if (index < 3) GPIOF->BSRR = bsrr_value;
//     else GPIOG->BSRR = bsrr_value;
// }

// void InitGPIOEXTI(void)
// {
//     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOFEN | RCC_AHB1ENR_GPIOGEN | RCC_AHB1ENR_GPIOBEN;
//     RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

//     GPIOF->MODER = (GPIOF->MODER & ~(GPIO_MODER_MODER7 | GPIO_MODER_MODER8 | GPIO_MODER_MODER9))
//                    | (GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);
    
//     GPIOF->OTYPER &= ~(GPIO_OTYPER_OT7 | GPIO_OTYPER_OT8 | GPIO_OTYPER_OT9);
//     GPIOF->PUPDR &= ~(GPIO_PUPDR_PUPDR7 | GPIO_PUPDR_PUPDR8 | GPIO_PUPDR_PUPDR9);

//     GPIOG->MODER = (GPIOG->MODER & ~GPIO_MODER_MODER1) | GPIO_MODER_MODER1_0;
//     GPIOG->OTYPER &= ~GPIO_OTYPER_OT1;
//     GPIOG->PUPDR &= ~GPIO_PUPDR_PUPDR1;

//     GPIOA->MODER &= ~GPIO_MODER_MODER0;
//     GPIOA->PUPDR = (GPIOA->PUPDR & ~GPIO_PUPDR_PUPDR0) | GPIO_PUPDR_PUPDR0_0;

//      // PB1
//     MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODER1, GPIO_MODER_MODER1);
//     MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPDR1, 0);

//     SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;

//     EXTI->IMR |= EXTI_IMR_MR0;
//     EXTI->FTSR |= EXTI_FTSR_TR0;
//     EXTI->RTSR &= ~EXTI_RTSR_TR0;
//     EXTI->PR = EXTI_PR_PR0;

//     NVIC_SetPriority(EXTI0_IRQn, 1);
//     NVIC_EnableIRQ(EXTI0_IRQn);
// }

// void InitTIM2(void)
// {
//     RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

//     TIM2->CR1 = 0;
//     TIM2->CNT = 0;
//     TIM2->PSC = 8399;
//     TIM2->ARR = FreqContainer[0];
//     TIM2->DIER |= TIM_DIER_UIE;

//     NVIC_SetPriority(TIM2_IRQn, 2);
//     NVIC_EnableIRQ(TIM2_IRQn);
// }

// void UpdFreqTIM2(uint8_t index)
// {
//     uint8_t freq_index = (index > 3) ? 0 : index;
//     TIM2->ARR = FreqContainer[freq_index];
//     TIM2->EGR |= TIM_EGR_UG;
// }

// void InitSystemTick1ms(void)
// {
//     SysTick->LOAD = (SystemCoreClock / 1000) - 1;
//     SysTick->VAL = 0;
//     SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
// }

// void ADC_Init(void)
// {
//     SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC1EN);

//     CLEAR_BIT(ADC1->CR2, ADC_CR2_ADON); //adc off
//     SET_BIT(ADC->CCR, ADC_CCR_ADCPRE_0); // devide by 4
//     MODIFY_REG(ADC1->SQR1, ADC_SQR1_L, 0); //num of channels
//     MODIFY_REG(ADC1->SQR3, ADC_SQR3_SQ1, 9 << ADC_SQR3_SQ1_Pos); //first read 
//     MODIFY_REG(ADC1->SMPR2, ADC_SMPR2_SMP9, 4 << ADC_SMPR2_SMP9_Pos); // charging cyles
//     SET_BIT(ADC1->CR2, ADC_CR2_ADON); // adc on
// }

// void InitClock168MHz(void)
// {
//     RCC->APB1ENR |= RCC_APB1ENR_PWREN;
//     PWR->CR |= PWR_CR_VOS;

//     RCC->CR |= RCC_CR_HSEON;
//     while (!(RCC->CR & RCC_CR_HSERDY));

//     FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY) | FLASH_ACR_LATENCY_5WS;

//     RCC->CFGR = (RCC->CFGR & ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2))
//                 | RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2;

//     RCC->PLLCFGR = (8 << RCC_PLLCFGR_PLLM_Pos)
//                   | (336 << RCC_PLLCFGR_PLLN_Pos)
//                   | RCC_PLLCFGR_PLLSRC_HSE
//                   | (7 << RCC_PLLCFGR_PLLQ_Pos);

//     RCC->CR |= RCC_CR_PLLON;
//     while (!(RCC->CR & RCC_CR_PLLRDY));

//     RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL;
//     while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

//     RCC->CR &= ~RCC_CR_HSION;
//     SystemCoreClock = 168000000;
// }
