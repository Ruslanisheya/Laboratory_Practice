#include "init.h"

static const uint16_t FreqContainer[] = {9999, 1999, 999, 499};

void OFF_LEDs(void)
{
    GPIOF->BSRR = GPIO_BSRR_BR7 | GPIO_BSRR_BR8 | GPIO_BSRR_BR9;
    GPIOG->BSRR = GPIO_BSRR_BR1;
}

void LED_OnIndex(uint8_t index)
{
    uint32_t bsrr_value = 0;
    
    if (index == 0) bsrr_value = GPIO_BSRR_BS7;
    else if (index == 1) bsrr_value = GPIO_BSRR_BS8;
    else if (index == 2) bsrr_value = GPIO_BSRR_BS9;
    else if (index == 3) bsrr_value = GPIO_BSRR_BS1;
    
    if (index < 3) GPIOF->BSRR = bsrr_value;
    else GPIOG->BSRR = bsrr_value;
}

void InitGPIOEXTI(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOFEN | RCC_AHB1ENR_GPIOGEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    GPIOF->MODER = (GPIOF->MODER & ~(GPIO_MODER_MODER7 | GPIO_MODER_MODER8 | GPIO_MODER_MODER9))
                   | (GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);
    
    GPIOF->OTYPER &= ~(GPIO_OTYPER_OT7 | GPIO_OTYPER_OT8 | GPIO_OTYPER_OT9);
    GPIOF->PUPDR &= ~(GPIO_PUPDR_PUPDR7 | GPIO_PUPDR_PUPDR8 | GPIO_PUPDR_PUPDR9);

    GPIOG->MODER = (GPIOG->MODER & ~GPIO_MODER_MODER1) | GPIO_MODER_MODER1_0;
    GPIOG->OTYPER &= ~GPIO_OTYPER_OT1;
    GPIOG->PUPDR &= ~GPIO_PUPDR_PUPDR1;

    GPIOA->MODER &= ~GPIO_MODER_MODER0;
    GPIOA->PUPDR = (GPIOA->PUPDR & ~GPIO_PUPDR_PUPDR0) | GPIO_PUPDR_PUPDR0_0;

    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;

    EXTI->IMR |= EXTI_IMR_MR0;
    EXTI->FTSR |= EXTI_FTSR_TR0;
    EXTI->RTSR &= ~EXTI_RTSR_TR0;
    EXTI->PR = EXTI_PR_PR0;

    NVIC_SetPriority(EXTI0_IRQn, 1);
    NVIC_EnableIRQ(EXTI0_IRQn);
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
