
#include "i2c.h"

/**********************************************************************/
//initialize I2C module 3
//Slightly modified version of TI's example code
void InitI2C3(void)
{
    //enable I2C module 0
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C3);

    //reset module
    //ROM_SysCtlPeripheralReset(SYSCTL_PERIPH_I2C3);

    //enable GPIO peripheral that contains I2C 0
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    // Configure the pin muxing for I2C0 functions on port B2 and B3.
    ROM_GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_0);
    ROM_GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_1);
    //GPIOD->ODR |= 0x00000002 ; // SDA (PD1 ) pin as open darin
    //ROM_GPIOPinTypeGPIOOutputOD (GPIO_PORTD_BASE,GPIO_PD1_I2C3SDA | GPIO_PIN_1);
    ROM_GPIOPinConfigure(GPIO_PD0_I2C3SCL);
    ROM_GPIOPinConfigure(GPIO_PD1_I2C3SDA);

    // Select the I2C function for these pins.
    ROM_GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);
    

    // Enable and initialize the I2C0 master module.  Use the system clock for
    // the I2C0 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.
    ROM_I2CMasterInitExpClk(I2C3_BASE, ROM_SysCtlClockGet(), false);

    //clear I2C FIFOs
    HWREG(I2C3_BASE + I2C_O_FIFOCTL) = 80008000;
#ifdef loop_back_enable
    //HWREG(I2C3_BASE + I2C_O_MCR) |= (1u<<0); // enable loop back
#endif 
    //debug_print("I2C is ready \n");  

}

void
I2CSlaveEnable(uint32_t ui32Base)
{
    //
    // Enable the clock to the slave block.
    //
    HWREG(ui32Base + I2C_O_MCR) |= I2C_MCR_SFE;

    //
    // Enable the slave.
    //
    HWREG(ui32Base + I2C_O_SCSR) = I2C_SCSR_DA;
}

void I2CSlaveInit(uint32_t ui32Base, uint8_t ui8SlaveAddr)
{
    //
    // Must enable the device before doing anything else.
    //
    I2CSlaveEnable(ui32Base);

    //
    // Set up the slave address.
    //
    HWREG(ui32Base + I2C_O_SOAR) = ui8SlaveAddr;
}

void I2CSlaveDataPut(uint32_t ui32Base, uint8_t ui8Data)
{
    //
    // Write the byte.
    //
    HWREG(ui32Base + I2C_O_SDR) = ui8Data;
}

uint32_t
I2CSlaveDataGet(uint32_t ui32Base)
{
    //
    // Read a byte.
    //
    return(HWREG(ui32Base + I2C_O_SDR));
}

void Delay_ms(int time_ms)
{
    int i, j;
    for(i = 0 ; i < time_ms; i++)
        for(j = 0; j < 3180; j++)
            {}  /* excute NOP for 1ms */
}