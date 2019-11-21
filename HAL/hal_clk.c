/*
 * hal_clk.c
 *
 *  Created on: Nov 21, 2019
 *      Author: Edwin
 */
#include "HAL/hal_clk.h"
#include "HAL/msp430fr6989.h"

#include <stdint.h>
#include <stdbool.h>

static inline void _unlock_registers()
{
    CSCTL0 |= CSKEY;
}

static inline void _lock_registers()
{
    CSCTL0 &= ~CSKEY;
}

clk_error_t hal_clk_config_LFXT(drive_strenght_t strength ,bool bypass, bool enable)
{
    _unlock_registers();

    // drive strength
    CSCTL4 &= ~LFXTDRIVE_3;
    CSCTL4 |= (uint16_t)(strength << 6);


    if(bypass){
        CSCTL4 |= LFXTBYPASS;
    } else {
        CSCTL4 &= ~LFXTBYPASS;
    }

    if(enable){
        CSCTL4 &= ~LFXTOFF;
    } else {
        CSCTL4 |= LFXTOFF;
    }
    _lock_registers();

    if(CSCTL5 & LFXTOFF) return clk_error_LFXT_FAULT;

    return clk_error_NO_ERROR
}





void hal_clk_config_ACLK(clk_ACLK_src_t source, clk_presc_t prescaler, bool enable)
{
    _unlock_registers();

    // select source
    CSCTL2 &= ~(uint16_t)(0x7 << 8);
    CSCTL2 |= source;

    // set prescaler
    CSCTL3 &= ~(uint16_t)(0x7 << 8);
    CSCTL3 |= (uint16_t)(prescaler << 8);

    _lock_registers();
}

void hal_clk_enable_ACLK(bool enable)
{
    _unlock_registers();
    if(enable){

    } else {

    }
    _lock_registers();
}

void hal_clk_select_ACLK_source(clk_ACLK_src_t source)
{

}


