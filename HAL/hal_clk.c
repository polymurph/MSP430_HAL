/*
 * hal_clk.c
 *
 *  Created on: Nov 21, 2019
 *      Author: Edwin Koch
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

    return clk_error_NO_ERROR;
}

clk_error_t hal_clk_config_HFXT(drive_strenght_t strength ,bool bypass, bool enable)
{
    _unlock_registers();

    // drive strength
    CSCTL4 &= ~HFXTDRIVE_3;
    CSCTL4 |= (uint16_t)(strength << 14);


    if(bypass){
        CSCTL4 |= HFXTBYPASS;
    } else {
        CSCTL4 &= ~HFXTBYPASS;
    }

    if(enable){
        CSCTL4 &= ~HFXTOFF;
    } else {
        CSCTL4 |= HFXTOFF;
    }
    _lock_registers();

    if(CSCTL5 & HFXTOFF) return clk_error_LFXT_FAULT;

    return clk_error_NO_ERROR;
}

void hal_clk_config_DCO(clk_dco_freq_t freq)
{
   _unlock_registers();

   // set frequency
   CSCTL1 &= ~(DCOFSEL2 | DCOFSEL1 | DCOFSEL0 | DCORSEL);
   CSCTL1 |= freq;

   _lock_registers();
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

    if(enable) {
        CSCTL6 |= ACLKREQEN;
    } else {
        CSCTL6 &= ~ACLKREQEN;
    }

    _lock_registers();
}

void hal_clk_config_MCLK(clk_MCLK_src_t source, clk_presc_t prescaler, bool enable)
{
    _unlock_registers();

    // select source
    CSCTL2 &= ~(uint16_t)(0x7);
    CSCTL2 |= source;

    // set prescaler
    CSCTL3 &= ~(uint16_t)(0x7);
    CSCTL3 |= (uint16_t)(prescaler);

    if(enable) {
        CSCTL6 |= MCLKREQEN;
    } else {
        CSCTL6 &= ~MCLKREQEN;
    }
    _lock_registers();
}

void hal_clk_config_SMCLK(clk_SMCLK_src_t source, clk_presc_t prescaler, bool enable)
{
    _unlock_registers();

    // select source
    CSCTL2 &= ~(uint16_t)(0x7 << 4);
    CSCTL2 |= source << 4;

    // set prescaler
    CSCTL3 &= ~(uint16_t)(0x7 << 4);
    CSCTL3 |= (uint16_t)(prescaler << 4);

    if(enable) {
        CSCTL6 |= SMCLKREQEN;
    } else {
        CSCTL6 &= ~SMCLKREQEN;
    }
    _lock_registers();
}


