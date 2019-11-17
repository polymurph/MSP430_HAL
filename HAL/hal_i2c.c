/*
 * hal_i2c.c
 *
 *  Created on: Nov 13, 2019
 *      Author: Edwin Koch
 */

#include "hal_i2c.h"
#include "msp430fr6989.h"

#include <stdbool.h>
#include <stdint.h>

static inline void _start_sequence(uint8_t address,bool read)
{

}

static inline void _write(uint8_t data)
{

}

static inline uint8_t _read();
{

}

static inline void _stop_sequence();
{

}

void hal_i2c_init(i2c_mode_t mode, i2c_clk_src_t source)
{
    // settup GPIOs for i2c mode

    // unlock register
    UCB0CTLW0 |= UCSWRST;

    // set master or slave mode
    UCB0CTLW0 &= ~UCMST;
    UCB0CTLW0 |= mode;

    // set eUSCI_B module to i2c functionality
    UCB0CTLW0 |= UCMODE_3;

    // select clock source
    UCB0CTLW0 &= ~(UCSSEL0 | UCSSEL1);
    UCB0CTLW0 |= source;

    // lock register
    UCB0CTLW0 &= ~UCSWRST;
}

void hal_i2c_setClockSource(i2c_clk_src_t source)
{
    // unlock register
    UCB0CTLW0 |= UCSWRST;
    UCB0CTLW0 &= ~(UCSSEL0 | UCSSEL1);
    UCB0CTLW0 |= source;
    // lock register
    UCB0CTLW0 &= ~UCSWRST;
}

void hal_i2c_setClockPrescaler(uint16_t prescaler)
{
    // unlock register
    UCB0CTLW0 |= UCSWRST;
    UCB0BRW = prescaler;
    // lock register
    UCB0CTLW0 &= ~UCSWRST;
}

void hal_i2c_write_Byte(uint8_t address, uint8_t data)
{
    _start_sequence(address, false);
    _write(data);
    _stop_sequence();
}

void hal_i2c_write(uint8_t address, const uint8_t * data, uint8_t len)
{
    uint8_t i = 0;
    _start_sequence(address, false);
    for(i = 0; i < len; i++){
        _write(data[i]);
    }
    _stop_sequence();
}

uint8_t hal_i2c_read_Byte(uint8_t address)
{
    uint8_t buf = 0;
    _start_sequence(address, true);
    buf = _read();
    _stop_sequence();
    return buf;
}

