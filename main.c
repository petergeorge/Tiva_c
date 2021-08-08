#include "i2c.h"
 
int main()
{
   uint32_t data;

   InitI2C3();

   SYSCTL->RCGCGPIO |= 0x20;   // enable clock to GPIOF 
   GPIOF->LOCK = 0x4C4F434B;   // unlockGPIOCR register
   GPIOF->PUR |= 0x10;         // Enable Pull Up resistor PF4
   GPIOF->DIR |= 0x08;         // set PF1 as an output and PF4 as an input pin
   GPIOF->DEN |= 0x18;         // Enable PF1 and PF4 as a digital GPIO pins 

   I2CSlaveInit(I2C3_BASE,4);
   I2CSlaveEnable(I2C3_BASE); 
   while(1)
   {
     data = I2CSlaveDataGet(I2C3_BASE);
     printf("data: %d\n ",data);
     Delay_ms(500);
   }
  return 0;
}
