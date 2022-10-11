
#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "rpi_pico_shift_register/shift_register_SIPO.h"

static void func_set_enable_pin(ShiftRegisterSIPO *sr, uint8_t enable_pin) {
    gpio_init(enable_pin);
    gpio_set_dir(enable_pin, GPIO_OUT);
    gpio_put(enable_pin, 0);    // enable output by default
    sr->enable_pin = enable_pin;
}

static void func_set_enable(ShiftRegisterSIPO *sr, bool value) {
    gpio_put(sr->enable_pin, !value);
}

static void func_latch(ShiftRegisterSIPO *sr) {
    gpio_put(sr->latch_pin, 1);
    gpio_put(sr->latch_pin, 0);
}

static void func_write_byte(ShiftRegisterSIPO *sr, uint8_t byte, ByteOrder byte_order) {
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

static void func_write_bit(ShiftRegisterSIPO *sr, bool value) {
    gpio_put(sr->serial_pin, value);
    gpio_put(sr->clock_pin, 1);
    gpio_put(sr->clock_pin, 0);
}

static void func_clear(ShiftRegisterSIPO *sr) {
    shift_register_SIPO_write_byte(sr, 0, MSBFIRST);
}

ShiftRegisterSIPO shift_register_SIPO_create(uint8_t serial_pin, uint8_t latch_pin, uint8_t clock_pin) {

    ShiftRegisterSIPO sr = {
        serial_pin,
        latch_pin,
        clock_pin,
        255,
        255,
        func_set_enable_pin,
        func_set_enable,
        func_latch,
        func_write_byte,
        func_write_bit,
        func_clear
    };

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

void shift_register_SIPO_set_enable_pin(ShiftRegisterSIPO *sr, uint8_t enable_pin) {
    sr->set_enable_pin(sr, enable_pin);
}

void shift_register_SIPO_set_enable(ShiftRegisterSIPO *sr, bool value) {
    sr->set_enable(sr, value);
}

void shift_register_SIPO_latch(ShiftRegisterSIPO *sr) {
    sr->latch(sr);
}

void shift_register_SIPO_write_byte(ShiftRegisterSIPO* sr, uint8_t byte, ByteOrder byte_order) {
    sr->write_byte(sr, byte, byte_order);
}

void shift_register_SIPO_write_bit(ShiftRegisterSIPO *sr, bool value) {
    sr->write_bit(sr, value);
}

void shift_register_SIPO_clear(ShiftRegisterSIPO* sr) {
    sr->clear(sr);
}