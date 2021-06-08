#include "SPI.h"
void SSI_init (void)
{
//1. Enable the SSI module using the RCGCSSI register (see page 344).
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);                                                       //enable SSI Module 0     address 0x400FE61C for all SSI modules(page 344)
//2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register (see page 338).
//To find out which GPIO port to enable, refer to Table 23-5 on page 1344.
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);                                                      //enable General-Purpose Input/Output(GPIO)(page 338)   address 0x400FE608 for all Ports
//3. Set the GPIO AFSEL bits for the appropriate pins (see page 668). To determine which GPIOs to
//configure, see Table 23-4 on page 1337.
ROM_GPIOPinTypeSSI(GPIO_PORTA_BASE,0x3c);
//4. Configure the PMCn fields in the GPIOPCTL register to assign the SSI signals to the appropriate
//pins. See page 685 and Table 23-5 on page 1344.
  
  ROM_GPIOPinConfigure(GPIO_PA2_SSI0CLK );
  ROM_GPIOPinConfigure(GPIO_PA3_SSI0FSS );
  ROM_GPIOPinConfigure(GPIO_PA4_SSI0RX );
  ROM_GPIOPinConfigure(GPIO_PA5_SSI0TX );
  
//5. Set the clock
  ROM_SSIClockSourceSet(SSI0_BASE,SSI_CLOCK_SYSTEM);

//6. sets the SSI protocol, mode of operation, bit rate, and data width
  //ROM_SSIConfigSetExpClk(SSI0_BASE,120000000,SSI_FRF_MOTO_MODE_0,SSI_MODE_MASTER,F_SPI,8);
  ROM_SSIConfigSetExpClk(SSI0_BASE,ROM_SysCtlClockGet(),SSI_FRF_MOTO_MODE_1,SSI_MODE_MASTER,4000000,8);
  ROM_SSIEnable(SSI0_BASE);
}

void SSI_send_char (uint32_t data)
{
  //data &= 0x000000ff;
    ROM_SSIDataPut(SSI0_BASE,data);
    while(ROM_SSIBusy(SSI0_BASE));
}
void SSI_Receive_char (uint32_t * data)
{
    ROM_SSIDataGet (SSI0_BASE, data);
    *data &= 0x00ff;
}

  