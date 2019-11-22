#include <msp430.h>
#include <stdbool.h>
#include "HAL/hal_spi.h"
/**
 * main.c
 */
//Chip-Select Port 2.4
void chip_select(bool select)
{
    if(select){
        P2OUT |= 0x10;
    } else {
        P2OUT &= ~0x10;
    }
}




int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	

	hal_spi_init(spi_mode_MASTER, spi_clk_source_ACLK, spi_clk_mode_1, 0,spi_mode_3PIN, spi_data_dir_MSB_FIRST);

	chip_select(true);
	hal_spi_trx(0xAA);
	chip_select(false);

	while(1)
	{

	}

	return 0;
}
