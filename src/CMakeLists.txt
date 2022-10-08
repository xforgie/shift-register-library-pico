
# add_library(PicoShiftRegisterLib shift_register_SIPO.c)

# include_directories(../include/PicoShiftRegisterLib)

add_library(PicoShiftRegisterLib shift_register_SIPO.c)

target_include_directories(PicoShiftRegisterLib PUBLIC "/home/xforgie/Desktop/rasppico/pico/PicoShiftRegisterLib/include/")

target_link_libraries(PicoShiftRegisterLib pico_stdlib)