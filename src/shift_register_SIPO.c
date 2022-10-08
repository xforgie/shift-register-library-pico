
#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "PicoShiftRegisterLib/shift_register_SIPO.h"

shift_register_SIPO* shift_register_SIPO_create(uint32_t num_connected, uint8_t serial_pin, uint8_t latch_pin, uint8_t clock_pin) {

    shift_register_SIPO *sr = malloc(sizeof(*sr));
    if (sr == NULL) {
        printf("ERROR: Could not allocate memory\n");
        exit(1);
    }

    sr->serial_pin = serial_pin;
    sr->latch_pin = latch_pin;
    sr->clock_pin = clock_pin;
    sr->enable_pin = 255;
    sr->clear_pin = 255;

    sr->num_connected = num_connected;

    gpio_init(serial_pin);
    gpio_init(latch_pin);
    gpio_init(clock_pin);

    gpio_set_dir(serial_pin, GPIO_OUT);
    gpio_set_dir(latch_pin, GPIO_OUT);
    gpio_set_dir(clock_pin, GPIO_OUT);

    gpio_put(serial_pin, 0);
    gpio_put(latch_pin, 0);
    gpio_put(clock_pin, 0);

    return sr;
}

void shift_register_SIPO_set_enable_pin(shift_register_SIPO *sr, uint8_t enable_pin) {
    gpio_init(enable_pin);
    gpio_set_dir(enable_pin, GPIO_OUT);
    gpio_put(enable_pin, 0);    // enable output by default
    sr->enable_pin = enable_pin;
}

void shift_register_SIPO_set_enable(shift_register_SIPO *sr, bool value) {
    gpio_put(sr->enable_pin, !value);
}

void shift_register_SIPO_latch(shift_register_SIPO *sr) {
    gpio_put(sr->latch_pin, 1);
    gpio_put(sr->latch_pin, 0);
}

void shift_register_SIPO_write_bit(shift_register_SIPO *sr, bool value) {
    gpio_put(sr->serial_pin, value);
    gpio_put(sr->clock_pin, 1);
    gpio_put(sr->clock_pin, 0);
}

void shift_register_SIPO_write_byte(shift_register_SIPO* sr, uint8_t byte, byte_order_t byte_order) {

    if (byte_order == MSBFIRST) {

        for (int i = 7; i >= 0; i--) {
            gpio_put(sr->serial_pin, (byte >> i) & 1);
            gpio_put(sr->clock_pin, 1);
            gpio_put(sr->clock_pin, 0);
        }

    } else if (byte_order == LSBFIRST) {

        for (int i = 0; i < 8; i++) {
            gpio_put(sr->serial_pin, (byte >> i) & 1);
            gpio_put(sr->clock_pin, 1);
            gpio_put(sr->clock_pin, 0);
        }

    }
}

void shift_register_SIPO_clear(shift_register_SIPO* sr) {
    for (int i = 0; i < sr->num_connected; i++)
        shift_register_SIPO_write_byte(sr, 0, MSBFIRST);
}

void shift_register_SIPO_destroy(shift_register_SIPO* sr) {
    free(sr);
}