
#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>
#include "HAL/hal_spi.h"
#include "HAL/hal_clk.h"

/**
 * main.c
 */

void init_chip_select()
{
    PM5CTL0 &= ~LOCKLPM5;

    P2DIR |= 0x10;
    P2OUT &= ~0x10;

    PM5CTL0 |= LOCKLPM5;
}

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

    uint8_t data[] ={
                     0xAA,
                     0x55,
                     0xA5,
                     0x5A
    };

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	init_chip_select();

/*
	hal_clk_config_MCLK(clk_MCLK_src_LFXT, 0, true);
	hal_clk_config_ACLK(clk_ACLK_src_LFXT, 0, true);

	hal_clk_output_ACLK_to_GPIO(true);
	hal_clk_output_MCLK_to_GPIO(true);
*/
	hal_spi_init(spi_mode_MASTER,spi_clk_source_ACLK, spi_clk_mode_2, 2, true);




	while(1)
	{
	    chip_select(true);

        hal_spi_tx_byte(0x0F);
        hal_spi_tx_byte(0xFF);

        chip_select(false);

	    //hal_spi_tx(data, sizeof(data));
	    for(i = 0; i < 0xFFF; i++);

	    chip_select(true);

        hal_spi_tx_byte(0x0C);
        hal_spi_tx_byte(0xFFF);

        chip_select(false);

        for(i = 0; i < 0xFF; i++);

	}

	return 0;
}
