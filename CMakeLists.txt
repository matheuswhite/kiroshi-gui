cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(kiroshi-gui)

pico_sdk_init()

add_executable(kiroshi-gui test/main.c src/lcd_driver.c)
target_include_directories(kiroshi-gui PUBLIC src/include)
target_link_libraries(kiroshi-gui pico_stdlib hardware_spi)

pico_enable_stdio_usb(kiroshi-gui 1)
pico_enable_stdio_uart(kiroshi-gui 0)
pico_add_extra_outputs(kiroshi-gui)
