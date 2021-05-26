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

void pwm_init(unsigned int module, unsigned int port, unsigned int divisor);
void pwm_pin_config(unsigned int port, unsigned int pin);
void pwm_ch_config(unsigned int pwm_module, unsigned int gen, unsigned int mode, unsigned int period,unsigned int duty,
                   unsigned int pwm_output);
