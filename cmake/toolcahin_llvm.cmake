# Copyright 2024 ETH Zurich and University of Bologna.
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0
#
# Viviane Potocnik <vivianep@iis.ee.ethz.ch>
# Philip Wiese <wiesep@iis.ee.ethz.ch>
# Alberto Dequino <alberto.dequino@unibo.it>

set(CMAKE_EXECUTABLE_SUFFIX ".elf")

set(CMAKE_SYSTEM_NAME Generic)

set(LLVM_TAG llvm)

set(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}/clang)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/clang++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_DIR}/clang)

set(CMAKE_OBJCOPY ${TOOLCHAIN_DIR}/${LLVM_TAG}-objcopy)
set(CMAKE_OBJDUMP ${TOOLCHAIN_DIR}/${LLVM_TAG}-objdump)
set(CMAKE_AR ${TOOLCHAIN_DIR}/${LLVM_TAG}-ar)

add_compile_options("--target=riscv32-unknown-elf")

# Use LLVM LLD linker
add_link_options("-fuse-ld=lld")