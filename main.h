#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "UART.h"
#include "ssi.h"
#include "I2C.h"
#include "gpio.h"
#include "pwm_functions.h"

// #define debug
#ifdef debug
#define debug_print(x)                 printf(x)
#else
#define debug_print(x) 
#endif

void vSSI_Task (void * para);

void gpio_readTask (void * para);

void vTaskPwm (void * para);