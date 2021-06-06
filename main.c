#include "SPI.h"

/* function prototype of SPI and Delay */
void SPI1_init(void);
void SPI1_Write(unsigned char data);
void Delay_ms(int time_ms); 

/* Main routine of code */
int main(void)
{
    unsigned char val1 = 'A';
    unsigned char val2 = 'B';

    SPI1_init();
    while(1)
		{              
    SPI1_Write(val1); /* write a character */
    Delay_ms(1000);
    SPI1_Write(val2); /* write a character */
    Delay_ms(1000);	
    }
}

void SPI1_Write(unsigned char data)
{
    GPIO_PORTA_DATA_R  &= ~(1<<2);       /* Make PF2 Selection line (SS) low */
    while((SSI0_SR_R & 2) == 0); /* wait untill Tx FIFO is not full */
    SSI0_DR_R = data;            /* transmit byte over SSI1Tx line */
    while(SSI0_SR_R & 0x10);     /* wait until transmit complete */
    GPIO_PORTA_DATA_R |= 0x04;        /* keep selection line (PF2) high in idle condition */
}

void SPI1_init(void)
{
    /* Enable clock to SPI1, GPIOD and GPIOF */
	
    SYSCTL_RCGCSSI_R |= (1<<0);   /*set clock enabling bit for SPI0 */
    SYSCTL_RCGCGPIO_R |= (1<<0); /* enable clock to GPIOA for SPI1 */
    SYSCTL_RCGCGPIO_R |= (1<<0); /* enable clock to GPIOA for slave select */

    /*Initialize pins for SPI0 alternate function*/
	
    GPIO_PORTA_AMSEL_R &= ~0xFF;      /* disable analog functionality PA2:PA5 */
    GPIO_PORTA_DEN_R |= 0x3C;         /* Set PA2:PA5 as digital pin */
    GPIO_PORTA_AFSEL_R |= 0x3C;       /* enable alternate function of PA2:PA5*/
    GPIO_PORTA_PCTL_R &= ~0x00FFFF00; /* assign PA2:PA5 pins to PA2:PA5 */
    GPIO_PORTA_PCTL_R |= 0x00222200;  /* assign PA2:PA5 pins to PA2:PA5  */
    
    /* Initialize PF2 as a digital output as a slave select pin 
	
    GPIO_PORTA_DEN_R |= (1<<2);         /* set PF2 pin digital 
    GPIO_PORTA_DIR_R |= (1<<2);         /* set PF2 pin output 
    GPIO_PORTA_DATA_R |= (1<<2);        /* keep SS idle high */

    /* Select SPI0 as a Master, POL = 0, PHA = 0, clock = 4 MHz, 8 bit data */
		
    SSI0_CR1_R = 0;          /* disable SPI1 and configure it as a Master */
    SSI0_CC_R = 0;           /* Enable System clock Option */
    SSI0_CPSR_R = 4;         /* Select prescaler value of 4 .i.e 16MHz/4 = 4MHz */
    SSI0_CR0_R = 0x00007;     /* 4MHz SPI0 clock, SPI mode, 8 bit data */
    SSI0_CR1_R |= 2;         /* enable SPI0 */
}

/* This function generates delay in ms */
/* calculations are based on 16MHz system clock frequency */

void Delay_ms(int time_ms)
{
    int i, j;
    for(i = 0 ; i < time_ms; i++)
        for(j = 0; j < 3180; j++)
            {}  /* excute NOP for 1ms */
}
 void ISR_SSI_handler()
 {
   
 }
