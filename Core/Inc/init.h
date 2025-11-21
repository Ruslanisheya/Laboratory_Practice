#include <stdint.h>
#include "..\..\CMSIS\Devices\STM32F4xx\Inc\STM32F429xx\stm32f429xx.h"
#include "..\..\CMSIS\Devices\STM32F4xx\Inc\stm32f4xx.h"

#ifndef INIT_H
#define INIT_H

void InitClock168MHz(void);
void InitSystemTick1ms(void);
void InitGPIOEXTI(void);
void InitTIM2(void);
void InitTIM1_PWM(void);
void UpdFreqTIM2(uint8_t index);
void OFF_LEDs(void);
void LED_OnIndex(uint8_t index);
void SetLEDBrightness(uint8_t index, uint16_t brightness);
void ADC_Init(void);
uint16_t ReadPotentiometer(void);

#endif


// #include <stdint.h>
// #include "..\..\CMSIS\Devices\STM32F4xx\Inc\STM32F429xx\stm32f429xx.h"
// #include "..\..\CMSIS\Devices\STM32F4xx\Inc\stm32f4xx.h"

// #ifndef INIT_H
// #define INIT_H

// void InitClock168MHz(void);
// void InitSystemTick1ms(void);
// void InitGPIOEXTI(void);
// void InitTIM2(void);
// void InitTIM1_PWM(void);  // Добавлена инициализация ШИМ
// void UpdFreqTIM2(uint8_t index);
// void OFF_LEDs(void);
// void LED_OnIndex(uint8_t index);
// void SetLEDBrightness(uint8_t index, uint16_t brightness);  // Добавлено управление яркостью
// void ADC_Init(void);
// uint16_t ReadPotentiometer(void);

// #endif


// // #include <stdint.h>
// // #include "..\..\CMSIS\Devices\STM32F4xx\Inc\STM32F429xx\stm32f429xx.h"
// // #include "..\..\CMSIS\Devices\STM32F4xx\Inc\stm32f4xx.h"

// // #ifndef INIT_H
// // #define INIT_H

// // void InitClock168MHz(void);
// // void InitSystemTick1ms(void);
// // void InitGPIOEXTI(void);
// // void InitTIM2(void);
// // void UpdFreqTIM2(uint8_t index);
// // void OFF_LEDs(void);
// // void LED_OnIndex(uint8_t index);
// // void ADC_Init(void);
// // uint16_t ReadPotentiometer(void);

// // #endif
