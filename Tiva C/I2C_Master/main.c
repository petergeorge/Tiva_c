#include "I2C.h"

int main(void)
{
  char data[2] = {0x01,0x02};
   I2C3_Init();
   SYSCTL->RCGCGPIO |= 0x20;   // enable clock to GPIOF 
   GPIOF->LOCK = 0x4C4F434B;   // unlockGPIOCR register
   GPIOF->PUR |= 0x10;         // Enable Pull Up resistor PF4
   GPIOF->DIR |= 0x08;         // set PF1 as an output and PF4 as an input pin
   GPIOF->DEN |= 0x18;         // Enable PF1 and PF4 as a digital GPIO pins 

   while (1)
   {
     unsigned int value = GPIOF->DATA;
     value = value >> 1;
     GPIOF->DATA = value;	
     if(value & (5<<1))
        I2C3_Write_Multiple(4, 0, 1, &data[1]);
	else 
	    I2C3_Write_Multiple(4, 0, 1, &data[0]); 
   }
	
}



