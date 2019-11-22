#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>
#include "HAL/hal_spi.h"
#include "HAL/hal_clk.h"
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
    uint8_t i = 0;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//hal_clk_config_LFXT(drive_strenght_INCREASED, false, true);
	//hal_clk_config_ACLK(clk_ACLK_src_LFXT, 1, true);

	hal_spi_init(spi_mode_MASTER, spi_clk_source_ACLK, spi_clk_mode_1, 1, true);


	chip_select(true);
	hal_spi_trx(0xAA);
	chip_select(false);

	while(1)
	{
	    hal_spi_trx(0xAA);
	    for(i = 0; i < 0xFF; i++);
	}

	return 0;
}
