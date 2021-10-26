#include "mine.h"
uint8_t openmv[4];

void Openmv_Receive_Data(uint16_t data) //接收Openmv传过来的数据
{
    
    int len = 4;
    static uint8_t state = 0;
    static uint8_t bit_number = 0;
    if (state == 0 && data == 0x2C)
    {
        state = 1;
        openmv[bit_number++] = data;
    }
    else if (state == 1 && data == len)
    {
        state = 2;
        openmv[bit_number++] = data;
    }
    else if (state == 2)
    {
        openmv[bit_number++] = data;
        if (bit_number >= len - 1)
        {
            state = 3;
        }
    }
    else if (state == 3) //检测是否接受到结束标志
    {
        if (data == 0x5B)
        {
            state = 0;
            openmv[bit_number++] = data;
        }
        else if (data != 0x5B)
        {
            state = 0;
            for (int i = 0; i < len; i++)
            {
                openmv[i] = 0x00;
            }
        }
    }
    else
    {
        state = 0;
        bit_number = 0;
        for (int i = 0; i < len; i++)
        {
            openmv[i] = 0x00;
        }
    }
}
