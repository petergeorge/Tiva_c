#include "I2C.h"

// Function prototypes initialize, tranmit and rea functions 
void I2C3_Init ( void );  
char I2C3_Write_Multiple(int slave_address, char slave_memory_address, int bytes_count, char* data);
char I2C3_read_Multiple(int slave_address, char slave_memory_address, int bytes_count, char* data);

int main(void)
{
	 char data[2] = {0x01,0x02};
	 I2C3_Init();
	 SYSCTL->RCGCGPIO |= 0x20;   /* enable clock to GPIOF */
   GPIOF->LOCK = 0x4C4F434B;   // unlockGPIOCR register
   GPIOF->PUR |= 0x10;        // Enable Pull Up resistor PF4
   GPIOF->DIR |= 0x08;          //set PF1 as an output and PF4 as an input pin
   GPIOF->DEN |= 0x18;         // Enable PF1 and PF4 as a digital GPIO pins 

	while (1)
	{
    unsigned int	value = GPIOF->DATA;
		value = value >> 1;
		GPIOF->DATA = value;	
		if(value & (5<<1))
    I2C3_Write_Multiple(4, 0, 1, &data[1]);
		else 
		I2C3_Write_Multiple(4, 0, 1, &data[0]);
	  
	}
	
}
// I2C intialization and GPIO alternate function configuration
void I2C3_Init ( void )
{
SYSCTL->RCGCGPIO  |= 0x00000008 ; // Enable the clock for port D
SYSCTL->RCGCI2C   |= 0x00000008 ; // Enable the clock for I2C 3
GPIOD->DEN |= 0x03; // Assert DEN for port D
// Configure Port D pins 0 and 1 as I2C 3
GPIOD->AFSEL |= 0x00000003 ;
GPIOD->PCTL |= 0x00000033 ;
GPIOD->ODR |= 0x00000002 ; // SDA (PD1 ) pin as open darin
I2C3->MCR  = 0x0010 ; // Enable I2C 3 master function
/* Configure I2C 3 clock frequency
(1 + TIME_PERIOD ) = SYS_CLK /(2*
( SCL_LP + SCL_HP ) * I2C_CLK_Freq )
TIME_PERIOD = 16 ,000 ,000/(2(6+4) *100000) - 1 = 7 */
I2C3->MTPR  = 0x07 ;
}
/* wait untill I2C Master module is busy */
/*  and if not busy and no error return 0 */
static int I2C_wait_till_done(void)
{
    while(I2C3->MCS & 1);   /* wait until I2C master is not busy */
    return I2C3->MCS & 0xE; /* return I2C error code, 0 if no error*/
}
// Receive one byte of data from I2C slave device
char I2C3_Write_Multiple(int slave_address, char slave_memory_address, int bytes_count, char* data)
{   
    char error;
    if (bytes_count <= 0)
        return -1;                  /* no write was performed */
    /* send slave address and starting address */
    I2C3->MSA = slave_address << 1;
    I2C3->MDR = slave_memory_address;
    I2C3->MCS = 3;                  /* S-(saddr+w)-ACK-maddr-ACK */

    error = I2C_wait_till_done();   /* wait until write is complete */
    if (error) return error;

    /* send data one byte at a time */
    while (bytes_count > 1)
    {
        I2C3->MDR = *data++;             /* write the next byte */
        I2C3->MCS = 1;                   /* -data-ACK- */
        error = I2C_wait_till_done();
        if (error) return error;
        bytes_count--;
    }
    
    /* send last byte and a STOP */
    I2C3->MDR = *data++;                 /* write the last byte */
    I2C3->MCS = 5;                       /* -data-ACK-P */
    error = I2C_wait_till_done();
    while(I2C3->MCS & 0x40);             /* wait until bus is not busy */
    if (error) return error;
    return 0;       /* no error */
}

