#include <stdint.h>

int main(void)
{
    *(uint32_t*)(0x40023800 + 0x30) |= 0x02;
    // 01000000000000100011100000000000 + 00110000

    while (1){}
}
