cmake_minimum_required(VERSION 3.12)

add_definitions(-DTARGET_BOARD=${TARGET_BOARD})
file(GLOB SRC_FILES src/*.c)

if (${TARGET_BOARD} STREQUAL "RP-PICO")
    project(kiroshi-gui)

    include(pico_sdk_import.cmake)

    pico_sdk_init()

    add_executable(kiroshi-gui test/lcd/main.c test/lcd/lcd_driver.c)
    target_include_directories(kiroshi-gui PUBLIC test/lcd)
    target_link_libraries(kiroshi-gui pico_stdlib hardware_spi kiroshilib)

    pico_enable_stdio_usb(kiroshi-gui 1)
    pico_enable_stdio_uart(kiroshi-gui 0)
    pico_add_extra_outputs(kiroshi-gui)
elseif (${TARGET_BOARD} STREQUAL "SDL2")
    project(kiroshi-gui C CXX)

    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})

    add_executable(kiroshi-gui ${SRC_FILES} test/sdl2/sdl2.c test/sdl2/sdl2_hardware.c)
    target_include_directories(kiroshi-gui PUBLIC src)
    target_link_libraries(kiroshi-gui ${SDL2_LIBRARIES})
endif ()
