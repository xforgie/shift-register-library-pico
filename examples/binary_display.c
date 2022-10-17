
/**
 * @file binary_display.c
 * @author xforgie (xforgie@gmail.com)
 * @brief This is an example to demonstrate how to interface with
 * an SN74HC595 shift register using the rpi_pico_shift_register library
 * @version 0.1
 * @date 2022-10-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "pico/stdlib.h"
#include "rpi_pico_shift_register/shift_register_SIPO.h"

int main() {

    const uint8_t serial_pin = 14;
    const uint8_t latch_pin = 5;
    const uint8_t clock_pin = 4;
    const uint8_t enable_pin = 2;

    ShiftRegisterSIPO sr = shift_register_SIPO_create(
        serial_pin,
        latch_pin,
        clock_pin
    );

    uint8_t sum = 0;
    uint32_t time_to_wait = 500;
    absolute_time_t current_time = get_absolute_time();
    absolute_time_t delay_time = make_timeout_time_ms(time_to_wait);

    while (true) {

        if (absolute_time_diff_us(current_time, delay_time) <= 0) {
            
            delay_time = make_timeout_time_ms(time_to_wait); // restart the timer
            
            shift_register_SIPO_write_byte(&sr, sum++, MSBFIRST);   // write data to the shift register
            shift_register_SIPO_latch(&sr); // latch the data to the output
        }

    }
    
    return 0;
}