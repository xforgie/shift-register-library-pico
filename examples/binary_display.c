/**
 * @file binary_display.c
 * @author xforgie (xforgie@gmail.com)
 * @brief This is an example to demonstrate how to interface with
 * an SN74HC595 shift register using the rppsr library
 * @version 0.1
 * @date 2022-10-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>

#include "pico/stdlib.h"
#include "rppsrl/shift_register_SIPO.h"

int main() {

    stdio_init_all();

    const uint8_t serial_pin = 15;
    const uint8_t latch_pin = 14;
    const uint8_t clock_pin = 13;

    ShiftRegisterSIPO sr = shift_register_SIPO_create(
        serial_pin,
        latch_pin,
        clock_pin
    );

    shift_register_SIPO_clear(&sr);
    shift_register_SIPO_latch(&sr);

    uint8_t sum = 0;
    uint32_t time_to_wait = 500;
    absolute_time_t current_time = get_absolute_time();
    absolute_time_t delay_time = make_timeout_time_ms(time_to_wait);

    while (true) {

        if (absolute_time_diff_us(current_time, delay_time) <= 0) {
            
            delay_time = make_timeout_time_ms(time_to_wait); // restart the timer
            
            shift_register_SIPO_write_byte(&sr, sum++, LSBFIRST); // write data to the shift register
            shift_register_SIPO_latch(&sr); // latch the data to the output

            printf("Sum: %02x\n", sum);
        }

        current_time = get_absolute_time();
    }
    
    return 0;
}