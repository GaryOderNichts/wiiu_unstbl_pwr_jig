cmake_minimum_required(VERSION 3.18)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "2.0.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 2.0.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(jig C CXX ASM)

# Initialize the SDK
pico_sdk_init()

add_executable(jig main.c)

pico_generate_pio_header(jig ${CMAKE_CURRENT_LIST_DIR}/jig.pio)

target_link_libraries(jig PRIVATE pico_stdlib hardware_pio)

pico_add_extra_outputs(jig)

pico_set_program_name(jig "jig")
pico_set_program_description(jig "Wii U battery jig thing")
pico_set_program_url(jig "")
pico_set_program_version(jig "1")
