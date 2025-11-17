#include "init.h"
#include <stdint.h>

void RCC_Init(void)
{
    MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, 0x80U);
    CLEAR_REG(RCC->CFGR);
    while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RESET);
    CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) != RESET);
    CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON);
    while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != RESET);
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP); //Сбросим бит байпаса в 0, если вдруг там что-то лежит

    SET_BIT(RCC->CR, RCC_CR_HSEON); //Запускаем внешний кварцевый резонатор
    while(READ_BIT(RCC->CR, RCC_CR_HSERDY) == RESET); //Ждём пока он запустится
    SET_BIT(RCC->CR, RCC_CR_CSSON); //Запустим Clock detector
    

    CLEAR_REG(RCC->PLLCFGR);
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_HSE);
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLM_2);
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_3 | RCC_PLLCFGR_PLLN_5 | RCC_PLLCFGR_PLLN_6 | RCC_PLLCFGR_PLLN_8);
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP_0);
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ_0 | RCC_PLLCFGR_PLLQ_1 | RCC_PLLCFGR_PLLQ_2 | RCC_PLLCFGR_PLLQ_3);

    SET_BIT(RCC->CFGR, RCC_CFGR_SW_PLL);
    SET_BIT(RCC->CFGR, RCC_CFGR_HPRE_DIV1);
    SET_BIT(RCC->CFGR, RCC_CFGR_PPRE1_DIV4);
    SET_BIT(RCC->CFGR, RCC_CFGR_PPRE2_DIV2);
    SET_BIT(RCC->CFGR, RCC_CFGR_MCO1);
    SET_BIT(RCC->CFGR, RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_1);
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_MCO2);
    SET_BIT(RCC->CFGR, RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_1);

    SET_BIT(FLASH->ACR, FLASH_ACR_LATENCY_5WS);
    SET_BIT(RCC->CR, RCC_CR_PLLON); //Запустим PLL
    while(READ_BIT(RCC->CR, RCC_CR_PLLRDY) == RESET); //Ждём запуска PLL
}

void ITR_Init(void)
{
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);

    SET_BIT(SYSCFG->EXTICR[3], SYSCFG_EXTICR4_EXTI13_PC);
    SET_BIT(EXTI->IMR, EXTI_IMR_IM13);
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR13);
    CLEAR_BIT(EXTI->FTSR, EXTI_FTSR_TR13);

    NVIC_SetPriority(EXTI15_10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}



// void GPIO_init__Memory(void){};

// void GPIO_Ini(void)
// {
//     SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN);

//     SET_BIT(GPIOB->MODER, GPIO_MODER_MODE7_0);
//     CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT_7);
//     SET_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDER_OSPEEDR7_0);
//     CLEAR_BIT(GPIOB->PUPDR, GPIO_PUPDR_PUPDR7_0);
// }

// void ITR_Init(void)
// {
//     //Настройка регистра SYSCFG_EXTICR4 (включение тактирования МК)
//     SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);  
//     MODIFY_REG(SYSCFG->EXTICR[3], SYSCFG_EXTICR4_EXTI13_Msk, SYSCFG_EXTICR4_EXTI13_PC); 

//     //Настройка регистров EXTI (настройка прерывания на 13 линии)
//     SET_BIT(EXTI->IMR, EXTI_IMR_MR13); 
//     SET_BIT(EXTI->RTSR, EXTI_RTSR_TR13);  
//     SET_BIT(EXTI->FTSR, EXTI_FTSR_TR13); 

//     //Настройка регистров NVIC (разрешение прерывания и настройка приоритета)
//     NVIC_SetPriority(EXTI15_10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
//     NVIC_EnableIRQ(EXTI15_10_IRQn);
// }





// void GPIO_init_led_pb7_blue (void)
// {
// *(uint32_t *)(0x40023800UL + 0x30UL) |= 0x02UL;
// *(uint32_t *)(0x40023800UL + 0x30UL) |= 0x06UL;
// *(uint32_t *)(0x40020400UL + 0x00UL) |= 0x4000UL;
// *(uint32_t *)(0x40020400UL + 0x04UL) |= 0x00UL;
// *(uint32_t *)(0x40020400UL + 0x08UL) |= 0x4000UL;
// *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x800000UL;
// }
// void GPIO_init_led_pb14_red (void)
// {
//     RCC_AHB1ENR |= RCC_GPIOB_EN | RCC_GPIOC_EN;
//     BIT_SET(GPIOB_MODER, GPIO_PIN_OUT_14);
//     BIT_SET(GPIOB_OTYPER, GPIO_OFF);
//     BIT_SET(GPIOB_OSPEEDR, GPIO_PIN_MED_14);
//     BIT_SET(GPIOB_BSRR, GPIO_PIN_RESET_14);
// }
// void GPIO_init_led_pb0_green (void)
// {
//    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN);
//    SET_BIT(GPIOB->MODER, GPIO_MODER_MODE0_0);
//    CLEAR_BIT(GPIOB->OTYPER,GPIO_OTYPER_OT_0);
//    SET_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDER_OSPEEDR0_0);
//    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR0);
// }
// void GPIO_button_input(void)
// {
//     //PС12
//     CLEAR_BIT(GPIOB->MODER, GPIO_MODER_MODE12_0);
//     CLEAR_BIT(GPIOB->PUPDR, GPIO_PUPDR_PUPDR12_0);
// }