# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

option(EXAMPLES "build examples" OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(rppsrl C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

if (EXAMPLES)
    add_subdirectory(./src)
    add_subdirectory(./examples)
else()
    add_subdirectory(./src)
endif()