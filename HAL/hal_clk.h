/*
 * hal_clk.h
 *
 *  Created on: Nov 21, 2019
 *      Author: Edwin
 */

#ifndef HAL_HAL_CLK_H_
#define HAL_HAL_CLK_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum{
    clk_error_NO_ERROR = 0,
    clk_error_LFXT_FAULT,

}clk_error_t;

typedef enum{
    clk_ACLK_src_LFXT,
    clk_ACLK_src_HFXT
}clk_ACLK_src_t;

typedef enum{
    clk_presc_DIV_1 = 0,
    clk_presc_DIV_2,
    clk_presc_DIV_4,
    clk_presc_DIV_8,
    clk_presc_DIV_16,
    clk_presc_DIV_32
}clk_presc_t;

typedef enum{
    drive_strenght_LOW = 0,
    drive_strenght_INCREASED = 1,
    drive_strenght_MAX = 3
}drive_strenght_t;


#endif /* HAL_HAL_CLK_H_ */
