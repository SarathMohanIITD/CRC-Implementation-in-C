//------------------------------------------------------------
//  Function for a better crc method 
//  (modified byte by byte crc remainder calculation)
//  Returns remainder
//-------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdint.h>
#include "../include/define.h"

uint8_t better(int data[],uint8_t *hash)
{   
    
    int temp;
    uint8_t remainder= INIT_REM;
    for (int byte = 0; byte < size; ++byte)
    {
        temp = data[byte] ^ remainder;
        remainder = hash[temp] ;
    }
    return((remainder )^ FIN_REM);
}