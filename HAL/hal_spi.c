/*
 * hal_spi.c
 *
 *  Created on: 11.11.2019
 *      Author: timon
 */
#include "hal_spi.h"
#include "msp430fr6989.h"

void hal_spi_init(spi_mode_t mode, spi_clk_t clk, spi_pin_mode_t pin)
{
    UCB0CTLW0 &= ~UCMST;
    UCB0CTLW0 |= mode;

    UCB0CTLW0 &= ~(UCMODE0 | UCMODE1);
    UCB0CTLW0 |= pin;
}

void hal_spi_pin(spi_pin_mode_t pin)
{
    UCB0CTLW0 &= ~(UCMODE0 | UCMODE1);
    UCB0CTLW0 |= pin;
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

//chip select procedure must be done by user
void hal_spi_tx(uint8_t data)
{
    UCA0TXBUF = data;         //transmit value
    while(UCA0IFG & UCTXIFG); //wait until value is transmitted
}

uint8_t hal_spi_rx(void)
{
    UCA0IFG = 0;
    UCA0TXBUF = 0x00;
    while(UCA0IFG & UCRXIFG);//data received?

    return UCA0RXBUF;
}

void hal_spi_trx_block(const uint8_t* txblock, uint8_t* rxblock)
{

}
