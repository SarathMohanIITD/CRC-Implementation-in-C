//------------------------------------------------------------
//  Function for bit by bit crc remainder calculation
//  Returns remainder
//-------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdint.h>
#include "../include/define.h"

uint8_t bitbybit(int data[])
{
    uint8_t remainder=0;
    for(int byte =0; byte<size; byte++)
    {
        remainder ^= data[byte];
        
        for(int i=0;i<8;i++)
        {
            if(remainder & 0x80)
                remainder = (remainder << 1) ^ POLYNOMIAL;
            else
                remainder<<1;
        }
    }
    return (remainder);
}