

#define TARGET_IS_TM4C123_RB1
#define PART_TM4C123GH6PM

#include <stdbool.h>
#include <stdint.h>
#include "rom.h"
#include "sysctl.h"
#include "pin_map.h"
#include "hw_memmap.h"
#include "pwm.h"
#include "gpio.h"
#include "TM4C123GH6PM.h"



int main()
{
  /* Clock setting for PWM and GPIO PORT */
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);        //Enable clock to PWM1 module
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);       //Enable clock to PORTF
  ROM_SysCtlPWMClockSet(SYSCTL_PWMDIV_64);               //Enable System Clock Divisor function
  
  /* Setting of PF2 pin for M1PWM6 channel output pin */
  ROM_GPIOPinConfigure(GPIO_PF2_M1PWM6);                 //Set the alternate function for PF2 as PWM output(pinmux)
  ROM_GPIOPinTypePWM(GPIO_PORTF_BASE,GPIO_PF2_M1PWM6);   //Make PF2 as Output(pin configure; DEN&Output)
  
  
  /*PWM1 channel 6 setting */
  ROM_PWMGenDisable(PWM1_BASE, PWM_GEN_3);
  ROM_PWMGenConfigure(PWM1_BASE,PWM_GEN_3,PWM_GEN_MODE_DOWN);
  ROM_PWMGenPeriodSet(PWM1_BASE,PWM_GEN_3,30000);
  ROM_PWMPulseWidthSet(PWM1_BASE,PWM_OUT_6,14000);
  ROM_PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true); // Enable PWM output channel 6
  ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_3);
  
  while(1)
  {
  }
  
  return 0;
}
