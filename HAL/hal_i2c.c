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

static inline void _stop_sequence()
{
    UCB1CTLW0 |= UCTXSTP;
    while(!(UCB1CTLW0 & UCTXSTP));
}

#if 0
static inline void _poll_busy()
{
    while(UCB1STATW & UCBBUSY);
}
#endif

static inline bool _start_sequence(uint8_t address, bool read)
{
    UCB1IFG = 0;    // clear old flags
    UCB1I2CSA = address;    // set slave address
    UCB1CTLW0 |= (read) ? (UCTR) : (0); // set send/recive mode
    UCB1CTLW0 |= UCTXSTT;   // generate start condition
    while(UCB1CTLW0 & UCTXSTT); // wait until start condition is sent

    // check for error
    if(UCB1IFG & UCNACKIFG){
        _stop_sequence();
        return true;
    }
    return false;
}

static inline bool _write_tx_buf(uint8_t data)
{
    UCB1TXBUF = data;
    while(!(UCB1IFG & UCTXIFG0));   // wait for transmit completion

    // check for error
    if(UCB1IFG & UCNACKIFG){
        _stop_sequence();
        return true;
    }
    return false;
}

static inline uint8_t _read_rx_buf()
{
    while(!(UCB1IFG & UCRXIFG0));
    return UCB1RXBUF;
}


void hal_i2c_init(i2c_mode_t i2c_mode, i2c_clk_src_t source, uint16_t prescaler)
{
    // settup GPIOs for i2c mode
    P4DIR &= ~0x03; // SDA and SCL as output
    P4SEL0 &= ~0x03;
    P4SEL1 |= 0x03;

    // unlock register
    UCB1CTLW0 |= UCSWRST;

    // set master or slave mode
    UCB1CTLW0 &= ~UCMST;
    UCB1CTLW0 |= i2c_mode;

    // set eUSCI_B module to i2c functionality
    UCB1CTLW0 |= UCMODE_3;

    // select clock source
    UCB1CTLW0 &= ~(UCSSEL0 | UCSSEL1);
    UCB1CTLW0 |= source;

    // set prescaler
    UCB1BRW = prescaler;

    // lock register
    UCB1CTLW0 &= ~UCSWRST;
}

void hal_i2c_setClockSource(i2c_clk_src_t source)
{
    // unlock register
    UCB1CTLW0 |= UCSWRST;
    UCB1CTLW0 &= ~(UCSSEL0 | UCSSEL1);
    UCB1CTLW0 |= source;
    // lock register
    UCB1CTLW0 &= ~UCSWRST;
}

void hal_i2c_setClockPrescaler(uint16_t prescaler)
{
    // unlock register
    UCB1CTLW0 |= UCSWRST;
    UCB1BRW = prescaler;
    // lock register
    UCB1CTLW0 &= ~UCSWRST;
}

void hal_i2c_write_Byte(uint8_t address, uint8_t data)
{
    _start_sequence(address, false);
    _write_tx_buf(data);
    _stop_sequence();
}

bool hal_i2c_write(uint8_t address, const uint8_t * data, uint8_t len)
{
    uint8_t i = 0;
    if(_start_sequence(address, false)) return true;
    for(i = 0; i < len; i++){
        if(_write_tx_buf(data[i])) return true;
    }
    _stop_sequence();
    return false;
}

bool hal_i2c_read_Byte(uint8_t address, uint8_t *byte)
{
    if(_start_sequence(address, true)) return true;
    *byte = _read_rx_buf();
    _stop_sequence();
    return false;
}

void hal_i2c_read(uint8_t address, uint8_t * data, uint8_t len)
{

}

