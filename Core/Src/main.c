#include "../Inc/init.h"
#include "../Inc/it_handlers.h"


uint8_t BtnFi = 0;//Button one push
uint8_t BtnTwSh = 0;//Button two short push
uint16_t FreqList[3] = {5000, 1250, 769};
uint8_t CurLEDI = 0;
uint8_t Mode = 0;
uint32_t LiTi = 0;//Lighting time
uint8_t Freq = 0;

void ResetLEDs(void)
{
    //все светодиоды и кнопки в GPIOC, порты: PC8, PC9, PC10, PC11, PC12 и PC6; кнопки - PC0 и PC3.
    SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR8 | GPIO_BSRR_BR9 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR12 | GPIO_BSRR_BR6);
    switch (CurLEDI)
    {
        case 0:
            //PC8
            SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS8);
            break;
        case 1:
            //PC9
            SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS9);
            break;
        case 2:
            //PC10
            SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS10);
            break;
        case 3:
            //PC11
            SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS11);
            break;
        case 4:
            //PC12
            SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS12);
            break;
        case 5:
            //PC6
            SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS6);
            break;           
    }
}

void flickers(void)
{
    if (LiTi < FreqList[Freq] / 2)
    {
        ResetLEDs();
    }
    else
    {
        SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR8 | GPIO_BSRR_BR9 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR12 | GPIO_BSRR_BR6);
    }

    if (LiTi >= FreqList[Freq])
    {
        LiTi = 0;
    }
}


void changeFlickerFrequency(void) 
{
    Freq = (Freq + 1) % 3;
}


void handleButton1(void)
{
    CurLEDI = (CurLEDI + 1) % 6;
    LiTi = 0;
}

int main(void)
{
    GPIO_Ini();
    RCC_Ini();
    EXTI_ITR_Ini();
    SysTick_Init();
    
    SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR8 | GPIO_BSRR_BR9 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR12 | GPIO_BSRR_BR6);
    while (1)
    {
        
        if (BtnFi)
        {
            handleButton1();
            BtnFi = 0; 
        }
        

        if (BtnTwSh)
        {
            changeFlickerFrequency();
            BtnTwSh = 0;
            LiTi = 0; 
        }
        
        if (Mode) 
        {
            SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR8 | GPIO_BSRR_BR9 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR12 | GPIO_BSRR_BR6);
            flickers();
        }
        else 
        {
            ResetLEDs();
        }
    }
}