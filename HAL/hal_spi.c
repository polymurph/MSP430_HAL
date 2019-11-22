/*
 * hal_spi.c
 *
 *  Created on: 11.11.2019
 *      Author: timon
 */
#include "hal_spi.h"
#include <stdint.h>
#include "msp430fr6989.h"

void hal_spi_init(spi_mode_t mode, spi_clk_source_t clk_source, spi_clk_t clk, uint16_t prescaler, spi_pin_mode_t pin, spi_data_dir_t direction)
{
    //Master or Slave
    UCB0CTLW0 &= ~UCMST;
    UCB0CTLW0 |= mode;

    //Clock Source
    UCB0CTLW0 &= ~(UCSSEL0 | UCSSEL1);
    //Check if SPI is in master mode
    if(UCB0CTLW0 & spi_mode_MASTER)
      {
       if(clk_source == spi_clk_source_UC0CLK)return;
          UCB0CTLW0 |= clk_source;
      }
    else
    {
      if(clk_source != spi_clk_source_UC0CLK)return;
         UCB0CTLW0 |= clk_source;
    }

    //Clock Prescaler
    UCB0CTLW0 |= UCSWRST; //Software Reset enable
    UCB0BRW   |= prescaler;
    UCB0CTLW0 &= ~UCSWRST; //Software Reset disable


    //Phase and Polarity
    UCB0CTLW0 &= ~(UCCKPL | UCCKPH);
    UCB0CTLW0 |= clk;

    //3 or 4 Pin
    UCB0CTLW0 &= ~(UCMODE0 | UCMODE1);
    UCB0CTLW0 |= pin;

    //MSB or LSB first
    UCB0CTLW0 &= ~UCMSB;
    UCB0CTLW0 |= direction;


        //MOSI (Port 1.6)
        P1DIR |= 0x04;
        P1SEL0 |= 0x04;
        P1SEL1 &= ~0x04;

        //Clock (Port 1.4)
        P1DIR |= 0x10;
        P1SEL0 |= 0x10;  //primary module function
        P1SEL1 &= ~0x10; //primary module function

        //Chip-Select(Port 2.4)
        P2SEL0  &= ~0x10;       //select normal I/O functionality
        P2SEL1 &= ~0x10;     //select normal I/O functionality
        P2DIR |= 0x10;         //set as output
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

uint8_t hal_spi_trx(uint8_t data)
{
      UCB0IFG = 0;
      UCB0TXBUF = data;
      while(UCB0IFG & UCRXIFG);//data received?

      return UCB0RXBUF;
}

//chip select procedure must be done by user
void hal_spi_tx(uint8_t data)
{
    UCB0TXBUF = data;         //transmit value
    while(UCB0IFG & UCTXIFG); //wait until value is transmitted
}

uint8_t hal_spi_rx(void)
{
    UCB0IFG = 0;
    UCB0TXBUF = 0x00;
    while(UCB0IFG & UCRXIFG);//data received?

    return UCB0RXBUF;
}

void hal_spi_trx_block(const uint8_t* txblock, uint8_t* rxblock)
{

}
