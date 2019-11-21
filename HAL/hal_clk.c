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

void hal_clk_config_ACLK(clk_ACLK_src_t source, clk_presc_t prescaler, bool enable)
{
    _unlock_registers();

    // set prescaler
    CSCTL3 &= ~(uint16_t)(0x7 << 8);
    CSCTL3 |= prescaler;



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


