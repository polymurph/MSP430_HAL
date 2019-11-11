/*
 * hal_spi.h
 *
 *  Created on: 11.11.2019
 *      Author: timon
 */

#ifndef HAL_HAL_SPI_H_
#define HAL_HAL_SPI_H_

#include <stdint.h>

typedef enum{
    spi_mode_MASTER = UCMST,
    spi_mdoe_SLAVE = 0
}spi_mode_t;

typedef enum{
    spi_data_dir_MSB_FIRST = UCMSB,
    spi_data_dir_LSB_FIRST = 0
}spi_data_dir_t;

typedef enum{
    spi_clk_1MHZ,
    spi_clk_8MHz,
}spi_clk_t;

typedef enum{
    spi_charLen_7BIT = UC7BIT,
    spi_charLen_8BIT = 0
}spi_charLen_t;

// TODO: choose better names
typedef enum{
    spi_clk_mode_0 = 0, //Rising Edge Tx, Falling Edge Rx, Polarity Low
    spi_clk_mode_1= UCCKPL, //Falling Edge Tx, Rising Edge Rx, Polarity High
    spi_clk_mode_2 = UCCKPH, //Falling Edge Tx, Rising Edge Rx, Polarity Low
    spi_clk_mode_3 = UCCKPL | UCCKPH //Rising Edge Tx, Falling Edge Rx, Polarity High
}spi_clk_mode_t;

void hal_spi_init(spi_mode_t mode, spi_clk_t clk);

void hal_spi_setCharLenght(spi_charLen_t len);

void hal_spi_setClockMode(spi_polarity_t mode);

uint8_t hal_spi_trx();

void hal_spi_tx();

void hal_spi_rx();

void hal_spi_trx_block(const uint8_t* txblock, uint8_t* rxblock);




#endif /* HAL_HAL_SPI_H_ */
