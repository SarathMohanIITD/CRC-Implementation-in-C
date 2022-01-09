//------------------------------------------------------------
//  Function for creating referance table of remainder
//  Returns all possible values of remainders for 
//              given polynomila (here : 0x15)
//-------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdint.h>
#include "../include/define.h"


uint8_t * precalc()
{   
    static uint8_t hash[256];
    uint8_t remainder =0;
    for (int div= 0; div < 256; ++div)
    {
       remainder = div;
        
        for(int i=0;i<8;i++)
        {
            if(remainder & 0x80)
                remainder = (remainder << 1) ^ POLYNOMIAL;
            else
                remainder<<1;
        } 
        hash[div]=(remainder);
    }
    return hash;
}