#include "init.h"
#include "it_handlers.h"

void INIT (void)
{
    InitClock168MHz();
    InitSystemTick1ms();
    InitGPIOEXTI();
    InitTIM2();
}

int main(void) 
{
    INIT(); 
    OFF_LEDs();
    Running = 0;
    CurLEDI = 0;
    SpeedI = 0;

    while (1) 
    {
        __WFI();
    }
}
