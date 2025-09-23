#include <stdint.h>
#include "../Inc/init.h"
#include "../Src/init.c"

int main(void) { 
    GPIO_Ini();
    while(1){ 
        
        if(READ_GPIO_C13 != 0)
        { 
            SET_GPIO_B7; //Установка единицы в 7-ой бит регистра ODR 
            RESET_GPIO_B14;
        } 
        else
        { 
            RESET_GPIO_B7; //Установка нуля в 7-ой бит регистра ODR 
            SET_GPIO_B14;
        } 
    } 
}
//int main(void)
//{
//    *(uint32_t *)(0x40023800UL + 0x30UL) |= 0x02UL;   // включение тактирования GPIOB
//    *(uint32_t *)(0x40020400UL + 0x00UL) |= 0x4000UL; // включение режима работы пина PB7
//    *(uint32_t *)(0x40020400UL + 0x04UL) = 0x00UL;    // зануление режимов работы вывода, регистр
//    *(uint32_t *)(0x40020400UL + 0x08UL) |= 0x4000UL; // настройка регистра OSPEED скорости (скорость средняя)
//    *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x80UL;   // Включает светодиод, BSSR
//    while (1)
//    {
//    }
//}
