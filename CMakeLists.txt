# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/xforgie/Desktop/rasppico/pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(PicoShiftRegisterLib C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_subdirectory(./src)

# Add executable. Default name is the project name, version 0.1

# add_executable(PicoShiftRegisterLib src/PicoShiftRegisterLib.c )

# pico_set_program_name(PicoShiftRegisterLib "PicoShiftRegisterLib")
# pico_set_program_version(PicoShiftRegisterLib "0.1")

# pico_enable_stdio_uart(PicoShiftRegisterLib 1)
# pico_enable_stdio_usb(PicoShiftRegisterLib 1)

# # Add the standard library to the build
# target_link_libraries(PicoShiftRegisterLib pico_stdlib)

# pico_add_extra_outputs(PicoShiftRegisterLib)

