# ROOT cmake folder
cmake_minimum_required(VERSION 3.16)

set(PICO_BOARD pico_w)

include(cmake/pico_sdk_import.cmake)

project(FeedbackSystem LANGUAGES C CXX ASM)

pico_sdk_init()

add_subdirectory(src)
