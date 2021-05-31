#include "main.h"

uint32_t SSI_tx_buffer [3] = {0};
uint32_t SSI_rx_buffer [3] = {0};


xQueueHandle xqueue;

uint8_t var = 0;
uint8_t spi_flag = 0;
uint32_t spi_rx_buffer [256] = {0};

int main(void)
 {

  gpio_init(portf,GPIO_PIN_3,GPIO_DIR_MODE_OUT,GPIO_PIN_TYPE_STD);
  gpio_init(portf,GPIO_PIN_2,GPIO_DIR_MODE_OUT,GPIO_PIN_TYPE_STD);
  gpio_init(portf,GPIO_PIN_1,GPIO_DIR_MODE_OUT,GPIO_PIN_TYPE_STD);
  gpio_init(portf,GPIO_PIN_4,GPIO_DIR_MODE_IN,GPIO_PIN_TYPE_STD_WPU);
  gpio_init(portf,GPIO_PIN_0,GPIO_DIR_MODE_IN,GPIO_PIN_TYPE_STD_WPU);
  SSI_init();
  
    debug_print("Init is done\n");
          //xTaskCreate (vUART_Task, "UART",100, NULL ,1, NULL);

          xTaskCreate (vSSI_Task, "SSI",100, NULL ,2, NULL);

          //xTaskCreate (vI2C_Task, "I2C",100, NULL ,3, NULL);
          xTaskCreate (gpio_readTask, "gpioRead",100, NULL ,2, NULL);
          xTaskCreate (gpio_writeTask, "GpioWrite",100, NULL ,2, NULL);
          debug_print("tasks created successfully\n");
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
  uint8_t loop_index = 0;
  for(;;)
  {
    if(spi_flag == 1)
    {
      SSI_receive_char(&spi_rx_buffer[loop_index]);
      spi_rx_buffer[loop_index++] &= 0x00FF;
      GPIOPinWrite(portf, GPIO_PIN_2, low);
      GPIOPinWrite(portf, GPIO_PIN_3, low);
      GPIOPinWrite(portf, GPIO_PIN_1, high);
    } 
    debug_print("SSI task is running\n");
  }
}

void vI2C_Task (void * para)
{
  for(;;)
  {
    I2CSendString (0x301,"welcoeme to mr I2C\n");
    debug_print("I2C task is running\n");
  }
}


void gpio_readTask (void * para)
{
  for (;;)
  {
    if (high == GPIOPinRead(portf,GPIO_PIN_4))
    {
      var = 1;
       GPIOPinWrite(portf, GPIO_PIN_2, low);
    }
    else
    {
      var = 0;
       GPIOPinWrite(portf, GPIO_PIN_2, high);
       GPIOPinWrite(portf, GPIO_PIN_3, low);
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

    }
  }
}

void ISR_SSI_handler (void)
{
  spi_flag = 1;
  SSI_clear_interrupt_flag();
}