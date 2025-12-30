cmake_minimum_required(VERSION 3.22)

# ============================================================================
# BOARD CONFIGURATION - Comment/uncomment to switch between boards
# ============================================================================

# Raspberry Pi Pico 2 (RP2350 - ARM Cortex-M33) - ACTIVE
set(PICO_BOARD pico2)
set(PICO_PLATFORM rp2350-arm-s)

# Raspberry Pi Pico (RP2040 - ARM Cortex-M0+) - INACTIVE
# set(PICO_BOARD pico)
# set(PICO_PLATFORM rp2040)

# Alternative: Raspberry Pi Pico 2 with RISC-V cores
# set(PICO_BOARD pico2)
# set(PICO_PLATFORM rp2350-riscv)

# ============================================================================

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
