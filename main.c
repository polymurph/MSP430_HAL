#include <msp430.h>
#include <stdbool.h>
#include "HAL/hal_i2c.h"

#define PCF8575_ADDRESS 0b01001110

void _init_LED();
void _set_LED(bool state);

#if 0
int main(void)
{
    uint8_t data[] = { 0b00000000,
                       0b00000000
    };
    uint8_t data_1[] = { 0b11111111,
                         0b11111111
    };
    uint8_t i = 0;

    _init_LED();

    hal_i2c_init();

    if(hal_i2c_dataWrite(PCF8575_ADDRESS,data,sizeof(data)) != I2C_NO_ERR) _set_LED(true);

    while(1)
    {

    }
}
#endif

#if 1
int main(void)
{
    uint8_t data[] = { 0b00000000,
                       0b00000000
    };
    uint8_t data_1[] = { 0b11111111,
                         0b11111111
    };
    uint8_t i = 0;

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	hal_i2c_init(i2c_mode_MASTER, i2c_clk_src_SMCLK, 8);

	hal_i2c_write(PCF8575_ADDRESS,data,sizeof(data));

	_set_LED(true);

	while(1)
	{
	    //hal_i2c_write(PCF8575_ADDRESS,data,sizeof(data));
	    _set_LED(true);
	    for(i =0; i < 0xFF; i++);
	    //hal_i2c_write(PCF8575_ADDRESS,data_1,sizeof(data_1));
	    _set_LED(false);
	    for(i =0; i < 0xFF; i++);
	}
}
#endif


void _init_LED()
{
    //PM5CTL0 |= LOCKLPM5;

    P1DIR |= 0x01;
    P1OUT &= ~0x01;

    P9DIR |= 0x80;
    P9OUT |= 0x80;

}

void _set_LED(bool state)
{
    if(state){
        P1OUT |= 0x01;
        P9OUT &= 0x80;
    } else {
        P1OUT &= ~0x01;
        P9OUT |= 0x80;
    }
}
