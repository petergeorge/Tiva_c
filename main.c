#include "main.h"

uint32_t SSI_tx_buffer [3] = {0};
uint32_t SSI_rx_buffer [3] = {0};


xQueueHandle xqueue;

uint8_t var = 0;

int main(void)
 {
    // UART_init(); //job run one time
    // SSI_init();
    // InitI2C0();

  gpio_init(portf,GPIO_PIN_3,GPIO_DIR_MODE_OUT,GPIO_PIN_TYPE_STD);
  gpio_init(portf,GPIO_PIN_2,GPIO_DIR_MODE_OUT,GPIO_PIN_TYPE_STD);
  gpio_init(portf,GPIO_PIN_1,GPIO_DIR_MODE_OUT,GPIO_PIN_TYPE_STD);
  gpio_init(portf,GPIO_PIN_4,GPIO_DIR_MODE_IN,GPIO_PIN_TYPE_STD_WPU);
  gpio_init(portf,GPIO_PIN_0,GPIO_DIR_MODE_IN,GPIO_PIN_TYPE_STD_WPU);
  
#ifdef debug
    printf("Init is done\n");
#endif
          //xTaskCreate (vUART_Task, "UART",100, NULL ,1, NULL);

          //xTaskCreate (vSSI_Task, "SSI",100, NULL ,2, NULL);

          //xTaskCreate (vI2C_Task, "I2C",100, NULL ,3, NULL);
          xTaskCreate (gpio_readTask, "gpioRead",100, NULL ,2, NULL);
          xTaskCreate (gpio_writeTask, "GpioWrite",100, NULL ,2, NULL);
#ifdef debug
    printf("tasks created successfully\n");
#endif
          vTaskStartScheduler();
          for(;;);

}

void vUART_Task (void * para)
{
  for(;;)
  {
    UART_send_string ("welcome \r\n");
  }
}

void vSSI_Task (void * para)
{
  for(;;)
  {
    SSI_Send_Receive_buffers (SSI_rx_buffer,SSI_tx_buffer,3);
#ifdef debug
    printf("SSI task is running\n");
#endif
  }
}

void vI2C_Task (void * para)
{
  for(;;)
  {
    I2CSendString (0x301,"welcoeme to mr I2C\n");
#ifdef debug
    printf("I2C task is running\n");
#endif
  }
}


void gpio_readTask (void * para)
{
  for (;;)
  {
    if (high == GPIOPinRead(portf,GPIO_PIN_4))
    {
      var = 1;
       GPIOPinWrite(portf, GPIO_PIN_2, high);
    }
    else
    {
      var = 0;
       GPIOPinWrite(portf, GPIO_PIN_2, low);
    }
  }
}

void gpio_writeTask (void * para)
{
  for (;;)
  {
    if (1 == var)
    {
      GPIOPinWrite(portf, GPIO_PIN_3, high);
      vTaskDelay(100);
      var = 0;
    }
    else
    {
      GPIOPinWrite(portf, GPIO_PIN_3, low);
    }
  }
}