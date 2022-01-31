cmake_minimum_required(VERSION 3.22)

set(PICO_SDK_PATH /usr/share/pico-sdk)

include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

project(pico)
pico_sdk_init()

file(GLOB_RECURSE SRC src/*.cpp)

add_executable(pico_main)
target_sources(pico_main PRIVATE ${SRC})

set_property(TARGET pico_main PROPERTY EXPORT_COMPILE_COMMANDS ON)
set_property(TARGET pico_main PROPERTY CXX_STANDARD 20)
set_property(TARGET pico_main PROPERTY CXX_STANDARD_REQUIRED 20)
set_property(TARGET pico_main PROPERTY COMPILE_OPTIONS -Wall -Wextra -Wpedantic -Wshadow)
target_link_libraries(pico_main pico_stdlib)

pico_enable_stdio_usb(pico_main 1)
pico_enable_stdio_uart(pico_main 0)
pico_add_extra_outputs(pico_main)
