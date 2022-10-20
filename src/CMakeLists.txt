add_library(rppsrl shift_register_SIPO.c shift_register_PISO.c)

target_compile_options(rppsrl PRIVATE -Wall)

target_include_directories(rppsrl PUBLIC ../include)

target_link_libraries(rppsrl pico_stdlib)