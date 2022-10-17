
add_executable(binary_display binary_display.c)

pico_set_program_name(binary_display "binary_display")
pico_set_program_version(binary_display "0.1")

pico_enable_stdio_uart(binary_display 1)
pico_enable_stdio_usb(binary_display 1)

target_include_directories(binary_display PUBLIC ../include)

target_link_libraries(binary_display pico_stdlib rpi_pico_shift_register)

pico_add_extra_outputs(binary_display)