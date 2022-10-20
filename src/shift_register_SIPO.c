
#include "pico/stdlib.h"
#include "rppsrl/shift_register_SIPO.h"

static void func_set_enable_pin(ShiftRegisterSIPO *sr, uint8_t enable_pin) {
    gpio_init(enable_pin);
    gpio_set_dir(enable_pin, GPIO_OUT);
    gpio_put(enable_pin, false);    // enable output by default (active low signal)
    sr->enable_pin = enable_pin;
}

static void func_enable(ShiftRegisterSIPO *sr, bool value) {
    gpio_put(sr->enable_pin, !value);
}

static void func_latch(ShiftRegisterSIPO *sr) {
    gpio_put(sr->latch_pin, true);
    gpio_put(sr->latch_pin, false);
}

static inline void func_write_bit(ShiftRegisterSIPO *sr, bool value) {
    gpio_put(sr->serial_pin, value);
    gpio_put(sr->clock_pin, true);
    gpio_put(sr->clock_pin, false);
}

static void func_write_byte(ShiftRegisterSIPO *sr, uint8_t byte, ByteOrder byte_order) {
    if (byte_order == LSBFIRST) {
        for (int i = 0; i < 8; i++)
            func_write_bit(sr, (byte >> i) & 1);
    } else { // default to MSB first
        for (int i = 7; i >= 0; i--)
            func_write_bit(sr, (byte >> i) & 1);
    }
}

static void func_clear(ShiftRegisterSIPO *sr) {
    shift_register_SIPO_write_byte(sr, false, MSBFIRST);
}

ShiftRegisterSIPO shift_register_SIPO_create(uint8_t serial_pin, uint8_t clock_pin, uint8_t latch_pin) {
    ShiftRegisterSIPO sr = {
        serial_pin,
        clock_pin,
        latch_pin,
        PIN_DISABLED,
        PIN_DISABLED,
        func_set_enable_pin,
        func_enable,
        func_latch,
        func_write_bit,
        func_write_byte,
        func_clear
    };

    gpio_init(serial_pin);
    gpio_init(clock_pin);
    gpio_init(latch_pin);

    gpio_set_dir(serial_pin, GPIO_OUT);
    gpio_set_dir(clock_pin, GPIO_OUT);
    gpio_set_dir(latch_pin, GPIO_OUT);

    gpio_put(serial_pin, false);
    gpio_put(clock_pin, false);
    gpio_put(latch_pin, false);

    return sr;
}

void shift_register_SIPO_set_enable_pin(ShiftRegisterSIPO *sr, uint8_t enable_pin) {
    return sr->set_enable_pin(sr, enable_pin);
}

void shift_register_SIPO_enable(ShiftRegisterSIPO *sr, bool value) {
    return sr->enable(sr, value);
}

void shift_register_SIPO_latch(ShiftRegisterSIPO *sr) {
    sr->latch(sr);
}

void shift_register_SIPO_write_bit(ShiftRegisterSIPO *sr, bool value) {
    sr->write_bit(sr, value);
}

void shift_register_SIPO_write_byte(ShiftRegisterSIPO* sr, uint8_t byte, ByteOrder byte_order) {
    sr->write_byte(sr, byte, byte_order);
}


void shift_register_SIPO_clear(ShiftRegisterSIPO* sr) {
    sr->clear(sr);
}