#ifndef INIT_H
#define INIT_H

#include "../../CMSIS/Devices/STM32F4xx/Inc/stm32f4xx.h"
#include "stm32f429xx.h"

void GPIO_Reset(void);
void RCC_Init(void);
void ITR_Init(void);


void Led_init(void);
void Buttons_Init(void);

#define GPIOD_MODER *(uint32_t *)(0x40020C00UL + 0x00UL)
#define GPIOD_OTYPER *(uint32_t *)(0x40020C00UL + 0x04UL)
#define GPIOD_OSPEEDR *(uint32_t *)(0x40020C00UL + 0x08UL)
#define GPIOD_PUPDR *(uint32_t *)(0x40020C00UL + 0x0CUL)
#define GPIOD_BSRR *(uint32_t *)(0x40020C00UL + 0x18UL)
#define GPIOD_IDR *(uint32_t *)(0x40020C00UL + 0x10UL)


#define GPIO_MODER_OUT_4 (0x01U << 8)   // bits 7:6 = 01

// MODER input settings (00)
#define GPIO_MODER_IN_4 (0x00U << 8)    // bits 9:8 = 00

// OSPEEDR medium speed (01)
#define GPIO_OSPEEDR_MED_0 (0x01U << 0)
#define GPIO_OSPEEDR_MED_1 (0x01U << 2)
#define GPIO_OSPEEDR_MED_2 (0x01U << 4)
#define GPIO_OSPEEDR_MED_3 (0x01U << 6)

#define RCC_AHB1ENR *(uint32_t *)(0x40023800UL + 0x030UL)
#define RCC_GPIOA_EN 0x01UL
#define RCC_GPIOB_EN 0x02UL
#define RCC_GPIOC_EN 0x04UL
#define RCC_GPIOD_EN 0x08UL

#define GPIOB_MODER         *(uint32_t *)(0x40020400UL + 0x00UL)
#define GPIOB_OTYPER        *(uint32_t *)(0x40020400UL + 0x04UL)
#define GPIOB_OSPEEDR       *(uint32_t *)(0x40020400UL + 0x08UL)
#define GPIOB_PUPDR         *(uint32_t *)(0x40020400UL + 0x0CUL)
#define GPIOB_BSRR          *(uint32_t *)(0x40020400UL + 0x18UL)

#define GPIO_OFF 0x00UL

#define GPIO_PIN_0 0x01UL
#define GPIO_PIN_1 0x02UL
#define GPIO_PIN_2 0x04UL
#define GPIO_PIN_3 0x08UL
#define GPIO_PIN_4 0x10UL
#define GPIO_PIN_7 0x80UL
#define GPIO_PIN_14 0x4000UL

#define GPIO_PIN_OUT_0 0x01UL
#define GPIO_PIN_OUT_1 0x04UL
#define GPIO_PIN_OUT_2 0x10UL
#define GPIO_PIN_OUT_3 0x40UL
#define GPIO_PIN_OUT_4 0x100UL
#define GPIO_PIN_OUT_7 0x4000UL
#define GPIO_PIN_OUT_14 0x10000000UL

#define GPIO_PIN_IN_0 0x00UL
#define GPIO_PIN_IN_4 0x00UL

#define GPIO_PIN_MED_0 0x01UL
#define GPIO_PIN_MED_1 0x04UL
#define GPIO_PIN_MED_2 0x10UL
#define GPIO_PIN_MED_3 0x40UL
#define GPIO_PIN_MED_4 0x100UL
#define GPIO_PIN_MED_7 0x4000UL
#define GPIO_PIN_MED_14 0x10000000UL

#define GPIO_PIN_RESET_0 0x10000UL
#define GPIO_PIN_RESET_1 0x20000UL
#define GPIO_PIN_RESET_2 0x40000UL
#define GPIO_PIN_RESET_3 0x80000UL
#define GPIO_PIN_RESET_4 0x100000UL
#define GPIO_PIN_RESET_7 0x800000UL
#define GPIO_PIN_RESET_14 0x40000000UL

#define GPIO_PIN_SET_0 0x01UL
#define GPIO_PIN_SET_1 0x02UL
#define GPIO_PIN_SET_2 0x04UL
#define GPIO_PIN_SET_3 0x08UL
#define GPIO_PIN_SET_4 0x10UL
#define GPIO_PIN_SET_7 0x80UL
#define GPIO_PIN_SET_14 0x4000UL

#define BIT_SET(REG, BIT) ((REG) |= (BIT))
#define BIT_CLEAR(REG, BIT) ((REG) &= ~(BIT))
#define BIT_READ(REG,BIT) ((REG) & (BIT))

// Debounce function
void delay_ms(uint32_t ms);

#endif



// void GPIO_Ini(void);
// void GPIO_init_CMSIS(void);
// void GPIO_init__Memory(void);
// void ITR_Init(void);



// void GPIO_init_led_pb7_blue (void);
// void GPIO_init_led_pb14_red (void);
// void GPIO_init_led_pb0_green (void);
// void GPIO_button_input(void);

// #define RCC_AHB1ENR         *(uint32_t *)(0x40023800UL + 0x30UL)
// #define RCC_GPIOB_EN        0x02UL
// #define RCC_GPIOC_EN        0x06UL

// #define GPIOB_MODER         *(uint32_t *)(0x40020400UL + 0x00UL)
// #define GPIOB_OTYPER        *(uint32_t *)(0x40020400UL + 0x04UL)
// #define GPIOB_OSPEEDR       *(uint32_t *)(0x40020400UL + 0x08UL)
// #define GPIOB_BSRR          *(uint32_t *)(0x40020400UL + 0x18UL)

// #define GPIOC_IDR           *(uint32_t *)(0x40020800UL + 0x10UL)

// #define GPIO_PIN_MED_14     0x10000000UL
// #define GPIO_PIN_OUT_14     0x10000000UL
// #define GPIO_PIN_RESET_14   0x40000000UL
// #define GPIO_PIN_SET_14     0x4000UL

// #define GPIO_PIN_MED_7      0x4000UL
// #define GPIO_PIN_OUT_7      0x4000UL
// #define GPIO_OFF            0x00UL
// #define GPIO_PIN_RESET_7    0x800000UL
// #define GPIO_PIN_SET_7      0x80UL

// #define GPIO_PIN_13         0x2000UL
// #define GPIO_PIN_12         0x1000UL

// #define GPIO_PIN_MED_0      0x1UL
// #define GPIO_PIN_OUT_0      0x1UL
// #define GPIO_OFF            0x00UL
// #define GPIO_PIN_RESET_0    0x10000UL
// #define GPIO_PIN_SET_0      0x10UL


// #define BIT_SET(REG, BIT)   ((REG) |= (BIT))
// #define BIT_READ(REG, BIT)  ((REG) & (BIT))