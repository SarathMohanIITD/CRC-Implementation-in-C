#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdint.h>
#include "../include/functions.h"
#include "../include/define.h"

//------------------------------------------------------------
//  Main function
//-------------------------------------------------------------
void main()
{   int nerr1=0,nerr2=0,nerr3=0;      //To count number of errors
    float cu_time1=0,cu_time2=0,cu_time3=0; //To calculate total time 
    for(int loop =0;loop<=LOOP;loop++)
    {
        srand(time(0));
        int* data = (int*)malloc(size * sizeof(int));
        int* errdata1 = (int*)malloc(size * sizeof(int));
        int* errdata2 = (int*)malloc(size * sizeof(int));
        int* errdata3 = (int*)malloc(size * sizeof(int));
        unsigned int err=(rand()%256); //Random error data
        uint8_t *hash;
        uint8_t rem1,rem2,rem3;
        
        for(int i=0;i<size-1;i++)    //Generathing random data 
        {   
            data[i]= (rand()%256);
            errdata1[i]=data[i];
            errdata2[i]=data[i];
            errdata3[i]=data[i];
        }
        data[size-1]=0;
        errdata1[size-1]=0;
        errdata2[size-1]=0;
        errdata3[size-1]=0;
        //-----------------------------------------------------
        //Currupting data by changing one element in the array
        //------------------------------------------------------
        //printf("\n\n\t Enter a byte data (noise)(0-255) to currupt the data ");
        //scanf("%d",&err);
        
        errdata1[25]^=err;
        errdata2[25]^=err;
        errdata3[25]^=err;       //Introducing error
        
        //-----------------------------------------------------
        //BIT BY BIT METHOD
        //------------------------------------------------------
        //Measuring time taken for bit by bit method
        clock_t start1 = clock();

        rem1 = bitbybit(data); //Generating crc with original data
        errdata1[size-1]=rem1;  //Appending crc to the noisy data
        //Decoding the error
        rem1=bitbybit(errdata1); //Checking for error and returning remainder
        if(!rem1) 
            nerr1++;  
        clock_t stop1 = clock();

        hash = precalc();

        //-----------------------------------------------------
        //BYTE BY BYTE METHOD
        //------------------------------------------------------
        //Measurning time taken for byte byte method
        clock_t start2 = clock();
        rem2 = bytebybyte(data,hash);
        errdata2[size-1]=rem2;  //Appending crc to the noisy data
        //Decoding the error
        rem2=bytebybyte(errdata2,hash);   //Checking for error and returning remainder
        if(!rem1) 
            nerr2++;
        clock_t stop2 = clock();

        
        //---------------------------------------------------------
        //  A BETTER METHOD
        //----------------------------------------------------------
        clock_t start3 = clock();
        rem3 = better(data,hash);
        errdata3[size-1]=rem3;       //Appending crc to the noisy data
        //Decoding the error
        rem3=better(errdata3,hash);   //Checking for error and returning remainder
        if(!rem1) 
            nerr3++;
        clock_t stop3 = clock();
        
        
        float time1 = (float)(stop1-start1)/CLOCKS_PER_SEC;
        float time2 = (float)(stop2-start2)/CLOCKS_PER_SEC;
        float time3 = (float)(stop3-start3)/CLOCKS_PER_SEC;

        cu_time1+=time1;
        cu_time2+=time2;
        cu_time3+=time3;

        
        free(data);
        free(errdata1);
        free(errdata2);
        free(errdata3);
        

    }
    printf("\n\n\t\t\tPOLYNOMIAL USED = 0x9B\n");
    printf("\t\t\tNUMBER OF FRAMES = %d\n\n",LOOP);

    printf("\t1. BIT BY BIT METHOD \n");
    printf("\t\t\tTotal time taken = %f seconds\n",cu_time1);
    printf("\t\t\tTotal number of errors detected = %d\n\n",nerr1);
    
    printf("\t2.  BYTE BY BYTE METHOD \n");
    printf("\t\t\tTotal time taken = %f seconds \n",cu_time2);
    printf("\t\t\tTotal number of errors detected = %d\n\n",nerr2);
    
    printf("\t3.  Better METHOD \n");
    printf("\t\t\tTotal time taken = %f seconds \n",cu_time3);
    printf("\t\t\tTotal number of errors detected = %d\n\n",nerr3);
}