#include "main.h"

uint32_t SSI_tx_buffer [3] = {0};
uint32_t SSI_rx_buffer [3] = {0};


static void ssi_callout (boolean_t ssi_ret);

uint8_t var = 0;
uint32_t spi_rx_buffer [1024] = {0};
uint32_t spi_tx_buffer [1024] = {0};

int main(void)
 {
 uint16_t loop_index;
  pwm_init(SYSCTL_PERIPH_PWM1, SYSCTL_PERIPH_GPIOF, SYSCTL_PWMDIV_64);
  pwm_pin_config(GPIO_PORTF_BASE, GPIO_PF2_M1PWM6);
  pwm_ch_config(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN, 50000,14000, PWM_OUT_6);
  gpio_init(portf,GPIO_PIN_3,GPIO_DIR_MODE_OUT,GPIO_PIN_TYPE_STD);
  // gpio_init(portf,GPIO_PIN_2,GPIO_DIR_MODE_OUT,GPIO_PIN_TYPE_STD);
  gpio_init(portf,GPIO_PIN_1,GPIO_DIR_MODE_OUT,GPIO_PIN_TYPE_STD);
  gpio_init(portf,GPIO_PIN_4,GPIO_DIR_MODE_IN,GPIO_PIN_TYPE_STD_WPU);
  gpio_init(portf,GPIO_PIN_0,GPIO_DIR_MODE_IN,GPIO_PIN_TYPE_STD_WPU);
  for (loop_index = 0; loop_index <1024 ;loop_index++)
  {
	  spi_tx_buffer[loop_index] = loop_index;
  }
  SSI_init();
  SSI_Send_Receive_buffers (spi_rx_buffer, spi_tx_buffer, 1024, ssi_callout);
  
    debug_print("Init is done\n");

          xTaskCreate (vSSI_Task, "SSI",100, NULL ,2, NULL);
          xTaskCreate (gpio_readTask, "gpioRead",100, NULL ,2, NULL);
          xTaskCreate (vTaskPwm, "PwmWrite",100, NULL ,2, NULL);
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
  for(;;)
  {
    if(true == get_ssiFlagStatus())
    {
    	ssi_cyclic();
    }
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
    if (low == GPIOPinRead(portf,GPIO_PIN_4))
    {
      var = 1;
      GPIOPinWrite(portf, GPIO_PIN_1, low);
    }
    else
    {
      var = 0;
      ROM_PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, false);            //Enable PWM output channel 6
      GPIOPinWrite(portf, GPIO_PIN_1, high);
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

void vTaskPwm (void * para)
{
  for(;;)
  {
    if (1 == var)
    {
     ROM_PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);            //Enable PWM output channel 6
      vTaskDelay(100);
      var = 0;
    }
 } 
}


static void ssi_callout (boolean_t ssi_ret)
{
  if (ssi_ret == TRUE)
  {
    debug_print("ssi send receive completed suuccessfully \n");
  }
  else
  {
    debug_print("ssi send receive completed unsuuccessfully \n");
  }
}
