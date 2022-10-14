
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "rpi_pico_shift_register/shift_register_PISO.h"

static void read_in_byte(ShiftRegisterPISO *sr, char *buffer) {

    gpio_put(sr->latch_pin, 0);

        uint8_t value = 0;

        for (int i = 0; i < 7; i++) {

            gpio_put(sr->clock_pin, 0);

            bool data = gpio_get(sr->serial_pin);
            printf("%d", data ? 1 : 0);
            value |= ((data ? 1 : 0) << i);

            gpio_put(sr->clock_pin, 1);
        }

    gpio_put(sr->latch_pin, 1);

    *buffer = value;

    printf("    value: %2x\n", value);
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

void shift_register_PISO_read_in_byte(ShiftRegisterPISO *sr, char *buffer) {
    sr->read_in_byte(sr, buffer);
}