# Copyright 2024 ETH Zurich and University of Bologna.
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0
#
# Moritz Scherer <scheremo@iis.ee.ethz.ch>
# Viviane Potocnik <vivianep@iis.ee.ethz.ch>
# Philip Wiese <wiesep@iis.ee.ethz.ch>
# Alberto Dequino <alberto.dequino@unibo.it>

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_COMPILER_WORKS 1)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

if (COMPILER STREQUAL "GCC")
    set(CMAKE_TOOLCHAIN_FILE cmake/toolchain_gcc.cmake)
else ()
    set(CMAKE_TOOLCHAIN_FILE cmake/toolchain_llvm.cmake)
endif ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(magia-sdk LANGUAGES C ASM)

set(ABI ilp32)
set(ISA rv32imac)


message(STATUS "[MAGIA-SDK] ABI                     : ${ABI}")
message(STATUS "[MAGIA-SDK] ISA                     : ${ISA}")
if (${DISASSEMBLE_LIBRARIES})
    message(STATUS "[MAGIA-SDK] DISASSEMBLE_LIBRARIES : ON")
else()
    message(STATUS "[MAGIA-SDK] DISASSEMBLE_LIBRARIES : OFF")
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmake/utils.cmake)

################################################################################
# Add subdirectories                                                           #
################################################################################

# Targets have to be included before the other folders to make them available
# Depending on the target, following static libraries have to added by the targets
add_subdirectory(targets)


# VIVIANEP: Include the picolibc library
include(${CMAKE_CURRENT_LIST_DIR}/cmake/picolibc.cmake)

# Include other subdirectories
add_subdirectory(hal)
# add_subdirectory(devices)
add_subdirectory(drivers)

################################################################################
# Testing                                                                      #
################################################################################

set(VALID_TEST_MODES "simulation" "none")

# Option for TEST_MODE with default value
set(TEST_MODE "none" CACHE STRING "Set what validation target the tests should be run on")

# Check if TEST_MODE is set to a valid option
if(NOT TEST_MODE IN_LIST VALID_TEST_MODES)
    # Collect all error messages into a single string
    set(error_messages "")
    list(APPEND error_messages "[MAGIA-SDK] Invalid TEST_MODE: ${TEST_MODE}")
    list(APPEND error_messages "[MAGIA-SDK] Available options for TEST_MODE are:")
    foreach(mode IN LISTS VALID_TEST_MODES)
        list(APPEND error_messages " - ${mode}")
    endforeach()

    # Convert the list of messages into a single multi-line string
    list(JOIN error_messages "\n" error_message)

    # Raise fatal error with all messages
    message(FATAL_ERROR "${error_message}")
endif()

set(NOC_MODEL_BINARY "magia.bin" CACHE STRING "Path to the simulation binary")
set(PRELOAD_MODE "0" CACHE STRING "Preload mode for simulation")

if (TEST_MODE STREQUAL "simulation")
    enable_testing()

    if(NOT EXISTS ${NOC_MODEL_BINARY})
        message(FATAL_ERROR "NoC model binary ${NOC_MODEL_BINARY} does not exist.")
    endif()

    # Convert PRELOAD_MODE to integer
    if ("${PRELOAD_MODE}" MATCHES "^[0-9]+$")
        set(PRELOAD_MODE_INT ${PRELOAD_MODE})
    else()
        message(FATAL_ERROR "PRELOAD_MODE must be an integer.")
    endif()

    message(STATUS "[MAGIA-SDK] NoC Model Binary      : ${NOC_MODEL_BINARY}")
    message(STATUS "[MAGIA-SDK] Preload Mode          : ${PRELOAD_MODE}")
endif()

add_subdirectory(tests)