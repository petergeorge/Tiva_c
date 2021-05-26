#include "pwm_functions.h"

/* Clock setting for PWM and GPIO PORT */
void pwm_init(unsigned int pwm_module, unsigned int port, unsigned int divisor)
{
  ROM_SysCtlPeripheralEnable(pwm_module);                //Enable clock to PWM module
  ROM_SysCtlPeripheralEnable(port);               //Enable clock to PORT
  ROM_SysCtlPWMClockSet(divisor);                 //Enable System Clock Divisor function
}

/* Setting of PF2 pin for M1PWM6 channel output pin */
void pwm_pin_config(unsigned int port, unsigned int pin)
{
  ROM_GPIOPinConfigure(pin);              //Set the alternate function for PF2 as PWM output(pinmux)
  ROM_GPIOPinTypePWM(port,pin);           //Make PF2 as Output(pin configure; DEN&Output)
}

/*PWM channel  setting */
void pwm_ch_config(unsigned int pwm_module, unsigned int gen, unsigned int mode, unsigned int period,unsigned int duty,
                   unsigned int pwm_output)
{
  ROM_PWMGenDisable(pwm_module, gen);                                  //Disable PWM Generator 
  ROM_PWMGenConfigure(pwm_module,gen,mode);                            //select down count mode of counter 3
  ROM_PWMGenPeriodSet(pwm_module,gen,period);                          //set load value of Generator frequency
  ROM_PWMPulseWidthSet(pwm_module,pwm_output,duty);                    //set duty cyle
  ROM_PWMGenEnable(pwm_module, gen);                                   //Enable PWM Generator
}

  
 



