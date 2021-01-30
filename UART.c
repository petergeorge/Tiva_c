#include "UART.h"





void UART_init (void)
{
// 1. Enable the UART module using the RCGCUART register (see page 342).
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
// 2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register (see page 338).
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
// To find out which GPIO port to enable, refer to Table 23-5 on page 1344.
// 3. Set the GPIO AFSEL bits for the appropriate pins (see page 668). To determine which GPIOs to
// configure, see Table 23-4 on page 1337.

ROM_GPIOPinTypeUART(GPIO_PORTA_BASE,2);
ROM_GPIOPinTypeUART(GPIO_PORTA_BASE,1);
// 4. Configure the GPIO current level and/or slew rate as specified for the mode selected (see
// page 670 and page 678).
// 5. Configure the PMCn fields in the GPIOPCTL register to assign the UART signals to the appropriate
ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
ROM_GPIOPinConfigure(GPIO_PA1_U0TX);

//1. Disable the UART by clearing the UARTEN bit in the UARTCTL register.
ROM_UARTDisable(UART0_BASE);
//2. Write the integer portion of the BRD to the UARTIBRD register.
//3. Write the fractional portion of the BRD to the UARTFBRD register.
ROM_UARTConfigSetExpClk(UART0_BASE, 80000000UL, 115200UL, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
//4. Write the desired serial parameters to the UARTLCRH register (in this case, a value of
//0x0000.0060).
//5. Configure the UART clock source by writing to the UARTCC register.
//6. Optionally, configure the ?DMA channel (see �Micro Direct Memory Access (?DMA)� on page 583)
//and enable the DMA option(s) in the UARTDMACTL register.
//7. Enable the UART by setting the UARTEN bit in the UARTCTL register.
ROM_UARTEnable(UART0_BASE);
}

void UART_send_string (uint8_t * string)
{
  uint8_t loop_index = 0;
  while (string[loop_index] != '\0')
  {
    UART_send_char(string[loop_index]);
    loop_index++;
  }
  UART_send_char('\n');
}

void UART_send_char (unsigned char data)
{
    ROM_UARTCharPut(UART0_BASE,data);
}