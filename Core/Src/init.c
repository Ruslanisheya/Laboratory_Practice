#include "../Inc/init.h"
#include <stdint.h>

void RCC_Ini(void)
{
MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, 0x80U);
CLEAR_REG(RCC->CFGR);
while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RESET);
CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) != RESET);
CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON);
while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != RESET);
CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);

//######################################################################################################################################

SET_BIT(RCC->CR, RCC_CR_HSEON);
while(READ_BIT(RCC->CR, RCC_CR_HSERDY) == RESET);
CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
SET_BIT(RCC->CR, RCC_CR_CSSON);

//######################################################################################################################################

CLEAR_REG(RCC->PLLCFGR);
SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_HSE);
MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLM, RCC_PLLCFGR_PLLM_2);
MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_Msk, RCC_PLLCFGR_PLLN_2 |RCC_PLLCFGR_PLLN_4 | RCC_PLLCFGR_PLLN_5 | RCC_PLLCFGR_PLLN_7);
CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP_Msk);
SET_BIT(RCC->CR, RCC_CR_PLLON);
while(READ_BIT(RCC->CR, RCC_CR_PLLRDY));

//######################################################################################################################################

MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV1);
MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV4);
MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, RCC_CFGR_PPRE2_DIV2);
MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO2PRE, RCC_CFGR_MCO2PRE_Msk);
CLEAR_BIT(RCC->CFGR, RCC_CFGR_MCO2);

//######################################################################################################################################

MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_5WS);
}


//######################################################################################################################################
//######################################################################################################################################


//Подключение тактирования для светодиодов
void GPIO_Ini(void)
{
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN |  RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOFEN);
    // PC8
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODE8_0);
    CLEAR_BIT(GPIOC->OTYPER, GPIO_OTYPER_OT_8);
    SET_BIT(GPIOC->OSPEEDR, GPIO_OSPEEDER_OSPEEDR8_0);
    CLEAR_BIT(GPIOC->PUPDR, GPIO_PUPDR_PUPDR8_0);
    // PC9
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODE9_0);
    CLEAR_BIT(GPIOC->OTYPER, GPIO_OTYPER_OT_9);
    SET_BIT(GPIOC->OSPEEDR, GPIO_OSPEEDER_OSPEEDR9_0);
    CLEAR_BIT(GPIOC->PUPDR, GPIO_PUPDR_PUPDR9_0);
    // PC10
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODE10_0);
    CLEAR_BIT(GPIOC->OTYPER, GPIO_OTYPER_OT_10);
    SET_BIT(GPIOC->OSPEEDR, GPIO_OSPEEDER_OSPEEDR10_0);
    CLEAR_BIT(GPIOC->PUPDR, GPIO_PUPDR_PUPDR10_0);
    // PC11
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODE11_0);
    CLEAR_BIT(GPIOC->OTYPER, GPIO_OTYPER_OT_11);
    SET_BIT(GPIOC->OSPEEDR, GPIO_OSPEEDER_OSPEEDR11_0);
    CLEAR_BIT(GPIOC->PUPDR, GPIO_PUPDR_PUPDR11_0);
    // PC12
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODE12_0);
    CLEAR_BIT(GPIOC->OTYPER, GPIO_OTYPER_OT_12);
    SET_BIT(GPIOC->OSPEEDR, GPIO_OSPEEDER_OSPEEDR12_0);
    CLEAR_BIT(GPIOC->PUPDR, GPIO_PUPDR_PUPDR12_0);
    // PC6
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODE6_0);
    CLEAR_BIT(GPIOC->OTYPER, GPIO_OTYPER_OT_6);
    SET_BIT(GPIOC->OSPEEDR, GPIO_OSPEEDER_OSPEEDR6_0);
    CLEAR_BIT(GPIOC->PUPDR, GPIO_PUPDR_PUPDR6_0);
}

//######################################################################################################################################
//######################################################################################################################################

void EXTI_ITR_Ini(void)
{
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);
//кнопка 1
    MODIFY_REG(SYSCFG->EXTICR[0], SYSCFG_EXTICR1_EXTI0_Msk, SYSCFG_EXTICR1_EXTI0_PC);
    SET_BIT(EXTI->IMR, EXTI_IMR_MR0);
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR0);
    SET_BIT(EXTI->FTSR, EXTI_FTSR_TR0);
//кнопка 2
    MODIFY_REG(SYSCFG->EXTICR[0], SYSCFG_EXTICR1_EXTI3_Msk, SYSCFG_EXTICR1_EXTI3_PC);
    SET_BIT(EXTI->IMR, EXTI_IMR_MR3);
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR3);
    SET_BIT(EXTI->FTSR, EXTI_FTSR_TR3);
    
    NVIC_SetPriority(EXTI0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_SetPriority(EXTI3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));

    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_EnableIRQ(EXTI3_IRQn);
}

//######################################################################################################################################
//######################################################################################################################################

void SysTick_Init(void)
{
    CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);
    SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
    SET_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk);
    MODIFY_REG(SysTick->LOAD, SysTick_LOAD_RELOAD_Msk,179999 << SysTick_LOAD_RELOAD_Pos);
    MODIFY_REG(SysTick->VAL, SysTick_VAL_CURRENT_Msk,0 << SysTick_VAL_CURRENT_Pos);
    SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);
}