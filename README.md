# Raspberry Pi Pico Shift Register Library

A C library to interface with SN74HC595 and CD4021B shift registers using the Raspberry Pi Pico

## Table of Contents

- [Examples](#examples)
- [Using the library](#using-the-library)
- [Documentation](#documentation)
- [License](#license)

## Examples

running 8 LEDs with the SN74HC595:
```c
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
```
Reading 8 button inputs from the CD4021B:
```c
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
```

Examples can be built by adding the EXAMPLES option when using CMake from a build folder:

```sh
cmake -DEXAMPLES=ON ..
```

The .uf2 files to transfer to the pico can then be found under build/examples after running the makefile in the build directory

## Using the library

add the rppsrl folder into the include directory in your project, and the librppsrl.a into a libraries folder

They can then be added with CMake:

```sh
target_include_directories(<project_name> PUBLIC path/to/include)
target_include_library(<project_name> /path/to/librppsrl.a)
```

## Documentation

Doxygen 1.8.17 was used to generate HTML-style docs, and can be opened from the index.html file under docs/html.

The doxygen configuration file can also be used to generate HTML-style docs from the source directory:

```sh
doxygen docs/doxygen.conf
```

These will be generated under the docs/ subdirectory.

## License

[BSD 3-Clause](LICENSE)
