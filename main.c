#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "UART.h"
#include "ssi.h"
void vLedTask(void * para);
void vButtonTask (void * para);
void vUART_Task (void * para);
void vSSI_Task (void * para);



/* Define the strings that will be passed in as the task parameters. These are
defined const and not on the stack to ensure they remain valid when the tasks are
executing. */
//static const char *pcTextForTask1 = "\x1B[31m Task 1 is running\r\n";
//static const char *pcTextForTask2 = "\x1B[34m Task 2 is running\r\n";
xQueueHandle xqueue;
int main(void)
 {
    UART_init(); //job run one time
    SSI_init();
          xTaskCreate (vUART_Task, "UART",100, NULL ,1, NULL);
          xTaskCreate (vSSI_Task, "SSI",100, NULL ,2, NULL);
	
          vTaskStartScheduler();
          for(;;);

//	return 0;
}

void vUART_Task (void * para)
{
  for(;;)
  {
    UART_send_string ("welcome \n");
  }
}

void vSSI_Task (void * para)
{
  for(;;)
  {
    SSI_send_char ('c');
  }
}


