
//void SSI_send_string(uint8_t * string)
// {
//  uint8_t loop_index = 0;
//  while (string[loop_index] != '\0')
//  {
//    ROM_SSICharPut(SSI0_BASE,string[loop_index]);
//    loop_index++;
//  }
//  ROM_SSICharPut(SSI0_BASE,'\n');
// }
#include <stdbool.h>
#include <stdint.h>
#include "gpio.h"

int main()
{
  gpio_init(portf,GPIO_PIN_3,GPIO_DIR_MODE_OUT,GPIO_PIN_TYPE_STD);
  gpio_init(portf,GPIO_PIN_4,GPIO_DIR_MODE_IN,GPIO_PIN_TYPE_STD_WPU);
  gpio_init(portf,GPIO_PIN_0,GPIO_DIR_MODE_IN,GPIO_PIN_TYPE_STD_WPU);
  while (1)
  {
    if (high == GPIOPinRead(portf,GPIO_PIN_4))
    {
      GPIOPinWrite(portf, GPIO_PIN_3, high);
    }
    else
    {
      GPIOPinWrite(portf, GPIO_PIN_3, low);
    }
  }
  return 0;
}
