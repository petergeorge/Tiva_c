void InitI2C0(void)
{
    //enable I2C module 0
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C3);

    //reset module
    //ROM_SysCtlPeripheralReset(SYSCTL_PERIPH_I2C3);

    //enable GPIO peripheral that contains I2C 0
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOD->DEN |= 0x03; // Assert DEN for port D
    // Configure the pin muxing for I2C0 functions on port B2 and B3.
   //ROM_GPIOPinConfigure(GPIO_PD0_I2C3SCL);
   //ROM_GPIOPinConfigure(GPIO_PD1_I2C3SDA);

    // Select the I2C function for these pins.
    ROM_GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);
    ROM_GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_1);

    // Enable and initialize the I2C0 master module.  Use the system clock for
    // the I2C0 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.
    ROM_I2CMasterInitExpClk(I2C3_BASE, ROM_SysCtlClockGet(), false);

    //clear I2C FIFOs
    HWREG(I2C3_BASE + I2C_O_FIFOCTL) = 80008000;
#ifdef loop_back_enable
    HWREG(I2C3_BASE + I2C_O_MCR) |= (1u<<0); // enable loop back
#endif 
    //debug_print("I2C is ready \n");  

}