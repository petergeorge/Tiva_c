#include "ssi.h"
#include "TM4C123GH6PM.h"

static uint32_t *ssi_ptrDataRx = NULL;
static uint32_t *ssi_ptrDataTx = NULL;
static uint16_t ssi_dataBufferSize = U8ZERO;
static ssi_callcout_func_type ssi_callout_func = NULL;
static boolean_t spi_flag = false;

static void SSI_send_char (uint32_t data);

static void SSI_receive_char (uint32_t * data);

static void SSI_clear_interrupt_flag (void);

static void SSI_enable_interrupt (void);

static void SSI_disable_interrupt (void)

extern void SSI_init (void)
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
  ROM_SSIConfigSetExpClk(SSI0_BASE,ROM_SysCtlClockGet(),SSI_FRF_MOTO_MODE_0,SSI_MODE_SLAVE,F_SPI,8);
  /* for using interrupt */
  NVIC_SetPriorityGrouping(0);
  NVIC_EnableIRQ(SSI0_IRQn);
  NVIC_SetPriority(SSI0_IRQn,1);
  __asm("cpsie i");
  ROM_SSIIntEnable(SSI0_BASE,  SSI_RXFF);

  ROM_SSIEnable(SSI0_BASE);
}

static void SSI_send_char (uint32_t data)
{
    ROM_SSIDataPut(SSI0_BASE,data);
}

static void SSI_receive_char (uint32_t * data)
{
  ROM_SSIDataGet(SSI0_BASE, data);
}

extern void SSI_Send_Receive_buffers (uint32_t ulDataRx[],uint32_t ulDataTx[],uint8_t size, ssi_callcout_func_type ssi_callout)
{
  uint8_t loop_index = 0;
  if ((size <SSI_TX_RX_BUFFER_SIZE)&&(NULL != ulDataRx)&&(NULL != ulDataTx)&&(ssi_callout != NULL))
  {
	 ssi_ptrDataRx = ulDataRx;
	 ssi_ptrDataTx = ulDataTx;
	 ssi_dataBufferSize = size;
	 ssi_callout_func = ssi_callout;
  }
  else
  {
    /* error */
    debug_print("size error \n");
  }

}

static void SSI_clear_interrupt_flag (void)
{
  ROM_SSIIntDisable(SSI0_BASE,  SSI_RXFF);
}

static void SSI_enable_interrupt (void)
{
  ROM_SSIIntEnable(SSI0_BASE,  SSI_RXFF);
}

static void SSI_disable_interrupt (void)
{
  ROM_SSIIntDisable(SSI0_BASE,  SSI_RXFF);
}
extern void set_ssiFlagStatusTrue (void)
{
	spi_flag = true;
}
extern boolean_t get_ssiFlagStatus (void)
{
	return spi_flag;
}
extern void ISR_SSI_handler (void)
{
	spi_flag = true;
    SSI_clear_interrupt_flag();
}

extern void ssi_cyclic (void)
{
	static uint16_t current_size = 0;

	if (current_size < ssi_dataBufferSize)
	{
        SSI_receive_char(&ssi_ptrDataRx[size]);
        ssi_ptrDataRx[0] &= 0x000000FF;
        SSI_send_char(ulDataTx[size]);
        current_size++;
	}
	else
	{
        ssi_callout_func(E_OK);
		current_size = U8ZERO;
	}
}
