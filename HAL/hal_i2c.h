/*
 * hal_i2c.h
 *
 *  Created on: Nov 13, 2019
 *      Author: Edwin Koch
 */

#ifndef HAL_HAL_I2C_H_
#define HAL_HAL_I2C_H_

#include <stdint.h>
#include <stdbool.h>

#include "msp430fr6989.h"

typedef enum{
    i2c_mode_MASTER,
    i2c_mode_SLAVE
}i2c_mode_t;

typedef enum{
    i2c_clk_src_
}i2c_clk_src_t;

typedef enum{
    i2c_clk_rate_
}i2c_clk_rate_t;

void hal_i2c_init(i2c_mode_t mode);



#endif /* HAL_HAL_I2C_H_ */
