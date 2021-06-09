#include "SPI.h"

/* function prototype of SPI and Delay */
void SPI0_init(void);
void SPI0_Write(unsigned char data);
void SSI_send_char (uint32_t data);
void Delay_ms(int time_ms); 
void SSI_Receive_char (uint32_t * data);
uint8_t i=0;
uint32_t data[256];
/* Main routine of code */
int main(void)
{
    
    unsigned char val1 = 'C';
    unsigned char val2 = 'D';

    SSI_init();
     
    for (i = 0; i<255 ; i++)
    {
      data[i] = 0;
    }
    
    while(1)
for (i = 0; i<255 ; i++)
    {
      SSI_send_char(val1+(i%2)); /* write a character */
       SSI_Receive_char (&data[i]);
       Delay_ms(100);
    }
    
   
    
}


/* This function generates delay in ms */
/* calculations are based on 16MHz system clock frequency */

void Delay_ms(int time_ms)
{
    int i, j;
    for(i = 0 ; i < time_ms; i++)
        for(j = 0; j < 3180; j++)
            {}  /* excute NOP for 1ms */
}

