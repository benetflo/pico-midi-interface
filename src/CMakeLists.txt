# CMakeLists for all source files and build executables

cmake_minimum_required(VERSION 3.16)

set(PICO_BOARD pico_w)
include(${CMAKE_CURRENT_LIST_DIR}/../cmake/pico_sdk_import.cmake)
pico_sdk_init()

project(firmware LANGUAGES C CXX ASM)

add_executable(${PROJECT_NAME} main.c midi_parser.c)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../inc
)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_uart
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})
