/*
 * I2C.c
 *
 *  Created on: Feb 3, 2021
 *      Author: Peter
 */


#include "I2C.h"

/**********************************************************************/
//initialize I2C module 0
//Slightly modified version of TI's example code
void InitI2C0(void)
{
    //enable I2C module 0
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C3);

    //enable GPIO peripheral that contains I2C 0
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    // Configure the pin muxing for I2C0 functions on port B2 and B3.
    ROM_GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_0);
    ROM_GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_1);
    
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

//sends an I2C command to the specified slave
void I2CSend(uint8_t slave_addr, uint8_t num_of_args, ...)
{
    uint8_t i = 0;
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.
    ROM_I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);

    //stores list of variable number of arguments
    va_list vargs;

    //specifies the va_list to "open" and the last fixed argument
    //so vargs knows where to start looking
    va_start(vargs, num_of_args);

    //put data to be sent into FIFO
    ROM_I2CMasterDataPut(I2C0_BASE, va_arg(vargs, uint32_t));

    //if there is only one argument, we only need to use the
    //single send I2C function
    if(num_of_args == 1)
    {
        //Initiate send of data from the MCU
        ROM_I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

        // Wait until MCU is done transferring.
        while(ROM_I2CMasterBusy(I2C0_BASE));

        //"close" variable argument list
        va_end(vargs);
    }

    //otherwise, we start transmission of multiple bytes on the
    //I2C bus
    else
    {
        //Initiate send of data from the MCU
        ROM_I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

        // Wait until MCU is done transferring.
        while(ROM_I2CMasterBusy(I2C0_BASE));

        //send num_of_args-2 pieces of data, using the
        //BURST_SEND_CONT command of the I2C module
        for(i = 1; i < (num_of_args - 1); i++)
        {
            //put next piece of data into I2C FIFO
            ROM_I2CMasterDataPut(I2C0_BASE, va_arg(vargs, uint32_t));
            //send next data that was just placed into FIFO
            ROM_I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

            // Wait until MCU is done transferring.
            while(ROM_I2CMasterBusy(I2C0_BASE));
        }

        //put last piece of data into I2C FIFO
        ROM_I2CMasterDataPut(I2C0_BASE, va_arg(vargs, uint32_t));
        //send next data that was just placed into FIFO
        ROM_I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
        // Wait until MCU is done transferring.
        while(ROM_I2CMasterBusy(I2C0_BASE));

        //"close" variable args list
        va_end(vargs);
    }
}

//sends an array of data via I2C to the specified slave
void I2CSendString(uint32_t slave_addr, char array[])
{
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.
    ROM_I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);

    //put data to be sent into FIFO
    ROM_I2CMasterDataPut(I2C0_BASE, array[0]);

    //if there is only one argument, we only need to use the
    //single send I2C function
    if(array[1] == '\0')
    {
        //Initiate send of data from the MCU
        ROM_I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

        // Wait until MCU is done transferring.
        while(ROM_I2CMasterBusy(I2C0_BASE));
    }

    //otherwise, we start transmission of multiple bytes on the
    //I2C bus
    else
    {
        //Initiate send of data from the MCU
        ROM_I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

        // Wait until MCU is done transferring.
        while(ROM_I2CMasterBusy(I2C0_BASE));

        //initialize index into array
        uint8_t i = 1;

        //send num_of_args-2 pieces of data, using the
        //BURST_SEND_CONT command of the I2C module
        while(array[i + 1] != '\0')
        {
            //put next piece of data into I2C FIFO
            ROM_I2CMasterDataPut(I2C0_BASE, array[i++]);

            //send next data that was just placed into FIFO
            ROM_I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

            // Wait until MCU is done transferring.
            while(ROM_I2CMasterBusy(I2C0_BASE));
        }

        //put last piece of data into I2C FIFO
        ROM_I2CMasterDataPut(I2C0_BASE, array[i]);

        //send next data that was just placed into FIFO
        ROM_I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);

        // Wait until MCU is done transferring.
        while(ROM_I2CMasterBusy(I2C0_BASE));
    }
}

//read specified register on slave device
uint32_t I2CReceive(uint32_t slave_addr)
{
    //specify that we are writing (a register address) to the
    //slave device
    ROM_I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);
/*
 * for accelemoter usage
    //specify register to be read
    I2CMasterDataPut(I2C0_BASE, reg);
*/
    //send control byte and register address byte to slave device
    ROM_I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

    //wait for MCU to finish transaction
    while(ROM_I2CMasterBusy(I2C0_BASE));

    //specify that we are going to read from slave device
    ROM_I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, true);

    //send control byte and read from the register we
    //specified
    ROM_I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

    //wait for MCU to finish transaction
    while(ROM_I2CMasterBusy(I2C0_BASE));

    //return data pulled from the specified register
    return ROM_I2CMasterDataGet(I2C0_BASE);
}
