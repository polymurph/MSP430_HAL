/*
 * hal_gpio.h
 *
 *  Created on: 25.11.2019
 *      Author: stephanblaettler
 *      TEST TEST
 *      testest
 */

#ifndef HAL_HAL_GPIO_H_
#define HAL_HAL_GPIO_H_

#include <stdint.h>
#include <stdbool.h>
#include "msp430fr6989.h"


typedef enum{
    pin_mode_INPUT,
    pin_mode_INPUT_PULLDOWN,
    pin_mode_INPUT_PULLUP,
    pin_mode_OUTPUT,
    // gpio_mode_OUTPUT_PULLUP // weak pull up/down instead of source
    pin_mode_PRIMARY_FUNCTION,
    pin_mode_SECCONDARY_FUNCTION,
    pin_mode_TERTIARY_FUNCTION
    
}pin_mode_t;


void hal_gpio_pin_init(pin_mode_t mode,);

void hal_gpio_pin_set(pin,bool logic_level);

void hal_gpio_pin_get();


#endif /* HAL_HAL_GPIO_H_ */
