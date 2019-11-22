#include <msp430.h> 
#include "HAL/hal_clk.h"

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	hal_clk_config_DCO(clk_dco_freq_1_MHz);
	hal_clk_config_LFXT(drive_strenght_INCREASED, false, true);
	hal_clk_config_MCLK(clk_MCLK_src_LFXT, clk_presc_DIV_1, false);
	hal_clk_config_ACLK(clk_ACLK_src_LFXT, 0, false);

	hal_clk_output_ACLK_to_GPIO(true);
	hal_clk_output_MCLK_to_GPIO(true);

#if 0
	PM5CTL0 &= ~LOCKLPM5;

	P4DIR |= 0x03;
	P4SEL0 |= 0x03;
	P4SEL1 |= 0x03;
	PM5CTL0 |= LOCKLPM5;
#endif

	while(1)
	{

	}
	return 0;
}
