#include "I2C.h"

int main(void)
{
   uint8_t data[2] = {0x01,0x02};
   InitI2C0();
   SYSCTL->RCGCGPIO |= 0x20;   // enable clock to GPIOF 
   GPIOF->LOCK = 0x4C4F434B;   // unlockGPIOCR register
   GPIOF->PUR |= 0x10;         // Enable Pull Up resistor PF4
   GPIOF->DIR |= 0x08;         // set PF1 as an output and PF4 as an input pin
   GPIOF->DEN |= 0x18;         // Enable PF1 and PF4 as a digital GPIO pins 
   ROM_I2CMasterEnable(I2C3_BASE);
   while (1)
   {
     unsigned int value = GPIOF->DATA;
     value = value >> 1;
     GPIOF->DATA = value;	
     ROM_I2CMasterSlaveAddrSet(I2C3_BASE,4,false);
     if(value & (5<<1))
     {
     ROM_I2CMasterDataPut(I2C3_BASE,data[1]);
     ROM_I2CMasterControl(I2C3_BASE,I2C_MASTER_CMD_SINGLE_SEND);
     }
     else 
     {
     ROM_I2CMasterDataPut(I2C3_BASE,data[0]);
     ROM_I2CMasterControl(I2C3_BASE,I2C_MASTER_CMD_SINGLE_SEND);
     }
   }
	
}



