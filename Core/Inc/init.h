#include <stdint.h>
#include "..\..\CMSIS\Devices\STM32F4xx\Inc\STM32F429xx\stm32f429xx.h"

#ifndef INIT_H
#define INIT_H

void InitClock168MHz(void);
void InitSystemTick1ms(void);
void InitGPIOEXTI(void);
void InitTIM2(void);
void UpdFreqTIM2(uint8_t index);
void OFF_LEDs(void);
void LED_OnIndex(uint8_t index);

#endif
