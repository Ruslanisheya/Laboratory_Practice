#include "it_handlers.h"

extern volatile uint8_t btncnt, flag;
void EXTI15_10_IRQHandler()
{
    SET_BIT(EXTI->PR, EXTI_PR_PR13);
    btncnt++;
    flag = !flag;
}


// #include "init.h"
// #include "it_handlers.h"
// #include <stdint.h>

// uint8_t BtnCount = 0;

// void EXTI15_10_IRQHandler(void)
// {
//     BtnCount++;
//     SET_BIT(EXTI->PR, EXTI_PR_PR13);
// }