
#include <stdio.h>

#include "pico/stdlib.h"
#include "rppsrl/shift_register_PISO.h"

static void read_in_byte(ShiftRegisterPISO *sr, uint8_t *buffer) {

    gpio_put(sr->latch_pin, false);

    uint8_t value = 0;
    
    for (int i = 0; i < 8; i++) {

        bool data = gpio_get(sr->serial_pin);
        value |= ((data ? 1 : 0) << i);

        busy_wait_us_32(1);
        gpio_put(sr->clock_pin, true);
        busy_wait_us_32(1);
        gpio_put(sr->clock_pin, false);
    }

    gpio_put(sr->latch_pin, true);

    *buffer = value;
}

ShiftRegisterPISO shift_register_PISO_create(uint8_t serial_pin, uint8_t clock_pin, uint8_t latch_pin) {

    ShiftRegisterPISO sr = {
        serial_pin,
        clock_pin,
        latch_pin,
        read_in_byte
    };

    gpio_init(serial_pin);
    gpio_init(clock_pin);
    gpio_init(latch_pin);

    gpio_set_dir(serial_pin, GPIO_IN);
    gpio_set_dir(clock_pin, GPIO_OUT);
    gpio_set_dir(latch_pin, GPIO_OUT);

    gpio_put(clock_pin, false);
    gpio_put(latch_pin, false);

    return sr;
}

void shift_register_PISO_read_in_byte(ShiftRegisterPISO *sr, uint8_t *buffer) {
    sr->read_in_byte(sr, buffer);
}