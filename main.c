
#include "pwm_functions.h"

int main()
{
  
  
  /* Clock setting for PWM and GPIO PORT */
  /* Enable Clock for PWM1 Module  with devisor and Port F */
  pwm_init(SYSCTL_PERIPH_PWM1, SYSCTL_PERIPH_GPIOF, SYSCTL_PWMDIV_64);
  
  /* Configure Port pin alternate function*/
  /* Setting of PF2 pin for M1PWM6 channel output pin */
  pwm_pin_config(GPIO_PORTF_BASE, GPIO_PF2_M1PWM6);
  
  /*PWM1 channel 6 setting */
  /* Configure PWM_Module, Generator, Mode, Period, Duty & PWM Channel*/
  pwm_ch_config(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN, 50000,14000, PWM_OUT_6);
  
  ROM_PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);            //Enable PWM output channel 6
  
  while(1)
  {
  }
  
  return 0;
}
