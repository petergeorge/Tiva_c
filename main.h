#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "UART.h"
#include "ssi.h"
#include "I2C.h"
#include "gpio.h"

#define debug

void vLedTask(void * para);
void vButtonTask (void * para);
void vUART_Task (void * para);
void vSSI_Task (void * para);
void vI2C_Task (void * para);

void gpio_readTask (void * para);

void gpio_writeTask (void * para);