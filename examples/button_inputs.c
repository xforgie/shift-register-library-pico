/**
 * @file button_inputs.c
 * @author xforgie (xforgie@gmail.com)
 * @brief This is an example to demonstrate how to
 * interface with a CD4021BE using the rppsr library
 * @version 0.1
 * @date 2022-10-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>

#include "pico/stdlib.h"
#include "rppsrl/shift_register_PISO.h"

void print_button_state(const uint8_t *v) {

    printf("Button states: ");
    
    for (int i = 0; i < 8; i++)
        printf("%c", (*v >> i) & 1 ? '1' : '0');

    printf("\n");
}

int main() {

    stdio_init_all();

    uint8_t buffer = 0;
    uint8_t cur_state = 0;
    const uint8_t serial_pin = 16;
    const uint8_t latch_pin = 14;
    const uint8_t clock_pin = 15;

    ShiftRegisterPISO sr = shift_register_PISO_create(serial_pin, clock_pin, latch_pin);

    uint8_t sum = 0;
    uint32_t time_to_wait = 100;
    absolute_time_t current_time = get_absolute_time();
    absolute_time_t delay_time = make_timeout_time_ms(time_to_wait);

    while (true) {

        if (absolute_time_diff_us(current_time, delay_time) <= 0) {
            
            delay_time = make_timeout_time_ms(time_to_wait); // restart the timer
            
            shift_register_PISO_read_in_byte(&sr, &buffer);
            
            // Check if any buttons have changed state
            if (buffer != cur_state) {
                cur_state = buffer;
                print_button_state(&buffer);
            }
        }

        current_time = get_absolute_time();
    }

    return 0;
}