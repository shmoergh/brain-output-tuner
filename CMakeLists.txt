cmake_minimum_required(VERSION 3.22)

# Include Pico SDK (from brain-sdk subdirectory)
include(brain-sdk/pico_sdk_import.cmake)

project(output-tuner C CXX ASM)

# Initialize the Pico SDK
pico_sdk_init()

# Add brain-sdk which includes brain libraries
add_subdirectory(brain-sdk)

add_executable(output-tuner main.cpp)

target_link_libraries(output-tuner
	pico_stdlib
	brain-common
	brain-ui
	brain-io)

pico_enable_stdio_usb(output-tuner 1)
pico_enable_stdio_uart(output-tuner 1)
pico_add_extra_outputs(output-tuner)
