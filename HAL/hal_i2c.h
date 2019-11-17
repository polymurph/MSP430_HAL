/*
 * hal_i2c.h
 *
 *  Created on: Nov 13, 2019
 *      Author: Edwin Koch
 */


// TODO: implement slave functionalities
// TODO: add a error handling system
// TODO: add polling time out functionality

#ifndef HAL_HAL_I2C_H_
#define HAL_HAL_I2C_H_

#include <stdint.h>
#include <stdbool.h>

#include "msp430fr6989.h"

typedef enum{
    i2c_mode_MASTER = UCMST,
    i2c_mode_SLAVE = 0
}i2c_mode_t;

typedef enum{
    i2c_clk_src_UCLKI = 0,
    i2c_clk_src_ACLK = UCSSEL0,
    i2c_clk_src_SMCLK = UCSSEL1
}i2c_clk_src_t;

typedef enum{
    i2c_clk_presc_
}i2c_clk_presc_t;


void hal_i2c_init(i2c_mode_t i2c_mode, i2c_clk_src_t source, uint16_t prescaler);

void hal_i2c_setClockSource(i2c_clk_src_t source);

void hal_i2c_setClockPrescaler(uint16_t prescaler);

void hal_i2c_write_Byte(uint8_t address, uint8_t data);

void hal_i2c_write(uint8_t address, const uint8_t * data, uint8_t len);

uint8_t hal_i2c_read_Byte(uint8_t address);

void hal_i2c_read(uint8_t address, uint8_t * data, uint8_t len);


#endif /* HAL_HAL_I2C_H_ */
