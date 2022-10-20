file(GLOB EXAMPLE_FILES binary_display.c button_inputs.c)

foreach (EXAMPLE_PATH ${EXAMPLE_FILES})

    get_filename_component(EXEC_NAME ${EXAMPLE_PATH} NAME_WE)

    add_executable(${EXEC_NAME} ${EXAMPLE_PATH})

    pico_enable_stdio_uart(${EXEC_NAME} 1)
    pico_enable_stdio_usb(${EXEC_NAME} 1)

    target_include_directories(${EXEC_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(${EXEC_NAME} pico_stdlib rppsrl)

    pico_add_extra_outputs(${EXEC_NAME})

endforeach(EXAMPLE_PATH ${CMAKE_CURRENT_SOURCE_DIR})