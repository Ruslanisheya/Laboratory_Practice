#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>
#include "..\..\CMSIS\Devices\STM32F4xx\Inc\STM32F429xx\stm32f429xx.h"
#include "init.h"

extern volatile uint32_t MSTicks;
extern volatile uint8_t CurLEDI;
extern volatile uint8_t SpeedI;
extern volatile uint8_t Running;
extern volatile uint32_t DebugCounter;

#endif


// #ifndef INTERRUPT_H
// #define INTERRUPT_H

// #include <stdint.h>
// #include "..\..\CMSIS\Devices\STM32F4xx\Inc\STM32F429xx\stm32f429xx.h"
// #include "init.h"

// extern volatile uint32_t MSTicks;
// extern volatile uint8_t CurLEDI;
// extern volatile uint8_t SpeedI;
// extern volatile uint8_t Running;
// extern volatile uint32_t DebugCounter;

// #endif


// // #ifndef INTERRUPT_H
// // #define INTERRUPT_H

// // #include <stdint.h>
// // #include "..\..\CMSIS\Devices\STM32F4xx\Inc\STM32F429xx\stm32f429xx.h"
// // #include "init.h"

// // extern volatile uint32_t MSTicks;
// // extern volatile uint8_t CurLEDI;
// // extern volatile uint8_t SpeedI;
// // extern volatile uint8_t Running;
// // extern volatile uint32_t DebugCounter;

// // #endif