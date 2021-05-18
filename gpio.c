
#include "gpio.h"

static uint32_t gpio_get_base_address (uint32_t ui32Port);

void gpio_init (gpio_port_t port,uint8_t  pin, uint32_t dir)
{
    uint32_t port_base_address = 0x00;
    switch (port)
    {
    case porta:
    {
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
        port_base_address = GPIO_PORTA_BASE;
    }
    break;

    case portb:
    {
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); 
        port_base_address = GPIO_PORTB_BASE;
    }
    break;

    case portc:
    {
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC); 
        port_base_address = GPIO_PORTC_BASE;
    }
    break;

    case portd:
    {
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
        port_base_address = GPIO_PORTD_BASE;
    }
    break;

    case porte:
    {
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        port_base_address = GPIO_PORTE_BASE;
    }
    break;

    case portf:
    {
        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        port_base_address = GPIO_PORTF_BASE;
    }
    break;

    default:
        /* handle incorrect gpio port */
        break;
    } 
    ROM_GPIODirModeSet(port_base_address,pin,dir); 
    ROM_GPIOPadConfigSet(port_base_address, pin, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
}

void GPIOPinWrite(uint32_t ui32Port, uint8_t ui8Pins, gpio_value_t ui8Val)
{
    uint32_t port_address = 0x00;
    uint8_t out_val = 0x00;

    port_address = gpio_get_base_address(ui32Port);

    switch (ui8Val)
    {

    case low:
    {
        out_val = 0x00;
    }
        break;

    case high:
    {
        out_val = (uint8_t)ui8Pins;
    }
        break;

    default:
         break;

    }
    ROM_GPIOPinWrite(port_address,ui8Pins,out_val);
}

volatile int32_t ret_val = 0x00;

gpio_value_t GPIOPinRead(uint32_t ui32Port, uint8_t ui8Pins)
{
    uint32_t port_address = 0x00;
    
    gpio_value_t pin_val = low;

    port_address = gpio_get_base_address(ui32Port);

    ret_val = ROM_GPIOPinRead (port_address,ui8Pins);
    if (ret_val == ui8Pins)
    {
        pin_val = high;
    }
    else if (ret_val == 0)
    {
        pin_val = low ;
    }
    else
    {
        while (1);
    }
    return pin_val;
}

static uint32_t gpio_get_base_address (uint32_t ui32Port)
{
    uint32_t port_address = 0x00;

    switch (ui32Port)
    {
    case porta:
        {
            port_address = GPIO_PORTA_BASE;
        }
        break;

    case portb:
        {
            port_address = GPIO_PORTB_BASE;
        }
        break;

    case portc:
        {
            port_address = GPIO_PORTC_BASE;
        }
        break;

    case portd:
        {
            port_address = GPIO_PORTD_BASE;
        }
        break;

    case porte:
        {
            port_address = GPIO_PORTE_BASE;
        }
        break;

    case portf:
        {
            port_address = GPIO_PORTF_BASE;
        }
        break;
    default:
        break;
    }
    return port_address ; 
}
