/*
 * hal_spi.c
 *
 *  Created on: 11.11.2019
 *      Author: timon
 */
#include "hal_spi.h"
#include "msp430fr6989.h"

void hal_spi_init(spi_mode_t mode, spi_clk_t clk)
{
    UCB0CTLW0 &= ~UCMST;
    UCB0CTLW0 |= mode;


}

void hal_spi_setClkSource(spi_clk_source_t source)
{
    UCB0CTLW0 &= ~(UCSSEL0 | UCSSEL1);

    // check if SPI is in master mode
    if(UCB0CTLW0 & spi_mode_MASTER)
    {
        if(source == spi_clk_source_UC0CLK)return;
        UCB0CTLW0 |= source;
    }else{
        if(source != spi_clk_source_UC0CLK)return;
        UCB0CTLW0 |= source;
    }
}

// Set Character length:7 Bit or 8 Bit
void hal_spi_setCharLenght(spi_charLen_t len)
{
    UCB0CTLW0 &= ~UC7BIT;
    UCB0CTLW0 |= len;
}

void hal_spi_setClockMode(spi_clk_mode_t mode)
{
    UCB0CTLW0 &= ~(UCCKPL | UCCKPH);
    UCB0CTLW0 |= mode;
}

uint8_t hal_spi_trx()
{

}

void hal_spi_tx()
{

}

void hal_spi_rx()
{

}

void hal_spi_trx_block(const uint8_t* txblock, uint8_t* rxblock)
{

}
