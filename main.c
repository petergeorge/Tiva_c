#include "SPI.h"

/* function prototype of SPI and Delay */
void SPI0_init(void);
void SPI0_Write(unsigned char data);
void SSI_send_char (uint32_t data);
void SSI_Receive_char (uint32_t * data);
uint8_t i=0;
uint32_t data[256];

unsigned char val1 = 'A';
unsigned char val2 = 'B';
/* Main routine of code */
int main(void)
{


    SSI_init();
    
    for (i = 0; i<255 ; i++)
    {
      data[i] = 0;
    }
    
    while(1)
    { 
    }
}



 void ISR_SSI_handler()
 {    
     SSI_Receive_char (&data[i]);
     SSI_send_char(val1+(i%2)); /* write a character */
     i++;
     ROM_SSIIntClear(SSI0_BASE,SSI_RXFF );
 }
