cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_FETCH_FROM_GIT on)
set(PICO_SDK_FETCH_FROM_GIT_PATH ..)
set(PICOTOOL_FETCH_FROM_GIT_PATH ..)
set(PIOASM_FETCH_FROM_GIT_PATH ..)

include(../pico_sdk_import.cmake)

project(motor-sequencer)

pico_sdk_init()

add_executable(motor-sequencer-fw
    src/main.c
)

target_link_libraries(motor-sequencer-fw pico_stdlib)

pico_add_extra_outputs(motor-sequencer-fw)